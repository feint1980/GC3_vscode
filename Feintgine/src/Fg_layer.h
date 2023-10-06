#ifndef _FG_LAYER_H
#define _FG_LAYER_H


#include "objectData.pb.h"
#include "LightBatch.h"
#include "F_Object.h"
#include "Brush.h"

namespace Feintgine
{
	class Fg_layer
	{
	public:
		Fg_layer();
		~Fg_layer();

		void load(Proc_Layer c_layer);

		float changeDepthToCurrentLayer(const F_Object & object);

		void addObjectToLayer(const F_Object & object);

		void draw(Feintgine::SpriteBatch & spriteBatch);

		void clearAllSelectedObject();

		void drawLight(Feintgine::LightBatch & lightBatch);

		Proc_Layer getProtoSer();

		void setObject(Proc_LoadObject & o1, Proc_LoadObject &o2);

		void setBrush(Proc_Brush & o1, Proc_Brush &o2);

		void setName(const std::string & name);

		void create(const std::string  & name, int depth);

		void clearObject();

		std::string getName() const { return m_name; }

		int getDepth() const { return m_depth; }

		std::vector<Feintgine::F_Object> getObjects() const { return m_objects; }

		void editorUpdate(const glm::vec2 & mousePos);

		void drawBox(Feintgine::DebugRender & debugRenderer);

		void addBrush(const Feintgine::Brush & brush);

		void updateDepth();

		void handleSelectObject();
		void handleDeselectObject();
		void removeSelectedObjects();

		void moveSelectedObject(const glm::vec2 & offset,bool first);

		void clearObjectOffset();
		
		void update(float deltaTime);
	private:
		int m_depth;
		bool startMoving = false;
			
		std::string m_name;
		std::vector<Feintgine::F_Object> m_objects;

		std::vector<Feintgine::Brush> m_brushes;

		glm::vec2 anchorPos;
	};
}

#endif
