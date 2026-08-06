#ifndef _TEXTRENDERER_H_
#define _TEXTRENDERER_H_
#pragma once

#include "Feintgine.h"
#include <ft2build.h>
#include <freetype/ftstroke.h>
#include "GLTexture.h"
#include <glm/glm.hpp>
#include "Vertex.h"
#include <map>
#include <vector>
// #include <iostream>
#include "GLSLProgram.h"
#include "Camera2D.h"
#include <cstring>
// #include <memory>
// #include "feint_common.h"
#include FT_FREETYPE_H

#pragma execution_character_set("utf-8")

const unsigned char ALIGN_FT_LEFT   = 1;
const unsigned char ALIGN_FT_RIGHT  = 2;
const unsigned char ALIGN_FT_CENTER = 3;

// Atlas dimensions — increase if you load more than ~300 glyphs
static constexpr int TEXT_ATLAS_W = 1024;
static constexpr int TEXT_ATLAS_H = 1024;


struct Character {
    // Legacy: per-glyph texture (used by renderText)
    GLuint     TextureID = 0;

    glm::ivec2 Size;
    glm::ivec2 Bearing;
    GLuint     Advance = 0;

    // Atlas: UV rect in normalised [0..1] coords (used by renderTextBatched)
    glm::vec2  uvMin { 0.f, 0.f };
    glm::vec2  uvMax { 0.f, 0.f };
};

struct UnicodeRange { unsigned long first; unsigned long last; }; 

class TextRenderer {

public:
    TextRenderer();
    ~TextRenderer();

    void  init(int fontSize, const std::vector<UnicodeRange>& ranges, const std::string& fontFilePath);


    void  init(int fontSize, int charCount, const std::string& fontFilePath); // legacy function 

    void  initShader();

    float getTotalScale() const { return totalScale; }

    // Raw (unscaled) recommended line spacing in pixels, from FreeType face metrics
    // at the pixel size passed to init(). Multiply by your render `scale` to get
    // the actual line-to-line vertical step. Used internally so "\n" moves to a
    // new line; exposed publicly in case you need it for layout (e.g. panel sizing).
    float getLineHeight() const { return m_lineHeight; }

    // ----------------------------------------------------------------
    // Legacy path — kept for backward compatibility
    // One texture bind + one draw call per glyph.
    // ----------------------------------------------------------------
    void renderText(
        const Feintgine::Camera2D& camera,
        const std::wstring&        text,
        const glm::vec2&           pos,
        const Feintgine::Color&    color,
        float                      scale,
        unsigned char              justification,
        float                      angleDegrees = 0.f);

    void renderBorderText(
        const Feintgine::Camera2D& camera,
        const std::wstring&        text,
        const glm::vec2&           pos,
        const Feintgine::Color&    color,
        float                      scale,
        unsigned char              justification,
        float                      angleDegrees = 0.f);

    // ----------------------------------------------------------------
    // Batched path — accumulate with renderTextBatched(), flush with end()
    //
    //   textRenderer.begin();
    //   textRenderer.renderTextBatched(...);  // can call N times
    //   textRenderer.renderTextBatched(...);
    //   textRenderer.end(camera);             // ONE draw call for all of the above
    // ----------------------------------------------------------------
    void begin();

    void renderTextBatched(
        const std::wstring&     text,
        const glm::vec2&        pos,
        const Feintgine::Color& color,
        float                   scale,
        unsigned char           justification,
        float                   angleDegrees = 0.f);

    // std::string version
    void renderTextBatched(
        const std::string&     text,
        const glm::vec2&        pos,
        const Feintgine::Color& color,
        float                   scale,
        unsigned char           justification,
        float                   angleDegrees = 0.f);

    // ----------------------------------------------------------------
    // Batched path + inline color markup. Same as renderTextBatched() but
    // parses simple tags in the text to change color mid-string:
    //
    //   textRenderer.renderTextBatchedColored(
    //       L"<white>Hi</white> <color=#38B6FF>friend</color>, welcome!",
    //       pos, defaultColor, scale, ALIGN_FT_LEFT);
    //
    // Built-in names (case-insensitive): white, black, red, green, blue,
    // yellow, cyan, magenta, orange, purple, pink, gray/grey.
    // Custom color: <color=#RRGGBB> or <color=#RRGGBBAA>.
    // Tags nest (a color stays in effect until its matching close tag or
    // the end of the string) and `color` is the base color used outside
    // any tags. A malformed or unrecognized tag (e.g. a stray "<3" or
    // "<some other markup>") is left as literal text rather than eaten,
    // so it doesn't silently vanish from dialogue.
    //
    // Still goes through begin()/end() like renderTextBatched() — each
    // color run lands in the matching BatchSegment automatically.
    void renderTextBatchedColored(
        const std::wstring&     text,
        const glm::vec2&        pos,
        const Feintgine::Color& color,
        float                   scale,
        unsigned char           justification,
        float                   angleDegrees = 0.f);

