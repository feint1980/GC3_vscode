#pragma once
#include "Dialouge_Avatar.h"
#include "InputManager.h"
#include "Vertex.h"
#include "EmptyObject.h"
#include "EGUI_DrawElement.h"
namespace Feintgine
{

	struct Line
	{
		void init( int charNum, const std::wstring & msg,
			bool isLeft, int t_emoji)
		{
			characterNum = charNum;
			msgContent = msg;
			m_isLeft = isLeft;
			emoji = t_emoji;
		}
		std::wstring msgContent;
		int characterNum;
		int emoji;
		bool m_isLeft;
	};

	struct Dialouge
	{

		std::string m_id;
		std::vector<Line> m_lines;
		std::vector<Dialouge_Avatar> m_chacters;
	};

	class F_Dialouge_Handler
	{
	public:
		F_Dialouge_Handler();
		~F_Dialouge_Handler();

		void loadDiaglouge(const std::string & path, float scale );

		void draw(SpriteBatch & spriteBatch);

		void handleInput(InputManager & inputManager);
		void update(float deltaTime);

		void goNext();

		void playDialouge(const std::string & dialougeID);

		Feintgine::F_Sprite getCharacterEmote(Dialouge_Avatar & dialougeAvr, int emoteNum);

		void handleTransition(float deltaTime);

		void registerTextGUI(Feintgine::GUI & gui,
			const std::string & name, const glm::vec2 & pos, const glm::vec2 & dim);
		

		void setText(const std::string & msg);
		void setText(const std::wstring & msg);
	private:


		bool m_isShowing = false;

		EmptyObject m_bg;
		glm::vec4 desRect;
		glm::vec4 desRect2;
		float m_scale;
		glm::vec2 m_leftAvtPos;
		glm::vec2 m_rightAvtPos;
		bool m_showLeftAvatar;
		bool m_showRightAvatar;

		bool m_isLeft;
		bool m_isTransition = false;

		float m_additionalDeltaTime = 1.0f;

		Feintgine::F_Sprite m_leftAvt;
		Feintgine::F_Sprite m_rightAvt;

		Feintgine::Color m_leftAvtColor;
		Feintgine::Color m_rightAvtColor;

		std::string m_filePath;

		std::vector<Dialouge> m_dialouges;

		EGUI_DrawElement m_drawElement;

		std::wstring m_msgContent; 

		Dialouge m_currentDialouge;

		int m_currentLine;

	};
}

