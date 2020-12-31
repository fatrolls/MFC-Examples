/*******************************************************************************
 *
 * Autor:			Joachim Raidl
 * Adresse:			Joachim.Raidl@iname.com
 * Klasse:			XString
 * Files:			XString.cpp, XString.h
 * Beschreibung:	Die Klasse XString stellt eine Erweiterung der Klasse
 *					CString dar. Neben den Standardfunktionen werden zusätzlich
 *					Funktionen für Element-Strings zur Verfügung gestellt.
 *					Elementstrings zeichnen sich dadurch aus, daß sie mehrere
 *					Werte durch einen Separator getrennt enthalten. So kann zum
 *					Beispiel aus dem Elementstring "012|345|678|901" jedes
 *					Element für sich gelesen und überschrieben werden.
 * Operatoren:		operator char*, operator const char*, operator CString,
 *					operator--, operator!
 * Funktionen:		Double(), Int(), Remove(), RemoveAll(), Insert(), Replace(),
 *					ReplaceAll(), Reverse(), Trim(), Lower(), Upper(), Fill(),
 *					ReplaceTabs(), Count(), FindIndex(), ReplaceText(),
 *					NCFind(), NCReplace(), NCReplaceAll(), NCRemove(),
 *					NCRemoveAll(),
 * Element-Fkt.:	SetSeparator(), RestoreSeparator(), Element(), operator(),
 *					Elements(), GetString(), GetDouble(), GetInt(), GetChar(),
 *					Get(), SetElement(), ElementIndex(), ElementSortString(),
 *					ElementSortDouble(), ElementSortChar(), ElementSortInt(),
 *					ElementSort(), SerializeElements(),
 * Friends:			itoa(), utoa(), dtoa(), Repeat(), Concat(),
 *					GetStringTableEntry(), GetDoubleFormatString(),
 *
 ******************************************************************************/

#include "StdAfx.H"
#include "XString.H"
#include <CType.H>

#ifdef _DEBUG
#define new DEBUG_NEW
#include "NoDump.h"
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char	XString::SEP	= '|';			// Trennzeichen für Element-Strings
char	XString::OLDSEP	= '|';			// Trennzeichen für Element-Strings
XString STRERROR = ">>> ERROR <<<";		// Fehlerstring für alle Klassen

/*****************************************************************************
 * Klasse:		XString
 * Funktion:	NCFind
 * Parameter:	s		Suchstring
 *				c		Suchzeichen
 * Return:		int		Erste gefundene Position des Suchtextes
 * Beispiel:	XString("Test TEST").Find("E")		==> 6
 *				XString("Test TEST").NCFind("E")	==> 1
 *
 * Die Funktion NCFind arbeitet wie alle nachfolgenden NC-Funktion im
 * Case-Unsensitiven Fall, daß heißt, sie berücksichtigt keine Groß-/Klein-
 * schreibung. Ansonsten arbeitet die Funktion genau wie Find.
 ****************************************************************************/
int XString::NCFind(const XString& s) const
{
	XString copy = this->Upper();

	return copy.Find(s.Upper());
}

int XString::NCFind(char c) const
{
	XString copy = this->Upper();

	return copy.Find((char) toupper(c));
}

/*****************************************************************************
 * Klasse:		XString
 * Funktion:	Remove, NCRemove
 * Parameter:	von, bis		Löschbereich
 *				s				Löschstring
 *				c				Löschzeichen
 * Return:		Ergebnisstring
 * Beispiel:	XString("0123456789").Remove(1, 3)		==> "0456789"
 *				XString("0123456789").Remove("345")		==> "0126789"
 *				XString("0123456789").Remove('4')		==> "012356789"
 *				XString("Test  Test").NCRemove("E")		==> "Tst  Test"
 *
 * Löscht einen bestimmten Teil aus dem String. Hierbei kann wahlweise ein
 * Bereich (von, bi), ein String (s) oder ein einzelnes Zeichen (c) gelöscht
 * werden.
 ****************************************************************************/
