
// #include "Player.h"
// #include <iostream>
// #include <string>
// #include <stdio.h>
// #include <ResourceManager.h>

// void Player::init(glm::vec2 position,
// 	const glm::vec2& drawDims,
// 	const glm::vec2 &collisonDims,
// 	Feintgine::Color color,
// 	Feintgine::Window & window, Feintgine::Camera2D * camera  , std::string name) {
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


// 	m_moveSpeed = MOVEMENT_SPEED;



// 	std::cout << feint_common::Instance()->convertVec2toString(m_pos) << "\n";

// 	/*mon_pos = m_pos + glm::vec2(7, -4);*/

// 	m_playerName = new Feintgine::SpriteFont("Fonts/OpenSans-Italic.ttf", 64);
// 	/*m_playerMon = new Feintgine::SpriteFont("Fonts/OpenSans-Italic.ttf", 64);*/
	
// 	m_name = name;// +"�";

// 	buffer_name = _strdup(m_name.c_str());

// 	//m_chatBub.loadTexture("Textures/black.png");

// 	is_init = true;
// 	/*buffer_mon = strdup(Feintgine::DataManager::Instance()->account_currency[1].c_str());*/
	
// 	//std::cout << Feintgine::DataManager::Instance()->getPlayerID();
// 	//m_stamina.init(Feintgine::ResourceManager::getTexture("Textures/bar.png"), glm::vec2(-13, 10), glm::vec2(0.2, 5), Feintgine::Color(30, 255, 30, 255));

// }

// void Player::destroy()
// {
// 	m_controlable = false;
// 	m_isAlive = false;


// }

// void Player::draw(Feintgine::SpriteBatch& spriteBatch) {
// 	glm::vec4 destRect;
// 	destRect.x = m_pos.x - m_dims.x / 2.0f;
// 	destRect.y = m_pos.y - m_dims.y / 2.0f;
// 	destRect.z = m_dims.x;
// 	destRect.w = m_dims.y;

// 	//std::cout << "pos is " << feint_common::Instance()->convertVec2toString(m_pos) << "\n";

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

	



// }


// void Player::drawGUI(Feintgine::SpriteBatch& GUIspriteBatch)
// {
// 	//m_stamina.draw(GUIspriteBatch,stamina_bar);



// }

// void Player::drawDebug(Feintgine::DebugRender & renderer)
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


// void Player::push()
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

// void Player::animation()
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

// void Player::setPos(const glm::vec2 & pos)
// {
// 	m_pos = pos;

// }

// void Player::setInit(bool value)
// {
// 	is_init = value;
// }



// void Player::say(const std::string & msg)
// {
	



// 	std::string convert = "  " + msg;
// 	//m_chatBub.say(msg.data());
	
// 	float line = 1;
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
// 		convert += "  "+ m_secondContent;
// 		line = 2.0;
		

// 	}

	
// 		glm::vec2 m_tspos = m_pos;
// 		m_tspos.y += 1.3f + (0.65f * line);
// 		m_tspos.x -= 0.8f;
// 		glm::vec2 coord = converter->converWorldToScreen(m_tspos);
	
// 		coord.x /= (1000.0f);
// 		coord.y /= (600.0f );

// 		m_CEChatbub->setPosition(CEGUI::UVector2(CEGUI::UDim(coord.x , 0 ) , CEGUI::UDim(coord.y, 0)));
	

// 	m_CEChatbub->setText((CEGUI::utf8*) +convert.c_str());

// 	//std::cout << m_CEChatbub->getText().max_size()  <<"\n";
// 	if (line > 1)
// 	{
// 		fit = getLongest(m_CEChatbub->getRenderedString().getPixelSize(m_CEChatbub, 0), m_CEChatbub->getRenderedString().getPixelSize(m_CEChatbub, 1));
// 	}
// 	else
// 	{
// 		fit = m_CEChatbub->getRenderedString().getPixelSize(m_CEChatbub, 0);
// 	}
	

// 	m_CEChatbub->setWidth(CEGUI::UDim::UDim(fit.d_width /1000.0f , 
// 		m_CEChatbub->getRenderedString().getPixelSize(m_CEChatbub, 0).d_height));
// 	m_CEChatbub->setHeight(CEGUI::UDim::UDim(0.05 * line,0));

	
	
