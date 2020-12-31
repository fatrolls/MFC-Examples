// TablePage.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\PukamSoft\PukamSoft.h"
//#include "MyPortfolio.h"
#include "TableData.h"
#include "TablePage.h"
#include "..\..\Common\UIClasses\SkinnedEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTablePage

CTablePage::CTablePage()
{
	m_bWorkInProgress = false;
	m_pEdit = NULL;
	m_nRowIndex = -1;

	m_bDetailsPage = FALSE;
}

CTablePage::~CTablePage()
{
	m_memBmp.DeleteObject();

	EmptyAllCollections();

	DestroyCheckBoxes();

	if (m_pEdit != NULL)
	{
		delete m_pEdit;
	}
}

BEGIN_MESSAGE_MAP(CTablePage, CWnd)
	//{{AFX_MSG_MAP(CTablePage)
	ON_WM_CREATE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTablePage message handlers

void CTablePage::InitializeTablePage(LPRECT lpRect, CWnd* pParentWnd, UINT nID)
{
	Create(NULL,"Table Page",WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,*lpRect,pParentWnd,nID,NULL);
}

int CTablePage::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rcClient;
	GetClientRect(&rcClient);

	CClientDC dc(this);
	m_memDC.CreateCompatibleDC(&dc);
	m_memBmp.CreateCompatibleBitmap(&dc,rcClient.Width(),rcClient.Height());
	m_memDC.SelectObject(&m_memBmp);
	
	return 0;
}

void CTablePage::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rcClient;
	GetClientRect(&rcClient);

	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),&m_memDC,0,0,SRCCOPY);
	// Do not call CWnd::OnPaint() for painting messages
}

