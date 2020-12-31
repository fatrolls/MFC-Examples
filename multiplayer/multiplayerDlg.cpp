// multiplayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "multiplayer.h"
#include "multiplayerDlg.h"

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
// CMultiplayerDlg dialog

CMultiplayerDlg::CMultiplayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMultiplayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMultiplayerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_pSndMan = NULL;

}

void CMultiplayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMultiplayerDlg)
	DDX_Control(pDX, IDC_LISTEVENT, m_PlayEvenList);
	DDX_Control(pDX, IDC_COMBOPLAYLIST, m_comboPlayList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMultiplayerDlg, CDialog)
	//{{AFX_MSG_MAP(CMultiplayerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNNORMAL, OnBtnVMnormal)
	ON_BN_CLICKED(IDC_BTNFADEIN, OnBtnVMfadein)
	ON_BN_CLICKED(IDC_BTNFADEOUT, OnBtnVMfadeout)
	ON_BN_CLICKED(IDC_BTNPLAYNORMAL, OnBtnPMnormal)
	ON_BN_CLICKED(IDC_BTNPLAYLOOP, OnBtnPMloop)
	ON_BN_CLICKED(IDC_BTNPLAY, OnBtnStatusplay)
	ON_BN_CLICKED(IDC_BTNSTOP, OnBtnStatusstop)
	ON_BN_CLICKED(IDC_BTNSPEEDUP, OnBtnspeedup)
	ON_BN_CLICKED(IDC_BTNSPEEDDOWN, OnBtnspeeddown)
	ON_BN_CLICKED(IDC_BTNVOLUMEUP, OnBtnvolumeup)
	ON_BN_CLICKED(IDC_BTNVOLUMEDOWN, OnBtnvolumedown)
	ON_BN_CLICKED(IDC_BTNRIGHTUP, OnBtnrightup)
	ON_BN_CLICKED(IDC_BTNRIGHTDOWN, OnBtnrightdown)
	ON_BN_CLICKED(IDC_BTNLEFTUP, OnBtnleftup)
	ON_BN_CLICKED(IDC_BTNLEFTDOWN, OnBtnleftdown)
	ON_BN_CLICKED(IDC_BTNPANCENTER, OnBtnpancenter)
	ON_BN_CLICKED(IDC_PLAYALL, OnPlayall)
	ON_BN_CLICKED(IDC_STOPALL, OnStopall)
	ON_COMMAND(IDM_FILEOPEN, OnFileopen)
	ON_CBN_SELCHANGE(IDC_COMBOPLAYLIST, OnSelchangeComboplaylist)
	ON_BN_CLICKED(IDC_BTNRESET, OnBtnreset)
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(WM_DSBPLAYEND, OnDSBPlayEnd)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiplayerDlg message handlers

BOOL CMultiplayerDlg::OnInitDialog()
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
	
	// TODO: Add extra initialization here
	m_pSndMan = new CSoundManager(); 
    
	ASSERT(m_pSndMan);
    
	m_pSndMan->SetHwnd(this->GetSafeHwnd());
	BOOL bOK = m_pSndMan->Initialize();
	ASSERT(bOK);

	if(!bOK)
		return FALSE;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMultiplayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMultiplayerDlg::OnPaint() 
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
HCURSOR CMultiplayerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CMultiplayerDlg::OnBtnVMnormal() 
{
	// TODO: Add your control notification handler code here
    int nIndex = m_comboPlayList.GetCurSel();
    DWORD dwKey;

	if(nIndex != LB_ERR)
	{
		dwKey = m_comboPlayList.GetItemData(nIndex);
		m_pSndMan->SetVolumeMode(dwKey, VMODE_NORMAL);
	}
}


void CMultiplayerDlg::OnBtnVMfadein() 
{
	// TODO: Add your control notification handler code here
    int nIndex = m_comboPlayList.GetCurSel();
    DWORD dwKey;

	if(nIndex != LB_ERR)
	{
		dwKey = m_comboPlayList.GetItemData(nIndex);
		m_pSndMan->SetVolumeMode(dwKey, VMODE_FADEIN);
	}
}


