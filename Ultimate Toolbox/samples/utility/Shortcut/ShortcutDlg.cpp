// ShortcutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "utsampleabout.h"
#include "Shortcut.h"
#include "ShortcutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CShortcutDlg dialog

CShortcutDlg::CShortcutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShortcutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShortcutDlg)
	m_bThrowException = FALSE;
	m_sPathCreate = _T("");
	m_sPathOpen = _T("");
	m_sFN = _T("");
	m_bParam = FALSE;
	m_nParam = 0;
	m_sParam = _T("");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bCreate = FALSE;
	::GetCurrentDirectory(MAX_PATH, m_sCurDir.GetBuffer(MAX_PATH));
	m_sCurDir.ReleaseBuffer();
}

void CShortcutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShortcutDlg)
	DDX_Control(pDX, IDC_PARAM_BOOL, m_ctlBool);
	DDX_Control(pDX, IDC_PARAM_SPIN, m_ctlSpin);
	DDX_Control(pDX, IDC_PARAM_KEY, m_ctlHotkey);
	DDX_Control(pDX, IDC_COMBO_FN, m_ctlFn);
	DDX_Check(pDX, IDC_CHECK_THROW_EXCEPTION, m_bThrowException);
	DDX_Text(pDX, IDC_EDIT_CREATE, m_sPathCreate);
	DDX_Text(pDX, IDC_EDIT_OPEN, m_sPathOpen);
	DDX_CBString(pDX, IDC_COMBO_FN, m_sFN);
	DDX_Check(pDX, IDC_PARAM_BOOL, m_bParam);
	DDX_Text(pDX, IDC_PARAM_NUMBER, m_nParam);
	DDV_MinMaxInt(pDX, m_nParam, 0, 99);
	DDX_Text(pDX, IDC_PARAM_STRING, m_sParam);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CShortcutDlg, CDialog)
	//{{AFX_MSG_MAP(CShortcutDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CREATE, OnButtonCreate)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_FILE_OK, OnButtonFileOk)
	ON_BN_CLICKED(IDC_BUTTON_FN_OK, OnButtonFnOk)
	ON_BN_CLICKED(IDC_RADIO_CREATE, OnRadioCreate)
	ON_BN_CLICKED(IDC_RADIO_OPEN, OnRadioOpen)
	ON_CBN_SELCHANGE(IDC_COMBO_FN, OnSelchangeComboFn)
	ON_BN_CLICKED(IDC_PARAM_BOOL, OnParamBool)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_BUTTON_PARAM_STRING, OnButtonParamString)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShortcutDlg message handlers

#define FN_CLOSE				_T("Close(BOOL bSave)")
#define FN_GETARGUMENTS			_T("GetArguments(...)")
#define FN_GETCURFILE			_T("GetCurFile()")
#define FN_GETDESCRIPTION		_T("GetDescription(...)")
#define FN_GETHOTKEY			_T("GetHotkey(...)")
#define FN_GETICONINDEX			_T("GetIconIndex(...)")
#define FN_GETICONPATH			_T("GetIconPath(...)")
#define FN_GETIDLIST			_T("GetIDList(...)")
#define FN_GETLASTERROR			_T("GetLastError()")
#define FN_GETPATH				_T("GetPath(..., BOOL bUNC)")
#define FN_GETSHOWCMD			_T("GetShowCmd(...)")
#define FN_GETWORKINGDIRECTORY	_T("GetWorkingDirectory(...)")
#define FN_ISDIRTY				_T("IsDirty()")
#define FN_OPEN					_T("Open()")
#define FN_RESOLVE				_T("Resolve(this, SLR_ANY_MATCH)")
#define FN_SAVE					_T("Save(LPCTSTR pszFileName, BOOL fRemember)")
#define FN_SETARGUMENTS			_T("SetArguments(LPCTSTR pszArguments)")
#define FN_SETDESCRIPTION		_T("SetDescription(LPCTSTR pszDescription)")
#define FN_SETHOTKEY			_T("SetHotkey(WORD wHotkey)")
#define FN_SETICONINDEX			_T("SetIconIndex(int nIconIndex)")
#define FN_SETICONPATH			_T("SetIconPath(LPCTSTR pszPath)")
#define FN_SETIDLIST			_T("SetIDList(pidlPrograms)")
#define FN_SETPATH				_T("SetPath(LPCTSTR pszPath)")
#define FN_SETRELATIVEPATH		_T("SetRelativePath(LPCTSTR pszPath)")
#define FN_SETSHOWCMD			_T("SetShowCmd(int nShowCmd)")
#define FN_SETWORKINGDIRECTORY	_T("SetWorkingDirectory(LPCTSTR pszWorkingDirectory)")

