// SoundManagerDlg.h : header file
//

#if !defined(AFX_SOUNDMANAGERDLG_H__A84121AA_1C0A_11D2_8890_0080C83F712F__INCLUDED_)
#define AFX_SOUNDMANAGERDLG_H__A84121AA_1C0A_11D2_8890_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "UTSampleAbout.h"
#include "OXSoundEffectManager.h"
#include "OXStaticHyperLink.h"
#include "OXCaptionPainter.h"

#include "MyAnimateCtrl.h"
#include "MyStatic.h"

/////////////////////////////////////////////////////////////////////////////
// CSoundManagerDlg dialog

class CSoundManagerDlg : public CDialog
{
// Construction
public:
	CSoundManagerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSoundManagerDlg)
	enum { IDD = IDD_SOUNDMANAGER_DIALOG };
	CMyStatic	m_ctlClose;
	CMyStatic	m_ctlCustomize;
	CMyStatic	m_ctlOption7;
	CMyStatic	m_ctlOption6;
	CMyStatic	m_ctlOption5;
	COXStaticHyperLink	m_ctlAbout;
	CMyStatic	m_ctlOption4;
	CMyStatic	m_ctlOption3;
	CMyStatic	m_ctlOption2;
	CMyStatic	m_ctlOption1;
	CMyStatic	m_ctlInfo;
	CMyAnimateCtrl	m_animMFC;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoundManagerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	COXSoundEffectOrganizer m_SoundEffectOrganizer;

	// caption painter
	COXCaptionPainter m_Caption;

	void SetupStaticControl(CMyStatic* m_pctl, COLORREF clrText,
		COLORREF clrBack, int nFontHeight, int nFontWeight,CString sFontName,
		BOOL bEmboss, int nHorzAlignment, int nVertAlignment, CString sEnterSound,
		CString sClickSound);

	// Generated message map functions
	//{{AFX_MSG(CSoundManagerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	afx_msg LONG OnAboutActivated(UINT wParam, LONG lParam);
	afx_msg LONG OnCustomize(UINT wParam, LONG lParam);
	afx_msg LONG OnClose(UINT wParam, LONG lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOUNDMANAGERDLG_H__A84121AA_1C0A_11D2_8890_0080C83F712F__INCLUDED_)
