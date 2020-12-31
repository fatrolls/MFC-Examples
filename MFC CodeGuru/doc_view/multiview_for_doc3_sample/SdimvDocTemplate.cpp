// Created by: Yog Sothoth
// Company: The Old Gods
// More Info: Niarlhetothep@Cyberdude.com
// Home Page: http://www.geocities.com/SiliconValley/Peaks/2976/

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @doc
// @module SdiMvDocTemplate.cpp | 
//         This module allow you to use a single document with multiple
//         view.
// @End -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Start =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Include file section.
// ------------------------------------------------------------------------
// Precompile header.
#include "stdafx.h"

// Class definition file.
#include "SdiMvDocTemplate.h"

// Afx privae include file.
#include <AfxPriv.h>
// End =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Start =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Macro definition.
// ------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(CFrameTemplate, CMultiDocTemplate)
// End =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Start =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Initialization method.
// ------------------------------------------------------------------------
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (IMPLEMENTATION)
//          <c CFrameTemplate> <nl>
//          Constructor.<nl>
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
CFrameTemplate::CFrameTemplate(
     UINT _nIDResource,             // @Parm The menu ressource id.
     CRuntimeClass* _pFrameClass,   // @Parm The frame runtime class.
     CRuntimeClass* _pViewClass,    // @Parm The view runtime class.
     UINT _nEventID,                // @Parm The Event id to load the window.
     UINT _nDefaultWndStatus,       // @Parm The default window state at loading.
                                    // @flag SW_HIDE             | Make it hide.
                                    // @flag SW_SHOWNORMAL       | Show it normaly.
                                    // @flag SW_SHOWMINIMIZED    | Show it maximized.
                                    // @flag SW_SHOWMAXIMIZED    | Show it minimized.
                                    // @flag SW_SHOWNOACTIVATE   | Show it and don't activate it.
                                    // @flag SW_SHOW             | Show it normally.
                                    // @flag SW_SHOWMINNOACTIVE  | Show it minimized and don't activate it.
                                    // @flag SW_SHOWNA           | Don't show it activate.
                                    // @flag SW_RESTORE          | Restore it.
     BOOL _bLoadAtStartup )         // @Parm The flag to specify if the frame must be load at the startup.
     : CMultiDocTemplate( _nIDResource, NULL, _pFrameClass, _pViewClass )
{
    // Save the parameter that are needed by us.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    m_nEventID = _nEventID;
    m_bLoadAtStartup = _bLoadAtStartup;
	m_nDefaultWndStatus = _nDefaultWndStatus;
    m_pDocument = NULL;
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (IMPLEMENTATION)
//          <c CFrameTemplate> <nl>
//          Destructor.<nl>
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
CFrameTemplate::~CFrameTemplate( void )
{
}
// End =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Start =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Information retrieving method.
// ------------------------------------------------------------------------
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (IMPLEMENTATION)
//          <c CFrameTemplate> <nl>
//          When the event id is generated, the frame is loaded. Return 
//          this event ID.<nl>
// @rdesc   The frame event id.
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
UINT CFrameTemplate::GetEventID( void )
{
    // Return the Event id that allow the user to open the frame.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    return m_nEventID;
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (IMPLEMENTATION)
//          <c CFrameTemplate> <nl>
//          If the flag is On, when the document is loaded, the frame is 
//          created.  Return the flag state.
// @rdesc   The frame startup loading state.
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
BOOL CFrameTemplate::LoadAtStartup( void )
{
    // Return the state of the frame at the creation of the document.  Tow 
    // options, the user want the frame to be open or close.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    return m_bLoadAtStartup;
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (IMPLEMENTATION)
//          <c CFrameTemplate> <nl>
//          If the load at startup is On, this param specify the frame 
//          style.  Return the style.
// @rdesc   The frame startup display state.
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
UINT CFrameTemplate::GetWndStatus( void )
{
    // Return the default window state (position, show / hide, minimize, 
    // ... ) of the window at the opening of a document.   Valid only if 
    // the Load at startup is TRUE.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
     return m_nDefaultWndStatus;
}
// End =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Start =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Runtime class getting method.
// ------------------------------------------------------------------------
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (IMPLEMENTATION)
//          <c CFrameTemplate> <nl>
//          The View Runtime class is a protected variable define in the 
//          CMultiDocTemplate class.  This method return it.
// @rdesc   The view runtime class.
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
CRuntimeClass* CFrameTemplate::GetViewClass( void )
{
    // Return the runtime view class associated with the frame template,
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    return m_pViewClass;
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (IMPLEMENTATION)
//          <c CFrameTemplate> <nl>
//          The Frame Runtime class is a protected variable define in the 
//          CMultiDocTemplate class.  This method return it.
// @rdesc   The view runtime class.
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
CRuntimeClass* CFrameTemplate::GetFrameClass( void )
{
    // Return the runtime frame class associated with the frame template,
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    return m_pFrameClass;
}
// End =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Start =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Document retrieval method.
// ------------------------------------------------------------------------
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (IMPLEMENTATION)
//          <c CFrameTemplate> <nl>
//          Allow you to retrieve the frame associated document.<nl>
// @rdesc   The document.
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
CDocument* CFrameTemplate::GetDocument( void ) 
{
    return m_pDocument;
}
// End =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Start =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Window retrieval method method.
// ------------------------------------------------------------------------
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (USEFULL_IMPLEMENTATION)
//          <c CSDIMVDocTemplate> <nl>
//          To find the frame window associated with the frame template.<nl>
// @rdesc   The founded frame window.<nl>
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
CFrameWnd* CFrameTemplate::FindFrame( void )
{
    // Validate the needed information.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    if ( !m_pDocument ) 
    {
        ASSERT ( m_pDocument );
        TRACE( "Invalid document while searching for a window in FindFrame in %s at %d.\n", THIS_FILE, __LINE__ );
    }
    
    // Search the document to find the associted frame window.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    POSITION Position = m_pDocument->GetFirstViewPosition();
    while ( Position != NULL )
    {
        // Retrieve the view at the given position.
        CView* pView = m_pDocument->GetNextView( Position );

        // Verify to see if the view and the frame runtime class
        // correspond to the frame template we are searching.
        if ( pView->IsKindOf( GetViewClass() ) &&
             pView->GetParentFrame()->IsKindOf( GetFrameClass() ) )
        {
            // Got it.
            return pView->GetParentFrame();
        }
    }

    // Not found.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    return NULL;
}
// End =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Start =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Creation method.
// ------------------------------------------------------------------------
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (IMPLEMENTATION)
//          <c CFrameTemplate> <nl>
//          Create the frame window.
// @rdesc   The frame wnd.
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
CFrameWnd* CFrameTemplate::CreateFrame( void )
{
    // Create the window and validate it.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    CMDIChildWnd* pNewFrame	= ( CMDIChildWnd* )( CreateNewFrame( GetDocument(), NULL ) );
    if ( !pNewFrame ) 
    {
        // Must never happen.
        ASSERT(pNewFrame);
        TRACE( "Unable to create frame wnd in CFrameTemplate::CreateFrame.\n", THIS_FILE, __LINE__ ); 
        return NULL;
    }
 
    // Make sure that the frame is a mdi child window.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    ASSERT( pNewFrame->IsKindOf( RUNTIME_CLASS( CMDIChildWnd ) ) );

    // Initialize the newly created frame.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    InitialUpdateFrame( pNewFrame, GetDocument(), FALSE );
	pNewFrame->SendMessageToDescendants( WM_INITIALUPDATE, 0, 0, TRUE, TRUE );
    //pNewFrame->ShowWindow( SW_HIDE );

    // Return the new frame.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    return pNewFrame;
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (IMPLEMENTATION)
//          <c CFrameTemplate> <nl>
//          Destroy one instance of a frame associated with this template.<nl>
// @rdesc   True if a window was destroy.  False otherwise.<nl>
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
bool CFrameTemplate::DestroyFrame( void )
{
    // Find a window and validate it.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    CFrameWnd* pWnd = FindFrame( );
    if ( !pWnd )
    {
        // Nothing to destroy.
        return false;
    }

    // Destroy the window.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    pWnd->DestroyWindow();
    return true;
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (USEFULL_IMPLEMENTATION)
//          <c CSDIMVDocTemplate> <nl>
//          Display the window.  If the window is not created, create it.
// @rdesc   True if the window is displayed.  False otherwise.
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
bool CFrameTemplate::ShowOrCreateFrame( void )
{
    // Verify if the window is already created.  If not, create it.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    CFrameWnd* pFrame = FindFrame(  );
    if ( !pFrame ) 
    {
        // Frame not open.  Create it and validate it.
        pFrame = CreateFrame();
        if ( !pFrame ) 
        {
            // Must never happen.
            ASSERT( pFrame );
            TRACE( "Unable to create frame in ShowOrCreateFrame in %s at %d.\n", THIS_FILE, __LINE__ );
            return false;
        }
    }
    
    // Retrieve the current window states.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    int nStates = SW_RESTORE;
    CWnd* pActWnd = ( ( CFrameWnd* ) AfxGetMainWnd() )->GetActiveFrame();
    if ( pActWnd ) 
    {
        WINDOWPLACEMENT wp;
        pActWnd->GetWindowPlacement( &wp );
        if ( wp.showCmd != SW_SHOWMINIMIZED )
        {
            nStates = wp.showCmd;
        }
    }

    // Activate the frame in the given states.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    pFrame->ActivateFrame( nStates );
    // pFrame->ShowWindow( nStates );
    return true;
}
// End =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Start =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Macro definition.
// ------------------------------------------------------------------------
IMPLEMENT_DYNAMIC( CSDIMVDocTemplate, CMultiDocTemplate )
// End =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Start =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Initialization method.
// ------------------------------------------------------------------------
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (IMPLEMENTATION)
//          <c CSDIMVDocTemplate> <nl>
//          Constructor.
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
CSDIMVDocTemplate::CSDIMVDocTemplate(
     UINT _nIDResource,                     // @Parm The document resource id.
     CRuntimeClass* _pDocClass,             // @Parm The document class name.
     BOOL _bAutoDelete )                    // @Parm True to close the document when closing the last window.
	 : CMultiDocTemplate( _nIDResource, _pDocClass, NULL, NULL )
{
    // Set the default value to the variable member.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	m_pOnlyDoc = NULL;
    m_bAutoDelete = _bAutoDelete;
    m_pTabToActivate = NULL;
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (IMPLEMENTATION)
//          <c CSDIMVDocTemplate> <nl>
//          Destructor.  Remove all the frame template from the list.
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
CSDIMVDocTemplate::~CSDIMVDocTemplate( void )
{
    // Must clean all memory allocated.
    // Scan the map and delete all frame template.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    POSITION Position = m_FrameIndex.GetStartPosition();
    while ( Position )
    {
        UINT nEventId;
        CFrameTemplate* pFrameTemplate = NULL;
        m_FrameIndex.GetNextAssoc( Position, nEventId, ( CFrameTemplate*& ) pFrameTemplate );
        
        // Validate the frame template.
        if ( !pFrameTemplate )
        {
            // Must never happen.
            ASSERT ( pFrameTemplate );
            TRACE ( "Invalid frame template in Destructor.\n", THIS_FILE, __LINE__ );
        }
        else
        {
            // Set the document pointer to the new loaded document.
            delete pFrameTemplate;
        }
    }
    
    // Remove all item from the index.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    m_FrameIndex.RemoveAll();
}
// End =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Start =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Document list management.
// ------------------------------------------------------------------------
//      In the MFC philosophy, a document template must support a list of
//      document.  Since this document template is a single one, we fake
//      the list.  We only kept a pointer to the current document.
//
//      The document template must provide 4 method.
//
//      A method to get the position of the first document in the list.
//      A method to get the document at the given position.
//      A method to add a document.
//      A method to remove a document.
//      A open document file.
// ------------------------------------------------------------------------
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (MFC_OVERLOADED)
//          <c CSDIMVDocTemplate> <nl>
//          This method is called by the CDocTemplate class when managing 
//          the document.  Because we only have 1 document,  we can't 
//          return the position of the first one.  We must return a special 
//          ID.
// @rdesc   Special id to identify the first document.
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
POSITION CSDIMVDocTemplate::GetFirstDocPosition( void ) const
{
    // Because we only have one document, we return a dummy position if the
    // document is valid.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	return ( m_pOnlyDoc == NULL ) ? NULL : BEFORE_START_POSITION;
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (MFC_OVERLOADED)
//          <c CSDIMVDocTemplate> <nl>
//          This method is called by the CDocTemplate class when managing 
//          the document.  Because we only have 1 document,  we only return 
//          the currrent document, depending on the position pass in 
//          parameter.  When returning, we set the current position to NULL, 
//          because there is no more document in the list.
// @rdesc   The document pointer.
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
CDocument* CSDIMVDocTemplate::GetNextDoc( 
     POSITION& _rPos ) const        // @Parm The position requested.
{
    // We got only 1 document at the same time.We set the next position to 
    // null. When the framework ask for the next document, we will return 
    // NULL.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    CDocument* pReturnDoc = NULL;
    
    // Validate the position requested.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    if ( _rPos == BEFORE_START_POSITION )
    {
        // The position correspond to the first document, our only one.
        // Return it.
        pReturnDoc = m_pOnlyDoc;
    }

    // The position is invalid.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    _rPos = NULL;
    return pReturnDoc;
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (MFC_OVERLOADED)
//          <c CSDIMVDocTemplate> <nl>
//          This method is called by the CDocTemplate class when opening a 
//          document.  Because we only have 1 docucument we first close the 
//          one we got, the we set the current to the one we receive in 
//          parameter.
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void CSDIMVDocTemplate::AddDocument( 
     CDocument* _pDoc )     // @Parm The new opened document.
{
    // Validate the new document.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    if ( !_pDoc )
    {
        ASSERT ( _pDoc );
        TRACE( "Invalid document parameter in the AddDocument method.\n", THIS_FILE, __LINE__ );
        return;
    }
    
    // Make sure the document is valid.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	ASSERT_VALID( _pDoc );

    // Call the add document method of our parent class. We don't call the 
    // multidoc add document because we don't want a multi doc application.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	CDocTemplate::AddDocument( _pDoc );
    
    // Verify that no document are already opened.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    if ( m_pOnlyDoc )
    {
        // Already have a document.
        // Must close it.
        CloseAllDocuments( FALSE );
    }
    
    // Save the current document pointer.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    m_pOnlyDoc = _pDoc;
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (MFC_OVERLOADED)
//          <c CSDIMVDocTemplate> <nl>
//          This method is called by the CDocTemplate class when closing a 
//          document.  Because we only have 1 docucument we only set the 
//          current one to NULL.
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void CSDIMVDocTemplate::RemoveDocument( 
     CDocument* _pDoc )     // @Parm The document to remove.
{
    // Validate the new document.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    if ( !_pDoc )
    {
        ASSERT ( _pDoc );
        TRACE( "Invalid document parameter in the RemoveDocument method.\n", THIS_FILE, __LINE__ );
        return;
    }

    // Since we only got one document to remove it must be the same that 
    // we kept.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    else if ( m_pOnlyDoc != _pDoc )
    {
        // Not the same.
    	ASSERT( m_pOnlyDoc == _pDoc );
        TRACE( "Document to remove is not the same as the one we got in the RemoveDocument method.\n", THIS_FILE, __LINE__ );
    }
    
    // Make sure the document is valid.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	ASSERT_VALID( _pDoc );

    // Call the remove document of CDocTemplate. Don't call the remove of 
    // our parent class CMultidocTemplate since this class manage one
    // document.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	CDocTemplate::RemoveDocument( _pDoc );

    // Set the current document to NULL to avoid any problem with windows.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	m_pOnlyDoc = NULL;
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (MFC_OVERLOADED)
//          <c CSDIMVDocTemplate> <nl>
//          This method is called by the CDocTemplate class when opening a 
//          document.  View description below.
//
// @devnote 
//          This method has been overloaded.  Because of the way the open
//          is implement, we had to overload it, and modify it. We open the 
//          document the same way the CMultiDocTemplate do it. In a normal 
//          doctemplate, there is only one frame associated to the template.  
//          The method can call the CreateNewFrame method and if the open 
//          document method fail, tell the newly created frame to destroy 
//          itself.
//
//          The MultiView Doc template is implemented to manage a list of
//          view.  When the method call CreateNewFrame, the problem emerge
//          , we had to create more than one frame.  What do we return and
//          what do we do if the open document fail. By overloading the open 
//          method, we open the document before creating any frame.  If 
//          everything goes well, then we create all the frame, and update 
//          it ourself.
// 
// @rdesc   The newly opened document.
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
CDocument* CSDIMVDocTemplate::OpenDocumentFile( 
     LPCTSTR _lpszPathName,         // @CMember The document file name.
     BOOL _bMakeVisible )           // @CMember True to make the document visible.
{
    // Create the document instance and validate it.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    CDocument* pDocument = CreateNewDocument();
    if ( !pDocument )
    {
        // The document is invalid.
        // Inform the user of the error, and exit the method.
        AfxMessageBox( AFX_IDP_FAILED_TO_CREATE_DOC );
        TRACE( "Unable of creating the document in OpenDocumentFile.\n", THIS_FILE, __LINE__ );
        return NULL;
    }

    // Validate the document.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    ASSERT_VALID( pDocument );

    // The document is valid.  Set the autodelete flag.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    pDocument->m_bAutoDelete = m_bAutoDelete;

    // Verify if we are creating a new document, or opening an exesting one.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    if ( _lpszPathName == NULL )
    {
        // Xreate a new document - with default document name
        SetDefaultTitle( pDocument );

        // Avoid creating temporary compound file when starting up invisible
        if ( !_bMakeVisible )
        {
            pDocument->m_bEmbedded = TRUE;
        }

        // Initialize the document.
        if ( !pDocument->OnNewDocument() )
        {
            // Unable to initialize the document.
            TRACE( "Unable to initialize the new document in OpenDocumentFile.\n", THIS_FILE, __LINE__ );
            return NULL;
        }
    }
    else
    {
        // Open an existing document
        CWaitCursor wait;
        if ( !pDocument->OnOpenDocument( _lpszPathName ) )
        {
            // Unable to open the document.
            TRACE( "Unable to open the document in OpenDocumentFile.\n", THIS_FILE, __LINE__ );

            // We must delete the document instance.
            RemoveDocument( pDocument );
            delete pDocument;
            CloseAllDocuments( FALSE );

            return NULL;
        }
        // Set the document file path and name.
        pDocument->SetPathName( _lpszPathName );
    }

    // Now that the document is created, we can create all the frame that 
    // are mark to be create at startup.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    AssignFrameTemplateDocument();
    OpenStartupFrame();

    // Return the created document.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    return pDocument;
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (IMPLEMENTATION)
//          <c CSDIMVDocTemplate> <nl>
//          Return the current document.<nl>
// @rdesc   The current document.
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
CDocument* CSDIMVDocTemplate::GetDocument( void )
{
    // Return the pointer to the currently open document.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    return m_pOnlyDoc;
}
// End =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Start =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Frame template method management.
// ------------------------------------------------------------------------
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (FUNCTIONAL)
//          <c CSDIMVDocTemplate> <nl>
//          Use to add a frame template in the list.  The frame correspond 
//          to a unique window.<nl>
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void CSDIMVDocTemplate::AddFrameTemplate( 
     CFrameTemplate* _pFrameTemplate,     // @Parm The frame to add to the list.
     bool _bStartupFrame )                // @Parm true to set this frame activated.
{
    // Validate the needed information.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    if ( !_pFrameTemplate )
    {
        // Must never happen.
        ASSERT ( _pFrameTemplate );
        TRACE( "Invalid frame template specify is the AddFrameTemplate method.\n", THIS_FILE, __LINE__ );
        return;
    }
    
    // Add the frame template in the map index.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    m_FrameIndex.SetAt( _pFrameTemplate->GetEventID(), _pFrameTemplate );    

    // Load the ressource associated with the frame template.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    _pFrameTemplate->LoadTemplate(  );

    // Remember the frame template if it's the one to activate.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    if ( _bStartupFrame )
    {
        m_pTabToActivate = _pFrameTemplate;
    }
}
// End =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Start =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Usefull method.
// ------------------------------------------------------------------------
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (USEFULL_IMPLEMENTATION)
//          <c CSDIMVDocTemplate> <nl>
//          To find the frame template with the given frame runtime class.
// @rdesc   The founded frame template.
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
CFrameTemplate* CSDIMVDocTemplate::FindFrame( 
     CString _ViewClassName,          // @Parm The view.
     CString _FrameClassName )        // @Parm The frame.
{
    // Scan the map to find the template of the active window.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    POSITION Position = m_FrameIndex.GetStartPosition();
    while ( Position )
    {
        UINT nEventId;
        CFrameTemplate* pFrameTemplate = NULL;
        m_FrameIndex.GetNextAssoc( Position, nEventId, ( CFrameTemplate*& ) pFrameTemplate );
        
        // Validate the frame template.
        if ( !pFrameTemplate )
        {
            // Must never happen.
            ASSERT ( pFrameTemplate );
            TRACE ( "Invalid frame template in FindFrame.\n", THIS_FILE, __LINE__ );
        }
        else if ( pFrameTemplate->GetViewClass()->m_lpszClassName == _ViewClassName && 
                  pFrameTemplate->GetFrameClass()->m_lpszClassName == _FrameClassName )
        {
            // Found it.
            return pFrameTemplate;
        }
    }
    
    // Not found.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    return NULL;
}   
  
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (USEFULL_IMPLEMENTATION)
//          <c CSDIMVDocTemplate> <nl>
//          To find the frame template with the given frame runtime class.
// @rdesc   The founded frame template.
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
CFrameTemplate* CSDIMVDocTemplate::FindFrame( 
     UINT _nEventId )        // @Parm The frame event id.
{
    // Scan the map to find the template of the active window.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    CFrameTemplate* pFrameTemplate = NULL;
    if ( m_FrameIndex.Lookup( _nEventId, ( CFrameTemplate*& ) pFrameTemplate ) )
    {
        // Find it.
        return pFrameTemplate;
    }
    
    // Not found.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    return NULL;
}   

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (USEFULL_IMPLEMENTATION)
//          <c CSDIMVDocTemplate> <nl>
//          When opening a new document, we must set the document pointer
//          of each frame template to the newly opened document.  This
//          action must be done before opening the window.<nl>
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void CSDIMVDocTemplate::AssignFrameTemplateDocument( void ) 
{
    // Scan the map and open the frame that must be open
    // at startup.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    POSITION Position = m_FrameIndex.GetStartPosition();
    while ( Position )
    {
        UINT nEventId;
        CFrameTemplate* pFrameTemplate = NULL;
        m_FrameIndex.GetNextAssoc( Position, nEventId, ( CFrameTemplate*& ) pFrameTemplate );
        
        // Validate the frame template.
        if ( !pFrameTemplate )
        {
            // Must never happen.
            ASSERT ( pFrameTemplate );
            TRACE ( "Invalid frame template in AssignFrameTemplateDocument.\n", THIS_FILE, __LINE__ );
        }
        else
        {
            // Set the document pointer to the new loaded document.
            pFrameTemplate->m_pDocument = m_pOnlyDoc;
        }
    }
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (USEFULL_IMPLEMENTATION)
//          <c CSDIMVDocTemplate> <nl>
//          When opening a document, we load the frame window that must
//          be loaded.<nl>
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void CSDIMVDocTemplate::OpenStartupFrame( void )
{
    // Local definition.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    CFrameWnd* WndToActivate = NULL;

    // Scan the map and open the frame that must be open
    // at startup.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    POSITION Position = m_FrameIndex.GetStartPosition();
    while ( Position )
    {
        UINT nEventId;
        CFrameTemplate* pFrameTemplate = NULL;
        m_FrameIndex.GetNextAssoc( Position, nEventId, ( CFrameTemplate*& ) pFrameTemplate );
        
        // Validate the frame template.
        if ( !pFrameTemplate )
        {
            // Must never happen.
            ASSERT ( pFrameTemplate );
            TRACE ( "Invalid frame template in map index while opening statup frame.\n", THIS_FILE, __LINE__ );
        }
        else if ( pFrameTemplate->LoadAtStartup() )
        {
            // The frame must be loaded when the document is being open.
            // Create the frame instance and validate it.
            CFrameWnd* pFrame = pFrameTemplate->CreateFrame();
            if ( !pFrame )
            {
                // Must never happen.
                ASSERT( pFrame );
                TRACE ( "Unable to create the window while opening statup frame.\n", THIS_FILE, __LINE__ );
            }
            else
            {
                // The frame is now created, we must activate it.
                pFrame->ShowWindow( pFrameTemplate->GetWndStatus() );

                if ( ( m_pTabToActivate && m_pTabToActivate == pFrameTemplate ) ||
                     !m_pTabToActivate )
                {
                    // Creating the tab to activate.
                    WndToActivate = pFrame;
                }
            }
        }
    }

    // Activate the window.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    if ( WndToActivate )
    {
        WndToActivate->ActivateFrame();
        WndToActivate->SetFocus();
    }
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (USEFULL_IMPLEMENTATION)
//          <c CSDIMVDocTemplate> <nl>
//          Patch to register the icon of the document correctly.<nl>
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void CSDIMVDocTemplate::RegisterIconType( void )
{
    // Get the application name.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    char buffer[1024];
    GetModuleFileName( NULL, buffer, 1024 );
    CString sBuffer( buffer );

    // Set the icon key to the resource id value.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    CString Icon = sBuffer + ",-";
    Icon.Format( Icon + "%d", m_nIDResource );

    // Get the doc string.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    CString RegDocName;
    GetDocString( RegDocName, CDocTemplate::regFileTypeId) ;
	RegSetValue( HKEY_CLASSES_ROOT, RegDocName + "\\DefaultIcon", REG_SZ, Icon, lstrlen( Icon ) * sizeof( TCHAR ) );
}
// End =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Start =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @Access Search method.
// ------------------------------------------------------------------------
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (USEFULL_IMPLEMENTATION)
//          <c CSDIMVDocTemplate> <nl>
//          Allow you to retrieve a frame template associated with the
//          given frame and view.  If the given view is not the one
//          normally associated with the frame template, we scan the list
//          of view to find the good one.<nl>
// @rdesc   The frame template.  Null if not found.<nl>
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
CFrameTemplate* CSDIMVDocTemplate::FindFrameTemplate( 
     CWnd* _pView,          // @Parm The view.
     CWnd* _pFrame )        // @Parm The frame.
{
    // Call the find method with string.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    return FindFrameTemplate( _pView->GetRuntimeClass()->m_lpszClassName,
                              _pFrame->GetRuntimeClass()->m_lpszClassName );
}   

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (USEFULL_IMPLEMENTATION)
//          <c CSDIMVDocTemplate> <nl>
//          Allow you to retrieve a frame template associated with the
//          given frame and view.  If the given view is not the one
//          normally associated with the frame template, we scan the list
//          of view to find the good one.<nl>
// @rdesc   The frame template.  Null if not found.<nl>
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
CFrameTemplate* CSDIMVDocTemplate::FindFrameTemplate( 
     CString _ViewClassName,          // @Parm The view.
     CString _FrameClassName )        // @Parm The frame.
{
    // Try to find it directly.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    CFrameTemplate* pChosenFrameTemplate = FindFrame( _ViewClassName, _FrameClassName );
    if ( pChosenFrameTemplate )
    {
        // Found it.
        return pChosenFrameTemplate;
    }

    // Didn't find the frame.
    // Probably a frame with more than one view.  
    // The focused view may not be the one registered.
    // Search all view, and try to find the one that match the frame.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    POSITION Position = m_pOnlyDoc->GetFirstViewPosition();
    while ( Position != NULL )
    {
        // Retrieve the view at the given position.
        CView* pView = m_pOnlyDoc->GetNextView( Position );

        // Verify that the view is associated with our frames.
        if ( pView->GetParentFrame()->GetRuntimeClass()->m_lpszClassName == _FrameClassName && 
             pView->GetRuntimeClass()->m_lpszClassName != _ViewClassName )
        {
            // Try to find it.
            pChosenFrameTemplate = FindFrame( pView->GetRuntimeClass()->m_lpszClassName, _FrameClassName );
            if ( pChosenFrameTemplate )
            {
                // Got it.
                return pChosenFrameTemplate;
            }
        }
    }
    
    // Not found.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    return NULL;
}   
// End =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Start =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// MFC overloaded method.
// ------------------------------------------------------------------------
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (MFC_OVERLOADED)
//          <c CSDIMVDocTemplate> <nl>
//          Usualy call by the opendocumentfile method, and when pressing 
//          the NewWindow item menu.  In this doc template, only call
//          when the new window is pressed.<nl>
// 
// @devnote
//          We overloaded the create new frame to avoid the creation of 
//          frame.  Since there are a list of frame template,associated 
//          with this doc template, we return NULL.This way we tell the 
//          framework that no frame were created.
//
//          When a new window is asked, we found the active window, and
//          we create a clone of the window.
//
// @rdesc   The newly created window.
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
CFrameWnd* CSDIMVDocTemplate::CreateNewFrame( 
     CDocument* _pDoc,          // @Parm The associated document.
     CFrameWnd* _pOther )       // @Parm The frame wnd to base on.
{

    // Validate the needed information.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    if( !AfxGetMainWnd() )
    {
        // The main window is not valid, or the current active frame is the main window.
        // This mean that no child frame are currently open.  Must never happen.
        ASSERT( AfxGetMainWnd() );
        TRACE( "Invalid main window in CreateNewFrame.\n", THIS_FILE, __LINE__ );
        return NULL;
    }
    else if ( !( ( CFrameWnd* ) AfxGetMainWnd() )->GetActiveFrame() )
    {
        // Must never happen.
        ASSERT( ( ( CFrameWnd* ) AfxGetMainWnd() )->GetActiveFrame() );
        TRACE( "Invalid active frame in CreateNewFrame.\n", THIS_FILE, __LINE__ );
        return NULL;
    }
    else if ( ( ( ( CFrameWnd* ) AfxGetMainWnd() )->GetActiveFrame() == AfxGetMainWnd() ) )
    {
        ASSERT( ( ( CFrameWnd* ) AfxGetMainWnd() )->GetActiveFrame() == AfxGetMainWnd() );
        TRACE( "Invalid main window in CreateNewFrame.\n", THIS_FILE, __LINE__ );
        return NULL;
    }
    else if ( !( ( CFrameWnd* ) AfxGetMainWnd() )->GetActiveFrame()->GetActiveView() )
    {
        // Must never happen.
        ASSERT( ( ( CFrameWnd* ) AfxGetMainWnd() )->GetActiveFrame()->GetActiveView() );
        TRACE( "Invalid active view in CreateNewFrame.\n", THIS_FILE, __LINE__ );
        return NULL;
    }

    // Find the correspondant template, and validate it.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    CFrameWnd* pChosenFrame = ( ( CFrameWnd* ) AfxGetMainWnd() )->GetActiveFrame();
    CView* pChosenView = pChosenFrame->GetActiveView();
    CFrameTemplate* pChosenFrameTemplate = FindFrameTemplate( pChosenView, pChosenFrame );
    if ( !pChosenFrameTemplate )
    {
        // Not found.
        // Not supposed to happen.
        ASSERT( pChosenFrameTemplate );
        return NULL;
    }

    // Create the associated window and return it.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    CMDIChildWnd* pNewFrame	= ( CMDIChildWnd* ) ( pChosenFrameTemplate->CreateNewFrame( m_pOnlyDoc, NULL ) );
    return pNewFrame;
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (MFC_OVERLOADED)
//          <c CSDIMVDocTemplate> <nl>
//          Usualy call by the opendocumentfile method, and when pressing 
//          the NewWindow item menu.  In this doc template, only call
//          when the new window is pressed.<nl>
// 
// @devnote
//          We overloaded the initial update frame to avoid the update of 
//          frame.  Since there are a list of frame template,  associated 
//          with this doc template, we do nothing.
//
//          When a new window is asked, we initialize it.
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void CSDIMVDocTemplate::InitialUpdateFrame( 
     CFrameWnd* _pFrame,            // @Parm The frame to initialize.
     CDocument* _pDoc,              // @Parm The associated document.
     BOOL _bMakeVisible )           // @Parm True to make the window visible.
{
    // Validate the needed information.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    if ( !_pFrame ) 
    {
        // Must never happen.
        ASSERT( _pFrame );
        TRACE( "Invalid frame argument in InitialUpdateFrame.\n", THIS_FILE, __LINE__ );
        return;
    }

    // Make sure that the frame is a mdi child window.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    if ( !_pFrame->IsKindOf( RUNTIME_CLASS( CMDIChildWnd ) ) ) 
    {
        // Must never happen.
        ASSERT( _pFrame->IsKindOf( RUNTIME_CLASS( CMDIChildWnd ) ) );
        TRACE( "Invalid MDI frame in InitialUpdateFrame.\n", THIS_FILE, __LINE__ );
        return;
    }

    // Initialize the newly created frame.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	_pFrame->InitialUpdateFrame( m_pOnlyDoc, _bMakeVisible );
}


// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @mfunc:  (MFC_OVERLOADED)
//          <c CSDIMVDocTemplate> <nl>
//          This method trap all event generated.  We overloaded it to load 
//          the frame template when their event ID are generated.<nl>
//
// @rdesc   TRUE if the message was handle.  FALSE otherwise.
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
BOOL CSDIMVDocTemplate::OnCmdMsg( 
     UINT _nID,                             // @Parm Contains the command ID.
     int _nCode,                            // @Parm Identifies the command notification code.
     void* _pExtra,                         // @Parm Used according to the value of nCode.
     AFX_CMDHANDLERINFO* _pHandlerInfo )    // @Parm If not NULL, OnCmdMsg fills in the pTarget 
                                            //       and pmf members of the pHandlerInfo structure 
                                            //       instead of dispatching the command. Typically, 
                                            //       this parameter should be NULL.
{
    // If pHandlerInfo is NULL, then handle the message.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    if ( _pHandlerInfo == NULL )
	{
        // We must handle this message.
        // Search the frame.
        CFrameTemplate* pChosenFrame = FindFrame( _nID );
        if ( _nCode == CN_COMMAND && m_pOnlyDoc && pChosenFrame )
        {
            // Try to create the frame.
            return pChosenFrame->ShowOrCreateFrame(  );
        }
        else if ( _nCode == CN_UPDATE_COMMAND_UI && m_pOnlyDoc && pChosenFrame )
        {
            // This is an Update UI event and the id is a frame open id.
            // Enable the menu item.
            ( ( CCmdUI* ) _pExtra )->Enable( TRUE );

            // Find the currently selected window.
            if ( ( ( CFrameWnd* ) AfxGetMainWnd() )->GetActiveFrame() != AfxGetMainWnd() )
            {
                CFrameWnd* pChosenFrame = ( ( CFrameWnd* ) AfxGetMainWnd() )->GetActiveFrame();
                CView* pChosenView = pChosenFrame->GetActiveView();
                CFrameTemplate* pChosenFrameTemplate = FindFrameTemplate( pChosenView, pChosenFrame );
                ( ( CCmdUI* ) _pExtra )->SetCheck( pChosenFrameTemplate->GetEventID() == _nID );
            }
            else
            {
                ( ( CCmdUI* ) _pExtra )->SetCheck( FALSE );
            }

            // Tell the framework that the message has been handle.
            return TRUE;
        }
    }

    // The message was not for us.
    // Call the parent class method.
    // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    return CMultiDocTemplate::OnCmdMsg( _nID, _nCode, _pExtra, _pHandlerInfo );
}
