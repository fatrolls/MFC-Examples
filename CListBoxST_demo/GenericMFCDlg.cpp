#include "stdafx.h"
#include "GenericMFC.h"
#include "GenericMFCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDS_MAILADDR	_T("mailto:davide_calabro@yahoo.com")
#define IDS_WEBADDR		_T("http://www.softechsoftware.it")

CGenericMFCDlg::CGenericMFCDlg(CWnd* pParent /*=NULL*/)
	: CResizableDialog(CGenericMFCDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGenericMFCDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGenericMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGenericMFCDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_LBXST, m_lbxListBox);

	DDX_Control(pDX, IDCANCEL, m_btnExit);

	DDX_Control(pDX, IDC_EMAILLINK, m_EMailLink);
	DDX_Control(pDX, IDC_HOMEPAGELINK, m_HomePageLink);
}

BEGIN_MESSAGE_MAP(CGenericMFCDlg, CResizableDialog)
	//{{AFX_MSG_MAP(CGenericMFCDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CGenericMFCDlg::OnInitDialog()
{
	COLORREF	crBtnColor;

	CResizableDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	
	// Calculate a color effect for hilighting the button
	crBtnColor = ::GetSysColor(COLOR_BTNFACE) + RGB(30, 30, 30);

	// Button exit
	m_btnExit.SetThemeHelper(&m_Theme);
	m_btnExit.SetIcon(IDI_NO3, IDI_NO4);
	m_btnExit.SetColor(CButtonST::BTNST_COLOR_BK_IN, crBtnColor);
	m_btnExit.SetTooltipText(_T("Close the application"));

	// Set HyperLink for E-Mail
	m_EMailLink.SetURL(IDS_MAILADDR);
	m_EMailLink.SetUnderline(CHyperLink::ulAlways);

	// Set HyperLink for Home Page
	m_HomePageLink.SetURL(IDS_WEBADDR);
	m_HomePageLink.SetUnderline(CHyperLink::ulAlways);
	
	// Preset layout
	AddAnchor(m_btnExit.m_hWnd, BOTTOM_RIGHT);
	AddAnchor(m_EMailLink.m_hWnd, BOTTOM_LEFT);
	AddAnchor(m_HomePageLink.m_hWnd, BOTTOM_LEFT);
	AddAnchor(m_lbxListBox.m_hWnd, TOP_LEFT, BOTTOM_RIGHT);

	CreateImageList();

	// Associate image list to list box
	m_lbxListBox.SetImageList(&m_ImageList);

	m_lbxListBox.AddString(_T("Copia le immagini in una cartella nel computer\nutilizzando Acquisizione guidata immagini"), 0);
	m_lbxListBox.AddString(_T("Visualizza una presentazione delle immagini\nutilizzando Visualizzatore immagini e fax per Windows"), 1);
	m_lbxListBox.AddString(_T("Stampa immagini\nutilizzando Stampa guidata foto (Disabled)"), 2);
	m_lbxListBox.AddString(_T("Apri cartelle per visualizzare i file\nutilizzando esplora risorse"), 3);
	m_lbxListBox.AddString(_T("Nessuna operazione"), 4);
	m_lbxListBox.AddString(_T("Play\nutilizzando Windows Media Player"), 5);

	m_lbxListBox.EnableItem(2, FALSE);

	return TRUE;
} // End of OnInitDialog

void CGenericMFCDlg::CreateImageList()
{
	BOOL	bRetValue = FALSE;
	HICON	hIcon = NULL;

	// Create image list
	bRetValue = m_ImageList.Create(32, 32, ILC_COLOR32 | ILC_MASK, 5, 1);
	ASSERT(bRetValue == TRUE);

	// Add some icons
	hIcon = AfxGetApp()->LoadIcon(IDI_SHELL32_203);
	m_ImageList.Add(hIcon);
	hIcon = AfxGetApp()->LoadIcon(IDI_SHELL32_141);
	m_ImageList.Add(hIcon);
	hIcon = AfxGetApp()->LoadIcon(IDI_SHELL32_137);
	m_ImageList.Add(hIcon);
	hIcon = AfxGetApp()->LoadIcon(IDI_SHELL32_005);
	m_ImageList.Add(hIcon);
	hIcon = AfxGetApp()->LoadIcon(IDI_SHELL32_110);
	m_ImageList.Add(hIcon);
	hIcon = AfxGetApp()->LoadIcon(IDI_SHELL32_131);
	m_ImageList.Add(hIcon);
} // End of CreateImageList
