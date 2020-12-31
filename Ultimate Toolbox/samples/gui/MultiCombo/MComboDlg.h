// MComboDlg.h : header file
//

#include "OXMultiComboBox.h"

#include "UTB64Bit.h"
/////////////////////////////////////////////////////////////////////////////
// CMComboDlg dialog

class CMComboDlg : public CDialog
{
// Construction
public:
	CMComboDlg(CWnd* pParent = NULL);	// standard constructor
// Dialog Data
	//{{AFX_DATA(CMComboDlg)
	enum { IDD = IDD_MCOMBO_DIALOG };
	COXMultiComboBox m_MCombo;
	CSpinButtonCtrl	m_wndSelectStartAfterSpin;
	CSpinButtonCtrl	m_wndSelectColNumSpin;
	CSpinButtonCtrl	m_wndMasterColumnSpin;
	CSpinButtonCtrl	m_wndLBTextRowNumSpin;
	CSpinButtonCtrl	m_wndItemDataIndexSpin;
	CSpinButtonCtrl	m_wndItemDataSpin;
	CSpinButtonCtrl	m_wndInsertAtColNumSpin;
	CSpinButtonCtrl	m_wndLBTextColNumSpin;
	CSpinButtonCtrl	m_wndColWidthSpin;
	CSpinButtonCtrl	m_wndColCountSpin;
	CSpinButtonCtrl	m_wndColWidthColSpin;
	int		m_MasterColumn;
	int		m_ColumnWidth;
	int		m_ColWidth_ColNum;
	int		m_ColCount;
	CString	m_AddList;
	int		m_InsertAt_ColNum;
	CString	m_LBText;
	int		m_LBText_ColNum;
	int		m_LBText_RowNum;
	int		m_SelectColNum;
	int		m_SelectStartAfter;
	CString	m_SelectString;
	DWORD_PTR	m_dwItemData;
	int		m_nItemDataIndex;
	BOOL	m_bFitToSize;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMComboDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMComboDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonSetmastercolumn();
	afx_msg void OnButtonSetcolumnwidth();
	afx_msg void OnButtonSetcolcount();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonInsertat();
	afx_msg void OnButtonGetlbtext();
	afx_msg void OnButtonSelectstring();
	afx_msg void OnButtonSetitemdata();
	afx_msg void OnButtonGetitemdata();
	afx_msg void OnEditchangeCombo1();
	afx_msg void OnEditupdateCombo1();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnCheckFittosize();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
