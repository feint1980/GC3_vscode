#include "ServerScriptingManager.h"

ServerScriptingManager::ServerScriptingManager()
{

}
ServerScriptingManager::~ServerScriptingManager()
{

}

void ServerScriptingManager::update(float deltaTime)
{

}

int ServerScriptingManager::handleCommand(RakNet::Packet *p)
{
    PacketCode requestCode = getSpecialRequestCode(p);
    switch (requestCode)
    {
        case PacketCode::LOGIN:
        {
            std::cout << "Login request found !!!\n";
            // todo : verify login
            std::string cData((const char*) p->data);
            
            return 12;
        }
        break;
        default :
            return 0;
        break;
    }
    return -22;
}