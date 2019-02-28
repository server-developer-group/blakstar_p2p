#ifndef _RUDP_Z_LIB_H_
#define _RUDP_Z_LIB_H_


#include "../zlib/zlib.h"




/*! Zlib wrapper
*  
*  @Version  2007. 8. 17
*
*  ¿Ã»£±‘
*/


class CRUDPZlib
{
public:
	static int Compress(char* pszDest , const int dest_size , const char* pszSrc , const int src_size );	

	static int UnCompress(char* pszDest , const int dest_size , const char* pszSrc , const int src_size );	
};


#endif
