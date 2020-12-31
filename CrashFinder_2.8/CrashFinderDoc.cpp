/*----------------------------------------------------------------------
Debugging Applications for Microsoft .NET and Microsoft Windows
Copyright © 1997-2008 John Robbins -- All rights reserved.

Version 2.8

With excellent updates from Scott Bloom, Ching Ming Kwok,
Jeff Shanholtz, Pablo Presedo, Julian Onions and Ken Gladstone!
----------------------------------------------------------------------*/
#include "stdafx.h"
#include "CrashFinder.h"

#include "CrashFinderDoc.h"

#include "CommonRoutines.h"

#include "SymbolEngine.h"

#include "FindView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE [] = __FILE__ ;
#endif


IMPLEMENT_DYNCREATE ( CCrashFinderDoc , CDocument )

BEGIN_MESSAGE_MAP ( CCrashFinderDoc , CDocument )
  //{{AFX_MSG_MAP(CCrashFinderDoc)
    ON_COMMAND ( ID_EDIT_FIND_CRASH         , OnEditFindCrash       )
    ON_COMMAND ( ID_EDIT_ADD_IMAGE          , OnEditAddImage        )
    ON_COMMAND ( ID_EDIT_REMOVE_IMAGE       , OnEditRemoveImage     )
    ON_COMMAND ( ID_EDIT_IMAGE_PROPERTIES   , OnEditImageProperties )
    ON_UPDATE_COMMAND_UI ( ID_EDIT_REMOVE_IMAGE , OnUpdateEditRemoveImage )
    ON_UPDATE_COMMAND_UI ( ID_EDIT_IMAGE_PROPERTIES , OnUpdateEditImageProperties )
  //}}AFX_MSG_MAP
END_MESSAGE_MAP ( )

CCrashFinderDoc :: CCrashFinderDoc ( )
                 : CDocument ( )    ,
                   m_cDataArray ( ) ,
                   m_cSymEng ( )
{
    ASSERT ( this ) ;

    m_pcTreeControl = NULL ;
    m_pcTreeView    = NULL ;
    m_pFormView     = NULL ;
    m_pEditControl  = NULL ;
}

CCrashFinderDoc :: ~CCrashFinderDoc ( )
{
    ASSERT ( this ) ;
}

BOOL CCrashFinderDoc :: OnNewDocument ( )
{
    ASSERT ( this ) ;

    // Go get a drink....
    CWaitCursor cWait ;

    if ( ( TRUE == SharedInitialization ( )     ) &&
         ( TRUE == CDocument::OnNewDocument ( ) )    )
    {
        // Let the user start adding binaries immediately.
        if ( TRUE == AddAnImage ( ) )
        {
            // Force the selection to the first item, if possible.
            HTREEITEM hItem = m_pcTreeControl->GetRootItem ( ) ;
            if ( NULL != hItem )
            {
                m_pcTreeControl->SelectItem ( hItem ) ;
            }
            return ( TRUE ) ;
        }
    }
    return ( FALSE ) ;
}

BOOL CCrashFinderDoc :: OnOpenDocument ( LPCTSTR lpszPathName )
{
    ASSERT ( this ) ;

    // Go get a drink....
    CWaitCursor cWait ;

    if ( ( TRUE == SharedInitialization ( )                   ) &&
         ( TRUE == CDocument::OnOpenDocument ( lpszPathName ) )   )
    {
        return ( TRUE ) ;
    }
    return ( FALSE ) ;
}

void CCrashFinderDoc :: OnCloseDocument ( )
{
    ASSERT ( this ) ;

    INT_PTR iCount = m_cDataArray.GetSize ( ) ;
    for ( int i = 0 ; i < iCount ; i++ )
    {
        CBinaryImage * pImage = (CBinaryImage *)m_cDataArray[ i ] ;
        ASSERT ( NULL != pImage ) ;
        delete pImage ;
    }

    // Clean out the image list I set earlier, if the tree control is a
    // valid window.
    if ( TRUE == ::IsWindow ( m_pcTreeControl->m_hWnd ) )
    {
        CImageList * pImageList =
                            m_pcTreeControl->GetImageList(TVSIL_NORMAL);
        if ( NULL != pImageList )
        {
            pImageList->DeleteImageList ( ) ;
            delete pImageList ;
        }
    }

    // Clean up the symbol engine.
    BOOL bRet = m_cSymEng.SymCleanup ( ) ;
    if ( FALSE == bRet )
    {
        ASSERT ( TRUE == bRet ) ;
        TRACE ( "m_cSymEng.SymCleanup FAILED!!!\n" ) ;
    }


    // Now that I have done my cleanup, let the main framework do it's
    // cleanup.
    CDocument::OnCloseDocument ( ) ;
}

