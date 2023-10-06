#pragma once
#include "F_TilePart.h"
#include <vector>
#include <iostream>
#include "TextRenderer.h"

#define TILE_CONFIG_SET 16
#define STACK_SPACING 64
#define TILE_SPACING 32

enum ScanType
{
	scanTopLeft,
	scanTopRight,
	scanBotLeft,
	scanBotRight
};


#define OVERLAP_LEFT 1 
#define OVERLAP_RIGHT 2
#define OVERLAP_UP 4
#define OVERLAP_DOWN 8
#define OVERLAP_TOP_LEFT 16
#define OVERLAP_TOP_RIGHT 32
#define OVERLAP_BOT_LEFT 64
#define OVERLAP_BOT_RIGHT 128

namespace Feintgine
{
	class F_TileManager
	{
	public:
		F_TileManager();
		~F_TileManager();

		void draw(SpriteBatch & spriteBatch);
		void update(float deltaTime);

		void addTilePart(const F_TilePart & tile);
		int getOverlapIndex(const F_TilePart &tile);
		int getOverlapIndex(const glm::vec2 &pos);
		void restructureTile(int index, glm::ivec2 t_index);

		void updateTiles();

		void scanNearByTile(F_TilePart & tile, ScanType scanType);

		void drawText(TextRenderer & textRenderer, const Feintgine::Camera2D cam);

		void restartTileStatus();


		F_TilePart getTilePartByIndex(int index);

	private :
		std::vector<F_TilePart> m_tileParts;

		unsigned int m_topLeft_overlap;
		unsigned int m_topRight_overlap;
		unsigned int m_botLeft_overlap;
		unsigned int m_botRight_overlap;

	};
}
