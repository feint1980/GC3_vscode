#include "CombatField.h"

int lua_CombatField_AddSlot(lua_State * L)
{
    if(lua_gettop(L) != 4)
    {
        std::cout << "gettop failed (lua_CombatFiled_AddSlot) " << lua_gettop(L) << "\n";
        return -1;
    }

    CombatField * host = static_cast<CombatField*>(lua_touserdata(L, 1));
    int collumn = lua_tonumber(L, 2); // x
    int row = lua_tonumber(L, 3); // y
    int side = lua_tonumber(L, 4);
    host->addSlot(collumn, row, side);
    return 0;
}

int lua_CombatField_AddCharacter(lua_State * L)
{
    if(lua_gettop(L) != 6)
    {
        std::cout << "gettop failed (lua_CombatFiled_AddCharacter) " << lua_gettop(L) << "\n";
        return -1;
    }

    CombatField * host = static_cast<CombatField*>(lua_touserdata(L, 1));
    int collumn = lua_tonumber(L, 2); // x
    int row = lua_tonumber(L, 3); // y
    int side = lua_tonumber(L, 4);
    std::string characterID = lua_tostring(L, 5);
    std::string portraitPath = lua_tostring(L, 6);
    CombatCharacter * character = host->addCharacter(collumn, row, side, characterID, portraitPath);

    lua_pushlightuserdata(L, character);

    return 1;
}

int lua_CombatField_GetSlot(lua_State * L)
{
    if(lua_gettop(L) != 4)
    {
        std::cout << "gettop failed (lua_CombatField_GetSlot) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        CombatField * host = static_cast<CombatField*>(lua_touserdata(L, 1));
        int collumn = lua_tonumber(L, 2); // x
        int row = lua_tonumber(L, 3); // y
        int side = lua_tonumber(L, 4);
        CSlot * slot = host->getSlot(collumn, row, side);
        lua_pushlightuserdata(L, slot);
        return 1;
    }
    return 0;
}

int lua_CombatField_GetCharacter(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_CombatField_GetCharacter) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        CombatField * host = static_cast<CombatField*>(lua_touserdata(L, 1));
        std::string characterID = lua_tostring(L, 2);
        int side = lua_tonumber(L, 3);
        CombatCharacter * character = host->getCharacter(characterID, side);
        lua_pushlightuserdata(L, character);

        return 1;
    }
    return 0;
}

int lua_CombatField_SetCharacterStatFloat(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_CombatField_SetCharacterStatFloat) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        CombatCharacter * character = static_cast<CombatCharacter*>(lua_touserdata(L, 1));
        std::string statName = lua_tostring(L, 2);
        float value = lua_tonumber(L, 3);
        character->setFloatValue(statName, value);
        return 0;
    }
    return 0;
}

int lua_CombatField_SetCharacterStatStr(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_CombatField_SetCharacterStatStr) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        CombatCharacter * character = static_cast<CombatCharacter*>(lua_touserdata(L, 1));
        std::string statName = lua_tostring(L, 2);
        std::string value = lua_tostring(L, 3);
        character->setStringValue(statName, value);
        return 0;
    }
    return 0;
}


int lua_CombatField_ListCharacterStats(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_CombatField_ListCharacterStats) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        CombatCharacter * character = static_cast<CombatCharacter*>(lua_touserdata(L, 1));
        character->listStats();
        return 0;
    }
    return 0;
}

int lua_CombatField_GetCharacterStatFloat(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_CombatField_GetCharacterStatFloat) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        CombatCharacter * character = static_cast<CombatCharacter*>(lua_touserdata(L, 1));
        std::string statName = lua_tostring(L, 2);
        float value = character->getFloatValue(statName);
        lua_pushnumber(L, value);

        return 1;
    }
    return 0;
}

int lua_CombatField_GetCharacterStatStr(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_CombatField_GetCharacterStatStr) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        CombatCharacter * character = static_cast<CombatCharacter*>(lua_touserdata(L, 1));
        std::string statName = lua_tostring(L, 2);
        std::string value = character->getStringValue(statName);
        lua_pushstring(L, value.c_str());

        return 1;
    }
    return 0;
}

int lua_getBannerInstance(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_getBannerInstance) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        CombatField * host = static_cast<CombatField*>(lua_touserdata(L, 1));
        lua_pushlightuserdata(L, host->getBanner());
        return 1;
    }
    return 0;
}

