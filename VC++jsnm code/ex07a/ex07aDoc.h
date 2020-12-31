// ex07aDoc.h : interface of the CEx07aDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX07ADOC_H__4A59A8DD_5797_11D0_8FCF_00C04FC2A0C2__INCLUDED_)
#define AFX_EX07ADOC_H__4A59A8DD_5797_11D0_8FCF_00C04FC2A0C2__INCLUDED_


class CEx07aDoc : public CDocument
{
protected: // create from serialization only
	CEx07aDoc();
	DECLARE_DYNCREATE(CEx07aDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx07aDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx07aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx07aDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX07ADOC_H__4A59A8DD_5797_11D0_8FCF_00C04FC2A0C2__INCLUDED_)
