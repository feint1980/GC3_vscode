#include "F_Object.h"

namespace Feintgine {


	void F_Object::loadFromFile(const std::string & filePath)
	{
		std::cout << "load file from " << filePath.c_str() << "\n";
		//if (!m_refab)
		//{
		m_refab = Proc_Object();
		//}

		m_loadObject.Clear();
		m_refab.Clear();
		m_lightListPos.clear();
		m_lightListAttenuation.clear();
		m_lightListColor.clear();
		m_lightListID.clear();
		m_coliders.clear();
		m_filePath = filePath.c_str();
		//Proc_Object proc_object;
		std::fstream input(filePath.c_str(), std::ios::in | std::ios::binary);
		if (!m_refab.ParseFromIstream(&input))
		{
			std::cout << "Failed to read object :  " << filePath << "\n";
		}
		else
		{
			m_name = m_refab.name();
			//std::cout << "loading object name " << m_name << "\n";
			m_sprites.clear();
			for (int i = 0; i <m_refab.proc_spritelist_size(); i++)
			{
				//std::cout << " layer index " << i << "has " << s_scence.layers(i).objects_size() << "object \n";

				F_Sprite sprite;
				sprite = Feintgine::SpriteManager::Instance()->getSprite(m_refab.proc_spritelist(i).proc_sprite().packetname() + "/" + m_refab.proc_spritelist(i).proc_sprite().name());
				//sprite.createFromProc(proc_object.proc_spritelist(i).proc_sprite());
				//glm::vec2 offsetPos = glm::vec2(0);
				//glm::vec2 offsetScale = glm::vec2(1);
				glm::vec2 offsetPos = feint_common::Instance()->convertProcVec2ToVec2(m_refab.proc_spritelist(i).offsetpos());
				glm::vec2 offsetScale = feint_common::Instance()->convertProcVec2ToVec2(m_refab.proc_spritelist(i).offsetscale());
				//std::cout << "offset Pos "
				//glm::vec2 offsetScale = convertProcVec2ToVec2(proc_object.proc_spritelist(i).offsetscale());
				glm::vec4 t_color  = feint_common::Instance()->convertProcVec4ToVec4(m_refab.proc_spritelist(i).color());
				t_color *= m_color;
				

				//prite.setInvert(m_refab.proc_spritelist(i).proc_sprite().);
				sprite.setInvert(m_refab.proc_spritelist(i).proc_sprite().isinvert());
				//Feintgine::Color color = Feintgine::Color(255, 255, 255, 255);
				//std::cout << "value of color loaded is " << v_color.x << "\n";
				Feintgine::Color color = Feintgine::Color(t_color.x * 255.0f, t_color.y * 255.0f, t_color.z * 255.0f, t_color.w * 255.0f);
				addSprite(sprite, offsetPos, offsetScale, color, m_refab.proc_spritelist(i).angle(), m_refab.proc_spritelist(i).depth(), i);
				//addSprite()

			}
			for (int i = 0; i < m_refab.lightlist_size(); i++)
			{
				//std::cout << " layer index " << i << "has " << s_scence.layers(i).objects_size() << "object \n";
	
				glm::vec2 pos = feint_common::Instance()->convertProcVec2ToVec2(m_refab.lightlist(i).pos());
				pos += m_pos;
				glm::vec3 attenuation = feint_common::Instance()->convertProcVec3ToVec3(m_refab.lightlist(i).atenuation());
				glm::vec4 color = feint_common::Instance()->convertProcVec4ToVec4(m_refab.lightlist(i).color());
				
				//std::cout << "offset Pos "
				//glm::vec2 offsetScale = convertProcVec2ToVec2(proc_object.proc_spritelist(i).offsetscale());
				addLight(pos, color, attenuation, i);
				//Feintgine::Color color = Feintgine::Color(v_color.x * 255.0f, v_color.y * 255.0f, v_color.z * 255.0f, v_color.w * 255.0f);
				
			}
			for (int i = 0; i < m_refab.coliderlist_size(); i++)
			{
				//std::cout << " layer index " << i << "has " << s_scence.layers(i).objects_size() << "object \n";

				glm::vec2 pos = feint_common::Instance()->convertProcVec2ToVec2(m_refab.coliderlist(i).pos());
				pos += m_pos;
				glm::vec2 dim = feint_common::Instance()->convertProcVec2ToVec2(m_refab.coliderlist(i).dim());
		
				//std::cout << "offset Pos "
				//glm::vec2 offsetScale = convertProcVec2ToVec2(proc_object.proc_spritelist(i).offsetscale());
				addColider(pos, dim, i);
				//Feintgine::Color color = Feintgine::Color(v_color.x * 255.0f, v_color.y * 255.0f, v_color.z * 255.0f, v_color.w * 255.0f);

			}

			std::cout << "read file ok \n";


		}
	}

