#include "F_DamakuBase.h"



F_DamakuBase::F_DamakuBase()
{
	
	std::vector<float> factors;
	factors.push_back(6.5);
	factors.push_back(1);
	factors.push_back(3);
	arcHypotrochoid.init(50, factors);
	m_rad = 100;
	arcfourier.init();
	arcfourier.calculateFourier();

	arcScripted.clearScript();
	arcScripted.addScript(40, 4, 1);
	arcScripted.addScript(70, 3, 2);
	arcScripted.addScript(100, -5, 3);
	arcScripted.addScript(130, 1, 4);
	arcScripted.addScript(160, 4, 2);
	arcScripted.addScript(190, -5, 1);
	arcScripted.addScript(100, 3, 1);
	arcScripted.addScript(200, 1, 1);
	arcScripted.addScript(100, 4, 1);
	arcScripted.addScript(50, 4, 1);
	arcScripted.addScript(10, 4, 1);
}


F_DamakuBase::~F_DamakuBase()
{
}


void F_DamakuBase::update(float deltaTime)
{
	
	m_t += time_speed * deltaTime;
	m_counter += 1 * deltaTime;
	glm::vec2 t_data = glm::vec2(0);
	switch (selectedMode)
	{
	case PATERN_MODE_hypotrochoid:
	{
		
		t_data = arcHypotrochoid.getValue(m_t);
		t_data = rotatePoint(t_data, m_angle);
		break;
	}

	case PATERN_MODE_hypocycloid:
		//t_data = hypocycloid(m_pos, 6.5f, 1, 50);
		t_data = archypocycloid.getValue(m_t);
		t_data = rotatePoint(t_data, m_angle);
		break;

	case PATERN_MODE_astroid:
		//t_data = randomCosSin();
		t_data = customized();
		t_data = rotatePoint(t_data, m_angle);
		break;
	case PATERN_MODE_fourier :
		arcfourier.update(deltaTime);
		m_destination = rotatePoint(arcfourier.getPos(),m_angle);
		
		break;
	case PATERN_MODE_scripted:
		arcScripted.update(deltaTime);
		m_destination = rotatePoint(arcScripted.getData(),m_angle);
		break;

	case PATERN_MODE_epicycloid:
		t_data = epicycloid.getValue(m_t);
		t_data = rotatePoint(t_data, m_angle);

		break;
	case PATERN_MODE_feint_custom1:
		t_data = feint_custom1.getValue(m_t);
		t_data = rotatePoint(t_data, m_angle);
		break;
	case PATERN_MODE_feint_custom2:
		t_data = feint_custom2.getValue(m_t);
		t_data = rotatePoint(t_data, m_angle);
		break;
	default:
		break;
	}
	if (selectedMode == PATERN_MODE_fourier || selectedMode == PATERN_MODE_scripted)
	{
		handleFourier(deltaTime);
	}
	else
	{
		
		if (m_destinationMode)
		{


			m_destination = t_data;

			float distance = glm::distance(m_pos, m_destination);
			if (distance < 1.0f)
			{
				m_pos = t_data;
				//std::cout << "reach";
			}
			else
			{
				m_direction = glm::normalize(m_destination - m_pos);
				m_pos += m_direction * m_speed;
			}
		}
		else
		{
			m_pos = t_data;
		}
	}
	
	for (int i = 0; i < m_traces.size(); i++)
	{
		m_traces[i].update(deltaTime);
		if (!m_traces[i].isAlive())
		{
			m_traces.erase(m_traces.begin() + i);
		}
	}

	genTrace(m_interval, m_traceLifeTime);
}

glm::vec2 F_DamakuBase::astroid(const glm::vec2 & pos, float a, float rad)
{
	glm::vec2 val;

	val.x = (a * pow(cos(m_t), 3)) *rad;
	val.y = (a * pow(sin(m_t), 3)) *rad;

	return val;
}



glm::vec2 F_DamakuBase::hypocycloid(const glm::vec2 & pos, float a, float b, float rad)
{
	glm::vec2 val;

	val.x = ((a - b) * cos(m_t) + (b * cos((a / b - 1)*m_t))) * rad;
	val.y = ((a - b) * sin(m_t) - (b * cos((a / b - 1)*m_t))) * rad;

	return val;
}

glm::vec2 F_DamakuBase::hypotrochoid(const glm::vec2 & pos, float a, float b, float c, float rad)
{
	glm::vec2 val;
	val.x = ((a - b) * cos(m_t) + (c * cos((a / b - 1)*m_t))) *rad;
	val.y = ((a - b) * sin(m_t) - (c * sin((a / b - 1)*m_t))) *rad;
	return val;
}

void F_DamakuBase::setInitialTime(float val_t)
{
	m_t = val_t;
	arcScripted.setTime(val_t);
}

