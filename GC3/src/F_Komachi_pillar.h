#pragma once
#include <SpriteBatch.h>
#include <GLSLProgram.h>
#include <Camera2D.h>
#include <GLTexture.h>
#include <DebugRender.h>
#include <LightBatch.h>
#include <F_LuaDynamicObject.h>
#include <F_BaseObject.h>

const unsigned int UPDATE_DIMENSION = 1;
const unsigned int UPDATE_FLASH = 2;
const unsigned int UPDATE_UV = 4;
const unsigned int UPDATE_COLOR = 8;
const unsigned int UPDATE_POS = 16;
const unsigned int UPDATE_LIGHT_ATT = 32;
const unsigned int UPDATE_LIGHT_COLOR = 64;
class F_Komachi_pillar: public Feintgine::F_BaseObject
{
public:
    F_Komachi_pillar();
    ~F_Komachi_pillar();

    void init(const Feintgine::GLTexture & texture_1, const Feintgine::GLTexture & texture_2, const glm::vec2 & pos, const glm::vec2 & dim, const Feintgine::Color & color);

    void draw(Feintgine::SpriteBatch & spriteBatch);
    void drawLight(Feintgine::LightBatch & lightBatch);
    void update(float deltaTime);

    void spawn(const glm::vec2 & pos, const glm::vec2 & dim, const Feintgine::Color & color);

    void setPos(const glm::vec2 & pos) { m_pos = pos; }

    void setMove(const glm::vec2 & targetPos, float time); 

    void setDim(const glm::vec2 & dim) { m_dims = dim; }

    void setColor(const Feintgine::Color & color) { m_color = color; }

    void setExpand(const glm::vec2 & targetDim, float time);

    //void addLightPillar(const glm::vec2 & pos, const glm::vec2 & dim, const Feintgine::Color & color);

    void setLight(const glm::vec4 & color, const glm::vec3 & attenuation, float lifeTime);

    void setLightColorTarget(const Feintgine::Color & targetColor, float time);

    void setLightAttenuationTarget(const glm::vec3 & targetAttenuation, float time);

    // only flash on vertical side
    void setUpdateUV(float time, float rate);

    // only flash on horizontal side
    void setFlash(float time, float freq);

    void setColorChange(const Feintgine::Color & targetColor, float time);

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
    float m_changeColorTime = 0;
    float m_moveTime = 0;

    Feintgine::Color m_targetColor;
    Feintgine::Color m_changeColorRate;

    bool m_visible = false;

    float m_updateUVRate = 0;
    float m_flashFreq = 0;
    float m_alphaChangeRate = 0;

    glm::vec2 m_targetDim;
    glm::vec2 m_extendRate;
    glm::vec2 m_moveRate;
    glm::vec2 m_targetPos;

    glm::vec3 m_attentionua;
    glm::vec3 m_attentionuaTarget;
    glm::vec3 m_attentionuaRate;
    float m_attentionuaTime = 0.0f;
	glm::vec3 t_attentionua;
    

    Feintgine::Color m_lightColor;
    Feintgine::Color m_lightColorTarget;
    Feintgine::Color m_lightColorRate;
    float m_lightColorTime = 0.0f;
    float m_lightLifetime = 0.0f;



    float m_attenuationScale = 0.0f;


};