XString XString::Remove(int von, int bis) const
{
	if (bis < 0)					bis = von;

	if ((von < 0) || (bis < von))	return *this;
	else							return Left(von) + Mid(bis);
}

XString XString::Remove(const XString& s) const
{
	int i = Find(s);

	if (i >= 0)	return Left(i) + Mid(i + s.GetLength());
	else		return *this;
}

XString XString::Remove(char c) const
{
	int i = Find(c);

	if (i >= 0)	return Left(i) + Mid(i+1);
	else		return *this;
}

XString	XString::NCRemove(const XString& s) const
{
	int i = NCFind(s);

	if (i >= 0)	return Left(i) + Mid(i + s.GetLength());
	else		return *this;
}

XString	XString::NCRemove(char c) const
{
	int i = NCFind(c);

	if (i >= 0)	return Left(i) + Mid(i+1);
	else		return *this;
}

/*****************************************************************************
 * Klasse:		XString
 * Funktion:	RemoveAll, NCRemoveAll
 * Parameter:	s				Löschstring
 *				c				Löschzeichen
 * Return:		Ergebnisstring
 * Beispiel:	XString("01234567890123456789").RemoveAll("34567")
 *					==> "0128901289"
 *				XString("Test TEST").NCRemoveAll("e")	==> "Tst TST"
 *
 * Löscht jedes Auftreten einse String (s) oder eines Zeichens (c) as einem
 * String.
 ****************************************************************************/
XString XString::RemoveAll(const XString& s) const
{
	XString hilf = *this;

	while (hilf.Find(s) >= 0)	hilf = hilf.Remove(s);
	return hilf;
}

XString XString::RemoveAll(char c) const
{
	XString hilf = *this;

	while (hilf.Find(c) >= 0)	hilf = hilf.Remove(c);
	return hilf;
}

XString XString::NCRemoveAll(const XString& s) const
{
	XString hilf = *this;

	while (hilf.NCFind(s) >= 0)	hilf = hilf.NCRemove(s);
	return hilf;
}

XString XString::NCRemoveAll(char c) const
{
	XString hilf = *this;

	while (hilf.NCFind(c) >= 0)	hilf = hilf.NCRemove(c);
	return hilf;
}

/*****************************************************************************
 * Klasse:		XString
 * Funktion:	Insert
 * Parameter:	s				Einfügestring
 *				at				Einfügeposition
 *				c				Löschzeichen
 * Return:		Ergebnisstring
 * Beispiel:	XString("0123456789").Insert("xx", 3)	==> "012xx3456789"
 *
 * Fügt einen String in den aktellen String ein.
 ****************************************************************************/
XString XString::Insert(const XString& s, int at) const
{
	if ((at <= GetLength()) && (at >= 0))	return Left(at) + s + Mid(at);
	else									return *this;
}

/*****************************************************************************
 * Klasse:		XString
 * Funktion:	Replace, NCReplace
 * Parameter:	s				Ersatzstring
 *				search			Suchstring
 *				von, bis		Ersatzbereich
 * Return:		Ergebnisstring
 * Beispiel:	XString("0123456789").Replace("xx", "345")	==> "012xx6789"
 *				XString("0123456789").Replace("xx", 1, 6)	==> "0xx789"
 *				XString("List LIST").NCReplace("I", "a")	==> "Last LIST"
 *
 * Ersetzt einen Teil-String (search) oder ein Bereich (von, bis) durch
 * einen neuen String.
 ****************************************************************************/
XString XString::Replace(const XString& s, const XString& search) const
{
	int i = Find(search);
	return Remove(search).Insert(s, i);
}

XString	XString::Replace(const XString& s, int von, int bis) const
{
	return Remove(von, bis).Insert(s, von);
}

XString XString::NCReplace(const XString& s, const XString& search) const
{
	int i = NCFind(search);
	return NCRemove(search).Insert(s, i);
}

