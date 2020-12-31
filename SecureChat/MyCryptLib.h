// MyCryptLib.h: interface for the MyCryptLib class.
// 
// Written by Amin Gholiha, 2005, The source code apply under 
// ADAPTIVE PUBLIC LICENSE (Please read License-APLl.txt)
// 
//  ADDITIONAL  LIMITATION OF LIABILITY
// -----------------------------------------------------
// IN NO EVENT WILL AMIN GHOLIHA  BE LIABLE TO YOU FOR ANY 
// DAMAGES, CLAIMS OR COSTS WHATSOEVER OR ANY CONSEQUENTIAL, 
// INDIRECT, INCIDENTAL DAMAGES, OR ANY LOST PROFITS OR LOST SAVINGS, 
// EVEN IF AN  REPRESENTATIVE HAS BEEN ADVISED OF 
// THE POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS OR 
// FOR ANY CLAIM BY ANY THIRD PARTY.  
// THE FOREGOING LIMITATIONS AND EXCLUSIONS APPLY TO 
// THE EXTENT PERMITTED BY APPLICABLE LAW IN YOUR JURISDICTION. 
// 
// 
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYCRYPTLIB_H__8F521792_8777_4A18_B55E_7EE1427D164B__INCLUDED_)
#define AFX_MYCRYPTLIB_H__8F521792_8777_4A18_B55E_7EE1427D164B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////
/// Definitions. 
//////////////////////////////////////////////

#define _MYCRYPTLIB_DEMOS_ // Undef to leave out the unnessary Demo*(..) functions. 

#define   WIN32_LEAN_AND_MEAN

// Is the system little or Big endian. 
#if (('1234' >> 24) == '1')
#define  SYSTEM_LITTLE_ENDIAN 1234
#elif (('4321' >> 24) == '1')
#define SYSTEM_BIG_ENDIAN      4321
#endif


#define LOHALF(x) ((DWORD)((x) & _MAXHALFNR_))
#define HIHALF(x) ((DWORD)((x) >> sizeof(DWORD)*4 & _MAXHALFNR_))
#define TOHIGH(x) ((DWORD)((x) << sizeof(DWORD)*4))
//#define rotate32(x,n) (((x) << n) | ((x) >> (32 - n)))
#define rotate32(x,n) _lrotl((x), (n))


#if (SYSTEM_BIG_ENDIAN)

#define SHA_BLOCK32(x) (x)
// The HiBITMASK used for computation, FIX FOR LATER: should change to fit your system e.g 64 bit CPUs. 
#define _HIBITMASK_ 0x00000008
// The maximum nr supported by the system, used to detect owerflows. 
#define _MAXIMUMNR_ 0xffffffff
// The maximum nr you can get using half the number of bits. 
#define _MAXHALFNR_ 0x000Lffff 
#else
#define SHA_BLOCK32(x) ((rotate32((x), 8) & 0x00ff00ff) | (rotate32((x), 24) & 0xff00ff00))
// The HiBITMASK used for computation, FIX FOR LATER: should change to fit your system e.g 64 bit CPUs. 
#define _HIBITMASK_ 0x80000000

// The maximum nr supported by the system, used to detect owerflows. 
#define _MAXIMUMNR_ 0xffffffff
// The maximum nr you can get using half the number of bits. 
#define _MAXHALFNR_ 0xffffL 
#endif


#define SHA1_BLOCK_SIZE  64
#define SHA1_DIGEST_SIZE 20

// for code cleanness. 

#define F0to19(x,y,z)       (((x) & (y)) ^ (~(x) & (z)))
#define F20to39(x,y,z)		((x) ^ (y) ^ (z))
#define F40to59(x,y,z)      (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define F60to79(x,y,z)		 F20to39(x,y,z)


#define sha_round(func,k)  t = a; a = rotate32(a,5) + func(b,c,d) + e + k + w[i];\
	e = d;d = c; c = rotate32(b, 30); b = t;

typedef struct
{   
	UINT wbuf[16];
	UINT hash[5];
	UINT count[2];
} SHA1_STATETYPE;

#ifdef _MYCRYPTLIB_DEMOS_
#include "HistoryEdit.h"
#include <math.h>
#endif

class MyCryptLib  
{
public:

#ifdef _MYCRYPTLIB_DEMOS_
	// Demostration of Diffie Hellman key exchange.. 
	void DemoDiffieHellman(CHistoryEdit *pLogg, UINT nSize);
	// Demostration of Digital signing..
	void DemoDSA(CHistoryEdit *pLogg, UINT nSize, BYTE* pEntropyPool=NULL,UINT nEntropySize=0);
	// Demostration of RSA.. 
	void DemoRSA(CHistoryEdit *pLogg,UINT nSize);
	// Used to test the Library function 
	void DemoSimpleTest(CHistoryEdit *pLogg);
#endif