    // std::string version
    void renderTextBatchedColored(
        const std::string&      text,
        const glm::vec2&        pos,
        const Feintgine::Color& color,
        float                   scale,
        unsigned char           justification,
        float                   angleDegrees = 0.f);


    std::vector<UnicodeRange> defaultVietnameseRanges();
    std::vector<UnicodeRange> defaultRussianRanges();
    std::vector<UnicodeRange> defaultJapaneseKanaRanges();
    std::vector<UnicodeRange> rangesFromText(const std::string& utf8Text);

    // color applies to the entire batch — call begin()/end() per color group if needed
    void end(const Feintgine::Camera2D& camera);

private:
    // Shared helpers
    void   buildVertices(
               const std::wstring& text,
               const glm::vec2&    pos,
               float               scale,
               unsigned char       justification,
               std::vector<GLfloat>& out_verts,
               bool                useAtlasUV,
               float               angleDegrees = 0.f);

    float  calcTextWidth(const std::wstring& text, float scale) const;
    float  calcMinHeight(const std::wstring& text, float scale) const;

    // ---- inline color markup support (renderTextBatchedColored) ----

    // One contiguous run of same-colored text within a line (tags stripped).
    struct ColorRun { std::wstring text; Feintgine::Color color; };

    // Parses <name>/<color=...>/</...> tags out of `text`, returning it as
    // lines (split on '\n', same semantics as buildVertices()'s own '\n'
    // splitting) of colored runs. `baseColor` is used for any text outside
    // all tags.
    std::vector<std::vector<ColorRun>> parseColorMarkup(
        const std::wstring&     text,
        const Feintgine::Color& baseColor) const;

    // Parses one tag's inner text (e.g. "white" or "color=#38B6FF") into a
    // color. Returns false if it's not a recognized name or hex value —
    // callers treat that as "not a color tag" and keep the text literal.
    bool parseColorToken(const std::wstring& tagBody, Feintgine::Color& outColor) const;

    // Finds the BatchSegment for `color` in m_batchSegments, creating one if
    // none matches yet. Used by the colored path; kept separate from the
    // existing renderTextBatched() overloads so their working logic is
    // untouched.
    BatchSegment& getOrCreateSegment(const Feintgine::Color& color);

    // Like buildVertices(), but for pre-parsed multi-color lines: lays out
    // each line's runs left-to-right with a continuous cursor (so a color
    // change doesn't add a gap or overlap), and appends each run's glyph
    // quads into the correct color's BatchSegment via getOrCreateSegment().
    // Justification/vertical-centering are computed per LINE across all of
    // that line's runs combined, so a multi-color line lines up exactly like
    // a single-color one would.
    void buildVerticesMultiColor(
        const std::vector<std::vector<ColorRun>>& lines,
        const glm::vec2&                          pos,
        float                                      scale,
        unsigned char                              justification,
        float                                      angleDegrees);

    // GL / shader
    Feintgine::GLSLProgram m_shader;
    GLuint m_VAO      = 0;
    GLuint m_VBO      = 0;
    GLsizeiptr m_vboCapacity = 0;   // current allocated VBO size in bytes

    // Legacy per-glyph textures
    std::map<wchar_t, Character> Characters;

    // Atlas
    GLuint m_atlasTexture = 0;

    // Batch accumulation — one segment per unique color
    struct BatchSegment {
        Feintgine::Color     color;
        std::vector<GLfloat> verts;
    };
    std::vector<BatchSegment> m_batchSegments;

    // Unused legacy fields kept to avoid breaking anything that references them
    FT_BitmapGlyph glyph_bitmap = nullptr;
    FT_Face        face         = nullptr;
    int            glyph_index  = 0;
    float          m_test_time  = 0.f;

    float totalScale = 0.f;

    // Unscaled line spacing (pixels) from FT_Size_Metrics::height at load time.
    // 0 until init() runs; buildVertices()/renderText() fall back to
    // calcMinHeight()*1.3 if it's still 0 for some reason.
    float m_lineHeight = 0.f;

    // Unscaled ascender/descender (pixels) from FT_Size_Metrics at load time.
    // Used as a fixed vertical anchor reference so pos.y doesn't shift depending
    // on which glyphs happen to be in the current string (see calcMinHeight()).
    // descender is typically negative (extends below the baseline).
    float m_ascender  = 0.f;
    float m_descender = 0.f;
};


/*
    Example :
    textRenderer.begin();
textRenderer.renderTextBatchedColored(
    "<white>Here</white> <blue>is some text</blue>",
    pos, defaultColor, scale, ALIGN_FT_LEFT);
textRenderer.end(camera);

*/

#endif
