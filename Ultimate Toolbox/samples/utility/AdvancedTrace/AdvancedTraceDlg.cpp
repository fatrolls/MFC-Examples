// AdvancedTraceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AdvancedTrace.h"
#include "AdvancedTraceDlg.h"

#include "UTSampleAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdvancedTraceDlg dialog

CAdvancedTraceDlg::CAdvancedTraceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAdvancedTraceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAdvancedTraceDlg)
	m_bChecked = FALSE;
	m_nComboItem = -1;
	m_sListBoxItem = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	pTrace=NULL;
}

void CAdvancedTraceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdvancedTraceDlg)
	DDX_Control(pDX, IDC_LISTCTRL, m_listCtrl);
	DDX_Control(pDX, IDC_LISTBOX, m_listBox);
	DDX_Control(pDX, IDC_OUTPUT_FILE2, m_linkOutputFile);
	DDX_Control(pDX, IDC_OUTPUT_FILE1, m_staticOutputFile);
	DDX_Control(pDX, IDC_SEPARATOR2, m_separator2);
	DDX_Control(pDX, IDC_SEPARATOR1, m_separator1);
	DDX_Check(pDX, IDC_CHECK, m_bChecked);
	DDX_CBIndex(pDX, IDC_COMBO, m_nComboItem);
	DDX_LBString(pDX, IDC_LISTBOX, m_sListBoxItem);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAdvancedTraceDlg, CDialog)
	//{{AFX_MSG_MAP(CAdvancedTraceDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON, OnButton)
	ON_BN_CLICKED(IDC_CHECK, OnCheck)
	ON_CBN_SELCHANGE(IDC_COMBO, OnSelchangeCombo)
	ON_EN_CHANGE(IDC_EDIT, OnChangeEdit)
	ON_LBN_SELCHANGE(IDC_LISTBOX, OnSelchangeListbox)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTCTRL, OnItemchangedListctrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdvancedTraceDlg message handlers

BOOL CAdvancedTraceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	{
		// put the following code in brackets in order to destroy COXTrace 
		// object before intantianting the new one

		OXTRACE(_T("Initialize dialog data"));

		OXTRACE_WRITE(_T("Add 'About...' menu item to system menu."));
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
		OXTRACE_WRITE(_T("Initialize controls"));

		OXTRACE_WRITE(_T("Setup static controls"));
		////////////////////////////////
		m_separator2.SetTextColor(::GetSysColor(COLOR_WINDOW));
		LOGFONT lf;
		GetFont()->GetObject(sizeof(lf), &lf);
		lf.lfWeight=1000;
		lf.lfHeight=-16;
		CFont font;
		font.CreateFontIndirect(&lf);
		m_staticOutputFile.SetTextFont(&font);

		m_linkOutputFile.SetToolTipText(_T("Click to open output file"));
		m_linkOutputFile.SetAction(ID_HLACTION_OPEN,_T("TraceTest.txt"));
		////////////////////////////////

		OXTRACE_WRITE(_T("Populate common controls with data"));
		////////////////////////////////
		// populate list control
		CString sColumnText;
		CString sItemText;
		for (int nColumn=0; nColumn<6; nColumn++)
		{
			sColumnText.Format(_T("Column %d"),nColumn+1);
			m_listCtrl.InsertColumn(nColumn,sColumnText,LVCFMT_LEFT,100);

			for(int nRow=0; nRow<10; nRow++)
			{
				sItemText.Format(_T("Item %d in column %d"),nRow+1,nColumn+1);
				if(nColumn==0)
					m_listCtrl.InsertItem(nRow,sItemText,0);
				else
					m_listCtrl.SetItem(nRow,nColumn,LVIF_TEXT,
						sItemText,NULL,NULL,NULL,NULL);
			}
		}
		/////////////////////////////////


		
		// populate listbox control
		for (int nIndex=0; nIndex<10; nIndex++)
		{
			sItemText.Format(_T("Listbox item %d"),nIndex+1);
			m_listBox.AddString(sItemText);
		}
		/////////////////////////////////

		// the COXTrace object created using OXTRACE macro will be destroyed 
		// when it is out of scope
	}


	////////////////////////////////

	pTrace=new COXTrace(_T("Demo Dialog"));

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAdvancedTraceDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		OXTRACE(_T("Display About Dialog"));
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

void CAdvancedTraceDlg::OnPaint() 
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
HCURSOR CAdvancedTraceDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAdvancedTraceDlg::OnButton() 
{
	// TODO: Add your control notification handler code here
	ASSERT(pTrace!=NULL);
	pTrace->Write(_T("Button has been clicked"));
}

void CAdvancedTraceDlg::OnCheck() 
{
	// TODO: Add your control notification handler code here
	ASSERT(pTrace!=NULL);
	UpdateData();
	pTrace->Write(_T("Button has been "),
		(m_bChecked ? _T("checked") : _T("unchecked")));
}

void CAdvancedTraceDlg::OnSelchangeCombo() 
{
	// TODO: Add your control notification handler code here
	ASSERT(pTrace!=NULL);
	UpdateData();
	pTrace->WriteFormatted(_T("Current item in combo box changed to: %d"),
		m_nComboItem);
}

void CAdvancedTraceDlg::OnChangeEdit() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
	ASSERT(pTrace!=NULL);
	UpdateData();
	pTrace->Write(_T("The contents of the edit control has been changed"));
}

void CAdvancedTraceDlg::OnSelchangeListbox() 
{
	// TODO: Add your control notification handler code here
	ASSERT(pTrace!=NULL);
	UpdateData();
	pTrace->WriteFormatted(_T("Current item in list box changed to: %s"),
		m_sListBoxItem);
}

void CAdvancedTraceDlg::OnItemchangedListctrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	ASSERT(pTrace!=NULL);
	UpdateData();
	pTrace->WriteFormatted(_T("The state of %d item has been changed in the list control"),
		pNMListView->iItem);

	*pResult = 0;
}

void CAdvancedTraceDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	if(pTrace!=NULL)
	{
		pTrace->Write(_T("State of dialog object:"),*this);
		delete pTrace;
		pTrace=NULL;
	}

	CDialog::OnOK();
}

void CAdvancedTraceDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	if(pTrace!=NULL)
	{
		pTrace->Write(_T("State of dialog object before closing:"),*this);
		delete pTrace;
		pTrace=NULL;
	}

	CDialog::OnCancel();
}