void CTablePage::DrawPage(CObList* pObListOfTables)
{
	EmptyAllCollections();

	CRect rcClient;
	GetClientRect(&rcClient);

	m_memDC.FillSolidRect(&rcClient,m_crBackColor);

	CRect rcPaint(rcClient.left+m_nLeftMargin,
				rcClient.top+m_nTopMargin,
				rcClient.right-m_nRightMargin,
				rcClient.bottom-m_nBottomMargin);

	POINT ptCursor;

	POSITION Chkpos;
	Chkpos = m_obListOfCheckBox.GetHeadPosition();
	
	ptCursor.x = rcPaint.left;
	ptCursor.y = rcPaint.top;

	LOGFONT lf;
	CFont font;

	CClientDC dc(this);
	CRect rcCell;
	
	POSITION pos = pObListOfTables->GetHeadPosition();
	CTableData* pTableData = NULL;

	while(pos != NULL)
	{
		pTableData = (CTableData*)pObListOfTables->GetNext(pos);
		CSkinnedButton *pchkButton = NULL;

		memset(&lf,0,sizeof(LOGFONT));
		strcpy(lf.lfFaceName,"Arial");
		lf.lfHeight = 120;
		lf.lfWeight = FW_BOLD;
		lf.lfQuality = ANTIALIASED_QUALITY;

		font.CreatePointFontIndirect(&lf,&dc);
		m_memDC.SelectObject(&font);
		
		rcCell.left = ptCursor.x;
		rcCell.top = ptCursor.y;
		rcCell.right = rcCell.left;
		rcCell.bottom = rcCell.top; 

		for(int nColumnTitleIdx=0; nColumnTitleIdx < pTableData->GetColumnTitleCount(); nColumnTitleIdx++)
		{
			SColumnTitle* psColumnTitle = pTableData->GetColumnTitle(nColumnTitleIdx);	
					
			rcCell.left = ptCursor.x;
			rcCell.top = ptCursor.y;
			rcCell.right = rcCell.left+pTableData->GetColumnWidth(nColumnTitleIdx);
			rcCell.bottom = rcCell.top+psColumnTitle->nHeight; 

			m_memDC.FillSolidRect(rcCell.left,rcCell.top,rcCell.right-rcCell.left,rcCell.bottom-rcCell.top,psColumnTitle->crBackColor);
			m_memDC.SetBkMode(TRANSPARENT);
			m_memDC.SetTextColor(psColumnTitle->nFontColor);

			CString szColumnTitleText(psColumnTitle->szText);

			if(!szColumnTitleText.IsEmpty())
			{
				m_memDC.DrawText(szColumnTitleText,rcCell,DT_CENTER);
			}

			CPen pen;

			pen.CreatePen(PS_SOLID,2,pTableData->GetColumnTitleLineColor());
			m_memDC.SelectObject(&pen);
			m_memDC.MoveTo(rcCell.left,rcCell.bottom);
			m_memDC.LineTo(rcCell.right,rcCell.bottom);
			pen.DeleteObject();

			pen.CreatePen(PS_SOLID,1,pTableData->GetColumnTitleVLineColor());
			m_memDC.SelectObject(&pen);
			m_memDC.MoveTo(rcCell.right,rcCell.bottom);
			m_memDC.LineTo(rcCell.right,rcCell.top);
			pen.DeleteObject();

			ptCursor.x = rcCell.right + 1;
			ptCursor.y = rcCell.top;
		}

		font.DeleteObject();

		ptCursor.x = rcPaint.left;
		ptCursor.y = rcCell.bottom + 2;

		memset(&lf,0,sizeof(LOGFONT));
		strcpy(lf.lfFaceName,"Arial");
		lf.lfHeight = 90;
		lf.lfQuality = ANTIALIASED_QUALITY;
		
		font.CreatePointFontIndirect(&lf,&dc);
		m_memDC.SelectObject(&font);

		ptCursor.x = rcPaint.left;
		ptCursor.y = rcCell.bottom + 1;
		
		for(int nRowIdx=0; nRowIdx < pTableData->GetRowCount(); nRowIdx++)
		{
			CRow* pRow = pTableData->GetRow(nRowIdx);

			bool bHasCellLine = false;

			for(int nCellIdx=0; nCellIdx < pRow->GetCellCount(); nCellIdx++)
			{
				CCell* pCell = pRow->GetCell(nCellIdx);
				CRect rcCellLine;
				for(int nCellLineIdx=0; nCellLineIdx < pCell->GetLineCount(); nCellLineIdx++)
				{

					SCellLine* pSCellLine = pCell->GetCellLine(nCellLineIdx);

					if(nCellLineIdx == 0)
					{
						rcCell.left = ptCursor.x;
						rcCell.top = ptCursor.y;
						rcCell.right = rcCell.left + pTableData->GetColumnWidth(nCellIdx);
						rcCell.bottom = rcCell.top + (pSCellLine->nCellLineHeight * pRow->GetNoOfLineCount());
						m_memDC.FillSolidRect(rcCell.left,rcCell.top,rcCell.right-rcCell.left,rcCell.bottom-rcCell.top,pCell->GetCellBackColor());
						bHasCellLine = pSCellLine->bHasCellLine; 
					}
				
					if (pSCellLine->bIsButton)
					{
					}
					else if (pSCellLine->bIsCheckBox)
					{
						if (Chkpos != NULL)
						{
							pchkButton = (CSkinnedButton*) m_obListOfCheckBox.GetNext(Chkpos);
							pchkButton->MoveWindowEng(rcCell.left+3,rcCell.top+5,true);
						}
					}
					else
					{
						rcCellLine.left = ptCursor.x;
						rcCellLine.top = ptCursor.y;
						rcCellLine.right = rcCellLine.left+pTableData->GetColumnWidth(nCellIdx);
						rcCellLine.bottom = rcCellLine.top+pSCellLine->nCellLineHeight;

						memset(&lf,0,sizeof(LOGFONT));
						strcpy(lf.lfFaceName,"Arial");
						lf.lfHeight = pSCellLine->nFontHeight * 10;
						lf.lfWeight = (pSCellLine->nFontWeight==1)?FW_BOLD:FW_REGULAR;
						lf.lfQuality = ANTIALIASED_QUALITY;
						
						font.CreatePointFontIndirect(&lf,&dc);
						m_memDC.SelectObject(&font);

						m_memDC.FillSolidRect(rcCellLine.left,rcCellLine.top,rcCellLine.right-rcCellLine.left,rcCellLine.bottom-rcCellLine.top,pSCellLine->crBackColor);
						m_memDC.SetBkMode(TRANSPARENT);
						m_memDC.SetTextColor(pSCellLine->nFontColor);

						CString szCellText(pSCellLine->szText);

						if(!szCellText.IsEmpty())
						{
							m_memDC.DrawText(szCellText,rcCellLine,pSCellLine->nFormat);
							
							if (pSCellLine->bIsEditable)
							{
							}
							else
							{
							}
						}
					}

					ptCursor.x = rcCellLine.left;
					ptCursor.y = rcCellLine.bottom;

					font.DeleteObject();
				}

				if (bHasCellLine)
				{
					CPen pen;

					pen.CreatePen(PS_SOLID,1,pTableData->GetRowLineColor());
					m_memDC.SelectObject(&pen);
					m_memDC.MoveTo(rcCell.left,rcCell.bottom);
					m_memDC.LineTo(rcCell.right,rcCell.bottom);
					pen.DeleteObject();

					
					pen.CreatePen(PS_SOLID,1,pTableData->GetRowVLineColor());
					m_memDC.SelectObject(&pen);
					m_memDC.MoveTo(rcCell.right,rcCell.bottom);
					m_memDC.LineTo(rcCell.right,rcCell.top);
					pen.DeleteObject();
					
				}
				ptCursor.x = rcCell.right + 1;
				ptCursor.y = rcCell.top;	
			}
			ptCursor.x = rcPaint.left;
			ptCursor.y = rcCell.bottom + 1;
		}

		ptCursor.x = rcPaint.left;
		ptCursor.y = rcCell.bottom + 30;
	}
	m_nHeight = ptCursor.y - 29;

	SetWindowPos(NULL,0,0,606-25,m_nHeight,SWP_NOMOVE|SWP_NOZORDER);

	Invalidate(TRUE);
}