/*****************************************************************************
 * Klasse:		XString
 * Funktion:	ReplaceAll, NCReplaceAll
 * Parameter:	s				Ersatzstring
 *				search			Suchstring
 * Return:		Anzahl der Ersetzungen
 * Beispiel:	XString("0123401234").Replace("xx", "34")	==> "012xx012xx"
 *				XString("List LIST").NCReplaceAll("I", "a")	==> "Last LaST"
 *
 * Ersetzt einen jedes Auftreten des Suchstrings durch den Ersatzstring. Bei
 * der NC-Version werden nicht die entsprechenden NC-Funktionen von Find und
 * Replace benutzt, da dies zu viele Konversionen nach sich ziehen würde.
 * Statt dessen wird der String als Kopie nur einmal konvertiert und dann
 * der Originalstring und die Groß-Kopie parallel gehandelt.
 ****************************************************************************/
int XString::ReplaceAll(const XString& s, const XString& search)
{
	XString aktString = *this;
	this->Empty();

	int len = search.GetLength();
	for (int pos = aktString.Find(search), i = 0; pos >= 0; pos = aktString.Find(search))
	{
		*this		+= aktString.Left(pos) + s;
		aktString	= aktString.Mid(pos + len);
		i++;
	}

	*this += aktString;

	return i;
}

int XString::NCReplaceAll(const XString& s, const XString& search)
{
	XString aktString = *this;
	this->Empty();

	XString AktString	= aktString.Upper();	// Groß-Version von aktString
	XString Search		= search.Upper();		// Groß-Version von search

	int len = Search.GetLength();
	for (int pos = AktString.Find(Search), i = 0; pos >= 0; pos = AktString.Find(Search))
	{
		*this		+= aktString.Left(pos) + s;
		aktString	= aktString.Mid(pos + len);
		AktString	= AktString.Mid(pos + len);
		i++;
	}

	*this += aktString;

	return i;
}

/*****************************************************************************
 * Klasse:		XString
 * Funktion:	ReplaceText
 * Parameter:	replace			Ersatz-Element-String
 * Return:		Ergebnisstring
 * Beipsiel:	XString("Das File * ist * Byte lang").ReplaceText("Test|100")
 *				==> "Das File Test ist 100 Byte lang"
 *
 * Ersetzt alle '*' durch die übergebenen Werte des Elementstrings 'replace'.
 * Die einzelnen Ersatzstring sind durch '|' voneinander zu trennen.
 ****************************************************************************/
XString XString::ReplaceText(const XString& replace) const
{
	XString erg = *this;
	XString rep;
	for (int i = 0; !!(rep = replace.GetString(i)); i++)
		if (erg.Find("*") >= 0)
			erg = erg.Replace(rep, "*");

	erg.ReplaceAll("*", "§");

	return erg;
}

/*****************************************************************************
 * Klasse:		XString
 * Funktion:	Count
 * Parameter:	c			Zählzeichen
 *				str			Zählstring
 * Return:		Anzahl der Zeichen im String
 * Beipsiel:	XString("123412341234").Count('1')	==> 3
 *				XString("123412341234").Count("41")	==> 2
 *
 * Zählt das Auftreten von c im String.
 ****************************************************************************/
int XString::Count(char c) const
{
	int anz = 0;
	for (int i = 0, l = GetLength(); i < l; i++)
		if (m_pchData[i] == c) anz++;

	return anz;
}

int XString::Count(const XString& str) const
{
	int anz = 0, p, l = str.GetLength();
	XString copy = *this;
	while ((p = copy.Find(str)) >= 0)
	{
		anz++;
		copy = copy.Mid(p + l);
	}

	return anz;
}

/*****************************************************************************
 * Klasse:		XString
 * Funktion:	Fill
 * Parameter:	n			Neue Länge
 * Return:		Ergebnisstring
 * Beipsiel:	XString("12345").Fill(10)	==> "12345     "
 *
 * Füllt den String mit Leerzeichen auf, sodaß er aus n Zeichen besteht.
 ****************************************************************************/
XString XString::Fill(int n) const
{
	XString erg = *this;
	for (int i = GetLength(); i < n; i++) erg += ' ';

	return erg;
}

