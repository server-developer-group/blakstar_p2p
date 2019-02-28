#include "StdAfx.h"
#include "UHPSender.h"
#include "RUDPNet.h"



CUHPSender::CUHPSender()
{
}

CUHPSender::~CUHPSender()
{
}

unsigned int
CUHPSender::Work( void* pParam )
{
	CRUDPNet* pNet = (CRUDPNet*)pParam;	

	pNet->SendUHP();

	pNet->EndUHP();

	return 0;
}