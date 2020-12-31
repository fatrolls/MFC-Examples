// ex08bDoc.h : interface of the CEx08bDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX08BDOC_H__13D86A3F_5BC8_11D0_8FD1_00C04FC2A0C2__INCLUDED_)
#define AFX_EX08BDOC_H__13D86A3F_5BC8_11D0_8FD1_00C04FC2A0C2__INCLUDED_


class CEx08bDoc : public CDocument
{
protected: // create from serialization only
	CEx08bDoc();
	DECLARE_DYNCREATE(CEx08bDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx08bDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx08bDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx08bDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX08BDOC_H__13D86A3F_5BC8_11D0_8FD1_00C04FC2A0C2__INCLUDED_)
