// #include "SimpleDrawingObejct.h"



// SimpleDrawingObject::SimpleDrawingObject()
// {
// 	m_uv = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
// 	m_color = Feintgine::Color(255, 255, 255, 255);
// }


// SimpleDrawingObject::~SimpleDrawingObject()
// {
// }

// void SimpleDrawingObject::init(const std::string &fobPath)
// {
// 	//std::cout << "load prefab " << fobPath << "\n";

// 	//f_object object;
// 	std::fstream input(fobPath.c_str(), std::ios::in | std::ios::binary);
// 	if (!object.ParseFromIstream(&input))
// 	{
// 		std::cout << "Failed to read object :  " << fobPath << "\n";
// 	}
// 	else
// 	{
		
// 		m_coliders.clear();
// 		glm::vec4 t_uv;
// 		t_uv.x = object.uv().xy().x();
// 		t_uv.y = object.uv().xy().y();
// 		t_uv.z = object.uv().zw().x();
// 		t_uv.w = object.uv().zw().y();

// 		Feintgine::Color t_color;
// 		t_color.r = object.color().color_r() / 255;
// 		t_color.g = object.color().color_g() / 255;
// 		t_color.b = object.color().color_b() / 255;
// 		t_color.a = object.color().color_a() / 255;

// 		m_name = object.name();
// 		m_type = object.type();

// 		//std::cout << "object has type " << m_type << "\n";
// 		m_uv = t_uv;
// 		m_dims.x = object.width();
// 		m_dims.y = object.heigh();

// 		actual_dim = m_dims;
// 		prefabPath = fobPath;
// 		m_texturePath = object.texturepath();
// 		m_color = t_color;

// 		m_texture = Feintgine::ResourceManager::getTexture(m_texturePath);

// 		for (int i = 0; i < object.coliderlist_size(); i++)
// 		{
// 			glm::vec2 c_pos;
// 			glm::vec2 c_dim;
// 			c_pos.x = object.coliderlist(i).pos().x();
// 			c_pos.y = object.coliderlist(i).pos().y();
// 			c_dim.x = object.coliderlist(i).dim().x();
// 			c_dim.y = object.coliderlist(i).dim().y();
// 			addColider(c_pos, c_dim);
// 		}


// 	}
// 	input.close();
// }

// void SimpleDrawingObject::draw(Feintgine::SpriteBatch & spriteBatch)
// {

		
// 		glm::vec4 desRect;
// 		desRect.x = m_pos.x - m_dims.x / 2.0f;
// 		desRect.y = m_pos.y - m_dims.y / 2.0f;
// 		desRect.z = m_dims.x;
// 		desRect.w = m_dims.y;
// 		spriteBatch.draw(desRect, m_uv, m_texture.id, m_depth, m_color, m_angle);
		
	
// }



// void SimpleDrawingObject::addColider(glm::vec2 c_pos, glm::vec2 c_dim)
// {
// 	ObjectColider col;
// 	col.init(c_pos, c_dim);
// 	m_coliders.push_back(col);
// }

// void SimpleDrawingObject::drawColiders(Feintgine::DebugRender & renderer)
// {
// 	for (int i = 0; i < m_coliders.size(); i++)
// 	{
// 		m_coliders[i].draw(renderer);
// 	}
// }

// void SimpleDrawingObject::setPos(glm::vec2 pos)
// {
// 	m_pos = pos;
// }

// void SimpleDrawingObject::setDim(glm::vec2 dim)
// {
// 	m_dims = dim;
// }

// void SimpleDrawingObject::setDepth(float depth)
// {
// 	m_depth = depth;
// }

// void SimpleDrawingObject::setColor(Feintgine::Color color)
// {
// 	m_color = color;
// }
