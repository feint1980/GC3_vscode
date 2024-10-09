

#include "FileTransferHost.h"




void FileTransferHost::init(unsigned int port)
{

	if(testInet6)
	{
		m_tcp.Start(port,1,-99999,AF_INET6);
		
	}	
	else
	{
		m_tcp.Start(port,1,-9999,AF_INET);
	}
	m_tcp.AttachPlugin(&m_flt);

      //std::cout << "|=========================================|\n";
        std::cout << "|        File Transfer OK                 |\n";
}

void FileTransferHost::sendFile(const std::string & filePath)
{

	fileList.Clear();
	m_flt.AddCallback(&testFileListProgress);
	m_flt.StartIncrementalReadThreads(1);
	
	file = filePath.c_str();
	unsigned int fileLength = GetFileLength(file.C_String());
	if (fileLength==0)
	{
		printf("Test file %s not found.\n", file.C_String());

		return ;
	}
	fileList.AddFile(file.C_String(), file.C_String(), 0, fileLength, fileLength, FileListNodeContext(0,0,0,0), true);
	printf("File added.\n");
	isDownloading = true;

}

void FileTransferHost::update()
{
	if(isDownloading)
	{
		m_packet = m_tcp.Receive();
		RakNet::SystemAddress sa;
		sa = m_tcp.HasNewIncomingConnection();
		if(sa != RakNet::UNASSIGNED_SYSTEM_ADDRESS)
		{
			m_flt.Send(&fileList, 0, sa,0,HIGH_PRIORITY,0, &incrementalReadInterface, 2000 * 1024);
			std::cout << "transfer send \n";
		}
		m_tcp.DeallocatePacket(m_packet);	
	}
			
}

