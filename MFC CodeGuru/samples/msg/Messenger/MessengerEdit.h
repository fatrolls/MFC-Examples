#if !defined(AFX_MESSENGEREDIT_H__56E4C8D5_EF17_11D1_B810_0060084C3BF4__INCLUDED_)
#define AFX_MESSENGEREDIT_H__56E4C8D5_EF17_11D1_B810_0060084C3BF4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MessengerEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMessengerEdit view

class CMessengerEdit : public CEditView
{
protected:
	CMessengerEdit();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMessengerEdit)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessengerEdit)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMessengerEdit();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMessengerEdit)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSENGEREDIT_H__56E4C8D5_EF17_11D1_B810_0060084C3BF4__INCLUDED_)
