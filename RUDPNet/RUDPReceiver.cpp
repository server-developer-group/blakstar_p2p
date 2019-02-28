#include "StdAfx.h"
#include "RUDPReceiver.h"

#include "RUDPNet.h"

CRUDPReceiver::CRUDPReceiver()
{
}

CRUDPReceiver::~CRUDPReceiver()
{
}

unsigned int 
CRUDPReceiver::Work( void* pParam )
{
	m_pNet = (CRUDPNet*)pParam;		

	m_pNet->WaitForRecvEvent();

	return 0;
}
