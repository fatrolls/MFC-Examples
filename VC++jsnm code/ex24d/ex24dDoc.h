// ex24dDoc.h : interface of the CEx24dDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX24DDOC_H__A9515B20_5B85_11D0_848F_00400526305B__INCLUDED_)
#define AFX_EX24DDOC_H__A9515B20_5B85_11D0_848F_00400526305B__INCLUDED_


class CEx24dDoc : public CDocument
{
protected: // create from serialization only
	CEx24dDoc();
	DECLARE_DYNCREATE(CEx24dDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx24dDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx24dDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx24dDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX24DDOC_H__A9515B20_5B85_11D0_848F_00400526305B__INCLUDED_)
