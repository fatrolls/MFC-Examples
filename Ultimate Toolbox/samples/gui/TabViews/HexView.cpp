// HexView.cpp : implementation file
//

#include "stdafx.h"
#include "TabViews.h"

#include "TabViewsDoc.h"
#include "TabViewsView.h"
#include "HexView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHexView

IMPLEMENT_DYNCREATE(CHexView, CEditView)

CHexView::CHexView()
{
}

CHexView::~CHexView()
{
}


BEGIN_MESSAGE_MAP(CHexView, CEditView)
	//{{AFX_MSG_MAP(CHexView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHexView diagnostics

#ifdef _DEBUG
void CHexView::AssertValid() const
{
	CEditView::AssertValid();
}

void CHexView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CTabViewsDoc* CHexView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTabViewsDoc)));
	return (CTabViewsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHexView message handlers

void CHexView::AddText(LPCTSTR pszText) 
{
	LONG nWindowTextLength;
	nWindowTextLength = GetEditCtrl().GetWindowTextLength();
	GetEditCtrl().SetSel(nWindowTextLength, nWindowTextLength);
	GetEditCtrl().ReplaceSel(pszText);
}


BOOL CHexView::PreCreateWindow(CREATESTRUCT& cs) 
{
	BOOL bRet = CEditView::PreCreateWindow(cs);
	cs.style |= ES_READONLY;	
	return bRet;
}

void CHexView::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();

	// Create a fixed size font
	if((HFONT)m_font==NULL)
	{
		m_font.CreateFont(	0,						// nHeight
							0,						// nWidth
							0,						// nEscapement
							0,						// nOrientation
							FW_DONTCARE,			// nWeight
							FALSE,					// bItalic
							FALSE,					// bUnderline
							0,						// cStrikeOut
							DEFAULT_CHARSET,		// nCharSet
							OUT_DEFAULT_PRECIS,		// nOutPrecision
							CLIP_DEFAULT_PRECIS,	// nClipPrecision
							DEFAULT_QUALITY,		// nQuality
							FIXED_PITCH,			// nPitchAndFamily
							NULL);					// lpszFacename 
	}
  
	GetEditCtrl().SetFont(&m_font, FALSE);

	TextToHex(TRUE);
}

void CHexView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if(bActivate && pActivateView==this)
	{
		SetRedraw(FALSE);
		TextToHex(FALSE);
		SetRedraw(TRUE);
	}

	CEditView::OnActivateView(bActivate, pActivateView, pDeactiveView);

}

void CHexView::TextToHex(BOOL bForFirstTime/*=FALSE*/)
{
	CTabViewsDoc* pDoc=(CTabViewsDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	CTabViewsView* pPrimaryView=(CTabViewsView*)pDoc->GetPrimaryView();
	ASSERT_VALID(pPrimaryView);

	if(!bForFirstTime && !pPrimaryView->GetEditCtrl().GetModify())
		return;

	CString sText;

	UINT nMaxIndex=pPrimaryView->GetBufferLength();
	if(nMaxIndex>0)
	{
		if(GetBufferLength()>0)
		{
			GetEditCtrl().SetReadOnly(FALSE);
			GetEditCtrl().SetSel(0,GetBufferLength(),TRUE);
			GetEditCtrl().Clear();
			GetEditCtrl().SetReadOnly(TRUE);
		}


		LPCTSTR pData=pPrimaryView->LockBuffer();
		ASSERT(pData!=NULL);

		UINT nIndex=0;
		CString sRaw;
		CString sHex;
		CString sHexTemp;

		while(nIndex<nMaxIndex)
		{
			// Split in two parts (of 8 bytes) seperated by a space
			sRaw.Empty();
			sHex.Empty();

			// ... Add offset
			sHex.Format(_T("%4.4X  "), nIndex);

			for(int nLoop=0; nLoop<2; nLoop++)
			{
				// Calculate 8 bytes
				UINT nPartIndex=0;
				while(nPartIndex<8  && nIndex<nMaxIndex)
				{
					if(_istprint(pData[nIndex]))
						sRaw+=(TCHAR)pData[nIndex];
					else
						sRaw+=_T('.');
					sHexTemp.Format(_T("%2.2X "),pData[nIndex]);
					sHex+=sHexTemp;
					nPartIndex++;
					nIndex++;
				}

			}

			// Show the text
			sText.Format(_T("%-54.54s| %-16.16s\r\n"), sHex, sRaw);
			AddText(sText);
		}

		pPrimaryView->UnlockBuffer();
	}
}
