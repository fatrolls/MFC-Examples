// CsvTestDlg.h : header file
//

#if !defined(AFX_CSVTESTDLG_H__ED9EE2A7_98D3_11D2_B0EC_0090271D78EB__INCLUDED_)
#define AFX_CSVTESTDLG_H__ED9EE2A7_98D3_11D2_B0EC_0090271D78EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCsvTestDlg dialog

class CCsvTestDlg : public CDialog
{
// Construction
public:
	CCsvTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCsvTestDlg)
	enum { IDD = IDD_CSVTEST_DIALOG };
	CButton	m_ctrlSave;
	BOOL	m_bUseHeaders;
	CString	m_strData;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCsvTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCsvTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnSave();
	afx_msg void OnAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	//
	// Strcuture defining the data being read in
	//
	struct SData
	{
		short nId;
		CString strName;
		unsigned char ucByte;
		short nInt;
		float fFloat;
		double fDouble;
		CString strString;
		BOOL bValid;
		CString strLastName;
		CString strAddress;

		SData()
		{
			Clear();
		}

		SData(const SData& x)
			: nId(x.nId), strName(x.strName), ucByte(x.ucByte), nInt(x.nInt),
			fFloat(x.fFloat), fDouble(x.fDouble), strString(x.strString),
			bValid(x.bValid), strLastName(x.strLastName), strAddress(x.strAddress)
		{
		}

		void Clear()
		{
			nId = 0;
			strName.Empty();
			ucByte = 0;
			nInt = 0;
			fFloat = 0.0;
			fDouble = 0.0;
			strString.Empty();
			bValid = false;
			strLastName.Empty();
			strAddress.Empty();
		}
	};

	CArray<SData, SData&> m_aData;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSVTESTDLG_H__ED9EE2A7_98D3_11D2_B0EC_0090271D78EB__INCLUDED_)
