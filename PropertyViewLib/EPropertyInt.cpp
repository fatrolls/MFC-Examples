// EPropertyInt.cpp: implementation of the EPropertyInt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IPropertyHost.h"
#include "EPropertyInt.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EPropertyInt::EPropertyInt( IPropertyHost* pHost , const CString& sName , void* pProperty , const CString& sUnit , bool bEnabled , int nMinAllowed, int nMaxAllowed ) : ENumericProperty( pHost , sName , pProperty , sUnit , bEnabled , nMinAllowed , nMaxAllowed )
{
	m_nByteWidth = 4;
	m_bSigned    = true;
}

EPropertyInt::~EPropertyInt()
{
}

double EPropertyInt::GetNumericValue()
{
	unsigned char* pPropertyChars = (unsigned char*)m_pProperty;

	//
	// pIntegerChars => __int64
	//

	__int64 n = 0;

	for( int i=m_nByteWidth-1 ; i>=0 ; i-- )	//most significant byte first
	{
		n <<= 8;
		n |= pPropertyChars[i];
	}

	//
	//
	//

	if( m_bSigned )
	{
		int nBitsRemaining = (8 - m_nByteWidth) * 8;
		n <<= nBitsRemaining;
		n >>= nBitsRemaining;	//brcause n is signed it will pull down 1's from 63th bit position
	}

	double d = n;

	return d;
}

bool EPropertyInt::SetNumeric( double dVarValue )
{
	bool bPropertyChanged = false;

	__int64 n = (__int64)dVarValue;

	unsigned char pNewValueChars[8];

	//
	// __int64 => pIntegerChars
	//

	for( int i=0 ; i<m_nByteWidth ; i++ )
	{
		unsigned char c =  n & 0xff;

		pNewValueChars[i] = c;

		n >>=8;
	}

	//
	// let host decide if change is allowed - if so, change it
	//

	if( m_pHost->PropertyChanging( m_pProperty , pNewValueChars ) )
	{
		memcpy( m_pProperty , pNewValueChars , m_nByteWidth );
		bPropertyChanged = true;
	}

	//
	//
	//

	return bPropertyChanged;
}

EPropertyInt* EPropertyInt::SetType( int nByteWidth , bool bSigned )
{
	ASSERT( nByteWidth==1 || nByteWidth==2 || nByteWidth==4 );
	m_nByteWidth = nByteWidth;
	m_bSigned    = bSigned;
	return this;
}

int EPropertyInt::GetNumSignificantDigits()
{
	return 10;
}
