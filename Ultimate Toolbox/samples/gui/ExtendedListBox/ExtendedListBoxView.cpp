// ExtendedListBoxView.cpp : implementation of the CExtendedListBoxView class
//

#include "stdafx.h"
#include "ExtendedListBox.h"

#include "ExtendedListBoxDoc.h"
#include "ExtendedListBoxView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExtendedListBoxView

IMPLEMENT_DYNCREATE(CExtendedListBoxView, CFormView)

BEGIN_MESSAGE_MAP(CExtendedListBoxView, CFormView)
	//{{AFX_MSG_MAP(CExtendedListBoxView)
	ON_LBN_SELCHANGE(IDC_LISTBOX_EX, OnSelchangeListboxEx)
	ON_BN_CLICKED(IDC_BUTTON_ITEM_BK_COLOR, OnButtonItemBkColor)
	ON_BN_CLICKED(IDC_BUTTON_ITEM_FONT, OnButtonItemFont)
	ON_BN_CLICKED(IDC_BUTTON_LISTBOX_BK_COLOR, OnButtonListboxBkColor)
	ON_BN_CLICKED(IDC_CHECK_HIGHLIGHT_ONLY_TEXT, OnCheckHighlightOnlyText)
	ON_EN_CHANGE(IDC_EDIT_INDENT, OnChangeEditIndent)
	ON_EN_CHANGE(IDC_EDIT_FONT_HEIGHT, OnChangeEditFontHeight)
	ON_EN_CHANGE(IDC_EDIT_MAXNUM_MRU_ITEMS, OnChangeEditMaxnumMruItems)
	ON_CBN_SELCHANGE(IDC_FONT_COMBO, OnSelchangeFontCombo)
	ON_LBN_SELCHANGE(IDC_FONT_LISTBOX, OnSelchangeFontListbox)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExtendedListBoxView construction/destruction

CExtendedListBoxView::CExtendedListBoxView()
	: CFormView(CExtendedListBoxView::IDD)
{
	//{{AFX_DATA_INIT(CExtendedListBoxView)
	m_bHighlightOnlyText = FALSE;
	m_nIndent = 0;
	m_nFontHeight = 0;
	m_nMaxNumMRUItems = 0;
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CExtendedListBoxView::~CExtendedListBoxView()
{
	for(int nIndex=0; nIndex<m_arrFonts.GetSize(); nIndex++)
	{
		CFont* pFont=m_arrFonts[nIndex];
		ASSERT(pFont!=NULL);
		delete pFont;
	}
}

void CExtendedListBoxView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExtendedListBoxView)
	DDX_Control(pDX, IDC_SPIN_FONT_MAXNUM_MRU_ITEMS, m_spinMaxNumMRUItems);
	DDX_Control(pDX, IDC_SPIN_FONT_HEIGHT, m_spinFontHeight);
	DDX_Control(pDX, IDC_FONT_LISTBOX, m_fontListBox);
	DDX_Control(pDX, IDC_FONT_COMBO, m_fontComboBox);
	DDX_Control(pDX, IDC_SEPARATOR_FONT_LIST_AND_COMBO, m_sepFontListAndCombo);
	DDX_Control(pDX, IDC_SPIN_INDENT, m_spinIndent);
	DDX_Control(pDX, IDC_SEPARATOR_LISTBOX, m_sepListBox);
	DDX_Control(pDX, IDC_SEPARATOR_ITEM_PROPERTIES, m_sepItemProperties);
	DDX_Control(pDX, IDC_LISTBOX_EX, m_listBoxEx);
	DDX_Control(pDX, IDC_BUTTON_LISTBOX_BK_COLOR, m_btnListBoxBkColor);
	DDX_Control(pDX, IDC_BUTTON_ITEM_FONT, m_btnItemFont);
	DDX_Control(pDX, IDC_BUTTON_ITEM_BK_COLOR, m_btnItemBkColor);
	DDX_Check(pDX, IDC_CHECK_HIGHLIGHT_ONLY_TEXT, m_bHighlightOnlyText);
	DDX_Text(pDX, IDC_EDIT_INDENT, m_nIndent);
	DDV_MinMaxUInt(pDX, m_nIndent, 0, 100);
	DDX_Text(pDX, IDC_EDIT_FONT_HEIGHT, m_nFontHeight);
	DDV_MinMaxUInt(pDX, m_nFontHeight, 1, 100);
	DDX_Text(pDX, IDC_EDIT_MAXNUM_MRU_ITEMS, m_nMaxNumMRUItems);
	DDV_MinMaxUInt(pDX, m_nMaxNumMRUItems, 0, 50);
	//}}AFX_DATA_MAP
	DDX_ColorPicker(pDX, IDC_BUTTON_LISTBOX_BK_COLOR, m_clrListBoxBack);
	DDX_ColorPicker(pDX, IDC_BUTTON_ITEM_BK_COLOR, m_clrItemBack);
	DDX_FontPickerFont(pDX, IDC_BUTTON_ITEM_FONT, &m_fontItem);
	DDX_FontPickerColor(pDX, IDC_BUTTON_ITEM_FONT, m_clrItemText);
}

