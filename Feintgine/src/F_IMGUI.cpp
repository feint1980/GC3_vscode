#include "F_IMGUI.h"

namespace Feintgine
{
    F_IMGUI::F_IMGUI()
    {
 
    }

    F_IMGUI::~F_IMGUI()
    {
    }

    void F_IMGUI::init(SDL_Window * sdlWindow,SDL_GLContext glContext)
    {

        m_glsl_version = "#version 130";
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        std::cout << "init imgui\n";
        IMGUI_CHECKVERSION();
        
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;     // Enable Gamepad Controls

        // ImGui::SetNextWindowPos(ImVec2(0,0), ImGuiCond_FirstUseEver); // ImGuiCond_FirstUseEver
        // ImGui::SetNextWindowSize(ImVec2(1600,800), ImGuiCond_FirstUseEver);

       // io.DisplaySize = ImVec2(1600,800);

       // 

        // io.Fonts->AddFontFromFileTTF("assets/fonts/Roboto-Bold.ttf", 24.0f);

        // m_fontSize = 24.0f;

        // //io.Fonts->
        // // Setup Dear ImGui style
        // ImGui::StyleColorsDark();
        // //ImGui::StyleColorsClassic();

        // ImGui_ImplSDL2_InitForOpenGL(sdlWindow, glContext);
        // ImGui_ImplOpenGL3_Init(m_glsl_version);

        // ImGui_ImplSDL2_InitForOpenGL(Feintgine::Window::getInstance().getWindow(), Feintgine::Window::getInstance().getGLContext());
    }

    void F_IMGUI::update()
    {
    }

    void F_IMGUI::begin(ImGuiWindowFlags flags)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("main_tc",&t_value, flags);
    }

    void F_IMGUI::render()
    {

        // ImGui::Begin("Test", &t_value, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus);  

        // ImGui::SetCursorPos(ImVec2(500,500));       
        // ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0,255,0,255));  
        // ImGui::Text("Hello, world!");
        // ImGui::PopStyleColor();
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    }
}