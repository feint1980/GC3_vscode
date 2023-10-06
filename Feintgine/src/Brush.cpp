#include "Brush.h"


namespace Feintgine
{

	Brush::Brush()
	{
	}


	Brush::~Brush()
	{
	}

	void Brush::setDepth(float depth)
	{
		m_depth = depth;
	}
	

	void Brush::loadFromProto(const Proc_Brush & proc_brush)
	{

		m_filePath = proc_brush.texturename().c_str();
		
		m_texture = Feintgine::ResourceManager::getTexture(m_filePath);

		m_pos = feint_common::Instance()->convertProcVec2ToVec2(proc_brush.pos());
		
		m_uv = feint_common::Instance()->convertProcVec2ToVec2(proc_brush.uv());

		m_dim = feint_common::Instance()->convertProcVec2ToVec2(proc_brush.dim());

		m_depth = proc_brush.depth();
		m_color = Feintgine::Color(255, 255, 255, 255);

	}


	Proc_Brush Brush::getProtoSer()
	{
		Proc_Brush proc_brush;

		proc_brush.set_allocated_texturename(&m_filePath);
		proc_brush.set_allocated_pos(new Proc_Vec2 (feint_common::Instance()->convertVec2ToProcVec2(m_pos)));
		proc_brush.set_allocated_dim(new Proc_Vec2(feint_common::Instance()->convertVec2ToProcVec2(m_dim)));
		proc_brush.set_allocated_uv(new Proc_Vec2(feint_common::Instance()->convertVec2ToProcVec2(m_uv)));
		proc_brush.set_depth(m_depth);
		return proc_brush;
	}

	void Brush::draw(Feintgine::SpriteBatch & spriteBatch)
	{
		//std::cout << "draw \n";
		glm::vec4 desRect;
		desRect.x = m_pos.x - m_dim.x / 2.0f;
		desRect.y = m_pos.y - m_dim.y / 2.0f;
		desRect.z = m_dim.x;
		desRect.w = m_dim.y;
		spriteBatch.draw(desRect, glm::vec4(0, 0, m_uv), m_texture.id, m_depth,m_color, 0.001f);
	}

	void Brush::init(const std::string & filePath , glm::vec2 pos, glm::vec2 dims, glm::vec2 uv, Feintgine::Color color , float depth)
	{

		m_filePath = filePath;
		m_texture = Feintgine::ResourceManager::getTexture(m_filePath.c_str());
		m_pos = pos;
		m_dim = dims;
		m_color = color;
		m_uv = uv;
		m_depth = depth;

	}

}