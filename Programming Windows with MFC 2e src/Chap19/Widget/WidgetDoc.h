// WidgetDoc.h : interface of the CWidgetDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WIDGETDOC_H__02909A4B_3F5C_11D2_AC89_006008A8274D__INCLUDED_)
#define AFX_WIDGETDOC_H__02909A4B_3F5C_11D2_AC89_006008A8274D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WidgetObj.h"
typedef CTypedPtrArray<CObArray, CWidget*> CWidgetArray;

class CWidgetDoc : public CDocument
{
protected: // create from serialization only
	CWidgetDoc();
	DECLARE_DYNCREATE(CWidgetDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWidgetDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL RemoveWidget (int nIndex);
	int AddWidget (int x, int y, COLORREF color);
	CWidget* GetWidget (int nIndex);
	int GetWidgetCount ();
	virtual ~CWidgetDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CWidgetArray m_arrWidgets;

// Generated message map functions
protected:
	//{{AFX_MSG(CWidgetDoc)
	afx_msg void OnInsertRedWidget();
	afx_msg void OnInsertBlueWidget();
	afx_msg void OnInsertYellowWidget();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIDGETDOC_H__02909A4B_3F5C_11D2_AC89_006008A8274D__INCLUDED_)
