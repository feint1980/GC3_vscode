#include "Fg_scene.h"



namespace Feintgine
{


	Fg_scene::Fg_scene()
	{
		deselectCurrentLayer();
	}


	Fg_scene::~Fg_scene()
	{
	}

	void Fg_scene::loadSceneFromFile(const std::string & filePath, CEGUI::MultiColumnList * list)
	{
		
		if (m_currentLayer)
		{
			m_currentLayer->getObjects().clear();
			deselectCurrentLayer();
		}
		if (list)
		{
			for (int i = 0; i < list->getRowCount(); i++)
			{
				list->removeRow(i);
			}
		}
		for(int i = 0; i < m_layers.size(); i++)
		{
			m_layers[i]->getObjects().clear();
			m_layers.erase(m_layers.begin() + i);
		}

		m_layers.clear();

		std::cout << "start loading scene \n";

		Proc_Scene s_scence;
		std::fstream input(filePath.c_str(), std::ios::in | std::ios::binary);
		if (!s_scence.ParseFromIstream(&input))
		{
			std::cout << "Failed to read scene :  " << filePath << "\n";
			return;
		}
		else
		{
			m_name = s_scence.name();
			m_layers.clear();
			for (int i = 0; i < s_scence.layerlist_size(); i++)
			{
				std::cout << " layer index " << i << "has " << s_scence.layerlist(i).objectlist_size()  << "object \n";
				Fg_layer * re_layer = new Fg_layer();
				
				re_layer->load(s_scence.layerlist(i));

				int i_layerDepth = re_layer->getDepth();
				CEGUI::ListboxTextItem * firstRowItem1 = new CEGUI::ListboxTextItem(re_layer->getName());
				CEGUI::ListboxTextItem * firstRowItem2 = new CEGUI::ListboxTextItem(std::to_string(i_layerDepth).c_str());
				CEGUI::ListboxTextItem * firstRowItem3 = new CEGUI::ListboxTextItem("v");


				firstRowItem1->setSelectionBrushImage("TaharezLook/ListboxSelectionBrush");
				firstRowItem2->setSelectionBrushImage("TaharezLook/ListboxSelectionBrush");
				firstRowItem3->setSelectionBrushImage("TaharezLook/ListboxSelectionBrush");


				if (list)
				{
					
					CEGUI::uint firstRow = list->addRow(firstRowItem1, 1);
					list->setItem(firstRowItem2, 2, firstRow);
					list->setItem(firstRowItem3, 3, firstRow);
					re_layer->setGUIText(firstRowItem3);
				
				}

				
				m_layers.push_back(std::move(re_layer));
				
			}
			std::cout << "total layer " << m_layers.size() << "\n";
			std::cout << "read scene ok \n";


		}
	}

	void Fg_scene::createNew(const std::string &name)
	{
		m_name = name;

		std::cout << "create new scence " << m_name << "\n";
		m_layers.clear();
		m_currentLayer = nullptr;
	}

	void Fg_scene::newLayer(const std::string & layerName, float depth)
	{
		m_currentLayer = nullptr;
		Fg_layer *re_layer = new Fg_layer();
		re_layer->create(layerName, depth);
		m_layers.push_back(std::move(re_layer));
	}

	Proc_Scene * Fg_scene::getProtoSer()
	{
		Proc_Scene * returnScene = new Proc_Scene();

		returnScene->set_name(m_name);

		for (int i = 0; i < m_layers.size(); i++)
		{
			std::cout << "layer " << m_layers[i]->getName() << " with " << m_layers[i]->getObjects().size() << " object \n";
			Proc_Layer  * layer = m_layers[i]->getProtoSer();
			returnScene->add_layerlist()->CopyFrom(*layer);
			//setLayer(layer, returnScene->add_layerlist());
		}


		return returnScene;
	}

	void Fg_scene::drawScene(Feintgine::SpriteBatch & spriteBatch)
	{
		for (int i = 0; i < m_layers.size(); i++)
		{
			m_layers[i]->draw(spriteBatch);
		}
	}

