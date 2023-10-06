#include "Fg_layer.h"

namespace Feintgine
{

	Fg_layer::Fg_layer()
	{
	}


	Fg_layer::~Fg_layer()
	{

	}

	void Fg_layer::load(Proc_Layer c_layer)
	{
		m_name = c_layer.name();
		m_depth = c_layer.depth();
		m_brushes.clear();
		m_objects.clear();
		std::cout << "layer " << m_name << " has " << c_layer.objectlist_size() << "objects \n";
		for (int i = 0; i < c_layer.objectlist_size(); i++)
		{
			F_Object fob;
			//fob.init(c_layer.objects(i).prefab());
		
			glm::vec2 t_pos = feint_common::Instance()->convertProcVec2ToVec2(c_layer.objectlist(i).pos());
			glm::vec2 t_scale = feint_common::Instance()->convertProcVec2ToVec2(c_layer.objectlist(i).scale());
			
			std::cout << "DEBUG the pos is ### " << feint_common::Instance()->convertVec2toString(t_pos) << "\n";
			//fob.


			fob.create(c_layer.objectlist(i).refab() , t_pos, t_scale, 0, m_depth);

			m_objects.push_back(fob);

		}
		std::cout << "layer " << m_name << " has " << c_layer.brushlist_size() << "brush \n";
		for (int i = 0; i < c_layer.brushlist_size(); i++)
		{
			Feintgine::Brush brush;

			brush.loadFromProto(c_layer.brushlist(i));
			m_brushes.push_back(brush);
		}
		std::cout << "layer " << m_name << " has " << m_brushes.size() << "brush \n";
	}

	float Fg_layer::changeDepthToCurrentLayer(const F_Object & object)
	{

		return object.getDepth() * 0.001;

	}

	void Fg_layer::addObjectToLayer(const F_Object & object)
	{
		 
		 F_Object t_object = object;
		 t_object.setDepth(m_depth + changeDepthToCurrentLayer(object));
		 m_objects.push_back(t_object);
		 updateDepth();

		
	}

	void Fg_layer::draw(Feintgine::SpriteBatch & spriteBatch)
	{
		for (int i = 0; i < m_objects.size(); ++i)
		{
			m_objects[i].draw(spriteBatch);
		}
		for (int i = 0; i < m_brushes.size(); ++i)
		{
			m_brushes[i].draw(spriteBatch);
		}
	}

	void Fg_layer::clearAllSelectedObject()
	{
		for (int i = 0; i < m_objects.size(); ++i)
		{
			if (m_objects[i].isSelected())
			{
				m_objects[i].setSelected(false);
			}
		}
	}

	void Fg_layer::drawLight(Feintgine::LightBatch & lightBatch)
	{
		for (int i = 0; i < m_objects.size(); ++i)
		{
			m_objects[i].drawLight(lightBatch);
		}
	}

	Proc_Layer Fg_layer::getProtoSer()
	{
		Proc_Layer m_proclayer;

		m_proclayer.set_name(m_name);
		m_proclayer.set_depth(m_depth);
		for (int i = 0; i < m_objects.size(); i++)
		{
			Proc_LoadObject loadObject1 = m_objects[i].getProtoSer();
			Proc_LoadObject loadObject2 = Proc_LoadObject(*m_proclayer.add_objectlist());
			setObject(loadObject1, loadObject2);
		}
		std::cout << "write layer " << m_proclayer.name() << " with " << m_proclayer.objectlist_size() << "object(s) \n";
		for (int i = 0; i < m_brushes.size(); i++)
		{
			Proc_Brush brush1 = m_brushes[i].getProtoSer();
			Proc_Brush brush2 = Proc_Brush(*m_proclayer.add_brushlist());
			setBrush(brush1, brush2);
		}
		std::cout << "write layer " << m_proclayer.name() << " with " << m_proclayer.brushlist_size() << "brush(s) \n";

		return m_proclayer;
	}

	void Fg_layer::setObject(Proc_LoadObject & o1, Proc_LoadObject &o2)
	{
		o2 = o1;
	}

	void Fg_layer::setBrush(Proc_Brush & o1, Proc_Brush &o2)
	{
		o2 = o1;
	}

	void Fg_layer::setName(const std::string & name)
	{
		m_name = name;
	}

	void Fg_layer::create(const std::string & name, int depth)
	{
		m_name = name;
		m_depth = depth;

	}

	void Fg_layer::clearObject()
	{
		std::cout << "called clear \n";
		m_objects.clear();
		m_brushes.clear();
	}

	void Fg_layer::editorUpdate(const glm::vec2 & mousePos)
	{
		for (int i = 0; i < m_objects.size(); i++)
		{
			m_objects[i].setHover(m_objects[i].isMouseInside(mousePos));

		}
	}

	void Fg_layer::drawBox(Feintgine::DebugRender & debugRenderer)
	{
		for (int i = 0; i < m_objects.size(); i++)
		{
			m_objects[i].showHoverBox(debugRenderer);
		}
	}

	void Fg_layer::addBrush(const Feintgine::Brush & brush)
	{
		//Feintgine::Brush t_brush = brush;
		//float totalDepth = m_depth + (brush.getDepth() * 0.001f);
		//t_brush.setDepth(totalDepth);
		m_brushes.push_back(brush);
	}

	void Fg_layer::updateDepth()
	{
		for (int i = 0; i < m_objects.size(); i++)
		{
			m_objects[i].calculatePriority();
		}
	}

	void Fg_layer::handleSelectObject()
	{
		for (int i = 0; i < m_objects.size(); i++)
		{
			if (m_objects[i].isHover())
			{
				m_objects[i].setSelected(true);
			}
		}
	}

	void Fg_layer::handleDeselectObject()
	{
		for (int i = 0; i < m_objects.size(); i++)
		{
			if (m_objects[i].isHover() && m_objects[i].isSelected())
			{
				m_objects[i].setSelected(false);
			}
		}
	}

	void Fg_layer::removeSelectedObjects()
	{
		for (int i = m_objects.size() -1; i >= 0; i--)
		{
			if (m_objects[i].isSelected())
			{
				m_objects.erase(m_objects.begin() + i);
			}
		}
	}

	void Fg_layer::moveSelectedObject(const glm::vec2 & offset,bool first )
	{
		for (int i = 0; i < m_objects.size(); i++)
		{

			if (m_objects[i].isSelected())
			{	
				if (first)
				{
					//std::cout << "Cur Pos " << feint_common::Instance()->convertVec2toString(m_objects[i].getPos()) << "\n";
					m_objects[i].calculateOffsetClick(offset);
				}
				else
				{
					m_objects[i].moveToOffset(offset);
				}
			//	m_objects[i].setPos(offset);
			}
		}
	}

	void Fg_layer::clearObjectOffset()
	{
		for (int i = 0; i < m_objects.size(); i++)
		{
			m_objects[i].resetOffset();
		}
	}

	void Fg_layer::update(float deltaTime)
	{
		
	}

}
