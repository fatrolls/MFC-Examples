// CPPTooltip_demoDoc.h : interface of the CPPTooltip_demoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CPPTOOLTIP_DEMODOC_H__2C8C9CF8_4437_4646_A12C_399A682575D0__INCLUDED_)
#define AFX_CPPTOOLTIP_DEMODOC_H__2C8C9CF8_4437_4646_A12C_399A682575D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPPTooltip_demoDoc : public CDocument
{
protected: // create from serialization only
	CPPTooltip_demoDoc();
	DECLARE_DYNCREATE(CPPTooltip_demoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPPTooltip_demoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPPTooltip_demoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPPTooltip_demoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPPTOOLTIP_DEMODOC_H__2C8C9CF8_4437_4646_A12C_399A682575D0__INCLUDED_)
