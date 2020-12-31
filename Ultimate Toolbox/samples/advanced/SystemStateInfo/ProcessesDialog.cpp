// ProcessesDialog.cpp : implementation file
//

#include "stdafx.h"
#include "systemstateinfo.h"
#include "ProcessesDialog.h"

#include "OXSysInfo.h"
#include "OXProcess.h"

#include "UTBStrOp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProcessesDialog dialog


CProcessesDialog::CProcessesDialog() : CPageDialog()
{
	//{{AFX_DATA_INIT(CProcessesDialog)
	m_nExpandLevel = 0;
	m_nExpandType = 1;
	//}}AFX_DATA_INIT
}


void CProcessesDialog::DoDataExchange(CDataExchange* pDX)
{
	CPageDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProcessesDialog)
	DDX_Control(pDX, IDC_SPIN_EXPANDLEVEL, m_spinExpandLevel);
	DDX_Control(pDX, IDC_EDIT_EXPANDLEVEL, m_editExpandLevel);
	DDX_Control(pDX, IDC_TREE_PROCESSES, m_tree);
	DDX_Text(pDX, IDC_EDIT_EXPANDLEVEL, m_nExpandLevel);
	DDX_Radio(pDX, IDC_RADIO_EXPANDLEVEL, m_nExpandType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProcessesDialog, CPageDialog)
	//{{AFX_MSG_MAP(CProcessesDialog)
	ON_BN_CLICKED(IDC_RADIO_EXPANDALL, OnRadioExpandall)
	ON_BN_CLICKED(IDC_RADIO_EXPANDLEVEL, OnRadioExpandlevel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProcessesDialog message handlers

void CProcessesDialog::OnInitDialog() 
{
	CPageDialog::OnInitDialog();

	// TODO: Add your specialized creation code here

	m_ilTree.Create(IDB_PROCESSES_TREE_IMAGE,16,1,RGB(255,0,255));
	m_tree.SetImageList(&m_ilTree,TVSIL_NORMAL);

	LV_COLUMN lvc={ sizeof(lvc) };
	lvc.fmt=LVCFMT_LEFT;
	lvc.cx=237;
	lvc.pszText=_T("Process image name");
	lvc.mask = LVCF_FMT|LVCF_WIDTH|LVCF_TEXT;
	m_tree.SetColumn(0,&lvc);
	m_tree.InsertColumn(1,_T("Process ID"),LVCFMT_LEFT,200,1);

	// set COXTreeCtrl styles
	m_tree.ModifyExStyle(0,TVOXS_PICKANYWHERE|TVOXS_ROWSEL);
	m_tree.ModifyStyle(0,TVS_SHOWSELALWAYS|TVS_HASBUTTONS|
		TVS_HASLINES|TVS_LINESATROOT);


	// spin control
	m_spinExpandLevel.SetRange(0,1);
	m_spinExpandLevel.SetPos(0);
	
	// layout manager 
	//
	m_LayoutManager.Attach(this);
	
	// tree control
	m_LayoutManager.TieChild(IDC_TREE_PROCESSES,OX_LMS_ANY,OX_LMT_SAME);
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

void CProcessesDialog::Refresh() 
{
	PopulateTree();
}

void CProcessesDialog::PopulateTree()
{
	if(!UpdateData())
		return;

	CWaitCursor waitCursor;

	COXProcessIterator processIterator;
	if(!processIterator.MakeSnapshot())
		return;

	m_tree.SetRedraw(FALSE);
	m_tree.DeleteAllItems();

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

	CString sValue;
	HTREEITEM htiRoot;
	HTREEITEM htiItem;

	COLORREF clrTopic=RGB(0,0,255);
	COLORREF clrValue=RGB(0,128,0);

	COXSysInfo m_SysInfo;

	HTREEITEM htiSelectItem=NULL;
	///////////////////////////////////////////////////
	//
	for(int nIndex=0; nIndex<processIterator.GetProcessCount(); nIndex++)
	{
		if(processIterator.IsValid() && processIterator.GetImageFileName(sValue))
		{
			ASSERT(!sValue.IsEmpty());
			if(sValue.Find(_T("\\??\\"))==0)
				sValue=sValue.Mid(4);

			CString sFullPath=sValue;
			// process image name and ID
			int nLastBackslashPos=sValue.ReverseFind('\\');
			if(nLastBackslashPos!=-1)
				sValue=sValue.Mid(nLastBackslashPos+1);
			htiRoot=InsertItem(sValue,NULL,0,pFontRoot,clrTopic);
			if(htiSelectItem==NULL)
				htiSelectItem=htiRoot;
			sValue.Format(_T("%u"),processIterator.GetProcessID());
			VERIFY(m_tree.SetSubItem(htiRoot,1,
				OX_SUBITEM_FONT|OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
				sValue,0,pFontSubRoot,RGB(0,0,0)));


			// full process image path
			CString sWindowsDirTag=_T("\\SystemRoot");
			CString sWindowsDir;
			if(!m_SysInfo.GetWindowsDir(&sWindowsDir))
				sWindowsDir.Empty();
			if(!sWindowsDir.IsEmpty() && sFullPath.Find(sWindowsDirTag)==0)
				sFullPath=sWindowsDir+sFullPath.Mid(sWindowsDirTag.GetLength());
			htiItem=InsertItem(_T("Full Image Path"),htiRoot);
			VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
				sFullPath,0,NULL,clrValue));
			VERIFY(m_tree.SetItemDrawEllipsis(htiItem,DT_PATH_ELLIPSIS,1));


			// process priority class
			DWORD dwPriorityClass;
			if(processIterator.GetPriorityClass(dwPriorityClass))
			{
				htiItem=InsertItem(_T("Priority Class"),htiRoot);

				switch(dwPriorityClass)
				{
				case HIGH_PRIORITY_CLASS:
					sValue.Format(_T("HIGH_PRIORITY_CLASS (%d)"),dwPriorityClass);
					break;
				case IDLE_PRIORITY_CLASS:
					sValue.Format(_T("IDLE_PRIORITY_CLASS (%d)"),dwPriorityClass);
					break;
				case NORMAL_PRIORITY_CLASS:
					sValue.Format(_T("NORMAL_PRIORITY_CLASS (%d)"),dwPriorityClass);
					break;
				case REALTIME_PRIORITY_CLASS:
					sValue.Format(_T("REALTIME_PRIORITY_CLASS (%d)"),dwPriorityClass);
					break;
				default:
					sValue.Format(_T("Unknown (%d)"),dwPriorityClass);
					break;
				}
				VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
					sValue,0,NULL,clrValue));
			}


			// process version
			DWORD dwVersion;
			if(processIterator.GetVersion(dwVersion) && dwVersion>0)
			{
				htiItem=InsertItem(_T("Version"),htiRoot);

				sValue.Format(_T("%d.%d"),HIWORD(dwVersion),LOWORD(dwVersion));
				VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
					sValue,0,NULL,clrValue));
			}


			// priority boost
			BOOL bDisabled;
			if(processIterator.IsPriorityBoostDisabled(bDisabled))
			{
				htiItem=InsertItem(_T("Priority Boost"),htiRoot);

				sValue=(bDisabled ? _T("Disabled") : _T("Enabled"));
				VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
					sValue,0,NULL,clrValue));
			}


			// creation time
			COleDateTime oleDateTime;
			if(processIterator.GetCreationTime(oleDateTime))
			{
				htiItem=InsertItem(_T("Creation Time"),htiRoot);

				sValue=oleDateTime.Format();
				VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
					sValue,0,NULL,clrValue));
			}		


			// kernel time
			DWORDLONG timeSpent;
			if(processIterator.GetKernelTime(timeSpent) && timeSpent>0)
			{
				htiItem=InsertItem(_T("Kernel Time"),htiRoot);

				sValue.Format(_T("%d ms"),timeSpent/10000);
				VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
					sValue,0,NULL,clrValue));
			}		


			// user time
			if(processIterator.GetUserTime(timeSpent) && timeSpent>0)
			{
				htiItem=InsertItem(_T("User Time"),htiRoot);

				sValue.Format(_T("%d ms"),timeSpent/10000);
				VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
					sValue,0,NULL,clrValue));
			}		
		}

		++processIterator;
	}
	//
	////////////////////////////////////////////////

	ExpandTree((m_nExpandType==0 ? m_nExpandLevel : -1));

	m_tree.SetFocus();
	m_tree.SelectItem(htiSelectItem);

	m_tree.SetRedraw(TRUE);
}


void CProcessesDialog::ExpandTree(int nExpandLevel/*=-1*/,
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

HTREEITEM CProcessesDialog::InsertItem(CString sItem, HTREEITEM htiParent/*=NULL*/, 
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


void CProcessesDialog::ShowControls()
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

void CProcessesDialog::OnRadioExpandall() 
{
	// TODO: Add your control notification handler code here
	
	ShowControls();
}

void CProcessesDialog::OnRadioExpandlevel() 
{
	// TODO: Add your control notification handler code here
	
	ShowControls();
}