BOOL CCrashFinderDoc :: SharedInitialization ( void )
{
    // BIG NOTE!
    // This function is called BEFORE the main framework functions for
    // document creation and loading.  Only things that rely on the
    // views can be done here.  Don't try and access any of the
    // document data as it is not valid yet.

    ASSERT ( this ) ;

    // Loop through the views looking for the one with the tree view.
    // if there are no tree views, then initialization must fail.
    POSITION pos = GetFirstViewPosition ( ) ;
    while ( NULL != pos )
    {
        CView * pView = GetNextView ( pos ) ;
        ASSERT ( NULL != pView ) ;
        if ( NULL == pView )
        {
            return ( FALSE ) ;
        }

        if ( TRUE == pView->IsKindOf ( RUNTIME_CLASS ( CTreeView ) ) )
        {
            m_pcTreeView = (CTreeView*)pView ;
            m_pcTreeControl = &m_pcTreeView->GetTreeCtrl ( ) ;
            ASSERT ( NULL != m_pcTreeControl ) ;

            if ( NULL == m_pcTreeControl )
            {
                return ( FALSE ) ;
            }
        }
        if ( TRUE == pView->IsKindOf ( RUNTIME_CLASS ( CFormView ) ) )
        {
            m_pFormView = (CFindView*)pView ;
            m_pEditControl = m_pFormView->GetHexEditControl ( ) ;
        }
    }

    ASSERT ( NULL != m_pcTreeControl ) ;
    if ( NULL == m_pcTreeControl )
    {
        return ( FALSE ) ;
    }
    ASSERT ( NULL != m_pFormView ) ;
    ASSERT ( NULL != m_pEditControl ) ;

    // Initialize the tree control and get back the font used.
    m_cTreeDisplay.InitializeTreeControl ( m_pcTreeControl ,
                                          &m_cSymEng        ) ;


    // Finally, initialize the symbol engine.
    return ( InitializeSymbolEngine ( m_cSymEng ) ) ;
}

