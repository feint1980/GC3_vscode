#pragma once
#include "LivingLabel.h"

const float FADE_TIME = 0.05f;
class TitleLabel : public LivingLabel
{
public:
	TitleLabel();
	~TitleLabel();

	void init(const glm::vec2 & pos, const std::wstring & firstSign, const std::wstring & secondSign , 
		const Feintgine::Color & color, const Feintgine::Color & color2);
	void setLifeTime(float value);
	virtual void update(float deltaTime) override;

	void draw(TextRenderer * textRenderer) override;
	
private :
	bool startCount = false;
	bool isFade = false;
	std::wstring m_subMesage;
	Feintgine::Color m_color2;

};

