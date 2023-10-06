// #include "T_Scene.h"



// T_Scene::T_Scene()
// {

// }


// T_Scene::~T_Scene()
// {
// }


// void T_Scene::loadSceneFromFile(const std::string & filePath)
// {

// 	m_layers.clear();

// 	Scence s_scence;
// 	std::fstream input(filePath.c_str(), std::ios::in | std::ios::binary);
// 	if (!s_scence.ParseFromIstream(&input))
// 	{
// 		std::cout << "Failed to read scene :  " << filePath << "\n";
// 	}
// 	else
// 	{
// 		m_name = s_scence.name();
// 		m_layers.clear();
// 		for (int i = 0; i < s_scence.layers_size(); i++)
// 		{
// 			std::cout << " layer index " << i << "has " << s_scence.layers(i).objects_size() << "object \n";
// 			T_Layer re_layer;
// 			re_layer.load(s_scence.layers(i));
// 			m_layers.push_back(re_layer);
// 		}

// 	std::cout << "read scene ok \n";


// 	}
	
// }

// void T_Scene::createNew(const std::string &name)
// {
// 	m_name = name;

// 	std::cout << "create new scence " << m_name << "\n";
// // 	m_layers.clear();
// // 	m_currentLayer = nullptr;
// }

// void T_Scene::newLayer(const std::string & layerName, float depth)
// {
// 	T_Layer re_layer;
// 	re_layer.create(layerName, depth);
// 	m_layers.push_back(re_layer);
// }

// Scence T_Scene::getProtoSer()
// {
// 	Scence returnScene;

// 	returnScene.set_name(m_name);

// 	for (int i = 0; i < m_layers.size(); i++)
// 	{
// 		std::cout << "layer " << m_layers[i].getName() << " with " << m_layers[i].getObjects().size() << " object \n";
// 		Layer layer_temp = m_layers[i].getProtoSer();
// 		setLayer(layer_temp, *returnScene.add_layers());
// 	}
	

// 	return returnScene;

// }

// void T_Scene::drawScene(Feintgine::SpriteBatch & spriteBatch)
// {
// 	for (int i = 0; i < m_layers.size(); i++)
// 	{
// 		m_layers[i].drawObjects(spriteBatch);
// 	}
// }

// void T_Scene::findAndSetCurrentLayer(const std::string & layerName)
// {
// 	for (int i = 0; i < m_layers.size(); i++)
// 	{
// 		if (m_layers[i].getName() == layerName)
// 		{
// 			m_currentLayer = &m_layers[i];
// 			std::cout << "select layer " << m_layers[i].getName() << "\n";
// 			return;
// 		}
// 	}
// 	std::cout << "layer " << " can not be found \n";
// 	m_currentLayer = nullptr;
// }

// void T_Scene::addLayer(T_Layer newLayer)
// {
// 	m_layers.push_back(newLayer);
// }

// void T_Scene::saveScene(const std::string & savePath)
// {
	


// 	Scence p_scene ;

// 	//p_scene.set_name(m_name);
// 	//std::cout << "this scene has " << m_layers.size() << "layer \n";

// 	p_scene = getProtoSer();

// 	std::string destiny = savePath;
// 	std::string fileName = m_name;
// 	fileName += ".fsc";
// 	destiny += fileName;


// 	std::fstream output(destiny.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);

// 	if (!p_scene.SerializeToOstream(&output)) {
// 		std::cout << "Failed to write scene .\n";

// 	}
// 	else
// 	{
// 		std::cout << "Write scene OK \n";
// 	}
	
	

// }

// void T_Scene::setLayer(Layer &l1, Layer &l2)
// {
// 	l2 = l1;
// }

// void T_Scene::drawColiders(Feintgine::DebugRender & renderer)
// {
// 	for (int i = 0; i < m_layers.size(); i++)
// 	{
// 		m_layers[i].drawColider(renderer);
// 	}
// }

// int T_Scene::getLayerIndexFromName(const std::string & name)
// {
// 	for (int i = 0; i < m_layers.size(); i++)
// 	{
// 		if (m_layers[i].getName() == name)
// 		{
// 			return i;
// 		}
// 	}

// 	return -1;
// }

// void T_Scene::removeLayer(int index)
// {
// 	m_layers.erase(m_layers.begin() + index);
// }

// void T_Scene::updateScreenPriority()
// {
// 	for(int i = 0; i < m_layers.size(); i++)
// 	{
// 		m_layers[i].updatePriority();
// 	}
// }



