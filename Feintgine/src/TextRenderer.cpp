#include "TextRenderer.h"

TextRenderer::TextRenderer()  {}
TextRenderer::~TextRenderer() {}

// ============================================================
//  INIT
// ============================================================

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
    bool                  useAtlasUV)
{
    float totalW   = calcTextWidth(text, scale);
    float minH     = calcMinHeight(text, scale);

    float startX = pos.x;
    if      (justification == ALIGN_FT_CENTER) startX = pos.x - totalW / 2.f;
    else if (justification == ALIGN_FT_RIGHT)  startX = pos.x - totalW;

    float curX = startX;
    totalScale = 0.f;

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

        verts.insert(verts.end(), {
            xpos,   ypos + h, u0, v0,
            xpos,   ypos,     u0, v1,
            xpos+w, ypos,     u1, v1,
            xpos,   ypos + h, u0, v0,
            xpos+w, ypos,     u1, v1,
            xpos+w, ypos + h, u1, v0,
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
    unsigned char              justification)
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

    for (wchar_t wc : text)
    {
        auto it = Characters.find(wc);
        if (it == Characters.end()) continue;
        const Character& ch = it->second;

        GLfloat xpos = curX + ch.Bearing.x * scale;
        GLfloat ypos = (pos.y - (minH / 2.f)) - (ch.Size.y - ch.Bearing.y) * scale;
        GLfloat w    = ch.Size.x * scale;
        GLfloat h    = ch.Size.y * scale;

        GLfloat vertices[6][4] = {
            { xpos,   ypos+h, 0.f, 0.f },
            { xpos,   ypos,   0.f, 1.f },
            { xpos+w, ypos,   1.f, 1.f },
            { xpos,   ypos+h, 0.f, 0.f },
            { xpos+w, ypos,   1.f, 1.f },
            { xpos+w, ypos+h, 1.f, 0.f },
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
    unsigned char              justification)
{
    renderText(camera, text, pos, color, scale, justification);
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
        unsigned char           justification)
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

    std::wstring wtext;
    wtext.assign(text.begin(), text.end());

    buildVertices(wtext, pos, scale, justification, target->verts, true);
}

void TextRenderer::renderTextBatched(
    const std::wstring&     text,
    const glm::vec2&        pos,
    const Feintgine::Color& color,
    float                   scale,
    unsigned char           justification)
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
    buildVertices(text, pos, scale, justification, target->verts, true);
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
    if (m_batchSegments.empty()) return;


    

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
