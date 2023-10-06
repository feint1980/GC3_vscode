
#ifndef _FG_SCENE_H
#define _FG_SCENE_H


#include "objectData.pb.h"
#include <string>
#include <vector>
#include "Fg_layer.h"
#include "GUI.h"


namespace Feintgine 
{


	class Fg_scene
	{
	public:
		Fg_scene();
		~Fg_scene();


		void loadSceneFromFile(const std::string & filePath, CEGUI::MultiColumnList * list);



		void createNew(const std::string &name);

		void newLayer(const std::string & layerName, float depth);

		std::vector<Fg_layer> getLayers() const { return m_layers; }

		Fg_layer * getCurrentLayer() const { return m_currentLayer; }

		Proc_Scene getProtoSer();

		void drawScene(Feintgine::SpriteBatch & spriteBatch);
		void drawLight(Feintgine::LightBatch & lightBatch);

		void removeCurrentLayer();
		
		void removeLayerByName(const std::string & name);

		void deselectCurrentLayer();

		void drawBox(Feintgine::DebugRender & debugRenderer);

		void editorUpdate(const glm::vec2 & mousePos);

 		void findAndSetCurrentLayer(const std::string & layerName);
// 
 		void addLayer(const Fg_layer & newLayer);
// 
 		void saveScene(const std::string & savePath);
// 
 		void setLayer(Proc_Layer &l1, Proc_Layer &l2);
// 
// 		void drawColiders(Feintgine::DebugRender & renderer);
// 
// 		int getLayerIndexFromName(const std::string & name);
// 
// 		void removeLayer(int index);
// 
// 		void updateScreenPriority();

		std::string getName() const { return m_name; }
		
	private:
		std::vector<Fg_layer> m_layers;

		std::string m_name;

		Fg_layer * m_currentLayer = nullptr;
	};

}

#endif

