#include "ClientDownloadHandler.h"
//#include "Functions.cpp"




void ClientDownloadHandler::download()
{

	m_fileList.Clear();	
	unsigned int fileLength = GetFileLength(file.C_String());
	m_fileList.AddFile(file.C_String(), file.C_String(), 0, fileLength, fileLength, FileListNodeContext(0,0,0,0), true);
	// Wait for the connection
	printf("File added.\n");
	RakSleep(100); 
	m_IsDownload = true;
	m_IsUpdate = true;
	int maxConnection = 1;
	int threadPriority = -99999;
	isDownload = true;

}

void ClientDownloadHandler::init(const std::string & ip, unsigned int port, unsigned int maxConnection, int threadPriority)
{

	m_ip = ip;
	m_port = port;
	
	m_tcp.AttachPlugin(&m_flt);
	
	std::cout << "!!!!! Init Download Handler OK !!!!!! \n";	
	if(testInet6)
	{
		m_tcp.Start(m_port + 1,maxConnection,threadPriority, AF_INET6);
		m_tcp.Connect("::1", m_port, false, AF_INET6);
		std::cout << "init INET6\n";
	}
	{
		m_tcp.Start(m_port+1,maxConnection,threadPriority, AF_INET);
		m_tcp.Connect(m_ip.c_str(), m_port, false, AF_INET);
		std::cout << "init INET \n";
	}
		
}

void ClientDownloadHandler::downloading()
{
 
	if(m_IsDownload)
	{
		RakNet::SystemAddress sa;
		sa = m_tcp.HasCompletedConnectionAttempt();
		if(sa != RakNet::UNASSIGNED_SYSTEM_ADDRESS)
		{
			//std::cout << "system address " << sa << "\n";
			m_flt.SetupReceive(&m_testCB, false,sa);
			std::cout << "downloading ... !!!!!!!!!!!!!!!!!!!!!!!!!!! \n";
			m_IsDownload = false;
			RakSleep(30);
		}
	}	
	
	
}
void ClientDownloadHandler::update()
{
	
	if(isDownload)	
	{
		m_packet = m_tcp.Receive();
		/*if(m_packet)
		{
			std::cout << "packet has data \n";
		}*/
		m_tcp.DeallocatePacket(m_packet);
		RakSleep(40);
	}
	
}

