#ifndef _TGUI_SCRIPTING_MANAGER_H_
#define _TGUI_SCRIPTING_MANAGER_H_

#include <Window.h>
#include <InputManager.h>
#include <map>
#include <set>
#include "../../TGUI_theme/ThemeCreator.hpp"
#include <async++.h>
#include "LuaManager.h"

#include <FrameBuffer.h>
#include <FrameBufferScreen.h>

struct TGUI_CanvasWrapper
{


    TGUI_CanvasWrapper() {}
    TGUI_CanvasWrapper(tgui::CanvasOpenGL3::Ptr * canvas) : canvas(canvas) {

    }

    void bindDrawCall(std::function<void()> draw) { drawF = draw;}

    // bool isBound = false;
    std::function<void()> drawF;
    tgui::CanvasOpenGL3::Ptr * canvas;
    void draw()
    {

        if(canvas && canvas->get() && canvas->get()->isVisible())
        {
            canvas->get()->bindFramebuffer();
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            glViewport(0, 0, canvas->get()->getSize().x, canvas->get()->getSize().y);
            if(drawF)
            {
                drawF();
            }
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
        
    }

    Feintgine::FrameBuffer m_frameBuffer;
	Feintgine::FrameBufferScreen m_frameBufferScreen;

};

class TGUIScriptingManager
{
    
public:
    TGUIScriptingManager();
    ~TGUIScriptingManager();

    void init(Feintgine::Window * m_window,lua_State * script);

    void update(float deltaTime);
    void draw();
    
    tgui::Label::Ptr createLabel(const std::string & text,float x, float y); 
    
    tgui::RichTextLabel::Ptr createRTLabel(const std::string & text,float x, float y); 

    tgui::Picture::Ptr createPicture(const std::string & path, float x, float y, float width, float height);

    tgui::EditBox::Ptr createEditBox(float x, float y, float width, float height, tgui::Panel::Ptr parent);

    tgui::Panel::Ptr createPanel(float x, float y, float width, float height, tgui::Panel::Ptr parent);

    tgui::Button::Ptr createButton(const std::string & text,float x, float y, float width, float height, tgui::Panel::Ptr parent);

    tgui::ScrollablePanel::Ptr createScrollablePanel(float x, float y, float width, float height,tgui::Panel::Ptr parent = nullptr);

    tgui::TabContainer::Ptr createTabContainer(float x, float y, float width, float height);

    tgui::Tabs::Ptr createTabs(float x, float y, float width, float height, tgui::TabContainer::Ptr parent);

    tgui::CanvasOpenGL3::Ptr * createCanvas(const std::string & name,float x, float y, float width, float height, tgui::Panel::Ptr parent);

    void addDrawCall(const std::string & name, std::function<void()> draw);

    lua_State * getLuaScript() { return m_script; }

    void checkInput(const SDL_Event &  evnt);

    void handleInput(Feintgine::InputManager & inputManager);

    void bindCanvasDrawCall(const std::string & name, std::function<void()> draw);

    std::function<void()> getDrawCall(const std::string & name);

    void cleanup();

    tgui::Gui * getTGUI() { return m_tgui; }

private:

    tgui::Gui * m_tgui = nullptr;
    lua_State * m_script = nullptr;

    std::vector<TGUI_CanvasWrapper> m_canvasList;
    std::unordered_map<std::string, TGUI_CanvasWrapper> m_canvasMap;
    std::unordered_map<std::string, std::function<void()>> m_drawCallMap;

    tgui::CanvasOpenGL3::Ptr  *m_currentCanvas = nullptr;

};


#endif