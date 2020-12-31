// CFileChangerDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FileChanger.h"
#include "FileChangerDemoDlg.h"

#include "UTSampleAbout.h"   

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileChangerDemoDlg dialog

CFileChangerDemoDlg::CFileChangerDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileChangerDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileChangerDemoDlg)
	m_bAll = TRUE;
	m_sFileIn = _T("");
	m_sFileOut = _T("");
	m_sFindText = _T("");
	m_bMatchCase = FALSE;
	m_bOverwrite = FALSE;
	m_sReplaceText = _T("");
	m_bUseCFile = FALSE;
	m_bWholeWord = FALSE;
	m_nTextBinary = 0;
	m_bMessage = TRUE;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileChangerDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileChangerDemoDlg)
	DDX_Control(pDX, IDC_OVERWRITE, m_ctlOverwrite);
	DDX_Control(pDX, IDC_WHOLEWORD, m_ctlWholeWord);
	DDX_Control(pDX, IDC_FILEOUT, m_ctlFileOut);
	DDX_Control(pDX, IDC_BROWSEOUT, m_ctlBrowseOut);
	DDX_Control(pDX, IDC_MATCHCASE, m_ctlMatchCase);
	DDX_Check(pDX, IDC_ALL, m_bAll);
	DDX_Text(pDX, IDC_FILEIN, m_sFileIn);
	DDX_Text(pDX, IDC_FILEOUT, m_sFileOut);
	DDX_Text(pDX, IDC_FINDTEXT, m_sFindText);
	DDX_Check(pDX, IDC_MATCHCASE, m_bMatchCase);
	DDX_Check(pDX, IDC_OVERWRITE, m_bOverwrite);
	DDX_Text(pDX, IDC_REPLACETEXT, m_sReplaceText);
	DDX_Check(pDX, IDC_USECFILE, m_bUseCFile);
	DDX_Check(pDX, IDC_WHOLEWORD, m_bWholeWord);
	DDX_Radio(pDX, IDC_TEXT, m_nTextBinary);
	DDX_Check(pDX, IDC_MESSAGE, m_bMessage);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFileChangerDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CFileChangerDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_TEXT, OnSelectTextBinary)
	ON_BN_CLICKED(IDC_FIND, OnFind)
	ON_BN_CLICKED(IDC_REPLACE, OnReplace)
	ON_BN_CLICKED(IDC_OVERWRITE, OnSelectOverwrite)
	ON_BN_CLICKED(IDC_BROWSEIN, OnBrowseIn)
	ON_BN_CLICKED(IDC_BROWSEOUT, OnBrowseOut)
	ON_BN_CLICKED(IDC_USECFILE, OnUsecfile)
	ON_BN_CLICKED(IDC_BINARY, OnSelectTextBinary)
	ON_EN_KILLFOCUS(IDC_FINDTEXT, OnSelectTextBinary)
	ON_EN_KILLFOCUS(IDC_REPLACETEXT, OnSelectTextBinary)
	ON_BN_CLICKED(IDC_MESSAGE, OnMessage)
	ON_MESSAGE(WM_OX_FILE_MATCH_FOUND, OnFileMatchFound)
	ON_MESSAGE(WM_OX_FILE_PRE_REPLACE, OnFilePreReplace)
	ON_MESSAGE(WM_OX_FILE_POST_REPLACE, OnFilePostReplace)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileChangerDemoDlg message handlers

BOOL CFileChangerDemoDlg::OnInitDialog()
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

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_fc.SetNotificationWnd(this);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFileChangerDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CUTSampleAboutDlg aboutDlg(IDR_MAINFRAME,ID_DESCRIPTION_FILE);
		aboutDlg.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFileChangerDemoDlg::OnPaint() 
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

HCURSOR CFileChangerDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFileChangerDemoDlg::OnSelectTextBinary() 
{
	UpdateData();
	m_ctlMatchCase.EnableWindow(m_nTextBinary == 0);
	m_ctlWholeWord.EnableWindow(m_nTextBinary == 0);
	if (m_nTextBinary == 1)
		{
		toBinary(m_sFindText);
		toBinary(m_sReplaceText);
		UpdateData(FALSE);
		}
}

