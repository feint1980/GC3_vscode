// #include "BasicMonster.h"


// BasicMonster::BasicMonster()
// {
// }


// BasicMonster::~BasicMonster()
// {
// }


// void BasicMonster::init(const glm::vec2& position,
// 	const glm::vec2& drawDims,
// 	const glm::vec2 &collisonDims,
// 	Feintgine::Color color) {
// 	Feintgine::GLTexture texture = Feintgine::ResourceManager::getTexture("Textures/kl.png");
// 	m_color = color;
// 	m_dims = drawDims;
// 	m_pos = position;
// 	m_colisDims = collisonDims;
// 	m_texture.init(texture, glm::ivec2(10, 8));
// 	tileIndex = 10;
// 	numTiles = 1;
// 	vel = glm::vec2(0);
// 	m_direction = 0;
// 	m_fireTexture = Feintgine::ResourceManager::getTexture("Textures/fire.png");

// }



// void BasicMonster::draw(Feintgine::SpriteBatch& spriteBatch) {
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

// 	if (m_fire != nullptr)
// 	{
// 		m_fire->draw(spriteBatch);
// 	}
// 	// Draw the sprite
// 	spriteBatch.draw(destRect, uvRect, m_texture.texture.id, 1.0f, m_color, 1.0f);
// }

// void BasicMonster::drawDebug(Feintgine::DebugRender & renderer)
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
// 	if (m_fire != nullptr)
// 	{
// 		m_fire->drawDebug(renderer);
// 	}

// }




// void BasicMonster::animation()
// {

// 	if (m_isdraged)
// 	{
// 		m_isSkill = false;
// 		m_moving = false;
// 		numTiles = 1;
	
// 	}

// 	if (m_isSkill)
// 	{
// 		fire();
// 		if (m_action != MonsterAction::SKILL)
// 		{
// 			m_action = MonsterAction::SKILL;

// 			m_animTime = 0.0f;
// 		}

// 	}
// 	else
// 	{

// 		if (!m_isdraged)
// 		{


// 			switch (m_facing)
// 			{
// 			case MonsterFacing::LEFT:
// 				tileIndex = 60;
// 				m_direction = 1;

// 				break;
// 			case MonsterFacing::RIGHT:

// 				tileIndex = 60;
// 				m_direction = -1;

// 				break;
// 			case MonsterFacing::UP:


// 				tileIndex = 40;
// 				break;
// 			case MonsterFacing::DOWN:
// 				tileIndex = 50;

// 				break;

// 			default:

// 				break;
// 			}
// 		}
// 	}


// 	if (foundTarget && !m_isSkill)
// 	{
// 		m_animSpeed = 0.22f;
// 	}
// 	else
// 	{
// 		m_animSpeed = MONSTER_ANIM_SPEED;
// 	}
// 	m_animTime += m_animSpeed;

// 	// Apply animation


// 	if (m_animTime > numTiles) {
// 		m_isSkill = false;
// 		m_action = MonsterAction::IDLE;
// 		flameable = true;

// 	}
// 	//
	
// 	tileIndex = tileIndex + (int)m_animTime % numTiles;

// }

// void BasicMonster::setPos(const glm::vec2 & pos)
// {
// 	m_pos = pos;

// }

// void BasicMonster::moveToGrid(glm::vec2 & gridPos)
// {
// 	/*if (!m_moving && !m_moveHor)
// 	{
// 		switch (m_facing)
// 		{
// 		case MonsterFacing::LEFT:
// 			if (m_pos.x > gridPos.x)
// 			{
// 				velSet(glm::vec2(-MONSTER_MOVE_SPEED, 0));
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
// 		case MonsterFacing::RIGHT:
// 			if (m_pos.x < gridPos.x)
// 			{
// 				velSet(glm::vec2(MONSTER_MOVE_SPEED, 0));
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


// 		case MonsterFacing::UP:
// 			if (m_pos.y < gridPos.y)
// 			{
// 				velSet(glm::vec2(0, MONSTER_MOVE_SPEED));
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
// 		case MonsterFacing::DOWN:
// 			if (m_pos.y > gridPos.y)
// 			{
// 				velSet(glm::vec2(0, -MONSTER_MOVE_SPEED));
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
// 	}*/
// 	if (!m_moving)
// 	{
// 		setPos(gridPos);
// 		move_blocked = false;
// 	}


// }
// void BasicMonster::fire()
// {
	
// 	//std::cout << "fire";
// 	tileIndex = 63;
// 	numTiles = 2;
// 	m_animSpeed = 0.042f;
	
	

// }
// void BasicMonster::checkOuter(std::vector<Grid>& gridList)
// {
// 	float leftOuterSide = m_pos.x - m_dims.x;
// 	float rightOuterSide = m_pos.x + m_dims.x;
// 	float upperOuterSide = m_pos.y + m_dims.y;
// 	float downerOuterSide = m_pos.y - m_dims.y;

