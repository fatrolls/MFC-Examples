// mltithrd.h : main header file for the MLTITHRD application
//

#if !defined(AFX_MLTITHRD_H__3C3D7AC8_B569_11D0_968D_444553540000__INCLUDED_)
#define AFX_MLTITHRD_H__3C3D7AC8_B569_11D0_968D_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
        #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMltithrdApp:
// See mltithrd.cpp for the implementation of this class
//

class CMltithrdApp : public CWinApp
{
public:
        CMltithrdApp();

// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CMltithrdApp)
        public:
        virtual BOOL InitInstance();
        //}}AFX_VIRTUAL

// Implementation

        //{{AFX_MSG(CMltithrdApp)
        afx_msg void OnAppAbout();
                // NOTE - the ClassWizard will add and remove member functions here.
                //    DO NOT EDIT what you see in these blocks of generated code !
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MLTITHRD_H__3C3D7AC8_B569_11D0_968D_444553540000__INCLUDED_)
