#pragma once
#include "F_EmptyObject.h"
#include "F_DamakuLineTrace.h"
#include "ArcFunction_hypotrochoid.h"
#include <feint_common.h>
#include "ArcFunction_hypocycloid.h"
#include "ArcFunction_Fourier_test.h"
#include <Arc_fourier.h>
#include "ArcFunction_Epicycloid.h"
#include "ArcFunction_feint_custom1.h"
#include "ArcFunction_feint_custom2.h"
#include <ArcFunction_scripted_base.h>


const float time_speed = 0.1f;

const short PATERN_MODE_hypotrochoid = 0;
const short PATERN_MODE_hypocycloid = 1;
const short PATERN_MODE_astroid = 2;
const short PATERN_MODE_fourier = 3;
const short PATERN_MODE_scripted = 4;
const short PATERN_MODE_epicycloid = 5;
const short PATERN_MODE_feint_custom1 = 6;
const short PATERN_MODE_feint_custom2 = 7;


class F_DamakuBase : public Feintgine::F_EmptyObject
{
public:
	F_DamakuBase();
	~F_DamakuBase();

	void update(float deltaTime);

	void setSprite(const Feintgine::F_Sprite & sprite);

	void setMode(int mode);

	glm::vec2 hypotrochoid(const glm::vec2 & pos, float a, float b, float c, float rad);

	glm::vec2 hypocycloid(const glm::vec2 & pos, float a, float b, float rad);

	glm::vec2 astroid(const glm::vec2 & pos, float a, float rad);

	glm::vec2 customized();

	glm::vec2 randomCosSin();

	void setInitialTime(float val_t);

	void genTrace(float interval, float lifeTime);

	void setTrace(float interval, float lifeTime);

	void clearTrace();

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void addArc(ArcFunction * arc);


	void changeCustomVal(float val);

	float reArc();


	glm::vec2 rotatePoint(const glm::vec2& pos, float angle);

	void setParam(std::vector<float> factors,float rad);

	void rotate(float val);

	void setAngle(float val);

	int getTotalFactors();

	void handleFourier(float deltaTime);

	void setDestinationMode(bool value);

protected:

	float m_traceLifeTime;
	float m_interval;

	float m_t;

	std::vector<F_DamakuLineTrace> m_traces;

	std::vector<ArcFunction *> m_arcs;

	ArcFunction_hypotrochoid arcHypotrochoid;
	
	ArcFunction_hypocycloid archypocycloid;

	ArcFunction_Epicycloid epicycloid;

	ArcFunction_feint_custom1 feint_custom1;

	ArcFunction_feint_custom2 feint_custom2;

//	ArcFunction_Fourier_test arcfourier;

	ArcFunction_scripted_base arcScripted;

	Arc_fourier arcfourier;

	float customVal = 400;

	int selectedMode = -1;

	glm::vec2 m_destination;

	glm::vec2 m_direction;

	float m_counter = 0;
	float m_tracerCounter = 0;

	bool m_destinationMode = false;

	//glm::vec2 m_destination;
	//glm::vec2 m_direction;
	float m_speed = 2.5f;

	float m_angle = 0;

	float m_rad;

};

