#include "stdafx.h"
#include "ColorString.h"

//  Copyright (c) 1996-1997, Keith Rule
//  You may freely use or modify this code provided this 
//  copyright is included in all derived versions.

UINT AFX_CDECL CColorStringBkgThread(LPVOID object)
{
	CColorString&	text = *((CColorString*) object);
	long			len, count = 0;
	CColorArray		renderColor;	// Hmm - This shouldn't be declared here, 
									// it causes a leak when the thread is terminated.

	// This isn't exactly efficent, but hey it's running in
	// the background
	for (;;) {
		len = text.GetLength();

		if (text.CommentPos() < len || text.KeywordPos() < len || text.QuotePos() < len) {
			renderColor.SetSize(len);
			renderColor.SetColor(text.m_defaultColor, 0, len);

			text.CommentPos(0); text.KeywordPos(0); text.QuotePos(0);
			if (text.m_color.GetSize() != len) {
				text.m_color.SetSize(len);
			}

			if (!text.ParseKeywords(renderColor)) goto restart;
			if (!text.ParseQuotes(renderColor)) goto restart;
			if (!text.ParseComments(renderColor)) goto restart;
		
			if (renderColor != text.m_color && len == text.GetLength())  
			{
				text.m_color = renderColor;
				text.DoUpdate(count > 0);
			}
		}
restart:
		::Sleep(100);
		count++;
	}

	return 0;
}


CColorString::CColorString(BOOL bUseThread) : CStringEx(), 
	m_defaultColor(RGB(0, 0, 0)), m_bkgThread(NULL),
	m_dQuoteColor(RGB(0, 0, 0)), m_sQuoteColor(RGB(0, 0, 0)), m_updateLevel(0),
	CThreadLock(), m_bUseThread(bUseThread), m_kPos(0), m_cPos(0), m_qPos(0)
{
	//TRACE("ColorString() - %x  File: %s, Line: %d\r\n", this, __FILE__, __LINE__);
}

CColorString::CColorString(const CString& stringSrc, BOOL bUseThread) : CStringEx( stringSrc ), m_bkgThread(NULL),
	m_defaultColor(RGB(0, 0, 0)), 
	m_dQuoteColor(RGB(0, 0, 0)), m_sQuoteColor(RGB(0, 0, 0)), m_updateLevel(0),
	CThreadLock(), m_bUseThread(bUseThread), m_kPos(0), m_cPos(0), m_qPos(0)
{
	//TRACE("ColorString() - %x  File: %s, Line: %d\r\n", this, __FILE__, __LINE__);
}

CColorString::CColorString(const CStringEx& stringSrc, BOOL bUseThread) : CStringEx( stringSrc ), m_bkgThread(NULL),
	m_defaultColor(RGB(0, 0, 0)), 
	m_dQuoteColor(RGB(0, 0, 0)), m_sQuoteColor(RGB(0, 0, 0)), m_updateLevel(0),
	CThreadLock(), m_bUseThread(bUseThread), m_kPos(0), m_cPos(0), m_qPos(0)
{
	//TRACE("ColorString() - %x  File: %s, Line: %d\r\n", this, __FILE__, __LINE__);
}

CColorString::CColorString(TCHAR ch, int nRepeat /*= 1*/, BOOL bUseThread) : CStringEx( ch, nRepeat ), m_bkgThread(NULL),
	m_defaultColor(RGB(0, 0, 0)),
	m_dQuoteColor(RGB(0, 0, 0)), m_sQuoteColor(RGB(0, 0, 0)), m_updateLevel(0),
	CThreadLock(), m_bUseThread(bUseThread), m_kPos(0), m_cPos(0), m_qPos(0)
{
	//TRACE("ColorString() - %x  File: %s, Line: %d\r\n", this, __FILE__, __LINE__);
}

CColorString::CColorString(LPCTSTR lpch, int nLength, BOOL bUseThread) : CStringEx( lpch, nLength ), m_bkgThread(NULL),
	m_defaultColor(RGB(0, 0, 0)), 
	m_dQuoteColor(RGB(0, 0, 0)), m_sQuoteColor(RGB(0, 0, 0)), m_updateLevel(0),
	CThreadLock(), m_bUseThread(bUseThread), m_kPos(0), m_cPos(0), m_qPos(0)
{
	//TRACE("ColorString() - %x  File: %s, Line: %d\r\n", this, __FILE__, __LINE__);
}

