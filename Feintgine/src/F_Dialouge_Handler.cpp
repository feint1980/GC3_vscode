#include "F_Dialouge_Handler.h"
#include <iostream>

#define LEFT_AVT_X_POS_MIN -200
#define LEFT_AVT_X_POS_MAX -100
#define AVT_Y_POS_MIN 0
#define AVT_Y_POS_MAX 100 
#define RIGHT_AVT_X_POS_MIN 300
#define RIGHT_AVT_X_POS_MAX 200

#define AVT_POS_MOVE_RATE 5.0f

// right is invert

Feintgine::F_Dialouge_Handler::F_Dialouge_Handler()
{
	//m_leftAvtPos = glm::vec2(LEFT_AVT_X_POS_MIN, AVT_Y_POS_MIN);
	//m_rightAvtPos = glm::vec2(RIGHT_AVT_X_POS_MIN, AVT_Y_POS_MIN);
	//m_leftAvtColor = Fe
}


Feintgine::F_Dialouge_Handler::~F_Dialouge_Handler()
{

}

void Feintgine::F_Dialouge_Handler::loadDiaglouge(const std::string & path, 
	float scale)
{
	m_showLeftAvatar = false;
	m_showRightAvatar = false;
	m_scale = scale;


	m_filePath = path;
	m_dialouges.clear();
	m_currentLine = -1;

	xml_document<> doc;
	//doc.utf
	std::vector<char> buffer = ResourceManager::getPreloadedFile(m_filePath.c_str());
	buffer.push_back('\0');
	//rapidxml::xml_node<char*> element = find
	doc.parse<0>(&buffer[0]);
	//doc.ut
	//doc.pa

	xml_node<> * F_Dialouges_node = nullptr;
	F_Dialouges_node = doc.first_node("F_Dialouges");

	if (!F_Dialouges_node)
	{
		
		exit(69);
	}
	xml_node<> * dialouges_node = F_Dialouges_node->first_node("dialouges");

	for (xml_node<> * dialouge_node = dialouges_node->first_node("dialouge");
		dialouge_node; dialouge_node = dialouge_node->next_sibling())
	{


		Dialouge dialouge;
		dialouge.m_id = dialouge_node->first_attribute("ID")->value();
		xml_node<> * chars_node = dialouge_node->first_node("chars");
		if (chars_node)
		{
			
			for (xml_node<> * char_node = chars_node->first_node("char");
				char_node; char_node = char_node->next_sibling())
			{
				Dialouge_Avatar avt;
				avt.loadSpritePacket(char_node->first_attribute("name")->value());
				dialouge.m_chacters.push_back(avt);

			}
		}
		xml_node<> * lines_node = dialouge_node->first_node("lines");
		if (lines_node)
		{
			for (xml_node<> * line_node = lines_node->first_node("line");
				line_node; line_node = line_node->next_sibling())
			{
				Line line;
				int charNum = std::atoi(line_node->first_attribute("character")->value());
				std::wstring msg = feint_common::Instance()->convertStringtoWstring(line_node->first_attribute("content")->value());
				bool isLeft = std::atoi(line_node->first_attribute("face")->value()) == 1;
				int emojiNum = std::atoi(line_node->first_attribute("emote")->value());

				line.init(charNum, msg, isLeft, emojiNum);
				dialouge.m_lines.push_back(line);
				
			}
		}
		m_dialouges.push_back(dialouge);

	}


	m_bg.init(Feintgine::ResourceManager::getTexture("Textures/black.png"),
		glm::vec2(0, -200), glm::vec2(660.0f, 340.0f), Feintgine::Color(255, 255, 255, 125));


	//playDialouge("first_encounter");
}

