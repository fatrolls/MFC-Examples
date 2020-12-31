// VirtualListView.cpp : implementation of the CVirtualListView class
//

#include "stdafx.h"
#include "VirtualList.h"

#include "VirtualListDoc.h"
#include "VirtualListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVirtualListView

IMPLEMENT_DYNCREATE(CVirtualListView, CListView)

BEGIN_MESSAGE_MAP(CVirtualListView, CListView)
	//{{AFX_MSG_MAP(CVirtualListView)
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetDispInfo)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVirtualListView construction/destruction

CVirtualListView::CVirtualListView()
{
	// TODO: add construction code here

}

CVirtualListView::~CVirtualListView()
{
}

BOOL CVirtualListView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.lpszName = WC_LISTVIEW;
	cs.style &= ~LVS_TYPEMASK;
	cs.style |= LVS_REPORT;
	cs.style |= LVS_OWNERDATA;
	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CVirtualListView drawing

void CVirtualListView::OnDraw(CDC* pDC)
{
	CVirtualListDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

void CVirtualListView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
	/*set number of items in list to number of items in RecordSet*/	
	/* create image list*/
	CDaoRecordset* pRecordSet = GetRecordSet();
	if(pRecordSet != NULL)
	{
		m_pImageList = new CImageList();
		m_pImageList->Create(IDB_IMAGELIST, 16, 1, RGB(0,0,0));
		GetListCtrl().SetImageList(m_pImageList, LVSIL_SMALL);	/* set extended stlyes*/
		
		DWORD dwExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | /*LVS_EX_SUBITEMIMAGES |*/
							LVS_EX_HEADERDRAGDROP | LVS_EX_TRACKSELECT;
		GetListCtrl().SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LPARAM(dwExStyle));	
		
		LV_COLUMN lvColumn;
		lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvColumn.fmt = LVCFMT_LEFT;	lvColumn.cx = 120;
		for(int i = 0; i < pRecordSet->GetFieldCount(); i++) // set up columns
		{
			CDaoFieldInfo m_fieldinfo;
			pRecordSet->GetFieldInfo(i, m_fieldinfo);//get field name
			int len = m_fieldinfo.m_strName.GetLength();
			CString temp = m_fieldinfo.m_strName;
			TCHAR* szBuffer = new TCHAR[len + 1];
			strcpy(szBuffer, temp.GetBuffer(len));
			temp.ReleaseBuffer();
			lvColumn.pszText = szBuffer;
			GetListCtrl().InsertColumn(i, &lvColumn);//insert column		
			delete szBuffer;
		}
		/*set number of items in ListView*/
		long count = GetRecordCount();//Get number of records
		GetListCtrl().SendMessage(LVM_SETITEMCOUNT, (WPARAM)count, (LPARAM)LVSICF_NOINVALIDATEALL);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CVirtualListView printing

BOOL CVirtualListView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVirtualListView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVirtualListView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CVirtualListView diagnostics

#ifdef _DEBUG
void CVirtualListView::AssertValid() const
{
	CListView::AssertValid();
}

void CVirtualListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CVirtualListDoc* CVirtualListView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVirtualListDoc)));
	return (CVirtualListDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVirtualListView message handlers

void CVirtualListView::OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	TCHAR szValue[MAX_PATH];
	szValue[0] = '\0';
	CDaoRecordset* pRecordSet = GetRecordSet();
	if(!pRecordSet)
		return;

	COleVariant varValue;
	long index = pDispInfo->item.iItem;
	long subItem = 	pDispInfo->item.iSubItem;


	if(pDispInfo->item.mask & LVIF_TEXT)
	{
		try
		{
			pRecordSet->SetAbsolutePosition(index);//Set the file to desired index
		}
		catch(CDaoException* e)
		{
			AfxMessageBox(e->m_pErrorInfo->m_strDescription, 
				    MB_ICONEXCLAMATION );
			e->Delete();
			return;
		}
		
		try
		{
			if(subItem)	
				pRecordSet->GetFieldValue(subItem, varValue);
			else
				pRecordSet->GetFieldValue(0, varValue);
		}
		catch(CDaoException* e)
		{
			AfxMessageBox(e->m_pErrorInfo->m_strDescription, 
				    MB_ICONEXCLAMATION );
			e->Delete();
			return;
		}

		const VARIANT* variant = LPCVARIANT(varValue);
		
		if(variant->vt & VT_BYREF)
			return;
		
		switch(variant->vt)
		{
			case VT_ERROR:{	
							strcpy(szValue, "Error");					
							break;
						  }
			case VT_I2:{	wsprintf(szValue, "%d", variant->iVal);
							break;
					   }
			case VT_I4:{	wsprintf(szValue, "%d", variant->lVal);
							break;
					   }
			case VT_R4:{	wsprintf(szValue, "%f", variant->fltVal);
							break;
					   }	
			case VT_R8:{	wsprintf(szValue, "%f", variant->dblVal);
							break;
					   }
			case VT_CY:{	COleCurrency c(varValue);
							CString s = c.Format();//ie. 1.00
							strcpy(szValue, s.GetBuffer(s.GetLength()));
							s.ReleaseBuffer();
							break;
					   }
			case VT_DATE:{	COleDateTime t(variant->date);
							CString s = t.Format( "%B %d, %Y" );//Day of Week, Month Day, Year
							strcpy(szValue, s.GetBuffer(s.GetLength()));
							s.ReleaseBuffer();
							break;
						 }
			case VT_BSTR:{  CString str = V_BSTRT( &varValue );//convert BSTR to CString
							strcpy(szValue, str.GetBuffer(str.GetLength()));
							str.ReleaseBuffer();
							break;
						}
			case VT_BOOL:{	if(variant->boolVal)
								strcpy(szValue, "TRUE");
							else
								strcpy(szValue, "FALSE");
							break;
						 }
			case VT_UI1:{	strcpy(szValue, (char*)variant->bVal);
							break;
						}

				default:{
							szValue[0] = '\0';
							break;
						}

		}
		lstrcpyn(pDispInfo->item.pszText, szValue, pDispInfo->item.cchTextMax);//set item text
	}
	
	if(pDispInfo->item.mask & LVIF_IMAGE)
		pDispInfo->item.iImage = 0;//set image to first in list

	*pResult = 0;
} 


CDaoRecordset* CVirtualListView::GetRecordSet()
{
	return GetDocument()->GetRecordSet();
}

long CVirtualListView::GetRecordCount()
{
	CDaoRecordset* pRecordset = GetRecordSet();
	if(pRecordset)
		return pRecordset->GetRecordCount();

	return 0;
}


