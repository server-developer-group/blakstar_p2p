#include "StdAfx.h"
#include "RUDPResender.h"
#include "SessionManager.h"
#include "RUDPNet.h"


#define MAX_RESEND_SLEEP_TIME				1




CRUDPResender::CRUDPResender()
{	
}

CRUDPResender::~CRUDPResender()
{	
}

unsigned int
CRUDPResender::Work( void* pParam )
{
	m_pNet = (CRUDPNet*)pParam;		
	
	CSessionManager* pMng = CSessionManager::GetInstance();

	while( 1 )
	{
		WaitForSingleObject( pMng->GetEvent() , INFINITE);		

		if( !m_pNet->IsActive() )
			break;
		
		//! 재전송할 것이 없으면 대기
		if(	!CSessionManager::GetInstance()->Resend(m_pNet) )
		{
			pMng->ResetEvent();
		}

		Sleep(MAX_RESEND_SLEEP_TIME);
	}

	return 0;
}