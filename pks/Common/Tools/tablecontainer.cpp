// TableContainer.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\PukamSoft\PukamSoft.h"
//#include "MyPortfolio.h"
#include "TableContainer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTableContainer

CTableContainer::CTableContainer()
{
	m_pMainTablePage	= NULL;
	m_pITTablePage		= NULL;
	m_pOTTablePage		= NULL;
	m_pVScrollBar		= NULL;
	m_pITTableData		= NULL;
	m_pOTTableData		= NULL;
	m_lPKID				= -1;
	m_nCurrentTableID	= ID_CI_TABLE;
	m_csPageTitle		= "";
	m_nSelectedRow		= -1;
	m_csPKID			= "";
	m_csSerialNumber	= "";
	m_csCompanyName		= "";
}

CTableContainer::~CTableContainer()
{
	if(m_pMainTablePage != NULL)
	{
		m_pMainTablePage->DestroyCheckBoxes();
		delete m_pMainTablePage;
		m_pMainTablePage = NULL;
	}

	if(m_pITTablePage != NULL)
	{
		m_pITTablePage->DestroyCheckBoxes();
		delete m_pITTablePage;
		m_pITTablePage = NULL;
	}

	if(m_pITTableData != NULL)
	{
		delete m_pITTableData;
		m_pITTableData = NULL;
	}

	if(m_pOTTablePage != NULL)
	{
		m_pOTTablePage->DestroyCheckBoxes();
		delete m_pOTTablePage;
		m_pOTTablePage = NULL;
	}

	if(m_pOTTableData != NULL)
	{
		delete m_pOTTableData;
		m_pOTTableData = NULL;
	}

	if(m_pVScrollBar != NULL)
	{
		delete m_pVScrollBar;
		m_pVScrollBar = NULL;
	}

	m_listOfTableID.RemoveAll();

	CTableData *pTableData;
	POSITION pos = m_obListOfTables.GetHeadPosition();

	while(pos != NULL)
	{
		pTableData = (CTableData*)m_obListOfTables.GetNext(pos);
		delete pTableData;
		pTableData = 0;
	}

	m_obListOfTables.RemoveAll();
}


BEGIN_MESSAGE_MAP(CTableContainer, CWnd)
	//{{AFX_MSG_MAP(CTableContainer)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTableContainer message handlers

int CTableContainer::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rcClient;
	GetClientRect(&rcClient);

	m_pMainTablePage = new CTablePage; 
	m_pMainTablePage->InitializeTablePage(CRect(25,10,606,20000),this,5000/*ID_TABLEPAGE*/);
	m_pMainTablePage->SetPageMargins(0,0,0,0);
	m_pMainTablePage->SetPageBackColor(BLACK/*RGB(255,255,255)*/);

	m_pVScrollBar = new CSkinnedScrollBar;
	m_pVScrollBar->SetImageResource(IDB_BITMAP_SCROLLBAR_BACK);
	m_pVScrollBar->SetScrollButtonImageResource(IDB_BITMAP_SCROLLBAR_BUTTON);
	m_pVScrollBar->SetScrollUpButtonImageResource(IDB_BITMAP_SCROLLBAR_UP);
	m_pVScrollBar->SetScrollDownButtonImageResource(IDB_BITMAP_SCROLLBAR_DOWN);

	m_pVScrollBar->CreateSkinControl("",CRect(611,10,626,410),this,5001/*ID_VSCROLLBAR*/);
	m_pVScrollBar->SetRangeMin(0);
	m_pVScrollBar->SetRangeMax(100);
	m_pVScrollBar->SetWindowPos(&wndTop,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE|SWP_HIDEWINDOW);
	
	return 0;
}

void CTableContainer::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rcClient;
	GetClientRect(&rcClient);

	dc.FillSolidRect(&rcClient,BLACK/*RGB(255,255,255)*/);
	CPen pen;
	pen.CreatePen(PS_SOLID,1,RGB(175,20,4));
	dc.SelectObject(&pen);
	dc.MoveTo(2,0);
	dc.LineTo(2,410);
	dc.MoveTo(2,410);
	dc.LineTo(626,410);
	dc.MoveTo(626,410);
	dc.LineTo(626,0);
	dc.MoveTo(626,0);
	dc.LineTo(2,0);
	
	// Do not call CWnd::OnPaint() for painting messages
}

BOOL CTableContainer::AddItem(UINT nTableID, int nRow, int nCol, SCellLine* pSCellLine)
{
	BOOL bRet = FALSE;
	if(!(m_listOfTableID.IsEmpty() || m_obListOfTables.IsEmpty()))
	{	
		POSITION posID = m_listOfTableID.GetHeadPosition();
		POSITION posTable = m_obListOfTables.GetHeadPosition();
		while((posID != NULL) && (posTable != NULL))
		{
			UINT nID = m_listOfTableID.GetNext(posID);
			CTableData* pTableData = (CTableData*)m_obListOfTables.GetNext(posTable);
			if(nID == nTableID)
			{
				pTableData->AddItem(nRow,nCol,pSCellLine);
				bRet = TRUE;
				break;
			}
		}
	}
	return bRet;
}

BOOL CTableContainer::ModifyItem(UINT nTableID, int nRow, int nCol, int nCellLine, SCellLine* pSCellLine)
{
	BOOL bRet = FALSE;
	if(!(m_listOfTableID.IsEmpty() || m_obListOfTables.IsEmpty()))
	{	
		POSITION posID = m_listOfTableID.GetHeadPosition();
		POSITION posTable = m_obListOfTables.GetHeadPosition();
		while((posID != NULL) && (posTable != NULL))
		{
			UINT nID = m_listOfTableID.GetNext(posID);
			CTableData* pTableData = (CTableData*)m_obListOfTables.GetNext(posTable);
			if(nID == nTableID)
			{
				pTableData->ModifyItem(nRow,nCol,nCellLine,pSCellLine);
				bRet = TRUE;
				break;
			}
		}
	}
	return bRet;
}

