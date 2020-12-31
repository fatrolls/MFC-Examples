// HTMLEditView.cpp : implementation of the CHTMLEditView class
//
// Written by Chris Maunder (chris@codeproject.com)
// The Code Project, http://www.codeproject.com

#include "stdafx.h"
#include "HTMLEdit.h"

#include "HTMLEditDoc.h"
#include "HTMLEditView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CHTMLEditView

IMPLEMENT_DYNCREATE(CHTMLEditView, CHtmlEditView)

BEGIN_MESSAGE_MAP(CHTMLEditView, CHtmlEditView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CHtmlEditView::OnFilePrint)
	ON_COMMAND(ID_BROWSE,      OnToggleBrowse)
	ON_COMMAND(ID_MODE_EDIT, OnModeEdit)
	ON_UPDATE_COMMAND_UI(ID_MODE_EDIT, OnUpdateModeEdit)
	ON_COMMAND(ID_MODE_VIEW, OnModeView)
	ON_UPDATE_COMMAND_UI(ID_MODE_VIEW, OnUpdateModeView)

	// You may want to add command and UI handlers such as:
	//   ON_COMMAND(ID_UNDERLINE,           OnUnderline)
	//   ON_UPDATE_COMMAND_UI(ID_UNDERLINE, OnUpdateUnderline)
	// instead of using the DHTMLEDITING_CMD_ENTRY mechanism
	// below, because the DHTMLEDITING_CMD_ENTRY mechanism allows 
	// the commands in the toolbar to still be active even when 
	// in view-mode only.

END_MESSAGE_MAP()

BEGIN_DHTMLEDITING_CMDMAP(CHTMLEditView)
	DHTMLEDITING_CMD_ENTRY(ID_EDIT_COPY, IDM_COPY)
	DHTMLEDITING_CMD_ENTRY(ID_EDIT_CUT,  IDM_CUT)
	DHTMLEDITING_CMD_ENTRY(ID_EDIT_PASTE,IDM_PASTE)
	DHTMLEDITING_CMD_ENTRY(ID_EDIT_UNDO, IDM_UNDO)

	DHTMLEDITING_CMD_ENTRY(ID_UNDERLINE, IDM_UNDERLINE)
	DHTMLEDITING_CMD_ENTRY(ID_ITALIC,    IDM_ITALIC)
	DHTMLEDITING_CMD_ENTRY(ID_BOLD,      IDM_BOLD)
	DHTMLEDITING_CMD_ENTRY(ID_LEFT,      IDM_JUSTIFYLEFT)
	DHTMLEDITING_CMD_ENTRY(ID_CENTER,    IDM_JUSTIFYCENTER)
	DHTMLEDITING_CMD_ENTRY(ID_RIGHT,     IDM_JUSTIFYRIGHT)

	DHTMLEDITING_CMD_ENTRY(ID_HYPERLINK,   IDM_HYPERLINK)
	DHTMLEDITING_CMD_ENTRY(ID_IMAGE,       IDM_IMAGE)
	DHTMLEDITING_CMD_ENTRY(ID_FONT,        IDM_FONT)
	DHTMLEDITING_CMD_ENTRY(ID_INDENT,      IDM_INDENT)
	DHTMLEDITING_CMD_ENTRY(ID_OUTDENT,     IDM_OUTDENT)
	DHTMLEDITING_CMD_ENTRY(ID_ORDERLIST,   IDM_ORDERLIST )
	DHTMLEDITING_CMD_ENTRY(ID_UNORDERLIST, IDM_UNORDERLIST)
END_DHTMLEDITING_CMDMAP()


// CHTMLEditView construction/destruction
CHTMLEditView::CHTMLEditView()
{
	// TODO: add construction code here
}

CHTMLEditView::~CHTMLEditView()
{
}

BOOL CHTMLEditView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlEditView::PreCreateWindow(cs);
}


// CHTMLEditView printing



// CHTMLEditView diagnostics

#ifdef _DEBUG
void CHTMLEditView::AssertValid() const
{
	CHtmlEditView::AssertValid();
}

void CHTMLEditView::Dump(CDumpContext& dc) const
{
	CHtmlEditView::Dump(dc);
}

CHTMLEditDoc* CHTMLEditView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHTMLEditDoc)));
	return (CHTMLEditDoc*)m_pDocument;
}
#endif //_DEBUG


// CHTMLEditView message handlers

void CHTMLEditView::OnInitialUpdate(void)
{
	CHtmlEditView::OnInitialUpdate();

	m_bDesignMode = TRUE;
}

void CHTMLEditView::OnToggleBrowse(void)
{
	m_bDesignMode = !m_bDesignMode;
	SetDesignMode(m_bDesignMode);	
}

void CHTMLEditView::OnModeEdit(void)
{
	m_bDesignMode = TRUE;
	SetDesignMode(m_bDesignMode);
}

void CHTMLEditView::OnUpdateModeEdit(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bDesignMode);
}

void CHTMLEditView::OnModeView(void)
{
	m_bDesignMode = FALSE;
	SetDesignMode(m_bDesignMode);
}

void CHTMLEditView::OnUpdateModeView(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(!m_bDesignMode);
}