BOOL CCrashFinderDoc :: LoadAndShowImage ( CBinaryImage * pImage       ,
                                           BOOL           bModifiesDoc ,
                                           BOOL           bIgnoreDups  )
{
    // Check the assumptions from outside the function.
    ASSERT ( this ) ;
    ASSERT ( NULL != m_pcTreeControl ) ;

    // A string that can be used for any user messages
    CString   sMsg                    ;
    // The state for the tree graphic
    int       iState = STATE_NOTVALID ;
    // A Boolean return value holder
    BOOL      bRet                    ;

    // Make sure the parameter is good.
    ASSERT ( NULL != pImage ) ;
    if ( NULL == pImage )
    {
        // Nothing much can happen with a bad pointer.
        return ( FALSE ) ;
    }

    // Check to see whether this image is valid. If it is, make sure
    // that it isn't already in the list and that it doesn't have
    // a conflicting load address. If it isn't a valid image, I add
    // it anyway because it isn't good form just to throw out user
    // data. If the image is bad, I just show it with the invalid
    // bitmap and don't load it into the symbol engine.
    if ( TRUE == pImage->IsValidImage ( ) )
    {

        // Here I walk through the items in the data array so that I can
        // look for three problem conditions:
        // 1. The binary image is already in the list. If so, I can
        //    only abort.
        // 2. The binary is going to load at an address that's already
        //    in the list. If that's the case, I'll display the
        //    Properties dialog box for the binary image so that its
        //    load address can be changed before adding it to the list.
        // 3. The project already includes an EXE image, and pImage is
        //     also an executable.

        // I always start out assuming that the data in pImage is valid.
        // Call me an optimist!
        BOOL bValid = TRUE ;
        INT_PTR iCount = m_cDataArray.GetSize ( ) ;
        for ( INT_PTR i = 0 ; i < iCount ; i++ )
        {
            CBinaryImage * pTemp = (CBinaryImage *)m_cDataArray[ i ] ;

            ASSERT ( NULL != pTemp ) ;
            if ( NULL == pTemp )
            {
                // Not much can happen with a bad pointer!
                return ( FALSE ) ;
            }

            // Do these two CString values match?
            if ( pImage->GetFullName ( ) == pTemp->GetFullName ( ) )
            {
                if ( FALSE == bIgnoreDups )
                {
                    // Tell the user!!
                    sMsg.FormatMessage ( IDS_DUPLICATEFILE      ,
                                         pTemp->GetFullName ( )  ) ;
                    AfxMessageBox ( sMsg ) ;
                }
                return ( FALSE ) ;
            }

            // If the current image from the data structure isn't
            // valid, I'm up a creek. Although I can check
            // duplicate names above, it's hard to check load
            // addresses and EXE characteristics. If pTemp isn't valid,
            // I have to skip these checks. Skipping them can lead
            // to problems, but since pTemp is marked in the list as
            // invalid, it's up to the user to reset the properties.
            if ( TRUE == pTemp->IsValidImage ( FALSE ) )
            {

                // Check that I don't add two EXEs to the project.
                if ( 0 == ( IMAGE_FILE_DLL &
                            pTemp->GetCharacteristics ( ) ) )
                {
                    if ( 0 == ( IMAGE_FILE_DLL &
                                pImage->GetCharacteristics ( ) ) )

                    {
                        // Tell the user!!
                        sMsg.FormatMessage ( IDS_EXEALREADYINPROJECT ,
                                             pImage->GetFullName ( ) ,
                                             pTemp->GetFullName ( )   ) ;
                        AfxMessageBox ( sMsg ) ;
                        // Trying to load two images marked as EXEs will
                        // automatically have the data thrown out for
                        // pImage.
                        return ( FALSE ) ;
                    }
                }

                // Check for load address conflicts.
                if ( pImage->GetLoadAddress ( ) ==
                     pTemp->GetLoadAddress( )      )
                {
                    sMsg.FormatMessage ( IDS_DUPLICATELOADADDR      ,
                                         pImage->GetFullName ( )    ,
                                         pTemp->GetFullName ( )      ) ;

                    if ( IDYES == AfxMessageBox ( sMsg , MB_YESNO ) )
                    {
                        // The user wants to change the properties by
                        // hand.
                        pImage->SetProperties ( ) ;

                        // Check that the load address really did
                        // change and that it doesn't now conflict with
                        // another binary.
                        int iIndex ;
                        if ( TRUE ==
                                IsConflictingLoadAddress (
                                               pImage->GetLoadAddress(),
                                               iIndex                 ))
                        {
                            sMsg.FormatMessage
                                          ( IDS_DUPLICATELOADADDRFINAL ,
                                            pImage->GetFullName ( )    ,
                  ((CBinaryImage*)m_cDataArray[iIndex])->GetFullName());
                            AfxMessageBox ( sMsg ) ;

                            // The data in pImage isn't valid, so go
                            //  ahead and exit the loop.
                            bValid = FALSE ;
                            break ;
                        }
                    }
                    else
                    {
                        // The data in pImage isn't valid, so go
                        // ahead and exit the loop.
                        bValid = FALSE ;
                        pImage->SetBinaryError ( eAddressConflict ) ;
                        break ;
                    }
                }
            }
        }
        if ( TRUE == bValid )
        {
            // This image is good (at least up to the symbol load).
            iState = STATE_VALIDATED ;
        }
        else
        {
            iState = STATE_NOTVALID ;
        }
    }
    else
    {
        // This image isn't valid.
        iState = STATE_NOTVALID ;
    }

    if ( STATE_VALIDATED == iState )
    {
        DWORD64 dwLoadAddress = 
           m_cSymEng.SymLoadModule64 ( NULL                          ,
                                       (PWSTR)pImage->
                                               GetFullNameString ( ) ,
                                       NULL                          ,
                                       pImage->GetLoadAddress ( )    ,
                                       0                              );
        // Watch out.  SymLoadModule returns the load address of the
        // image, not TRUE.
        bRet = ( dwLoadAddress > 0 ) ;
        ASSERT ( FALSE != bRet ) ;
        if ( FALSE == bRet )
        {
            TRACE ( "m_cSymEng.SymLoadModule failed!!\n" ) ;
            iState = STATE_NOTVALID ;
        }
        else
        {
            CImageHlp_Module cModInfo ;
            BOOL bRet2 =
                  m_cSymEng.SymGetModuleInfo64(pImage->GetLoadAddress(),
                                               &cModInfo              );
            ASSERT ( TRUE == bRet2 ) ;
            if ( TRUE == bRet2 )
            {
                // Check if the symbols type is not SymNone.
                if ( SymNone != cModInfo.SymType )
                {
                    iState = STATE_VALIDATED ;
                    // Set the image symbol information.
                    pImage->SetSymbolInformation ( cModInfo ) ;
                }
                else
                {
                    iState = STATE_NOTVALID ;
                    // Unload the module.  The symbol engine loads a
                    // module even without symbols so I need to unload
                    // them here.  I only want good loads to happen.
                    m_cSymEng.SymUnloadModule64(
                                              pImage->GetLoadAddress());
                    pImage->SetBinaryError ( eNoSymbolsAtAll ) ;
                }
            }
            else
            {
                iState = STATE_NOTVALID ;
            }
        }
    }

    // Set the extra data value for pImage to the state of the symbol
    // load.
    if ( STATE_VALIDATED == iState )
    {
        pImage->SetExtraData ( TRUE ) ;
    }
    else
    {
        pImage->SetExtraData ( FALSE ) ;
    }

    // Put this item into the array.
    m_cDataArray.Add ( pImage ) ;

    // Does adding the item modify the document?
    if ( TRUE == bModifiesDoc )
    {
        SetModifiedFlag ( ) ;
    }

    // Get the image into the tree.
    bRet = m_cTreeDisplay.InsertImageInTree ( pImage ,
                                              iState  ) ;
    ASSERT ( bRet ) ;

    // All OK, Jumpmaster!!
    return ( bRet ) ;
}

