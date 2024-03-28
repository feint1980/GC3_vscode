

#include <SDL2/SDL.h>
#include <GL/glew.h>

#ifndef _A_CONTEXT_SAVER_H_
#define _A_CONTEXT_SAVER_H_


namespace Feintgine
{
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

        private:

        static A_Context_saver * p_Context_saver;
        SDL_GLContext p_glContext;
        SDL_Window * p_window;
    };
   
  
}


#endif