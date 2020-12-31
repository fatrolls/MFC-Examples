/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 by Juraj Rojko jrojko@twist.cz
// All rights reserved
//
// VBScriptEditorView.cpp : implementation of the CVBScriptEditorView class
//

#include "stdafx.h"
#include "VBScriptEditor.h"

#include "VBScriptEditorDoc.h"
#include "VBScriptEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVBScriptEditorView

IMPLEMENT_DYNCREATE(CVBScriptEditorView, CRichEditView)

BEGIN_MESSAGE_MAP(CVBScriptEditorView, CRichEditView)
	//{{AFX_MSG_MAP(CVBScriptEditorView)
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRichEditView::OnFilePrintPreview)

	ON_NOTIFY_REFLECT(EN_PROTECTED, OnProtected)
	ON_MESSAGE(WM_SETTEXT, OnSetText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVBScriptEditorView construction/destruction

CVBScriptEditorView::CVBScriptEditorView()
{
	m_chComment = 1;
	m_bCaseSensitive = FALSE;
	m_bChangeCase = TRUE;

	SetStringQuotes(_T("\""));

	SetKeywordColor(RGB(0,0,255), FALSE);
	SetConstantColor(RGB(0,0,0), TRUE);
	SetCommentColor(RGB(0,128,0), FALSE);
	SetNumberColor(RGB(255,0,255), FALSE);
	SetStringColor(RGB(255,0,255), FALSE);

	m_bInForcedChange = FALSE;
	m_changeType = ctUndo;
	m_crOldSel.cpMin = m_crOldSel.cpMax = 0;
}

CVBScriptEditorView::~CVBScriptEditorView()
{
}

BOOL CVBScriptEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}


void CVBScriptEditorView::OnInitialUpdate()
{
	// Set the printing margins (720 twips = 1/2 inch).
	SetMargins(CRect(720, 720, 720, 720));

	CRichEditView::OnInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
// CVBScriptEditorView printing

BOOL CVBScriptEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}


/////////////////////////////////////////////////////////////////////////////
// CVBScriptEditorView diagnostics

