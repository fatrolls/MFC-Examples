// XHtmlTreeTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XHtmlTreeTest.h"
#include "XHtmlTreeTestDlg.h"
#include "about.h"
#include "ResourceTextFile.h"
#include "XString.h"
#include "XHtmlDraw.h"
#include "XMessageBox.h"
#include "FindDialog.h"
#include "ColorDlg.h"
#include "XNamedColors.h"
#include "PPTooltip.h"
#include "XTrace.h"
#include "XmlDocument.h"	// not compatible with windowsx.h
#include "mmsystem.h"

// from windowsx.h

#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))

typedef CXBreadCrumbBar::XHTMLDRAW_APP_COMMAND	APP_COMMAND;

#pragma warning(disable : 4996)	// disable bogus deprecation warning

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma message("automatic link to WINMM.LIB")
#pragma comment(lib, "winmm.lib")

//=============================================================================
// define app command message used by <a href=\"app:WM_APP_COMMAND\">
//=============================================================================
#define WM_APP_COMMAND_1	(WM_APP+100)
#define WM_APP_COMMAND_2	(WM_APP+101)
#define WM_APP_COMMAND_SEL	(WM_APP+102)

//=============================================================================
BEGIN_MESSAGE_MAP(CXHtmlTreeTestDlg, CDialog)
//=============================================================================
	//{{AFX_MSG_MAP(CXHtmlTreeTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CONTEXTMENU()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_CLICKED(IDC_COLLAPSE_ALL, OnCollapseAll)
	ON_BN_CLICKED(IDC_EXPAND_ALL, OnExpandAll)
	ON_BN_CLICKED(IDC_CHECKBOXES, OnUpdateTree)
	ON_BN_CLICKED(IDC_SHOW_CHECKED, OnShowChecked)
	ON_BN_CLICKED(IDC_FIND, OnFind)
	ON_BN_CLICKED(IDC_CHECK_ALL, OnCheckAll)
	ON_BN_CLICKED(IDC_COLORS, OnColors)
	ON_BN_CLICKED(IDC_LOG, OnLog)
	ON_BN_CLICKED(IDC_SMART_CHECKBOXES, OnUpdateTree)
	ON_BN_CLICKED(IDC_HTML, OnUpdateTree)
	ON_BN_CLICKED(IDC_STRIP_HTML, OnUpdateTree)
	ON_BN_CLICKED(IDC_IMAGES, OnUpdateTree)
	ON_BN_CLICKED(IDC_READONLY, OnUpdateTree)
	ON_BN_CLICKED(ID_FINDNEXT, FindNext)
	ON_BN_CLICKED(ID_FINDPREV, FindPrev)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_COMMAND(ID_DISABLE, OnDisable)
	ON_COMMAND(ID_ENABLE, OnEnable)
	ON_COMMAND(ID_FIND, OnFind)
	ON_COMMAND(ID_TREE_SEPARATOR, OnSeparator)
	ON_COMMAND(ID_TREE_DELETE, OnDelete)
	ON_NOTIFY(NM_RCLICK, IDC_TREE1, OnRclickTree1)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, OnSelchangedTree1)
	ON_NOTIFY(TVN_BEGINLABELEDIT, IDC_TREE1, OnBeginlabeleditTree1)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREE1, OnEndlabeleditTree1)
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(WM_XHTMLTREE_CHECKBOX_CLICKED, OnCheckbox)
	ON_REGISTERED_MESSAGE(WM_XHTMLTREE_ITEM_EXPANDED, OnExpanded)
	ON_REGISTERED_MESSAGE(WM_CHECKEDITEMSDIALOG_CLOSING, OnCheckedItemsDialogClosing)
	ON_REGISTERED_MESSAGE(WM_XHTMLTREE_DISPLAY_TOOLTIP, OnDisplayTreeToolTip)
	ON_REGISTERED_MESSAGE(WM_XHTMLTREE_INIT_TOOLTIP, OnInitTreeToolTip)
#ifdef XHTMLDRAGDROP
#ifdef XHTMLTREE_DEMO
	ON_REGISTERED_MESSAGE(WM_XHTMLTREE_SCROLL_SPEED, OnScrollSpeed)
#endif // XHTMLTREE_DEMO
	ON_REGISTERED_MESSAGE(WM_XHTMLTREE_BEGIN_DRAG, OnBeginDrag)
	ON_REGISTERED_MESSAGE(WM_XHTMLTREE_END_DRAG, OnEndDrag)
	ON_REGISTERED_MESSAGE(WM_XHTMLTREE_DROP_HOVER, OnDropHover)
#endif // XHTMLDRAGDROP
	
	ON_MESSAGE(WM_APP_COMMAND_SEL, OnAppCommandSel)
	ON_MESSAGE(WM_APP_COMMAND_1, OnAppCommand1)
	ON_MESSAGE(WM_APP_COMMAND_2, OnAppCommand2)
END_MESSAGE_MAP()

//=============================================================================
CXHtmlTreeTestDlg::CXHtmlTreeTestDlg(CWnd* pParent /*=NULL*/, int nInput /*= 0*/)
	: CDialog(CXHtmlTreeTestDlg::IDD, pParent)
//=============================================================================
{
	//{{AFX_DATA_INIT(CXHtmlTreeTestDlg)
	m_bCheckBoxes      = TRUE;
	m_bSmartCheckBoxes = TRUE;
	m_bHtml            = TRUE;
	m_bStripHtml       = FALSE;
	m_bImages          = TRUE;
	m_bReadOnly        = FALSE;
	m_bCheckAll        = TRUE;
	m_nInput           = nInput;
	m_nLineNo          = 1;
	m_nCount           = 0;
	m_pCheckedItemsDlg = NULL;
	m_strResourceName  = _T("");
	m_strFind          = _T("");
	m_nFindStart       = 0;
	m_nFindDir         = 1;
	m_bFindCheck       = FALSE;
	m_rectFind         = CRect(0,0,0,0);
	m_rgbText          = GetSysColor(COLOR_WINDOWTEXT);
	m_rgbBackground    = GetSysColor(COLOR_WINDOW);
	m_ptCheckedItems   = CPoint(0,0);
	m_bLog             = TRUE;
	m_hTrackItem       = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

//=============================================================================
void CXHtmlTreeTestDlg::DoDataExchange(CDataExchange* pDX)
//=============================================================================
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXHtmlTreeTestDlg)
	DDX_Control(pDX, IDC_SCROLL1, m_ScrollSpeed1);
	DDX_Control(pDX, IDC_SCROLL2, m_ScrollSpeed2);
	DDX_Control(pDX, IDC_SCROLL3, m_ScrollSpeed3);
	DDX_Control(pDX, IDC_BREAD_CRUMB, m_BreadCrumb);
	DDX_Control(pDX, IDC_STATIC_ITEM_INFO, m_ItemInfo);
	DDX_Control(pDX, IDC_CHECK_ALL, m_btnCheckAll);
	DDX_Control(pDX, IDC_COLLAPSE_ALL, m_btnCollapseAll);
	DDX_Control(pDX, IDC_EXPAND_ALL, m_btnExpandAll);
	DDX_Control(pDX, IDC_TREE_INFO, m_TreeInfo);
	DDX_Control(pDX, IDC_ITEMIMAGE, m_ItemImage);
	DDX_Control(pDX, IDC_NOSEPARATORS, m_NoSeparators);
	DDX_Control(pDX, IDC_NOCHILDREN, m_NoChildren);
	DDX_Control(pDX, IDC_NOCHECKED, m_NoChecked);
	DDX_Control(pDX, IDC_ISCHECKED, m_IsChecked);
	DDX_Control(pDX, IDC_EXPANDED, m_Expanded);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_TREE1, m_Tree);
	DDX_Check(pDX, IDC_CHECKBOXES, m_bCheckBoxes);
	DDX_Check(pDX, IDC_SMART_CHECKBOXES, m_bSmartCheckBoxes);
	DDX_Check(pDX, IDC_HTML, m_bHtml);
	DDX_Check(pDX, IDC_STRIP_HTML, m_bStripHtml);
	DDX_Check(pDX, IDC_IMAGES, m_bImages);
	DDX_Check(pDX, IDC_READONLY, m_bReadOnly);
	DDX_Check(pDX, IDC_LOG, m_bLog);
	//}}AFX_DATA_MAP
}

