#ifndef _RUDP_DELIVER_H_
#define _RUDP_DELIVER_H_


#include "Thread.h"


//! 전방선언
class CRUDPNet;
class CRUDPSession;



/*! Network recv한 데이타를 처리하는 스레드
*  
*  @Version  2007. 5. 22
*
*  이호규
*/

class CRUDPDeliver : public IThread
{
private:
	CRUDPNet*	m_pNet;		

public:
	CRUDPDeliver();
	~CRUDPDeliver();

	unsigned int Work( void* pParam );

private:
	void OnProcess( CRUDPSession* pSession );
};


#endif