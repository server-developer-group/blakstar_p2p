#include "StdAfx.h"
#include "RUDPDeliver.h"

#include "RUDPSession.h"
#include "DeliveryManager.h"
#include "RUDPNet.h"
#include "SessionManager.h"

#include "assert_msg.h"



CRUDPDeliver::CRUDPDeliver()
{	
}

CRUDPDeliver::~CRUDPDeliver()
{	
}

unsigned int 
CRUDPDeliver::Work( void* pParam )
{
	m_pNet = (CRUDPNet*)pParam;	

	CDeliveryManager* pMng = CDeliveryManager::GetInstance();

	while( 1 )
	{
		WaitForSingleObject(pMng->GetEvent()  , 100);

		if( !m_pNet->IsActive() )
			break;

		while( !pMng->IsEmpty() )
		{
			CRUDPSession* pSession = pMng->front();

			//! 패킷 처리
			OnProcess( pSession );			

			pMng->PopDelivery();
		}	

		pMng->ResetEvent();

		//! 세션 검사
		CSessionManager::GetInstance()->Check();
	}

	return 0;
}

void
CRUDPDeliver::OnProcess( CRUDPSession* pSession )
{	
	RUDPPacket* pPacket = pSession->GetPacket();			

	if( NULL != pPacket)
	{
		//! 패킷 Receive 이벤트 호출
		m_pNet->OnReceive(pSession->GetAddr() , pPacket);

		pSession->PopPacket();
	}	
	else
	{
		assert_msg( pPacket != NULL , "OnProcess에서 패킷이 없음" );
	}
}