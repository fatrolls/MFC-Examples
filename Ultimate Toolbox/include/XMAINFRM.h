// ==========================================================================
// 							Class Specification : COXMainFrame
// ==========================================================================

// Header file : xmainfrm.h

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.                      
                          
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CMDIFrameWnd

//	YES	Is a Cwnd.                     
//	YES	Two stage creation (constructor & Create())
//	YES	Has a message map
//	NO Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//		This is a base class that is used to provide a basic layer
//		for all MainFrames that we want to have a bitmap and/or color shown as
//		background. Palette handling is provided. It has a subclass for the MDICLIENT.
// 		There is also some functionality to save and restore its position on
//		on the screen

// Remark:
//		***

// Prerequisites (necessary conditions):
//		***

/////////////////////////////////////////////////////////////////////////////
#ifndef __X_MAINFRAME_H__
#define __X_MAINFRAME_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

#include "xmdiclt.h"

// User message for sending palette changes to this MDI Childs
#define WM_DOREALIZE   (WM_USER + 105)

class OX_CLASS_DECL COXMainFrame : public CMDIFrameWnd
{
DECLARE_DYNAMIC(COXMainFrame)

// Data members -------------------------------------------------------------
public:
	WINDOWPLACEMENT*	m_pWindowPlacement;
	// --- The initial window placement.
	//     This is used to initially show the window
	//     The last used placement is persistently saved, and used the next time
	//     the window is created
		
protected:
   	COXMDIClient			m_XMDIClient;
	
// Member functions ---------------------------------------------------------
public:
	COXMainFrame();
	// --- In  : 
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state

	virtual BOOL CreateClient(LPCREATESTRUCT lpCreateStruct, CMenu* pWindowMenu );
   	// --- In  : lpCreateStruct : A long pointer to a CREATESTRUCT structure.
    //			 pWindowMenu : A pointer to the Window pop-up menu.
	// --- Out : 
	// --- Returns : Nonzero if successful; otherwise 0.
	// --- Effect : Creates the MDI client window that manages the CMDIChildWnd objects. 
	//				This member function should be called if you override the
	//	 			OnCreate member function directly.
	
	void InitialShowWindow(WINDOWPLACEMENT& windowPlacement, UINT nCmdShow);
	// --- In  : windowPlacement : The placement of the mainframe
	//							   that must be used the show the window initialy
	//			 nCmdShow : 
	// --- Out : 
	// --- Returns :
	// --- Effect : Show the window in the correct state

	BOOL SetPaletteState(BOOL bBackGround = TRUE);
	// --- In  : bBackGround : whether the DIB on the MDI CLIENT is treated as
	//			  			   a background image or foreground for palette selecting
	// --- Out : 
	// --- Returns : successful or not
	// --- Effect : Set this parameter always BEFORE you set a new Background

	BOOL GetPaletteState();
	// --- In  : 
	// --- Out : 
	// --- Returns : whether the DIB on the MDI CLIENT is treated as
	//			     a background or foreground image for palette selecting
	// --- Effect : 

	BOOL SetWallPaper(COLORREF rgbColor = RGB(192, 192, 192),
		EWallOrg eWallOrganisation = WP_Center , COXDIB* pDib = NULL );
	// --- In  :  rgbColor : The background color of te MDICLIENT
	//			  eWallOrganisation : the organisation of the bitmap on the MDI CLIENT
	//			  pDib : the Device Independant Bitmap to be painted on the MDI CLIENT
	// --- Out : 
	// --- Returns : Succeeded or not
	// --- Effect : Paints a DIB with a special organisation and back color on the
	//				Client area of the MDI Client of this mainframe

	virtual ~COXMainFrame();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:      
    
// Message handlers ---------------------------------------------------------
    //{{AFX_MSG(COXMainFrame)
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnClose();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()

private:                 

};

#endif
// ==========================================================================