void CTablePage::SetPageMargins(int nLeft, int nTop, int nRight, int nBottom)
{
	m_nLeftMargin = nLeft;
	m_nTopMargin = nTop;
	m_nRightMargin = nRight;
	m_nBottomMargin = nBottom;
}

void CTablePage::SetPageBackColor(COLORREF crBackColor)
{
	m_crBackColor = crBackColor;
}

LRESULT CTablePage::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{

	return CWnd::WindowProc(message, wParam, lParam);
}

void CTablePage::EmptyAllCollections()
{
	m_ListOfCellInfo.RemoveAll();
}

BOOL CTablePage::PreTranslateMessage(MSG* pMsg) 
{
	switch(pMsg->message)
	{
	case WM_USER:
		{
			switch(LOWORD(pMsg->wParam))
			{
			case MSG_COMMAND:
				{
					if(HIWORD(pMsg->wParam) >= ID_TABLE_CHECK)
					{
						UINT nCheckBoxControlID;
						
						nCheckBoxControlID = HIWORD(pMsg->wParam);

						POSITION posCheckID = m_listOfCheckIDs.GetHeadPosition();
						POSITION posCheck = m_obListOfCheckBox.GetHeadPosition();

						UINT nID;
						CSkinnedButton *pchkButton = NULL;

						m_nRowIndex = -1;

						while(posCheckID != NULL)
						{	
							nID = m_listOfCheckIDs.GetNext(posCheckID);
							pchkButton = (CSkinnedButton*)m_obListOfCheckBox.GetNext(posCheck);

							m_nRowIndex++;

							if (nID == nCheckBoxControlID)
							{
								break;
							}
						}

						int nState =  pchkButton->GetCurrentState();

						if(nState == BUTTON_STATE_PRESSED)
						{
							GetParent()->PostMessage(pMsg->message,MSG_SETCHECK,(LPARAM)m_nRowIndex);
						}
						else
						{
							GetParent()->PostMessage(pMsg->message,MSG_UNCHECK,(LPARAM)m_nRowIndex);
						}		
					}
				break;
				}
			default:
				break;
			}
		return TRUE;
		}
	default:
		break;
	}
	return CWnd::PreTranslateMessage(pMsg);
}

