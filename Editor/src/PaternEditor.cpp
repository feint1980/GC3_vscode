#include "PaternEditor.h"



PaternEditor::PaternEditor()
{
}


PaternEditor::~PaternEditor()
{
}

void PaternEditor::init(Feintgine::GUI * gui,SpriteListHolder * spriteHolder)
{
	m_gui = gui;
	m_spriteListHolder = spriteHolder;

	m_damakuTest.init(Feintgine::SpriteManager::Instance()->getSprite("character/reimu_accessory_3.png"), glm::vec2(0)\
		, glm::vec2(1), Feintgine::Color(255, 255, 255, 255));
	m_damakuTest.setTrace(0.5, 2.0f);

	damaku_applySprite = static_cast<CEGUI::PushButton*>(m_gui->createWidget("TaharezLook/Button",
		glm::vec4(0.605, 0.28, 0.1, 0.04), glm::vec4(0), "damaku_applySprite"));
	damaku_applySprite->setText("Apply to Damaku");
		

	patern_combolist = static_cast<CEGUI::Combobox*>
		(m_gui->createWidget("TaharezLook/Combobox", glm::vec4(0.55, 0.4, 0.14, 0.22), glm::vec4(0), "patern_combolist"));


	patern_combolist->setSortingEnabled(false);
	patern_combolist->setReadOnly(true);

	int packetId = 0;
	const CEGUI::Image* sel_img = &CEGUI::ImageManager::getSingleton().get("TaharezLook/MultiListSelectionBrush");
	CEGUI::ListboxTextItem * item;
	item = new CEGUI::ListboxTextItem("hypotrochoid", packetId++);
	item->setSelectionBrushImage(sel_img);
	patern_combolist->addItem(item);

	item = new CEGUI::ListboxTextItem("hypocycloid", packetId++);
	item->setSelectionBrushImage(sel_img);
	patern_combolist->addItem(item);

	item = new CEGUI::ListboxTextItem("astroid", packetId++);
	item->setSelectionBrushImage(sel_img);
	patern_combolist->addItem(item);


	item = new CEGUI::ListboxTextItem("fourier", packetId++);
	item->setSelectionBrushImage(sel_img);
	patern_combolist->addItem(item);

	item = new CEGUI::ListboxTextItem("scripted", packetId++);
	item->setSelectionBrushImage(sel_img);
	patern_combolist->addItem(item);

	item = new CEGUI::ListboxTextItem("epicycloid", packetId++);
	item->setSelectionBrushImage(sel_img);
	patern_combolist->addItem(item);

	item = new CEGUI::ListboxTextItem("feint_custom1", packetId++);
	item->setSelectionBrushImage(sel_img);
	patern_combolist->addItem(item);

	item = new CEGUI::ListboxTextItem("feint_custom2", packetId++);
	item->setSelectionBrushImage(sel_img);
	patern_combolist->addItem(item);

	damaku_applySprite->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&PaternEditor::applySpriteToDamaku, this));

	patern_combolist->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted, 
		CEGUI::Event::Subscriber(&PaternEditor::onComboValueChanged, this));

	m_damakuTest.setMode(0);
	patern_combolist->setItemSelectState(patern_combolist->getListboxItemFromIndex(0),true);

	patern_factor_a = static_cast<CEGUI::Editbox *>
		(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.58, 0.46, 0.045, 0.03), 
			glm::vec4(0), "patern_factor_a"));

	patern_factor_b = static_cast<CEGUI::Editbox *>
		(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.58, 0.495, 0.045, 0.03),
			glm::vec4(0), "patern_factor_b"));

	patern_factor_c = static_cast<CEGUI::Editbox *>
		(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.58, 0.53, 0.045, 0.03),
			glm::vec4(0), "patern_factor_c"));

	patern_factor_d = static_cast<CEGUI::Editbox *>
		(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.58, 0.565, 0.045, 0.03),
			glm::vec4(0), "patern_factor_d"));

	patern_factor_r = static_cast<CEGUI::Editbox *>
		(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.58, 0.6, 0.045, 0.03),
			glm::vec4(0), "patern_factor_r"));


	patern_totalClone = static_cast<CEGUI::Editbox *>
		(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.63, 0.735, 0.045, 0.03),
			glm::vec4(0), "patern_totalClone")); 

	patern_traceTime = static_cast<CEGUI::Editbox *>
		(m_gui->createWidget("TaharezLook/Editbox", glm::vec4(0.63, 0.765, 0.045, 0.03),
			glm::vec4(0), "patern_traceTime"));


	patern_factor_a->setText("0");
	patern_factor_b->setText("0");
	patern_factor_c->setText("0");
	patern_factor_d->setText("0");
	patern_factor_r->setText("0");

	patern_traceTime->setText("2.0");

	patern_totalClone->setText(std::to_string(totalDamakuClone));

	patern_factor_a->subscribeEvent(CEGUI::Editbox::EventTextChanged,
		CEGUI::Event::Subscriber(&PaternEditor::onParamChanged, this));

	patern_factor_b->subscribeEvent(CEGUI::Editbox::EventTextChanged,
		CEGUI::Event::Subscriber(&PaternEditor::onParamChanged, this));

	patern_factor_c->subscribeEvent(CEGUI::Editbox::EventTextChanged,
		CEGUI::Event::Subscriber(&PaternEditor::onParamChanged, this));

	patern_factor_d->subscribeEvent(CEGUI::Editbox::EventTextChanged,
		CEGUI::Event::Subscriber(&PaternEditor::onParamChanged, this));

	patern_factor_r->subscribeEvent(CEGUI::Editbox::EventTextChanged,
		CEGUI::Event::Subscriber(&PaternEditor::onParamChanged, this));

	patern_totalClone->subscribeEvent(CEGUI::Editbox::EventTextChanged,
		CEGUI::Event::Subscriber(&PaternEditor::onTotalNumberChange, this));

	patern_traceTime->subscribeEvent(CEGUI::Editbox::EventTextChanged,
		CEGUI::Event::Subscriber(&PaternEditor::onTraceValueChange, this));


	patern_factor_a_label = static_cast<CEGUI::DefaultWindow*>
		(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.565, 0.463, 0.08, 0.02), glm::vec4(0), "patern_factor_a_label"));
	patern_factor_a_label->setText("a");
	patern_factor_a_label->setProperty("HorzFormatting", "LeftAligned");

	patern_factor_b_label = static_cast<CEGUI::DefaultWindow*>
		(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.565, 0.498, 0.08, 0.02), glm::vec4(0), "patern_factor_b_label"));
	patern_factor_b_label->setText("b");
	patern_factor_b_label->setProperty("HorzFormatting", "LeftAligned");

	patern_factor_c_label = static_cast<CEGUI::DefaultWindow*>
		(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.565, 0.533, 0.08, 0.02), glm::vec4(0), "patern_factor_c_label"));
	patern_factor_c_label->setText("c");
	patern_factor_c_label->setProperty("HorzFormatting", "LeftAligned");

	patern_factor_d_label = static_cast<CEGUI::DefaultWindow*>
		(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.565, 0.568, 0.08, 0.02), glm::vec4(0), "patern_factor_d_label"));
	patern_factor_d_label->setText("d");
	patern_factor_d_label->setProperty("HorzFormatting", "LeftAligned");

	patern_factor_r_label = static_cast<CEGUI::DefaultWindow*>
		(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.565, 0.603, 0.08, 0.02), glm::vec4(0), "patern_factor_r_label"));
	patern_factor_r_label->setText("r");
	patern_factor_r_label->setProperty("HorzFormatting", "LeftAligned");

	//0.568


	patern_totalClone_label = static_cast<CEGUI::DefaultWindow*>
		(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.565, 0.735, 0.08, 0.02), glm::vec4(0), "patern_totalClone_label"));
	patern_totalClone_label->setText("total danmaku");
	patern_totalClone_label->setProperty("HorzFormatting", "LeftAligned");

	patern_traceTime_label = static_cast<CEGUI::DefaultWindow*>
		(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.565, 0.765, 0.08, 0.02), glm::vec4(0), "patern_traceTime_label"));
	patern_traceTime_label->setText("trace time");
	patern_traceTime_label->setProperty("HorzFormatting", "LeftAligned");


	patern_destination_mode = static_cast<CEGUI::ToggleButton *>
		(m_gui->createWidget("TaharezLook/Checkbox", glm::vec4(0.645, 0.795, 0.05, 0.05),
			glm::vec4(0), "patern_destination_mode"));

	patern_destination_mode->subscribeEvent(CEGUI::ToggleButton::EventMouseClick,
		CEGUI::Event::Subscriber(&PaternEditor::onDestinationToggle, this));


	patern_destination_mode_label = static_cast<CEGUI::DefaultWindow*>
		(m_gui->createWidget("TaharezLook/Label", glm::vec4(0.565, 0.805, 0.08, 0.02), glm::vec4(0), "patern_destination_mode_label"));
	patern_destination_mode_label->setText("destination mode");
	patern_destination_mode_label->setProperty("HorzFormatting", "LeftAligned");

