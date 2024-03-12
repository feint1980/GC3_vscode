
#include "F_LuaBridgeObject.h"


namespace Feintgine
{



F_LuaBridgeObject::F_LuaBridgeObject()
{

}


F_LuaBridgeObject::~F_LuaBridgeObject()
{

}


int davai(int x)
{
    return x * 2;
}

int getIntField(lua_State* L, const char * tableName, const char* key)
{
    lua_getglobal(L, tableName);
    lua_pushstring(L, key);
    lua_gettable(L, -2);  // get table[key]
 
    int result = (int)lua_tonumber(L, -1);
    lua_pop(L, 1);  // remove number from stack
    return result;
}

std::string getStringField(lua_State* L, const char * tableName,const char* key)
{
    lua_getglobal(L, tableName);
    lua_pushstring(L, key);
    lua_gettable(L, -2);  // get table[key]
 
    std::string result = lua_tostring(L, -1);
    lua_pop(L, 1);  // remove string from stack
    return result;
}

glm::vec2 GetVec2FromTable(lua_State* L, const char* outerTableName, const char* innerTableName) {
    double x = 0.0;
    double y = 0.0;

    lua_getglobal(L, outerTableName); // Push the outer table onto the stack
    lua_getfield(L, -1, innerTableName); // Push the inner table onto the stack

    if (lua_istable(L, -1)) { // Check if the top of the stack is a table
        lua_rawgeti(L, -1, 1); // Get the value at index 1 within the inner table
        x = lua_tonumber(L, -1); // Get the value as a number
        lua_pop(L, 1); // Pop the value off the stack

        lua_rawgeti(L, -1, 2); // Get the value at index 2 within the inner table
        y = lua_tonumber(L, -1); // Get the value as a number
        lua_pop(L, 1); // Pop the value off the stack
    } else {
        // Handle error if the inner table is not found
    }

    lua_pop(L, 2); // Pop the outer table and inner table off the stack

    return glm::vec2(x, y); // Return the glm::vec2
}


void F_LuaBridgeObject::addObject(const std::string & tableName)
{

    std::cout << "add object called \n";

    glm::vec2 pos = GetVec2FromTable(m_LuaState, tableName.c_str(), "pos");
    std::cout << "C++ side pos: " << pos.x << " " << pos.y <<  "\n";
    glm::vec2 scale = GetVec2FromTable(m_LuaState, tableName.c_str(), "scale");
    std::cout << "C++ side scale: " << scale.x << " " << scale.y << "\n";
    const std::string assetPath = getStringField(m_LuaState, tableName.c_str(),"assetPath");
    std::cout << "C++ side assetPath: " << assetPath << "\n";
    const std::string name = getStringField(m_LuaState, tableName.c_str(), "name");
    std::cout << "C++ side name: " << name << "\n";
    int id = getIntField(m_LuaState, tableName.c_str(), "id");
    std::cout << "C++ side id: " << id << "\n";
    glm::vec2 vel = GetVec2FromTable(m_LuaState, tableName.c_str(), "vel");
    std::cout << "C++ side vel: " << vel.x << " " << vel.y << "\n";

   F_LuaObject luaObject;
   luaObject.init(pos, scale, assetPath, name, id, vel);
   m_luaObjects.push_back(luaObject);
}

void F_LuaBridgeObject::init()
{
    m_LuaState = luaL_newstate();
    luaL_openlibs(m_LuaState);
    luaopen_base(m_LuaState);

    luabridge::getGlobalNamespace(m_LuaState).beginNamespace("main")
    .addFunction("createObject", [&](const std::string & tableName) {
        addObject(tableName);
         })
    .endNamespace();

}

void F_LuaBridgeObject::
readFile(const std::string & filePath)
{
    int resultDofile = luaL_dofile(m_LuaState, filePath.c_str());

    if(resultDofile != LUA_OK)
    {
        std::cout << lua_tostring(m_LuaState, -1) << "\n";
        return;
    }


    glm::vec2 pos = glm::vec2(0,0);
   

    glm::vec2 scale = glm::vec2(1,1);
    const std::string assetPath = "./Assets/F_AObjects/boss_komachi.xml";
    const std::string name = "komachi";
    
    int id = 7;
    
    glm::vec2 vel = glm::vec2(0,0);

    F_LuaObject luaObject;
    luaObject.init(pos, scale, assetPath, name, id, vel);
    m_luaObjects.push_back(luaObject);


}

void F_LuaBridgeObject::draw(Feintgine::SpriteBatch & spriteBatch)
{
    for(int i = 0; i < m_luaObjects.size(); i++)
    {
        m_luaObjects[i].draw(spriteBatch); // <-- this cause crash
    }
}

void F_LuaBridgeObject::update(float deltaTime)
{
    for(int i = 0; i < m_luaObjects.size(); i++)
    {
       // m_luaObjects[i].update(deltaTime);
    }
}

void F_LuaBridgeObject::test()
{
    std::cout << "init lua \n";
    init(); 
    luabridge::getGlobalNamespace(m_LuaState)
    .beginNamespace("test")
    .addFunction ("davai", +[] (int x) { return x * 3; })
    .endNamespace();

    std::cout << "reading file \n";

    int resultDofile = luaL_dofile(m_LuaState, "Assets/Lua/test.lua");

    if(resultDofile != LUA_OK)
    {
        std::cout << lua_tostring(m_LuaState, -1) << "\n";
        return;
    }


   // lua_getglobal(m_LuaState, "boss_komachi");

    int id = getIntField(m_LuaState, "boss_komachi","id");

    std::cout << "from C++ : " << id << "\n";

    std::cout << "from C++ : " << getStringField(m_LuaState , "boss_komachi", "name") << "\n";

    glm::vec2 position = GetVec2FromTable(m_LuaState, "boss_komachi", "pos");

    glm::vec2 scale = GetVec2FromTable(m_LuaState, "boss_komachi", "scale");

    std::cout << "from C++ : " << position.x << " " << position.y << "\n";
    std::cout << "from C++ : " << scale.x << " " << scale.y << "\n";
    
    if(resultDofile != LUA_OK)
    {
        std::cout << "unable to read file \n";
        std::cout << lua_tostring(m_LuaState, -1) << "\n";
    }
    std::cout << "test end \n";
    // run file Lua
}
}