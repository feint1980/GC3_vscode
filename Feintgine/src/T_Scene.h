
// #ifndef _T_SCENE_H_
// #define _T_SCENE_H_

// #include "T_Layer.h"
// #include <vector>
// #include <string>
// //#include "f_object.pb.h"
// #include <iostream>
// #include <fcntl.h>
// #include <fstream>
// #include <google/protobuf/text_format.h>
// #include <google/protobuf/io/zero_copy_stream_impl.h>
// #include <google/protobuf/io/coded_stream.h>


// class T_Scene
// {
// public:
// 	T_Scene();
// 	~T_Scene();

// 	void loadSceneFromFile(const std::string & filePath);

// 	void createNew(const std::string &name);

// 	void newLayer(const std::string & layerName, float depth);

// 	std::vector<T_Layer> getLayers() const { return m_layers; }

// 	T_Layer * getCurrentLayer() const { return m_currentLayer; }

// 	Scence getProtoSer();

// 	void drawScene(Feintgine::SpriteBatch & spriteBatch);

// 	void findAndSetCurrentLayer(const std::string & layerName);

// 	void addLayer(T_Layer newLayer);

// 	void saveScene(const std::string & savePath);

// 	void setLayer(Layer &l1, Layer &l2);

// 	void drawColiders(Feintgine::DebugRender & renderer);

// 	int getLayerIndexFromName(const std::string & name);
	
// 	void removeLayer(int index);

// 	void updateScreenPriority();

// 	std::string getName() const { return m_name; }

// private:
// 	std::vector<T_Layer> m_layers;

// 	std::string m_name;

// 	T_Layer * m_currentLayer = nullptr;
// };

// #endif