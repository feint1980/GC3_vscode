// #include "OtherPlayer.h"
// #include <iostream>
// #include <string>
// #include <stdio.h>
// #include <ResourceManager.h>
// #include <iostream>
// void OtherPlayer::init(glm::vec2 position,
// 	const glm::vec2& drawDims,
// 	const glm::vec2 &collisonDims,
// 	Feintgine::Color color,
// 	Feintgine::Window & window, Feintgine::Camera2D * camera, const std::string & name) {
// 	//m_gui = gui;

// 	Feintgine::GLTexture texture = Feintgine::ResourceManager::getTexture("Textures/rabit.png");
// 	m_paste_window = window;
// 	converter = camera; 
// 	m_color = color;
// 	m_dims = drawDims;
// 	m_pos = position;
// 	m_colisDims = collisonDims;
// 	m_texture.init(texture, glm::ivec2(10, 12));
// 	tileIndex = 0;
// 	numTiles = 1;
// 	vel = glm::vec2(0);
// 	m_direction = 0;

// 	//std::cout << feint_common::Instance()->convertVec2toString(camera.getPosition()) << "\n";


// 	m_moveSpeed = MOVEMENT_SPEED;


// 	m_name = name;
// 	buffer_name = strdup(m_name.c_str());



// 	/*mon_pos = m_pos + glm::vec2(7, -4);*/

// 	m_playerName = new Feintgine::SpriteFont("Fonts/OpenSans-Italic.ttf", 64);
// 	/*m_playerMon = new Feintgine::SpriteFont("Fonts/OpenSans-Italic.ttf", 64);*/



// 	/*buffer_mon = strdup(DataManager::Instance()->account_currency[1].c_str());*/

// 	//std::cout << DataManager::Instance()->getPlayerID();

// }

// void OtherPlayer::destroy()
// {
// 	m_controlable = false;
// 	m_isAlive = false;


// }

// void OtherPlayer::draw(Feintgine::SpriteBatch& spriteBatch) {
// 	glm::vec4 destRect;
// 	destRect.x = m_pos.x - m_dims.x / 2.0f;
// 	destRect.y = m_pos.y - m_dims.y / 2.0f;
// 	destRect.z = m_dims.x;
// 	destRect.w = m_dims.y;



// 	glm::vec4 uvRect = m_texture.getUVs(tileIndex);

// 	// Check direction
// 	if (m_direction == -1) {

// 		uvRect.x += 1.0f / m_texture.dims.x;
// 		uvRect.z *= -1;
// 	}




// 	// Draw the sprite
// 	spriteBatch.draw(destRect, uvRect, m_texture.texture.id, 5.0f, m_color, 1.0f);
// 	m_playerName->draw(spriteBatch,
// 		buffer_name, m_pos + glm::vec2(0, 0.4f), glm::vec2(0.0085f),
// 		6.0f, Feintgine::Color(22, 240, 240, 255), Feintgine::Justification::MIDDLE);

// 	m_chatBub.draw(spriteBatch);

// }


// void OtherPlayer::drawGUI(Feintgine::SpriteBatch& GUIspriteBatch)
// {
// 	//m_stamina.draw(GUIspriteBatch,stamina_bar);



// }

// void OtherPlayer::loadGUI(Feintgine::GUI &gui)
// {

// 	glm::vec2 m_tspos = m_pos;
// 	m_tspos.y += 80.0f;
// 	glm::vec2 coord = converter->converWorldToScreen(m_tspos);
// 	coord.x /= 1000.0f;
// 	coord.y /= 600.0f;
// 	m_CEChatbub = static_cast<CEGUI::DefaultWindow*> (gui.createWidget("TaharezLook/StaticText",
// 		glm::vec4(coord.x, coord.y, 0.1, 0.05), glm::vec4(0), m_name + "chatBub"));
// 	m_CEChatbub->setProperty("HorzFormatting", "HorzCentred");
// 	m_CEChatbub->setVisible(false);
// }

// void OtherPlayer::drawDebug(Feintgine::DebugRender & renderer)
// {
// 	// the actual collison 
// 	glm::vec4 destRect;
// 	destRect.x = m_pos.x - m_colisDims.x / 2.0f;
// 	destRect.y = m_pos.y - m_colisDims.y / 2.0f;
// 	destRect.z = m_colisDims.x;
// 	destRect.w = m_colisDims.y;


// 	//Outer collsion
// 	glm::vec4 destRectOuter;

