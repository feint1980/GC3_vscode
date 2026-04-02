
#ifndef TURN_DISPLAYER_H
#define TURN_DISPLAYER_H

#include "CharacterIcon.h"
#include "LuaManager.h"
#include <TextRenderer.h>
#include "InfoHolder.h"

#define TURN_DISPLAYER_ICON_SIZE 100.0f

class TurnDisplayer
{
public:
    TurnDisplayer();
    ~TurnDisplayer();

    void init(const std::string & scriptPath,lua_State * script);

    void addIcon(const std::string & characterID, int side, int order);

    void draw(Feintgine::SpriteBatch & spriteBatch);

    void drawText(TextRenderer * textRenderer);

    CharacterIcon * getCharacterIcon(const std::string & characterID, int side);

    void update(float deltaTime);

    void sortTurnOrder();

    void setSelection(const std::string & characterID, int side);

    void setRollUpdate(bool value) {

        // std::cout << "C++ setRollUpdate called \n"; 
        m_isUpdateRoll = value;
        
        // ensure roll character always empty

        m_rollChracters.clear();
        
        for(int i = 0 ; i < m_characters.size(); i++)
        {
            m_rollChracters.push_back(m_characters[i].get());
        }
        // std::cout << "C++ setRollUpdate end \n"; 
    }

    std::vector<CharacterIcon *> getSortedCharacters();

    bool isDisplayBusy();

private:
    
    void updateRoll(float deltaTime);
    void updateSelector(float deltaTime);
    lua_State * m_script = nullptr;

    std::vector< std::shared_ptr<CharacterIcon>> m_characters;
    std::vector<CharacterIcon *> m_rollChracters;
    // std::vector< std::shared_ptr<CharacterIcon>> m_displayCharacters;
    std::unordered_map<std::string, std::shared_ptr<CharacterIcon>> m_charactersMap;
    glm::vec2 m_pos;
    glm::vec2 m_defaultDimentions;

    bool m_isUpdateRoll = false;

    bool m_isBusy = false;

    bool m_isUpdateSelector = false;
    std::unordered_map<std::string, std::string> m_portraitMap;

    int m_readyCount = 0;

    EmptyObject m_selector;
    glm::vec2 m_selectorPos;
    glm::vec2 m_selectorTargetPos;
};


#endif // TURN_DISPLAYER_H