void CMultiplayerDlg::OnBtnVMfadeout() 
{
	// TODO: Add your control notification handler code here
    int nIndex = m_comboPlayList.GetCurSel();
    DWORD dwKey;

	if(nIndex != LB_ERR)
	{
		dwKey = m_comboPlayList.GetItemData(nIndex);
		m_pSndMan->SetVolumeMode(dwKey, VMODE_FADEOUT);
	}
}

void CMultiplayerDlg::OnBtnPMnormal() 
{
	// TODO: Add your control notification handler code here
    int nIndex = m_comboPlayList.GetCurSel();
    DWORD dwKey;

	if(nIndex != LB_ERR)
	{
		dwKey = m_comboPlayList.GetItemData(nIndex);
		m_pSndMan->SetPlayMode(dwKey, PMODE_PLAY);
	}
}

void CMultiplayerDlg::OnBtnPMloop() 
{
	// TODO: Add your control notification handler code here
    int nIndex = m_comboPlayList.GetCurSel();
    DWORD dwKey;

	if(nIndex != LB_ERR)
	{
		dwKey = m_comboPlayList.GetItemData(nIndex);
		m_pSndMan->SetPlayMode(dwKey, PMODE_LOOP);
	}
}

void CMultiplayerDlg::OnBtnStatusplay() 
{
	// TODO: Add your control notification handler code here
    int nIndex = m_comboPlayList.GetCurSel();
    DWORD dwKey;

	if(nIndex != LB_ERR)
	{
		dwKey = m_comboPlayList.GetItemData(nIndex);
		m_pSndMan->StartPlay(dwKey);
	}
}

void CMultiplayerDlg::OnBtnStatusstop() 
{
	// TODO: Add your control notification handler code here
    int nIndex = m_comboPlayList.GetCurSel();
    DWORD dwKey;

	if(nIndex != LB_ERR)
	{
		dwKey = m_comboPlayList.GetItemData(nIndex);
		m_pSndMan->StopPlay(dwKey);
	}
}

void CMultiplayerDlg::OnBtnspeedup() 
{
	// TODO: Add your control notification handler code here
    int nIndex = m_comboPlayList.GetCurSel();
    DWORD dwKey;

	if(nIndex != LB_ERR)
	{
		dwKey = m_comboPlayList.GetItemData(nIndex);

		DWORD dwFreq;
		if(m_pSndMan->GetFrequency(dwKey, &dwFreq))
		{
             dwFreq += 100;
			 m_pSndMan->SetFrequency(dwKey, dwFreq);
		}
	}
}

void CMultiplayerDlg::OnBtnspeeddown() 
{
	// TODO: Add your control notification handler code here
    int nIndex = m_comboPlayList.GetCurSel();
    DWORD dwKey;

	if(nIndex != LB_ERR)
	{
		dwKey = m_comboPlayList.GetItemData(nIndex);

		DWORD dwFreq;
		if(m_pSndMan->GetFrequency(dwKey, &dwFreq))
		{
             dwFreq -= 100;
			 m_pSndMan->SetFrequency(dwKey, dwFreq);
		}
	}
}

void CMultiplayerDlg::OnBtnvolumeup() 
{
	// TODO: Add your control notification handler code here
    int nIndex = m_comboPlayList.GetCurSel();
    DWORD dwKey;

	if(nIndex != LB_ERR)
	{
		dwKey = m_comboPlayList.GetItemData(nIndex);

		LONG lVol;
		if(m_pSndMan->GetVolume(dwKey, &lVol))
		{
             lVol += 200;
			 m_pSndMan->SetVolume(dwKey, lVol);
		}
	}
}

void CMultiplayerDlg::OnBtnvolumedown() 
{
	// TODO: Add your control notification handler code here
    int nIndex = m_comboPlayList.GetCurSel();
    DWORD dwKey;

	if(nIndex != LB_ERR)
	{
		dwKey = m_comboPlayList.GetItemData(nIndex);

		LONG lVol;
		if(m_pSndMan->GetVolume(dwKey, &lVol))
		{
             lVol -= 200;
			 m_pSndMan->SetVolume(dwKey, lVol);
		}
	}
}


