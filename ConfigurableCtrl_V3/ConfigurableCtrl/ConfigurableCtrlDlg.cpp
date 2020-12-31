
// ConfigurableCtrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConfigurableCtrl.h"
#include "ConfigurableCtrlDlg.h"
#include "afxdialogex.h"

#include "CellCtrls\CellEdit.h"
#include "CellCtrls\CellCheckBox.h"
#include "CellCtrls\CellComboBox.h"
#include "CellCtrls\CellDateCtrl.h"
#include "CellCtrls\CellColorCtrl.h"
#include "CellCtrls\CellTimeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CTRLTYPE_EDIT			_T("Edit Ctrl")
#define CTRLTYPE_COMBO			_T("ComboBox")
#define CTRLTYPE_CHECKBOX		_T("CheckBox")
#define CTRLTYPE_DATEPICKER		_T("DatePicker")
#define CTRLTYPE_COLORPICKER	_T("ColorPicker")

#define ALIGNMENTTYPE_LEFT		_T("Left")
#define ALIGNMENTTYPE_RIGHT		_T("Right")
#define ALIGNMENTTYPE_CENTER	_T("Center")

// CConfigurableCtrlDlg dialog

CConfigurableCtrlDlg::CConfigurableCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConfigurableCtrlDlg::IDD, pParent), m_bKeyUp(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CConfigurableCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MYLIST, m_ListCtrl);
	DDX_Control(pDX, IDC_BUT_ENDISALL, m_EnDisAll);
	DDX_Control(pDX, IDC_ENDISCOL, m_EnDisCol);
	DDX_Control(pDX, IDC_ENDISROW, m_EnDisRow);
	DDX_Control(pDX, IDC_TABPROPS, m_PropsTab);
	DDX_Control(pDX, IDC_BUT_ENDISCELL, m_EnDisCell);
	DDX_Control(pDX, IDC_STA_ENDISROW, m_EnDisRowStat);
	DDX_Control(pDX, IDC_STAENDISCOL, m_EnDisColStat);
	DDX_Control(pDX, IDC_GRPENDIS, m_EnDisGrp);
	DDX_Control(pDX, IDC_ROWCOL_ADDCOL, m_RC_AddColumn);
	DDX_Control(pDX, IDC_ROWCOL_ADDROW, m_RC_AddRow);
	DDX_Control(pDX, IDC_ROWCOLHEAD, m_RC_HeaderName);
	DDX_Control(pDX, IDC_ROWCOLNAME, m_RC_RowName);
	DDX_Control(pDX, IDC_ROWCOLPOS, m_RC_HeaderPos);
	DDX_Control(pDX, IDC_ROWCOLWIDTH, m_RC_HeaderWidth);
	DDX_Control(pDX, IDC_STA_ROWCOLHEAD, m_RC_Sta_Head);
	DDX_Control(pDX, IDC_STA_ROWCOLNAME, m_RC_Sta_RowName);
	DDX_Control(pDX, IDC_STA_ROWCOLPOS, m_RC_Sta_HeadPos);
	DDX_Control(pDX, IDC_STA_ROWCOLWIDTH, m_RC_Sta_HeadWidth);
	DDX_Control(pDX, IDC_ROWCOL_REMCOL, m_RC_RemoveColumn);
	DDX_Control(pDX, IDC_ROWCOL_REMROW, m_RC_RemoveRow);
	DDX_Control(pDX, IDC_ROWCOLROW, m_RC_Row);
	DDX_Control(pDX, IDC_STA_ROWCOLROW, m_RC_Sta_Row);
	DDX_Control(pDX, IDC_CTRL_COL, m_Ctrl_Column);
	DDX_Control(pDX, IDC_CTRL_ADD, m_Ctrl_Add);
	DDX_Control(pDX, IDC_CTRL_REM, m_Ctrl_Remove);
	DDX_Control(pDX, IDC_CTRL_ROW, m_Ctrl_Row);
	DDX_Control(pDX, IDC_CTRL_CTRLTYPE, m_Ctrl_Type);
	DDX_Control(pDX, IDC_STA_CTRL_COL, m_Ctrl_Sta_Col);
	DDX_Control(pDX, IDC_STA_CTRL_ROW, m_Ctrl_Sta_Row);
	DDX_Control(pDX, IDC_STA_CTRLTYPE, m_Ctrl_Sta_Type);
	DDX_Control(pDX, IDC_CTRL_DEFAULT, m_Ctrl_Default);
	DDX_Control(pDX, IDC_STA_CTRL_DEFAULT, m_Ctrl_Sta_Default);
	DDX_Control(pDX, IDC_CB_ADD, m_CB_Add);
	DDX_Control(pDX, IDC_CB_COLUMN, m_CB_Column);
	DDX_Control(pDX, IDC_CB_IDX, m_CB_Index);
	DDX_Control(pDX, IDC_CB_REMOVE, m_CB_Remove);
	DDX_Control(pDX, IDC_CB_ROW, m_CB_Row);
	DDX_Control(pDX, IDC_CB_SEL, m_CB_Select);
	DDX_Control(pDX, IDC_CB_TXT_VAL, m_CB_TextValue);
	DDX_Control(pDX, IDC_STA_CB_IDX, m_CB_Sta_Index);
	DDX_Control(pDX, IDC_STA_CB_ROW, m_CB_Sta_Row);
	DDX_Control(pDX, IDC_STA_CB_TXTVAL, m_CB_Sta_TextValue);
	DDX_Control(pDX, IDC_STA_CB_COL, m_CB_Sta_Column);
	DDX_Control(pDX, IDC_EVA_COLUMN, m_Eval_Column);
	DDX_Control(pDX, IDC_EVA_ROW, m_Eval_Row);
	DDX_Control(pDX, IDC_EVA_VALUE, m_Eval_Value);
	DDX_Control(pDX, IDC_ALIGN_ALIGN, m_Align_Align);
	DDX_Control(pDX, IDC_ALIGN_BUT, m_Align_Button);
	DDX_Control(pDX, IDC_ALIGN_COLUMN, m_Align_Column);
	DDX_Control(pDX, IDC_ALIGN_ROW, m_Align_Row);
	DDX_Control(pDX, IDC_STA_ALIGN_ALIGN, m_Align_Sta_Align);
	DDX_Control(pDX, IDC_STA_ALIGN_COLUMN, m_Align_Sta_Row);
	DDX_Control(pDX, IDC_STA_ALIGN_ROW, m_Align_Sta_Column);
}

