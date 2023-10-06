
#ifndef _IGAMESCREEN_H_
#define _IGAMESCREEN_H_

#define SCREEN_INDEX_NULL -1
enum class GameState { TOWN, PLAY };
const float FADE_SPEED = 0.0125f;
namespace Feintgine{

	class IMainGame;

	enum class ScreenState{
		NONE,
		RUNNING,
		EXIT_APPLICATION,
		CHANGE_NEXT,
		CHANGE_PREVIOUS
	};

	class IGameScreen
	{
	public:
		friend class ScreenList;
		IGameScreen();
		virtual ~IGameScreen();

		virtual int getNextScreenIndex() const = 0;
		virtual int getPreviousScreenIndex() const = 0;

		virtual void build() = 0;
		virtual void destroy() = 0;

		virtual void onEntry() = 0;
		virtual void onExit() = 0;

		virtual void update(float deltaTime) = 0;
		virtual void draw() = 0;
		virtual void checkInput() = 0;
		void startScreen();

	

		int getScreenIndex() const{ return m_screenIndex; }

		void setParentGame(IMainGame * game) { m_game = game; }

		void setRunning() { m_currentState = ScreenState::RUNNING; }
		ScreenState getState() const { return m_currentState; }
		void changeNextScreen();
		void changePrevScreen();

	protected:
		ScreenState m_currentState = ScreenState::NONE;
		IMainGame *m_game = nullptr;
		int m_screenIndex = -1;
		float m_alpha = 0;
		bool startup = false;
		bool changeNext = false;
		bool changeBack = false;
		bool m_isExit = false;

	};
}

#endif
