// #pragma once
// 
// #include "SimpleObject.h"
// #include <SDL.h>
// #include "TileSheet.h"
// #include "ResourceManager.h"
// #include "SpriteBatch.h"
// 
// #include <rapidxml.hpp>
// #include <string>
// #include <map>
// #include <fstream>
// 
// #include <iostream>
// 
// using namespace rapidxml;
// using namespace std;
// struct anim{
// 	anim(int index, float t){
// 		tileIndex = index;
// 		tick = t;
// 	}
// 	float tick;
// 	int tileIndex;
// 
// };
// 
// typedef std::map<std::string, std::vector<anim>>::iterator it_type;
// 
// 
// class Boss
// {
// public : 
// 	void init(const glm::vec2 &positon, const glm::vec2 &dimentions, Feintgine::GLTexture texture, glm::vec2 sheetRes, Feintgine::Color &color,std::string name);
// 
// 	void setColor(const Feintgine::Color &color);
// 	void setPos(const glm::vec2 &pos);
// 
// 	//void loadInfo()
// 	
// 	Feintgine::Color getColor() const { return m_color; }
// 
// 	glm::vec2 getPos() const { return m_postion; }
// 
// 	void draw(Feintgine::SpriteBatch & spriteBatch);
// 	void setDepth(float depth);
// 
// 	
// 	virtual void update() = 0;
// 
// 	void playAnimation(std::string name, bool loop = false);
// 	void updateAnim();
// protected:
// 
// 	
// 
// 	glm::vec2 m_postion;
// 	glm::vec2 m_dimentions;
// 	
// 	Feintgine::TileSheet m_spriteSheet;
// 
// 	int m_tileIndex = 0;
// 	int numTiles = 0;
// 
// 	float m_animTime;
// 	float m_depth = 1;
// 
// 	float animSpeed;
// 
// 	int realTileIndex = 0;
// 
// 	int m_direction = 0;
// 
// 	std::string m_anim_name = "";
// 
// 	bool m_isPlayAnim = false;
// 	std::map <std::string, std::vector<anim> > m_animMap;
// 
// 	Feintgine::Color m_color = Feintgine::Color(255, 255, 255, 255);
// 
// 	std::string m_name;
// 	int currentTick =0;
// 	int iterator = 0;
// 
// 	bool m_isLoop = false;
// private : 
// 	void loadInfo();
// };