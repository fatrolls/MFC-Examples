#if !defined(AFX_SPWFVW_H__D3F202B5_FC3A_11D0_9C9A_444553540000__INCLUDED_)
#define AFX_SPWFVW_H__D3F202B5_FC3A_11D0_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CSpwFView : public CFormView
{
protected:
	CSpwFView();
	DECLARE_DYNCREATE(CSpwFView)

public:
	//{{AFX_DATA(CSpwFView)
	enum { IDD = IDD_DIALOG_VIEW };
	//}}AFX_DATA

public:
	//{{AFX_VIRTUAL(CSpwFView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	virtual ~CSpwFView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	//{{AFX_MSG(CSpwFView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_SPWFVW_H__D3F202B5_FC3A_11D0_9C9A_444553540000__INCLUDED_)
