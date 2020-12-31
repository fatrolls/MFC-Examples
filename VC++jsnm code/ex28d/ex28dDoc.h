// ex28dDoc.h : interface of the CEx28dDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX28DDOC_H__BA9E33F0_958A_11D0_AAA2_444553540000__INCLUDED_)
#define AFX_EX28DDOC_H__BA9E33F0_958A_11D0_AAA2_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CEx28dDoc : public CDocument
{
private:
	void OpenOdbc();
public:
	void GetQuery();
	void PutQuery();
	void GetFieldSpecs();
	void OpenRecordset();

	CRecordset* m_pRecordset;
	CDatabase m_database;
	CStringArray m_arrayFieldName;
	CWordArray m_arrayFieldSize;
	int m_nFields;
 	int m_nRowCount;
	CString m_strConnect;
	CString m_strQuery;
	BOOL m_bConnected;

protected: // create from serialization only
	CEx28dDoc();
	DECLARE_DYNCREATE(CEx28dDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx28dDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx28dDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx28dDoc)
	afx_msg void OnRequery();
	afx_msg void OnUpdateRequery(CCmdUI* pCmdUI);
	afx_msg void OnFileOdbcConnect();
	afx_msg void OnUpdateFileOdbcConnect(CCmdUI* pCmdUI);
	afx_msg void OnFileOdbcDisconnect();
	afx_msg void OnUpdateFileOdbcDisconnect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX28DDOC_H__BA9E33F0_958A_11D0_AAA2_444553540000__INCLUDED_)
