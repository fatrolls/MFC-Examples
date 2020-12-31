// ex07bDoc.h : interface of the CEx07bDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX07BDOC_H__1096E32D_5958_11D0_8FCF_00C04FC2A0C2__INCLUDED_)
#define AFX_EX07BDOC_H__1096E32D_5958_11D0_8FCF_00C04FC2A0C2__INCLUDED_


class CEx07bDoc : public CDocument
{
protected: // create from serialization only
	CEx07bDoc();
	DECLARE_DYNCREATE(CEx07bDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx07bDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx07bDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx07bDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX07BDOC_H__1096E32D_5958_11D0_8FCF_00C04FC2A0C2__INCLUDED_)
