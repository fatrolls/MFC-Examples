// PageTestListTree.cpp : implementation file
//

#include "stdafx.h"
#include "CPPTooltip_demo.h"
#include "PageTestListTree.h"
#include ".\pagetestlisttree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageTestListTree property page

IMPLEMENT_DYNCREATE(CPageTestListTree, CPropertyPage)

CPageTestListTree::CPageTestListTree() : CPropertyPage(CPageTestListTree::IDD)
{
	//{{AFX_DATA_INIT(CPageTestListTree)
	m_place_tip = 0;
	m_balloon = FALSE;
	//}}AFX_DATA_INIT
}

CPageTestListTree::~CPageTestListTree()
{
}

void CPageTestListTree::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageTestListTree)
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Control(pDX, IDC_LIST1, m_list_ctrl);
	DDX_Control(pDX, IDC_LIST2, m_list_box);
	DDX_Control(pDX, IDC_TREE1, m_tree);
	DDX_Radio(pDX, IDC_RADIO1, m_place_tip);
	DDX_Check(pDX, IDC_CHECK1, m_balloon);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPageTestListTree, CPropertyPage)
	//{{AFX_MSG_MAP(CPageTestListTree)
	ON_BN_CLICKED(IDC_RADIO1, OnChangePlacement)
	ON_BN_CLICKED(IDC_RADIO2, OnChangePlacement)
	ON_BN_CLICKED(IDC_CHECK1, OnChangeTypeTitletip)
	//}}AFX_MSG_MAP
	ON_NOTIFY (UDM_TOOLTIP_DISPLAY, NULL, NotifyDisplayTooltip)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageTestListTree message handlers

