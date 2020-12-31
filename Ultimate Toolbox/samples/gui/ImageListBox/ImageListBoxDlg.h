// ImageListBoxDlg.h : header file
//

#if !defined(AFX_IMAGELISTBOXDLG_H__A574A807_4041_11D3_8AF4_0080C8F8F09F__INCLUDED_)
#define AFX_IMAGELISTBOXDLG_H__A574A807_4041_11D3_8AF4_0080C8F8F09F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OXSeparator.h"
#include "OXHistoryCombo.h"
#include "OXImageListBox.h"
#include "OXColorPickerButton.h"

/////////////////////////////////////////////////////////////////////////////
// CImageListBoxDlg dialog

class CImageListBoxDlg : public CDialog
{
// Construction
public:
	CImageListBoxDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CImageListBoxDlg)
	enum { IDD = IDD_IMAGELISTBOX_DIALOG };
	COXColorPickerButton	m_btnBkColor;
	COXSeparator	m_sepOperations;
	COXImageListBox	m_listImages;
	COXHistoryCombo	m_comboIconSourceFile;
	CString	m_sIconSourceFile;
	int		m_nSourceType;
	int		m_nSelectedImage;
	BOOL	m_bUseSmallIcons;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageListBoxDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	CImageList m_ilDefault;
	COLORREF m_clrBackground;

protected:
	void ShowControls();
	void LoadFromFile();

	// Generated message map functions
	//{{AFX_MSG(CImageListBoxDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonAddDefault();
	afx_msg void OnButtonRemove();
	afx_msg void OnEditchangeComboIconsourceFilename();
	afx_msg void OnSelchangeComboIconsourceFilename();
	afx_msg void OnSelchangeListImages();
	afx_msg void OnRadioCustom();
	afx_msg void OnRadioDefault();
	afx_msg void OnButtonBkColor();
	afx_msg void OnCheckSmallIcons();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGELISTBOXDLG_H__A574A807_4041_11D3_8AF4_0080C8F8F09F__INCLUDED_)
