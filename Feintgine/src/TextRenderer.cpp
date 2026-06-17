#include "TextRenderer.h"
#include <cmath>

namespace {
    // Rotates `point` around `pivot` by `angleRad` radians (CCW, standard math convention).
    inline glm::vec2 rotateAroundPivot(const glm::vec2& point, const glm::vec2& pivot, float angleRad)
    {
        if (angleRad == 0.f) return point; // skip the trig for the common case

        float s = sinf(angleRad);
        float c = cosf(angleRad);
        glm::vec2 p = point - pivot;
        return glm::vec2(p.x * c - p.y * s, p.x * s + p.y * c) + pivot;
    }
}

std::wstring utf8ToWString(const std::string& utf8)
    {
        std::wstring result;
        result.reserve(utf8.size());

        size_t i = 0;
        const size_t n = utf8.size();
        while (i < n)
        {
            unsigned char b0 = static_cast<unsigned char>(utf8[i]);
            uint32_t codepoint = 0;
            size_t extraBytes = 0;

            if      (b0 < 0x80)            { codepoint = b0;        extraBytes = 0; }
            else if ((b0 & 0xE0) == 0xC0)   { codepoint = b0 & 0x1F; extraBytes = 1; }
            else if ((b0 & 0xF0) == 0xE0)   { codepoint = b0 & 0x0F; extraBytes = 2; }
            else if ((b0 & 0xF8) == 0xF0)   { codepoint = b0 & 0x07; extraBytes = 3; }
            else { ++i; continue; } // invalid leading byte, skip it

            if (i + extraBytes >= n) break; // truncated sequence at end of string

            bool valid = true;
            for (size_t k = 1; k <= extraBytes; ++k)
            {
                unsigned char cb = static_cast<unsigned char>(utf8[i + k]);
                if ((cb & 0xC0) != 0x80) { valid = false; break; }
                codepoint = (codepoint << 6) | (cb & 0x3F);
            }

            if (!valid) { ++i; continue; }
            i += extraBytes + 1;

            if (codepoint > 0xFFFF)
            {
                codepoint -= 0x10000;
                result.push_back(static_cast<wchar_t>(0xD800 + (codepoint >> 10)));
                result.push_back(static_cast<wchar_t>(0xDC00 + (codepoint & 0x3FF)));
            }
            else
            {
                result.push_back(static_cast<wchar_t>(codepoint));
            }
        }
        return result;
    }

    std::vector<UnicodeRange> TextRenderer::defaultVietnameseRanges()
    {
        return {
            { 0x0020, 0x007E }, // Basic Latin (printable ASCII)
            { 0x00A0, 0x00FF }, // Latin-1 Supplement
            { 0x0102, 0x0103 }, // Ă ă
            { 0x0110, 0x0111 }, // Đ đ
            { 0x0128, 0x0129 }, // Ĩ ĩ
            { 0x0168, 0x0169 }, // Ũ ũ
            { 0x01A0, 0x01A1 }, // Ơ ơ
            { 0x01AF, 0x01B0 }, // Ư ư
            { 0x1EA0, 0x1EF9 }, // Vietnamese tone-marked vowels (full block)
        };
    }

    std::vector<UnicodeRange> TextRenderer::defaultRussianRanges()
    {
        return {
            { 0x0020, 0x007E }, // Basic Latin (printable ASCII)
            { 0x0400, 0x04FF }, // Cyrillic — covers Russian (Ё, А–Я, а–я) plus extended Slavic letters
        };
    }

    std::vector<UnicodeRange> TextRenderer::defaultJapaneseKanaRanges()
    {
        return {
            { 0x0020, 0x007E }, // Basic Latin
            { 0x3000, 0x303F }, // CJK Symbols and Punctuation (、。「」etc.)
            { 0x3040, 0x309F }, // Hiragana
            { 0x30A0, 0x30FF }, // Katakana
            { 0xFF00, 0xFFEF }, // Halfwidth/Fullwidth forms (fullwidth ASCII, ｡｢｣ etc.) — optional, drop if unused
        };
    }
    std::vector<UnicodeRange> TextRenderer::rangesFromText(const std::string& utf8Text)
    {
        std::wstring decoded = utf8ToWString(utf8Text); // reuse the decoder from earlier
        std::vector<unsigned long> codepoints;
        codepoints.reserve(decoded.size());
        for (wchar_t wc : decoded)
            codepoints.push_back(static_cast<unsigned long>(static_cast<unsigned short>(wc)));

        std::sort(codepoints.begin(), codepoints.end());
        codepoints.erase(std::unique(codepoints.begin(), codepoints.end()), codepoints.end());

        std::vector<UnicodeRange> ranges;
        for (unsigned long cp : codepoints)
        {
            if (!ranges.empty() && cp == ranges.back().last + 1)
                ranges.back().last = cp; // extend the current run
            else
                ranges.push_back({ cp, cp }); // start a new run
        }
        return ranges;
    }

