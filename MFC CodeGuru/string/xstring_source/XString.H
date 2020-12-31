/*****************************************************************************
 *
 * Autor:			Joachim Raidl
 * Adresse:			Joachim.Raidl@iname.com
 * Klasse:			XString
 * JRRC:			%J%
 *
 ****************************************************************************/

#ifndef __XSTRING__
#define __XSTRING__

class XString;

typedef const XString	XS;

class XString : public CString
{
//==============================================================================
// Konstruktoren
//==============================================================================
public:
	XString()							: CString()					{}
	XString(const XString& xstr)		: CString(xstr)				{}
	XString(const CString& cstr)		: CString(cstr)				{}
	XString(TCHAR c, int nRepeat = 1)	: CString(c, nRepeat)		{}
	XString(LPCTSTR lptstr, int nLength): CString(lptstr, nLength)	{}
	XString(const unsigned char* psz )	: CString(psz)				{}
	XString(LPCSTR lpstr )				: CString(lpstr)			{}
	XString(const int i)				: CString(itoa(i))			{}
	XString(const UINT u)				: CString(utoa(u))			{}
	XString(const double d)				: CString(dtoa(d))			{}
	XString(LPCWSTR lpwstr )			: CString(lpwstr)			{}

//==============================================================================
// Operatoren
//==============================================================================
public:
	operator CString () const			{ return *this; }

	XString	operator--()				{ *this = Left(GetLength() - 1); return *this; }
	XString	operator--(int)				{ XString copy(*this); *this = Left(GetLength() - 1); return copy; }
	int		operator!() const			{ return IsEmpty(); }

//==============================================================================
// Funktionen
//==============================================================================
public:
	double	Double() const				{ return atof(m_pchData); }
	int		Int() const					{ return atoi(m_pchData); }
	char	Char() const				{ return m_pchData[0]; }	// Kein Fehler bei Leerstring
	bool	Bool() const				{ return (Int() != 0); }

	XString	Remove(int von=0, int bis=-1) const;
	XString	Remove(const XString& s) const;
	XString	Remove(char c) const;

	XString	RemoveAll(const XString& s) const;
	XString	RemoveAll(char c) const;

	XString	Insert(const XString& s, int at=0) const;

	XString	Replace(const XString& s, int von=0, int bis=-1) const;
	XString	Replace(const XString& s, const XString& search) const;

	int		ReplaceAll(const XString& s, const XString& search);

	// NC... = NoCase... ==> Groﬂ-/Kleinschreibung wird nicht beachtet
	int		NCFind(const XString& s) const;
	int		NCFind(char c) const;

	XString	NCRemove(const XString& s) const;
	XString	NCRemove(char c) const;

	XString	NCRemoveAll(const XString& s) const;
	XString	NCRemoveAll(char c) const;

	XString	NCReplace(const XString& s, const XString& search) const;
	int		NCReplaceAll(const XString& s, const XString& search);

	XString	Reverse() const				{ XString copy = *this; copy.MakeReverse(); return copy; }

	XString	Trim() const				{ XString copy = *this; copy.TrimRight(); copy.TrimLeft(); return copy; }
	XString	Lower() const				{ XString copy = *this; copy.MakeLower(); return copy; }
	XString	Upper() const				{ XString copy = *this; copy.MakeUpper(); return copy; }                                       

	XString Left(int n) const			{ return CString::Left(n); }
	XString Mid(int i) const			{ return CString::Mid(i); }
	XString Mid(int i, int n) const		{ return CString::Mid(i, n); }
	XString Right(int n) const			{ return CString::Right(n); }

	XString	Fill(int n) const;
	XString	ReplaceTabs(int abstand = 4) const;

	int		Count(char c) const;
	int		Count(const XString& str) const;
	int		FindIndex(char c, int pos) const;
	XString	ReplaceText(const XString& replace) const;