CColorString::CColorString(const unsigned char* psz, BOOL bUseThread) : CStringEx( psz ), m_bkgThread(NULL),
	m_defaultColor(RGB(0, 0, 0)), 
	m_dQuoteColor(RGB(0, 0, 0)), m_sQuoteColor(RGB(0, 0, 0)),
	CThreadLock(), m_bUseThread(bUseThread), m_kPos(0), m_cPos(0), m_qPos(0)
{
	//TRACE("ColorString() - %x  File: %s, Line: %d\r\n", this, __FILE__, __LINE__);
}

CColorString::CColorString(LPCWSTR lpsz, BOOL bUseThread) : CStringEx( lpsz ), m_bkgThread(NULL),
	m_defaultColor(RGB(0, 0, 0)), 
	m_dQuoteColor(RGB(0, 0, 0)), m_sQuoteColor(RGB(0, 0, 0)), m_updateLevel(0),
	CThreadLock(), m_bUseThread(bUseThread), m_kPos(0), m_cPos(0), m_qPos(0)
{
	//TRACE("ColorString() - %x  File: %s, Line: %d\r\n", this, __FILE__, __LINE__);
}

CColorString::CColorString(LPCSTR lpsz, BOOL bUseThread) : CStringEx( lpsz ), m_bkgThread(NULL),
	m_defaultColor(RGB(0, 0, 0)),
	m_dQuoteColor(RGB(0, 0, 0)), m_sQuoteColor(RGB(0, 0, 0)), m_updateLevel(0),
	CThreadLock(), m_bUseThread(bUseThread), m_kPos(0), m_cPos(0), m_qPos(0)
{
	//TRACE("ColorString() - %x  File: %s, Line: %d\r\n", this, __FILE__, __LINE__);
}

CColorString::~CColorString()
{
	if (m_bkgThread != NULL) {
		m_bkgThread->SuspendThread();
		delete m_bkgThread;
	}

	for (int i = 0; i < KeywordHashSize; i++) {
		for (int j = 0; j < m_keywordTable[i].GetSize(); j++) {
			if (m_keywordTable[i][j] != NULL) delete m_keywordTable[i][j];
		}
	}

	for (i = 0; i < m_comment.GetSize(); i++) {
		if (m_comment[i] != NULL) delete m_comment[i];
	}

	for (i = 0; i < m_quote.GetSize(); i++) {
		if (m_quote[i] != NULL) delete m_quote[i];
	}
}

void CColorString::AddUpdateTarget(CColorStringUpdate* update)
{
	for (int i = 0; i < m_update.GetSize(); i++) {
		if (m_update[i] == update) return;
	}
	m_update.Add(update);
}

BOOL CColorString::AddKeyword(const CString& keyword, COLORREF color /*= RGB(0, 0, 200)*/) 
{
	CKeywordInfo* pKey = new CKeywordInfo(keyword, color);
	if (pKey != NULL) {
		m_keywordTable[Hash(keyword)].Add(pKey);
	}
	return pKey != NULL;
}

BOOL CColorString::AddComment(const CString& begin /*= _T("//")*/, const CString& end /*= _T("\n")*/, COLORREF color /*= RGB(0, 200, 0)*/)			
{
	CCommentInfo* pComment = new CCommentInfo(begin, end, color);
	if (pComment != NULL) {
		m_comment.Add(pComment);
	}
	return pComment != NULL;
}

BOOL CColorString::AddQuote(const CString & begin, const CString & end, COLORREF color)
{
	CQuoteInfo* pQuote = new CQuoteInfo(begin, end, color);
	if (pQuote != NULL) {
		m_quote.Add(pQuote);
	}
	return pQuote != NULL;
}

void CColorString::SetDefaults(COLORREF color /*= RGB(0, 0, 0)*/, COLORREF sQuoteColor /*= RGB(0, 0,0)*/, COLORREF dQuoteColor /*= RGB(0, 0, 0)*/)					
{
	m_defaultColor = color; 
	m_sQuoteColor = sQuoteColor;
	m_dQuoteColor = dQuoteColor;
}

COLORREF CColorString::GetColor(long index)							
{
	COLORREF retval = m_defaultColor;
	if (index >= 0 && index < m_color.GetSize()) {
		retval = m_color[index];
	}
	return retval;
}

void CColorString::BeginUpdate(long pos, long len)
{
	if (m_updateLevel <= 0) m_updatePos = GetLength();
	m_updateLevel++;
}

