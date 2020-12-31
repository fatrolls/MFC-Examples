// ServicesDialog.cpp : implementation file
//

#include "stdafx.h"
#include "systemstateinfo.h"
#include "ServicesDialog.h"

#include "OXIteratorService.h"

#include "UTBStrOp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define SERVICEREF_FLAG				0x22663344

/////////////////////////////////////////////////////////////////////////////
// CServicesDialog dialog


CServicesDialog::CServicesDialog() : CPageDialog()
{
	//{{AFX_DATA_INIT(CServicesDialog)
	m_nExpandLevel = 0;
	m_nExpandType = 1;
	//}}AFX_DATA_INIT
	
	BOOL bIsWindowsNT=FALSE;
	m_SysInfo.IsNT(&bIsWindowsNT);

	if(!bIsWindowsNT)
		AfxThrowNotSupportedException();
}


void CServicesDialog::DoDataExchange(CDataExchange* pDX)
{
	CPageDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServicesDialog)
	DDX_Control(pDX, IDC_SPIN_EXPANDLEVEL, m_spinExpandLevel);
	DDX_Control(pDX, IDC_EDIT_EXPANDLEVEL, m_editExpandLevel);
	DDX_Control(pDX, IDC_TREE_SERVICES, m_tree);
	DDX_Text(pDX, IDC_EDIT_EXPANDLEVEL, m_nExpandLevel);
	DDX_Radio(pDX, IDC_RADIO_EXPANDLEVEL, m_nExpandType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CServicesDialog, CPageDialog)
	//{{AFX_MSG_MAP(CServicesDialog)
	ON_BN_CLICKED(IDC_RADIO_EXPANDALL, OnRadioExpandall)
	ON_BN_CLICKED(IDC_RADIO_EXPANDLEVEL, OnRadioExpandlevel)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_SERVICES, OnDblclkTreeServices)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServicesDialog message handlers

void CServicesDialog::OnInitDialog() 
{
	CPageDialog::OnInitDialog();

	// TODO: Add your specialized creation code here

	m_ilTree.Create(IDB_SERVICES_TREE_IMAGE,16,1,RGB(255,0,255));
	m_tree.SetImageList(&m_ilTree,TVSIL_NORMAL);

	LV_COLUMN lvc={ sizeof(lvc) };
	lvc.fmt=LVCFMT_LEFT;
	lvc.cx=237;
	lvc.pszText=_T("Item");
	lvc.mask = LVCF_FMT|LVCF_WIDTH|LVCF_TEXT;
	m_tree.SetColumn(0,&lvc);
	m_tree.InsertColumn(1,_T("Value"),LVCFMT_LEFT,200,1);

	// set COXTreeCtrl styles
	m_tree.ModifyExStyle(0,TVOXS_PICKANYWHERE|TVOXS_ROWSEL);
	m_tree.ModifyStyle(0,TVS_SHOWSELALWAYS|TVS_HASBUTTONS|
		TVS_HASLINES|TVS_LINESATROOT);


	// spin control
	m_spinExpandLevel.SetRange(0,3);
	m_spinExpandLevel.SetPos(0);
	
	// layout manager 
	//
	m_LayoutManager.Attach(this);
	
	// tree control
	m_LayoutManager.TieChild(IDC_TREE_SERVICES,OX_LMS_ANY,OX_LMT_SAME);
	//////////////////

	// radio buttons and expand level edit control
	m_LayoutManager.TieChild(IDC_RADIO_EXPANDALL,
		OX_LMS_LEFT|OX_LMS_BOTTOM,OX_LMT_SAME);

	m_LayoutManager.TieChild(IDC_RADIO_EXPANDLEVEL,
		OX_LMS_LEFT|OX_LMS_BOTTOM,OX_LMT_SAME);

	m_LayoutManager.TieChild(IDC_EDIT_EXPANDLEVEL,OX_LMS_LEFT,
		OX_LMT_OPPOSITE,IDC_RADIO_EXPANDLEVEL);
	m_LayoutManager.TieChild(IDC_EDIT_EXPANDLEVEL,OX_LMS_BOTTOM,OX_LMT_SAME);

	m_LayoutManager.TieChild(IDC_SPIN_EXPANDLEVEL,OX_LMS_LEFT,
		OX_LMT_OPPOSITE,IDC_EDIT_EXPANDLEVEL);
	m_LayoutManager.TieChild(IDC_SPIN_EXPANDLEVEL,OX_LMS_BOTTOM,OX_LMT_SAME);
	//////////////////

	//////////////////////////////////////

	PopulateTree();

	ShowControls();
}