	// Collecting Entropy using existing HW. 
	BOOL MTCollectEntropy(BYTE *pRandomPool, UINT nSize);
	// Verifies Signature Computed by DigitalSignSHA1rDSA using the trusted public keys n and e. 
	BOOL DigitalVerifySHA1rDSA(unsigned char* pmsgbuff, UINT nSizeMsg,DWORD n[],DWORD e,DWORD S[],UINT nSize);
	// Creates an Digital signature (S) of pmsgbuff using private key d, public key n.
	int DigitalSignSHA1rDSA(unsigned char* pmsgbuff, UINT nSizeMsg,DWORD d[],DWORD n[],DWORD S[],UINT nSize);
	// Computes The Sha1Hash for an given data with length nSize
	void SHA1Hash(unsigned char *_pOutDigest, const unsigned char *_pData,UINT nSize);
	void SHA1_Start(SHA1_STATETYPE* _pcsha1);
	void SHA1_Finish(unsigned char* _pShaValue, SHA1_STATETYPE* _pcsha1);
	void SHA1_Hash(const unsigned char *_pData, unsigned int _iSize, SHA1_STATETYPE* _pcsha1);
	// RSA Decrypt using CRT method. 
	int RSADecryptCRT(DWORD m[],DWORD c[],DWORD p[], DWORD q[], DWORD dP[], DWORD dQ[], DWORD qInv[], UINT nSize);
	// RSA Encrypt function 
	inline int RSAEncrypt(DWORD c[], DWORD m[], DWORD n[], DWORD e[], UINT nSize);
	// RSA Encrypt function 
	inline int RSAEncrypt(DWORD c[],DWORD m[],DWORD n[],UINT nSize,DWORD e);
	// Generates an RSA Key 	
	int RSAGenerateKey(DWORD n[], DWORD d[], DWORD p[], DWORD q[], DWORD dP[], DWORD dQ[], DWORD qInv[], UINT nSize,UINT nPSize,UINT nQSize,DWORD e=65537, BYTE* pSeedData=NULL,UINT nSeedData=0);
	// Genereates an RSA SAFE Prime nr. 
	int BNMakeRSAPrime(DWORD p[],DWORD ee, UINT nSize,UINT nMaximumRetry=30);
	MyCryptLib();
	virtual ~MyCryptLib();
	// Create an well defined Random nr. 
	UINT BNMakeRandomNr(DWORD a[], UINT nSize);
	// Return an CStirng containing the number. 
	CString BNPrint(const DWORD *p, UINT nSize);
	// print out the number in C format. 
	CString BNPrintC(const DWORD *p, UINT nSize);
	// Generate an prime nr. 
	int BNMakePrime(DWORD p[],UINT nSize,PBYTE pEntropyPool=NULL, UINT nSizeEntropyPool=0);
	// Is the number provided an prime nr? 
	int BNIsPrime(DWORD W[],UINT nSize,UINT nrRounds);
	// Generate an random nr between the given border. 
	inline DWORD RandBetween(DWORD dwLower,DWORD dwUpper);
	// Mersenne Twister random generator, returns an random nr. 
	inline DWORD MTRandom();
	// Mersenne Twinster init..
	inline BOOL MTInit(BYTE *pRandomPool=NULL, UINT nSize=0);
	// The Rabin Miller algorihm 
	int BNRabinMiller(const DWORD w[], UINT ndigits, UINT t);
	// GCD(x,y) Greatest Common dividor. 
	int BNGcd(DWORD g[], const DWORD x[], const DWORD y[], UINT nSize);
	// inv = u^(-1) mod v
	int BNModInv(DWORD inv[], const DWORD u[], const DWORD v[], UINT nSize);
	// w=x*x more optimized and Mult. 
	inline int BNSquare(DWORD w[], const DWORD x[], UINT nSize);
	// Computes y = x^e mod m 
	int BNModExp(DWORD yout[], const DWORD x[], const DWORD e[], const DWORD m[], UINT nSize);
	// a = (x * y) mod m 
	DWORD BNModMult(DWORD a[], const DWORD x[], const DWORD y[], const DWORD m[], UINT nSize);
	// r = u mod v
	DWORD BNMod(DWORD r[], const DWORD u[], UINT nUSize, DWORD v[], UINT nVSize);
	// Get an Big nr from Hex string
	UINT BNFromHex(DWORD a[], UINT nSize, const char *s,UINT nStringLength);
	// Get an Big nr from Decimal String 
	UINT BNFromDecimal(DWORD a[], UINT nSize, const char *s, UINT nStringLength);
	// Returns ceil(x) as a non-negative integer or 0 if x < 0, We don't whant to include Math lib for only this function. 
	UINT BNUiceil(double x);
	// Big nr => octets 
	UINT BNToOctets(const DWORD a[], UINT nSize, unsigned char *c, UINT nbytes);
	// array of octets => Bing number 
	UINT BNFromOctets(DWORD a[], UINT nSize, const unsigned char *c, UINT nOctBytes);
	// convert an Big Numer to an CString 
	CString BNToString( const DWORD *a, UINT nSize,UINT nBase=10);
	// returns r = a mod d, where d is an normal DWORD. 
	inline DWORD BNModdw(DWORD a[],DWORD d, UINT nSize);
	//  for future Optimization 
	inline void BNFree(DWORD **p);
	inline DWORD * BNAlloc(UINT nSize);
	// Returns number of significant bits in d 
	UINT BNBitLength(const DWORD *d,UINT nSize);
	// w=u-v, where v is an normal DWORD. 
	DWORD BNSubtractdw(DWORD w[], const DWORD u[], DWORD v,  UINT  nSize);
	// returns a-b
	inline int BNComparedw(const DWORD a[], DWORD b, UINT nSize);
	// returns a-b
	int BNCompare(const DWORD a[], const DWORD b[], UINT nSize);
	//  a = b >> x 
	inline DWORD BNShiftRight(DWORD a[], const DWORD *b, DWORD x, DWORD nSize);
	//a = b << x 
	inline DWORD BNShiftLeft(DWORD a[], const DWORD *b, UINT x, UINT nSize);
	// Divide an big nr with an ordenary DWORD.
	inline DWORD BNDividedw(DWORD q[], const DWORD u[], DWORD  v, UINT nSize);
	// Sets a=d
	void BNSetEqualdw(DWORD a[], const DWORD d, UINT nSize);
	// Set a=b 
	inline void BNSetEqual(DWORD a[], const DWORD b[], UINT nSize);
	// returns a==0
	int BNIsZero(const DWORD a[], UINT nSize);
	// Returns True if A == B. 
	int BNIsEqual(const DWORD a[], const DWORD b[], UINT nSize);
	// Returns the real size of A
	inline UINT BNSizeof(const DWORD A[], UINT nSize);
	// Makesure that the data in A is zero
	void BNSetZero(DWORD A[],UINT nSize);
	// Divides 
	int BNDivide(DWORD q[], DWORD r[], const DWORD u[], UINT usize,DWORD v[],UINT vsize);
	// Subtract Big numbers, returns C=B-A, (B>A)
	DWORD BNSubtract(DWORD C[], const DWORD A[], const DWORD B[], const UINT nSize);
	// Adds Big numbers, returns C=A+B
	DWORD BNAdd(DWORD C[], const DWORD A[],const  DWORD B[], const UINT nSize);
	// Adds an normal DWORD to an big DWORD. 
	DWORD BNAdddw(DWORD w[], const DWORD u[], DWORD v, UINT nSize);
	// Multiplies Big numbers C=A*B. 
	inline	DWORD BNMultiply(DWORD C[], const DWORD A[], const DWORD B[], const UINT nSize);
	inline DWORD BNMultiplydw(DWORD w[], const DWORD u[], DWORD v, UINT nSize);
private:
	// SHA1 Functions 
	inline void SHA1_Transform(SHA1_STATETYPE* _pcsha1);


