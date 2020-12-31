/*----------------------------------------------------------------------
Debugging Applications for Microsoft .NET and Microsoft Windows
Copyright © 1997-2008 John Robbins -- All rights reserved.

Version 2.8

With excellent updates from Scott Bloom, Ching Ming Kwok,
Jeff Shanholtz, Pablo Presedo, Julian Onions and Ken Gladstone!
----------------------------------------------------------------------*/
#include "stdafx.h"
#include "CrashFinder.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "CrashFinderDoc.h"
#include "CrashFinderTreeView.h"
#include "About.h"
#include "AppOptionsDlg.h"

#include "SymbolEngine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE [] = __FILE__ ;
#endif

BEGIN_MESSAGE_MAP ( CCrashFinderApp , CWinApp )
  ON_COMMAND ( ID_APP_ABOUT     , OnAppAbout    )
  ON_COMMAND ( ID_VIEW_OPTIONS  , OnViewOptions )
  ON_COMMAND ( ID_FILE_NEW      , CWinApp::OnFileNew )
  ON_COMMAND ( ID_FILE_OPEN     , CWinApp::OnFileOpen )
END_MESSAGE_MAP ( )

CCrashFinderApp :: CCrashFinderApp ( )
                 : CWinApp ( )
{
    m_bShowFullPaths     = FALSE ;
    m_bConfirmDeletions  = TRUE  ;
    m_bInsertText        = TRUE  ;
    m_bOneLine           = TRUE  ;
    m_bShowDisplacements = FALSE ;
}

CCrashFinderApp theApp ;

BOOL CCrashFinderApp :: InitInstance ( )
{

    SetRegistryKey ( _T ( "Bugslayer" ) ) ;

    // Load standard INI file options (including MRU)
    LoadStdProfileSettings ( ) ;

    // Load the global state.
    RestoreGlobalState ( ) ;

    // Register the application's document templates.  Document
    // templates serve as the connection between documents, frame
    // windows and views.

    CMultiDocTemplate * pDocTemplate ;
    pDocTemplate =
        new CMultiDocTemplate ( IDR_CRASHFTYPE                        ,
                                RUNTIME_CLASS ( CCrashFinderDoc     ) ,
                                RUNTIME_CLASS ( CChildFrame         ) ,
                                RUNTIME_CLASS ( CCrashFinderTreeView) );
    AddDocTemplate ( pDocTemplate ) ;

    // Hook up to handle the filetypes!
    RegisterShellFileTypes ( ) ;
    EnableShellOpen ( ) ;

    // Create main MDI Frame window
    CMainFrame * pMainFrame = new CMainFrame ;
    if ( !pMainFrame->LoadFrame ( IDR_MAINFRAME ) )
    {
        return ( FALSE ) ;
    }
    m_pMainWnd = pMainFrame ;

    // Parse command line for standard shell commands, DDE, file open
    CCommandLineInfo cmdInfo ;
    ParseCommandLine ( cmdInfo ) ;

    // Knock off the empty file at startup if there was not one passed
    // on the command line.
    if ( CCommandLineInfo::FileNew == cmdInfo.m_nShellCommand )
    {
        cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing ;
    }

    // Dispatch commands specified on the command line
    if ( !ProcessShellCommand ( cmdInfo ) )
    {
        return ( FALSE ) ;
    }

    // The main window has been initialized, so show and update it.
    pMainFrame->ShowWindow ( m_nCmdShow ) ;
    pMainFrame->UpdateWindow ( ) ;

    return ( TRUE ) ;
}

int CCrashFinderApp :: ExitInstance ( )
{
    ASSERT ( this ) ;
    SaveGlobalState ( ) ;
    return ( CWinApp::ExitInstance ( ) ) ;
}


// App command to run the dialog
void CCrashFinderApp :: OnAppAbout ( )
{
    CAboutDlg aboutDlg ;
    aboutDlg.DoModal ( ) ;
}

