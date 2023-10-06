#pragma once

#include <glm/glm.hpp>
#include <Vertex.h>
#include <SpriteBatch.h>
#include <vector>
#include <iostream>
#include "block.h"

class Light {
public:
	void draw(Feintgine::SpriteBatch& spriteBatch) {
		glm::vec4 destRect;
		destRect.x = position.x - size / 2.0f;
		destRect.y = position.y - size / 2.0f;
		destRect.z = size;
		destRect.w = size;
		spriteBatch.draw(destRect, glm::vec4(-1.0f, -1.0f, 2.0f, 2.0f), 0, 4.0f, color, 0.0f);
	}
	void drawShadows(Feintgine::SpriteBatch& spriteBatch  , std::vector<block> blocks)
	{
		
		vector2f pos = vector2f(position.x, position.y);

		for (int i = 0; i < blocks.size(); i++)
		{
			std::vector<Feintgine::Edge*> away = blocks[i].getNotFacingEdges(position);
			for (int j = 0; j < away.size(); j++)
			{
		
				quads = new vector2f[4];
			
				vector2f towards = away[j]->p1 - pos;
				towards.normalize();
				towards *= 10000;
				quads[0] = vector2f(away[j]->p1.x + towards.x, away[j]->p1.y + towards.y);
				quads[1] = vector2f(away[j]->p1.x, away[j]->p1.y);

				towards = away[j]->p2 - pos;
				towards.normalize();
				towards *= 10000;

				quads[2] = vector2f(away[j]->p2.x , away[j]->p2.y);
				quads[3] = vector2f(away[j]->p2.x + towards.x, away[j]->p1.y + towards.y);

				spriteBatch.draw(quads);

			}
		}


		
	}
	vector2f *quads;
	Feintgine::Color color;
	glm::vec2 position;
	float size;
};