// 	destRectOuter.x = m_pos.x - m_dims.x;
// 	destRectOuter.y = m_pos.y - m_dims.y;
// 	destRectOuter.z = m_dims.x * 2;
// 	destRectOuter.w = m_dims.y * 2;


// 	//Center pos
// 	glm::vec4 centerPos;

// 	centerPos.x = m_pos.x;
// 	centerPos.y = m_pos.y;
// 	centerPos.z = 0.1f;
// 	centerPos.w = 0.1f;

// 	renderer.drawBox(destRect, Feintgine::Color(0, 255, 0, 255), 0);
// 	renderer.drawBox(centerPos, Feintgine::Color(255, 0, 0, 255), 0);
// 	renderer.drawBox(destRectOuter, Feintgine::Color(255, 255, 0, 255), 0);

// 	if (m_hitBox != nullptr)
// 	{
// 		m_hitBox->drawDebug(renderer);
// 	}


// }


// void OtherPlayer::push()
// {

// 	m_controlable = false;
// 	stamina_bar -= 0.04;
// 	switch (m_facing)
// 	{
// 	case PlayerFacing::LEFT:
// 		m_hitBox = new HitBox(glm::vec2(m_pos.x, m_pos.y), glm::vec2(-0.6f, 0.1f), 0.3f, 1);

// 		break;
// 	case PlayerFacing::RIGHT:
// 		m_hitBox = new HitBox(glm::vec2(m_pos.x, m_pos.y), glm::vec2(0.6f, 0.1f), 0.3f, 2);

// 		break;
// 	case PlayerFacing::UP:
// 		m_hitBox = new HitBox(glm::vec2(m_pos.x, m_pos.y), glm::vec2(0.1f, .6f), 0.3f, 3);

// 		break;
// 	case PlayerFacing::DOWN:

// 		m_hitBox = new HitBox(glm::vec2(m_pos.x, m_pos.y), glm::vec2(0.1f, -.6f), 0.3f, 4);
// 		break;
// 	default:
// 		break;

// 	}


// }

// void OtherPlayer::animation()
// {

// 	float animSpeed = ANIMATION_SPEED;

// 	if (m_isAlive)
// 	{

// 		switch (m_facing)
// 		{
// 		case PlayerFacing::LEFT:
// 			tileIndex = 100;
// 			m_direction = 1;
// 			break;
// 		case PlayerFacing::RIGHT:
// 			tileIndex = 100;
// 			m_direction = -1;
// 			break;
// 		case PlayerFacing::UP:
// 			tileIndex = 90;
// 			break;
// 		case PlayerFacing::DOWN:
// 			tileIndex = 110;
// 			break;

// 		default:
// 			break;
// 		}

// 		if (m_isPushing)
// 		{
// 			velSet(glm::vec2(0));
// 			m_controlable = false;
// 			animSpeed = 0.22f;
// 			switch (m_facing)
// 			{
// 			case PlayerFacing::LEFT:
// 				tileIndex = 82;
// 				numTiles = 2;
// 				m_direction = 1;
// 				break;
// 			case PlayerFacing::RIGHT:
// 				tileIndex = 82;
// 				numTiles = 2;
// 				m_direction = -1;
// 				break;
// 			case PlayerFacing::UP:
// 				tileIndex = 84;
// 				numTiles = 2;
// 				break;
// 			case PlayerFacing::DOWN:
// 				tileIndex = 80;
// 				numTiles = 2;
// 				break;

// 			default:
// 				break;
// 			}

// 			if (m_action != PlayerAction::PUSH)
// 			{
// 				m_action = PlayerAction::PUSH;

// 				m_animTime = 0.0f;
// 			}
// 		}
// 		else
// 		{
// 			m_controlable = true;
// 		}
// 	}
// 	else
// 	{


// 		if (deathTime > 0.8f)
// 		{

// 			animSpeed = 0.08f;
// 			if (deadType == 0)
// 			{
// 				if (tileIndex == 34)
// 				{
// 					tileIndex = 34;
// 					numTiles = 1;
// 				}
// 				else
// 				{
// 					tileIndex = 30;
// 					numTiles = 5;
// 				}
// 			}
// 			else
// 			{
// 				if (tileIndex == 18)
// 				{
// 					tileIndex = 18;
// 					numTiles = 1;
// 				}
// 				else
// 				{
// 					tileIndex = 11;
// 					numTiles = 8;
// 				}
// 			}



