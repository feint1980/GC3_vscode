#pragma once

#include "F_PlayerRecorder.h"
#include <fstream>


class F_RecordPlayer
{
public:
	F_RecordPlayer();
	~F_RecordPlayer();

	void loadFromFile(const std::string & filePath);

private:

	std::vector<recordedState> m_recordedStates;
	std::vector<recordedAction> m_recordedActions;

};

