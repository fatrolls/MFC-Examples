// NetworkResourcesDialog.cpp : implementation file
//

#include "stdafx.h"
#include "systemstateinfo.h"
#include "NetworkResourcesDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetworkResourcesDialog dialog


CNetworkResourcesDialog::CNetworkResourcesDialog() : CPageDialog()
{
	//{{AFX_DATA_INIT(CNetworkResourcesDialog)
	m_bShowComment = TRUE;
	m_bShowDisks = TRUE;
	m_bShowPrinters = TRUE;
	m_bReportErrors = TRUE;
	m_nResourceScope = -1;
	m_nInitialLevel = 0;
	m_nMaxLevel = 10;
	//}}AFX_DATA_INIT
}


void CNetworkResourcesDialog::DoDataExchange(CDataExchange* pDX)
{
	CPageDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetworkResourcesDialog)
	DDX_Control(pDX, IDC_SPIN_MAXLEVEL, m_spinMaxLevel);
	DDX_Control(pDX, IDC_SPIN_INITIALLEVEL, m_spinInitialLevel);
	DDX_Control(pDX, IDC_SEPARATOR2, m_ctlSeparator2);
	DDX_Control(pDX, IDC_SEPARATOR1, m_ctlSeparator1);
	DDX_Control(pDX, IDC_RESOURCES_TREE, m_treeNetBrowse);
	DDX_Control(pDX, IDC_LIST_DETAILS, m_listDetails);
	DDX_Control(pDX, IDC_EDIT_MAXLEVEL, m_editMaxLevel);
	DDX_Control(pDX, IDC_EDIT_INITIALLEVEL, m_editInitialLevel);
	DDX_Control(pDX, IDC_COMBO_SCOPE, m_cmbResourceScope);
	DDX_Check(pDX, IDC_CHECK_COMMENTS, m_bShowComment);
	DDX_Check(pDX, IDC_CHECK_DISKS, m_bShowDisks);
	DDX_Check(pDX, IDC_CHECK_PRINTERS, m_bShowPrinters);
	DDX_Check(pDX, IDC_CHECK_REPORT, m_bReportErrors);
	DDX_CBIndex(pDX, IDC_COMBO_SCOPE, m_nResourceScope);
	DDX_Text(pDX, IDC_EDIT_INITIALLEVEL, m_nInitialLevel);
	DDX_Text(pDX, IDC_EDIT_MAXLEVEL, m_nMaxLevel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetworkResourcesDialog, CPageDialog)
	//{{AFX_MSG_MAP(CNetworkResourcesDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_RESOURCES_TREE, OnSelchangedResourcesTree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetworkResourcesDialog message handlers

