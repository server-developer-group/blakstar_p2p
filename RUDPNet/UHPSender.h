#ifndef _UHP_SENDER_H_
#define _UHP_SENDER_H_

#include "Thread.h"


//! 전방선언




/*! UHP의 패킷을 대상 클라이언트에게 일정시간 동안 send하는 스레드
*  
*  @Version  2007. 5. 31
*
*  이호규
*/

class CUHPSender : public IThread
{
private:	

public:
	CUHPSender();
	~CUHPSender();

	unsigned int Work( void* pParam );

private:

};


#endif