//=======================================
// PSAPI Working Set Demo - Matt Pietrek 1996
// Microsoft Systems Journal, November 1996
// FILE: "PSAPIWorkingSetDemo.CPP"
//=======================================
#define  WIN32_LEAN_AND_MEAN
#pragma comment ( linker,"/ALIGN:4096" )

#include <windows.h>
#include <stdlib.h>
#include <lmerr.h>
#include <Commdlg.h>
//#include <commctrl.h>

ULONGLONG GetPhysicalAddress(ULONG vAddress);
long baseaddress=0;
#define BUFSIZE 4096
DWORD g_WorkingSetPages[ 1024 * 128 ];
unsigned char dim[65536];
char * m_strAddr;
char * m_strContent;
char * m_strLength;

BOOL InitPhysicalMemory();
BOOL ReadPhysicalMemory(PVOID buffer, ULONGLONG address, DWORD length);
void ExitPhysicalMemory();
void Read(HWND hDlg);
void Save(HWND hDlg);

typedef LONG NTSTATUS;

typedef struct _UNICODE_STRING
{
    USHORT Length;
    USHORT MaximumLength;
    PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef enum _SECTION_INHERIT
{
    ViewShare = 1,
	ViewUnmap = 2
} SECTION_INHERIT, *PSECTION_INHERIT;

typedef struct _OBJECT_ATTRIBUTES
{
    ULONG Length;
    HANDLE RootDirectory;
    PUNICODE_STRING ObjectName;
    ULONG Attributes;
    PVOID SecurityDescriptor;
    PVOID SecurityQualityOfService;
} OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;

#define InitializeObjectAttributes( p, n, a, r, s ) { \
	(p)->Length = sizeof( OBJECT_ATTRIBUTES ); \
	(p)->RootDirectory = r; \
	(p)->Attributes = a; \
	(p)->ObjectName = n; \
	(p)->SecurityDescriptor = s; \
	(p)->SecurityQualityOfService = NULL; \
}

// Interesting functions in NTDLL
typedef NTSTATUS (WINAPI *ZwOpenSectionProc)
(
 PHANDLE SectionHandle, 
 DWORD DesiredAccess, 
 POBJECT_ATTRIBUTES ObjectAttributes
 );

typedef NTSTATUS (WINAPI *ZwMapViewOfSectionProc)
(
 HANDLE SectionHandle,
 HANDLE ProcessHandle,
 PVOID *BaseAddress,
 ULONG ZeroBits,
 ULONG CommitSize,
 PLARGE_INTEGER SectionOffset,
 PULONG ViewSize,
 SECTION_INHERIT InheritDisposition,
 ULONG AllocationType,
 ULONG Protect
 );

typedef NTSTATUS (WINAPI *ZwUnmapViewOfSectionProc)
(
 HANDLE ProcessHandle, 
 PVOID BaseAddress
 );

typedef VOID (WINAPI *RtlInitUnicodeStringProc)
(
 IN OUT PUNICODE_STRING DestinationString,
 IN PCWSTR SourceString
 );

// Global variables
static HMODULE hModule = NULL;
static HANDLE hPhysicalMemory = NULL;
static ZwOpenSectionProc ZwOpenSection;
static ZwMapViewOfSectionProc ZwMapViewOfSection;
static ZwUnmapViewOfSectionProc ZwUnmapViewOfSection;
static RtlInitUnicodeStringProc RtlInitUnicodeString;

void Read(HWND hDlg);
void Save(HWND hDlg);

int num=0;
PVOID pAddr=0;
unsigned char szFile[MAX_PATH];
BOOL SearchMark(BOOL Encrypted,DWORD ProcessId);
unsigned char * tData;
unsigned char * ReadData;

void DisplayErrorText( DWORD dwLastError );

#pragma hdrstop
#include "psapi.h"
#include "resource.h"

BOOL StartWorkingSetDelta( DWORD pid );
void EndWorkingSetDelta( HWND hWndOwner );
void printtofile(HWND hDlg);
char szPrtBuffer[102400];

BOOL GetModuleNameAndSectionInfo(
        HANDLE  hProcess,           // IN
        PVOID   p,                  // IN
        PSTR    pszModuleName,      // OUT
        DWORD   cbModuleName,       // IN
        PSTR    pszSectionName,     // OUT
        DWORD   cbSectionName,      // IN
        PDWORD  puSectionNum );     // OUT

