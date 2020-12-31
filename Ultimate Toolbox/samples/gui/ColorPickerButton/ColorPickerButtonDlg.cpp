// ColorPickerButtonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ColorPickerButton.h"
#include "ColorPickerButtonDlg.h"

#include "UTSampleAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static void GradientFill(CDC* pDC, CRect rect, COLORREF clr, int nAlignment);
static void PaintRect(CDC* pDC, int x, int y, int w, int h, COLORREF color);

/////////////////////////////////////////////////////////////////////////////
// CColorPickerButtonDlg dialog

ButtonToolTipIDTable CColorPickerButtonDlg::m_arrStandardColorsTooltips[] = 
{
    { RGB(0x00, 0x00, 0x00),    IDS_OX_CLRPICKER_BLACK			},
    { RGB(0x80, 0x00, 0x00),    IDS_OX_CLRPICKER_DARKRED	    },
    { RGB(0x00, 0x80, 0x00),    IDS_OX_CLRPICKER_GREEN		    },
    { RGB(0x80, 0x80, 0x00),    IDS_OX_CLRPICKER_DARKYELLOW     },
    { RGB(0x00, 0x00, 0x80),    IDS_OX_CLRPICKER_DARKBLUE       },
    { RGB(0x80, 0x00, 0x80),    IDS_OX_CLRPICKER_VIOLET			},
    { RGB(0x00, 0x80, 0x80),    IDS_OX_CLRPICKER_TEAL			},
    { RGB(0xC0, 0xC0, 0xC0),    IDS_OX_CLRPICKER_LIGHTGREY      },
    { RGB(0xC0, 0xDC, 0xC0),    IDS_OX_CLRPICKER_LIGHTGREEN		},
    { RGB(0xA6, 0xCA, 0xF1),    IDS_OX_CLRPICKER_LIGHTBLUE		},
    { RGB(0xFF, 0xFB, 0xF0),    IDS_OX_CLRPICKER_LIGHTYELLOW	},
    { RGB(0xA0, 0xA0, 0xA4),    IDS_OX_CLRPICKER_GREY40			},
    { RGB(0x80, 0x80, 0x80),    IDS_OX_CLRPICKER_GREY50         },
    { RGB(0xFF, 0x00, 0x00),    IDS_OX_CLRPICKER_RED            },
    { RGB(0x00, 0xFF, 0x00),    IDS_OX_CLRPICKER_BRIGHTGREEN    },    
    { RGB(0xFF, 0xFF, 0x00),    IDS_OX_CLRPICKER_YELLOW         },    
    { RGB(0x00, 0x00, 0xFF),    IDS_OX_CLRPICKER_BLUE           },
    { RGB(0xFF, 0x00, 0xFF),    IDS_OX_CLRPICKER_PINK		    },
    { RGB(0x00, 0xFF, 0xFF),    IDS_OX_CLRPICKER_TURQUOISE      },
    { RGB(0xFF, 0xFF, 0xFF),    IDS_OX_CLRPICKER_WHITE          }
};

CColorPickerButtonDlg::CColorPickerButtonDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CColorPickerButtonDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CColorPickerButtonDlg)
	m_sTooltip = _T("");
	m_sText = _T("");
	m_nArrowStyle = -1;
	m_nButtonAlignment = -1;
	m_bAutoResize = FALSE;
	m_bDisable = FALSE;
	m_bHyperlook = FALSE;
	m_bImage = FALSE;
	m_bMultiline = FALSE;
	m_bTooltip = FALSE;
	m_bTracklook = FALSE;
	m_nNumColors = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CColorPickerButtonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorPickerButtonDlg)
	DDX_Control(pDX, IDC_COMBO_NUMCOLORS, m_comboNumColors);
	DDX_Control(pDX, IDC_BUTTON_COLOR_PICKER, m_btnColorPicker);
	DDX_Control(pDX, IDC_EDIT_TOOLTIP, m_ctlTooltip);
	DDX_Control(pDX, IDC_BUTTON_SETTOOLTIP, m_btnSetTooltip);
	DDX_Text(pDX, IDC_EDIT_TOOLTIP, m_sTooltip);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_sText);
	DDX_Radio(pDX, IDC_RADIO_ARROWNORMAL, m_nArrowStyle);
	DDX_Radio(pDX, IDC_RADIO_LEFTTOP, m_nButtonAlignment);
	DDX_Check(pDX, IDC_CHECK_AUTORESIZE, m_bAutoResize);
	DDX_Check(pDX, IDC_CHECK_DISABLED, m_bDisable);
	DDX_Check(pDX, IDC_CHECK_HYPERLOOK, m_bHyperlook);
	DDX_Check(pDX, IDC_CHECK_IMAGE, m_bImage);
	DDX_Check(pDX, IDC_CHECK_MULTILINE, m_bMultiline);
	DDX_Check(pDX, IDC_CHECK_TOOLTIP, m_bTooltip);
	DDX_Check(pDX, IDC_CHECK_TRACKLOOK, m_bTracklook);
	DDX_CBIndex(pDX, IDC_COMBO_NUMCOLORS, m_nNumColors);
	//}}AFX_DATA_MAP
	DDX_ColorPicker(pDX, IDC_BUTTON_COLOR_PICKER, m_clr);
}

