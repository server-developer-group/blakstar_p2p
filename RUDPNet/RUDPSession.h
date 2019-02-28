#ifndef _RUDP_SESSION_H_ 
#define _RUDP_SESSION_H_

#include "RUDPPacket.h"
#include "RUDPStruct.h"
#include "RUDPAddr.h"
#include "Pooler.h"
#include "Lock.h"


//! stl
#include <deque>
using std::deque;




class CRUDPNet;
class RUDPPacket;





/*! 외부 클라이언트와 연결을 추상화한 클래스
*  
*  @Version  2007. 5. 23
*
*  이호규
*/


class CRUDPSession
{
	struct RUDPNotConfirmation
	{
		RUDPPacket* m_pPacket;
		RUDPHeader* m_pHeader;		

		RUDPNotConfirmation(RUDPPacket* pPacket , RUDPHeader* pHeader){m_pPacket=pPacket;m_pHeader=pHeader;}		
	};

private:
	deque<RUDPPacket*>			m_dequeRecv;
	deque<RUDPNotConfirmation>	m_dequeResend;

	Pooler<RUDPPacket>	m_plPacket;
	Pooler<RUDPHeader>	m_plHeader;

	unsigned long	m_ulRef;
	unsigned int	m_uResponse;
	unsigned char	m_chUID;
	unsigned char	m_chPrevUID;

	RUDPAddr	m_addr;	

	CLock	m_csRef;
	CLock	m_csRecvQueue;
	CLock	m_csPooler;	
	CLock	m_csResponse;
	CLock	m_csResendQueue;
	CLock	m_csUID;
	CLock	m_csHeader;

public:
	CRUDPSession();
	~CRUDPSession();

	void Reset();

	void AddRef();
	void RelRef();

	void SaveData(const char* pszBuffer , int ret);
	RUDPPacket* GetPacket();
	void PopPacket();

	void SetAddr(const RUDPAddr& addr);
	const RUDPAddr& GetAddr();

	bool IsExpired();
	void PushResendPacket(RUDPPacket* pPacket , RUDPHeader* pHeader);
	void PopResendPacket(const unsigned char UID);
	bool HasResendPacket();
	bool Resend(CRUDPNet* pNet);
	bool IsPrevUID(unsigned char UID);		

	RUDPPacket* AcquirePacket();
	void		ReleasePacket(RUDPPacket* pPacket);

	RUDPHeader* AcquireHeader();
	void		ReleaseHeader(RUDPHeader* pHeader);

	unsigned char AddUID();
	
};


#endif