TextRenderer::TextRenderer()  {}
TextRenderer::~TextRenderer() {}

// ============================================================
//  INIT
// ============================================================

void TextRenderer::init(int fontSize, const std::vector<UnicodeRange>& ranges, const std::string& fontFilePath)
{
    initShader();

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "Error (FREETYPE): Can't init library\n";
        return;
    }

    FT_Face ftFace;
    if (FT_New_Face(ft, fontFilePath.c_str(), 0, &ftFace))
    {
        std::cout << "Error (FREETYPE): Can't load font: " << fontFilePath << "\n";
        FT_Done_FreeType(ft);
        return;
    }

    FT_Set_Pixel_Sizes(ftFace, 0, fontSize);

    FT_Stroker stroker;
    FT_Stroker_New(ft, &stroker);
    FT_Stroker_Set(stroker, 2 * 64, FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    std::vector<unsigned char> atlasData(TEXT_ATLAS_W * TEXT_ATLAS_H * 2, 0);
    int  penX = 0, penY = 0, rowH = 0;
    bool atlasFull = false;

    for (const UnicodeRange& range : ranges)
    {
        if (atlasFull) break;

        for (unsigned long c = range.first; c <= range.last; ++c)
        {
            FT_UInt glyphIndex = FT_Get_Char_Index(ftFace, c);
            if (glyphIndex == 0) continue; // font has no glyph here — skip, don't waste atlas space on .notdef

            if (FT_Load_Glyph(ftFace, glyphIndex, FT_LOAD_DEFAULT))
            {
                std::cout << "ERROR::FREETYPE: Failed to load glyph U+" << std::hex << c << std::dec << "\n";
                continue;
            }

            FT_Glyph glyphStroke;
            FT_Get_Glyph(ftFace->glyph, &glyphStroke);
            FT_Glyph_Stroke(&glyphStroke, stroker, true);
            FT_Glyph_To_Bitmap(&glyphStroke, FT_RENDER_MODE_NORMAL, nullptr, true);
            FT_BitmapGlyph bmpStroke = reinterpret_cast<FT_BitmapGlyph>(glyphStroke);

            unsigned int cx = bmpStroke->bitmap.width;
            unsigned int cy = bmpStroke->bitmap.rows;

            if (FT_Load_Glyph(ftFace, glyphIndex, FT_LOAD_DEFAULT))
            {
                FT_Done_Glyph(glyphStroke);
                continue;
            }

            FT_Glyph glyphFill;
            FT_Get_Glyph(ftFace->glyph, &glyphFill);
            FT_Glyph_To_Bitmap(&glyphFill, FT_RENDER_MODE_NORMAL, nullptr, true);
            FT_BitmapGlyph bmpFill = reinterpret_cast<FT_BitmapGlyph>(glyphFill);

            std::vector<unsigned char> glyphBuf(cx * cy * 2, 0);
            for (unsigned int i = 0; i < cx * cy; ++i)
                glyphBuf[i * 2 + 1] = bmpStroke->bitmap.buffer[i];

            unsigned int fx    = bmpFill->bitmap.width;
            unsigned int fy    = bmpFill->bitmap.rows;
            unsigned int off_x = (cx > fx) ? (cx - fx) / 2 : 0;
            unsigned int off_y = (cy > fy) ? (cy - fy) / 2 : 0;

            for (unsigned int y = 0; y < fy; ++y)
                for (unsigned int x = 0; x < fx; ++x)
                {
                    unsigned int src = y * fx + x;
                    unsigned int dst = (y + off_y) * cx + (x + off_x);
                    glyphBuf[dst * 2 + 0] = bmpFill->bitmap.buffer[src];
                }

            GLuint tex;
            glGenTextures(1, &tex);
            glBindTexture(GL_TEXTURE_2D, tex);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RG8, cx, cy, 0, GL_RG, GL_UNSIGNED_BYTE, glyphBuf.data());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            if (penX + (int)cx > TEXT_ATLAS_W)
            {
                penX  = 0;
                penY += rowH + 1;
                rowH  = 0;
            }

            if (penY + (int)cy > TEXT_ATLAS_H)
            {
                std::cout << "WARNING: Atlas full at codepoint U+" << std::hex << c << std::dec
                           << " — increase TEXT_ATLAS_H or trim ranges\n";
                FT_Done_Glyph(glyphStroke);
                FT_Done_Glyph(glyphFill);
                atlasFull = true;
                break;
            }

            for (unsigned int y = 0; y < cy; ++y)
                for (unsigned int x = 0; x < cx; ++x)
                {
                    int atlasIdx = ((penY + y) * TEXT_ATLAS_W + (penX + x)) * 2;
                    int glyphIdx = (y * cx + x) * 2;
                    atlasData[atlasIdx + 0] = glyphBuf[glyphIdx + 0];
                    atlasData[atlasIdx + 1] = glyphBuf[glyphIdx + 1];
                }

            Character ch;
            ch.TextureID = tex;
            ch.Size      = glm::ivec2(cx, cy);
            ch.Bearing   = glm::ivec2(bmpStroke->left, bmpStroke->top);
            ch.Advance   = ftFace->glyph->advance.x;
            ch.uvMin     = { (float)penX / TEXT_ATLAS_W, (float)penY / TEXT_ATLAS_H };
            ch.uvMax     = { (float)(penX + cx) / TEXT_ATLAS_W, (float)(penY + cy) / TEXT_ATLAS_H };

            Characters.insert({ static_cast<wchar_t>(c), ch });

            penX += (int)cx + 1;
            rowH  = std::max(rowH, (int)cy);

            FT_Done_Glyph(glyphStroke);
            FT_Done_Glyph(glyphFill);
        }
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(1, &m_atlasTexture);
    glBindTexture(GL_TEXTURE_2D, m_atlasTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RG8, TEXT_ATLAS_W, TEXT_ATLAS_H, 0, GL_RG, GL_UNSIGNED_BYTE, atlasData.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    FT_Stroker_Done(stroker);
    FT_Done_Face(ftFace);
    FT_Done_FreeType(ft);

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    m_vboCapacity = sizeof(GLfloat) * 6 * 4 * 256;
    glBufferData(GL_ARRAY_BUFFER, m_vboCapacity, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextRenderer::init(int fontSize, int charCount, const std::string& fontFilePath)
{
    initShader();

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "Error (FREETYPE): Can't init library\n";
        return;
    }

    FT_Face ftFace;
    if (FT_New_Face(ft, fontFilePath.c_str(), 0, &ftFace))
    {
        std::cout << "Error (FREETYPE): Can't load font: " << fontFilePath << "\n";
        FT_Done_FreeType(ft);
        return;
    }

    FT_Set_Pixel_Sizes(ftFace, 0, fontSize);

    // Stroker for 2px outline
    FT_Stroker stroker;
    FT_Stroker_New(ft, &stroker);
    FT_Stroker_Set(stroker, 2 * 64, FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // ----------------------------------------------------------------
    // Atlas scratch buffer (2 bytes per pixel: R=fill, G=outline)
    // ----------------------------------------------------------------
    std::vector<unsigned char> atlasData(TEXT_ATLAS_W * TEXT_ATLAS_H * 2, 0);
    int penX = 0, penY = 0, rowH = 0;

    for (int c = 0; c < charCount; c++)
    {
        FT_UInt glyphIndex = FT_Get_Char_Index(ftFace, c);

        // ---- Outline glyph (G channel) ----
        if (FT_Load_Glyph(ftFace, glyphIndex, FT_LOAD_DEFAULT))
        {
            std::cout << "ERROR::FREETYPE: Failed to load glyph " << c << "\n";
            continue;
        }

        FT_Glyph glyphStroke;
        FT_Get_Glyph(ftFace->glyph, &glyphStroke);
        FT_Glyph_Stroke(&glyphStroke, stroker, true);
        FT_Glyph_To_Bitmap(&glyphStroke, FT_RENDER_MODE_NORMAL, nullptr, true);
        FT_BitmapGlyph bmpStroke = reinterpret_cast<FT_BitmapGlyph>(glyphStroke);

        unsigned int cx = bmpStroke->bitmap.width;
        unsigned int cy = bmpStroke->bitmap.rows;

        // ---- Fill glyph (R channel) ----
        if (FT_Load_Glyph(ftFace, glyphIndex, FT_LOAD_DEFAULT))
            continue;

        FT_Glyph glyphFill;
        FT_Get_Glyph(ftFace->glyph, &glyphFill);
        FT_Glyph_To_Bitmap(&glyphFill, FT_RENDER_MODE_NORMAL, nullptr, true);
        FT_BitmapGlyph bmpFill = reinterpret_cast<FT_BitmapGlyph>(glyphFill);

        // ---- Pack into RG buffer ----
        std::vector<unsigned char> glyphBuf(cx * cy * 2, 0);

        for (unsigned int i = 0; i < cx * cy; ++i)
            glyphBuf[i * 2 + 1] = bmpStroke->bitmap.buffer[i]; // G = outline

        unsigned int fx     = bmpFill->bitmap.width;
        unsigned int fy     = bmpFill->bitmap.rows;
        unsigned int off_x  = (cx > fx) ? (cx - fx) / 2 : 0;
        unsigned int off_y  = (cy > fy) ? (cy - fy) / 2 : 0;

        for (unsigned int y = 0; y < fy; ++y)
            for (unsigned int x = 0; x < fx; ++x)
            {
                unsigned int src = y * fx + x;
                unsigned int dst = (y + off_y) * cx + (x + off_x);
                glyphBuf[dst * 2 + 0] = bmpFill->bitmap.buffer[src]; // R = fill
            }

        // ---- Build per-glyph texture (legacy path) ----
        GLuint tex;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RG8, cx, cy, 0,
                     GL_RG, GL_UNSIGNED_BYTE, glyphBuf.data());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // ---- Place glyph into atlas ----
        if (penX + (int)cx > TEXT_ATLAS_W)
        {
            penX  = 0;
            penY += rowH + 1;
            rowH  = 0;
        }

        if (penY + (int)cy > TEXT_ATLAS_H)
        {
            std::cout << "WARNING: Atlas full at glyph " << c << " — increase TEXT_ATLAS_H\n";
            FT_Done_Glyph(glyphStroke);
            FT_Done_Glyph(glyphFill);
            break;
        }

        for (unsigned int y = 0; y < cy; ++y)
            for (unsigned int x = 0; x < cx; ++x)
            {
                int atlasIdx = ((penY + y) * TEXT_ATLAS_W + (penX + x)) * 2;
                int glyphIdx = (y * cx + x) * 2;
                atlasData[atlasIdx + 0] = glyphBuf[glyphIdx + 0]; // R
                atlasData[atlasIdx + 1] = glyphBuf[glyphIdx + 1]; // G
            }

        // ---- Store Character entry ----
        Character ch;
        ch.TextureID = tex;
        ch.Size      = glm::ivec2(cx, cy);
        ch.Bearing   = glm::ivec2(bmpStroke->left, bmpStroke->top);
        ch.Advance   = ftFace->glyph->advance.x;
        ch.uvMin     = { (float)penX          / TEXT_ATLAS_W, (float)penY          / TEXT_ATLAS_H };
        ch.uvMax     = { (float)(penX + cx)   / TEXT_ATLAS_W, (float)(penY + cy)   / TEXT_ATLAS_H };

        Characters.insert({ c, ch });

        penX += (int)cx + 1;
        rowH  = std::max(rowH, (int)cy);

        FT_Done_Glyph(glyphStroke);
        FT_Done_Glyph(glyphFill);

        // std::cout << "[TextRenderer] atlas texture id: " << m_atlasTexture << "\n";
        // std::cout << "[TextRenderer] characters loaded: " << Characters.size() << "\n";
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    // ---- Upload atlas texture ----
    glGenTextures(1, &m_atlasTexture);
    glBindTexture(GL_TEXTURE_2D, m_atlasTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RG8,
                 TEXT_ATLAS_W, TEXT_ATLAS_H, 0,
                 GL_RG, GL_UNSIGNED_BYTE, atlasData.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    FT_Stroker_Done(stroker);
    FT_Done_Face(ftFace);
    FT_Done_FreeType(ft);

    // ---- VAO / VBO ----
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    m_vboCapacity = sizeof(GLfloat) * 6 * 4 * 256;
    glBufferData(GL_ARRAY_BUFFER, m_vboCapacity, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
    // Unbind VBO *after* glVertexAttribPointer so the VAO records the binding
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextRenderer::initShader()
{
    m_shader.compileShaders("Shaders/textShader.vert", "Shaders/textShader.frag");
    m_shader.addAttribute("TexCoords");
    m_shader.linkShaders();
}

// ============================================================
//  PRIVATE HELPERS
// ============================================================

float TextRenderer::calcTextWidth(const std::wstring& text, float scale) const
{
    float w = 0.f;
    for (wchar_t c : text)
    {
        auto it = Characters.find(c);
        if (it != Characters.end())
            w += (it->second.Advance >> 6) * scale;
    }
    return w;
}

float TextRenderer::calcMinHeight(const std::wstring& text, float scale) const
{
    float minH = 0.f;
    bool  first = true;
    for (wchar_t c : text)
    {
        auto it = Characters.find(c);
        if (it == Characters.end()) continue;
        float h = it->second.Size.y * scale;
        if (first || h < minH) { minH = h; first = false; }
    }
    return minH;
}

void TextRenderer::buildVertices(
    const std::wstring&   text,
    const glm::vec2&      pos,
    float                 scale,
    unsigned char         justification,
    std::vector<GLfloat>& verts,
    bool                  useAtlasUV,
    float                 angleDegrees)
{
    float totalW   = calcTextWidth(text, scale);
    float minH     = calcMinHeight(text, scale);

    float startX = pos.x;
    if      (justification == ALIGN_FT_CENTER) startX = pos.x - totalW / 2.f;
    else if (justification == ALIGN_FT_RIGHT)  startX = pos.x - totalW;

    float curX = startX;
    totalScale = 0.f;

    float angleRad = glm::radians(angleDegrees);

    for (wchar_t wc : text)
    {
        auto it = Characters.find(wc);
        if (it == Characters.end()) continue;
        const Character& ch = it->second;

        GLfloat xpos = curX + ch.Bearing.x * scale;
        GLfloat ypos = (pos.y - (minH / 2.f)) - (ch.Size.y - ch.Bearing.y) * scale;
        GLfloat w    = ch.Size.x * scale;
        GLfloat h    = ch.Size.y * scale;

        float u0, v0, u1, v1;
        if (useAtlasUV)
        {
            u0 = ch.uvMin.x; v0 = ch.uvMin.y;
            u1 = ch.uvMax.x; v1 = ch.uvMax.y;
        }
        else
        {
            u0 = 0.f; v0 = 0.f;
            u1 = 1.f; v1 = 1.f;
        }

        // Rotate every corner of this glyph's quad around `pos` (the anchor the
        // caller passed in). Because rotation is rigid, the whole string rotates
        // together as one block — glyphs keep their relative spacing/baseline.
        glm::vec2 p0 = rotateAroundPivot({ xpos,     ypos + h }, pos, angleRad);
        glm::vec2 p1 = rotateAroundPivot({ xpos,     ypos     }, pos, angleRad);
        glm::vec2 p2 = rotateAroundPivot({ xpos + w, ypos     }, pos, angleRad);
        glm::vec2 p3 = rotateAroundPivot({ xpos + w, ypos + h }, pos, angleRad);

        verts.insert(verts.end(), {
            p0.x, p0.y, u0, v0,
            p1.x, p1.y, u0, v1,
            p2.x, p2.y, u1, v1,
            p0.x, p0.y, u0, v0,
            p2.x, p2.y, u1, v1,
            p3.x, p3.y, u1, v0,
        });

        curX       += (ch.Advance >> 6) * scale;
        totalScale += (ch.Advance >> 6) * scale;
    }
}

// ============================================================
//  LEGACY renderText  (kept for backward compatibility)
//  One draw call per glyph, per-glyph textures.
// ============================================================

void TextRenderer::renderText(
    const Feintgine::Camera2D& camera,
    const std::wstring&        text,
    const glm::vec2&           pos,
    const Feintgine::Color&    color,
    float                      scale,
    unsigned char              justification,
    float                      angleDegrees)
{
    m_shader.use();
    glBindVertexArray(m_VAO);
    glActiveTexture(GL_TEXTURE0);

    glUniform4f(m_shader.getUniformLocation("textColor"),
                color.r, color.g, color.b, color.a);

    glm::mat4 cam = camera.getCameraMatrix();
    glUniformMatrix4fv(m_shader.getUniformLocation("projection"),
                       1, GL_FALSE, &cam[0][0]);

    float totalW = calcTextWidth(text, scale);
    float minH   = calcMinHeight(text, scale);

    float startX = pos.x;
    if      (justification == ALIGN_FT_CENTER) startX = pos.x - totalW / 2.f;
    else if (justification == ALIGN_FT_RIGHT)  startX = pos.x - totalW;

    float curX = startX;
    totalScale = 0.f;

    float angleRad = glm::radians(angleDegrees);

    for (wchar_t wc : text)
    {
        auto it = Characters.find(wc);
        if (it == Characters.end()) continue;
        const Character& ch = it->second;

        GLfloat xpos = curX + ch.Bearing.x * scale;
        GLfloat ypos = (pos.y - (minH / 2.f)) - (ch.Size.y - ch.Bearing.y) * scale;
        GLfloat w    = ch.Size.x * scale;
        GLfloat h    = ch.Size.y * scale;

        glm::vec2 p0 = rotateAroundPivot({ xpos,     ypos + h }, pos, angleRad);
        glm::vec2 p1 = rotateAroundPivot({ xpos,     ypos     }, pos, angleRad);
        glm::vec2 p2 = rotateAroundPivot({ xpos + w, ypos     }, pos, angleRad);
        glm::vec2 p3 = rotateAroundPivot({ xpos + w, ypos + h }, pos, angleRad);

        GLfloat vertices[6][4] = {
            { p0.x, p0.y, 0.f, 0.f },
            { p1.x, p1.y, 0.f, 1.f },
            { p2.x, p2.y, 1.f, 1.f },
            { p0.x, p0.y, 0.f, 0.f },
            { p2.x, p2.y, 1.f, 1.f },
            { p3.x, p3.y, 1.f, 0.f },
        };

        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        curX       += (ch.Advance >> 6) * scale;
        totalScale += (ch.Advance >> 6) * scale;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    m_shader.unuse();
}

void TextRenderer::renderBorderText(
    const Feintgine::Camera2D& camera,
    const std::wstring&        text,
    const glm::vec2&           pos,
    const Feintgine::Color&    color,
    float                      scale,
    unsigned char              justification,
    float                      angleDegrees)
{
    renderText(camera, text, pos, color, scale, justification, angleDegrees);
}

// ============================================================
//  BATCHED path — begin() / renderTextBatched() / end()
//
//  begin()              — clears the accumulation buffer
//  renderTextBatched()  — appends vertices into a per-color segment (no GL calls)
//  end()                — one VBO upload + one draw call per unique color
// ============================================================

void TextRenderer::begin()
{
    m_batchSegments.clear();
}

void TextRenderer::renderTextBatched(
        const std::string&     text,
        const glm::vec2&        pos,
        const Feintgine::Color& color,
        float                   scale,
        unsigned char           justification,
        float                   angleDegrees)
{
    // std::cout << "[TextRenderer] renderTextBatched() text length: " << text.size() << "\n";
    if (text.empty()) return;

    // Find an existing segment for this color, or create one
    BatchSegment* target = nullptr;
    for (auto& seg : m_batchSegments)
    {
        if (seg.color.r == color.r &&
            seg.color.g == color.g &&
            seg.color.b == color.b &&
            seg.color.a == color.a)
        {
            target = &seg;
            break;
        }
    }
    if (!target)
    {
        m_batchSegments.push_back({ color, {} });
        target = &m_batchSegments.back();
    }

    target->verts.reserve(target->verts.size() + text.size() * 6 * 4);

    std::wstring wtext= utf8ToWString(text);
    
    // wtext.assign(text.begin(), text.end());

    buildVertices(wtext, pos, scale, justification, target->verts, true, angleDegrees);
}

void TextRenderer::renderTextBatched(
    const std::wstring&     text,
    const glm::vec2&        pos,
    const Feintgine::Color& color,
    float                   scale,
    unsigned char           justification,
    float                   angleDegrees)
{

    // std::cout << "[TextRenderer] renderTextBatched() text length: " << text.size() << "\n";
    if (text.empty()) return;

    // Find an existing segment for this color, or create one
    BatchSegment* target = nullptr;
    for (auto& seg : m_batchSegments)
    {
        if (seg.color.r == color.r &&
            seg.color.g == color.g &&
            seg.color.b == color.b &&
            seg.color.a == color.a)
        {
            target = &seg;
            break;
        }
    }
    if (!target)
    {
        m_batchSegments.push_back({ color, {} });
        target = &m_batchSegments.back();
    }

    target->verts.reserve(target->verts.size() + text.size() * 6 * 4);
    buildVertices(text, pos, scale, justification, target->verts, true, angleDegrees);
}

void TextRenderer::end(const Feintgine::Camera2D& camera)
{
    // std::cout << "[TextRenderer] end() called, segments: " << m_batchSegments.size() << "\n";
    // for (int i = 0; i < (int)m_batchSegments.size(); i++)
    // std::cout << "  seg[" << i << "] verts: " << m_batchSegments[i].verts.size()
    //             << " color: " << (int)m_batchSegments[i].color.r
    //             << " " << (int)m_batchSegments[i].color.g
    //             << " " << (int)m_batchSegments[i].color.b
    //             << " " << (int)m_batchSegments[i].color.a << "\n";
    if (m_batchSegments.empty())
    {
        return;
    } 

    m_shader.use();
    glBindVertexArray(m_VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_atlasTexture);

    glm::mat4 cam = camera.getCameraMatrix();
    glUniformMatrix4fv(m_shader.getUniformLocation("projection"),
                       1, GL_FALSE, &cam[0][0]);

    GLint colorUniform = m_shader.getUniformLocation("textColor");

    for (const auto& seg : m_batchSegments)
    {
        if (seg.verts.empty()) continue;

        // glUniform4f(colorUniform,
        //             seg.color.r / 255.f,
        //             seg.color.g / 255.f,
        //             seg.color.b / 255.f,
        //             seg.color.a / 255.f);

        glUniform4f(colorUniform,
                seg.color.r ,
                seg.color.g ,
                seg.color.b ,
                seg.color.a );


        GLsizeiptr needed = static_cast<GLsizeiptr>(seg.verts.size() * sizeof(GLfloat));
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        if (needed > m_vboCapacity)
        {
            m_vboCapacity = needed * 2;
            glBufferData(GL_ARRAY_BUFFER, m_vboCapacity, nullptr, GL_DYNAMIC_DRAW);
        }
        glBufferSubData(GL_ARRAY_BUFFER, 0, needed, seg.verts.data());

        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(seg.verts.size() / 4));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    m_shader.unuse();
}
