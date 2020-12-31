// ex23cDoc.h : interface of the CEx23cDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX23CDOC_H__4F329AF9_5DF1_11D0_848F_00400526305B__INCLUDED_)
#define AFX_EX23CDOC_H__4F329AF9_5DF1_11D0_848F_00400526305B__INCLUDED_


class CEx23cDoc : public CDocument
{
protected: // create from serialization only
	CEx23cDoc();
	DECLARE_DYNCREATE(CEx23cDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx23cDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx23cDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx23cDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX23CDOC_H__4F329AF9_5DF1_11D0_848F_00400526305B__INCLUDED_)
