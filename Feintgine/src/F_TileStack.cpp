#include "F_TileStack.h"


namespace Feintgine
{
	F_TileStack::F_TileStack()
	{
		m_pos = glm::vec2(0);
		m_dim = glm::vec2(STACK_SPACING);
		m_color = Color(255, 255, 255, 255);
	}


	F_TileStack::~F_TileStack()
	{

	}


	void F_TileStack::drawIndicatior(DebugRender & renderer)
	{
		glm::vec4 desRect = glm::vec4(m_pos, m_dim);

		renderer.drawBox_center(desRect, m_color, 0.0f);
	}

	void F_TileStack::update(float deltaTime)
	{

		if (isPlace)
		{
			m_topLeft.create(glm::vec2(m_pos.x - TILE_CONFIG_SET, m_pos.y + TILE_CONFIG_SET), glm::vec2(SPACING_OFFSET),
				glm::ivec2(0), m_texture);
			m_topRight.create(glm::vec2(m_pos.x + TILE_CONFIG_SET, m_pos.y + TILE_CONFIG_SET), glm::vec2(SPACING_OFFSET),
				glm::ivec2(1, 0), m_texture);
			m_botLeft.create(glm::vec2(m_pos.x - TILE_CONFIG_SET, m_pos.y - TILE_CONFIG_SET), glm::vec2(SPACING_OFFSET),
				glm::ivec2(0, 1), m_texture);
			m_botRight.create(glm::vec2(m_pos.x + TILE_CONFIG_SET, m_pos.y - TILE_CONFIG_SET), glm::vec2(SPACING_OFFSET),
				glm::ivec2(1, 1), m_texture);


			scanNearByTile(m_topLeft, scanTopLeft);
			scanNearByTile(m_topRight, scanTopRight);
			scanNearByTile(m_botLeft, scanBotLeft);
			scanNearByTile(m_botRight, scanBotRight);

			m_tileManager->addTilePart(m_topLeft);
			m_tileManager->addTilePart(m_topRight);
			m_tileManager->addTilePart(m_botLeft);
			m_tileManager->addTilePart(m_botRight);		

		}
	}


	void F_TileStack::handleInput(InputManager & inputManager)
	{

		glm::vec2 screenPos = glm::vec2(350, 50);
		glm::vec2 SpacingOffset = glm::vec2(STACK_SPACING);
		glm::vec2 curMousePos = m_camera->convertScreenToWorld(inputManager.getMouseCoords() - screenPos);
		float xbalanceVal = 0.0f;
		float ybalanceVal = 0.0f;
		if (curMousePos.x < 0)
		{
			xbalanceVal = SpacingOffset.x;
		}
		if (curMousePos.y < 0)
		{
			ybalanceVal = SpacingOffset.y;
		}
		int xVal = (curMousePos.x - xbalanceVal) / SpacingOffset.x;
		int yVal = (curMousePos.y - ybalanceVal) / SpacingOffset.y;
		glm::vec2 gridedPos = glm::vec2((xVal* SpacingOffset.x) + 32, (yVal*SpacingOffset.y) + 32);
		m_pos = gridedPos;

		if (inputManager.isKeyDown(SDL_BUTTON_LEFT))
		{
			isPlace = true;
		}
		else
		{
			isPlace = false;
		}


	}

	void F_TileStack::init(const GLTexture &texture, int col, int row, Camera2D * camera)
	{
		m_camera = camera;
		m_col = col;
		m_row = row;
		m_texture = texture;
	}


	void F_TileStack::bindTileManager(F_TileManager * tileManager)
	{
		m_tileManager = tileManager;
	}

