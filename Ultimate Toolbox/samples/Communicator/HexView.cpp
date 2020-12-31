// HexView.cpp : implementation file
//

#include "stdafx.h"
#include "Communicator.h"
#include "CommunicatorDoc.h"
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
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHexView message handlers

void CHexView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
	{
	UNREFERENCED_PARAMETER(pSender);
	CCommunicatorDoc::CHintData* pHintData = (CCommunicatorDoc::CHintData*)pHint;
	CString sText;

	if (lHint == CCommunicatorDoc::NotifyAddData)
		{
		sText.Format(_T("%i. Data length = 0x%X (%i)\r\n"), 
			pHintData->m_hClient, pHintData->m_nDataLength, pHintData->m_nDataLength);
		AddText(sText);

		// Show the received data
		if (pHintData->m_pData == NULL)
			{
			sText = _T("\t<Unknown Data>\r\n");
			AddText(sText);
			return;
			}

		BYTE* pData = pHintData->m_pData;
		UINT nMaxIndex = pHintData->m_nDataLength;
		UINT nIndex = 0;
		CString sRaw;
		CString sHex;
		CString sHexTemp;
		while (nIndex < nMaxIndex)
			{
			// Split in two parts (of 8 bytes) seperated by a space
			sRaw.Empty();
			sHex.Empty();

			// ... Add offset
			sRaw.Format(_T("%4.4X  "), nIndex);

			for (int nLoop = 0; nLoop < 2; nLoop++)
				{
				// Calculate 8 bytes
				UINT nPartIndex = 0;
				while (nPartIndex < 8  && nIndex < nMaxIndex)
					{
					if (isprint(pData[nIndex]))
						sRaw += (char)pData[nIndex];
					else
						sRaw += _T('.');
					sHexTemp.Format(_T("%2.2X "), pData[nIndex]);
					sHex += sHexTemp;
					nPartIndex++;
					nIndex++;
					}

				sRaw += _T(' ');
				sHex += _T(' ');
				}

			// Show the text
			sText.Format(_T("%-24.24s|%s\r\n"), sRaw, sHex);
			AddText(sText);
			}
		AddText(_T("\r\n"));
		}
	}

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
  
	GetEditCtrl().SetFont(&m_font, FALSE);
	}
