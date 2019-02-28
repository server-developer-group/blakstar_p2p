#ifndef _RUDP_RESENDER_H_
#define _RUDP_RESENDER_H_

#include "Thread.h"


//! 전방선언
class CRUDPNet;
class CRUDPSession;



/*! Reliable 데이타를 다시 재전송해주는 스레드
*  
*  @Version  2007. 5. 28
*
*  이호규
*/

class CRUDPResender : public IThread
{
private:
	CRUDPNet*	m_pNet;		

public:
	CRUDPResender();
	~CRUDPResender();

	unsigned int Work( void* pParam );

private:

};


#endif