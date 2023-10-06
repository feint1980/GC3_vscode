#pragma once
#include <F_Sprite.h>
#include <SpriteBatch.h>
#include <feint_common.h>
#include <F_AnimatedObject.h>

enum SPELL_ID {
	Fantasy_Heaven = 1,
	Youkai_Seal,
	Fantasy_Orb,
	Demon_Binding_array,
	s_Yin_Yang_Orb,
	Purification_Rod,
	Demon_Binding_Circle,
	Yin_Yang_Sancitifier_Orb,
	Fantasy_Seal,

	// Marisa 
	Meteoric_Shower,
	Stardust_Reverie,
	Luminous_Strike,
	Orreries_Sun, 
	Master_Spark,
	Escape_Velocity,
	Gravity_Beat,
	Earthlight_Ray,
	Non_Directional_Laser,
	Blazing_Star,
	Final_Spark,
	Sure_Fire_Master_Spark



}; 

class SpellcardIcon 
{
public:	
	SpellcardIcon();
	~SpellcardIcon();

	void draw(Feintgine::SpriteBatch & spriteBatch);
	void init(const Feintgine::F_Sprite & sprite,
		const glm::vec2 dim, const Feintgine::Color & color);

	void setID(SPELL_ID id);

	SPELL_ID getID() const { return m_id; }

	void setPos(const glm::vec2 & pos,bool motion = true);
	void setColor(const Feintgine::Color color);
	void setScale(float scale);

	void update(float deltaTime);

	bool isMoving() const { return m_isMoving; }

	void setDepth(float depth);
	float getDepth() const { return m_depth; }

	glm::vec2 getTPos() const { return t_pos; }

	void setFocus(bool val);

	void setSignName(const std::wstring & signName);

	void setSpellName(const std::wstring & spellName);

	void setGrazeCost(int val);

	void setCD(float val);

	std::wstring getSignName() const { return m_signName; }

	std::wstring getSpellName() const { return m_spellcardName; }


	int getGrazeCost() const { return m_grazeCost; }

	float getCD() const { return m_cd; }

private : 

	glm::vec2 m_pos;
	glm::vec2 m_dim;
	glm::vec2 t_pos;
	glm::vec2 m_prevPos;
	glm::vec2 m_vector; 
	float m_scale = 1.0f;
	float m_targetScale;
	int transitionflag = 0;

	bool m_isFocus = false;
	bool m_previousReady = true;


	float m_depth = 40.0f;
	
	float m_animScale = 1.0f;

	bool m_isMoving = false;

	float scaleRate = 0.025f;

	Feintgine::F_AnimatedObject m_frame;

	Feintgine::F_Sprite m_sprite;
	Feintgine::Color m_color;

	std::wstring m_signName;
	std::wstring m_spellcardName;
	int m_grazeCost;
	float m_cd;

	SPELL_ID m_id;
};