// 	m_chatActive = true;
// 	chatLifeTime = 0;

// }

// void Player::updateGUI()
// {
// 	if (m_chatActive)
// 	{
// 		if (!m_CEChatbub->isVisible())
// 		{
			
// 			m_CEChatbub->setVisible(true);
// 			//std::cout << m_CEChatbub->getPosition() << "\n";
// 			//std::cout << "current \n";
		
// 			//std::cout << feint_common::Instance()->convertVec2toString(coord) << "\n";

// 		}
// 		else
// 		{
// 			if (chatLifeTime < 220)
// 			{
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

// int Player::getNearst(const std::string & ts)
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

// void Player::moveToGrid(glm::vec2 & gridPos)
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
// void Player::checkOuter(std::vector<Grid>& gridList)
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
// void Player::handleInput(Feintgine::InputManager& inputManager)
// {


	
	

// 	if (m_chatBox->isActive())
// 	{
// 		isGUIfree = false;
// 		if (inputManager.isKeyPressed(SDL_BUTTON_LEFT))
// 		{
// 			if (!m_chatBox->isMouseContainedInArea())
// 			{
// 				m_chatBox->deactivate();
// 			}
			
// 		}
// 		if (inputManager.isKeyPressed(SDLK_ESCAPE))
// 		{
// 			m_chatBox->deactivate();
// 		}
// 		//if(inputManager.getMouseCoords().g)
// 	}
// 	else
// 	{
// 		isGUIfree = true;
// 	}

// 	if (isGUIfree)
// 	{

// 		if (inputManager.isKeyPressed(SDLK_RETURN))
// 		{
// 			m_chatBox->activate();
// 		}

// 		if (m_controlable)
// 		{

// // 			if (inputManager.isKeyPressed(SDLK_j))
// // 			{
// // 
// // 				m_chatBub.say("what , are you even ?");
// // 			}

// 			if (vel.x != 0 || vel.y != 0)
// 			{
// 				m_moving = true;
// 			}
// 			else
// 			{
// 				m_moving = false;
// 			}

// 			if (!m_moveHor)
// 			{
// 				if (inputManager.isKeyDown(SDLK_a))
// 				{

// 					moveLeft();
// 					//Enet_UDP::Instance()->sendPlayerState(m_name, MOVELEFT, m_pos);


// 				}

// 				else if (inputManager.isKeyDown(SDLK_d))
// 				{
// 					if (!m_moveHor)
// 					{
// 						moveRight();
// 						//Enet_UDP::Instance()->sendPlayerState(m_name, MOVERIGHT, m_pos);


// 					}
// 				}
// 				else
// 				{
					
// 				}
// 			}

// 			if (!m_moveVer)
// 			{
// 				if (inputManager.isKeyDown(SDLK_w))
// 				{
// 					moveUp();
// 					//Enet_UDP::Instance()->sendPlayerState(m_name, MOVEUP, m_pos);




// 				}



// 				else if (inputManager.isKeyDown(SDLK_s))
// 				{

// 					moveDown();
// 					//Enet_UDP::Instance()->sendPlayerState(m_name, MOVEDOWN, m_pos);


// 				}
// 				else
// 				{
// 					//stahp();
// 				}



// 			}

// 		}



// 	}
// 	else
// 	{
// 		if (inputManager.isKeyPressed(SDLK_RETURN))
// 		{
// 			chat();
// 		}
// 	}
	
// }




// void Player::velSet(const glm::vec2 & velset)
// {
// 	vel = velset;
// }



// void Player::drawChat(Feintgine::SpriteBatch & spriteBatch)
// {
// 	//m_chatBub.draw(spriteBatch);
// }

// CEGUI::Sizef Player::getLongest(CEGUI::Sizef a, CEGUI::Sizef b)
// {
// 	if (a.d_width > b.d_width)
// 	{
// 		return a;
// 	}
// 	return b;
	
// }

