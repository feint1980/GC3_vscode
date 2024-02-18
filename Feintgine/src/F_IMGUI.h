
#ifndef F_IMGUI_H
#define F_IMGUI_H





#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <map>


namespace Feintgine
{
    class F_IMGUI
    {
    public:
        F_IMGUI();
        ~F_IMGUI();

        void init(SDL_Window * sdlWindow,SDL_GLContext glContext);
        void update();
        void render();
        void begin(ImGuiWindowFlags flags);

        float getFontSize() { return m_fontSize; }  

    private:
        const char* m_glsl_version;

        float m_fontSize = 0;

        bool t_value = true;

    };
}



#endif // !F_IMGUI_H

