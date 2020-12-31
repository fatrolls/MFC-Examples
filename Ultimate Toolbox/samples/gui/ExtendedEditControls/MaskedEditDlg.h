// MaskedEditDlg.h : header file
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __MaskedEditDlg_h__
#define __MaskedEditDlg_h__


#include "OXMaskedEdit.h"    // COXMaskedEdit
#include "OXSeparator.h"

/////////////////////////////////////////////////////////////////////////////
// CMaskedEditDlg dialog

class CMaskedEditDlg : public CPropertyPage
{
// Construction
public:
	CMaskedEditDlg() ;
	
	// Dialog Data
protected:
	//{{AFX_DATA(CMaskedEditDlg)
	enum { IDD = IDD_MASKEDEDIT_DIALOG };
	COXSeparator	m_sepBottom;
	COXMaskedEdit m_editMasked;
	CComboBox     m_comboMasks;
	CString       m_csPromptChar;
	BOOL	m_bAutoTab;
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMaskedEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX) ;
	//}}AFX_VIRTUAL
	
// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CMaskedEditDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelendokMasks();
	afx_msg void OnEditchangeMasks();
	afx_msg void OnChangeEditPrompt();
	afx_msg void OnButtonEmpty();
	afx_msg void OnCheckAutotab();
	//}}AFX_MSG
	afx_msg void OnValidateEditTest(NMHDR * pNotifyStruct, LRESULT * result);
	DECLARE_MESSAGE_MAP()
};

#endif // __MaskedEditDlg_h__
/////////////////////////////////////////////////////////////////////////////
