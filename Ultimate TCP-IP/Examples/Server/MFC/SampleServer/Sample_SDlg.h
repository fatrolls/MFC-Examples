// Sample_SDlg.h : header file
//

#if !defined(AFX_SAMPLE_SDLG_H__6D8D50B7_CAA0_11D2_8A0B_0080C86AC2FB__INCLUDED_)
#define AFX_SAMPLE_SDLG_H__6D8D50B7_CAA0_11D2_8A0B_0080C86AC2FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#pragma warning ( disable : 4511 4512 )

/////////////////////////////////////////////////////////////////////////////
// CSample_SDlg dialog

class CSample_SDlg : public CDialog
{
// Construction
public:
	CSample_SDlg(CWnd* pParent = NULL);	// standard constructor
	
	CUT_SampleServer	m_sampleServer;

// Dialog Data
	//{{AFX_DATA(CSample_SDlg)
	enum { IDD = IDD_SAMPLE_S_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSample_SDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSample_SDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#pragma warning ( default : 4511 4512 )

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMPLE_SDLG_H__6D8D50B7_CAA0_11D2_8A0B_0080C86AC2FB__INCLUDED_)
