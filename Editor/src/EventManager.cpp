#include "EventManager.h"

EventManager *EventManager::p_Instance = 0;

EventManager::EventManager()
{
}


EventManager::~EventManager()
{
}

void EventManager::setEventHandler(int handler)
{
	m_currentEventHandler = handler;
}
