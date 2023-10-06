#ifndef _F_OBJECT_H_
#define _F_OBJECT_H_



#include "F_Sprite.h"
#include "GLSLProgram.h"
#include "ColiderBox.h"
#include "objectData.pb.h"
#include <fstream>
#include "SpriteManager.h"
#include "LightBatch.h"
#include "TextRenderer.h"
namespace Feintgine
{


	struct SelfSprite {

		SelfSprite(const F_Sprite & t_sprite,const glm::vec2 & t_posOffset,const glm::vec2 & t_scaleOffset,const Feintgine::Color & t_color, float t_angleOffset ,float t_depth,int ID)
		{
			sprite = t_sprite;
			posOffset = t_posOffset;
			scaleOffset = t_scaleOffset;
			color = t_color;
			angleOffset = t_angleOffset;
			depth = t_depth;
			m_ID = ID;
		}
		bool checkInside(const glm::vec2  & mousePos)
		{
			if (mousePos.x > posOffset.x - (sprite.getDim().x * scaleOffset.x) / 2.0f && mousePos.x < posOffset.x + (sprite.getDim().x * scaleOffset.x) / 2.0f &&
				mousePos.y > posOffset.y - (sprite.getDim().y * scaleOffset.y) / 2.0f && mousePos.y < posOffset.y + (sprite.getDim().y * scaleOffset.y) / 2.0f)
			{

				return true;
			}
			return false;
		}
		F_Sprite sprite;
		glm::vec2 posOffset;
		glm::vec2 scaleOffset;
		Feintgine::Color color;
		float angleOffset;
		float depth;
		int m_ID;
	};

	class F_Object
	{
	public:

		void loadFromFile(const std::string & filePath);

		void setPos(const glm::vec2 & pos);

		glm::vec2 getPos() const { return m_pos; }

		void create(const Proc_Object & object,const glm::vec2 & pos , const glm::vec2 scale ,float angle, float depth);
		
		Proc_LoadObject getProtoSer();

		void addSprite(const F_Sprite  & t_sprite,const glm::vec2 & t_posOffset,const glm::vec2 & t_scaleOffset,const  Feintgine::Color & t_color, float offsetAngle, float t_depth,int ID);

		void draw(Feintgine::SpriteBatch & spriteBatch);

		void drawLight(LightBatch &lightBatch);

		void setLight(Proc_SpotLight & l1, Proc_SpotLight & l2);

		void setColider(Proc_ColiderBox & c1, Proc_ColiderBox & c2);

		void addLight(const glm::vec2 & pos, const glm::vec4 & color,const glm::vec3 & attenuation,int ID);

		void drawColider(DebugRender & renderer);

		void addColider(const glm::vec2 & pos,const glm::vec2 & dim,int ID);

		void calculatePriority();

		glm::vec2 getFullDimObject();

		void saveToFile(const std::string & name ,const std::string & filePath);

		void showHoverBox(Feintgine::DebugRender & debugRenderer);

		Proc_SpotLight getLightSer(const glm::vec2 & pos, const glm::vec4 & color, const glm::vec3 & attennua);
		Proc_ColiderBox getColSer(const glm::vec2 & pos, const glm::vec2 & dim);
	

		std::vector<glm::vec2> m_lightListPos;
		std::vector<glm::vec2> m_lightListOffsetPos;
		std::vector<glm::vec4> m_lightListColor;
		std::vector<glm::vec3> m_lightListAttenuation;
		
		std::vector<int> m_lightListID;

		SelfSprite * getSpriteByPos(glm::vec2 mousePos);

		/*int getLightIndexByID(int ID);*/

		void calculateOffsetClick(const glm::vec2 & offset);

		void moveToOffset(const glm::vec2 & offsetSet);

		std::vector<ColiderBox> m_coliders;

// 		int getColiderIndexByID(int ID);
// 
// 		void setFitScale(float scale);
// 		void setEnlargeSize(float size);

		void setSelected(bool value);

		bool isSelected() const { return m_selected; }

		float getDepth() const { return m_depth; }

		void setDepth( float depth);

// 		std::string getFilePath() const {
// 		
// 			return m_filePath;
// 		}

		void resetOffset();

		void setHover(bool value);

		// SelfSprite * getSpriteByID(int ID);

		std::string getName() const { return m_name; }

		//void deleteSpriteByID(int ID);
		//void deleteColiderByID(int ID);

		bool isHover() const {
			return m_hover;
		}

		bool isMouseInside(const glm::vec2 & mousePos);
	

		void clearLightAfterward();

		F_Object();
		~F_Object();

	protected:

		float m_fitScale = 1;
		float m_enlarger = 1.0f;

		GLSLProgram  used_shader;

		bool m_hover = false;
		bool m_selected = false;

		std::vector<SelfSprite> m_sprites;
		std::string m_name;
		std::string m_filePath;

		Feintgine::Color m_hoverColor = Feintgine::Color(90, 90, 233, 255);
		Feintgine::Color m_selectedColor = Feintgine::Color(233, 100, 233, 255);

		glm::vec4 m_color = glm::vec4(1);

		Proc_LoadObject m_loadObject;
		Proc_Object  m_refab;
		
		glm::vec2 m_pos;
		glm::vec2 m_dim;
		float m_depth;
		float m_angle;

		float m_maxX;
		float m_maxY;
		float m_minX;
		float m_minY;
		glm::vec2 t_calculatedOffset;
		glm::vec2 savePos;

		float t_priority;

	};
}

#endif
