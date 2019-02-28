#include "StdAfx.h"
#include "User.h"
#include "RUDPNetManager.h"

CUser::CUser(const RUDPAddr& addr):
m_addr(addr)
{
}

CUser::~CUser()
{
}

void 
CUser::SendPacket(RUDPPacket* pPacket)
{
	CRudpNetManager::GetInstance()->SendPacket(m_addr , pPacket , true);
}