	void F_Object::setPos(const glm::vec2  &pos)
	{
		m_pos = pos;
		for (int i = 0; i < m_lightListPos.size(); i++)
		{
			m_lightListPos[i] = m_lightListOffsetPos[i] + m_pos;			
		}
	}

	void F_Object::create(const Proc_Object & object, const glm::vec2 & pos, const glm::vec2 scale, float angle, float depth)
	{
		//std::cout << "DEBUG #### " << object.name() << "\n";
		std::string loadTarget = "./Assets/F_Objects/" + object.name() + ".fob";	
		loadFromFile(loadTarget);
		setPos(pos);
		setDepth(depth);
	//	m_pos = pos;
		m_dim = m_dim * scale;
		m_angle = angle; 
		//m_depth = depth;
		
	}

	Proc_LoadObject F_Object::getProtoSer()
	{
					
		Proc_LoadObject object;

// 		for (size_t i = 0; i < m_lightListID.size(); i++)
// 		{
// 			Proc_SpotLight * t_light = new Proc_SpotLight(getLightSer(m_lightListPos[i], m_lightListColor[i], m_lightListAttenuation[i]));
// 			t_light = m_refab.add_lightlist();
// 		}
// 		for (size_t i = 0; i < m_coliders.size(); i++)
// 		{
// 			Proc_ColiderBox * t_col = new Proc_ColiderBox(getColSer(m_coliders[i].getPos(), m_coliders[i].getPos()));
// 			t_col = m_refab.add_coliderlist();
// 		}
		object.set_allocated_refab(&m_refab);
		object.set_allocated_pos(new Proc_Vec2(feint_common::Instance()->convertVec2ToProcVec2(m_pos)));
		object.set_allocated_scale(new Proc_Vec2(feint_common::Instance()->convertVec2ToProcVec2(m_dim)));
		object.set_angle(m_angle);
		object.set_allocated_color(new Proc_Vec4(feint_common::Instance()->convertVec4ToProcVec4(m_color)));

		return object;

	}

	void F_Object::addSprite(const F_Sprite & t_sprite, const glm::vec2  & t_posOffset, const glm::vec2 &t_scaleOffset, const Feintgine::Color & t_color, float t_angleOffset, float t_depth, int ID)
	{
		m_sprites.emplace_back(t_sprite, t_posOffset, t_scaleOffset, t_color, t_angleOffset,t_depth,ID);
	}

	void F_Object::draw(Feintgine::SpriteBatch & spriteBatch)
	{
		for (int i = 0; i < m_sprites.size(); i++)
		{
			glm::vec4 desRect;// (0, 0, 50, 50);
			desRect.x = (m_pos.x + m_sprites[i].posOffset.x * m_fitScale * m_enlarger) - (m_sprites[i].sprite.getDim().x * m_sprites[i].scaleOffset.x / 2.0f * m_fitScale * m_enlarger);
			desRect.y = (m_pos.y + m_sprites[i].posOffset.y * m_fitScale * m_enlarger) - (m_sprites[i].sprite.getDim().y * m_sprites[i].scaleOffset.y / 2.0f * m_fitScale * m_enlarger);
			desRect.z = m_sprites[i].scaleOffset.x * m_sprites[i].sprite.getDim().x * m_fitScale * m_enlarger;
			desRect.w = m_sprites[i].scaleOffset.y * m_sprites[i].sprite.getDim().y * m_fitScale * m_enlarger;

			spriteBatch.draw(desRect, m_sprites[i].sprite.getUV(), m_sprites[i].sprite.getTexture().id, m_depth + (m_sprites[i].depth * 0.1) + t_priority , m_sprites[i].color /*+ Feintgine::Color(m_color) */, m_angle + m_sprites[i].angleOffset);
		}
	}
	
