
#include "TurnDisplayer.h"

int lua_TurnDisplayer_AddIcon(lua_State * L)
{
    if(lua_gettop(L) != 4)
    {
        std::cout << "lua_TurnDisplayer_AddIcon Error\n";
        return -1;
    }
    else
    {
        TurnDisplayer * turnDisplayer = static_cast<TurnDisplayer*>(lua_touserdata(L, 1));
        std::string characterID = lua_tostring(L, 2);
        int side = lua_tonumber(L, 3);
        int order = lua_tonumber(L, 4);
        turnDisplayer->addIcon(characterID, side, order);
        return 0;
    }
    return 0;

}

int lua_TurnDisplayer_UpdateOrder(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "lua_TurnDisplayer_UpdateOrder Error\n";
        return -1;
    }
    else
    {
        TurnDisplayer * turnDisplayer = static_cast<TurnDisplayer*>(lua_touserdata(L, 1));
        turnDisplayer->sortTurnOrder();
        return 0;
    }
    return 0;
}

int lua_TurnDisplayer_GetCharacterIcon(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "lua_TurnDisplayer_GetCharacterIcon Error\n";
        return -1;
    }
    else
    {
        TurnDisplayer * turnDisplayer = static_cast<TurnDisplayer*>(lua_touserdata(L, 1));
        std::string characterID = lua_tostring(L, 2);
        int side = lua_tonumber(L, 3);
        CharacterIcon * icon = turnDisplayer->getCharacterIcon(characterID, side);
        lua_pushlightuserdata(L, icon);

        return 1;
    }
    return 0;
}

int lua_TurnDisplayer_SetCharacterIconOrder(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "lua_TurnDisplayer_SetCharacterIconOrder Error\n";
        return -1;
    }
    else
    {
        CharacterIcon * characterIcon = static_cast<CharacterIcon*>(lua_touserdata(L, 1));
        int order = lua_tonumber(L, 2);
        characterIcon->setOrder(order);
        return 0;
    }
    return 0;
}

int lua_TurnDisplayer_SetCharacterIconSpeedChange(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "lua_TurnDisplayer_SetCharacterIconSpeedChange Error\n";
        return -1;
    }
    else
    {
        CharacterIcon * characterIcon = static_cast<CharacterIcon*>(lua_touserdata(L, 1));
        int changeValue = lua_tonumber(L, 2);
        characterIcon->setSpeedChange(changeValue);
        return 0;
    }
    return 0;
}

int lua_TurnDisplayer_SetCharacterIconSpeed(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "lua_TurnDisplayer_SetCharacterIconSpeed Error\n";
        return -1;
    }
    else
    {
        CharacterIcon * characterIcon = static_cast<CharacterIcon*>(lua_touserdata(L, 1));
        float speed = lua_tonumber(L, 2);
        characterIcon->setSpeed(speed);
        return 0;
    }
    return 0;
}

int lua_TurnDisplayer_SetCharacterIconDisplaySpeed(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "lua_TurnDisplayer_SetCharacterIconDisplaySpeed Error\n";
        return -1;
    }
    else
    {
        CharacterIcon * characterIcon = static_cast<CharacterIcon*>(lua_touserdata(L, 1));
        float speed = lua_tonumber(L, 2);
        characterIcon->setDisplaySpeed(speed);
        return 0;
    }
    return 0;
}

int lua_TurnDisplayer_SetUpdateSpeed(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "lua_TurnDisplayer_SetUpdateSpeed Error\n";
        return -1;
    }
    else
    {
        TurnDisplayer * turnDisplayer = static_cast<TurnDisplayer*>(lua_touserdata(L, 1));
        bool value = lua_toboolean(L, 2);
        turnDisplayer->setRollUpdate(value);
        return 0;
    }
    return 0;
}

