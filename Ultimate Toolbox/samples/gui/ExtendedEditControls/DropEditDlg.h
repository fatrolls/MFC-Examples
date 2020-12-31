#if !defined(AFX_DROPEDITDLG_H__7C884D29_CFE1_11D2_A7D5_525400DAF3CE__INCLUDED_)
#define AFX_DROPEDITDLG_H__7C884D29_CFE1_11D2_A7D5_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DropEditDlg.h : header file
//

#include "OXSeparator.h"
#include "OXBrowseDirEdit.h"
#include "OXBrowseColorEdit.h"
#include "OXCalculatorEdit.h"


class CMenuEdit: public COXDropEdit<COXEdit>
{
DECLARE_DYNAMIC(CMenuEdit)

// Data members -------------------------------------------------------------
public:

protected:
	CMenu m_menu;

private:

// Member functions ---------------------------------------------------------
public:
	CMenuEdit() {
		VERIFY(m_menu.CreatePopupMenu());
		for(int nIndex=1; nIndex<=10; nIndex++)
		{
			CString sMenuText;
			sMenuText.Format(_T("Item %d"),nIndex);
			m_menu.AppendMenu(MF_STRING,nIndex,sMenuText);
		}
		AssociateMenu(&m_menu);
	};
	virtual ~CMenuEdit() {};

// Overrides
	//{{AFX_VIRTUAL(COXPhysicalEdit)
	//}}AFX_VIRTUAL

protected:
	// Generated message map functions
	//{{AFX_MSG(COXPhysicalEdit)
	//}}AFX_MSG
	afx_msg void OnMenuSelect(UINT nID);
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CDropEditDlg dialog

class CDropEditDlg : public CPropertyPage
{
	DECLARE_DYNCREATE(CDropEditDlg)

// Construction
public:
	CDropEditDlg();
	~CDropEditDlg();

// Dialog Data
	//{{AFX_DATA(CDropEditDlg)
	enum { IDD = IDD_DROPEDIT_DIALOG };
	COXCalculatorEdit	m_editCalculator;
	COXSeparator	m_sepCalculator;
	COXSeparator	m_sepMenu;
	CMenuEdit	m_editMenu;
	COXSeparator	m_sepBrowseColor;
	COXBrowseColorEdit	m_editBrowseColor;
	COXSeparator	m_sepBrowseFile;
	COXBrowseFileEdit	m_editBrowseFile;
	COXSeparator	m_sepBrowseDir32;
	COXBrowseDirEdit	m_editBrowseDir32;
	COXBrowseDirEdit16	m_editBrowseDir16;
	COXSeparator	m_sepBrowseDir16;
	BOOL	m_bLeftAligned;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDropEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDropEditDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckLeftaligned();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DROPEDITDLG_H__7C884D29_CFE1_11D2_A7D5_525400DAF3CE__INCLUDED_)
