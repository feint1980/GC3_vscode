

#include "ClientHandler.h"



ClientHandler::ClientHandler()
{
    pw = "DavaiMachi";
}

ClientHandler::~ClientHandler()
{

}

void ClientHandler::init(const std::string & serverIP, unsigned int port)
{
    std::cout << "Init Client \n";

    // pw = serverPW;

    m_client = RakNet::RakPeerInterface::GetInstance();

    m_serverIP = serverIP;
    m_port = port;
    
    m_client->AllowConnectionResponseIPMigration(false);


    m_socketDescriptor = RakNet::SocketDescriptor(m_port + 1, 0);
    m_socketDescriptor.socketFamily = AF_INET;
    m_client->Startup(8, &m_socketDescriptor, 1);
    m_client->SetOccasionalPing(true);

    m_isInited = true;

}

void ClientHandler::connect()
{
    if(m_isInited)
    {
        RakNet::ConnectionAttemptResult car = m_client->Connect(m_serverIP.c_str(), m_port, pw.c_str(), pw.size());
        RakAssert(car == RakNet::CONNECTION_ATTEMPT_STARTED);
    
        std::cout << "IP address: \n";
        for(int i = 0; i < m_client->GetNumberOfAddresses(); i++)
        {
            printf("%i. %s\n", i+1, m_client->GetLocalIP(i));
        }
        std::cout << "init networking OK ! \n";
        std::cout << "GUID is : " << m_client->GetGuidFromSystemAddress (RakNet::UNASSIGNED_SYSTEM_ADDRESS).ToString() << "\n"; 
        // if(car != RakNet::CONNECTION_ATTEMPT_STARTED)
        // {
        //     m_isConnected = true;
        // }
        //m_isConnected = true;
        
    }
}