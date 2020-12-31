// AutoCompleteDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "AutoComplete.h"
#include "AutoCompleteDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg-Dialogfeld für Anwendungsbefehl "Info"

void DoMessageLoop()
{
	MSG message1;
	while(::PeekMessage(&message1,NULL,0,0, PM_REMOVE))
		{
		::TranslateMessage(&message1);
		::DispatchMessage(&message1);
		}
}

/*********************************************************************/

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialogfelddaten
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
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
		// Keine Nachrichten-Handler
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoCompleteDlg Dialogfeld

CAutoCompleteDlg::CAutoCompleteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAutoCompleteDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAutoCompleteDlg)
	m_EditText = _T("");
	m_Verzeichnis = _T("");
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Verzeichnis = _T("C:\\");
#ifdef _DEBUG
	m_Verzeichnis = _T("C:\\Temp\\");
#endif
}

CAutoCompleteDlg::~CAutoCompleteDlg()
{
}

void CAutoCompleteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAutoCompleteDlg)
	DDX_Control(pDX, IDC_EDIT10, m_VerzEdit5);
	DDX_Control(pDX, IDC_EDIT9, m_VerzEdit4);
	DDX_Control(pDX, IDC_EDIT7, m_VerzEdit3);
	DDX_Control(pDX, IDC_EDIT6, m_VerzEdit2);
	DDX_Control(pDX, IDC_EDIT5, m_VerzEdit);
	DDX_Control(pDX, IDC_EDIT4, m_ACEdit1);
	DDX_Control(pDX, IDC_EDIT3, m_MEditCtrl);
	DDX_Control(pDX, IDC_COMBO2, m_ComboBox2);
	DDX_Control(pDX, IDC_COMBO1, m_ComboBox);
	DDX_Control(pDX, IDC_EDIT2, m_EditCtrl2);
	DDX_Control(pDX, IDC_LIST1, m_ListeBox);
	DDX_Control(pDX, IDC_EDIT1, m_EditCtrl1);
	DDX_Text(pDX, IDC_EDIT1, m_EditText);
	DDX_Text(pDX, IDC_EDIT8, m_Verzeichnis);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAutoCompleteDlg, CDialog)
	//{{AFX_MSG_MAP(CAutoCompleteDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, OnDirAuswahl)
	//}}AFX_MSG_MAP
	ON_MESSAGE(ENAC_UPDATE,OnUpdateEdit2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoCompleteDlg Nachrichten-Handler

BOOL CAutoCompleteDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_EditCtrl1.Init();
	m_EditCtrl2.Init();
	m_ComboBox.Init();
	m_ComboBox2.Init();
	m_MEditCtrl.Init();

	//m_EditCtrl1.SetMode(_MODE_FIND_ALL_);
	m_EditCtrl2.SetMode(_MODE_CURSOR_O_LIST_);
	
	m_VerzEdit.Init();
	m_VerzEdit2.Init();
	m_VerzEdit3.Init();
	m_VerzEdit4.Init();
	m_VerzEdit5.Init();
	
	m_VerzEdit.SetMode(_MODE_FILESYSTEM_);
	m_VerzEdit2.SetMode(_MODE_FS_ONLY_FILE_);
	m_VerzEdit3.SetMode(_MODE_FS_ONLY_DIR_);
	m_VerzEdit4.SetMode(_MODE_FS_START_DIR_);
	m_VerzEdit5.SetMode(_MODE_SD_ONLY_FILE_);

	m_VerzEdit4.SetStartDirectory(m_Verzeichnis);
	m_VerzEdit5.SetStartDirectory(m_Verzeichnis);

	static LPCTSTR STRINGS[] = 
		{
		_T("Textstart"),
		_T("Textend"),
		_T("One1"),
		_T("One12"),
		_T("One"),
		_T("Lemon"),
		_T("Apple"),
		_T("Pear"),
		_T("Melon"),
		_T("Apricot"),

		"<INSTALLDIR>",
		"<WINDOWS>",
		"<SYSTEM>",
		"<DESKTOP>",
		"<SENDTO>",
		"<AUTOSTART>",
		"<PROGRAMDIR>",
		"<STARTMENU>",
		"<TEMPDIR>",
		"<PRODUCTNAME>",
		"<STARTMENU_A_U>",
		"<SETUPDIR>",
		
		"<DESKTOP_A_U>",
		"<AUTOSTART_A_U>",
		"<FAVORITES>",
		"<FAVORITES_A_U>",
	
		"<REG_PATH1>",
		"<REG_PATH2>",
		"<REG_PATH3>",
		"<REG_PATH4>",
		"<REG_PATH5>",

	
		"<FONTS>",
		"<PERSONALDIR>",
		"<APPDATA>",
		"<APPDATA_A_U>",
	
		"<COMMONFILESDIR>",
	
		"<DATA_PATH1>",
		"<DATA_PATH2>",
		"<DATA_PATH3>",

		NULL
		};

	m_EditCtrl1.AddSearchStrings(STRINGS);
	m_EditCtrl2.AddSearchStrings(STRINGS);
	m_ComboBox.AddSearchStrings(STRINGS);
	m_ComboBox2.AddSearchStrings(STRINGS);
	m_MEditCtrl.AddSearchStrings(STRINGS);

	for (int i=0; STRINGS[i]; i++)
		{
		m_ListeBox.AddString(STRINGS[i]);
		}

	m_EditCtrl1.SetSeparator("\\");
	m_MEditCtrl.SetSeparator("\\");
	m_ComboBox2.SetSeparator("\\");
	

	m_ACEdit1.Init();
	m_ACEdit1.AddSearchString("PRODUCTNAME>");
	m_ACEdit1.AddSearchString("PRODUCTVERSION>");
	m_ACEdit1.AddSearchString("DATE>");
	m_ACEdit1.AddSearchString("DATE1>");
	m_ACEdit1.SetSeparator("< ",'<');



	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

void CAutoCompleteDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// Wollen Sie Ihrem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch für Sie erledigt.

void CAutoCompleteDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext für Zeichnen

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Symbol in Client-Rechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Die Systemaufrufe fragen den Cursorform ab, die angezeigt werden soll, während der Benutzer
//  das zum Symbol verkleinerte Fenster mit der Maus zieht.
HCURSOR CAutoCompleteDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAutoCompleteDlg::OnUpdateEdit1() 
{
	UpdateData(true);
	
	SetWindowText(m_EditText);
	ASSERT(0);	
			/*
			if(sel >= 0)
				{
				if(m_Liste->GetText(sel, m_Text2))
					{
					sel = m_EditText.GetLength();
					m_EditText = m_Text2;
					UpdateData(false);
					m_EditCtrl.SetSel(sel,m_EditText.GetLength());
					}
				}
				*/
}

/*********************************************************************/

BOOL CAutoCompleteDlg::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult) 
{
	TRACE("message = %ld\n",message);
	return CDialog::OnChildNotify(message, wParam, lParam, pLResult);
}