void CServicesDialog::Refresh() 
{
	PopulateTree();
}

void CServicesDialog::PopulateTree()
{
	if(!UpdateData())
		return;

	CWaitCursor waitCursor;

	m_tree.SetRedraw(FALSE);
	m_tree.DeleteAllItems();
	COXTreeHeader* pHeader=(COXTreeHeader*)m_tree.GetDlgItem(0);
	ASSERT(pHeader);
	pHeader->SortColumn(-1,0);

	// create fonts to customize tree items appearance
	LOGFONT lf;
	CFont fontRoot;
	CFont fontSubRoot;
	CFont* pFontRoot=GetFont();
	if(pFontRoot->GetLogFont(&lf))
	{
		lf.lfHeight=-14;
		UTBStr::tcsncpy(lf.lfFaceName,LF_FACESIZE,_T("Arial"),LF_FACESIZE);
		fontRoot.CreateFontIndirect(&lf);

		lf.lfHeight=-12;
		lf.lfWeight=FW_BOLD;
		UTBStr::tcsncpy(lf.lfFaceName,LF_FACESIZE,_T("Times New Roman"),LF_FACESIZE);
		fontSubRoot.CreateFontIndirect(&lf);
	}
	pFontRoot=((HFONT)fontRoot!=NULL) ? &fontRoot : NULL;
	CFont* pFontSubRoot=((HFONT)fontSubRoot!=NULL) ? &fontSubRoot : NULL;

	HTREEITEM htiRoot=NULL;
	HTREEITEM htiSelectItem=NULL;

	COLORREF clrTopic=RGB(0,0,255);


	COXIteratorService iterServices;

	// iterate through all services
	//

	CStringArray arrAllServiceName;
	CStringArray arrServiceName;
	CStringArray arrDeviceName;

	VERIFY(iterServices.StartIteration());
	iterServices.GetKeyNames(arrAllServiceName);
	int nIndex=0;
	for(nIndex=0; nIndex<arrAllServiceName.GetSize(); nIndex++)
	{
		COXService service(arrAllServiceName[nIndex]);
		if((service.QueryServiceType()&SERVICE_KERNEL_DRIVER)==
			SERVICE_KERNEL_DRIVER || 
			(service.QueryServiceType()&SERVICE_FILE_SYSTEM_DRIVER)==
			SERVICE_FILE_SYSTEM_DRIVER)
			arrDeviceName.Add(arrAllServiceName[nIndex]);
		else
			arrServiceName.Add(arrAllServiceName[nIndex]);
	}


	// display services and info about them
	if(arrServiceName.GetSize()>0)
	{
		htiRoot=InsertItem(_T("Services"),NULL,0,pFontRoot,clrTopic);
		htiSelectItem=htiRoot;
	}

	for(nIndex=0; nIndex<arrServiceName.GetSize(); nIndex++)
		InsertServiceInfo(arrServiceName[nIndex],htiRoot,pFontSubRoot,FALSE);
	///////////////////////////////////////////////////////


	// display devices and info about them
	if(arrDeviceName.GetSize()>0)
	{
		htiRoot=InsertItem(_T("Devices"),NULL,1,pFontRoot,clrTopic);
		if(htiSelectItem==NULL)
			htiSelectItem=htiRoot;
	}

	for(nIndex=0; nIndex<arrDeviceName.GetSize(); nIndex++)
		InsertServiceInfo(arrDeviceName[nIndex],htiRoot,pFontSubRoot,TRUE);
	///////////////////////////////////////////////////////

	//
	///////////////////////////////////////////////////////


	ExpandTree((m_nExpandType==0 ? m_nExpandLevel : -1));

	m_tree.SetFocus();
	m_tree.SelectItem(htiSelectItem);

	m_tree.SetRedraw(TRUE);
}


