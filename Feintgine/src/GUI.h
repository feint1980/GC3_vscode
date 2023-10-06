#ifndef _GUI_H_
#define _GUI_H_

#include <CEGUI/CEGUI.h>
#include <CEGUI/Image.h>
#include <CEGUI/ImageManager.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <glm/glm.hpp>
#include <SDL2/SDL.h> 
#include <iostream>

const int MAXKEY = 80;

namespace Feintgine
{
	class GUI
	{
	public:
		void init(const std::string& resourceDirectory);
		void destroy();

		void draw();
		void update();

		void setMouseCursor(const std::string& imageFile);
		void showMouseCursor();
		void hideMouseCursor();


		void addOnwidget();
		void onSDLEvent(SDL_Event& evnt);

		void injectUTF8Text(const char* utf8str);

		void loadScheme(const std::string& schemeFile);
		void setFont(const std::string& fontFile);
		CEGUI::Window* createWidget(const std::string& type, const glm::vec4& destRectPerc, const glm::vec4& destRectPix, const std::string& name = "");
		static void setWidgetDestRect(CEGUI::Window* widget, const glm::vec4& destRectPerc, const glm::vec4& destRectPix);
		
		// Getters
		static CEGUI::UVector2 convertToGUIPos(float x, float y) { return CEGUI::UVector2(CEGUI::UDim(x, 0.0f), CEGUI::UDim(y, 0.000f)); };
		static CEGUI::OpenGL3Renderer* getRenderer() { return m_renderer; }
		 CEGUI::GUIContext* getContext() { return m_context; }
		 CEGUI::Window * getWindow() const { return m_root; }
		 CEGUI::GUIContext* m_context = nullptr;

		
	private:
		static CEGUI::OpenGL3Renderer* m_renderer;
		
		CEGUI::Window* m_root = nullptr;
		unsigned int m_lastTime = 0;
	};
}

#endif 