	void F_Object::drawLight(LightBatch &lightBatch)
	{
		
		for (int i = 0; i < m_lightListPos.size(); i++)
		{
			
			lightBatch.addLight(m_lightListPos[i], m_lightListColor[i], m_lightListAttenuation[i]);
			
		}

	}

	void F_Object::setLight(Proc_SpotLight & l1, Proc_SpotLight & l2)
	{
		l2 = l1;
	}

	void F_Object::setColider(Proc_ColiderBox & c1, Proc_ColiderBox & c2)
	{
		c2 = c1;
	}

	void F_Object::addLight(const glm::vec2 & pos, const glm::vec4 & color, const glm::vec3 & attenuation, int ID)
	{
	
		Proc_Object object;
		m_lightListPos.push_back(pos);
		m_lightListOffsetPos.push_back(m_pos + pos);
		m_lightListColor.push_back(color);
		m_lightListAttenuation.push_back(attenuation);
		m_lightListID.push_back(ID);
	
		
		//setLight(getLightSer(pos, color, attenuation), *t_light);
				
	}
	



	void F_Object::drawColider(DebugRender & renderer)
	{
		for (int i = 0; i < m_coliders.size(); i++)
		{
			m_coliders[i].draw(renderer);
		}
	}

	void F_Object::addColider(const glm::vec2 & pos,const glm::vec2 & dim,int ID)
	{
		ColiderBox col;
		col.init(pos, dim,ID);
		m_coliders.push_back(col);
// 		if (m_refab)
// 		{
// 			Proc_ColiderBox t_col;
// 			t_col.set_allocated_pos(new Proc_Vec2(convertVec2ToProcVec2(pos)));
// 			t_col.set_allocated_dim(new Proc_Vec2(convertVec2ToProcVec2(dim)));
// 			setColider(t_col, *m_refab->add_coliderlist());
// 		}

	}

	void F_Object::calculatePriority()
	{
		float amount = 0.5;
		float repost = (m_pos.y - (getFullDimObject().y / 2.0f)) / 10000.0f;
		t_priority = amount - repost;
	}