void CServicesDialog::ExpandTree(int nExpandLevel/*=-1*/,
								HTREEITEM htiParent/*=NULL*/)
{
	if(nExpandLevel==0)
		return;

	if(htiParent==NULL)
	{
		htiParent=m_tree.GetRootItem();
		ASSERT(htiParent!=NULL);
	}

	HTREEITEM hti=m_tree.GetNextItem(htiParent,TVGN_CHILD);
	while(hti!=NULL)
	{
		m_tree.Expand(hti,TVE_EXPAND);

		COXTreeItem* xti=m_tree.GetXItem(hti);
		ASSERT(xti!=NULL);
		if(xti->ItemHasChildren())
			ExpandTree((nExpandLevel==-1 ? -1 : nExpandLevel-1),hti);

		hti=m_tree.GetNextItem(hti,TVGN_NEXT);
	}
}

HTREEITEM CServicesDialog::InsertItem(CString sItem, HTREEITEM htiParent/*=NULL*/, 
									 int nImage/*=-1*/, CFont* pFont/*=NULL*/, 
									 COLORREF clr/*=CLR_NONE*/)
{
	HTREEITEM hti=m_tree.InsertItem(sItem,htiParent);
	ASSERT(hti!=NULL);

	// associate new font
	if(pFont!=NULL)
		VERIFY(m_tree.SetItemFont(hti,pFont));
	// and new color
	if(clr!=CLR_NONE)
		VERIFY(m_tree.SetItemColor(hti,clr));

	m_tree.SetItemImage(hti,nImage,nImage);

	return hti;
}

