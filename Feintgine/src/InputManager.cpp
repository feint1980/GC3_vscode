#include "InputManager.h"
//#include <iostream>
namespace Feintgine {

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::pressKey(unsigned int keyID) {
    // Here we are treating _keyMap as an associative array.
    // if keyID doesn't already exist in _keyMap, it will get added
    _keyMap[keyID] = true;
	//_isMouseMove = false;
	
}

void InputManager::releaseKey(unsigned int keyID) {
    _keyMap[keyID] = false;
	_isMouseMove = false;
	//_isMouseMove = false;
}

void InputManager::setMouseCoords(float x, float y){
	_mouseCoords = glm::vec2(x, y);
	_isMouseMove = true;
}
void InputManager::update()
{
	for (auto &it : _keyMap)
	{
		_previousKeyMap[it.first] = it.second;
	}
}

bool InputManager::isKeyPressed(unsigned int keyID)
{
	
	if (isKeyDown(keyID) && !wasKeyDown(keyID))
	{
		//_isMouseMove = false;
		//std::cout << "key " << keyID << "pressed \n";
		return true;
	}
	return false;
	
}

bool InputManager::isKeyDown(unsigned int keyID) 
{
    // We dont want to use the associative array approach here
    // because we don't want to create a key if it doesnt exist.
    // So we do it manually
    auto it = _keyMap.find(keyID);
    if (it != _keyMap.end()) {
        // Found the key
		//_isMouseMove = false;
        return it->second;
    } else {
        // Didn't find the key
        return false;
    }
}


bool InputManager::wasKeyDown(unsigned int keyID)
{
	auto it = _previousKeyMap.find(keyID);
	if (it != _previousKeyMap.end()) {
		// Found the key
		//_isMouseMove = false;
		return it->second;
		
	}
	else {
		// Didn't find the key
		return false;
	}
}

}