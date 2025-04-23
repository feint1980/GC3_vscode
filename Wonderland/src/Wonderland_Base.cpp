#include "Wonderland_Base.h"


Wonderland_Base::Wonderland_Base()
{

}

Wonderland_Base::~Wonderland_Base()
{

}

void Wonderland_Base::init(Feintgine::Camera2D * camera)
{
    m_camera = camera;
    m_entities.reserve(2500);
    // init lua
    m_script = luaL_newstate();
    luaL_openlibs(m_script);

    // register lua function
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
    for(int i = 0 ; i < m_entities.size(); i++)
    {
        m_entities[i]->draw(spriteBatch);
    }
}

void Wonderland_Base::update(float deltaTime)
{
    for(int i = 0 ; i < m_entities.size(); i++)
    {
        m_entities[i]->update(deltaTime);
    }
}

void Wonderland_Base::handleInput(Feintgine::InputManager & inputManager)
{
    // void handleInput(Feintgine::InputManager & inputManager);
}