BEGIN_MESSAGE_MAP(CColorPickerButtonDlg, CDialog)
	//{{AFX_MSG_MAP(CColorPickerButtonDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FONTCOLOR, OnButtonFontcolor)
	ON_BN_CLICKED(IDC_BUTTON_SETTEXT, OnButtonSettext)
	ON_BN_CLICKED(IDC_BUTTON_SETTOOLTIP, OnButtonSettooltip)
	ON_BN_CLICKED(IDC_CHECK_AUTORESIZE, OnCheckAutoresize)
	ON_BN_CLICKED(IDC_CHECK_DISABLED, OnCheckDisabled)
	ON_BN_CLICKED(IDC_CHECK_HYPERLOOK, OnCheckHyperlook)
	ON_BN_CLICKED(IDC_CHECK_IMAGE, OnCheckImage)
	ON_BN_CLICKED(IDC_CHECK_MULTILINE, OnCheckMultiline)
	ON_BN_CLICKED(IDC_CHECK_TOOLTIP, OnCheckTooltip)
	ON_BN_CLICKED(IDC_CHECK_TRACKLOOK, OnCheckTracklook)
	ON_BN_CLICKED(IDC_RADIO_ARROWNONE, OnRadioArrow)
	ON_BN_CLICKED(IDC_RADIO_CENTERBOTTOM, OnRadioButtonAlignment)
	ON_CBN_SELCHANGE(IDC_COMBO_NUMCOLORS, OnSelchangeComboNumcolors)
	ON_BN_CLICKED(IDC_BUTTON_COLOR_PICKER, OnButtonColorPicker)
	ON_BN_CLICKED(IDC_RADIO_ARROWNORMAL, OnRadioArrow)
	ON_BN_CLICKED(IDC_RADIO_ARROWRIGHT, OnRadioArrow)
	ON_BN_CLICKED(IDC_RADIO_CENTERCENTER, OnRadioButtonAlignment)
	ON_BN_CLICKED(IDC_RADIO_CENTERTOP, OnRadioButtonAlignment)
	ON_BN_CLICKED(IDC_RADIO_LEFTBOTTOM, OnRadioButtonAlignment)
	ON_BN_CLICKED(IDC_RADIO_LEFTCENTER, OnRadioButtonAlignment)
	ON_BN_CLICKED(IDC_RADIO_LEFTTOP, OnRadioButtonAlignment)
	ON_BN_CLICKED(IDC_RADIO_RIGHTBOTTOM, OnRadioButtonAlignment)
	ON_BN_CLICKED(IDC_RADIO_RIGHTCENTER, OnRadioButtonAlignment)
	ON_BN_CLICKED(IDC_RADIO_RIGHTTOP, OnRadioButtonAlignment)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorPickerButtonDlg message handlers