BOOL CTableContainer::RemoveItem(UINT nTableID, int nRow, int nCol)
{
	BOOL bRet = FALSE;
	if(!(m_listOfTableID.IsEmpty() || m_obListOfTables.IsEmpty()))
	{	
		POSITION posID = m_listOfTableID.GetHeadPosition();
		POSITION posTable = m_obListOfTables.GetHeadPosition();
		while((posID != NULL) && (posTable != NULL))
		{
			UINT nID = m_listOfTableID.GetNext(posID);
			CTableData* pTableData = (CTableData*)m_obListOfTables.GetNext(posTable);
			if(nID == nTableID)
			{
				pTableData->RemoveItem(nRow);
				bRet = TRUE;
				break;
			}
		}
	}
	return bRet;
}

BOOL CTableContainer::RemoveAllItems(UINT nTableID)
{
	BOOL bRet = FALSE;
	if(!(m_listOfTableID.IsEmpty() || m_obListOfTables.IsEmpty()))
	{	
		POSITION posID = m_listOfTableID.GetHeadPosition();
		POSITION posTable = m_obListOfTables.GetHeadPosition();
		while((posID != NULL) && (posTable != NULL))
		{
			UINT nID = m_listOfTableID.GetNext(posID);
			CTableData* pTableData = (CTableData*)m_obListOfTables.GetNext(posTable);
			if(nID == nTableID)
			{
				pTableData->RemoveAll();
				bRet = TRUE;
				break;
			}
		}
	}
	return bRet;
}

void CTableContainer::SetColumnWidth(UINT nTableID, int nWidth, int nIndex/*=-1*/)
{
	if(m_listOfTableID.IsEmpty() || m_obListOfTables.IsEmpty())
	{
		return;
	}
	POSITION posID = m_listOfTableID.GetHeadPosition();
	POSITION posTable = m_obListOfTables.GetHeadPosition();
	while((posID != NULL) && (posTable != NULL))
	{
		UINT nID = m_listOfTableID.GetNext(posID);
		CTableData* pTableData = (CTableData*)m_obListOfTables.GetNext(posTable);
		if(nID == nTableID)
		{
			pTableData->SetColumnWidth(nWidth,nIndex);
			break;
		}
	}
}

void CTableContainer::AddColumnTitle(UINT nTableID, SColumnTitle *psColumnTitle)
{
	if(m_listOfTableID.IsEmpty() || m_obListOfTables.IsEmpty())
	{
		return;
	}
	POSITION posID = m_listOfTableID.GetHeadPosition();
	POSITION posTable = m_obListOfTables.GetHeadPosition();
	while((posID != NULL) && (posTable != NULL))
	{
		UINT nID = m_listOfTableID.GetNext(posID);
		CTableData* pTableData = (CTableData*)m_obListOfTables.GetNext(posTable);
		if(nID == nTableID)
		{
			pTableData->AddColumnTitle(psColumnTitle);
			break;
		}
	}
}

void CTableContainer::SetColumnTitleLineColor(UINT nTableID, COLORREF crColumnTitleLineColor)
{
	if(m_listOfTableID.IsEmpty() || m_obListOfTables.IsEmpty())
	{
		return;
	}
	POSITION posID = m_listOfTableID.GetHeadPosition();
	POSITION posTable = m_obListOfTables.GetHeadPosition();
	while((posID != NULL) && (posTable != NULL))
	{
		UINT nID = m_listOfTableID.GetNext(posID);
		CTableData* pTableData = (CTableData*)m_obListOfTables.GetNext(posTable);
		if(nID == nTableID)
		{
			pTableData->SetColumnTitleLineColor(crColumnTitleLineColor);
			break;
		}
	}
}

void CTableContainer::SetColumnTitleVLineColor(UINT nTableID, COLORREF crColumnTitleVLineColor)
{
	if(m_listOfTableID.IsEmpty() || m_obListOfTables.IsEmpty())
	{
		return;
	}
	POSITION posID = m_listOfTableID.GetHeadPosition();
	POSITION posTable = m_obListOfTables.GetHeadPosition();
	while((posID != NULL) && (posTable != NULL))
	{
		UINT nID = m_listOfTableID.GetNext(posID);
		CTableData* pTableData = (CTableData*)m_obListOfTables.GetNext(posTable);
		if(nID == nTableID)
		{
			pTableData->SetColumnTitleVLineColor(crColumnTitleVLineColor);
			break;
		}
	}
}

void CTableContainer::SetTableTitleColor(UINT nTableID, COLORREF crTitleColor)
{
	if(m_listOfTableID.IsEmpty() || m_obListOfTables.IsEmpty())
	{
		return;
	}
	POSITION posID = m_listOfTableID.GetHeadPosition();
	POSITION posTable = m_obListOfTables.GetHeadPosition();
	while((posID != NULL) && (posTable != NULL))
	{
		UINT nID = m_listOfTableID.GetNext(posID);
		CTableData* pTableData = (CTableData*)m_obListOfTables.GetNext(posTable);
		if(nID == nTableID)
		{
			pTableData->SetTitleColor(crTitleColor);
			break;
		}
	}
}

void CTableContainer::SetRowLineColor(UINT nTableID, COLORREF crRowLineColor)
{
	if(m_listOfTableID.IsEmpty() || m_obListOfTables.IsEmpty())
	{
		return;
	}
	POSITION posID = m_listOfTableID.GetHeadPosition();
	POSITION posTable = m_obListOfTables.GetHeadPosition();
	while((posID != NULL) && (posTable != NULL))
	{
		UINT nID = m_listOfTableID.GetNext(posID);
		CTableData* pTableData = (CTableData*)m_obListOfTables.GetNext(posTable);
		if(nID == nTableID)
		{
			pTableData->SetRowLineColor(crRowLineColor);
			break;
		}
	}
}

void CTableContainer::SetRowVLineColor(UINT nTableID, COLORREF crRowVLineColor)
{
	if(m_listOfTableID.IsEmpty() || m_obListOfTables.IsEmpty())
	{
		return;
	}
	POSITION posID = m_listOfTableID.GetHeadPosition();
	POSITION posTable = m_obListOfTables.GetHeadPosition();
	while((posID != NULL) && (posTable != NULL))
	{
		UINT nID = m_listOfTableID.GetNext(posID);
		CTableData* pTableData = (CTableData*)m_obListOfTables.GetNext(posTable);
		if(nID == nTableID)
		{
			pTableData->SetRowVLineColor(crRowVLineColor);
			break;
		}
	}
}

