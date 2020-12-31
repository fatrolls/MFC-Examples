// Created by: Yog Sothoth
// Company: The Old Gods
// More Info: Azathoth@Cyberdude.com
// Home Page: http://www.geocities.com/SiliconValley/Peaks/2976/

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @doc
// @module SdiMvDocTemplate.h | 
//         This module allow you to use a single document with multiple
//         view.
// @End -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Start ==================================================================
// Definition to avoid multiple include.
// ------------------------------------------------------------------------
#if !defined( _SDIMVDocTemplate_H_ )
#define _SDIMVDocTemplate_H_ 

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// End ====================================================================

// Start ==================================================================
// Include file section.
// ------------------------------------------------------------------------
// Template include file.
#include <afxtempl.h>
// End ====================================================================

// Start ==================================================================
// Class definition.
// ------------------------------------------------------------------------
class CSDIMVDocTemplate;
class CFrameTemplate;
// End ====================================================================

// Start ==================================================================
// Class declaration.
// ------------------------------------------------------------------------
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @class:  (FUNCTIONAL_CLASS)
//          Use to define a template of frame to open with a document.  
//          This class must be overloaded from the CMultiDocTemplate, 
//          to avoid an assertion. This assertion happen when the MDI 
//          frame is created.  MFC has make a standard that when you 
//          create a MDIChildWnd, this template must be a multidoc template.
//          For each frame you want to create and access via an event, you 
//          create a Frame Template.
// @base    public | CMultiDocTemplate
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class CFrameTemplate : public CMultiDocTemplate
{
    // --------------------------------------------------------------------
    // @group Friendship definition.
    // --------------------------------------------------------------------
    friend class CSDIMVDocTemplate;

    // --------------------------------------------------------------------
    // @group Macro definition.
    // --------------------------------------------------------------------
    DECLARE_DYNAMIC( CFrameTemplate )

    // --------------------------------------------------------------------
    // @group Data definition.
    // --------------------------------------------------------------------
    private:
        // @Access Base data.
        UINT m_nEventID;               // @CMember The Event id use to show the window.
        BOOL m_bLoadAtStartup;         // @CMember The startup state. (ON / OFF)
		UINT m_nDefaultWndStatus;      // @CMember The window state at startup.
    public:
    protected:
        CDocument* m_pDocument;        // @CMember The associated document.

    // --------------------------------------------------------------------
    // @group Implementation Method definition.
    // --------------------------------------------------------------------
    private:
    public:
        // @Access Creation and destruction method.
        // @CMember Constructor.
        CFrameTemplate( 
            UINT _nIDResource, CRuntimeClass* _pFrameClass, CRuntimeClass* _pViewClass,
            UINT _nEventID, UINT _nDefaultWndStatus = WS_VISIBLE, BOOL _bLoadAtStartup = FALSE );
        ~CFrameTemplate( void );                // @CMember Destructor.<nl>

        // @Access Information retrieving method.
        UINT GetEventID( void );                // @CMember Return the Event id used to open the frame.
        BOOL LoadAtStartup( void );             // @CMember Return the show state at startup. (ON / OFF)
        UINT GetWndStatus( void );              // @CMember Return the window state when loading at startup.<nl>

        // @Access Runtime class getting method.
        CRuntimeClass* GetViewClass( void );    // @CMember Return the runtime view class.
        CRuntimeClass* GetFrameClass( void );   // @CMember Return the runtime view frame.<nl>

        // @Access Document retrieval method.
        CDocument* GetDocument( void );         // @Cmember To retrieve the associated document.<nl>
 
        // @Access Window retrieval method.
        CFrameWnd* FindFrame( void );           // @CMember To find the frame window associated with the frame template.<nl>

    protected:

    // --------------------------------------------------------------------
    // @group Funcional Method definition.
    // --------------------------------------------------------------------
    private:
    public:
        // @Access Creation method.
        CFrameWnd* CreateFrame( void );         // @Cmember Create the frame instance.
        bool DestroyFrame( void );              // @Cmember Destroy a frame instance.
        bool ShowOrCreateFrame( void );         // @CMember To display the frame.<nl>
        
    protected:
};
// End ====================================================================

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @class:  (FUNCTIONAL_CLASS)
//          This class is the doc template.  We overload the different
//          method.  Instead of loading the default associated frame and
//          view, we load the id correspondant frame.
// @base    public | CMultiDocTemplate
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class CSDIMVDocTemplate : public CMultiDocTemplate
{
    // --------------------------------------------------------------------
    // @group Macro definition.
    // --------------------------------------------------------------------
    DECLARE_DYNAMIC( CSDIMVDocTemplate )

    // --------------------------------------------------------------------
    // @group Data definition.
    // --------------------------------------------------------------------
    private:
    public:
    protected:
        // @Access Defautl member.
        CFrameTemplate* m_pTabToActivate;     // @CMember The tab to activate when loading.

        // @Access Flag.
        BOOL m_bAutoDelete;             // @CMember Flag to know if we must delete the doc.
        CDocument* m_pOnlyDoc;          // @CMember The only document loaded.
        
        // @Access List information.
        CMap< UINT, UINT, CFrameTemplate*, CFrameTemplate*& > m_FrameIndex;   // @CMember The index on the list.

    // --------------------------------------------------------------------
    // @group Implementation Method definition.
    // --------------------------------------------------------------------
    private:
        // @Access Private Usefull method.
        // @CMember To find the frame template associated with the given frame and view.
        CFrameTemplate* FindFrame( CString _ViewClassName, CString _FrameClassName );
        CFrameTemplate* FindFrame( UINT _nEventId );                        // @CMember To find the frame template with the given frame runtime class.
        void AssignFrameTemplateDocument( void );                           // @CMember To set the frame template document.
        void OpenStartupFrame( void );                                      // @CMember To open all frame that must be open with the document.<nl>

    public:
        // @Access Initialization method.
        // @CMember Constructor.
        CSDIMVDocTemplate( UINT _nIDResource, CRuntimeClass* _pDocClass, BOOL _bAutoDelete = TRUE );
        virtual ~CSDIMVDocTemplate( void );                                 // @CMember Destructor.

        // @Access Document related method.
        // @CMember To open the document file.
        virtual CDocument* OpenDocumentFile( LPCTSTR _lpszPathName, BOOL _bMakeVisible );   
    	virtual void AddDocument( CDocument* _pDoc );                       // @CMember To add a document in the list.
        virtual void RemoveDocument( CDocument* _pDoc );                    // @CMember To remove a document from the list.
        virtual POSITION GetFirstDocPosition( void ) const;                 // @CMember To get the position of the first document.
        virtual CDocument* GetNextDoc( POSITION& _rPos ) const;             // @CMember To get the document at the given position.
        virtual CDocument* GetDocument( void );                             // @CMember To retrieve the active document.

        // @Access Search method.
        // @CMember To find the frame template associated with the given frame and view.
        CFrameTemplate* FindFrameTemplate( CString _ViewClassName, CString _FrameClassName );
        CFrameTemplate* FindFrameTemplate( CWnd* _pView, CWnd* _pFrame );   // @CMember To find the frame template associated with the given frame and view.

    protected:

    // --------------------------------------------------------------------
    // @group Funcional Method definition.
    // --------------------------------------------------------------------
    private:
    public:
        // @Access Frame template method management.
        virtual void AddFrameTemplate( CFrameTemplate* _pFrameTemplate, bool _bStartupFrame = false );   // @CMember To add a frame template to the list.<nl>
        
        // @Access Tools method.
        // @CMember Register the associated icon with the document.
        void RegisterIconType( void );

    protected:

    // --------------------------------------------------------------------
    // @group MFC Definition.
    // --------------------------------------------------------------------
    private:
    public:
        // @Access Overloaded method to manage the creation of the frame with the document.
        // @CMember Call by the framework when loading a window.
        virtual CFrameWnd* CreateNewFrame( CDocument* _pDoc, CFrameWnd* _pOther );

        // @CMember Call by the framework when the frame is being display.
        virtual void InitialUpdateFrame( CFrameWnd* _pFrame, CDocument* _pDoc, BOOL _bMakeVisible = TRUE );

        // @Access Message map method to trap the template menu id.
        // @CMember MFC method call when receiving an event.
        virtual BOOL OnCmdMsg( UINT _nID, int _nCode, void* _pExtra, AFX_CMDHANDLERINFO* _pHandlerInfo );
        
    protected:
};

