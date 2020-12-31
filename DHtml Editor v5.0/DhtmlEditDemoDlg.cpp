
#include "stdafx.h"
#include "DHtmlEditDemo.h"
#include "DHtmlEditDemoDlg.h"
#include "TableProperties.h"
#include "HrProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// forward declaration
int CALLBACK EnumFontNameProc(LOGFONT *plf, TEXTMETRIC* ptm, int nFontType, LPARAM lParam);

CDHtmlEditDemoDlg::CDHtmlEditDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDHtmlEditDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDHtmlEditDemoDlg)
	//}}AFX_DATA_INIT

	mk_OrgMain.left  = 0;
	mk_OrgMain.right = 0;

	pi_Editor = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// Set checkbox status to FALSE 
	// (for ms_ComboStatus not required as the CString constructor sets them to "")
	memset(mb_CheckStatus, 0, _CheckBoxCount *4);
}

void CDHtmlEditDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDHtmlEditDemoDlg)
	DDX_Control(pDX, IDC_BUTTON_HTML5, mCtrl_Html5);
	DDX_Control(pDX, IDC_STATIC_URL, mCtrl_StaticUrl);
	DDX_Control(pDX, IDC_BUTTON_GOFORWARD, mCtrl_GoForward);
	DDX_Control(pDX, IDC_BUTTON_GOBACK, mCtrl_GoBack);
	DDX_Control(pDX, IDC_BUTTON_LOAD, mCtrl_Load);
	DDX_Control(pDX, IDC_EDIT_URL, mCtrl_EditUrl);
	DDX_Control(pDX, IDC_BUTTON_SAVE, mCtrl_Save);
	DDX_Control(pDX, IDC_BUTTON_HELP, mCtrl_Help);
	DDX_Control(pDX, IDC_BUTTON_BACKCOLOR, mCtrl_BgText);
	DDX_Control(pDX, IDC_BUTTON_BGCOLOR, mCtrl_BgBody);
	DDX_Control(pDX, IDC_BUTTON_BGCOLOR_CELL, mCtrl_BgCell);
	DDX_Control(pDX, IDC_BUTTON_CLEAR, mCtrl_Clear);
	DDX_Control(pDX, IDC_BUTTON_COL_LEFT, mCtrl_ColLeft);
	DDX_Control(pDX, IDC_BUTTON_COL_RIGHT, mCtrl_ColRight);
	DDX_Control(pDX, IDC_BUTTON_COMBINE, mCtrl_Combine);
	DDX_Control(pDX, IDC_BUTTON_DELETE_COL, mCtrl_DeleteCol);
	DDX_Control(pDX, IDC_BUTTON_DELETE_ROW, mCtrl_DeleteRow);
	DDX_Control(pDX, IDC_BUTTON_FORECOLOR, mCtrl_ForeColor);
	DDX_Control(pDX, IDC_BUTTON_HR, mCtrl_Hr);
	DDX_Control(pDX, IDC_BUTTON_HRPROP, mCtrl_HrProp);
	DDX_Control(pDX, IDC_BUTTON_IMAGE, mCtrl_Image);
	DDX_Control(pDX, IDC_BUTTON_LINK, mCtrl_Link);
	DDX_Control(pDX, IDC_BUTTON_NOBR, mCtrl_NoBr);
	DDX_Control(pDX, IDC_BUTTON_REMOVEFORMAT, mCtrl_RemoveFormat);
	DDX_Control(pDX, IDC_BUTTON_ROW_ABOVE, mCtrl_RowAbove);
	DDX_Control(pDX, IDC_BUTTON_ROW_BELOW, mCtrl_RowBelow);
	DDX_Control(pDX, IDC_BUTTON_SPLIT, mCtrl_Split);
	DDX_Control(pDX, IDC_BUTTON_TABLE, mCtrl_Table);
	DDX_Control(pDX, IDC_BUTTON_TABLEPROP, mCtrl_TableProp);
	DDX_Control(pDX, IDC_STATIC_EDITOR, mCtrl_StaticEditor);
	DDX_Control(pDX, IDC_CHECK_SOURCE, mCtrl_CheckSource);
	DDX_Control(pDX, IDC_CHECK_DESIGN, mCtrl_CheckDesign);
	DDX_Control(pDX, IDC_CHECK_BOLD, mCtrl_CheckBold);
	DDX_Control(pDX, IDC_CHECK_ITALIC, mCtrl_CheckItalic);
	DDX_Control(pDX, IDC_CHECK_UNDERLINE, mCtrl_CheckUnderline);
	DDX_Control(pDX, IDC_CHECK_LEFTALIGN, mCtrl_CheckLeftAlign);
	DDX_Control(pDX, IDC_CHECK_CENTERALIGN, mCtrl_CheckCenterAlign);
	DDX_Control(pDX, IDC_CHECK_RIGHTALIGN, mCtrl_CheckRightAlign);
	DDX_Control(pDX, IDC_CHECK_ORDERLIST, mCtrl_CheckOrderList);
	DDX_Control(pDX, IDC_CHECK_UNORDERLIST, mCtrl_CheckUnOrderList);
	DDX_Control(pDX, IDC_COMBO_FONTNAME, mCtrl_ComboFontName);
	DDX_Control(pDX, IDC_COMBO_FONTSIZE, mCtrl_ComboFontSize);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDHtmlEditDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDHtmlEditDemoDlg)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO_FONTNAME, OnComboSelchangeComboFontname)
	ON_CBN_SELCHANGE(IDC_COMBO_FONTSIZE, OnSelchangeComboFontsize)
	ON_WM_TIMER()
	ON_CBN_EDITCHANGE(IDC_COMBO_FONTSIZE, OnEditchangeComboFontsize)
	ON_CBN_CLOSEUP(IDC_COMBO_FONTSIZE, OnCloseupComboFontsize)
	ON_WM_GETMINMAXINFO()
	ON_MESSAGE(WM_EXITSIZEMOVE, OnExitSizeMove)
	ON_WM_WINDOWPOSCHANGED()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CDHtmlEditDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	mCtrl_CheckDesign.SetCheck(TRUE);

	// ############## RESIZING STUFF ###################
	
	// retrieve the origional size of Internet Explorer Control and main window
	// before any resizing took place (BEFORE assigning pi_Editor !!)
	mCtrl_StaticEditor.GetWindowRect(mk_OrgMsie);
	GetWindowRect(mk_OrgMain);

	// ############# END RESIZING STUFF ################


	pi_Editor = new CHtmlEditor();
	if (!pi_Editor->CreateEditor(&mCtrl_StaticEditor, this, FALSE, TRUE))
	{
		MessageBox(_T("Error creating CHtmlEditor"), _T("Error"), MB_ICONSTOP);
		CDialog::EndDialog(0);
		return TRUE;
	}

	// Fill the Font combo box
	EnumFontFamilies(GetDC()->m_hDC, 0, (FONTENUMPROC)EnumFontNameProc, (LPARAM)&mCtrl_ComboFontName);

	CString s_Title;
	GetWindowText(s_Title);
	#ifdef _UNICODE
		SetWindowText(s_Title + _T(" - Unicode"));
	#else
		SetWindowText(s_Title + _T(" - MultiByte"));
	#endif
	return TRUE;
}