// Helper function prototypes
DWORD GetDlgSelectedItemData( HWND hDlg, int ctlID );
BOOL CALLBACK PSAPIWorkingSetDemDlgProc( HWND, UINT, WPARAM, LPARAM );

DWORD g_PageSize = 0x1000;  // We can adjust later for Alpha

void AddProcessToList( HWND hWnd, DWORD processID )
{
    //
    // Adds the process name and ID to the top list, then calls
    // AddProcessDetails to fill in the details about the process
    //
	
    char szProcessName[MAX_PATH] = "未知";
    char szItemString[MAX_PATH+64];
    
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
	
    if ( hProcess )     // Get the name of the executable module
    {
        HMODULE hMod;
        DWORD cbNeeded;
		
        // Get just the first module in the process.  This appears to
        // always be the executable file.    
        if ( EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded) )
        {
            GetModuleBaseName( hProcess, hMod, szProcessName,sizeof(szProcessName));
        }
    }
	
    // Format the description string for this process
    wsprintf( szItemString, "%s (ID:%u)", szProcessName, processID );
	
    // Add the string to the process listbox, and associate the PID with it
    long lbIndex = SendMessage( hWnd, LB_ADDSTRING, 0, (LPARAM) szItemString );
	SendMessage( hWnd, LB_SETITEMDATA, lbIndex, processID );
	
    if ( hProcess )
        CloseHandle( hProcess );
}

void UpdateProcessList(HWND hDlg)
{
    //
    // Clears the listview, obtains a list of process IDs, and shows them
    //
    
    // Get the process list HWND, then clear it
    HWND hWnd = GetDlgItem( hDlg, IDC_LB_PROCESS_LIST );
    SendMessage( hWnd, LB_RESETCONTENT, 0, 0 );

	
    // Get the list of process IDs
    DWORD aProcesses[1024], cbNeeded;
    if (!EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded)) return;
    
    // Calculate how many process IDs were returned
    DWORD cProcesses = cbNeeded / sizeof(DWORD);
	
    // Spit out the information for each ID
    for ( unsigned i = 0; i < cProcesses; i++ ) AddProcessToList( hWnd, aProcesses[i] );
}

int CompareDWORDs( const void * a, const void * b )
{
    if ( *(PDWORD)a == *(PDWORD)b ) return 0;
    return *(PDWORD)a > *(PDWORD)b ? 1 : -1;
}

// Declare a big array of DWORDs to hold the working set information returned
// by QueryWorkingSet().  Since this memory isn't initialized, it doesn't
// affect the size of our executable.
//DWORD g_WorkingSetPages[ 1024 * 128 ];

