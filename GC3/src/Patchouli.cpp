// #include "Patchouli.h"
// #include <iostream>
// 
// 
// void Patchouli::update()
// {
// 
// 	updateAnim();
// 	if (starLight)
// 	{
// 		if (m_light.size <= 200.0f)
// 		{
// 			m_light.size += 4.5f;
// 		}
// 		else
// 		{
// 			if (m_tileIndex == 0)
// 			{
// 				starLight = false;
// 				createTheWall();
// 				explod();
// 				cheat_physic = true;
// 			}		
// 		}
// 	}
// 	else
// 	{
// 		if (m_tileIndex == 0)
// 		{
// 			if (m_light.size >= 0)
// 			{
// 				m_light.size -= 5.0f;
// 			}
// 		}
// 		
// 	}
// 	if (!offTrigger)
// 	{
// 		if (m_tileIndex == 8)
// 		{
// 			starLight = true;
// 			offTrigger = true;
// 		}
// 	}
// 
// 
// 
// }
// 
// 
// 
// 
// 
// void Patchouli::velSet(glm::vec2 newLoc, float time)
// {
// 	m_anchorTime = 0;
// 	m_moveTime = time;
// 	isMoving = true;
// 	m_velset = newLoc;
// 
// }
// 
// 
// void Patchouli::addStone()
// {
// 	
// 	
// 
// }
// 
// void Patchouli::draw(Feintgine::SpriteBatch & spriteBatch)
// {
//  
// 	
// 	m_depth++;
// 	//glBlendFunc(GL_DST_ALPHA, GL_DST_ALPHA);
// 
// 	glm::vec4 destRect;
// 	destRect.x = m_postion.x - m_dimentions.x / 2.0f;
// 	destRect.y = m_postion.y - m_dimentions.y / 2.0f;
// 	destRect.z = m_dimentions.x;
// 	destRect.w = m_dimentions.y;
// 
// 	glm::vec4 uvRect = m_spriteSheet.getUVs(m_tileIndex);
// 
// 	if (m_direction == -1) {
// 
// 		uvRect.x += 1.0f / m_spriteSheet.dims.x;
// 		uvRect.z *= -1;
// 	}
// 
// 
// 	spriteBatch.draw(destRect, uvRect, m_spriteSheet.texture.id, m_depth, m_color, m_angle);
// 	
// 
// 
// 
// }
// 
// void Patchouli::drawChildren(Feintgine::SpriteBatch & spriteBatch)
// {
// 	//glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
// 	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
// 	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
// 	glm::vec2 converted_pos = m_postion;
// 	if (m_direction != -1)
// 	{
// 		converted_pos.x -= 2.0f;
// 	}
// 	else
// 	{
// 		converted_pos.x += 2.0f;
// 	}
// 	for (int i = 0; i < m_stones.size(); i++)
// 	{
// 	
// 		
// 		m_stones[i].fayde_spec(1.0f, 2.5f, 0.05f);
// 		m_stones[i].update(converted_pos);
// 		m_stones[i].draw(spriteBatch);
// 	}
// 	//m_stone.setPos(converted_pos);
// 
// 	m_sigil.setPos(converted_pos);
// 	m_sigil.setAngle(m_sigil.getAngle() + .01f);
// 	
// 	m_sigil.fayde_spec(0.7f, 4.5f, 0.025f);
// 		
// 	m_sigil.draw(spriteBatch);
// 	//m_core_stone.draw(spriteBatch);
// 	
// }
// 
// void Patchouli::drawLight(Feintgine::SpriteBatch & spriteBatch)
// {
// 	glm::vec2 converted_pos = m_postion;
// 	if (m_direction != -1)
// 	{
// 		converted_pos.x -= 2.0f;
// 	}
// 	else
// 	{
// 		converted_pos.x += 2.0f;
// 	}
// 	m_light.position = converted_pos;
// 	m_light.draw(spriteBatch);
// }
// 
// void Patchouli::moveLeft()
// {
// 	m_direction = -1;
// 	m_postion.x -= 0.25f;
// 	
// 	playAnimation("Move");
// 	
// }
// 
// void Patchouli::moveRight()
// {
// 	m_direction = 1;
// 	m_postion.x += 0.25f;
// 
// 	playAnimation("Move");
// }
// 
// void Patchouli::handleInput(Feintgine::InputManager& inputManager)
// {
// 	if (inputManager.isKeyPressed(SDLK_j))
// 	{
// 		playAnimation("Book");
// 		
// 	}
// 	if (inputManager.isKeyPressed(SDLK_k))
// 	{
// 		playAnimation("Fly");
// 	}
// 	if (inputManager.isKeyDown(SDLK_a))
// 	{
// 		moveLeft();
// 	}
// 	if (inputManager.isKeyDown(SDLK_d))
// 	{
// 		moveRight();
// 	}
// 
// }
// 
// void Patchouli::handleStone()
// {
// 	
// }
// 
// void Patchouli::onInit()
// {
// 	float f = 0;
// 	for (int i = 0; i < 5; i++)
// 	{
// 		m_stone.init(Feintgine::ResourceManager::getTexture("Textures/bosses/patchouli/stone_pure.png"), glm::vec2(m_postion), glm::vec2(2.8), Feintgine::Color(255, 251, 25, 255));
// 		m_core_stone.init(Feintgine::ResourceManager::getTexture("Textures/bosses/patchouli/stone_pure.png"), glm::vec2(m_postion), glm::vec2(1.4f), Feintgine::Color(255, 251, 25, 255));
// 		m_stone.setCirCleAngle(f);
// 		m_core_stone.setCirCleAngle(f);
// 		m_core_stone.setCore(true);
// 		m_core_stone.setDepth(4.0f);
// 		m_stones.push_back(m_stone);
// 		m_stones.push_back(m_core_stone);
// 		f += 10.0f;
// 
// 	}
// 	m_light.color = Feintgine::Color(255, 251, 25, 255);
// 	m_light.size = 0.0f;
// 	m_sigil.init(Feintgine::ResourceManager::getTexture("Textures/bosses/patchouli/a_sigil.png"), glm::vec2(0, 10), glm::vec2(12), Feintgine::Color(244, 40, 255, 255));
// 	
// 	std::cout << m_stones.size();
// }
// 
// void Patchouli::createTheWall()
// {
// 	b2BodyDef groundBodyDef;
// 	groundBodyDef.position.Set(0, -45.0f);
// 
// 	b2Body * groundBody = m_world->CreateBody(&groundBodyDef);
// 	b2PolygonShape box;
// 	box.SetAsBox(75, 5);
// 	groundBody->CreateFixture(&box, 0);
// 
// 
// 	b2BodyDef leftBodyDef;
// 	leftBodyDef.position.Set(-68, 0);
// 
// 	b2Body * leftWall = m_world->CreateBody(&leftBodyDef);
// 	box.SetAsBox(5, 75);
// 	leftWall->CreateFixture(&box, 0);
// 
// 	b2BodyDef rightBodyDef;
// 	rightBodyDef.position.Set(16, 0);
// 
// 	b2Body * rightWall = m_world->CreateBody(&rightBodyDef);
// 	box.SetAsBox(5, 75);
// 	rightWall->CreateFixture(&box, 0);
// 
// 
// 	b2BodyDef topBodyDef;
// 	topBodyDef.position.Set(0, 45);
// 
// 	b2Body * topWall = m_world->CreateBody(&topBodyDef);
// 	box.SetAsBox(75, 5);
// 	topWall->CreateFixture(&box, 0);
// }
// 
// void Patchouli::setB2World(b2World * world)
// {
// 	m_world = world;
// }
// 
// void Patchouli::setBlocks(std::vector<block> blocks)
// {
// 	m_blocks = blocks;
// }
// 
// void Patchouli::explod()
// {
// 	for (int i = 0; i < m_blocks.size(); i++)
// 	{
// 		m_blocks[i].getBody()->ApplyLinearImpulse(m_blocks[i].summonDirection(glm::vec2(m_postion.x,m_postion.y)), m_blocks[i].getBody()->GetWorldCenter(), true);
// 		m_blocks[i].getBody()->SetAngularVelocity(4.7f);
// 	}
// }
// 
