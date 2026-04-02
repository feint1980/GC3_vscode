#include "CharacterIcon.h"

CharacterIcon::CharacterIcon()
{

}

CharacterIcon::~CharacterIcon()
{
    
}
void CharacterIcon::init(const std::string & texturePath,int side , int order, const glm::vec2 & dim)
{
    m_portrait.init(Feintgine::ResourceManager::getTexture(texturePath), m_pos,dim,Feintgine::Color(255, 255, 255, 255));
    m_side = side;
    m_order = order;
    Feintgine::Color red = Feintgine::Color(255, 0, 0, 255);
    Feintgine::Color blue = Feintgine::Color(0, 0, 255, 255);
    m_dim = dim;
    if(m_side == 1)
    {
        m_border.init(Feintgine::ResourceManager::getTexture("./Assets/TB_GUI/faces/face_border.png"), m_pos,dim * 1.07f,red);
    }
    else if (m_side == 2)
    {
        m_border.init(Feintgine::ResourceManager::getTexture("./Assets/TB_GUI/faces/face_border.png"), m_pos,dim * 1.07f,blue);
    }
    m_portrait.setDepth(2);
    m_portrait.setDepth(3);

}

void CharacterIcon::draw(Feintgine::SpriteBatch & spriteBatch)
{
    m_portrait.draw(spriteBatch);
    m_border.draw(spriteBatch);
}

void CharacterIcon::drawText(TextRenderer * textRenderer)
{
    // std::wstring text = std::to_wstring(m_displaySpeed);
    std::wostringstream wss;
    wss << std::fixed << std::setprecision(2) << m_displaySpeed;
    std::wstring text = wss.str();
    m_displaySpeedPos = m_pos;
    m_displaySpeedPos.y -= (m_dim.y * 0.4f);
    textRenderer->renderTextBatched(text, m_displaySpeedPos, Feintgine::Color(255, 255, 255, 255), 1.0f, ALIGN_FT_CENTER);   
    if(m_isUpdateSpeedChange != 0)
    {
        wss = std::wostringstream();
        wss << std::fixed << std::setprecision(2) << m_speedChange;
        text = wss.str();
        std::wstring sign = L"";
        Feintgine::Color color = Feintgine::Color(255,0, 0, 255);
        if(m_speedChange >= 0)
        {
            sign = L"+";
            color = Feintgine::Color(0, 255, 0, 255);
        }
        text = sign + text;

        // text = std::to_wstring(m_speedChange); 
        textRenderer->renderTextBatched(text, m_speedChangeTextPos, color, 1.0f, ALIGN_FT_CENTER);
    } 

}

void CharacterIcon::update(float deltaTime)
{
    updateMovement(deltaTime);    
    updateSpeedChange(deltaTime);
}


void CharacterIcon::updateMovement(float deltaTime)
{
    if(m_isUpdateMovement)
    {
        float distance = glm::distance( m_targetPos, m_pos);
        if (distance >  0.5f)
        {
             float step = 15.0f * deltaTime;
            // clamp step to never exceed remaining distance
            m_pos += glm::normalize(m_targetPos - m_pos) * std::min(step, distance);
            
        }
        else
        {
            m_pos = m_targetPos;
            m_isUpdateMovement = false;
            m_state &= ~ICON_POS_CHANGE;

            
            // std::cout << "order " << m_order << " pos " << m_pos.x << " " << m_pos.y << " speed " << m_speed << "\n";
            // InfoHolder::getInstance()->getLuaEventPipeline()->sendPollSignal("TurnDisplayerIsReady", true);
            // std::cout << "update done \n";
        }
        m_portrait.setPos(m_pos);
        m_border.setPos(m_pos);
    }

}
void CharacterIcon::updateSpeedChange(float deltaTime)
{
    if(m_isUpdateSpeedChange != 0)
    {
        if(m_isUpdateSpeedChange == 1)
        {
            float distance = glm::distance( m_speedChangeTextPosOffset, m_speedChangeTextPos);
            if (distance >  0.5f)
            {
                float step = 15.0f * deltaTime;
                // clamp step to never exceed remaining distance
                m_speedChangeTextPos += glm::normalize(m_speedChangeTextPosOffset - m_speedChangeTextPos) * std::min(step, distance);
                
            }
            else
            {
                m_speedChangeTextPos = m_speedChangeTextPosOffset;
                m_isUpdateSpeedChange +=1;
            }
        }
        else if(m_isUpdateSpeedChange == 2)
        {
            m_counter += deltaTime;
            if(m_counter > 50.0f)
            {
                float distance = glm::distance( m_speedChangeTextPos, m_displaySpeedPos );
                if (distance >  0.5f)
                {
                    float step = 15.0f * deltaTime;
                    // clamp step to never exceed remaining distance
                    m_speedChangeTextPos += glm::normalize(m_displaySpeedPos - m_speedChangeTextPos) * std::min(step, distance);
                    
                }
                else
                {
                    m_speedChangeTextPos = m_displaySpeedPos;
                    m_isUpdateSpeedChange +=1;
                    m_displaySpeed = m_speed;// + m_speedChange;
                    // m_state &= ~ICON_SPEED_CHANGE;

                    
                }
            }    
        }
        
    }
}