BEGIN_MESSAGE_MAP(CConfigurableCtrlDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOVE()
	ON_BN_CLICKED(IDC_BUT_ENDISALL, &CConfigurableCtrlDlg::OnBnClickedButEndisall)
	ON_BN_CLICKED(IDC_BUT_ENDISCELL, &CConfigurableCtrlDlg::OnBnClickedButEndiscell)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABPROPS, &CConfigurableCtrlDlg::OnSelchangeTabprops)
	ON_BN_CLICKED(IDC_ROWCOL_ADDCOL, &CConfigurableCtrlDlg::OnBnClickedRowcolAddcol)
	ON_BN_CLICKED(IDC_ROWCOL_REMCOL, &CConfigurableCtrlDlg::OnBnClickedRowcolRemcol)
	ON_BN_CLICKED(IDC_ROWCOL_ADDROW, &CConfigurableCtrlDlg::OnBnClickedRowcolAddrow)
	ON_BN_CLICKED(IDC_ROWCOL_REMROW, &CConfigurableCtrlDlg::OnBnClickedRowcolRemrow)
	ON_BN_CLICKED(IDC_CTRL_ADD, &CConfigurableCtrlDlg::OnBnClickedCtrlAdd)
	ON_BN_CLICKED(IDC_CTRL_REM, &CConfigurableCtrlDlg::OnBnClickedCtrlRem)
	ON_BN_CLICKED(IDC_CB_ADD, &CConfigurableCtrlDlg::OnBnClickedCbAdd)
	ON_BN_CLICKED(IDC_CB_SEL, &CConfigurableCtrlDlg::OnBnClickedCbSel)
	ON_BN_CLICKED(IDC_CB_REMOVE, &CConfigurableCtrlDlg::OnBnClickedCbRemove)
	ON_BN_CLICKED(IDC_EVA_EVALUATE, &CConfigurableCtrlDlg::OnBnClickedEvaEvaluate)
	ON_WM_SIZING()
	ON_BN_CLICKED(IDC_ALIGN_BUT, &CConfigurableCtrlDlg::OnBnClickedAlignBut)
