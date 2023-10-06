#pragma once
#include "F_TilePart.h"
#include "InputManager.h"
#include "DebugRender.h"
#include <vector>
#include "Camera2D.h"
#include "F_TileManager.h"


namespace Feintgine
{

	class F_TileStack
	{
	public:
		F_TileStack();
		~F_TileStack();


		void drawIndicatior(DebugRender & renderer);
		void update(float deltaTime);

		void handleInput(InputManager & inputManager);
		void init(const GLTexture &texture, int col, int row, Camera2D * camera);
		void bindTileManager(F_TileManager * tileManager);

		void scanNearByTile(F_TilePart & tile, ScanType scanType);

	private:
		F_TilePart m_topLeft;
		F_TilePart m_topRight;
		F_TilePart m_botLeft;
		F_TilePart m_botRight;

		glm::vec2 m_pos;
		glm::vec2 m_dim;
		Color m_color;
		Camera2D * m_camera;

		GLTexture m_texture;

		F_TileManager * m_tileManager;

		int m_col;
		int m_row;

		bool isPlace = false;

		unsigned int m_topLeft_overlap;
		unsigned int m_topRight_overlap;
		unsigned int m_botLeft_overlap;
		unsigned int m_botRight_overlap;

	};
}

