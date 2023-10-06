#include "Gohei_Rod.h"

const float ROTATE_SPEED = 0.12f;

Gohei_Rod::Gohei_Rod()
{
}


Gohei_Rod::~Gohei_Rod()
{
}


glm::vec2 t_rotatePoint(const glm::vec2& pos, float angle) {
	glm::vec2 newv;
	newv.x = pos.x * cos(angle) - pos.y * sin(angle);
	newv.y = pos.x * sin(angle) + pos.y * cos(angle);
	return newv;
}


void Gohei_Rod::init(const Feintgine::GLTexture & texture, const Feintgine::Color & color,
	const glm::vec2 & scale,float angle)
{
	m_texture = texture;
	m_color = color;
	m_scale = scale;
	m_angle = angle;
	m_isDone = false;
	m_afterImageParticle.init(&m_pos, &m_color, .3f, 10);
	m_afterImageParticle.setAlphaRate(0.2f);


	m_dim = glm::vec2(300,100);

	//positionOffset = glm::vec2(-200, -100);
	//m_angle = degreeToRad(-180);

}


void Gohei_Rod::draw(Feintgine::SpriteBatch & spriteBatch)
{
	if (!m_isDone)
	{
		glm::vec4 desRect;// (0, 0, 50, 50);
		desRect.x = m_pos.x - (m_texture.width * m_scale.x / 2.0f);
		desRect.y = m_pos.y - (m_texture.height * m_scale.y / 2.0f);
		desRect.z = m_scale.x * m_texture.width;
		desRect.w = m_scale.y * m_texture.height;
		// 
		spriteBatch.draw(desRect,glm::vec4(0,0,1,1),
			m_texture.id, 15, m_color, m_angle);
	
	}
	m_afterImageParticle.draw(spriteBatch);
}


bool Gohei_Rod::checkColliderWithEnemyBullet(const EnemyBulletBase & bullet)
{
	glm::vec2 pos = bullet.getPos();
	glm::vec2 dim = bullet.getDim() * bullet.getScale();

	glm::vec2 halfDim = m_dim * 0.5f;

// 	glm::vec2 tl = glm::vec2(-halfDim.x, halfDim.y) + m_pos;
// 	glm::vec2 bl = glm::vec2(-halfDim.x, -halfDim.y) + m_pos;
// 	glm::vec2 br = glm::vec2(halfDim.x, -halfDim.y) + m_pos;
// 	glm::vec2 tr = glm::vec2(halfDim.x, halfDim.y) + m_pos;
// 
// 	glm::vec2 positionOffset = m_pos;
// 
	glm::vec2 a_tl;
	glm::vec2 a_tr;
	glm::vec2 a_bl;
	glm::vec2 a_br;
// 	// Rotate the points
 	float tAgnle = (m_angle);
// 	a_tl = t_rotatePoint(tl, tAgnle)  ;
// 	a_bl = t_rotatePoint(bl, tAgnle);
// 	a_br = t_rotatePoint(br, tAgnle) ;
// 	a_tr = t_rotatePoint(tr, tAgnle) ;

	glm::vec4 desRect(m_pos - m_dim * 0.5f, m_dim);

	glm::vec2 halfDims(desRect.z / 2.0f, desRect.w / 2.0f);

	// Get points centered at origin
	glm::vec2 tl(-halfDims.x, halfDims.y);
	glm::vec2 bl(-halfDims.x, -halfDims.y);
	glm::vec2 br(halfDims.x, -halfDims.y);
	glm::vec2 tr(halfDims.x, halfDims.y);

	glm::vec2 positionOffset(desRect.x, desRect.y);

	// Rotate the points
	a_tl = t_rotatePoint(tl, tAgnle) + halfDims + positionOffset;
	a_bl = t_rotatePoint(bl, tAgnle) + halfDims + positionOffset;
	a_br = t_rotatePoint(br, tAgnle) + halfDims + positionOffset;
	a_tr = t_rotatePoint(tr, tAgnle) + halfDims + positionOffset;


	float maxX = getMax(a_tl.x, a_bl.x, a_br.x, a_tr.x);
	float minX = getMin(a_tl.x, a_bl.x, a_br.x, a_tr.x);
	float maxY = getMax(a_tl.y, a_bl.y, a_br.y, a_tr.y);
	float minY = getMin(a_tl.y, a_bl.y, a_br.y, a_tr.y);


	if (pos.x > minX && pos.x < maxX
		&& pos.y < maxY && pos.y > minY)
	{
		return true;
	}

	
// 	if (colliderDepth > 0)
// 	{
// 		
// 		return true;
// 	}


	return false;
}



