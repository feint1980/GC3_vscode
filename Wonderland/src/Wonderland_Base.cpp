#include "Wonderland_Base.h"

int lua_LoadScene(lua_State * L)
{
    if(lua_gettop(L) != 2 )
    {
        std::cout << "gettop failed (lua_LoadScene) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        Wonderland_Base * host = (Wonderland_Base *)lua_touserdata(L, 1);
        std::string scenePath= lua_tostring(L, 2);

        host->loadScene(scenePath);
    }
}

int lua_CreatePlayer(lua_State * L)
{
    if(lua_gettop(L) != 4 )
    {
        std::cout << "gettop failed (lua_CreatePlayer) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        Wonderland_Base * host = (Wonderland_Base *)lua_touserdata(L, 1);
        std::string animationPath = lua_tostring(L, 2);
        int hpCap = lua_tointeger(L, 3);
        int staminaCap = lua_tointeger(L, 4);

        W_Player * player = host->initPlayer(animationPath, hpCap, staminaCap);
        lua_pushlightuserdata(L, player);
        return 1;
    }
}

Wonderland_Base::Wonderland_Base()
{

}

Wonderland_Base::~Wonderland_Base()
{

}

W_Player * Wonderland_Base::initPlayer(const std::string & animationPath, int hpCap, int staminaCap)
{
    if(!m_player)
    {
        m_player = std::make_unique<W_Player>();
    }
    m_player->initCharacter(animationPath, hpCap, staminaCap);

    return m_player.get();
}

void Wonderland_Base::init(Feintgine::Camera2D * camera)
{
    m_camera = camera;
    m_entities.reserve(2500);
    // init lua
    m_script = luaL_newstate();
    luaL_openlibs(m_script);

    // register lua function
    lua_register(m_script, "cppLoadScene", lua_LoadScene);
    
    lua_register(m_script, "cppCreatePlayer", lua_CreatePlayer);

    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "../../Lua/Wonderland/Wonderland_Base.lua")))
    {
        std::cout << "Run script Wonderland_Base OK \n";
    }
    lua_getglobal(m_script, "InitWonderlandBase");
    if(lua_isfunction(m_script, -1))
    {
        lua_pushlightuserdata(m_script, this);
        const int argc = 1;
        const int returnCount = 0;
        if(LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argc, returnCount, 0)))
        {
            std::cout << "InitWonderlandBase from C++ OK \n";
        }
    }

    lua_getglobal(m_script, "WonderLandTestHost");
    if(lua_isfunction(m_script, -1))
    {
        // lua_pushlightuserdata(m_script, this);
        const int argc = 0;
        const int returnCount = 0;
        if(LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argc, returnCount, 0)))
        {
            std::cout << "InitWonderlandBase from C++ OK \n";
        }
    }

}

W_BaseEntity * Wonderland_Base::createEntity(const std::string & entityName, const std::string & animPath, const glm::vec2 & pos)
{
    if(m_entityMap.find(entityName) != m_entityMap.end())
    {
        // just a warning for now
        std::cout << "entity " << entityName << " already exists \n"; 
    }
    std::unique_ptr<W_BaseEntity> entity = std::make_unique<W_BaseEntity>();
    entity->init(animPath, pos);
    m_entities.push_back(std::move(entity));
    m_entityMap[entityName] = entity.get();
    return entity.get();
}

void Wonderland_Base::draw(Feintgine::SpriteBatch & spriteBatch)
{
    
    if(m_scene)
    {
        m_scene->drawScene(spriteBatch);
    }
    for(int i = 0 ; i < m_entities.size(); i++)
    {
        m_entities[i]->draw(spriteBatch);
    }
    if(m_player)
    {
        m_player->draw(spriteBatch);
    }
}

void Wonderland_Base::update(float deltaTime)
{
    for(int i = 0 ; i < m_entities.size(); i++)
    {
        m_entities[i]->update(deltaTime);
    }
    if(m_player)
    {
        m_player->update(deltaTime);
    }
}

void Wonderland_Base::handleInput(Feintgine::InputManager & inputManager)
{
    int signal = 0;

    // signal chart
    // 1 = left
    // 2 = right
    // 4 = up
    // 8 = down
    if(inputManager.isKeyPressed(SDLK_LEFT) or inputManager.isKeyDown(SDLK_a))
    {
        signal = 1;
    }

    if(inputManager.isKeyPressed(SDLK_RIGHT) or inputManager.isKeyDown(SDLK_d))
    {
        signal = 2;
    }

    if(inputManager.isKeyPressed(SDLK_UP) or inputManager.isKeyDown(SDLK_w))
    {
        signal = 4;
    }

    if(inputManager.isKeyPressed(SDLK_DOWN) or inputManager.isKeyDown(SDLK_s))
    {
        signal = 8;
    }

    if(signal != 0)
    {
        sendSignalToLua(signal);
    }
    
}

void Wonderland_Base::sendSignalToLua(int signal)
{
    lua_getglobal(m_script, "WonderLandInputHandling");
    if(lua_isfunction(m_script, -1))
    {
        // lua_pushlightuserdata(m_script, this);
        lua_pushinteger(m_script, signal);
        const int argc = 1;
        const int returnCount = 0;
        if(LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argc, returnCount, 0)))
        {
            std::cout << "sendSignalToLua " << signal << " OK \n";
        }
    }
}

void Wonderland_Base::loadScene(const std::string & filePath)
{
    if(!m_scene)
    {
        m_scene = std::make_unique<Feintgine::Fg_scene>();
        m_scene->loadSceneFromFile(filePath,nullptr);
    }
}

void Wonderland_Base::drawLight(Feintgine::LightBatch & lightBatch)
{
    if(m_scene)
    {
        m_scene->drawLight(lightBatch);
    }
}
