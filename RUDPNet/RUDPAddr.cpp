#include "StdAfx.h"
#include "RUDPAddr.h"

#include <winsock2.h>





RUDPAddr::RUDPAddr():
m_ulIP(0),
m_usPort(0)
{

}

RUDPAddr::RUDPAddr(const char* pszIP  , unsigned short usPort):
m_ulIP(0),
m_usPort(0)
{
	m_ulIP	 =	inet_addr(pszIP);
	m_usPort =	usPort;
}	

RUDPAddr::RUDPAddr(unsigned long ulIP  , unsigned short usPort):
m_ulIP(0),
m_usPort(0)
{
	m_ulIP	 =	ulIP;
	m_usPort =	usPort;
}

void
RUDPAddr::Reset()
{
	m_ulIP	 =	0;
	m_usPort =	0;
}

unsigned short	
RUDPAddr::GetPort() const
{
	return	m_usPort;
}

unsigned long	
RUDPAddr::GetIP() const
{
	return  m_ulIP;
}	

bool 
RUDPAddr::operator==(const RUDPAddr & r)
{
	if( m_ulIP == r.m_ulIP  &&  m_usPort == r.m_usPort )
		return true;
	return false;
}

RUDPAddr& 
RUDPAddr::operator=(const RUDPAddr& c)
{
	m_ulIP		=	c.GetIP(); 
	m_usPort	=	c.GetPort();

	return (*this);
}

bool
RUDPAddr::operator!=(const RUDPAddr & r)
{
	if( m_ulIP == r.m_ulIP  &&  m_usPort == r.m_usPort )
		return false;
	return true;
}