void CServicesDialog::InsertServiceInfo(CString sServiceKeyName,
										HTREEITEM htiRoot,
										CFont* pFont,
										BOOL bDevice)
{
	CString sValue;
	DWORD dwValue;
	HTREEITEM htiSubRoot;
	HTREEITEM htiItem;

//	COLORREF clrTopic=RGB(0,0,255);
	COLORREF clrValue=RGB(0,128,0);

	COXService service(sServiceKeyName);
	SERVICE_STATUS ss;

	// Display name and status
	htiSubRoot=InsertItem(service.QueryDisplayName(),htiRoot,-1,pFont);

	service.QueryStatus(&ss,TRUE);
	switch(ss.dwCurrentState)
	{
	case SERVICE_STOPPED:
		sValue=_T("Stopped"); 
		break;
	case SERVICE_START_PENDING:
		sValue=_T("Start pending"); 
		break;
	case SERVICE_STOP_PENDING:
		sValue=_T("Stop pending"); 
		break;
	case SERVICE_RUNNING:
		sValue=_T("Running"); 
		break;
	case SERVICE_CONTINUE_PENDING:
		sValue=_T("Continue pending"); 
		break;
	case SERVICE_PAUSE_PENDING:
		sValue=_T("Pause pending"); 
		break;
	case SERVICE_PAUSED:
		sValue=_T("Paused"); 
		break;
	default:
		if(ss.dwWin32ExitCode==NO_ERROR)
			sValue=_T("Status:<unknown>");
		else
			sValue=_T("Stopped"); 
	}
	VERIFY(m_tree.SetSubItem(htiSubRoot,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
		sValue,0,NULL,clrValue));
	/////////////////////////////////////////////

	// Binary Path Name
	CString sWindowsDirTag=_T("\\SystemRoot");
	CString sWindowsDir;
	if(!m_SysInfo.GetWindowsDir(&sWindowsDir))
		sWindowsDir.Empty();
	sValue=service.QueryBinaryPathName();
	if(sValue.IsEmpty())
		sValue=_T("<unavailable>");
	if(!sWindowsDir.IsEmpty() && sValue.Find(sWindowsDirTag)==0)
		sValue=sWindowsDir+sValue.Mid(sWindowsDirTag.GetLength());
	htiItem=InsertItem(_T("Pathname"),htiSubRoot);
	VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
		sValue,0,NULL,clrValue));
	VERIFY(m_tree.SetItemDrawEllipsis(htiItem,DT_PATH_ELLIPSIS,1));
	/////////////////////////////////////////////

	// Service Type
	sValue.Empty();
	htiItem=InsertItem(_T("Service Type"),htiSubRoot);
	if((ss.dwServiceType&SERVICE_WIN32_OWN_PROCESS)==
		SERVICE_WIN32_OWN_PROCESS)
	{
		ASSERT(!bDevice);
		sValue=_T("Runs in its own process"); 
	}
	else if((ss.dwServiceType&SERVICE_WIN32_SHARE_PROCESS)==
		SERVICE_WIN32_SHARE_PROCESS)
	{
		ASSERT(!bDevice);
		sValue=_T("Shares a process with other processes"); 
	}
	else if((ss.dwServiceType&SERVICE_KERNEL_DRIVER)==
		SERVICE_KERNEL_DRIVER)
	{
		ASSERT(bDevice);
		sValue=_T("Kernel device driver"); 
	}
	else if((ss.dwServiceType&SERVICE_FILE_SYSTEM_DRIVER)==
		SERVICE_FILE_SYSTEM_DRIVER)
	{
		ASSERT(bDevice);
		sValue=_T("File system driver"); 
	}
	if((ss.dwServiceType&SERVICE_INTERACTIVE_PROCESS)==
		SERVICE_INTERACTIVE_PROCESS)
	{
		ASSERT(!bDevice);
		ASSERT(!sValue.IsEmpty());
		sValue=sValue+_T(" and can iteract with the desktop");
	}
	VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
		sValue,0,NULL,clrValue));
	/////////////////////////////////////////////

	// Start Type
	dwValue=service.QueryStartType();
	htiItem=InsertItem(_T("Start Type"),htiSubRoot);
	switch(dwValue)
	{
	case SERVICE_BOOT_START:
		ASSERT(bDevice);
		sValue=_T("Boot");
		break;
	case SERVICE_SYSTEM_START: 
		ASSERT(bDevice);
		sValue=_T("System");
		break;
	case SERVICE_AUTO_START: 
		sValue=_T("Automatic");
		break;
	case SERVICE_DEMAND_START:
		sValue=_T("Manual");
		break;
	case SERVICE_DISABLED:
		sValue=_T("Disabled");
		break;
	default:
		sValue=_T("<unknown>");
	}
	VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
		sValue,0,NULL,clrValue));
	/////////////////////////////////////////////

	// Error Severity
	dwValue=service.QueryErrorControl();
	htiItem=InsertItem(_T("Error Severity"),htiSubRoot);
	switch(dwValue)
	{
	case SERVICE_ERROR_IGNORE:
		sValue=_T("Ignore");
		break;
	case SERVICE_ERROR_NORMAL: 
		sValue=_T("Normal");
		break;
	case SERVICE_ERROR_SEVERE: 
		sValue=_T("Severe");
		break;
	case SERVICE_ERROR_CRITICAL: 
		sValue=_T("Critical");
		break;
	default:
		sValue=_T("<unknown>");
	}
	VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
		sValue,0,NULL,clrValue));
	/////////////////////////////////////////////

	// Load Order Group
	sValue=service.QueryLoadOrderGroup();
	if(!sValue.IsEmpty())
	{
		htiItem=InsertItem(_T("Group"),htiSubRoot);
		VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
			sValue,0,NULL,clrValue));
	}
	/////////////////////////////////////////////

	// 
	sValue=service.QueryStartName();
	if(!bDevice)
	// Service Account Name
	{
		if(sValue.IsEmpty())
			sValue=_T("LocalSystem");
		htiItem=InsertItem(_T("Service Account Name"),htiSubRoot);
		VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
			sValue,0,NULL,clrValue));
	}
	else
	// Driver Object Name 
	{
		if(!sValue.IsEmpty())
		{
			htiItem=InsertItem(_T("Driver Object Name"),htiSubRoot);
			VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
				sValue,0,NULL,clrValue));
		}
	}
	/////////////////////////////////////////////

	// Dependencies
	CString sDependencies=service.QueryDependencies();
	if(!sDependencies.IsEmpty())
	{
		htiItem=InsertItem(_T("Dependencies"),htiSubRoot,-1,pFont);
		int nPos;
		while((nPos=sDependencies.Find(_T("|")))!=-1)
		{
			ASSERT(nPos>1);
			CString sName=sDependencies.Left(nPos);
			if(sName.Left(1)==SC_GROUP_IDENTIFIER)
				sName=sName.Mid(1)+_T(" (Group)");
			InsertItem(sName,htiItem);
			sDependencies=sDependencies.Mid(nPos+1);
		}
		if(sDependencies.Left(1)==SC_GROUP_IDENTIFIER)
			sDependencies=sDependencies.Mid(1)+_T(" (Group)");
		InsertItem(sDependencies,htiItem);
	}
	/////////////////////////////////////////////

	// Dependents
	COXIteratorService iterServices(service);
	if(iterServices.StartDependentIteration())
	{
		CStringArray arrAllServiceName;
		iterServices.GetKeyNames(arrAllServiceName);
		HTREEITEM htiItem=NULL;
		if(arrAllServiceName.GetSize()>0)
			htiItem=InsertItem(_T("Dependents"),htiSubRoot,-1,pFont);
		for(int nIndex=0; nIndex<arrAllServiceName.GetSize(); nIndex++)
		{
			COXService service(arrAllServiceName[nIndex]);
			HTREEITEM hti=InsertItem(service.QueryDisplayName(),htiItem);
			if((service.QueryServiceType()&SERVICE_KERNEL_DRIVER)==
				SERVICE_KERNEL_DRIVER || 
				(service.QueryServiceType()&SERVICE_FILE_SYSTEM_DRIVER)==
				SERVICE_FILE_SYSTEM_DRIVER)
			{
				VERIFY(m_tree.SetSubItem(hti,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
					_T("Device"),0,NULL,clrValue));
			}
			else
			{
				VERIFY(m_tree.SetSubItem(hti,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
					_T("Service"),0,NULL,clrValue));
			}
			m_tree.SetItemData(hti,SERVICEREF_FLAG);
		}
	}
	/////////////////////////////////////////////

}