	void Fg_scene::drawLight(Feintgine::LightBatch & lightBatch)
	{
		for (int i = 0; i < m_layers.size(); i++)
		{
			m_layers[i]->drawLight(lightBatch);
		}
	}

	void Fg_scene::removeCurrentLayer()
	{
		if (m_currentLayer)
		{
			for (int i = 0; i < m_layers.size(); i++)
			{

				if (m_layers[i] == m_currentLayer)
				{
					m_layers[i]->clearObject();
					m_layers.erase(m_layers.begin() + i);
					deselectCurrentLayer();
				}
			}
		}
		
	}

	void Fg_scene::removeLayerByName(const std::string & name)
	{
		std::cout << "remove layer with name " << name << "\n";
		std::cout << "size " << m_layers.size() << "\n";
		for (int i = 0; i < m_layers.size(); i++)
		{
			std::cout << "compare " + m_layers[i]->getName() + " with " + m_currentLayer->getName() << "\n";
			if (m_layers[i]->getName() == name)
			{
				m_layers[i]->clearObject();
				m_layers.erase(m_layers.begin() + i);
				std::cout << "hit \n";
				deselectCurrentLayer();
			}
		}
	}

	void Fg_scene::deselectCurrentLayer()
	{
		if (m_currentLayer)
		{
			m_currentLayer = nullptr;
		}
	}

	void Fg_scene::drawBox(Feintgine::DebugRender & debugRenderer)
	{
		if (m_currentLayer)
		{
			m_currentLayer->drawBox(debugRenderer);
		}
	}

	void Fg_scene::editorUpdate(const glm::vec2 & mousePos)
	{
		
		if (m_currentLayer)
		{
			//std::cout << "got \n";
			m_currentLayer->editorUpdate(mousePos);
			
		}
	}

	void Fg_scene::findAndSetCurrentLayer(const std::string & layerName)
	{
		for (int i = 0; i < m_layers.size(); i++)
		{
			if(m_layers[i])
			{
				std::cout << "find name " << m_layers[i]->getName() << " with name " << layerName << "\n";
				if (m_layers[i]->getName() == layerName)
				{
					std::cout << "hit \n";
					m_currentLayer = m_layers[i];
					return;
				}
			}
		}
		std::cout << "layer " << layerName << " can not be found \n";
		deselectCurrentLayer();
	}

	void Fg_scene::addLayer(Fg_layer * newLayer)
	{
		deselectCurrentLayer();
		Fg_layer * layer = newLayer;
		m_layers.push_back(layer);
	}

	void Fg_scene::saveScene(const std::string & savePath)
	{
		Proc_Scene * p_scene = new Proc_Scene();

		//p_scene.set_name(m_name);
		//std::cout << "this scene has " << m_layers.size() << "layer \n";

		p_scene = getProtoSer(); 
		std::cout << "savePath is " << savePath << "\n";

		std::string destiny = savePath;
		std::string fileName = m_name;
		fileName += ".fsc";
		destiny += fileName;


		std::fstream output(destiny.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
		//std::fstream output(destiny.c_str(), std::ios::out | std::ios::trunc);
		//p_scene.Serial
		if (!p_scene->SerializeToOstream(&output)) {
			std::cout << "Failed to write scene " << m_name << " to " << destiny.c_str() << "  .\n";

		}
		else
		{

			for(int i = 0; i < p_scene->layerlist_size(); i++)
			{
				std::cout << "write layer " << p_scene->layerlist(i).name() << "\n";
				for(int j = 0; j < p_scene->layerlist(i).objectlist_size(); j++)
				{
					//std::cout << "write object " << p_scene.layerlist(i).objectlist(j).k
				}
			}

			std::cout << "Write scene OK \n";
		}
		

	}

	void Fg_scene::setLayer(Proc_Layer * l1, Proc_Layer * l2)
	{
		l2 = l1;
	}

}
