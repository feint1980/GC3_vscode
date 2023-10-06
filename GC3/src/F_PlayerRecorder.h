#pragma once

#include "F_Player.h"
#include <iostream>
#include <fstream>
#include <string>

class F_PlayerRecorder
{
public:
	F_PlayerRecorder();
	~F_PlayerRecorder();


	void init(F_Player * player, double * engineTime);

	void update(float deltaTime);

	void writeRecord(const std::string & path);


private :


	F_Player * m_player; 

	unsigned long m_playerPrevState = 0;

	double * m_engineTime;

	std::vector<recordedState> m_recordedStates;
	std::vector<recordedAction> m_recordedActions;

};