// 		}

// 		else
// 		{
// 			if (deadType == 0)
// 			{
// 				tileIndex = 40;
// 				numTiles = 2;
// 			}
// 			else
// 			{
// 				tileIndex = 10;
// 				numTiles = 1;
// 			}

// 		}
// 		deathTime += 0.01f;
// 	}

// 	// Increment animation time
// 	m_animTime += animSpeed;

// 	// Check for push end
// 	if (m_animTime > numTiles) {
// 		m_isPushing = false;
// 		m_action = PlayerAction::IDLE;
// 		m_controlable = true;

// 	}
// 	// Apply animation
// 	tileIndex = tileIndex + (int)m_animTime % numTiles;

// }

// void OtherPlayer::setPos(const glm::vec2 & pos)
// {
// 	m_pos = pos;

// }

// void OtherPlayer::moveLeft()
// {
// 	m_facing = PlayerFacing::LEFT;
// 	move();
// 	m_moveVer = true;
// }

// void OtherPlayer::moveRight()
// {
// 	m_facing = PlayerFacing::RIGHT;
// 	move();
// 	m_moveVer = true;
// }

// void OtherPlayer::moveUp()
// {
// 	m_facing = PlayerFacing::UP;
// 	move();
// 	m_moveHor = true;
// }

// void OtherPlayer::moveDown()
// {
// 	m_facing = PlayerFacing::DOWN;
// 	move();
// 	m_moveHor = true;
// }

// void OtherPlayer::setFacing(int value)
// {
// 	switch (value)
// 	{
// 	case MOVELEFT:
// 		m_facing = PlayerFacing::LEFT;
// 		break;
// 	case MOVERIGHT:
// 		m_facing = PlayerFacing::RIGHT;
// 		break;
// 	case MOVEUP:
// 		m_facing = PlayerFacing::UP;
// 		break;
// 	case MOVEDOWN:
// 		m_facing = PlayerFacing::DOWN;
// 		break;
// 	default:
// 		break;
// 	}
// 	move();
// }

// void OtherPlayer::moveToGrid(glm::vec2 & gridPos)
// {
// 	if (!m_moving && !m_moveHor)
// 	{
// 		switch (m_facing)
// 		{
// 		case PlayerFacing::LEFT:
// 			if (m_pos.x > gridPos.x)
// 			{
// 				velSet(glm::vec2(-MOVEMENT_SPEED, 0));
// 				numTiles = 3;
// 				m_controlable = false;

// 			}
// 			else
// 			{
// 				setPos(gridPos);
// 				numTiles = 1;
// 				m_controlable = true;

// 			}
// 			break;
// 		case PlayerFacing::RIGHT:
// 			if (m_pos.x < gridPos.x)
// 			{
// 				velSet(glm::vec2(MOVEMENT_SPEED, 0));
// 				numTiles = 3;
// 				m_controlable = false;

// 			}
// 			else
// 			{
// 				setPos(gridPos);
// 				numTiles = 1;
// 				m_controlable = true;
// 			}
// 			break;

// 		default:
// 			break;
// 		}
// 	}
// 	if (!m_moving && !m_moveVer)
// 	{
// 		switch (m_facing)
// 		{


// 		case PlayerFacing::UP:
// 			if (m_pos.y < gridPos.y)
// 			{
// 				velSet(glm::vec2(0, MOVEMENT_SPEED));
// 				numTiles = 2;
// 				m_controlable = false;

// 			}
// 			else
// 			{
// 				setPos(gridPos);
// 				numTiles = 1;
// 				m_controlable = true;
// 			}
// 			break;
// 		case PlayerFacing::DOWN:
// 			if (m_pos.y > gridPos.y)
// 			{
// 				velSet(glm::vec2(0, -MOVEMENT_SPEED));
// 				numTiles = 2;
// 				m_controlable = false;
// 			}
// 			else
// 			{
// 				numTiles = 1;
// 				setPos(gridPos);
// 				m_controlable = true;
// 			}
// 			break;
// 		default:
// 			break;
// 		}
// 	}

// }
// void OtherPlayer::checkOuter(std::vector<Grid>& gridList)
// {
// 	float leftOuterSide = m_pos.x - m_dims.x;
// 	float rightOuterSide = m_pos.x + m_dims.x;
// 	float upperOuterSide = m_pos.y + m_dims.y;
// 	float downerOuterSide = m_pos.y - m_dims.y;

