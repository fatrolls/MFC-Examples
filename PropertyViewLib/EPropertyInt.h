// EPropertyInt.h: interface for the EPropertyInt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EPROPERTYINT_H__8A232506_B2CC_45B7_A136_F167F6A1B89D__INCLUDED_)
#define AFX_EPROPERTYINT_H__8A232506_B2CC_45B7_A136_F167F6A1B89D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ENumericProperty.h"

class EPropertyInt : public ENumericProperty
{

protected:

	int m_nByteWidth;
	int m_bSigned;

public:

	EPropertyInt( IPropertyHost* pHost , const CString& sName , void* pProperty , const CString& sUnit="" , bool bEnabled=true , int nMinAllowed=0 , int nMaxAllowed=0 );
	virtual ~EPropertyInt();

	//
	// ENumericProperty
	//
	virtual double GetNumericValue();
	virtual bool SetNumeric( double dVarValue );
	virtual int GetNumSignificantDigits();

public:

	EPropertyInt* SetType( int nByteWidth , bool bSigned );

};

#endif // !defined(AFX_EPROPERTYINT_H__8A232506_B2CC_45B7_A136_F167F6A1B89D__INCLUDED_)
