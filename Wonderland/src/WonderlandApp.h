#pragma once 


#include <IMainGame.h>
#include "Wonderland_MainMenu.h"
#include "WonderlandPrototypeScene.h"



class WonderlandApp : public Feintgine::IMainGame
{
public:
    WonderlandApp();
    ~WonderlandApp();

    virtual void onInit() override;
    virtual void addScreen() override;
    virtual void onExit() override;

private:

    std::unique_ptr<Wonderland_MainMenu> m_mainMenu = nullptr;
    std::unique_ptr<WonderlandPrototypeScene> m_prototypeScene = nullptr;

};

