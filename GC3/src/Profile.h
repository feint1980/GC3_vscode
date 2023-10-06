// #pragma once
// #include <string>
// #include <iostream>
// #include <glm/glm.hpp>
// #include <serverData.pb.h>
// #include <feint_common.h>
// #include <ClientSocket.h>
// using namespace std;



// class Profile
// {
// public:

// 	Profile() {

// 	}
// 	~Profile() {

// 	}

// 	static Profile *Instance()
// 	{
// 		if (p_Instance == 0)
// 		{
// 			p_Instance = new Profile;
// 			return p_Instance;
// 		}
// 		return p_Instance;
// 	}
// 	string getName() const { return player_name; }
// 	string getLocation() const { return player_location; }
// 	glm::vec2 getPos() const { return player_pos; }

// 	void setPlayerIDSession(const std::string & ID);

// 	void passSocket(ClientSocket * sock);


	
// 	ClientSocket * getParsedSock() const { return m_socket; }


// private: 

// 	static Profile *p_Instance;

// 	//std::string 

// 	ClientSocket *m_socket = nullptr;

// 	string player_name;
// 	glm::vec2 player_pos;
// 	string player_location;


// };