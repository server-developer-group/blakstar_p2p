#include "StdAfx.h"
#include "DeliveryManager.h"
#include "RUDPSession.h"


CDeliveryManager::CDeliveryManager()
{
	m_Event = WSACreateEvent();	
}

CDeliveryManager::~CDeliveryManager()
{
	WSACloseEvent(m_Event);	
}

bool
CDeliveryManager::IsEmpty()
{
	m_csDeliver.Lock();
	bool bEmpty = m_dequeDeliver.empty();
	m_csDeliver.UnLock();

	return bEmpty;
}

void
CDeliveryManager::PushDelivery(CRUDPSession* pSession)
{
	pSession->AddRef();

	m_csDeliver.Lock();
	m_dequeDeliver.push_back(pSession);
	m_csDeliver.UnLock();

	m_csEvent.Lock();
	SetEvent(m_Event);
	m_csEvent.UnLock();
}

void
CDeliveryManager::PopDelivery()
{
	m_csDeliver.Lock();

	CRUDPSession* pSession = m_dequeDeliver.front();
	pSession->RelRef();

	m_dequeDeliver.pop_front();

	m_csDeliver.UnLock();
}

CRUDPSession*
CDeliveryManager::front()
{
	m_csDeliver.Lock();
	CRUDPSession* pSession = m_dequeDeliver.front();
	m_csDeliver.UnLock();

	return pSession;
}

WSAEVENT
CDeliveryManager::GetEvent()
{
	m_csEvent.Lock();
	WSAEVENT event = m_Event;
	m_csEvent.UnLock();
	
	return event;
}

void
CDeliveryManager::ResetEvent()
{
	m_csEvent.Lock();
	WSAResetEvent(m_Event);
	m_csEvent.UnLock();
}

void	
CDeliveryManager::Stop()
{
	m_csEvent.Lock();
	SetEvent(m_Event);
	m_csEvent.UnLock();
}