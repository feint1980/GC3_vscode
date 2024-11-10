#pragma once
#include <SpriteBatch.h>
#include <GLSLProgram.h>
#include <Camera2D.h>
#include <GLTexture.h>
#include <DebugRender.h>
#include <LightBatch.h>





const int UPDATE_DIMENSION = 1;
const int UPDATE_SPLASH = 2;
const int UPDATE_UV = 4;
class Komachi_pillar
{
public:
    Komachi_pillar();
    ~Komachi_pillar();

    void init(const Feintgine::GLTexture & texture_1, const Feintgine::GLTexture & texture_2, const glm::vec2 & pos, const glm::vec2 & dim, const Feintgine::Color & color);

    void draw(Feintgine::SpriteBatch & spriteBatch);
    void drawLight(Feintgine::LightBatch & lightBatch);
    void update(float deltaTime);

    void setPos(const glm::vec2 & pos) { m_pos = pos; }

    void setDim(const glm::vec2 & dim) { m_dims = dim; }

    void setColor(const Feintgine::Color & color) { m_color = color; }

    void setExpand(const glm::vec2 & maxDim, float rate);

private:

    Feintgine::GLTexture m_texture_1;
    Feintgine::GLTexture m_texture_2; 
    glm::vec2 m_pos;
    glm::vec2 m_dims;
    Feintgine::Color m_color;
    glm::vec4 m_uv = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

    unsigned int m_frameIndex = 0;

    GLuint m_textureId;

    unsigned int m_updateState = 0;

};