// 	patern_factor_a->setValidationString("\\d*");
// 	patern_factor_b->setValidationString("\\d*");
// 	patern_factor_c->setValidationString("\\d*");
// 	patern_factor_r->setValidationString("\\d*");

	patern_factor_a->setValidationString("^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+){0,10}$");
	patern_factor_b->setValidationString("^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+){0,10}$");
	patern_factor_c->setValidationString("^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+){0,10}$");
	patern_factor_d->setValidationString("^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+){0,10}$");
	patern_factor_r->setValidationString("^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+){0,10}$");


	patern_traceTime->setValidationString("^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+){0,10}$");


	patern_totalClone->setValidationString("^[0-9]*$"); // only int



	m_widgetFactors.emplace_back(patern_factor_a, patern_factor_a_label);
	m_widgetFactors.emplace_back(patern_factor_b, patern_factor_b_label);
	m_widgetFactors.emplace_back(patern_factor_c, patern_factor_c_label);
	m_widgetFactors.emplace_back(patern_factor_d, patern_factor_d_label);

	// init list 
	m_paternList = static_cast<CEGUI::MultiColumnList*>
		(m_gui->createWidget("TaharezLook/MultiColumnList",
			glm::vec4(0.78, 0.5, 0.15, 0.4), glm::vec4(0), "m_paternList"));

	m_paternList->addColumn("type", 1, cegui_reldim(0.6f));
	m_paternList->addColumn("ID", 2, cegui_reldim(0.15f));	
	m_paternList->addColumn("time", 3, cegui_reldim(0.25f));
	m_paternList->getHorzScrollbar()->hide();

	for (int i = 0; i < totalDamakuClone; i++)
	{
		F_DamakuBase t = m_damakuTest;
		t.setAngle(i * degreeToRad(360 / totalDamakuClone));
		m_damakuTests.push_back(t);

	}

}