/*****************************************************************************
 * Klasse:		XString
 * Funktion:	ReplaceTabs
 * Parameter:	abstand			Tablatorabstand
 * Return:		String ohne Tabulatorzeichen
 * Beispiel:	str = "Blank\tEinfügen";
 *				ReplaceTabs(str, 4)		==>	"Blank   einfügen"
 *
 * Ersetzt alle Tabulatoren innerhalb des Strings durch entsprechend viele
 * Leerzeichen und gibt diesen dann zurück. Hierbei werden die Leerzeichen
 * so eingefügt, daß die Position des darauffolgenden Textes mit der
 * vorherigen übereinstimmt. Bei einem Tabulatorabstand von 4 kann ein Text,
 * der einem Tabulatorzeichen folgt immer nur bei der Position 4, 8, 12, ...
 * erscheinen.
 ****************************************************************************/
XString XString::ReplaceTabs(int abstand) const
{
	XString erg = *this;
	int i;
	while ((i = erg.Find('\t')) >= 0)
		erg = erg.Left(i) + Repeat(' ', abstand - i % abstand) + erg.Mid(i + 1);

	return erg;
}

/*****************************************************************************
 * Klasse:		XString
 * Funktion:	FindIndex
 * Parameter:	c			Suchzeichen
 *				pos			Suchposition
 * Return:		Position des i-ten Auftauchens von c wenn es existiert,
 *				-1 sonst
 * Beipsiel:	XString("0|1|2|3|4|5|6").FindIndex('|', 5)	==> 9
 *							      ^
 *				XString("0|1|2|3|4|5|6").FindIndex('|', 11)	==> -1
 *
 * Gibt den Index des i-ten Auftauchens des Zeichens c zurück.
 ****************************************************************************/
int XString::FindIndex(char c, int pos) const
{
	if (!pos)	return 0;

	for (int i=0, l=GetLength(); (i < l) && pos; i++)
		if (m_pchData[i] == c) pos--;

	int erg;
	if (!pos)	erg = i-1;
	else		erg = -1;

	return erg;
}

/*****************************************************************************
 * Klasse:		XString
 * Funktion:	operator(), Element, Elements
 * Parameter:	i			Position
 *				von, bis	Bereich
 *				sep			Separator
 * Return:		i-tes Element bzw. (von-bis)-Elemente des Strings
 * Beispiele:	XString str	= "0|1|2|3"
 * 				str(1)			= str.Element(1)	==> "1"
 *				str(5)			= str.GetString(5)	==> ""
 *				str.GetDouble(1)					==> 1.0
 *				str.GetInt(0)						==> 0
 *				str.GetChar(3)						==> '3'
 * 				str(1, 2)		= str.Elements(1,2)	==> "1|2"
 *				str(2, -1)		= str.Elements(2)	==> "2|3"
 *				XString("0, 1, 2, 3).Element(2,',')	==> "2"
 *
 * Der Funktions-Operator '()' gibt ein Element eines Element-Strings zurück.
 * Ein Element-String ist ein String mit mehreren durch ein Separator getrennte
 * Elemente. Je nach Übergabeparameter kann ein einzelnes Element oder eine
 * Teil-Elementstring zurückgegeben werden. Es existieren mehrere Overloads für
 * diese Funktion:
 *
 *		(i)				i-tes Element als String
 *		Element(i)		i-tes Element als String
 *		Element(i, c)	i-tes Element. Als Trenner wird c benutzt
 *		(i, j)			Elementstring mit den Elementen i bis j
 *		Elements(i, j)	Elementstring mit den Elementen i bis j
 *		(i, -1)			Elementstring mit allen Elementen ab dem i-ten Element
 *		Elements(i, -1)	Elementstring mit allen Elementen ab dem i-ten Element
 *
 *		String(i)		i-tes Element als String
 *		Double(i)		i-tes Element als Double
 *		Int(i)			i-tes Element als Int
 *		Char(i)			i-tes Element als Char
 ****************************************************************************/