void CColorString::EndUpdate(long pos, long len)	{
	m_updateLevel--;
	if (pos < m_updatePos) m_updatePos = pos;
	if (m_updateLevel == 0) Process(m_updatePos);
	return;
}

BOOL IsToken(TCHAR c, BOOL bCharOnly)
{
	return !((!bCharOnly && IsWhite(c)) || (bCharOnly && !(IsAlphaNum(c) || c == '#')));
}

long CColorString::GetToken(CString& token, long pos, BOOL bCharOnly)
{
	long	retval = -1;
	TCHAR	c;

	// Skip whitespace
	while (pos < GetLength() && !IsToken(GetAt(pos), bCharOnly)) {
		pos++;
	}

	// Save start position
	retval = pos;

	// Fill in token
	token = _T("");
	if (pos < GetLength()) {
		for (c = GetAt(pos); IsToken(c, bCharOnly); c = GetAt(++pos)) {
			token += c;
			if (pos+1 >= GetLength()) break;
		}
	}
	
	// return start position
	return retval;
}

long CColorString::GetComment(const CString& beginToken, const CString& endToken, long& commentLen, long pos)
{
	long len = GetLength();
	long beginTokenLen = beginToken.GetLength();
	long endTokenLen = endToken.GetLength();

	commentLen = 0;
	if (!beginToken.IsEmpty() && !endToken.IsEmpty()) {
		// Skip Whitespace
		for (int i = pos; i < len && IsWhite(GetAt(i)); i++) 
			;

		// Find Comment
		if (i/*+beginTokenLen*/ < len && Mid(i, beginTokenLen) == beginToken) {
			// Find close of comment
			for (int j = i+beginTokenLen; j+endTokenLen < len; j++) {
				if (Mid(j, endTokenLen) == endToken) {
					commentLen = (j+endTokenLen)-i; 
					return i;
				}
			}

			// Handle case where single line comments goes to EOF
			if (j+endTokenLen >= len && endToken == _T("\n")) {
				commentLen = len - i;
				return i;
			}
		}
	}

	return -1;
}

long CColorString::GetQuote(const CString & beginToken, const CString & endToken, long & commentLen, long pos)
{
	long len = GetLength();
	long beginTokenLen = beginToken.GetLength();
	long endTokenLen = endToken.GetLength();
	long i = pos;

	commentLen = 0;
	if (!beginToken.IsEmpty() && !endToken.IsEmpty()) {
		// Find Quote
start:
		// Skip Whitespace
		for (; i < len && IsWhite(GetAt(i)); i++) 
			;

		if (i < len && Mid(i, beginTokenLen) == beginToken) {
			// Find close of comment
			for (int j = i+beginTokenLen; j+endTokenLen < len; j++) {
				if (GetAt(j) == '\n') {
					i++;
					goto start;
				}
				if (Mid(j, endTokenLen) == endToken) {
					commentLen = (j+endTokenLen)-i; 
					return i;
				}
			}

			// Handle case where single line comments goes to EOF
			if (j+endTokenLen >= len && endToken == _T("\n")) {
				commentLen = len - i;
				return i;
			}
		}
	}

	return -1;
}

CKeywordInfo* CColorString::KeywordLookup(const CString& token)
{
	CArray<CKeywordInfo*, CKeywordInfo*>& keywordTable = m_keywordTable[Hash(token)];
	long size = keywordTable.GetSize();

	for (int i = 0; i < size; i++) {
		if (token == keywordTable[i]->Keyword()) {
			return keywordTable[i];
		}
	}
	return NULL;
}

long CColorString::Offset2Line(long pos)
{
	long prev, cur, i = 1, len = m_lineOffset.GetSize();

	if (pos <= 0) return 0;

	if (m_lineOffset.GetSize() > 0) {
		prev = m_lineOffset[0];
		for (i = 1; i < len; i++) {
			cur = m_lineOffset[i];
			if (pos >= prev && pos < cur) {
				return i-1;
			}
			prev = cur;
		}
	}

	return len-1;
}

void CColorString::Reset(long pos /*= 0*/)
{
	ThreadLock();
	m_lineOffset.SetSize(0);
	m_lineOffset.Add(0);
	for (int i = 0; i < GetLength(); i++) {
		if (GetAt(i) == '\n') m_lineOffset.Add(i+1);
	}
	ThreadUnlock();

	KeywordPos(0); CommentPos(0); QuotePos(0);

	m_color.SetColor(m_defaultColor, pos, GetLength()-pos);

	if (!m_bUseThread) 
	{
		ParseKeywords(m_color);
		ParseQuotes(m_color);
		ParseComments(m_color);
	}
}