// 	float leftSide = m_pos.x - m_colisDims.x / 2.0f;
// 	float rightSide = m_pos.x + m_colisDims.x / 2.0f;
// 	float upperSide = m_pos.y + m_colisDims.y / 2.0f;
// 	float downerSide = m_pos.y - m_colisDims.y / 2.0f;



// 	// for (auto & g : gridList)
// 	// {
// 	// 	if (g.getPos().x > leftOuterSide &&  g.getPos().x < rightOuterSide && g.getPos().y < upperOuterSide && g.getPos().y > downerOuterSide)
// 	// 	{
// 	// 		if (g.getPos().x >= leftSide && g.getPos().x <= rightSide && g.getPos().y <= upperSide && g.getPos().y >= downerSide)
// 	// 		{
// 	// 			//g.changeColor(Feintgine::Color(0, 255, 0, 255));
// 	// 			if (move_delay >  AI_RECALCULATE)
// 	// 			{
// 	// 				//moveToGrid(g.getPos());
// 	// 			}
				
			
// 	// 			stahp();
// 	// 		}
// 	// 		else
// 	// 		{

// 	// 		}
// 	// 	}

// 	// }
// }


// void BasicMonster::velSet(const glm::vec2 & velset)
// {
// 	vel = velset;
// }
// void BasicMonster::stahp()
// {
// 	vel = glm::vec2(0);
	
// 	m_moving = false;


// 	//move_delay = 0;
// 	//m_controlable = true;
// }
// void BasicMonster::AI()
// {
// 	//std::cout << "AI called \n";
// 	//std::cout << vel.x << "\n";
// 	if (!m_isdraged)
// 	{
// 		int dir = rand() % 4;

// 		switch (dir)
// 		{
// 		case 0:

// 			m_facing = MonsterFacing::LEFT;


// 			break;
// 		case 1:
// 			m_facing = MonsterFacing::RIGHT;

// 			break;
// 		case 2:
// 			m_facing = MonsterFacing::UP;

// 			break;
// 		case 3:
// 			m_facing = MonsterFacing::DOWN;

// 			break;
// 		default:
// 			break;
// 		}
// 	}
	
// }
// void BasicMonster::move()
// {
	
// 	if (!m_isSkill)
// 	{

// 		m_moving = true;
// 		numTiles = 3;

// 		float moveSpeed;
// 		if (!foundTarget)
// 		{
// 			moveSpeed = MONSTER_MOVE_SPEED;
// 		}
// 		else
// 		{
// 			moveSpeed = MONSTER_MOVE_SPEED * 1.8f;
// 		}
// 		switch (m_facing)
// 		{
// 		case MonsterFacing::LEFT:
// 			vel = glm::vec2(-moveSpeed, 0);
// 			m_hitBox = new HitBox(glm::vec2(m_pos.x, m_pos.y - m_colisDims.y / 2), glm::vec2(-8.0f, m_colisDims.y), 0.11f, 1);


// 			break;
// 		case MonsterFacing::RIGHT:
// 			vel = glm::vec2(moveSpeed, 0);
// 			m_hitBox = new HitBox(glm::vec2(m_pos.x, m_pos.y - m_colisDims.y / 2), glm::vec2(8.0f, m_colisDims.y), 0.11f, 2);

// 			break;
// 		case MonsterFacing::UP:
// 			vel = glm::vec2(0, moveSpeed);
// 			m_hitBox = new HitBox(glm::vec2(m_pos.x - m_colisDims.x / 2, m_pos.y), glm::vec2(m_colisDims.x, 8.1f), 0.11f, 3);

// 			break;
// 		case MonsterFacing::DOWN:
// 			vel = glm::vec2(0, -moveSpeed);
// 			m_hitBox = new HitBox(glm::vec2(m_pos.x - m_colisDims.x / 2, m_pos.y), glm::vec2(m_colisDims.x, -8.1f), 0.11f, 4);
// 			break;

// 		default:

// 			break;
// 		}
// 	}

// }
// void BasicMonster::tileCollide(std::vector<PushableObject> & objectList)
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

// 			if (o.pushing)
// 			{
				
// 				m_isdraged = true;
// 				switch (o.m_pushDirection)
// 				{
// 				case 1:
// 					setPos(glm::vec2(o.getPos().x - o.getDims().x / 2, o.getPos().y));
// 					tileIndex = 30;
// 					numTiles = 1;
// 					break;
// 				case 2:
// 					setPos(glm::vec2(o.getPos().x + o.getDims().x / 2, o.getPos().y));
// 					tileIndex = 30;
// 					numTiles = 1;
// 					break;
// 				case 3:
// 					setPos(glm::vec2(o.getPos().x , o.getPos().y + o.getDims().y / 2));
// 					tileIndex = 20;
// 					numTiles = 1;
// 					break;
// 				case 4:
// 					setPos(glm::vec2(o.getPos().x , o.getPos().y - o.getDims().y / 2));
// 					tileIndex = 20;
// 					numTiles = 1;
// 					break;