void Gohei_Rod::update(const glm::vec2 &pos, float deltaTime, std::vector<EnemyBulletBase * > bullets)
{
	
	m_pos = pos;
// 	if (m_body)
// 	{
// 		m_body->SetTransform(b2Vec2(m_pos.x, m_pos.y), m_angle);
// 	}
	
	if (!m_isDone)
	{
		for (auto i = 0; i < bullets.size(); i++)
		{

			if (checkColliderWithEnemyBullet(*bullets[i]))
			{
				bullets[i]->setLifeTime(0.05f);
				bullets[i]->setDisabled(true);
				//bullets.erase(bullets.begin() + i);
	
			}


		}

		if (m_angle > m_maxAngle)
		{
			m_angle -= ROTATE_SPEED * deltaTime;
		}
		else
		{
			m_isDone = true;
			m_angle = 0.0f;
		}


		
	}
	m_afterImageParticle.update(m_pos,deltaTime, m_texture, m_angle, m_isDone);

}



void Gohei_Rod::drawDebug(Feintgine::DebugRender & renderer)
{

	glm::vec2 halfDim = m_dim * 0.5f;

	glm::vec2 tl = glm::vec2(-halfDim.x, halfDim.y) + m_pos ;
	glm::vec2 bl = glm::vec2(-halfDim.x, -halfDim.y) + m_pos;
	glm::vec2 br = glm::vec2(halfDim.x, -halfDim.y) + m_pos;
	glm::vec2 tr = glm::vec2(halfDim.x, halfDim.y) + m_pos;

	glm::vec2 positionOffset =m_pos;

	glm::vec2 a_tl;
	glm::vec2 a_tr;
	glm::vec2 a_bl;
	glm::vec2 a_br;
	// Rotate the points
	float tAgnle = (m_angle);
// 	a_tl = t_rotatePoint(tl, tAgnle) ;
// 	a_bl = t_rotatePoint(bl, tAgnle)  ;
// 	a_br = t_rotatePoint(br, tAgnle)  ;
// 	a_tr = t_rotatePoint(tr, tAgnle)  ;
	glm::vec4 desRect(m_pos - m_dim * 0.5f, m_dim );
	//renderer.drawBox(a_tl, a_tr, a_br, a_bl, Feintgine::Color(255, 0, 0, 255), tAgnle);
	//renderer.drawBox(tl, tr, br, bl, Feintgine::Color(255, 0, 0, 255), tAgnle);
	renderer.drawBox(desRect, Feintgine::Color(255, 0, 0, 255), tAgnle);
}

void Gohei_Rod::setMaxAngle(float angle)
{
	m_maxAngle = angle;
}

void Gohei_Rod::registerCamera(Feintgine::Camera2D * camera)
{
	m_camera = camera;
}

float Gohei_Rod::getMax(float a, float b, float c, float d)
{
	float arr[4];
	arr[0] = a;
	arr[1] = b;
	arr[2] = c;
	arr[3] = d;
	for (int i = 1; i < 4; ++i) {

		// Change < to > if you want to find the smallest element
		if (arr[0] < arr[i])
		{
			arr[0] = arr[i];
		}
			
	}
	return arr[0];

}

float Gohei_Rod::getMin(float a, float b, float c, float d)
{
	float arr[4];
	arr[0] = a;
	arr[1] = b;
	arr[2] = c;
	arr[3] = d;
	for (int i = 1; i < 4; ++i) {

		// Change < to > if you want to find the smallest element
		if (arr[0] > arr[i])
		{
			arr[0] = arr[i];
		}

	}
	return arr[0];
}

// void Gohei_Rod::initLogic(b2World * world)
// {
// 
// 	b2BodyDef bodyDef;
// 	bodyDef.type = b2_kinematicBody;
// 	bodyDef.position.Set(m_pos.x, m_pos.y);
// 	m_body = world->CreateBody(&bodyDef);
// 
// 
// 	b2PolygonShape goheiShape;
// 	goheiShape.SetAsBox(m_dim.x * 0.5f, m_dim.y * 0.5f);
// 	goheiShape.m_centroid.Set(m_dim.x * 0.5f, 0);
// 
// 	b2FixtureDef fixtureDef;
// 	fixtureDef.shape = &goheiShape;
// 	//fixtureDef.
// 	m_fixture = m_body->CreateFixture(&fixtureDef);
// 	m_body->SetUserData(this);
// 	
// 
// 	
// 
// }