BOOL CColorPickerButtonDlg::OnInitDialog()
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
	
	// Set button resources
	m_originalSize = m_btnColorPicker.GetButtonSize();
	m_bAutoResize=TRUE;

	VERIFY(m_btnColorPicker.LoadBitmap(IDB_IMAGE, m_bAutoResize, RGB(255, 0, 255)));
	m_bImage=TRUE;

	m_btnColorPicker.SetToolTip(TRUE);
	m_bTooltip=TRUE;

	m_sText=_T("Pick color");
	m_btnColorPicker.SetText(m_sText);

	m_btnColorPicker.SetVerticalAlignment(BS_VCENTER);
	m_btnColorPicker.SetHorizontalAlignment(BS_LEFT);
	m_nButtonAlignment = 3;

	m_nArrowStyle=0;

	m_bMultiline=(m_btnColorPicker.GetStyle()&BS_MULTILINE)==BS_MULTILINE;

	m_sTooltip = m_btnColorPicker.GetToolTipText();

	m_bDisable=FALSE;
	m_bHyperlook=FALSE;
	m_bTracklook=FALSE;

	m_comboNumColors.AddString(_T("10 clrs, 2 rows, big buttons"));
	m_comboNumColors.AddString(_T("16 clrs, 2 rows"));
	m_comboNumColors.AddString(_T("20 clrs, 4 rows, standard colors"));
	m_comboNumColors.AddString(_T("40 clrs, 4 rows, default option"));
	m_nNumColors=3;
	
	m_clr=RGB(255,255,255);
	m_btnColorPicker.SetDefaultColor(RGB(0,0,128));

//	m_btnColorPicker.SetColorBandHeight(6);

	m_btnColorPicker.SizeToContent();

	UpdateData(FALSE);

	ShowControls();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CColorPickerButtonDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CColorPickerButtonDlg::OnPaint() 
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
		CPaintDC dc(this); // device context for painting

		if(m_rectTop.IsRectEmpty() || m_rectBottom.IsRectEmpty())
		{
			CRect rect;
			GetClientRect(&rect);

			rect.DeflateRect(7,7);
			m_rectTop=rect;
			m_rectBottom=rect;

			m_rectTop.bottom=rect.top+20;
			m_rectBottom.top=rect.bottom-20;
		}

		GradientFill(&dc,m_rectTop,m_clr,0);
		GradientFill(&dc,m_rectBottom,m_clr,2);

		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CColorPickerButtonDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CColorPickerButtonDlg::OnButtonFontcolor() 
{
	// TODO: Add your control notification handler code here
	
	CFont* pTextFont = m_btnColorPicker.GetFont();
	ASSERT(pTextFont != NULL);
	LOGFONT logFont;
	pTextFont->GetLogFont(&logFont);

	CFontDialog fontDlg(&logFont);
	fontDlg.m_cf.rgbColors = m_btnColorPicker.GetTextColor();
	if (fontDlg.DoModal() == IDOK)
	{
		CFont newTextFont;
		// ... CFontDialog::GetCurrentFont() ASSERTs without reason if m_hWnd == NULL,
		//	   so we use m_cf.lpLogFont directly
		VERIFY(newTextFont.CreateFontIndirect(fontDlg.m_cf.lpLogFont));
		// ... SetTextFont() will keep a copy
		m_btnColorPicker.SetTextFont(&newTextFont);
		m_btnColorPicker.SetTextColor(fontDlg.GetColor());

		if(m_bAutoResize)
		{
			m_btnColorPicker.SizeToContent();
		}
		else
		{
			m_btnColorPicker.Invalidate();
		}
	}
}

void CColorPickerButtonDlg::OnButtonSettext() 
{
	// TODO: Add your control notification handler code here
	
	if (!UpdateData(TRUE))
		return;

	m_btnColorPicker.SetText(m_sText);
	if(m_bAutoResize)
	{
		m_btnColorPicker.SizeToContent();
	}
	else
	{
		m_btnColorPicker.Invalidate();
	}
}

void CColorPickerButtonDlg::OnButtonSettooltip() 
{
	// TODO: Add your control notification handler code here
	
	if (!UpdateData(TRUE))
		return;

	m_btnColorPicker.SetToolTipText(m_sTooltip);
}