// 				default:
// 					break;
// 				}
// 			}

// 			//	o.changeColor(Feintgine::Color(255, 0, 0, 255));
// 			setPos(m_pos - vel);
// 			stahp();
// 			move_blocked = true;
// 			if (foundTarget)
// 			{
// 				if (m_facing == MonsterFacing::LEFT || m_facing == MonsterFacing::RIGHT)
// 				{
// 					m_isSkill = true;
// 					m_moving = false;
// 				}
				
// 			}
// 			if (m_isdraged)
// 			{
// 				if (o.getVel().x == 0 && o.getVel().y == 0)
// 				{
// 					destroy();
// 				}
// 			}
// 		}
// 		else
// 		{
// 			//o.changeColor(Feintgine::Color(255, 255, 255, 255));
// 		}
// 	}




// }
// void BasicMonster::destroy()
// {
// 	isAlive = false;
// }
// void BasicMonster::tileCollide(std::vector<OutsideGrid> & objectList)
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
// 			stahp();
// 			move_blocked = true;
// 		}
// 		else
// 		{
// 			//o.changeColor(Feintgine::Color(255, 255, 255, 255));
// 		}
// 	}




// }
// bool BasicMonster::checkColide(Player & obj)
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
// bool BasicMonster::checkColide(OutsideGrid & obj)
// {


// 	float leftSideA = m_pos.x - m_colisDims.x / 3.0f;
// 	float rightSideA = m_pos.x + m_colisDims.x / 3.0f;
// 	float upperSideA = m_pos.y + m_colisDims.y / 3.0f;
// 	float downSideA = m_pos.y - m_colisDims.y / 3.0f;

// 	float leftSideB = obj.getPos().x - obj.getDimentions().x / 2.0f;
// 	float rightSideB = obj.getPos().x + obj.getDimentions().x / 2.0f;
// 	float upperSideB = obj.getPos().y + obj.getDimentions().y / 2.0f;
// 	float downSideB = obj.getPos().y - obj.getDimentions().y / 2.0f;



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
// bool BasicMonster::checkColide(PushableObject & obj)
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
// void BasicMonster::update(std::vector<Grid> &gridList, std::vector<PushableObject> &objectList, std::vector<OutsideGrid> & outList , Player & player) {


// 	if (player.isActive())
// 	{

// 		animation();

// 		if (m_fire != nullptr)
// 		{
// 			m_fire->lastm(objectList, player);
// 			if (m_fire->isGone)
// 			{
// 				delete m_fire;
// 				m_fire = nullptr;
// 			}
// 		}

// 		if (tileIndex == 64 && flameable)
// 		{

// 			m_animSpeed = 0.0001f;
// 			switch (m_facing)
// 			{
// 			case MonsterFacing::LEFT:
// 				m_fire = new Fire();
// 				m_fire->init(glm::vec2(m_pos.x - m_colisDims.x / 2, m_pos.y), glm::vec2(3, 0.4), m_fireTexture, Feintgine::Color(255, 255, 255, 255), glm::vec2(1));
// 				m_fire->setDirection(-1);
// 				break;
// 			case MonsterFacing::RIGHT:
// 				m_fire = new Fire();
// 				m_fire->init(glm::vec2(m_pos.x + m_colisDims.x / 2, m_pos.y), glm::vec2(3, 0.4), m_fireTexture, Feintgine::Color(255, 255, 255, 255), glm::vec2(1));
// 				break;
// 			case MonsterFacing::UP:
// 				break;
// 			case MonsterFacing::DOWN:
// 				break;

// 			default:
// 				break;
// 			}
// 			flameable = false;
// 		}

// 		if (!move_blocked)
// 		{
// 			stahp();
// 			move();
// 		}

// 		if (checkColide(player))
// 		{
// 			player.destroy();
			
// 		}

// 		m_pos += vel;
// 		if (m_action != MonsterAction::SKILL)
// 		{
// 			if (move_delay > AI_RECALCULATE)
// 			{
// 				if (!foundTarget)
// 				{
// 					AI();
// 					move_delay = 0;
// 				}

// 			}
// 		}

// 		move_delay++;




// 		tileCollide(objectList);
// 		if (!m_isdraged)
// 		{
// 			checkOuter(gridList);
// 			tileCollide(outList);
// 		}

// 		if (m_hitBox != nullptr)
// 		{
// 			//m_hitBox->update(objectList);
// 			if (m_hitBox->track(player))
// 			{
// 				foundTarget = true;
// 				m_hitBox->m_lifeTime = 0.0f;


// 			}
// 			else
// 			{
// 				foundTarget = false;
// 			}
// 			if (m_hitBox->onDestroySelf())
// 			{
// 				m_hitBox->destroy();
// 				m_hitBox = nullptr;
// 			}
// 		}


// 	}
// }

