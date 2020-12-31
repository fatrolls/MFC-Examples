// coolsb_mfctestDoc.h : interface of the CCoolsb_mfctestDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_COOLSB_MFCTESTDOC_H__DEB73C59_9153_4B5D_B5DC_D6D50665A363__INCLUDED_)
#define AFX_COOLSB_MFCTESTDOC_H__DEB73C59_9153_4B5D_B5DC_D6D50665A363__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCoolsb_mfctestDoc : public CDocument
{
protected: // create from serialization only
	CCoolsb_mfctestDoc();
	DECLARE_DYNCREATE(CCoolsb_mfctestDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCoolsb_mfctestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCoolsb_mfctestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCoolsb_mfctestDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COOLSB_MFCTESTDOC_H__DEB73C59_9153_4B5D_B5DC_D6D50665A363__INCLUDED_)