XString XString::Element(int i, char sep) const
{
	char tempSep = SEP;
	SEP = sep;
	XString erg = Elements(i, i);
	SEP = tempSep;

	return erg;
}

XString XString::Elements(int von, int bis) const
{
	if (bis < 0) bis = Count(SEP);	// Rest ab von
	bis += 1 - von;					// bis = bis - von + 1

	if (von <  0) return "";		// Falscher Parameter von
	if (bis <  0) return "";		// Falscher Parameter bis < von 

	int	len = GetLength();			// Länge des aktuellen Strings
	XString copy = *this;			// Copy des aktuellen Strings

	for (int v = 0;	(v < len) && von; v++) if (copy[v] == SEP) von--;
	for (int b = v;	(b < len) && bis; b++) if (copy[b] == SEP) bis--;
	if ((b > 0) && !((b == len) && bis)) b--;

	XString erg;
	if (v >= len)		erg = Repeat(SEP, --bis);
	else if (b == 0)	erg = "";
	else if (b < len)	erg = copy.Mid(v, b - v); 
	else				erg = copy.Mid(v) + Repeat(SEP, --bis);

	return erg;
}

XString XString::Elements(int von, int bis, char sep) const
{
	char tempSep = SEP;
	SEP = sep;
	XString erg = Elements(von, bis);
	SEP = tempSep;

	return erg;
}

/*****************************************************************************
 * Klasse:		XString
 * Funktion:	SetElement
 * Parameter:	pos			Suchposition
 *				rep			Ersatzstring, -int, -double
 * Return:		String mit ersetzem Wert
 * Beipsiel:	str = "1|2|3"
 *				str.SetElement(1, "99")	==> "1|99|3"
 *				str.SetElement(5, "99")	==> "1|2|3|||99"
 *				str.SetElement(1)		==> "1||3"
 *				str.SetElement(2, 75)	==> "1|2|75"
 *				str.SetElement(1, 1.23)	==> "1|1.23|3"
 *
 * Ersetzt in einem Elemente-String den i-ten Eintrag. Wenn der Eintrag nicht
 * existiert, wird er automatisch generiert. Defaultmäßig wird der Replace-
 * String durch "" repäsentiert, was einem Löschen des i-ten Elements ent-
 * spricht. Alternativ kann auch ein double- oder int-Wert übergeben werden.
 ****************************************************************************/
XString XString::SetElement(int pos, const XString& rep) const
{
	if (pos < 0)	return *this;

	int n = GetLength();
	int s = Count(SEP);

	if (s < pos) return (*this + Repeat(SEP, pos - s) + rep);

	for (int von = 0;	pos;	 von++)	if (m_pchData[von] == SEP) pos--;
	for (int bis = von; bis < n; bis++)	if (m_pchData[bis] == SEP) break;

	if (bis < von)	return Insert(rep, von);
	else			return Replace(rep, von, bis);
}

/*****************************************************************************
 * Klasse:		XString
 * Funktion:	ElementIndex
 * Parameter:	such		Suchstring
 * Return:		Elementposition des Suchstrings, wenn er gefunden wurde,
 *				-1 sonst
 * Beipsiel:	str = "0|1|2|3"
 *	 			str.ElementIndex("2")	==> 2
 *				str.ElementIndex("5")	==> -1
 *				str.ElementIndex(1.0)	==> 1
 *				str.ElementIndex(3)		==> 3
 *
 * Liefert den Index eines Eintrags in einer Element-Liste zurück. Bei der
 * Übergabe von int- oder double-Werten, werden die Werte überprüft und nicht
 * die Strings. So wird der Eintrag "3.0" auch dann gefunden, wenn nach 3
 * gesucht wird.
 ****************************************************************************/
int XString::ElementIndex(const XString& such) const
{
	for (int j=0; j<=Count(SEP); j++) if (GetString(j) == such) return j;
	return -1;
}

