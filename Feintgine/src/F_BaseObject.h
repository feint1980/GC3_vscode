#ifndef F_BASEOBJECT_H_
#define F_BASEOBJECT_H_

#include "SpriteBatch.h"
#include "F_AnimatedObject.h"
#include "LightBatch.h"

#include "AfterImageParticle.h"

namespace Feintgine
{
    class F_BaseObject
    {
    public:
        F_BaseObject();
        ~F_BaseObject();

        void init(const glm::vec2 & scale, const Feintgine::F_AnimatedObject & animation,
                const Feintgine::Color & color,const glm::vec2 & vel,const glm::vec2 & pos,float depth,int afterImageCount, float afterImageRate);

        void init(const glm::vec2 & scale, const std::string & animationPath,
                const Feintgine::Color & color,const glm::vec2 & vel,const glm::vec2 & pos,float depth,int afterImageCount, float afterImageRate);

        void draw(Feintgine::SpriteBatch & spriteBatch);

        void update(float deltaTime);

    protected:

        glm::vec2 m_pos;
        glm::vec2 * p_pos;
        glm::vec2 m_scale;
        Feintgine::Color m_color;
        Feintgine::F_AnimatedObject m_animation;
        AfterImageObject m_afterImagesParticle;
        glm::vec2 m_vel;
        float m_angle;
        float m_depth;


    };
}


#endif // !F_BASEOBJECT_H_