#pragma once

#include "RUDPAddr.h"


class RUDPPacket;

class CUser
{
private:
	const RUDPAddr m_addr;

public:
	CUser(const RUDPAddr& addr);
	~CUser();

	void SendPacket(RUDPPacket* pPacket);
};