// A helper to check if a load address is already in the project.  This
// returns TRUE if the address is a conflicting address and iIndex is
// the one that it conflicts with.
BOOL CCrashFinderDoc :: IsConflictingLoadAddress ( DWORD64 dwAddr ,
                                                   int &   iIndex  )
{
    ASSERT ( this ) ;

    CBinaryImage * pImage ;
    INT_PTR iCount = m_cDataArray.GetSize ( ) ;

    for ( iIndex = 0 ; iIndex < iCount ; iIndex++ )
    {
        pImage = (CBinaryImage*)m_cDataArray[ iIndex ] ;
        if ( dwAddr == pImage->GetLoadAddress ( ) )
        {
            return ( TRUE ) ;
        }
    }
    return ( FALSE ) ;
}

int CCrashFinderDoc :: LookUpAddress ( DWORD               dwAddr     ,
                                       CString &           sModule    ,
                                       IMAGEHLP_SYMBOL64 & stIHSym    ,
                                       DWORD64 &           dwFnDispl  ,
                                       IMAGEHLP_LINE64 &   stIHLine   ,
                                       DWORD &             dwSrcDispl  )
{
    ASSERT ( this ) ;

    // Check that there there are things in the symbol engine.
    if ( 0 == m_cDataArray.GetSize ( ) )
    {
        CString sMsg ;
        VERIFY ( sMsg.LoadString ( IDS_NOMODULESLOADED ) ) ;
        AfxMessageBox ( sMsg ) ;
        return ( -1 ) ;
    }

    BOOL bSymFound  = TRUE ;
    BOOL bLineFound = TRUE ;
    BOOL bModFound  = TRUE ;

    // Try and find the module.  If this cannot be found, then it is no
    // use looking anything else up.
    CImageHlp_Module cMod ;
    bModFound = m_cSymEng.SymGetModuleInfo64( dwAddr , &cMod ) ;
    if ( FALSE == bModFound )
    {
        bSymFound = FALSE ;
        bLineFound = FALSE ;
    }
    else
    {
        // Pull out the module.
        sModule = cMod.ImageName ;

        // Look up the symbol information.
        BOOL bRet = m_cSymEng.SymGetSymFromAddr64( dwAddr        ,
                                                  &dwFnDispl    ,
                                                  &stIHSym       ) ;
        if ( FALSE == bRet )
        {
            bSymFound = FALSE ;
        }

        // Look up the line stuff.
        bRet = m_cSymEng.SymGetLineFromAddr64 ( dwAddr        ,
                                               &dwSrcDispl    ,
                                               &stIHLine       ) ;
        if ( FALSE == bRet )
        {
            bLineFound = FALSE ;
        }
    }

    int iRet = 0 ;

    if ( TRUE == bSymFound )
    {
        iRet |= eLUSYM ;
    }
    if ( TRUE == bLineFound )
    {
        iRet |= eLULINE ;
    }
    if ( TRUE == bModFound )
    {
        iRet |= eLUMOD ;
    }

    return ( iRet ) ;
}


