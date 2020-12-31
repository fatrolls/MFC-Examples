// SysInfoDialog.cpp : implementation file
//

#include "stdafx.h"
#include "systemstateinfo.h"
#include "SysInfoDialog.h"

#include "OXSysInfo.h"
#include "OXInteger.h"

#include "UTBStrOp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSysInfoDialog dialog


CSysInfoDialog::CSysInfoDialog() : CPageDialog()
{
	//{{AFX_DATA_INIT(CSysInfoDialog)
	m_nExpandLevel = 0;
	m_nExpandType = 1;
	m_bShowPrinters = FALSE;
	//}}AFX_DATA_INIT
}


void CSysInfoDialog::DoDataExchange(CDataExchange* pDX)
{
	CPageDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSysInfoDialog)
	DDX_Control(pDX, IDC_SPIN_EXPANDLEVEL, m_spinExpandLevel);
	DDX_Control(pDX, IDC_EDIT_EXPANDLEVEL, m_editExpandLevel);
	DDX_Control(pDX, IDC_TREE_ITEMS, m_tree);
	DDX_Text(pDX, IDC_EDIT_EXPANDLEVEL, m_nExpandLevel);
	DDX_Radio(pDX, IDC_RADIO_EXPANDLEVEL, m_nExpandType);
	DDX_Check(pDX, IDC_SHOWPRINTERS, m_bShowPrinters);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSysInfoDialog, CPageDialog)
	//{{AFX_MSG_MAP(CSysInfoDialog)
	ON_BN_CLICKED(IDC_RADIO_EXPANDALL, OnRadioExpandall)
	ON_BN_CLICKED(IDC_RADIO_EXPANDLEVEL, OnRadioExpandlevel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSysInfoDialog message handlers

void CSysInfoDialog::OnInitDialog() 
{
	CPageDialog::OnInitDialog();

	// TODO: Add your specialized creation code here

	m_ilTree.Create(IDB_SYSINFO_TREE_IMAGE,16,1,RGB(255,0,255));
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
	m_LayoutManager.TieChild(IDC_TREE_ITEMS,OX_LMS_ANY,OX_LMT_SAME);
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

	m_LayoutManager.TieChild(IDC_SHOWPRINTERS,OX_LMS_BOTTOM,OX_LMT_SAME);
	//////////////////

	//////////////////////////////////////

	PopulateTree();

	ShowControls();
}

void CSysInfoDialog::Refresh() 
{
	PopulateTree();
}

void CSysInfoDialog::PopulateTree()
{
	if(!UpdateData())
		return;

	CWaitCursor waitCursor;

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
		UTBStr::tcsncpy(lf.lfFaceName, LF_FACESIZE, _T("Arial"),LF_FACESIZE);
		fontRoot.CreateFontIndirect(&lf);

		lf.lfHeight=-12;
		lf.lfWeight=FW_BOLD;
		UTBStr::tcsncpy(lf.lfFaceName,LF_FACESIZE,_T("Times New Roman"),LF_FACESIZE);
		fontSubRoot.CreateFontIndirect(&lf);
	}
	pFontRoot=((HFONT)fontRoot!=NULL) ? &fontRoot : NULL;
	CFont* pFontSubRoot=((HFONT)fontSubRoot!=NULL) ? &fontSubRoot : NULL;

	CString sValue;
	DWORD dwValue;
	BOOL bResult;
	HTREEITEM htiRoot;
	HTREEITEM htiSubRoot;
	HTREEITEM htiItem;

	COLORREF clrTopic=RGB(0,0,255);
	COLORREF clrValue=RGB(0,128,0);

	COXInteger Integer;

	COXSysInfo m_SysInfo;
	BOOL bIsWindowsNT=FALSE;

	///////////////////////////////////////////////////
	// SYSTEM
	//
	htiRoot=InsertItem(_T("System"),NULL,0,pFontRoot,clrTopic);
	HTREEITEM htiSelectItem=htiRoot;

	// operating system
	DWORD dwPlatform,dwMajor,dwMinor;
	if(m_SysInfo.GetWindowsVersion(&dwPlatform,&dwMajor,&dwMinor))
	{
		htiItem=InsertItem(_T("Operating system"),htiRoot);

		if(dwPlatform==VER_PLATFORM_WIN32s)
		{
			sValue=_T("Windows 3.1");
		}
		else if(dwPlatform==VER_PLATFORM_WIN32_WINDOWS)
		{
			if(dwMajor==4 && dwMinor==0)
			{
				sValue=_T("Windows 95");
				BOOL bIsOSR2;
				if(m_SysInfo.IsOSR2(&bIsOSR2) && bIsOSR2)
					sValue=sValue+_T(" OSR 2");
			}
			else if(dwMajor==4 && dwMinor==10)
				sValue=_T("Windows 98");
			else if(dwMajor==4 && dwMinor==90)
				sValue=_T("Windows Me");
			else
				sValue=_T("Unknown");
		}
		else if(dwPlatform==VER_PLATFORM_WIN32_NT)
		{
			if(dwMajor==5)
			{
				switch (dwMinor)
				{
				case 2:
					sValue = _T("Windows Server 2003");
					break;
				case 1:
					sValue = _T("Windows XP");
					break;
				case 0:
					{
						sValue=_T("Windows 2000");
						BOOL bIsNTServer;
						if(m_SysInfo.IsNTServer(&bIsNTServer))
						{
							if(bIsNTServer)
								sValue+=_T(" Server");
							else
								sValue+=_T(" Professional");
						}
					}
					break;
				default:
					sValue = _T("Windows Vista");
				}

				VERIFY(sValue.GetBuffer(1024)!=NULL);
				//sValue.Format(_T("%s v%d.%d"),sValue,dwMajor,dwMinor);
				sValue.ReleaseBuffer();

				bIsWindowsNT=TRUE;
			}
			else
			{
				sValue=_T("Windows NT");
				BOOL bIsNTServer;
				if(m_SysInfo.IsNTServer(&bIsNTServer))
				{
					if(bIsNTServer)
						sValue+=_T(" Server");
					else
						sValue+=_T(" Workstation");
				}
				
				VERIFY(sValue.GetBuffer(1024)!=NULL);
				sValue.Format(_T("%s v%d.%d"),sValue,dwMajor,dwMinor);
				sValue.ReleaseBuffer();

				bIsWindowsNT=TRUE;
			}
		}
		else
			sValue=_T("Unknown");

		VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
			sValue,0,NULL,clrValue));
	}
	////////////////////////////////////////////////

	// build number
	if(m_SysInfo.GetWindowsBuildNumber(&dwValue))
	{
		htiItem=InsertItem(_T("Build Number"),htiRoot);
		sValue.Format(_T("%u"),dwValue);
		VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
			sValue,0,NULL,clrValue));
	}
	////////////////////////////////////////////////

	// platform info
	if(m_SysInfo.GetWindowsPlatformInfo(sValue) && !sValue.IsEmpty() &&
		!sValue.SpanExcluding(_T(" ")).IsEmpty())
	{
		htiItem=InsertItem(_T("Platform Info"),htiRoot);
		VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
			sValue,0,NULL,clrValue));
	}
	////////////////////////////////////////////////

	// computer name
	if(m_SysInfo.GetComputerName(&sValue))
	{
		htiItem=InsertItem(_T("Computer name"),htiRoot);
		VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
			sValue,0,NULL,clrValue));
	}
	////////////////////////////////////////////////

	// User & Domain name
	CString sDomain;
	if(bIsWindowsNT && m_SysInfo.GetUserAndDomainName(&sValue,&sDomain))
	{
		htiItem=InsertItem(_T("Domain name"),htiRoot);
		VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
			sDomain,0,NULL,clrValue));
		htiItem=InsertItem(_T("User name"),htiRoot);
		VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
			sValue,0,NULL,clrValue));
	}
	else if(m_SysInfo.GetUserName(&sValue))
	{
		htiItem=InsertItem(_T("User name"),htiRoot);
		VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
			sValue,0,NULL,clrValue));
	}
	////////////////////////////////////////////////

	
	// Network Interface Card (NIC) Address
	NICADDRESS NICAddress;
	if(m_SysInfo.GetNICAddress(&NICAddress))
	{
		htiItem=InsertItem(_T("Network Interface Card (NIC) Address"),htiRoot);
		sValue.Format(_T("%.2x.%.2x.%.2x.%.2x.%.2x.%.2x"), 
			NICAddress.data[0],NICAddress.data[1],NICAddress.data[2],
			NICAddress.data[3],NICAddress.data[4],NICAddress.data[5]);
		VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
			sValue,0,NULL,clrValue));
	}
	////////////////////////////////////////////////

	// IP address(es)
	CStringArray arrIPAddresses;
	if(m_SysInfo.GetListIPAddresses(&arrIPAddresses))
	{
		ASSERT(arrIPAddresses.GetSize()>0);
		
		if(arrIPAddresses.GetSize()>1)
		{
			htiSubRoot=InsertItem(_T("IP Addresses"),htiRoot,-1,pFontSubRoot);
			sValue.Format(_T("%u"),arrIPAddresses.GetSize());
			VERIFY(m_tree.SetSubItem(htiSubRoot,1,
				OX_SUBITEM_TEXT|(pFontSubRoot!=NULL ? OX_SUBITEM_FONT : 0),
				sValue,0,pFontSubRoot));
		}
		else
			htiSubRoot=htiRoot;

		for(int nIndex=0; nIndex<arrIPAddresses.GetSize(); nIndex++)
		{
			if(nIndex==0)
				htiItem=InsertItem(_T("Primary IP Address"),htiSubRoot);
			else
			{
				sValue.Format(_T("IP Address %u"),nIndex);
				htiItem=InsertItem(sValue,htiSubRoot);
			}
			VERIFY(m_tree.SetSubItem(htiItem,1,
				OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
				arrIPAddresses[nIndex],0,NULL,clrValue));
		}
	}
	////////////////////////////////////////////////

	//
	// The end of SYSTEM topic
	///////////////////////////////////////////////////


	///////////////////////////////////////////////////
	// DIRECTORIES
	//
	htiRoot=InsertItem(_T("Directories"),NULL,1,pFontRoot,clrTopic);

	// Windows directory
	if(m_SysInfo.GetWindowsDir(&sValue))
	{
		htiItem=InsertItem(_T("Windows directory"),htiRoot);
		VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
			sValue,0,NULL,clrValue));
	}
	////////////////////////////////////////////////

	// System directory
	if(m_SysInfo.GetSystemDir(&sValue))
	{
		htiItem=InsertItem(_T("System directory"),htiRoot);
		VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
			sValue,0,NULL,clrValue));
	}
	////////////////////////////////////////////////

	// Temporary directory
	if(m_SysInfo.GetTempDir(&sValue))
	{
		htiItem=InsertItem(_T("Temporary directory"),htiRoot);
		VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
			sValue,0,NULL,clrValue));
	}
	////////////////////////////////////////////////

	//
	// The end of DIRECTORIES topic
	///////////////////////////////////////////////////


	///////////////////////////////////////////////////
	// PROCESSOR(S)
	//

	// Number of CPUs
	int nNumProcessors;
	if(m_SysInfo.GetNumProcessors(&nNumProcessors))
	{
		VERIFY(nNumProcessors>=1);

		// topic will depend on the number of processors used in the system
		if(nNumProcessors>1)
		{
			htiRoot=InsertItem(_T("Processors"),NULL,2,pFontRoot,clrTopic);
			sValue.Format(_T("%d"),nNumProcessors);
			VERIFY(m_tree.SetSubItem(htiRoot,1,
				OX_SUBITEM_TEXT|(pFontRoot!=NULL ? OX_SUBITEM_FONT : 0),
				sValue,0,pFontRoot));
			htiSubRoot=InsertItem(_T("Primary processor"),
				htiRoot,-1,pFontSubRoot);
		}
		else
			htiSubRoot=InsertItem(_T("Processor"),NULL,2,pFontRoot,clrTopic);
		///////////////////////////////////////////////////////////////////

		// primary processor description
		//
		// Processor Architecture
		DWORD dwProcessorType;
		if(m_SysInfo.GetProcessorType(&dwProcessorType))
		{
			htiItem=InsertItem(_T("Architecture"),htiSubRoot);
			
			switch(dwProcessorType)
			{
				case PROCESSOR_INTEL_386:
					sValue=_T("Intel 386");
					break;
				case PROCESSOR_INTEL_486:
					sValue=_T("Intel 486");
					break;
				case PROCESSOR_INTEL_PENTIUMCELERON:
					sValue=_T("Intel Pentium Celeron");
					break;
				case PROCESSOR_INTEL_PENTIUMPRO:
					sValue=_T("Intel Pentium Pro");
					break;
				case PROCESSOR_INTEL_PENTIUM:
					sValue=_T("Intel Pentium");
					break;
				case PROCESSOR_INTEL_PENTIUM2:
					sValue=_T("Intel Pentium II");
					break;
				case PROCESSOR_INTEL_PENTIUM3:
					sValue=_T("Intel Pentium III");
					break;
				case PROCESSOR_MIPSR4000:
					sValue=_T("MIPS R4000");
					break;
				case PROCESSOR_ALPHA21064:
					sValue=_T("Alpha 21064");
					break;
				case PROCESSOR_ALPHA21066:
					sValue=_T("Alpha 21066");
					break;
				case PROCESSOR_ALPHA21164:
					sValue=_T("Alpha 21164");
					break;
				case PROCESSOR_PPC601:
					sValue=_T("PowerPC 601");
					break;
				case PROCESSOR_PPC603:
					sValue=_T("PowerPC 603");
					break;
				case PROCESSOR_PPC604:
					sValue=_T("PowerPC 604");
					break;
				case PROCESSOR_PPC603PLUS:
					sValue=_T("PowerPC 603+");
					break;
				case PROCESSOR_PPC604PLUS:
					sValue=_T("PowerPC 604+");
					break;
				case PROCESSOR_PPC620:
					sValue=_T("PowerPC 620");
					break;
				default:
					sValue=_T("UNKNOWN");
					break;
			}
			VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
				sValue,0,NULL,clrValue));
		}

		// Processor speed
		DWORD dwSpeed;
		if(m_SysInfo.GetProcessorSpeed(&dwSpeed))
		{
			htiItem=InsertItem(_T("Speed"),htiSubRoot);
			sValue.Format(_T("%d MHz"),dwSpeed);
			VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
				sValue,0,NULL,clrValue));
		}

		// Math CoProcessor
		if(m_SysInfo.IsCoProcessorPresent(&bResult))
		{
			htiItem=InsertItem(_T("Math CoProcessor"),htiSubRoot);
			sValue=bResult ? _T("Present") : _T("Not present");
			VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
				sValue,0,NULL,clrValue));
		}

		// MMX technology
		if(m_SysInfo.IsMMXProcessor(&bResult))
		{
			htiItem=InsertItem(_T("MMX technology"),htiSubRoot);
			sValue=bResult ? _T("Present") : _T("Not present");
			VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
				sValue,0,NULL,clrValue));
		}

		// Time stamp 
		DWORD dwHigh, dwLow;
		if(m_SysInfo.GetTimeStamp(&dwHigh,&dwLow))
		{
			htiItem=InsertItem(_T("Time stamp"),htiSubRoot);
			sValue.Format(_T("%08lx  %08lx"),dwHigh,dwLow);
			VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
				sValue,0,NULL,clrValue));
		}

		/////////////////////////////////////////////


		// multiple processors description
		if(nNumProcessors>1)
			for(int nIndex=2; nIndex<=nNumProcessors; nIndex++)
			{
				sValue.Format(_T("Processor %d"),nIndex);
				htiSubRoot=InsertItem(sValue,htiRoot,-1,pFontSubRoot);

				// Processor speed
				DWORD dwSpeed;
				if(m_SysInfo.GetProcessorSpeed(&dwSpeed,nIndex-1))
				{
					htiItem=InsertItem(_T("Speed"),htiSubRoot);
					sValue.Format(_T("%d MHz"),dwSpeed);
					VERIFY(m_tree.SetSubItem(htiItem,1,
						OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
						sValue,0,NULL,clrValue));
				}
			}
		/////////////////////////////////////////////
	}

	//
	// The end of PROCESSOR(S) topic
	///////////////////////////////////////////////////


	///////////////////////////////////////////////////
	// DISC INFORMATION
	//
	htiRoot=InsertItem(_T("Disc Information"),NULL,3,pFontRoot,clrTopic);

	int	nDiskType;
	CString	sFileSysType;
	CString	sVolName;
	DWORDLONG dwTotalSpace, dwFreeSpace;
	DWORD dwVolSer;
	int nIndex=0;
	for(nIndex=0; nIndex<26; nIndex++)
	{
		if(m_SysInfo.GetDriveTypeInfo(nIndex,&sFileSysType,&nDiskType))
		{
			if(m_SysInfo.GetDriveVolumeInfo(nIndex,&sVolName,
				&dwVolSer,&dwTotalSpace,&dwFreeSpace))
			{
				sValue.Format(_T("Drive %c:"),nIndex+65);
				htiSubRoot=InsertItem(sValue,htiRoot,-1,pFontSubRoot);

				if(nDiskType == DRIVE_FIXED || nIndex==0 || nIndex==1)
				{
					// type of disk
					if(nIndex==0 || nIndex==1)
					{
						m_tree.SetItemImage(htiSubRoot,8,8);
						sValue=_T("Floppy Disk");
					}
					else
					{
						m_tree.SetItemImage(htiSubRoot,9,9);
						sValue=_T("Fixed Disk");
					}
					VERIFY(m_tree.SetSubItem(htiSubRoot,1,
						OX_SUBITEM_TEXT,sValue,0,NULL));

					// File System
					htiItem=InsertItem(_T("File System"),htiSubRoot);
					VERIFY(m_tree.SetSubItem(htiItem,1,
						OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
						sFileSysType,0,NULL,clrValue));

					// Volume name
					htiItem=InsertItem(_T("Volume Name"),htiSubRoot);
					VERIFY(m_tree.SetSubItem(htiItem,1,
						OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
						sVolName.IsEmpty() ? _T("<Blank>") : sVolName,0,
						NULL,clrValue));

					// Volume Serial
					htiItem=InsertItem(_T("Volume Serial"),htiSubRoot);
					sValue.Format(_T("%u"),dwVolSer);
					VERIFY(m_tree.SetSubItem(htiItem,1,
						OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
						sValue,0,NULL,clrValue));

					// Total space 
					htiItem=InsertItem(_T("Total space"),htiSubRoot);
					Integer.SetNumber(dwTotalSpace/1024);
					sValue=Integer.GetStringNumber(10,TRUE)+_T(" KB");
					VERIFY(m_tree.SetSubItem(htiItem,1,
						OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
						sValue,0,NULL,clrValue));

					// Free space
					htiItem=InsertItem(_T("Free space"),htiSubRoot);
					Integer.SetNumber(dwFreeSpace/1024);
					sValue=Integer.GetStringNumber(10,TRUE)+_T(" KB");
					VERIFY(m_tree.SetSubItem(htiItem,1,
						OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
						sValue,0,NULL,clrValue));
				}
				else if(nDiskType==DRIVE_CDROM)
				{
					m_tree.SetItemImage(htiSubRoot,10,10);

					// type of disk
					VERIFY(m_tree.SetSubItem(htiSubRoot,1,
						OX_SUBITEM_TEXT,_T("CD ROM"),0,NULL));

					// File System
					htiItem=InsertItem(_T("File System"),htiSubRoot);
					VERIFY(m_tree.SetSubItem(htiItem,1,
						OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
						sFileSysType,0,NULL,clrValue));

					// Volume name
					htiItem=InsertItem(_T("Volume Name"),htiSubRoot);
					VERIFY(m_tree.SetSubItem(htiItem,1,
						OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
						sVolName.IsEmpty() ? _T("<Blank>") : sVolName,0,
						NULL,clrValue));
				}
				else if(nDiskType==DRIVE_REMOTE)
				{
					m_tree.SetItemImage(htiSubRoot,11,11);

					// type of disk
					VERIFY(m_tree.SetSubItem(htiSubRoot,1,
						OX_SUBITEM_TEXT,_T("Network Disk"),0,NULL));

					// File System
					htiItem=InsertItem(_T("File System"),htiSubRoot);
					VERIFY(m_tree.SetSubItem(htiItem,1,
						OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
						sFileSysType,0,NULL,clrValue));

					// Volume name
					htiItem=InsertItem(_T("Volume Name"),htiSubRoot);
					VERIFY(m_tree.SetSubItem(htiItem,1,
						OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
						sVolName.IsEmpty() ? _T("<Blank>") : sVolName,0,
						NULL,clrValue));
				}
				else
				{
					// type of disk
					VERIFY(m_tree.SetSubItem(htiSubRoot,1,
						OX_SUBITEM_TEXT,_T("Unknown"),0,NULL));
				}
			}
		}
	}

	//
	// The end of DISC INFORMATION topic
	///////////////////////////////////////////////////


	///////////////////////////////////////////////////
	// DISPLAY
	//
	htiRoot=InsertItem(_T("Display"),NULL,4,pFontRoot,clrTopic);

	// Font Size
	if(m_SysInfo.IsSmallFont(&bResult))
	{
		htiItem=InsertItem(_T("Font Size"),htiRoot);
		sValue=bResult ? _T("Small fonts") : _T("Large fonts");
		VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
			sValue,0,NULL,clrValue));
	}
	////////////////////////////////////////////////

	// Display resolution
	int	nXRes, nYRes;
	if(m_SysInfo.GetDisplayResolution(&nXRes,&nYRes))
	{
		htiItem=InsertItem(_T("Current Resolution"),htiRoot);
		sValue.Format(_T("%u x %u"), nXRes, nYRes);
		VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
			sValue,0,NULL,clrValue));
	}
	////////////////////////////////////////////////

	// Display colors
	int nNumBits;
	DWORDLONG dwNumColors;
	if(m_SysInfo.GetDisplayNumColors(&dwNumColors,&nNumBits))
	{
		htiItem=InsertItem(_T("Current Colors"),htiRoot);
		sValue.Format(_T(" (%u bits)"),nNumBits);
		Integer.SetNumber(dwNumColors);
		sValue=Integer.GetStringNumber(10,TRUE)+sValue;
		VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
			sValue,0,NULL,clrValue));
	}
	////////////////////////////////////////////////

	// Display max resolution
	if(m_SysInfo.GetDisplayMaxResolution(&nXRes,&nYRes))
	{
		htiItem=InsertItem(_T("Max Resolution"),htiRoot);
		sValue.Format(_T("%u x %u"), nXRes, nYRes);
		VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
			sValue,0,NULL,clrValue));
	}
	////////////////////////////////////////////////

	// Display max colors
	if(m_SysInfo.GetDisplayMaxNumColors(&dwNumColors,&nNumBits))
	{
		htiItem=InsertItem(_T("Max Colors"),htiRoot);
		sValue.Format(_T(" (%u bits)"),nNumBits);
		Integer.SetNumber(dwNumColors);
		sValue=Integer.GetStringNumber(10,TRUE)+sValue;
		VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
			sValue,0,NULL,clrValue));
	}
	////////////////////////////////////////////////

	// List of all display modes
	CArrayDisplayMode arrDisplayMode;
	if(m_SysInfo.GetAllDisplayModes(&arrDisplayMode) && 
		arrDisplayMode.GetSize()>0)
	{
		htiSubRoot=InsertItem(_T("List of all Display Modes"),
			htiRoot,-1,pFontSubRoot);
		sValue.Format(_T("%u"),arrDisplayMode.GetSize());
		VERIFY(m_tree.SetSubItem(htiSubRoot,1,
			OX_SUBITEM_TEXT|(pFontSubRoot!=NULL ? OX_SUBITEM_FONT : 0),
			sValue,0,pFontSubRoot));

		for(nIndex=1; nIndex<=arrDisplayMode.GetSize(); nIndex++)
		{
			DISPLAYMODE displayMode=arrDisplayMode.GetAt(nIndex-1);

			sValue.Format(_T("Display Mode %u"),nIndex);
			htiItem=InsertItem(sValue,htiSubRoot);
			Integer.SetNumber(displayMode.dwNumColors);
			sValue.Format(_T("%d x %d (%d bit, %s colors)"),
				displayMode.dwHorzResolution,displayMode.dwVertResolution,
				displayMode.dwBitsPerPixel,Integer.GetStringNumber(10,TRUE));
			VERIFY(m_tree.SetSubItem(htiItem,1,
				OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
				sValue,0,NULL,clrValue));
		}
	}
	////////////////////////////////////////////////

	//
	// The end of DISPLAY topic
	///////////////////////////////////////////////////

	
	///////////////////////////////////////////////////
	// MEMORY
	//
	htiRoot=InsertItem(_T("Memory"),NULL,5,pFontRoot,clrTopic);

	// Physical Memory
	htiSubRoot=InsertItem(_T("Physical Memory"),htiRoot,-1,pFontSubRoot);

	if(m_SysInfo.GetTotalPhysicalMemory(&dwValue))
	{
		htiItem=InsertItem(_T("Total amount"),htiSubRoot);
		Integer.SetNumber(dwValue/1024);
		sValue=Integer.GetStringNumber(10,TRUE)+_T(" KB");
		VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
			sValue,0,NULL,clrValue));
	}

	if(m_SysInfo.GetFreePhysicalMemory(&dwValue))
	{
		htiItem=InsertItem(_T("Free amount"),htiSubRoot);
		Integer.SetNumber(dwValue/1024);
		sValue=Integer.GetStringNumber(10,TRUE)+_T(" KB");
		VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
			sValue,0,NULL,clrValue));
	}
	////////////////////////////////////////////////

	// Swap File
	htiSubRoot=InsertItem(_T("Swap File"),htiRoot,-1,pFontSubRoot);

	if(m_SysInfo.GetTotalPageFile(&dwValue))
	{
		htiItem=InsertItem(_T("Total amount"),htiSubRoot);
		Integer.SetNumber(dwValue/1024);
		sValue=Integer.GetStringNumber(10,TRUE)+_T(" KB");
		VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
			sValue,0,NULL,clrValue));
	}

	if(m_SysInfo.GetFreePageFile(&dwValue))
	{
		htiItem=InsertItem(_T("Free amount"),htiSubRoot);
		Integer.SetNumber(dwValue/1024);
		sValue=Integer.GetStringNumber(10,TRUE)+_T(" KB");
		VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
			sValue,0,NULL,clrValue));
	}
	////////////////////////////////////////////////

	// Virtual Memory
	htiSubRoot=InsertItem(_T("Virtual Memory"),htiRoot,-1,pFontSubRoot);

	if(m_SysInfo.GetTotalVirtual(&dwValue))
	{
		htiItem=InsertItem(_T("Total amount"),htiSubRoot);
		Integer.SetNumber(dwValue/1024);
		sValue=Integer.GetStringNumber(10,TRUE)+_T(" KB");
		VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
			sValue,0,NULL,clrValue));
	}

	if(m_SysInfo.GetFreeVirtual(&dwValue))
	{
		htiItem=InsertItem(_T("Free amount"),htiSubRoot);
		Integer.SetNumber(dwValue/1024);
		sValue=Integer.GetStringNumber(10,TRUE)+_T(" KB");
		VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
			sValue,0,NULL,clrValue));
	}
	////////////////////////////////////////////////

	// Resources
	int nValue=0;
	if(m_SysInfo.GetFreeSystemResources(&nValue,RT_SYSTEM))
	{
		htiSubRoot=InsertItem(_T("Resources"),htiRoot,-1,pFontSubRoot);

		htiItem=InsertItem(_T("Free System Resources"),htiSubRoot);
		sValue.Format(_T("%u %%"),nValue);
		VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
			sValue,0,NULL,clrValue));

		VERIFY(m_SysInfo.GetFreeSystemResources(&nValue,RT_GDI));
		htiItem=InsertItem(_T("Free GDI Resources"),htiSubRoot);
		sValue.Format(_T("%u %%"),nValue);
		VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
			sValue,0,NULL,clrValue));

		VERIFY(m_SysInfo.GetFreeSystemResources(&nValue,RT_USER));
		htiItem=InsertItem(_T("Free User Resources"),htiSubRoot);
		sValue.Format(_T("%u %%"),nValue);
		VERIFY(m_tree.SetSubItem(htiItem,1,OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
			sValue,0,NULL,clrValue));
	}
	////////////////////////////////////////////////

	//
	// The end of MEMORY topic
	///////////////////////////////////////////////////

	
	///////////////////////////////////////////////////
	// MODEM(S)
	//

	// Number of Modems
	int nNumModems;
	if(m_SysInfo.GetNumModems(&nNumModems) && nNumModems>0)
	{
		// topic will depend on the number of modems installed
		if(nNumModems>1)
		{
			htiRoot=InsertItem(_T("Modems"),NULL,6,pFontRoot,clrTopic);
			sValue.Format(_T("%u"),nNumModems);
			VERIFY(m_tree.SetSubItem(htiRoot,1,
				OX_SUBITEM_TEXT|(pFontRoot!=NULL ? OX_SUBITEM_FONT : 0),
				sValue,0,pFontRoot));
		}
		else
			htiRoot=InsertItem(_T("Modem"),NULL,6,pFontRoot,clrTopic);
		///////////////////////////////////////////////////////////////////

		// loop through all installed modems
		CArrayModemInfo arrModemInfo;
		VERIFY(m_SysInfo.GetModemInfo(&arrModemInfo));
		ASSERT(arrModemInfo.GetSize()==nNumModems);
		for(int nIndex=0; nIndex<nNumModems; nIndex++)
		{
			if(nNumModems>1)
			{
				sValue.Format(_T("Modem %d"),nIndex+1);
				htiSubRoot=InsertItem(sValue,htiRoot,-1,pFontSubRoot);
			}
			else
				htiSubRoot=htiRoot;

			MODEMINFO modemInfo=arrModemInfo.GetAt(nIndex);

			// Port
			htiItem=InsertItem(_T("Port"),htiSubRoot);
			sValue.Format(_T("COM%d"),modemInfo.nPort);
			VERIFY(m_tree.SetSubItem(htiItem,1,
				OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
				sValue,0,NULL,clrValue));

			// Description
			htiItem=InsertItem(_T("Description"),htiSubRoot);
			VERIFY(m_tree.SetSubItem(htiItem,1,
				OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
				modemInfo.sDriverDesc,0,NULL,clrValue));

			// Manufacturer
			htiItem=InsertItem(_T("Manufacturer"),htiSubRoot);
			VERIFY(m_tree.SetSubItem(htiItem,1,
				OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
				modemInfo.sManufacturer,0,NULL,clrValue));

			// Model
			htiItem=InsertItem(_T("Model"),htiSubRoot);
			VERIFY(m_tree.SetSubItem(htiItem,1,
				OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
				modemInfo.sModel,0,NULL,clrValue));
		}
		/////////////////////////////////////////////
	}

	//
	// The end of MODEM(S) topic
	///////////////////////////////////////////////////


	///////////////////////////////////////////////////
	// PRINTER(S)
	//
	if(m_bShowPrinters)
	{
		CStringArray arrPrinterName;
		if(m_SysInfo.GetAllPrintersName(arrPrinterName))
		{
			if(arrPrinterName.GetSize()>0)
			{
				CString sDefaultPrinterName;
				VERIFY(m_SysInfo.GetDefaultPrinterName(sDefaultPrinterName));

				sValue=_T("Printer");
				if(arrPrinterName.GetSize()>1)
					sValue=sValue+_T("s");
				htiRoot=InsertItem(sValue,NULL,7,pFontRoot,clrTopic);
				if(arrPrinterName.GetSize()>1)
				{
					sValue.Format(_T("%u"),arrPrinterName.GetSize());
					VERIFY(m_tree.SetSubItem(htiRoot,1,
						OX_SUBITEM_TEXT|(pFontRoot!=NULL ? OX_SUBITEM_FONT : 0),
						sValue,0,pFontRoot));
				}
				
				for(int nIndex=0; nIndex<arrPrinterName.GetSize(); nIndex++)
				{
					// printer status
					BOOL bLocalPrinter=TRUE;
					m_SysInfo.IsLocalPrinter(arrPrinterName[nIndex],
						&bLocalPrinter);
					///////////////////////////////////////

					// default printer
					BOOL bDefaultPrinter=(!sDefaultPrinterName.IsEmpty() & 
						arrPrinterName[nIndex]==sDefaultPrinterName);
					///////////////////////////////////////

					int nImage=-1;
					if(bLocalPrinter)
						nImage=(bDefaultPrinter ? 14 : 15);
					else
						nImage=(bDefaultPrinter ? 12 : 13);

					htiSubRoot=InsertItem(arrPrinterName[nIndex],
						htiRoot,nImage,pFontSubRoot);
					if(bDefaultPrinter)
						VERIFY(m_tree.SetSubItem(htiSubRoot,1,
							OX_SUBITEM_TEXT,_T("Default Printer"),0,NULL));

					// printer info
					LPPRINTER_INFO_2 lpPrinterInfo=NULL;
					if(m_SysInfo.GetPrinterInfo(arrPrinterName[nIndex],lpPrinterInfo))
					{
						ASSERT(lpPrinterInfo!=NULL);

						// server name
						if(lpPrinterInfo->pServerName!=NULL && 
							lstrlen(lpPrinterInfo->pServerName)>0)
						{
							htiItem=InsertItem(_T("Server Name"),htiSubRoot);
							VERIFY(m_tree.SetSubItem(htiItem,1,
								OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
								lpPrinterInfo->pServerName,0,NULL,clrValue));
						}
						///////////////////////////////////////

						// share name
						if((lpPrinterInfo->Attributes&PRINTER_ATTRIBUTE_SHARED)!=0 &&
							lpPrinterInfo->pShareName!=NULL && 
							lstrlen(lpPrinterInfo->pShareName)>0)
						{
							htiItem=InsertItem(_T("Share Name"),htiSubRoot);
							VERIFY(m_tree.SetSubItem(htiItem,1,
								OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
								lpPrinterInfo->pShareName,0,NULL,clrValue));
						}
						///////////////////////////////////////

						// port(s)
						if(lpPrinterInfo->pPortName!=NULL && 
							lstrlen(lpPrinterInfo->pPortName)>0)
						{
							if(_tcschr(lpPrinterInfo->pPortName,';')!=NULL)
								htiItem=InsertItem(_T("Ports"),htiSubRoot);
							else
								htiItem=InsertItem(_T("Port"),htiSubRoot);
							VERIFY(m_tree.SetSubItem(htiItem,1,
								OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
								lpPrinterInfo->pPortName,0,NULL,clrValue));
						}
						///////////////////////////////////////

						// driver name
						if(lpPrinterInfo->pDriverName!=NULL && 
							lstrlen(lpPrinterInfo->pDriverName)>0)
						{
							htiItem=InsertItem(_T("Driver Name"),htiSubRoot);
							VERIFY(m_tree.SetSubItem(htiItem,1,
								OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
								lpPrinterInfo->pDriverName,0,NULL,clrValue));
						}
						///////////////////////////////////////

						// brief description
						if(lpPrinterInfo->pComment!=NULL && 
							lstrlen(lpPrinterInfo->pComment)>0)
						{
							htiItem=InsertItem(_T("Brief Description"),htiSubRoot);
							VERIFY(m_tree.SetSubItem(htiItem,1,
								OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
								lpPrinterInfo->pComment,0,NULL,clrValue));
						}
						///////////////////////////////////////

						// physical location
						if(lpPrinterInfo->pLocation!=NULL && 
							lstrlen(lpPrinterInfo->pLocation)>0)
						{
							htiItem=InsertItem(_T("Physical Location"),htiSubRoot);
							VERIFY(m_tree.SetSubItem(htiItem,1,
								OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
								lpPrinterInfo->pLocation,0,NULL,clrValue));
						}
						///////////////////////////////////////

						// print processor
						if(lpPrinterInfo->pPrintProcessor!=NULL && 
							lstrlen(lpPrinterInfo->pPrintProcessor)>0)
						{
							htiItem=InsertItem(_T("Print Processor"),htiSubRoot);
							VERIFY(m_tree.SetSubItem(htiItem,1,
								OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
								lpPrinterInfo->pPrintProcessor,0,NULL,clrValue));
						}
						///////////////////////////////////////

						// average number of pages per minute that have been printed 
						// on the printer
						if(lpPrinterInfo->AveragePPM>0)
						{
							htiItem=InsertItem(_T("Average number of pages"),
								htiSubRoot);
							sValue.Format(_T("%u per minute"),
								lpPrinterInfo->AveragePPM);
							VERIFY(m_tree.SetSubItem(htiItem,1,
								OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
								sValue,0,NULL,clrValue));
						}
						///////////////////////////////////////

						// printer IP address
						if(lpPrinterInfo->pServerName!=NULL && 
							lstrlen(lpPrinterInfo->pServerName)>0)
						{
							CString sHostName=lpPrinterInfo->pServerName;
							if(sHostName.Left(2)==_T("\\\\"))
								sHostName=sHostName.Mid(2);
							if(m_SysInfo.GetPrimaryIPAddress(&sValue,sHostName))
							{
								htiItem=InsertItem(_T("Primary IP Address"),
									htiSubRoot);
								VERIFY(m_tree.SetSubItem(htiItem,1,
									OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
									sValue,0,NULL,clrValue));
							}
						}
						///////////////////////////////////////

						// device and environment settings
						if(lpPrinterInfo->pDevMode!=NULL)
						{
							htiSubRoot=InsertItem(_T("Environment"),
								htiSubRoot,-1,pFontSubRoot);

							// page orientation 
							if((lpPrinterInfo->pDevMode->dmFields&DM_ORIENTATION)!=0)
							{
								htiItem=InsertItem(_T("Orientation"),htiSubRoot);
								if(lpPrinterInfo->pDevMode->dmOrientation==
									DMORIENT_PORTRAIT)
									sValue=_T("Portrait");
								else if(lpPrinterInfo->pDevMode->dmOrientation==
									DMORIENT_LANDSCAPE)
									sValue=_T("Landscape");
								else 
									ASSERT(FALSE);

								VERIFY(m_tree.SetSubItem(htiItem,1,
									OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
									sValue,0,NULL,clrValue));
							}
							///////////////////////////////////////

							// paper size 
							if((lpPrinterInfo->pDevMode->dmFields&DM_PAPERSIZE)!=0 &&
								lpPrinterInfo->pDevMode->dmPaperSize!=0)
							{
								htiItem=InsertItem(_T("Paper size"),htiSubRoot);

								switch(lpPrinterInfo->pDevMode->dmPaperSize)
								{
								case DMPAPER_LETTER:
									sValue=_T("Letter, 8 1/2- by 11-inches");
									break;
								case DMPAPER_LEGAL:
									sValue=_T("Legal, 8 1/2- by 14-inches");
									break;
								case DMPAPER_A4:
									sValue=_T("A4 Sheet, 210- by 297-millimeters");
									break;
								case DMPAPER_CSHEET:
									sValue=_T("C Sheet, 17- by 22-inches");
									break;
								case DMPAPER_DSHEET:
									sValue=_T("D Sheet, 22- by 34-inches");
									break;
								case DMPAPER_ESHEET:
									sValue=_T("E Sheet, 34- by 44-inches");
									break;
								case DMPAPER_LETTERSMALL:
									sValue=_T("Letter Small, 8 1/2- by 11-inches");
									break;
								case DMPAPER_TABLOID:
									sValue=_T("Tabloid, 11- by 17-inches");
									break;
								case DMPAPER_LEDGER:
									sValue=_T("Ledger, 17- by 11-inches");
									break;
								case DMPAPER_STATEMENT:
									sValue=_T("Statement, 5 1/2- by 8 1/2-inches");
									break;
								case DMPAPER_EXECUTIVE:
									sValue=_T("Executive, 7 1/4- by 10 1/2-inches");
									break;
								case DMPAPER_A3:
									sValue=_T("A3 sheet, 297- by 420-millimeters");
									break;
								case DMPAPER_A4SMALL:
									sValue=_T("A4 small sheet, 210- by 297-millimeters");
									break;
								case DMPAPER_A5:
									sValue=_T("A5 sheet, 148- by 210-millimeters");
									break;
								case DMPAPER_B4:
									sValue=_T("B4 sheet, 250- by 354-millimeters");
									break;
								case DMPAPER_B5:
									sValue=_T("B5 sheet, 182- by 257-millimeter paper");
									break;
								case DMPAPER_FOLIO:
									sValue=_T("Folio, 8 1/2- by 13-inch paper");
									break;
								case DMPAPER_QUARTO:
									sValue=_T("Quarto, 215- by 275-millimeter paper");
									break;
								case DMPAPER_10X14:
									sValue=_T("10- by 14-inch sheet");
									break;
								case DMPAPER_11X17:
									sValue=_T("11- by 17-inch sheet");
									break;
								case DMPAPER_NOTE:
									sValue=_T("Note, 8 1/2- by 11-inches");
									break;
								case DMPAPER_ENV_9:
									sValue=_T("#9 Envelope, 3 7/8- by 8 7/8-inches");
									break;
								case DMPAPER_ENV_10:
									sValue=_T("#10 Envelope, 4 1/8- by 9 1/2-inches");
									break;
								case DMPAPER_ENV_11:
									sValue=_T("#11 Envelope, 4 1/2- by 10 3/8-inches");
									break;
								case DMPAPER_ENV_12:
									sValue=_T("#12 Envelope, 4 3/4- by 11-inches");
									break;
								case DMPAPER_ENV_14:
									sValue=_T("#14 Envelope, 5- by 11 1/2-inches");
									break;
								case DMPAPER_ENV_DL:
									sValue=_T("DL Envelope");
									break;
								case DMPAPER_ENV_C5:
									sValue=_T("C5 Envelope, 162- by 229-millimeters");
									break;
								case DMPAPER_ENV_C3:
									sValue=_T("C3 Envelope, 324- by 458-millimeters");
									break;
								case DMPAPER_ENV_C4:
									sValue=_T("C4 Envelope, 229- by 324-millimeters");
									break;
								case DMPAPER_ENV_C6:
									sValue=_T("C6 Envelope, 114- by 162-millimeters");
									break;
								case DMPAPER_ENV_C65:
									sValue=_T("C65 Envelope, 114- by 229-millimeters");
									break;
								case DMPAPER_ENV_B4:
									sValue=_T("B4 Envelope, 250- by 353-millimeters");
									break;
								case DMPAPER_ENV_B5:
									sValue=_T("B5 Envelope, 176- by 250-millimeters");
									break;
								case DMPAPER_ENV_B6:
									sValue=_T("B6 Envelope, 176- by 125-millimeters");
									break;
								case DMPAPER_ENV_ITALY:
									sValue=_T("Italy Envelope, 110- by 230-millimeters");
									break;
								case DMPAPER_ENV_MONARCH:
									sValue=_T("Monarch Envelope, 3 7/8- by 7 1/2-inches");
									break;
								case DMPAPER_ENV_PERSONAL:
									sValue=_T("6 3/4 Envelope, 3 5/8- by 6 1/2-inches");
									break;
								case DMPAPER_FANFOLD_US:
									sValue=_T("US Std Fanfold, 14 7/8- by 11-inches");
									break;
								case DMPAPER_FANFOLD_STD_GERMAN:
									sValue=_T("German Std Fanfold, 8 1/2- by 12-inches");
									break;
								case DMPAPER_FANFOLD_LGL_GERMAN:
									sValue=_T("German Legal Fanfold, 8 1/2- by 13-inches");
									break;
								default:
									sValue=_T("Unknown");
								}

								VERIFY(m_tree.SetSubItem(htiItem,1,
									OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
									sValue,0,NULL,clrValue));
							}
							else if((lpPrinterInfo->pDevMode->dmFields&
								DM_PAPERLENGTH)!=0 && 
								(lpPrinterInfo->pDevMode->dmFields&
								DM_PAPERWIDTH)!=0)
							{
								htiItem=InsertItem(_T("Paper size"),htiSubRoot);

								sValue.Format(_T("%u- by %u-millimeters"),
									lpPrinterInfo->pDevMode->dmPaperWidth,
									lpPrinterInfo->pDevMode->dmPaperLength);
								VERIFY(m_tree.SetSubItem(htiItem,1,
									OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
									sValue,0,NULL,clrValue));
							}
							///////////////////////////////////////

							// printer quality 
							if((lpPrinterInfo->pDevMode->dmFields&
								DM_PRINTQUALITY)!=0 && 
								lpPrinterInfo->pDevMode->dmPrintQuality<=0)
							{
								htiItem=InsertItem(_T("Print Quality"),htiSubRoot);

								switch(lpPrinterInfo->pDevMode->dmPrintQuality)
								{
								case DMRES_HIGH:
									sValue=_T("High");
									break;
								case DMRES_MEDIUM:
									sValue=_T("Medium");
									break;
								case DMRES_LOW:
									sValue=_T("Low");
									break;
								case DMRES_DRAFT:
									sValue=_T("Draft");
									break;
								default:
									sValue=_T("Unknown");
								}

								VERIFY(m_tree.SetSubItem(htiItem,1,
									OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
									sValue,0,NULL,clrValue));
							}
							///////////////////////////////////////

							// printer resolution 
							if(lpPrinterInfo->pDevMode->dmPrintQuality>0 && 
								(lpPrinterInfo->pDevMode->dmFields&
								DM_YRESOLUTION)!=0)
							{
								htiItem=InsertItem(_T("Print Resolution"),htiSubRoot);

								sValue.Format(_T("%u x %u DPI"),
									lpPrinterInfo->pDevMode->dmPrintQuality,
									lpPrinterInfo->pDevMode->dmYResolution);

								VERIFY(m_tree.SetSubItem(htiItem,1,
									OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
									sValue,0,NULL,clrValue));
							}
							///////////////////////////////////////

						}
						///////////////////////////////////////

						// we have to free memory ourselves
						::GlobalFree(lpPrinterInfo); 
					}
					///////////////////////////////////////

				}
			}
		}
	}

	//
	// The end of PRINTER(S) topic
	///////////////////////////////////////////////////

	ExpandTree((m_nExpandType==0 ? m_nExpandLevel : -1));

	m_tree.SetFocus();
	m_tree.SelectItem(htiSelectItem);

	m_tree.SetRedraw(TRUE);
}


void CSysInfoDialog::ExpandTree(int nExpandLevel/*=-1*/,
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

HTREEITEM CSysInfoDialog::InsertItem(CString sItem, HTREEITEM htiParent/*=NULL*/, 
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


void CSysInfoDialog::ShowControls()
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

void CSysInfoDialog::OnRadioExpandall() 
{
	// TODO: Add your control notification handler code here
	
	ShowControls();
}

void CSysInfoDialog::OnRadioExpandlevel() 
{
	// TODO: Add your control notification handler code here
	
	ShowControls();
}