void Feintgine::F_Dialouge_Handler::draw(SpriteBatch & spriteBatch)
{
	if (m_isShowing)
	{


		desRect.x = m_leftAvtPos.x - (m_leftAvt.getDim().x * m_scale) / 2.0f;
		desRect.y = m_leftAvtPos.y - (m_leftAvt.getDim().y * m_scale) / 2.0f;
		desRect.z = m_leftAvt.getDim().x  * m_scale;
		desRect.w = m_leftAvt.getDim().y  * m_scale;
		spriteBatch.draw(desRect, m_leftAvt.getUV(), m_leftAvt.getTexture().id, 60, m_leftAvtColor, 0);

		desRect2.x = m_rightAvtPos.x - (m_rightAvt.getDim().x * m_scale) / 2.0f;
		desRect2.y = m_rightAvtPos.y - (m_rightAvt.getDim().y * m_scale) / 2.0f;
		desRect2.z = m_rightAvt.getDim().x  * m_scale;
		desRect2.w = m_rightAvt.getDim().y  * m_scale;
		m_rightAvt.setInvert(true);
		spriteBatch.draw(desRect2, m_rightAvt.getUV(), m_rightAvt.getTexture().id, 60, m_rightAvtColor, 0);

		m_bg.draw(spriteBatch);
	}
}

void Feintgine::F_Dialouge_Handler::handleInput(InputManager & inputManager)
{
	if (m_isShowing)
	{


		if (inputManager.isKeyPressed(SDLK_j))
		{
			goNext();
		}
	}
}

void Feintgine::F_Dialouge_Handler::update(float deltaTime)
{
	handleTransition(deltaTime);
}

void Feintgine::F_Dialouge_Handler::goNext()
{
	m_currentLine++;
	if (m_currentLine >= m_currentDialouge.m_lines.size())
	{
		m_isShowing = false;
		m_leftAvtColor = Feintgine::Color(0, 0, 0, 0);
		m_rightAvtColor = Feintgine::Color(0, 0, 0, 0);
		m_drawElement.setText(L"");
		
		return;
	}
	Line lineData = m_currentDialouge.m_lines[m_currentLine];
	m_msgContent = lineData.msgContent;
	

	m_isTransition = true;
	if (lineData.m_isLeft)
	{
		m_showLeftAvatar = true;
		m_showRightAvatar = false;
		m_isLeft = true;
		m_leftAvtColor = Feintgine::Color(255, 255, 255, 255);
		
		m_leftAvt = getCharacterEmote(m_currentDialouge.m_chacters[lineData.characterNum-1], lineData.emoji);// ;
	}
	else
	{
		m_isLeft = false;

		m_rightAvtColor = Feintgine::Color(255, 255, 255, 255);
		m_showLeftAvatar = false;
		m_showRightAvatar = true;
		m_rightAvt = getCharacterEmote(m_currentDialouge.m_chacters[lineData.characterNum-1], lineData.emoji);// ;
	}

	m_drawElement.setText(m_msgContent);
}

void Feintgine::F_Dialouge_Handler::playDialouge(const std::string & dialougeID)
{
	m_leftAvt = Feintgine::F_Sprite();
	m_rightAvt = Feintgine::F_Sprite();
	m_leftAvtPos = glm::vec2(LEFT_AVT_X_POS_MIN, AVT_Y_POS_MIN);
	m_rightAvtPos = glm::vec2(RIGHT_AVT_X_POS_MIN, AVT_Y_POS_MIN);
	for (int i = 0; i < m_dialouges.size(); i++)
	{
		if (m_dialouges[i].m_id == dialougeID.c_str())
		{
			m_currentDialouge = m_dialouges[i];

			
			m_currentLine = -1;
			m_isShowing = true;
			goNext();
			
			return;
		}
	}
	
	
}

Feintgine::F_Sprite Feintgine::F_Dialouge_Handler::getCharacterEmote(Dialouge_Avatar & dialougeAvr, int emoteNum)
{

	std::string spriteName = dialougeAvr.getFileName();

	return dialougeAvr.getSpriteByNum(emoteNum);
	
}

