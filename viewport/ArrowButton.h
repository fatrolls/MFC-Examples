#if !defined(AFX_ARROWBUTTON_H__1A6DA697_E016_4038_A26F_3DE7C7294E06__INCLUDED_)
#define AFX_ARROWBUTTON_H__1A6DA697_E016_4038_A26F_3DE7C7294E06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ArrowButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CArrowButton window
#include "DrawArrow.h"

class CArrowButton : public CButton
{
// Construction
public:
        CArrowButton();

// Attributes
public:

// Operations
public:
   void SetDirection(DrawArrow::Direction dir);

// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CArrowButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
        virtual ~CArrowButton();

        // Generated message map functions
protected:
        DrawArrow::Direction direction;
        //{{AFX_MSG(CArrowButton)
                // NOTE - the ClassWizard will add and remove member functions here.
        //}}AFX_MSG

        DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARROWBUTTON_H__1A6DA697_E016_4038_A26F_3DE7C7294E06__INCLUDED_)
