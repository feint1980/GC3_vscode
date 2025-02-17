
#include "NetworkPacket.h"

unsigned char GetPacketIdentifier(RakNet::Packet *p)
{
	if (p==0)
		return 255;

	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
	{
		RakAssert(p->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
		return (unsigned char) p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];
	}
	else
		return (unsigned char) p->data[0];
}

PacketCode getSpecialRequestCode(RakNet::Packet *p)
{
 //   std::cout << "getSpecialRequestCode called \n";

    std::string cData((const char*) p->data);
    if(cData.find("|LOGIN_REQUEST|") != std::string::npos)
    {
        if(cData.find("|LOGIN_END_REQUEST|") != std::string::npos)
        {
            return PacketCode::LOGIN;
        }
        //std::cout << "Login request found !!!\n";
        //proceed to verify login

        return PacketCode::INVALID;
    }
    
    //std::cout << "Not a request, normal message : \n";
    return PacketCode::INVALID;
}
std::string combine2Package(const std::string & type,const std::string & id, const std::string & pw)
{

    std::string returnVal = "|" + type + "_REQUEST|" + id + "|" + pw + "|" + type + "_END_REQUEST|";

    //std::string returnVal = "|LOGIN_REQUEST|" + id + "|" + pw + "|END_REQUEST|";
    return returnVal;
}

std::string combine3Package(const std::string & type,const std::string & id, const std::string & pw, const std::string & key)
{

    std::string returnVal = "|" + type + "_REQUEST|" + id + "|" + pw + "|" + key + "|" + type + "_END_REQUEST|";

    //std::string returnVal = "|LOGIN_REQUEST|" + id + "|" + pw + "|END_REQUEST|";  
    return returnVal;
}

