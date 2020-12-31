// ParseDialog.cpp : implementation file
//

#include "stdafx.h"
#include "RegExpression.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParseDialog dialog


CParseDialog::CParseDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CParseDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CParseDialog)
	m_sRule = _T("");
	m_sInfo = _T("");
	//}}AFX_DATA_INIT
}


void CParseDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParseDialog)
	DDX_Control(pDX, ID_PARSE, m_btnParse);
	DDX_Control(pDX, IDC_LIST_PARSING, m_wndListResult);
	DDX_Text(pDX, IDC_EDIT_RULE, m_sRule);
	DDX_Text(pDX, IDC_STATICINFO, m_sInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParseDialog, CDialog)
	//{{AFX_MSG_MAP(CParseDialog)
	ON_BN_CLICKED(ID_PARSE, OnParse)
	ON_EN_CHANGE(IDC_EDIT_RULE, OnChangeEditRule)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParseDialog message handlers

BOOL CParseDialog::OnParse() 
{
	UpdateData(TRUE);
	if (m_sRule.IsEmpty())
	{
		
		return FALSE;
	}
	this->m_wndListResult.DeleteAllItems();
	int nStop=0;
	BOOL bRet=this->m_reg.LoadRule(m_sRule, &nStop);
	if (!bRet)
	{
		ASSERT(nStop<m_sRule.GetLength());
		CEdit* pEdit=(CEdit*) this->GetDlgItem(IDC_EDIT_RULE);
		pEdit->SetSel(nStop,nStop+1);
		int nError=this->m_reg.GetError();
		this->m_reg.TranslateError(nError,m_sInfo);
		pEdit->SetFocus();
		UpdateData(FALSE);
		return FALSE;
	}
	else
		m_sInfo=_T("OK");
	UpdateData(FALSE);
	tRegExpTag* pTag;
	CString sType;
	for (int n=0;n<this->m_reg.GetTagCount();n++)
	{
		pTag=this->m_reg.GetTag(n);
		switch (pTag->nType)
		{
		case  OX_REGEXP_TAG_COMMON_CHAR:
			sType=_T("TAG_COMMON_CHAR");
			break;
		case  OX_REGEXP_TAG_SPECCHAR:
			sType=_T("TAG_SPECCHAR");
			break;		
		case  OX_REGEXP_TAG_COMA:
			sType=_T("TAG_COMA");
			break;
		case  OX_REGEXP_TAG_NOT_DEFINED:
			sType=_T("TAG_NOT_DEFINED");
			break;		
		case  OX_REGEXP_TAG_BEGINING_OF_THE_LINE:
			sType=_T("BEGINING_OF_THE_LINE");
			break;
		case  OX_REGEXP_TAG_END_OF_THE_LINE:
			sType=_T("TAG_END_OF_THE_LINE");
			break;		
		case  OX_REGEXP_TAG_CHAR_ZERO_OR_MORE:
			sType=_T("TAG_CHAR_ZERO_OR_MORE");
			break;
		case  OX_REGEXP_TAG_CHAR_ONE_OR_MORE:
			sType=_T("TAG_CHAR_ONE_OR_MORE");
			break;		
		case  OX_REGEXP_TAG_CHAR_ZERO_OR_ONE:
			sType=_T("TAG_CHAR_ZERO_OR_ONE");
			break;
		case  OX_REGEXP_TAG_CHAR_NOT_NEW_LINE:
			sType=_T("TAG_CHAR_NOT_NEW_LINE");
			break;		
		case  OX_REGEXP_TAG_PATTERN_START:
			sType=_T("TAG_PATTERN_START");
			break;
		case  OX_REGEXP_TAG_PATTERN:
			sType=_T("TAG_PATTERN");
			break;		
		case  OX_REGEXP_TAG_PATTERN_END:
			sType=_T("TAG_PATTERN_END");
			break;
		case  OX_REGEXP_TAG_CHARS_EITHER:
			sType=_T("TAG_CHARS_EITHER");
			break;		
		case  OX_REGEXP_TAG_CHARS_EXACTLY:
			sType=_T("TAG_CHARS_EXACTLY");
			break;
		case  OX_REGEXP_TAG_CHARS_EXACTLY_END:
			sType=_T("TAG_CHARS_EXACTLY_END");
			break;		
		case  OX_REGEXP_TAG_CHARS_AT_LEAST:
			sType=_T("TAG_CHARS_AT_LEAST");
			break;
		case  OX_REGEXP_TAG_CHARS_AT_LEAST_MOST:
			sType=_T("TAG_CHARS_AT_LEAST_MOST");
			break;		
		case  OX_REGEXP_TAG_CHARSET:
			sType=_T("TAG_CHARSET");
			break;
		case  OX_REGEXP_TAG_NON_CHARSET:
			sType=_T("TAG_NON_CHARSET");
			break;		
		case  OX_REGEXP_TAG_WORD_BOUNDARY:
			sType=_T("TAG_WORD_BOUNDARY");
			break;
		case  OX_REGEXP_TAG_NON_WORD_BOUNDARY:
			sType=_T("TAG_NON_WORD_BOUNDARY");
			break;		
		case  OX_REGEXP_TAG_DIGIT:
			sType=_T("TAG_DIGIT");
			break;
		case  OX_REGEXP_TAG_NON_DIGIT:
			sType=_T("TAG_NON_DIGIT");
			break;		
		case  OX_REGEXP_TAG_FORMFEED:
			sType=_T("TAG_FORMFEED");
			break;
		case  OX_REGEXP_TAG_NEWLINE:
			sType=_T("TAG_NEWLINE");
			break;		
		case  OX_REGEXP_TAG_RETURN:
			sType=_T("TAG_RETURN");
			break;
		case  OX_REGEXP_TAG_WHITESPACE:
			sType=_T("TAG_WHITESPACE");
			break;		
		case  OX_REGEXP_TAG_NON_WHITESPACE:
			sType=_T("TAG_NON_WHITESPACE");
			break;
		case  OX_REGEXP_TAG_TAB:
			sType=_T("TAG_TAB");
			break;		
		case  OX_REGEXP_TAG_VERT_TAB:
			sType=_T("TAG_VERT_TAB");
			break;
		case  OX_REGEXP_TAG_ANY_WORD:
			sType=_T("TAG_ANY_WORD");
			break;		
		case  OX_REGEXP_TAG_ANY_NON_WORD:
			sType=_T("TAG_ANY_NON_WORD");
			break;
		case  OX_REGEXP_TAG_REFERENCE_BACK:
			sType=_T("TAG_REFERENCE_BACK");
			break;
		case  OX_REGEXP_TAG_ASCII_CODE:
			sType=_T("TAG_ASCII_CODE");
			break;
		case OX_REGEXP_TAG_CHARSET_BEGIN_LINE:
			sType=_T("TAG_CHARSET_BEGIN_LINE");
			break; 
		case OX_REGEXP_TAG_NON_CHARSET_BEGIN_LINE:
			sType=_T("TAG_NON_CHARSET_BEGIN_LINE");
			break; 
		case OX_REGEXP_TAG_CHARSET_END_LINE:
			sType=_T("TAG_CHARSET_END_LINE");
			break; 
		case OX_REGEXP_TAG_NON_CHARSET_END_LINE:
			sType=_T("TAG_NON_CHARSET_END_LINE");
			break; 
		case OX_REGEXP_TAG_CHARSET_BEGIN_END_LINE:
			sType=_T("TAG_CHARSET_BEGIN_END_LINE");
			break; 
		case OX_REGEXP_TAG_NON_CHARSET_BEGIN_END_LINE:
			sType=_T("TAG_NON_CHARSET_BEGIN_END_LINE");
			break;	
		case OX_REGEXP_TAG_ANY_EXACTLY:
			sType=_T("TAG_ANY_EXACTLY");
			break;
		case OX_REGEXP_TAG_ANY_AT_LEAST:
			sType=_T("TAG_ANY_AT_LEAST");
			break;
		case OX_REGEXP_TAG_ANY_AT_LEAST_MOST:
			sType=_T("TAG_ANY_AT_LEAST_MOST");
			break;
		case OX_REGEXP_TAG_ANY_ZERO_OR_MORE:
			sType=_T("TAG_ANY_ZERO_OR_MORE");
			break;
		case OX_REGEXP_TAG_ANY_ONE_OR_MORE:
			sType=_T("TAG_ANY_ONE_OR_MORE");
			break;
		case OX_REGEXP_TAG_ANY_ZERO_OR_ONE:
			sType=_T("TAG_ANY_ZERO_OR_ONE");
			break;
		default:
			sType=_T("Unknown Tag.");
		}
		this->m_wndListResult.InsertItem(n,(LPCTSTR) sType);
		if (!pTag->sValue.IsEmpty())
			m_wndListResult.SetItemText(n,1,(LPCTSTR) pTag->sValue);
		if (pTag->nType==OX_REGEXP_TAG_CHARS_EXACTLY ||
			pTag->nType==OX_REGEXP_TAG_CHARS_AT_LEAST ||
			pTag->nType==OX_REGEXP_TAG_CHARS_AT_LEAST_MOST ||
			pTag->nType==OX_REGEXP_TAG_CHAR_NOT_NEW_LINE ||
			pTag->nType==OX_REGEXP_TAG_DIGIT ||
			pTag->nType==OX_REGEXP_TAG_NON_DIGIT ||
			pTag->nType==OX_REGEXP_TAG_WHITESPACE ||
			pTag->nType==OX_REGEXP_TAG_NON_WHITESPACE ||
			pTag->nType==OX_REGEXP_TAG_ANY_WORD ||
			pTag->nType==OX_REGEXP_TAG_ANY_NON_WORD)
		{
			TCHAR szBuffer[_MAX_PATH];
			itoa(pTag->nFirstValue,(char*) szBuffer,10);
			m_wndListResult.SetItemText(n,2,(LPCTSTR) szBuffer);
//			if (pTag->nType==OX_REGEXP_TAG_CHARS_AT_LEAST_MOST ||
//				pTag->nType==OX_REGEXP_TAG_ANY_AT_LEAST_MOST)
			{
				itoa(pTag->nSecondValue,(char*) szBuffer,10);
				m_wndListResult.SetItemText(n,3,(LPCTSTR) szBuffer);
			}
		}
	}
	return TRUE;
}

void CParseDialog::OnChangeEditRule() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(TRUE);
	
}

BOOL CParseDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_wndListResult.InsertColumn(0,_T("Type"),LVCFMT_LEFT,200);
	m_wndListResult.InsertColumn(1,_T("Value"),LVCFMT_LEFT,50);
	m_wndListResult.InsertColumn(2,_T("Min"),LVCFMT_LEFT,30);
	m_wndListResult.InsertColumn(3,_T("Max"),LVCFMT_LEFT,30);
	
	CWnd* pWnd=this->GetDlgItem(IDC_EDIT_RULE);
	pWnd->SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CParseDialog::OnOK() 
{
	if (OnParse())	
		CDialog::OnOK();
	else
		CDialog::OnCancel();
}
