
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


RequestCode getSpecialRequestCode(RakNet::Packet *p)
{
 //   std::cout << "getSpecialRequestCode called \n";

    std::string cData((const char*) p->data);
    if(cData.find("|LOGIN_REQUEST|") != std::string::npos)
    {
        //std::cout << "Login request found !!!\n";
        //proceed to verify login
        return RequestCode::login;
    }
    
    //std::cout << "Not a request, normal message : \n";
    return RequestCode::invalid;
}
std::string combineLoginPackage(const std::string & id, const std::string & pw)
{
    std::string returnVal = "|LOGIN_REQUEST|" + id + "|" + pw + "|END_REQUEST|";
    return returnVal;
}