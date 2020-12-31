// SSIDialog.h : header file
//

#if !defined(_SSIDIALOG_H_)
#define _SSIDIALOG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxtempl.h>

#include "PageDialog.h"
#include "SSITaskbarIcon.h"

#include "OXLayoutManager.h"
#include "OXShortcutBar.h"
#include "OXSeparator.h"
#include "OXBitmapButton.h"

typedef struct _tagPAGEDIALOG
{
	CPageDialog* pPageDialog;
	UINT nTemplateID;

	// constructor
	_tagPAGEDIALOG(CPageDialog* pPage=NULL, UINT nID=0)
	{
		pPageDialog=pPage;
		nTemplateID=nID;
	}

	// destructor
	~_tagPAGEDIALOG()
	{
		if(pPageDialog!=NULL)
		{
			if(::IsWindow(pPageDialog->GetSafeHwnd()))
				pPageDialog->DestroyWindow();
			delete pPageDialog;
		}
	}

	// copy constructor
	_tagPAGEDIALOG& operator=(const _tagPAGEDIALOG& page)
	{
		pPageDialog=page.pPageDialog;
		nTemplateID=page.nTemplateID;
		return *this;
	}

} PAGEDIALOG;

typedef CArray<PAGEDIALOG,PAGEDIALOG&> CPageArray;

/////////////////////////////////////////////////////////////////////////////
// CSSIDialog dialog

class CSSIDialog : public CDialog
{
// Construction
public:
	CSSIDialog(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSSIDialog)
	enum { IDD = IDD_SSI_DIALOG };
	COXSeparator	m_ctlBottomSeparator;
	COXBitmapButton	m_btnRefresh;
	COXSeparator	m_ctlTopic;
	COXShortcutBar	m_shb;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSSIDialog)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	void Initialize();
	void IniTaskbarIcon();
	CRect GetPageRect();

// Implementation
public:

protected:
	CImageList m_ilLarge;
	CImageList m_ilSmall;

	HICON m_hIcon;
	CSSITaskbarIcon m_TaskbarIcon;
	COXLayoutManager m_LayoutManager;

	BOOL m_bInitialized;

	CPageArray m_arrPages;
	int m_nActivePage;

	// Generated message map functions
	//{{AFX_MSG(CSSIDialog)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnButtonRefresh();
	//}}AFX_MSG
	afx_msg void OnRestore();
	afx_msg void OnClose();
	afx_msg void OnAbout();

	afx_msg void OnActivateItem(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnSHBContextMenu(NMHDR* pNotifyStruct, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(_SSIDIALOG_H_)

