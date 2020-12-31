//--------------------------------------------------------------------------//
//                                                                          //
// Using the property control in a view                                     //
//                                                                          //
// 1) Create a new default CView inherited class                            //
// 2) Change baseclass of your new class from CView to EGridView            //
//        Dont forget to change base class in IMPLEMENT_DYNCREATE() etc..   //
// 3) Make sure your project links to propertylib                           //
//        Set dependency on the propertylib for your project, and linker    //
//        will be able to find the .lib                                     //
//--------------------------------------------------------------------------//

#ifndef EGRIDVIEW_H
#define EGRIDVIEW_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class EProperty;
class IPropertyHost;

#include "EGridCtrl.h"
#include "IPropertyChangeListener.h"

class EGridView : public CView , public IPropertyChangeListener
{

protected:

	EGridCtrl m_GridCtrl;

	EGridView();

public:
		
	virtual ~EGridView();

	DECLARE_DYNCREATE(EGridView);
	DECLARE_MESSAGE_MAP();

protected:

	//{{AFX_MSG(EGridView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	//{{AFX_VIRTUAL(EGridView)
	public:
	virtual void OnDraw(CDC* pDC);
//	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

	//
	//
	//

//	void SetGridModel( IGridModel* pModel );

public:

};

//{{AFX_INSERT_LOCATION}}

#endif
