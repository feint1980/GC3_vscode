



#ifndef _CLIENT_DOWNLOAD_HANDLER_H_
#define _CLIENT_DOWNLOAD_HANDLER_H_


//Raknet::RakString file;

#include "RakPeerInterface.h"
#include "FileListTransfer.h"
#include "RakSleep.h"

#include "MessageIdentifiers.h"
#include "FileListTransferCBInterface.h"
#include "FileOperations.h"
#include "SuperFastHash.h"
#include "RakAssert.h"
#include "BitStream.h"
#include "IncrementalReadInterface.h"
#include "PacketizedTCP.h"
#include "SocketLayer.h"
#include <stdio.h>
#include "Gets.h"
#include "RakString.h"

#include <string>

#include <iostream>




static RakNet::RakString file = "/root/download/master.zip";
static RakNet::RakString fileCopy = "/root/download/master.zip_download";
static bool isDownload = false;
class TestCB : public RakNet::FileListTransferCBInterface
{
public:
	bool OnFile(
		OnFileStruct *onFileStruct)
	{
		printf("OnFile: %i. (100%%) %i/%i %s %ib / %ib\n",
			onFileStruct->setID,
			onFileStruct->fileIndex+1,
			onFileStruct->numberOfFilesInThisSet,
			onFileStruct->fileName,
			onFileStruct->byteLengthOfThisFile,
			onFileStruct->byteLengthOfThisSet);

		std::cout << "mod \n";

		FILE *fp = fopen(fileCopy.C_String(), "wb");
		fwrite(onFileStruct->fileData, onFileStruct->byteLengthOfThisFile, 1, fp);
		fclose(fp);

		// Make sure it worked


		unsigned int hash1 = SuperFastHashFile(file.C_String());
		if (RakNet::BitStream::DoEndianSwap())
			RakNet::BitStream::ReverseBytesInPlace((unsigned char*) &hash1, sizeof(hash1));
		unsigned int hash2 = SuperFastHashFile(fileCopy.C_String());
		if (RakNet::BitStream::DoEndianSwap())
			RakNet::BitStream::ReverseBytesInPlace((unsigned char*) &hash2, sizeof(hash2));
		RakAssert(hash1==hash2);

		// Return true to have RakNet delete the memory allocated to hold this file.
		// False if you hold onto the memory, and plan to delete it yourself later


		return true;
	}

	virtual void OnFileProgress(FileProgressStruct *fps)
	{
		printf("OnFileProgress: %i partCount=%i partTotal=%i (%i%%) %i/%i %s %ib/%ib %ib/%ib total\n",
			fps->onFileStruct->setID,
			fps->partCount, fps->partTotal, (int) (100.0*(double)fps->onFileStruct->bytesDownloadedForThisFile/(double)fps->onFileStruct->byteLengthOfThisFile),
			fps->onFileStruct->fileIndex+1,
			fps->onFileStruct->numberOfFilesInThisSet,
			fps->onFileStruct->fileName,
			fps->onFileStruct->bytesDownloadedForThisFile,
			fps->onFileStruct->byteLengthOfThisFile,
			fps->onFileStruct->bytesDownloadedForThisSet,
			fps->onFileStruct->byteLengthOfThisSet,
			fps->firstDataChunk);
	}

	virtual bool OnDownloadComplete(DownloadCompleteStruct *dcs)
	{
		printf("Download complete.\n");

		// Returning false automatically deallocates the automatically allocated handler that was created by DirectoryDeltaTransfer
		isDownload = false;

		return false;
	}

};



class TestFileListProgress : public RakNet::FileListProgress
{
	virtual void OnFilePush(const char *fileName, unsigned int fileLengthBytes, unsigned int offset,
 unsigned int bytesBeingSent, bool done, RakNet::SystemAddress targetSystem, unsigned short setID)
	{
		printf("Sending %s bytes=%i offset=%i\n", fileName, bytesBeingSent, offset);
	}

	virtual void OnFilePushesComplete( RakNet::SystemAddress systemAddress, unsigned short setID )
	{
		char str[32];
		systemAddress.ToString(true, (char*) str);
		RAKNET_DEBUG_PRINTF("File pushes complete to %s\n", str);	
	}
	
	virtual void OnSendAborted( RakNet::SystemAddress systemAddress )
	{
		char str[32];
		systemAddress.ToString(true, (char*) str);
		RAKNET_DEBUG_PRINTF("Send aborted to %s\n", str);	
	}



};

static TestFileListProgress testFileListProgress;

static TestCB m_testCB;


class ClientDownloadHandler
{
public:
	
	void init(const std::string & ip, unsigned int port, unsigned int maxConnection, int threadPriority);

	void download();
	void update();
	void downloading();
private:

	RakNet::RakString m_file;		
	RakNet::FileListTransfer m_flt;
	// Use TCP 
	RakNet::PacketizedTCP m_tcp;

	const bool testInet6 = false;
	std::string m_ip;
	RakNet::FileList m_fileList;	
	
	RakNet::IncrementalReadInterface m_incrementalReadInterface;
	
	RakNet::Packet * m_packet;
   	unsigned int m_port;		
	bool m_IsUpdate = false;
	bool m_IsDownload = false;
	RakNet::SystemAddress m_sa;
	//TestCB m_testCB;
	
};


#endif 






