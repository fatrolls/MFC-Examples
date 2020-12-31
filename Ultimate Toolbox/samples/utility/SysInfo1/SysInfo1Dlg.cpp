// SysInfo1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "utsampleabout.h"
#include "SysInfo1.h"
#include "SysInfo1Dlg.h"

#include "UTBStrOp.h"
#include "UTB64Bit.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSysInfo1Dlg dialog

CSysInfo1Dlg::CSysInfo1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSysInfo1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSysInfo1Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSysInfo1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSysInfo1Dlg)
	DDX_Control(pDX, IDC_TREE1, m_InfoTree);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSysInfo1Dlg, CDialog)
	//{{AFX_MSG_MAP(CSysInfo1Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSysInfo1Dlg message handlers

BOOL CSysInfo1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_hRootItem = NULL;
	m_ilFolder.Create(IDB_IMAGELIST, 16, 0, RGB(255,0,255));
	m_InfoTree.SetImageList(&m_ilFolder, TVSIL_NORMAL); 

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	GetSystemInformation() ;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSysInfo1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CUTSampleAboutDlg dlgAbout(IDR_MAINFRAME,ID_DESCRIPTION_FILE);
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSysInfo1Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSysInfo1Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void CSysInfo1Dlg::GetSystemInformation()
{
	CString	theBuffer ;
	int		xRes, yRes ;
	DWORD	dwValue ;
	CString	theString ;
	HTREEITEM hTypeItem = 0;
	
		

	// ***************
	// Windows version
	// ***************
	DWORD	dwPlatform, dwMajor, dwMinor ;
	CString	theVersion ;
	HTREEITEM  after = 0;
	if (m_oxSysInfo.GetWindowsVersion(&dwPlatform, &dwMajor, &dwMinor))
	{
		theBuffer.Format(_T(" WINDOWS "));
			hTypeItem = m_InfoTree.InsertItem(theBuffer, m_hRootItem);
				m_InfoTree.SetItemImage(hTypeItem, 0,1);
		//

		if (dwPlatform == VER_PLATFORM_WIN32s)
			theVersion = _T("Windows 3.1");
		else
		if (dwPlatform == VER_PLATFORM_WIN32_WINDOWS)
		{
			if (dwMajor == 4)
			{
				switch (dwMinor)
				{
				case 0:
					{
						theVersion = _T("Windows 95");
						// if szCSDVersion[1] is C or B, it's OSR2, but we're not getting that info back
					}
					break;
				case 10:
						theVersion = _T("Windows 98");
						// if szCSDVersion[1] is A, it's SE, but one again, we don't get that back
						break;
				case 90:
					theVersion = _T("Windows ME");
					break;
	

				}
			}
			else
				theVersion = _T("Unknown version");
		}
		else
		if (dwPlatform == VER_PLATFORM_WIN32_NT)
		{
			if (dwMajor == 5)
			{
				switch (dwMinor)
				{
				case 2:
					theVersion=_T("Windows Server 2003");
					break;
				case 1:
					theVersion = _T("Windows XP");
					break;
				case 0:
					theVersion = _T("Windows 2000");
					break;
				default:
					theVersion = _T("Windows Vista");
				}
			}
			else
				theVersion = _T("Windows NT");
		}
		else
			theVersion = _T("Unknown");

		theBuffer.Format(_T("Windows Version: %s, %u.%u"), theVersion, dwMajor, dwMinor) ;
		after = m_InfoTree.InsertItem(theBuffer, hTypeItem);
		m_InfoTree.SetItemImage(after, 2,2);

	}

	// **************
	// Processor Type
	// **************
	DWORD	dwProcessorType ;

	if (m_oxSysInfo.GetProcessorType(&dwProcessorType))
	{
		theBuffer.Format(_T(" PROCESSOR ")) ;
			hTypeItem = m_InfoTree.InsertItem(theBuffer, m_hRootItem);
				m_InfoTree.SetItemImage(hTypeItem, 11,11);
			////

		theBuffer = _T("Processor: ");
		
		switch(dwProcessorType)
		{
			case PROCESSOR_INTEL_386:
				theBuffer += _T("Intel 386");
				break ;

			case PROCESSOR_INTEL_486:
				theBuffer += _T("Intel 486");
				break ;

			case PROCESSOR_INTEL_PENTIUM:
				theBuffer += _T("Intel Pentium");
				break ;

			case PROCESSOR_MIPSR4000:
				theBuffer += _T("MIPS R4000");
				break ;

			case PROCESSOR_ALPHA21064:
				theBuffer += _T("Alpha 21064");
				break ;

			case PROCESSOR_ALPHA21066:
				theBuffer += _T("Alpha 21066");
				break ;

			case PROCESSOR_ALPHA21164:
				theBuffer += _T("Alpha 21164");
				break ;

			case PROCESSOR_PPC601:
				theBuffer += _T("PowerPC 601");
				break ;

			case PROCESSOR_PPC603:
				theBuffer += _T("PowerPC 603");
				break ;

			case PROCESSOR_PPC604:
				theBuffer += _T("PowerPC 604");
				break ;

			case PROCESSOR_PPC603PLUS:
				theBuffer += _T("PowerPC 603+");
				break ;

			case PROCESSOR_PPC604PLUS:
				theBuffer += _T("PowerPC 604+");
				break ;

			case PROCESSOR_PPC620:
				theBuffer += _T("PowerPC 620");
				break ;

			default:
				theBuffer += _T("UNKNOWN");
				break ;
		}
			after = m_InfoTree.InsertItem(theBuffer, hTypeItem);
		m_InfoTree.SetItemData(after, TVI_DATA_FOLDER);
		m_InfoTree.SetItemImage(after, 3,3);
	}

	// **************
	// Number of CPUs
	// **************
	int		iNumProcessors ;
	if (m_oxSysInfo.GetNumProcessors(&iNumProcessors))
	{
		theBuffer.Format(_T("Number of CPUs: %d"), iNumProcessors) ;
		after = m_InfoTree.InsertItem(theBuffer, hTypeItem);
		m_InfoTree.SetItemData(after, TVI_DATA_FOLDER);
		m_InfoTree.SetItemImage(after, 3,3);
	}

	theBuffer.Format(_T(" COMPUTER ")) ;
		hTypeItem = m_InfoTree.InsertItem(theBuffer, m_hRootItem);
			m_InfoTree.SetItemImage(hTypeItem, 6,6);
		//

	// *************
	// Computer name
	// *************
	if (m_oxSysInfo.GetComputerName(&theString))
	{
		theBuffer.Format(_T("Computer Name: %s"), theString) ;
		after = m_InfoTree.InsertItem(theBuffer, hTypeItem);
		m_InfoTree.SetItemData(after, TVI_DATA_FOLDER);
	m_InfoTree.SetItemImage(after, 3,3);

	}

	// *********
	// User & Domain name
	// *********
	if (m_oxSysInfo.GetUserName(&theString))
		{
		theBuffer.Format(_T("User Name: %s"), theString) ;
				hTypeItem = m_InfoTree.InsertItem(theBuffer, m_hRootItem);
				m_InfoTree.SetItemImage(hTypeItem, 9,9);
	}

	CString sDomain;
	if (m_oxSysInfo.GetUserAndDomainName(&theString, &sDomain))
	{
		theBuffer.Format(_T("User Name: %s"), theString) ;
				hTypeItem = m_InfoTree.InsertItem(theBuffer, m_hRootItem);
					m_InfoTree.SetItemImage(hTypeItem, 9,9);
		theBuffer.Format(_T("Domain Name: %s"), sDomain) ;
				hTypeItem = m_InfoTree.InsertItem(theBuffer, m_hRootItem);
				m_InfoTree.SetItemImage(hTypeItem, 9,9);
	}

	// **********
	// IP Address
	// **********

	CStringArray IPArray;
	if (m_oxSysInfo.GetListIPAddresses(&IPArray))
		{
		for (int j = 0; j < IPArray.GetSize(); j++)
			{
			theBuffer.Format(_T("IP Address(%d): %s"), j, IPArray[j]);
					hTypeItem = m_InfoTree.InsertItem(theBuffer, m_hRootItem);
						m_InfoTree.SetItemImage(hTypeItem, 5,5);
			}
		}


	theBuffer.Format(_T(" DIRECTORIES ")) ;
		hTypeItem = m_InfoTree.InsertItem(theBuffer, m_hRootItem);
		m_InfoTree.SetItemImage(hTypeItem, 8,8);
		//

	// *****************
	// Windows directory
	// *****************
	if (m_oxSysInfo.GetWindowsDir(&theString))
	{
		theBuffer.Format(_T("Windows Directory: %s"), theString) ;
				after = m_InfoTree.InsertItem(theBuffer,hTypeItem );
					m_InfoTree.SetItemImage(after, 6,6);
	}

	// ****************
	// System directory
	// ****************
	if (m_oxSysInfo.GetSystemDir(&theString))
	{
		theBuffer.Format(_T("System Directory: %s"), theString) ;
				after = m_InfoTree.InsertItem(theBuffer, hTypeItem);
				m_InfoTree.SetItemImage(after, 6,6);
	}

	// *******************
	// Temporary directory
	// *******************
	if (m_oxSysInfo.GetTempDir(&theString))
	{
		theBuffer.Format(_T("Temp Directory: %s"), theString) ;
				after = m_InfoTree.InsertItem(theBuffer, hTypeItem);
				m_InfoTree.SetItemImage(after, 6,6);
	}

	// ****************
	// Disk information
	// ****************

	theBuffer.Format(_T(" DISK INFORMATION ")) ;
		hTypeItem = m_InfoTree.InsertItem(theBuffer, m_hRootItem);
		m_InfoTree.SetItemImage(after, 6,6);
	//

	int		i, iDiskType ;
	CString	theFileSysType ;
	CString	theVolName ;
	DWORDLONG	dwTotalSpace, dwFreeSpace;
	DWORD	dwVolSer ;

	for(i=0;i<26;i++)
	{
		if (m_oxSysInfo.GetDriveTypeInfo(i, &theFileSysType, &iDiskType))
		{
			if (m_oxSysInfo.GetDriveVolumeInfo(i, &theVolName, &dwVolSer, &dwTotalSpace, &dwFreeSpace))
			{
				if (iDiskType == DRIVE_FIXED)
				{
					theBuffer.Format(_T("Drive %c: Fixed Disk"), i + 65) ;
					after = m_InfoTree.InsertItem(theBuffer, hTypeItem);
					m_InfoTree.SetItemData(after, TVI_DATA_FOLDER);
					//m_InfoTree.SetItemImage(after, 3,3);
					theBuffer.Format(_T("  Volume Name: %s (%s)"), theVolName, 
						theFileSysType) ;
					after = m_InfoTree.InsertItem(theBuffer, hTypeItem);
						m_InfoTree.SetItemImage(after, 3,3);
					m_InfoTree.SetItemData(after, TVI_DATA_FOLDER);
					theBuffer.Format(_T("  Volume Serial: %u"), dwVolSer) ;
					after = m_InfoTree.InsertItem(theBuffer, hTypeItem);
					m_InfoTree.SetItemImage(after, 3,3);
					m_InfoTree.SetItemData(after, TVI_DATA_FOLDER);

					LPTSTR psBuffer=theBuffer.GetBuffer(256);
					UTBStr::stprintf(psBuffer, 256, _T("  Total Space: %I64d "), dwTotalSpace) ;
					theBuffer.ReleaseBuffer();
					after = m_InfoTree.InsertItem(theBuffer, hTypeItem);
					m_InfoTree.SetItemData(after, TVI_DATA_FOLDER);
					m_InfoTree.SetItemImage(after, 3,3);

					psBuffer=theBuffer.GetBuffer(256);
					UTBStr::stprintf(psBuffer, 256,_T("  Total Space: %I64d "), dwFreeSpace) ;
					theBuffer.ReleaseBuffer();
					after = m_InfoTree.InsertItem(theBuffer, hTypeItem);
					m_InfoTree.SetItemData(after, TVI_DATA_FOLDER);
					m_InfoTree.SetItemImage(after, 3,3);
				}
				else
				if (iDiskType == DRIVE_CDROM)
				{
					theBuffer.Format(_T("Drive %c: CD-ROM"), i + 65) ;
					after = m_InfoTree.InsertItem(theBuffer, hTypeItem);
					m_InfoTree.SetItemData(after, TVI_DATA_FOLDER);
					
					theBuffer.Format(_T("  Volume Name: %s (%s)"), theVolName, theFileSysType) ;							hTypeItem = m_InfoTree.InsertItem(theBuffer, m_hRootItem);
					after = m_InfoTree.InsertItem(theBuffer, hTypeItem);
					m_InfoTree.SetItemData(after, TVI_DATA_FOLDER);
					m_InfoTree.SetItemImage(after, 3,3);

				}
				else
				if (iDiskType == DRIVE_REMOTE)
				{
					theBuffer.Format(_T("Drive %c: Network Disk"), i + 65) ;
						after = m_InfoTree.InsertItem(theBuffer, hTypeItem);
							m_InfoTree.SetItemData(after, TVI_DATA_FOLDER);

					theBuffer.Format(_T("  Volume Name: %s (%s)"), theVolName, theFileSysType) ;
						after = m_InfoTree.InsertItem(theBuffer, hTypeItem);
					m_InfoTree.SetItemData(after, TVI_DATA_FOLDER);
						m_InfoTree.SetItemImage(after, 3,3);

				}
			}
		}
	}

	theBuffer.Format(_T(" DISPLAY ")) ;
		hTypeItem = m_InfoTree.InsertItem(theBuffer, m_hRootItem);
		//

	// ******************
	// Display resolution
	// ******************
	if (m_oxSysInfo.GetDisplayResolution(&xRes, &yRes))
	{
		theBuffer.Format(_T("Display Resolution: %d x %d"), xRes, yRes) ;
			after = m_InfoTree.InsertItem(theBuffer, hTypeItem);
		m_InfoTree.SetItemData(after, TVI_DATA_FOLDER);
			m_InfoTree.SetItemImage(after, 3,3);

	}

	// **************
	// Display colors
	// **************
	int		iNumBits ;
	DWORDLONG	dwNumColors;

	if (m_oxSysInfo.GetDisplayNumColors(&dwNumColors, &iNumBits))
	{
		LPTSTR psBuffer=theBuffer.GetBuffer(256);
		UTBStr::stprintf(psBuffer, 256,_T("Current Display Colors: %I64d (%d bits)"), 
			dwNumColors, iNumBits) ;
		theBuffer.ReleaseBuffer();
		after = m_InfoTree.InsertItem(theBuffer, hTypeItem);
		m_InfoTree.SetItemData(after, TVI_DATA_FOLDER);
		m_InfoTree.SetItemImage(after, 3,3);

	}

	// ******
	// Memory
	// ******

	theBuffer.Format(_T(" MEMORY ")) ;
		hTypeItem = m_InfoTree.InsertItem(theBuffer, m_hRootItem);
		//

	if (m_oxSysInfo.GetTotalPhysicalMemory(&dwValue))
	{
		theBuffer.Format(_T("Total Physical RAM: %u bytes"), dwValue) ;
			after = m_InfoTree.InsertItem(theBuffer, hTypeItem);
		m_InfoTree.SetItemData(after, TVI_DATA_FOLDER);
			m_InfoTree.SetItemImage(after, 3,3);

	}

	if (m_oxSysInfo.GetFreePhysicalMemory(&dwValue))
	{
		theBuffer.Format(_T("Free Physical RAM: %u bytes"), dwValue) ;
			after = m_InfoTree.InsertItem(theBuffer, hTypeItem);
		m_InfoTree.SetItemData(after, TVI_DATA_FOLDER);
	m_InfoTree.SetItemImage(after, 3,3);

	}

	if (m_oxSysInfo.GetTotalPageFile(&dwValue))
	{
		theBuffer.Format(_T("Total Page File: %u bytes"), dwValue) ;
			after = m_InfoTree.InsertItem(theBuffer, hTypeItem);
		m_InfoTree.SetItemData(after, TVI_DATA_FOLDER);
	m_InfoTree.SetItemImage(after, 3,3);

	}

	if (m_oxSysInfo.GetFreePageFile(&dwValue))
	{
		theBuffer.Format(_T("Free Page File: %u bytes"), dwValue) ;
			after = m_InfoTree.InsertItem(theBuffer, hTypeItem);
		m_InfoTree.SetItemData(after, TVI_DATA_FOLDER);
	m_InfoTree.SetItemImage(after, 3,3);

	}

	if (m_oxSysInfo.GetTotalVirtual(&dwValue))
	{
		theBuffer.Format(_T("Total Virtual Memory: %u bytes"), dwValue) ;
		after = m_InfoTree.InsertItem(theBuffer, hTypeItem);
		m_InfoTree.SetItemData(after, TVI_DATA_FOLDER);
	m_InfoTree.SetItemImage(after, 3,3);

	}

	if (m_oxSysInfo.GetFreeVirtual(&dwValue))
	{
		theBuffer.Format(_T("Free Virtual Memory: %u bytes"), dwValue) ;
			after = m_InfoTree.InsertItem(theBuffer, hTypeItem);
		m_InfoTree.SetItemData(after, (DWORD)3);
	m_InfoTree.SetItemImage(after, 3,3);

	}

}
