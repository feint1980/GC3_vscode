


#ifndef _A_CONTEXT_SAVER_H_
#define _A_CONTEXT_SAVER_H_
#include "GLTexture.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <vector>
#include <string>

namespace Feintgine
{
    

    struct textureBuffer
    {
       
         std::string filePath;
         std::vector<unsigned char> buffer;
         textureBuffer(const std::string & filePath, std::vector<unsigned char> & buffer)
         {
             this->filePath = filePath;
             this->buffer = buffer;
         }
    };

    class A_Context_saver
    {
    public:
        A_Context_saver()
        {

        }
        ~A_Context_saver()
        {

        }

        void saveContext(SDL_Window * window,const SDL_GLContext & context){
            p_glContext = context;
            p_window = window;
        }

        void addTextureBuffer(const std::string & filePath, std::vector<unsigned char> & buffer)
        {
            textureBuffer tb(filePath,buffer);
            m_textureBuffers.push_back(std::move(tb));
        }

        static A_Context_saver * getContext_saver()
        {
            if(p_Context_saver == nullptr) 
            {
                p_Context_saver = new A_Context_saver();
            }
            return p_Context_saver; 
        }

        SDL_GLContext getContext(){ return p_glContext; }

        SDL_Window* getWindow(){ return p_window; }

        void addTexture(GLTexture *texture)
        {
            p_glTextures.push_back(texture);
        }

        void addIn(std::vector<unsigned char> * in)
        {
            m_ins.push_back(in);
        }

        void addOut(std::vector<unsigned char> out)
        {
            //m_outs.push_back(out);
        }
        void addWidth(long width)
        {
            m_widths.push_back(width);
        }

        void addHeight(long height)
        {
            m_heights.push_back(height);
        }
        
    


        std::vector<GLTexture *> getTextures()
        {
            return p_glTextures;
        }

        // std::vector <std::vector<unsigned char>> getOuts()
        // {
        //     return m_outs;
        // }
        std::vector <long> getWidths()
        {
            return m_widths;
        }

        std::vector <long> getHeights()
        {
            return m_heights;
        }

        std::vector<textureBuffer> getTextureBuffers()
        {
            return m_textureBuffers;
        }

        private:

        std::vector<GLTexture * > p_glTextures;

        static A_Context_saver * p_Context_saver;
        std::vector< std::vector<unsigned char> *> m_ins;
        //std::vector< std::vector<unsigned char>> m_outs;
        std::vector<long> m_widths;
        std::vector<long> m_heights;
        SDL_GLContext p_glContext;
        SDL_Window * p_window;
        std::vector<textureBuffer> m_textureBuffers;


    };
   
  
}


#endif