// ##################### RESIZING STUFF ############################

// Handler for Windows Message WM_WINDOWPOSCHANGED
// Called multiple times WHILE the user resizes or moves or maximizes the main window
// Do nothing here while resizing to avoid flickering
void CDHtmlEditDemoDlg::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	// If main window was maximized or normalized --> resize MSIE
	static BOOL b_Zoomed = -1;
	if (b_Zoomed != IsZoomed())
	{
		b_Zoomed  = IsZoomed();

		if (!IsIconic()) OnExitSizeMove(0,0);
	}

	CDialog::OnWindowPosChanged(lpwndpos);
}

// Handler for Windows Message WM_EXITSIZEMOVE
// Called after the user has FINISHED to move or resize the main window
LRESULT CDHtmlEditDemoDlg::OnExitSizeMove(WPARAM wParam, LPARAM lParam)
{
	if (!pi_Editor)
		return 0;

	CRect k_NewMain;
	GetWindowRect(k_NewMain);

	// IMPORTANT: Resize MSIE only if size has changed !!
	// Otherwise (afer a Move) MSIE would stay blank !
	static CSize k_Size(0,0);
	if (k_Size == k_NewMain.Size()) return 0;
	k_Size = k_NewMain.Size();


	CSize k_Diff = k_NewMain.Size() - (mk_OrgMain.Size() - mk_OrgMsie.Size());

	pi_Editor->MoveWindow(0, 0, k_Diff.cx, k_Diff.cy, SWP_NOMOVE);
	Invalidate(FALSE);
	return 0;
}