void AddWorkingSetInfo( HWND hDlg, DWORD processID )
{
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE, processID);
	
    if ( !hProcess ) return;
	
    HWND hWndLb = GetDlgItem( hDlg, IDC_LB_WORKING_SET_DETAILS );
	
    __try
    {
        SendMessage( hWndLb, WM_SETREDRAW, FALSE, 0 );  // Disable LB updating
		
        char szBuffer[MAX_PATH * 4];
		memset(szPrtBuffer,0,10240);
        if (!QueryWorkingSet(hProcess, g_WorkingSetPages,sizeof(g_WorkingSetPages))) __leave;
		
        DWORD cPages = g_WorkingSetPages[0];    // First DWORD is page count
        DWORD cPrivatePages = 0;
        DWORD cSharedPages = 0;
        DWORD cPageTablePages = 0;
		
        qsort( &g_WorkingSetPages[1], cPages, sizeof(DWORD), CompareDWORDs );
		
        for ( DWORD i = 1; i <= cPages; i++ )
        {
            DWORD pageAddr = g_WorkingSetPages[i] & 0xFFFFF000;
            DWORD pageFlags = g_WorkingSetPages[i] & 0x00000FFF;
            DWORD thisPageAddr, nextPageAddr, nextPageFlags;
            DWORD cPagesThisRange = 0;
			
            // Loop through all subseqent pages that are contiguous in
            // memory and have the same attributes
            while ( i <= cPages )
            {
                cPagesThisRange++;
				
                if ( i == cPages )  // Break out if its the last page
                    break;
				
                thisPageAddr = g_WorkingSetPages[i] & 0xFFFFF000;
                nextPageAddr = g_WorkingSetPages[i+1] & 0xFFFFF000;
                nextPageFlags = g_WorkingSetPages[i+1] & 0x00000FFF;
				
                if ((nextPageAddr == (thisPageAddr + g_PageSize)) && (nextPageFlags == pageFlags))
                {
					i++;       // Keep going
                }
                else            // Non-contiguous page or different flags
                    break;
            }
			
            // Is it a page from outside of the "page table" region???
            if ( (pageAddr < 0xC0000000) || (pageAddr > 0xE0000000) )
            {
                if ( pageFlags & 0x100 )            // 0x100 == shared
                    cSharedPages+= cPagesThisRange;
                else                                // 0x000 == private
                    cPrivatePages+= cPagesThisRange;
            }
            else    // It's a page from the page table region
                cPageTablePages += cPagesThisRange;
			
            PSTR pszBuffCurr = szBuffer;    // ptr to working output string
			
            pszBuffCurr += wsprintf(pszBuffCurr, "%08X  %4uK",pageAddr, cPagesThisRange * 4 );
			
            // 0x100 == not private (i.e., shared)
            pszBuffCurr += wsprintf( pszBuffCurr,pageFlags & 0x100 ? "  S":  "  P" );
			
            // 0x01 == ReadOnly
            // 0x04 == Writeable
            // 0x05 == Copy On Write (special case)
            if ( 0x5 == (pageFlags & 0x5) )
                pszBuffCurr += wsprintf( pszBuffCurr, " CW" );
            else if ( pageFlags & 0x1 )
                pszBuffCurr += wsprintf( pszBuffCurr, " RO" );
            else if ( pageFlags & 0x4 )
                pszBuffCurr += wsprintf( pszBuffCurr, " RW" );
            else
                pszBuffCurr += wsprintf( pszBuffCurr, " ??" );
			
            // 0x02 == Executable
            pszBuffCurr += wsprintf( pszBuffCurr,pageFlags & 0x2 ? " E  " : "    " );
			
            char    szMod[MAX_PATH];
            char    szSection[IMAGE_SIZEOF_SHORT_NAME+1];
            DWORD   uSection;
            BOOL    fFoundInfo;
			
            // Get information (such as the module and section name) for the
            // page that was faulted in
            fFoundInfo = GetModuleNameAndSectionInfo(
				hProcess,
				(PVOID)pageAddr,
				szMod, sizeof(szMod),
				szSection, sizeof(szSection),
				&uSection );
			
            if ( fFoundInfo )   // We found Win32 module info!
            {
                if ( uSection ) // We even know which section!
                {
                    pszBuffCurr += wsprintf(pszBuffCurr,"%s!%s(%u)",szMod,szSection,uSection);
                }
                else            // We have a module, but no section
                {
                    pszBuffCurr += wsprintf( pszBuffCurr, "%s", szMod );
                }
            }
            else
            {
                // Perhaps it's a memory mapped file!
                char szOwner[MAX_PATH];
                if ( GetMappedFileNameA( hProcess, (PVOID)pageAddr,
					szOwner, sizeof(szOwner)))
                    pszBuffCurr += wsprintf( pszBuffCurr, "%s", szOwner );
            }
			
            // Add the output string to the listbox (finally!)
            SendMessage( hWndLb, LB_ADDSTRING, 0, (LPARAM) szBuffer);
			char crtl[]={13,10,0};
			strcat(szPrtBuffer,crtl);
			strcat(szPrtBuffer,szBuffer);
        }
		
        //
        // Fix this!  page size should be determined dynamically!
        //
        wsprintf( szBuffer, "总内存: %uK", cPages * 4 );
        SetDlgItemText( hDlg, IDC_TOTAL_MEMORY, szBuffer );
        wsprintf( szBuffer, "私有内存: %uK", cPrivatePages * 4 );
        SetDlgItemText( hDlg, IDC_PRIVATE_MEMORY, szBuffer );
        wsprintf( szBuffer, "共享内存: %uK", cSharedPages * 4 );
        SetDlgItemText( hDlg, IDC_SHARED_MEMORY, szBuffer );
        wsprintf( szBuffer, "页表: %uK", cPageTablePages * 4 );
        SetDlgItemText( hDlg, IDC_PAGE_TABLES, szBuffer );
    }
    __finally
    {
        SendMessage( hWndLb, WM_SETREDRAW, TRUE, 0 );   // Enable LB updating
        CloseHandle( hProcess );
    }
	EnableWindow(GetDlgItem(hDlg, IDC_READ), FALSE);
	//EnableWindow(GetDlgItem(hDlg, IDC_SAVEWORKSET), FALSE);
}

