#include "F_SpellcardBase.h"



F_SpellcardBase::F_SpellcardBase()
{
	m_depth = 30;
	textOffset = glm::vec2(-150, -50);
}


F_SpellcardBase::~F_SpellcardBase()
{

}




void F_SpellcardBase::init(const Feintgine::GLTexture & texture,
	const glm::vec2 & pos, const glm::vec2 & intendPos,
	const glm::vec2 & dim, const Feintgine::Color & color, float depth, bool isLeft /*= true */)
{
	m_texture = texture;
	m_pos = pos;
	m_intendedPos = intendPos;
	m_dim = dim;
	m_isLeft = isLeft;
	m_depth = depth;
	m_color = color;
	m_firstDistance = glm::distance(m_pos, m_intendedPos);

}


void F_SpellcardBase::loadDesciption(const std::string & signName,
	const std::string & spellName, int id)
{
	m_signName = feint_common::Instance()->convertStringtoWstring(signName);
	m_spellName = feint_common::Instance()->convertStringtoWstring(spellName);

	std::wstring totalString = colorCode(id) + m_signName;
	totalString.append(L"[colour='FFFF0000'] \"");
	totalString.append(m_spellName);
	totalString.append(L"\"");
	m_cegui_text.setText(totalString);
	float rasSize = 0.012f;
	rasSize *= m_signName.size() + m_spellName.size() + 2;
	//m_cegui_text.setDim(glm::vec2(rasSize, 0.1f));

}



void F_SpellcardBase::loadDesciption(const std::wstring & signName,
	const std::wstring & spellName, int id)
{
	m_signName = signName;
	m_spellName = spellName;
	std::wstring totalString = colorCode(id) + m_signName;
	totalString.append(L"[colour='FFFF0000'] \"");
	totalString.append(m_spellName);
	totalString.append(L"\"");
	m_cegui_text.setText(totalString);
	float rasSize = 0.012f;
	rasSize *= m_signName.size() + m_spellName.size() + 2;
	//m_cegui_text.setDim(glm::vec2(rasSize, 0.1f));
	//std::cout << "called id " << (int)id << "\n";
}

void F_SpellcardBase::registerText(Feintgine::GUI & gui, const std::string & name, const glm::vec2 & pos, const glm::vec2 & dim)
{
	m_cegui_text.init(name.c_str(), pos);
	// m_cegui_text.setText("sajdsajhdashdsa");
	//m_cegui_text.setAlignment(5);
}

void F_SpellcardBase::loadSound(Feintgine::AudioEngine * audioEngine,
	const std::string & filePath)
{
	m_audioEngine = audioEngine;
	m_audioEngine->loadSoundEffect(filePath);

}

void F_SpellcardBase::update(float deltaTime)
{
	
	if (m_isAlive)
	{
		float t_distance = glm::distance(m_pos, m_intendedPos);
		glm::vec2 t_direction = m_intendedPos - m_pos;
		m_pos += t_direction * (t_distance / m_firstDistance) *0.5f  * deltaTime;
		//glm::vec2 t_textOffset = textOffset;
		//t_textOffset.x -= m_cegui_text.getDim().d_width.d_offset * 2.0f ;
		m_cegui_text.setPos(glm::vec2(m_pos + textOffset));
	}
	m_lifeTime -= m_lifeTimeRate * deltaTime;
	if (m_lifeTime < 0)
	{
		m_isAlive = false;
		m_cegui_text.setPos(glm::vec2(-1000));
	}
}

void F_SpellcardBase::draw(Feintgine::SpriteBatch & spriteBatch)
{

	const glm::vec4 uvrect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 desRect;
	desRect.x = m_pos.x - m_dim.x / 2.0f;
	desRect.y = m_pos.y - m_dim.y / 2.0f;
	desRect.z = m_dim.x;
	desRect.w = m_dim.y;
	spriteBatch.draw(desRect, uvrect, m_texture.id, 4000, m_color, 0.0f);

}

void F_SpellcardBase::setTextPos(const glm::vec2 & pos)
{
	m_cegui_text.setPos(pos);
}

void F_SpellcardBase::drawText(const Feintgine::Camera2D & camera, TextRenderer & renderer)
{
	renderer.renderText(camera,(m_signName),
		m_pos + textOffset,
		m_color, 1.0f, ALIGN_FT_RIGHT);
	renderer.renderText(camera, (m_spellName),
		m_pos + textOffset2,
		Feintgine::Color(255,0,0,255), 1.0f, ALIGN_FT_RIGHT);
}

std::wstring F_SpellcardBase::colorCode(int id)
{
	std::wstring returnVal;
		
	switch (id)
	{
	case 1:
		//L"Fantasy Heaven";
		returnVal = L"[colour='FFFFFFFF']";
		break;
	case 2:
		//L"Youkai Seal";
		returnVal = L"[colour='FFFFFFFF']";
		break;
	case 3:
		//L"Fantasy Orbs";
		returnVal = L"[colour='FF000000']";
		break;
	case 4: 
		// L"Demon Binding Array";
		returnVal = L"[colour='FF000000']";
		break;
	case 5:
		// L"Yin-Yang Orb";
		returnVal = L"[colour='FFC0D0FFF']";
		break;
	case 6:
		//L"Purification Rod";
		returnVal = L"[colour='FFFFFFFF']";
		break;
	case 7:
		//L"Demon Binding Circle";
		returnVal = L"[colour='FF000000']";
		break;
	case 8:
		//L"Yin-Yang Sanctifier Orb";
		returnVal = L"[colour='FFF0F000']";
		break;
	case 9:
		//returnVal = L"Fantasy Seal";
		returnVal = L"[colour='FF000000']";
		break;

		// Marisa

	case 10:
		
		returnVal = L"[colour='FF00FFC7']";
		break;

	case 11:
		//returnVal = L"Stardust Reverie"; 00E5FF
		returnVal = L"[colour='FF00E5FF']";
		break;

	case 12:
		//returnVal = L"Luminous Strike"; F9FF5B
		returnVal = L"[colour='FFF9FF5B']";
		break;

	case 13:
		//returnVal = L"Orreries Sun"; EF14FF
		returnVal = L"[colour='FFEF14FF']";
		break;

	case 14:
	//	returnVal = L"Master Spark"; FDFFF9
		returnVal = L"[colour='FF000000']";
		break;

	case 15:
		//returnVal = L"Escape Velocity"; 2E00FF
		returnVal = L"[colour='FF2E00FF']";
		break;

	case 16:
		//returnVal = L"Gravity Beat"; 8496FF
		returnVal = L"[colour='FF8496FF']";
		break;

	case 17:
	//	returnVal = L"Earthlight Ray"; 00E1FF
		returnVal = L"[colour='FF00E1FF']";
		break;

	case 18:
		//returnVal = L"Non-Directional Laser"; FF7F00
		returnVal = L"[colour='FFFF7F00']";
		break;

	case 19:
		//returnVal = L"Blazing Star"; FF1D00
		returnVal = L"[colour='FFFF1D00']";
		break;

	case 20:
		//returnVal = L"Final Spark"; FF00DC
		returnVal = L"[colour='FFFF00DC']";
		break;

	case 21:
		//returnVal = L"Sure-Fire Master Spark";  FF00DC
		returnVal = L"[colour='FFFF00DC']";
		break;


	default:
		break;
	}

	return returnVal;

}

