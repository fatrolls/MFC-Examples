// MsgMapperView.cpp : implementation of the CMsgMapperView class
//

#include "stdafx.h"
#include "MsgMapper.h"

#include "MsgMapperDoc.h"
#include "MsgMapperView.h"

#include "mainfrm.h"
#include "childfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMsgMapperView

IMPLEMENT_DYNCREATE(CMsgMapperView, CEditView)

BEGIN_MESSAGE_MAP(CMsgMapperView, CEditView)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CMsgMapperView construction/destruction

CMsgMapperView::CMsgMapperView()
	//: CEditView(CMsgMapperView::IDD)
{
	// TODO: add construction code here

}

CMsgMapperView::~CMsgMapperView()
{
}

void CMsgMapperView::DoDataExchange(CDataExchange* pDX)
{
	CEditView::DoDataExchange(pDX);
//	DDX_Control(pDX, IDC_EDITTEXT, m_textEdit);
}

BOOL CMsgMapperView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CEditView::PreCreateWindow(cs);
}

void CMsgMapperView::OnInitialUpdate()
{
	CEditView::OnInitialUpdate();

	CMsgMapperDoc * doc = GetDocument();

	// grab charset structure from message
	CUT_CharSetStruct *cs = doc->m_message.GetCharSetStruct();

	VERIFY(m_font.CreateFont(
	   16,                        // nHeight
	   0,                         // nWidth
	   0,                         // nEscapement
	   0,                         // nOrientation
	   FW_NORMAL,                 // nWeight
	   FALSE,                     // bItalic
	   FALSE,                     // bUnderline
	   0,                         // cStrikeOut
	   cs->nCharSet,			  // nCharSet
	   OUT_DEFAULT_PRECIS,        // nOutPrecision
	   CLIP_DEFAULT_PRECIS,       // nClipPrecision
	   DEFAULT_QUALITY,           // nQuality
	   DEFAULT_PITCH | FF_DONTCARE,  // nPitchAndFamily
	   _T("Arial")));       // lpszFacename

	GetEditCtrl().SetFont(&m_font);

	_TCHAR *strTemp = new _TCHAR(1);
	
	size_t size = 0;

	int result = doc->m_message.GetMessageBody(strTemp, 1, &size);

	if(result == UTE_BUFFER_TOO_SHORT) {
		if(size > 0) {
			delete [] strTemp;
			strTemp = new _TCHAR[size*2 + 1];
			result = doc->m_message.GetMessageBody(strTemp, size, &size);
			if(result == UTE_SUCCESS) {
				GetEditCtrl().SetWindowText(strTemp);
			}
		}
	}

	delete [] strTemp;

	// code in CLeftView will populate the tree control with message attributes
	OnSize(0,0,0);
	
}


// CMsgMapperView diagnostics

#ifdef _DEBUG
void CMsgMapperView::AssertValid() const
{
	CEditView::AssertValid();
}

void CMsgMapperView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMsgMapperDoc* CMsgMapperView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMsgMapperDoc)));
	return (CMsgMapperDoc*)m_pDocument;
}
#endif //_DEBUG


// CMsgMapperView message handlers


void CMsgMapperView::OnSize(UINT nType, int cx, int cy)
{
	CEditView::OnSize(nType, cx, cy);

}

void CMsgMapperView::ViewRawMessage(void)
{
	CMsgMapperDoc * doc = GetDocument();

	GetEditCtrl().SetWindowText(doc->m_strRawMessage);

}

void CMsgMapperView::ViewTextMessage(void)
{
	CMsgMapperDoc * doc = GetDocument();
	size_t size = doc->m_message.GetMessageBodyLength();
	if(size > 0) {
		_TCHAR * str = new _TCHAR[size];
		int result = doc->m_message.GetMessageBody(str, size, &size);
		if(result == UTE_SUCCESS) {
			GetEditCtrl().SetWindowText(str);
		}
		else {
			((CMainFrame*)((CMsgMapperApp*)AfxGetApp())->m_pMainWnd)->
				SetStatusText(CUT_ERR::GetErrorString(result));
		}
		delete [] str;
	}
}

void CMsgMapperView::ViewHTMLMessage(void)
{
	CMsgMapperDoc * doc = GetDocument();
	size_t size = doc->m_message.GetHtmlMessageBodyLength();
	if(size > 0) {
		_TCHAR * str = new _TCHAR[size];
		int result = doc->m_message.GetHtmlMessageBody(str, size, &size);
		if(result == UTE_SUCCESS) {
			GetEditCtrl().SetWindowText(str);
		}
		else {
			((CMainFrame*)((CMsgMapperApp*)AfxGetApp())->m_pMainWnd)->
				SetStatusText(CUT_ERR::GetErrorString(result));
		}
		delete [] str;
	}
}

void CMsgMapperView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	// TODO: Add your specialized code here and/or call the base class
	CEditView::OnActivateView(bActivate, pActivateView, pDeactiveView);

	// tell the app that the UI should be updated
	if(bActivate == FALSE) {
		((CMsgMapperApp*)AfxGetApp())->SetEditViewTypes(bActivate,bActivate,bActivate);
	}
	else {

		CMsgMapperDoc * doc = GetDocument();
		BOOL bHtmlPresent = doc->m_message.IsHtmlMessageBodyPresent();
		((CMsgMapperApp*)AfxGetApp())->SetEditViewTypes(bActivate,bHtmlPresent,bActivate);
	}
}