	void F_TileStack::scanNearByTile(F_TilePart & tile,ScanType scanType)
	{
		glm::vec2 tilePos = tile.getPos();
		int index1 = -1;
		int index2 = -1;
		int index3 = -1;

		// reset value
		m_topLeft_overlap = 0;
		m_topRight_overlap = 0;
		m_botLeft_overlap = 0;
		m_botRight_overlap = 0;

		switch (scanType)
		{
		case scanTopLeft:
		{
			glm::vec2 leftTilePos = glm::vec2(tilePos.x - TILE_SPACING, tilePos.y);
			glm::vec2 upTilePos = glm::vec2(tilePos.x, tilePos.y + TILE_SPACING);
			glm::vec2 upLeftTilePos = glm::vec2(tilePos.x - TILE_SPACING, tilePos.y + TILE_SPACING);
			
			// calculate flags
			index1 = m_tileManager->getOverlapIndex(leftTilePos);
			if (index1 != -1)
			{			
				m_topLeft_overlap |= OVERLAP_LEFT;
			}
			index2 = m_tileManager->getOverlapIndex(upTilePos);
			if (index2 != -1)
			{
				m_topLeft_overlap |= OVERLAP_UP;
			}
			index3 = m_tileManager->getOverlapIndex(upLeftTilePos);
			if (index3 != -1)
			{
				m_topLeft_overlap |= OVERLAP_TOP_LEFT;
			}
			if (m_topLeft_overlap & OVERLAP_LEFT)
			{
				F_TilePart targetTile = m_tileManager->getTilePartByIndex(index1);
				if (targetTile.getIndex() == glm::ivec2(1, 0))
				{			
					m_tileManager->restructureTile(index1, glm::ivec2(1, 2));
					tile.setIndex(glm::ivec2(2, 2));
				}
				if (targetTile.getIndex() == glm::ivec2(3, 4))
				{
					m_tileManager->restructureTile(index1, glm::ivec2(3, 0));
					tile.setIndex(glm::ivec2(2, 2));
				}
			}
			if (m_topLeft_overlap & OVERLAP_UP)
			{
				F_TilePart targetTile = m_tileManager->getTilePartByIndex(index2);
				if (targetTile.getIndex() == glm::ivec2(0, 1))
				{			
					m_tileManager->restructureTile(index2, glm::ivec2(0, 3));
					tile.setIndex(glm::ivec2(0, 4));
				}
				if (targetTile.getIndex() == glm::ivec2(2, 5))
				{
					m_tileManager->restructureTile(index2, glm::ivec2(2, 1));
					tile.setIndex(glm::ivec2(0, 4));
				}
			}
			if (m_topLeft_overlap & OVERLAP_TOP_LEFT)
			{
				F_TilePart targetTile = m_tileManager->getTilePartByIndex(index3);
				if (targetTile.getIndex() == glm::ivec2(1, 3))
				{		
					m_tileManager->restructureTile(index3, glm::ivec2(1, 3));
					tile.setIndex(glm::ivec2(2, 4));
					if (m_topLeft_overlap & OVERLAP_LEFT)
					{
						m_tileManager->restructureTile(index1, glm::ivec2(1, 4));
						
					}
					if (m_topLeft_overlap & OVERLAP_UP)
					{
						m_tileManager->restructureTile(index2, glm::ivec2(2, 3));
					}

				}

				if (targetTile.getIndex() == glm::ivec2(3, 1))
				{			
					m_tileManager->restructureTile(index3, glm::ivec2(1, 3));
					tile.setIndex(glm::ivec2(2, 4));
					if (m_topLeft_overlap & OVERLAP_LEFT)
					{
						m_tileManager->restructureTile(index1, glm::ivec2(1, 4));

					}
					if (m_topLeft_overlap & OVERLAP_UP)
					{
						m_tileManager->restructureTile(index2, glm::ivec2(2, 3));
					}
				}				
			}		
		}
		break;
		case scanTopRight:
		{
			glm::vec2 rightTilePos = glm::vec2(tilePos.x + TILE_SPACING, tilePos.y);
			glm::vec2 upTilePos = glm::vec2(tilePos.x, tilePos.y + TILE_SPACING);
			glm::vec2 upRightTilePos = glm::vec2(tilePos.x + TILE_SPACING, tilePos.y + TILE_SPACING);

			// calculate flags
			index1 = m_tileManager->getOverlapIndex(rightTilePos);
			if (index1 != -1)
			{
				m_topLeft_overlap |= OVERLAP_RIGHT;
			}
			index2 = m_tileManager->getOverlapIndex(upTilePos);
			if (index2 != -1)
			{
				m_topLeft_overlap |= OVERLAP_UP;
			}
			index3 = m_tileManager->getOverlapIndex(upRightTilePos);
			if (index3 != -1)
			{
				m_topLeft_overlap |= OVERLAP_TOP_RIGHT;
			}
			if (m_topLeft_overlap & OVERLAP_RIGHT)
			{
				F_TilePart targetTile = m_tileManager->getTilePartByIndex(index1);
				if (targetTile.getIndex() == glm::ivec2(0, 0))
				{			
					m_tileManager->restructureTile(index1, glm::ivec2(2, 2));
					tile.setIndex(glm::ivec2(1, 2));
				}
				if (targetTile.getIndex() == glm::ivec2(0, 4))
				{
					m_tileManager->restructureTile(index1, glm::ivec2(2, 0));
					tile.setIndex(glm::ivec2(1, 2));
				}
			}
			if (m_topLeft_overlap & OVERLAP_UP)
			{
				F_TilePart targetTile = m_tileManager->getTilePartByIndex(index2);
				if (targetTile.getIndex() == glm::ivec2(1, 1))
				{
					m_tileManager->restructureTile(index2, glm::ivec2(3, 3));
					tile.setIndex(glm::ivec2(3, 4));
				}
				if (targetTile.getIndex() == glm::ivec2(1, 5))
				{
					m_tileManager->restructureTile(index2, glm::ivec2(3, 1));
					tile.setIndex(glm::ivec2(3, 4));
				}


			}
			if (m_topLeft_overlap & OVERLAP_TOP_RIGHT)
			{
				F_TilePart targetTile = m_tileManager->getTilePartByIndex(index3);
				if (targetTile.getIndex() == glm::ivec2(1, 0))
				{				
					m_tileManager->restructureTile(index3, glm::ivec2(1, 2));
					tile.setIndex(glm::ivec2(2, 2));
				}

				if (targetTile.getIndex() == glm::ivec2(2, 1))
				{				
					m_tileManager->restructureTile(index3, glm::ivec2(2, 3));
					tile.setIndex(glm::ivec2(1, 4));
				}
				if (m_topLeft_overlap & OVERLAP_RIGHT)
				{
					m_tileManager->restructureTile(index1, glm::ivec2(2, 4));				
				}
				if (m_topLeft_overlap & OVERLAP_UP)
				{
					m_tileManager->restructureTile(index2, glm::ivec2(1, 3));
				}
					
			}
			
		}
		break;
		case scanBotLeft:
		{
			glm::vec2 leftTilePos = glm::vec2(tilePos.x - TILE_SPACING, tilePos.y);
			glm::vec2 downTilePos = glm::vec2(tilePos.x, tilePos.y - TILE_SPACING);
			glm::vec2 downLeftTilePos = glm::vec2(tilePos.x - TILE_SPACING, tilePos.y - TILE_SPACING);

			// calculate flags
			index1 = m_tileManager->getOverlapIndex(leftTilePos);
			if (index1 != -1)
			{
				m_topLeft_overlap |= OVERLAP_LEFT;
			}
			index2 = m_tileManager->getOverlapIndex(downTilePos);
			if (index2 != -1)
			{
				m_topLeft_overlap |= OVERLAP_DOWN;
			}
			index3 = m_tileManager->getOverlapIndex(downLeftTilePos);
			if (index3 != -1)
			{
				m_topLeft_overlap |= OVERLAP_BOT_LEFT;
			}
			if (m_topLeft_overlap & OVERLAP_LEFT)
			{
				F_TilePart targetTile = m_tileManager->getTilePartByIndex(index1);
				if (targetTile.getIndex() == glm::ivec2(1, 1))
				{			
					m_tileManager->restructureTile(index1, glm::ivec2(1, 5));
					tile.setIndex(glm::ivec2(2, 5));
				}
				if (targetTile.getIndex() == glm::ivec2(3, 3))
				{			
					m_tileManager->restructureTile(index1, glm::ivec2(3, 1));
					tile.setIndex(glm::ivec2(2, 5));
				}
			}
			if (m_topLeft_overlap & OVERLAP_DOWN)
			{
				F_TilePart targetTile = m_tileManager->getTilePartByIndex(index2);
				if (targetTile.getIndex() == glm::ivec2(0, 0))
				{
					m_tileManager->restructureTile(index2, glm::ivec2(0, 3));
					tile.setIndex(glm::ivec2(0, 4));
				}
				if (targetTile.getIndex() == glm::ivec2(2, 2))
				{
					m_tileManager->restructureTile(index2, glm::ivec2(2, 0));
					tile.setIndex(glm::ivec2(0, 4));
				}
			}
			if (m_topLeft_overlap & OVERLAP_BOT_LEFT)
			{
				F_TilePart targetTile = m_tileManager->getTilePartByIndex(index3);
				if (targetTile.getIndex() == glm::ivec2(3, 0))
				{
					//std::cout << "change \n";					
					m_tileManager->restructureTile(index3, glm::ivec2(1, 4));
					tile.setIndex(glm::ivec2(2, 3));
					if (m_topLeft_overlap & OVERLAP_LEFT)
					{
						m_tileManager->restructureTile(index1, glm::ivec2(1, 3));

					}
					if (m_topLeft_overlap & OVERLAP_DOWN)
					{
						m_tileManager->restructureTile(index2, glm::ivec2(2, 4));
					}
				}
								
			}
			
		}
		break;
		case scanBotRight:
		{
			glm::vec2 rightTilePos = glm::vec2(tilePos.x + TILE_SPACING, tilePos.y);
			glm::vec2 downTilePos = glm::vec2(tilePos.x, tilePos.y - TILE_SPACING);
			glm::vec2 downRightTilePos = glm::vec2(tilePos.x + TILE_SPACING, tilePos.y - TILE_SPACING);

			// calculate flags
			index1 = m_tileManager->getOverlapIndex(rightTilePos);
			if (index1 != -1)
			{
				m_topLeft_overlap |= OVERLAP_RIGHT;
			}
			index2 = m_tileManager->getOverlapIndex(downTilePos);
			if (index2 != -1)
			{
				m_topLeft_overlap |= OVERLAP_DOWN;
			}
			index3 = m_tileManager->getOverlapIndex(downRightTilePos);
			if (index3 != -1)
			{
				m_topLeft_overlap |= OVERLAP_BOT_RIGHT;
			}
			if (m_topLeft_overlap & OVERLAP_RIGHT)
			{
				F_TilePart targetTile = m_tileManager->getTilePartByIndex(index1);
				if (targetTile.getIndex() == glm::ivec2(0, 1))
				{			
					m_tileManager->restructureTile(index1, glm::ivec2(2, 5));
					tile.setIndex(glm::ivec2(1, 5));
				}
				if (targetTile.getIndex() == glm::ivec2(0, 3))
				{
					m_tileManager->restructureTile(index1, glm::ivec2(2, 1));
					tile.setIndex(glm::ivec2(1, 5));
				}
			}
			if (m_topLeft_overlap & OVERLAP_DOWN)
			{
				F_TilePart targetTile = m_tileManager->getTilePartByIndex(index2);
				if (targetTile.getIndex() == glm::ivec2(1, 0))
				{
					m_tileManager->restructureTile(index2, glm::ivec2(3, 4));
					tile.setIndex(glm::ivec2(3, 3));
				}
				if (targetTile.getIndex() == glm::ivec2(1, 2))
				{
					m_tileManager->restructureTile(index2, glm::ivec2(3, 0));
					tile.setIndex(glm::ivec2(3, 3));
				}
			}
			if (m_topLeft_overlap & OVERLAP_BOT_RIGHT)
			{
				F_TilePart targetTile = m_tileManager->getTilePartByIndex(index3);
				if (targetTile.getIndex() == glm::ivec2(2, 0))
				{
					m_tileManager->restructureTile(index3, glm::ivec2(2, 4));
					tile.setIndex(glm::ivec2(1, 3));
					if (m_topLeft_overlap & OVERLAP_RIGHT)
					{
						m_tileManager->restructureTile(index1, glm::ivec2(2, 3));

					}
					if (m_topLeft_overlap & OVERLAP_DOWN)
					{
						m_tileManager->restructureTile(index2, glm::ivec2(1, 4));
					}
				}		
			}		
		}
		break;
		default:
			break;
		}

	
	}

}