void UpdateWorkingSetInfo( HWND hDlg, DWORD processID )
{
    // Clear out the text summary fields
    SetDlgItemText( hDlg, IDC_TOTAL_MEMORY, "" );
    SetDlgItemText( hDlg, IDC_PRIVATE_MEMORY, "" );
    SetDlgItemText( hDlg, IDC_SHARED_MEMORY, "" );
    SetDlgItemText( hDlg, IDC_PAGE_TABLES, "" );
	
    // Clear out the listbox     
    SendDlgItemMessage( hDlg, IDC_LB_WORKING_SET_DETAILS, LB_RESETCONTENT, 0, 0 );
    AddWorkingSetInfo( hDlg, processID );
}

void EmptyProcessWorkingSet( HWND hDlg, DWORD processID )
{
    HANDLE hProcess = OpenProcess(  PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ | PROCESS_SET_QUOTA,
		FALSE, processID );
	
    if ( !hProcess )
    {
        MessageBox( hDlg, "不能打开该进程", 0, MB_OK );
        return;
    }
	
    SetProcessWorkingSetSize( hProcess, 0xFFFFFFFF, 0xFFFFFFFF );
	
    UpdateWorkingSetInfo( hDlg, processID );    
}

void RefreshViews( HWND hDlg )
{
    UpdateProcessList( hDlg );  // Should be self-explanatory!
	
    // Clear the working set LB HWND
    SendDlgItemMessage(hDlg, IDC_LB_WORKING_SET_DETAILS, LB_RESETCONTENT,0,0);
}

// ======================= Start of UI code ===============================
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	//	hInst=hInstance;
    DialogBox(  hInstance, MAKEINTRESOURCE(IDD_PSAPIWorkingSetDemo),0, (DLGPROC)PSAPIWorkingSetDemDlgProc );
    return 0;
	
}