int lua_Banner_SetMsg(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_Banner_SetMsg) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        Banner * banner = static_cast<Banner*>(lua_touserdata(L, 1));
        std::string msg = lua_tostring(L, 2);
        banner->setMessage(msg);
        return 0;
    }
    return 0;
}

int lua_Banner_ShowMsg(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_Banner_ShowMsg) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        Banner * banner = static_cast<Banner*>(lua_touserdata(L, 1));
        std::string msg = lua_tostring(L, 2);
        banner->showMessage(msg);
        return 0;
    }
    return 0;
}

int lua_Banner_SetVisible(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_Banner_SetVisible) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        Banner * banner = static_cast<Banner*>(lua_touserdata(L, 1));
        bool visible = lua_toboolean(L, 2);
        banner->setVisible(visible);
        return 0;
    }
    return 0;
}

CombatField::CombatField()
{
    // m_slotIndexMap = std::unordered_map<glm::ivec3, int>();
}

CombatField::~CombatField()
{

}

void CombatField::init(const std::string & scriptPath, lua_State * script)
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

    if(!m_banner)
    {
        m_banner = new Banner();
    }
    m_banner->init("./Assets/Textures/border.png");
    m_banner->showMessage("test");
    lua_register(m_script, "cpp_CombatField_AddSlot", lua_CombatField_AddSlot);
    lua_register(m_script, "cpp_CombatField_GetSlot", lua_CombatField_GetSlot);
    lua_register(m_script, "cpp_CombatField_AddCharacter", lua_CombatField_AddCharacter);
    lua_register(m_script, "cpp_CombatField_GetCharacter", lua_CombatField_GetCharacter);
    
    // Characters stats
    lua_register(m_script, "cpp_CombatField_SetCharacterStatFloat" , lua_CombatField_SetCharacterStatFloat);
    lua_register(m_script, "cpp_CombatField_SetCharacterStatStr", lua_CombatField_SetCharacterStatStr);
    lua_register(m_script, "cpp_CombatField_ListCharacterStats", lua_CombatField_ListCharacterStats);

    lua_register(m_script, "cpp_CombatField_GetCharacterStatFloat", lua_CombatField_GetCharacterStatFloat);

    lua_register(m_script, "cpp_CombatField_GetCharacterStatStr" , lua_CombatField_GetCharacterStatStr);

    lua_register(m_script, "cpp_getBannerInstance", lua_getBannerInstance);
    lua_register(m_script, "cpp_Banner_SetMsg" , lua_Banner_SetMsg);
    lua_register(m_script, "cpp_Banner_ShowMsg" , lua_Banner_ShowMsg);
    lua_register(m_script, "cpp_Banner_SetVisible", lua_Banner_SetVisible);

    // lua_register

    m_bg.init(Feintgine::ResourceManager::getTexture("./Assets/Textures/Palace_of_the_Earth_Spirits.png"),glm::vec2(0,100), glm::vec2(1280, 720),Feintgine::Color(255, 255, 255, 255));

    m_enumToIndecies.reserve(25);
    // init map | collumn, row, side (1 = left, 2 = right)
    m_enumToIndecies[LeftFrontTop] = glm::ivec3(0,0,1);
    m_enumToIndecies[LeftCenterTop] = glm::ivec3(0,1,1);
    m_enumToIndecies[LeftRearTop] = glm::ivec3(0,2,1);
    m_enumToIndecies[LeftFrontMid] = glm::ivec3(1,0,1);
    m_enumToIndecies[LeftCenterMid] = glm::ivec3(1,1,1);
    m_enumToIndecies[LeftRearMid] = glm::ivec3(1,2,1);
    m_enumToIndecies[LeftFrontBot] = glm::ivec3(2,0,1);
    m_enumToIndecies[LeftCenterBot] = glm::ivec3(2,1,1);
    m_enumToIndecies[LeftRearBot] = glm::ivec3(2,2,1);

    m_enumToIndecies[RightFrontTop] = glm::ivec3(0,0,2);
    m_enumToIndecies[RightCenterTop] = glm::ivec3(0,1,2);
    m_enumToIndecies[RightRearTop] = glm::ivec3(0,2,2);
    m_enumToIndecies[RightFrontMid] = glm::ivec3(1,0,2);
    m_enumToIndecies[RightCenterMid] = glm::ivec3(1,1,2);
    m_enumToIndecies[RightRearMid] = glm::ivec3(1,2,2);
    m_enumToIndecies[RightFrontBot] = glm::ivec3(2,0,2);
    m_enumToIndecies[RightCenterBot] = glm::ivec3(2,1,2);
    m_enumToIndecies[RightRearBot] = glm::ivec3(2,2,2);

}