void CNetworkResourcesDialog::OnInitDialog() 
{
	CPageDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	// Fill combo box with values
	m_cmbResourceScope.AddString(_T("Connected Resources"));
	m_cmbResourceScope.AddString(_T("Global Resources"));
	m_cmbResourceScope.AddString(_T("Persistent Connections"));
	m_cmbResourceScope.AddString(_T("Recent Connections"));
	m_cmbResourceScope.AddString(_T("Current Context Resources"));
	// ... Net scope is 1-based, index in combo is 0-based
	m_cmbResourceScope.SetCurSel(4);
	m_nResourceScope=4;

	// Set the spin ranges
	m_spinMaxLevel.SetRange(0,100);
	m_spinInitialLevel.SetRange(0,100);
	
	// ... Set net browse tree initial values
	SetTreeInitSettings();

	// initialize list of network resource detailes
	TCHAR rgtsz[][20] = {_T("Name"),_T("Value"),_T("Description")};
	LV_COLUMN lvcolumn;
	for(int nIndex=0; nIndex<3; nIndex++)  // add the columns to the list control
	{
		lvcolumn.mask=LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH;
		lvcolumn.fmt=LVCFMT_LEFT;
		lvcolumn.pszText=rgtsz[nIndex];
		lvcolumn.iSubItem=nIndex;
		lvcolumn.cx=(nIndex==0 ? 70 : (nIndex==1 ? 40 : 150));
		VERIFY(m_listDetails.InsertColumn(nIndex,&lvcolumn)!=-1);
	}


	// layout manager 
	//
	m_LayoutManager.Attach(this);
	
	// tree control
	m_LayoutManager.TieChild(IDC_RESOURCES_TREE,OX_LMS_ANY,OX_LMT_SAME);

	// list control
	m_LayoutManager.TieChild(IDC_LIST_DETAILS,
		OX_LMS_RIGHT|OX_LMS_BOTTOM|OX_LMS_LEFT,OX_LMT_SAME);

	// separators, combo, check buttons and expand level edit controls
	m_LayoutManager.TieChild(IDC_SEPARATOR1,OX_LMS_RIGHT|OX_LMS_BOTTOM,
		OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_SEPARATOR2,OX_LMS_RIGHT|OX_LMS_BOTTOM,
		OX_LMT_SAME);

	m_LayoutManager.TieChild(IDC_COMBO_SCOPE,OX_LMS_RIGHT|OX_LMS_BOTTOM,
		OX_LMT_SAME);

	m_LayoutManager.TieChild(IDC_CHECK_COMMENTS,OX_LMS_RIGHT|OX_LMS_BOTTOM,
		OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_CHECK_DISKS,OX_LMS_RIGHT|OX_LMS_BOTTOM,
		OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_CHECK_PRINTERS,OX_LMS_RIGHT|OX_LMS_BOTTOM,
		OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_CHECK_REPORT,OX_LMS_RIGHT|OX_LMS_BOTTOM,
		OX_LMT_SAME);

	m_LayoutManager.TieChild(IDC_STATIC_INITIALLEVEL,OX_LMS_RIGHT|OX_LMS_BOTTOM,
		OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_EDIT_INITIALLEVEL,OX_LMS_RIGHT|OX_LMS_BOTTOM,
		OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_SPIN_INITIALLEVEL,OX_LMS_RIGHT|OX_LMS_BOTTOM,
		OX_LMT_SAME);

	m_LayoutManager.TieChild(IDC_STATIC_MAXLEVEL,OX_LMS_RIGHT|OX_LMS_BOTTOM,
		OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_EDIT_MAXLEVEL,OX_LMS_RIGHT|OX_LMS_BOTTOM,
		OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_SPIN_MAXLEVEL,OX_LMS_RIGHT|OX_LMS_BOTTOM,
		OX_LMT_SAME);
	//////////////////

	// Perform first time initialization if necessary
	if (!m_treeNetBrowse.IsInitialized())
		VERIFY(m_treeNetBrowse.Initialize());
	m_treeNetBrowse.SetFocus();
	m_treeNetBrowse.SelectItem(m_treeNetBrowse.GetRootItem());

	// item tips for Details List control
	m_ItemTip.Attach(&m_listDetails);

	//////////////////////////////////////
}


void CNetworkResourcesDialog::Refresh() 
{
	// Get the data from the GUI
	if (!UpdateData(TRUE))
		// ... Data validation failed, user already warned, so just return
		return;

	// ... Set new initial values
	SetTreeInitSettings();
	// ... Build the contents of the tree again
	m_treeNetBrowse.BuildTreeContents();
	// ... Select the root 
	m_treeNetBrowse.SelectItem(m_treeNetBrowse.GetRootItem());
	m_treeNetBrowse.SetFocus();
}

void CNetworkResourcesDialog::SetTreeInitSettings()
{
	// Set initial values of the net browse control
	m_treeNetBrowse.ShowCommentName(m_bShowComment);
	m_treeNetBrowse.ShowDisks(m_bShowDisks);
	m_treeNetBrowse.ShowPrinters(m_bShowPrinters);
	// ... Net scope is 1-based, index in combo is 0-based
	m_treeNetBrowse.SetResourceScope(m_nResourceScope+1);
	m_treeNetBrowse.SetMaxNumLevels(m_nMaxLevel);
	m_treeNetBrowse.SetInitialExpandLevel(m_nInitialLevel);
	m_treeNetBrowse.ReportErrors(m_bReportErrors);
}

void CNetworkResourcesDialog::OnSelchangedResourcesTree(NMHDR* pNMHDR, 
														LRESULT* pResult) 
{
	UNREFERENCED_PARAMETER(pNMHDR);
	// TODO: Add your control notification handler code here
	
	// SHow the information about the currently selected resource
	const NETRESOURCE* pNetResource=m_treeNetBrowse.GetCurrentNetResource();
	PopulateDetailsList(pNetResource);

	*pResult=0;
}


