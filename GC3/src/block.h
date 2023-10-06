#pragma once
#include "EmptyObject.h"
#include <Box2D/Box2D.h>

class block : public EmptyObject
{
public:
	block(){}
	~block(){};


	Feintgine::Vertex topLeft;
	Feintgine::Vertex bottomLeft;
	Feintgine::Vertex topRight;
	Feintgine::Vertex bottomRight;




	vector2f getVertex(int i) { return m_verticies[i % 4]; }

	vector2f *getVerticies() { return m_verticies; }

	//std::vector<Feintgine::Edge*> getFacingEdges(vector2f);
	std::vector<Feintgine::Edge*> getNotFacingEdges(glm::vec2 point);

	//This should be the only way that you modify verticies (bypassing this method will screw things up)


	vector2f* getNormals() { return normals; }
	vector2f getNormal(int i) { return normals[i % 4]; }

	Feintgine::Edge** getEdges() { return edges; }
	Feintgine::Edge* getEdge(int i) { return edges[i % 4]; }

	bool isClockwise() { return clockwise; }

	void setShadow(bool value);

	void loadPhysic(b2World *world);


	void update();

	void setRotation(float angle);

	void resetVerticies();
	//Update everything
	void updateAll();
	//Update the clockwise variable
	void updateClockwise();
	//Update the normal vectors
	void updateNormals();
	//Update the edges
	void updateEdges();


	b2Body * getBody() const { return m_body; }

	b2Vec2 summonDirection(glm::vec2 centerPos);
	b2Vec2 explod(glm::vec2 centerPos);

	private:

		float normal_math_a = -1;

		vector2f *m_verticies;
		bool clockwise;
		vector2f *normals;
		Feintgine::Edge *edges[4];
		glm::vec2 rotatePoint(const glm::vec2& pos, float angle);

		b2Fixture * m_fixture = nullptr;
		b2Body *m_body = nullptr;
};



