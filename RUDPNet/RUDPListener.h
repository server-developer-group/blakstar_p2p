#ifndef _RUDP_LISTENER_H_
#define _RUDP_LISTENER_H_


class RUDPAddr;
class RUDPPacket;

class IRUDPListener
{
public:
	virtual void OnReceive( const RUDPAddr& addr , const RUDPPacket* pPacket) = 0;

	//! 후크 함수
	virtual void OnUHPSuccess(const RUDPAddr& addr){}
	virtual void OnUHPTimeout(const RUDPAddr& addr){}
};

#endif