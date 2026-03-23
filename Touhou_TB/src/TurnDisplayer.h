
#ifndef TURN_DISPLAYER_H
#define TURN_DISPLAYER_H

#include "CharacterIcon.h"
#include "LuaManager.h"


#define TURN_DISPLAYER_ICON_SIZE 120.0f

class TurnDisplayer
{
public:
    TurnDisplayer();
    ~TurnDisplayer();

    void init(const std::string & scriptPath,lua_State * script);

    void addPortrait(const std::string & characterID,int side);

    void draw(Feintgine::SpriteBatch & spriteBatch);

    CharacterIcon * getCharacterIcon(const std::string & characterID, int side);

    void sortTurnOrder();

private:
    
    lua_State * m_script = nullptr;

    std::vector< std::shared_ptr<CharacterIcon>> m_characters;
    std::unordered_map<std::string, std::shared_ptr<CharacterIcon>> m_charactersMap;
    glm::vec2 m_pos;
    glm::vec2 m_defaultDimentions;

    std::unordered_map<std::string, std::string> m_portraitMap;
};


#endif // TURN_DISPLAYER_H