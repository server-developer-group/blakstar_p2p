/*******************************************************************************
*
* FILE:         seedx.h
*
* DESCRIPTION:  header file for seedx.c
*
*******************************************************************************/

#ifndef SEED_H
#define SEED_H

/********************** Include files ************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/********************* Type Definitions **********************/

#ifndef TYPE_DEFINITION
    #define TYPE_DEFINITION
    #if defined(__alpha)
        typedef unsigned int        DWORD;
        typedef unsigned short      WORD;
    #else
        typedef unsigned long int   DWORD;
        typedef unsigned short int  WORD;
    #endif
    typedef unsigned char           BYTE;
#endif


/******************* Constant Definitions *********************/

#define NoRounds         16
#define NoRoundKeys      (NoRounds*2)
#define SeedBlockSize    16    /* in bytes */
#define SeedBlockLen     128   /* in bits */


/********************** Common Macros ************************/

#if defined(_MSC_VER)
    #define ROTL(x, n)     (_lrotl((x), (n)))
    #define ROTR(x, n)     (_lrotr((x), (n)))
#else
    #define ROTL(x, n)     (((x) << (n)) | ((x) >> (32-(n))))
    #define ROTR(x, n)     (((x) >> (n)) | ((x) << (32-(n))))
#endif


/**************** Function Prototype Declarations **************/

#ifndef PROTOTYPES
#define PROTOTYPES  1
#endif

#if PROTOTYPES
#define PROTO_LIST(list)    list
#else
#define PROTO_LIST(list)    ()
#endif

void SeedEncrypt 
    PROTO_LIST((BYTE *pbData, DWORD *pdwRoundKey));
void SeedDecrypt
    PROTO_LIST((BYTE *pbData, DWORD *pdwRoundKey));
void SeedEncRoundKey
    PROTO_LIST((DWORD *pdwRoundKey, BYTE *pbUserKey));

/******************************************************************/
#endif


/* Seed 함수 wrapper 클래스 */
class CSeed
{
public:
	static void Seed(DWORD* pdwRoundKey, BYTE* pbyUserKey);

	static void Encrypt(DWORD* pdwRoundKey , const char* pszData ,  int nSize);

	static void Decrypt(const char* pszData , DWORD* pdwKey);
};