// Called when the global application options change.
void CCrashFinderDoc :: ShowFullPaths ( BOOL bShowFull )
{
    ASSERT ( this ) ;
    ASSERT ( NULL != m_pcTreeControl ) ;
    if ( NULL == m_pcTreeControl )
    {
        return ;
    }

    // Here I will just loop through each item in the tree control and
    // using the CBinaryImage pointer stored in each tree item's extra
    // data, just change the node.
    HTREEITEM hItem = m_pcTreeControl->GetRootItem ( ) ;
    while ( NULL != hItem )
    {
        CBinaryImage * pImage =
                (CBinaryImage *)m_pcTreeControl->GetItemData ( hItem ) ;
        ASSERT ( NULL != pImage ) ;
        if ( NULL != pImage )
        {
            m_pcTreeControl->
                        SetItemText ( hItem                         ,
                                      bShowFull
                                          ? pImage->GetFullName()
                                          : pImage->GetName()       );
            hItem = m_pcTreeControl->GetNextItem ( hItem , TVGN_NEXT ) ;
        }
    }
}
void CCrashFinderDoc :: RedoFind ( void )
{
    m_pFormView->RedoFind ( ) ;
}

void CCrashFinderDoc :: Serialize ( CArchive & ar )
{
    ASSERT ( this ) ;

    int            iCount  ;
    CBinaryImage * pImage  ;

    if ( ar.IsStoring ( ) )
    {
        // Write out the count of items.
        iCount = (int)m_cDataArray.GetSize ( ) ;
        ar << iCount ;
        // Now loop through and write out each item in the array.
        for ( int i = 0 ; i < iCount ; i++ )
        {
            pImage = (CBinaryImage*)m_cDataArray[ i ] ;
            ar << pImage ;
        }
    }
    else
    {
        ar >> iCount ;
        for ( int i = 0 ; i < iCount ; i++ )
        {
            ar >> pImage ;
            LoadAndShowImage ( pImage , FALSE ) ;
        }
        // Force the selection to the first item, if possible.
        HTREEITEM hItem = m_pcTreeControl->GetRootItem ( ) ;
        if ( NULL != hItem )
        {
            m_pcTreeControl->SelectItem ( hItem ) ;
        }
    }
}

CView * CCrashFinderDoc :: GetCurrentView ( void )
{
    CMDIFrameWnd * pFrame = (CMDIFrameWnd*)AfxGetApp( )->m_pMainWnd ;
    ASSERT ( NULL != pFrame ) ;

    if ( NULL == pFrame )
    {
        return ( NULL ) ;
    }

    // Get the active MDI child window.
    CMDIChildWnd * pChild = (CMDIChildWnd *)pFrame->GetActiveFrame ( ) ;
    ASSERT ( NULL != pChild ) ;

    if ( NULL == pChild )
    {
        return ( NULL ) ;
    }

    // Get the active view attached to the active MDI child window.
    CView * pView = pChild->GetActiveView ( ) ;

    return ( pView ) ;

}

#ifdef _DEBUG
void CCrashFinderDoc :: AssertValid ( ) const
{
    ASSERT ( this ) ;

    CDocument::AssertValid ( ) ;
}

void CCrashFinderDoc :: Dump ( CDumpContext & dc ) const
{
    ASSERT ( this ) ;

    // Dump the basic stuff.
    CDocument::Dump ( dc ) ;

    // Now dump this document's specific stuff.
    dc << _T ( "m_pcTreeControl " ) << m_pcTreeControl ;
    dc << _T ( "m_cDataArray    " ) << m_cDataArray    ;

}
#endif //_DEBUG

void CCrashFinderDoc :: OnEditFindCrash ( )
{
    ASSERT ( this ) ;
    m_pEditControl->SetFocus ( ) ;
}