// 	float leftSide = m_pos.x - m_colisDims.x / 2.0f;
// 	float rightSide = m_pos.x + m_colisDims.x / 2.0f;
// 	float upperSide = m_pos.y + m_colisDims.y / 2.0f;
// 	float downerSide = m_pos.y - m_colisDims.y / 2.0f;



// 	for (auto & g : gridList)
// 	{
// 		if (g.getPos().x > leftOuterSide &&  g.getPos().x < rightOuterSide && g.getPos().y < upperOuterSide && g.getPos().y > downerOuterSide)
// 		{
// 			if (g.getPos().x >= leftSide && g.getPos().x <= rightSide && g.getPos().y <= upperSide && g.getPos().y >= downerSide)
// 			{
// 				//g.changeColor(Feintgine::Color(0, 255, 0, 255));
// 				moveToGrid(g.getPos());


// 			}
// 			else
// 			{

// 			}
// 		}

// 	}
// }
// void OtherPlayer::handleInput(Feintgine::InputManager& inputManager)
// {


// 	// 		if (inputManager.isKeyPressed(SDLK_i))
// 	// 		{
// 	// 			
// 	// 			if (m_inventory.show)
// 	// 			{
// 	// 				m_inventory.show = false;
// 	// 
// 	// 			}
// 	// 			else
// 	// 			{
// 	// 				m_inventory.show = true;
// 	// 
// 	// 			}
// 	// 
// 	// 		}


// 	if (stamina_bar > 0.17f)
// 	{
// 		if (inputManager.isKeyDown(SDLK_LSHIFT))
// 		{
// 			m_moveSpeed = MOVEMENT_SPEED * 1.5f;
// 			stamina_bar -= 0.005;
// 		}
// 		else
// 		{
// 			m_moveSpeed = MOVEMENT_SPEED;
// 		}

// 	}
// 	else
// 	{
// 		m_moveSpeed = MOVEMENT_SPEED;
// 	}

// 	if (m_controlable)
// 	{

// 		if (inputManager.isKeyPressed(SDLK_j))
// 		{
// 			m_isPushing = true;
// 			push();

// 		}

// 		if (vel.x != 0 || vel.y != 0)
// 		{
// 			m_moving = true;
// 		}
// 		else
// 		{
// 			m_moving = false;
// 		}

// 		if (!m_moveHor)
// 		{
// 			if (inputManager.isKeyDown(SDLK_a))
// 			{

// 				m_facing = PlayerFacing::LEFT;
// 				move();
// 				m_moveVer = true;



// 			}

// 			else if (inputManager.isKeyDown(SDLK_d))
// 			{
// 				if (!m_moveHor)
// 				{
// 					m_facing = PlayerFacing::RIGHT;
// 					move();
// 					m_moveVer = true;



// 				}
// 			}
// 			else
// 			{
// 				stahp();
// 			}
// 		}

// 		if (!m_moveVer)
// 		{
// 			if (inputManager.isKeyDown(SDLK_w))
// 			{

// 				m_facing = PlayerFacing::UP;
// 				move();
// 				m_moveHor = true;



// 			}



// 			else if (inputManager.isKeyDown(SDLK_s))
// 			{

// 				m_facing = PlayerFacing::DOWN;
// 				move();
// 				m_moveHor = true;




// 			}
// 			else
// 			{
// 				stahp();
// 			}



// 		}

// 	}

// 	// 		if (m_quickSlot.hover)
// 	// 		{
// 	// 			if (inputManager.isKeyPressed(SDL_BUTTON_RIGHT))
// 	// 			{
// 	// 				if (m_quickSlot.getItem() != nullptr)
// 	// 				{
// 	// 					m_quickSlot.remove();
// 	// 				}
// 	// 				
// 	// 			}
// 	// 		}

// 	// 	if (m_inventory.show)
// 	// 	{
// 	// 		m_inventory.update(inputManager,m_quickSlot);
// 	// 		
// 	// 
// 	// 	}
// 	// 	if (inputManager.isKeyPressed(SDLK_1))
// 	// 	{
// 	// 		stamina_bar += m_quickSlot.use();
// 	// 		m_inventory.refreshItem();
// 	// 		
// 	// 	}


// 	//std::cout << m_mousePos.y << "\n";
// 	//std::cout << ( inputManager.getMouseCoords().x -500)/35 << "  " << (inputManager.getMouseCoords().y -350)/35 << "\n";
// }




