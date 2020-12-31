#if !defined(AFX_PAGE_H__6F1FA2D4_130A_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_PAGE_H__6F1FA2D4_130A_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPage1)
public:
	CPage1();
	~CPage1();
	//{{AFX_DATA(CPage1)
	enum { IDD = IDD_DIALOG_PAGE1 };
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CPage1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CPage1)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CPage2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPage2)
public:
	CPage2();
	~CPage2();
	//{{AFX_DATA(CPage2)
	enum { IDD = IDD_DIALOG_PAGE2 };
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CPage2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CPage2)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CPage3 : public CPropertyPage
{
public:
	CPage3();
	~CPage3();
	//{{AFX_DATA(CPage3)
	enum { IDD = IDD_DIALOG_PAGE3 };
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CPage3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CPage3)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_PAGE_H__6F1FA2D4_130A_11D1_9C9A_444553540000__INCLUDED_)
