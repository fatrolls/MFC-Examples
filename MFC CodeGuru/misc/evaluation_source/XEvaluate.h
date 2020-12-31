/*****************************************************************************
 *
 * Autor:			Joachim Raidl
 * Adresse:			Joachim.Raidl@iname.com
 * Klasse:			XEvaluate
 * Inlines:			Error(), ValPush(), OpPush(), TxtPush(), ValPop(), 
 *					ValTop(), OpPop(), OpTop(), TxtPop(), TxtTop(), fak(), 
 *
 ****************************************************************************/

#ifndef __XEVALUATE__
#define __XEVALUATE__

#include <afxtempl.h>
#include "XString.h"
#include "math.h"
#include "float.h"

typedef CMap<CString, LPCTSTR, CString, LPCTSTR>	XStringMap;
typedef CMap<CString, LPCTSTR, double,	double>		XDoubleMap;
typedef CMap<CString, LPCTSTR, int,		int>		XIntMap;
typedef CList<int, int>								XIntList;
typedef CList<double, double>						XDoubleList;
typedef CList<CString, LPCTSTR>						XStringList;

const double PI	= 3.14159265358979323846;
const double e	= 2.7182818284590452354;

class XEvaluate
{
private:
	#define OP(a, b, c, d)	MAKELONG(MAKEWORD(a, b), MAKEWORD(c, d))

	//========================================================================
	// Die enum-Elemente wurden so gewählt, daß sie zum Test mit ENUMSTR als
	// Strings ausgegeben werden können. So kann zum Beipsiel mit
	//
	// afxDump << ENUMSTR(SIN) << ", " << ENUMSTR(MUL) << ", " << ENUMSTR(GE)
	//
	// auch wirklich der Text "sin, *, >=" angezeigt werden.
	//========================================================================
	enum {	ADD = '+', SUB = '-', MUL = '*', DIV = '/',
			MOD = '%', AND = '&', OR  = '|', XOR = '^',
			LT  = '<', GT  = '>', SET = '=', NOT = '!',
			NOTB= '~', DP  = ':', SQR = '²', EXP = 'e',
			DEC = 'd', BIN = 'b', HEX = 'h', CHR = 'c',	// 123, 1100b, 0x12, 'a
			RAD = 'r', DEG = '°', GON = 'g', FIX = 'f',
			CUBE= '³', NOP = '0',
			EQ		= OP('=', '=', ' ', ' '),	NEQ		= OP('!', '=', ' ', ' '),
			LE		= OP('<', '=', ' ', ' '),	GE		= OP('>', '=', ' ', ' '),
			ADDEQ	= OP('+', '=', ' ', ' '),	SUBEQ	= OP('-', '=', ' ', ' '),
			MULEQ	= OP('*', '=', ' ', ' '),	DIVEQ	= OP('/', '=', ' ', ' '),
			NEG		= OP('-', '-', ' ', ' '),
			SIN		= OP('s', 'i', 'n', ' '),	COS		= OP('c', 'o', 's', ' '),
			TAN		= OP('t', 'a', 'n', ' '),	ASIN	= OP('a', 's', 'i', 'n'),
			ACOS	= OP('a', 'c', 'o', 's'),	ATAN	= OP('a', 't', 'a', 'n'),
			ABS		= OP('a', 'b', 's', ' '),	INT		= OP('i', 'n', 't', ' '),
			FRACT	= OP('f', 'r', 'a', 'c'),	SQRT	= OP('s', 'q', 'r', 't'),
			LN		= OP('l', 'n', ' ', ' '),	LOG		= OP('l', 'o', 'g', ' '),
			LOG10	= OP('1', '0', ' ', ' '),	POW		= OP('p', 'o', 'w', ' '),
			FAK		= OP('f', 'a', 'k', ' '),
			USRFN	= OP('(', ')', ' ', ' '),	SETFN	= OP(':', '=', ' ', ' '),
			ERR		= OP('E', 'r', 'r', ' '),
			STOP	= OP('S', 't', 'o', 'p'),
		};

	#define ENUMSTR(oper)	(XString((char) LOBYTE(LOWORD(oper))) + XString((char) HIBYTE(LOWORD(oper))) + \
							 XString((char) LOBYTE(HIWORD(oper))) + XString((char) HIBYTE(HIWORD(oper))))

// Variable
protected:
	XIntList		op;			// Stack der Operatoren
	XDoubleList		val;		// Stack der Operanden
	XStringList		txt;		// Stack der Variablennamen
	XStringMap		usrfn;		// Benutzerdefinierte Funktionen
	XDoubleMap		var;		// Interne Variable für Zwischenrechnungen
	XDoubleMap		*extVar;	// Externe Variable für Zwischenrechnungen
	XIntMap			fkt;		// Map der Funktionen und den zugeordneten Operatoren
	XString			err;		// Fehlervariable
	int				komma;		// Anzahl der Nachkommastellen
	double			oldValue;	// Wert der letzten Berechnung (für @)
	int				out;		// Zahlensystem für Ausgabe
	int				modus;		// Modus für Trigonometrische Funktionen
	bool			valFlag;	// Wurde ein Wert auf den Stack gesetzt?
	bool			oldValFlag;	// = valFlag der vorherigen Schleife

protected:
	double	ToRad(double x);
	double	ToMod(double x);
	double	Dec(const XString& val);
	XString Bin(int val, int len = -1);
	XString Hex(int val, int len = -1);
	XString Help();
	XString Reset();
	XString Status();
	XString VarList();
	XString SetFunction(const XString& name, const XString& str);
	double	UseFunction(const XString& name, double x);
	bool	IsBinOp(int oper);

	bool	TestError();

#define VALERR		DBL_MAX
#define OPERR		ERR
#define TXTERR		"+ERR+"

// Inlines
protected:

	bool	Error(LPCTSTR text)		{ err = "Syntax Error: "; err += text; return false; }

	void	ValPush(double x)		{ val.AddHead(x); valFlag = true;		}
	void	OpPush(int oper)		{ op.AddHead(oper);						}
	void	TxtPush(LPCTSTR var)	{ txt.AddHead(var);						}

	double	ValPop()				{ return (val.IsEmpty() ? VALERR : val.RemoveHead());	}
	double	ValTop()				{ return (val.IsEmpty() ? VALERR : val.GetHead());		}

	int		OpPop()					{ return (op.IsEmpty()  ? OPERR  : op.RemoveHead());	}
	int		OpTop()					{ return (op.IsEmpty()  ? OPERR  : op.GetHead());		}
	
	XString	TxtPop()				{ return (txt.IsEmpty() ? TXTERR : txt.RemoveHead());	}
	XString	TxtTop()				{ return (txt.IsEmpty() ? TXTERR : txt.GetHead());		}

	double	fak(double x)			{ for (double ret = 1; x > 0; ret *= x--); return ret; }

public:
	XEvaluate();
	XString Calc(LPCTSTR formel, XDoubleMap *extVar = NULL);
};

extern XEvaluate eval;

inline XString Evaluate(LPCTSTR formel, XDoubleMap *extVar = NULL)
{
	return eval.Calc(formel, extVar);
}

#endif // __XEVALUATE__