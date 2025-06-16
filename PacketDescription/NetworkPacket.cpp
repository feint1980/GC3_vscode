
#include "NetworkPacket.h"

unsigned char GetPacketIdentifier(RakNet::Packet *p,unsigned int index )
{
	//  index is 0 by default
	if (p==0)
	{
		return 255;
	}
	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
	{
		RakAssert(p->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
		return (unsigned char) p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time) + index];
	}
	else
	{
		return (unsigned char) p->data[index];
	}
}

PacketHeader getPacketHeader(RakNet::Packet *p)
{
	PacketHeader header;
	if (p==0)
	{
		return header;
	}
	RakNet::BitStream bs(p->data, p->length, false);

	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
	{
		RakAssert(p->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
		bs.IgnoreBits(sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
	}
	else 
	{
		bs.IgnoreBits(sizeof(RakNet::MessageID));
	}

	bs.Read(header.channel);
	bs.Read(header.request);

	return header;
}


// unsigned char GetPacketChanel(RakNet::Packet *p)
// {
// 	if (p==0)
// 		return 255;
// 	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
// 	{
// 		RakAssert(p->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
// 		return (unsigned char) p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time) + 1];
// 	}
// 	else
// 		return (unsigned char) p->data[1];
// }


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

std::string wrapRequest(unsigned short channel, unsigned char request,  const std::vector<std::string> & datas)
{
	std::string reTurnValue = "";
	reTurnValue.push_back(channel);
	reTurnValue.push_back(request);
	reTurnValue.push_back('|');
	for (int i = 0; i < datas.size(); i++)
	{
		reTurnValue.append(datas[i]);
		reTurnValue.push_back('|');
	}
	return reTurnValue;
}

std::string wrapResponse(unsigned short channel, unsigned short request, unsigned short value ,  const std::vector<std::string> & datas)
{
	std::string reTurnValue = "";
	reTurnValue.push_back(channel);
	reTurnValue.push_back(request);
	reTurnValue.push_back(value);
	reTurnValue.push_back('|');
	for (int i = 0; i < datas.size(); i++)
	{
		reTurnValue.append(datas[i]);
		reTurnValue.push_back('|');
	}
	return reTurnValue;
}