void Feintgine::F_Dialouge_Handler::handleTransition(float deltaTime)
{
	if (m_isTransition)
	{
		if (m_isLeft)
		{
			//LEFT 
			
			m_leftAvtColor.change(15, 0.025f, 1.01f);
			m_rightAvtColor.change(15, 0.025f, 0.51f);

			

			if (m_leftAvtPos.x < LEFT_AVT_X_POS_MAX)
			{
				m_leftAvtPos.x += AVT_POS_MOVE_RATE * deltaTime * m_additionalDeltaTime;
			}
			else
			{
				m_leftAvtPos.x = LEFT_AVT_X_POS_MAX;
				m_isTransition = false;
			}
			if (m_leftAvtPos.y < AVT_Y_POS_MAX)
			{
				m_leftAvtPos.y += AVT_POS_MOVE_RATE * deltaTime * m_additionalDeltaTime;
			}
			else
			{
				m_leftAvtPos.y = AVT_Y_POS_MAX;
			}
			// RIGHT
			if (m_rightAvtPos.x > RIGHT_AVT_X_POS_MIN)
			{
				m_rightAvtPos.x -= AVT_POS_MOVE_RATE * deltaTime * m_additionalDeltaTime;
			}
			else
			{
				m_rightAvtPos.x = RIGHT_AVT_X_POS_MIN;
			}
			if (m_rightAvtPos.y > AVT_Y_POS_MIN)
			{
				m_rightAvtPos.y -= AVT_POS_MOVE_RATE * deltaTime * m_additionalDeltaTime;
			}
			else
			{
				m_rightAvtPos.y = AVT_Y_POS_MIN;
			}

		}
		else
		{

			m_rightAvtColor.change(15, 0.025f, 1.01f);
			m_leftAvtColor.change(15, 0.025f, 0.51f);
			//RIGHT 
			if (m_rightAvtPos.x > RIGHT_AVT_X_POS_MAX)
			{
				m_rightAvtPos.x -= AVT_POS_MOVE_RATE * deltaTime * m_additionalDeltaTime;
			}
			else
			{
				m_rightAvtPos.x = RIGHT_AVT_X_POS_MAX;
				
			}
			if (m_rightAvtPos.y < AVT_Y_POS_MAX)
			{
				m_rightAvtPos.y += AVT_POS_MOVE_RATE * deltaTime * m_additionalDeltaTime;
			}
			else
			{
				m_rightAvtPos.y = AVT_Y_POS_MAX;
				m_isTransition = false;
			}
			// LEFT
			if (m_leftAvtPos.x > LEFT_AVT_X_POS_MIN)
			{
				m_leftAvtPos.x -= AVT_POS_MOVE_RATE * deltaTime * m_additionalDeltaTime;
			}
			else
			{
				m_leftAvtPos.x = LEFT_AVT_X_POS_MIN;
			}
			if (m_leftAvtPos.y > AVT_Y_POS_MIN)
			{
				m_leftAvtPos.y -= AVT_POS_MOVE_RATE * deltaTime * m_additionalDeltaTime;
			}
			else
			{
				m_leftAvtPos.y = AVT_Y_POS_MIN;
			}
		}


	}

}

void Feintgine::F_Dialouge_Handler::registerTextGUI(Feintgine::GUI & gui,
	const std::string & name, const glm::vec2 & pos,
	const glm::vec2 & dim)
{

	m_drawElement.init(name.c_str(), pos);
	//m_drawElement.setAlignment(0);

	m_drawElement.setPos(glm::vec2(-400, 200));

}

void Feintgine::F_Dialouge_Handler::setText(const std::string & msg)
{
	m_drawElement.setText(msg);
	float rasSize = 0.012f;
	rasSize *= msg.size();
	//m_drawElement.setDim(glm::vec2(rasSize, 0.1f));
}

void Feintgine::F_Dialouge_Handler::setText(const std::wstring & msg)
{
	m_drawElement.setText(msg);
	float rasSize = 0.012f;
	rasSize *= msg.size();
	//m_drawElement.setDim(glm::vec2(rasSize, 0.1f));
}