BOOL CExtendedListBoxView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CExtendedListBoxView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_bHighlightOnlyText=m_listBoxEx.GetHighlightOnlyText();
	m_clrListBoxBack=m_listBoxEx.GetBkColor();
	m_nFontHeight=m_fontListBox.GetFontHeight();
	m_nMaxNumMRUItems=((COXFontListBox*)m_fontComboBox.GetListBoxCtrl())->
		GetMaxItemsBeforeSeparator();

	UpdateData(FALSE);

	m_btnItemBkColor.SetToolTip(TRUE);
	m_btnItemFont.SetToolTip(TRUE);
	m_btnListBoxBkColor.SetToolTip(TRUE);

	m_btnItemFont.SetBuddy(IDC_STATIC_ITEM_FONT);

	// spin controls
	m_spinIndent.SetRange(0,100);
	m_spinFontHeight.SetRange(1,100);
	m_spinMaxNumMRUItems.SetRange(0,50);


	m_fontComboBox.SetSaveRestoreMRUState(TRUE);


	// populate extended list box
	//

	// set image list to be displayed
	static CImageList imageList;
	imageList.Create(IDB_IL_LISTBOXEX,32,0,RGB(192,192,192));
	m_listBoxEx.SetImageList(&imageList);

	// fonts for items
	static CFont g_fontHeader;
	VERIFY(g_fontHeader.CreatePointFont(200,_T("Arial")));
	static CFont g_fontFamily;
	VERIFY(g_fontFamily.CreatePointFont(160,_T("Times New Roman")));

	// hierarchial items
	AddSimpsonsItem(_T("Simpsons"),0,0,RGB(0,0,0),
		_T("Reside in Springfield, USA"),&g_fontHeader);
	AddSimpsonsItem(_T("Homer"),1,20,RGB(0,0,255),_T("Still has hair"),&g_fontFamily);
	AddSimpsonsItem(_T("Marge"),2,20,RGB(0,0,255),_T(""),&g_fontFamily);
	AddSimpsonsItem(_T("Bart"),3,40,RGB(0,128,0),_T(""),&g_fontFamily);
	AddSimpsonsItem(_T("Lisa"),4,40,RGB(0,128,0),_T(""),&g_fontFamily);
	AddSimpsonsItem(_T("Maggie"),5,40,RGB(0,128,0),_T(""),&g_fontFamily);
	AddSimpsonsItem(_T("GrandPa"),6,20,RGB(128,128,128),_T(""),&g_fontFamily);

	for(int nIndex=0; nIndex<m_listBoxEx.GetCount(); nIndex++)
	{
		CFont* pFont=new CFont;
		m_arrFonts.Add(pFont);
	}

	m_listBoxEx.SetCurSel(0);
	OnSelchangeListboxEx();

	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
}

/////////////////////////////////////////////////////////////////////////////
// CExtendedListBoxView printing