END_MESSAGE_MAP()

// CConfigurableCtrlDlg message handlers

BOOL CConfigurableCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_PropsTab.InsertItem(0, _T("Enabling"), 0);
	m_PropsTab.InsertItem(1, _T("Add/Remove Rows/Columns"), 0);
	m_PropsTab.InsertItem(2, _T("Add/Remove Controls"), 0);
	m_PropsTab.InsertItem(3, _T("Manipulate Combo items"), 0);
	m_PropsTab.InsertItem(4, _T("Change Ctrl Alignment"), 0);

	ViewRowColTabItems(FALSE);
	ViewCtrlTabItems(FALSE);
	ViewComboTabItems(FALSE);
	ViewAlignmentTabItems(FALSE);

	m_Ctrl_Type.AddString(CTRLTYPE_EDIT);
	m_Ctrl_Type.AddString(CTRLTYPE_COMBO);
	m_Ctrl_Type.AddString(CTRLTYPE_CHECKBOX);
	m_Ctrl_Type.AddString(CTRLTYPE_DATEPICKER);
	m_Ctrl_Type.AddString(CTRLTYPE_COLORPICKER);
	m_Ctrl_Type.SetCurSel(0);

	m_Align_Align.AddString(ALIGNMENTTYPE_LEFT);
	m_Align_Align.AddString(ALIGNMENTTYPE_RIGHT);
	m_Align_Align.AddString(ALIGNMENTTYPE_CENTER);

///////////////////////////////////////////////////////////////////////////////////////

//	CCellDateCtrl::SetDateFormat(_T("d dddd MMMM yyyy"));
// Insert columns into CListCtrl	
	m_ListCtrl.InsertColumn(0, _T("Property Name"));
	m_ListCtrl.InsertColumn(1, _T("Property Value"));

	m_ListCtrl.SetColumnWidth(0, 160);
	m_ListCtrl.SetColumnWidth(1, 140);
	
// A few lines:
	m_ListCtrl.InsertItem(0, _T("My thoughts"));
	m_ListCtrl.InsertItem(1, _T("Is sky green?"));
	m_ListCtrl.InsertItem(2, _T("My favourite cactus"));
	m_ListCtrl.InsertItem(3, _T("Random Date"));
	m_ListCtrl.InsertItem(4, _T("Is checkbox on right checked?"));
	m_ListCtrl.InsertItem(5, _T("US Declaration of Independence"));
	m_ListCtrl.InsertItem(6, _T("Shoppping list"));
	m_ListCtrl.InsertItem(7, _T("A nice old car"));
	m_ListCtrl.InsertItem(8, _T("A color"));
	m_ListCtrl.InsertItem(9, _T("My time"));

	m_ListCtrl.SetItem(0, 1, new CCellEdit, _T("(Not interesting)"));

	m_ListCtrl.SetItem(1, 1, new CCellCheckBox, _T("0"));
	m_ListCtrl.SetItem(2, 1, new CCellComboBox, _T("Mammilaria\nTurpinicarpus\nEchinopsis\nRebutia\nLobivia\nNotocactus\nMammilaria\nOpuntia\nCereus\nLophophora\nEchinofossulocactus\nLeuchtenbergia"));
	m_ListCtrl.SetItem(3, 1, new CCellDateCtrl, _T("20070906"));
//	CCellDateCtrl * pDtCrtl = dynamic_cast<CCellDateCtrl *>(m_ListCtrl.GetItemCellCtrl(3, 1));
//	pDtCrtl->SetYMD(2007, 9, 6);
	m_ListCtrl.SetItem(4, 1, new CCellCheckBox, _T("1No, No, it's not."));
	m_ListCtrl.SetItem(5, 1, new CCellDateCtrl, _T("17760704"));
