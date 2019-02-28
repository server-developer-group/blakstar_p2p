#ifndef _RUDP_NET_H_
#define _RUDP_NET_H_

#include <winsock2.h>

#include "NetAdapter.h"
#include "RUDPListener.h"
#include "Lock.h"


#include <string>
#include <vector>

using std::string;
using std::vector;

class RUDPAddr;
class CRUDPSession;
class RUDPPacket;
struct RUDPHeader;
class CUHPSender;


template <typename OperationClass> class CThread;



/*! RUDP의 모든 자원과 기능을 관리하는 클래스 
*  
*  @Version  2007. 5. 22
*
*  이호규
*/

class CRUDPNet
{
private:
	CNetAdapter		m_Adapter;
	string			m_strRead;

	SOCKET			m_hSocket;
	SOCKADDR_IN		m_SockAddr;
	SOCKADDR_IN		m_FromAddr;	
	OVERLAPPED		m_rOL;

	WSAEVENT		m_rEvent;	
	IRUDPListener*	m_pListener;

	CThread<CUHPSender>*	m_pUHPSender;
	vector<RUDPAddr>		m_vUHPAddr;

	bool	m_bActive;	
	bool	m_bUHPStart;

	DWORD	m_dwSeedKey[32];

	CLock	m_csActive;	
	CLock	m_csSocket;		
	CLock	m_csUHPAddr;
	CLock	m_csUHPStart;

public:
	CRUDPNet(IRUDPListener* pListener , unsigned short usPort);
	~CRUDPNet();

	void WaitForRecvEvent();	

	void SendPacket(const RUDPAddr& addr , RUDPPacket* pPacket , bool bReliable = false);
	void _SendPacket(const RUDPAddr& addr , RUDPPacket* pPacket , RUDPHeader* pHeader);	

	void OnReceive( const RUDPAddr& addr , const RUDPPacket* pPacket);

	bool IsActive();
	void StopNet();		

	bool StartUHP(vector<RUDPAddr>& v_addr);
	void SendUHP();
	void EndUHP();	

	unsigned long  GetIP();
	unsigned short GetPort();

private:
	void CreateSocket(unsigned short usPort);	
	void EnumNetworkEvents();
	void RecvData();
	void _RecvData(const RUDPAddr& addr , int dwTransferBytes);
	void DeliverData( CRUDPSession* pSession , const char* pszBuffer , int ret );
	void RecvOL();	
	void ProcessData(const char* pszBuffer , CRUDPSession* pSession , const RUDPHeader* pHeader ,int usSrcSize);
	void AsyncSendto(const RUDPAddr& addr , string& strSend);
	void SendConfirmation(const RUDPAddr& addr , const RUDPHeader* pHeader);
	void PunchUHP(const RUDPAddr& addr);
	bool IsUHPStart();
	int  Compress(string& strDummy , string& strSend);
	void Encrypt(int nBytes , unsigned short usSrcSize , string& strDummy , string& stream);
};

#endif