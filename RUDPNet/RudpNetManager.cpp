#include "StdAfx.h"

#include "RUDPNet.h"
#include "RUDPReceiver.h"
#include "RUDPDeliver.h"
#include "RUDPResender.h"

#include "RudpNetManager.h"
#include "SessionManager.h"
#include "DeliveryManager.h"



CRudpNetManager* 
CRudpNetManager::GetInstance()
{
	static CRudpNetManager instance;
	return &instance;
}


CRudpNetManager::CRudpNetManager():
m_pRUDPNet(NULL),
m_pReceiver(NULL),
m_pDeliver(NULL),
m_pResender(NULL)
{
}

CRudpNetManager::~CRudpNetManager()
{	
}

void 
CRudpNetManager::Startup(IRUDPListener* pListener , unsigned short usPort)
{
	if( NULL == m_pRUDPNet && 
		NULL == m_pReceiver &&
		NULL == m_pDeliver && 
		NULL == m_pResender)
	{
		m_pRUDPNet = new CRUDPNet(pListener , usPort);	

		//! 싱클톤 미리 생성
		CSessionManager::GetInstance();
		CDeliveryManager::GetInstance();

		StartThread();			
	}
}

void
CRudpNetManager::StartThread()
{
	m_pReceiver = new CThread<CRUDPReceiver>;
	m_pReceiver->run(m_pRUDPNet);

	m_pDeliver = new CThread<CRUDPDeliver>;
	m_pDeliver->run(m_pRUDPNet);	

	m_pResender = new CThread<CRUDPResender>;
	m_pResender->run(m_pRUDPNet);
}

//! 순서 중요- m_pRUDPNet이 제일 나중에 삭제되야함
void
CRudpNetManager::Cleanup()
{
	//! RUDP Net 중지
	m_pRUDPNet->StopNet();

	//! 리소스 제거
	if( NULL != m_pReceiver )
	{
		m_pReceiver->join();
		delete m_pReceiver;
		m_pReceiver= NULL;
	}

	if( NULL != m_pDeliver )
	{
		m_pDeliver->join();
		delete m_pDeliver;
		m_pDeliver= NULL;
	}

	if( NULL != m_pResender )
	{
		m_pResender->join();
		delete m_pResender;
		m_pResender= NULL;
	}

	if( NULL != m_pRUDPNet )
	{
		delete m_pRUDPNet;
		m_pRUDPNet= NULL;
	}	
}

void
CRudpNetManager::SendPacket(const RUDPAddr& addr , RUDPPacket* pPacket , bool bReliable)
{
	m_pRUDPNet->SendPacket(addr , pPacket , bReliable);
}

bool 
CRudpNetManager::StartUHP(vector<RUDPAddr>& v_addr)
{
	return m_pRUDPNet->StartUHP(v_addr);
}

unsigned long 
CRudpNetManager::GetIP()
{
	return m_pRUDPNet->GetIP();
}

unsigned short 
CRudpNetManager::GetPort()
{
	return m_pRUDPNet->GetPort();
}