//=============================================================================
BOOL CXHtmlTreeTestDlg::OnInitDialog()
//=============================================================================
{
	CDialog::OnInitDialog();

	m_hAccel = LoadAccelerators(AfxGetInstanceHandle(), 
					MAKEINTRESOURCE(IDR_ACCELERATOR));

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
	
	CreateTooltips();	// set up tooltips for app

	m_List.SetContextMenuId(IDR_XLISTBOX);

	m_List.Printf(CXListBox::Blue, CXListBox::White, 0, _T("XHtmlTreeTest v1.6"));
	m_List.Printf(CXListBox::Blue, CXListBox::White, 0, _T(""));

#ifdef XHTMLHTML
	CXHtmlDraw::XHTMLDRAW_APP_COMMAND AppCommands[] = 
	{
		{ m_hWnd, WM_APP_COMMAND_1, 123, _T("WM_APP_COMMAND1") },
		{ m_hWnd, WM_APP_COMMAND_2, 456, _T("WM_APP_COMMAND2") },
	};

	m_Tree.m_Links.SetAppCommands(AppCommands, 
		sizeof(AppCommands)/sizeof(AppCommands[0]));
#endif

	// set + / - buttons
	m_btnCheckAll.SetGlyph(0, 12, FW_NORMAL, _T("Arial"), 0xD7);
	m_btnExpandAll.SetGlyph(0, 10, FW_NORMAL, _T("Arial"), 0x2B);
	m_btnCollapseAll.SetGlyph(0, 16, FW_NORMAL, _T("Arial"), 0x2D);
	
	GetDlgItem(IDC_UPDATE)->EnableWindow(FALSE);
	m_Edit.EnableWindow(FALSE);

	if (m_Tree.GetHasCheckBoxes())
		m_bCheckBoxes = TRUE;
	CButton *pBtn = (CButton*) GetDlgItem(IDC_CHECKBOXES);
	pBtn->SetCheck(m_bCheckBoxes);

	// create image list for level 0 items
	m_Images.Create(IDB_DOGS, 16, 9, RGB(0,255,255));
	m_Tree.SetImageList(&m_Images, TVSIL_NORMAL);

	m_BreadCrumb.SetWindowText(_T(""));

	UpdateTree(FALSE);

	DumpInfo(NULL);

#ifdef XHTMLDRAGDROP
	OnScrollSpeed(0, 0);
#else
	m_ScrollSpeed1.ShowWindow(FALSE);
	m_ScrollSpeed2.ShowWindow(FALSE);
	m_ScrollSpeed3.ShowWindow(FALSE);
#endif // XHTMLDRAGDROP

	//CXNamedColors nc;
	//nc.Dump(_T("namedcolors.html"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

//=============================================================================
void CXHtmlTreeTestDlg::CreateTooltips()
//=============================================================================
{
	m_ToolTips.Create(this, TTS_ALWAYSTIP);
	::SendMessage(m_ToolTips.m_hWnd, TTM_SETMAXTIPWIDTH, 0, SHRT_MAX);

	m_ToolTips.AddTool(GetDlgItem(IDC_CHECK_ALL),
			_T("Toggle checkbox for all items"));
	m_ToolTips.AddTool(GetDlgItem(IDC_EXPAND_ALL),
			_T("Expand all items"));
	m_ToolTips.AddTool(GetDlgItem(IDC_COLLAPSE_ALL),
			_T("Collapse all items"));
	m_ToolTips.AddTool(GetDlgItem(IDC_SCROLL1),
			_T("Low speed indicator for dragging scroll"));
	m_ToolTips.AddTool(GetDlgItem(IDC_SCROLL2),
			_T("Medium speed indicator for dragging scroll"));
	m_ToolTips.AddTool(GetDlgItem(IDC_SCROLL3),
			_T("High speed indicator for dragging scroll"));
}

//=============================================================================
void CXHtmlTreeTestDlg::LoadXmlFileFromResource(LPCTSTR lpszResource)
//=============================================================================
{
	//m_Tree.LoadXmlFromFile(_T("D:\\CP Articles\\XHtmlTreeTest\\1.0\\src\\dogs.xml"), CXHtmlTree::NoConvertAction);
	//m_Tree.LoadXmlFromFile(_T("D:\\CP Articles\\XHtmlTreeTest\\1.0\\vs2005\\utf16le.xml"), CXHtmlTree::NoConvertAction);
	//m_Tree.LoadXmlFromFile(_T("D:\\CP Articles\\XHtmlTreeTest\\1.0\\vs2005\\utf16le.xml"), CXHtmlTree::ConvertToAnsi);
	//return;

	m_strResourceName = lpszResource;

#ifdef XHTMLXML

	CXHtmlTree::ConvertAction eConvertAction = CXHtmlTree::NoConvertAction;

#ifdef UNICODE
	eConvertAction = CXHtmlTree::ConvertToUnicode;
#endif

	m_Tree.LoadXmlFromResource(NULL, lpszResource, _T("TEXT"), eConvertAction);
	m_Tree.SaveXml(m_Tree.GetRootItem(), _T("save.xml"), TRUE);	// test of saving XML
#else
	AfxMessageBox(_T("XML is currently disabled.\r\n\r\n")
				  _T("Define XHTMLXML and re-compile to enable XML.\r\n"));
#endif

	m_nCount = m_Tree.GetXmlCount();
}

//=============================================================================
void CXHtmlTreeTestDlg::LoadTextFileFromResource(LPCTSTR lpszResource, 
												 int nRoot /*=0*/)
//=============================================================================
{
	TRACE(_T("in CXHtmlTreeTestDlg::LoadTextFileFromResource: %s\n"), lpszResource);

	m_strResourceName = lpszResource;

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

	CString strTitle = _T("<font color=\"dodgerblue\">Dogs of the World</font>");
	CString strRoot = _T("");
	if (nRoot)
		strRoot.Format(_T(" %d"), nRoot);
	strTitle += strRoot;

	hParent[0] = m_Tree.InsertItem(strTitle, TV_NOIMAGE, TV_NOIMAGE);
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

//=============================================================================
void CXHtmlTreeTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
//=============================================================================
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

//=============================================================================
void CXHtmlTreeTestDlg::OnPaint() 
//=============================================================================
{
	CPaintDC dc(this); // device context for painting
	if (IsIconic())
	{

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

		// paint CXBreadCrumbBar objects
		m_BreadCrumbBar.Draw(m_hWnd, FALSE);
	}
}

//=============================================================================
HCURSOR CXHtmlTreeTestDlg::OnQueryDragIcon()
//=============================================================================
{
	return (HCURSOR) m_hIcon;
}

//=============================================================================
void CXHtmlTreeTestDlg::SetBreadCrumbBar(HTREEITEM hItem)
//=============================================================================
{
	TRACE(_T("in CXHtmlTreeTestDlg::SetBreadCrumbBar\n"));

	// display item breadcrumb trail
	const TCHAR sepchar = _T('~');
	CStringArray sa;
	CPtrArray pa;

	if (hItem == NULL)
		hItem = m_Tree.GetSelectedItem();

	m_Tree.GetItemPath(hItem, sa, pa);

	CString strPath = _T("");
	int i = 0;
	int n = sa.GetSize();
	CString s = _T("");

	// accumulate breadcrumbs, separate with '~'
	for (i = 0; i < n; i++)
	{
		if (!strPath.IsEmpty())
			strPath += sepchar;
		s.Format(_T("<a href=\"app:WM_APP_COMMAND_SEL%d\">"), i);
		// last breadcrumb is inactive
		if (i < (n-1))
			strPath += s;
		s = sa[i];
		if (s.IsEmpty())
			s = _T(' ');	// ensure breadcrumb element is not empty
		int index = s.Find(_T('('));
		// remove parenthetical remarks to shorten string
		if (index >= 0)
			s = s.Left(index);
		if (s.IsEmpty())
			s = _T(' ');	// ensure breadcrumb element is not empty
		strPath += s;
		if (i < (n-1))
			strPath += _T("</a>");
	}
	TRACE(_T("strPath=<%s>\n"), strPath);

	APP_COMMAND *AppCommands = new APP_COMMAND [pa.GetSize()];

	int ncmd = 0;
	for (ncmd = 0; ncmd < pa.GetSize(); ncmd++)
	{
		AppCommands[ncmd].hWnd       = m_hWnd;
		AppCommands[ncmd].uMessage   = WM_APP_COMMAND_SEL;
		AppCommands[ncmd].wParam     = (WPARAM)pa[ncmd];
		s.Format(_T("WM_APP_COMMAND_SEL%d"), ncmd);
		AppCommands[ncmd].pszCommand = _tcszdup(s);
	}

	CRect rect;
	m_BreadCrumb.GetWindowRect(&rect);
	ScreenToClient(&rect);

	CXBreadCrumbBar::XHTMLDRAWSTRUCT ds;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	CFont *pFont = GetFont();	// get font for the dialog
	if (pFont)
		pFont->GetLogFont(&lf);
	ds.bBold = TRUE;
	ds.bLogFont = TRUE;
	memcpy(&ds.lf, &lf, sizeof(LOGFONT));

	ds.crBackground = GetSysColor(COLOR_BTNFACE);
	ds.rect = rect;

	m_BreadCrumbBar.SetCrumbs(strPath, sepchar)
				   .SetSeparator(_T(" > "))
				   .SetAppCommands(AppCommands, ncmd)
				   .InitDrawStruct(&ds, FALSE);

	m_BreadCrumbBar.Draw(m_hWnd, FALSE);

	for (ncmd = 0; ncmd < pa.GetSize(); ncmd++)
	{
		if (AppCommands[ncmd].pszCommand)
			delete [] AppCommands[ncmd].pszCommand;
	}
	delete [] AppCommands;
}

//=============================================================================
// OnSelchangedTree1
//
// This function shows how to handle TVN_SELCHANGED messages from XHtmlTree.
//
void CXHtmlTreeTestDlg::OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult) 
//=============================================================================
{
	NMTREEVIEW* pNMTreeView = (NMTREEVIEW*)pNMHDR;
	
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;

	CString strItem = m_Tree.GetItemText(hItem);
	TRACE(_T("in CXHtmlTreeTestDlg::OnSelchangedTree1:  <%s>\n"), strItem);

	GetDlgItem(IDC_UPDATE)->EnableWindow(FALSE);
	m_Edit.EnableWindow(TRUE);
	m_Edit.SetWindowText(strItem);

	if (hItem)
	{
		if (m_bLog)
			m_List.Printf(CXListBox::Blue, CXListBox::White, 0, 
				_T("%04d  selection changed to '%s'"), m_nLineNo++, strItem);

		DumpInfo(hItem);

		SetBreadCrumbBar(hItem);
	}

	*pResult = 0;
}

//=============================================================================
// OnRclickTree1
//
// This function shows how to handle NM_RCLICK messages
//
void CXHtmlTreeTestDlg::OnRclickTree1(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
//=============================================================================
{
	TRACE(_T("in CXHtmlTreeTestDlg::OnRclickTree1\n"));

	// get the mouse position from this message
	const MSG* pMessage = GetCurrentMessage();
	ASSERT(pMessage);

	if (pMessage)
	{
		CPoint point = pMessage->pt;	// get the point from the message
		LogRightClick(_T("NM_RCLICK"), point);
	}

	*pResult = 0;
}

//=============================================================================
// OnContextMenu
//
// This function shows how to handle WM_CONTEXTMENU messages
//
void CXHtmlTreeTestDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
//=============================================================================
{
	TRACE(_T("in CXHtmlTreeTestDlg::OnContextMenu\n"));

	if (pWnd->m_hWnd == m_Tree.m_hWnd)
		LogRightClick(_T("WM_CONTEXTMENU"), point);
}

//=============================================================================
void CXHtmlTreeTestDlg::LogRightClick(LPCTSTR lpszMsg, CPoint point) 
//=============================================================================
{
	CPoint pt = point;
	m_Tree.ScreenToClient(&pt);
	UINT flags = 0;
	HTREEITEM hItem = m_Tree.HitTest(pt, &flags);

	// check if mouse clicked anywhere on item 
	if (hItem && (flags & (TVHT_ONITEM | TVHT_ONITEMBUTTON | TVHT_ONITEMRIGHT | TVHT_ONITEMINDENT)))
	{
		if (m_bLog)
			m_List.Printf(CXListBox::Blue, CXListBox::White, 0, 
				_T("%04d  right click (%s) on item 0x%X - '%s'"), 
				m_nLineNo++, lpszMsg, hItem, m_Tree.GetItemText(hItem, TRUE));
		
		if (_tcsicmp(lpszMsg, _T("WM_CONTEXTMENU")) == 0)
		{
			CMenu menu;
			VERIFY(menu.CreatePopupMenu());

			if (m_Tree.IsEnabled(hItem))
			{
				VERIFY(menu.AppendMenu(MF_STRING, ID_DISABLE, _T("Disable")));
				VERIFY(menu.AppendMenu(MF_STRING|MF_GRAYED, ID_ENABLE, _T("Enable")));
			}
			else
			{
				VERIFY(menu.AppendMenu(MF_STRING|MF_GRAYED, ID_DISABLE, _T("Disable")));
				VERIFY(menu.AppendMenu(MF_STRING, ID_ENABLE, _T("Enable")));
			}

			VERIFY(menu.AppendMenu(MF_SEPARATOR, 0, _T("")));
			VERIFY(menu.AppendMenu(MF_STRING, ID_TREE_DELETE, _T("Delete")));

			VERIFY(menu.AppendMenu(MF_SEPARATOR, 0, _T("")));
			VERIFY(menu.AppendMenu(MF_STRING, ID_TREE_SEPARATOR, _T("Insert Separator")));

			m_hTrackItem = hItem;

			VERIFY(menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, point.x, point.y, this, NULL));
		}
	}
	else
	{
		if (m_bLog)
			m_List.Printf(CXListBox::Blue, CXListBox::White, 0, 
				_T("%04d  right click (%s), not on item"), 
				m_nLineNo++, lpszMsg);
	}
}

//=============================================================================
void CXHtmlTreeTestDlg::OnDisable()
//=============================================================================
{
	if (m_hTrackItem)
		m_Tree.EnableBranch(m_hTrackItem, FALSE);
	m_hTrackItem = 0;
	DumpInfo(m_Tree.GetSelectedItem());
}

//=============================================================================
void CXHtmlTreeTestDlg::OnEnable()
//=============================================================================
{
	if (m_hTrackItem)
		m_Tree.EnableBranch(m_hTrackItem, TRUE);
	m_hTrackItem = 0;
	DumpInfo(m_Tree.GetSelectedItem());
}

//=============================================================================
void CXHtmlTreeTestDlg::OnSeparator()
//=============================================================================
{
	TRACE(_T("in CXHtmlTreeTestDlg::OnSeparator\n"));
	if (m_hTrackItem)
		m_Tree.InsertSeparator(m_hTrackItem);
	m_hTrackItem = 0;
	DumpInfo(m_Tree.GetSelectedItem());
}

//=============================================================================
void CXHtmlTreeTestDlg::OnDelete()
//=============================================================================
{
	TRACE(_T("in CXHtmlTreeTestDlg::OnDelete\n"));
	if (m_hTrackItem)
		m_Tree.DeleteItem(m_hTrackItem);
	m_hTrackItem = 0;
	DumpInfo(m_Tree.GetSelectedItem());
}

//=============================================================================
// OnUpdate() is called when the user clicks the Update button to update
// the item text with the text from the edit box.
//
void CXHtmlTreeTestDlg::OnUpdate() 
//=============================================================================
{
	CString strItem = _T("");
	m_Edit.GetWindowText(strItem);
	strItem.Replace(_T("\r\n"), _T(" "));

	HTREEITEM hItem = m_Tree.GetSelectedItem();
	ASSERT(hItem);

	if (hItem)
	{
		if (strItem.IsEmpty())
		{
			strItem = m_Tree.GetItemText(hItem);
			m_Edit.SetWindowText(strItem);
		}
		else
		{
			if (m_bLog)
				m_List.Printf(CXListBox::Green, CXListBox::White, 0, 
					_T("%04d  Updating item text"), m_nLineNo++);
			m_Tree.SetItemText(hItem, strItem);
			m_Tree.SetItemTextColor(hItem, RGB(255,0,0));
			SetBreadCrumbBar(hItem);
		}
	}

	GetDlgItem(IDC_UPDATE)->EnableWindow(FALSE);
}

//=============================================================================
// OnExpanded
//
// This function shows how to handle WM_XHTMLTREE_ITEM_EXPANDED messages 
// from XHtmlTree.
//
LRESULT CXHtmlTreeTestDlg::OnExpanded(WPARAM wParam, LPARAM /*lParam*/)
//=============================================================================
{
	TRACE(_T("in CXHtmlTreeTestDlg::OnExpanded\n"));

	XHTMLTREEMSGDATA *pData = (XHTMLTREEMSGDATA *)wParam;
	ASSERT(pData);

	if (pData)
	{
		HTREEITEM hItem = pData->hItem;

		if (hItem)
		{
			if (m_bLog)
				m_List.Printf(CXListBox::Blue, CXListBox::White, 0, 
					_T("%04d  item expanded/collapsed at '%s'"), m_nLineNo++,
					m_Tree.GetItemText(hItem));
			DumpInfo(hItem);
		}
	}
	return 0;
}

//=============================================================================
// OnCheckbox
//
// This function shows how to handle WM_XHTMLTREE_CHECKBOX_CLICKED messages 
// from XHtmlTree.
//
LRESULT CXHtmlTreeTestDlg::OnCheckbox(WPARAM wParam, LPARAM lParam)
//=============================================================================
{
	TRACE(_T("in CXHtmlTreeTestDlg::OnCheckbox\n"));

	XHTMLTREEMSGDATA *pData = (XHTMLTREEMSGDATA *)wParam;
	ASSERT(pData);

	BOOL bChecked = lParam;

	if (pData)
	{
		HTREEITEM hItem = pData->hItem;

		if (hItem)
		{
			if (m_bLog)
				m_List.Printf(CXListBox::Blue, CXListBox::White, 0, 
					_T("%04d  checkbox %schecked at '%s'"), m_nLineNo++,
					bChecked ? _T("") : _T("un"),
					m_Tree.GetItemText(hItem));

			DumpInfo(hItem);

			UINT uState = m_Tree.GetItemState(hItem, TVIS_STATEIMAGEMASK);
			uState = uState >> 12;
			int nStateImage = m_Tree.GetStateImage(hItem);
			TRACE(_T("bChecked=%d  uState=%X  nStateImage=%d\n"), bChecked, uState, nStateImage);

			if (m_pCheckedItemsDlg)
				OnShowChecked();
		}
	}

	return 0;
}

//=============================================================================
void CXHtmlTreeTestDlg::DumpInfo(HTREEITEM hItem)
//=============================================================================
{
	CString str = _T("");
	if (hItem)
	{
		str = m_Tree.GetItemText(hItem);
		TRACE(_T("DumpInfo:  0x%X  <%s>.....\n"), hItem, str);
		str.Format(_T("   bChecked=%d nChildren=%d nChecked=%d bExpanded=%d bHasBeenExpanded=%d nDisabled=%d"),
			m_Tree.GetCheck(hItem), m_Tree.GetChildrenCount(hItem), 
			m_Tree.GetChildrenCheckedCount(hItem),
			m_Tree.IsExpanded(hItem),
			m_Tree.GetHasBeenExpanded(hItem),
			m_Tree.GetChildrenDisabledCount(hItem));
		if (m_bLog)
			m_List.Printf(CXListBox::Black, CXListBox::White, 0, 
					_T("%04d  %s"), m_nLineNo++, str);
		TRACE(_T("DumpInfo:  %s  GetCheck()=%d  GetEnable()=%d\n"), 
			str, m_Tree.GetCheck(hItem), m_Tree.IsEnabled(hItem));

		TCHAR s[100];
		_stprintf(s, _T("Item Info - 0x%X"), hItem);
		if (m_Tree.IsSeparator(hItem))					//+++1.6
			_tcscat(s, _T("  (Separator)"));
		m_ItemInfo.SetWindowText(s);

		int nImage, nSelImage;
		m_Tree.GetItemImage(hItem, nImage, nSelImage);
		_itot(nImage, s, 10);
		if (nImage == TV_NOIMAGE)
			_tcscpy(s, _T("TV_NOIMAGE"));
		m_ItemImage.SetWindowText(s);

		m_IsChecked.SetWindowText(m_Tree.GetCheck(hItem) ? _T("TRUE") : _T("FALSE"));
		m_NoChecked.SetWindowText(_itot(m_Tree.GetChildrenCheckedCount(hItem), s, 10));
		m_NoChildren.SetWindowText(_itot(m_Tree.GetChildrenCount(hItem), s, 10));
		m_NoSeparators.SetWindowText(_itot(m_Tree.GetSeparatorCount(hItem), s, 10));

		m_Expanded.SetWindowText(m_Tree.IsExpanded(hItem) ? _T("Yes") : _T("No"));
	}

	HTREEITEM hRoot = m_Tree.GetRootItem();
	if (hRoot)
	{
		int nTotalChildren = m_Tree.GetChildrenCount(hRoot);
		int nTotalCheckedChildren = m_Tree.GetChildrenCheckedCount(hRoot);
		TRACE(_T("nTotalChildren=%d  nTotalCheckedChildren=%d\n"), nTotalChildren, nTotalCheckedChildren);
		str.Format(_T("Tree contains %d children, %d %s checked."),
				nTotalChildren, 
				nTotalCheckedChildren,
				(nTotalCheckedChildren == 1) ? _T("is") : _T("are"));
		m_TreeInfo.SetWindowText(str);
	}
}

//=============================================================================
// OnAppCommand will be called when user clicks on "American Staghound" link
//    wParam = parameter #3 from XHTMLTREE_APP_COMMAND
//    lParam = HTREEITEM of item
LRESULT CXHtmlTreeTestDlg::OnAppCommand1(WPARAM wParam, LPARAM lParam)
//=============================================================================
{
	TRACE(_T("in CXHtmlTreeTestDlg::OnAppCommand1:  wParam=%d  lParam=%X\n"), wParam, lParam);

	TCHAR plaintext[1000];

	CXHtmlDraw hd;
	hd.GetPlainText(m_Tree.GetItemText((HTREEITEM)lParam), 
		plaintext, sizeof(plaintext)/sizeof(TCHAR)-1);

	if (m_bLog)
		m_List.Printf(CXListBox::Blue, CXListBox::White, 0, 
			_T("%04d  app command 1:  '%s'   wParam = %u   lParam = %X"), 
			m_nLineNo++, plaintext, wParam, lParam);

	CString s;
	s.Format(_T("got WM_APP_COMMAND_1 for '%s'\n\nwParam = %u   lParam = %X"),
		plaintext, wParam, lParam);

	::PlaySound(_T("woofwoof"), AfxGetApp()->m_hInstance,
				SND_RESOURCE|SND_ASYNC|SND_NOWAIT|SND_NODEFAULT);

	XMessageBox(m_hWnd, s, _T("XHtmlTreeTest"),
				MB_OK | MB_ICONINFORMATION | MB_NOSOUND);

	return 0;
}

//=============================================================================
// OnAppCommand2 will be called when user clicks on "Greyhound" link
//    wParam = parameter #3 from XHTMLTREE_APP_COMMAND
//    lParam = HTREEITEM of item
LRESULT CXHtmlTreeTestDlg::OnAppCommand2(WPARAM wParam, LPARAM lParam)
//=============================================================================
{
	TRACE(_T("in CXHtmlTreeTestDlg::OnAppCommand2:  wParam=%d  lParam=%X\n"), wParam, lParam);

	TCHAR plaintext[1000];

	CXHtmlDraw hd;
	hd.GetPlainText(m_Tree.GetItemText((HTREEITEM)lParam), 
		plaintext, sizeof(plaintext)/sizeof(TCHAR)-1);

	if (m_bLog)
		m_List.Printf(CXListBox::Blue, CXListBox::White, 0, 
			_T("%04d  app command 2:  '%s'   wParam = %u   lParam = %X"), 
			m_nLineNo++, plaintext, wParam, lParam);

	CString s;
	s.Format(_T("got WM_APP_COMMAND_2 for '%s'\n\nwParam = %u   lParam = %X"),
		plaintext, wParam, lParam);

	XMessageBox(m_hWnd, s, _T("XHtmlTreeTest"),
				MB_OK | MB_ICONINFORMATION | MB_NOSOUND);

	return 0;
}

//=============================================================================
void CXHtmlTreeTestDlg::OnChangeEdit1() 
//=============================================================================
{
	GetDlgItem(IDC_UPDATE)->EnableWindow(TRUE);
}

//=============================================================================
void CXHtmlTreeTestDlg::OnCollapseAll() 
//=============================================================================
{
	if (m_bLog)
		m_List.Printf(CXListBox::Green, CXListBox::White, 0, 
				_T("%04d  Collapsing all items"), m_nLineNo++);

	m_Tree.CollapseAll();
	m_Tree.SetFocus();
}

//=============================================================================
void CXHtmlTreeTestDlg::OnExpandAll() 
//=============================================================================
{
	if (m_bLog)
		m_List.Printf(CXListBox::Green, CXListBox::White, 0, 
				_T("%04d  Expanding all items"), m_nLineNo++);

	m_Tree.ExpandAll();
	m_Tree.SetFocus();
}

//=============================================================================
void CXHtmlTreeTestDlg::OnCheckAll() 
//=============================================================================
{
	if (m_bLog)
		m_List.Printf(CXListBox::Green, CXListBox::White, 0, 
				_T("%04d  Toggling checkbox for all items"), m_nLineNo++);

	m_Tree.CheckAll(m_bCheckAll);
	m_bCheckAll = !m_bCheckAll;
	m_Tree.SetFocus();
}

//=============================================================================
void CXHtmlTreeTestDlg::OnUpdateTree() 
//=============================================================================
{
	UpdateTree(TRUE);
	m_Tree.SetFocus();
}

//=============================================================================
void CXHtmlTreeTestDlg::UpdateTree(BOOL bReInit) 
//=============================================================================
{
	UpdateData(TRUE);
	if (bReInit)
		if (m_bLog)
			m_List.Printf(CXListBox::Green, CXListBox::White, 0, 
				_T("%04d  Reinitializing tree"), m_nLineNo++);

	m_ItemImage.SetWindowText(_T(""));
	m_IsChecked.SetWindowText(_T(""));
	m_NoChecked.SetWindowText(_T(""));
	m_NoChildren.SetWindowText(_T(""));
	m_Expanded.SetWindowText(_T(""));
	m_TreeInfo.SetWindowText(_T(""));

	UpdateData(TRUE);

	m_Tree.Initialize(m_bCheckBoxes, TRUE)
		  .SetSmartCheckBox(m_bSmartCheckBoxes)
		  .SetHtml(m_bHtml)
		  .SetStripHtml(m_bStripHtml)
		  .SetImages(m_bImages)
		  .SetReadOnly(m_bReadOnly)
		  .SetDragOps(XHTMLTREE_DO_DEFAULT)
		  //.SetSeparatorColor(RGB(0,0,255))
		  .SetDropCursors(IDC_NODROP, IDC_DROPCOPY, IDC_DROPMOVE);

	//m_Tree.SetInsertMarkColor(RGB(255,0,0));

	TRACE(_T("setting image list\n"));
	if (m_bImages)
		m_Tree.SetImageList(&m_Images, TVSIL_NORMAL);
	else
		m_Tree.SetImageList(NULL, TVSIL_NORMAL);

	m_Tree.SetTextColor(m_rgbText);

	if (m_bReadOnly)
		m_Tree.SetBkColor(m_Tree.GetDisabledColor(GetSysColor(COLOR_WINDOW)));
	else
		m_Tree.SetBkColor(m_rgbBackground);

	if (m_nInput == 0)
		LoadTextFileFromResource(_T("IDU_DOGS1"));
	else if (m_nInput == 1)
		LoadTextFileFromResource(_T("IDU_DOGS2"));
	else if (m_nInput == 2)
		LoadXmlFileFromResource(_T("IDU_DOGS3"));
	else if (m_nInput == 3)
		LoadXmlFileFromResource(_T("IDU_DOGS4"));
	else if (m_nInput == 4)
	{
		//+++1.6   multiple roots
		LoadTextFileFromResource(_T("IDU_DOGS2"), 1);
		LoadTextFileFromResource(_T("IDU_DOGS2"), 2);
		LoadTextFileFromResource(_T("IDU_DOGS2"), 3);
		LoadTextFileFromResource(_T("IDU_DOGS2"), 4);
		LoadTextFileFromResource(_T("IDU_DOGS2"), 5);
	}

	if (m_bLog)
		m_List.Printf(CXListBox::Blue, CXListBox::White, 0, 
			_T("%04d  %d items loaded from resource '%s'"), 
			m_nLineNo++, m_nCount, m_strResourceName);

	CString strTitle;
	strTitle.LoadString(AFX_IDS_APP_TITLE);
	strTitle += _T(" - ");
	strTitle += m_strResourceName;
	SetWindowText(strTitle);
}

//=============================================================================
void CXHtmlTreeTestDlg::OnShowChecked() 
//=============================================================================
{
	if ((m_pCheckedItemsDlg == NULL) ||
		(!::IsWindow(m_pCheckedItemsDlg->m_hWnd)))
	{
		m_pCheckedItemsDlg = new CCheckedItemsDialog(this, m_ptCheckedItems);
	}

	int nChecked = 0;
	CString str = _T("");

	HTREEITEM hItem = m_Tree.GetFirstCheckedItem();
	while (hItem)
	{
		CString s;
		s.Format(_T("0x%08X   "), hItem);
		CString strText = m_Tree.GetItemText(hItem, TRUE);
		if (!str.IsEmpty())
			str += _T("\r\n");
		str += s;
		str += strText;
		nChecked++;

		hItem = m_Tree.GetNextCheckedItem(hItem);
	}

	if (nChecked == 0)
	{
		str = _T("No checked items at this time.");
	}

	if (m_pCheckedItemsDlg)
		m_pCheckedItemsDlg->SetText(str);

	m_Tree.SetFocus();
}

//=============================================================================
// OnInitTreeToolTip
//
// This message is received when tooltip is being initialized.
//=============================================================================
#ifdef XHTMLTOOLTIPS
LRESULT CXHtmlTreeTestDlg::OnInitTreeToolTip(WPARAM, LPARAM lParam)
#else
LRESULT CXHtmlTreeTestDlg::OnInitTreeToolTip(WPARAM, LPARAM)
#endif
{
	TRACE(_T("in CXHtmlTreeTestDlg::OnInitTreeToolTip\n"));

#ifdef XHTMLTOOLTIPS

	CPPToolTip * pToolTip = (CPPToolTip *) lParam;

	if (pToolTip && IsWindow(pToolTip->m_hWnd))
	{
		pToolTip->SetColorBk(RGB(255, 255, 255), RGB(240, 247, 255), RGB(192, 192, 208));
		pToolTip->SetEffectBk(13, 5);
		pToolTip->SetDelayTime(PPTOOLTIP_TIME_AUTOPOP, 8000);
	}

#endif

	return 0;
}

//=============================================================================
// OnDisplayTreeToolTip
//
// This message is received when tooltip is about to be displayed.  
// Return FALSE to allow the display, TRUE to prevent it.
//=============================================================================
#ifdef XHTMLTOOLTIPS
LRESULT CXHtmlTreeTestDlg::OnDisplayTreeToolTip(WPARAM wParam, LPARAM lParam)
#else
LRESULT CXHtmlTreeTestDlg::OnDisplayTreeToolTip(WPARAM wParam, LPARAM)
#endif
{
	TRACE(_T("in CXHtmlTreeTestDlg::OnDisplayTreeToolTip\n"));

	LRESULT lResult = 0;

	XHTMLTREEMSGDATA *pData = (XHTMLTREEMSGDATA *)wParam;
	ASSERT(pData);

	HTREEITEM hItem = pData->hItem;

#ifdef XHTMLTOOLTIPS

	CPPToolTip * pToolTip = (CPPToolTip *) lParam;

	if (hItem && pToolTip && IsWindow(pToolTip->m_hWnd))
	{
		// do custom stuff here
	}
	else
	{
		lResult = 1;	// don't display
	}

#endif

	CString strText = m_Tree.GetItemText(hItem);
	TRACE(_T("hItem=%X  strText=<%s>\n"), hItem, strText);

	if (_tcsncmp(strText, _T("Galgo"), 5) == 0)
	{
		// zero tip width will use default width
		m_Tree.SetItemNote(hItem, 
			_T("This is alternate text. For standard tooltip, it is limited to 80 characters."),
			0);
	}

	return lResult;
}

//=============================================================================
// OnCheckedItemsDialogClosing
//
//  This message is received when the checked items dialog closes.
//
LRESULT CXHtmlTreeTestDlg::OnCheckedItemsDialogClosing(WPARAM, LPARAM lParam)
//=============================================================================
{
	TRACE(_T("in CXHtmlTreeTestDlg::OnCheckedItemsDialogClosing\n"));
	m_ptCheckedItems.x = GET_X_LPARAM(lParam);
	m_ptCheckedItems.y = GET_Y_LPARAM(lParam);
	TRACEPOINT(m_ptCheckedItems);
	m_pCheckedItemsDlg = NULL;
	return 0;
}

//=============================================================================
void CXHtmlTreeTestDlg::OnFind() 
//=============================================================================
{
	SetFocus();
	CFindDialog dlg;
	dlg.m_strFind = m_strFind;
	dlg.m_nFindStart = m_nFindStart;
	dlg.m_nFindDir = m_nFindDir;
	dlg.m_bCheck = m_bFindCheck;
	dlg.m_rect = m_rectFind;

	int rc = dlg.DoModal();
	m_strFind = dlg.m_strFind;
	m_nFindStart = dlg.m_nFindStart;
	m_nFindDir = dlg.m_nFindDir;
	m_bFindCheck = dlg.m_bCheck;
	m_rectFind = dlg.m_rect;

	if (rc == IDOK)
	{
		Find();
	}
	m_Tree.SetFocus();
}

//=============================================================================
void CXHtmlTreeTestDlg::FindNext() 
//=============================================================================
{
	m_nFindDir = 1;
	Find();
}

//=============================================================================
void CXHtmlTreeTestDlg::FindPrev() 
//=============================================================================
{
	m_nFindDir = 0;
	Find();
}

//=============================================================================
void CXHtmlTreeTestDlg::Find() 
//=============================================================================
{
	if (!m_strFind.IsEmpty())
	{
		HTREEITEM hItem = m_Tree.GetSelectedItem();
		if ((hItem == NULL) || (m_nFindStart == 1) || m_bFindCheck)
			hItem = m_Tree.GetRootItem();
		if (hItem)
		{
			BOOL bContinue = TRUE;
			while (bContinue)
			{
				HTREEITEM hItemFound = m_Tree.FindItem(m_strFind, FALSE, 
											m_nFindDir == 1, FALSE, !m_bFindCheck, hItem);
				TRACE(_T("hItemFound=%X\n"), hItemFound);
				if (hItemFound)
				{
					if (m_bFindCheck)
					{
						if ((m_bSmartCheckBoxes && !m_Tree.ItemHasChildren(hItemFound)) ||
							!m_bSmartCheckBoxes)
						{
							m_Tree.SetCheck(hItemFound);
						}
						hItem = hItemFound;
					}
					else
					{
						m_Tree.SelectItem(hItemFound);
						bContinue = FALSE;
					}
				}
				else
				{
					if (!m_bFindCheck)
					{
						CString s;
						s.Format(_T("Cannot find string '%s'"), m_strFind);
						XMessageBox(m_hWnd, s, _T("XHtmlTreeTest"),
									MB_OK | MB_ICONEXCLAMATION | MB_NOSOUND);
					}
					bContinue = FALSE;
				}
			}

			if (m_bFindCheck)
				if (m_bLog)
					m_List.Printf(CXListBox::Blue, CXListBox::White, 0, 
						_T("%04d  %d items checked after search for '%s'"), 
						m_nLineNo++, m_Tree.GetCheckedCount(), m_strFind);
		}
	}
}

//=============================================================================
BOOL CXHtmlTreeTestDlg::PreTranslateMessage(MSG* pMsg) 
//=============================================================================
{
	if ((pMsg->hwnd == 0) || !IsWindow(pMsg->hwnd))
		return TRUE;

	m_ToolTips.RelayEvent(pMsg);
	TranslateAccelerator(m_hWnd, m_hAccel, pMsg);
	if ((pMsg->hwnd == 0) || !IsWindow(pMsg->hwnd))
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

//=============================================================================
void CXHtmlTreeTestDlg::OnColors() 
//=============================================================================
{
	CColorDlg dlg;
	dlg.m_rgbText = m_rgbText;
	dlg.m_rgbBackground = m_rgbBackground;
	if (dlg.DoModal() == IDOK)
	{
		m_rgbText = dlg.m_rgbText;
		m_rgbBackground = dlg.m_rgbBackground;
		m_Tree.SetTextColor(m_rgbText);
		m_Tree.SetBkColor(m_rgbBackground);
		m_Tree.RedrawWindow();
	}
}

//=============================================================================
void CXHtmlTreeTestDlg::OnClose() 
//=============================================================================
{
	CDialog::OnCancel();
}

//=============================================================================
void CXHtmlTreeTestDlg::OnCancel() 
//=============================================================================
{
	TRACE(_T("in CXHtmlTreeTestDlg::OnCancel\n"));
	// override the base class OnCancel() --
	// prevent the ESC key from cancelling the dialog
	//CDialog::OnCancel();
}

//=============================================================================
void CXHtmlTreeTestDlg::OnBeginlabeleditTree1(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
//=============================================================================
{
	TRACE(_T("in CXHtmlTreeTestDlg::OnBeginlabeleditTree1\n"));
	//TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;

	if (m_bLog)
		m_List.Printf(CXListBox::Blue, CXListBox::White, 0, 
			_T("%04d  received TVN_BEGINLABELEDIT"), 
			m_nLineNo++);

	*pResult = FALSE;			// return FALSE to allow edit
}

//=============================================================================
void CXHtmlTreeTestDlg::OnEndlabeleditTree1(NMHDR* pNMHDR, LRESULT* pResult) 
//=============================================================================
{
	TRACE(_T("in CXHtmlTreeTestDlg::OnEndlabeleditTree1\n"));
	
	*pResult = TRUE;			// return TRUE to accept edit

	NMTVDISPINFO* pTVDispInfo = (NMTVDISPINFO*) pNMHDR;
	HTREEITEM hItem = pTVDispInfo->item.hItem;
	ASSERT(hItem);

	LPTSTR pszText = pTVDispInfo->item.pszText;

	BOOL bComplete = pszText && (*pszText != _T('\0'));
	if (!bComplete)
		*pResult = FALSE;		// don't allow empty label

	if (m_bLog)
		m_List.Printf(CXListBox::Blue, CXListBox::White, 0, 
			_T("%04d  received TVN_ENDLABELEDIT: edit %s"), 
			m_nLineNo++, bComplete ? _T("complete") : _T("canceled"));

	if (pszText && (*pszText != _T('\0')))
		m_Edit.SetWindowText(pszText);

	SetTimer(1, 50, NULL);	// set timer to update bread crumb bar - the item
							// text has not yet been updated in the tree

}

//=============================================================================
void CXHtmlTreeTestDlg::OnLog() 
//=============================================================================
{
	m_bLog = !m_bLog;
	UpdateData(FALSE);
}

//=============================================================================
LRESULT CXHtmlTreeTestDlg::OnAppCommandSel(WPARAM wParam, LPARAM)
//=============================================================================
{
	TRACE(_T("in CXHtmlTreeTestDlg::OnAppCommandSel: wParam=%X\n"), wParam);

	if  (wParam)
	{
		m_Tree.SelectItem((HTREEITEM)wParam);		
	}

	return 0;
}

//=============================================================================
void CXHtmlTreeTestDlg::OnMouseMove(UINT nFlags, CPoint point) 
//=============================================================================
{
	m_BreadCrumbBar.RelayMouseMove(m_hWnd);
	CDialog::OnMouseMove(nFlags, point);
}

//=============================================================================
void CXHtmlTreeTestDlg::OnLButtonUp(UINT nFlags, CPoint point) 
//=============================================================================
{
	m_BreadCrumbBar.RelayClick(m_hWnd);
	CDialog::OnLButtonUp(nFlags, point);
}

//=============================================================================
void CXHtmlTreeTestDlg::OnTimer(UINT nIDEvent) 
//=============================================================================
{
	KillTimer(nIDEvent);
	SetBreadCrumbBar(NULL);
	CDialog::OnTimer(nIDEvent);
}

#ifdef XHTMLDRAGDROP

//=============================================================================
LRESULT CXHtmlTreeTestDlg::OnBeginDrag(WPARAM wParam, LPARAM lParam)
//
// Message handler for WM_XHTMLTREE_BEGIN_DRAG:
//    wParam = pointer to XHTMLTREEMSGDATA struct
//    lParam = pointer to XHTMLTREEDRAGMSGDATA struct
//=============================================================================
{
	TRACE(_T("in CXHtmlTreeTestDlg::OnBeginDrag\n"));

	XHTMLTREEMSGDATA *pMsg = (XHTMLTREEMSGDATA *) wParam;
	ASSERT(pMsg);

	XHTMLTREEDRAGMSGDATA *pData = (XHTMLTREEDRAGMSGDATA *) lParam;

	LRESULT lResult = 0;

	if (pMsg && pData)
	{
		CString strCopyMove = _T("move");
		if (pData->bCopyDrag)
			strCopyMove = _T("copy");
		CString strItem = m_Tree.GetItemText(pData->hItem);
		TRACE(_T("starting %s drag on '%s'\n"), strCopyMove, strItem);

		if (strItem == _T("Longdog"))
			lResult = 1;

		if (m_bLog && (lResult == 0))
			m_List.Printf(CXListBox::Blue, CXListBox::White, 0, 
				_T("%04d  starting %s drag on '%s'"), 
				m_nLineNo++, strCopyMove, strItem);
		else if (m_bLog && (lResult == 1))
			m_List.Printf(CXListBox::Red, CXListBox::White, 0, 
				_T("%04d  rejecting drag of '%s'"), 
				m_nLineNo++, strItem);
	}
	else
	{
		TRACE(_T("ERROR bad param\n"));
		ASSERT(FALSE);
	}

	return lResult;	// return 0 to allow drag
}

//=============================================================================
LRESULT CXHtmlTreeTestDlg::OnEndDrag(WPARAM wParam, LPARAM lParam)
//
// Message handler for WM_XHTMLTREE_END_DRAG:
//    wParam = pointer to XHTMLTREEMSGDATA struct
//    lParam = pointer to XHTMLTREEDRAGMSGDATA struct; 0 = drag terminated
//=============================================================================
{
	TRACE(_T("in CXHtmlTreeTestDlg::OnEndDrag\n"));

	XHTMLTREEMSGDATA *pMsg = (XHTMLTREEMSGDATA *) wParam;
	ASSERT(pMsg);

	XHTMLTREEDRAGMSGDATA *pData = (XHTMLTREEDRAGMSGDATA *) lParam;

	LRESULT lResult = 0;

	if (pMsg)
	{
		if (pData)
		{
			CString strItem = m_Tree.GetItemText(pData->hItem);
			CString strDropTarget = _T("");

			if (((UINT_PTR)pData->hAfter & 0xFFFF0000) == 0xFFFF0000)
				strDropTarget = m_Tree.GetItemText(pData->hNewParent);
				//strTextAfter.Format(_T("0x%X"), hAfter);
			else if (pData->hAfter)
				strDropTarget = m_Tree.GetItemText(pData->hAfter);

			TRACE(_T("ending drag:  dropping '%s' on '%s'\n"), strItem, strDropTarget);

			if (strDropTarget == _T("Longdog"))
				lResult = 1;

			if (m_bLog && (lResult == 0))
				m_List.Printf(CXListBox::Blue, CXListBox::White, 0, 
					_T("%04d  ending drag:  dropping '%s' on '%s'"), 
					m_nLineNo++, strItem, strDropTarget);
			else if (m_bLog && (lResult == 1))
				m_List.Printf(CXListBox::Red, CXListBox::White, 0, 
					_T("%04d  ending drag:  rejecting drop of '%s' on '%s'"), 
					m_nLineNo++, strItem, strDropTarget);

			DumpInfo(m_Tree.GetSelectedItem());
		}
		else
		{
			// lParam = 0 ==> drag was terminated by user (left button up
			// when not on item, ESC key, right mouse button down)
			if (m_bLog)
				m_List.Printf(CXListBox::Red, CXListBox::White, 0, 
					_T("%04d  drag terminated by user"), m_nLineNo++);
		}
	}

	return lResult;	// return 0 to allow drop
}

//=============================================================================
LRESULT CXHtmlTreeTestDlg::OnDropHover(WPARAM wParam, LPARAM lParam)
//
// Message handler for WM_XHTMLTREE_DROP_HOVER:
//    wParam = pointer to XHTMLTREEMSGDATA struct
//    lParam = pointer to XHTMLTREEDRAGMSGDATA struct
//=============================================================================
{
	TRACE(_T("in CXHtmlTreeTestDlg::OnDropHover\n"));

	XHTMLTREEMSGDATA *pMsg = (XHTMLTREEMSGDATA *) wParam;
	ASSERT(pMsg);

	XHTMLTREEDRAGMSGDATA *pData = (XHTMLTREEDRAGMSGDATA *) lParam;

	LRESULT lResult = 0;

	if (pMsg && pData)
	{
		CString strItem = m_Tree.GetItemText(pData->hItem);
		CString strTextHover = m_Tree.GetItemText(pData->hAfter);
		TRACE(_T("dragging '%s' over '%s'\n"), strItem, strTextHover);

		if (strTextHover == _T("Longdog"))
			lResult = 1;
	
#if 0  // -----------------------------------------------------------
		if (m_bLog)
			m_List.Printf(CXListBox::Blue, CXListBox::White, 0, 
				_T("%04d  dragging '%s' over '%s'"), 
				m_nLineNo++, strItem, strTextHover);
#endif // -----------------------------------------------------------
	}
	else
	{
		TRACE(_T("ERROR bad param\n"));
		ASSERT(FALSE);
	}

	return lResult;
}

//=============================================================================
LRESULT CXHtmlTreeTestDlg::OnScrollSpeed(WPARAM wParam, LPARAM)
//=============================================================================
{
	CXNamedColors nc(_T("BtnFace"));

	COLORREF rgbOn  = RGB(0,255,0);
	COLORREF rgbOff = nc.GetRGB();

	m_ScrollSpeed1.SetBackgroundColor((wParam >= 1) ? rgbOn : rgbOff);
	m_ScrollSpeed2.SetBackgroundColor((wParam >= 2) ? rgbOn : rgbOff);
	m_ScrollSpeed3.SetBackgroundColor((wParam >= 3) ? rgbOn : rgbOff);

	return 0;
}

#endif // XHTMLDRAGDROP
