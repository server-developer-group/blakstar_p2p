#include "StdAfx.h"
#include "UserManager.h"
#include "User.h"
#include "RUDPPacket.h"
#include "RUDPPacketDef.h"


CUserManager::CUserManager()
{
}

CUserManager::~CUserManager()
{
	map<const RUDPAddr , CUser*>::iterator where = m_mapUser.begin();
	while( where != m_mapUser.end() )
	{
		delete where->second;
		++where;
	}
}

void 
CUserManager::InsertNewUser( const RUDPAddr& addr )
{
	m_mapUser.insert( map<const RUDPAddr , CUser*>::value_type( addr , new CUser(addr) ) );
}

void 
CUserManager::ExchangeAddr()
{
	map<const RUDPAddr , CUser*>::iterator where = m_mapUser.begin();
	while( where != m_mapUser.end() )
	{
		_ExchangeAddr(where->first, where->second);
		++where;
	}
}

void
CUserManager::_ExchangeAddr(const RUDPAddr& addr, CUser* pUser)
{
	vector<RUDPAddr*>	v_data;

	map<const RUDPAddr , CUser*>::iterator where = m_mapUser.begin();
	while( where != m_mapUser.end() )
	{
		RUDPAddr& temp = const_cast<RUDPAddr&>(where->first);

		if( temp != addr )
		{
			v_data.push_back(&temp);
		}

		++where;
	}

	RUDPPacket packet;
	packet.m_uPacketID = RUDP_EXCHANGE_ADDR;

	CPacketData<RUDP_EXCHANGE_ADDR>::SetMultiDataIntoStream(&packet , v_data);

	pUser->SendPacket(&packet);
}

void
CUserManager::Broadcast(RUDPPacket* pPacket)
{
	map<const RUDPAddr , CUser*>::iterator where = m_mapUser.begin();
	while( where != m_mapUser.end() )
	{
		CUser* pUser = where->second;
		pUser->SendPacket(pPacket);

		++where;
	}
}