void CMultiplayerDlg::OnBtnleftup() 
{
	// TODO: Add your control notification handler code here
    int nIndex = m_comboPlayList.GetCurSel();
    DWORD dwKey;

	if(nIndex != LB_ERR)
	{
		dwKey = m_comboPlayList.GetItemData(nIndex);

		LONG lGain;
		if(m_pSndMan->GetPan(dwKey, &lGain))
		{
             lGain -= 200;
			 m_pSndMan->SetPan(dwKey, lGain);
		}
	}
}

void CMultiplayerDlg::OnBtnleftdown() 
{
	// TODO: Add your control notification handler code here
    int nIndex = m_comboPlayList.GetCurSel();
    DWORD dwKey;

	if(nIndex != LB_ERR)
	{
		dwKey = m_comboPlayList.GetItemData(nIndex);

		LONG lGain;
		if(m_pSndMan->GetPan(dwKey, &lGain))
		{
             lGain += 200;
			 m_pSndMan->SetPan(dwKey, lGain);
		}
	}
}


void CMultiplayerDlg::OnBtnrightup() 
{
	// TODO: Add your control notification handler code here
    int nIndex = m_comboPlayList.GetCurSel();
    DWORD dwKey;

	if(nIndex != LB_ERR)
	{
		dwKey = m_comboPlayList.GetItemData(nIndex);

		LONG lGain;
		if(m_pSndMan->GetPan(dwKey, &lGain))
		{
             lGain += 200;
			 m_pSndMan->SetPan(dwKey, lGain);
		}
	}
}

void CMultiplayerDlg::OnBtnrightdown() 
{
	// TODO: Add your control notification handler code here
    int nIndex = m_comboPlayList.GetCurSel();
    DWORD dwKey;

	if(nIndex != LB_ERR)
	{
		dwKey = m_comboPlayList.GetItemData(nIndex);

		LONG lGain;
		if(m_pSndMan->GetPan(dwKey, &lGain))
		{
             lGain -= 200;
			 m_pSndMan->SetPan(dwKey, lGain);
		}
	}
}

void CMultiplayerDlg::OnBtnpancenter() 
{
	// TODO: Add your control notification handler code here
    int nIndex = m_comboPlayList.GetCurSel();
    DWORD dwKey;

	if(nIndex != LB_ERR)
	{
		dwKey = m_comboPlayList.GetItemData(nIndex);

	    m_pSndMan->SetPan(dwKey, 0);
	}
}


void CMultiplayerDlg::OnBtnreset() 
{
	// TODO: Add your control notification handler code here
    int nIndex = m_comboPlayList.GetCurSel();
    DWORD dwKey;
	BOOL  bPlaying = FALSE;

	if(nIndex != LB_ERR)
	{
		dwKey = m_comboPlayList.GetItemData(nIndex);
		m_pSndMan->SetCurrentPosition(dwKey, 0);
        
		m_pSndMan->IsPlaying(dwKey, &bPlaying);
		if(bPlaying)
		    m_pSndMan->SetPlayMode(dwKey, PMODE_LOOP);
	}
}


void CMultiplayerDlg::OnPlayall() 
{
	// TODO: Add your control notification handler code here
	m_pSndMan->PlayAllSound();
}


void CMultiplayerDlg::OnStopall() 
{
	// TODO: Add your control notification handler code here
	m_pSndMan->StopAllSound();
}