void CFileChangerDemoDlg::OnSelectOverwrite() 
{
	UpdateData();
	m_ctlFileOut.EnableWindow(!m_bOverwrite);
	m_ctlBrowseOut.EnableWindow(!m_bOverwrite);
}

void CFileChangerDemoDlg::OnUsecfile() 
{
	UpdateData();
	m_ctlOverwrite.EnableWindow(!m_bUseCFile);
	if (m_bUseCFile)
		{
		m_bOverwrite = FALSE;
		UpdateData(FALSE);
		OnSelectOverwrite();
		}
}

void CFileChangerDemoDlg::OnBrowseIn() 
{
	OnBrowse(m_sFileIn);
}

void CFileChangerDemoDlg::OnBrowseOut() 
{
	OnBrowse(m_sFileOut);
}

void CFileChangerDemoDlg::OnBrowse(CString& sEditBoxText) 
{
	UpdateData();
	CFileDialog dlg(TRUE, NULL, sEditBoxText, OFN_HIDEREADONLY,
		_T("All Files (*.*)|*.*|Text Files (*.txt)|*.txt|HTML Files (*.html; *.htm)|*.html; *.htm||"), this);
	if (dlg.DoModal() == IDOK)
		{
		sEditBoxText = dlg.GetPathName();
		UpdateData(FALSE);
		}
}

void CFileChangerDemoDlg::OnMessage() 
{
	UpdateData();
}

// Demo Codes ---------------------------------------------

void CFileChangerDemoDlg::OnFind() 
{
	UINT nResult = 0;
	CFile fIn;
	
	UpdateData();
	try
		{
		if (m_bUseCFile)
			{
			fIn.Open(m_sFileIn, CFile::modeRead);
			m_fc.UseFiles(&fIn);
			}
		else
			{
			m_fc.UseFiles(m_sFileIn);
			}

		if (m_nTextBinary == 0)
			{
			nResult = m_fc.Search(m_sFindText, m_bAll, m_bMatchCase, m_bWholeWord);
			}
		else
			{
			CByteArray binary;
			toBinary(m_sFindText, &binary);
			UpdateData(FALSE); // to display formatted m_sFindText
			nResult = m_fc.Search(binary, m_bAll);
			}
		}
	catch(CException* e)
		{
		fIn.Abort();
		e->ReportError();
		e->Delete();
		}
	
	CString sMsg; sMsg.Format(_T("Function return: %d"), nResult);
	AfxMessageBox(sMsg, MB_ICONINFORMATION);
}

void CFileChangerDemoDlg::OnReplace() 
{
	UINT nResult = 0;
	CFile fIn, fOut;
	
	UpdateData();
	try
		{
		if (m_bUseCFile)
			{
			fIn.Open(m_sFileIn, CFile::modeRead);
			fOut.Open(m_sFileOut, CFile::modeReadWrite | CFile::modeCreate);
			m_fc.UseFiles(&fIn, &fOut);
			}
		else
			{
			if (m_bOverwrite)
				m_fc.UseFiles(m_sFileIn);
			else
				m_fc.UseFiles(m_sFileIn, m_sFileOut);
			}

		if (m_nTextBinary == 0)
			{
			nResult = m_fc.Replace(m_sFindText, m_sReplaceText,
				m_bAll, m_bMatchCase, m_bWholeWord);
			}
		else
			{
			CByteArray binary, replaceBinary;
			toBinary(m_sFindText, &binary);
			toBinary(m_sReplaceText, &replaceBinary);
			UpdateData(FALSE);
			nResult = m_fc.Replace(binary, replaceBinary, m_bAll);
			}
		}
	catch(CException* e)
		{
		fIn.Abort();
		fOut.Abort();
		e->ReportError();
		e->Delete();
		}
	
	CString sMsg; sMsg.Format(_T("Function return: %d"), nResult);
	AfxMessageBox(sMsg, MB_ICONINFORMATION);
}

