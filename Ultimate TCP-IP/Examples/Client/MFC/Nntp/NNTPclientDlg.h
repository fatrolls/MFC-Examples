// NNTPclientDlg.h : header file
//
//{{AFX_INCLUDES()
#include "richtext.h"
//}}AFX_INCLUDES

#if !defined(AFX_NNTPCLIENTDLG_H__03D2D771_1763_11D3_87EE_0080C86498A0__INCLUDED_)
#define AFX_NNTPCLIENTDLG_H__03D2D771_1763_11D3_87EE_0080C86498A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MyNntpClass.h"
/////////////////////////////////////////////////////////////////////////////
// CNNTPclientDlg dialog

#pragma warning ( disable : 4511 4512 )

class CNNTPclientDlg : public CDialog
{
// Construction
public:
	BOOL m_bisAborted;
	CMyNntpClass m_nntpClient;
	UT_ARTICLEINFO *m_ArticleInfo;
	CUT_Msg m_currentSelectedMsg;
	CUT_MapFileDataSource* m_pMapFileDataSource;
	int m_icounter;  //counter to keep track of the items inserted
					 // in the article list control from the dialog


	// strings to be populated in the OnNGetArticleList() call back function
	// and to be used in the OnInsertItem of the article List control
	CString  m_strSubject, m_strAuthor, m_strDate, m_strRefrence, m_strBytesCount, m_strNumberOfLines ;

	// add ASCII string - called from MyNntpClass
	void AddGroup(LPCSTR groupName);

	CNNTPclientDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CNNTPclientDlg();

// Dialog Data
	//{{AFX_DATA(CNNTPclientDlg)
	enum { IDD = IDD_NNTPCLIENT_DIALOG };
	CButton	m_saveAttachBtn;
	CButton	m_chkLoadBtn;
	CComboBox	m_CBattachments;
	CStatic	m_staticWindow;
	CAnimateCtrl	m_animateWnd;
	CComboBox	m_serversCombo;
	CListBox	m_listGroup;
	CListCtrl	m_articlesList;
	BOOL	m_bLoadFromFile;
	CString	m_strGroupFileName;
	CString	m_strServerName;
	CString	m_strSelecteGroup;
	CRichText	m_richText;
	CString	m_strAttachment;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNNTPclientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CNNTPclientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConnect();
	afx_msg void OnDblclkGroupList();
	afx_msg void OnCheck1();
	virtual void OnCancel();
	afx_msg void OnOK();
	afx_msg void OnInsertitemArticlesList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkArticlesList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickArticlesList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSaveNewsGroups();
	afx_msg void OnSelchangeServersCombo();
	afx_msg void OnSave();
	afx_msg void OnPostNew();
	afx_msg void OnDlete();
	afx_msg void OnReply();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	// thread to handle the connection and the retrieval of news groups
	static unsigned __stdcall ThreadProc( LPVOID pThis);
	// thread to handle the  the retrieval of articles
	static unsigned __stdcall ArticlsThreadProc( LPVOID pThis);
	// a handle to the thread so we can check for any  currently running threads
	HANDLE	m_ThreadHandle;

};

#pragma warning ( default : 4511 4512 )

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NNTPCLIENTDLG_H__03D2D771_1763_11D3_87EE_0080C86498A0__INCLUDED_)
