#include "Camera2D.h"

namespace Feintgine
{

	Camera2D::Camera2D() : _position(0.0f, 0.0f),
		_cameraMatrix(1.0f),
		_orthoMatrix(1.0f),
		_scale(1.0f),
		_needsMatrixUpdate(true),
		_screenWidth(500),
		_screenHeight(500),
		_angle(0.0f),
		m_controlFlag(0),
		m_minScale(0.01f),
		m_maxScale(60.0f)
		
	{
	}


	Camera2D::~Camera2D()
	{
	}

	void Camera2D::init(int screenWidth, int screenHeight , int controlFlag) {
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
		m_controlFlag = controlFlag;
	}

	//updates the camera matrix if needed
	void Camera2D::update() {

		//Only update if our position or scale have changed
		if (_needsMatrixUpdate) {

			//Camera Translation
			glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, translate);

			//Camera Scale
			glm::vec3 scale(_scale , _scale , 0.0f);
			_cameraMatrix = glm::scale(glm::mat4(1.0f), scale  ) * _cameraMatrix;

			glm::vec3 rotattion(1, 1, _angle);
			_cameraMatrix = glm::rotate(_cameraMatrix, _angle, rotattion);

			_needsMatrixUpdate = false;
		}
	}




	void Camera2D::logicUpdate(float deltatime)
	{
		if (m_shakeLifetime > 0.0f)
		{
			
			m_shakeLifetime -= CAMERA_SHAKETIME_RATE * deltatime;

			_position.x = m_savedPos.x + feint_common::Instance()->randomFloat(-m_hozShakeFreq, m_hozShakeFreq);
			_position.y = m_savedPos.y + feint_common::Instance()->randomFloat(-m_vertShakeFreq, m_vertShakeFreq);
			_needsMatrixUpdate = true;
		}
		else
		{
			_position = m_savedPos;
			_needsMatrixUpdate = true;

			m_shakeLifetime = 0.0f;
		}
	}

	glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords) {
		// Invert Y direction

		//std::cout << "Not converted : " << feint_common::Instance()->convertVec2toString(screenCoords) << "\n";
		//screenCoords -
		screenCoords.y = _screenHeight - screenCoords.y;
		// Make it so that 0 is the center
		screenCoords -= glm::vec2(_screenWidth / 2.0f, _screenHeight / 2.0f);
		// Scale the coordinates
		screenCoords /= (_scale);
		// Translate with the camera position
		screenCoords += _position ;
		//std::cout << "converted : " << feint_common::Instance()->convertVec2toString(converScreen) << "\n";
		return screenCoords;
	}

	glm::vec2 Camera2D::convertScreenToWorld( glm::vec2  screenCoords, glm::vec2  viewPort, glm::vec2 resolution)
	{
		// Invert Y direction
		float y_cord = resolution.y - viewPort.y;
		screenCoords.y = y_cord - _screenHeight - screenCoords.y;
		// Make it so that 0 is the center
		
		screenCoords -= glm::vec2(_screenWidth / 2.0f, _screenHeight / 2.0f) + viewPort;
		screenCoords.y += y_cord;
		// Scale the coordinates
		screenCoords /= (_scale);
		// Translate with the camera position
		screenCoords += _position;
		//std::cout << "converted : " << feint_common::Instance()->convertVec2toString(converScreen) << "\n";
		return screenCoords;
	}

	glm::vec2 Camera2D::converWorldToScreen(glm::vec2 worldCorrds)
	{
	
		//worldCorrds -= glm::vec2(_screenWidth / 2, _screenHeight / 2);
		
		glm::vec2 psede = _position;
		psede *= _scale ;

		worldCorrds *= _scale ;

		worldCorrds -= psede;
		//worldCorrds /= _scale;	

		worldCorrds += glm::vec2(_screenWidth / 2, (_screenHeight / 2));
		worldCorrds.y = _screenHeight - worldCorrds.y;
	//	worldCorrds.y = -worldCorrds.y;
		return worldCorrds ;

	}


	glm::vec2 Camera2D::convertScreenToWorldViewPort(const glm::vec2 & screenCoords, glm::vec2 viewPos, glm::vec2 resolution)
	{

		glm::vec2 converScreen = screenCoords;
		converScreen += _position;

		converScreen.x = (screenCoords.x - viewPos.x) - (_screenWidth / 2.0f);
		converScreen.y = resolution.y - screenCoords.y - viewPos.y - (_screenHeight / 2.0f);
		converScreen /= (_scale);
		//float xPos = screenCoords
		// Translate with the camera position
		//converScreen += ;
		//std::cout << "converted : " << feint_common::Instance()->convertVec2toString(converScreen) << "\n";
		return converScreen;

// 		glm::vec2 converScreen = screenCoords;
// 		glm::vec2 psede = _position;
// 		psede *= _scale;
// 		converScreen *= _scale;
// 		converScreen -= (psede);
// 		//converScreen += glm::vec2(_screenWidth / 2, (_screenHeight / 2));
// 		converScreen.x = (screenCoords.x )  - (_screenWidth /2.0f) ;
// 		converScreen.y =  (resolution.y  ) - (screenCoords.y ) - (_screenHeight / 2.0f);
// 		converScreen -= (viewPos); 
// 		//float xPos = screenCoords
// 		// Translate with the camera position
// 		//converScreen += ;
// 		//std::cout << "converted : " << feint_common::Instance()->convertVec2toString(converScreen) << "\n";
// 		return converScreen ;
	
	}

	bool Camera2D::isInPortView(const glm::vec2 &pos, const glm::vec2 &dimention)
	{
		glm::vec2 scaledScreenDimensions = glm::vec2(_screenWidth, _screenHeight) / (_scale );

		// The minimum distance before a collision occurs
		const float MIN_DISTANCE_X = dimention.x / 2.0f + scaledScreenDimensions.x / 2.0f;
		const float MIN_DISTANCE_Y = dimention.y / 2.0f + scaledScreenDimensions.y / 2.0f;

		// Center position of the parameters 
		glm::vec2 centerPos = pos + dimention / 2.0f;
		// Center position of the camera
		glm::vec2 centerCameraPos = _position;
		// Vector from the input to the camera
		glm::vec2 distVec = centerPos - centerCameraPos;

		// Get the depth of the collision
		float xDepth = MIN_DISTANCE_X - abs(distVec.x);
		float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

		// If both the depths are > 0, then we collided
		if (xDepth > 0 && yDepth > -3.0f) {
			// There was a collision
			return true;
		}
		return false;
	}

	void Camera2D::move(glm::vec2 vel)
	{
		_position += vel / _scale;
		//std::cout << "move to x " << vel.x << "to y " << vel.y << "\n";
		_needsMatrixUpdate = true;
	}


	void Camera2D::savePos()
	{
		m_savedPos = _position;
	}

	void Camera2D::startShake(float shakeTime, float vertFreq, float hozFreq)
	{
		//m_savedPos = _position;
		m_shakeLifetime = shakeTime;
		m_vertShakeFreq = vertFreq;
		m_hozShakeFreq = hozFreq;

	}

	void Camera2D::setLimitScale(glm::vec2 val)
	{
		m_maxScale = val.x;
		m_minScale = val.y;
	}

	void Camera2D::setMaxScale(float maxScale)
	{
		m_minScale = maxScale;
	}

	void Camera2D::setMinScale(float minScale)
	{
		m_minScale = minScale;
	}

	void Camera2D::handleInput(InputManager & inputmanager, SDL_Event &evnt)
	{
		if (m_controlFlag > 0)
		{
			if (m_controlFlag & CAMERA_MODE_ZOOM)
			{
				switch (evnt.type)
				{
					case SDL_MOUSEWHEEL:
					{
						if (evnt.wheel.y > 0)
						{
							_scale *= 1.1f;
						}
						else
						{
							_scale *= 0.9f;

						}
					}
					break;
					default:
						break;
				}
				if (_scale < m_minScale)
				{
					_scale = m_minScale;
				}
				if (_scale > m_maxScale)
				{
					_scale = m_maxScale;
				}

			}
			if (m_controlFlag & CAMERA_MODE_MOVE_MOUSE)
			{
				switch (evnt.type)
				{
				case SDL_MOUSEMOTION:
				{
					if (inputmanager.isKeyDown(SDL_BUTTON_RIGHT))
					{
						move(-glm::vec2((float)evnt.motion.xrel  / _scale , (float)-evnt.motion.yrel / _scale ));
					}
				}
				break;
				default:
					break;
				}
			}
			if (m_controlFlag & CAMERA_MODE_MOVE_KEY)
			{

			}
		}
		_needsMatrixUpdate = true;
		
	}

}