	XString FromTo(int von, int bis)	{ return Mid(von, bis-von+1); }

//==============================================================================
// Funktionen auf Element-Strings
//==============================================================================
public:
	static	char SEP;
	static	char OLDSEP;
	static	char SetSeparator(char c)				{ OLDSEP = SEP; SEP = c; return SEP; }
	static	char RestoreSeparator()					{ SEP = OLDSEP; return SEP; }

	XString	Elements(int von, int bis = -1) const;
	XString	Elements(int von, int bis, char sep) const;
	XString	Element(int i) const					{ return Elements(i, i); }
	XString	Element(int i, char sep) const;

	XString	operator()(int i) const					{ return Elements(i, i); }
	XString	operator()(int von, int bis) const		{ return Elements(von, bis); }

	XString	GetString(int i) const					{ return Element(i); }
	double	GetDouble(int i) const					{ return Element(i).Double(); }
	char	GetChar(int i) const					{ return Element(i).Char(); }
	int		GetInt(int i) const						{ return Element(i).Int(); }
	bool	GetBool(int i) const					{ return Element(i).Bool(); }

	void	Get(XString& ret, int i) const			{ ret = GetString(i); }
	void	Get(double& ret, int i) const			{ ret = GetDouble(i); }
	void	Get(char& ret, int i) const				{ ret = GetChar(i); }
	void	Get(int& ret, int i) const				{ ret = GetInt(i); }
	void	Get(bool& ret, int i) const				{ ret = GetBool(i); }

	XString	GetString(int i, char sep) const		{ return Element(i, sep); }
	double	GetDouble(int i, char sep) const		{ return Element(i, sep).Double(); }
	char	GetChar(int i, char sep) const			{ return Element(i, sep).Char(); }
	int		GetInt(int i, char sep) const			{ return Element(i, sep).Int(); }
	bool	GetBool(int i, char sep) const			{ return Element(i, sep).Bool(); }

	XString	SetElement(int pos, const XString& rep) const;
	XString	SetElement(int pos, double rep) const	{ return SetElement(pos, dtoa(rep)); }
	XString	SetElement(int pos, char rep) const		{ return SetElement(pos, XString(rep)); }
	XString	SetElement(int pos, int rep) const		{ return SetElement(pos, itoa(rep)); }
	XString	SetElement(int pos, bool rep) const		{ return SetElement(pos, itoa((int) rep)); }

	int		ElementIndex(const XString& such) const;
	int		ElementIndex(double such) const;
	int		ElementIndex(int such) const;
	int		ElementIndex(char such) const;
	int		ElementIndex(bool such) const;

	XString	ElementSortString() const;
	XString	ElementSortChar() const;
	XString	ElementSortInt() const;
	XString	ElementSortDouble() const;
	XString ElementSort() const						{ return ElementSortString(); }

	XString GetDoubleFormatString() const;

public:
	friend	XString itoa(int i);
	friend	XString utoa(UINT u);
	friend	XString dtoa(double d);
	friend	XString dtoa(double d, int n);

	friend	XString Repeat(char c, int n);
	friend	XString Repeat(const XString& str, int n);
	friend	XString GetDoubleFormatString(const XString& str);
	friend	XString GetStringTableEntry(UINT id);

	friend	XString Concat(XS&,XS&);
	friend	XString Concat(XS&,XS&,XS&);
	friend	XString Concat(XS&,XS&,XS&,XS&);
	friend	XString Concat(XS&,XS&,XS&,XS&,XS&);
	friend	XString Concat(XS&,XS&,XS&,XS&,XS&,XS&);
	friend	XString Concat(XS&,XS&,XS&,XS&,XS&,XS&,XS&);
	friend	XString Concat(XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&);
	friend	XString Concat(XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&);
	friend	XString Concat(XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&);
	friend	XString Concat(XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&);
	friend	XString Concat(XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&);
	friend	XString Concat(XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&);
	friend	XString Concat(XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&);
	friend	XString Concat(XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&);
	friend	XString Concat(XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&,XS&);
};

void AFXAPI SerializeElements(CArchive& ar, XString* pElements, int nCount);

extern XString STRERROR;

#endif // __XSTRING__
