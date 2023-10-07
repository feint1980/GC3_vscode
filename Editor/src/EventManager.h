#pragma once

const int SPRITE_LIST = 1;
const int BUILD_OBJECT = 2;
class EventManager
{
public:
	EventManager();
	~EventManager();


	static EventManager *Instance()
	{
		if (p_Instance == 0)
		{
			p_Instance = new EventManager;
			return p_Instance;
		}
		return p_Instance;
	}
	void setEventHandler(int handler);
	int getEventHandler() const { return m_currentEventHandler; }

private:


	int m_currentEventHandler = 0;
	static EventManager *p_Instance;
};