BOOL CPageTestListTree::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	m_font.CreateFont(-11, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Verdana"));
	m_list_ctrl.SetFont(&m_font);
	m_list_box.SetFont(&m_font);
	m_tree.SetFont(&m_font);
	m_combo.SetFont(&m_font);
	
	m_tooltip.Create(this, FALSE);
	m_tooltip.SetBehaviour(PPTOOLTIP_MULTIPLE_SHOW);
	m_tooltip.SetNotify();
	m_tooltip.AddTool(&m_list_ctrl);
	m_tooltip.AddTool(&m_list_box);
	m_tooltip.AddTool(&m_tree);
	m_tooltip.AddTool(&m_combo);

	//List box
	m_list_box.AddString(_T("1. First Item"));
	m_list_box.AddString(_T("2. Second Item"));
	m_list_box.AddString(_T("3. Third Item"));
	m_list_box.AddString(_T("4. Fourth Item"));
	m_list_box.AddString(_T("5. Fifth Item"));
	m_list_box.AddString(_T("6. Sixth Item"));
	m_list_box.AddString(_T("7. Seventh Item"));
	m_list_box.AddString(_T("8. Eighth Item"));
	m_list_box.AddString(_T("9. Ninth Item"));
	m_list_box.AddString(_T("10. Tenth Item"));
	m_list_box.AddString(_T("11. Last long long item"));

	//List Control
	CRect rect;
	m_list_ctrl.GetClientRect(&rect);
	m_list_ctrl.InsertColumn(0, _T("¹"), LVCFMT_LEFT, 25);
	m_list_ctrl.InsertColumn(1, _T("Description"), LVCFMT_LEFT, rect.Width() - 25);
	m_list_ctrl.InsertItem(0, _T(""));
	m_list_ctrl.SetItem(0, 0, LVIF_TEXT, _T("1"), -1, 0, 0, 0);
	m_list_ctrl.SetItem(0, 1, LVIF_TEXT, _T("First Item"), -1, 0, 0, 0);
	m_list_ctrl.InsertItem(1, _T(""));
	m_list_ctrl.SetItem(1, 0, LVIF_TEXT, _T("2"), -1, 0, 0, 0);
	m_list_ctrl.SetItem(1, 1, LVIF_TEXT, _T("Second Item"), -1, 0, 0, 0);
	m_list_ctrl.InsertItem(2, _T(""));
	m_list_ctrl.SetItem(2, 0, LVIF_TEXT, _T("3"), -1, 0, 0, 0);
	m_list_ctrl.SetItem(2, 1, LVIF_TEXT, _T("Third Item"), -1, 0, 0, 0);
	m_list_ctrl.InsertItem(3, _T(""));
	m_list_ctrl.SetItem(3, 0, LVIF_TEXT, _T("4"), -1, 0, 0, 0);
	m_list_ctrl.SetItem(3, 1, LVIF_TEXT, _T("Fourth Item"), -1, 0, 0, 0);
	m_list_ctrl.InsertItem(4, _T(""));
	m_list_ctrl.SetItem(4, 0, LVIF_TEXT, _T("5"), -1, 0, 0, 0);
	m_list_ctrl.SetItem(4, 1, LVIF_TEXT, _T("Fifth Item"), -1, 0, 0, 0);
	m_list_ctrl.InsertItem(5, _T(""));
	m_list_ctrl.SetItem(5, 0, LVIF_TEXT, _T("6"), -1, 0, 0, 0);
	m_list_ctrl.SetItem(5, 1, LVIF_TEXT, _T("Sixth Item"), -1, 0, 0, 0);
	m_list_ctrl.InsertItem(6, _T(""));
	m_list_ctrl.SetItem(6, 0, LVIF_TEXT, _T("7"), -1, 0, 0, 0);
	m_list_ctrl.SetItem(6, 1, LVIF_TEXT, _T("Seventh Item"), -1, 0, 0, 0);
	m_list_ctrl.InsertItem(7, _T(""));
	m_list_ctrl.SetItem(7, 0, LVIF_TEXT, _T("8"), -1, 0, 0, 0);
	m_list_ctrl.SetItem(7, 1, LVIF_TEXT, _T("Eighth Item"), -1, 0, 0, 0);
	m_list_ctrl.InsertItem(8, _T(""));
	m_list_ctrl.SetItem(8, 0, LVIF_TEXT, _T("9"), -1, 0, 0, 0);
	m_list_ctrl.SetItem(8, 1, LVIF_TEXT, _T("Ninth Item"), -1, 0, 0, 0);

	//Tree Control
	HTREEITEM root = m_tree.InsertItem(_T("Group 0"));
	m_tree.InsertItem(_T("First"), root);
	m_tree.InsertItem(_T("Second"), root);
	m_tree.InsertItem(_T("Third"), root);
	m_tree.InsertItem(_T("Fourth"), root);
	m_tree.InsertItem(_T("Fifth"), root);
	root = m_tree.InsertItem(_T("Group 1"));
	m_tree.InsertItem(_T("Sixth"), root);
	m_tree.InsertItem(_T("Seventh"), root);
	m_tree.InsertItem(_T("Eighth"), root);
	m_tree.InsertItem(_T("Ninth"), root);
	m_tree.InsertItem(_T("Tenth"), root);

	//ComboBox
	m_combo.AddString(_T("First"));
	m_combo.AddString(_T("Second"));
	m_combo.AddString(_T("Third"));
	m_combo.AddString(_T("Fourth"));
	m_combo.AddString(_T("Fifth"));
	m_combo.SetCurSel(0);

	UpdateData(FALSE);
	OnChangeTypeTitletip();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPageTestListTree::PreTranslateMessage(MSG* pMsg) 
{
	m_tooltip.RelayEvent(pMsg);
	
	return CPropertyPage::PreTranslateMessage(pMsg);
}

void CPageTestListTree::NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result)
{
	*result = 0;
	NM_PPTOOLTIP_DISPLAY * pNotify = (NM_PPTOOLTIP_DISPLAY*)pNMHDR;

	if (NULL == pNotify->hwndTool)
	{
		//Order to update a tooltip for a current Tooltip Help
		//He has not a handle of the window
		//If you want change tooltip's parameter than make it's here
	}
	else
	{
		//Order to update a tooltip for a specified window as tooltip's tool

		//Gets a ID of the window if needed
		UINT nID = CWnd::FromHandle(pNotify->hwndTool)->GetDlgCtrlID();

		//Change a tooltip's parameters for a current window (control)
		BOOL bOutside = FALSE;
		CPoint pt = *pNotify->pt;
		CRect rect, rcCtrl;
		if (IDC_LIST1 == nID)
		{
//			pNotify->ti->sTooltip = "List Control";
			m_list_ctrl.GetWindowRect(&rcCtrl);
			pt -= rcCtrl.TopLeft();
			LVHITTESTINFO li;
			li.pt = pt;
			int nItem = m_list_ctrl.SubItemHitTest(&li);
			int nSubItem = li.iSubItem;
			UINT nFlags =   li.flags;
			if (nFlags & LVHT_ONITEM)
			{
				pNotify->ti->sTooltip = m_list_ctrl.GetItemText(li.iItem, li.iSubItem);
				CHeaderCtrl* pHeader = (CHeaderCtrl*)m_list_ctrl.GetDlgItem(0);
				CRect rcHeader;
				Header_GetItemRect(pHeader->m_hWnd, li.iSubItem, &rcHeader);
				rcHeader.OffsetRect(-m_list_ctrl.GetScrollPos(SB_HORZ), 0);
				if (rcHeader.PtInRect(pt))
				{
					//We are over the header
					CString str;
					str.Format(_T("<b>Header</b> - column %d"), li.iSubItem);
					pNotify->ti->sTooltip = str;
					pt = *pNotify->pt;
					pt.x += 5;
					pt.y += 20;
					*pNotify->pt = pt;
				}
				else
				{
					m_list_ctrl.GetSubItemRect(li.iItem, li.iSubItem, LVIR_BOUNDS, rect);
					if (m_place_tip == 0)
					{
						pt = rcCtrl.TopLeft();
						rect.OffsetRect(pt);
						rect.OffsetRect(1, 1);
						pt = rect.TopLeft();
						if (m_balloon)
							pt.y = rect.bottom;
						*pNotify->pt = pt;
					}
					else
					{
						*pNotify->pt = CPoint(rcCtrl.left, rcCtrl.bottom);
					} //if
				}
			} //if
		}
		else if (IDC_LIST2 == nID)
		{
			//This is notification for listbox
			m_list_box.GetWindowRect(&rcCtrl);
			pt -= rcCtrl.TopLeft();
			UINT nItem = m_list_box.ItemFromPoint(pt, bOutside);
			m_list_box.GetText(nItem, pNotify->ti->sTooltip);
			if (m_place_tip == 0)
			{
				pt = rcCtrl.TopLeft();
				m_list_box.GetItemRect(nItem, rect);
				rect.OffsetRect(pt);
				rect.OffsetRect(1, 1);
				pt = rect.TopLeft();
				if (m_balloon)
					pt.y = rect.bottom;
				*pNotify->pt = pt;
			}
			else
			{
				*pNotify->pt = CPoint(rcCtrl.left, rcCtrl.bottom);

			} //if
		}
		else if (IDC_TREE1 == nID)
		{
			m_tree.GetWindowRect(&rcCtrl);
			pt -= rcCtrl.TopLeft();
			TVHITTESTINFO ti;
			ti.pt = pt;
			m_tree.HitTest(&ti);
			UINT nFlags = ti.flags;
			if (nFlags & TVHT_ONITEM)
			{
				pNotify->ti->sTooltip = m_tree.GetItemText(ti.hItem);
				m_tree.GetItemRect(ti.hItem, rect, TRUE);
				if (m_place_tip == 0)
				{
					pt = rcCtrl.TopLeft();
					rect.OffsetRect(pt);
					rect.OffsetRect(1, 1);
					pt = rect.TopLeft();
					if (m_balloon)
						pt.y = rect.bottom;
					*pNotify->pt = pt;
				}
				else
				{
					*pNotify->pt = CPoint(rcCtrl.left, rcCtrl.bottom);
				} //if
			} //if
		}
		else if (IDC_COMBO1 == nID)
		{
			int nItem = m_combo.GetCurSel();
			m_combo.GetWindowText(pNotify->ti->sTooltip);
			pt.x += 5;
			pt.y += 20;
			*pNotify->pt = pt;
		} //if
	} //if
} //End NotifyDisplayTooltip

void CPageTestListTree::OnChangePlacement()
{
	UpdateData();
}

void CPageTestListTree::OnChangeTypeTitletip()
{
	UpdateData();
	m_tooltip.SetDefaultSizes(m_balloon);
	if (m_balloon)
		m_tooltip.SetDirection(PPTOOLTIP_BOTTOMEDGE_LEFT);
	else
		m_tooltip.SetDirection(PPTOOLTIP_TOPEDGE_LEFT);
}

BOOL CPageTestListTree::OnKillActive() 
{
	m_tooltip.HideTooltip();
	
	return CPropertyPage::OnKillActive();
}