void CColorPickerButtonDlg::OnCheckAutoresize() 
{
	// TODO: Add your control notification handler code here
	
	if (!UpdateData(TRUE))
		return;

	if (m_bAutoResize)
	{
		m_btnColorPicker.SizeToContent();
	}
	else
	{
		// ... Get old position
		CRect rect;
		m_btnColorPicker.GetWindowRect(rect);
		ScreenToClient(rect);
		// ... Move
		m_btnColorPicker.SetWindowPos(NULL, -1, -1, m_originalSize.cx, m_originalSize.cy,
			SWP_NOMOVE|SWP_NOZORDER|SWP_NOREDRAW|SWP_NOACTIVATE);
		// ... Invalidate old and new position
		InvalidateRect(rect);
		m_btnColorPicker.Invalidate();
	}
}

void CColorPickerButtonDlg::OnCheckDisabled() 
{
	// TODO: Add your control notification handler code here
	
	if (!UpdateData(TRUE))
		return;

	m_btnColorPicker.EnableWindow(!m_bDisable);
}

void CColorPickerButtonDlg::OnCheckHyperlook() 
{
	// TODO: Add your control notification handler code here
	
	if (!UpdateData(TRUE))
		return;

	m_btnColorPicker.SetHyperLook(m_bHyperlook);
}

void CColorPickerButtonDlg::OnCheckImage() 
{
	// TODO: Add your control notification handler code here
	
	if (!UpdateData(TRUE))
		return;

	if(m_bImage)
	{
		VERIFY(m_btnColorPicker.LoadBitmap(IDB_IMAGE, m_bAutoResize, RGB(255, 0, 255)));
	}
	else
	{
		m_btnColorPicker.RemoveImage(m_bAutoResize);
	}

	if(!m_bAutoResize)
	{
		m_btnColorPicker.Invalidate();
	}

}

void CColorPickerButtonDlg::OnCheckMultiline() 
{
	// TODO: Add your control notification handler code here
	
	if (!UpdateData(TRUE))
		return;

	if(m_bMultiline)
		m_btnColorPicker.ModifyStyle(0,BS_MULTILINE);
	else
		m_btnColorPicker.ModifyStyle(BS_MULTILINE,0);

	if (m_bAutoResize)
	{
		m_btnColorPicker.SizeToContent();
	}
	else
	{
		m_btnColorPicker.Invalidate();
	}
}

void CColorPickerButtonDlg::OnCheckTooltip() 
{
	// TODO: Add your control notification handler code here
	
	if (!UpdateData(TRUE))
		return;

	m_btnColorPicker.SetToolTip(m_bTooltip);

	ShowControls();
}

void CColorPickerButtonDlg::OnCheckTracklook() 
{
	// TODO: Add your control notification handler code here
	
	if (!UpdateData(TRUE))
		return;

	m_btnColorPicker.SetTrackLook(m_bTracklook);
}

void CColorPickerButtonDlg::OnRadioArrow() 
{
	// TODO: Add your control notification handler code here
	
	if (!UpdateData(TRUE))
		return;

	switch(m_nArrowStyle)
	{
	case 0:
		{
			m_btnColorPicker.SetStyleEx(OXBB_EX_DROPDOWN);
			break;
		}
	case 1:
		{
			m_btnColorPicker.SetStyleEx(OXBB_EX_DROPDOWN|OXBB_EX_DROPDOWNRIGHT);
			break;
		}
	case 2:
		{
			m_btnColorPicker.SetStyleEx(OXBB_EX_DROPDOWN|OXBB_EX_DROPDOWNNOARROW);
			break;
		}
	}

	if(m_bAutoResize)
	{
		m_btnColorPicker.SizeToContent();
	}
	else
	{
		m_btnColorPicker.Invalidate();
	}
}

