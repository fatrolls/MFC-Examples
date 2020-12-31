#ifndef _CCOLORSTRING_H_
#define _CCOLORSTRING_H_

#include <afxtempl.h>
#include <ctype.h>
#include "StringEx.h"

//  Copyright (c) 1996-1997, Keith Rule
//  You may freely use or modify this code provided this 
//  copyright is included in all derived versions.

const KeywordHashSize = 113;

UINT AFX_CDECL CColorStringBkgThread(LPVOID);

inline long Hash(const CString& name)
{
	long	hashval = 0;
	long	len = name.GetLength();
	for (int i = 0; i < len; i++) {
		hashval += name[i];
	}
	return hashval%KeywordHashSize;
}

inline BOOL IsWhite(TCHAR c)
{
	return iswspace(c) || c == '\r' || c == '\n' || !iswprint(c);
}

inline BOOL IsAlphaNum(TCHAR c)
{
	return iswalnum(c);
}


class CColorStringUpdate {
public:
	virtual void DoColorStringUpdate(BOOL bDataChanged = TRUE) = 0;
};

class CThreadLock {
private:
	mutable CRITICAL_SECTION	m_threadLock;
public:
	CThreadLock()							{::InitializeCriticalSection(&m_threadLock);}
	~CThreadLock()							{::DeleteCriticalSection(&m_threadLock);}
	void	ThreadLock(void) const			{::EnterCriticalSection(&m_threadLock);}
#if(_WIN32_WINNT >= 0x0400)
	BOOL	TryThreadLock(void) const		{return ::TryEnterCriticalSection(&m_threadLock);}
#else
	BOOL	TryThreadLock(void)	const		{ThreadLock(); return TRUE;}
#endif
	void	ThreadUnlock(void) const		{::LeaveCriticalSection(&m_threadLock);}
};

class CCommentInfo : public CObject {
private:
	CString			m_begin, m_end;
	COLORREF		m_color;
public:
	CCommentInfo(const CString& begin = _T("//"), const CString& end = _T("\n"), COLORREF color = RGB(0, 200, 0)) :
		m_begin(begin), m_end(end), m_color(color)
	{
		;
	}
	CString& Begin()				{return m_begin;}
	CString Begin() const			{return m_begin;}
	CString& End()					{return m_end;}
	CString End() const				{return m_end;}
	COLORREF Color() const			{return m_color;}
};

class CQuoteInfo : public CObject {
private:
	CString			m_begin, m_end;
	COLORREF		m_color;
public:
	CQuoteInfo(const CString& begin = _T("//"), const CString& end = _T("\n"), COLORREF color = RGB(0, 200, 200)) :
		m_begin(begin), m_end(end), m_color(color)
	{
		;
	}
	CString& Begin()				{return m_begin;}
	CString Begin() const			{return m_begin;}
	CString& End()					{return m_end;}
	CString End() const				{return m_end;}
	COLORREF Color() const			{return m_color;}
};

class CKeywordInfo : public CObject {
private:
	CString			m_keyword;
	COLORREF		m_color;
public:
	CKeywordInfo(const CString& value = _T(""), COLORREF color = RGB(0, 0, 200)) : 
					m_keyword(value), m_color(color) {;}
	CString& Keyword()				{return m_keyword;}
	CString Keyword() const			{return m_keyword;}
	COLORREF Color() const			{return m_color;}
};

class CColorArray : public CThreadLock {
protected:
	CArray<COLORREF, COLORREF>	m_color;
public:
	CColorArray() {
			//TRACE("CColorArray() - %x  File: %s, Line: %d\r\n", this, __FILE__, __LINE__);
	}
	CColorArray(const CColorArray& copy) {
		if (&copy != this) {
			ThreadLock();
			copy.ThreadLock();
			m_color.SetSize(0);
			for (int i = 0; i < copy.m_color.GetSize(); i++) {
				m_color.Add(copy[i]);
			}
			copy.ThreadUnlock();
			ThreadUnlock();
		}
	}

