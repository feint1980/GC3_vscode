
#ifndef COMBAT_DUIPANEL_H
#define COMBAT_DUIPANEL_H

#include "TB_EmptyObject.h"

class CombatGUIPanel 
{
public:
    CombatGUIPanel();
    ~CombatGUIPanel();

    void init(bool isLeft);
    void draw(Feintgine::SpriteBatch & spriteBatch);
    void update(float deltaTime);
    
    private:

    TB_EmptyObject  m_backgroundDock;

    bool m_isLeft;


};


#endif // COMBAT_DUIPANEL_H