void CColorPickerButtonDlg::OnRadioButtonAlignment() 
{
	// TODO: Add your control notification handler code here
	
	if (!UpdateData(TRUE))
		return;

	DWORD nHorizontalAlignment = (DWORD)-1;
	DWORD nVerticalAlignment = (DWORD)-1;

	if ((m_nButtonAlignment == 0) || (m_nButtonAlignment == 1) || (m_nButtonAlignment == 2))
		nVerticalAlignment = BS_TOP;
	if ((m_nButtonAlignment == 3) || (m_nButtonAlignment == 4) || (m_nButtonAlignment == 5))
		nVerticalAlignment = BS_VCENTER;
	if ((m_nButtonAlignment == 6) || (m_nButtonAlignment == 7) || (m_nButtonAlignment == 8))
		nVerticalAlignment = BS_BOTTOM;

	if ((m_nButtonAlignment == 0) || (m_nButtonAlignment == 3) || (m_nButtonAlignment == 6))
		nHorizontalAlignment = BS_LEFT;
	if ((m_nButtonAlignment == 1) || (m_nButtonAlignment == 4) || (m_nButtonAlignment == 7))
		nHorizontalAlignment = BS_CENTER;
	if ((m_nButtonAlignment == 2) || (m_nButtonAlignment == 5) || (m_nButtonAlignment == 8))
		nHorizontalAlignment = BS_RIGHT;

	ASSERT(nHorizontalAlignment != (DWORD)-1);
	ASSERT(nVerticalAlignment != (DWORD)-1);

	DWORD nOldVerticalAlignment=m_btnColorPicker.GetVerticalAlignment();

	m_btnColorPicker.SetVerticalAlignment(nVerticalAlignment);
	m_btnColorPicker.SetHorizontalAlignment(nHorizontalAlignment);

	if(m_bAutoResize && (nOldVerticalAlignment==BS_VCENTER || 
		nVerticalAlignment==BS_VCENTER))
	{
		m_btnColorPicker.SizeToContent();
	}
}

void CColorPickerButtonDlg::OnSelchangeComboNumcolors() 
{
	// TODO: Add your control notification handler code here
	
	if (!UpdateData(TRUE))
		return;

	// get Color Picker
	COXColorPickerCtrl* pColorPickerCtrl=m_btnColorPicker.GetColorPickerCtrl();

	// clear buttons color and tooltips arrays
	pColorPickerCtrl->SetButtonDataTable(NULL,0);
	pColorPickerCtrl->SetToolTipTextTable(NULL,0);

	// set default style
	pColorPickerCtrl->SetPopupBarStyle(0);

	// set default & custom buttons text
	pColorPickerCtrl->SetDefaultButtonText(CString(_T("Default")));
	pColorPickerCtrl->SetCustomButtonText(CString(_T("Custom...")));

	// set default button size
	pColorPickerCtrl->SetButtonSize(CSize(18,18));

	switch(m_nNumColors)
	{
	case 0:
		{
			pColorPickerCtrl->SetNumButtons(10);
			pColorPickerCtrl->SetNumRows(2);
			pColorPickerCtrl->SetButtonSize(CSize(30,30));
			break;
		}
	case 1:
		{
			pColorPickerCtrl->SetNumButtons(16);
			pColorPickerCtrl->SetNumRows(2);

			pColorPickerCtrl->SetPopupBarStyle(POPUPBAR_NODEFAULT);
			pColorPickerCtrl->SetCustomButtonText(_T("More Colors..."));

			break;
		}
	case 2:
		{
			pColorPickerCtrl->SetNumButtons(20);
			pColorPickerCtrl->SetNumRows(4);

			pColorPickerCtrl->SetPopupBarStyle(POPUPBAR_NODEFAULT|POPUPBAR_NOCUSTOM);

			pColorPickerCtrl->PopulateColorTable();
			pColorPickerCtrl->SetToolTipTextIDTable(m_arrStandardColorsTooltips,20);

			break;
		}
	case 3:
		{
			pColorPickerCtrl->SetNumButtons(40);
			pColorPickerCtrl->SetNumRows(4);
			break;
		}
	}

}

void CColorPickerButtonDlg::OnButtonColorPicker() 
{
	// TODO: Add your control notification handler code here

	COLORREF oldColor=m_clr;

	if (!UpdateData(TRUE))
		return;

	if(m_clr!=oldColor)
	{
		InvalidateRect(m_rectTop);
		InvalidateRect(m_rectBottom);
	}
}

void CColorPickerButtonDlg::ShowControls() 
{
	UpdateData(TRUE);

	m_ctlTooltip.EnableWindow(m_bTooltip);
	m_btnSetTooltip.EnableWindow(m_bTooltip);

	UpdateData(FALSE);
}


