
#include "GUI_handler.h"
#include "BAttleScene.h"

GUI_handler::GUI_handler()
{

}


GUI_handler::~GUI_handler()
{

}

void GUI_handler::init(const std::string & selectionTexturePath,const glm::vec2 & dim)
{

    m_selectionZone.init(Feintgine::ResourceManager::getTexture(selectionTexturePath), glm::vec2(5000, 0), dim, Feintgine::Color(255, 255, 255, 255));
}


void GUI_handler::setPhase(int phaseType, int sides)
{

    m_phaseType = phaseType;
    m_SelectionSide = sides;
}

GUI_icon * GUI_handler::getSelectedIcon(GUI_icon * icon)
{

    for(int i = 0; i < m_icons.size(); i++)
    {
        if(m_icons[i] == icon)
        {
            m_selectedIcon = m_icons[i];
            
            return m_selectedIcon;
        }
    }
}

void GUI_handler::addIcon(GUI_icon * icon)
{
    if(icon)
    {
        m_icons.push_back(icon);
    }
}

void GUI_handler::setFocusColor(const Feintgine::Color & color)
{
    m_selectionZone.setColor(color);
}
void GUI_handler::registerCamera(Feintgine::Camera2D * camera)
{
    m_cam = camera;
}

void GUI_handler::setIconPos(GUI_icon *  icon, const glm::vec2 & pos)
{

    for(int i = 0; i < m_icons.size(); i++)
    {
        if(m_icons[i] == icon)
        {
            m_icons[i]->setPos(pos);
        }
    }
}

void GUI_handler::draw(Feintgine::SpriteBatch & spriteBatch)
{
    m_selectionZone.draw(spriteBatch);
    for(int i = 0; i < m_icons.size(); i++)
    {
        m_icons[i]->draw(spriteBatch);
    }

}

void GUI_handler::registerBattleScene(BattleScene * scene)
{
    m_battleScene = scene;
}

void GUI_handler::handleInput(Feintgine::InputManager & inputManager,lua_State * luaState)
{
    int signal = 0;
	if(inputManager.isKeyPressed(SDLK_LEFT))
	{
		signal = 1;
	}

	if(inputManager.isKeyPressed(SDLK_RIGHT))
	{
		signal = 2;
	}

	if(inputManager.isKeyPressed(SDLK_RETURN))
	{
		signal = 32;
	}

    if(inputManager.isKeyPressed(SDLK_ESCAPE))
    {
        signal = 64;
    }

	if(signal != 0)
	{
		lua_getglobal(luaState, "handleInput");
		if (lua_isfunction(luaState, -1))
		{
			lua_pushlightuserdata(luaState, m_battleScene); // host

			//std::cout << "Issue next task pointer " << object << "\n";

			//lua_pushlightuserdata(luaState, m_guiHandler);

			lua_pushnumber(luaState, signal);

			// lua_pushlightuserdata(luaState, entity->getTargetSlot());

			if (!LuaManager::Instance()->checkLua(luaState, lua_pcall(luaState, 2, 1, 0)))
			{
				std::cout << "call handleInput failed \n";
			}
		}
	}
	if(inputManager.isMouseMove())
	{
        glm::vec2 mousePos = m_cam->convertScreenToWorld(inputManager.getMouseCoords());

        int signal = 0;
        if(inputManager.isKeyPressed(SDL_BUTTON_LEFT))
        {
            signal = 1;
        }
        if(inputManager.isKeyPressed(SDL_BUTTON_RIGHT))
        {
            signal = 2;
        }

        lua_getglobal(luaState, "handleMouse");
        if (lua_isfunction(luaState, -1))
        {
            lua_pushlightuserdata(luaState, m_battleScene); // host

            lua_pushnumber(luaState, mousePos.x);
            lua_pushnumber(luaState, mousePos.y);
            lua_pushnumber(luaState, signal);

            if (!LuaManager::Instance()->checkLua(luaState, lua_pcall(luaState, 4, 1, 0)))
            {
                std::cout << "call handleMouse failed \n";
            }
        }
	}
	
}

void GUI_handler::update(float deltaTime)
{
    for(int i = 0; i < m_icons.size(); i++)
    {
        m_icons[i]->update(deltaTime);
    }
    if(m_selectedIcon)
    {
        m_selectionZone.setPos(m_selectedIcon->getPos());
    }

}

