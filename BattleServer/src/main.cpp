
#include <RakNet/MessageIdentifiers.h>

#include <RakNet/RakPeerInterface.h>
#include <RakNet/RakNetStatistics.h>
#include <RakNet/RakNetTypes.h>
#include <RakNet/BitStream.h>
#include <RakNet/RakSleep.h>
#include <RakNet/PacketLogger.h>
#include <RakNet/Gets.h>
#include <RakNet/Kbhit.h>
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <stdlib.h>

#include <stdio.h>
#include <string.h>
//#include "Gets.h"

#include "BattleMain.h"

#include <iostream>
    

int wmain(int argc, wchar_t const *argv[])
{
    std::cout << "Battle Server Start ...\n";
    int index = 1;
    std::string ip = "127.0.0.1"; // main server ip
    std::string name = "BS_TE";

    if(argc >= 2)
    {
        std::cout << "argv[1] : " << argv[1] << "\n";
        std::wstring tArgv1 = std::wstring(argv[1]);
        std::wcout << "tArgv1 : " << tArgv1 << "\n";
        index = std::stoi(tArgv1.c_str());
        // ip = argv[2];
    }
    std::cout << "server index : " << index << "\n";
    name = name + "_" + std::to_string(index);

    BattleMain server;
    std::cout << "Davai \n";
    server.setName(name);   
    server.init("FFX2","DavaiMachi", 1123 + index, 121,ip); // 1 + 100 + 20 (spare room)

    server.run();

	return 0;
}