#ifdef _DEBUG
void CVBScriptEditorView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CVBScriptEditorView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CVBScriptEditorDoc* CVBScriptEditorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVBScriptEditorDoc)));
	return (CVBScriptEditorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVBScriptEditorView message handlers
void CVBScriptEditorView::Initialize() 
{
	PARAFORMAT pf;
	pf.cbSize = sizeof(PARAFORMAT);
	pf.dwMask = PFM_TABSTOPS ;
	pf.cTabCount = MAX_TAB_STOPS;
	for( int itab = 0 ; itab < pf.cTabCount  ; itab++ )
		pf.rgxTabs[itab] = (itab + 1) * 1440/5 ;

	SetParaFormat( pf );

	CHARFORMAT cfDefault;
	cfDefault.cbSize = sizeof(cfDefault);
	cfDefault.dwEffects = CFE_PROTECTED; 
	cfDefault.dwMask = CFM_BOLD | CFM_FACE | CFM_SIZE | CFM_CHARSET | CFM_PROTECTED;
	cfDefault.yHeight = 200;
	cfDefault.bCharSet = 0xEE; 
	strcpy(cfDefault.szFaceName, _T("Courier New")); 

	GetRichEditCtrl().SetDefaultCharFormat(cfDefault);
	
	GetRichEditCtrl().SetEventMask(ENM_CHANGE | ENM_SELCHANGE | ENM_PROTECTED);
}

void CVBScriptEditorView::SetSLComment(TCHAR chComment, TCHAR chComment2)
{
	m_chComment = chComment;
	m_chComment2 = chComment2;
}

void CVBScriptEditorView::SetSLComment(LPCTSTR lpszComment)
{
	m_strComment = lpszComment;
}

void CVBScriptEditorView::AddKeywords(LPCTSTR lpszKwd)
{
	m_strKeywords = m_strKeywords + lpszKwd;
	m_strKeywordsLower = m_strKeywords;
	if (!m_bCaseSensitive)
		m_strKeywordsLower.MakeLower();
}

void CVBScriptEditorView::ClearKeywords()
{
	m_strKeywords.Empty();
	m_strKeywordsLower.Empty();
}							  

void CVBScriptEditorView::AddConstants(LPCTSTR lpszConst)
{
	m_strConstants = m_strConstants + lpszConst;
	m_strConstantsLower = m_strConstants;
	if (!m_bCaseSensitive)
		m_strConstantsLower.MakeLower();
}

void CVBScriptEditorView::ClearConstants()
{
	m_strConstants.Empty();
	m_strConstantsLower.Empty();
}							  

void CVBScriptEditorView::SetCaseSensitive(BOOL bSensitive)
{
	m_bCaseSensitive = bSensitive;
}

void CVBScriptEditorView::SetChangeCase(BOOL bChange)
{
	m_bChangeCase = bChange;
}

void CVBScriptEditorView::SetStringQuotes(LPCTSTR lpszStrQ)
{
	m_strStringQuotes = lpszStrQ;
}

void CVBScriptEditorView::SetKeywordColor(COLORREF clr, BOOL bBold)
{
	m_icKeyword.clrColor = clr;
	m_icKeyword.bBold = bBold;
}

void CVBScriptEditorView::SetConstantColor(COLORREF clr, BOOL bBold)
{
	m_icConstant.clrColor = clr;
	m_icConstant.bBold = bBold;
}

void CVBScriptEditorView::SetCommentColor(COLORREF clr, BOOL bBold)
{
	m_icComment.clrColor = clr;
	m_icComment.bBold = bBold;
}

void CVBScriptEditorView::SetNumberColor(COLORREF clr, BOOL bBold)
{
	m_icNumber.clrColor = clr;
	m_icNumber.bBold = bBold;
}

void CVBScriptEditorView::SetStringColor(COLORREF clr, BOOL bBold)
{
	m_icString.clrColor = clr;
	m_icString.bBold = bBold;
}
int CVBScriptEditorView::IsKeyword(LPCTSTR lpszSymbol)
{
	CString strSymbol; strSymbol.Format(" %s ", lpszSymbol);
	if (!m_bCaseSensitive) 
		strSymbol.MakeLower();
				
	return m_strKeywordsLower.Find(strSymbol);
}

int CVBScriptEditorView::IsConstant(LPCTSTR lpszSymbol)
{
	CString strSymbol; strSymbol.Format(" %s ", lpszSymbol);
	if (!m_bCaseSensitive) 
		strSymbol.MakeLower();
				
	return m_strConstantsLower.Find(strSymbol);
}

BOOL CVBScriptEditorView::IsStringQuote(TCHAR ch)
{
	return (m_strStringQuotes.Find(ch) >= 0);
}


void CVBScriptEditorView::SetFormatRange(int nStart, int nEnd, BOOL bBold, COLORREF clr)
{
	if (nStart >= nEnd)
		return;

	GetRichEditCtrl().SetSel(nStart, nEnd);

	DWORD dwEffects = bBold?CFE_BOLD:0;

	CHARFORMAT cfm;
	cfm.cbSize = sizeof(cfm);
    GetRichEditCtrl().GetSelectionCharFormat(cfm);
	
	if ((cfm.dwMask & CFM_COLOR)  && cfm.crTextColor == clr && 
		(cfm.dwMask & CFM_BOLD) && (cfm.dwEffects & CFE_BOLD) == dwEffects)
		return;

	cfm.dwEffects = dwEffects;
	cfm.crTextColor = clr;
	cfm.dwMask = CFM_BOLD | CFM_COLOR;

	GetRichEditCtrl().SetSelectionCharFormat(cfm);
}

void CVBScriptEditorView::ChangeCase(int nStart, int nEnd, LPCTSTR lpsz)
{
	ASSERT((nEnd - nStart) == (int)_tcslen(lpsz));

	if (!m_bCaseSensitive && m_bChangeCase) {
		GetRichEditCtrl().SetSel(nStart, nEnd);
		GetRichEditCtrl().ReplaceSel(lpsz);
	}
}

void CVBScriptEditorView::FormatTextRange(int nStart, int nEnd)
{
	if (nStart >= nEnd)
		return;

	m_bInForcedChange = TRUE;

	CHARRANGE crOldSel;

	GetRichEditCtrl().GetSel(crOldSel);
	LockWindowUpdate();
	GetRichEditCtrl().HideSelection(TRUE, FALSE);

	TCHAR *pBuffer = NULL;
	try {
		GetRichEditCtrl().SetSel(nStart, nEnd);
		pBuffer = new TCHAR[nEnd - nStart + 1];
		long nLen = GetRichEditCtrl().GetSelText(pBuffer);

		ASSERT(nLen <= nEnd - nStart);

		pBuffer[nLen] = 0;

		TCHAR *pStart, *pPtr;
		pStart = pPtr = pBuffer;

		TCHAR* pSymbolStart = NULL;
		SymbolColor ic;

		while (*pPtr != 0) {
			TCHAR ch = *pPtr;

			if (ch == m_chComment && (m_chComment2 == 0 || pPtr[1] == m_chComment2)) {
				pSymbolStart = pPtr;
				do {
					ch = *(++pPtr);
				} while (ch != 0 && ch != '\r');
				ic = m_icComment;
			} else if (IsStringQuote(ch)) { // Process strings
				pSymbolStart = pPtr;
				TCHAR ch1 = ch;
				do {
					ch = *(++pPtr);
				} while (ch != 0 && ch != ch1 && ch != '\r');
				if (ch == ch1) pPtr++;
				ic = m_icString;
			} else if (_istdigit(ch)) { // Process numbers
				pSymbolStart = pPtr;
				_tcstod(pSymbolStart, &pPtr);
				ic = m_icNumber;
			} else if (_istalpha(ch) || ch == '_') { // Process keywords
				pSymbolStart = pPtr;
				do {
					ch = *(++pPtr);
				} while (_istalnum(ch) || ch == '_');
				*pPtr = 0;
				int nPos = IsKeyword(pSymbolStart);
				if (nPos >= 0) {
					ChangeCase(nStart + pSymbolStart - pBuffer, nStart + pPtr - pBuffer, 
								m_strKeywords.Mid(nPos+1, pPtr - pSymbolStart));
					if (_tcsicmp(m_strComment, pSymbolStart) == 0) {
						*pPtr = ch;
						*pSymbolStart = m_chComment;
						if (pSymbolStart[1] != 0 && m_chComment2 != 0)
							pSymbolStart[1] = m_chComment2;
						pPtr = pSymbolStart;
						pSymbolStart = NULL;
						continue;
					}
					ic = m_icKeyword;
				} else {
					nPos = IsConstant(pSymbolStart);
					if (nPos >= 0) {
							ChangeCase(nStart + pSymbolStart - pBuffer, nStart + pPtr - pBuffer, 
										m_strConstants.Mid(nPos+1, pPtr - pSymbolStart));
						ic = m_icConstant;
					} else {
						pSymbolStart = NULL;
					}
				}
				*pPtr = ch;
			} else {
				pPtr++;
			}

			if (pSymbolStart != NULL) {
				ASSERT(pSymbolStart < pPtr);
				SetFormatRange(nStart + pStart - pBuffer, nStart + pSymbolStart - pBuffer, FALSE, RGB(0,0,0));
				SetFormatRange(nStart + pSymbolStart - pBuffer, nStart + pPtr - pBuffer, ic.bBold, ic.clrColor);
				pStart = pPtr;
				pSymbolStart = 0;
			} else if (*pPtr == 0)
				SetFormatRange(nStart + pStart - pBuffer, nStart + pPtr - pBuffer, FALSE, RGB(0,0,0));
		}

	} catch(...){}

	delete [] pBuffer;

	GetRichEditCtrl().SetSel(crOldSel);
	GetRichEditCtrl().HideSelection(FALSE, FALSE);
	UnlockWindowUpdate();

	m_bInForcedChange = FALSE;
}

void CVBScriptEditorView::FormatTextLines(int nLineStart, int nLineEnd)
{
	long nStart = GetRichEditCtrl().LineIndex(GetRichEditCtrl().LineFromChar(nLineStart));
	long nEnd = GetRichEditCtrl().LineIndex(GetRichEditCtrl().LineFromChar(nLineEnd));
	nEnd += GetRichEditCtrl().LineLength(nLineEnd);

	FormatTextRange(nStart, nEnd);
}


void CVBScriptEditorView::FormatAll()
{
	FormatTextRange(0, GetTextLength());
}

LRESULT CVBScriptEditorView::OnSetText(WPARAM wParam, LPARAM lParam)
{
	LRESULT res = Default();
	//FormatAll();
	return res;	
}

void CVBScriptEditorView::OnChange() 
{
	if (m_bInForcedChange)
		return;

	CHARRANGE crCurSel; 
	GetRichEditCtrl().GetSel(crCurSel);

	if (m_changeType == ctMove && crCurSel.cpMin == crCurSel.cpMax) {
		// cut was canceled, so this is paste operation
		m_changeType = ctPaste;
	}

	switch(m_changeType) {
	case ctReplSel:// old=(x,y) -> cur=(x+len,x+len)
	case ctPaste:  // old=(x,y) -> cur=(x+len,x+len)
		FormatTextLines(m_crOldSel.cpMin, crCurSel.cpMax);
		break;
	case ctDelete: // old=(x,y) -> cur=(x,x)
	case ctBack:   // old=(x,y) -> cur=(x,x), newline del => old=(x,x+1) -> cur=(x-1,x-1)
	case ctCut:    // old=(x,y) -> cur=(x,x)
		FormatTextLines(crCurSel.cpMin, crCurSel.cpMax);
		break;
	case ctUndo:   // old=(?,?) -> cur=(x,y)
		FormatTextLines(crCurSel.cpMin, crCurSel.cpMax);
		break;
	case ctMove:   // old=(x,x+len) -> cur=(y-len,y) | cur=(y,y+len)
		FormatTextLines(crCurSel.cpMin, crCurSel.cpMax);
		if (crCurSel.cpMin > m_crOldSel.cpMin) // move after
			FormatTextLines(m_crOldSel.cpMin, m_crOldSel.cpMin);
		else // move before
			FormatTextLines(m_crOldSel.cpMax, m_crOldSel.cpMax);
		break;
	default:
		FormatAll();
		break;
	}

	//undo action does not call OnProtected, so make it default
	m_changeType = ctUndo;
}

void CVBScriptEditorView::OnProtected(NMHDR* pNMHDR, LRESULT* pResult)
{
	ENPROTECTED* pEP = (ENPROTECTED*)pNMHDR;

	// determine type of change will occur

	switch (pEP->msg) {
	case WM_KEYDOWN:
		switch (pEP->wParam) {
		case VK_DELETE:
			m_changeType = ctDelete;
			break;
		case VK_BACK:
			m_changeType = ctBack;
			break;
		default:
			m_changeType = ctUnknown;
			break;
		}
		break;
	case EM_REPLACESEL:
	case WM_CHAR:
		m_changeType = ctReplSel;
		break;
	case WM_PASTE:
		m_changeType = (m_changeType == ctCut)?ctMove:ctPaste;
		break;
	case WM_CUT:
		m_changeType = ctCut;
		break;
	case EM_SETCHARFORMAT:
		// Ignore this
		break;
	default:
		m_changeType = ctUnknown;
		break;
	};

	if (pEP->msg != EM_SETCHARFORMAT && m_changeType != ctMove)
		m_crOldSel = pEP->chrg;

	*pResult = FALSE;
}

static LPCTSTR szKeywords = " Call Const Dim Do Loop Erase Exit For To Step Next "
"Each Function If Then Else On Error Resume Option Explicit Private Public Randomize "
"ReDim Rem Select Case Set Sub End While Wend "
"And Eqv Imp Is Mod Not Or Xor ";

static LPCTSTR szConstants = " Empty False True Nothing Null "
"vbBlack vbRed vbGreen vbYellow vbBlue vbMagenta vbCyan vbWhite "
"vbBinaryCompare vbTextCompare vbDatabaseCompare "
"vbGeneralDate vbLongDate vbShortDate vbLongTime vbShortTime "
"vbSunday vbMonday vbTuesday vbWednesday vbThursday vbFriday vbSaturday "
"vbFirstJan1 vbFirstFourDays vbFirstFullWeek vbUseSystem vbUseSystemDayOfWeek "
"vbObjectError vbOKOnly vbOKCancel vbAbortRetryIgnore vbYesNoCancel vbYesNo "
"vbRetryCancel vbCritical vbQuestion vbExclamation vbInformation "
"vbDefaultButton1 vbDefaultButton2 vbDefaultButton3 vbDefaultButton4 "
"vbApplicationModal vbSystemModal "
"vbCr vbCrLf vbFormFeed vbLf vbNewLine vbNullChar vbNullString vbTab vbVerticalTab "
"vbEmpty vbNull vbInteger vbLong vbSingle vbDouble vbCurrency vbDate vbString "
"vbObject vbError vbBoolean vbVariant vbDataObject vbDecimal vbByte vbArray ";

int CVBScriptEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CRichEditView::OnCreate(lpCreateStruct) == -1)
		return -1;

	Initialize();

	SetCaseSensitive(FALSE);
	SetStringQuotes(_T("\""));
	SetSLComment(_T('\''));
	SetSLComment(_T("rem"));
	AddKeywords(szKeywords);
	AddConstants(szConstants);
	
	return 0;
}
