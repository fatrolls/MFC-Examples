// ==========================================================================
// 						Class Specification : COXMDIClient
// ==========================================================================

// Header file : xmdiclt.h

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.                      
                          
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CWnd

//	YES	Is a Cwnd.                     
//	YES	Two stage creation (constructor & Create())
//	YES	Has a message map
//	NO	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
// 		This class implements a MDIClient area. This is the window in the client area
//		of the MDiFrameWindow and which manages all the mdichild framewindows
//		This implementation takes care of painting a bitmap on its paint DC

// Remark:

// Prerequisites (necessary conditions):

/////////////////////////////////////////////////////////////////////////////

#ifndef __XMDICLT_H__
#define __XMDICLT_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

#include "oxdib.h"			// Encapsulation of a Device independant bitmap
#include "screen.h"			// Enumeration of possible screen organisations


// User message for sending palette changes to this MDI CLIENT
#define WM_DOMDICLTREALIZE   (WM_USER + 104)

class OX_CLASS_DECL COXMDIClient : public CWnd
{
// Data members -------------------------------------------------------------
public:
protected:
	COXDIB		m_bmpBackGround;
	CPalette*	m_pPictPalette;
	CBitmap*	m_pTotalNewBitmap;
	COLORREF	m_rgbBkColor;
	EWallOrg	m_eWallPaperOrganisation;

	CSize		m_sizeClient;
	CSize 		m_DibSize;
	
	HBITMAP		m_hOldDestBitmap;
	HBITMAP		m_hOldSrcBitmap;
	CDC			m_MemDCSrc;
	CDC			m_MemDCDest;

    BOOL		m_bFirstCreation;
	BOOL		m_bBackGround;
	BOOL		m_bWin4;

	static  WNDPROC pfnSuper;

// Member functions ---------------------------------------------------------
public:
	COXMDIClient();
	// --- In  : 
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state

	virtual ~COXMDIClient();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object

	BOOL SetPaletteState(BOOL bBackGround = TRUE, EPalUpdate ePalUpdate = PU_IntelUpdate);
	// --- In  : bBackGround : whether the DIB on the MDI CLIENT is treated as
	//			  			   a background image or foreground for palette selecting
	//			 ePalUpdate	: Specifying PU_NoUpdate causes the palette not to be realized now
	//						  Specifying PU_IntelUpdate causes the palette to be realized intelligently
	//						  Specifying PU_ForceUpdate causes the palette to be realized now
	// --- Out : 
	// --- Returns : successful or not
	// --- Effect : Set this parameter always BEFORE you set a new Background

	BOOL GetPaletteState();
	// --- In  : 
	// --- Out : 
	// --- Returns : whether the DIB on the MDI CLIENT is treated as
	//			     a background or foreground image for palette selecting
	// --- Effect : 

	BOOL SetNewBackGround(COLORREF rgbColor = GetSysColor(COLOR_APPWORKSPACE),
		EWallOrg eWallOrganisation = WP_Center , COXDIB* pDib = NULL );
	// --- In  :  rgbColor : The background color of te MDICLIENT
	//			  eWallOrganisation : the organisation of the bitmap on the MDI CLIENT
	//			  pDib : the Device Independant Bitmap to be painted on the MDI CLIENT
	// --- Out : 
	// --- Returns : Succeeded or not
	// --- Effect : Paints a DIB with a special organisation and back color on the
	//				client area of this MDI client window
    
	virtual WNDPROC* GetSuperWndProcAddr();
	// --- In  :
	// --- Out : 
	// --- Returns : The address in which to store the default WndProc for this class. 
	// --- Effect : Needed when we subclass a Windows object


protected:
	BOOL PrepareMemDC(int nWidth, int nHeight);
	
// Message handlers ---------------------------------------------------------
	// Generated message map functions
	//{{AFX_MSG(COXMDIClient)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	afx_msg LRESULT OnDoMDICltRealize(WPARAM wParam, LPARAM lParam);  // user message
	DECLARE_MESSAGE_MAP()
};

#endif
/////////////////////////////////////////////////////////////////////////////