// void OtherPlayer::velSet(const glm::vec2 & velset)
// {
// 	vel = velset;
// }



// void OtherPlayer::updateGUI(glm::vec2 playerPos)
// {
// 	if (m_chatActive)
// 	{
// 		if (!m_CEChatbub->isVisible())
// 		{

// 			m_CEChatbub->setVisible(true);

// // 			glm::vec2 m_tspos =  m_pos ;
// // 			//	m_tspos.y += 40.0f + (20.0f * line);
// // 			std::cout << "Debug \n";
// // 			glm::vec2 coord = converter->converWorldToScreen(m_tspos);
// // 			std::cout << "local Pos"  <<feint_common::Instance()->convertVec2toString(coord) << "\n";
// // 			std::cout <<"World Pos"  <<feint_common::Instance()->convertVec2toString(m_pos) << "\n";
// // 			std::cout << "Camera Pos" << feint_common::Instance()->convertVec2toString(converter->getPosition()) << "\n";
// // // 			coord.x *= converter.getScale();
// // // 			coord.y *= converter.getScale();
// // 			coord.x /= (1000.0f);
// // 			coord.y /= (600.0f );
// // 
// // 			std::cout << "actual Pos" << feint_common::Instance()->convertVec2toString(coord) << "\n";


// // 			std::cout << feint_common::Instance()->convertVec2toString(m_pos) << "\n";
// // 			std::cout << feint_common::Instance()->convertVec2toString() << "\n";
 	
	
			
// 		}
// 		else
// 		{
// 			if (chatLifeTime < 220)
// 			{

// 				glm::vec2 m_tspos = m_pos ;
// 				m_tspos.y += 1.3f + (0.65f * line);
// 				m_tspos.x -= 0.8f;
// 				glm::vec2 coord = converter->converWorldToScreen(m_tspos);
// 				coord.x /= (1000.0f);
// 				coord.y /= (600.0f);

// 				m_CEChatbub->setPosition(CEGUI::UVector2(CEGUI::UDim(coord.x, 0), CEGUI::UDim(coord.y, 0)));

// 				chatLifeTime++;
// 				//m_CEChatbub->setPosition(CEGUI::UVector2()))
// 			}
// 			else
// 			{
// 				m_chatActive = false;
// 			}

// 		}
// 	}
// 	else
// 	{
// 		if (m_CEChatbub->isVisible())
// 		{
// 			m_CEChatbub->setVisible(false);
// 			chatLifeTime = 0;
// 		}
// 	}

	
// }

// CEGUI::Sizef OtherPlayer::getLongest(CEGUI::Sizef a, CEGUI::Sizef b)
// {
// 	if (a.d_width > b.d_width)
// 	{
// 		return a;
// 	}
// 	return b;
// }

// int OtherPlayer::getNearst(const std::string &ts)
// {
// 	int sizeRule = ts.size() / 2;
// 	int biggest = ts.size() / 2;
// 	for (int i = 0; i < ts.size(); i++)
// 	{
// 		if (ts[i] == ' ')
// 		{
// 			//std::cout << " found " << i << "\n";
// 			if (abs(i - sizeRule) < abs(biggest))
// 			{
// 				biggest = i - sizeRule;
// 				//std::cout << "changed " << biggest << "\n";
// 			}
// 		}
// 	}
// 	return biggest + sizeRule;
// }

// void OtherPlayer::stahp()
// {
// 	vel = glm::vec2(0);
// 	numTiles = 1;
// 	m_moving = false;
// 	m_moveVer = false;
// 	m_moveHor = false;
// 	//m_controlable = true;
// }
// void OtherPlayer::move()
// {

// 		switch (m_facing)
// 		{
// 		case PlayerFacing::LEFT:
			
// 			numTiles = 3;
// 			break;
// 		case PlayerFacing::RIGHT:
			
// 			numTiles = 3;
// 			break;
// 		case PlayerFacing::UP:
			
// 			numTiles = 2;
// 			break;
// 		case PlayerFacing::DOWN:
			
// 			numTiles = 2;
// 			break;

// 		default:

// 			break;
// 		}
	

// }

// void OtherPlayer::say(const std::string & msg)
// {




// 	std::string convert = "  " + msg;
// 	//m_chatBub.say(msg.data());