void CTablePage::DrawTableHeader(CTableData *pTableData, POINT &ptCursor)
{
	LOGFONT lf;
	CFont font;

	CClientDC dc(this);

	memset(&lf,0,sizeof(LOGFONT));
	strcpy(lf.lfFaceName,"Arial");
	lf.lfHeight = 240;
	lf.lfQuality = ANTIALIASED_QUALITY;

	font.CreatePointFontIndirect(&lf,&dc);
	m_memDC.SelectObject(&font);

	UINT nTableID = pTableData->GetTableID();
	
	if(nTableID == ID_CI_TABLE)
	{
		m_bDetailsPage = TRUE;

		m_memDC.SetTextColor((COLORREF)DETAILS_TEXT_COLOR);

		CRect rcCell;
		rcCell.left = ptCursor.x;
		rcCell.top = ptCursor.y;

		TCHAR szDetails[] = "Report | ";

		m_memDC.DrawText((LPCTSTR)szDetails,strlen(szDetails),rcCell,DT_SINGLELINE | DT_CALCRECT | DT_LEFT);
		m_memDC.DrawText((LPCTSTR)szDetails,strlen(szDetails),rcCell,DT_BOTTOM | DT_SINGLELINE | DT_LEFT);

		int nCellHeight = rcCell.bottom - rcCell.top;

		TCHAR *szTitle = pTableData->GetTableTitle();
		m_memDC.SetTextColor(pTableData->GetTitleColor());

		rcCell.left = rcCell.right;

		m_memDC.DrawText((LPCTSTR)szTitle,strlen(szTitle),rcCell,DT_SINGLELINE | DT_CALCRECT | DT_LEFT);

		rcCell.bottom = rcCell.top + nCellHeight;
		
		m_memDC.DrawText((LPCTSTR)szTitle,strlen(szTitle),rcCell,DT_BOTTOM | DT_SINGLELINE | DT_LEFT);

		font.DeleteObject();

		rcCell.left = ptCursor.x;
		rcCell.top = ptCursor.y;

		if (0)
		{	
		}
		else
		{
			rcCell.left = rcCell.left + 349 + 73;
			
			STitleAttrib sTitleAttrib;

			POSITION pos = pTableData->GetAttribHeadPosition();

			if (pos == NULL)
			{
				ptCursor.y = rcCell.bottom + 20;
				return;
			}
				
			sTitleAttrib = pTableData->GetNextAttribute(pos);

			TCHAR *pszAttribute = sTitleAttrib.szAttribute;

			memset(&lf,0,sizeof(LOGFONT));
			strcpy(lf.lfFaceName,"Arial");
			lf.lfHeight = 80;
			lf.lfQuality = ANTIALIASED_QUALITY;

			font.CreatePointFontIndirect(&lf,&dc);
			m_memDC.SelectObject(&font);

			m_memDC.SetTextColor((COLORREF)TITLE_ATTRIBUTENAME_COLOR);

			m_memDC.DrawText((LPCTSTR)pszAttribute,strlen(pszAttribute),rcCell,DT_SINGLELINE | DT_CALCRECT | DT_CENTER | DT_TOP);

			rcCell.right = rcCell.left + 112 + 10;

			int nAttributeHeight = m_memDC.DrawText((LPCTSTR)pszAttribute,strlen(pszAttribute),rcCell,DT_TOP | DT_SINGLELINE | DT_CENTER);

			font.DeleteObject();

			TCHAR *pszAttribVal = sTitleAttrib.szValue;

			memset(&lf,0,sizeof(LOGFONT));
			strcpy(lf.lfFaceName,"Arial");
			lf.lfHeight = 140;
			lf.lfQuality = ANTIALIASED_QUALITY;

			font.CreatePointFontIndirect(&lf,&dc);
			m_memDC.SelectObject(&font);

			m_memDC.SetTextColor(pTableData->GetTitleColor());

			rcCell.top = rcCell.bottom + 0;
					
			m_memDC.DrawText((LPCTSTR)pszAttribVal,strlen(pszAttribVal),rcCell,DT_SINGLELINE | DT_CALCRECT | DT_CENTER | DT_TOP);

			rcCell.right = rcCell.left + 112 + 10;

			int nAttribValueHeight = m_memDC.DrawText((LPCTSTR)pszAttribVal,strlen(pszAttribVal),rcCell,DT_TOP | DT_SINGLELINE | DT_CENTER| DT_END_ELLIPSIS);

			font.DeleteObject();

			if (pos == NULL)
			{
				ptCursor.y = rcCell.bottom + 20;
				return;
			}

			CPen pen;

			pen.CreatePen(PS_SOLID,1,TITLE_DIVIDER_LINE_COLOR);
			m_memDC.SelectObject(&pen);
			m_memDC.MoveTo(rcCell.right,ptCursor.y);
			m_memDC.LineTo(rcCell.right,rcCell.bottom);
			pen.DeleteObject();

			rcCell.left = rcCell.right + 1;
			rcCell.top = ptCursor.y;
			rcCell.right = rcCell.left + 91;
			rcCell.bottom = rcCell.top + nAttributeHeight; 

			sTitleAttrib = pTableData->GetNextAttribute(pos);
			
			pszAttribute = sTitleAttrib.szAttribute;

			memset(&lf,0,sizeof(LOGFONT));
			strcpy(lf.lfFaceName,"Arial");
			lf.lfHeight = 80;
			lf.lfQuality = ANTIALIASED_QUALITY;

			font.CreatePointFontIndirect(&lf,&dc);
			m_memDC.SelectObject(&font);

			m_memDC.SetTextColor((COLORREF)TITLE_ATTRIBUTENAME_COLOR);

			m_memDC.DrawText((LPCTSTR)pszAttribute,strlen(pszAttribute),rcCell,DT_TOP | DT_SINGLELINE | DT_CENTER);

			font.DeleteObject();

			pszAttribVal = sTitleAttrib.szValue;

			memset(&lf,0,sizeof(LOGFONT));
			strcpy(lf.lfFaceName,"Arial");
			lf.lfHeight = 140;
			lf.lfQuality = ANTIALIASED_QUALITY;

			font.CreatePointFontIndirect(&lf,&dc);
			m_memDC.SelectObject(&font);

			m_memDC.SetTextColor(pTableData->GetTitleColor());

			rcCell.top = rcCell.bottom + 0;
			rcCell.bottom = rcCell.top + nAttribValueHeight;
					
			m_memDC.DrawText((LPCTSTR)pszAttribVal,strlen(pszAttribVal),rcCell,DT_TOP | DT_SINGLELINE | DT_CENTER);

			font.DeleteObject();

			if (pos == NULL)
			{
				ptCursor.y = rcCell.bottom + 20;
				return;
			}

			pen.CreatePen(PS_SOLID,1,TITLE_DIVIDER_LINE_COLOR);
			m_memDC.SelectObject(&pen);
			m_memDC.MoveTo(rcCell.right,ptCursor.y);
			m_memDC.LineTo(rcCell.right,rcCell.bottom);
			pen.DeleteObject();

			rcCell.left = rcCell.right + 1;
			rcCell.top = ptCursor.y;
			rcCell.right = rcCell.left + 116;
			rcCell.bottom = rcCell.top + nAttributeHeight; 

			sTitleAttrib = pTableData->GetNextAttribute(pos);
			
			pszAttribute = sTitleAttrib.szAttribute;

			memset(&lf,0,sizeof(LOGFONT));
			strcpy(lf.lfFaceName,"Arial");
			lf.lfHeight = 80;
			lf.lfQuality = ANTIALIASED_QUALITY;

			font.CreatePointFontIndirect(&lf,&dc);
			m_memDC.SelectObject(&font);

			m_memDC.SetTextColor((COLORREF)TITLE_ATTRIBUTENAME_COLOR);

			m_memDC.DrawText((LPCTSTR)pszAttribute,strlen(pszAttribute),rcCell,DT_TOP | DT_SINGLELINE | DT_CENTER);

			font.DeleteObject();

			pszAttribVal = sTitleAttrib.szValue;

			memset(&lf,0,sizeof(LOGFONT));
			strcpy(lf.lfFaceName,"Arial");
			lf.lfHeight = 140;
			lf.lfQuality = ANTIALIASED_QUALITY;

			font.CreatePointFontIndirect(&lf,&dc);
			m_memDC.SelectObject(&font);

			m_memDC.SetTextColor(pTableData->GetTitleColor());

			rcCell.top = rcCell.bottom + 0;
			rcCell.bottom = rcCell.top + nAttribValueHeight;
					
			m_memDC.DrawText((LPCTSTR)pszAttribVal,strlen(pszAttribVal),rcCell,DT_TOP | DT_SINGLELINE | DT_CENTER);

			font.DeleteObject();
			
			if (pos == NULL)
			{
				ptCursor.y = rcCell.bottom + 20;
				return;
			}

			pen.CreatePen(PS_SOLID,1,TITLE_DIVIDER_LINE_COLOR);
			m_memDC.SelectObject(&pen);
			m_memDC.MoveTo(rcCell.right,ptCursor.y);
			m_memDC.LineTo(rcCell.right,rcCell.bottom);
			pen.DeleteObject();

			rcCell.left = rcCell.right + 1;
			rcCell.top = ptCursor.y;
			rcCell.right = rcCell.left + 83;
			rcCell.bottom = rcCell.top + nAttributeHeight; 

			sTitleAttrib = pTableData->GetNextAttribute(pos);
			
			pszAttribute = sTitleAttrib.szAttribute;

			memset(&lf,0,sizeof(LOGFONT));
			strcpy(lf.lfFaceName,"Arial");
			lf.lfHeight = 80;
			lf.lfQuality = ANTIALIASED_QUALITY;

			font.CreatePointFontIndirect(&lf,&dc);
			m_memDC.SelectObject(&font);

			m_memDC.SetTextColor((COLORREF)TITLE_ATTRIBUTENAME_COLOR);

			m_memDC.DrawText((LPCTSTR)pszAttribute,strlen(pszAttribute),rcCell,DT_TOP | DT_SINGLELINE | DT_CENTER);

			font.DeleteObject();

			pszAttribVal = sTitleAttrib.szValue;

			memset(&lf,0,sizeof(LOGFONT));
			strcpy(lf.lfFaceName,"Arial");
			lf.lfHeight = 140;
			lf.lfQuality = ANTIALIASED_QUALITY;

			font.CreatePointFontIndirect(&lf,&dc);
			m_memDC.SelectObject(&font);

			m_memDC.SetTextColor(pTableData->GetTitleColor());

			rcCell.top = rcCell.bottom + 0;
			rcCell.bottom = rcCell.top + nAttribValueHeight;
					
			m_memDC.DrawText((LPCTSTR)pszAttribVal,strlen(pszAttribVal),rcCell,DT_TOP | DT_SINGLELINE | DT_CENTER);

			font.DeleteObject();

			ptCursor.y = rcCell.bottom + 20;
		}
	}
}

