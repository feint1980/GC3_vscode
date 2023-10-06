#include "F_Boss_Base.h"
#include "F_Player.h"



#define RANDOM_DISTANCE_VALUE_X 300.0f
#define RANDOM_DISTANCE_VALUE_Y 150.0f

F_Boss_Base::F_Boss_Base()
{
	m_isDecided = false;
}


F_Boss_Base::~F_Boss_Base()
{
}

void F_Boss_Base::draw(Feintgine::SpriteBatch & spriteBatch)
{

	m_animation.draw(spriteBatch);
	m_dialougeHandler.draw(spriteBatch);

}

void F_Boss_Base::update(float deltaTime, F_Player & player)
{
	// mandatory animation update;
	m_animation.setPos(m_pos);
	m_animation.update(deltaTime);
	m_dialougeHandler.update(deltaTime);
	handleAI(deltaTime);

}

void F_Boss_Base::drawLight(Feintgine::LightBatch & lightBatch)
{

}

void F_Boss_Base::handleInput(Feintgine::InputManager & inputManager)
{
	m_dialougeHandler.handleInput(inputManager);
}

void F_Boss_Base::init(const std::string & animationFile,
	const std::string & stateFile, const std::string & dialougeFile)
{
	m_animation.init(animationFile);
	m_dialougeHandler.loadDiaglouge(dialougeFile,1.0f);
	m_animation.playAnimation("idle");
	m_pos = glm::vec2(0, 200);
}

void F_Boss_Base::startDialouge(const std::string & dialougeID)
{
	m_dialougeHandler.playDialouge(dialougeID);
}


void F_Boss_Base::loadState(const std::string & filePath, bool preloaded /*= true*/)
{
	xml_document<> doc;

	std::string fileLocation = "./Data/stageData/bosses/";
	fileLocation.append(filePath);
	std::vector<char> buffer;
	if (preloaded)
	{
		buffer = Feintgine::ResourceManager::getPreloadedFile(fileLocation);
	}
	else
	{
		std::ifstream  file(fileLocation);
		buffer = std::vector<char>((std::istreambuf_iterator<char>(file)), \
			std::istreambuf_iterator<char>());
		buffer.push_back('\0');
	}

	doc.parse<0>(&buffer[0]);

	xml_node<> *BossStates_node = nullptr;

	auto now = std::chrono::system_clock::now();
	BossStates_node = doc.first_node("BossStates");

	if (!BossStates_node)
	{
		std::cout << "Error while parsing value action for Boss in F_Boss_Base.cpp \n";
	}
	else
	{
		for (xml_node<> * ComboState_node = BossStates_node->first_node("ComboState");
			ComboState_node; ComboState_node = ComboState_node->next_sibling())
		{
				

		}
	}
}

void F_Boss_Base::registerTextGUI(Feintgine::GUI & gui,
	const std::string & name, const glm::vec2 & pos, const glm::vec2 & dim)
{
	m_dialougeHandler.registerTextGUI(gui, name, pos, dim);
}

void F_Boss_Base::handleAI(float deltaTime)
{
	m_AICounterTime += 0.1f * deltaTime;


	if (m_AICounterTime > 20.0f)
	{
		m_AICounterTime = 0.0;
		m_destination = glm::vec2(feint_common::Instance()->getRandomNum(-RANDOM_DISTANCE_VALUE_X, RANDOM_DISTANCE_VALUE_X),
			feint_common::Instance()->getRandomNum(0, RANDOM_DISTANCE_VALUE_X));
		m_firstDistance = glm::length(m_destination - m_pos);
		m_isDecided = true;
		m_direction = m_destination - m_pos;
		if (m_direction.x < 0)
		{
			m_animation.playAnimation("left");
		}
		else
		{
			m_animation.playAnimation("right");
		}
	}

	if (m_isDecided)
	{

		float t_distance = glm::length(m_destination - m_pos);

		if (t_distance > 50.0f)
		{
			m_pos += m_direction * (t_distance / m_firstDistance) *0.025f  * deltaTime;
		}
		else
		{
			m_isDecided = false;
			m_animation.playAnimation("idle");
		}
	}


}
