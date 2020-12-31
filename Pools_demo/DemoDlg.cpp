// DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "DemoDlg.h"
#include "PreciseTimer.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define TIMER_ID 10283

BOOL CALLBACK EnumChildProcEnable(HWND hwnd,LPARAM lParam)
{
	EnableWindow(hwnd,(BOOL)lParam);
	return TRUE;
}

#define NUM_OF_THREADS		5
#define NUM_OF_OPERATIONS	5000000
#define NUM_OF_ALLOCATIONS	1000
#define BUFFER_SIZE		    (10*1024)

int MessageLoop ( 
				 HANDLE* lphObjects,  // handles that need to be waited on 
				 int     cObjects     // number of handles to wait on 
				 )
{ 
	UINT nLeft = cObjects;
    // The message loop lasts until we get a WM_QUIT message,
    // upon which we shall return from the function.
    while (TRUE)
    {
        // block-local variable 
        DWORD result ; 
        MSG msg ; 
		
        // Read all of the messages in this next loop, 
        // removing each message as we read it.
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
        { 
            // If it's a quit message, we're out of here.
            if (msg.message == WM_QUIT)  
                return 1; 
            // Otherwise, dispatch the message.
            DispatchMessage(&msg); 
        } // End of PeekMessage while loop.
		
        // Wait for any message sent or posted to this queue 
        // or for one of the passed handles be set to signaled.
        result = MsgWaitForMultipleObjects(cObjects, lphObjects, 
			FALSE, INFINITE, QS_ALLINPUT); 
		
        // The result tells us the type of event we have.
        if (result == (WAIT_OBJECT_0 + cObjects))
        {
            // New messages have arrived. 
            // Continue to the top of the always while loop to 
            // dispatch them and resume waiting.
            continue;
        } 
        else 
        { 
		
			
            // One of the handles became signaled. 
			if(!--nLeft)
			{
				break;
			}

			result = result - WAIT_OBJECT_0;
			
			for(int i = result ; i < cObjects - 1 ; i++)
			{
				lphObjects[i] = lphObjects[i + 1];
			}
			
			cObjects--;

        } // End of else clause.
    } // End of the always while loop. 

	return 0; 
} // End of function.




DWORD WINAPI BufferPoolThreadProc(LPVOID lpParameter)
{
	CDemoDlg* pDlg = (CDemoDlg*)lpParameter;


	CPreciseTimer timer;
	
	
    
	void** pBuffersPointersArray = new void*[pDlg->m_nMaximumBuffers];

	memset(pBuffersPointersArray,0,pDlg->m_nMaximumBuffers * sizeof(void*));

	srand(10);

	UINT nNumberOfOperationForEachThread = pDlg->m_nNumberOfOperations/pDlg->m_nNumberOfThreads;


	for(UINT i = 0 ; i < nNumberOfOperationForEachThread ; i++)
	{
		timer.StartTimer();

		UINT index = (UINT)((((double)rand())/RAND_MAX) * (pDlg->m_nMaximumBuffers - 1)) ;

		if(pBuffersPointersArray[index] == NULL)
		{
		  pBuffersPointersArray[index] = pDlg->m_BuffPoolObj.Allocate();		 
		  pDlg->m_BPAllocateCount++;		  		 		 
		}
		else
		{
		  pDlg->m_BuffPoolObj.Free(pBuffersPointersArray[index]);
		  pBuffersPointersArray[index] = NULL;
		  pDlg->m_BPFreeCount++;		  
		}
		
		pDlg->m_nBPTotalTime += timer.GetTime();
	}

	for( i = 0 ; i < pDlg->m_nMaximumBuffers ; i++)
	{
		if(pBuffersPointersArray[i] != NULL)
		{
			pDlg->m_BuffPoolObj.Free(pBuffersPointersArray[i]);
			pBuffersPointersArray[i] = NULL;
		}
	}


	delete pBuffersPointersArray;

	return 0;
}

