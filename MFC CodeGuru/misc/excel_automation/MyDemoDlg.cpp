// MyDemoDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "MyDemo.h"
#include "MyDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg-Dialogfeld für Anwendungsbefehl "Info"

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
// CMyDemoDlg Dialogfeld

CMyDemoDlg::CMyDemoDlg(CWnd* pParent /*=NULL*/)
: CDialog(CMyDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDemoDlg)
	// HINWEIS: Der Klassenassistent fügt hier Member-Initialisierung ein
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDemoDlg)
	// HINWEIS: Der Klassenassistent fügt an dieser Stelle DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyDemoDlg, CDialog)
//{{AFX_MSG_MAP(CMyDemoDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDemoDlg Nachrichten-Handler

BOOL CMyDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Hinzufügen des Menübefehls "Info..." zum Systemmenü.
	
	// IDM_ABOUTBOX muss sich im Bereich der Systembefehle befinden.
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
	
	// Symbol für dieses Dialogfeld festlegen. Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden
	
	// ZU ERLEDIGEN: Hier zusätzliche Initialisierung einfügen
	
	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

void CMyDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMyDemoDlg::OnPaint() 
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
HCURSOR CMyDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMyDemoDlg::OnButton1() 
{
	CFileDialog dlg(TRUE);
	
	if (dlg.DoModal()==IDOK)
	{
		CString FullPathName = dlg.GetPathName();
		OpenExcel();  // may be called more than one time 
		DoExcelConversion(FullPathName); 
		CloseExcel(); // may be called without a preceeding OpenExcel() 
	}
}

bool CMyDemoDlg::OpenExcel()
{
	if (!m_bExcelStarted)
		if (m_Excel.CreateDispatch("Excel.Application"))
		{
			//
			// un-comment these lines, is you want to see what Excel is doing
			//
			//			CWnd *pExelWnd = CWnd::FindWindow("XLMAIN", NULL);
			//			if (pExelWnd )
			//			{
			//				pExelWnd->ShowWindow(SW_SHOWNORMAL);
			//				pExelWnd->UpdateWindow();
			//				pExelWnd->BringWindowToTop();
			//			}			
			//			BringWindowToTop();
			m_bExcelStarted=true;
		}
		return m_bExcelStarted;
}

bool CMyDemoDlg::CloseExcel()
{
	if (m_bExcelStarted)
	{
		m_Excel.Quit();
		m_Excel.ReleaseDispatch();
		m_bExcelStarted=false;
	}
	return m_bExcelStarted;
}

void CMyDemoDlg::DoExcelConversion(CString File)
{ 
    CString XlsFile="C:\\temp\\demo.xls"; 
	
    COleVariant FilenameOpen(File), 
        FilenameSave(XlsFile), 
        Origin((short)2), // xlWindows 
        StartRow((short)1), 
        DataType((short)1), // xlDelimited 
        TextQualifier((short)1), // xlDoubleQuote 
        ConsecutiveDelimiter((long)FALSE, VT_BOOL), 
        Tab((long)FALSE, VT_BOOL), 
        Semicolon((long)TRUE, VT_BOOL), 
        Fileformat((short)33), // xlExcel4 
        Save((long)FALSE, VT_BOOL); 
	
    TRY 
    { 
		Workbooks Wbs(m_Excel.Workbooks()); 
		
		Wbs.OpenText(FilenameOpen, Origin, StartRow, DataType, 
            TextQualifier, ConsecutiveDelimiter, Tab, Semicolon); 
		
		Range ran(m_Excel.Columns(COleVariant("A:Z"))); 
		
		ran.AutoFit(); 
		
		Workbook Wb(m_Excel.Workbooks(COleVariant((short)1))); 
		
		Wb.SaveAs(FilenameSave, Fileformat); 
		
		Wb.Close(Save); 
		
		// perhaps you want to delete the text file, 
		// because now you have an Excel sheet 
		// DeleteFile(File); 
    } 
    CATCH(COleDispatchException, e) 
    { 
		TRACE(e->m_strDescription); 
		MessageBox("Error creating Excel-file:\n"+e->m_strDescription, 
            "My Demo Dialog", MB_OK); 
    } 
    END_CATCH; 
}