int lua_TurnDisplayer_SetSelection(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "lua_TurnDisplayer_SetSelection Error\n";
        return -1;
    }
    else
    {
        TurnDisplayer * turnDisplayer = static_cast<TurnDisplayer*>(lua_touserdata(L, 1));
        std::string characterID = lua_tostring(L, 2);
        int side = lua_tonumber(L, 3);
        turnDisplayer->setSelection(characterID, side);
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

    // m_pos.y = 300.0f;
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

    lua_register(m_script, "cpp_TurnDisplayer_AddIcon", lua_TurnDisplayer_AddIcon);

    lua_register(m_script, "cpp_TurnDisplayer_UpdateOrder", lua_TurnDisplayer_UpdateOrder);

    lua_register(m_script, "cpp_TurnDisplayer_GetCharacterIcon", lua_TurnDisplayer_GetCharacterIcon);

    lua_register(m_script, "cpp_TurnDisplayer_SetCharacterIconOrder", lua_TurnDisplayer_SetCharacterIconOrder);

    lua_register(m_script, "cpp_TurnDisplayer_SetCharacterIconSpeedChange", lua_TurnDisplayer_SetCharacterIconSpeedChange);

    lua_register(m_script, "cpp_TurnDisplayer_SetCharacterIconSpeed", lua_TurnDisplayer_SetCharacterIconSpeed);

    lua_register(m_script, "cpp_TurnDisplayer_SetCharacterIconDisplaySpeed", lua_TurnDisplayer_SetCharacterIconDisplaySpeed);

    lua_register(m_script, "cpp_TurnDisplayer_SetUpdateSpeedChange", lua_TurnDisplayer_SetUpdateSpeed);

    lua_register(m_script, "cpp_TurnDisplayer_SetSelection", lua_TurnDisplayer_SetSelection);


    m_pos = glm::vec2(0.0f, 400.0f);
    m_defaultDimentions = glm::vec2(TURN_DISPLAYER_ICON_SIZE, TURN_DISPLAYER_ICON_SIZE);
    m_portraitMap["S_Reimu"] = "./Assets/TB_GUI/faces/Reimu_face.png";
    m_portraitMap["S_Meiling"] = "./Assets/TB_GUI/faces/Meiling_face.png";
    m_portraitMap["S_Yukari"] = "./Assets/TB_GUI/faces/Yukari_face.png";
    m_portraitMap["S_Patchouli"] = "./Assets/TB_GUI/faces/Patchouli_face.png";

    m_selector.init(Feintgine::ResourceManager::getTexture("./Assets/TB_GUI/faces/face_border.png"), m_pos,glm::vec2(TURN_DISPLAYER_ICON_SIZE) * 1.075f, Feintgine::Color(0,255,0, 255));
}

void TurnDisplayer::sortTurnOrder()
{
    float spacing = TURN_DISPLAYER_ICON_SIZE * 1.1f;
    int totalDisplayer = m_characters.size();
    float width = spacing * totalDisplayer;
    float leftPos = m_pos.x - width / 2.0f;
    float centerLeftPos = leftPos + spacing / 2.0f;

    m_isBusy = true;
    InfoHolder::getInstance()->getLuaPollEvent()->sendPollSignal("TurnDisplayReady", false);

    InfoHolder::getInstance()->getLuaEventPipeline()->sendPollSignal("TurnDisplayerIsReady", false);
    
    std::vector<CharacterIcon *> sortedCharacters = getSortedCharacters();

    for (int i = 0; i < sortedCharacters.size(); i++)
    {
        sortedCharacters[i]->setTargetPos(glm::vec2(centerLeftPos, m_pos.y));
        centerLeftPos += spacing;
    }
}

std::vector<CharacterIcon*> TurnDisplayer::getSortedCharacters()
{
    std::vector<CharacterIcon*> result;
    result.reserve(m_characters.size());

    for (auto& c : m_characters)
        result.push_back(c.get());

    std::sort(result.begin(), result.end(), [](CharacterIcon* a, CharacterIcon* b) {
        return a->getOrder() < b->getOrder();  // ascending: lowest order first
    });

    return result;
}

// std::vector<CharacterIcon *> TurnDisplayer::getSortedCharacters()
// {
//     std::vector<CharacterIcon *> bCharacters;
    
//     std::vector<CharacterIcon *> rCharacters;
//     for (int i = 0; i < m_characters.size(); i++)
//     {
//         bCharacters.push_back(m_characters[i].get());
//     }

//     // sort by order
//     int min = 15;
//     int index = -1;
//     while(bCharacters.size() > 0)
//     {
//         for(int i = 0; i < bCharacters.size(); i++)
//         {
//             if(bCharacters[i]->getOrder() < min)
//             {
//                 min = bCharacters[i]->getOrder();
//                 index = i;
//             }
//         }

//         rCharacters.push_back(bCharacters[index]);
//         bCharacters.erase(bCharacters.begin() + index);
//         min = 15;
//         index = -1;
//     }

//     std::cout << "sort done \n";
//     return rCharacters;
// }