void PaternEditor::draw(Feintgine::SpriteBatch & spriteBatch)
{
	//m_damakuTest.draw(spriteBatch);

	for (int i = 0; i < m_damakuTests.size(); i++)
	{
		m_damakuTests[i].draw(spriteBatch);
	}
}

void PaternEditor::update(float deltaTime)
{

	if (m_isPlay)
	{
		//m_damakuTest.update(deltaTime);

		for (int i = 0; i < m_damakuTests.size(); i++)
		{
			m_damakuTests[i].update(deltaTime);
		}
	}

	if (m_spriteListHolder)
	{
		if (m_spriteListHolder->getDisplaySample())
		{
			damaku_applySprite->setEnabled(true);
		}
		else
		{
			damaku_applySprite->setEnabled(false);
		}
	}
	

}

void PaternEditor::handleInput(Feintgine::InputManager & inputManager/*, SDL_Event & evnt*/)
{
	if (inputManager.isKeyPressed(SDLK_SPACE))
	{
		togglePlay();
	}
	if (inputManager.isKeyPressed(SDLK_BACKSPACE))
	{
// 		m_damakuTest.setInitialTime(0);
// 		m_damakuTest.clearTrace();
// 		//m_damakuTest.update(1);
// 		m_damakuTest.setPos(glm::vec2(0));
// 		m_damakuTest.setAngle(0);

		for (int i = 0; i < m_damakuTests.size();i++)
		{
			m_damakuTests[i].setInitialTime(0);
			m_damakuTests[i].clearTrace();
			m_damakuTests[i].setPos(glm::vec2(0));
			m_damakuTests[i].setAngle((i) * degreeToRad(360 / m_damakuTests.size()));
		}
	}
	if (inputManager.isKeyDown(SDLK_RIGHT))
	{
		//m_damakuTest.rotate(0.01f);
		//m_damakuTest.changeCustomVal(1);
	}
	if (inputManager.isKeyDown(SDLK_LEFT))
	{
		//m_damakuTest.rotate(-0.01f);
		//m_damakuTest.changeCustomVal(-1);
	}

// 	if (inputManager.isKeyPressed(SDLK_UP))
// 	{
// 		m_damakuTest.rotate()
// 	}
// 	if (inputManager.isKeyPressed(SDLK_LEFT))
// 	{
// 		m_damakuTest.changeCustomVal(-1);
// 	}


}

void PaternEditor::show(bool value)
{
	if (value)
	{
		damaku_applySprite->show();
		patern_combolist->show();
		m_paternList->show();
		patern_factor_a->show();
		patern_factor_b->show();
		patern_factor_c->show();
		patern_factor_c->show();
		patern_factor_r->show();
		patern_totalClone->show();
		patern_traceTime->show();
		patern_factor_a_label->show();
		patern_factor_b_label->show();
		patern_factor_c_label->show();
		patern_factor_d_label->show();
		patern_factor_r_label->show();
		patern_totalClone_label->show();
		patern_traceTime_label->show();
		patern_destination_mode->show();
		patern_destination_mode_label->show();

	}
	else
	{
		damaku_applySprite->hide();
		patern_combolist->hide();
		m_paternList->hide();
		patern_factor_a->hide();
		patern_factor_a->hide();
		patern_factor_b->hide();
		patern_factor_c->hide();
		patern_factor_d->hide();
		patern_factor_r->hide();
		patern_totalClone->hide();
		patern_traceTime->hide();
		patern_factor_a_label->hide();
		patern_factor_b_label->hide();
		patern_factor_c_label->hide();
		patern_factor_d_label->hide();
		patern_factor_r_label->hide();
		patern_totalClone_label->hide();
		patern_traceTime_label->hide();
		patern_destination_mode->hide();
		patern_destination_mode_label->hide();
	}
}

