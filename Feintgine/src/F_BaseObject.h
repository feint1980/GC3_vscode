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

        void init(unsigned int id,  const glm::vec2 & scale, const Feintgine::F_AnimatedObject & animation,
                const Feintgine::Color & color,const glm::vec2 & vel,const glm::vec2 & pos,float depth,int afterImageCount, float afterImageRate);

        void init(unsigned int id, const glm::vec2 & scale, const std::string & animationPath,
                const Feintgine::Color & color,const glm::vec2 & vel,const glm::vec2 & pos,float depth,int afterImageCount, float afterImageRate);

        void draw(Feintgine::SpriteBatch & spriteBatch);

        void drawLight(Feintgine::LightBatch & lightBatch);

        void setAfterImageScaleRate(float scaleRate); // scale rate for the after image trace

        virtual void update(float deltaTime) = 0;

        unsigned int getID() const { return m_id; }

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
        unsigned int m_id;

    };
}


#endif // !F_BASEOBJECT_H_