BOOL CALLBACK PSAPIWorkingSetDemDlgProc(HWND hDlg, UINT msg,WPARAM wParam, LPARAM lParam)
{
    //
    // The dialog procedure for the main window
    //
    switch ( msg )
    {
	case WM_COMMAND:
		{
			HWND hwndCtl = (HWND)lParam;
			
			switch ( LOWORD(wParam) )
			{
			case IDC_LB_WORKING_SET_DETAILS:
				{
					switch (HIWORD(wParam)) 
					{ 
					case LBN_SELCHANGE: 
						
						//TCHAR tchBuffer[MAX_PATH];
						// 第一个 DWORD 是页数
						DWORD cPages = g_WorkingSetPages[0];
						DWORD cPrivatePages = 0;
						DWORD cSharedPages = 0;
						DWORD cPageTablePages = 0;
						DWORD thisPageAddr;
						DWORD cPagesThisRange = 0;
						
						int nItem; 
						int j; 
						HWND hwndList; 
						hwndList = GetDlgItem(hDlg, IDC_LB_WORKING_SET_DETAILS);
						nItem = SendMessage(hwndList, LB_GETCURSEL, 0, 0); 
						j = SendMessage(hwndList, LB_GETITEMDATA, nItem, 0);
						thisPageAddr = g_WorkingSetPages[nItem+1] & 0xFFFFF000;
						char addr[10];
						//wsprintf(addr,"%X",thisPageAddr);
						//SetDlgItemText(hDlg, IDC_ADDR, addr);
						int k=0;
						
						// 第一个 DWORD 是页数
						cPages = g_WorkingSetPages[0];
						
						for (DWORD i = 1; i <= cPages; i++)
						{
							DWORD pageAddr = g_WorkingSetPages[i] & 0xFFFFF000;
							DWORD pageFlags = g_WorkingSetPages[i] & 0x00000FFF;
							DWORD thisPageAddr, nextPageAddr, nextPageFlags;
							DWORD cPagesThisRange = 0;
							
							while (i <= cPages)
							{
								cPagesThisRange++;
								if (i == cPages) break; // Break out if its the last page
								thisPageAddr = g_WorkingSetPages[i] & 0xFFFFF000;
								nextPageAddr = g_WorkingSetPages[i+1] & 0xFFFFF000;
								nextPageFlags = g_WorkingSetPages[i+1] & 0x00000FFF;
								
								if ((nextPageAddr == (thisPageAddr + g_PageSize)) && (nextPageFlags == pageFlags))
								{
									i++;       // Keep going
								}
								else break;    // Non-contiguous page or different flags
							}
							
							k++;
							
							if(k==nItem+1)
							{
								wsprintf(addr,"%X",thisPageAddr);
								SetDlgItemText(hDlg, IDC_ADDR, addr);
								
								wsprintf(addr,"%d",cPagesThisRange * 4 * 1024);
								SetDlgItemText(hDlg, IDC_LENGTH, addr);
								
								EnableWindow(GetDlgItem(hDlg, IDC_READ), TRUE);
								EnableWindow(GetDlgItem(hDlg, IDC_SAVEMEMORY), TRUE);
								break;
							}					
						}
					}
				}
				break;
			case IDC_READ:
				Read(hDlg); 
				break;
			case IDC_SAVEMEMORY:
				Save(hDlg); 
				break;
			case IDC_SAVEWORKSET:
				{
					printtofile(hDlg);
				}
				break;
			case IDC_BUTTON_REFRESH_PROCESS_LIST:
				RefreshViews( hDlg );
				break;
				
			case IDC_LB_PROCESS_LIST:
				if ( LBN_SELCHANGE == HIWORD(wParam) )
				{
					// Was an item selected in the process list?  If so, get the
					// associated itemdata (really a PID), and refresh the working
					// set information for the process
					DWORD pid = GetDlgSelectedItemData(hDlg, IDC_LB_PROCESS_LIST);          
					UpdateWorkingSetInfo( hDlg, pid );
				}
				break;
				
			case IDC_BUTTON_EMPTY_WORKING_SET:
				{
					DWORD pid = GetDlgSelectedItemData(hDlg, IDC_LB_PROCESS_LIST);
					EmptyProcessWorkingSet( hDlg, pid );
				}
				break;
				
			case IDC_BUTTON_START_DELTA:
				{
					DWORD pid = GetDlgSelectedItemData(hDlg, IDC_LB_PROCESS_LIST);
					if ( StartWorkingSetDelta( pid ) )
					{
						// Disable the "Start Delta" button and enable the
						// "end delta" button
						EnableWindow( GetDlgItem(hDlg, IDC_BUTTON_START_DELTA),FALSE );
						EnableWindow(   GetDlgItem(hDlg, IDC_BUTTON_END_DELTA),TRUE );
						SetFocus( GetDlgItem(hDlg,IDC_BUTTON_END_DELTA) ); 
					}
					else
						MessageBox(hDlg, "不能监视 working set", 0,MB_OK);
				}
				break;
				
			case IDC_BUTTON_END_DELTA:
				EndWorkingSetDelta( hDlg );
				
				// Enable the "Start Delta" button and disable the "end delta"
				EnableWindow( GetDlgItem(hDlg, IDC_BUTTON_END_DELTA), FALSE );
				EnableWindow( GetDlgItem(hDlg, IDC_BUTTON_START_DELTA), TRUE );
				SetFocus( GetDlgItem(hDlg, IDC_BUTTON_START_DELTA) );
				break;
			}
		}
		break;
	case WM_INITDIALOG:
		{
			// Get the window coordinates where the program was last running,
			// and move the window to that spot.
			//    POINT pt;
			//GetSetPositionInfoFromRegistry( FALSE, &pt );
			//SetWindowPos(hDlg, 0, pt.x, pt.y, 0, 0,SWP_NOSIZE | SWP_NOREDRAW | SWP_NOZORDER | SWP_NOACTIVATE);
			
			// Disable the "End Delta" button
			//EnableWindow( GetDlgItem( hDlg, IDC_BUTTON_END_DELTA ), FALSE );
			RefreshViews( hDlg );   // Fill treeviews with initial values
			
		}
		break;
	case WM_CLOSE:
		{
			// Save off the window's X,Y coordinates for next time
			EndDialog( hDlg, 0 );
		}
		break;
		// let everything else fall through
    }
    return FALSE;
}