BOOL CShortcutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_ctlFn.AddString(FN_CLOSE);
	m_ctlFn.AddString(FN_GETARGUMENTS);
	m_ctlFn.AddString(FN_GETCURFILE);
	m_ctlFn.AddString(FN_GETDESCRIPTION);
	m_ctlFn.AddString(FN_GETHOTKEY);
	m_ctlFn.AddString(FN_GETICONINDEX);
	m_ctlFn.AddString(FN_GETICONPATH);
	m_ctlFn.AddString(FN_GETIDLIST);
	m_ctlFn.AddString(FN_GETLASTERROR);
	m_ctlFn.AddString(FN_GETPATH);
	m_ctlFn.AddString(FN_GETSHOWCMD);
	m_ctlFn.AddString(FN_GETWORKINGDIRECTORY);
	m_ctlFn.AddString(FN_ISDIRTY);
//	m_ctlFn.AddString(FN_OPEN);
	m_ctlFn.AddString(FN_RESOLVE);
	m_ctlFn.AddString(FN_SAVE);
	m_ctlFn.AddString(FN_SETARGUMENTS);
	m_ctlFn.AddString(FN_SETDESCRIPTION);
	m_ctlFn.AddString(FN_SETHOTKEY);
	m_ctlFn.AddString(FN_SETICONINDEX);
	m_ctlFn.AddString(FN_SETICONPATH);
	m_ctlFn.AddString(FN_SETIDLIST);
	m_ctlFn.AddString(FN_SETPATH);
	m_ctlFn.AddString(FN_SETRELATIVEPATH);
	m_ctlFn.AddString(FN_SETSHOWCMD);
	m_ctlFn.AddString(FN_SETWORKINGDIRECTORY);

	m_ctlSpin.SetRange(0, 99);

	UpdateControls();
	((CButton*)GetDlgItem(IDC_RADIO_OPEN))->SetCheck(1);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CShortcutDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CShortcutDlg::OnPaint() 
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

HCURSOR CShortcutDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CShortcutDlg::UpdateControls()
{
	UpdateData();
	BOOL bOpened = !m_scDemo.GetCurFile().IsEmpty();

	SetDlgItemText(IDC_EDIT_OUTPUT, m_sOutput);
	GetDlgItem(IDC_EDIT_OPEN)->EnableWindow(!m_bCreate);
	GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(!m_bCreate);
	GetDlgItem(IDC_EDIT_CREATE)->EnableWindow(m_bCreate);
	GetDlgItem(IDC_BUTTON_CREATE)->EnableWindow(m_bCreate);

	GetDlgItem(IDC_COMBO_FN)->EnableWindow(bOpened);
	GetDlgItem(IDC_SAVE)->EnableWindow(bOpened);
	GetDlgItem(IDC_BUTTON_FN_OK)->EnableWindow(bOpened && !m_sFN.IsEmpty());

	GetDlgItem(IDC_PARAM_BOOL)  ->EnableWindow(bOpened && m_sFN.Find(_T("BOOL")) != -1);
	GetDlgItem(IDC_PARAM_KEY)   ->EnableWindow(bOpened && m_sFN.Find(_T("WORD")) != -1);
	GetDlgItem(IDC_PARAM_NUMBER)->EnableWindow(bOpened && m_sFN.Find(_T("int")) != -1);
	GetDlgItem(IDC_PARAM_SPIN)  ->EnableWindow(bOpened && m_sFN.Find(_T("int")) != -1);
	GetDlgItem(IDC_PARAM_STRING)->EnableWindow(bOpened && m_sFN.Find(_T("LPCTSTR")) != -1);
	GetDlgItem(IDC_BUTTON_PARAM_STRING)->EnableWindow(bOpened && m_sFN.Find(_T("LPCTSTR")) != -1);
}

void CShortcutDlg::OnButtonCreate() 
{
	CFileDialog dlg(FALSE, _T("LNK"), _T("New Shortcut"), 
		OFN_HIDEREADONLY | OFN_NODEREFERENCELINKS);
	dlg.m_ofn.lpstrTitle = _T("Create...");
	dlg.m_ofn.lpstrInitialDir = m_sCurDir;
	if (dlg.DoModal() == IDOK)
	{
		SetDlgItemText(IDC_EDIT_CREATE, dlg.GetPathName());
		m_sCurDir = dlg.GetPathName().Left(dlg.GetPathName().GetLength()
			- dlg.GetFileTitle().GetLength());
	}
}

