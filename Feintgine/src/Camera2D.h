
#ifndef _CAMERA2D_H_
#define _CAMERA2D_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <SDL2/SDL.h> 
#include "InputManager.h"
#include "feint_common.h"

const int CAMERA_MODE_ZOOM = 1;
const int CAMERA_MODE_MOVE_KEY = 2;
const int CAMERA_MODE_MOVE_MOUSE = 4;


const float CAMERA_SHAKETIME_RATE = 0.1f;

namespace Feintgine
{


	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void init(int screenWidth, int screenHeight ,int controlFlag =0 );// init the camera ( usually take the screen resolution )
		void update(); // update the camera ( moving , change view ... etc ) 

		void logicUpdate(float deltatime);

		void setPosition(const glm::vec2 & newPosition){ _position = newPosition ; _needsMatrixUpdate = true; }// set new position for the camera , can be used as moving camera 
		void setScale(const float & newScale) { _scale = newScale; _needsMatrixUpdate = true; }// set the scale , that mean zoom in or out 
		void setAngle(const float &newAngle){ _angle = newAngle; _needsMatrixUpdate = true; }
		void cam_rotate(const float t_angle){ _angle = t_angle; }

		glm::vec2 getPosition(){ return _position; } // get the position of the camera
		float getScale(){ return _scale; } // get the scale of the camera	
		glm::mat4 getCameraMatrix()const { return _cameraMatrix; } // get camera's matrix 
		glm::vec2 convertScreenToWorld(glm::vec2 screenCoords); // convert the pos of mouse in camera to current world 
		glm::vec2 convertScreenToWorld(glm::vec2 screenCoords, glm::vec2 viewPort, glm::vec2 resolution);
		glm::vec2 converWorldToScreen(glm::vec2 worldCorrds);
		
		glm::vec2 convertScreenToWorldViewPort(const glm::vec2 & screenCoords, glm::vec2 viewPos, glm::vec2 resolution);
		bool isInPortView(const glm::vec2 &pos,const glm::vec2 &dimention); // check object in camera or not 

		void move(glm::vec2 vel);


		void savePos();
		void startShake(float shakeTime, float vertFreq, float hozFreq);

		void setLimitScale(glm::vec2 val);
		void setMaxScale(float maxScale);
		void setMinScale(float minScale);

		void handleInput(InputManager & inputmanager , SDL_Event &evnt);

		int getScreenWidth() const { return _screenWidth; }
		int getScreenHeight() const { return _screenHeight; }

	private:
		int _screenWidth, _screenHeight;
		bool _needsMatrixUpdate;
		float _scale;
		float _angle;
		glm::vec2 _position;
		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;
		int m_controlFlag;
		float m_maxScale;
		float m_minScale;

		glm::vec2 m_savedPos;

		float m_vertShakeFreq;
		float m_hozShakeFreq;

		float m_shakeLifetime = 0.0f;

		
	};
}
#endif

