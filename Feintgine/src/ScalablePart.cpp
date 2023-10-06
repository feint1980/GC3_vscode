#include "ScalablePart.h"



namespace FeintGUI
{

	ScalablePart::ScalablePart()
	{
	}


	ScalablePart::~ScalablePart()
	{
	}

	void ScalablePart::init(const std::string & guiName, glm::vec2 mainPos, glm::vec2 dim, unsigned short partFlag)
	{
		

 		m_partFlag = partFlag;
		std::cout << "test convert " << guiName << "\n";
		std::string total = guiName +"_"+ getPartName() + ".png";
 		std::cout << "test full " << total << "\n";

		m_sprite = Feintgine::SpriteManager::Instance()->getSprite(total);


	}

	void ScalablePart::calculateProperty(glm::vec2 mainPos, glm::vec2 mainDim)
	{
		float scaleFactory_x;
		float scaleFactory_y;
		switch (m_partFlag)
		{
		case TOP_LEFT_PART:
			m_scale = glm::vec2(1);
			m_pos.x = mainPos.x - (mainDim.x / 2.0f) -( m_sprite.getDim().x/2.0f);
			m_pos.y = mainPos.y + mainDim.y / 2.0f + (m_sprite.getDim().y / 2.0f);
			//m_dim = glm::vec2(1);
			
			break;
		case TOP_BORDER_PART:
			scaleFactory_x = (mainDim.x / m_sprite.getDim().x);
			m_scale = glm::vec2(scaleFactory_x,1);
			m_pos.x = mainPos.x ;
			m_pos.y = mainPos.y + mainDim.y / 2.0f + (m_sprite.getDim().y / 2.0f);
			break;
		case TOP_RIGHT_PART:
			m_scale = glm::vec2(1);
			m_pos.x = mainPos.x + (mainDim.x / 2.0f) + (m_sprite.getDim().x / 2.0f);
			m_pos.y = mainPos.y + mainDim.y / 2.0f + (m_sprite.getDim().y / 2.0f);
			break;
		case RIGHT_BORDER_PART:
			scaleFactory_y = (mainDim.y / m_sprite.getDim().y);
			m_scale = glm::vec2(1, scaleFactory_y);
			m_pos.x = mainPos.x + mainDim.x / 2.0f + (m_sprite.getDim().x / 2.0f);;
			m_pos.y = mainPos.y;
			break;
		case BOT_RIGHT_PART:
			m_scale = glm::vec2(1);
			m_pos.x = mainPos.x + (mainDim.x / 2.0f) + (m_sprite.getDim().x / 2.0f);
			m_pos.y = mainPos.y - mainDim.y / 2.0f - (m_sprite.getDim().y / 2.0f);
			break;
		case BOT_BORDER_PART:
			scaleFactory_x = (mainDim.x / m_sprite.getDim().x);
			m_scale = glm::vec2(scaleFactory_x, 1);
			m_pos.x = mainPos.x;
			m_pos.y = mainPos.y - mainDim.y / 2.0f - (m_sprite.getDim().y / 2.0f);
			break;
		case BOT_LEFT_PART:
			m_scale = glm::vec2(1);
			m_pos.x = mainPos.x - (mainDim.x / 2.0f) - (m_sprite.getDim().x / 2.0f);
			m_pos.y = mainPos.y - mainDim.y / 2.0f - (m_sprite.getDim().y / 2.0f);
			break;
		case LEFT_BORDER_PART:
			scaleFactory_y = (mainDim.y / m_sprite.getDim().y);
			m_scale = glm::vec2(1, scaleFactory_y);
			m_pos.x = mainPos.x - mainDim.x / 2.0f - (m_sprite.getDim().x / 2.0f);;
			m_pos.y = mainPos.y;
			break;
		case CENTER_PART:
			scaleFactory_x = (mainDim.x / m_sprite.getDim().x);
			scaleFactory_y = (mainDim.y / m_sprite.getDim().y);
			m_pos = mainPos; 
			m_scale = glm::vec2(scaleFactory_x, scaleFactory_x);
			break;
		default:
			break;
		}
	}



	void ScalablePart::draw(Feintgine::SpriteBatch & spriteBatch)
	{
		glm::vec4 desRect;// (0, 0, 50, 50);
		desRect.x = m_pos.x - (m_sprite.getDim().x * m_scale.x / 2.0f);
		desRect.y = m_pos.y - (m_sprite.getDim().y * m_scale.y / 2.0f);
		desRect.z = m_scale.x * m_sprite.getDim().x;
		desRect.w = m_scale.y * m_sprite.getDim().y;

		//spriteBatch.draw(desRect, uvrect, m_sprite.getTexture().id, m_depth, m_color, 0.0f, m_spec);
		glm::vec4 calculateUV = m_sprite.getUV();

// 		calculateUV.x += m_scale.x;
// 		calculateUV.y += m_scale.y;
		spriteBatch.draw(desRect, calculateUV, m_sprite.getTexture().id, 100, Feintgine::Color(255,255,255,255) , 0.0f);
		//spriteBatch.draw(desRect, m_sprite.getUV(), m_sprite.getTexture().id, m_depth, m_color, m_spec);

	}

	std::string ScalablePart::getPartName()
	{
		switch (m_partFlag)
		{
		case TOP_LEFT_PART :
			return "top_left";
		case TOP_BORDER_PART:
			return "border_top";
		case TOP_RIGHT_PART:
			return "top_right";
		case RIGHT_BORDER_PART:
			return "border_right";
		case BOT_RIGHT_PART:
			return "bottom_right";
		case BOT_BORDER_PART:
			return "border_bot";
		case BOT_LEFT_PART:
			return "bottom_left";
		case LEFT_BORDER_PART:
			return "border_left";
		case CENTER_PART:
			return "center";
		default:
			return "Invalid part !!!!";
		}
	}

}
