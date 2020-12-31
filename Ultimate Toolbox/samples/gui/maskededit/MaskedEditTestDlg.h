// MaskedEditTestDlg.h : header file
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __MaskedEditTestDlg_h__
#define __MaskedEditTestDlg_h__


#include "OXMaskedEdit.h"    // COXMaskedEdit

/////////////////////////////////////////////////////////////////////////////
// CMaskedEditTestDlg dialog

class CMaskedEditTestDlg : public CDialog
	{
	// Construction
	public:
		CMaskedEditTestDlg(CWnd* pParent = NULL) ;
		
		// Dialog Data
	protected:
		//{{AFX_DATA(CMaskedEditTestDlg)
	enum { IDD = IDD_MASKEDEDITTEST_DIALOG };
		COXMaskedEdit m_editMasked   ;
		CComboBox     m_comboMasks   ;
		CString       m_csPromptChar ;
	BOOL	m_bAutoTab;
	//}}AFX_DATA
		
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMaskedEditTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX) ;
	//}}AFX_VIRTUAL
		
	// Implementation
	protected:
	HICON m_hIcon ;
		
	// Generated message map functions
	//{{AFX_MSG(CMaskedEditTestDlg)
	virtual BOOL OnInitDialog() ;
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint() ;
	afx_msg HCURSOR OnQueryDragIcon() ;
	afx_msg void OnSelendokMasks   () ;
	afx_msg void OnEditchangeMasks () ;
	afx_msg void OnChangeEditPrompt() ;
	afx_msg void OnButtonEmpty();
	afx_msg void OnCheckAutotab();
	//}}AFX_MSG
	afx_msg void OnValidateEditTest(NMHDR * pNotifyStruct, LRESULT * result);
	DECLARE_MESSAGE_MAP()
	} ;

#endif // __MaskedEditTestDlg_h__
/////////////////////////////////////////////////////////////////////////////