BOOL CExtendedListBoxView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CExtendedListBoxView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CExtendedListBoxView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CExtendedListBoxView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
	UNREFERENCED_PARAMETER(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CExtendedListBoxView diagnostics

#ifdef _DEBUG
void CExtendedListBoxView::AssertValid() const
{
	CFormView::AssertValid();
}

void CExtendedListBoxView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CExtendedListBoxDoc* CExtendedListBoxView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExtendedListBoxDoc)));
	return (CExtendedListBoxDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExtendedListBoxView message handlers

int CExtendedListBoxView::AddSimpsonsItem(LPCTSTR lpszText, 
										  int nImageIndex, 
										  int nIndent,
										  COLORREF clrText, 
										  LPCTSTR lpszTooltipText,
										  CFont* pFont)
{
	int nIndex=m_listBoxEx.AddString(lpszText);
	ASSERT(nIndex!=LB_ERR);
	m_listBoxEx.SetItemImageIndex(nIndex,nImageIndex);
	m_listBoxEx.SetItemIndent(nIndex,nIndent);
	m_listBoxEx.SetItemTextColor(nIndex,clrText);
	m_listBoxEx.SetItemTooltipText(nIndex,lpszTooltipText);
	m_listBoxEx.SetItemFont(nIndex,pFont);
	return nIndex;
}

void CExtendedListBoxView::OnSelchangeListboxEx() 
{
	// TODO: Add your control notification handler code here
	if(!UpdateData(TRUE))
		return;

	int nIndex=m_listBoxEx.GetCurSel();
	ASSERT(nIndex!=LB_ERR);
	m_nIndent=m_listBoxEx.GetItemIndent(nIndex);;
	m_clrItemBack=m_listBoxEx.GetItemBkColor(nIndex);
	m_clrItemText=m_listBoxEx.GetItemTextColor(nIndex);
	CFont* pFont=m_listBoxEx.GetItemFont(nIndex);
	ASSERT(pFont!=NULL);
	LOGFONT lf;
	VERIFY(pFont->GetLogFont(&lf));
	if((HFONT)m_fontItem!=NULL)
		VERIFY(m_fontItem.DeleteObject());
	VERIFY(m_fontItem.CreateFontIndirect(&lf));

	UpdateData(FALSE);
}

void CExtendedListBoxView::OnButtonItemBkColor() 
{
	// TODO: Add your control notification handler code here
	
	if(!UpdateData(TRUE))
		return;

	int nIndex=m_listBoxEx.GetCurSel();
	VERIFY(m_listBoxEx.SetItemBkColor(nIndex,m_clrItemBack));
}

void CExtendedListBoxView::OnButtonItemFont() 
{
	// TODO: Add your control notification handler code here
	
	if(!UpdateData(TRUE))
		return;

	int nIndex=m_listBoxEx.GetCurSel();

	CFont* pFont=m_arrFonts[nIndex];
	ASSERT(pFont!=NULL);
	LOGFONT lf;
	VERIFY(m_fontItem.GetLogFont(&lf));
	if(pFont->m_hObject!=NULL)
		VERIFY(pFont->DeleteObject());
	VERIFY(pFont->CreateFontIndirect(&lf));

	VERIFY(m_listBoxEx.SetItemFont(nIndex,pFont));
	VERIFY(m_listBoxEx.SetItemTextColor(nIndex,m_clrItemText));
}

void CExtendedListBoxView::OnButtonListboxBkColor() 
{
	// TODO: Add your control notification handler code here
	
	if(!UpdateData(TRUE))
		return;

	m_listBoxEx.SetBkColor(m_clrListBoxBack);
	VERIFY(m_listBoxEx.SetItemBkColor(-1,m_clrListBoxBack));
}

void CExtendedListBoxView::OnCheckHighlightOnlyText() 
{
	// TODO: Add your control notification handler code here
	
	if(!UpdateData(TRUE))
		return;

	m_listBoxEx.SetHighlightOnlyText(m_bHighlightOnlyText);
}

void CExtendedListBoxView::OnChangeEditIndent() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if(!::IsWindow(m_listBoxEx.GetSafeHwnd()))
		return;
	
	if(!UpdateData(TRUE))
		return;

	int nIndex=m_listBoxEx.GetCurSel();
	VERIFY(m_listBoxEx.SetItemIndent(nIndex,m_nIndent));
}

void CExtendedListBoxView::OnChangeEditFontHeight() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
	if(!::IsWindow(m_listBoxEx.GetSafeHwnd()))
		return;
	
	if(!UpdateData(TRUE))
		return;

	m_fontListBox.SetFontHeight(m_nFontHeight);
}

void CExtendedListBoxView::OnChangeEditMaxnumMruItems() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
	if(!::IsWindow(m_listBoxEx.GetSafeHwnd()))
		return;
	
	if(!UpdateData(TRUE))
		return;

	((COXFontListBox*)m_fontComboBox.GetListBoxCtrl())->
		SetMaxItemsBeforeSeparator(m_nMaxNumMRUItems);
}

void CExtendedListBoxView::OnSelchangeFontCombo() 
{
	// TODO: Add your control notification handler code here
	CFont* pFont=m_fontComboBox.GetSelectedFont();
	if(pFont!=NULL)
	{
		m_fontListBox.SelectFont(pFont);
	}
}

void CExtendedListBoxView::OnSelchangeFontListbox() 
{
	// TODO: Add your control notification handler code here
	CFont* pFont=m_fontListBox.GetItemFont(m_fontListBox.GetCurSel());
	if(pFont!=NULL)
	{
		m_fontComboBox.SelectFont(pFont);
	}
}
