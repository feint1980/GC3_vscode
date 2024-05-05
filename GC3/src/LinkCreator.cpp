#include "LinkCreator.h"



/*
	Callstack create a link

	Update with main amplifier list
	select an amplifier 
	put that amplifier in second list
	create a link, then put it in a list
	result that multiple link creation can be created


*/

LinkCreator::LinkCreator()
{

}


LinkCreator::~LinkCreator()
{

}

void LinkCreator::draw(Feintgine::SpriteBatch & spriteBatch)
{
// 	for (int i = 0; i < m_amplifiers.size(); i++)
// 	{
// 		m_amplifiers[i]->draw(spriteBatch);
// 	}

	for (int i = 0; i < m_links.size(); i++)
	{
		m_links[i]->draw(spriteBatch);
	}

}

void LinkCreator::update(float deltaTime, std::vector<FairyBase *> & amplifiers, std::vector<EnemyBulletBase *> enemy_bullets, F_Player & player)
{


	for(auto i = 0; i < amplifiers.size(); i++)
	{
		if((amplifiers[i])->getInternalID() == AMPLIFIER)
		{
			auto t2 = dynamic_cast<EnemyAmplifier *>(amplifiers[i]);
			{
				if (t2->getLinkPartner())
				{
					if (t2->isLeft())
					{
						if (t2->getLinkingStatus() == 1)
						{
							if (!t2->getCreateFlag())
							{
								createLink(t2);
								t2->setCreateFlag(true);
							}
							
						}
					}
				}
			}
		}
	}
	// for (int i = 0; i < amplifiers.size(); i++)
	// {
	// 	if (amplifiers[i]->getLinkPartner())
	// 	{
	// 		if (amplifiers[i]->isLeft())
	// 		{
	// 			if (amplifiers[i]->getLinkingStatus() == 1)
	// 			{
	// 				if (!amplifiers[i]->getCreateFlag())
	// 				{
	// 					createLink(amplifiers[i]);
	// 					amplifiers[i]->setCreateFlag(true);
	// 				}
					
	// 			}
	// 		}
	// 	}
	// }

// 	for (int i = 0; i < m_amplifiers.size(); i++)
// 	{
// 		m_amplifiers[i]->update(deltaTime,amplifiers, player);
// 	}

	for (int i = 0; i < m_links.size(); i++)
	{
		if (!m_links[i]->isRemove())
		{
			m_links[i]->update(deltaTime, enemy_bullets, player);
		}
		else
		{
			m_links.erase(m_links.begin() + i);
		}
		
	}
}

void LinkCreator::registerAudioEngine(Feintgine::AudioEngine * audioEngine)
{
	m_audioEngine = audioEngine;
}

void LinkCreator::drawDebug(Feintgine::DebugRender & debugRenderer)
{
	for (int i = 0; i < m_links.size(); i++)
	{
		m_links[i]->drawDebug(debugRenderer);
	}
}

void LinkCreator::createLink(EnemyAmplifier * amplifier)
{

	std::cout << "create a link \n";
	m_amplifiers.push_back(amplifier);

	LinkAmplifier * link = new LinkAmplifier();

	int index = m_amplifiers.size() - 1;

	//link->init("Assets/F_AObjects/lightning_effect.xml", m_amplifiers[index]->getPos(), m_amplifiers[index]);


	link->init("Assets/F_AObjects/lightning_effect.xml", m_amplifiers[index]->getPos(), m_amplifiers[index]);
	link->registerAudioEngine(m_audioEngine);
	m_links.push_back(link);

}

void LinkCreator::clearList()
{

	for (auto i = 0; i < m_links.size(); i++)
	{
		m_links.erase(m_links.begin() + i);
	}

	for (auto i = 0; i < m_amplifiers.size(); i++)
	{
		m_amplifiers.erase(m_amplifiers.begin() + i);
	}
	m_links.clear();
	m_amplifiers.clear();


	
}

