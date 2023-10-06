#include "F_RecordPlayer.h"



F_RecordPlayer::F_RecordPlayer()
{
}


F_RecordPlayer::~F_RecordPlayer()
{
}

void F_RecordPlayer::loadFromFile(const std::string & filePath)
{
	std::ifstream infile(filePath.c_str());

	std::string line;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		double  a, b,c;
		if (!(iss >> a >> b >> c))
		{ 
			break;
		}
		else
		{
			recordedState newRecord;
			newRecord.state = a;
			newRecord.startTime = b;
			//newRecord.endTime = c;
			m_recordedStates.push_back(newRecord);
		}

	}
	infile.close();

	for (int i = 0; i < m_recordedStates.size(); i++)
	{
		std::cout << m_recordedStates[i].state << "\n";
	}

}
