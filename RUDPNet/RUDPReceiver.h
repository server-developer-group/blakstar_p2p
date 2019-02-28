#ifndef _RUDP_RECEIVER_H_
#define _RUDP_RECEIVER_H_

#include "Thread.h"


//! 전방선언
class CRUDPNet;



/*! Network의 data를 recv 함
*  
*  @Version  2007. 5. 22
*
*  이호규
*/


class CRUDPReceiver : public IThread
{
private:
	CRUDPNet*	m_pNet;	

public:
	CRUDPReceiver();
	~CRUDPReceiver();

	unsigned int Work( void* pParam );
};


#endif