void CShortcutDlg::OnButtonOpen()
{
	CFileDialog dlg(TRUE, _T(".LNK"), NULL, 
		OFN_HIDEREADONLY | OFN_NODEREFERENCELINKS,
		_T("Shortcut Files (*.LNK) | *.LNK;*.lnk | All Files (*.*) | *.*;* ||"), this);
	dlg.m_ofn.lpstrInitialDir = m_sCurDir;
	if (dlg.DoModal() == IDOK)
	{
		SetDlgItemText(IDC_EDIT_OPEN, m_sCurDir = dlg.GetPathName());
		m_sCurDir = dlg.GetPathName().Left(dlg.GetPathName().GetLength()
			- dlg.GetFileTitle().GetLength());
	}
}

void CShortcutDlg::OnButtonParamString() 
{
	CFileDialog dlg(TRUE, NULL, NULL, 
		OFN_HIDEREADONLY | OFN_NODEREFERENCELINKS);
	dlg.m_ofn.lpstrTitle = _T("Get pathname...");
	dlg.m_ofn.lpstrInitialDir = m_sCurDir;
	if (dlg.DoModal() == IDOK)
	{
		SetDlgItemText(IDC_PARAM_STRING, m_sCurDir = dlg.GetPathName());
		m_sCurDir = dlg.GetPathName().Left(dlg.GetPathName().GetLength()
			- dlg.GetFileTitle().GetLength());
	}
}

void CShortcutDlg::OnSave() 
{
	CString sTemp = m_sParam;
	SetDlgItemText(IDC_PARAM_STRING, _T(""));
	if (UpdateData()) DemoOutput(FN_SAVE);
	SetDlgItemText(IDC_PARAM_STRING, sTemp);
}

void CShortcutDlg::OnButtonFileOk()
{
	if (UpdateData()) DemoOutput(FN_OPEN);
}

void CShortcutDlg::OnButtonFnOk() 
{
	if (UpdateData()) DemoOutput(m_sFN);
}

void CShortcutDlg::OnRadioCreate() 
{
	m_bCreate = TRUE;
	UpdateControls();
}

void CShortcutDlg::OnRadioOpen() 
{
	m_bCreate = FALSE;
	UpdateControls();
}

void CShortcutDlg::OnSelchangeComboFn() 
{
	UpdateControls();
	SetDlgItemText(IDC_EDIT_OUTPUT, _T(""));
}

void CShortcutDlg::OnParamBool() 
{
	UpdateData();
	m_ctlBool.SetWindowText(m_bParam ? _T("TRUE") : _T("FALSE"));
}

// for CShortcutDlg::DemoOutput() only
#define SWITCH \
	if(FALSE) \
	{ \

#define CASE(fn) \
	} \
	else if(sFN.Compare(fn) == 0) \
	{ \

#define END_SWITCH \
	} \

//////////////////////////////////////////////////////////////////////////////////////////////
// This is the only function that you may need to look into in order to understand COXShortcut