//	pDtCrtl = dynamic_cast<CCellDateCtrl *>(m_ListCtrl.GetItemCellCtrl(5, 1));
//	pDtCrtl->SetYMD(1776, 7, 4);
	m_ListCtrl.SetItem(6, 1, new CCellEdit, _T("Potatoes, carrots, onions"));
	m_ListCtrl.SetItem(7, 1, new CCellComboBox, _T("Lagonda\nArmstrong Siddeley\nBentley\nBugatti\nDe Dion Bouton\nHispano Suiza\nLagonda\nLorraine Dietrich\nMercedes\nNapier\nRolls Royce"));
	m_ListCtrl.SetItem(8, 1, new CCellColorCtrl, _T("0X000000FF"));

	m_ListCtrl.SetItem(9, 1, new CCellTimeCtrl);//, _T("220304"));

//	CCellTimeCtrl *pTmCrtl = dynamic_cast<CCellTimeCtrl *>(m_ListCtrl.GetItemCellCtrl(9, 1));
//	if (pTmCrtl)
//		pTmCrtl->SetTimeFormat(_T("hh HH m t.ss h"));
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CConfigurableCtrlDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CConfigurableCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CConfigurableCtrlDlg::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);
// Seems no way round this and have to explicitly call m_ListCtrl this way.
// Note: this is needed because when move, we want to either close any open
// popups associated with the control or move these as well. It looks funny 
// otherwise.  
	m_ListCtrl.OnParentMove(x, y);
}

BOOL CConfigurableCtrlDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN) 
		m_bKeyUp = FALSE;
	if(pMsg->message==WM_KEYUP) 
		m_bKeyUp = TRUE;
	if((pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN))
	{
		if (m_bKeyUp)
		{
			m_bKeyUp = FALSE;
			return m_ListCtrl.OnEnterEsc(pMsg->wParam);
		}
		else
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CConfigurableCtrlDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnSizing(fwSide, pRect);

	m_ListCtrl.OnSizing(fwSide, pRect);
}

void CConfigurableCtrlDlg::OnBnClickedButEndisall()
{
	if (m_ListCtrl.IsWindowEnabled())
	{
		m_ListCtrl.EnableWindow(FALSE);
		m_EnDisAll.SetWindowText(_T("Enable Ctrl"));
	}
	else
	{
		m_ListCtrl.EnableWindow();
		m_EnDisAll.SetWindowText(_T("Disable Ctrl"));
	}
}


void CConfigurableCtrlDlg::OnBnClickedButEndiscell()
{
	int iItem, iSubItem;

	CString str;

	m_EnDisRow.GetWindowText(str);
	iItem = _ttoi(str);

	m_EnDisCol.GetWindowText(str);
	iSubItem = _ttoi(str);

	m_ListCtrl.EnableCtrl(iItem, iSubItem, !m_ListCtrl.IsCtrlEnabled(iItem, iSubItem));
}

void CConfigurableCtrlDlg::ViewEnDisTabItems(BOOL bVisible)
{
	m_EnDisAll.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_EnDisCol.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_EnDisRow.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_EnDisCell.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_EnDisRowStat.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_EnDisColStat.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_EnDisGrp.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
}

void CConfigurableCtrlDlg::ViewRowColTabItems(BOOL bVisible)
{
	m_RC_AddColumn.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_RC_AddRow.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_RC_HeaderName.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_RC_RowName.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_RC_HeaderPos.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_RC_HeaderWidth.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_RC_Sta_Head.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_RC_Sta_RowName.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_RC_Sta_HeadPos.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_RC_Sta_HeadWidth.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_RC_RemoveColumn.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_RC_RemoveRow.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_RC_Row.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_RC_Sta_Row.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
}

void CConfigurableCtrlDlg::ViewCtrlTabItems(BOOL bVisible)
{
	m_Ctrl_Column.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_Ctrl_Row.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_Ctrl_Type.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_Ctrl_Default.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_Ctrl_Remove.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_Ctrl_Add.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_Ctrl_Sta_Col.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_Ctrl_Sta_Row.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_Ctrl_Sta_Type.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_Ctrl_Sta_Default.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
}

void CConfigurableCtrlDlg::ViewComboTabItems(BOOL bVisible)
{
	m_CB_Add.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_CB_Column.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_CB_Index.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_CB_Remove.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_CB_Row.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_CB_Select.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_CB_TextValue.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_CB_Sta_Index.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_CB_Sta_Row.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_CB_Sta_Column.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_CB_Sta_TextValue.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
}

