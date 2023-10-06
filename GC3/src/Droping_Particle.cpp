// #include "Droping_Particle.h"

// const float reset_x = -0.0f;
// const float reset_x_1 = -15.0f;
// const float reset_x_2 = -30.0f;
// const float reset_x_3 = -45.0f;
// const float reset_x_4 = -60.0f;

// const float reset_x_5 = 15.0f;
// const float reset_x_6 = 30.0f;
// const float reset_x_7 = 45.0f;
// const float reset_x_8 = 60.0f;

// const float reset_y = 46.3f;

// Droping_Particle::Droping_Particle()
// {
// 	srand(time(NULL));
// }


// Droping_Particle::~Droping_Particle()
// {
// }

// void Droping_Particle::update(Feintgine::Camera2D & camera, bool isOn)
// {


// 	if (m_body != nullptr)
// 	{
// 		m_pos.x = m_body->GetPosition().x;
// 		m_pos.y = m_body->GetPosition().y;
// 		m_angle = m_body->GetAngle();
// 	}
// 	if (count >= 100)
// 	{
// 		int f = rand() % 40 - 20;

// 		int o;
// 		if (!forced)
// 		{
// 			o = rand() % 10 - 5;
// 		}
// 		else
// 		{
// 			o = 0;
// 		}
	


// 		m_body->ApplyForce(b2Vec2((float)f, o/ 0.35f), m_body->GetWorldCenter(), false);
		
// 		count = 0;

		
// 	}

// 	count++;

// 	if (!camera.isInPortView(m_pos, m_dims))
// 	{
// 		if (!isOn)
// 		{
// 			autoPos();
// 		}
// 	}

	
// }

// void Droping_Particle::destroy()
// {
// 	is_destroy = true;
// }

// void Droping_Particle::setFreeFall()
// {


// // 	int x = rand() % 14 -7;
// // 	int y = rand() % 14 - 7;
// // 	m_vel = glm::vec2(x*0.04f, y*0.04f);

// }


// void Droping_Particle::autoPos()
// {
// 	m_body->SetLinearVelocity(b2Vec2(0, 0));
// 	count = 90;
// 	forced = false;


// 	int dec = rand() % 130-65;
	
// 	//float newY = reset_y;
	
// 	resetPos(glm::vec2(dec, reset_y));
// }

// void Droping_Particle::firstPos()
// {



// 	//m_body->SetTransform(b2Vec2((float)a, float(b)), m_body->GetAngle());
// }

// void Droping_Particle::resetPos(const glm::vec2 & pos)
// {
// 	m_body->SetTransform(b2Vec2(pos.x, pos.y), m_body->GetAngle());
// }

// void Droping_Particle::loadPhysic(b2World * world)
// {

// 	b2BodyDef bodyDef;
// 	bodyDef.type = b2_dynamicBody;
// 	bodyDef.position.Set(m_pos.x, m_pos.y);

// 	m_body = world->CreateBody(&bodyDef);
// 	//b2CircleShape circleShape;
// 	//circleShape.m_radius = m_dims.x / 2.0f;
// 	b2PolygonShape boxShape;
// 	boxShape.SetAsBox(m_dims.x / 2.0f, m_dims.y / 2.0f);

	

// 	b2FixtureDef fixDef;
// 	fixDef.shape = &boxShape;
// 	fixDef.restitution = 1.35f;
// 	fixDef.density = 0.1f / (m_dims.x * m_dims.y);
// 	fixDef.friction = 0.33f;


// 	fixDef.filter.groupIndex = -1;
// 	m_fixture = m_body->CreateFixture(&fixDef);
// 	int f = rand() % 4 + 1;
// 	m_body->SetAngularVelocity(f * 0.25f);
	
// }

