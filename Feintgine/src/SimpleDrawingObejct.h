
// #ifndef _SIMPLEDRAWINGOBJECT_H_
// #define _SIMPLEDRAWINGOBJECT_H_

// #include "SpriteBatch.h"
// #include "GLTexture.h"
// #include <iostream>
// #include <fstream>
// //#include "f_object.pb.h"
// #include "ObjectColider.h"
// #include <vector>
// #include "DebugRender.h"
// #include "ResourceManager.h"
// class SimpleDrawingObject
// {
// public:
// 	SimpleDrawingObject();
// 	~SimpleDrawingObject();

// 	void init(const std::string &fobPath);

// 	void draw(Feintgine::SpriteBatch & spriteBatch);
	
// 	std::string getPrefabFilePath() const { 
// 		return prefabPath; }

// 	void addColider(glm::vec2 c_pos, glm::vec2 c_dim);

// 	void drawColiders(Feintgine::DebugRender & renderer);

// 	void setPos(glm::vec2 pos);

// 	void setDim(glm::vec2 dim);

// 	void setDepth(float depth);

// 	float getDepth() const { return m_depth; }

// 	void setColor(Feintgine::Color color);

// 	int getType() const { return m_type; }

// 	std::vector<ObjectColider> getCols() { return m_coliders; }

// 	glm::vec2 getPos() const { return m_pos; }
// 	glm::vec2 getDim() const { return m_dims; }

// 	std::string getName() const { return m_name; }

// 	glm::vec2 getActualDim() const { return actual_dim; }
	
// protected:
// 	glm::vec2 m_pos;
// 	glm::vec2 m_dims;
// 	glm::vec4 m_uv;
// 	Feintgine::GLTexture m_texture;

// 	float m_depth = 1;
	
// 	float m_angle = 0;

// 	float m_spec = 1;

// 	int m_type;

// 	std::string m_name;

// 	std::string m_texturePath;

// 	Feintgine::Color m_color;

// 	std::string prefabPath;

// 	std::vector<ObjectColider> m_coliders;
	
// 	glm::vec2 actual_dim;
// };

// #endif
