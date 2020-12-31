// MinDialogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MinDialog.h"
#include "MinDialogDlg.h"
#include "..\src\about.h"
#include "..\src\ResourceTextFile.h"
#include "..\src\XString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMinDialogDlg dialog

BEGIN_MESSAGE_MAP(CMinDialogDlg, CDialog)
	//{{AFX_MSG_MAP(CMinDialogDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREE1, OnEndlabeleditTree1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMinDialogDlg::CMinDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMinDialogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMinDialogDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nCount = 0;
}

void CMinDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMinDialogDlg)
	DDX_Control(pDX, IDC_TREE2, m_Tree);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CMinDialogDlg message handlers

BOOL CMinDialogDlg::OnInitDialog()
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
	
	InitTree();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMinDialogDlg::InitTree()
{
	// create image list for level 0 items
	m_Images.Create(IDB_DOGS, 16, 9, RGB(0,255,255));
	m_Tree.SetImageList(&m_Images, TVSIL_NORMAL);

	m_Tree.Initialize(TRUE, TRUE);
	m_Tree.SetSmartCheckBox(TRUE);
	m_Tree.SetHtml(FALSE);
	m_Tree.SetImages(TRUE);

	LoadTextFileFromResource(_T("IDU_DOGS"));
}

//=============================================================================
void CMinDialogDlg::LoadTextFileFromResource(LPCTSTR lpszResource)
//=============================================================================
{
	TRACE(_T("in CMinDialogDlg::LoadTextFileFromResource: %s\n"), lpszResource);

	//m_strResourceName = lpszResource;

	m_nCount = 0;

	CResourceTextFile::ConvertAction eConvertAction = 
			CResourceTextFile::NoConvertAction;

#ifdef _UNICODE
	eConvertAction = CResourceTextFile::ConvertToUnicode;
#endif

	CResourceTextFile rtf;
	if (!rtf.Open(NULL, lpszResource, _T("TEXT"), eConvertAction))
	{
		CString msg;
		msg.Format(_T("Can't find resource %s"), lpszResource);
		AfxMessageBox(msg);
		return;
	}

	//HTREEITEM hItems[100];
	HTREEITEM hParent[5] =  { 0 };

	hParent[0] = m_Tree.InsertItem(_T("Dogs of the World"),
								 TV_NOIMAGE, TV_NOIMAGE);
	int nLevel = 0;

	// nLevel = 0:  root
	//			1:  dog category
	//          2:  dog breed
	//          3:  breed sub-list

	BOOL bSubList = FALSE;
	int nImage = 1;
	int nItem = 1;

	TCHAR szLine[1000];

	while (!rtf.IsAtEOF())
	{
		int index = 0;

		rtf.ReadLine(szLine, sizeof(szLine)/sizeof(TCHAR)-2);

		// hack to stop display
		if (_tcscmp(szLine, _T("...")) == 0)
			break;

		_tcsrtrim(szLine, NULL);

		XHTMLTREEDATA xhtd;

		if (szLine[0] == _T('\0'))
		{
			// line is empty - back to level 0

			nLevel = 0;
			bSubList = FALSE;
			continue;
		}
		else if (szLine[0] == _T(';'))
		{
			// comment line - ignore
			continue;
		}
		else if (szLine[0] == _T(' '))
		{
			// line begins with space - this is sublist
			if (!bSubList)
				nLevel++;
			bSubList = TRUE;
			index = 1;		// skip space
		}
		else
		{
			// line does not begin with space - not a sublist
			if (bSubList)
				nLevel--;
			bSubList = FALSE;
		}

		TRACE(_T("szLine=<%s>\n"), szLine);

		int nNoteWidth = 0;
		CString strNote = _T("");

		TCHAR *cp = _tcschr(szLine, _T('~'));
		if (cp)
		{
			*cp++ = _T('\0');
			TCHAR digit = *cp++;
			if (digit != _T('0'))
				xhtd.bChecked = TRUE;

			if (*cp++ == _T('~'))
			{
				digit = *cp++;
				if (digit != _T('1'))
					xhtd.bEnabled = FALSE;
			}

			if (*cp == _T('~'))
			{
				cp++;
				nNoteWidth = _ttoi(cp);
				while (*cp && isdigit(*cp))
					cp++;
			}

			if (*cp == _T('~'))
			{
				cp++;
				strNote = cp;
				TRACE(_T("strNote=<%s>\n"), strNote);
			}
		}

		// line not empty - add item
		TVINSERTSTRUCT tvis      = { 0 };
		tvis.item.mask           = TVIF_TEXT;
		tvis.item.pszText        = &szLine[index];
		tvis.item.cchTextMax     = (int)_tcslen(&szLine[index]);
		tvis.hParent             = hParent[nLevel];
		tvis.item.iImage         = TV_NOIMAGE;
		tvis.item.iSelectedImage = TV_NOIMAGE;
		tvis.item.mask          |= TVIF_IMAGE | TVIF_SELECTEDIMAGE;
		tvis.item.mask          |= TVIF_PARAM;
		tvis.item.lParam         = nItem++;

		if (nLevel == 0)
		{
			// set image for level 0 items
			ASSERT(nImage < 9);
			tvis.item.iImage = tvis.item.iSelectedImage = nImage;
			nImage++;
		}

		HTREEITEM hItem = m_Tree.InsertItem(&tvis, &xhtd);
		ASSERT(hItem);

		//hItems[m_nCount] = hItem;

		if (!strNote.IsEmpty())
			m_Tree.SetItemNote(hItem, strNote, nNoteWidth);

		m_nCount++;

		//if (m_nCount > 2)
		//	break;

		if (nLevel < 4)
		{
			hParent[nLevel+1] = hItem;
		}

		if (nLevel == 0)
			nLevel++;
	}
	//m_Tree.SetCheck(hItems[m_nCount-2], TRUE);
	//m_Tree.SetCheck(hItems[m_nCount-1], TRUE);
	//m_Tree.SetCheck(hItems[m_nCount-1], FALSE);
	//m_Tree.SetReadOnly(TRUE);

	rtf.Close();
}

void CMinDialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMinDialogDlg::OnPaint() 
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

HCURSOR CMinDialogDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMinDialogDlg::OnEndlabeleditTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TRACE(_T("in CMinDialogDlg::OnEndlabeleditTree1\n"));

	*pResult = TRUE;			// return TRUE to accept edit

	NMTVDISPINFO* pTVDispInfo = (NMTVDISPINFO*) pNMHDR;
	HTREEITEM hItem = pTVDispInfo->item.hItem;
	ASSERT(hItem);

	LPTSTR pszText = pTVDispInfo->item.pszText;

	BOOL bComplete = pszText && (*pszText != _T('\0'));
	if (!bComplete)
		*pResult = FALSE;		// don't allow empty label
}
