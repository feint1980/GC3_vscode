
#ifndef TURN_DISPLAYER_H
#define TURN_DISPLAYER_H

#include "CharacterIcon.h"
#include "LuaManager.h"
#include <TextRenderer.h>

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

    void setRollUpdate(bool value) { m_isUpdateRoll = value; }

    std::vector<CharacterIcon *> getSortedCharacters();

private:
    
    void updateRoll(float deltaTime);
    lua_State * m_script = nullptr;

    std::vector< std::shared_ptr<CharacterIcon>> m_characters;
    // std::vector< std::shared_ptr<CharacterIcon>> m_displayCharacters;
    std::unordered_map<std::string, std::shared_ptr<CharacterIcon>> m_charactersMap;
    glm::vec2 m_pos;
    glm::vec2 m_defaultDimentions;


    bool m_isUpdateRoll = false;

    std::unordered_map<std::string, std::string> m_portraitMap;

    int m_readyCount = 0;
};


#endif // TURN_DISPLAYER_H