void CShortcutDlg::DemoOutput(LPCTSTR lpszFN)
{
	LPCTSTR fmtX = _T("%02X");
	LPCTSTR fmtN = _T("%d");
	LPCTSTR fmtS = _T("\"%s\"");

	CString sFN = lpszFN;
	CString sBuffer;

	// ... assume successful
	BOOL bSuccess = TRUE;
	m_sOutput = CString(sFN) + _T("\r\nOK\r\n");
	
	try
	{
		SWITCH
		CASE(FN_CLOSE)
			m_scDemo.Close(m_bParam);

		CASE(FN_GETARGUMENTS)
			if (bSuccess == m_scDemo.GetArguments(sBuffer))
				m_sOutput.Format(fmtS, sBuffer);
		
		CASE(FN_GETCURFILE)
			sBuffer = m_scDemo.GetCurFile();
			m_sOutput.Format(fmtS, sBuffer);

		CASE(FN_GETDESCRIPTION)
			if (bSuccess == m_scDemo.GetDescription(sBuffer))
				m_sOutput.Format(fmtS, sBuffer);
		
		CASE(FN_GETHOTKEY)
			WORD wVirtualKeyCode, wModifiers, wHotkey;
			if (bSuccess == m_scDemo.GetHotkey(wHotkey))
			{
				wVirtualKeyCode = (WORD)(wHotkey & 0x00FF);
				wModifiers = (WORD)(wHotkey >> 8);
				m_ctlHotkey.EnableWindow(TRUE);
				m_ctlHotkey.SetHotKey(wVirtualKeyCode, wModifiers);
				m_sOutput += _T("Please see 'Key' for the current value");
			}
		
		CASE(FN_GETICONINDEX)
			int iIcon;
			if (bSuccess == m_scDemo.GetIconIndex(iIcon))
				m_sOutput.Format(fmtN, iIcon);

		CASE(FN_GETICONPATH)
			if (bSuccess == m_scDemo.GetIconPath(sBuffer))
				m_sOutput.Format(fmtS, sBuffer);
		
		CASE(FN_GETIDLIST)
			LPMALLOC g_pMalloc;
			LPITEMIDLIST pidl;

			// we need to call SHGetMalloc() to get an allocator
			// pointer to free the memory allocation afterwards
			if (SUCCEEDED(SHGetMalloc(&g_pMalloc)) && (bSuccess == m_scDemo.GetIDList(pidl)))
			{
				m_sOutput.Empty();

				// output pidl
				LPITEMIDLIST pidlWalkthrough = pidl;
				int cb = pidl->mkid.cb;
				while (cb)
				{
					int nLen = cb - sizeof(USHORT);
					m_sOutput += _T('{');
					for (int i = 0; i < nLen; i++)
					{
						sBuffer.Format(fmtX, pidlWalkthrough->mkid.abID[i]);
						m_sOutput += sBuffer + ((i == nLen - 1) ? _T("}\r\n") : _T(", "));
					}
					
					pidlWalkthrough = (LPITEMIDLIST) (((LPBYTE) pidlWalkthrough) + cb); 
					cb = pidlWalkthrough->mkid.cb; 
				}
				
				// ... now we're freeing it
				g_pMalloc->Free(pidl);
			}
		
		CASE(FN_GETLASTERROR)
			m_sOutput.Format(fmtN, m_scDemo.GetLastError());
		
		CASE(FN_GETPATH)
			if (bSuccess == m_scDemo.GetPath(sBuffer, m_bParam))
				m_sOutput.Format(fmtS, sBuffer);
		
		CASE(FN_GETSHOWCMD)
			int iShowCmd;
			if (bSuccess == m_scDemo.GetShowCmd(iShowCmd))
			{
				m_sOutput.Format(fmtN, iShowCmd);
				m_sOutput += _T(": ");

				// NOTE: not all showcmd would be accepted as is
				switch(iShowCmd)
				{
				case SW_HIDE:			m_sOutput += _T("SW_HIDE");				break;
				case SW_MAXIMIZE:		m_sOutput += _T("SW_MAXIMIZE");			break;
				case SW_MINIMIZE:		m_sOutput += _T("SW_MINIMIZE");			break;
				case SW_RESTORE:		m_sOutput += _T("SW_RESTORE");			break;
				case SW_SHOW:			m_sOutput += _T("SW_SHOW");				break;
				case SW_SHOWDEFAULT:	m_sOutput += _T("SW_SHOWDEFAULT");		break;
//				case SW_SHOWMAXIMIZED:	m_sOutput += _T("SW_SHOWMAXIMIZED");	break;
				case SW_SHOWMINIMIZED:	m_sOutput += _T("SW_SHOWMINIMIZED");	break;
				case SW_SHOWMINNOACTIVE:m_sOutput += _T("SW_SHOWMINNOACTIVE");	break;
				case SW_SHOWNA:			m_sOutput += _T("SW_SHOWNA");			break;
				case SW_SHOWNOACTIVATE: m_sOutput += _T("SW_SHOWNOACTIVATE");	break;
				case SW_SHOWNORMAL:		m_sOutput += _T("SW_SHOWNORMAL");		break;
				default:				m_sOutput += _T("(undefined)");			break;
				}
			}

		CASE(FN_GETWORKINGDIRECTORY)
			if (bSuccess == m_scDemo.GetWorkingDirectory(sBuffer))
				m_sOutput.Format(fmtS, sBuffer);
		
		CASE(FN_ISDIRTY)
			m_sOutput.Format(fmtN, m_scDemo.IsDirty());
		
		CASE(FN_OPEN)
			if (m_bCreate)
			{
				// in real situation, you rarely use _T("") to start a new shortcut file
				// because it appears as "My Computer" (the topest level, as you may find from
				// the GetIDList()).
				m_sOutput = _T("Here we use empty path as the object this shortcut points to.");
				bSuccess = m_scDemo.Open(m_sPathCreate, _T(""), m_bThrowException);
			}
			else
			{
				bSuccess = m_scDemo.Open(m_sPathOpen, NULL, m_bThrowException);
			}

		CASE(FN_RESOLVE)
			bSuccess = m_scDemo.Resolve(this, SLR_ANY_MATCH);

		CASE(FN_SAVE)
			if (m_sParam.IsEmpty())
			{
				m_sOutput = _T("Here we use NULL as the first parameter.");
				bSuccess = m_scDemo.Save();
			}
			else
			{
				if (AfxMessageBox(CString(_T("Save as ")) + m_sParam, MB_OKCANCEL) == IDOK)
					bSuccess = m_scDemo.Save(m_sParam, m_bParam);
			}

		CASE(FN_SETARGUMENTS)
			bSuccess = m_scDemo.SetArguments(m_sParam);

		CASE(FN_SETDESCRIPTION)
			bSuccess = m_scDemo.SetDescription(m_sParam);

		CASE(FN_SETHOTKEY)
			WORD wVirtualKeyCode, wModifiers, wHotkey;
			m_ctlHotkey.GetHotKey(wVirtualKeyCode, wModifiers);
			wHotkey = (WORD)((wModifiers << 8) + wVirtualKeyCode);
			bSuccess = m_scDemo.SetHotkey(wHotkey);

		CASE(FN_SETICONINDEX)
			bSuccess = m_scDemo.SetIconIndex(m_nParam);

		CASE(FN_SETICONPATH)
			bSuccess = m_scDemo.SetIconPath(m_sParam);

		CASE(FN_SETIDLIST)
			m_sOutput = _T("Here we use \"Programs\" folder as an example.");
			int nFolder = CSIDL_PROGRAMS;
			
			LPMALLOC g_pMalloc;
			LPITEMIDLIST pidl; 
 
			if (SUCCEEDED(SHGetMalloc(&g_pMalloc)) && 
				SUCCEEDED(SHGetSpecialFolderLocation(NULL, nFolder, &pidl)))
			{
				bSuccess = m_scDemo.SetIDList(pidl);
				g_pMalloc->Free(pidl);
			}

		CASE(FN_SETPATH)
			bSuccess = m_scDemo.SetPath(m_sParam);

		CASE(FN_SETRELATIVEPATH)
			bSuccess = m_scDemo.SetRelativePath(m_sParam);

		CASE(FN_SETSHOWCMD)
			bSuccess = m_scDemo.SetShowCmd(m_nParam);

		CASE(FN_SETWORKINGDIRECTORY)
			bSuccess = m_scDemo.SetWorkingDirectory(m_sParam);

		END_SWITCH
	}
	catch (COleException* e)
	{
		bSuccess = FALSE;
		e->ReportError();
		e->Delete();
	}

	if (!bSuccess)
	{
		CString sFormat = CString(sFN) + _T("\r\n");
		HRESULT hres = m_scDemo.GetLastError();

		if (m_bThrowException)
			sFormat += _T("Error: exception was thrown.");
		else
		{
			// even when not successful, SUCCEEDED(hres) may be TRUE, e.g. S_FALSE;
			// These kinds of HRESULT will cause a FALSE return on member functions
			// (without throwing exceptions even when m_bThrowException == TRUE)
			if (SUCCEEDED(hres))
			{
				if (hres == S_FALSE)
					sFormat += _T("Failed (or succeeded with S_FALSE).");
				else
					// in case there are more codes (S_XXX) defined
					// currently only S_OK (same as NOERROR) and S_FALSE are defined
					// (check WinError.h)
					sFormat += _T("Failed (or succeeded with unexpected result).");
			}
			else
			// These are OLE-defined errors (should we have set m_bThrowException == TRUE,
			// an exception will be thrown)
				sFormat += _T("Error: no exception was thrown.");
		}
		sFormat += _T(" HRESULT: $%08X");
		m_sOutput.Format(sFormat, hres);
	}
	
	SetWindowText(CString(_T("Demo of COXShortcut - ")) + m_scDemo.GetCurFile());
	UpdateControls();
}