void CCrashFinderDoc :: OnEditAddImage ( void )
{
    AddAnImage ( ) ;
}

BOOL CCrashFinderDoc :: AddAnImage ( void )
{
    ASSERT ( this ) ;

    BOOL bRet = TRUE ;

    CString szFilter ;
    CString szTitle  ;

    // Get the filter list and the title of the dialog.
    VERIFY ( szFilter.LoadString ( IDS_ADDFILTER ) ) ;
    VERIFY ( szTitle.LoadString ( IDS_ADDTITLE ) ) ;

    // The open file dialog.
    CFileDialog cFD ( TRUE                      ,
                      NULL                      ,
                      NULL                      ,
                      OFN_ALLOWMULTISELECT  |
                        OFN_FILEMUSTEXIST   |
                        OFN_NOCHANGEDIR     |
                        OFN_PATHMUSTEXIST   |
                        OFN_HIDEREADONLY        ,
                      szFilter                  ,
                      AfxGetApp()->m_pMainWnd    ) ;

    cFD.m_ofn.lpstrTitle = (LPCTSTR)szTitle ;

    // Set up the buffers that will be used to return the file
    // information.  Since the dialog allows multple selection, I make
    // sure to allocate a big enough buffer to handle a good number
    // of files.
    #define MAXFILEOPENSIZE 16384
    LPTSTR szFileName = new TCHAR[ MAXFILEOPENSIZE ] ;
    szFileName[ 0 ] = _T ( '\0' ) ;
    cFD.m_ofn.lpstrFile = szFileName ;
    cFD.m_ofn.nMaxFile = MAXFILEOPENSIZE ;

    LPTSTR szFileTitle = new TCHAR[ MAXFILEOPENSIZE ] ;
    szFileTitle[ 0 ] = _T ( '\0' ) ;
    cFD.m_ofn.lpstrFileTitle = szFileTitle ;
    cFD.m_ofn.nMaxFileTitle = MAXFILEOPENSIZE ;

    // Prompt the user.
    if ( IDOK == cFD.DoModal ( ) )
    {
        // Loop through get each file.
        CString sFinalList ;
        CString sCurr      ;

        POSITION pos = cFD.GetStartPosition ( ) ;
        while ( NULL != pos )
        {
            // Get the file name.
            sCurr = cFD.GetNextPathName ( pos ) ;
            sCurr.MakeUpper ( ) ;

            // Allocate the individual file information.
            CBinaryImage * pImage = new CBinaryImage ( sCurr ) ;

            // Only do the work if the image is valid.
            if ( TRUE == pImage->IsValidImage ( ) )
            {
                // Load and show the image.
                if ( FALSE == LoadAndShowImage ( pImage ) )
                {
                    delete pImage ;
                    bRet = FALSE ;
                }
                else
                {

                    // Load this image 's dlls
                    CMapStringToPtr moduleList ;

                    CString strDllImageName ;
                    LPVOID pPtr ;
                    if ( TRUE == pImage->GetModules ( sCurr      ,
                                                      moduleList  ) )
                    {
                        // GetModules will add sCurr into the moduleList
                        // for ensuring sCurr will not be reload later.
                        // remove it here
                        moduleList.RemoveKey ( sCurr ) ;

                        POSITION mlPos=moduleList.GetStartPosition ( ) ;
                        while ( NULL != mlPos )
                        {
                            moduleList.GetNextAssoc ( mlPos           ,
                                                      strDllImageName ,
                                                      pPtr            );
                            CBinaryImage* pDllImage =
                                      new CBinaryImage(strDllImageName);
                            // Load and show the image.  Note that I
                            // will not show any message boxes for
                            // duplicate items here.
                            if ( FALSE == LoadAndShowImage ( pDllImage ,
                                                             TRUE      ,
                                                             TRUE     ))
                            {
                                delete pDllImage ;
                                //bRet = FALSE ;
                            }
                        }
                    }
                }
            }
            else
            {
                delete pImage ;
                bRet = FALSE ;
            }
        }
    }
    else
    {
        bRet = FALSE ;
    }

    // Get rid of the memory we allocated for the file buffer.
    delete [] szFileName ;
    delete [] szFileTitle ;

    return ( bRet ) ;
}

