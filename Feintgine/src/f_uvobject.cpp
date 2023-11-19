#include "f_uvobject.h"


namespace Feintgine {
    
        void F_UVObject::init(const F_Sprite & sprite, const glm::vec2 & pos, const glm::vec2 & scalingFactor, const Feintgine::Color & color)
        {
            m_sprite = sprite;
            m_pos = pos;
            m_scale = scalingFactor;
            m_color = color;
            m_uv = m_sprite.getUV();    
            //m_trackUV = m_uv;
            //m_trackUV.w = m_trackUV.w / m_trackUVYCrop;
        }
        void F_UVObject::init(const GLTexture & texture, const glm::vec2 & pos, const glm::vec2 & scalingFactor, const Feintgine::Color & color)
        {
            m_texture = texture;
            m_pos = pos;
            m_scale = scalingFactor;
            m_color = color;
            m_uv = glm::vec4( 0.0f,0.0f, 1.0f, 1.0f);
            //m_trackUV = glm::vec4( 0.0f,0.0f, 0, 0.125f);
           
        }
    
        void F_UVObject::setPos(const glm::vec2 & pos)
        {
            m_pos = pos;
        }
    
        void F_UVObject::setScaleWithActualSize(const glm::vec2 & dim)
        {
            glm::vec2 scale = dim / m_sprite.getTextureDim();
    
            m_scale = scale;
        }
        
        void F_UVObject::setScale(const glm::vec2 & scale)
        {
            m_scale = scale;
        }

        void F_UVObject::setColor(const Feintgine::Color & color)
        {
            m_color = color;
        }

        void F_UVObject::draw(Feintgine::SpriteBatch & spriteBatch)
        {
            //const glm::vec4 uvrect(0.0f, 0.0f, 1.0f, 1.0f);
            glm::vec4 desRect;// (0, 0, 50, 50);
            desRect.x = m_pos.x - (m_sprite.getDim().x * m_scale.x / 2.0f);
            desRect.y = m_pos.y - (m_sprite.getDim().y * m_scale.y / 2.0f);
            desRect.z = m_scale.x * m_texture.width;
            desRect.w = m_scale.y * m_texture.height;
        
            spriteBatch.draw(desRect, m_uv, m_texture.id, m_depth, m_color, m_angle);
    
        }

        void F_UVObject::update(float deltaTime)
        {

            
           // timer = 0.1f* + deltaTime;

           // std::cout << "update \n";
             m_uv.y -= 0.01f * deltaTime;
            // if(m_uv.y > 0.125)
            // {
            //     m_uv.y =0;
            // }
           
            
           // m_trackUV.y -= 0.001f * deltaTime;
            //m_trackUV.w += 0.001f * deltaTime;
            // if(m_trackUV.y < (m_uv.y + m_uv.w - m_uv.w / m_trackUVYCrop))
            // {
            //     std::cout << "if hit \n";
            //     m_trackUV.y += 0.2f * deltaTime;
            // }
            // else
            // {
            //     std::cout << "else hit \n";
            //       m_trackUV.y = m_uv.y + m_uv.w - m_uv.w / m_trackUVYCrop;
            // }
            
        }

}