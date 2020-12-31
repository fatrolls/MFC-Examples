// DriveTreeDoc.h : interface of the CDriveTreeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRIVETREEDOC_H__090B382B_959D_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_DRIVETREEDOC_H__090B382B_959D_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDriveTreeDoc : public CDocument
{
protected: // create from serialization only
	CDriveTreeDoc();
	DECLARE_DYNCREATE(CDriveTreeDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDriveTreeDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDriveTreeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDriveTreeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRIVETREEDOC_H__090B382B_959D_11D2_8E53_006008A82731__INCLUDED_)
