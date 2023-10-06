#include "F_TileManager.h"


namespace Feintgine
{

	F_TileManager::F_TileManager()
	{
		m_tileParts.reserve(300);
	}


	F_TileManager::~F_TileManager()
	{
	}



	void F_TileManager::draw(SpriteBatch & spriteBatch)
	{
		for (auto i = 0; i < m_tileParts.size(); i++)
		{
			m_tileParts[i].draw(spriteBatch);
		}
	}

	void F_TileManager::update(float deltaTime)
	{
		for (auto i = 0; i < m_tileParts.size(); i++)
		{
			m_tileParts[i].update(deltaTime);
		}
	}

	void F_TileManager::addTilePart(const F_TilePart & tile)
	{
		int index = getOverlapIndex(tile);
		if (index == -1)
		{
			restartTileStatus();
			m_tileParts.push_back(tile);
		}
		//updateTiles();
	}
	int F_TileManager::getOverlapIndex(const F_TilePart &tile)
	{
		int returnVal = -1;
		for (auto i = 0; i < m_tileParts.size(); i++)
		{
			if (m_tileParts[i].getPos() == tile.getPos())
			{
				returnVal = i;
				return returnVal;
			}
		}
		return returnVal;		
	}

	int F_TileManager::getOverlapIndex(const glm::vec2 &pos)
	{
		int returnVal = -1;
		for (auto i = 0; i < m_tileParts.size(); i++)
		{
			if (m_tileParts[i].getPos() == pos)
			{
				returnVal = i;
				return returnVal;
			}
		}
		return returnVal;
	}


	void F_TileManager::restructureTile(int index, glm::ivec2 t_index)
	{
		if (index != -1)
		{
			m_tileParts[index].setIndex(t_index);
		}
	}

	void F_TileManager::updateTiles()
	{
		for (auto i = 0; i < m_tileParts.size(); i++)
		{
			scanNearByTile(m_tileParts[i], scanTopLeft);
			scanNearByTile(m_tileParts[i], scanTopRight);
			scanNearByTile(m_tileParts[i], scanBotLeft);
			scanNearByTile(m_tileParts[i], scanBotRight);
		}
	}