int XString::ElementIndex(double such) const
{
	for (int j=0; j<=Count(SEP); j++) if (GetDouble(j) == such) return j;
	return -1;
}

int XString::ElementIndex(int such) const
{
	for (int j=0; j<=Count(SEP); j++) if (GetInt(j) == such) return j;
	return -1;
}

int XString::ElementIndex(char such) const
{
	for (int j=0; j<=Count(SEP); j++) if (GetChar(j) == such) return j;
	return -1;
}

int XString::ElementIndex(bool such) const
{
	for (int j=0; j<=Count(SEP); j++) if (GetBool(j) == such) return j;
	return -1;
}

/*****************************************************************************
 * Klasse:		XString
 * Funktion:	ElementSortString, ElementSortDouble, ElementSortInt,
 *				ElementSortChar
 *				(template<>Sort, compString, compDouble, compInt, compChar)
 * Parameter:	-
 * Return:		Sortierter Element-String
 * Beipsiel:	XString("9|3|1").ElementSortString()		==>	"1|3|9"
 *				XString("4|4.3|3.9").ElementSortDouble()	==>	"3.9|4|4.3"
 *
 * Sortiert die Elemente eines Element-Strings nach dem angegebenen Typ in
 * aufsteigender Reihenfolge. Hierzu wird das Template 'Sort' definiert, daß
 * nurstatisch in diesem File definiert ist.
 *
 * Zum Sortieren des Strings werden zuerst die Elemente in ein Array übertragen
 * und dann mittels der Library-Funktion 'qsort' sortiert. Für jeden Typ steht
 * hierfür eine spezielle Vergleichsfunktion 'compTyp' zur Verfügung, die
 * ebenfalls nur statisch in diesem File definiert ist.
 ****************************************************************************/
int compString(XString *a, XString *b)	{ return a->Compare(*b); }
int compDouble(double *a, double *b)	{ return ((*a == *b) ? 0 : ((*a > *b) ? 1 : -1)); }
int compChar(char *a, char *b)			{ return ((*a == *b) ? 0 : ((*a > *b) ? 1 : -1)); }
int compInt(int *a, int *b)				{ return ((*a == *b) ? 0 : ((*a > *b) ? 1 : -1)); }

template<class Typ> XString Sort(Typ, const XString& str, int (*comp)(const void *a, const void *b))
{
	const int anz = str.Count(XString::SEP) + 1;	// Anzahl der Elemente
	Typ *ar = new Typ[anz];							// Array für die Elemente

	for (int i=0; i<anz; i++)	str.Get(ar[i], i);	// Array erzeugen
	qsort(ar, anz, sizeof(ar[0]), comp);			// Array sortieren

	XString ret = ar[0];							// Rückgabewert
	for (i=1; i<anz; i++) ret = Concat(ret, ar[i]);	// Elementstring aufbauen

	delete [] ar;									// Array löschen
	return ret;
}

#define CAST	int (*)(const void*, const void*)
XString XString::ElementSortString() const	{ return Sort((XString)0,	*this, (CAST)compString); }
XString XString::ElementSortDouble() const	{ return Sort((double)0,	*this, (CAST)compDouble); }
XString XString::ElementSortChar() const	{ return Sort((char)0,		*this, (CAST)compChar); }
XString XString::ElementSortInt() const		{ return Sort((int)0,		*this, (CAST)compInt); }
#undef CAST

/*****************************************************************************
 * Klasse:		XString
 * Funktion:	GetDoubleFormatString
 * Parameter:	-
 * Return:		Formatstring im C++-Format
 * Beipsiel:	XString("###.##").GetDoubleFormatString()	==>	"%6.2lf"
 *				XString("*****").GetDoubleFormatString()	==> "%5.0lf"
 *				GetDoubleFormatString("###.##")				==> "%6.2lf"
 *
 * Erzeugt einen C++-Formatstring (der in printf()- oder Format()-Funktionen
 * benutzt werden kann) aus einem Formatstring in Direkteingabe (also
 * Angabe der Stellen). Zusätzlich existiert noch eine friend-Version die
 * direkt den Formatstring als Parameter erhält.
 ****************************************************************************/