void CTableContainer::SetTableTitle(UINT nTableID,TCHAR *pszTitle)
{
	if(m_listOfTableID.IsEmpty() || m_obListOfTables.IsEmpty())
	{
		return;
	}
	POSITION posID = m_listOfTableID.GetHeadPosition();
	POSITION posTable = m_obListOfTables.GetHeadPosition();
	while((posID != NULL) && (posTable != NULL))
	{
		UINT nID = m_listOfTableID.GetNext(posID);
		CTableData* pTableData = (CTableData*)m_obListOfTables.GetNext(posTable);
		if(nID == nTableID)
		{
			pTableData->SetTableTitle(pszTitle);
			break;
		}
	}
}

void CTableContainer::CreateTableEng(UINT nTableID)
{
	CTableData* pTableData = new CTableData(nTableID);
	m_obListOfTables.AddTail((CObject*)pTableData);
	m_listOfTableID.AddTail(nTableID);
}

void CTableContainer::RemoveTableEng(UINT nTableID)
{
	if(m_listOfTableID.IsEmpty() || m_obListOfTables.IsEmpty())
	{
		return;
	}
	POSITION posID = m_listOfTableID.GetHeadPosition();
	POSITION posTable = m_obListOfTables.GetHeadPosition();
	while((posID != NULL) && (posTable != NULL))
	{
		UINT nID = m_listOfTableID.GetNext(posID);
		
		if(nID == nTableID)
		{
			m_obListOfTables.RemoveAt(posTable);
			m_listOfTableID.RemoveAt(posID);
			break;
		}
	}
}

void CTableContainer::DrawTable()
{
	m_pMainTablePage->CreateCheckBoxes(&m_obListOfTables);
	m_pMainTablePage->DrawPage(&m_obListOfTables);
	ShowVerticalScroll(m_pMainTablePage->GetHeight());
}

void CTableContainer::SetDimensions(UINT nTableID,int nRows, int nCols)
{
	if(m_listOfTableID.IsEmpty() || m_obListOfTables.IsEmpty())
	{
		return;
	}

	POSITION posID = m_listOfTableID.GetHeadPosition();
	POSITION posTable = m_obListOfTables.GetHeadPosition();
	while((posID != NULL) && (posTable != NULL))
	{
		UINT nID = m_listOfTableID.GetNext(posID);
		CTableData* pTableData = (CTableData*)m_obListOfTables.GetNext(posTable);
		if(nID == nTableID)
		{
			pTableData->SetDimensions(nRows,nCols);
			break;
		}
	}	
}

SCellLine CTableContainer::GetItem(UINT nTableID, int nRow, int nCol, int nCellLine)
{
	SCellLine sCellLine;
	memset(&sCellLine,0,sizeof(SCellLine));

	if(!(m_listOfTableID.IsEmpty() || m_obListOfTables.IsEmpty()))
	{	
		POSITION posID = m_listOfTableID.GetHeadPosition();
		POSITION posTable = m_obListOfTables.GetHeadPosition();
		while((posID != NULL) && (posTable != NULL))
		{
			UINT nID = m_listOfTableID.GetNext(posID);
			CTableData* pTableData = (CTableData*)m_obListOfTables.GetNext(posTable);
			if(nID == nTableID)
			{
				sCellLine = pTableData->GetItem(nRow,nCol,nCellLine);
				return sCellLine;
				break;
			}
		}
	}
	return sCellLine;
}

int CTableContainer::GetRowCount(UINT nTableID)
{
	if(!(m_listOfTableID.IsEmpty() || m_obListOfTables.IsEmpty()))
	{	
		POSITION posID = m_listOfTableID.GetHeadPosition();
		POSITION posTable = m_obListOfTables.GetHeadPosition();
		while((posID != NULL) && (posTable != NULL))
		{
			UINT nID = m_listOfTableID.GetNext(posID);
			CTableData* pTableData = (CTableData*)m_obListOfTables.GetNext(posTable);
			if(nID == nTableID)
			{
				return pTableData->GetRowCount();
				break;
			}
		}
	}

	return -1;
}

void CTableContainer::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	
	CWnd::OnShowWindow(bShow, nStatus);
	
	if (bShow)
	{
		m_pMainTablePage->ShowWindow(SW_NORMAL);
	}
	else
	{
		m_pMainTablePage->ShowWindow(SW_HIDE);	
	}
}

