#pragma once
#include <SpriteBatch.h>
#include <GLSLProgram.h>
#include <Camera2D.h>
#include <GLTexture.h>
#include <DebugRender.h>
#include <LightBatch.h>
#include <F_LuaDynamicObject.h>


const unsigned int UPDATE_DIMENSION = 1;
const unsigned int UPDATE_FLASH = 2;
const unsigned int UPDATE_UV = 4;
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

    void setExpand(const glm::vec2 & targetDim, float time);

    // only flash on vertical side
    void setUpdateUV(float time, float rate);

    // only flash on horizontal side
    void setFlash(float time, float freq);

private:

    Feintgine::GLTexture m_texture_1;
    Feintgine::GLTexture m_texture_2; 
    glm::vec2 m_pos;
    glm::vec2 m_dims;
    glm::vec2 m_displayDim;
    Feintgine::Color m_color;
    glm::vec4 m_uv = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

    unsigned int m_frameIndex = 0;

    GLuint m_textureId;

    unsigned int m_updateState = 0;

    float m_expandTime = 0;
    float m_flashTime = 0;
    float m_updateUVTime = 0;


    float m_updateUVRate = 0;
    float m_flashFreq = 0;

    glm::vec2 m_targetDim;
    glm::vec2 m_extendRate;

    float m_attenuationScale = 0.0f;


};