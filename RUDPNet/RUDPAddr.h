#ifndef _RUDP_ADDR_H_
#define _RUDP_ADDR_H_

#include <stdio.h>



#pragma pack(1)




/*! IP와 port를 나타내는 클래스 - IP : network order , PORT : host order
*  
*  @Version  2007. 5. 22
*
*  이호규 
*/

class RUDPAddr
{
private:
	unsigned long	m_ulIP;
	unsigned short	m_usPort;		

public:		
	RUDPAddr();
	RUDPAddr(const char* pszIP , unsigned short usPort);
	RUDPAddr(unsigned long ulIP  , unsigned short usPort);

	void Reset();

	unsigned short GetPort() const;
	unsigned long  GetIP() const;

	friend bool operator < ( const RUDPAddr& l , const RUDPAddr& r )
	{
		bool bCompare = false;

		if( l.m_ulIP < r.m_ulIP )
			bCompare = true;
		else if( l.m_ulIP == r.m_ulIP && l.m_usPort < r.m_usPort )
			bCompare = true;

		return bCompare;		
	}

	bool operator==(const RUDPAddr & r);
	bool operator!=(const RUDPAddr & r);	

	RUDPAddr& operator=(const RUDPAddr& c);
};




#pragma pack()


#endif

