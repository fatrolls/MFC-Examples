// ex29adoc.h : interface of the CEx29aDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX29ADOC_H__87130E7D_8817_11D0_86C5_F5A2C72DE570__INCLUDED_)
#define AFX_EX29ADOC_H__87130E7D_8817_11D0_86C5_F5A2C72DE570__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

extern void DaoErrorMsg(CDaoException* e);

class CEx29aDoc : public CDocument
{
protected: // create from serialization only
	CEx29aDoc();
	DECLARE_DYNCREATE(CEx29aDoc)

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides

// Attributes
public:
	CDaoRecordset* m_pRecordset;
	CDaoDatabase m_database;
	CStringArray m_arrayFieldName;
	CWordArray m_arrayFieldSize;
	int m_nFields;
 	int m_nRowCount;
 	CString m_strDatabase;
	CString m_strConnect;
	CString m_strQuery;
	BOOL m_bConnected;
	enum {UNK, MDB, ISAM, ODBC} m_nDatabaseType;


public:
	virtual ~CEx29aDoc();
	//{{AFX_VIRTUAL(CEx29aDoc)
	public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	protected:
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
	virtual	BOOL OnNewDocument();
	virtual void DeleteContents();
	//}}AFX_VIRTUAL
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
public:
	void GetQuery();
	void PutQuery();
	void GetFieldSpecs();
	void OpenRecordset();
private:
	void DaoOpenMdb();
	void DaoOpenOdbc();
	void DaoOpenIsam();

// Generated message map functions
protected:
	//{{AFX_MSG(CEx29aDoc)
	afx_msg void OnRequery();
	afx_msg void OnUpdateRequery(CCmdUI* pCmdUI);
	afx_msg void OnFileDaoOpenMdb();
	afx_msg void OnFileDaoOpenOdbc();
	afx_msg void OnFileDaoOpenIsam();
	afx_msg void OnUpdateFileDaoOpen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnFileDaoDisconnect();
	afx_msg void OnUpdateFileDaoDisconnect(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX29ADOC_H__87130E7D_8817_11D0_86C5_F5A2C72DE570__INCLUDED_)