// Returns the DWORD of "item data" associated with the currently selected
// item in the listbox specified by the ctlID param
DWORD GetDlgSelectedItemData( HWND hDlg, int ctlID )
{
    LONG lbIndex = SendDlgItemMessage( hDlg, ctlID, LB_GETCURSEL, 0, 0 );
    return SendDlgItemMessage(hDlg, ctlID, LB_GETITEMDATA, lbIndex, 0 );
}

void printtofile(HWND hDlg)
{
//	unsigned char crtl[]={13,10};
//	char szText[5][1024];
//	char line[1024];
//	HWND hwndListView = GetDlgItem( hDlg, IDC_LB_PROCESS_LIST );
//	int itemcount = ListView_GetItemCount(hwndListView);
	
	DWORD dwBytesWritten;
	HANDLE hFile;
	hFile = CreateFile("test.txt",GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if (INVALID_HANDLE_VALUE != hFile)
	{
		WriteFile(hFile, "地址        大小   属性    所有者  \r\n", strlen("地址        大小   属性    所有者  \r\n"), &dwBytesWritten, NULL);
		WriteFile(hFile, "===================================\r\n", strlen("===================================\r\n"), &dwBytesWritten, NULL);
		WriteFile(hFile, szPrtBuffer, strlen(szPrtBuffer), &dwBytesWritten, NULL);
		MessageBox(NULL,"报表文件 test.txt 已经生成!","OK",0);
		CloseHandle(hFile);
	}
}

void DisplayErrorText( DWORD dwLastError )
{
    HMODULE hModule = NULL; // default to system source
    LPSTR MessageBuffer;
    DWORD dwBufferLength;

    DWORD dwFormatFlags = FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_IGNORE_INSERTS |
        FORMAT_MESSAGE_FROM_SYSTEM ;

    if(dwLastError >= NERR_BASE && dwLastError <= MAX_NERR) 
	{
        hModule = LoadLibraryEx(
            TEXT("netmsg.dll"),
            NULL,
            LOAD_LIBRARY_AS_DATAFILE
            );

        if(hModule != NULL)
            dwFormatFlags |= FORMAT_MESSAGE_FROM_HMODULE;
    }

    if(dwBufferLength = FormatMessageA(
        dwFormatFlags,
        hModule, // module to get message from (NULL == system)
        dwLastError,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // default language
        (LPSTR) &MessageBuffer,
        0,
        NULL
        ))
    {

		MessageBox(NULL,MessageBuffer,0,0);
		LocalFree(MessageBuffer);
    }

    if(hModule != NULL) FreeLibrary(hModule);
}

BOOL IsNT()
{
	OSVERSIONINFO stOSVI;
	memset(&stOSVI, NULL, sizeof(OSVERSIONINFO));
	stOSVI.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	BOOL bRet = GetVersionEx(&stOSVI);
	if (FALSE == bRet) return FALSE;
	return (VER_PLATFORM_WIN32_NT == stOSVI.dwPlatformId);
}

BOOL InitPhysicalMemory()
{
	if (!(hModule = LoadLibrary("ntdll.dll")))
	{
		return FALSE;
	}
	
	// 以下从NTDLL获取我们需要的几个函数指针
    if (!(ZwOpenSection = (ZwOpenSectionProc)GetProcAddress(hModule, "ZwOpenSection")))
    {
        return FALSE;
    }
	
    if (!(ZwMapViewOfSection = (ZwMapViewOfSectionProc)GetProcAddress(hModule, "ZwMapViewOfSection")))
    {
        return FALSE;
    }
	
    if (!(ZwUnmapViewOfSection = (ZwUnmapViewOfSectionProc)GetProcAddress(hModule, "ZwUnmapViewOfSection")))
    {
        return FALSE;
    }
	
    if (!(RtlInitUnicodeString = (RtlInitUnicodeStringProc)GetProcAddress(hModule, "RtlInitUnicodeString")))
    {
        return FALSE;
    }
	
	// 以下打开内核对象
    WCHAR PhysicalMemoryName[] = L"\\Device\\PhysicalMemory";
    UNICODE_STRING PhysicalMemoryString;
    OBJECT_ATTRIBUTES attributes;
    RtlInitUnicodeString(&PhysicalMemoryString, PhysicalMemoryName);
    InitializeObjectAttributes(&attributes, &PhysicalMemoryString, 0, NULL, NULL);
    NTSTATUS status = ZwOpenSection(&hPhysicalMemory, SECTION_MAP_READ, &attributes );
	
	return (status >= 0);
}

// terminate -- free handles
void ExitPhysicalMemory()
{
	if (hPhysicalMemory != NULL) CloseHandle(hPhysicalMemory);
	if (hModule != NULL) FreeLibrary(hModule);
}

BOOL ReadPhysicalMemory(PVOID buffer, ULONGLONG address, DWORD length)
{
	DWORD outlen;			// 输出长度，根据内存分页大小可能大于要求的长度
	PVOID vaddress;			// 映射的虚地址
    NTSTATUS status;		// NTDLL函数返回的状态
    LARGE_INTEGER base;		// 物理内存地址
	
    vaddress = 0;
	outlen = length;
    base.QuadPart = (ULONGLONG)(address);
	
	// 映射物理内存地址到当前进程的虚地址空间
    status = ZwMapViewOfSection(hPhysicalMemory,
        (HANDLE) -1,
        (PVOID *)&vaddress,
        0,
        length,
        &base,
        &outlen,
        ViewShare,
        0,
        PAGE_READONLY);
	
	if (status < 0)
	{
		return FALSE;
	}
	
	// 当前进程的虚地址空间中，复制数据到输出缓冲区
	memmove(buffer, vaddress, length); 
	
	// 完成访问，取消地址映射
    status = ZwUnmapViewOfSection((HANDLE)-1, (PVOID)vaddress);
	
	return (status >= 0);
}

void Read(HWND hDlg)
{
	int nLength;		// 读取字节数
	DWORD dwAddr;		// 起始物理地址
	static UCHAR buf[65536];	// 数据缓冲区
	static CHAR str[65536*8];	// 显示缓冲区
	char szFile[BUFSIZE];
	memset(szFile,0,BUFSIZE);

	SendDlgItemMessage(hDlg, IDC_ADDR, WM_GETTEXT, BUFSIZE, (LPARAM) szFile);
	dwAddr = strtol( szFile, 0, 16 ); //转换 16 进制的串到长型

	//PHYSICAL_ADDRESS
	//MmGetPhysicalAddress(dwAddr);

	SendDlgItemMessage(hDlg, IDC_LENGTH, WM_GETTEXT, BUFSIZE, (LPARAM) szFile);
	nLength=atol(szFile);  //转换 10 进制的串到长型

	if (dwAddr & 0xfff)		// 这里以NT默认的4KB字节分页
	{
		MessageBox(NULL,"物理内存地址必须对齐到 4 KB!",0,0);
		return;
	}
	
	if (nLength<=0) return;
	if (nLength > 65536) nLength = 65536;
	
	// 以下读取物理内存
	
	if (!InitPhysicalMemory())
	{
		MessageBox(NULL,"InitPhysicalMemory 失败!",0,0);
		return;
	}

	ULONGLONG retval = GetPhysicalAddress(dwAddr);

	if (!ReadPhysicalMemory(buf, retval, nLength))
	{
		ExitPhysicalMemory();
		MessageBox(NULL,"读物理内存失败!",0,0);
		return;
	}
	
	ExitPhysicalMemory();
	
	// 以下输出到屏幕
	
	int m,n;
	int nLines;
	char tmp[65536];
	
	char* p = str;
	
	// 确定行数
	nLines = nLength/16;
	if (nLength % 16) nLines++;
	
	for (m = 0; m < nLines; m++)
	{
		// 物理地址
		wsprintf(tmp,"%08X  ", dwAddr + 16 * m);
		memcpy(p, tmp, 10);
		p += 10;
		
		// 以HEX码形式输出
		for (n = 0; n < 16; n++)
		{
			if (m * 16 + n < nLength)
			{
				wsprintf(tmp,"%02X ", buf[m*16+n]);
			}
			else
			{
				wsprintf(tmp,"%s","   ");		// 不满一行，填充
			}
			
			memcpy(p, tmp, 3);
			p += 3;
		}
		
		memcpy(p, "  ", 2);
		p += 2;
		
		// 以字符形式输出
		for (n = 0; n < 16; n++)
		{
			if (m * 16 + n < nLength)
			{
				if (isprint(buf[m*16+n]) || (buf[m*16+n] >= 0xa1) && (n < 16 - 1))
				{
					wsprintf(tmp,"%c", buf[m*16+n]);		// 可打印字符
				}
				else
				{
					wsprintf(tmp,"%s",".");		// 不可打印字符，以'.'代替
				}
			}
			else
			{
				wsprintf(tmp,"%s"," ");		// 不满一行，填充
			}
			memcpy(p, tmp, 1);
			p += 1;
		}
		memcpy(p, "\r\n", 2);
		p += 2;
	}
	*p = '\0';
    SetWindowText(GetDlgItem(hDlg, IDC_CONTENT), str);
}

void Save(HWND hDlg)
{
	int nLength;		        // 读取字节数
	DWORD dwAddr;			    // 起始物理地址
	//UCHAR buf[65536];	// 数据缓冲区
	char szFile[BUFSIZE];
	memset(szFile,0,BUFSIZE);

	SendDlgItemMessage(hDlg, IDC_ADDR, WM_GETTEXT, BUFSIZE, (LPARAM) szFile);
	dwAddr = strtol( szFile, 0, 16 ); //转换 16 进制的串到长型

	SendDlgItemMessage(hDlg, IDC_LENGTH, WM_GETTEXT, BUFSIZE, (LPARAM) szFile);
	nLength=atol(szFile);  //转换 10 进制的串到长型

	unsigned char * buf=new unsigned char[nLength];	// 数据缓冲区

	if (dwAddr & 0xfff)		// 这里以NT默认的4KB字节分页
	{
		MessageBox(NULL,"物理内存地址必须对齐到 4 KB!",0,0);
		delete[]buf;
		return;
	}

	//if (nLength<=0) return;
	
	// 以下读取物理内存
	
	if (!InitPhysicalMemory())
	{
		MessageBox(NULL,"InitPhysicalMemory 失败!",0,0);
		delete[]buf;
		return;
	}
	
	if (!ReadPhysicalMemory(buf, (ULONGLONG)dwAddr, nLength))
	{
		ExitPhysicalMemory();
		MessageBox(NULL,"ReadPhysicalMemory 失败!",0,0);
		delete[]buf;
		return;
	}
	
	ExitPhysicalMemory();
	
	OPENFILENAME ofn;
	char szFilter[] = "*.*\0" ;
	ZeroMemory(&ofn,sizeof( OPENFILENAME));
	ofn.lStructSize = sizeof( OPENFILENAME) ;
	ofn.lpstrFilter = szFilter;
	ofn.nFilterIndex = 0 ;
	ofn.nMaxFile = MAX_PATH ;
	char Dir[MAX_PATH]="test.dat";
	ofn.lpstrFile=Dir;
	ofn.Flags = 0 ;
	
	if(GetSaveFileName(&ofn))
	{
		HANDLE hFile = CreateFile(ofn.lpstrFile,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		
		if (hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(NULL,"创建文件失败!",0,0);
			delete[]buf;
			return;
		}
		DWORD nWritten=0;
		WriteFile(hFile, buf, nLength, &nWritten, NULL);
		if (nWritten != nLength) MessageBox(NULL,"写文件失败!",0,0);
		else MessageBox(NULL,"Success!",0,0);
		CloseHandle(hFile);
	}
	delete[]buf;
}

ULONGLONG GetPhysicalAddress(ULONG vAddress) 
{
	ULONGLONG add;
	
	if (vAddress < 0x80000000L || vAddress >= 0xA0000000L)
		//add.QuadPart = (ULONGLONG) vAddress & 0xFFFF000;
		add = (ULONGLONG) vAddress & 0xFFFF000;
	else
		//add.QuadPart = (ULONGLONG) vAddress & 0x1FFFF000;
		add = (ULONGLONG) vAddress & 0x1FFFF000;
	return add;
}
