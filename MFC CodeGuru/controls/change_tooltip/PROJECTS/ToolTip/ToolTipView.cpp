// ToolTipView.cpp : implementation of the CToolTipView class
//

#include "stdafx.h"
#include "ToolTip.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolTipView


IMPLEMENT_DYNCREATE(CToolTipView, CView)

BEGIN_MESSAGE_MAP(CToolTipView, CView)
	//{{AFX_MSG_MAP(CToolTipView)
	ON_COMMAND(ID_CHANGE_TOOL_TIP, OnChangeToolTip)
	ON_NOTIFY_EX_RANGE( TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
    ON_NOTIFY_EX_RANGE( TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolTipView construction/destruction

CToolTipView::CToolTipView()
{
	// TODO: add construction code here

}

CToolTipView::~CToolTipView()
{
}

BOOL CToolTipView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CToolTipView drawing

void CToolTipView::OnDraw(CDC* pDC)
{
	CToolTipDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CString strMessage = TEXT("Click the \"CT\" button to enter new text");
	pDC->TextOut(100,20,strMessage, strMessage.GetLength());

	strMessage = TEXT("Thank you All for the help on this subject!");
	pDC->TextOut(100,40,strMessage, strMessage.GetLength());

	strMessage = TEXT("Michael Hupp, Kostya Sebov, Tim Hodgson, Thibault Mangold");
	pDC->TextOut(100,60,strMessage, strMessage.GetLength());

	strMessage = TEXT("Dicky Singh, David Little, David Elliot for the mfc-l");
	pDC->TextOut(100,80,strMessage, strMessage.GetLength());

	strMessage = TEXT("From Hans Wedemeyer  hansw@flash.net");
	pDC->TextOut(100,100,strMessage, strMessage.GetLength());


	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CToolTipView printing

BOOL CToolTipView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CToolTipView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CToolTipView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CToolTipView diagnostics

#ifdef _DEBUG
void CToolTipView::AssertValid() const
{
	CView::AssertValid();
}

void CToolTipView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CToolTipDoc* CToolTipView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolTipDoc)));
	return (CToolTipDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CToolTipView message handlers
/////////////////////////////////////////////////////////////////////////////////
//
BOOL CToolTipView::GetToolText( UINT nID, CString& strTipText, CString& /*strMessage*/)
{
    CString strFullString;

    switch( nID )
    {
		case ID_FILE_NEW:  // have to handle all toolbar tool tip messages here
        case ID_FILE_OPEN:
		case ID_FILE_SAVE:
		case ID_EDIT_CUT:
		case ID_EDIT_COPY:
		case ID_EDIT_PASTE:
		case ID_FILE_PRINT:
		case ID_APP_ABOUT:
					if (strFullString.LoadString(nID))
					   AfxExtractSubString ( strTipText, strFullString, 1,'\n');
            break;

        case ID_CHANGE_TOOL_TIP:

					strTipText = m_strNewToolTipText;
            	    

					// if the user tried to enter a zero legth string, it could
					// cause confusion, so put the default sring back in
					if ( strTipText.GetLength() == 0 )// put back the default string
					{	
						if (strFullString.LoadString (ID_CHANGE_TOOL_TIP))
						   AfxExtractSubString ( strTipText, strFullString, 1,'\n' );
					}
			break;
    }
   
    
    return TRUE;
}

#define _TTT__
#ifdef _TTT__
//////////////////////////////////////////////////////////////////////////////////
//                           
BOOL CToolTipView::OnToolTipText(UINT nID, NMHDR* pNMHDR, LRESULT* pResult )
{
    ASSERT ( pNMHDR->code == TTN_NEEDTEXTA || TTN_NEEDTEXTW );

    TOOLTIPTEXTA* pTTTA = ( TOOLTIPTEXTA *)pNMHDR;
    TOOLTIPTEXTW* pTTTW = ( TOOLTIPTEXTW *)pNMHDR;

    CString strTipText;
    CString strMessage;

    if( GetToolText(pNMHDR->idFrom, strTipText, strMessage))
    {
#ifndef _UNICODE
        if(pNMHDR->code == TTN_NEEDTEXTA)
            lstrcpyn(pTTTA->szText,strTipText,_countof(pTTTA->szText));
        else
            _mbstowcsz(pTTTW->szText,strTipText,_countof(pTTTW->szText));
#else
        if(pNMHDR->code == TTN_NEEDTEXTA)
            _wcstombsz(pTTTA->szText,strTipText,_countof(pTTTA->szText));
        else
            lstrcpyn(pTTTW->szText,strTipText,_countof(pTTTW->szText));

#endif


     // SetMessageText(strMessage); // change status bar message here need pointer to CMainFrame
      
		// ok we handled the message, the buck stops here
		return TRUE;

    }

	// we did not handle the message, pass it on
    return CToolTipView::OnToolTipText(nID,pNMHDR,pResult);

}
#endif

void CToolTipView::OnChangeToolTip() 
{
	 
    CChangeTTT  dlgTTT;
    dlgTTT.DoModal();

}
/////////////////////////////////////////////////////////////////////
// 
CToolTipView* CToolTipView::GetVP( )
{
   CMDIChildWnd* pChild = ((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd))->MDIGetActive();

   if( ! pChild )
   {return NULL;} // no views open

   // get a pointer to the active window by
   // using the pFrame pointer to call GetActiveView()
   CView* pView = pChild->GetActiveView();

   if( ! pView )
   {return NULL;} // no views open

   // Fail if view is of wrong kind
   // this could occur with splitter windows, or additional views on a single
   // document !
   if ( ! pView->IsKindOf(RUNTIME_CLASS(CToolTipView)))
   { return NULL; }

   return (CToolTipView*) pView;
}
////////////////////////////////////////////////
//
void CToolTipView::SetNewTTT(CString strNew)
{
   m_strNewToolTipText = strNew;
}

CString CToolTipView::GetTTT(void)
{
   return ( m_strNewToolTipText );
}
