#ifndef _RUDP_NET_MANAGER_H_
#define _RUDP_NET_MANAGER_H_


//! stl
#include <vector>
using std::vector;



//! 전방 선언
class CRUDPReceiver;
class CRUDPDeliver;
class CRUDPNet;
class IRUDPListener;
class RUDPPacket;
class RUDPAddr;
class CRUDPResender;

template <typename OperationClass> class CThread;




#define DEFAULT_PORT					9190





/*! RUDP의 facade 클래스 - 외부에서 사용할 RUDP의 인터페이스를 제공하는 클래스
*  
*  @Version  2007. 5. 22
*
*  이호규
*/

class CRudpNetManager
{
private:
	CRUDPNet*	m_pRUDPNet;

	CThread<CRUDPReceiver>*	m_pReceiver;
	CThread<CRUDPDeliver>*	m_pDeliver;	
	CThread<CRUDPResender>* m_pResender;

public:
	static CRudpNetManager* GetInstance();	
	~CRudpNetManager();

	void Startup(IRUDPListener* pListener , unsigned short usPort = DEFAULT_PORT);
	void Cleanup();

	void SendPacket(const RUDPAddr& addr , RUDPPacket* pPacket , bool bReliable = false);

	bool StartUHP(vector<RUDPAddr>& v_addr);

	unsigned long  GetIP();
	unsigned short GetPort();

public:
	CRudpNetManager();

private:

	void StartThread();
	
};

#endif