	CColorArray& operator=(const CColorArray& copy) {
		if (&copy != this) {
			ThreadLock();
			copy.ThreadLock();
			m_color.SetSize(0);
			for (int i = 0; i < copy.m_color.GetSize(); i++) {
				m_color.Add(copy[i]);
			}
			copy.ThreadUnlock();
			ThreadUnlock();
		}
		return *this;
	}

	BOOL operator==(const CColorArray& rhs)
	{
		ThreadLock();
		rhs.ThreadLock();
		BOOL retval = FALSE;
		if (rhs.m_color.GetSize() == m_color.GetSize()) {
			retval = TRUE;
			for (int i = 0; i < m_color.GetSize(); i++) {
				if (rhs[i] != m_color[i]) {
					retval = FALSE;
					break;
				}
			}
		}
		rhs.ThreadUnlock();
		ThreadUnlock();
		return FALSE;
	}

	BOOL operator!=(const CColorArray& rhs) 
	{
		return !(*this == rhs);
	}

	void SetSize(long size) 
	{
		ThreadLock();
		m_color.SetSize(size);
		ThreadUnlock();
	}

	long GetSize() 
	{
		long retval;
		ThreadLock();
		retval = m_color.GetSize();
		ThreadUnlock();
		return retval;
	}

	COLORREF operator[](long index) const
	{
		COLORREF retval;
		ThreadLock();
		retval = m_color[index];
		ThreadUnlock();
		return retval;
	}

	COLORREF GetAt(long index) const
	{
		COLORREF retval;
		ThreadLock();
		retval = m_color[index];
		ThreadUnlock();
		return retval;
	}

	void SetAt(long index, COLORREF value) {
		ThreadLock();
		m_color.SetAt(index, value);
		ThreadUnlock();
	}

	BOOL SetColor(COLORREF color, long pos, long len = 1)
	{
		BOOL retval = FALSE;
	
		for (int i = pos; i < GetSize() && i < pos + len; i++) {
			if (!retval && m_color[i] != color) retval = TRUE;
			SetAt(i, color);
		}
		return retval;
	}

	void InsertAt(int nIndex, COLORREF newElement, int nCount = 1)
	{
		ThreadLock();
		m_color.InsertAt(nIndex, newElement, nCount);
		ThreadUnlock();
	}

	void RemoveAt(int nIndex, int nCount = 1)
	{
		ThreadLock();
		m_color.RemoveAt(nIndex, nCount);
		ThreadUnlock();
	}
};

class CColorString : public CStringEx, public CThreadLock
{
private:
	CColorArray											m_color;
	CColorArray											m_renderColor;
	CArray<CKeywordInfo*, CKeywordInfo*>				m_keywordTable[KeywordHashSize];
	CArray<CCommentInfo*, CCommentInfo*>				m_comment;
	CArray<CQuoteInfo*, CQuoteInfo*>					m_quote;
	CArray<CColorStringUpdate*, CColorStringUpdate*>	m_update;
	CArray<long, long>									m_lineOffset;
	COLORREF											m_defaultColor;
	COLORREF											m_dQuoteColor;
	COLORREF											m_sQuoteColor;
	long												m_updateLevel, m_updatePos;
	CWinThread*											m_bkgThread;
	long												m_kPos, m_cPos, m_qPos;
	BOOL												m_bUseThread;

public:
	long GetQuote(const CString& beginToken, const CString& endToken, long& commentLen, long pos);
	BOOL AddQuote(const CString& begin = _T("\""), const CString& end = _T("\""), COLORREF color = RGB(0, 0, 200));
	// Construction/Destruction
	CColorString(BOOL bUseThread = TRUE);
	CColorString(const CString& stringSrc, BOOL bUseThread = TRUE);
	CColorString(const CStringEx& stringSrc, BOOL bUseThread = TRUE);
	CColorString(TCHAR ch, int nRepeat = 1, BOOL bUseThread = TRUE);
	CColorString(LPCTSTR lpch, int nLength, BOOL bUseThread = TRUE);
	CColorString(const unsigned char* psz, BOOL bUseThread = TRUE);
	CColorString(LPCWSTR lpsz, BOOL bUseThread = TRUE);
	CColorString(LPCSTR lpsz, BOOL bUseThread = TRUE);
	~CColorString();

