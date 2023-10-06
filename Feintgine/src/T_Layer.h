
// #ifndef _T_LAYER_H_
// #define _T_LAYER_H_

// //#include "B_Object.h"
// #include <vector>
// #include "SpriteBatch.h"
// //#include "f_object.pb.h"


// class T_Layer
// {
// public:
// 	T_Layer();
// 	~T_Layer();

// 	void load(Layer c_layer);

// 	void create(const std::string & name, float depth);

// 	void drawObjects(Feintgine::SpriteBatch & spriteBatch);

// 	void drawColider(Feintgine::DebugRender & renderer);

// 	void addObject(const std::string & prefab, glm::vec2 pos);

// 	float getDepth() const { return m_depth; }

// 	Layer getProtoSer();

// 	void setSprite(Sprite &s1, Sprite &s2);

// 	void update(const glm::vec2 & mousePos);

// 	void handle();

// 	void drawDebug(Feintgine::DebugRender & renderer);

// 	std::string getName() const { return m_name; }

// 	std::vector<B_Object> getObjects() { return m_objects; }

// 	void deselectObjects();

// 	void selectObjects(bool holdCTRL);

// 	bool isHidden() const { return m_hidden; }

// 	void calculateObjectsOffset(const glm::vec2 pos);

// 	void moveSelectedObject(const glm::vec2 & newPos);

// 	void setHide(bool val);

// 	B_Object *getObjectOnGrid(glm::vec2 &pos);

// 	int getObjectOnGridIndex(glm::vec2 &pos);

// 	void deleteObjectFromIndex(int index);

// 	void deleteSelected();
	
// 	void updatePriority();



// private:

// 	std::string m_name;
// 	float m_depth;
// 	std::vector<B_Object> m_objects;

// 	bool m_hidden = false;


// };

// #endif