// Start =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @contents2 Sample: Using the document template. |
//            This sample will show you how to use the multiple view doc
//            template.
// ------------------------------------------------------------------------
// @ex  | 
//    CSDIMVDocTemplate *pDocTemplate = new CSDIMVDocTemplate( IDR_SDIMULTYPE, RUNTIME_CLASS( CSDIMultipleViewTestDoc ) );
//    pDocTemplate->AddFrameTemplate(
//        new CFrameTemplate( 
//            IDR_SDIMULTYPE, 
//            RUNTIME_CLASS( CChildFrame ), 
//            RUNTIME_CLASS( CSDIMultipleViewTestView ), 
//            ID_SHOWMVTEST, 
//            SW_SHOWMAXIMIZED, 
//            TRUE ) );
//
//    pDocTemplate->AddFrameTemplate(
//        new CFrameTemplate( 
//            IDR_SDIMULTYPE1, 
//            RUNTIME_CLASS( CChildFrame ), 
//            RUNTIME_CLASS( CMyView1 ), 
//            ID_SHOWMVTEST1, 
//            SW_SHOWMINIMIZED, 
//            TRUE ) );
//
//    pDocTemplate->AddFrameTemplate(
//        new CFrameTemplate( 
//            IDR_SDIMULTYPE2, 
//            RUNTIME_CLASS( CChildFrame ), 
//            RUNTIME_CLASS( CMyView2 ), 
//            ID_SHOWMVTEST2, 
//            SW_HIDE, 
//            TRUE ) );
//    AddDocTemplate(pDocTemplate);
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#endif // _SDIMVDocTemplate_h_