// void Player::stahp()
// {
// 	vel = glm::vec2(0);
// 	numTiles = 1;
// 	m_moving = false;
// 	m_moveVer = false;
// 	m_moveHor = false;
// 	//m_controlable = true;
// }
// void Player::move()
// {
// 	if (stamina_bar > 0.07f)
// 	{
// 		stamina_bar -= 0.00005;
// 		switch (m_facing)
// 		{
// 		case PlayerFacing::LEFT:
// 			vel = glm::vec2(-m_moveSpeed, 0);
// 			numTiles = 3;
// 			break;
// 		case PlayerFacing::RIGHT:
// 			vel = glm::vec2(m_moveSpeed, 0);
// 			numTiles = 3;
// 			break;
// 		case PlayerFacing::UP:
// 			vel = glm::vec2(0, m_moveSpeed);
// 			numTiles = 2;
// 			break;
// 		case PlayerFacing::DOWN:
// 			vel = glm::vec2(0, -m_moveSpeed);
// 			numTiles = 2;
// 			break;

// 		default:

// 			break;
// 		}
// 	}

// }


// void Player::loadGUI(Feintgine::GUI &gui)
// {
// 	m_chatBox = static_cast<CEGUI::Editbox*>(gui.createWidget("TaharezLook/Editbox",
// 		glm::vec4(0.01f, 0.95f, 0.38f, 0.05f), glm::vec4(0), "chatBox"));
// 	m_chatBox->setMaxTextLength(MAXKEY);


// 	glm::vec2 m_tspos = m_pos;
// 	m_tspos.y += 80.0f;
// 	glm::vec2 coord = converter->converWorldToScreen(m_tspos);
// 	coord.x /= 1000.0f;
// 	coord.y /= 600.0f;

// 	m_CEChatbub = static_cast<CEGUI::DefaultWindow*> (gui.createWidget("TaharezLook/StaticText",
// 		glm::vec4(coord.x, coord.y, 0.1, 0.05), glm::vec4(0), m_name + "chatBub"));
// 	m_CEChatbub->setProperty("HorzFormatting", "HorzCentred");
// 	m_CEChatbub->setVisible(false);

	

// 	//m_chatBox->
// 	m_submitbutton = static_cast<CEGUI::PushButton*>(gui.createWidget("Vanilla/Button",
// 		glm::vec4(0.4f, 0.95f, 0.1f, 0.05f), glm::vec4(0), "submitChat"));
// 	m_submitbutton->setText("Chat");



// 	m_submitbutton->subscribeEvent(CEGUI::DefaultWindow::EventMouseClick, [&](const CEGUI::EventArgs & e) {
// 		chat();
// 		return true;
// 	});
// }

// void Player::chat()
// {
	
// 	std::wstring message = feint_common::Instance()->convertStringtoWstring(m_chatBox->getText().c_str());
// 	if (message.size() > 0)
// 	{

// 		ClientSocket::Instance()->chat(m_name, feint_common::Instance()->convertWstringToString(message));
// 		m_chatBox->setText("");
// 		m_chatBox->deactivate();
// 	}

// }



// void Player::moveLeft()
// {
// 	m_facing = PlayerFacing::LEFT;
// 	move();
// 	m_moveVer = true;
// }

// void Player::moveRight()
// {
// 	m_facing = PlayerFacing::RIGHT;
// 	move();
// 	m_moveVer = true;
// }

// void Player::moveUp()
// {
// 	m_facing = PlayerFacing::UP;
// 	move();
// 	m_moveHor = true;

// }

// void Player::moveDown()
// {
// 	m_facing = PlayerFacing::DOWN;
// 	move();
// 	m_moveHor = true;
// }

// void Player::tileCollide(std::vector<PushableObject> & objectList)
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
// bool Player::checkColide(PushableObject & obj)
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

// // void Player::addMon(float value)
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

// void Player::tileCollide(std::vector<TownTile> & objectList)
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
// bool Player::checkColide(TownTile & obj)
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
// void Player::update(std::vector<Grid> &gridList, std::vector<PushableObject> &objectList, std::vector<TownTile> & simpleObjectList) {


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

// 	//m_chatBub.update(m_pos);

// 	updateGUI();

// }

// // void Player::refreshItem()
// // {
// // 	m_inventory.init(glm::vec2(11, 2), glm::vec2(5, 6), glm::vec2(5, 4),m_gui);
// // }
