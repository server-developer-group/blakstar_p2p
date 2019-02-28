// UHPClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "RUDPNetManager.h"
#include "RUDPListener.h"
#include "RUDPAddr.h"
#include "RUDPPacket.h"


#include "PacketMacro.h"
#include "assert_msg.h"

#include <vector>
using std::vector;


using std::cout;
using std::endl;



#define MAX_SERVER_IP_SIZE					16


char				g_szServerIP[MAX_SERVER_IP_SIZE];
int					g_ServerPortNum = 0;
vector<RUDPAddr>	g_vAddr;


RUDP_NO_DATA(1 , RUDP_PORT_REGISTER)
RUDP_MULTI_DATA(2 , RUDP_EXCHANGE_ADDR , RUDPAddr)
RUDP_NO_DATA(3 , RUDP_UHP_START)

struct Hello
{
	char szData[32];
};

RUDP_DATA(4 , RUDP_HELLO , Hello)




class MyListener : public IRUDPListener
{
public:
	void OnReceive(const RUDPAddr& addr , const RUDPPacket* pPacket)
	{
		switch( pPacket->m_uPacketID )
		{
		case RUDP_EXCHANGE_ADDR:
			{
				cout << "Received network addr of other UHPClient~!! " << endl;

				CPacketData<RUDP_EXCHANGE_ADDR>::GetMultiDataFromStream(pPacket , g_vAddr);

				vector<RUDPAddr>::iterator where = g_vAddr.begin();
				while( where != g_vAddr.end() )
				{
					RUDPAddr& addr  = *where;
					cout << addr.GetIP() << " : " << addr.GetPort() << endl;
					++where;
				}				
			}
			break;

		case RUDP_UHP_START:
			{
				cout << "UHP Start~!!" << endl;

				//! UHP 시작
				if( !CRudpNetManager::GetInstance()->StartUHP(g_vAddr) )
				{
					cout << "UHP Start 실퍠" << endl;
				}
				else
				{
					cout << "UDP Hole Punching Success~!!" << endl;
				}
			}
			break;

		case RUDP_HELLO:
			{
				Hello data;
				CPacketData<RUDP_HELLO>::GetDataFromStream(pPacket , data);

				cout << data.szData << " - " << addr.GetIP() << " : " << addr.GetPort() << endl;
			}
			break;
		}
	}

	void OnUHPSuccess(const RUDPAddr& addr)
	{
		cout << "OnUHPSuccess : " << addr.GetIP() << " : " << addr.GetPort() << endl;
	}

	void OnUHPTimeout(const RUDPAddr& addr)
	{
		cout << "OnUHPTimeout : " << addr.GetIP() << " : " << addr.GetPort() << endl;
	}
};


void GetServerInfo(RUDPAddr &server_addr)
{
	//! server ip 얻기
	cout << "Input Server IP : " << endl;
	gets(g_szServerIP);	

	//! server port 얻기
	cout << "Input Server Port : " << endl;

	char szNum[64];
	gets(szNum);
	g_ServerPortNum = atoi(szNum);

	server_addr = RUDPAddr(g_szServerIP , g_ServerPortNum);
}


int _tmain(int argc, _TCHAR* argv[])
{
	char szNum[64];

	RUDPAddr server_addr;
	GetServerInfo(server_addr);
	
	cout << "Input Port Num : " << endl;
	gets(szNum);
	int nNum = atoi(szNum);
	
	if( 0 != nNum)
	{
		//! RUDPNet Start~!!
		MyListener listener;
		CRudpNetManager::GetInstance()->Startup(&listener , nNum);

		while(1)
		{
			cout << "r for Registration , s for UHP Start , h for sending Hello to other UHPClient" << endl;
			char ch = getchar();

			if( 'e' == ch )
				break;

			switch(ch)
			{
			case 'r':
				{
					//! 패킷 전송
					RUDPPacket packet;
					packet.m_uPacketID = RUDP_PORT_REGISTER;					

					CRudpNetManager::GetInstance()->SendPacket(server_addr , &packet , true);	
				}
				break;

			case 's':
				{
					RUDPPacket packet;
					packet.m_uPacketID = RUDP_UHP_START;					

					CRudpNetManager::GetInstance()->SendPacket(server_addr , &packet , true);						
				}
				break;

			case 'h':
				{
					RUDPPacket packet;
					packet.m_uPacketID = RUDP_HELLO;					

					Hello data;
					sprintf( data.szData , "Hello~!! done" );

					CPacketData<RUDP_HELLO>::SetDataIntoStream(&packet , data);

					vector<RUDPAddr>::iterator where = g_vAddr.begin();
					while( where != g_vAddr.end() )
					{
						CRudpNetManager::GetInstance()->SendPacket(*where , &packet , true);
						++where;
					}					
				}
				break;				
			}

		}		

		//! RDUP 해제
		CRudpNetManager::GetInstance()->Cleanup();	
	}	

	return 0;
}