void CNetworkResourcesDialog::PopulateDetailsList(const NETRESOURCE* pNetResource) 
{
	m_listDetails.SetRedraw(FALSE);

	VERIFY(m_listDetails.DeleteAllItems());
	if(pNetResource!=NULL)
	{
		int nIndex=0;
		CString sValue;

		sValue.Format(_T("%i"),pNetResource->dwScope);
		InsertDetailsListItem(nIndex,_T("Scope"),sValue,
			GetScopeName(pNetResource));

		sValue.Format(_T("%i"), pNetResource->dwType); 
		InsertDetailsListItem(nIndex,_T("Type"),sValue,
			GetTypeName(pNetResource));

		sValue.Format(_T("%i"), pNetResource->dwDisplayType); 
		InsertDetailsListItem(nIndex,_T("Display Type"),sValue,
			GetDisplayTypeName(pNetResource));

		sValue.Format(_T("0x%X"), pNetResource->dwUsage); 
		InsertDetailsListItem(nIndex,_T("Usage"),sValue,
			GetUsageName(pNetResource));
		
		if(pNetResource->lpLocalName!=NULL && 
			lstrlen(pNetResource->lpLocalName)>0)
			InsertDetailsListItem(nIndex,_T("Local Name"),_T(""),
				pNetResource->lpLocalName);

		if(pNetResource->lpRemoteName!=NULL && 
			lstrlen(pNetResource->lpRemoteName)>0)
			InsertDetailsListItem(nIndex,_T("Remote Name"),_T(""),
				pNetResource->lpRemoteName);

		if(pNetResource->lpComment!=NULL && 
			lstrlen(pNetResource->lpComment)>0)
			InsertDetailsListItem(nIndex,_T("Comment"),_T(""),
				pNetResource->lpComment);

		if(pNetResource->lpProvider!=NULL && 
			lstrlen(pNetResource->lpProvider)>0)
			InsertDetailsListItem(nIndex,_T("Provider"),_T(""),
				pNetResource->lpProvider);
	}

	if(m_listDetails.GetItemCount()>0)
		m_listDetails.SetItemState(0,LVIS_SELECTED|LVIS_FOCUSED,
			LVIS_SELECTED|LVIS_FOCUSED);

	m_listDetails.SetRedraw(TRUE);

	UpdateData(FALSE);
}

void CNetworkResourcesDialog::InsertDetailsListItem(int& nIndex,
													const CString& sName,
													const CString& sValue,
													const CString& sDescription)
{
	ASSERT(nIndex>=0);

	LV_ITEM	lvitem={ 0 };

	// name
	VERIFY(m_listDetails.InsertItem(nIndex,sName)!=-1);

	// value
	lvitem.mask=LVIF_TEXT;
	lvitem.iItem=nIndex;
	lvitem.iSubItem=1;
	lvitem.pszText=(LPTSTR)(LPCTSTR)sValue;
	VERIFY(m_listDetails.SetItem(&lvitem));

	// description
	lvitem.mask=LVIF_TEXT;
	lvitem.iItem=nIndex;
	lvitem.iSubItem=2;
	lvitem.pszText=(LPTSTR)(LPCTSTR)sDescription;
	VERIFY(m_listDetails.SetItem(&lvitem));

	nIndex++;
}


CString CNetworkResourcesDialog::GetScopeName(const NETRESOURCE* pNetResource) const
{
	ASSERT(pNetResource != NULL);
	CString sScopeName;
	switch (pNetResource->dwScope)
	{
		case RESOURCE_CONNECTED:
			sScopeName = _T("(Connected resources)");
			break;
		case RESOURCE_GLOBALNET:
			sScopeName = _T("(Global resources)");
			break;
		case RESOURCE_REMEMBERED:
			sScopeName = _T("(Persistent connections)");
			break;
		case RESOURCE_RECENT:
			sScopeName = _T("(Recent connections)");
			break;
		case RESOURCE_CONTEXT:
			sScopeName = _T("(Current context resources)");
			break;
		default:
			// Let string stay empty
			break;
	}
	return sScopeName;
}