void CServicesDialog::ShowControls()
{
	if(UpdateData())
	{
		CWnd* pDlgItem=GetDlgItem(IDC_EDIT_EXPANDLEVEL);
		ASSERT(pDlgItem!=NULL);
		pDlgItem->EnableWindow((m_nExpandType==0));
		pDlgItem=GetDlgItem(IDC_SPIN_EXPANDLEVEL);
		ASSERT(pDlgItem!=NULL);
		pDlgItem->EnableWindow((m_nExpandType==0));
	}
}

void CServicesDialog::OnRadioExpandall() 
{
	// TODO: Add your control notification handler code here
	
	ShowControls();
}

void CServicesDialog::OnRadioExpandlevel() 
{
	// TODO: Add your control notification handler code here
	
	ShowControls();
}

void CServicesDialog::OnDblclkTreeServices(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UNREFERENCED_PARAMETER(pNMHDR);

	CPoint point;
	if(::GetCursorPos(&point))
	{
		m_tree.ScreenToClient(&point);
		UINT nFlags;
		int nItem=m_tree.HitTest(point,&nFlags);
		if(nItem!=-1)
		{
			HTREEITEM hti=m_tree.GetItemFromIndex(nItem);
			ASSERT(hti!=NULL);
			if(m_tree.GetItemIndent(hti)<point.x && 
				m_tree.GetItemData(hti)==SERVICEREF_FLAG && 
				(nFlags&TVHT_ONITEM)==TVHT_ONITEM)
			{
				CString sItemText=m_tree.GetItemText(hti);
				for(int nIndex=0; nIndex<(int)m_tree.GetVisibleCount(); nIndex++)
				{
					HTREEITEM htiFound=m_tree.GetItemFromIndex(nIndex);
					ASSERT(htiFound!=NULL);
					CString sTextCompareTo=m_tree.GetItemText(htiFound);
					if(sItemText==sTextCompareTo && 
						m_tree.GetItemData(htiFound)!=SERVICEREF_FLAG)
					{
						m_tree.EnsureVisible(htiFound);
						m_tree.SelectItem(htiFound);
						break;
					}
				}
			}
		}
	}

	*pResult = 0;
}
