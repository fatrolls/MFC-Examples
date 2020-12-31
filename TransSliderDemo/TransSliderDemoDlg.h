// TransSliderDemoDlg.h : header file
//

#if !defined(AFX_TRANSSLIDERDEMODLG_H__2B6B2C5C_48BE_48CA_B959_6E682DB834C1__INCLUDED_)
#define AFX_TRANSSLIDERDEMODLG_H__2B6B2C5C_48BE_48CA_B959_6E682DB834C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MySliderControl.h"
/////////////////////////////////////////////////////////////////////////////
// CTransSliderDemoDlg dialog

class CTransSliderDemoDlg : public CDialog
{
	BOOL SetBitmap(UINT uResourceID);
	BOOL TileBitmap(CDC* pDC, CRect rc);
	BOOL GetBitmapAndPalette(UINT nIDResource, CBitmap& bitmap, CPalette& pal);
	// For background bitmap
	CBitmap m_BmpPattern;
	CPalette m_BmpPalette;
	int m_nBmpWidth;
	int m_nBmpHeight;

// Construction
public:
	CTransSliderDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTransSliderDemoDlg)
	enum { IDD = IDD_TRANSSLIDERDEMO_DIALOG };
	CMySliderControl	m_Slider2;
	CMySliderControl	m_Slider;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransSliderDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTransSliderDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnChangebitmap();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSSLIDERDEMODLG_H__2B6B2C5C_48BE_48CA_B959_6E682DB834C1__INCLUDED_)
