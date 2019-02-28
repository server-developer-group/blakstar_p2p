#ifndef _NET_ADAPTER_H_ 
#define	_NET_ADAPTER_H_


//! STL
#include <map>
using std::map;




/*! 네트워크 인터페이스를 추상화한 클래스
*  
*  @Version  2006. 7. 14
*
*  이호규
*/


class CNetAdapter
{
protected:

public:
	CNetAdapter();
	~CNetAdapter();	
	
	unsigned long	GetInternetIP();

protected:
	unsigned long	GetIP(int dwIndex);
	void			GetAdapterInfo();	
};


#endif