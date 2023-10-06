// #include "T_Layer.h"



// T_Layer::T_Layer()
// {
// }


// T_Layer::~T_Layer()
// {
// }



// void T_Layer::load(Layer c_layer)
// {
// 	m_name = c_layer.name();
// 	m_depth = c_layer.depth();
// 	//m_objects.clear();
// 	std::cout << "layer " << m_name << " has " << c_layer.objects_size() << "objects \n";
// 	for (int i = 0; i < c_layer.objects_size(); i++)
// 	{
// 		B_Object fob;
// 		//fob.init(c_layer.objects(i).prefab());
// 		glm::vec2 t_pos;
// 		t_pos.x = c_layer.objects(i).x_pos();
// 		t_pos.y = c_layer.objects(i).y_pos();
// 		glm::vec2 t_scale;
// 		t_scale.x = c_layer.objects(i).x_scale();
// 		t_scale.y = c_layer.objects(i).y_scale();

// // 		fob.setPos(t_pos);
// // 		fob.reScale(t_scale);

// 		fob.create(c_layer.objects(i).prefab(), t_pos, t_scale, 0, m_depth);

// 		m_objects.push_back(fob);

// 	}

// }

// void T_Layer::create(const std::string & name, float depth)
// {
// 	m_name = name; 
// 	m_depth = depth;
// }

// void T_Layer::drawObjects(Feintgine::SpriteBatch & spriteBatch)
// {
// 	if (!m_hidden)
// 	{
// 		for (int i = 0; i < m_objects.size(); i++)
// 		{
// 			m_objects[i].draw(spriteBatch);
// 		}
// 	}
// }

// void T_Layer::drawColider(Feintgine::DebugRender & renderer)
// {
// 	if (!m_hidden)
// 	{
// 		for (int i = 0; i < m_objects.size(); i++)
// 		{
// 			m_objects[i].drawColiders(renderer);
// 		}
// 	}


// }

// void T_Layer::addObject(const std::string & prefab, glm::vec2 pos)
// {
// 	B_Object fob;

// 	fob.create(prefab, pos, glm::vec2(1),0, m_depth);

// 	m_objects.push_back(fob);
// }

// Layer T_Layer::getProtoSer()
// {
// 	Layer layer;
// 	layer.set_name(m_name);
// 	layer.set_depth(m_depth);

// 	for (int i = 0; i < m_objects.size(); i++)
// 	{
// 		Sprite spt = m_objects[i].getProtoSer();
// 		setSprite(spt, *layer.add_objects());

// 	}


// 	std::cout << "write layer " << layer.name() << " with " << layer.objects_size() << "object(s) \n";

// 	return layer;

// }

// void T_Layer::setSprite(Sprite &s1, Sprite &s2)
// {
// 	s2 = s1;
// }

// void T_Layer::update(const glm::vec2 & mousePos)
// {
// 	for (int i = 0; i < m_objects.size(); i++)
// 	{
// 		m_objects[i].checkInside(mousePos);
// 	}

// }

// void T_Layer::handle()
// {
// 	for (int i = 0; i < m_objects.size(); i++)
// 	{
// 		if (m_objects[i].isDestroyed())
// 		{
// 			m_objects.erase(m_objects.begin() + i);
// 		}

// 	}
// }

// void T_Layer::drawDebug(Feintgine::DebugRender & renderer)
// {
// 	if (!m_hidden)
// 	{
// 		for (int i = 0; i < m_objects.size(); i++)
// 		{
// 			m_objects[i].drawRect(renderer);
// 		}
// 	}

// }



// void T_Layer::deselectObjects()
// {
// 	for (int i = 0; i < m_objects.size(); i++)
// 	{
// 		if (m_objects[i].isSelect())
// 		{
// 			m_objects[i].setSelect(false);
// 		}
// 	}
// }

// void T_Layer::selectObjects(bool holdCTRL)
// {
// 	//std::cout << "hovers object :" << getHoveredObject().size() << "\n";
// 	int countCall = 0;

// 	for (int i = 0; i <m_objects.size(); i++)
// 	{
// 		if (m_objects[i].isHover())
// 		{
// 			countCall++;
// 			if (!m_objects[i].isSelect())
// 			{
// 				m_objects[i].setSelect(true); 
// 			}
// 			else if (holdCTRL)
// 			{
// 				m_objects[i].setSelect(false);

// 			}
// 		}	
// 	} 
// 	if (countCall < 1)
// 	{
// 		for (int i = 0; i < m_objects.size(); i++)
// 		{
// 			m_objects[i].setSelect(false);
// 		}
// 	}

// }

// void T_Layer::calculateObjectsOffset(const glm::vec2 pos)
// {
// 	for (int i = 0; i < m_objects.size(); i++)
// 	{
// 		if (m_objects[i].isSelect())
// 		{
// 			m_objects[i].calculateOffset(pos);
// 		}
// 	}
// }

// void T_Layer::moveSelectedObject(const glm::vec2 & newPos)
// {
// 	for (int i = 0; i < m_objects.size(); i++)
// 	{
// 		if (m_objects[i].isSelect())
// 		{
// 			m_objects[i].drag(newPos);
// 		}
// 	}
// }

// void T_Layer::setHide(bool val)
// {
// 	m_hidden = val;
// }

// B_Object * T_Layer::getObjectOnGrid(glm::vec2 &pos)
// {
// 	for (int i = 0; i < m_objects.size(); i++)
// 	{
// 		if (m_objects[i].getPos() == pos)
// 		{
// 			return &m_objects[i];
// 		}
// 	}
// 	return nullptr;
// }

// int T_Layer::getObjectOnGridIndex(glm::vec2 &pos)
// {
// 	for (int i = 0; i < m_objects.size(); i++)
// 	{
// 		if (m_objects[i].getPos() == pos)
// 		{
// 			return i;
// 		}
// 	}

// 	return -1;
// }

// void T_Layer::deleteObjectFromIndex(int index)
// {
// 	m_objects.erase(m_objects.begin() + index);
// }

// void T_Layer::deleteSelected()
// {
// 	for (int i = 0; i < m_objects.size(); i++)
// 	{
// 		if (m_objects[i].isSelect())
// 		{
// 			m_objects.erase(m_objects.begin() + i);
// 		}
// 	}
// }

// void T_Layer::updatePriority()
// {
// 	for (int i = 0; i < m_objects.size(); i++)
// 	{
// 		m_objects[i].calculatePriority();
// 	}	
// }