// Handler for Windows Message WM_GETMINMAXINFO
// Main Window is about to be resized --> prevent illegal sizes
// Don't allow main window to become smaller than the origional size defined in Resources
// ptMinTrackSize requires WINDOW size
void CDHtmlEditDemoDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// ATTENTION:
	// This function is called once BEFORE OnInitDialog() is called !!!
	// At the first call of this function mk_OrgMain is not yet valid
	if (mk_OrgMain.Width() > 0)
	{
		lpMMI->ptMinTrackSize.x = mk_OrgMain.Width();
		lpMMI->ptMinTrackSize.y = mk_OrgMain.Height() *2 /3; // allow decreasing the height a little
	}	
	CDialog::OnGetMinMaxInfo(lpMMI);
}

// ##################### END RESIZING STUFF #########################

void CDHtmlEditDemoDlg::OnDestroy(void)
{
	if (pi_Editor) pi_Editor->DestroyWindow();
	// delete pi_Editor is not required as DestroyWindow() does the job !
}

void CDHtmlEditDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this);
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width()  - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else CDialog::OnPaint();
}

HCURSOR CDHtmlEditDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDHtmlEditDemoDlg::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == ID_TIMER_COMBO_FONTSIZE)
	{
		KillTimer(nIDEvent);
		OnUserChangedFontsize();
	}	
	
	CDialog::OnTimer(nIDEvent);
}

// ################ FONTS ##################

// List all installed fonts into the combobox
int CALLBACK EnumFontNameProc(LOGFONT *plf, TEXTMETRIC* ptm, int nFontType, LPARAM lParam)
{
	CComboBox* i_Combo = (CComboBox*) lParam;
	i_Combo->AddString(plf->lfFaceName);
	return TRUE;
}

void CDHtmlEditDemoDlg::OnComboSelchangeComboFontname()
{
	CString s_Font;
	mCtrl_ComboFontName.GetWindowText(s_Font);

	if (!pi_Editor->ExecSetCommand(IDM_FONTNAME, s_Font.AllocSysString()))
		MessageBox(_T("The selection or cursor position is invalid!"), _T("Error"), MB_ICONSTOP);
}

void CDHtmlEditDemoDlg::OnSelchangeComboFontsize()
{
	SetTimer(ID_TIMER_COMBO_FONTSIZE, 200, 0);
}

void CDHtmlEditDemoDlg::OnEditchangeComboFontsize() 
{
	SetTimer(ID_TIMER_COMBO_FONTSIZE, 200, 0);
}

void CDHtmlEditDemoDlg::OnCloseupComboFontsize() 
{
	SetTimer(ID_TIMER_COMBO_FONTSIZE, 200, 0);
}

// called from ID_TIMER_COMBO_FONTSIZE
void CDHtmlEditDemoDlg::OnUserChangedFontsize()
{
	CString s_Size;
	mCtrl_ComboFontSize.GetWindowText(s_Size);

	UINT u32_Size = _ttol(s_Size);
	// Do nothing after entering the first digit of a 2 digit number (1..3)
	if (u32_Size < 4 || u32_Size > 99) 
		return;

	// Do not use IDM_FONTSIZE here as it is very gross
	if (!pi_Editor->ExecSetCommand(IDM_FONTSIZE_STYLE, (int)u32_Size))
		MessageBox(_T("The selection or cursor position is invalid!"), _T("Error"), MB_ICONSTOP);
}

// ##################  BUTTON & CHECKBOX CLICKS ####################

// Receives all clicks on buttons and checkboxes
LRESULT CDHtmlEditDemoDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	/*
	CString s_Debug;
	s_Debug.Format(_T("Msg 0x%04X, wParam 0x%08X, lParam 0x%08X"), message, wParam, lParam);
	OutputDebugString(s_Debug);
	*/

	if (message == WM_COMMAND)
	{
		// IDOK is sent when the user hits the Enter key 
		// (except if the cursor is in the Internet Explorer control)
		// Per default this would close the dialog, the application would shut down
		if (wParam == IDOK) 
		{
			// Did the user hit the Enter key while the cursor is in the URL Edit box ?
			if (::GetFocus() == mCtrl_EditUrl.m_hWnd)
			{
				OnWmCommand(IDC_BUTTON_LOAD); // Surf to the URL
			}
			return 0; // prevent this message from getting to CDialog::WindowProc()
		}

		OnWmCommand(wParam);
	}

	if (message == WM_IDLEUPDATECMDUI) OnUpdateUI (wParam);

	return CDialog::WindowProc(message, wParam, lParam);
}