void CFileChangerDemoDlg::toBinary(CString& sText, CByteArray* binary /* = NULL */, BOOL bFormat /* = TRUE */)
{
	TCHAR ch; CString sByte, sFormatted; int n = 0, i, nLen;
	
	nLen = sText.GetLength();
	for (i = 0; i < nLen; i++)
		{
		ch = sText[i];
		if (_istxdigit(ch)) { sByte += ch; n++;}
		if (n == 2 || (n > 0 && (ch == _T(' ') || i == nLen - 1)))
			{
			sByte.MakeUpper();
			if (n == 1) sFormatted += _T('0');
			sFormatted += sByte + _T(' ');
			n = 0; sByte.Empty();
			}
		}

	if (binary)
		{
		nLen = sFormatted.GetLength();
		if (binary->GetSize()) binary->RemoveAll();
		binary->SetSize(nLen / 3);
		for (i = 0, n = 0; n < nLen; i++, n+=3)
			binary->SetAt(i, (BYTE)(xch2int(sFormatted[n]) * 0x10 + 
			xch2int(sFormatted[n+1])));
		}

	if (bFormat) 
		sText = sFormatted;
}

int CFileChangerDemoDlg::xch2int(TCHAR ch)
	{
	switch (ch)
		{
		case _T('0'): return 0;
		case _T('1'): return 1;
		case _T('2'): return 2;
		case _T('3'): return 3;
		case _T('4'): return 4;
		case _T('5'): return 5;
		case _T('6'): return 6;
		case _T('7'): return 7;
		case _T('8'): return 8;
		case _T('9'): return 9;
		case _T('a'): case _T('A'): return 10;
		case _T('b'): case _T('B'): return 11;
		case _T('c'): case _T('C'): return 12;
		case _T('d'): case _T('D'): return 13;
		case _T('e'): case _T('E'): return 14;
		case _T('f'): case _T('F'): return 15;
		}
	return -1;
	}

// CMyFileChanger : derived from COXFileChanger -----------

LRESULT CFileChangerDemoDlg::OnFileMatchFound(WPARAM wParam, LPARAM /* lParam */)
	{
	COXFileChanger::COXFileChangerData* pFileChangerData = (COXFileChanger::COXFileChangerData*)wParam;
	ASSERT(AfxIsValidAddress(pFileChangerData, sizeof(COXFileChanger::COXFileChangerData)));

	if (m_bMessage)
		{
		CString sMsg;
		sMsg.Format(_T("%s [%d]\r\n\r\nCount?"), pFileChangerData->m_pFile->GetFileName(), 
			pFileChangerData->m_nPos);

		switch(AfxMessageBox(sMsg, MB_YESNOCANCEL | MB_ICONQUESTION))
			{
			case IDCANCEL: pFileChangerData->m_bContinue = FALSE;
			case IDNO:  return FALSE;
			}
		}
	return (LRESULT)TRUE;
	}

LRESULT CFileChangerDemoDlg::OnFilePreReplace(WPARAM wParam, LPARAM /* lParam */)
	{
	COXFileChanger::COXFileChangerData* pFileChangerData = (COXFileChanger::COXFileChangerData*)wParam;
	ASSERT(AfxIsValidAddress(pFileChangerData, sizeof(COXFileChanger::COXFileChangerData)));

	if (m_bMessage)
		{
		CString sMsg;
		sMsg.Format(_T("%s [%d]\r\n\r\nReplace?"), pFileChangerData->m_pFile->GetFileName(), 
			pFileChangerData->m_nPos);

		switch(AfxMessageBox(sMsg, MB_YESNOCANCEL | MB_ICONQUESTION))
			{
			case IDCANCEL: pFileChangerData->m_bContinue = FALSE;
			case IDNO:  return FALSE;
			}
		}
	return (LRESULT)TRUE;
	}

LRESULT CFileChangerDemoDlg::OnFilePostReplace(WPARAM wParam, LPARAM /* lParam */)
	{
	COXFileChanger::COXFileChangerData* pFileChangerData = (COXFileChanger::COXFileChangerData*)wParam;
	ASSERT(AfxIsValidAddress(pFileChangerData, sizeof(COXFileChanger::COXFileChangerData)));

	if (m_bMessage)
		{
		CString sMsg;
		sMsg.Format(_T("%s [%d]"), pFileChangerData->m_pFile->GetFileName(), pFileChangerData->m_nPos);
		AfxMessageBox(sMsg, MB_ICONINFORMATION);
		}
	
	// ... Return value is not used
	return (LRESULT)0;
	}
