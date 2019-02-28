// UHPServer.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include "RUDPNetManager.h"
#include "RUDPListener.h"
#include "RUDPAddr.h"
#include "RUDPPacket.h"


#include "UserManager.h"
#include "RUDPPacketDef.h"

#include "assert_msg.h"

using std::cout;
using std::endl;







class MyListener : public IRUDPListener
{
public:
	void OnReceive(const RUDPAddr& addr , const RUDPPacket* pPacket)
	{
		switch( pPacket->m_uPacketID )
		{
		case RUDP_PORT_REGISTER:
			{
				cout << "Registration for " << addr.GetIP() << " : " << addr.GetPort() << endl;
				CUserManager::GetInstance()->InsertNewUser( addr );
			}
			break;

		case RUDP_UHP_START:
			{
				cout << "Relaying UHP Start to the other UHPClient" << endl;

				RUDPPacket packet(RUDP_UHP_START);
				CUserManager::GetInstance()->Broadcast(&packet);
			}
			break;
		}
	}
};



int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Input Port Num : " << endl;

	char szNum[64];
	gets(szNum);

	int nNum = atoi(szNum);

	if( 0 != nNum)
	{
		//! RUDPNet Start~!!
		MyListener listener;
		CRudpNetManager::GetInstance()->Startup(&listener , nNum);

		while(1)
		{
			cout << "Push e for Exchange after UHP Client Registration" << endl;
			char ch = getchar();

			if( 'x' == ch )
				break;

			switch(ch)
			{
			case 'e':
				{
					CUserManager::GetInstance()->ExchangeAddr();
				}
				break;		
			}
		}
		
		//! RDUP ÇØÁ¦
		CRudpNetManager::GetInstance()->Cleanup();	
	}	

	return 0;
}

