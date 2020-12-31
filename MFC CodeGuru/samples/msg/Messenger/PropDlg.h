#if !defined(AFX_PROPDLG_H__743542B4_F3E8_11D1_B81B_0060084C3BF4__INCLUDED_)
#define AFX_PROPDLG_H__743542B4_F3E8_11D1_B81B_0060084C3BF4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PropDlg.h : header file
//

#ifndef TPROPERTIES_DLG_H
	#include "PropertiesDlg.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropDlg dialog
typedef CTPropertiesDlg<CDialog> CPropertiesDlg;

template <class TWnd>
class CPropDlg : public CTPropertiesDlg<TWnd>
{
// Construction
public:
	CPropDlg(UINT nIDTemplate = IDD_PROPERTIES_DIALOG );   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPropDlg)
	enum { IDD = IDD_PROPERTIES_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnApply();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPropDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnApplyNow();
	afx_msg void OnOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void AddProperties(CTreeCursor &root,long base);
	void AddExampleProperties(CTreeCursor &root,long base);

	void ModifyProperties(long base);


};

/////////////////////////////////////////////////////////////////////////////
// CPropDlg dialog

template <class TWnd>
CPropDlg<TWnd>::CPropDlg(UINT nIDTemplate)
	: CTPropertiesDlg<TWnd>(nIDTemplate)
{
	//{{AFX_DATA_INIT(CPropDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


template <class TWnd>
void CPropDlg<TWnd>::DoDataExchange(CDataExchange* pDX)
{
	CTPropertiesDlg<TWnd>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

DT_BEGIN_MESSAGE_MAP(CPropDlg, CTPropertiesDlg, TWnd)
//TWND_BEGIN_MESSAGE_MAP(CPropDlg, TWnd)
	//{{AFX_MSG_MAP(CPropDlg)
	ON_BN_CLICKED(ID_APPLY_NOW, OnApplyNow)
	ON_BN_CLICKED(IDOK, OnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropDlg message handlers

template <class TWnd>
BOOL CPropDlg<TWnd>::OnInitDialog() 
{
	CTPropertiesDlg<TWnd>::OnInitDialog();
	
	// TODO: Add extra initialization here
	CTreeCursor root;
	long base = 0;

	root = m_TreeCtrl.GetRootItem().AddTail("Properties");
	AddProperties(root,base += 10);
	AddExampleProperties(root,base += 10);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

template <class TWnd>
void CPropDlg<TWnd>::AddProperties(CTreeCursor & root,long base)
{
	CTreeCursor cursor;

	cursor = root.AddTail("Program properties");

	CMessengerApp *pApp = (CMessengerApp *)AfxGetApp();
	AddText(cursor,base ++,"Enter DB file name",pApp->m_DBPath);
}

template <class TWnd>
void CPropDlg<TWnd>::ModifyProperties(long base)
{
	CMessengerApp *pApp = (CMessengerApp *)AfxGetApp();

	GetText(base ++,pApp->m_DBPath);
}


template <class TWnd>
void CPropDlg<TWnd>::AddExampleProperties(CTreeCursor & root,long base)
{
	CTreeCursor cursor;

	cursor = root.AddTail("Example");

	AddText(cursor,base ++,"Default Label","BMW");
	AddFont(cursor,base ++,"Font","Arial");
	AddText(cursor,base ++,"Size",10);
	AddColor(cursor,base ++,"Color",RGB(255,0,0));

	cursor.AddTail(" ");
	m_TreeCtrl.m_LeftBracket = "[";
	m_TreeCtrl.m_RightBracket = "]";


	AddText(cursor,base ++,"Default Label","BMW","Modify label");
	AddFont(cursor,base ++,"Font","Arial","Replace font");
	AddText(cursor,base ++,"Size",10,"Enter number");
	AddColor(cursor,base ++,"Color",RGB(255,0,0),"Select black color");
}

template <class TWnd>
void CPropDlg<TWnd>::OnApplyNow() 
{
	// TODO: Add your control notification handler code here
	long base = 0;
	
	ModifyProperties(base += 10);

	CTPropertiesDlg<TWnd>::OnApplyNow();
}

template <class TWnd>
void CPropDlg<TWnd>::OnOk() 
{
	// TODO: Add your control notification handler code here
	OnApplyNow();

	EndDialog(IDOK);
}

template <class TWnd>
BOOL CPropDlg<TWnd>::OnApply()
{
	OnApplyNow();

	return TRUE;
}


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPDLG_H__743542B4_F3E8_11D1_B81B_0060084C3BF4__INCLUDED_)
