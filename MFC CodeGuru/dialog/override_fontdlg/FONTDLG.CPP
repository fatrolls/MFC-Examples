#include "..\main\stdafx.h"
// MyFontDlg.cpp : implementation file
//

#include <math.h>
#include <wtypes.h>
#include <afxdlgs.h>
#include <dlgs.h>
#include <..\src\afximpl.h>

#include <aflform.h>
#include "..\..\help\context.h"
#include "..\main\entities.h"
#include "fontdlg.h"
#include "..\..\res\entities\resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ERROR_MESSAGE "MY_ERROR_MESSAGE"
static const UINT nMess=RegisterWindowMessage(ERROR_MESSAGE);


static void PASCAL DDV_Real(CDataExchange *pDX,const CString &str,BOOL use_string,BOOL CanPopup)
{
	if (pDX->m_bSaveAndValidate)
	{
		double fl;
		if (use_string && (A_FLFORMC::Str2Float (str, fl) < 0 || fl<1e-7))
		{
			if (CanPopup)
				pDX->m_pDlgWnd->PostMessage(nMess);
			pDX->Fail();
		}
	}
}
		


/////////////////////////////////////////////////////////////////////////////
// CFontDlg

IMPLEMENT_DYNAMIC(CFontDlg, CFontDialog)

CFontDlg::CFontDlg(double height, LPLOGFONT lplfInitial) : 
	CFontDialog (lplfInitial,CF_EFFECTS | CF_SCREENFONTS | CF_SHOWHELP | CF_SCALABLEONLY,
		NULL, NULL)
{
	m_bHeightUndefined = height < 0.0;
        m_Height = fabs (height);

	m_szHeight = A_FLFORMC::Float2Str(m_Height);

	m_cf.Flags|=CF_ENABLETEMPLATE;
	m_cf.lpTemplateName=MAKEINTRESOURCE(TEXTSTYLE_FONT_DLG);
	m_cf.hInstance=HResources;

	if (lplfInitial)
	{
		m_MyLogfont=*lplfInitial;
		m_bLogfontInitialized=TRUE;
		m_szSpecFont=lplfInitial->lfFaceName;
	}
	else
	{
		m_bLogfontInitialized;
		m_szSpecFont="";
	}

	m_bFontChanged=FALSE;
	m_bActive=TRUE;
}


double CFontDlg::GetHeight(void)
{
	double height;

	if (A_FLFORMC::Str2Float (m_szHeight, height) < 0 || height < 1e-7)
        height = m_Height;

	if (m_bHeightUndefined)
        height = - height;

	return (height);
}

void CFontDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, TEXTSTYLE_FONT_HEIGHT_CBX, m_bHeightUndefined);
	DDX_Text(pDX, TEXTSTYLE_FONT_HEIGHT_EBX, m_szHeight);
	DDV_Real(pDX, m_szHeight, !m_bHeightUndefined, m_bActive);
}


BEGIN_MESSAGE_MAP(CFontDlg, CFontDialog)
	//{{AFX_MSG_MAP(CFontDlg)
	ON_BN_CLICKED(TEXTSTYLE_FONT_HEIGHT_CBX, OnCheckHeightundefined)
	ON_EN_KILLFOCUS(TEXTSTYLE_FONT_HEIGHT_EBX, OnKillfocusEditheight)
	ON_COMMAND(ID_HELP, OnHelpBut)
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(cmb1, OnSelchangeFontCombo)
	ON_CBN_SELCHANGE(cmb2, OnSelchangeFontstyleCombo)
	ON_CBN_SELCHANGE(cmb5, OnSelchangeScriptCombo)
	ON_WM_ACTIVATEAPP()
	ON_WM_QUERYENDSESSION()
	ON_REGISTERED_MESSAGE(nMess, OnErrMessage)
END_MESSAGE_MAP()


