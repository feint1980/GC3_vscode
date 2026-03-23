
#include "TurnDisplayer.h"

int lua_TurnDisplayer_AddPortrait(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "lua_TurnDisplayer_AddPortrait Error\n";
        return -1;
    }
    else
    {
        TurnDisplayer * turnDisplayer = static_cast<TurnDisplayer*>(lua_touserdata(L, 1));
        std::string characterID = lua_tostring(L, 2);
        int side = lua_tonumber(L, 3);
        turnDisplayer->addPortrait(characterID, side);
        return 0;
    }
    return 0;

}

TurnDisplayer::TurnDisplayer()
{

}

TurnDisplayer::~TurnDisplayer()
{

}

void TurnDisplayer::init(const std::string & scriptPath,lua_State * script)
{

    m_script = script;
    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, scriptPath.c_str())))
    {
        std::cout << "Run script " << scriptPath << " OK \n";
    }
    else
    {
        std::cout << "Run script " << scriptPath << " failed \n";
        return;
    }

    lua_register(m_script, "cpp_TurnDisplayer_AddPortrait", lua_TurnDisplayer_AddPortrait);

    m_pos = glm::vec2(0.0f, 0.0f);
    m_defaultDimentions = glm::vec2(TURN_DISPLAYER_ICON_SIZE, TURN_DISPLAYER_ICON_SIZE);
    m_portraitMap["S_Reimu"] = "./Assets/TB_GUI/faces/Reimu_face.png";
    m_portraitMap["S_Meiling"] = "./Assets/TB_GUI/faces/Meiling_face.png";
    m_portraitMap["S_Yukari"] = "./Assets/TB_GUI/faces/Yukari_face.png";
    m_portraitMap["S_Patchouli"] = "./Assets/TB_GUI/faces/Patchouli_face.png";

}


void TurnDisplayer::sortTurnOrder()
{
    float spacing = TURN_DISPLAYER_ICON_SIZE * 1.05f;
    int totalDisplayer = m_characters.size();

}

void TurnDisplayer::addPortrait(const std::string & characterID, int side)
{

    std::string key = characterID + "_" + std::to_string(side);

    if(m_portraitMap.find(key) != m_portraitMap.end())
    {
        std::cout << "key  " << key << " already added\n";
        return;
    }

    std::shared_ptr<CharacterIcon> icon = std::make_shared<CharacterIcon>();
    icon->init(m_portraitMap[characterID], side, m_defaultDimentions);
    m_characters.push_back(icon);

    m_portraitMap[key] = m_portraitMap[characterID];

}

CharacterIcon * TurnDisplayer::getCharacterIcon(const std::string & characterID, int side)
{

    std::string key = characterID + "_" + std::to_string(side);
    if(m_charactersMap.find(key) != m_charactersMap.end())
    {
        return m_charactersMap[key].get();
    }
    std::cout << "Character " << key << " not found\n";
    return nullptr;
}



void TurnDisplayer::draw(Feintgine::SpriteBatch & spriteBatch)
{
    for (int i = 0; i < m_characters.size(); i++)
    {
        m_characters[i]->draw(spriteBatch);
    }
}