// 	line = 1;
// 	CEGUI::Sizef fit;
// 	if (convert.size() > MAXKEY / 2)
// 	{
// 		std::cout << "detected \n";
// 		//std::cout << << "\n";
// 		int findIndex = getNearst(convert);
// 		//std::cout << findIndex << "\n";
// 		std::string m_content = convert.substr(0, findIndex);

// 		std::string m_secondContent = convert.substr(findIndex, convert.size() - 1);

// 		convert = m_content + "\n";
// 		convert += "  " + m_secondContent;
// 		line = 2.0;

// 	}


	



// 	m_CEChatbub->setText((CEGUI::utf8*) + convert.c_str());

// 	//std::cout << m_CEChatbub->getText().max_size()  <<"\n";
// 	if (line > 1)
// 	{
// 		fit = getLongest(m_CEChatbub->getRenderedString().getPixelSize(m_CEChatbub, 0), m_CEChatbub->getRenderedString().getPixelSize(m_CEChatbub, 1));
// 	}
// 	else
// 	{
// 		fit = m_CEChatbub->getRenderedString().getPixelSize(m_CEChatbub, 0);
// 	}


// 	m_CEChatbub->setWidth(CEGUI::UDim::UDim(fit.d_width / 1000.0f,
// 		m_CEChatbub->getRenderedString().getPixelSize(m_CEChatbub, 0).d_height));
// 	m_CEChatbub->setHeight(CEGUI::UDim::UDim(0.05 * line, 0));



// 	m_chatActive = true;
// 	chatLifeTime = 0;

// }

// void OtherPlayer::tileCollide(std::vector<PushableObject> & objectList)
// {
// 	float leftOuterSide = m_pos.x - m_dims.x;
// 	float rightOuterSide = m_pos.x + m_dims.x;
// 	float upperOuterSide = m_pos.y + m_dims.y;
// 	float downerOuterSide = m_pos.y - m_dims.y;

// 	float leftSide = m_pos.x - m_colisDims.x / 2.0f;
// 	float rightSide = m_pos.x + m_colisDims.x / 2.0f;
// 	float upperSide = m_pos.y + m_colisDims.y / 2.0f;
// 	float downerSide = m_pos.y - m_colisDims.y / 2.0f;

// 	for (auto & o : objectList)
// 	{
// 		if (checkColide(o))
// 		{

// 			//	o.changeColor(Feintgine::Color(255, 0, 0, 255));
// 			setPos(m_pos - vel);
// 		}
// 		else
// 		{
// 			//o.changeColor(Feintgine::Color(255, 255, 255, 255));
// 		}
// 	}




// }
// bool OtherPlayer::checkColide(PushableObject & obj)
// {


// 	float leftSideA = m_pos.x - m_colisDims.x / 3.0f;
// 	float rightSideA = m_pos.x + m_colisDims.x / 3.0f;
// 	float upperSideA = m_pos.y + m_colisDims.y / 3.0f;
// 	float downSideA = m_pos.y - m_colisDims.y / 3.0f;

// 	float leftSideB = obj.getPos().x - obj.getDims().x / 2.0f;
// 	float rightSideB = obj.getPos().x + obj.getDims().x / 2.0f;
// 	float upperSideB = obj.getPos().y + obj.getDims().y / 2.0f;
// 	float downSideB = obj.getPos().y - obj.getDims().y / 2.0f;



// 	if (leftSideA > leftSideB && leftSideA < rightSideB || rightSideA > leftSideB && rightSideA < rightSideB)
// 	{
// 		if (upperSideA >= downSideB && upperSideA <= upperSideB || downSideA <= upperSideB && downSideA >= downSideB)
// 		{
// 			return true;
// 		}

// 	}
// 	if (upperSideA > downSideB && upperSideA < upperSideB || downSideA < upperSideB && downSideA > downSideB)
// 	{
// 		if (leftSideA >= leftSideB && leftSideA <= rightSideB || rightSideA >= leftSideB && rightSideA <= rightSideB)
// 		{
// 			return true;
// 		}
// 	}
// 	else
// 	{
// 		return false;
// 	}
// 	return false;
// }