XString XString::GetDoubleFormatString() const
{
	int punktPosition = Find('.') + 1;
	int laenge = GetLength();
	if (punktPosition == 0) punktPosition = laenge;

	XString ret;
	ret.Format("%%%d.%dlf", laenge, laenge - punktPosition);

	return ret;
}

XString GetDoubleFormatString(const XString& str)
{
	return str.GetDoubleFormatString();
}

/*****************************************************************************
 * Klasse:		- (friend XString)
 * Funktion:	GetStringTableEntry
 * Parameter:	id		ID des Strings in der String-Table
 * Return:		Eintrag in der String-Table
 *
 * Mit dieser Funktion wird ein Eintrag aus der String-Table gelesen und
 * zurückgegeben
 ****************************************************************************/
XString GetStringTableEntry(UINT id)
{
	XString ret;
	ret.LoadString(id);
	return ret;
}

/*****************************************************************************
 * Klasse:		- (friend XString)
 * Funktion:	itoa, utoa, dtoa
 * Parameter:	i, u, d		Zahlenwert im jeweiligen Format
 *				n			Anzahl der Nachkommastellen
 * Return:		Formatierter XString
 * Beipsiel:	itoa(5)			==> "5"
 *				dtoa(3.72)		==> "3.72"
 *				dtoa(3.72, 1)	==> "3.7"
 *
 * Wandelt eine Zahl vom Typ int, unsigned oder double in einen XString um
 ****************************************************************************/
XString itoa(int i)				{ XString h; h.Format("%d", i); return h; }
XString utoa(UINT u)			{ XString h; h.Format("%u", u); return h; }
XString dtoa(double d)			{ XString h; h.Format("%g", d); return h; }
XString dtoa(double d, int n)	{ XString h; h.Format("%.*f", n, d); return h; }

/*****************************************************************************
 * Klasse:		- (friend XString)
 * Funktion:	Repeat
 * Parameter:	c		Zu wiederholendes Zeichen
 *				str		Zu wiederholende Zeichenkette
 *				n		Anzahl der Wiederholungen
 * Return:		Formatierter String
 * Beipsiel:	Repeat('*', 5)	==> "*****"
 *				Repeat('#', 0)	==> ""
 *				Repeat("01", 5)	==> "0101010101"
 *
 * Erzeugt einen String aus mehreren Wiederholungen eines Zeichens oder
 * eines Strings.
 ****************************************************************************/
XString Repeat(char c, int n)
{
	XString erg(c, n);

	return erg;
}

XString Repeat(const XString& str, int n)
{
	for (XString ret; n > 0; n--)
		ret += str;

	return ret;
}

/*****************************************************************************
 * Klasse:		- (friend XString)
 * Funktion:	Concat
 * Parameter:	a, b, .., h
 * Return:		Zusammengesetzter Element-String
 * Beipsiel:	Concat("alpha", "beta", "gamma")	==> "alpha|beta|gamma"
 *
 * Verbindet Strings zu einem durch '|' getrennten Elemente-String. Die
 * Funktion kann mit bis zu 8 Elementen aufgerufen werden. Eine beliebige
 * Anzahl an Parametern mittels "..." ist nicht möglich, da XString kein
 * skalarer Typ ist. Dies wäre nur mit char* möglich, dann müssten aber alle
 * Parameter explizit gecastet werden.
 ****************************************************************************/
#define S	XString::SEP

XString Concat(XS& a,XS& b)
	{ return (a+S+b); }

XString Concat(XS& a,XS& b,XS& c)
	{ return (a+S+b+S+c); }

XString Concat(XS& a,XS& b,XS& c,XS& d)
	{ return (a+S+b+S+c+S+d); }

XString Concat(XS& a,XS& b,XS& c,XS& d,XS& e)
	{ return (a+S+b+S+c+S+d+S+e); }

XString Concat(XS& a,XS& b,XS& c,XS& d,XS& e,XS& f)
	{ return (a+S+b+S+c+S+d+S+e+S+f); }

