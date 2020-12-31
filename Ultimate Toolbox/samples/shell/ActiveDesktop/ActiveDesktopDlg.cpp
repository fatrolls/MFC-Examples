// ActiveDesktopDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ActiveDesktop.h"
#include "ActiveDesktopDlg.h"
#include "UTSampleAbout.h"

#include "UTBSTrOp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
// CActiveDesktopDlg dialog

CActiveDesktopDlg::CActiveDesktopDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CActiveDesktopDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CActiveDesktopDlg)
	m_bComps = FALSE;
	m_bDesktop = FALSE;
	m_nWOpt = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	::ZeroMemory(&m_pattern, 8);
	::ZeroMemory(&m_bmp,512);
	VERIFY(m_bitmap.CreateBitmap(64,64,1,1,&m_bmp));
	m_bEditEnabled=FALSE;
	m_bRemoveEnabled=FALSE;

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CActiveDesktopDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CActiveDesktopDlg)
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_STATIC_PATTERN, m_stcPattern);
	DDX_Control(pDX, IDC_LIST_MAIN, m_lstMain);
	DDX_Control(pDX, IDC_EDIT_WALLPAPER, m_edtWallpaper);
	DDX_Control(pDX, ID_REMOVE, m_btnRemove);
	DDX_Control(pDX, ID_EDIT, m_btnEdit);
	DDX_Control(pDX, ID_APPLY, m_btnApply);
	DDX_Check(pDX, IDC_CHECK_COMPS, m_bComps);
	DDX_Check(pDX, IDC_CHECK_DESKTOP, m_bDesktop);
	DDX_CBIndex(pDX, IDC_COMBO_WOPT, m_nWOpt);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CActiveDesktopDlg, CDialog)
	//{{AFX_MSG_MAP(CActiveDesktopDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_DESKTOP, OnCheckDesktop)
	ON_BN_CLICKED(IDC_CHECK_COMPS, OnCheckComps)
	ON_BN_CLICKED(ID_APPLY, OnApply)
	ON_BN_CLICKED(ID_EDIT, OnEdit)
	ON_BN_CLICKED(ID_NEW, OnNew)
	ON_BN_CLICKED(ID_REMOVE, OnRemove)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_MAIN, OnItemchangedListMain)
	ON_BN_CLICKED(IDC_STATIC_PATTERN, OnStaticPattern)
	ON_BN_CLICKED(ID_REFRESH, OnRefresh)
	ON_EN_CHANGE(IDC_EDIT_WALLPAPER, OnChangeEditWallpaper)
	ON_CBN_SELCHANGE(IDC_COMBO_WOPT, OnSelchangeComboWopt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CActiveDesktopDlg message handlers

BOOL CActiveDesktopDlg::OnInitDialog()
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
	

	Init();
	m_desktop.SetParent(m_hWnd);

	GetDlgItem(ID_APPLY)->EnableWindow(FALSE);
	GetDlgItem(ID_EDIT)->EnableWindow(m_bEditEnabled);
	GetDlgItem(ID_REMOVE)->EnableWindow(m_bRemoveEnabled);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CActiveDesktopDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CActiveDesktopDlg::OnPaint() 
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
HCURSOR CActiveDesktopDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CActiveDesktopDlg::OnCheckDesktop() 
{
	UpdateData(TRUE);	
	GetDlgItem(IDC_CHECK_COMPS)->EnableWindow(m_bDesktop);
	GetDlgItem(IDC_EDIT_WALLPAPER)->EnableWindow(m_bDesktop);
	GetDlgItem(IDC_LIST_MAIN)->EnableWindow(m_bDesktop);
	GetDlgItem(IDC_STATIC_PATTERN)->EnableWindow(m_bDesktop);
	GetDlgItem(ID_NEW)->EnableWindow(m_bDesktop);
	GetDlgItem(ID_EDIT)->EnableWindow(m_bDesktop?m_bEditEnabled:FALSE);
	GetDlgItem(ID_REMOVE)->EnableWindow(m_bDesktop?m_bRemoveEnabled:FALSE);
	GetDlgItem(IDC_STATIC_PATTERN_NAME)->EnableWindow(m_bDesktop);
	GetDlgItem(IDC_STATIC_WALLPAPER)->EnableWindow(m_bDesktop);
	GetDlgItem(IDC_STATIC_FILENAME)->EnableWindow(m_bDesktop);
	GetDlgItem(IDC_COMBO_WOPT)->EnableWindow(m_bDesktop);
	GetDlgItem(IDC_EDIT_WALLPAPER)->EnableWindow(m_bDesktop);
	GetDlgItem(IDC_STATIC_MAIN)->EnableWindow(m_bDesktop);
	GetDlgItem(IDC_STATIC_WALL)->EnableWindow(m_bDesktop);

	GetDlgItem(ID_APPLY)->EnableWindow(TRUE);
}

void CActiveDesktopDlg::OnCheckComps() 
{
	UpdateData(TRUE);	
	GetDlgItem(ID_APPLY)->EnableWindow(TRUE);
}

void CActiveDesktopDlg::OnApply() 
{
	UpdateData(TRUE);
	ApplyChanges();
	GetDlgItem(ID_APPLY)->EnableWindow(FALSE);
	OnRefresh();
}

void CActiveDesktopDlg::OnEdit() 
{
	UpdateData(TRUE);	
	POSITION pos=m_lstMain.GetFirstSelectedItemPosition();
	if (pos==NULL)
		return;

	int nNumber=m_lstMain.GetNextSelectedItem(pos);
	CString sSource=m_lstMain.GetItemText(nNumber,1);
	LPCOMPONENT pComp=m_desktop.GetComponent((LPCTSTR) sSource);
	if (!pComp)
	{
		AfxMessageBox(_T("Error to get the item"));
		return;
	}
	m_dlgComp.m_bEnabled=pComp->fChecked;
	m_dlgComp.m_bScrollable=(pComp->fNoScroll)?FALSE:TRUE;
	m_dlgComp.m_bSizeable=pComp->cpPos.fCanResize;
	m_dlgComp.m_nAction=CCompDialog::ACTION_MODIFY;
	m_dlgComp.m_nHeight=pComp->cpPos.dwHeight;
	m_dlgComp.m_nLeft=pComp->cpPos.iLeft;
	m_dlgComp.m_nTop=pComp->cpPos.iTop;
	m_dlgComp.m_nWidth=pComp->cpPos.dwWidth;
	LPTSTR lpszName=GetTcharString(pComp->wszFriendlyName);
	
	m_dlgComp.m_sName=lpszName;
	delete [] lpszName;
	LPTSTR lpszSource=GetTcharString(pComp->wszSource);
	m_dlgComp.m_sSource=lpszSource;
	delete [] lpszSource;

	if (m_dlgComp.DoModal()==IDOK)
	{
		pComp->fChecked=m_dlgComp.m_bEnabled;
		pComp->fNoScroll=m_dlgComp.m_bScrollable?FALSE:TRUE;
		pComp->cpPos.fCanResize=pComp->cpPos.fCanResizeX=
			pComp->cpPos.fCanResizeY=m_dlgComp.m_bSizeable;
		pComp->cpPos.dwHeight=m_dlgComp.m_nHeight;
		pComp->cpPos.iLeft=m_dlgComp.m_nLeft;
		pComp->cpPos.iTop=m_dlgComp.m_nTop;
		pComp->cpPos.dwWidth=m_dlgComp.m_nWidth;
		LPWSTR lpszwName=GetWcharString((LPCTSTR) m_dlgComp.m_sName);
		UTBStr::wcscpy(pComp->wszFriendlyName, MAX_PATH, lpszwName);
		delete [] lpszwName;
		if (!m_desktop.ModifyItem(pComp))
			AfxMessageBox(_T("Error to modify the item."));
		else
			m_desktop.ApplyChanges();
	}
	delete pComp;

	OnRefresh();
}

void CActiveDesktopDlg::OnNew() 
{
	UpdateData(TRUE);
	m_dlgComp.m_nAction=CCompDialog::ACTION_NEW;
	if (m_dlgComp.DoModal()==IDOK)
	{
		COMPONENT comp;
		::ZeroMemory(&comp, sizeof(comp));

		comp.dwSize=sizeof(comp);
		comp.fChecked=m_dlgComp.m_bEnabled;
		comp.fNoScroll=(m_dlgComp.m_bScrollable)?FALSE:TRUE;
		comp.fDirty=TRUE;
		comp.iComponentType=COMP_TYPE_WEBSITE;
		LPWSTR lpszwName=GetWcharString((LPCTSTR) m_dlgComp.m_sName);
		ASSERT(lpszwName);
		UTBStr::wcscpy(comp.wszFriendlyName, MAX_PATH, lpszwName);
		delete [] lpszwName;
		LPWSTR lpszSource=GetWcharString((LPCTSTR) m_dlgComp.m_sSource);
		UTBStr::wcscpy(comp.wszSource, INTERNET_MAX_URL_LENGTH, lpszSource);
		delete [] lpszSource;
		comp.cpPos.dwSize=sizeof(comp.cpPos);
		comp.cpPos.dwHeight=m_dlgComp.m_nHeight;
		comp.cpPos.dwWidth=m_dlgComp.m_nWidth;
		comp.cpPos.fCanResize=m_dlgComp.m_bSizeable;
		comp.cpPos.fCanResizeX=comp.cpPos.fCanResizeY=comp.cpPos.fCanResize;
		comp.cpPos.iLeft=m_dlgComp.m_nLeft;
		comp.cpPos.iTop=m_dlgComp.m_nTop;
		if (!m_desktop.AddItem(&comp))
			AfxMessageBox(_T("Error to create new item!"));
	}

}

void CActiveDesktopDlg::OnRemove() 
{
	UpdateData(TRUE);	
	POSITION pos=m_lstMain.GetFirstSelectedItemPosition();
	if (pos==NULL)
		return;

	int nNumber=m_lstMain.GetNextSelectedItem(pos);
	CString sSource=m_lstMain.GetItemText(nNumber,1);
	LPCOMPONENT pComp=m_desktop.GetComponent((LPCTSTR) sSource);

	if (!m_desktop.RemoveItem(pComp))
		AfxMessageBox(_T("Error to delete the item"));
	
	delete pComp;
	
	UpdateData(TRUE);	
	OnRefresh();
}

void CActiveDesktopDlg::OnItemchangedListMain(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if ((pNMListView->uNewState ^ pNMListView->uOldState)
		& 0x3000)
	{
		GetDlgItem(ID_APPLY)->EnableWindow(TRUE);
	}
	if (m_lstMain.GetSelectedCount())
	{
		m_bEditEnabled=TRUE;
		m_bRemoveEnabled=TRUE;
	}
	else
	{
		m_bEditEnabled=FALSE;
		m_bRemoveEnabled=FALSE;
	}
	GetDlgItem(ID_EDIT)->EnableWindow(m_bEditEnabled);
	GetDlgItem(ID_REMOVE)->EnableWindow(m_bRemoveEnabled);

	*pResult = 0;
}

void CActiveDesktopDlg::OnStaticPattern() 
{
	UpdateData(TRUE);	
}

void CActiveDesktopDlg::OnOK() 
{
	OnApply();
	
	CDialog::OnOK();
}

BOOL CActiveDesktopDlg::Init()
{
	CRect rct;
	m_lstMain.GetClientRect(&rct);
	m_lstMain.InsertColumn(0,_T("Name"),LVCFMT_LEFT,rct.Width()/2);
	m_lstMain.InsertColumn(1,_T("URL"),LVCFMT_LEFT,rct.Width()/2);
	DWORD dwExStyle=m_lstMain.GetExtendedStyle();
	m_lstMain.SetExtendedStyle(dwExStyle | 
		LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	if (!m_desktop.Init())
	{
		AfxMessageBox(_T(
			"Initialization failed. \
Make sure you have installed Active Desktop \
(shell.dll version 4.71 or better)"));
		return FALSE;
	}
	OnRefresh();

	return TRUE;

}

void CActiveDesktopDlg::UpdatePattern()
{

	if (HBITMAP(m_bitmap))
		m_bitmap.DeleteObject();

	BYTE* pPointer=(BYTE*) &m_bmp;

	for (int i=0; i<8; i++)
	{
		int nBit=1;
		for (int n=0; n<8; n++)
		{
			if (nBit & m_pattern[i])
			{
				for (int u=0; u<8; u++)
					*(pPointer+u*8)=0xFF;
			}
			else
			{
				for (int u=0; u<8; u++)
					*(pPointer+u*8)=0;
			}
			nBit=nBit<<1;
			pPointer++;
		}
		pPointer+=56;
	}
	
	VERIFY(m_bitmap.CreateBitmap(64,64,1,1,&m_bmp));

	m_stcPattern.SetBitmap(HBITMAP(m_bitmap));
	m_stcPattern.RedrawWindow();

}

void CActiveDesktopDlg::OnRefresh() 
{
	m_lstMain.DeleteAllItems();
	VERIFY(m_desktop.Refresh());
	VERIFY(m_desktop.IsDesktopEnabled(&m_bDesktop));
	VERIFY(m_desktop.IsComponentsEnabled(&m_bComps));
	CString sWallpaper;
	VERIFY(m_desktop.GetWallpaper(sWallpaper));
	m_edtWallpaper.SetWindowText((LPCTSTR) sWallpaper);
	m_nWOpt=m_desktop.GetWallpaperStyle();
	int nComps=m_desktop.GetItemCount();
	UpdateData(FALSE);
	for (int i=0;i<nComps;i++)
	{
		LPCOMPONENT pComp=m_desktop.GetComponent(i);
		ASSERT(pComp);
		LPTSTR lpszName=GetTcharString(pComp->wszFriendlyName);
		int n=m_lstMain.InsertItem(m_lstMain.GetItemCount(),lpszName);
		delete[]lpszName;
		lpszName=GetTcharString(pComp->wszSource);
		m_lstMain.SetItemText(n,1,lpszName);
		delete[] lpszName;
		m_lstMain.SetCheck(n,pComp->fChecked);
		delete pComp;
	}
	UpdateData(FALSE);
	
	
	VERIFY(m_desktop.GetPattern((BYTE*) &m_pattern));
	UpdatePattern();
	OnCheckDesktop();
	GetDlgItem(ID_APPLY)->EnableWindow(FALSE);
}

void CActiveDesktopDlg::ApplyChanges()
{
	if (!m_desktop.SetDesktopEnable(m_bDesktop))
	{
		AfxMessageBox(_T("Error to enable Active Desktop"));
		return;
	}
	if (!m_desktop.SetComponentsEnable(m_bComps))
	{
		AfxMessageBox(_T("Error to enable components"));
		return;
	}
	CString sWallpaper;
	m_edtWallpaper.GetWindowText(sWallpaper);
	if (!m_desktop.SetWallpaper(sWallpaper))
	{
		AfxMessageBox(_T("Error to set wallpaper"));
		return;

	}
	if (!m_desktop.SetWallpaperStyle(m_nWOpt))
	{
		AfxMessageBox(_T("Error to set wallpaper style"));
		return;

	}
	VERIFY(m_desktop.ApplyChanges());

	
	for (int i=0; i< m_lstMain.GetItemCount(); i++)
	{
		CString sSource=m_lstMain.GetItemText(i,1);
		LPCOMPONENT pComp=m_desktop.GetComponent(sSource);
		if (!pComp)
		{
			CString sText;
			sText.Format(_T("Couldnot get item %s"),sSource);
			AfxMessageBox(sText);
			continue;
		}
		if (pComp->fChecked!=m_lstMain.GetCheck(i))
		{
			pComp->fChecked=m_lstMain.GetCheck(i);
			if (!m_desktop.ModifyItem(pComp))
			{
				CString sText;
				sText.Format(_T("Couldnot modify item %s"),sSource);
				AfxMessageBox(sText);
			}
			else
				m_desktop.ApplyChanges();
			
		}
		delete pComp;
	}


}

void CActiveDesktopDlg::OnChangeEditWallpaper() 
{
	GetDlgItem(ID_APPLY)->EnableWindow(TRUE);
}

void CActiveDesktopDlg::OnSelchangeComboWopt() 
{
	GetDlgItem(ID_APPLY)->EnableWindow(TRUE);	
}
