/*----------------------------------------------------------------------
Debugging Applications for Microsoft .NET and Microsoft Windows
Copyright © 1997-2008 John Robbins -- All rights reserved.

Version 2.8

With excellent updates from Scott Bloom, Ching Ming Kwok,
Jeff Shanholtz, Pablo Presedo, Julian Onions and Ken Gladstone!
----------------------------------------------------------------------*/
#if !defined ( _CRASHFINDERDOC_H )
#define _CRASHFINDERDOC_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "BinaryImage.h"

#include "SymbolEngine.h"

#include "CommonRoutines.h"

#include "FindView.h"


class CCrashFinderDoc : public CDocument
{
protected   :

    CCrashFinderDoc ( ) ;

    DECLARE_DYNCREATE ( CCrashFinderDoc )

public      :

public      :
    virtual BOOL OnNewDocument ( ) ;
    virtual BOOL OnOpenDocument ( LPCTSTR lpszPathName ) ;
    virtual void OnCloseDocument ( ) ;
    virtual void Serialize ( CArchive & ar ) ;

public      :
    virtual ~CCrashFinderDoc ( ) ;

#ifdef _DEBUG
    virtual void AssertValid ( ) const ;
    virtual void Dump ( CDumpContext & dc ) const ;
#endif

    // Called when the global application options change.
    void ShowFullPaths ( BOOL bShowFull ) ;
    void RedoFind ( void ) ;

    // A helper function to look up the specified address and fill in
    // the symbol data structures.
    int LookUpAddress ( DWORD               dwAddr     ,
                        CString &           sModule    ,
                        IMAGEHLP_SYMBOL64 & stIHSym    ,
                        DWORD64 &           dwFnDispl  ,
                        IMAGEHLP_LINE64 &   stIHLine   ,
                        DWORD &             dwSrcDispl  ) ;

    CSymbolEngine * GetSymbolEngine ( void )
    {
        return ( &m_cSymEng ) ;
    }

protected   :
    // The function that does the shared initialization for new and
    // opened documents.
    virtual BOOL SharedInitialization ( void ) ;

    // The function that does the actual work to load a binary image
    // into the symbol engine and show it in the tree.
    BOOL LoadAndShowImage ( CBinaryImage * pImage               ,
                            BOOL           bModifiesDoc = TRUE  ,
                            BOOL           bIgnoreDups  = FALSE  ) ;

    // A helper to get the current view for the document.
    CView * GetCurrentView ( void ) ;

    // A helper to check if a load address is already in the project.
    // This returns TRUE if the address is a conflicting address.
    BOOL IsConflictingLoadAddress ( DWORD64 dwAddr , int & iIndex ) ;

    // Adds an image to the tree.
    BOOL AddAnImage ( void ) ;

    // Generated message map functions
protected   :
    //{{AFX_MSG(CCrashFinderDoc)
    afx_msg void OnEditFindCrash ( ) ;
    afx_msg void OnEditAddImage ( ) ;
    afx_msg void OnEditRemoveImage ( ) ;
    afx_msg void OnEditImageProperties ( ) ;
    afx_msg void OnUpdateEditRemoveImage ( CCmdUI * pCmdUI ) ;
    afx_msg void OnUpdateEditImageProperties ( CCmdUI * pCmdUI ) ;
    //}}AFX_MSG


    DECLARE_MESSAGE_MAP ( )

////////////////////////////////////////////////////////////////////////
//                       Protected Data Members
////////////////////////////////////////////////////////////////////////
protected   :
    // The tree control from the tree view.
    CTreeCtrl *     m_pcTreeControl ;
    // The tree view itself.
    CTreeView *     m_pcTreeView    ;
    // The form view which contains the find stuff.
    CFindView *     m_pFormView     ;
    // The edit control in the form view.
    CEdit *         m_pEditControl  ;

    // The data structure that holds all the items.
    CObArray        m_cDataArray    ;

    // The symbol engine itself for this instance of the document.
    CSymbolEngine   m_cSymEng       ;

    CString         m_strAddresses  ;

    // The display and action class for the tree control.
    CrashFinderTreeDisplay m_cTreeDisplay ;
} ;

//{{AFX_INSERT_LOCATION}}

#endif // !_CRASHFINDERDOC_H