long CColorString::GetLineCount() 
{
	long retval = 0;
	ThreadLock();
	retval = m_lineOffset.GetSize();
	ThreadUnlock();
	return retval;
}

long CColorString::GetLineOffset(long index) 
{
	long retval = 0;
	ThreadLock();
	if (index >= m_lineOffset.GetSize()) return GetLength();
	if (index < 0) return 0;
	retval = m_lineOffset[index];
	ThreadUnlock();
	return retval;
}

BOOL CColorString::ParseComments(CColorArray& color)
{
	long			len = GetLength();
	long			pos, size, start;
	BOOL			bComment;

	len = GetLength();
	pos = CommentPos();

	while (pos < len) {
		bComment = FALSE;
		for (int i = 0; i < m_comment.GetSize(); i++) {
			if ((start = GetComment(m_comment[i]->Begin(), m_comment[i]->End(), size, pos)) >= pos) {
				
				// We've found a comment
				color.SetColor(m_comment[i]->Color(), start, size);

				ThreadLock();
				if (pos != CommentPos() || len != GetLength()) {
					ThreadUnlock();
					return FALSE;
				}
				
				pos = CommentPos(start+size-1);
				ThreadUnlock();
			}
		}

		if (!bComment) {
			ThreadLock();
			pos = CommentPos(CommentPos()+1);
			ThreadUnlock();
		}
	}

	return TRUE;
}

BOOL CColorString::ParseKeywords(CColorArray& color)
{
	CString			token;
	long			beginToken;
	CKeywordInfo*	pKeyword = NULL;
	long			len = GetLength();
	long			pos;

	pos = KeywordPos();

	while (pos < len) {
		beginToken = GetToken(token, pos, TRUE);
		long tokenLen = token.GetLength();
		if (tokenLen > 0) {
			if ((pKeyword = KeywordLookup(token)) != NULL) {
				color.SetColor(pKeyword->Color(), beginToken, tokenLen);
			} 
		} 

		ThreadLock();
		if (pos != KeywordPos() || len != GetLength()) {
			ThreadUnlock();
			return FALSE;
		}
		pos = KeywordPos((tokenLen > 0 ? beginToken + tokenLen : pos + 1));
		ThreadUnlock();
	}

	return TRUE;
}

BOOL CColorString::ParseQuotes(CColorArray& color)
{
	long			len = GetLength();
	long			pos, size, start;
	BOOL			bQuote;

	len = GetLength();
	pos = QuotePos();

	while (pos < len) {
		bQuote = FALSE;
		for (int i = 0; i < m_quote.GetSize(); i++) {
			if ((start = GetQuote(m_quote[i]->Begin(), m_quote[i]->End(), size, pos)) >= pos) {
				
				// We've found a comment
				color.SetColor(m_quote[i]->Color(), start, size);

				ThreadLock();
				if (pos != QuotePos() || len != GetLength()) {
					ThreadUnlock();
					return FALSE;
				}
				
				pos = QuotePos(start+size-1);
				ThreadUnlock();
			}
		}

		if (!bQuote) {
			ThreadLock();
			pos = QuotePos(QuotePos()+1);
			ThreadUnlock();
		}
	}

	return TRUE;
}


void CColorString::DoUpdate(BOOL bDataChangedFlag)
{
	for (int i = 0; i < m_update.GetSize(); i++) {
		m_update[i]->DoColorStringUpdate(bDataChangedFlag);
	}
}

void CColorString::Process(long pos /*= 0*/)
{
	long			len = GetLength();

	ThreadLock();
	if (m_color.GetSize() != len) {
		//TRACE("m_color(%d) != len(%d)\r\n", m_color.GetSize(), len);
		m_color.SetSize(len);
	}
	if (m_renderColor.GetSize() != len) m_renderColor.SetSize(len);
	ThreadUnlock();

	Reset(pos);

	if (m_bkgThread == NULL) {
		m_bkgThread = AfxBeginThread(CColorStringBkgThread, this, THREAD_PRIORITY_LOWEST);
	}
}

CString CColorString::GetLine(long index)
{
	CString retval = _T("");

	if (index >= 0 && index < GetLineCount()) {
		long begin = GetLineOffset(index);
		long size;
		if (index+1 < GetLineCount()) {
			size = GetLineOffset(index+1)-begin-1;
		} else {
			size = GetLength()-begin;
		}
		ThreadLock();
		retval = Mid(begin, size); 
		ThreadUnlock();
	}

	return retval;
}