void F_DamakuBase::genTrace(float interval, float lifeTime)
{
	if (m_tracerCounter < m_counter)
	{
		F_DamakuLineTrace bg;
		bg.init(m_sprite,
			m_pos, m_scale, Feintgine::Color(255, 0, 255, 200));
		bg.setLifeTime(lifeTime);
		m_traces.push_back(bg);
		m_tracerCounter = m_counter + interval;

	}
}

void F_DamakuBase::draw(Feintgine::SpriteBatch & spriteBatch)
{

	Feintgine::F_EmptyObject::draw(spriteBatch);
	for (int i = 0; i < m_traces.size(); i++)
	{
		m_traces[i].draw(spriteBatch);
	}
}

void F_DamakuBase::clearTrace()
{
	m_traces.clear();
}

void F_DamakuBase::setTrace(float interval, float lifeTime)
{
	m_interval = interval;
	m_traceLifeTime = lifeTime;
}

void F_DamakuBase::setSprite(const Feintgine::F_Sprite & sprite)
{
	m_sprite = sprite;
}

void F_DamakuBase::setMode(int mode)
{
	selectedMode = mode;
}

void F_DamakuBase::addArc(ArcFunction * arc)
{
	m_arcs.push_back(arc);
}



glm::vec2 F_DamakuBase::customized()
{
	glm::vec2 val;
	float rad = pow(customVal * sin(m_t), 2);
	float t_rad2 = pow(customVal * cos(m_t), 2);
	val.x = (reArc() * customVal) * cos((m_t));
	val.y = (reArc() * customVal) * sin((m_t));

	return val;
}

void F_DamakuBase::changeCustomVal(float val)
{
	customVal += val;
}

float F_DamakuBase::reArc()
{
	float returnVal;

	float t_limit = 5;
	float minLimit = -2.0;


	return returnVal = -minLimit / pow(t_limit, 2) * pow(m_t, 2) + 2 * minLimit / t_limit * m_t;
}

glm::vec2 F_DamakuBase::randomCosSin()
{
	glm::vec2 val;
	//float rad = m_rad;


	float a = sqrt(m_t) - (3 * m_t )+ 2;

	val.x = ((cos(m_t)) * m_rad) ;
	val.y = ((sin(a)) * m_rad);

	return val;
}

int F_DamakuBase::getTotalFactors()
{

	switch (selectedMode)
	{
		case PATERN_MODE_hypotrochoid:
		{
			return arcHypotrochoid.getFactorCount();
		}
		case PATERN_MODE_hypocycloid:
		{
			return archypocycloid.getFactorCount();
		}
		case PATERN_MODE_epicycloid:
		{
			return epicycloid.getFactorCount();
		}
		case PATERN_MODE_feint_custom1:
		{
			return feint_custom1.getFactorCount();
		}
		case PATERN_MODE_feint_custom2:
		{
			return feint_custom2.getFactorCount();
		}
		default:
		{
			return -1;
		}
	}
}

void F_DamakuBase::setParam(std::vector<float> factors,float rad)
{

	switch (selectedMode)
	{
	case PATERN_MODE_hypotrochoid:
	{
		arcHypotrochoid.init(rad, factors);
		break;
	}
	case PATERN_MODE_hypocycloid:
	{
		archypocycloid.init(rad, factors);
		break;
	}
	case PATERN_MODE_fourier:
	{
		arcfourier.init();
		arcfourier.calculateFourier();
		break;
	}
	case PATERN_MODE_epicycloid:
	{
		epicycloid.init(rad,factors);
		break;

	}
	case PATERN_MODE_feint_custom1:
	{

		feint_custom1.init(rad, factors);
		break;
	}
	case PATERN_MODE_feint_custom2:
	{

		feint_custom2.init(rad, factors);
		break;

	}
	case PATERN_MODE_scripted :
	{
	
		//std::cout << "init called \n";
		break;

	}
	default:
	{
		break;
	}
	}

	
}

glm::vec2 F_DamakuBase::rotatePoint(const glm::vec2& pos, float angle)
{
	glm::vec2 newv;
	newv.x = pos.x * cos(angle) - pos.y * sin(angle);
	newv.y = pos.x * sin(angle) + pos.y * cos(angle);
	return newv;
}

void F_DamakuBase::rotate(float val)
{
	m_angle += val;
}

void F_DamakuBase::setAngle(float val)
{
	m_angle = val;
}

void F_DamakuBase::handleFourier(float deltaTime)
{
	float t_distance = glm::length(m_destination - m_pos);
	m_direction = m_destination - m_pos;

	if (t_distance > 5.0f)
	{
		m_pos += m_direction  *0.1f  * deltaTime;
	}

}

void F_DamakuBase::setDestinationMode(bool value)
{
	m_destinationMode = value;
}
