// MyRegular.h: interface for the CMyRegular class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYREGULAR_H__458C0FD3_B2F6_11D3_AC61_0050BAAB46B1__INCLUDED_)
#define AFX_MYREGULAR_H__458C0FD3_B2F6_11D3_AC61_0050BAAB46B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OXRegExpression.h"
class CFindDialog;

class CMyRegular : public COXRegExpression  
{
public:
	BOOL Match(CString sString);
 	CFindDialog* m_pParent;
	virtual BOOL OnMatch(int nStart, int nLength);
	CMyRegular();
	virtual ~CMyRegular();

protected:
	CString m_sString;
};

#endif // !defined(AFX_MYREGULAR_H__458C0FD3_B2F6_11D3_AC61_0050BAAB46B1__INCLUDED_)
