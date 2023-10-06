#include "ChatBubble.h"



ChatBubble::ChatBubble()
{
	uvrect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	m_spriteFont = new Feintgine::SpriteFont("Fonts/LiberationMono-Regular.ttf", 64);
	lifeTime = 0; 
	limitTime = 0;
	
}


ChatBubble::~ChatBubble()
{
}

void ChatBubble::update(glm::vec2 pos)
{
	m_pos = pos + glm::vec2(0,2.1f);
	if (lifeTime < limitTime)
	{
	lifeTime++;

	}
	else
	{
		isShow = false;
	}
	if (!isShow)
	{
		if (m_color.a > 0 || m_textColor.a > 0)
		{
			m_color.a -= 5;
			m_textColor.a -= 5;
		}
		else
		{
			isClean = true;
		}
	
	}
	
}

void ChatBubble::draw(Feintgine::SpriteBatch & spriteBatch)
{
	if (!isClean)
	{

		//std::cout << " draw call \n";
		char * bufferName = _strdup(m_content.c_str());
		char * secondBuffer = _strdup(m_secondContent.c_str());

		glm::vec4 desRect;
		desRect.x = m_pos.x - m_dims.x / 2.0f;
		desRect.y = m_pos.y - m_dims.y / 2.0f;
		desRect.z = m_dims.x;
		desRect.w = m_dims.y;
		spriteBatch.draw(desRect, glm::vec4(-1.0f, -1.0f, 2.0f, 2.0f), m_texture.id, 20.0f, m_color, 0);
		
	
		m_spriteFont->draw(spriteBatch,
			bufferName, m_pos - pos1, glm::vec2(0.0085f),
			25.0f, m_textColor, Feintgine::Justification::MIDDLE);
		m_spriteFont->draw(spriteBatch,
			secondBuffer, m_pos- pos2, glm::vec2(0.0085f),
			25.0f, m_textColor, Feintgine::Justification::MIDDLE);
	}

	
}

void ChatBubble::loadTexture(const std::string & filePath)
{
	m_texture = Feintgine::ResourceManager::getTexture(filePath);
}

void ChatBubble::say(const std::string & msg )
{
	if (msg != "")
	{
		if(msg.size() > MAXKEY/2 && msg.find(" "))
		{
			//std::cout << "detected \n";
			//std::cout << << "\n";
			int findIndex = getnearst(msg);
			std::cout << findIndex << "\n";
			m_content = msg.substr(0, findIndex);

			m_secondContent = msg.substr(findIndex, msg.size()-1);
			line = 2;
		}		
		else
		{
			line = 1;
			m_content = msg;
			m_secondContent = "";
		}
		lifeTime = 0;
		limitTime = basicTime + msg.size() * 10;
		isClean = false;
		isShow = true;
		m_dims = basicDim + glm::vec2(0.32f * (float)getMax(m_content.size() , m_secondContent.size()), 1.0f * (float)line);
		m_color = Feintgine::Color(255, 255, 255, 160);
		m_textColor = Feintgine::Color(255, 255, 255, 255);
	}

	if (line > 1)
	{
		 pos1 = glm::vec2(0, -0.1f);
		 pos2 = glm::vec2(0, 0.7f);
		//std::cout << "multi line \n";
	}
	else
	{
		 pos1 = glm::vec2(0, 0.4f);
		 pos2 = glm::vec2(0, 0.7f);;
		//std::cout << line << "single line \n";
	}

}

int ChatBubble::getnearst(const std::string & ts)
{
	int sizeRule = ts.size()/2;
	int biggest = ts.size()/2;
	for (int i = 0; i < ts.size(); i++)
	{
		if (ts[i] == ' ')
		{
			//std::cout << " found " << i << "\n";
			if (abs(i - sizeRule) < abs(biggest))
			{
				biggest =  i- sizeRule;
				//std::cout << "changed " << biggest << "\n";
			}
		}
	}
	return biggest + sizeRule;
}

int ChatBubble::getMax( int t1,  int t2)
{
	if (t1 > t2)
	{
		return t1;
	}
	return t2;
}