	void F_TileManager::scanNearByTile(F_TilePart & tile, ScanType scanType)
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
			index1 = getOverlapIndex(leftTilePos);
			if (index1 != -1)
			{
				m_topLeft_overlap |= OVERLAP_LEFT;
			}
			index2 = getOverlapIndex(upTilePos);
			if (index2 != -1)
			{
				m_topLeft_overlap |= OVERLAP_UP;
			}
			index3 = getOverlapIndex(upLeftTilePos);
			if (index3 != -1)
			{
				m_topLeft_overlap |= OVERLAP_TOP_LEFT;
			}
			if (m_topLeft_overlap & OVERLAP_LEFT)
			{
				F_TilePart targetTile = getTilePartByIndex(index1);
				if (targetTile.getIndex() == glm::ivec2(1, 0))
				{
					restructureTile(index1, glm::ivec2(1, 2));
					tile.setIndex(glm::ivec2(2, 2));
				}
				if (targetTile.getIndex() == glm::ivec2(3, 4))
				{
					restructureTile(index1, glm::ivec2(3, 0));
					tile.setIndex(glm::ivec2(2, 2));
				}
			}
			if (m_topLeft_overlap & OVERLAP_UP)
			{
				F_TilePart targetTile = getTilePartByIndex(index2);
				if (targetTile.getIndex() == glm::ivec2(0, 1))
				{
					restructureTile(index2, glm::ivec2(0, 3));
					tile.setIndex(glm::ivec2(0, 4));
				}
				if (targetTile.getIndex() == glm::ivec2(2, 5))
				{
					restructureTile(index2, glm::ivec2(2, 1));
					tile.setIndex(glm::ivec2(0, 4));
				}
			}
			if (m_topLeft_overlap & OVERLAP_TOP_LEFT)
			{
				F_TilePart targetTile = getTilePartByIndex(index3);
				if (targetTile.getIndex() == glm::ivec2(1, 3))
				{
					restructureTile(index3, glm::ivec2(1, 3));
					tile.setIndex(glm::ivec2(2, 4));
					if (m_topLeft_overlap & OVERLAP_LEFT)
					{
						restructureTile(index1, glm::ivec2(1, 4));

					}
					if (m_topLeft_overlap & OVERLAP_UP)
					{
						restructureTile(index2, glm::ivec2(2, 3));
					}

				}

				if (targetTile.getIndex() == glm::ivec2(3, 1))
				{
					restructureTile(index3, glm::ivec2(1, 3));
					tile.setIndex(glm::ivec2(2, 4));
					if (m_topLeft_overlap & OVERLAP_LEFT)
					{
						restructureTile(index1, glm::ivec2(1, 4));

					}
					if (m_topLeft_overlap & OVERLAP_UP)
					{
						restructureTile(index2, glm::ivec2(2, 3));
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
			index1 = getOverlapIndex(rightTilePos);
			if (index1 != -1)
			{
				m_topLeft_overlap |= OVERLAP_RIGHT;
			}
			index2 = getOverlapIndex(upTilePos);
			if (index2 != -1)
			{
				m_topLeft_overlap |= OVERLAP_UP;
			}
			index3 = getOverlapIndex(upRightTilePos);
			if (index3 != -1)
			{
				m_topLeft_overlap |= OVERLAP_TOP_RIGHT;
			}
			if (m_topLeft_overlap & OVERLAP_RIGHT)
			{
				F_TilePart targetTile = getTilePartByIndex(index1);
				if (targetTile.getIndex() == glm::ivec2(0, 0))
				{
					restructureTile(index1, glm::ivec2(2, 2));
					tile.setIndex(glm::ivec2(1, 2));
				}
				if (targetTile.getIndex() == glm::ivec2(0, 4))
				{
					restructureTile(index1, glm::ivec2(2, 0));
					tile.setIndex(glm::ivec2(1, 2));
				}
			}
			if (m_topLeft_overlap & OVERLAP_UP)
			{
				F_TilePart targetTile = getTilePartByIndex(index2);
				if (targetTile.getIndex() == glm::ivec2(1, 1))
				{
					restructureTile(index2, glm::ivec2(3, 3));
					tile.setIndex(glm::ivec2(3, 4));
				}
				if (targetTile.getIndex() == glm::ivec2(1, 5))
				{
					restructureTile(index2, glm::ivec2(3, 1));
					tile.setIndex(glm::ivec2(3, 4));
				}


			}
			if (m_topLeft_overlap & OVERLAP_TOP_RIGHT)
			{
				F_TilePart targetTile = getTilePartByIndex(index3);
				if (targetTile.getIndex() == glm::ivec2(1, 0))
				{
					restructureTile(index3, glm::ivec2(1, 2));
					tile.setIndex(glm::ivec2(2, 2));
				}

				if (targetTile.getIndex() == glm::ivec2(2, 1))
				{
					restructureTile(index3, glm::ivec2(2, 3));
					tile.setIndex(glm::ivec2(1, 4));
				}
				if (m_topLeft_overlap & OVERLAP_RIGHT)
				{
					restructureTile(index1, glm::ivec2(2, 4));
				}
				if (m_topLeft_overlap & OVERLAP_UP)
				{
					restructureTile(index2, glm::ivec2(1, 3));
				}
				std::cout << "work \n";

			}

		}
		break;
		case scanBotLeft:
		{
			glm::vec2 leftTilePos = glm::vec2(tilePos.x - TILE_SPACING, tilePos.y);
			glm::vec2 downTilePos = glm::vec2(tilePos.x, tilePos.y - TILE_SPACING);
			glm::vec2 downLeftTilePos = glm::vec2(tilePos.x - TILE_SPACING, tilePos.y - TILE_SPACING);

			// calculate flags
			index1 = getOverlapIndex(leftTilePos);
			if (index1 != -1)
			{
				m_topLeft_overlap |= OVERLAP_LEFT;
			}
			index2 = getOverlapIndex(downTilePos);
			if (index2 != -1)
			{
				m_topLeft_overlap |= OVERLAP_DOWN;
			}
			index3 = getOverlapIndex(downLeftTilePos);
			if (index3 != -1)
			{
				m_topLeft_overlap |= OVERLAP_BOT_LEFT;
			}
			if (m_topLeft_overlap & OVERLAP_LEFT)
			{
				F_TilePart targetTile = getTilePartByIndex(index1);
				if (targetTile.getIndex() == glm::ivec2(1, 1))
				{
					restructureTile(index1, glm::ivec2(1, 5));
					tile.setIndex(glm::ivec2(2, 5));
				}
				if (targetTile.getIndex() == glm::ivec2(3, 3))
				{
					restructureTile(index1, glm::ivec2(3, 1));
					tile.setIndex(glm::ivec2(2, 5));
				}
			}
			if (m_topLeft_overlap & OVERLAP_DOWN)
			{
				F_TilePart targetTile = getTilePartByIndex(index2);
				if (targetTile.getIndex() == glm::ivec2(0, 0))
				{
					restructureTile(index2, glm::ivec2(0, 3));
					tile.setIndex(glm::ivec2(0, 4));
				}
				if (targetTile.getIndex() == glm::ivec2(2, 2))
				{
					restructureTile(index2, glm::ivec2(2, 0));
					tile.setIndex(glm::ivec2(0, 4));
				}
			}
			if (m_topLeft_overlap & OVERLAP_BOT_LEFT)
			{
				F_TilePart targetTile = getTilePartByIndex(index3);
				if (targetTile.getIndex() == glm::ivec2(3, 0))
				{
					//std::cout << "change \n";					
					restructureTile(index3, glm::ivec2(1, 4));
					tile.setIndex(glm::ivec2(2, 3));
					if (m_topLeft_overlap & OVERLAP_LEFT)
					{
						restructureTile(index1, glm::ivec2(1, 3));

					}
					if (m_topLeft_overlap & OVERLAP_DOWN)
					{
						restructureTile(index2, glm::ivec2(2, 4));
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
			index1 = getOverlapIndex(rightTilePos);
			if (index1 != -1)
			{
				m_topLeft_overlap |= OVERLAP_RIGHT;
			}
			index2 = getOverlapIndex(downTilePos);
			if (index2 != -1)
			{
				m_topLeft_overlap |= OVERLAP_DOWN;
			}
			index3 = getOverlapIndex(downRightTilePos);
			if (index3 != -1)
			{
				m_topLeft_overlap |= OVERLAP_BOT_RIGHT;
			}
			if (m_topLeft_overlap & OVERLAP_RIGHT)
			{
				F_TilePart targetTile = getTilePartByIndex(index1);
				if (targetTile.getIndex() == glm::ivec2(0, 1))
				{
					restructureTile(index1, glm::ivec2(2, 5));
					tile.setIndex(glm::ivec2(1, 5));
				}
				if (targetTile.getIndex() == glm::ivec2(0, 3))
				{
					restructureTile(index1, glm::ivec2(2, 1));
					tile.setIndex(glm::ivec2(1, 5));
				}
			}
			if (m_topLeft_overlap & OVERLAP_DOWN)
			{
				F_TilePart targetTile = getTilePartByIndex(index2);
				if (targetTile.getIndex() == glm::ivec2(1, 0))
				{
					restructureTile(index2, glm::ivec2(3, 4));
					tile.setIndex(glm::ivec2(3, 3));
				}
				if (targetTile.getIndex() == glm::ivec2(1, 2))
				{
					restructureTile(index2, glm::ivec2(3, 0));
					tile.setIndex(glm::ivec2(3, 3));
				}
			}
			if (m_topLeft_overlap & OVERLAP_BOT_RIGHT)
			{
				F_TilePart targetTile = getTilePartByIndex(index3);
				if (targetTile.getIndex() == glm::ivec2(2, 0))
				{
					restructureTile(index3, glm::ivec2(2, 4));
					tile.setIndex(glm::ivec2(1, 3));
					if (m_topLeft_overlap & OVERLAP_RIGHT)
					{
						restructureTile(index1, glm::ivec2(2, 3));

					}
					if (m_topLeft_overlap & OVERLAP_DOWN)
					{
						restructureTile(index2, glm::ivec2(1, 4));
					}
				}
			}
		}
		break;
		default:
			break;
		}	
	}

	void F_TileManager::drawText(TextRenderer & textRenderer, const Feintgine::Camera2D cam)
	{
		for (auto i = 0; i < m_tileParts.size(); i++)
		{
			m_tileParts[i].drawText(textRenderer,cam);
		}
	}

	void F_TileManager::restartTileStatus()
	{
		for (auto i = 0; i < m_tileParts.size(); i++)
		{
			m_tileParts[i].resetStatus();
		}
	}

	Feintgine::F_TilePart F_TileManager::getTilePartByIndex(int index)
	{
		F_TilePart retTile;
		if (index > 0 && index < m_tileParts.size())
		{
			retTile = m_tileParts[index];			
		}
		else
		{
			//std::cout << "waring , empty retTile \n";
		}
		return retTile;
	}

}