void CConfigurableCtrlDlg::ViewAlignmentTabItems(BOOL bVisible)
{
	m_Align_Align.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_Align_Button.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_Align_Column.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_Align_Row.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_Align_Sta_Align.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_Align_Sta_Row.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
	m_Align_Sta_Column.ShowWindow(bVisible? SW_SHOW : SW_HIDE);
}

void CConfigurableCtrlDlg::OnSelchangeTabprops(NMHDR *pNMHDR, LRESULT *pResult)
{
	int iIdx = m_PropsTab.GetCurFocus();

	switch (iIdx)
	{
		case 0:
			ViewEnDisTabItems(TRUE);
			ViewRowColTabItems(FALSE);
			ViewCtrlTabItems(FALSE);
			ViewComboTabItems(FALSE);
			ViewAlignmentTabItems(FALSE);
		break;

		case 1:
			ViewEnDisTabItems(FALSE);
			ViewRowColTabItems(TRUE);
			ViewCtrlTabItems(FALSE);
			ViewComboTabItems(FALSE);
			ViewAlignmentTabItems(FALSE);
		break;

		case 2:
			ViewEnDisTabItems(FALSE);
			ViewRowColTabItems(FALSE);
			ViewCtrlTabItems(TRUE);
			ViewComboTabItems(FALSE);
			ViewAlignmentTabItems(FALSE);
		break;

		case 3:
			ViewEnDisTabItems(FALSE);
			ViewRowColTabItems(FALSE);
			ViewCtrlTabItems(FALSE);
			ViewComboTabItems(TRUE);
			ViewAlignmentTabItems(FALSE);
		break;

		case 4:
			ViewEnDisTabItems(FALSE);
			ViewRowColTabItems(FALSE);
			ViewCtrlTabItems(FALSE);
			ViewComboTabItems(FALSE);
			ViewAlignmentTabItems(TRUE);
		break;
	}

	*pResult = 0;
}

void CConfigurableCtrlDlg::OnBnClickedRowcolAddcol()
{
	int iPos, iWidth;
	CString str;
	
	m_RC_HeaderPos.GetWindowText(str);
	iPos = _ttoi(str);

	m_RC_HeaderWidth.GetWindowText(str);
	iWidth = _ttoi(str);
	
	m_RC_HeaderName.GetWindowText(str);

	m_ListCtrl.InsertColumn(iPos, str);
	m_ListCtrl.SetColumnWidth(iPos, iWidth);
}

void CConfigurableCtrlDlg::OnBnClickedRowcolRemcol()
{
	int iPos;
	CString str;
	
	m_RC_HeaderPos.GetWindowText(str);
	iPos = _ttoi(str);

	m_ListCtrl.DeleteColumn(iPos);
}

void CConfigurableCtrlDlg::OnBnClickedRowcolAddrow()
{
	int iPos;
	CString str;
	
	m_RC_Row.GetWindowText(str);
	iPos = _ttoi(str);
	
	m_RC_RowName.GetWindowText(str);
	m_ListCtrl.InsertItem(iPos, str);
}

void CConfigurableCtrlDlg::OnBnClickedRowcolRemrow()
{
	int iPos;
	CString str;
	
	m_RC_Row.GetWindowText(str);
	iPos = _ttoi(str);

	m_ListCtrl.DeleteItem(iPos);
}

void CConfigurableCtrlDlg::OnBnClickedCtrlAdd()
{
	int iRow, iColumn;
	CString str;
	CCellCtrl *pCtrl = NULL;

	m_Ctrl_Type.GetWindowText(str);

	if (!str.Compare(CTRLTYPE_EDIT))
		pCtrl = new CCellEdit;
	else if (!str.Compare(CTRLTYPE_COMBO))
		pCtrl = new CCellComboBox;
	else if (!str.Compare(CTRLTYPE_CHECKBOX))
		pCtrl = new CCellCheckBox;
	else if (!str.Compare(CTRLTYPE_DATEPICKER))
		pCtrl = new CCellDateCtrl;
	else if (!str.Compare(CTRLTYPE_COLORPICKER))
		pCtrl = new CCellColorCtrl;
	
	m_Ctrl_Row.GetWindowText(str);
	iRow = _ttoi(str);

	m_Ctrl_Column.GetWindowText(str);
	iColumn = _ttoi(str);
	
	m_Ctrl_Default.GetWindowText(str);

	m_ListCtrl.SetItem(iRow, iColumn, pCtrl, str);
}