/*********************************************************************/

LONG CAutoCompleteDlg::OnUpdateEdit2(UINT lParam, LONG wParam)
	{
	UpdateData(true);
	
	if(wParam == IDC_EDIT1)
		SetWindowText(m_EditText);
	return 0;
	}

/*********************************************************************/

void CAutoCompleteDlg::OnOK() 
{
}

/*********************************************************************/

int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM dwData)
{
	switch(uMsg)
		{
		case BFFM_INITIALIZED:
			{
			::SendMessage( hwnd, 
				BFFM_SETSELECTION, 
				TRUE, 
				LPARAM(dwData));
			}
			break;
		}
	return 0;
}

/**********************************************************************/

void CAutoCompleteDlg::OnDirAuswahl() 
{
	LPMALLOC lpMalloc;
	BROWSEINFO browseInfo;
	bool m_bAuswahl = false;

	lstrcpy(szDirectory,m_Verzeichnis.GetBuffer(0));
	ZeroMemory( &browseInfo, sizeof(browseInfo));
	browseInfo.hwndOwner		= m_hWnd; 
	browseInfo.pszDisplayName	= szDirectory; 
	browseInfo.lpszTitle		= _T("Wählen Sie das Ziel-Verzeichnis");
	browseInfo.ulFlags			= BIF_RETURNONLYFSDIRS|BIF_NEWDIALOGSTYLE; 
	browseInfo.lpfn				= BFFCALLBACK( BrowseCallbackProc );
	browseInfo.lParam			= (long)szDirectory; 
	
	//Display Common Dialog to obtain File To Load...
	ITEMIDLIST* pidl = SHBrowseForFolder(&browseInfo);
	if(pidl)
		{
		//Obtain the file path from the ITemID...
		if(SHGetPathFromIDList(pidl, szDirectory))
			{
			
			if (!SHGetMalloc(&lpMalloc) && (NULL != lpMalloc))
				{
				if (NULL != pidl)
					{
					lpMalloc->Free(pidl);
					}
				
				lpMalloc->Release();
				}
			m_bAuswahl = true;
			}		
		}

	if(!m_bAuswahl)
		return;

	m_Verzeichnis = szDirectory;
	if (m_Verzeichnis.Right(1) != '\\')
		m_Verzeichnis += _T("\\");
	UpdateData(false);

	m_VerzEdit4.SetStartDirectory(m_Verzeichnis);
	m_VerzEdit5.SetStartDirectory(m_Verzeichnis);
}

/*********************************************************************/

