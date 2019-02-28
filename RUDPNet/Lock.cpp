#include "stdafx.h"
#include ".\lock.h"
#include "assert.h"

CLock::CLock():bLock(FALSE)
{
#if ( defined( _WIN32_WINNT ) && ( _WIN32_WINNT >= 0x0403 ) )
	InitializeCriticalSectionAndSpinCount( &m_insCS , 4000 );
#else
	InitializeCriticalSection( &m_insCS );
#endif
}

CLock::~CLock()
{
	if( IsLock() == TRUE)
		LeaveCriticalSection(&m_insCS);

	DeleteCriticalSection(&m_insCS);
}

const CLock & CLock::operator = (const CLock & lock)
{
	return (*this);
}

void
CLock::Lock()
{
	EnterCriticalSection(&m_insCS);	
	InterlockedCompareExchange( (LONG*)&bLock , TRUE  , FALSE);	 
}


void
CLock::UnLock()
{
	LeaveCriticalSection(&m_insCS);
	InterlockedCompareExchange( (LONG*)&bLock , FALSE  , TRUE);	 
}

//! util
BOOL
CLock::IsLock() const
{
	//! 동기화 처리
	BOOL bResult = FALSE;

	if( InterlockedCompareExchange( (LONG*)&bResult , TRUE  , TRUE) == TRUE )
		bResult = TRUE;

	return bResult;
}