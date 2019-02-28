#ifndef _TEMPLATE_THREAD_
#define _TEMPLATE_THREAD_

//! 필요해더
#include "windows.h"
#include "process.h"

#include <vector>

using std::vector;



/*! 스레드로 만들어주는 클래스
*  
*  @Version  2005. 5. 12
*
*  Template인자로 받은 클래스를 스레드 function으로 구동시켜준다.
*/


template <typename OperationClass>
class CThread
{
protected:
	HANDLE			m_hThread;
	vector<void*>	v;	

public:
	CThread():m_hThread(INVALID_HANDLE_VALUE)
	{}

	virtual ~CThread(){}

	//! 스레드 함수 종료를 기다림
	void join(BOOL bWaitAll = TRUE , DWORD dwMillisec = INFINITE){
		if( m_hThread != INVALID_HANDLE_VALUE )
			WaitForSingleObject(m_hThread , dwMillisec);
	}


	//! 스레드 시작
	void run(void* pParam)
	{
		if( m_hThread == INVALID_HANDLE_VALUE)
		{
			unsigned int nFlag = 0 , nThreadId = 0;

			v.push_back(pParam);
			v.push_back((void*)this);

			m_hThread = (HANDLE)_beginthreadex(NULL , 0 , CThread::ThreadAddress, (void*)&v,
				nFlag , &nThreadId);		
		}		
	}	

	//! util
	HANDLE GetThreadHandle(){return m_hThread;}


private:

	//! 템플릿 인자 클래스의 멤버함수를 호출
	static unsigned int __stdcall ThreadAddress(void* pData){		
		OperationClass	op;
		IThread *thread = (IThread*)&op;

		vector<void*>* pV = (vector<void*>*)pData;

		//! 인자 구별
		void* pParam	=	(*pV)[0];
		CThread<OperationClass>* pThread	=	(CThread<OperationClass>*)(*pV)[1];					

		thread->Work( pParam );

		return 0;
	}


	
};





/*! 스레드 인터페이스 - 

1.스레드에서 쓰일 클래스는 이것을 상속받아야한다.

2. void work를 오버라이딩한다
*/


class IThread
{	
public:	
	virtual unsigned int Work( void* pParam ) = 0;	
};



#endif