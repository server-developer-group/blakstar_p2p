#include "StdAfx.h"
#include "RUDPZlib.h"

#include "../util/assert_msg.h"

int
CRUDPZlib::Compress(char* pszDest , const int dest_size , const char* pszSrc , const int src_size )
{
	int nResult = -1;

	uLongf fsize = dest_size;	

	if( Z_OK == compress((Bytef*)pszDest ,  &fsize , (const Bytef*)pszSrc , src_size ) )
	{
		nResult = fsize;
	}
	else
	{
		assert_msg( false , "압축실패" );
	}

	return nResult;
}

int
CRUDPZlib::UnCompress(char* pszDest , const int dest_size , const char* pszSrc , const int src_size )
{
	int nResult = -1;

	uLongf fsize = dest_size;
	if( Z_OK == uncompress((Bytef*)pszDest ,  &fsize , (const Bytef*)pszSrc , src_size ))
	{
		nResult = fsize;
	}

	return nResult;
}