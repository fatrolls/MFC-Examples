// MyNntpClass.h: interface for the MyNntpClass class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_MYNNTPCLASS_H__48FA7A76_1906_11D3_87F0_0080C86498A0__INCLUDED_)
#define AFX_MYNNTPCLASS_H__48FA7A76_1906_11D3_87F0_0080C86498A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "nntpc.h"

// earliy definition to avoid the circular dependency
class CNNTPclientDlg;

class CMyNntpClass : public CUT_NNTPClient  
{

public:
	CMyNntpClass();
	virtual ~CMyNntpClass();
	// we need to over ride this function so we can abort if we wish
	BOOL IsAborted();
	void SetParentWindow( CNNTPclientDlg *parent);
	virtual int	OnNGetNewsGroupList(LPCSTR newGroupTitle);
	virtual int OnNGetArticleList(LPCSTR artId, LPCSTR subject,LPCSTR author,LPCSTR date, LPCSTR refrence,LPCSTR BytesCount, LPCSTR NumberOfLines, LPCSTR xrefs);
protected:
	CNNTPclientDlg *m_pPrntDlg;

};

#endif // !defined(AFX_MYNNTPCLASS_H__48FA7A76_1906_11D3_87F0_0080C86498A0__INCLUDED_)