	// Access Functions
	long KeywordPos() 
	{
		long retval;
		ThreadLock();
		retval = m_kPos;
		ThreadUnlock();
		return retval;
	}

	long KeywordPos(long pos)
	{
		long retval;
		ThreadLock();
		retval = m_kPos = pos;
		ThreadUnlock();
		return retval;
	}

	long CommentPos() 
	{
		long retval;
		ThreadLock();
		retval = m_cPos;
		ThreadUnlock();
		return retval;
	}

	long CommentPos(long pos)
	{
		long retval;
		ThreadLock();
		retval = m_cPos = pos;
		ThreadUnlock();
		return retval;
	}

	long QuotePos() 
	{
		long retval;
		ThreadLock();
		retval = m_qPos;
		ThreadUnlock();
		return retval;
	}

	long QuotePos(long pos)
	{
		long retval;
		ThreadLock();
		retval = m_qPos = pos;
		ThreadUnlock();
		return retval;
	}

	long GetLength()
	{
		ThreadLock();
		long retval = CStringEx::GetLength();
		ThreadUnlock();
		return retval;
	}

	// Assignement operators
	CColorString& operator=(const CString& rhs);
	CColorString& operator=(const CStringEx& rhs);
	CColorString& operator=(TCHAR ch);
	CColorString& operator=(LPCSTR lpsz);
	CColorString& operator=(LPCWSTR lpsz);
	CColorString& operator=(const unsigned char* psz);

	// string concatenation
	CColorString& operator+=(const CString& string);
	CColorString& operator+=(TCHAR ch);
	CColorString& operator+=(LPCTSTR lpsz);
	CColorString& Insert(int pos, LPCTSTR s);
	CColorString& Insert(int pos, TCHAR c);
	CColorString& Delete(int pos, int len);
	CColorString& Replace(int pos, int len, LPCTSTR s);
	void SetAt(int nIndex, TCHAR ch);

	// Access String Info
	CString GetLine(long index);
	long GetLineCount();
	long GetLineOffset(long index);
	long Offset2Line(long pos);

	// Change Bracketing
	virtual void BeginUpdate(long pos = 0, long len = 1);
	virtual void EndUpdate(long pos = 0, long len = 1);

	// Update
	void AddUpdateTarget(CColorStringUpdate* update);
	void DoUpdate(BOOL bDataChangedFlag = TRUE);

	// Color Coding
	BOOL AddKeyword(const CString& keyword, COLORREF color = RGB(0, 0, 200));
	BOOL AddComment(const CString& begin = _T("//"), const CString& end = _T("\n"), COLORREF color = RGB(0, 200, 0));
	
	// Color Access
	COLORREF GetColor(long index);

	// Parsing and Lookup
	long GetComment(const CString& beginToken, const CString& endToken, long& commentLen, long pos);
	CKeywordInfo* KeywordLookup(const CString& token);
	long GetToken(CString& token, long pos, BOOL bCharOnly = TRUE);
	
	// Background Color Processing
	void Reset(long pos = 0);
	BOOL ParseComments(CColorArray& color);
	BOOL ParseKeywords(CColorArray& color);
	BOOL ParseQuotes(CColorArray& color);
	void Process(long pos = 0);	
	void SetDefaults(COLORREF color = RGB(0, 0, 0), COLORREF sQuoteColor = RGB(0, 0,0), COLORREF dQuoteColor = RGB(0, 0, 0));
	
	friend UINT AFX_CDECL CColorStringBkgThread(LPVOID object);
};


#endif