XString Concat(XS& a,XS& b,XS& c,XS& d,XS& e,XS& f,XS& g)
	{ return (a+S+b+S+c+S+d+S+e+S+f+S+g); }

XString Concat(XS& a,XS& b,XS& c,XS& d,XS& e,XS& f,XS& g,XS& h)
	{ return (a+S+b+S+c+S+d+S+e+S+f+S+g+S+h); }

XString Concat(XS& a,XS& b,XS& c,XS& d,XS& e,XS& f,XS& g,XS& h,XS& i)
	{ return (a+S+b+S+c+S+d+S+e+S+f+S+g+S+h+S+i); }

XString Concat(XS& a,XS& b,XS& c,XS& d,XS& e,XS& f,XS& g,XS& h,XS& i,XS& j)
	{ return (a+S+b+S+c+S+d+S+e+S+f+S+g+S+h+S+i+S+j); }

XString Concat(XS& a,XS& b,XS& c,XS& d,XS& e,XS& f,XS& g,XS& h,XS& i,XS& j,XS& k)
	{ return (a+S+b+S+c+S+d+S+e+S+f+S+g+S+h+S+i+S+j+S+k); }

XString Concat(XS& a,XS& b,XS& c,XS& d,XS& e,XS& f,XS& g,XS& h,XS& i,XS& j,XS& k,XS& l)
	{ return (a+S+b+S+c+S+d+S+e+S+f+S+g+S+h+S+i+S+j+S+k+S+l); }

XString Concat(XS& a,XS& b,XS& c,XS& d,XS& e,XS& f,XS& g,XS& h,XS& i,XS& j,XS& k,XS& l,XS& m)
	{ return (a+S+b+S+c+S+d+S+e+S+f+S+g+S+h+S+i+S+j+S+k+S+l+S+m); }

XString Concat(XS& a,XS& b,XS& c,XS& d,XS& e,XS& f,XS& g,XS& h,XS& i,XS& j,XS& k,XS& l,XS& m,XS& n)
	{ return (a+S+b+S+c+S+d+S+e+S+f+S+g+S+h+S+i+S+j+S+k+S+l+S+m+S+n); }

XString Concat(XS& a,XS& b,XS& c,XS& d,XS& e,XS& f,XS& g,XS& h,XS& i,XS& j,XS& k,XS& l,XS& m,XS& n,XS& o)
	{ return (a+S+b+S+c+S+d+S+e+S+f+S+g+S+h+S+i+S+j+S+k+S+l+S+m+S+n+S+o); }

XString Concat(XS& a,XS& b,XS& c,XS& d,XS& e,XS& f,XS& g,XS& h,XS& i,XS& j,XS& k,XS& l,XS& m,XS& n,XS& o,XS& p)
	{ return (a+S+b+S+c+S+d+S+e+S+f+S+g+S+h+S+i+S+j+S+k+S+l+S+m+S+n+S+o+S+p); }

#undef S

/****************************************************************************
 * Klasse:		-
 * Funktion:	SerializeElements
 * Parameter:	ar			Archiv, in das, bzw. von dem serialisiert wird
 *				pElements	Pointer auf ein oder mehrere Elemente
 *				nCount		Anzahl der zu serialisierenden Elemente
 * Return:		-
 *
 * Diese Funktion wird benötigt, wenn eine Template-Klasse serialisiert wird.
 * Für CMap-, CList- und CArray-Instatiierungen mit XString wird diese
 * Funktion aus der Serialize-Funktion der Template-Klasse heraus aufgerufen.
 ****************************************************************************/
void AFXAPI SerializeElements(CArchive& ar, XString* pElements, int nCount)
{
	ASSERT(nCount == 0 || AfxIsValidAddress(pElements, nCount * sizeof(XString)));

	if (ar.IsStoring())	for (; nCount--; ++pElements) ar << *pElements;
	else				for (; nCount--; ++pElements) ar >> *pElements;
}

