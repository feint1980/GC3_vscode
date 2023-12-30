#include "F_Komachi_Souls_Object.h"

#define RANDOM_RANGE 500.0f

F_Komachi_Souls_Object::F_Komachi_Souls_Object()
{
   m_pos = glm::vec2(0.0f);
   m_scale = glm::vec2(1.0f);
   m_color = Feintgine::Color(255, 255, 255, 255);
   m_vel = glm::vec2(0.0f);
   m_angle = 0.0f;
   m_depth = 0.0f;
   p_pos = &m_pos;
}

F_Komachi_Souls_Object::~F_Komachi_Souls_Object()
{

}

void F_Komachi_Souls_Object::randomlyDecide()
{
   // range

   float destinationX = feint_common::Instance()->getRandomNum(-RANDOM_RANGE, RANDOM_RANGE);
   float destinationY = feint_common::Instance()->getRandomNum(-RANDOM_RANGE, RANDOM_RANGE);
   
   m_destination = glm::vec2(destinationX, destinationY);
   float speed = feint_common::Instance()->getRandomNum(1.0f, 5.0f);
   m_vel = glm::normalize(m_destination - m_pos) * speed;
}


void F_Komachi_Souls_Object::update(float deltaTime)
{
   m_decideTimer += deltaTime;
   if (m_decideTimer > 150.0f)
   {
      m_decideTimer = 0.0f;
      randomlyDecide();
   }
   //Feintgine::F_BaseObject::update(deltaTime);
   m_pos += m_vel * deltaTime;
   m_animation.setPos(m_pos);
   m_angle = atan2(m_vel.y, m_vel.x) + degreeToRad(270);
   
   m_animation.setAngle(m_angle);
   //m_animation.setColor
   m_animation.setScale(m_scale);
   m_animation.update(deltaTime);
   m_afterImagesParticle.update(deltaTime, m_animation.getCurrentAnimation()->getCurrentIndex(),m_angle);
}
