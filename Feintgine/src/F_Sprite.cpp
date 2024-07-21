#include "F_Sprite.h"
#include <iostream>
#include "objectData.pb.h"

namespace Feintgine {

	F_Sprite::F_Sprite()
	{
	}


	F_Sprite::F_Sprite(const glm::vec2 & pos,const glm::vec2 & dim,const glm::vec2 & anchor, const std::string & texture_path, const std::string & packetName, const std::string & name)
	{
		init(pos, dim, anchor, texture_path, packetName, name);
	}

	F_Sprite::~F_Sprite()
	{
	}

	void F_Sprite::setDim(const glm::vec2 & dim)
	{
		m_dim = dim;
		updateUV();
	}



	void F_Sprite::setAnchor(const glm::vec2 & anchor)
	{
		m_anchor = anchor;
	}

	void F_Sprite::setTextureDim(const glm::vec2 & textureDim)
	{
		m_textureDim = textureDim;
	}


	void F_Sprite::setInvert(bool val)
	{
		m_isInverted = val;
	}

	Proc_Vec2 * F_Sprite::convertVec2ToProcVec2(const glm::vec2 & v2)
	{
		Proc_Vec2 * pv2 = new Proc_Vec2();
		pv2->set_valuex(v2.x);
		pv2->set_valuey(v2.y);
		return pv2;
	}

	Proc_Vec3 * F_Sprite::convertVec3ToProcVec3(const glm::vec3 & v3)
	{
		Proc_Vec3 * pv3 = new Proc_Vec3();
		pv3->set_valuex(v3.x);
		pv3->set_valuey(v3.y);
		pv3->set_valuez(v3.z);
		return pv3;
	}

	Proc_Vec4 * F_Sprite::convertVec4ToProcVec4(const glm::vec4 & v4)
	{
		Proc_Vec4 * pv4 = new Proc_Vec4();
		pv4->set_valuex(v4.x);
		pv4->set_valuey(v4.y);
		pv4->set_valuez(v4.z);
		pv4->set_valuew(v4.w);
		return pv4;
	}



	Proc_Sprite F_Sprite::getProcSprite()
	{
		Proc_Sprite proc_sprite;
		proc_sprite.set_texturepath(m_texturePath);
		//Proc_Vec2 dim = 
		proc_sprite.set_allocated_dim(convertVec2ToProcVec2(m_dim));
		proc_sprite.set_name(m_name);
		proc_sprite.set_packetname(m_packetName);

		return proc_sprite;

	}

	void F_Sprite::init(const glm::vec2 & pos, const glm::vec2 & dim, const glm::vec2 & anchor, const std::string & texture_path, const std::string & packetName, const std::string & name)
	{

		m_pos = pos;
		m_dim = dim;
		m_anchor = anchor;
		m_texturePath = texture_path;
		m_texture = Feintgine::ResourceManager::getTexture(m_texturePath);
		m_textureDim = glm::vec2(m_texture.width, m_texture.height);
		m_packetName = packetName;
		m_name = name;
		//	std::cout << "DIM " << m_texture.width << " " << m_texture.height << "\n";
		updateUV();

	}
	void F_Sprite::updateTextureBuffers()
	{
		m_texture = Feintgine::ResourceManager::getTexture(m_texturePath);
	}
	

	void F_Sprite::createFromProc(const Proc_Sprite & sprite)
	{
		
		glm::vec2 pos(0);
		glm::vec2 dim(0);
		glm::vec2 anchor(0.5);

		m_pos = pos;
		m_dim = dim;
		m_anchor = anchor;
		m_texturePath = sprite.texturepath();
		//std::cout << "texture path is " << sprite.texturepath() << "\n";
		
		m_texture = Feintgine::ResourceManager::getTexture(m_texturePath);
		m_textureDim = glm::vec2(m_texture.width, m_texture.height);
		m_packetName = sprite.packetname();
		m_name = sprite.name();
		//std::cout << "texture name is " << m_packetName << "\n";
		//std::cout << "name is " << m_name << "\n";
		//	std::cout << "DIM " << m_texture.width << " " << m_texture.height << "\n";
		updateUV();
	}

	void F_Sprite::updateUV()
	{
		// This shit was calculated by Feint in the sleepless night ( easy part tho ) 
		m_uv.x = m_pos.x / m_textureDim.x;
		m_uv.y = 1 - ((m_pos.y + m_dim.y) / m_textureDim.y);
		m_uv.z = m_dim.x / m_textureDim.x;
		m_uv.w = (m_dim.y / m_textureDim.y);
	}

}
