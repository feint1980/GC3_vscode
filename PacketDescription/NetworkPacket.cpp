
#include "NetworkPacket.h"




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