void CConfigurableCtrlDlg::OnBnClickedCtrlRem()
{
	int iRow, iColumn;
	CString str;

	m_Ctrl_Row.GetWindowText(str);
	iRow = _ttoi(str);

	m_Ctrl_Column.GetWindowText(str);
	iColumn = _ttoi(str);

	m_ListCtrl.DeleteCtrl(iRow, iColumn);
}

void CConfigurableCtrlDlg::OnBnClickedCbAdd()
{
	int iRow, iColumn, iIndex;
	CString str;

	m_CB_Row.GetWindowText(str);
	iRow = _ttoi(str);

	m_CB_Column.GetWindowText(str);
	iColumn = _ttoi(str);

	m_CB_Index.GetWindowText(str);
	iIndex = _ttoi(str);

	m_CB_TextValue.GetWindowText(str);

	CCellComboBox * pComboCrtl = dynamic_cast<CCellComboBox *>(m_ListCtrl.GetItemCellCtrl(iRow, iColumn));

	if (pComboCrtl)
		pComboCrtl->InsertItem(iIndex, str);
}

void CConfigurableCtrlDlg::OnBnClickedCbSel()
{
	int iRow, iColumn, iIndex;
	CString str;

	m_CB_Row.GetWindowText(str);
	iRow = _ttoi(str);

	m_CB_Column.GetWindowText(str);
	iColumn = _ttoi(str);

	m_CB_Index.GetWindowText(str);
	iIndex = _ttoi(str);

	CCellComboBox * pComboCrtl = dynamic_cast<CCellComboBox *>(m_ListCtrl.GetItemCellCtrl(iRow, iColumn));

	if (pComboCrtl)
		pComboCrtl->SetSelectedItem(iIndex);
}

void CConfigurableCtrlDlg::OnBnClickedCbRemove()
{
	int iRow, iColumn, iIndex;
	CString str;

	m_CB_Row.GetWindowText(str);
	iRow = _ttoi(str);

	m_CB_Column.GetWindowText(str);
	iColumn = _ttoi(str);

	m_CB_Index.GetWindowText(str);
	iIndex = _ttoi(str);

	CCellComboBox * pComboCrtl = dynamic_cast<CCellComboBox *>(m_ListCtrl.GetItemCellCtrl(iRow, iColumn));

	if (pComboCrtl)
		pComboCrtl->RemoveItem(iIndex);
}

void CConfigurableCtrlDlg::OnBnClickedEvaEvaluate()
{
	int iRow, iColumn;
	CString str;

	m_Eval_Row.GetWindowText(str);
	iRow = _ttoi(str);

	m_Eval_Column.GetWindowText(str);
	iColumn = _ttoi(str);

	CString test = m_ListCtrl.GetItemText(iRow, iColumn); 
	m_Eval_Value.SetWindowText(test);
}

void CConfigurableCtrlDlg::OnBnClickedAlignBut()
{
	int iRow, iColumn;
	CString str;

	m_Align_Row.GetWindowText(str);
	iRow = _ttoi(str);

	m_Align_Column.GetWindowText(str);
	iColumn = _ttoi(str);
	
	m_Align_Align.GetWindowText(str);

	Alignment align = Left;
	BOOL change = FALSE;

	if (!str.Compare(ALIGNMENTTYPE_LEFT))
	{
		align = Left;
		change = TRUE;
	}
	if (!str.Compare(ALIGNMENTTYPE_RIGHT))
	{
		align = Right;
		change = TRUE;
	}
	else if (!str.Compare(ALIGNMENTTYPE_CENTER))
	{
		align = Center;	
		change = TRUE;
	}
	if (change)	
		m_ListCtrl.SetCtrlAlignment(iRow, iColumn, align);
}
