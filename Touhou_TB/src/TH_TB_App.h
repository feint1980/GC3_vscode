#pragma once 


#include <IMainGame.h>
#include "TestTBScreen.h"

class TH_TB_App : public Feintgine::IMainGame
{
public:
    TH_TB_App();
    ~TH_TB_App();

    virtual void onInit() override;
    virtual void addScreen() override;
    virtual void onExit() override;

private:

    std::unique_ptr<TestTBScreen> m_test = nullptr;

};