	// SHA1 MASK
	static const UINT _SHA_MASK_[4];
	static const UINT _SHA_BITS_[4];

	// Prime nrs
	static const DWORD SMALL_PRIMES[];
	static const UINT _NUMBEROFPRIMES_;

	// The Mersenne Twister radnom bufffer and index. 
	UINT m_mtIndex;
	DWORD m_mtbuffer[624];
	BOOL m_bSeeded;
	// Helpers for code cleaness. 
	inline int BNQhatTooBigHelper(DWORD qhat, DWORD  rhat,DWORD vn2, DWORD ujn2);
	inline DWORD BNMultSub(DWORD wn, DWORD w[], const DWORD v[], DWORD q, UINT n);
	inline void BNMultSubHelper(DWORD uu[2], DWORD qhat, DWORD v1, DWORD v0);
	inline int BNMultiplyHelper(DWORD p[2], const DWORD x, const DWORD y);
	inline DWORD BNDivideHelper(DWORD *q, DWORD *r, const DWORD u[2], DWORD v);
	inline int BNModSquareTmp(DWORD a[], const DWORD x[], DWORD m[], UINT nSize, DWORD temp[], DWORD tqq[], DWORD trr[]);
	inline int BNModuloTmp(DWORD r[], const DWORD u[], UINT nUSize, DWORD v[], UINT nVSize, DWORD tqq[], DWORD trr[]);
	inline int BNMultTmp(DWORD a[], const DWORD x[], const DWORD y[], DWORD m[], UINT nSize,  DWORD temp[], DWORD tqq[], DWORD trr[]);
};

#endif // !defined(AFX_MYCRYPTLIB_H__8F521792_8777_4A18_B55E_7EE1427D164B__INCLUDED_)