void CMultiplayerDlg::OnFileopen() 
{
	// TODO: Add your command handler code here
	CString strFileName;
	DWORD   dwSndKey;
	char FileString[] = "Wave File(*.wav)\0*.wav\0\0";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_CREATEPROMPT|OFN_OVERWRITEPROMPT,NULL,NULL);
	dlg.m_ofn.lpstrFilter = (LPSTR)FileString;
    dlg.m_ofn.lpstrTitle = "Open Wave File";
	
	if(dlg.DoModal()==IDOK)
	{
		strFileName = dlg.GetFileTitle();
		strFileName += ".";
		strFileName += dlg.GetFileExt();
        LPSTR sName = strFileName.GetBuffer(strFileName.GetLength());

		if(m_pSndMan->LoadWaveFile(sName, &dwSndKey))
		{
			CString str;
			int     index;
            str.Format(_T("Sound #%d"), dwSndKey);
			index = m_comboPlayList.AddString(str);
            m_comboPlayList.SetItemData(index, dwSndKey);
			str += _T(" created!");
			m_PlayEvenList.AddString(str);
		}
		strFileName.ReleaseBuffer();
	}
}


void CMultiplayerDlg::OnSelchangeComboplaylist() 
{
	// TODO: Add your control notification handler code here
    int nIndex = m_comboPlayList.GetCurSel();
    DWORD dwKey;

	if(nIndex != LB_ERR)
	{
		dwKey = m_comboPlayList.GetItemData(nIndex);

        VOLUMEMODE vm;
		if(m_pSndMan->GetVolumeMode(dwKey, &vm))
		{
			switch(vm)
			{
			    case VMODE_NORMAL:
					 ((CButton*)GetDlgItem(IDC_BTNNORMAL))->SetCheck(1);
					 ((CButton*)GetDlgItem(IDC_BTNFADEIN))->SetCheck(0);
					 ((CButton*)GetDlgItem(IDC_BTNFADEOUT))->SetCheck(0);
                     break;
				case VMODE_FADEIN:
					 ((CButton*)GetDlgItem(IDC_BTNNORMAL))->SetCheck(0);
					 ((CButton*)GetDlgItem(IDC_BTNFADEIN))->SetCheck(1);
					 ((CButton*)GetDlgItem(IDC_BTNFADEOUT))->SetCheck(0);
                     break;
				case VMODE_FADEOUT:
					 ((CButton*)GetDlgItem(IDC_BTNNORMAL))->SetCheck(0);
					 ((CButton*)GetDlgItem(IDC_BTNFADEIN))->SetCheck(0);
					 ((CButton*)GetDlgItem(IDC_BTNFADEOUT))->SetCheck(1);
                     break;
                default:
					 break;
			}
		}


        PLAYMODE pm;
		if(m_pSndMan->GetPlayMode(dwKey, &pm))
		{
			switch(pm)
			{
			    case PMODE_WAIT:
				case PMODE_PLAY:
					 ((CButton*)GetDlgItem(IDC_BTNPLAYNORMAL))->SetCheck(1);
					 ((CButton*)GetDlgItem(IDC_BTNPLAYLOOP))->SetCheck(0);
                     break;
				case PMODE_LOOP:
					 ((CButton*)GetDlgItem(IDC_BTNPLAYNORMAL))->SetCheck(0);
					 ((CButton*)GetDlgItem(IDC_BTNPLAYLOOP))->SetCheck(1);
                     break;
                default:
					 break;
			}
		}

		BOOL  bPlay;
		if(m_pSndMan->IsPlaying(dwKey, &bPlay))
		{
			if(bPlay)
			{
			    ((CButton*)GetDlgItem(IDC_BTNPLAY))->SetCheck(1);
				((CButton*)GetDlgItem(IDC_BTNSTOP))->SetCheck(0);
			}
			else
			{
			    ((CButton*)GetDlgItem(IDC_BTNPLAY))->SetCheck(0);
				((CButton*)GetDlgItem(IDC_BTNSTOP))->SetCheck(1);
			}
		}
	}
}


LONG CMultiplayerDlg::OnDSBPlayEnd(UINT uiParam, LONG lParam)
{
	DWORD dwKey = (DWORD)uiParam;
    CString strText;
    strText.Format(_T("Sound #%d playing stop!"), dwKey);

	m_PlayEvenList.AddString(strText.GetBuffer(strText.GetLength()));
    strText.ReleaseBuffer();

	return 1L;
}


BOOL CMultiplayerDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_pSndMan)
		delete m_pSndMan;

	return CDialog::DestroyWindow();
}