void CCrashFinderDoc :: OnEditRemoveImage ( )
{
    ASSERT ( this ) ;
    ASSERT ( NULL != m_pcTreeControl ) ;
    if ( NULL == m_pcTreeControl )
    {
        return ;
    }

    // A general scratch buffer.
    CString sMsg ;

    // Make sure something is selected.
    HTREEITEM hItem = m_pcTreeControl->GetSelectedItem ( ) ;
    ASSERT ( NULL != hItem ) ;

    // Get the CBinaryImage out of the tree node extra data.
    CBinaryImage * pImage =
                (CBinaryImage *)m_pcTreeControl->GetItemData ( hItem ) ;
    ASSERT ( NULL != pImage ) ;
    // Am I supposed to confirm deletions?
    CCrashFinderApp * pApp = (CCrashFinderApp *)AfxGetApp ( ) ;
    ASSERT ( NULL != pApp ) ;

    if ( ( NULL == pImage ) || ( NULL == pApp ) )
    {
        VERIFY ( sMsg.LoadString ( IDS_CATASTROPHICFAILURE ) ) ;
        AfxMessageBox ( sMsg ) ;
        return ;
    }


    if ( TRUE == pApp->ConfirmDeletions ( ) )
    {
        sMsg.FormatMessage ( IDS_CONFIRMREMOVE       ,
                             pImage->GetFullName ( )  ) ;

        if ( IDNO == AfxMessageBox ( sMsg , MB_YESNO ) )
        {
            // Get out now.
            return ;
        }
    }

    // Loop through each item in the data array until I find this item.
    INT_PTR iCount = m_cDataArray.GetSize ( ) ;
    int iIndex = 0 ;
    for ( ; iIndex < iCount ; iIndex++ )
    {
        if ( pImage == m_cDataArray[ iIndex ] )
        {
            break ;
        }
    }
    ASSERT ( iIndex < iCount ) ;

    if ( iIndex == iCount )
    {
        VERIFY ( sMsg.LoadString ( IDS_CATASTROPHICFAILURE ) ) ;
        AfxMessageBox ( sMsg ) ;
        return ;
    }

    // Remove this image from the symbol engine.
    BOOL bRet;
    if ( TRUE == pImage->GetExtraData ( ) )
    {
        bRet= m_cSymEng.SymUnloadModule64 ( pImage->GetLoadAddress ( ) );
    }

    // Remove this item from the data structure.
    delete pImage ;
    m_cDataArray.RemoveAt ( iIndex ) ;

    // Now remove this item from the tree.
    bRet = m_pcTreeControl->DeleteItem ( hItem ) ;
    ASSERT ( TRUE == bRet ) ;

    // Set the selected item to the top item in the list.
    hItem = m_pcTreeControl->GetRootItem ( ) ;
    if ( NULL != hItem )
    {
        m_pcTreeControl->SelectItem ( hItem ) ;
    }

    // Mark the document as dirty.
    SetModifiedFlag ( ) ;
}

