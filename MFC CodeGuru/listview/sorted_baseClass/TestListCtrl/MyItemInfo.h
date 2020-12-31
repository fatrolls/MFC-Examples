// MyItemInfo.h: interface for the CMyItemInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYITEMINFO_H__CBAA6794_F21D_11D1_9F9F_84E5D3000000__INCLUDED_)
#define AFX_MYITEMINFO_H__CBAA6794_F21D_11D1_9F9F_84E5D3000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ItemInfo.h"

class CMyItemInfo : public CItemInfo  
{
public:

	CMyItemInfo(int iItem, CString& Name, int Number) :
		CItemInfo(iItem),
		m_Name(Name),
		m_Number(Number) {m_NumberAsString.Format("%d",Number); };

	virtual ~CMyItemInfo() {};

	CString& GetName() {return m_Name;}
	int GetNumber() {return m_Number;}
	CString& GetNumberAsString() {return m_NumberAsString;}

private:

	CMyItemInfo();

    CString m_Name;
	CString m_NumberAsString;
    int m_Number;

};

#endif // !defined(AFX_MYITEMINFO_H__CBAA6794_F21D_11D1_9F9F_84E5D3000000__INCLUDED_)