int CTablePage::GetHeight()
{
	return m_nHeight;
}

void CTablePage::CreateCheckBoxes(CObList *pObListOfTables)
{
	POSITION pos = pObListOfTables->GetHeadPosition();
	int nID = 1;
	
	UINT nCheckBoxControlID = ID_TABLE_CHECK - 1;

	while(pos != NULL)
	{
		CTableData* pTableData = (CTableData*)pObListOfTables->GetNext(pos);

		for(int nRowIdx=0; nRowIdx < pTableData->GetRowCount(); nRowIdx++)
		{
			CRow* pRow = pTableData->GetRow(nRowIdx);
			for(int nCellIdx=0; nCellIdx < pRow->GetCellCount(); nCellIdx++)
			{
				CCell* pCell = pRow->GetCell(nCellIdx);
				for(int nCellLineIdx=0; nCellLineIdx < pCell->GetLineCount(); nCellLineIdx++)
				{
					SCellLine* pSCellLine = pCell->GetCellLine(nCellLineIdx);
				
					if (pSCellLine->bIsCheckBox)
					{
						nCheckBoxControlID++;
						CSkinnedButton *pchkButton = NULL;
						pchkButton = new CSkinnedButton;
						pchkButton->SetImageResource(IDB_UNCHECK,IDB_UNCHECK,IDB_CHECK);
						pchkButton->CreateSkinControl("",CRect(0,0,18,18),this,nCheckBoxControlID,FL_BUTTON_TYPE_TOGGLE);
						m_obListOfCheckBox.AddTail((CObject*)pchkButton);
						m_listOfCheckIDs.AddTail(nCheckBoxControlID);
					}
				}
			}
		}
	}
}

void CTablePage::DestroyCheckBoxes()
{
	CSkinnedButton *pchkButton = NULL;
	POSITION pos;

	for(pos = m_obListOfCheckBox.GetHeadPosition();pos != NULL;)
	{
		pchkButton = (CSkinnedButton *)m_obListOfCheckBox.GetNext(pos);
		delete pchkButton;
		pchkButton = NULL;
	}

	m_obListOfCheckBox.RemoveAll();
	m_listOfCheckIDs.RemoveAll();
}

void CTablePage::ResetCheckBoxes(CObList* pObListOfTables)
{
	CSkinnedButton *pchkButton = NULL;
	POSITION pos;

	for(pos = m_obListOfCheckBox.GetHeadPosition();pos != NULL;)
	{
		pchkButton = (CSkinnedButton *)m_obListOfCheckBox.GetNext(pos);
		if(pchkButton->GetCurrentState() == BUTTON_STATE_PRESSED)
		{
			pchkButton->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
		}
	}
}