#include "block.h"
#include <iostream>


std::vector<Feintgine::Edge*> block::getNotFacingEdges(glm::vec2 point)
{
	std::vector<Feintgine::Edge*> notFacing;

	vector2f p = vector2f(point.x, point.y);

	for (int i = 0; i < 4; i++) {
		vector2f towards = p - getEdge(i)->getMiddle();
		float dot = getNormal(i) * towards;
		if (dot <= 0)
			notFacing.push_back(getEdge(i));
	}

	return notFacing;
}

void block::loadPhysic(b2World * world)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(m_pos.x, m_pos.y);

	m_body = world->CreateBody(&bodyDef);
	b2PolygonShape boxShape;
	boxShape.SetAsBox(m_dims.x / 2.0f, m_dims.y / 2.0f);

	b2FixtureDef fixDef;
	fixDef.shape = &boxShape;
	fixDef.restitution = 1.35f;
	fixDef.density = 1.0f / (m_dims.x * m_dims.y);
	fixDef.friction = 2.33f;
		
	m_fixture = m_body->CreateFixture(&fixDef);
	
	
}

void block::update()
{
	if (m_body != nullptr)
	{
		m_pos.x = m_body->GetPosition().x;
		m_pos.y = m_body->GetPosition().y;
	}



	const glm::vec4 uvrect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 destRect;
	destRect.x = m_pos.x - m_dims.x / 2;
	destRect.y = m_pos.y - m_dims.y / 2;
	destRect.z = m_dims.x;
	destRect.w = m_dims.y;

	glm::vec2 halfDims(destRect.z / 2.0f, destRect.w / 2.0f);

	// Get points centered at origin
	glm::vec2 tl(-halfDims.x, halfDims.y);
	glm::vec2 bl(-halfDims.x, -halfDims.y);
	glm::vec2 br(halfDims.x, -halfDims.y);
	glm::vec2 tr(halfDims.x, halfDims.y);

	// Rotate the points
	if (m_body != nullptr)
	{
		m_angle = m_body->GetAngle();
	}

	tl = rotatePoint(tl, m_angle) + halfDims;
	bl = rotatePoint(bl, m_angle) + halfDims;
	br = rotatePoint(br, m_angle) + halfDims;
	tr = rotatePoint(tr, m_angle) + halfDims;

	
	topLeft.setPosition(destRect.x + tl.x, destRect.y + tl.y);
	topLeft.setUV(0, 1);


	bottomLeft.setPosition(destRect.x + bl.x, destRect.y + bl.y);
	bottomLeft.setUV(0, 1);


	bottomRight.setPosition(destRect.x + br.x, destRect.y + br.y);
	bottomRight.setUV(0, 1);


	topRight.setPosition(destRect.x + tr.x, destRect.y + tr.y);
	topRight.setUV(0, 1);

	

	//topLeft.color = color;
// 	topLeft.setPosition(destRect.x, destRect.y + destRect.w);
// 	topLeft.setUV(0, 1);
// 
// 	
// 	bottomLeft.setPosition(destRect.x, destRect.y);
// 	bottomLeft.setUV(0, 1);
// 
// 	
// 	bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
// 	bottomRight.setUV(0, 1);
// 
// 	
// 	topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
// 	topRight.setUV(0, 1);

	m_verticies = new vector2f[4];
	normals = new vector2f[4];


	
		m_verticies[0] = vector2f(topLeft.position.x, topLeft.position.y);
		m_verticies[1] = vector2f(bottomLeft.position.x, bottomLeft.position.y);
		m_verticies[2] = vector2f(bottomRight.position.x, bottomRight.position.y);
		m_verticies[3] = vector2f(topRight.position.x, topRight.position.y);


	updateNormals();
	updateClockwise();
	updateEdges();


	//std::cout << m_body->GetAngle() << "\n";

	
}

void block::setRotation(float angle)
{
	//m_body->SetAngularVelocity(angle);
}

void block::resetVerticies()
{

}

void block::updateClockwise()
{
	double sum = 0;
	for (int i = 0; i < 3 - 1; i++) {
		sum += (getVertex(i + 1).x - getVertex(i).x) * (getVertex(i + 1).y + getVertex(i).y);
	}
	clockwise = sum > 0;
}

void block::updateNormals()
{
	for (int i = 0; i < 4; i++) {
		vector2f diff = getVertex(i) - getVertex(i + 1);
		float temp = diff.x;
		diff.x = diff.y;
		diff.y = -temp;
	
			diff *= -1;
		
			normals[i] = diff.normalized();
		
		
	}
}

void block::updateEdges()
{
	for (int i = 0; i < 4; i++) {
		edges[i] = new Feintgine::Edge(getVertex(i), getVertex(i + 1));
	}
}



glm::vec2 block::rotatePoint(const glm::vec2& pos, float angle)
{
	glm::vec2 newv;
	newv.x = pos.x * cos(angle) - pos.y * sin(angle);
	newv.y = pos.x * sin(angle) + pos.y * cos(angle);
	return newv;
}

b2Vec2 block::summonDirection(glm::vec2 centerPos)
{
	b2Vec2 dir;
	dir.x = (centerPos.x - m_pos.x) * 0.72f ;
	dir.y = (centerPos.y - m_pos.y) * 0.72f;

	return dir;
}

b2Vec2 block::explod(glm::vec2 centerPos)
{
	b2Vec2 dir;
	dir.x = (centerPos.x - m_pos.x) * 2.72f;
	dir.y = (centerPos.y - m_pos.y) * 2.72f;
	dir.x = -dir.x;
	dir.y = -dir.y;

	return dir;
}