// // void OtherPlayer::addMon(float value)
// // {
// // 	float totalMon = std::stof(DataManager::Instance()->account_currency[0]);
// // 	totalMon += value;
// // 	std::string strMon = std::to_string(totalMon);
// // 	std::string condition = "character_id = '";
// // 	condition.append(DataManager::Instance()->getAccountID());
// // 	condition.append("'");
// // 	DataManager::Instance()->updateData("character_currency", "currency", strdup(strMon.c_str()), strdup(condition.c_str()));
// // 
// // 	condition = "SELECT currency from character_currency WHERE character_id = '";
// // 	condition.append(DataManager::Instance()->getAccountID());
// // 	condition.append("'");
// // 
// // 	DataManager::Instance()->getTableData(strdup(condition.c_str()), DataManager::Instance()->account_currency);
// // 
// // }

// void OtherPlayer::tileCollide(std::vector<TownTile> & objectList)
// {
// 	float leftOuterSide = m_pos.x - m_dims.x;
// 	float rightOuterSide = m_pos.x + m_dims.x;
// 	float upperOuterSide = m_pos.y + m_dims.y;
// 	float downerOuterSide = m_pos.y - m_dims.y;

// 	float leftSide = m_pos.x - m_colisDims.x / 2.0f;
// 	float rightSide = m_pos.x + m_colisDims.x / 2.0f;
// 	float upperSide = m_pos.y + m_colisDims.y / 2.0f;
// 	float downerSide = m_pos.y - m_colisDims.y / 2.0f;

// 	for (auto & o : objectList)
// 	{
// 		if (o.touchable)
// 		{

// 			if (checkColide(o))
// 			{

// 				//	o.changeColor(Feintgine::Color(255, 0, 0, 255));
// 				setPos(m_pos - vel);
// 			}
// 			else
// 			{
// 				//o.changeColor(Feintgine::Color(255, 255, 255, 255));
// 			}
// 		}
// 	}




// }
// bool OtherPlayer::checkColide(TownTile & obj)
// {


// 	float leftSideA = m_pos.x - m_colisDims.x / 3.0f;
// 	float rightSideA = m_pos.x + m_colisDims.x / 3.0f;
// 	float upperSideA = m_pos.y + m_colisDims.y / 3.0f;
// 	float downSideA = m_pos.y - m_colisDims.y / 3.0f;

// 	float leftSideB = obj.getPos().x - obj.getDims().x / 2.0f;
// 	float rightSideB = obj.getPos().x + obj.getDims().x / 2.0f;
// 	float upperSideB = obj.getPos().y + obj.getDims().y / 2.0f;
// 	float downSideB = obj.getPos().y - obj.getDims().y / 2.0f;



// 	if (leftSideA > leftSideB && leftSideA < rightSideB || rightSideA > leftSideB && rightSideA < rightSideB)
// 	{
// 		if (upperSideA >= downSideB && upperSideA <= upperSideB || downSideA <= upperSideB && downSideA >= downSideB)
// 		{
// 			return true;
// 		}

// 	}
// 	if (upperSideA > downSideB && upperSideA < upperSideB || downSideA < upperSideB && downSideA > downSideB)
// 	{
// 		if (leftSideA >= leftSideB && leftSideA <= rightSideB || rightSideA >= leftSideB && rightSideA <= rightSideB)
// 		{
// 			return true;
// 		}
// 	}
// 	else
// 	{
// 		return false;
// 	}
// 	return false;
// }
// void OtherPlayer::update(glm::vec2 playerPos , std::vector<Grid> &gridList, std::vector<PushableObject> &objectList, std::vector<TownTile> & simpleObjectList) {


// 	m_chatBub.update(m_pos);
// 	if (stamina_bar > 1.0f)
// 	{
// 		stamina_bar = 1.0f;
// 	}
// 	if (stamina_bar < 0.0f)
// 	{
// 		stamina_bar = 0.0f;
// 	}
// 	else
// 	{
// 		stamina_bar += 0.0001;
// 	}



// 	animation();
// 	m_pos += vel;


// 	if (!m_isAlive)
// 	{
// 		m_controlable = false;
// 		velSet(glm::vec2(0));

// 	}

// 	checkOuter(gridList);

// 	tileCollide(objectList);
// 	tileCollide(simpleObjectList);
// 	if (m_hitBox != nullptr)
// 	{
// 		m_hitBox->update(objectList);
// 		if (m_hitBox->onDestroySelf())
// 		{
// 			m_hitBox->destroy();
// 			m_hitBox = nullptr;
// 		}
// 	}

// 	updateGUI(playerPos);

// }

// // void OtherPlayer::refreshItem()
// // {
// // 	m_inventory.init(glm::vec2(11, 2), glm::vec2(5, 6), glm::vec2(5, 4),m_gui);
// // }
