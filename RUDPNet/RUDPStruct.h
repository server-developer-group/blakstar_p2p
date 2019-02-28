#ifndef _RUDP_STRUCT_H_
#define _RUDP_STRUCT_H_




#pragma pack(1)




/*! RUDP 기능을 위해 내부적으로 쓰이는 data 해더
*  
*  @Version  2007. 5. 22
*
*  이호규 
*/

struct RUDPHeader
{
	unsigned char	ID;				//! 패킷 종류 - Reliable , UnReliable등
	unsigned char   UID;			//! 패킷 고유 아이디 - 순환됨
	unsigned short	usSize;

	void Reset(){ID=0L;UID=0;usSize=0;}
};








#pragma pack()


#endif