CString CNetworkResourcesDialog::GetTypeName(const NETRESOURCE* pNetResource) const
{
	ASSERT(pNetResource != NULL);
	CString sTypeName;
	switch (pNetResource->dwType)
	{
		case RESOURCETYPE_ANY:
			sTypeName = _T("(Any resource)");
			break;
		case RESOURCETYPE_DISK:
			sTypeName = _T("(Disk resource)");
			break;
		case RESOURCETYPE_PRINT:
			sTypeName = _T("(Print resource)");
			break;
		case RESOURCETYPE_RESERVED:
			sTypeName = _T("(Reserved resource)");
			break;
		case RESOURCETYPE_UNKNOWN:
			sTypeName = _T("(Unknown resource)");
			break;
		default:
			// Let string stay empty
			break;
	}
	return sTypeName;
}

CString CNetworkResourcesDialog::GetDisplayTypeName(const NETRESOURCE* pNetResource) const
{
	ASSERT(pNetResource != NULL);
	CString sDisplayTypeName;
	switch (pNetResource->dwDisplayType)
	{
		case RESOURCEDISPLAYTYPE_GENERIC:
			sDisplayTypeName = _T("(Unspecified)");
			break;
		case RESOURCEDISPLAYTYPE_DOMAIN:
			sDisplayTypeName = _T("(Domain)");
			break;
		case RESOURCEDISPLAYTYPE_SERVER:
			sDisplayTypeName = _T("(Server)");
			break;
		case RESOURCEDISPLAYTYPE_SHARE:
			sDisplayTypeName = _T("(Share)");
			break;
		case RESOURCEDISPLAYTYPE_FILE:
			sDisplayTypeName = _T("(file)");
			break;
		case RESOURCEDISPLAYTYPE_GROUP:
			sDisplayTypeName = _T("(Broup)");
			break;
		case RESOURCEDISPLAYTYPE_NETWORK:
			sDisplayTypeName = _T("(Network)");
			break;
		case RESOURCEDISPLAYTYPE_ROOT:
			sDisplayTypeName = _T("(Network Root)");
			break;
		case RESOURCEDISPLAYTYPE_SHAREADMIN:
			sDisplayTypeName = _T("(Administrative Share)");
			break;
		case RESOURCEDISPLAYTYPE_DIRECTORY:
			sDisplayTypeName = _T("(Directory)");
			break;
		case RESOURCEDISPLAYTYPE_TREE:
			sDisplayTypeName = _T("(Tree)");
			break;
		default:
			// Let string stay empty
			break;
	}
	return sDisplayTypeName;
}

CString CNetworkResourcesDialog::GetUsageName(const NETRESOURCE* pNetResource) const
{
	ASSERT(pNetResource != NULL);
	CString sUsageName;
	if (pNetResource->dwScope == RESOURCE_GLOBALNET)
	{
		if ((pNetResource->dwUsage & RESOURCEUSAGE_CONNECTABLE) == RESOURCEUSAGE_CONNECTABLE)
			sUsageName += _T("Connectable - ");
		if ((pNetResource->dwUsage & RESOURCEUSAGE_CONTAINER) == RESOURCEUSAGE_CONTAINER)
			sUsageName += _T("Container - ");
		if ((pNetResource->dwUsage & RESOURCEUSAGE_NOLOCALDEVICE) == RESOURCEUSAGE_NOLOCALDEVICE)
			sUsageName += _T("Local not needed - ");
		if ((pNetResource->dwUsage & RESOURCEUSAGE_SIBLING) == RESOURCEUSAGE_SIBLING)
			sUsageName += _T("Sibling - ");
		if ((pNetResource->dwUsage & RESOURCEUSAGE_RESERVED) == RESOURCEUSAGE_RESERVED)
			sUsageName += _T("Reserved - ");
		if (!sUsageName.IsEmpty())
		{
			// ... Remove trailing hyphen
			sUsageName = sUsageName.Left(sUsageName.GetLength() - 3);
			// ... Add parentheses
			sUsageName = _T("(") + sUsageName + _T(")");
		}
	}
	return sUsageName;
}