// received WM_COMMAND
void CDHtmlEditDemoDlg::OnWmCommand(WPARAM wParam)
{
	// this table is just for demonstration
	CString s_NewTable = _T("<table border=1 bordercolor=#996633><tr><td colspan=2><div>1AB</div></td><td><div>1C</div></td><td><div>1D</div></td></tr><tr><td><div>2A</div></td><td><div>2B</div></td><td colspan=2><div>2CD</div></td></tr><tr><td><div>3A</div></td><td colspan=2><div>3BC</div></td><td><div>3D</div></td></tr></table>");

	cHtmlDocument *pi_Doc  = pi_Editor->GetDocument();
	cHtmlTableCell  i_Cell  = 0;
	cHtmlTable      i_Table = 0;
	BOOL            b_SelOK = TRUE;
	CString         s_Text;

	// ######## GET CELL #########

	switch (LOWORD(wParam))
	{
	case IDC_BUTTON_BGCOLOR_CELL:
	case IDC_BUTTON_COMBINE:
	case IDC_BUTTON_SPLIT:
	case IDC_BUTTON_DELETE_ROW:
	case IDC_BUTTON_DELETE_COL:
		i_Cell  = pi_Doc->GetSelectedCell(); // outputs error
		i_Table = i_Cell.GetParentTable();
		if (!i_Cell.Valid() || !i_Table.Valid())
			return;
	}

	switch (LOWORD(wParam))
	{
	
	// ##################  Control  ##################
	
	case IDC_BUTTON_HTML5:
	{
		CString s_Html = pi_Editor->GetDocument()->GetHtmlW3C(); // get HTML 5 code
		
		TCHAR t_TempDir[MAX_PATH];
		GetTempPath(MAX_PATH, t_TempDir);
		CString s_Path = CString(t_TempDir) + "Dhtml5.txt";
		
		CFile i_File;
		i_File.Open(s_Path, CFile::modeCreate | CFile::modeWrite);
		
		// Write Unicode BOM
		#ifdef _UNICODE
			BYTE u8_BOM[] = { 0xFF, 0xFE };
			i_File.Write(u8_BOM, sizeof(u8_BOM));	
		#endif

		i_File.Write(s_Html.GetBuffer(0), s_Html.GetLength() * sizeof(TCHAR));
		i_File.Close();

		ShellExecute(m_hWnd, _T("open"), s_Path, _T(""), _T(""), SW_SHOW);
		break;
	}
	case IDC_BUTTON_CLEAR:
		pi_Editor->Clear();
		break;
	case IDC_BUTTON_SAVE:
		pi_Editor->GetDocument()->CleanUpTags(); // remove empty tags
		pi_Editor->Save();
		break;
	case IDC_BUTTON_LOAD:
		mCtrl_EditUrl.GetWindowText(s_Text);
		pi_Editor->Navigate(s_Text);
		break;
	case IDC_BUTTON_GOBACK:
		pi_Editor->GoBack();
		break;
	case IDC_BUTTON_GOFORWARD:
		pi_Editor->GoForward();
		break;
	case IDC_BUTTON_HELP:
		pi_Editor->NavigateToEmbeddedResource(_T("Html_Help"));
		break;
	case IDC_CHECK_DESIGN:
	case IDC_CHECK_SOURCE:
		pi_Editor->SetDisplayMode(mCtrl_CheckSource.GetCheck(), 
			                      mCtrl_CheckDesign.GetCheck());
		break;
	
	// ################## Text formatting ##################

	case IDC_BUTTON_FORECOLOR:
		b_SelOK = pi_Editor->ExecSetCommand(IDM_FORECOLOR, _T("red"));
		break;
	case IDC_BUTTON_BACKCOLOR:
		b_SelOK = pi_Editor->ExecSetCommand(IDM_BACKCOLOR, _T("#AAFFBB"));
		break;
	case IDC_BUTTON_REMOVEFORMAT:
		b_SelOK = pi_Editor->ExecSetCommand(IDM_REMOVEFORMAT);
		break;
	case IDC_CHECK_BOLD:
		b_SelOK = pi_Editor->ExecSetCommand(IDM_BOLD);
		break;
	case IDC_CHECK_ITALIC:
		b_SelOK = pi_Editor->ExecSetCommand(IDM_ITALIC);
		break;
	case IDC_CHECK_UNDERLINE:
		b_SelOK = pi_Editor->ExecSetCommand(IDM_UNDERLINE);
		break;
	case IDC_CHECK_LEFTALIGN:
		b_SelOK = pi_Editor->ExecSetCommand(IDM_JUSTIFYLEFT);
		break;
	case IDC_CHECK_CENTERALIGN:
		b_SelOK = pi_Editor->ExecSetCommand(IDM_JUSTIFYCENTER);
		break;
	case IDC_CHECK_RIGHTALIGN:
		b_SelOK = pi_Editor->ExecSetCommand(IDM_JUSTIFYRIGHT);
		break;
	case IDC_CHECK_UNORDERLIST:
		b_SelOK = pi_Editor->ExecSetCommand(IDM_UNORDERLIST);
		break;
	case IDC_CHECK_ORDERLIST:
		b_SelOK = pi_Editor->ExecSetCommand(IDM_ORDERLIST);
		break;
	
	// ##################  Table  ##################

	case IDC_BUTTON_TABLE:
		// ---- comment out one of the following lines ! ----
		b_SelOK = pi_Editor->GetDocument()->PasteIntoSelection(s_NewTable);
	// 	b_SelOK = pi_Editor->GetDocument().InsertTable(2,2); // insert empty table 2 x 2 cells
		break;
	case IDC_BUTTON_TABLEPROP:
		SetTableProperties();
		break;
	case IDC_BUTTON_ROW_ABOVE:
		pi_Doc->InsertNewTableRow(FALSE);
		break;
	case IDC_BUTTON_ROW_BELOW:
		pi_Doc->InsertNewTableRow(TRUE);
		break;
	case IDC_BUTTON_COL_LEFT:
		pi_Doc->InsertNewTableColumn(FALSE);
		break;
	case IDC_BUTTON_COL_RIGHT:
		pi_Doc->InsertNewTableColumn(TRUE);
		break;
	case IDC_BUTTON_DELETE_ROW:
		i_Table.DeleteRow(i_Cell.GetRowIndex());
		break;		
	case IDC_BUTTON_DELETE_COL:
		i_Table.DeleteColumn(i_Cell.GetColIndex());
		break;
	case IDC_BUTTON_BGCOLOR_CELL:
		i_Cell.SetBgColor(_T("#CC8855"));
		break;
	case IDC_BUTTON_COMBINE:
		if (!i_Cell.Combine())
			MessageBox(_T("You can only combine cells which have a right neighbour."), _T("Error"), MB_ICONSTOP);
		break;		
	case IDC_BUTTON_SPLIT:
		i_Cell.Split();
		break;

	// ###############  other HTML stuff  ##################

	case IDC_BUTTON_BGCOLOR:
		pi_Doc->GetBody(TRUE).SetAttribute(_T("bgcolor"), _T("#FFDDAA"));
		break;
	case IDC_BUTTON_HR:
		b_SelOK = pi_Editor->ExecSetCommand(IDM_HORIZONTALLINE);
		break;
	case IDC_BUTTON_HRPROP:
		SetHRproperties();
		break;
	case IDC_BUTTON_IMAGE:
		b_SelOK = pi_Editor->ExecSetCommand(IDM_IMAGE);
		break;
	case IDC_BUTTON_LINK:
		{
		cHtmlElement i_Sel = pi_Editor->GetDocument()->GetSelection(FALSE);
		if (!i_Sel.Valid()) b_SelOK = FALSE;
		else b_SelOK = pi_Editor->ExecSetCommand(IDM_HYPERLINK);
		break;
		}
	case IDC_BUTTON_NOBR:
		b_SelOK = pi_Doc->AddToSelection(_T("<Nobr>"), _T("</Nobr>"));
		break;
	}

	if (!b_SelOK) 
		MessageBox(_T("The selection or cursor position is invalid for this function!"), _T("Error"), MB_ICONSTOP);
}