BOOL CFontDlg::OnInitDialog() 
{
	CFontDialog::OnInitDialog();

	CWnd *cwnd;
	cwnd=GetDlgItem(stc3);
	ASSERT(cwnd!=NULL);
	cwnd->ShowWindow(SW_HIDE);

	cwnd=GetDlgItem(cmb3);
	ASSERT(cwnd!=NULL);
	cwnd->ShowWindow(SW_HIDE);

	cwnd=GetDlgItem(stc4);
	ASSERT(cwnd!=NULL);
	cwnd->ShowWindow(SW_HIDE);

	cwnd=GetDlgItem(cmb4);
	ASSERT(cwnd!=NULL);
	cwnd->ShowWindow(SW_HIDE);

	if (m_bHeightUndefined)
	{
		cwnd=GetDlgItem(TEXTSTYLE_FONT_HEIGHT_EBX);
		ASSERT(cwnd!=NULL);
		cwnd->EnableWindow(FALSE);
	}

	if (afxData.bWin31)
	{
		cwnd=GetDlgItem(cmb5);
		ASSERT(cwnd!=NULL);
		cwnd->EnableWindow(FALSE);
	}

	CComboBox *comboFont=(CComboBox *)GetDlgItem(cmb1);
	ASSERT(comboFont!=NULL);

	m_bFontAdded=FALSE;

	if (!m_szSpecFont.IsEmpty())
	{
		int i=comboFont->FindStringExact(-1,m_szSpecFont);
		if (i==CB_ERR)
		{		
			m_bFontAdded=TRUE;
			i=comboFont->AddString(m_szSpecFont);
			int j=comboFont->GetCurSel();
			if (j==CB_ERR)
			{
				if (m_szSpecFont.Compare(m_lf.lfFaceName)==0)
				{
					comboFont->SetCurSel(i);
				}
			}

			UpdateCombos();
		}
	}
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFontDlg::OnCheckHeightundefined() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CWnd *cwnd=GetDlgItem(TEXTSTYLE_FONT_HEIGHT_EBX);
	ASSERT(cwnd!=NULL);
	cwnd->EnableWindow(!m_bHeightUndefined);
}

void CFontDlg::OnKillfocusEditheight() 
{
	// TODO: Add your control notification handler code here
	CWnd *cwnd=GetFocus();
	if (cwnd!=GetDlgItem(IDCANCEL) && cwnd!=GetDlgItem(pshHelp) && m_bActive)
		UpdateData(TRUE);
	
}

void CFontDlg::OnHelpBut(void)
{
	AfxGetApp()->WinHelp (HLPID_TEXTSTYLE_FONT, HELP_CONTEXT);
}

void CFontDlg::OnSelchangeFontCombo()
{
	m_bFontChanged=TRUE;
	UpdateCombos();
	Default();
}

void CFontDlg::UpdateCombos(void)
{
	CComboBox *comboFont=(CComboBox *)GetDlgItem(cmb1);
	ASSERT(comboFont!=NULL);
	int i=comboFont->GetCurSel();
	BOOL enable=TRUE;
	
	if (i!=CB_ERR)
	{
		CString str;
		comboFont->GetLBText(i,str);
		if (str==m_szSpecFont && m_bFontAdded)
			enable=FALSE;
	}

	CWnd *cwnd;
	cwnd=GetDlgItem(cmb2);
	ASSERT(cwnd!=NULL);
	cwnd->EnableWindow(enable);

	if (!afxData.bWin31)
	{
		cwnd=GetDlgItem(cmb5);
		ASSERT(cwnd!=NULL);
		cwnd->EnableWindow(enable);
	}
}

void CFontDlg::OnActivateApp(BOOL act,HTASK)
{
	if (act)
		UpdateData(TRUE);
	m_bActive=act;
	Default();
}

BOOL CFontDlg::OnQueryEndSession(void)
{
	m_bActive=FALSE;
	return (BOOL)Default();
}

LONG CFontDlg::OnErrMessage(UINT,LONG)
{
	BOOL save=m_bActive;
	m_bActive=FALSE;
	AfxMessageBox("Height must be positive number!");
	m_bActive=save;
	return 0;
}

void CFontDlg::OnSelchangeFontstyleCombo(void)
{
	m_bFontChanged=TRUE;
	Default();
}

void CFontDlg::OnSelchangeScriptCombo(void)
{
	m_bFontChanged=TRUE;
	Default();
}

void CFontDlg::GetCurrentFont(LPLOGFONT lplf)
{
//	ASSERT(m_hWnd != NULL);	// why on Earth should it be here???
	ASSERT(lplf != NULL);

	if (m_bLogfontInitialized && !m_bFontChanged)
	{
		*lplf=m_MyLogfont;
		lplf->lfUnderline=m_lf.lfUnderline;
		lplf->lfStrikeOut=m_lf.lfStrikeOut;
	}
	else if (m_hWnd != NULL)
		SendMessage(WM_CHOOSEFONT_GETLOGFONT, 0, (DWORD)(LPVOID)lplf);
	else
		*lplf = m_lf;
}
