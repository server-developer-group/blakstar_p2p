#ifndef _RUDP_PACKET_H_
#define _RUDP_PACKET_H_



//! stl
#include <string>
using std::string;






/*! P2P에 사용되는 패킷 클래스
*  
*  @Version  2007. 5.23
*
*  이호규 
*/

class RUDPPacket
{
public:
	unsigned int m_uPacketID;	

	//! 패킷 data
	string	 PacketData;

public:
	RUDPPacket();
	RUDPPacket(const unsigned int uPacketID);	

	void Reset();	

	void operator=(const RUDPPacket& packet);	

	void ProcessStream( const char* pszBuffer , int ret );

	void MakeStream(string& strData);

	int  GetPacketSize();
};


#endif