#ifndef _ASSERT_MSG_H_
#define _ASSERT_MSG_H_

#include <assert.h>


#ifdef _DEBUG

	#define assert_msg(exp , msg)				assert( (exp) && (msg) )	

#else

	#define assert_msg(exp , msg)			

#endif




#endif