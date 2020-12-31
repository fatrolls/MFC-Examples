#if !defined(AFX_STATESDLG_H__1F33BE83_F7DE_4D3C_A817_F4B2E06D4495__INCLUDED_)
#define AFX_STATESDLG_H__1F33BE83_F7DE_4D3C_A817_F4B2E06D4495__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StatesDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStatesDlg dialog

class CStatesDlg : public CDialog
{
// Construction
public:
	DWORD GetStates() const;
	CStatesDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStatesDlg)
	enum { IDD = IDD_STATESDLG };
	BOOL	m_bAll;
	BOOL	m_bChecked;
	BOOL	m_bFocused;
	BOOL	m_bSelected;
	BOOL	m_bUnfocused;
	BOOL	m_bUnchecked;
	BOOL	m_bUnselected;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStatesDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	DWORD m_dwStates;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATESDLG_H__1F33BE83_F7DE_4D3C_A817_F4B2E06D4495__INCLUDED_)