// This message is posted from cHtmlEditor::cMsieWnd
// Set the checkboxes according to the current selection / cursor position
// This function is called with every keypress of the user so it is speed optimized
void CDHtmlEditDemoDlg::OnUpdateUI(WPARAM wParam)
{
	if (wParam == HTMLEDIT_INIT_DONE)
	{
		/*
		Put any code here you want to execute after the HTML Editor is ready initialized
		For example any code that loads content into the editor
		*/
		return;
	}

	// Called after every CleanUp (e.g. after Navigation)
	if (wParam == HTMLEDIT_SETDEFAULT)
	{
		cHtmlDocument *pi_Doc = pi_Editor->GetDocument();
		pi_Doc->SetDocumentDefault(_T("BODY"),  cHtmlRuleStyle::E_FontSize,    DEFAULT_FONT_SIZE_STR); // "14"
		pi_Doc->SetDocumentDefault(_T("BODY"),  cHtmlRuleStyle::E_FontFamily,  DEFAULT_FONT_FAMILY);   // "Arial"
		pi_Doc->SetDocumentDefault(_T("BODY"),  cHtmlRuleStyle::E_MarginLeft,  _T("3px"));
		pi_Doc->SetDocumentDefault(_T("BODY"),  cHtmlRuleStyle::E_MarginTop,   _T("2px"));

		pi_Doc->SetDocumentDefault(_T("TABLE"), cHtmlRuleStyle::E_FontSize,    DEFAULT_FONT_SIZE_STR);
		pi_Doc->SetDocumentDefault(_T("TABLE"), cHtmlRuleStyle::E_FontFamily,  DEFAULT_FONT_FAMILY);

		// The title must not be empty for a valid Html 5 document (W3C)
		pi_Doc->SetTitle(_T("ElmüSoft DHTML Editor"));
		return;
	}

	if (wParam == HTMLEDIT_KILLFOCUS)
	{
		/*
		Put any code here you want to execute when the Html Editor loses focus
		For example any code to automatically save user changes
		*/
		return;
	}

	// Display the new URL in Edit box after a navigation took place
	// Replace Mime encoding ("%20" --> " ")
	if (wParam == HTMLEDIT_NAVIGATED)
	{
		mCtrl_EditUrl.SetWindowText(cMisc::DecodeMime(pi_Editor->GetDocument()->GetUrl()));
		return;
	}

	// illegal message
	if (wParam != HTMLEDIT_UPDATE_UI)
		return;

	// ---------------- Enable / Disable -------------------

	       UINT u32_CurDisplay  = pi_Editor->GetDisplayMode();
	static UINT u32_LastDisplay = 0;

    if (u32_LastDisplay != u32_CurDisplay) // do nothing if unchanged
	{
	    u32_LastDisplay   =  u32_CurDisplay;
		BOOL b_DesignMode = (u32_CurDisplay == IDM_EDITMODE);
		BOOL b_BrowseMode = (u32_CurDisplay == IDM_BROWSEMODE);
		BOOL b_SourceMode = (u32_CurDisplay == IDM_VIEWSOURCE);
		
		mCtrl_CheckBold       .EnableWindow(b_DesignMode);
		mCtrl_CheckItalic     .EnableWindow(b_DesignMode);
		mCtrl_CheckUnderline  .EnableWindow(b_DesignMode);
		mCtrl_CheckLeftAlign  .EnableWindow(b_DesignMode);
		mCtrl_CheckCenterAlign.EnableWindow(b_DesignMode);
		mCtrl_CheckRightAlign .EnableWindow(b_DesignMode);
		mCtrl_CheckOrderList  .EnableWindow(b_DesignMode);
		mCtrl_CheckUnOrderList.EnableWindow(b_DesignMode);
		mCtrl_ComboFontName   .EnableWindow(b_DesignMode);
		mCtrl_ComboFontSize   .EnableWindow(b_DesignMode);
		mCtrl_BgText          .EnableWindow(b_DesignMode);
		mCtrl_BgBody          .EnableWindow(b_DesignMode);
		mCtrl_BgCell          .EnableWindow(b_DesignMode);
		mCtrl_ColLeft         .EnableWindow(b_DesignMode);
		mCtrl_ColRight        .EnableWindow(b_DesignMode);
		mCtrl_Combine         .EnableWindow(b_DesignMode);
		mCtrl_DeleteCol       .EnableWindow(b_DesignMode);
		mCtrl_DeleteRow       .EnableWindow(b_DesignMode);
		mCtrl_ForeColor       .EnableWindow(b_DesignMode);
		mCtrl_Hr              .EnableWindow(b_DesignMode);
		mCtrl_HrProp          .EnableWindow(b_DesignMode);
		mCtrl_Image           .EnableWindow(b_DesignMode);
		mCtrl_Link            .EnableWindow(b_DesignMode);
		mCtrl_NoBr            .EnableWindow(b_DesignMode);
		mCtrl_RemoveFormat    .EnableWindow(b_DesignMode);
		mCtrl_RowAbove        .EnableWindow(b_DesignMode);
		mCtrl_RowBelow        .EnableWindow(b_DesignMode);
		mCtrl_Split           .EnableWindow(b_DesignMode);
		mCtrl_Table           .EnableWindow(b_DesignMode);
		mCtrl_TableProp       .EnableWindow(b_DesignMode);
		
		mCtrl_EditUrl         .EnableWindow(b_BrowseMode);
		mCtrl_Load            .EnableWindow(b_BrowseMode);
		mCtrl_GoBack          .EnableWindow(b_BrowseMode);
		mCtrl_GoForward       .EnableWindow(b_BrowseMode);
		mCtrl_StaticUrl       .EnableWindow(b_BrowseMode);

		mCtrl_Save            .EnableWindow(!b_SourceMode);
		mCtrl_Help            .EnableWindow(!b_SourceMode);
		mCtrl_Html5           .EnableWindow(!b_SourceMode);
		mCtrl_Clear           .EnableWindow(!b_SourceMode);
		mCtrl_CheckDesign     .EnableWindow(!b_SourceMode);
	}

	// ---------- Set dynamic checkboxes (buttons) ---------

	// Arrays for all checkboxes, their state and their MSIE commands
	static UINT    u32_bCmd[] = { IDM_VIEWSOURCE,     IDM_EDITMODE,       IDM_BOLD,         IDM_ITALIC,         IDM_UNDERLINE,         IDM_JUSTIFYLEFT,       IDM_JUSTIFYCENTER,       IDM_JUSTIFYRIGHT,       IDM_ORDERLIST,         IDM_UNORDERLIST         };
	static CButton *p_Check[] = { &mCtrl_CheckSource, &mCtrl_CheckDesign, &mCtrl_CheckBold, &mCtrl_CheckItalic, &mCtrl_CheckUnderline, &mCtrl_CheckLeftAlign, &mCtrl_CheckCenterAlign, &mCtrl_CheckRightAlign, &mCtrl_CheckOrderList, &mCtrl_CheckUnOrderList };

	ASSERT(sizeof(u32_bCmd) == sizeof(mb_CheckStatus)); // illegal _CheckBoxCount

	// Set the checkboxes according to the current selection / cursor position
	for (UINT b=0; b<_CheckBoxCount; b++)
	{
		BOOL b_Active = (pi_Editor->QueryStatus(u32_bCmd[b]) & OLECMDF_LATCHED) > 0;
		if  (b_Active == mb_CheckStatus[b])
			continue;

		mb_CheckStatus[b] = b_Active;
		p_Check[b]->SetCheck(b_Active);
	}

	if (u32_CurDisplay != IDM_EDITMODE)
		return;

	// ---------- Set dynamic comboboxes (font) ---------

	static UINT      u32_cCmd[]    = { IDM_FONTNAME,         IDM_FONTSIZE_STYLE   };
	static CComboBox *p_Combo[]    = { &mCtrl_ComboFontName, &mCtrl_ComboFontSize };
	static BOOL       b_DropList[] = { TRUE, /*DropList*/    FALSE  /*DropDown*/  };

	ASSERT(sizeof(u32_cCmd) == sizeof(ms_ComboStatus)); // illegal _ComboBoxCount

	// Set font name and size according to the current selection / cursor position
	CString s_Value;
	for (UINT c=0; c<_ComboBoxCount; c++)
	{
		if (pi_Editor->ExecGetCommandStr(u32_cCmd[c], &s_Value))
		{
			if (s_Value == ms_ComboStatus[c] || s_Value.GetLength() == 0)
				continue;

			if (p_Combo[c]->GetDroppedState()) // If combobox not currently dropped down
				continue;
			
			ms_ComboStatus[c] = s_Value;

			// Depending on the style of the ComboBox we must choose another function here
			if (b_DropList[c]) p_Combo [c]->SelectString(0, s_Value);
			else               p_Combo [c]->SetWindowText(s_Value);
		}
	}
}