void CCrashFinderApp :: OnViewOptions ( )
{
    CAppOptionsDlg cOptDlg ;

    // Set up to show the current state.
    cOptDlg.m_bConfirmDeletions  = m_bConfirmDeletions  ;
    cOptDlg.m_bShowFullPaths     = m_bShowFullPaths     ;
    cOptDlg.m_bOneLine           = m_bOneLine           ;
    cOptDlg.m_bInsertText	     = m_bInsertText        ;
    cOptDlg.m_bShowDisplacements = m_bShowDisplacements ;

    if ( IDOK == cOptDlg.DoModal ( ) )
    {

        // Loop through the document templates and have them loop
        // through their specific documents.
        CDocTemplate * pDocTemplate ;
        POSITION posTemplate = GetFirstDocTemplatePosition ( ) ;
        while ( NULL != posTemplate )
        {
            pDocTemplate = GetNextDocTemplate ( posTemplate ) ;
            ASSERT ( NULL != pDocTemplate ) ;
            if ( NULL != pDocTemplate )
            {
                POSITION posDoc = pDocTemplate->GetFirstDocPosition ( );
                CCrashFinderDoc * pCFDoc ;
                while ( NULL != posDoc )
                {
                    pCFDoc =
                       (CCrashFinderDoc *)pDocTemplate->
                                                    GetNextDoc(posDoc) ;
                    ASSERT ( NULL != pCFDoc ) ;

                    if ( m_bShowFullPaths != cOptDlg.m_bShowFullPaths )
                    {
                        pCFDoc->ShowFullPaths ( m_bShowFullPaths ) ;
                    }
                    if ( ( m_bOneLine != cOptDlg.m_bOneLine ) ||
                         ( m_bShowDisplacements !=
                               cOptDlg.m_bShowDisplacements )    )
                    {
                        m_bShowDisplacements =
                                        cOptDlg.m_bShowDisplacements ;
                        pCFDoc->RedoFind ( ) ;
                    }
                }
            }
        }
        // Save all the changes.
        m_bConfirmDeletions  = cOptDlg.m_bConfirmDeletions  ;
        m_bShowFullPaths     = cOptDlg.m_bShowFullPaths     ;
        m_bOneLine           = cOptDlg.m_bOneLine           ;
        m_bInsertText        = cOptDlg.m_bInsertText	    ;
        m_bShowDisplacements = cOptDlg.m_bShowDisplacements ;
    }
}

BOOL CCrashFinderApp :: ConfirmDeletions ( void ) const
{
    ASSERT ( this ) ;
    return ( m_bConfirmDeletions ) ;
}

BOOL CCrashFinderApp :: ShowFullPaths ( void ) const
{
    ASSERT ( this ) ;
    return ( m_bShowFullPaths ) ;
}

const LPCTSTR k_SHOWFULLPATHS = _T ( "ShowFullPaths" ) ;
const LPCTSTR k_CONFIRMDELETIONS = _T ( "ConfirmDeletions" ) ;
const LPCTSTR k_ONELINE = _T ( "OneLine" ) ;
const LPCTSTR k_INSERTTEXT = _T ( "InsertText" ) ;
const LPCTSTR k_SHOWDISPLACEMENTS = _T( "ShowDisplacements" ) ;

// Saves the global application state.
void CCrashFinderApp :: SaveGlobalState ( void )
{
    CString sVersion ;

    VERIFY ( sVersion.LoadString ( IDS_VERSIONREGKEY ) ) ;

    WriteProfileInt ( sVersion          ,
                      k_SHOWFULLPATHS   ,
                      m_bShowFullPaths  ) ;

    WriteProfileInt ( sVersion            ,
                      k_CONFIRMDELETIONS  ,
                      m_bConfirmDeletions  ) ;

    WriteProfileInt ( sVersion   ,
                      k_ONELINE  ,
                      m_bOneLine  ) ;

    WriteProfileInt ( sVersion   ,
                      k_INSERTTEXT  ,
                      m_bInsertText  ) ;

    WriteProfileInt ( sVersion             ,
                      k_SHOWDISPLACEMENTS  ,
                      m_bShowDisplacements  ) ;
}

// Restored the global application state.
void CCrashFinderApp :: RestoreGlobalState ( void )
{
    CString sVersion ;

    VERIFY ( sVersion.LoadString ( IDS_VERSIONREGKEY ) ) ;

    m_bShowFullPaths = (BOOL)GetProfileInt ( sVersion        ,
                                             k_SHOWFULLPATHS ,
                                             FALSE            ) ;
    m_bConfirmDeletions = (BOOL)GetProfileInt( sVersion           ,
                                               k_CONFIRMDELETIONS ,
                                               TRUE                ) ;

    m_bOneLine = (BOOL)GetProfileInt ( sVersion  ,
                                       k_ONELINE ,
                                       TRUE       ) ;

    m_bInsertText = (BOOL)GetProfileInt ( sVersion     ,
                                          k_INSERTTEXT ,
                                          TRUE          ) ;

    m_bShowDisplacements =
                        (BOOL)GetProfileInt ( sVersion             ,
                                              k_SHOWDISPLACEMENTS  ,
                                              m_bShowDisplacements  ) ;
}