BOOL CTableContainer::PreTranslateMessage(MSG* pMsg) 
{
	switch(pMsg->message)
	{
	case WM_USER:
		{	
			switch(pMsg->wParam)
			{
			case MSG_SETCHECK:
				{
					int nRowIndex = pMsg->lParam;
					m_nSelectedRow = nRowIndex;
					SCellLine sCellCheck;
					if(m_pMainTablePage->IsWindowVisible())
					{
						POSITION pos = m_obListOfTables.GetHeadPosition();
						while(pos != NULL)
						{
							CTableData* pTableData = (CTableData*)m_obListOfTables.GetNext(pos);
							sCellCheck = pTableData->GetItem(nRowIndex,0,0);
							sCellCheck.bIsChecked = TRUE;
							pTableData->ModifyItem(nRowIndex,0,0,&sCellCheck);
							SCellLine sCellCompany = pTableData->GetItem(nRowIndex,1,0);
							SCellLine sCellCustomerID = pTableData->GetItem(nRowIndex,2,0);
							m_csCompanyName = sCellCompany.szText;
							m_csPKID = sCellCustomerID.szText;
						}
					}
					else if(m_pITTablePage != NULL && m_pITTablePage->IsWindowVisible())
					{
						sCellCheck = m_pITTableData->GetItem(nRowIndex,0,0);
						sCellCheck.bIsChecked = TRUE;
						m_pITTableData->ModifyItem(nRowIndex,0,0,&sCellCheck);
						if(m_pITTableData->GetTableID() == ID_IT_TABLE)
						{
							SCellLine sCellCustomerID = m_pITTableData->GetItem(nRowIndex,0,0);
							SCellLine sCellSerialNumber = m_pITTableData->GetItem(nRowIndex,1,0);
							m_csPKID = sCellCustomerID.szText;
							m_csSerialNumber = sCellSerialNumber.szText;
						}
					}
				}
				break;
			case MSG_UNCHECK:
				{
					int nRowIndex = pMsg->lParam;
					SCellLine sCellUnCheck;
					if(m_pMainTablePage->IsWindowVisible())
					{
						POSITION pos = m_obListOfTables.GetHeadPosition();
						while(pos != NULL)
						{
							CTableData* pTableData = (CTableData*)m_obListOfTables.GetNext(pos);
							sCellUnCheck = pTableData->GetItem(nRowIndex,0,0);
							sCellUnCheck.bIsChecked = FALSE;
							pTableData->ModifyItem(nRowIndex,0,0,&sCellUnCheck);
						}
					}
					else if(m_pITTablePage != NULL && m_pITTablePage->IsWindowVisible())
					{
						sCellUnCheck = m_pITTableData->GetItem(nRowIndex,0,0);
						sCellUnCheck.bIsChecked = FALSE;
						m_pITTableData->ModifyItem(nRowIndex,0,0,&sCellUnCheck);
					}
				}
				break;
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

void CTableContainer::ShowVerticalScroll(int nTableHeight)
{
	if (m_pMainTablePage->IsWindowVisible())
	{	
		if (nTableHeight > 400)
		{
			m_pVScrollBar->MoveWindowEng(CRect(605,70,620,410),TRUE);
			m_pVScrollBar->SetPos(0);
			m_pVScrollBar->ShowWindow(SW_NORMAL);
		}
		else
		{
			m_pVScrollBar->ShowWindow(SW_HIDE);
		}

		m_pMainTablePage->SetWindowPos(NULL,25,10,606,20000,SWP_NOZORDER|SWP_NOSIZE);
	}
	else if (m_pITTablePage != NULL && m_pITTablePage->IsWindowVisible())
	{	
		if (nTableHeight > 400)
		{
			m_pVScrollBar->MoveWindowEng(CRect(605,70,620,410),TRUE);
			m_pVScrollBar->SetPos(0);
			m_pVScrollBar->ShowWindow(SW_NORMAL);
		}
		else
		{
			m_pVScrollBar->ShowWindow(SW_HIDE);
		}

		m_pITTablePage->SetWindowPos(NULL,25,10,606,20000,SWP_NOZORDER|SWP_NOSIZE);
	}
	else if (m_pOTTablePage != NULL && m_pOTTablePage->IsWindowVisible())
	{	
		if (nTableHeight > 400)
		{
			m_pVScrollBar->MoveWindowEng(CRect(605,70,620,410),TRUE);
			m_pVScrollBar->SetPos(0);
			m_pVScrollBar->ShowWindow(SW_NORMAL);
		}
		else
		{
			m_pVScrollBar->ShowWindow(SW_HIDE);
		}

		m_pOTTablePage->SetWindowPos(NULL,25,10,606,20000,SWP_NOZORDER|SWP_NOSIZE);
	}
}

void CTableContainer::PopulateTable(UINT nTableID)
{
	CCustomDB *pdbWrapper = ((CPukamSoftApp*)AfxGetApp())->GetConnectionObject();

	RemoveAllItems(nTableID);

	if(nTableID == ID_CI_TABLE)
	{
		CStringArray csArrayOfRecords[5];

		COLORREF crTitleBack = RGB(164,92,0);
		COLORREF crTitleText = RGB(255,223,0);

		CString szFields="vCompanyName,pk_vCustomerID,vContactPerson,vPhoneO,vFax";
		
		CString csTableName("Customer_Info");

		pdbWrapper->Select(csTableName,csArrayOfRecords,5,(char*)(LPCTSTR)szFields);

		if (csArrayOfRecords[0].GetSize() > 0)
		{
			SetDimensions(nTableID,csArrayOfRecords[0].GetSize() + 1,9);
		}
		else
		{
			SetDimensions(nTableID,1,9);
		}
		
		SetColumnTitleLineColor(nTableID, crTitleBack);
		SetRowLineColor(nTableID, crTitleBack);
		SetColumnTitleVLineColor(nTableID, RGB(249,231,207));
		SetRowVLineColor(nTableID, crTitleBack);

		SColumnTitle sColumnTitle;

		strcpy(sColumnTitle.szText,"");
		sColumnTitle.nFontColor=crTitleText;
		sColumnTitle.crBackColor=crTitleBack;
		sColumnTitle.nHeight=35;
		AddColumnTitle(nTableID,&sColumnTitle);

		strcpy(sColumnTitle.szText,"Company Name");
		sColumnTitle.nFontColor=crTitleText;
		sColumnTitle.crBackColor=crTitleBack;
		sColumnTitle.nHeight=35;
		AddColumnTitle(nTableID,&sColumnTitle);

		strcpy(sColumnTitle.szText,"Customer\nID");
		sColumnTitle.nFontColor=crTitleText;
		sColumnTitle.crBackColor=crTitleBack;
		AddColumnTitle(nTableID,&sColumnTitle);

		strcpy(sColumnTitle.szText,"Contact Person");
		sColumnTitle.nFontColor=crTitleText;
		sColumnTitle.crBackColor=crTitleBack;
		AddColumnTitle(nTableID,&sColumnTitle);

		strcpy(sColumnTitle.szText,"Phone\nNumber");
		sColumnTitle.nFontColor=crTitleText;
		sColumnTitle.crBackColor=crTitleBack;
		AddColumnTitle(nTableID,&sColumnTitle);

		SetColumnWidth(nTableID,25,0);
		SetColumnWidth(nTableID,195,1);
		SetColumnWidth(nTableID,95,2);
		SetColumnWidth(nTableID,145,3);
		SetColumnWidth(nTableID,107,4);
		
		SCellLine sCellLine;
		
		for(int i=0; i < csArrayOfRecords[0].GetSize();i++)
		{
			memset(&sCellLine,0,sizeof(SCellLine));
			sCellLine.crBackColor = RGB(249,231,207);
			sCellLine.nCellLineHeight = 28;
			sCellLine.bHasCellLine = true;
			sCellLine.bIsButton = FALSE;
			sCellLine.bIsCheckBox = TRUE;
			wsprintf(sCellLine.szText,"%s",csArrayOfRecords[1].GetAt(i));
			AddItem(nTableID,i,0,&sCellLine);

			memset(&sCellLine,0,sizeof(SCellLine));
			sCellLine.crBackColor = RGB(255,255,255);
			sCellLine.nFontHeight = 12;
			sCellLine.nFontColor = RGB(59,59,59);
			sCellLine.nFontWeight = 1;
			sCellLine.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS; 
			sCellLine.nCellLineHeight = 28;
			sCellLine.bHasCellLine = true;
			wsprintf(sCellLine.szText,"%s",csArrayOfRecords[0].GetAt(i));
			AddItem(nTableID,i,1,&sCellLine);

			memset(&sCellLine,0,sizeof(SCellLine));
			sCellLine.crBackColor = RGB(249,231,207);
			sCellLine.nFontHeight = 12;
			sCellLine.nFontColor = RGB(59,59,59);
			sCellLine.nFontWeight = 0;
			sCellLine.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE;   
			sCellLine.nCellLineHeight = 28;
			sCellLine.bHasCellLine = true;
			wsprintf(sCellLine.szText,"%s",csArrayOfRecords[1].GetAt(i));
			AddItem(nTableID,i,2,&sCellLine);

			memset(&sCellLine,0,sizeof(SCellLine));
			sCellLine.crBackColor = RGB(255,255,255);
			sCellLine.nFontHeight = 12;
			sCellLine.nFontColor = RGB(59,59,59);
			sCellLine.nFontWeight = 0;
			sCellLine.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE;
			sCellLine.nCellLineHeight = 28;
			sCellLine.bHasCellLine = true;
			wsprintf(sCellLine.szText,"%s",csArrayOfRecords[2].GetAt(i));
			AddItem(nTableID,i,3,&sCellLine);

			memset(&sCellLine,0,sizeof(SCellLine));
			sCellLine.crBackColor = RGB(249,231,207);
			sCellLine.nFontHeight = 12;
			sCellLine.nFontColor = RGB(59,59,59);
			sCellLine.nFontWeight = 1;
			sCellLine.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;   
			sCellLine.nCellLineHeight = 28;
			sCellLine.bIsEditable = true;
			sCellLine.bHasCellLine = true;
			wsprintf(sCellLine.szText,"%s",csArrayOfRecords[3].GetAt(i));
			AddItem(nTableID,i,4,&sCellLine);
		}
	}
}

CString CTableContainer::GetPageTitle()
{
	return m_csPageTitle;
}

void CTableContainer::PopulateDetailsTable(CTableData *pDetailsTable, UINT nTableID, long lPKID)
{
	CCustomDB *pdbWrapper = ((CPukamSoftApp*)AfxGetApp())->GetConnectionObject();

	if (nTableID == ID_IT_TABLE)
	{
		CStringArray csArrayOfRecords[6];

		COLORREF crTitleBack = RGB(88,122,0);
		COLORREF crTitleText = RGB(144,212,11);

		CString szFields="pk_vSerialNumber,dtDate,vCategory,nQuantity,vStorageLocation,nBalanceQuantity";
		CString csCondition;
		csCondition.Format("where fk_vCustomerID = '%s'",m_csPKID);
		
		CString csTableName("Transactions_Inward");

		pdbWrapper->Select(csTableName,csArrayOfRecords,6,(char*)(LPCTSTR)szFields,csCondition);

		if (csArrayOfRecords[0].GetSize() > 0)
		{
			pDetailsTable->SetDimensions(csArrayOfRecords[0].GetSize() + 1,7);
		}
		else
		{
			pDetailsTable->SetDimensions(1,7);
		}
		
		SColumnTitle sColumnTitle;

		strcpy(sColumnTitle.szText,"");
		sColumnTitle.nFontColor=crTitleText;
		sColumnTitle.crBackColor=crTitleBack;
		sColumnTitle.nHeight=35;
		pDetailsTable->AddColumnTitle(&sColumnTitle);

		strcpy(sColumnTitle.szText,"Serial\nNumber");
		sColumnTitle.nFontColor=crTitleText;
		sColumnTitle.crBackColor=crTitleBack;
		sColumnTitle.nHeight=35;
		pDetailsTable->AddColumnTitle(&sColumnTitle);

		strcpy(sColumnTitle.szText,"Date");
		sColumnTitle.nFontColor=crTitleText;
		sColumnTitle.crBackColor=crTitleBack;
		pDetailsTable->AddColumnTitle(&sColumnTitle);

		strcpy(sColumnTitle.szText,"Category");
		sColumnTitle.nFontColor=crTitleText;
		sColumnTitle.crBackColor=crTitleBack;
		pDetailsTable->AddColumnTitle(&sColumnTitle);

		strcpy(sColumnTitle.szText,"Quantity");
		sColumnTitle.nFontColor=crTitleText;
		sColumnTitle.crBackColor=crTitleBack;
		pDetailsTable->AddColumnTitle(&sColumnTitle);

		strcpy(sColumnTitle.szText,"Storage\nLocation");
		sColumnTitle.nFontColor=crTitleText;
		sColumnTitle.crBackColor=crTitleBack;
		pDetailsTable->AddColumnTitle(&sColumnTitle);

		strcpy(sColumnTitle.szText,"Balance\nQuantity");
		sColumnTitle.nFontColor=crTitleText;
		sColumnTitle.crBackColor=crTitleBack;
		pDetailsTable->AddColumnTitle(&sColumnTitle);

		pDetailsTable->SetColumnWidth(25,0);
		pDetailsTable->SetColumnWidth(95,1);
		pDetailsTable->SetColumnWidth(85,2);
		pDetailsTable->SetColumnWidth(90,3);
		pDetailsTable->SetColumnWidth(90,4);
		pDetailsTable->SetColumnWidth(95,5);
		pDetailsTable->SetColumnWidth(90,6);
		
		SCellLine sCellLine;
		
		for(int i=0; i < csArrayOfRecords[0].GetSize();i++)
		{
			memset(&sCellLine,0,sizeof(SCellLine));
			sCellLine.crBackColor = RGB(234,249,196);
			sCellLine.nCellLineHeight = 28;
			sCellLine.bHasCellLine = true;
			sCellLine.bIsButton = FALSE;
			sCellLine.bIsCheckBox = TRUE;
			wsprintf(sCellLine.szText,"%s",m_csPKID);
			pDetailsTable->AddItem(i,0,&sCellLine);

			memset(&sCellLine,0,sizeof(SCellLine));
			sCellLine.crBackColor = RGB(255,255,255);
			sCellLine.nFontHeight = 12;
			sCellLine.nFontColor = RGB(59,59,59);
			sCellLine.nFontWeight = 1;
			sCellLine.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS; 
			sCellLine.nCellLineHeight = 28;
			sCellLine.bHasCellLine = true;
			wsprintf(sCellLine.szText,"%s",csArrayOfRecords[0].GetAt(i));
			pDetailsTable->AddItem(i,1,&sCellLine);

			memset(&sCellLine,0,sizeof(SCellLine));
			sCellLine.crBackColor = RGB(234,249,196);
			sCellLine.nFontHeight = 12;
			sCellLine.nFontColor = RGB(59,59,59);
			sCellLine.nFontWeight = 0;
			sCellLine.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE;   
			sCellLine.nCellLineHeight = 28;
			sCellLine.bHasCellLine = true;
			wsprintf(sCellLine.szText,"%s",csArrayOfRecords[1].GetAt(i));
			pDetailsTable->AddItem(i,2,&sCellLine);

			memset(&sCellLine,0,sizeof(SCellLine));
			sCellLine.crBackColor = RGB(255,255,255);
			sCellLine.nFontHeight = 12;
			sCellLine.nFontColor = RGB(59,59,59);
			sCellLine.nFontWeight = 0;
			sCellLine.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE;
			sCellLine.nCellLineHeight = 28;
			sCellLine.bHasCellLine = true;
			wsprintf(sCellLine.szText,"%s",csArrayOfRecords[2].GetAt(i));
			pDetailsTable->AddItem(i,3,&sCellLine);

			memset(&sCellLine,0,sizeof(SCellLine));
			sCellLine.crBackColor = RGB(234,249,196);
			sCellLine.nFontHeight = 12;
			sCellLine.nFontColor = RGB(59,59,59);
			sCellLine.nFontWeight = 1;
			sCellLine.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;   
			sCellLine.nCellLineHeight = 28;
			sCellLine.bIsEditable = true;
			sCellLine.bHasCellLine = true;
			wsprintf(sCellLine.szText,"%s",csArrayOfRecords[3].GetAt(i));
			pDetailsTable->AddItem(i,4,&sCellLine);

			memset(&sCellLine,0,sizeof(SCellLine));
			sCellLine.crBackColor = RGB(255,255,255);
			sCellLine.nFontHeight = 12;
			sCellLine.nFontColor = RGB(59,59,59);
			sCellLine.nFontWeight = 0;
			sCellLine.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;   
			sCellLine.nCellLineHeight = 28;
			sCellLine.bIsEditable = true;
			sCellLine.bHasCellLine = true;
			wsprintf(sCellLine.szText,"%s",csArrayOfRecords[4].GetAt(i));
			pDetailsTable->AddItem(i,5,&sCellLine);

			memset(&sCellLine,0,sizeof(SCellLine));
			sCellLine.crBackColor = RGB(234,249,196);
			sCellLine.nFontHeight = 12;
			sCellLine.nFontColor = RGB(59,59,59);
			sCellLine.nFontWeight = 1;
			sCellLine.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;   
			sCellLine.nCellLineHeight = 28;
			sCellLine.bIsEditable = true;
			sCellLine.bHasCellLine = true;
			wsprintf(sCellLine.szText,"%s",csArrayOfRecords[5].GetAt(i));
			pDetailsTable->AddItem(i,6,&sCellLine);
		}
	}
	else if (nTableID == ID_OT_TABLE)
	{
		CStringArray csArrayOfRecords[6];
		CStringArray csArrayOfRecords2;

		COLORREF crTitleBack = RGB(2,138,128);
		COLORREF crTitleText = RGB(10,255,250);

		CString szFields="fk_vCustomerID,fk_vSerialNumber,pk_vGatePassNo,dtDate,nQuantity";
		CString szFields2="nQuantity";
		CString csCondition;
		CString csCondition2;
		csCondition.Format("where fk_vCustomerID = '%s' and fk_vSerialNumber = '%s'",m_csPKID,m_csSerialNumber);
		csCondition2.Format("where fk_vCustomerID = '%s' and pk_vSerialNumber = '%s'",m_csPKID,m_csSerialNumber);
		
		CString csTableName("Transactions_Outward");
		CString csTableName2("Transactions_Inward");

		pdbWrapper->Select(csTableName,csArrayOfRecords,5,(char*)(LPCTSTR)szFields,csCondition);
		pdbWrapper->Select(csTableName2,&csArrayOfRecords2,1,(char*)(LPCTSTR)szFields2,csCondition2);

		int nQuantity = atoi(csArrayOfRecords2.GetAt(0));

		for (int j=0; j<csArrayOfRecords[0].GetSize(); j++)
		{
			int nOutQuantity = atoi(csArrayOfRecords[4].GetAt(j));
			int nBalanceQuantity = nQuantity - nOutQuantity;
			CString csBalance;
			csBalance.Format("%d",nBalanceQuantity);
			csArrayOfRecords[5].Add(csBalance);
			nQuantity = nBalanceQuantity;
		}

		if (csArrayOfRecords[0].GetSize() > 0)
		{
			pDetailsTable->SetDimensions(csArrayOfRecords[0].GetSize() + 1,7);
		}
		else
		{
			pDetailsTable->SetDimensions(1,7);
		}
		
		SColumnTitle sColumnTitle;

		strcpy(sColumnTitle.szText,"");
		sColumnTitle.nFontColor=crTitleText;
		sColumnTitle.crBackColor=crTitleBack;
		sColumnTitle.nHeight=35;
		pDetailsTable->AddColumnTitle(&sColumnTitle);

		strcpy(sColumnTitle.szText,"Customer\nID");
		sColumnTitle.nFontColor=crTitleText;
		sColumnTitle.crBackColor=crTitleBack;
		sColumnTitle.nHeight=35;
		pDetailsTable->AddColumnTitle(&sColumnTitle);

		strcpy(sColumnTitle.szText,"Serial\nNumber");
		sColumnTitle.nFontColor=crTitleText;
		sColumnTitle.crBackColor=crTitleBack;
		pDetailsTable->AddColumnTitle(&sColumnTitle);

		strcpy(sColumnTitle.szText,"Gate Pass\nNumber");
		sColumnTitle.nFontColor=crTitleText;
		sColumnTitle.crBackColor=crTitleBack;
		pDetailsTable->AddColumnTitle(&sColumnTitle);

		strcpy(sColumnTitle.szText,"Date");
		sColumnTitle.nFontColor=crTitleText;
		sColumnTitle.crBackColor=crTitleBack;
		pDetailsTable->AddColumnTitle(&sColumnTitle);

		strcpy(sColumnTitle.szText,"Quantity");
		sColumnTitle.nFontColor=crTitleText;
		sColumnTitle.crBackColor=crTitleBack;
		pDetailsTable->AddColumnTitle(&sColumnTitle);

		strcpy(sColumnTitle.szText,"Balance\nQuantity");
		sColumnTitle.nFontColor=crTitleText;
		sColumnTitle.crBackColor=crTitleBack;
		pDetailsTable->AddColumnTitle(&sColumnTitle);

		pDetailsTable->SetColumnWidth(25,0);
		pDetailsTable->SetColumnWidth(95,1);
		pDetailsTable->SetColumnWidth(95,2);
		pDetailsTable->SetColumnWidth(95,3);
		pDetailsTable->SetColumnWidth(85,4);
		pDetailsTable->SetColumnWidth(90,5);
		pDetailsTable->SetColumnWidth(90,6);
		
		SCellLine sCellLine;
		
		for(int i=0; i < csArrayOfRecords[0].GetSize();i++)
		{
			memset(&sCellLine,0,sizeof(SCellLine));
			sCellLine.crBackColor = RGB(218,251,250);
			sCellLine.nCellLineHeight = 28;
			sCellLine.bHasCellLine = true;
			sCellLine.bIsButton = FALSE;
			sCellLine.bIsCheckBox = TRUE;
			wsprintf(sCellLine.szText,"%s",csArrayOfRecords[1].GetAt(i));
			pDetailsTable->AddItem(i,0,&sCellLine);

			memset(&sCellLine,0,sizeof(SCellLine));
			sCellLine.crBackColor = RGB(255,255,255);
			sCellLine.nFontHeight = 12;
			sCellLine.nFontColor = RGB(59,59,59);
			sCellLine.nFontWeight = 0;
			sCellLine.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS; 
			sCellLine.nCellLineHeight = 28;
			sCellLine.bHasCellLine = true;
			wsprintf(sCellLine.szText,"%s",csArrayOfRecords[0].GetAt(i));
			pDetailsTable->AddItem(i,1,&sCellLine);

			memset(&sCellLine,0,sizeof(SCellLine));
			sCellLine.crBackColor = RGB(218,251,250);
			sCellLine.nFontHeight = 12;
			sCellLine.nFontColor = RGB(59,59,59);
			sCellLine.nFontWeight = 1;
			sCellLine.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE;   
			sCellLine.nCellLineHeight = 28;
			sCellLine.bHasCellLine = true;
			wsprintf(sCellLine.szText,"%s",csArrayOfRecords[1].GetAt(i));
			pDetailsTable->AddItem(i,2,&sCellLine);

			memset(&sCellLine,0,sizeof(SCellLine));
			sCellLine.crBackColor = RGB(255,255,255);
			sCellLine.nFontHeight = 12;
			sCellLine.nFontColor = RGB(59,59,59);
			sCellLine.nFontWeight = 1;
			sCellLine.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE;
			sCellLine.nCellLineHeight = 28;
			sCellLine.bHasCellLine = true;
			wsprintf(sCellLine.szText,"%s",csArrayOfRecords[2].GetAt(i));
			pDetailsTable->AddItem(i,3,&sCellLine);

			memset(&sCellLine,0,sizeof(SCellLine));
			sCellLine.crBackColor = RGB(218,251,250);
			sCellLine.nFontHeight = 12;
			sCellLine.nFontColor = RGB(59,59,59);
			sCellLine.nFontWeight = 0;
			sCellLine.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;   
			sCellLine.nCellLineHeight = 28;
			sCellLine.bIsEditable = true;
			sCellLine.bHasCellLine = true;
			wsprintf(sCellLine.szText,"%s",csArrayOfRecords[3].GetAt(i));
			pDetailsTable->AddItem(i,4,&sCellLine);

			memset(&sCellLine,0,sizeof(SCellLine));
			sCellLine.crBackColor = RGB(255,255,255);
			sCellLine.nFontHeight = 12;
			sCellLine.nFontColor = RGB(59,59,59);
			sCellLine.nFontWeight = 1;
			sCellLine.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;   
			sCellLine.nCellLineHeight = 28;
			sCellLine.bIsEditable = true;
			sCellLine.bHasCellLine = true;
			wsprintf(sCellLine.szText,"%s",csArrayOfRecords[4].GetAt(i));
			pDetailsTable->AddItem(i,5,&sCellLine);

			memset(&sCellLine,0,sizeof(SCellLine));
			sCellLine.crBackColor = RGB(218,251,250);
			sCellLine.nFontHeight = 12;
			sCellLine.nFontColor = RGB(59,59,59);
			sCellLine.nFontWeight = 1;
			sCellLine.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;   
			sCellLine.nCellLineHeight = 28;
			sCellLine.bIsEditable = true;
			sCellLine.bHasCellLine = true;
			wsprintf(sCellLine.szText,"%s",csArrayOfRecords[5].GetAt(i));
			pDetailsTable->AddItem(i,6,&sCellLine);
		}
	}
}

BOOL CTableContainer::DisplayDetailsTable(UINT nTableID)
{
	if(m_nSelectedRow == -1)
	{
		MessageBoxEng(this->GetParent(),MB_MSG_USERDEFINED_ERROR,MB_OK_BUTTON,"Report Selection Error","Please select one of the entries to proceed");
		return FALSE;
	}
	if(nTableID == ID_IT_TABLE)
	{
		if(m_pMainTablePage->IsWindowVisible())
		{
			m_pMainTablePage->ShowWindow(SW_HIDE);
		}

		m_pITTablePage = new CTablePage; 
		m_pITTablePage->InitializeTablePage(CRect(25,10,606,20000),this,5002/*ID_TABLEPAGE*/);
		m_pITTablePage->SetPageMargins(0,0,0,0);
		m_pITTablePage->SetPageBackColor(BLACK/*RGB(255,255,255)*/);

		m_pITTableData = new CTableData(ID_IT_TABLE);
		TCHAR szTableTitle[32] = "Inward Transactions";
		m_pITTableData->SetTableTitle(szTableTitle);
		m_pITTableData->SetTitleColor(RGB(0,146,159));
		m_pITTableData->SetColumnTitleLineColor(RGB(2,138,128));
		m_pITTableData->SetRowLineColor(RGB(2,138,128));
		m_pITTableData->SetColumnTitleVLineColor(RGB(218,251,250));
		m_pITTableData->SetRowVLineColor(RGB(2,138,128));

		PopulateDetailsTable(m_pITTableData,ID_IT_TABLE,m_nSelectedRow);

		CObList obListOfTables;
		obListOfTables.AddTail((CObject*)m_pITTableData);

		m_pITTablePage->CreateCheckBoxes(&obListOfTables);
		m_pITTablePage->DrawPage(&obListOfTables);
		ShowVerticalScroll(m_pITTablePage->GetHeight());
		m_pITTablePage->ShowWindow(SW_NORMAL);
		
		m_csPageTitle = m_csCompanyName;
		m_nSelectedRow = -1;
	}
	else if(nTableID == ID_OT_TABLE)
	{
		if(m_pMainTablePage->IsWindowVisible())
		{
			m_pMainTablePage->ShowWindow(SW_HIDE);
		}
		else if(m_pITTablePage && m_pITTablePage->IsWindowVisible())
		{
			m_pITTablePage->DestroyCheckBoxes();
			delete m_pITTablePage;
			m_pITTablePage = 0;
			if(m_pITTableData)
			{
				delete m_pITTableData;
				m_pITTableData = 0;
			}
		}

		m_pOTTableData = new CTableData(ID_OT_TABLE);
		TCHAR szTableTitle[32] = "Outward Transactions";
		m_pOTTableData->SetTableTitle(szTableTitle);
		m_pOTTableData->SetTitleColor(RGB(0,146,159));
		m_pOTTableData->SetColumnTitleLineColor(RGB(88,122,0));
		m_pOTTableData->SetRowLineColor(RGB(88,122,0));
		m_pOTTableData->SetColumnTitleVLineColor(RGB(234,249,196));
		m_pOTTableData->SetRowVLineColor(RGB(88,122,0));

		m_pOTTablePage = new CTablePage; 
		m_pOTTablePage->InitializeTablePage(CRect(25,10,606,20000),this,5002/*ID_TABLEPAGE*/);
		m_pOTTablePage->SetPageMargins(0,0,0,0);
		m_pOTTablePage->SetPageBackColor(BLACK/*RGB(255,255,255)*/);
		PopulateDetailsTable(m_pOTTableData,ID_OT_TABLE,m_nSelectedRow);

		CObList obListOfTables;
		obListOfTables.AddTail((CObject*)m_pOTTableData);

		m_pOTTablePage->CreateCheckBoxes(&obListOfTables);
		m_pOTTablePage->DrawPage(&obListOfTables);

		ShowVerticalScroll(m_pOTTablePage->GetHeight());
		m_pOTTablePage->ShowWindow(SW_NORMAL);
		m_nSelectedRow = -1;
	}
	return TRUE;
}

void CTableContainer::DisplayMainTable()
{
	if(m_pITTablePage && m_pITTablePage->IsWindowVisible())
	{
		m_pITTablePage->ShowWindow(SW_HIDE);
		delete m_pITTablePage;
		m_pITTablePage = 0;
		if(m_pITTableData)
		{
			delete m_pITTableData;
			m_pITTableData = 0;
		}
	}
	if(m_pOTTablePage && m_pOTTablePage->IsWindowVisible())
	{
		m_pOTTablePage->ShowWindow(SW_HIDE);
		delete m_pOTTablePage;
		m_pOTTablePage = 0;
		if(m_pOTTableData)
		{
			delete m_pOTTableData;
			m_pOTTableData = 0;
		}
	}
	if(!m_pMainTablePage->IsWindowVisible())
	{
		m_pMainTablePage->ResetCheckBoxes(&m_obListOfTables);
		m_pMainTablePage->ShowWindow(SW_NORMAL);
	}
	Invalidate(TRUE);
}

void CTableContainer::DeleteEntry(UINT nTableID)
{
	int nRetCode;
	if(m_nSelectedRow == -1)
	{
		MessageBoxEng(this->GetParent(),MB_MSG_USERDEFINED_ERROR,MB_OK_BUTTON,"Report Selection Error","Please select one of the entries to proceed");
	}
	else
	{
		nRetCode = MessageBoxEng(this->GetParent(),MB_MSG_USERDEFINED_CONFIRMATION,MB_YESNO_BUTTON,"Report Deletion Confirmation","Are you sure you want to delete the selected entries?");
		if(nRetCode == ID_MB_YES_BUTTON)
		{
			switch(nTableID)
			{
			case ID_CI_TABLE:
				{
					CTableData* pTableData = (CTableData*)m_obListOfTables.GetHead();
					CString csData = pTableData->GetItem(m_nSelectedRow,2,0).szText;
					pTableData->RemoveItem(m_nSelectedRow);
					m_pMainTablePage->ResetCheckBoxes(&m_obListOfTables);
					m_pMainTablePage->DrawPage(&m_obListOfTables);
					CCustomDB *pdbWrapper = ((CPukamSoftApp*)AfxGetApp())->GetConnectionObject();
					CString csCondition;
					csCondition.Format("where pk_vCustomerID = '%s'",csData);
					CString csTableName("Customer_Info");
					pdbWrapper->Delete(csTableName,csCondition);
					break;
				}
			case ID_IT_TABLE:
				break;
			case ID_OT_TABLE:
				break;
			}
		}
	}
}