// set properties of a <HR> element (horizontal line)
void CDHtmlEditDemoDlg::SetHRproperties()
{
	cHtmlDocument *pi_Doc = pi_Editor->GetDocument();
	cHtmlHR         i_HR  = pi_Doc->GetSelection();

	if (!i_HR.Valid())
	{
		MessageBox(_T("Please select a <HR> element. (horizontal line)"), _T("Error"), MB_ICONSTOP);
		return;
	}

	CHrProperties i_Prop(this);
	i_Prop.ms_Color   = i_HR.GetProperty(cHtmlHR::E_Color);
	i_Prop.ms_Width   = i_HR.GetProperty(cHtmlHR::E_Width);
	i_Prop.ms_Size    = i_HR.GetProperty(cHtmlHR::E_Size);
	i_Prop.ms32_Shade = i_HR.GetShade() ? 1 : 0;

	if (IDOK == i_Prop.DoModal())
	{
		i_HR.SetProperty(cHtmlHR::E_Color, i_Prop.ms_Color);
		i_HR.SetProperty(cHtmlHR::E_Width, i_Prop.ms_Width);
		i_HR.SetProperty(cHtmlHR::E_Size,  i_Prop.ms_Size);

		i_HR.SetShade(i_Prop.ms32_Shade == 1);
	}
}

