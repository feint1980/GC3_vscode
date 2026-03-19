#include "CombatField.h"

int lua_CombatFiled_AddSlot(lua_State * L)
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

int lua_CombatFiled_AddCharacter(lua_State * L)
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
    host->addCharacter(collumn, row, side, characterID, portraitPath);
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

    lua_register(m_script, "cpp_CombatFiled_AddSlot", lua_CombatFiled_AddSlot);
    lua_register(m_script, "cpp_CombatFiled_AddCharacter", lua_CombatFiled_AddCharacter);


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
    return nullptr;
    // int row, collumn, side;
    // collumn = m_enumToIndecies[pos].x;
    // row = m_enumToIndecies[pos].y;
    // side = m_enumToIndecies[pos].z;
    // return &m_slots[m_slotIndexMap[collumn, row, side]];
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

}

void CombatField::update(float deltaTime)
{
    // std::cout << "character size " << m_characters.size() << "\n";
    for (int i = 0 ; i < m_characters.size(); i++)
    {
        m_characters[i]->update(deltaTime);
    }
}

void CombatField::addCharacter(int collumn, int row, int side, const std::string & characterID, const std::string & portraitPath, const glm::vec2 & scale)
{
    std::cout << "CombatField::addCharacter called \n"; 
    CombatCharacter * character = new CombatCharacter();
    std::cout << "target slot " << collumn << " " << row << " " << side << "\n";
    CSlot * slot = getSlot(collumn , row , side);
    std::cout << "result slot " << slot->getIndex().x << " " << slot->getIndex().y << " " << slot->getSide() << "\n";
    
    character->init(slot, InfoHolder::getInstance()->getCharacterAnimationPath(characterID) , portraitPath, scale, side);
    m_characters.push_back(std::move(character));

}

void CombatField::initSlots(int collumns, int rows)
{
    // decide to do it in lua
}