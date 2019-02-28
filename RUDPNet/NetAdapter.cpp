#include "StdAfx.h"

#include "NetAdapter.h"
#include "winsock2.h"
#include "IPHLPAPI.h"
#include "assert.h"


PIP_ADAPTER_INFO m_pinfo = NULL;

map<int , PIP_ADDR_STRING> m_mapAdapter;


CNetAdapter::CNetAdapter()
{
	GetAdapterInfo();	
}

CNetAdapter::~CNetAdapter()
{
	if( NULL != m_pinfo)
		free(m_pinfo);
}

void
CNetAdapter::GetAdapterInfo()
{
	//! Network card 1개
	unsigned long len = sizeof(IP_ADAPTER_INFO);
	m_pinfo = (IP_ADAPTER_INFO *) malloc (len);	

	unsigned long nError = GetAdaptersInfo(m_pinfo,&len);	

	//! 버퍼가 모자르면
	if( ERROR_BUFFER_OVERFLOW == nError )
	{
		//! 기존 메모리 삭제
		free(m_pinfo);

		//! 다시 생성
		m_pinfo = (IP_ADAPTER_INFO *) malloc (len);		

		//! 어댑터 정보 얻기
		nError = GetAdaptersInfo(m_pinfo,&len);
		if( nError != 0)
			ExitProcess(1);
	}	

	PIP_ADAPTER_INFO info = m_pinfo;			
	while( info != NULL )
	{
		PIP_ADDR_STRING pAddressList = &(info->IpAddressList);	

		m_mapAdapter.insert( map<int , PIP_ADDR_STRING>::value_type( info->Index , pAddressList) );
		info = info->Next;	
	}			
}

unsigned long
CNetAdapter::GetInternetIP()
{
	unsigned long ulResult = 0;

	//! 라우팅 테이블
	PMIB_IPFORWARDTABLE pIpForwardTable;
	DWORD dwSize = 0;
	DWORD dwRetVal = 0;

	pIpForwardTable = (MIB_IPFORWARDTABLE*) GlobalAlloc(GMEM_FIXED , sizeof(MIB_IPFORWARDTABLE));
	if (GetIpForwardTable(pIpForwardTable, &dwSize, 0) == ERROR_INSUFFICIENT_BUFFER) {
		GlobalFree(pIpForwardTable);
		pIpForwardTable = (MIB_IPFORWARDTABLE*) GlobalAlloc(GMEM_FIXED ,dwSize);
	}

	if ((dwRetVal = GetIpForwardTable(pIpForwardTable, &dwSize, 0)) == NO_ERROR) {

		ulResult = GetIP(pIpForwardTable->table[0].dwForwardIfIndex);	
	}

	return ulResult;
}

unsigned long
CNetAdapter::GetIP(int dwIndex)
{
	//assert( dwIndex > 0 );

	unsigned long ulResult = 0;

	if( 1 == dwIndex)
	{
		ulResult = inet_addr("127.0.0.1");
	}
	else
	{
		map<int , PIP_ADDR_STRING>::iterator where = m_mapAdapter.find(dwIndex);
		if( where != m_mapAdapter.end() )
		{
			const PIP_ADDR_STRING pAddressList = where->second;
			ulResult = inet_addr(pAddressList->IpAddress.String);
		}		
	}

	return ulResult;
}