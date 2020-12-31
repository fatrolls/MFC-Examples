// CustomURLProtocolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CustomURLProtocol.h"
#include "CustomURLProtocolDlg.h"
#include <Strsafe.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCustomURLProtocolDlg dialog
CCustomURLProtocolDlg::CCustomURLProtocolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomURLProtocolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCustomURLProtocolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_PROTOCOL_NAME, m_ProtocolName);
	DDX_Control(pDX, IDC_EDT_COMPANY_NAME, m_CompanyName);
	DDX_Control(pDX, IDC_EDT_APP_PATH, m_AppPath);
}

BEGIN_MESSAGE_MAP(CCustomURLProtocolDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BROWSE, &CCustomURLProtocolDlg::OnBnClickedBrowse)
	ON_BN_CLICKED(IDOK, &CCustomURLProtocolDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_TEST, &CCustomURLProtocolDlg::OnBnClickedBtnTest)
	ON_BN_CLICKED(IDCANCEL, &CCustomURLProtocolDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CCustomURLProtocolDlg::OnBnClickedBtnDelete)
END_MESSAGE_MAP()


// CCustomURLProtocolDlg message handlers

BOOL CCustomURLProtocolDlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCustomURLProtocolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
void CCustomURLProtocolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCustomURLProtocolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCustomURLProtocolDlg::OnBnClickedBrowse()
{
	CFileDialog FileDialog(TRUE, L"*.*", NULL, OFN_HIDEREADONLY,L"Executable Files: (*.exe)|*.exe||");

	if(FileDialog.DoModal() == IDOK)
	{
		CString szPath = FileDialog.GetPathName().GetBuffer();
		m_AppPath.SetWindowTextW(szPath);
	}
}

void CCustomURLProtocolDlg::initializeParameter()
{
	CString szProtocolName;
	CString szCompanyName;
	CString szAppPath;

	m_ProtocolName.GetWindowTextW(szProtocolName);
	m_CompanyName.GetWindowTextW(szCompanyName);
	m_AppPath.GetWindowTextW(szAppPath);

	m_CustomURLProtocol.setProtocolName(szProtocolName.GetBuffer());
	m_CustomURLProtocol.setCompanyName(szCompanyName.GetBuffer());
	m_CustomURLProtocol.setAppPath(szAppPath.GetBuffer());
}

void CCustomURLProtocolDlg::OnBnClickedOk()
{
	DWORD errorCode = 0;
	// Initialize Custom Protocol Class Parameter
	initializeParameter();
	// Delete Custom Protocol if already present
	m_CustomURLProtocol.DeleteCustomProtocol();
	// Create new Custom protocol 
	if(m_CustomURLProtocol.CreateCustomProtocol() != ERROR_SUCCESS)
		MessageBox(m_CustomURLProtocol.getErrorMsg().c_str());
	else
		MessageBox(L"Successfully Created Custom Protocol.");
}

std::string WStringToString(const std::wstring& s)
{
	std::string temp(s.length(), ' ');
	std::copy(s.begin(), s.end(), temp.begin());
	return temp;
}

CString CCustomURLProtocolDlg::CreateHtmlFile()
{
	std::wstring str(L"<html xmlns=\"http://www.w3.org/1999/xhtml\"><head><title>Launch Custom URL \
</title><script type=\"text/javascript\">function LaunchURLScript(){var url = \"");

	str.append(m_CustomURLProtocol.getProtocolName());
	str.append(L":\";window.open(url);self.focus();}</script></head><body  style= \"background-color:#D7D7D7\">	\
<input type=\"submit\" name=\"Launch\" id=\"Launch\" value=\"Launch Custom URL\" onClick=\"LaunchURLScript()\"  />	\
</body></html>");

	//Get Temp Path
	WCHAR TempPath[MAX_PATH];
	GetTempPathW(MAX_PATH, TempPath);
	wcscat_s(TempPath,MAX_PATH,L"\\Test.html");

	std::string str1 = WStringToString(str);
	CFile cFile(TempPath,CFile::modeCreate|CFile::modeReadWrite);
	cFile.Write(str1.c_str(),str1.length());
	cFile.Close();
	return TempPath;
}

void CCustomURLProtocolDlg::OnBnClickedBtnTest()
{
	CString testFilePath;
	initializeParameter();
	testFilePath = CreateHtmlFile();
	ShellExecute(NULL,L"open",testFilePath.GetBuffer(),NULL,NULL,SW_MAXIMIZE);
}

void CCustomURLProtocolDlg::OnBnClickedCancel()
{
	OnCancel();
}

void CCustomURLProtocolDlg::OnBnClickedBtnDelete()
{
	DWORD errorCode = 0;
	initializeParameter();
	if(m_CustomURLProtocol.DeleteCustomProtocol() != ERROR_SUCCESS)
		MessageBox(m_CustomURLProtocol.getErrorMsg().c_str());
	else
		MessageBox(L"Successfully Deleted Custom Protocol.");
}