void PaternEditor::togglePlay()
{
	if (m_isPlay)
	{
		m_isPlay = false;
	}
	else
	{
		m_isPlay = true;
	}

}

bool PaternEditor::applySpriteToDamaku(const CEGUI::EventArgs &e)
{
	//m_damakuTest.setSprite(m_spriteListHolder->getDisplaySample()->getSprite());
	for (int i = 0; i < m_damakuTests.size(); i++)
	{
		m_damakuTests[i].setSprite(m_spriteListHolder->getDisplaySample()->getSprite());
	}

	return true;
}


bool PaternEditor::onComboValueChanged(const CEGUI::EventArgs &e)
{
	m_damakuTest.setMode(patern_combolist->getItemIndex(patern_combolist->getSelectedItem()));
	for (int i = 0; i < m_damakuTests.size(); i++)
	{
		m_damakuTests[i].setMode(patern_combolist->getItemIndex(patern_combolist->getSelectedItem()));
	}
	resetParams();
	return true;
}

bool PaternEditor::onParamChanged(const CEGUI::EventArgs &e)
{

	if (patern_factor_a->getText().size() > 0 && patern_factor_b->getText().size() > 0 \
		&& patern_factor_c->getText().size() > 0 && patern_factor_r->getText().size() > 0 \
		&& patern_factor_d->getText().size() > 0)
	{
		std::vector<float> factors;
		factors.push_back(std::stoi(patern_factor_a->getText().c_str()));
		factors.push_back(std::stoi(patern_factor_b->getText().c_str()));
		factors.push_back(std::stoi(patern_factor_c->getText().c_str()));
		factors.push_back(std::stoi(patern_factor_d->getText().c_str()));
		m_damakuTest.setParam(factors, std::stoi(patern_factor_r->getText().c_str()));
		for (int i = 0; i < m_damakuTests.size(); i++)
		{
			m_damakuTests[i].setParam(factors, std::stoi(patern_factor_r->getText().c_str()));
		}
	}
	return true;
}

bool PaternEditor::onTotalNumberChange(const CEGUI::EventArgs &e)
{
	for (int i = 0; i < m_damakuTests.size(); i++)
	{
		m_damakuTests.erase(m_damakuTests.begin() + i);

	}
	m_damakuTests.clear();

	totalDamakuClone = std::stoi(patern_totalClone->getText().c_str());

	for (int i = 0; i < totalDamakuClone; i++)
	{
		F_DamakuBase t = m_damakuTest;
		t.setAngle(i * degreeToRad(360 / totalDamakuClone));
		//t.setTrace(0.5f, std::stof(patern_traceTime->getText().c_str()));	
		m_damakuTests.push_back(t);

	}

	for (int i = 0; i < m_damakuTests.size(); i++)
	{
		m_damakuTests[i].setTrace(0.5f, std::stof(patern_traceTime->getText().c_str()));
	}

	return true;
}

bool PaternEditor::onTraceValueChange(const CEGUI::EventArgs &e)
{
	for (int i = 0; i < m_damakuTests.size(); i++)
	{
		m_damakuTests[i].setTrace(0.5f, std::stof(patern_traceTime->getText().c_str()));
	}
	//m_damakuTest.setTrace(0.5f, std::stof(patern_traceTime->getText().c_str()));

	return true;
}

void PaternEditor::setSpriteHolder(SpriteListHolder * holder)
{
	m_spriteListHolder = holder;
}

bool PaternEditor::onDestinationToggle(const CEGUI::EventArgs &e)
{
	for (int i = 0; i < m_damakuTests.size(); i++)
	{
		m_damakuTests[i].setDestinationMode(patern_destination_mode->isSelected());
	}

	return true;
}

void PaternEditor::resetParams()
{
	for (int i = 0; i < m_widgetFactors.size(); i++)
	{
		if (m_widgetFactors[i].editBox && m_widgetFactors[i].editLabel)
		{
			//m_widgetFactors[i].editBox->disable();
			m_widgetFactors[i].editBox->hide();
			m_widgetFactors[i].editLabel->hide();
		}
		
	}

	for (int i = 0; i < m_damakuTest.getTotalFactors(); i++)
	{
		m_widgetFactors[i].editBox->show();
		m_widgetFactors[i].editLabel->show();
	}
}

