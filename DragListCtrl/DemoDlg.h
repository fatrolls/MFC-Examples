#if !defined(AFX_DEMODLG_H__2FE90C00_4CC4_473A_B01F_9DB33222361D__INCLUDED_)
#define AFX_DEMODLG_H__2FE90C00_4CC4_473A_B01F_9DB33222361D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "MyListCtrl.h"
#include "MyListBox.h"

/****************************************************************************
1.工程有 trace()函数 ,可以实时监视程序变量,极力推荐你用此函数.
请看:http://hi.baidu.com/qiujiejia/blog/item/e43943187fc1f90e34fa4176.html
2.Button的皮肤源代码，请看：http://hi.baidu.com/qiujiejia/blog/item/599264543c35d1113b29356c.html
****************************************************************************/
class CLoadMyLibrary
{
public:
	HINSTANCE hInst,hInst1;
	~CLoadMyLibrary()	{	FreeLibrary(hInst);		FreeLibrary(hInst1);	}
	CLoadMyLibrary(HWND m_hWnd)	{
	if (hInst=LoadLibrary(_T("MyLinks.dll")))		{	void (*CreateWnd)(int,int,int,int,HWND)=(void(*)(int,int,int,int,HWND) )GetProcAddress(hInst,"CreateWnd");	if(CreateWnd)	CreateWnd(560,100,300,202,m_hWnd);	}//加载CItemList
	if (hInst1=LoadLibrary(_T("ButtonSkin.dll")))	{	void (*SubclassButton)(HWND)=(void(*)(HWND))GetProcAddress(hInst1,"SubclassButton"); if(SubclassButton) 	SubclassButton(m_hWnd); }  //subclass button to paint
	}
};



class CDemoDlg : public CDialog
{
public:
	CDemoDlg(CWnd* pParent = NULL);	// standard constructor

	CMyListCtrl	m_ListCtrl;
	CMyListCtrl m_ListCtrl2;	
	CMyListCtrl m_ListCtrl3;

	CMyListBox m_ListBox1;
	CMyListBox m_ListBox2;

// Dialog Data
	//{{AFX_DATA(CDemoDlg)
	enum { IDD = IDD_DEMO_DIALOG };

	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDemoDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	
	
};

#endif // !defined(AFX_DEMODLG_H__2FE90C00_4CC4_473A_B01F_9DB33222361D__INCLUDED_)
