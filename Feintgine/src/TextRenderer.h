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
#include <iostream>
#include "GLSLProgram.h"
#include "Camera2D.h"
#include <cstring>
#include <memory>
#include "feint_common.h"
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

class TextRenderer {

public:
    TextRenderer();
    ~TextRenderer();

    void  init(int fontSize, int charCount, const std::string& fontFilePath);
    void  initShader();

    float getTotalScale() const { return totalScale; }

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
        unsigned char              justification);

    void renderBorderText(
        const Feintgine::Camera2D& camera,
        const std::wstring&        text,
        const glm::vec2&           pos,
        const Feintgine::Color&    color,
        float                      scale,
        unsigned char              justification);

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
        unsigned char           justification);

    // std::string version
    void renderTextBatched(
        const std::string&     text,
        const glm::vec2&        pos,
        const Feintgine::Color& color,
        float                   scale,
        unsigned char           justification);



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
               bool                useAtlasUV);

    float  calcTextWidth(const std::wstring& text, float scale) const;
    float  calcMinHeight(const std::wstring& text, float scale) const;

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
};

#endif
