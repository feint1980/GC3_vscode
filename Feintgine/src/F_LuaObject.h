#ifndef F_LUA_OBJECT_H
#define F_LUA_OBJECT_H

#include "F_AnimatedObject.h"


namespace Feintgine
{

    class F_LuaObject
    {
        public:
            F_LuaObject();
            ~F_LuaObject();

            void init(const glm::vec2 & pos, const glm::vec2 & scale, const std::string & filePath, const std::string & name, int id, const glm::vec2 & vel = glm::vec2(0,0));

            void draw(Feintgine::SpriteBatch & spriteBatch);

            void update(float deltaTime);

            void setPos(const glm::vec2 & pos)
            {
                m_pos = pos;
            }

            void setDepth(float depth)
            {
                m_depth = depth;
            }

            void setTargetPos(const glm::vec2 & target)
            {
                m_targetPos = target;
            }

            void setColor(const Feintgine::Color & color)
            {
                m_animation.setColor(color);
            }

        protected:
            glm::vec2 m_targetPos; 
            glm::vec2 m_pos;
            glm::vec2 m_scale;
            F_AnimatedObject m_animation;
            std::string m_name;
            float m_depth;
            int m_id;
            glm::vec2 m_vel;


    };

}
#endif