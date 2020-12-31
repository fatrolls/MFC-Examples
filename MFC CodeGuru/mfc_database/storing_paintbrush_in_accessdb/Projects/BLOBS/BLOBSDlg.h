// BLOBSDlg.h : header file
//

#if !defined(AFX_BLOBSDLG_H__18FE210F_F229_11D1_8F3C_0080C82231F1__INCLUDED_)
#define AFX_BLOBSDLG_H__18FE210F_F229_11D1_8F3C_0080C82231F1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CBLOBSDlg dialog

class CBLOBSDlg : public CDialog
{
// Construction
public:
	CBitmap OleBmp;
	CBLOBSDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBLOBSDlg)
	enum { IDD = IDD_BLOBS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBLOBSDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBLOBSDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLoadImage();
	afx_msg void OnAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL ReadFromBLOB(CByteArray & DBArray);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLOBSDLG_H__18FE210F_F229_11D1_8F3C_0080C82231F1__INCLUDED_)