static void GradientFill(CDC* pDC, CRect rect, COLORREF clr, int nAlignment)
{
	int cxCap=rect.Width();
	int cyCap=rect.Height();

	// red, green and blue color vals
	int red=GetRValue(clr);				
	int green=GetGValue(clr);				
	int blue=GetBValue(clr);		
	
	int nCurBlock;
	// width of area to shade and width squared
	int nWidth, nWidth_x_2;				
	// width of one shade band
	int nDelta;	
	UINT nNumberShade=64;

	switch(nAlignment)
	{
	case 0:
		{
			nWidth=cxCap;
			nWidth_x_2=cxCap*cxCap;
			nDelta=__max(nWidth/nNumberShade,1);
			nCurBlock=cxCap-nDelta;

			while(nCurBlock>0) 
			{
				// paint bands right to left
				int nRest_x_2=(nWidth-nCurBlock)*(nWidth-nCurBlock);
				PaintRect(pDC, nCurBlock+rect.left, rect.top, nDelta, cyCap,	
					RGB(red-(red*nRest_x_2)/nWidth_x_2, 
					green-(green*nRest_x_2)/nWidth_x_2, 
					blue-(blue*nRest_x_2)/nWidth_x_2));
				// next band
				nCurBlock-=nDelta;							
			}
			// whatever's left ==> black
			PaintRect(pDC,rect.left,rect.top,nCurBlock+nDelta,cyCap,RGB(0,0,0));  

			break;
		}
	case 1:
		{
			nCurBlock=cxCap/2;
			nWidth=cxCap/2;
			nWidth_x_2=cxCap*cxCap/4;
			nDelta=__max(nWidth/(2*nNumberShade),1);

			while(nCurBlock>0) 
			{
				// paint bands right to left
				int nRest_x_2=(nWidth-nCurBlock)*(nWidth-nCurBlock);
				PaintRect(pDC, nWidth+nCurBlock+rect.left, rect.top, nDelta, cyCap,	
					RGB(red-(red*nRest_x_2)/nWidth_x_2, 
					green-(green*nRest_x_2)/nWidth_x_2, 
					blue-(blue*nRest_x_2)/nWidth_x_2));
				// next band
				nCurBlock-=nDelta;							
			}
			// whatever's left ==> black
			PaintRect(pDC,nWidth+rect.left, rect.top,nCurBlock+nDelta,cyCap,RGB(0,0,0));  

			nCurBlock=0;
			while(nCurBlock<=nWidth) 
			{
				// paint bands left to right
				int nRest_x_2=nCurBlock*nCurBlock;
				PaintRect(pDC, nCurBlock+rect.left, rect.top, nDelta, cyCap,	
					RGB(red-(red*nRest_x_2)/nWidth_x_2, 
					green-(green*nRest_x_2)/nWidth_x_2, 
					blue-(blue*nRest_x_2)/nWidth_x_2));
				// next band
				nCurBlock+=nDelta;							
			}
			// whatever's left ==> black
			PaintRect(pDC,nCurBlock-nDelta+rect.left, rect.top,
				nWidth-nCurBlock+nDelta, cyCap,RGB(0,0,0));  

			break;
		}
	case 2:
		{
			nCurBlock=0;
			nWidth=cxCap;
			nWidth_x_2=cxCap*cxCap;
			nDelta=__max(nWidth/nNumberShade,1);

			while(nCurBlock<nWidth) 
			{
				// paint bands left to right
				int nRest_x_2=nCurBlock*nCurBlock;
				PaintRect(pDC, nCurBlock+rect.left, rect.top, nDelta, cyCap,	
					RGB(red-(red*nRest_x_2)/nWidth_x_2, 
					green-(green*nRest_x_2)/nWidth_x_2, 
					blue-(blue*nRest_x_2)/nWidth_x_2));
				// next band
				nCurBlock+=nDelta;							
			}
			// whatever's left ==> black
			PaintRect(pDC,nCurBlock-nDelta+rect.left, rect.top,
				nWidth-nCurBlock+nDelta-1, cyCap,RGB(0,0,0));  

			break;
		}
	}
}


//////////////////
// Helper to paint rectangle with a color.
//
static void PaintRect(CDC* pDC, int x, int y, int w, int h, COLORREF color)
{
	CBrush brush(color);
	CBrush* pOldBrush = pDC->SelectObject(&brush);
	pDC->PatBlt(x, y, w, h, PATCOPY);
	pDC->SelectObject(pOldBrush);
}