CColorString& CColorString::operator=(const CString& rhs)
{
	BeginUpdate();
	ThreadLock();
	*((CString*) this) = rhs;
	long len = GetLength();
	m_color.SetSize(len);
	ThreadUnlock();
	EndUpdate(0, len);
	return *this;
}

CColorString& CColorString::operator=(const CStringEx& rhs)
{
	BeginUpdate();
	ThreadLock();
	*((CStringEx*) this) = rhs;
	long len = GetLength();
	m_color.SetSize(len);
	ThreadUnlock();
	EndUpdate(0, len);
	return *this;
}

CColorString& CColorString::operator=(TCHAR ch)
{
	BeginUpdate();
	ThreadLock();
	*((CString*) this) = ch;
	long len = GetLength();
	m_color.SetSize(len);
	ThreadUnlock();
	EndUpdate(0, len);
	return *this;
}

CColorString& CColorString::operator=(LPCSTR lpsz)
{
	BeginUpdate();
	ThreadLock();
	*((CString*) this) = lpsz;
	long len = GetLength();
	m_color.SetSize(len);
	ThreadUnlock();
	EndUpdate(0, len);
	return *this;
}

CColorString& CColorString::operator=(LPCWSTR lpsz)
{
	BeginUpdate();
	ThreadLock();
	*((CString*) this) = lpsz;
	long len = GetLength();
	m_color.SetSize(len);
	ThreadUnlock();
	EndUpdate(0, len);
	return *this;
}

CColorString& CColorString::operator=(const unsigned char* psz)
{
	BeginUpdate();
	ThreadLock();
	*((CString*) this) = psz;
	long len = GetLength();
	m_color.SetSize(len);
	ThreadUnlock();
	EndUpdate(0, len);
	return *this;
}

// string concatenation
CColorString& CColorString::operator+=(const CString& string)
{
	ThreadLock();
	long pos = GetLength();
	ThreadUnlock();

	BeginUpdate();

	ThreadLock();
	*((CString*) this) += string;
	long len = GetLength();
	m_color.SetSize(len);
	ThreadUnlock();

	EndUpdate(pos, len-pos);
	return *this;
}

CColorString& CColorString::operator+=(TCHAR ch)
{
	BeginUpdate();
	ThreadLock();
	long pos = GetLength();
	*((CString*) this) += ch;
	long len = GetLength();
	m_color.SetSize(len);
	ThreadUnlock();

	EndUpdate(pos, len);
	return *this;
}

CColorString& CColorString::operator+=(LPCTSTR lpsz)
{
	BeginUpdate();

	ThreadLock();
	long pos = GetLength();
	*((CString*) this) += lpsz;
	long len = GetLength();
	m_color.SetSize(len);
	ThreadUnlock();

	EndUpdate(pos, len-pos);
	return *this;
}

CColorString& CColorString::Insert(int pos, LPCTSTR s)
{
	BeginUpdate();
	ThreadLock();
	CStringEx::Insert(pos, s);
	m_color.InsertAt(pos, m_defaultColor, strlen(s));
	long len = GetLength();
	ThreadUnlock();
	EndUpdate(pos, len-pos);
	return *this;
}

CColorString& CColorString::Insert(int pos, TCHAR c)
{
	BeginUpdate();
	ThreadLock();
	CStringEx::Insert(pos, c);
	m_color.InsertAt(pos, m_defaultColor);
	long len = GetLength();
	ThreadUnlock();
	EndUpdate(pos, len-pos);
	return *this;
}

CColorString& CColorString::Delete(int pos, int len)
{
	BeginUpdate();
	ThreadLock();
	CStringEx::Delete(pos, len);
	m_color.RemoveAt(pos, len);
	long tLen = GetLength();
	ThreadUnlock();
	EndUpdate(pos, tLen-pos);
	return *this;
}

CColorString& CColorString::Replace(int pos, int len, LPCTSTR s)
{
	BeginUpdate();
	ThreadLock();
	CStringEx::Replace(pos, len, s);
	ThreadUnlock();
	EndUpdate(pos, len);
	return *this;
}

void CColorString::SetAt(int nIndex, TCHAR ch)
{
	BeginUpdate();

	ThreadLock();
	CString::SetAt(nIndex, ch);
	m_color.SetAt(nIndex, m_defaultColor);
	ThreadUnlock();
	EndUpdate(nIndex, 1);
}