	void F_Object::saveToFile(const std::string & name, const std::string & filePath)
	{
		Proc_Object proc_object;
		for (int i = 0; i < m_lightListID.size(); i++)
		{
			Proc_SpotLight *light = proc_object.add_lightlist();
			Proc_Vec2 * pos = new Proc_Vec2();
			pos->set_valuex(m_lightListPos[i].x);
			pos->set_valuey(m_lightListPos[i].y);
			Proc_Vec4 *color = new Proc_Vec4();
			color->set_valuex(m_lightListColor[i].x);
			color->set_valuey(m_lightListColor[i].y);
			color->set_valuez(m_lightListColor[i].z);
			color->set_valuew(m_lightListColor[i].w);
			Proc_Vec3 * attenuation = new Proc_Vec3();
			attenuation->set_valuex(m_lightListAttenuation[i].x);
			attenuation->set_valuey(m_lightListAttenuation[i].y);
			attenuation->set_valuez(m_lightListAttenuation[i].z);
// 			Proc_Vec2 * offset = new Proc_Vec2();
// 			offset->set_valuex(m_lightListOffsetPos[i].x);
// 			offset->set_valuey(m_lightListOffsetPos[i].y);
			light->set_allocated_pos(pos);
			light->set_allocated_color(color);
			light->set_allocated_atenuation(attenuation);	
			//light->set_allocated_offset(offset);
		}
		for (int i = 0; i < m_coliders.size(); i++)
		{
			Proc_ColiderBox *colider = proc_object.add_coliderlist();
			Proc_Vec2 * pos = new Proc_Vec2();
			pos->set_valuex(m_coliders[i].getPos().x);
			pos->set_valuey(m_coliders[i].getPos().y);
			Proc_Vec2 * dim = new Proc_Vec2();
			dim->set_valuex(m_coliders[i].getDim().x);
			dim->set_valuey(m_coliders[i].getDim().y);
			colider->set_allocated_pos(pos);
			colider->set_allocated_dim(dim);
		}
		for (int i = 0; i < m_sprites.size(); i++)
		{
			std::cout << "write sprite START ======================= \n";
			Proc_OwnSprite * ownSprite = proc_object.add_proc_spritelist();
			Proc_Sprite * sprite = new Proc_Sprite(); 
			std::cout << "write sprite texture path : " << m_sprites[i].sprite.getTexturePath() <<  " \n";
			sprite->set_texturepath(m_sprites[i].sprite.getTexturePath());
			std::cout << "confirm twexture path : " << sprite->texturepath() << "\n";
			Proc_Vec2 dim = feint_common::Instance()->convertVec2ToProcVec2(m_sprites[i].sprite.getDim());
			sprite->set_allocated_dim(&dim);
			sprite->set_name(m_sprites[i].sprite.getName());
			sprite->set_packetname(m_sprites[i].sprite.getPacketName());
			sprite->set_isinvert(m_sprites[i].sprite.isInverted());
			
			ownSprite->set_allocated_proc_sprite(sprite);
			Proc_Vec2 * offsetPos = new Proc_Vec2();
			offsetPos->set_valuex(m_sprites[i].posOffset.x); 
			offsetPos->set_valuey(m_sprites[i].posOffset.y);
			ownSprite->set_allocated_offsetpos(offsetPos);
			Proc_Vec2 * offsetScale = new Proc_Vec2();
			offsetScale->set_valuex(m_sprites[i].scaleOffset.x);
			offsetScale->set_valuey(m_sprites[i].scaleOffset.y);
			ownSprite->set_allocated_offsetscale(offsetScale);
			glm::vec4 trans_color = glm::vec4(m_sprites[i].color.r, m_sprites[i].color.g , m_sprites[i].color.b , m_sprites[i].color.a );
			
			Proc_Vec4 * color = new Proc_Vec4();
			color->set_valuex(trans_color.x);
			color->set_valuey(trans_color.y);
			color->set_valuez(trans_color.z);
			color->set_valuew(trans_color.w);
			ownSprite->set_allocated_color(color);

			ownSprite->set_depth(m_sprites[i].depth);
			ownSprite->set_angle(m_sprites[i].angleOffset);
			std::cout << "write sprite END ======================= \n";

		}
		std::cout << "feint debug, reach here \n";
		proc_object.set_name(name);
		std::cout << "feint debug, reach here 2 \n";
		//proc_object.SerializeAsString();
		std::cout << "feint debug, reach here 3 \n";
		std::cout << "check after loop +=========================\n";
		for (int i = 0; i < proc_object.proc_spritelist_size(); i++)
		{
			std::cout << "check write data \n";
			std::cout << "texture patch :" <<  proc_object.proc_spritelist(i).proc_sprite().texturepath() << "\n";
		}
		std::string finalPath = filePath + name + ".fob";
		std::cout << "final path : " << finalPath << "\n";
		std::fstream output(finalPath.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
	
		if (!proc_object.SerializeToOstream(&output)) {
			std::cout << "Failed to write scene .\n";

		}
		else
		{
			std::cout << "Save Object " << proc_object.name() << " OK \n";
		}

		//proc_object.Clear();
		//Proc_Object


	}



	Proc_SpotLight F_Object::getLightSer(const glm::vec2 & pos, const glm::vec4 & color, const glm::vec3 & attennua)
	{

		Proc_SpotLight t_light;
		t_light.set_allocated_pos(new Proc_Vec2(feint_common::Instance()->convertVec2ToProcVec2(pos)));
		t_light.set_allocated_color(new Proc_Vec4(feint_common::Instance()->convertVec4ToProcVec4(color)));
		t_light.set_allocated_atenuation(new Proc_Vec3(feint_common::Instance()->convertVec3ToProcVec3(attennua)));

		return t_light;

	}

	Proc_ColiderBox F_Object::getColSer(const glm::vec2 & pos, const glm::vec2 & dim)
	{
		Proc_ColiderBox t_col;
		t_col.set_allocated_pos(new Proc_Vec2(feint_common::Instance()->convertVec2ToProcVec2(pos)));
		t_col.set_allocated_dim(new Proc_Vec2(feint_common::Instance()->convertVec2ToProcVec2(dim)));

		return t_col;
	}

	


	

	Feintgine::SelfSprite * F_Object::getSpriteByPos(glm::vec2 mousePos)
	{
		for (int i = 0; i < m_sprites.size(); i++)
		{
			if (m_sprites[i].checkInside(mousePos))
			{
				return &m_sprites[i];
			}
		}

		return nullptr;
	}

	

	void F_Object::calculateOffsetClick(const glm::vec2 & offset)
	{
		t_calculatedOffset = m_pos - offset;
		savePos = m_pos;

	}

	void F_Object::moveToOffset(const glm::vec2 & offsetSet)
	{

		setPos(savePos + t_calculatedOffset- ((m_pos - offsetSet)));
		t_calculatedOffset = m_pos - offsetSet;
		savePos = m_pos;
	}

	void F_Object::setDepth(float depth)
	{
		m_depth = depth;
	}


	void F_Object::resetOffset()
	{
		t_calculatedOffset = glm::vec2(0);
		savePos = glm::vec2(0);
	}

	void F_Object::showHoverBox(Feintgine::DebugRender & debugRenderer)
	{

		Feintgine::Color t_color;
		glm::vec4 desRect(m_pos, getFullDimObject());
		if (m_hover)
		{
			t_color = m_hoverColor;
		}

		if (m_selected)
		{
			t_color = m_selectedColor;
		}
		debugRenderer.drawBox_center(desRect, t_color, m_angle);
	}

	void F_Object::setSelected(bool value)
	{
		m_selected = value;
	}

	void F_Object::setHover(bool value)
	{
		m_hover = value;
	}

	void F_Object::clearLightAfterward()
	{

		m_lightListPos.clear();
		m_lightListAttenuation.clear();
		m_lightListColor.clear();
		m_lightListID.clear();

	}

	bool F_Object::isMouseInside(const glm::vec2 & mousePos)
	{
		
		glm::vec2 halfdim = getFullDimObject() / 2.0f;
		//std::cout << "check mouse inside " << mousePos.x << " " << mousePos.y  << "\n";
		if (mousePos.x > m_pos.x - halfdim.x && mousePos.x < m_pos.x + halfdim.x && mousePos.y > m_pos.y - halfdim.y && mousePos.y < m_pos.y + halfdim.y)
		{

			return true;
		}

		return false;
	}

	F_Object::F_Object()
	{
	}

	glm::vec2 F_Object::getFullDimObject()
	{
		m_maxX = 0;
		m_maxY = 0;
		m_minX = 0;
		m_minY = 0;
		for (int i = 0; i < m_sprites.size(); i++)
		{
			float maxX = m_sprites[i].posOffset.x + ((m_sprites[i].sprite.getDim().x * m_sprites[i].scaleOffset.x) / 2);
			float maxY = m_sprites[i].posOffset.y + ((m_sprites[i].sprite.getDim().y * m_sprites[i].scaleOffset.y) / 2);
			float minX = m_sprites[i].posOffset.x - ((m_sprites[i].sprite.getDim().x * m_sprites[i].scaleOffset.x) / 2);
			float minY = m_sprites[i].posOffset.x - ((m_sprites[i].sprite.getDim().x * m_sprites[i].scaleOffset.x) / 2);
			if (maxX > m_maxX)
			{
				m_maxX = maxX;
			}
			if (maxY > m_maxY)
			{
				m_maxY = maxY;
			}
			if (minX < m_minX)
			{
				m_minX = minX;
			}
			if (minY < m_minY)
			{
				m_minY = minY;
			}

		}
		glm::vec2 maxDim;
		maxDim.x = m_maxX - m_minX;
		maxDim.y = m_maxY - m_minY;

		return maxDim;
	}


	F_Object::~F_Object()
	{
	}

}
