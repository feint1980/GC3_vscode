#include "TestRender3D.h"
//#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <video_reader.h>

TestRender3D::TestRender3D()
{

}

TestRender3D::TestRender3D(Feintgine::Window * window)
{
	m_window = window;
	m_screenIndex = 36;

	initShader();
}

TestRender3D::~TestRender3D()
{
}

int TestRender3D::getNextScreenIndex() const
{
	return -1;
}

int TestRender3D::getPreviousScreenIndex() const
{
	return -1;
}

void TestRender3D::build()
{
	std::cout << "build called \n";
}

void TestRender3D::destroy()
{
	std::cout << "destroy \n";
}

void TestRender3D::onEntry()
{
	//ourModel = Feintgine::Model("Assets/3D/eiki/eiki_5.obj");
	ourModel = Feintgine::Model("Assets/3D/eiki/eiki_saved.fbx");
	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight(), 7);


	VideoReaderState vr_state;

	if (!video_reader_open(&vr_state, "Videos/test.mov"))
	{
		std::cout << "Could not open video file (make sure you set a video file that exists) \n";
	}

	glEnable(GL_DEPTH_TEST);
}

void TestRender3D::onExit()
{
	
}

void TestRender3D::update(float deltaTime)
{
	camera.ProcessKeyboard(cameraMovement, deltaTime);

	
	modelAngle += 0.01f * deltaTime;
}

void TestRender3D::draw()
{
	glViewport(0, 0, 1600, 900);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.4f, 0.4f, 0.3f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	
	m_shader.use();
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)m_window->getScreenWidth() / (float)m_window->getScreenHeight(), 0.1f, 100.0f);
	
	


	glm::mat4 view = camera.GetViewMatrix();
	//m_shader.setUniformMat4()
	m_shader.setUniformMat4("projection", projection);
	m_shader.setUniformMat4("view", view);

	// render the loaded model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	// it's a bit too big for our scene, so scale it down
	model = glm::rotate(model, modelAngle, glm::vec3(0,1,0));
	m_shader.setUniformMat4("model", model);
	//ourModel.d
	ourModel.Draw(m_shader);

	m_shader.unuse();



}

void TestRender3D::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		//m_gui.onSDLEvent(evnt);
		m_camera.handleInput(m_game->m_inputManager, evnt);
		m_game->onSDLEvent(evnt);

		camera.handleMouseScroll(evnt);

	}
	handleInput(m_game->m_inputManager);
}

void TestRender3D::initShader()
{
	std::cout << "3d stuff \n";

	m_shader.compileShaders("Shaders/3d/3d.vert", "Shaders/3d/3d.frag");
	m_shader.addAttribute("aPos");
	m_shader.addAttribute("aNormal");
	m_shader.addAttribute("aTexCoords");
	m_shader.linkShaders();
	m_alpha = 1;


}

void TestRender3D::handleInput(Feintgine::InputManager & inputManager)
{
	if (inputManager.isKeyPressed(SDLK_ESCAPE))
	{
		m_currentState = Feintgine::ScreenState::EXIT_APPLICATION;
	}

	 cameraMovement = 0;
	//const int FORWARD = 1;
	//const int BACKWARD = 2;
	//const int LEFT = 4;
	//const int RIGHT = 8;
	if (inputManager.isKeyDown(SDLK_LEFT))
	{
		cameraMovement += 4;
	}
	if (inputManager.isKeyDown(SDLK_RIGHT))
	{
		cameraMovement += 8;
	}
	if (inputManager.isKeyDown(SDLK_UP))
	{
		cameraMovement += 1;
	}
	if (inputManager.isKeyDown(SDLK_DOWN))
	{
		cameraMovement += 2;
	}
	m_cameraClick = false;
	if (inputManager.isKeyPressed(SDL_BUTTON_LEFT))
	{
		m_cameraClick = true;
		//glm::vec2 t_mouse = inputManager.getMouseCoords();

		//camera.ProcessMouseMovement(t_mouse.x, t_mouse.y, m_cameraClick);
	}


}
