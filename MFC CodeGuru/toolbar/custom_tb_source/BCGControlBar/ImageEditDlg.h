#if !defined(AFX_IMAGEEDITDLG_H__07E27535_C6D9_11D1_A647_00A0C93A70EC__INCLUDED_)
#define AFX_IMAGEEDITDLG_H__07E27535_C6D9_11D1_A647_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ImageEditDlg.h : header file
//

#include "ColorSelector.h"
#include "ImagePaintArea.h"

/////////////////////////////////////////////////////////////////////////////
// CImageEditDlg dialog

class CImageEditDlg : public CDialog
{
// Construction
public:
	CImageEditDlg(CBitmap* pBitmap, SIZE sizeImage, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CImageEditDlg)
	enum { IDD = IDD_IMAGE_EDITOR };
	CButton	m_wndPasteButton;
	CStatic	m_wndPreview;
	CImagePaintArea	m_wndLargeDrawArea;
	CColorSelector	m_wndColor;
	//}}AFX_DATA

protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImageEditDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClear();
	afx_msg void OnColors();
	afx_msg void OnCopy();
	afx_msg void OnPaste();
	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Attributes:
	CBitmap*	m_pBitmap;
	CSize		m_sizeImage;

	CRect		m_rectPreviewFrame;
	CRect		m_rectPreviewImage;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEEDITDLG_H__07E27535_C6D9_11D1_A647_00A0C93A70EC__INCLUDED_)
