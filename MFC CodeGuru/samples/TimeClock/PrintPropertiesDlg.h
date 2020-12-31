#if !defined(AFX_PRINTPROPERTIESDLG_H__E6E09121_F3C4_11D0_90FC_0060976CDDF4__INCLUDED_)
#define AFX_PRINTPROPERTIESDLG_H__E6E09121_F3C4_11D0_90FC_0060976CDDF4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PrintPropertiesDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPrintPropertiesDlg dialog

class CPrintPropertiesDlg : public CDialog
{
// Construction
public:
	CPrintPropertiesDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
private:

	//{{AFX_DATA(CPrintPropertiesDlg)
	enum { IDD = IDD_PRINT_PROPERTIES };
	CString	m_strFri;
	CString	m_strMon;
	CString	m_strSat;
	CString	m_strThu;
	CString	m_strTue;
	CString	m_strWed;
	CString	m_strSun;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrintPropertiesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrintPropertiesDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CString& GetMonTotal () { return m_strMon; }
	CString& GetTueTotal () { return m_strTue; }
	CString& GetWedTotal () { return m_strWed; }
	CString& GetThuTotal () { return m_strThu; }
	CString& GetFriTotal () { return m_strFri; }
	CString& GetSatTotal () { return m_strSat; }
	CString& GetSunTotal () { return m_strSun; }
	void SetMonTotal ( CString& str ) { m_strMon = str; }
	void SetTueTotal ( CString& str ) { m_strTue = str; }
	void SetWedTotal ( CString& str ) { m_strWed = str; }
	void SetThuTotal ( CString& str ) { m_strThu = str; }
	void SetFriTotal ( CString& str ) { m_strFri = str; }
	void SetSatTotal ( CString& str ) { m_strSat = str; }
	void SetSunTotal ( CString& str ) { m_strSun = str; }
protected:
private:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTPROPERTIESDLG_H__E6E09121_F3C4_11D0_90FC_0060976CDDF4__INCLUDED_)
