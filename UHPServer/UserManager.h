#pragma once

#include "RUDPAddr.h"


#include <map>
using std::map;



class CUser;
class RUDPPacket;


class CUserManager
{	
private:
	map<const RUDPAddr , CUser*>	m_mapUser;

public:
	~CUserManager();

	static CUserManager* GetInstance()
	{
		static CUserManager instance;
		return &instance;
	}

	void InsertNewUser( const RUDPAddr& addr );
	void ExchangeAddr();
	void Broadcast(RUDPPacket* pPacket);

private:
	CUserManager();

	void _ExchangeAddr(const RUDPAddr& addr, CUser* pUser);
};
