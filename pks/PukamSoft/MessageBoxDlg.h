#if !defined(AFX_MESSAGEBOXDLG_H__04D028CB_961F_4C86_9CB9_00147D1091D6__INCLUDED_)
#define AFX_MESSAGEBOXDLG_H__04D028CB_961F_4C86_9CB9_00147D1091D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MessageBoxDlg.h : header file
//
#include "..\Common\UIClasses\SkinnedStatic.h"
#include "..\Common\UIClasses\SkinnedButton.h"
#define ID_MB_TOP_BAND_STATIC		1010
#define ID_MB_LEFT_ICON_STATIC		1011
#define ID_MB_MESSAGE_TEXT_STATIC	1012
#define ID_MB_OK_BUTTON				1013
#define ID_MB_CANCEL_BUTTON			1014
#define ID_MB_YES_BUTTON			1015
#define ID_MB_NO_BUTTON				1016
#define MAX_MSG						13

#define MB_ICON_ERROR				100
#define MB_ICON_WARNING				200
#define MB_ICON_CONFIRMATION		300
#define MB_ICON_INFORMATION			400
/////////////////////////////////////////////////////////////////////////////
// CMessageBoxDlg dialog

class CMessageBoxDlg : public CDialog
{
// Construction
public:
	CMessageBoxDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMessageBoxDlg)
	enum { IDD = IDD_MESSAGEBOX_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessageBoxDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void CreateControls();
	void InitializeScreen();
	void DestroyControls();
	
	void InitializeMessageBox(int nMessageID,int nButtonType, CString csTopBandText = "", CString csUserText = "");
protected:

	CRect m_rcClient;
	int m_nMessageID;
	int m_nButtonType;
	CString m_csTopBandText;
	CString m_csMessageText;
	CString m_csUserText;
	CSkinnedStatic* m_pTopBandStatic;
	CSkinnedStatic* m_pLeftIconStatic;
	CSkinnedStatic* m_pMessageTextStatic;
	CSkinnedButton* m_pButton1;
	CSkinnedButton* m_pButton2;
protected:

	// Generated message map functions
	//{{AFX_MSG(CMessageBoxDlg)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSAGEBOXDLG_H__04D028CB_961F_4C86_9CB9_00147D1091D6__INCLUDED_)
