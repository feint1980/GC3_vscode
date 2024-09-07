#include "F_Lua_EntityManipulator.h"


F_Lua_EntityManipulator::F_Lua_EntityManipulator()
{


}


F_Lua_EntityManipulator::~F_Lua_EntityManipulator()
{
    m_entity = nullptr;
    m_camera = nullptr;
    tempSlot = nullptr;

    std::cout << "remove manipulator ######################################## \n"; 

}

void F_Lua_EntityManipulator::moveToSlot(F_Lua_BaseEntity * entity, Slot * slot, float time)
{
    m_entity = entity;

    m_state = EntityState::Move;

    m_startPos = m_entity->getPos();
    m_endPos = slot->getPos();
    m_endPos.y += m_entity->getYOffset();

    
    m_completionTime = time;

    m_elaspedTime = 0.0f;
    tempSlot = slot;

}

void F_Lua_EntityManipulator::waitTime(F_Lua_BaseEntity * entity, float time)
{  
    m_entity = entity;

    m_state = EntityState::Wait;

    m_completionTime = time;

    m_elaspedTime = 0.0f;

}


void F_Lua_EntityManipulator::setZoomCamera(F_Lua_BaseEntity * entity,Feintgine::Camera2D * camera, const glm::vec2 & zoomCenter,float zoomTarget, float time)
{

    m_entity = entity;
    m_camera = camera;
    m_scaleTarget = zoomTarget;
    m_completionTime = time;
    m_elaspedTime = 0.0f;
    m_savedScale = m_camera->getScale();
    m_state = EntityState::CameraZoom;
    m_currentScale = m_savedScale;
    m_zoomCenter = zoomCenter;
    m_camSavedPos = m_camera->getPosition();


}


void F_Lua_EntityManipulator::movePortrait(EmptyObject * portrait, const glm::vec2 & TargetPos, float time)
{

    m_portraitTargetPos = TargetPos; 

   // portrait->setPos(TargetPos);
}

void F_Lua_EntityManipulator::setPortaitPos(EmptyObject * portrait, const glm::vec2 & TargetPos)
{
    portrait->setPos(TargetPos);
}



void F_Lua_EntityManipulator::moveToPos(F_Lua_BaseEntity * entity, glm::vec2 pos, float time)
{

    m_entity = entity;
    m_state = EntityState::Move;
    m_startPos = m_entity->getPos();
    m_endPos = pos;
    m_completionTime = time;
    m_elaspedTime = 0.0f;

}


void F_Lua_EntityManipulator::playAnimation(F_Lua_BaseEntity * entity, const std::string & animationName, int time, float totalTime)
{

    m_entity = entity;

    m_state = EntityState::Animation;
    m_completionTime = totalTime;
    if(m_entity)
    {

        m_entity->playAnimation(animationName, time);
    }
    m_elaspedTime = 0;
    if(time == -1)
    {
        m_animationUseTime = true;
    }


}


bool F_Lua_EntityManipulator::update(float deltaTime)
{
    switch(m_state)
    {

        case EntityState::Move:
        {
            if(m_entity)
            {
                    m_elaspedTime += deltaTime;

                    if(m_elaspedTime < m_completionTime)
                    {
                        glm::vec2 tPos = (m_endPos - m_startPos) * (m_elaspedTime / m_completionTime) + m_startPos;
                        
                        m_entity->setPos(tPos);
                        
                    }
                    else
                    {
                        
                        m_entity->setPos(m_endPos);
                        m_state = EntityState::None;
                        m_entity->setCurrentSlot(tempSlot);
                        return true;
                    }   
            }
        }
        break;

        case EntityState::Animation:
        {

            if(m_entity)
            {
                m_elaspedTime += deltaTime;
                //m_entity->update(deltaTime);
                if(m_elaspedTime > m_completionTime)
                {
                    m_state = EntityState::None;
                    return true;
                }
                if(m_entity->isAnimationStoped())
                {
                    m_state = EntityState::None;
                    return true;
                }
            }
        }
        break;
        case EntityState::CameraZoom:
        {
            if(m_camera)
            {
                m_elaspedTime += deltaTime;

                if(m_elaspedTime < m_completionTime)
                {
                      m_currentScale = m_savedScale + (m_scaleTarget - m_savedScale) * (m_elaspedTime / m_completionTime);
                    m_camera->setScale(m_currentScale);
                    m_camera->setPosition(m_camSavedPos + (m_zoomCenter - m_camSavedPos) * (m_elaspedTime / m_completionTime));

                   
                }
                else 
                {
                   
                    m_camera->setScale(m_scaleTarget);
                    m_camera->setPosition(m_zoomCenter);
                    m_state = EntityState::None;
                    return true;
                }
            }
        }
        break;

        case EntityState::Wait:
        {
            if(m_entity)
            {
                
                
                if(m_elaspedTime > m_completionTime)
                {
                    m_state = EntityState::None;
                    return true;
                }
                else 
                {
                    m_elaspedTime += deltaTime;
                    std::cout << m_elaspedTime <<" / " << m_completionTime  << std::endl;
                }
            }
        }
        break;
        case EntityState::None:
        {

            return true;
        }
        break;

        default:
        break;

    }

    return false;
}