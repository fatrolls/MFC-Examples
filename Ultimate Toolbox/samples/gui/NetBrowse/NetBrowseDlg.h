// ==========================================================================
// 					Class Specification : CNetBrowseDlg
// ==========================================================================

// Header file : NetBrowseDlg.h

//==================  Dundas Software ======================================                          
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CDialog

//	YES	Is a Cwnd.                     
//	YES	Two stage creation (constructor & Create())
//	YES	Has a message map
//	YES	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         

// Remark:

// Prerequisites (necessary conditions):

/////////////////////////////////////////////////////////////////////////////

#ifndef __NETBROWSEDLG_H__
#define __NETBROWSEDLG_H__

#include "OXNetBrowseTree.h"

class CNetBrowseDlg : public CDialog
{
// Data members -------------------------------------------------------------
public:
	//{{AFX_DATA(CNetBrowseDlg)
	enum { IDD = IDD_NETBROWSE_DIALOG };
	CSpinButtonCtrl	m_wndMaxLevelsSpin;
	CComboBox	m_wndScopeList;
	CSpinButtonCtrl	m_wndExpandLevelSpin;
	COXNetBrowseTree	m_wndNetBrowseTree;
	CString	m_sComment;
	CString	m_sDisplayType;
	CString	m_sProvider;
	CString	m_sRemoteName;
	CString	m_sScope;
	CString	m_sType;
	CString	m_sUsage;
	CString	m_sLocalName;
	BOOL	m_bShowDisks;
	BOOL	m_bShowCommentNames;
	int		m_nExpandLevel;
	BOOL	m_bShowPrinters;
	BOOL	m_bReportErrors;
	int		m_nScopeList;
	int		m_nMaxLevels;
	//}}AFX_DATA

protected:
	HICON m_hIcon;

private:
	
// Member functions ---------------------------------------------------------
public:
	CNetBrowseDlg(CWnd* pParent = NULL);	// standard constructor
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Constructs the object

	virtual ~CNetBrowseDlg();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of the object

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetBrowseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	void SetTreeInitSettings();
	CString GetScopeName(const NETRESOURCE* pNetResource) const;
	CString GetTypeName(const NETRESOURCE* pNetResource) const;
	CString GetDisplayTypeName(const NETRESOURCE* pNetResource) const;
	CString GetUsageName(const NETRESOURCE* pNetResource) const;

	//{{AFX_MSG(CNetBrowseDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangedNetTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReinitialize();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
};

#endif // __NETBROWSEDLG_H__
// ==========================================================================