void CCrashFinderDoc :: OnEditImageProperties ( )
{
    ASSERT ( this ) ;
    // Make sure something is selected.
    HTREEITEM hItem = m_pcTreeControl->GetSelectedItem ( ) ;
    ASSERT ( NULL != hItem ) ;

    // Get the CBinaryImage out of the tree node extra data.
    CBinaryImage * pImage =
                (CBinaryImage *)m_pcTreeControl->GetItemData ( hItem ) ;
    if ( NULL == pImage )
    {
        //Get the parent item then.
        hItem = m_pcTreeControl->GetParentItem ( hItem ) ;
        pImage = (CBinaryImage *)m_pcTreeControl->GetItemData ( hItem );
        ASSERT ( NULL != pImage ) ;
        if ( NULL == pImage )
        {
            return ;
        }
    }

    // Make a copy of the binary image so I don't screw anything up.
    CBinaryImage cTemp ( *pImage ) ;
    // Now ask the CBinaryImage to take care of it's own properties.
    // However, to make sure that the user does not accidentally cause
    // a load address conflict, I watch the new value and make sure not
    // to let it happen.
    DWORD64 dwOldAddr = cTemp.GetLoadAddress ( ) ;
    if ( TRUE == cTemp.SetProperties ( ) )
    {
        BOOL bGood = FALSE ;

        do
        {
            int iIndex ;
            if ( FALSE ==
                    IsConflictingLoadAddress(cTemp.GetLoadAddress ( ),
                                             iIndex                   ))
            {
                bGood = TRUE ;
                break ;
            }
            else
            {
                // Force the old address back and see if the user wants
                // to reset the properties.

                CString sMsg ;
                sMsg.FormatMessage
                              ( IDS_DUPLICATELOADADDR      ,
                                cTemp.GetFullName ( )      ,
                  ((CBinaryImage*)m_cDataArray[iIndex])->GetFullName());

                if ( IDYES == AfxMessageBox ( sMsg , MB_YESNO ) )
                {
                    cTemp.SetLoadAddress ( dwOldAddr ) ;

                    if ( FALSE == cTemp.SetProperties ( ) )
                    {
                        break ;
                    }
                }
                else
                {
                    break ;
                }
            }

        } while ( FALSE == bGood ) ;

        // If everything is copacetic, do the actual change.
        if ( TRUE == bGood )
        {
            BOOL bRet ;

            BOOL bOriginalGoodLoad = pImage->GetExtraData ( ) ;

            // Remove this image from the symbol engine if they were
            // loaded in the first place.
            if ( TRUE == pImage->GetExtraData ( ) )
            {
                bRet =
                  m_cSymEng.SymUnloadModule64(pImage->GetLoadAddress());
                ASSERT ( FALSE != bRet ) ;
            }

            // Overwrite the item with the new data.
            *pImage = cTemp ;

            // Reload the symbol information with the new base address.
            LPCTSTR szFullName = (LPCTSTR)pImage->GetFullName ( ) ;
            bRet = (BOOL)
               m_cSymEng.SymLoadModule64( NULL                      ,
                                         (PCTSTR)szFullName         ,
                                         NULL                       ,
                                         pImage->GetLoadAddress ( ) ,
                                         0                           ) ;
            ASSERT ( FALSE != bRet ) ;

            // Set the item image based on how the symbol load went.
            int iState = STATE_NOTVALID ;
            if ( FALSE != bRet )
            {
                // Set the extra data value to show the symbol load.
                pImage->SetExtraData ( TRUE ) ;
                iState = STATE_VALIDATED ;
            }
            else
            {
                // No symbols loaded.
                pImage->SetExtraData ( FALSE ) ;
            }

            m_pcTreeControl->SetItemImage ( hItem , iState , iState ) ;



            bRet = m_cTreeDisplay.UpdateImageStats ( hItem             ,
                                                     pImage            ,
                                                     bOriginalGoodLoad);
            ASSERT ( TRUE == bRet ) ;

        }
    }
}

void CCrashFinderDoc :: OnUpdateEditRemoveImage ( CCmdUI * pCmdUI )
{
    ASSERT ( this ) ;

    // You can only remove an item when the tree view is active.
    CTreeView * pView = (CTreeView *)GetCurrentView ( ) ;

    BOOL bEnable = FALSE ;
    if ( pView == m_pcTreeView )
    {
        if ( m_pcTreeControl->GetCount ( ) > 0 )
        {
            bEnable = TRUE ;
        }
    }

    pCmdUI->Enable ( bEnable ) ;
}

void CCrashFinderDoc :: OnUpdateEditImageProperties ( CCmdUI * pCmdUI )
{
    ASSERT ( this ) ;

    // 1.  The tree view has to be active.
    // 2.  An item has to be selected.
    // 3.  That item must be properly loaded.

    CTreeView * pView = (CTreeView *)GetCurrentView ( ) ;

    BOOL bEnable = FALSE ;
    if ( pView == m_pcTreeView )
    {
        HTREEITEM hItem = m_pcTreeControl->GetSelectedItem ( ) ;

        if ( NULL != hItem )
        {
            CBinaryImage * pImage = (CBinaryImage *)
                                 m_pcTreeControl->GetItemData ( hItem );
            if ( NULL == pImage )
            {
                hItem = m_pcTreeControl->GetParentItem ( hItem ) ;
                pImage = (CBinaryImage *)
                                 m_pcTreeControl->GetItemData ( hItem );
                if ( NULL != pImage )
                {
                    bEnable = pImage->GetExtraData ( ) ;
                }
            }
            else
            {
                bEnable = pImage->GetExtraData ( ) ;
            }
        }
    }

    pCmdUI->Enable ( bEnable ) ;
}

