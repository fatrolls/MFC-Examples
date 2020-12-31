// ClipDockDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClipDock.h"
#include "ClipDockDlg.h"
#include "OXClipPocket.h"
#include "OXToolTipCtrl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClipDockDlg dialog

CClipDockDlg::CClipDockDlg()
	: COXAppBar<COXMulticlipboardDlg>()
{
	//{{AFX_DATA_INIT(CClipDockDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pButton=NULL;
}

CClipDockDlg::~CClipDockDlg()
{
	if (m_pButton)
	{
		m_pButton->DestroyWindow();
		delete m_pButton;
	}

}

void CClipDockDlg::DoDataExchange(CDataExchange* pDX)
{
	COXMulticlipboardDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClipDockDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClipDockDlg, COXAppBar<COXMulticlipboardDlg>)
	//{{AFX_MSG_MAP(CClipDockDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClipDockDlg message handlers

BOOL CClipDockDlg::OnInitDialog()
{
	COXMulticlipboardDlg::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	SetPocketsInRow(1);
	AdjustSize(1);
	Register(TRUE);
	SetBarStyle(OX_APPBARS_RIGHT | OX_APPBARS_FLOAT | OX_APPBARS_DIFFERENT_DIMS);

	CRect rect;
	CalculateDesiredRect(1,rect);
	CalcWindowRect(&rect);
	this->SetDockDimension(ABE_RIGHT, rect.Width());	
	SetEdge(ABE_RIGHT);
	SetAlwaysOnTop(TRUE);
	
	GetClientRect(&rect);
	m_pButton=new CButton;
	rect.DeflateRect(10,10);
	rect.bottom=rect.top+18;
	m_pButton->Create(_T("About"), WS_VISIBLE | WS_CHILD, rect, this, ID_APP_ABOUT);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClipDockDlg::OnPaint() 
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
		COXMulticlipboardDlg::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClipDockDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CClipDockDlg::OnSetEdge(UINT nEdge)
{
	if (nEdge==ABE_FLOAT)
		SetPocketsInRow(4);
	else
		SetPocketsInRow(1);
	
		AdjustSize(GetLastPocketIndex());

}

BOOL CClipDockDlg::CanResize()
{
	if (GetEdge()==ABE_FLOAT)
		return TRUE;
	else
		return FALSE;
}

void CClipDockDlg::OnClipInfoChanged(UINT nPocketNumber)
{
	COXMulticlipboardDlg::OnClipInfoChanged(nPocketNumber);
	COXClipPocket* pPocket=GetPocket(nPocketNumber);
	ASSERT(pPocket);

	COXToolTipCtrl* pTip=GetToolTip();

	if (pPocket->GetDataType()==CF_TEXT)
	{
		tOXData* pData=pPocket->GetData();
		if (pData->Stgmed.tymed==TYMED_HGLOBAL)
		{
			//we have text in global memory;
			TCHAR szBuffer[28];
			void* pText=::GlobalLock(pData->Stgmed.hGlobal);
			DWORD dwSize= (DWORD)min(27,::GlobalSize(pData->Stgmed.hGlobal));
			::ZeroMemory((void*) &szBuffer, 28);
			::CopyMemory((void*) &szBuffer, pText, dwSize);
			::GlobalUnlock(pData->Stgmed.hGlobal);
			lstrcpy(((LPTSTR) &szBuffer+24),_T(".."));
			pTip->DelTool(pPocket);
			pTip->AddTool(pPocket,(LPCTSTR) &szBuffer);
		}
	}
}

BOOL CClipDockDlg::ClipObjectToPocket(COXClipPocket* pPocket, 
		COleDataObject* pObject)
{
	return COXMulticlipboardDlg::ClipObjectToPocket(pPocket,pObject);
}

UINT CClipDockDlg::GetButtonsHeight()
{
	return 38;
}

void CClipDockDlg::OnDestroy() 
{

	COXAppBar<COXMulticlipboardDlg>::OnDestroy();
	
	
}