DWORD WINAPI RegularThreadProc(LPVOID lpParameter)
{
	CDemoDlg* pDlg = (CDemoDlg*)lpParameter;
    
	CPreciseTimer timer;

	void** pBuffersPointersArray = new void*[pDlg->m_nMaximumBuffers];
	
	memset(pBuffersPointersArray,0,pDlg->m_nMaximumBuffers * sizeof(void*));
	
	srand(10);
		
	UINT nNumberOfOperationForEachThread = pDlg->m_nNumberOfOperations/pDlg->m_nNumberOfThreads;
	
	
	for(UINT i = 0 ; i < nNumberOfOperationForEachThread ; i++)
	{
		timer.StartTimer();
		
		UINT index = (UINT)((((double)rand())/RAND_MAX) * (pDlg->m_nMaximumBuffers - 1));
		if(pBuffersPointersArray[index] == NULL)
		{
			pBuffersPointersArray[index] = new char[pDlg->m_nBufferSize];	
			
			pDlg->m_RegAllocateCount++;
			
		}
		else
		{
			delete pBuffersPointersArray[index];
			pBuffersPointersArray[index] = NULL;

		
			pDlg->m_RegFreeCount++;
		}		
		
		pDlg->m_nRegTotalTime += timer.GetTime();
	}

	for( i = 0 ; i < pDlg->m_nMaximumBuffers ; i++)
	{
		if(pBuffersPointersArray[i] != NULL)
		{
			delete pBuffersPointersArray[i];
			pBuffersPointersArray[i] = NULL;
		}
	}
	
	delete pBuffersPointersArray;
	
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg dialog

CDemoDlg::CDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemoDlg)
	m_BPFreeStatic = _T("");
	m_RegFreeStatic = _T("");
	m_BPAllocateStatic = _T("");
	m_RegAllocateStatic = _T("");
	m_BPAvTime = _T("");
	m_RegAvTime = _T("");
	m_BPTotalTime = _T("");
	m_RegTotalTime = _T("");
	m_nBufferSize			= BUFFER_SIZE;
	m_nMaximumBuffers		= NUM_OF_ALLOCATIONS;
	m_nNumberOfOperations	= NUM_OF_OPERATIONS;
	m_nNumberOfThreads      = NUM_OF_THREADS;
	m_nMinNumberOfSegments = 2;
	m_nMaxNumberOfSegments = -1;
	m_nInitialNumberOfSegments = 2;
	m_nFreeBuffersPrecentForSegmentDeletion = 0.3333f;
	m_nBuffersPerSegment = 100;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_BPFreeCount		= 0;
	m_RegFreeCount		= 0;
	m_BPAllocateCount	= 0;
	m_RegAllocateCount	= 0;

	
	
	

	
}

CDemoDlg::~CDemoDlg()
{	
}

void CDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoDlg)
	DDX_Control(pDX, IDC_REGULAR_ALLOCATION_PROGRESS, m_RegularAllocationProgress);
	DDX_Control(pDX, IDC_BUFFER_POOL_PROGRESS, m_BuffPollProgress);
	DDX_Text(pDX, IDC_BP_FREE_STATIC, m_BPFreeStatic);
	DDX_Text(pDX, IDC_REG_FREE_STATIC, m_RegFreeStatic);
	DDX_Text(pDX, IDC_BP_ALLOCATE_STATIC, m_BPAllocateStatic);
	DDX_Text(pDX, IDC_REG_ALLOCATE_STATIC, m_RegAllocateStatic);
	DDX_Text(pDX, IDC_BP_AV_TIME_STATIC, m_BPAvTime);
	DDX_Text(pDX, IDC_REG_AV_TIME_STATIC, m_RegAvTime);
	DDX_Text(pDX, IDC_BP_TOTAL_TIME_STATIC, m_BPTotalTime);
	DDX_Text(pDX, IDC_REG_TOTAL_TIME_STATIC, m_RegTotalTime);
	DDX_Text(pDX, IDC_BUFFERS_SIZE_EDT, m_nBufferSize);
	DDX_Text(pDX, IDC_MAXIMUM_BUFFERS_EDT, m_nMaximumBuffers);
	DDX_Text(pDX, IDC_NUM_OF_OPERATIONS_EDT, m_nNumberOfOperations);
	DDX_Text(pDX, IDC_NUM_OF_THREADS_EDT, m_nNumberOfThreads);
	DDX_Text(pDX, IDC_NUM_OF_SEGMENTS_MIN_EDT, m_nMinNumberOfSegments);
	DDX_Text(pDX, IDC_NUM_OF_SEGMENTS_MAX_EDT, m_nMaxNumberOfSegments);
	DDX_Text(pDX, IDC_NUM_OF_SEGMENTS_START_EDT, m_nInitialNumberOfSegments);
	DDX_Text(pDX, IDC_PRECENT_FOR_DELETION_EDT, m_nFreeBuffersPrecentForSegmentDeletion);
	DDX_Text(pDX, IDC_NUM_OF_BUFFERS_PER_SEGMENTS_EDT, m_nBuffersPerSegment);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_TEST_BUTTON, OnTestButton)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_TEST_BP_BUTTON, OnTestBpButton)
	ON_BN_CLICKED(IDC_TEST_GLOBAL_BUTTON, OnTestGlobalButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg message handlers

BOOL CDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	
    //Just To Demonstrate The Object Pool
	SomeTypeObjectPool.Create(100,3,1,5);
	
	//allocate an object
	SomeType* pST = SomeTypeObjectPool.Allocate();

	//as you can see the virtual table has been initialized
	pST->DoSomethingOrRather();
	
	pST->GetTheFlaot();

	//free the object
	SomeTypeObjectPool.Free(pST);

	//destoy the pool
	SomeTypeObjectPool.Destroy();

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
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

void CDemoDlg::OnPaint() 
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
HCURSOR CDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDemoDlg::OnTestButton() 
{
	DWORD dwThreadId;


	UpdateData(TRUE);

	m_BPFreeCount		= 0;
	m_RegFreeCount		= 0;
	m_BPAllocateCount	= 0;
	m_RegAllocateCount	= 0;

	m_BuffPollProgress.SetRange32(0, m_nNumberOfOperations);
	m_BuffPollProgress.SetPos(0);
	m_BuffPollProgress.SetStep(1);

	m_nBPTotalTime = 0;
	

	m_RegularAllocationProgress.SetRange32(0, m_nNumberOfOperations);
	m_RegularAllocationProgress.SetPos(0);
	m_RegularAllocationProgress.SetStep(1);
	
	m_nRegTotalTime = 0;

	EnumChildWindows(this->GetSafeHwnd(),         // handle to parent window
		EnumChildProcEnable,  // callback function
		(LPARAM)FALSE);
	
	SetTimer(TIMER_ID,500,NULL);

	m_BuffPoolObj.Create(m_nBufferSize,
		m_nBuffersPerSegment,
		m_nInitialNumberOfSegments,
		m_nMinNumberOfSegments,
		m_nMaxNumberOfSegments,
		m_nFreeBuffersPrecentForSegmentDeletion);
	

	PHANDLE pHandles = new HANDLE[2 * m_nNumberOfThreads];

	for(UINT i = 0 ; i < m_nNumberOfThreads ; i++)
	{	
		pHandles[2*i] = CreateThread(NULL,0,BufferPoolThreadProc,this,0,&dwThreadId);
		
		if(pHandles[2*i] == NULL)
			break;

		pHandles[2*i + 1] = CreateThread(NULL,0,RegularThreadProc,this,0,&dwThreadId);

		if(pHandles[2*i + 1] == NULL)
			break;
	}
	
	MessageLoop(pHandles,2 * m_nNumberOfThreads);

	KillTimer(TIMER_ID);
	
	delete pHandles;

	m_BuffPoolObj.Destroy();

	m_BuffPollProgress.SetPos(m_nNumberOfOperations);
	m_RegularAllocationProgress.SetPos(m_nNumberOfOperations);



	EnumChildWindows(this->GetSafeHwnd(),         // handle to parent window
		EnumChildProcEnable,  // callback function
		(LPARAM)TRUE);
	

}



void CDemoDlg::OnTestBpButton() 
{
	DWORD dwThreadId;

	UpdateData(TRUE);

	EnumChildWindows(this->GetSafeHwnd(),         // handle to parent window
		EnumChildProcEnable,  // callback function
		(LPARAM)FALSE);
	
	
	m_BPFreeCount		= 0;	
	m_BPAllocateCount	= 0;
	
	
	m_BuffPollProgress.SetRange32(0, m_nNumberOfOperations);
	m_BuffPollProgress.SetPos(0);
	m_BuffPollProgress.SetStep(1);
	
	m_nBPTotalTime = 0;


	
	m_BuffPoolObj.Create(m_nBufferSize,
		m_nBuffersPerSegment,
		m_nInitialNumberOfSegments,
		m_nMinNumberOfSegments,
		m_nMaxNumberOfSegments,
		m_nFreeBuffersPrecentForSegmentDeletion);

	SetTimer(TIMER_ID,500,NULL);

	PHANDLE pHandles = new HANDLE[m_nNumberOfThreads];
	
	for(UINT i = 0 ; i < m_nNumberOfThreads ; i++)
	{	
		pHandles[i] = CreateThread(NULL,0,BufferPoolThreadProc,this,0,&dwThreadId);
		
		if(pHandles[i] == NULL)
			break;
	}	

	MessageLoop(pHandles,m_nNumberOfThreads);

	KillTimer(TIMER_ID);
	
	delete pHandles;
	
	m_BuffPoolObj.Destroy();

	m_BuffPollProgress.SetPos(m_nNumberOfOperations);



	EnumChildWindows(this->GetSafeHwnd(),         // handle to parent window
		EnumChildProcEnable,  // callback function
		(LPARAM)TRUE);
}

void CDemoDlg::OnTestGlobalButton() 
{
	DWORD dwThreadId;

	UpdateData(TRUE);

	EnumChildWindows(this->GetSafeHwnd(),         // handle to parent window
		EnumChildProcEnable,  // callback function
		(LPARAM)FALSE);
	
	m_RegFreeCount		= 0;
	m_RegAllocateCount	= 0;
	
	
	
	m_RegularAllocationProgress.SetRange32(0, m_nNumberOfOperations);
	m_RegularAllocationProgress.SetPos(0);
	m_RegularAllocationProgress.SetStep(1);
	
	m_nRegTotalTime = 0;

	SetTimer(TIMER_ID,500,NULL);

	PHANDLE pHandles = new HANDLE[m_nNumberOfThreads];
	
	for(UINT i = 0 ; i < m_nNumberOfThreads ; i++)
	{			
		pHandles[i] = CreateThread(NULL,0,RegularThreadProc,this,0,&dwThreadId);
		
		if(pHandles[i] == NULL)
			break;
	}	

	MessageLoop(pHandles,m_nNumberOfThreads);

	KillTimer(TIMER_ID);
	
	delete pHandles;
	
	
	m_RegularAllocationProgress.SetPos(m_nNumberOfOperations);
	
	EnumChildWindows(this->GetSafeHwnd(),         // handle to parent window
		EnumChildProcEnable,  // callback function
		(LPARAM)TRUE);
}


void CDemoDlg::OnTimer(UINT nIDEvent) 
{
	UINT num;
	m_BPFreeStatic.Format(_T("%lu"),m_BPFreeCount);
	m_RegFreeStatic.Format(_T("%lu"),m_RegFreeCount);
	m_BPAllocateStatic.Format(_T("%lu"),m_BPAllocateCount);
	m_RegAllocateStatic.Format(_T("%lu"),m_RegAllocateCount);
	
	if(m_RegFreeCount + m_RegAllocateCount > 0)
	{
		num = (UINT)(m_nRegTotalTime/(m_RegFreeCount + m_RegAllocateCount));
		m_RegAvTime.Format(_T("%lu"),num);
	}
	
	num = (UINT)(m_nRegTotalTime/10000);
	m_RegTotalTime.Format(_T("%lu"),num);
	
	if(m_BPFreeCount + m_BPAllocateCount > 0)
	{
		num = (UINT)(m_nBPTotalTime/(m_BPFreeCount + m_BPAllocateCount));
		m_BPAvTime.Format(_T("%lu"),num);
	}
	
	num = (UINT)(m_nBPTotalTime/10000);
	m_BPTotalTime.Format(_T("%lu"),num);
	
	
	UpdateData(FALSE);
	
	m_BuffPollProgress.SetPos(m_BPFreeCount + m_BPAllocateCount);	
	m_RegularAllocationProgress.SetPos(m_RegFreeCount + m_RegAllocateCount);
	
	CDialog::OnTimer(nIDEvent);
}





















