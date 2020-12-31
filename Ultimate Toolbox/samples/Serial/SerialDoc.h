// SerialDoc.h : interface of the CSerialDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERIALDOC_H__172F9584_051F_11D2_88B0_0080C859A484__INCLUDED_)
#define AFX_SERIALDOC_H__172F9584_051F_11D2_88B0_0080C859A484__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class COXSerialCommConfig;
class COXSerialCommFile;
class CSerialView;

class CSerialDoc : public CDocument
{
protected: // create from serialization only
	CSerialDoc();
	DECLARE_DYNCREATE(CSerialDoc)

// Attributes
public:
	CSerialView* GetView() const;
	BOOL SendKeyDown(UINT nChar);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerialDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	protected:
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSerialDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	COXSerialCommFile* m_pCommFile;
	COXSerialCommConfig* m_pCommConfig;

	DWORD m_dwTxTimeout;
	DWORD m_dwRxTimeout;

	CEvent m_eventClose;

	CWinThread* m_pIncomingTextThread;
	
// Generated message map functions
protected:
	//{{AFX_MSG(CSerialDoc)
	afx_msg void OnConnect();
	afx_msg void OnUpdateConnect(CCmdUI* pCmdUI);
	afx_msg void OnDisconnect();
	afx_msg void OnUpdateDisconnect(CCmdUI* pCmdUI);
	afx_msg void OnReceive();
	afx_msg void OnUpdateReceive(CCmdUI* pCmdUI);
	afx_msg void OnSend();
	afx_msg void OnUpdateSend(CCmdUI* pCmdUI);
	afx_msg void OnSerialSetup();
	afx_msg void OnUpdateSerialSetup(CCmdUI* pCmdUI);
	afx_msg void OnSetTimeout();
	afx_msg void OnUpdateSetTimeout(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIALDOC_H__172F9584_051F_11D2_88B0_0080C859A484__INCLUDED_)