void TurnDisplayer::update(float deltaTime)
{
    if(m_isBusy)
    {
        if(!isDisplayBusy())
        {
            m_isBusy = false;
            InfoHolder::getInstance()->getLuaPollEvent()->sendPollSignal("TurnDisplayReady", true);
            InfoHolder::getInstance()->getLuaEventPipeline()->sendPollSignal("TurnDisplayerIsReady", true);
            
        }
    }

    if(m_isUpdateRoll)
    {
        updateRoll(deltaTime);
    }
    else
    {
        if(m_isUpdateSelector)
        {
            updateSelector(deltaTime);
        }    
    }
    
    for (std::size_t i = 0; i < m_characters.size(); i++)
    {
        m_characters[i]->update(deltaTime);
    }
    m_selectorPos.y = m_pos.y;
    
    // if(isDisplayReady())
    // {
    //     InfoHolder::getInstance()->getLuaEventPipeline()->sendPollSignal("TurnDisplayerIsReady", true);
    // }
    // else
    // {
    //     InfoHolder::getInstance()->getLuaEventPipeline()->sendPollSignal("TurnDisplayerIsReady", false);
    // }
}

bool TurnDisplayer::isDisplayBusy()
{
    for (std::size_t i = 0; i < m_characters.size(); i++)
    {
        if(m_characters[i]->getState() != 0) // not 0
        {
            // std::cout << "found state " << m_characters[i]->getState() << "\n";
            return true;
        }
    }
    return false;

}

void TurnDisplayer::updateRoll(float deltaTime)
{   

    for(std::size_t i = 0; i < m_rollChracters.size(); i++)
    {
        if(m_rollChracters[i]->getUpdateSpeedChangeState() == 3)
        {
            m_rollChracters[i]->setUpdateSpeedChangeState(0);
            m_rollChracters.erase(m_rollChracters.begin() + i);
            // std::cout << "ready increase \n";
        }
    }
    if(m_rollChracters.size() == 0)
    {

        m_isUpdateRoll = false;

        sortTurnOrder();
    }
}

void TurnDisplayer::setSelection(const std::string & characterID, int side)
{

    std::cout << "setSelection data check \n";

    std::cout << "TurnDisplayer::setSelection " << characterID << " " << side << "\n";
    CharacterIcon * selected =  getCharacterIcon(characterID, side);
    if(selected != nullptr)
    {
        m_selectorTargetPos = selected->getPos();
        std::cout << "target is " << m_selectorTargetPos.x << " " << m_selectorTargetPos.y << "\n"; 
        m_isUpdateSelector = true;
    }
    else
    {
        std::cout << "TurnDisplayer::setSelection character not found \n";
    }
}

void TurnDisplayer::updateSelector(float deltaTime)
{
    
    float distance = glm::distance( m_selectorTargetPos, m_selectorPos);
    
    if (distance >  0.5f)
    {
        float step = 35.0f * deltaTime;
        m_selectorPos += glm::normalize(m_selectorTargetPos - m_selectorPos) * std::min(step, distance);
    
    }
    else
    {
        m_selectorPos = m_selectorTargetPos;
        m_isUpdateSelector = false;
    }
    m_selector.setPos(m_selectorPos);
}

void TurnDisplayer::addIcon(const std::string & characterID, int side, int order)
{

    std::string key = characterID + "_" + std::to_string(side);
    std::shared_ptr<CharacterIcon> icon ;//= std::make_shared<CharacterIcon>();
    if(m_portraitMap.find(key) != m_portraitMap.end())
    {
        std::cout << "key  " << key << " already added\n";
        icon = m_charactersMap[key];
    }
    else
    {
        icon = std::make_shared<CharacterIcon>();
    }

    
    icon->init(m_portraitMap[characterID], side, order, m_defaultDimentions);
    m_characters.push_back(icon);
    
    m_charactersMap[key] = icon; 

}

CharacterIcon * TurnDisplayer::getCharacterIcon(const std::string & characterID, int side)
{

    // for(auto & c : m_charactersMap)
    // {
    //     std::cout << "name " << c.first << "===========\n";
    //     std::cout << "order " << c.second->getOrder() << " | speed | " << c.second->getSpeed() << " pos " << c.second->getPos().x << " " << c.second->getPos().y << "\n"; 
    // }


    std::string key = characterID + "_" + std::to_string(side);

    std::cout << "key search is " << key << "\n";

    if(m_charactersMap.find(key) != m_charactersMap.end())
    {
        return m_charactersMap[key].get();
    }
    std::cout << "Character " << key << " not found\n";
    return nullptr;
}

void TurnDisplayer::draw(Feintgine::SpriteBatch & spriteBatch)
{
    for (std::size_t i = 0; i < m_characters.size(); i++)
    {
        m_characters[i]->draw(spriteBatch);
    }


    m_selector.draw(spriteBatch);
}

void TurnDisplayer::drawText(TextRenderer * textRenderer)
{
    if(!textRenderer)
    {
        return;
    }
    for(std::size_t i = 0; i < m_characters.size(); i++)
    {
        m_characters[i]->drawText(textRenderer);
    }
}