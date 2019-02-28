#include "StdAfx.h"
#include "RUDPPacket.h"


RUDPPacket::RUDPPacket()
{
	PacketData.reserve(64);
	Reset();
}

RUDPPacket::RUDPPacket(const unsigned int uPacketID):
m_uPacketID(uPacketID)
{
	RUDPPacket();
}

void 
RUDPPacket::Reset()
{
	m_uPacketID = 0;	
	PacketData.clear();	
}

void 
RUDPPacket::operator=(const RUDPPacket& packet)
{
	//! 해더 복사
	m_uPacketID =	packet.m_uPacketID;

	//! 바디 복사
	PacketData	 =	packet.PacketData;
}		

void
RUDPPacket::ProcessStream( const char* pszBuffer , int ret )
{
	memcpy( &m_uPacketID , pszBuffer , sizeof(unsigned int) );

	//! 바디 담기
	PacketData.append( pszBuffer + sizeof(unsigned int) , 
					  ret - sizeof(unsigned int) );
}

void 
RUDPPacket::MakeStream(string& strData)
{
	strData.append((const char*)&m_uPacketID , sizeof(unsigned int));
	strData += PacketData;
}

int 
RUDPPacket::GetPacketSize()
{
	return sizeof(unsigned int) + PacketData.size();
}