#include "F_PlayerRecorder.h"



F_PlayerRecorder::F_PlayerRecorder()
{
}


F_PlayerRecorder::~F_PlayerRecorder()
{
}

void F_PlayerRecorder::init(F_Player * player, double * engineTime)
{
	m_player = player;
	m_engineTime = engineTime;
}

void F_PlayerRecorder::update(float deltaTime)
{
	if (m_player)
	{
	
		if (m_player->getPlayerState() != m_playerPrevState)
		{
			m_playerPrevState = m_player->getPlayerState();

			recordedState newState;
// 			if (m_recordedStates.size() > 0)
// 			{
// 				m_recordedStates[m_recordedStates.size() - 1].endTime = *m_engineTime;
// 			}

			newState.startTime = *m_engineTime;
			newState.state = m_player->getPlayerState();
			m_recordedStates.push_back(newState);

		}
		if (m_player->getPlayerAction() != 0)
		{
			recordedAction newAction;
			newAction.tAction = m_player->getPlayerAction();
			newAction.time = *m_engineTime;
			m_recordedActions.push_back(newAction);
		}
		

	}
}

void F_PlayerRecorder::writeRecord(const std::string & path)
{
// 	if (m_recordedStates.size() > 0)
// 	{
// 		m_recordedStates[m_recordedStates.size() - 1].endTime = *m_engineTime;
// 	}
	std::ofstream myfile(path.c_str());

	if (myfile.is_open())
	{
		std::string str;
		for (int i = 0; i < m_recordedStates.size(); i++)
		{
			str = "";
			str += std::to_string(m_recordedStates[i].state);
			str += " " + std::to_string(m_recordedStates[i].startTime); /*+ " " + std::to_string(m_recordedStates[i].endTime);*/
			myfile << str <<"\n";
		}
		myfile << "\n";
		for (int i = 0; i < m_recordedActions.size(); i++)
		{
			str = "";
			str += std::to_string(m_recordedActions[i].tAction);
			str += " " + std::to_string(m_recordedActions[i].time);
			myfile << str << "\n";
		}
		myfile << "\n";
		std::cout << "written to " << path.c_str() << "\n";
		myfile.close();
	}
	else std::cerr << "Unable to open file";

}
