#include "AnimatedObject.h"



AnimatedObject::AnimatedObject()
{
}


AnimatedObject::~AnimatedObject()
{
}

void AnimatedObject::init(const std::string & filePath)
{
	m_playing = false;
	m_animations.clear();
	xml_document<> doc;
	
	std::ifstream file(filePath.c_str());
	std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);

	xml_node<> * AObj_node = nullptr;

	AObj_node = doc.first_node("AObj");

	m_name = AObj_node->first_attribute("name")->value();
	m_texture = Feintgine::ResourceManager::getTexture(AObj_node->first_attribute("texture")->value());
	col = std::stoi(AObj_node->first_attribute("col")->value());
	row = std::stoi(AObj_node->first_attribute("row")->value());

	xml_node<> * animations_node = AObj_node->first_node("animations");
	
	for (xml_node<> * animation_node = animations_node->first_node("animation");
		animation_node; animation_node = animation_node->next_sibling())
	{
		animation t_animation;
		std::string animationName = animation_node->first_attribute("name")->value();
		t_animation.loopKey = 0;
		int counter = 0;
		xml_node<> * anims_node = animation_node->first_node("anims");
		for (xml_node<> * anim_node = anims_node->first_node("anim");
			anim_node; anim_node = anim_node->next_sibling())
		{
			anim t_anim;
			t_anim.index =std::stoi(anim_node->first_attribute("index")->value());
			t_anim.time = std::stoi(anim_node->first_attribute("time")->value());
			if (anim_node->first_attribute("loop"))
			{
				t_animation.loopKey = counter;
			}
			t_animation.anims.push_back(t_anim);
			counter++;
		}

		m_animations.insert(std::pair<std::string, animation>(animationName, t_animation));
	}

	
	m_color = Feintgine::Color(255, 255, 255, 255);
	m_pos = glm::vec2(0);
	m_dims = glm::vec2((float)m_texture.width / col, (float)m_texture.height / row);

	//startAnimation(m_animations.begin()->first);
	is_init = true;

}

void AnimatedObject::startAnimation(const std::string & name)
{

	//std::cout << "start playing " << name << "\n";
	std::map<std::string, animation>::iterator it = m_animations.begin();
	it = m_animations.find(name);

	if (it != m_animations.end())
	{
		m_currentAnimation = (*it).second;
		currentAnim = 0;
		m_index = m_currentAnimation.anims[currentAnim].index;
		
	}
	else
	{
	//	std::cout << " can not find animation " << name << "\n";
	}


}

void AnimatedObject::updateAnim()
{
	if (m_playing)
	{
	
	
		currentTime++;

		if (currentTime > m_currentAnimation.anims[currentAnim].time)
		{
			
			
			currentAnim++;
			
			currentTime = 0;
			
			
			
		
			
			if (currentAnim >= m_currentAnimation.anims.size())
			{
				currentAnim = 0;
				if (m_currentAnimation.loopKey != 0)
				{
					currentAnim += m_currentAnimation.loopKey;
				}
			}
			//std::cout << "current anium " << currentAnim << "\n";
			//std::cout << m_currentAnimation.anims[currentAnim].index << "\n";

			m_index = m_currentAnimation.anims[currentAnim].index;
		}
		
	
	
	}
	
}

glm::vec4 AnimatedObject::CalculateUV()
{
	int xTile = m_index % col;
	int yTile = m_index / col;

	glm::vec4 uv;
	uv.x = xTile / (float)col;

	
	uv.y = yTile / (float)row;
	uv.z = 1.0f / col;
	uv.w = 1.0f / row;

	//std::cout << "uv " << uv.x  << "\t " << uv.y << "\t " << uv.z << "\t " << uv.w << "\t " << "\n";
	return uv;

}

void AnimatedObject::update()
{
	updateAnim();
}

void AnimatedObject::draw(Feintgine::SpriteBatch & spriteBatch)
{

	m_uv = CalculateUV();

	glm::vec4 desRect;
	desRect.x = m_pos.x - m_dims.x / 2.0f;
	desRect.y = m_pos.y - m_dims.y / 2.0f;
	desRect.z = m_dims.x;
	desRect.w = m_dims.y;

	if (invert)
	{
		m_uv.x += 1.0f / m_texture.height;
		m_uv.z *= -1;
	}

	spriteBatch.draw(desRect, m_uv, m_texture.id, m_depth, m_color,m_angle);


}

void AnimatedObject::setPlaying(bool val)
{
	m_playing = val;
}


void AnimatedObject::setPos(const glm::vec2 & pos)
{
	m_pos = pos;
}

void AnimatedObject::toggleAnim()
{
	if (m_playing)
	{
		m_playing = false;
	}
	else
	{
		m_playing = true;
	}
}



void AnimatedObject::setInvert(bool value)
{
	invert = value;
}