// set properties of a table
void CDHtmlEditDemoDlg::SetTableProperties()
{
	cHtmlElement i_Sel = pi_Editor->GetDocument()->GetSelection();
	cHtmlTable i_Table = i_Sel.FindParent(_T("TABLE"));
	if (!i_Table.Valid())
	{
		MessageBox(_T("Please set the cursor into a table!"), _T("Error"), MB_ICONSTOP);
		return;
	}

	cHtmlInlineStyle i_Style = i_Table.GetStyle();

	CTableProperties i_Prop(this);

	i_Prop.mu32_Rules     = i_Table.GetBorderRules();
	i_Prop.ms_BackgColor  = i_Table.GetBgColor();
	i_Prop.ms_BorderColor = i_Table.GetBorderColor();
	i_Prop.ms_BorderWidth = i_Table.GetBorderWidth();
	i_Prop.ms_CellSpacing = i_Table.GetCellSpacing();
	i_Prop.ms_CellPadding = i_Table.GetCellPadding();
	i_Prop.ms_Width       = i_Style.GetProperty(cHtmlInlineStyle::E_Width);
	i_Prop.ms_Height      = i_Style.GetProperty(cHtmlInlineStyle::E_Height);
	i_Prop.ms_Width. Replace(_T("px"), _T(""));
	i_Prop.ms_Height.Replace(_T("px"), _T(""));

	if (IDOK == i_Prop.DoModal())
	{
		i_Table.SetBorderRules((cHtmlTable::eRules)i_Prop.mu32_Rules);
		i_Table.SetBgColor    (i_Prop.ms_BackgColor);
		i_Table.SetBorderColor(i_Prop.ms_BorderColor);
		i_Table.SetBorderWidth(i_Prop.ms_BorderWidth);
		i_Table.SetCellSpacing(i_Prop.ms_CellSpacing);
		i_Table.SetCellPadding(i_Prop.ms_CellPadding);

		if (i_Prop.ms_Width. GetLength() && i_Prop.ms_Width. Find(_T("%")) < 0) 
			i_Prop.ms_Width  += _T("px");
		if (i_Prop.ms_Height.GetLength() && i_Prop.ms_Height.Find(_T("%")) < 0) 
			i_Prop.ms_Height += _T("px");
		
		i_Style.SetProperty(cHtmlInlineStyle::E_Width,  i_Prop.ms_Width);
		i_Style.SetProperty(cHtmlInlineStyle::E_Height, i_Prop.ms_Height);
	}
}