CSlot * CombatField::getSlot(int collumn, int row, int side)
{

    return &m_slots[m_slotIndexMap[{collumn , row , side}]];
}

CSlot * CombatField::getSlot(SlotPos pos)
{
    // return nullptr;
    int row, collumn, side;
    collumn = m_enumToIndecies[pos].x;
    row = m_enumToIndecies[pos].y;
    side = m_enumToIndecies[pos].z;
    return &m_slots[m_slotIndexMap[{collumn, row, side}]];
}

void CombatField::addSlot(int collumn, int row, int side)
{
    std::string defaultTexture = "./Assets/Textures/circle.png";

    // CSlot slot;
    // slot.init(defaultTexture, collumn, row, side);
    // m_slots.push_back(slot);
    m_slots.emplace_back(defaultTexture,collumn, row, side);
    // m_slotIndexMap.insert(std::make_pair(glm::ivec3(collumn, row, side), m_slots.size() - 1));
    m_slotIndexMap[{collumn, row, side}] = m_slots.size() - 1;
}

void CombatField::draw(Feintgine::SpriteBatch & spriteBatch)
{
    m_bg.draw(spriteBatch);
    for (auto i = 0; i < m_slots.size(); i++)
    {
        m_slots[i].draw(spriteBatch);
    }
    for (int i = 0 ; i < m_characters.size(); i++)
    {
        m_characters[i]->draw(spriteBatch);
    }
    if(m_banner)
    {
        m_banner->draw(spriteBatch);
    }

}

void CombatField::update(float deltaTime)
{
    // std::cout << "character size " << m_characters.size() << "\n";
    for (int i = 0 ; i < m_characters.size(); i++)
    {
        m_characters[i]->update(deltaTime);
    }
    if(m_banner)
    {
        m_banner->update(deltaTime);
    }
}

CombatCharacter * CombatField::addCharacter(int collumn, int row, int side, const std::string & characterID, const std::string & portraitPath, const glm::vec2 & scale)
{
    std::string key = characterID + "_" + std::to_string(side);

    CSlot* slot = getSlot(collumn, row, side);
    if(!slot)
    {
        std::cout << "invalid slot " << collumn << " " << row << " " << side << "\n";
        return nullptr;
    }
    if(m_charactersMap.find(key) != m_charactersMap.end())
    {
        m_charactersMap[key]->init(slot, InfoHolder::getInstance()->getCharacterAnimationPath(characterID), portraitPath, scale, side);
        return m_charactersMap[key].get();
    }

    auto character = std::make_shared<CombatCharacter>();
    
    character->init(slot, InfoHolder::getInstance()->getCharacterAnimationPath(characterID), portraitPath, scale, side);

    // Build the map key
    
    // Add to both containers
    m_characters.push_back(character);       // shared_ptr copies fine
    m_charactersMap[key] = character; 

    return character.get();
}

CombatCharacter * CombatField::getCharacter(const std::string & characterID, int side)
{   
    std::string key = characterID + "_" + std::to_string(side);
    if(m_charactersMap.find(key) != m_charactersMap.end())
    {
        std::cout << "return the character key " << key << "\n";
        std::cout << "value " << m_charactersMap[key].get() << "\n";
        return m_charactersMap[key].get();
    }
    std::cout << "(CombatField::getCharacter) character not found " << key << "\n";
    return nullptr;
}

void CombatField::initSlots(int collumns, int rows)
{
    // decide to do it in lua
}

void CombatField::drawText(TextRenderer * textRenderer)
{
    if(!textRenderer)
    {
        return;
    }
    for (int i = 0; i < m_characters.size(); i++)
    {
        m_characters[i]->drawText(textRenderer);
    }
    if(m_banner)
    {
        m_banner->drawText(textRenderer);
    }
}