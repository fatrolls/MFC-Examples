/*****************************************************************************
 *
 * Autor:			Joachim Raidl
 * Adresse:			Joachim.Raidl@iname.com
 * Klasse:			XEvaluate
 * Files:			Evaluate.Cpp, Evaluate.H
 * Beschreibung:	Kurze Beschreibung der Klasse
 * Funktionen:		ToRad(), ToMod(), Dec(), Bin(), Hex(), Help(), Reset(), 
 *					Status(), VarList(), SetFunction(), UseFunction(), 
 *					TestError(), IsBinOp(), Calc(), 
 *
 ****************************************************************************/

#include "StdAfx.h"
#include "XEvaluate.h"
#include <math.h>

XEvaluate eval;

/*****************************************************************************
 * Klasse:		XEvaluate
 * Funktion:	XEvaluate
 * Parameter:	-
 * Return:		-
 *
 * Im Konstruktor wird die Liste der Funktionen erzeugt.
 ****************************************************************************/
XEvaluate::XEvaluate()
{
	komma	= -1;
	extVar	= NULL;
	Reset();

	fkt["sin"]	= SIN;		fkt["cos"]	= COS;		fkt["tan"]	= TAN;
	fkt["acos"]	= ACOS;		fkt["asin"]	= ASIN;		fkt["atan"]	= ATAN;

	fkt["dec"]	= DEC;		fkt["hex"]	= HEX;		fkt["bin"]	= BIN;	fkt["chr"]	= CHR;
	fkt["rad"]	= RAD;		fkt["deg"]	= DEG;		fkt["gon"]	= GON;

	fkt["pow"]	= POW;		fkt["sqr"]	= SQR;		fkt["sqrt"]	= SQRT;	
	fkt["exp"]	= EXP;		fkt["log"]	= LOG;		fkt["log10"]= LOG10;
	fkt["cube"]	= CUBE;

	fkt["abs"]	= ABS;		fkt["int"]	= INT;		fkt["fract"]= FRACT;
	fkt["fak"]	= FAK;		fkt["fix"]	= FIX;
}


/*****************************************************************************
 * Klasse:		XEvaluate
 * Funktion:	ToRad
 * Parameter:	x			Wert in Radian, Altgrad oder Neugrad
 * Return:		Wert in Radian
 *
 * Wandelt einen Werte vom aktuellen Kreismodus in Radian um.
 ****************************************************************************/
double XEvaluate::ToRad(double x)
{
	switch (modus)
	{
	case DEG:	return x * PI / 180;
	case GON:	return x * PI / 200;
	default:	return x;
	}
}

/*****************************************************************************
 * Klasse:		XEvaluate
 * Funktion:	ToMod
 * Parameter:	x			Wert in Radian
 * Return:		Wert in Radian, Altgrad oder Neugrad
 *
 * Wendelt einen Wert von Radian in einen Wert im aktuellen Kreismodus um.
 ****************************************************************************/
double XEvaluate::ToMod(double x)
{
	switch (modus)
	{
	case DEG:	return x * 180 / PI;
	case GON:	return x * 200 / PI;
	default:	return x;
	}
}

/*****************************************************************************
 * Klasse:		XEvaluate
 * Funktion:	Dec
 * Parameter:	val			Binär-, Dezimal- oder Hexadezimal-Wert als String
 * Return:		Wert als Double
 * Beispiel:	Dec("1001b")	==> 9
 *				Dec("0x80")		==> 128
 *				Dec("1234")		==> 1234
 *				Dec("12e3")		==> 12000
 *				Dec("12e-3")	==> 0.012
 *
 * Rechnet einen Wert in Stringdarstellung als Binär- (abschließendes 'b'),
 * Hexadezimal- (führendes '0x') oder Dezimalwert in einen Zahlenwer um.
 ****************************************************************************/
double XEvaluate::Dec(const XString& val)
{
	double ret = 0;
	int i, len = val.GetLength();

	if ((len > 2) && (val.Left(2) == "0x"))
		for (i = 2; i < len; i++)
			ret = 16 * ret + ((val[i] >= 'a') ? val[i] - 'a' + 10 : val[i] - '0');
	else if (val.Right(1) == "b")
		for (i = 0, len--; i < len; i++)
			ret = 2 * ret + ((val[i] == '1') ? 1 : 0);
	else
		ret = atof(val);

	return ret;
}

/*****************************************************************************
 * Klasse:		XEvaluate
 * Funktion:	Bin, Hex
 * Parameter:	val			Zahlenwert
 *				len			Minimale Länge des Binärwerts
 * Return:		Wert als Binär- oder Hexadezimalwert in Stringdarstellung
 * Beispiel:	Bin(9)		= "1001"
 *				Bin(9, 8)	= "00001001"
 *				Hex(128)	= "0x80"
 *				Hex(128, 4)	= "0x0080"
 *
 * Berechnet die Binär- bzw. Hexadezimaldarstellung eines Wertes und gibt
 * sie als String zurück.
 ****************************************************************************/
XString XEvaluate::Bin(int val, int len)
{
	ASSERT(len < 50);
	char hilf[50];
	if (len == -1)	return itoa(val, hilf, 2);

	itoa(val, hilf, 2);
	return Repeat('0', len - strlen(hilf)) + hilf;
}

XString XEvaluate::Hex(int val, int len)
{
	ASSERT(len < 50);
	char hilf[50];
	if (len == -1)	return XString("0x") + itoa(val, hilf, 16);

	itoa(val, hilf, 16);
	return "0x" + Repeat('0', len - strlen(hilf)) + hilf;
}

/*****************************************************************************
 * Klasse:		XEvaluate
 * Funktion:	Help
 * Parameter:	-
 * Return:		Hilfetext
 *
 * Diese Funktion erzeugt einen kurzen Hilfetext, der beschreibt, wie die
 * Klase arbeitet. Zusätzlich wird eine Lite mit allen verfügbaren Funktionen
 * zurückgegeben.
 ****************************************************************************/
XString XEvaluate::Help()
{
	XString ret =	"Evaluation    © by J. Raidl (10/1997)\n\n" \
					"Berechnen wie auf Papier.\n" \
					"Eingabe der gesamten Berechnungsformel:\n" \
					"1+2*pow(3,4)-sqr(abs(-2))  ==>  159\n\n" \
					"Variablenzuweisung (alpha = sin(pi/2))\n" \
					"Zahlensysteme (65 = 1000001b = 0x41 = \'A)\n" \
					"Benutzerfunktionen (sincos := sin(x)/cos(x))\n\n" \
					"Operatoren und Funktionen:\n" \
					"+  -  *  /  %  ~  !  &  |  ^  ==  !=  >  < \n" \
					">=  <=  =  +=  -=  *=  /=  $  #  @  §  ?\n";

	XString key;
	int		value;
	int		n = 0;
	for (POSITION pos = fkt.GetStartPosition(); pos; )
	{
		fkt.GetNextAssoc(pos, key, value);
		ret += key + " ";
		if ((++n % 10) == 0) ret += "\n";
	}

	return ret;
}

/*****************************************************************************
 * Klasse:		XEvaluate
 * Funktion:	Reset
 * Parameter:	-
 * Return:		"Reset"
 *
 * Mit dieser Funktion werden alle gespeicherten Variablen und Funktionen
 * gelöscht und der Ursprungszustand der Klasse wieder hergestellt.
 ****************************************************************************/
XString XEvaluate::Reset()
{
	var.RemoveAll();
	usrfn.RemoveAll();

	op.RemoveAll();
	val.RemoveAll();
	txt.RemoveAll();

	var["pi"]= PI;
	var["e"] = e;
	
	out = DEC;
	modus = RAD;
	
	return "Reset";
}

/*****************************************************************************
 * Klasse:		XEvaluate
 * Funktion:	Status
 * Parameter:	-
 * Return:		Aktuelle Status
 *
 * Gibt den Status des Berechnungsmoduls aus. Hierzu gehören die aktuelle
 * Anzahl der Nachkommastellen, der aktuelle Kreismodus und der aktuelle
 * Ausgabemodus
 ****************************************************************************/
XString XEvaluate::Status()
{
	XString ret = "FIX = " + itoa(komma) + "    ";

		 if (modus == DEG)	ret += "DEG";
	else if (modus == GON)	ret += "GON";
	else					ret += "RAD";

	ret += "    ";
		 if (out == BIN)	ret += "BIN";
	else if (out == HEX)	ret += "HEX";
	else if (out == CHR)	ret += "CHR";
	else					ret += "DEC";

	return ret;
}

/*****************************************************************************
 * Klasse:		XEvaluate
 * Funktion:	VarList
 * Parameter:	-
 * Return:		Variablen- und Funktionsliste
 *
 * Hier wird eine Liste aller internen und externen Variablen sowie aller
 * benutzerdefinierten Funktionen erzeugt.
 ****************************************************************************/
XString XEvaluate::VarList()
{
	XString ret;

	XString key;
	double	value;
	for (POSITION pos = var.GetStartPosition(); pos; )
	{
		var.GetNextAssoc(pos, key, value);
		ret += "[" + key + "] = ";
		if (komma >= 0)	ret += dtoa(value, komma);
		else			ret += dtoa(value);
		ret += "\n";
	}

	if (extVar)
		for (pos = extVar->GetStartPosition(); pos; )
		{
			extVar->GetNextAssoc(pos, key, value);
			ret += "[" + key + "] = ";
			if (komma >= 0)	ret += dtoa(value, komma);
			else			ret += dtoa(value);
			ret += "\n";
		}

	XString fkt;
	for (pos = usrfn.GetStartPosition(); pos; )
	{
		usrfn.GetNextAssoc(pos, key, fkt);
		ret += "[" + key + "] = " + fkt + "\n";
	}

	return ret;
}

/*****************************************************************************
 * Klasse:		XEvaluate
 * Funktion:	SetFunction
 * Parameter:	name		Funktionsname
 *				str			Funktionsbeschreibung
 * Return:		Funktionsname wenn Ok, sonst Fehlermeldung
 *
 * Definiert eine benutzerdefinierte Funktion und gibt deren Namen zurück.
 ****************************************************************************/
XString XEvaluate::SetFunction(const XString& name, const XString& str)
{
	if (str.Find('x') < 0)	{ Error("fn(x) = ..x.."); return err; }

	usrfn[name] = --XString(str);
	return name + " := " + usrfn[name];
}

/*****************************************************************************
 * Klasse:		XEvaluate
 * Funktion:	UseFunction
 * Parameter:	name		Funktionsname
 *				x			Wert für die Funktionsberechnung
 * Return:		Berechneter Funktionswert
 *
 * Berechnet eine Benutzerdefinierte Funktion.
 ****************************************************************************/
double XEvaluate::UseFunction(const XString& name, double x)
{
	double	buffer;
	BOOL	xExist = var.Lookup("x", buffer);

	var["x"] = x;

	XString hilf;
	usrfn.Lookup(name, hilf);
	
	double ret = atof(Calc(hilf, extVar));

	if (xExist)	var["x"] = buffer;
	else		var.RemoveKey("x");

	return ret;
}

/*****************************************************************************
 * Klasse:		XEvaluate
 * Funktion:	TestError
 * Parameter:	-
 * Return:		false wenn ein Fehler vorliegt, sonst true
 *
 * Mit dieser Funktion wird getestet, ob bei der letzten Operation ein
 * Fehler aufgetreten ist. Wenn dies der Fall war, liegt als letztes Element
 * auf dem jeweiligen Stack ein Fehlerwert.
 ****************************************************************************/
bool XEvaluate::TestError()
{
	if (!val.IsEmpty()	&& (ValTop() == VALERR))	{ ValPop(); return Error("value");	}
	if (!op.IsEmpty()	&& (OpTop()  == OPERR))		{ OpPop();	return Error("op");		}
	if (!txt.IsEmpty()	&& (TxtTop() == TXTERR))	{ TxtPop();	return Error("var");	}

	return true;
}

/*****************************************************************************
 * Klasse:		XEvaluate
 * Funktion:	IsBinOp
 * Parameter:	oper	Zu testender Operator
 * Return:		true, wenn 'oper' ein binärer Operator ist, sonst false
 *
 * Stellt fest, ob der übergebene Operator ein binärer Operator ist.
 ****************************************************************************/
bool XEvaluate::IsBinOp(int oper)
{
	switch (oper)
	{
	case ADD:	case SUB:	case MUL:	case DIV:
	case MOD:	case AND:	case OR:	case XOR:
	case LT:	case GT:	case SET:	case EQ:
	case NEQ:	case LE:	case GE:
	case ADDEQ:	case SUBEQ:	case MULEQ:	case DIVEQ:		return true;
	}
	return false;
}

/*****************************************************************************
 * Klasse:		XEvaluate
 * Funktion:	Calc
 * Parameter:	formel		Formelstring
 *				extVar		Map mit vordefinierten Variablen
 * Return:		Berechnungsergebnis der Formel als String
 * Beispiel:	Calc("1+2*3+4*5")				==> "27"
 *				Calc("fix=1;sin(pi/2")			==> "1.0"
 *				Calc("deg;fix=3;sin(90)")		==> "1.000"
 *				Calc("a=pi/4;sin(a)*cos(a)")	==> "0.5"
 *				Calc("a:=sin(x);a(pi/2)")		==> "1"
 *
 * Mit dieser Funktion können arithmetische Ausdrücke evaluiert werden.
 * Hierbei können auch Variablen benutzt werden.
 ****************************************************************************/
XString XEvaluate::Calc(LPCTSTR formel, CMap<CString, LPCTSTR, double,	double> *ext)
{
	//========================================================================
	// Externe Variable-Map
	//========================================================================
	if (ext) extVar = ext;

	//========================================================================
	// Leerzeichen aus dem String entfernen
	//========================================================================
	XString			str = XString(formel).RemoveAll(' ') + ')';

	//========================================================================
	// Jede Teilberechnung wird separat ausgeführt. Die letzte Berechnung
	// findet in diesem Aufruf statt.
	//========================================================================
	for (int i = str.Find(';'), j; i > 0; )
	{
		Calc(str.Left(i));
		str = str.Mid(i + 1);
		i = str.Find(';');
	}

	const int	len = str.GetLength();
	double		a, b;		// Zwischenwerte
	XString		name, hilf;	// Variablen- oder Funktionsname, Hilfsvariable
	int			op1, op2;	// Stackoperatoren

	OpPush(STOP);
	oldValFlag = false;

	for (i = 0; (i < len); i++)
	{
		if (!TestError()) return err;

		valFlag = false;
		int c = str[i];
		switch (c)
		{
		//====================================================================
		// Auswertung starten
		//====================================================================
		case ')':
			do
			{
				op1 = OpPop();
				op2 = (op.IsEmpty() ? STOP : OpTop());

				switch (op1)
				{
				case STOP:	break;
				//============================================================
				// Unäre Operatoren / Funktionen
				//============================================================
				case ABS:	a = ValPop();						ValPush(fabs(a));					break;
				case ACOS:	a = ValPop();						ValPush(ToMod(acos(a)));			break;
				case ASIN:	a = ValPop();						ValPush(ToMod(asin(a)));			break;
				case ATAN:	a = ValPop();						ValPush(ToMod(atan(a)));			break;
				case COS:	a = ValPop();						ValPush(cos(ToRad(a)));				break;
				case CUBE:	a = ValPop();						ValPush(a * a * a);					break;
				case EXP:	a = ValPop();						ValPush(exp(a));					break;
				case FAK:	a = ValPop();						ValPush(fak(a));					break;
				case FRACT:	a = ValPop();						ValPush(a - (int) a);				break;
				case INT:	a = ValPop();						ValPush((int) a);					break;
				case LN:	a = ValPop();						ValPush(log(a));					break;
				case LOG10:	a = ValPop();						ValPush(log10(a));					break;
				case LOG:	a = ValPop();						ValPush(log(a));					break;
				case NEG:	a = ValPop();						ValPush(-a);						break;
				case NOT:	a = ValPop();						ValPush(a == 0);					break;
				case NOTB:	a = ValPop();						ValPush(~(int) a);					break;
				case SET:	a = ValPop();						ValPush(var[TxtPop()] = a);			break;
				case SIN:	a = ValPop();						ValPush(sin(ToRad(a)));				break;
				case SQR:	a = ValPop();						ValPush(a * a);						break;
				case SQRT:	a = ValPop();						ValPush(sqrt(a));					break;
				case TAN:	a = ValPop();						ValPush(tan(ToRad(a)));				break;

				//============================================================
				// Binäre Operatoren / Funktionen
				//============================================================
				case ADD:	a = ValPop();	b = ValPop();		ValPush((op2 == SUB) ? b-a : b+a);	break;
				case ADDEQ:	a = ValPop();	b = var[TxtTop()];	ValPush(var[TxtPop()] = b + a);		break;
				case AND:	a = ValPop();	b = ValPop();		ValPush((int) b & (int) a);			break;
				case DIV:	a = ValPop();	b = ValPop();		ValPush((op2 == DIV) ? b*a : b/a);	break;
				case DIVEQ:	a = ValPop();	b = var[TxtTop()];	ValPush(var[TxtPop()] = b / a);		break;
				case EQ:	a = ValPop();	b = ValPop();		ValPush(b == a);					break;
				case GE:	a = ValPop();	b = ValPop();		ValPush(b >= a);					break;
				case GT:	a = ValPop();	b = ValPop();		ValPush(b >  a);					break;
				case LE:	a = ValPop();	b = ValPop();		ValPush(b <= a);					break;
				case LT:	a = ValPop();	b = ValPop();		ValPush(b <  a);					break;
				case MOD:	a = ValPop();	b = ValPop();		ValPush((int) b % (int) a);			break;
				case MUL:	a = ValPop();	b = ValPop();		ValPush((op2 == DIV) ? b/a : b*a);	break;
				case MULEQ:	a = ValPop();	b = var[TxtTop()];	ValPush(var[TxtPop()] = b * a);		break;
				case NEQ:	a = ValPop();	b = ValPop();		ValPush(b != a);					break;
				case OR:	a = ValPop();	b = ValPop();		ValPush((int) b | (int) a);			break;
				case POW:	a = ValPop();	b = ValPop();		ValPush(pow(b, a));					break;
				case SUB:	a = ValPop();	b = ValPop();		ValPush((op2 == SUB) ? b+a : b-a);	break;
				case SUBEQ:	a = ValPop();	b = var[TxtTop()];	ValPush(var[TxtPop()] = b - a);		break;
				case XOR:	a = ValPop();	b = ValPop();		ValPush((int) b ^ (int) a);			break;

				//============================================================
				// Benutzerdefinierte Funktionen
				//============================================================
				case USRFN:	a = ValPop();	name = TxtPop();	ValPush(UseFunction(name, a));		break;

				//============================================================
				// Spezialfunktionen
				//============================================================
				case FIX:	if ((komma = (int) ValPop()) < 0) komma = -1;	break;
				case NOP:													break;
				case DEC:	out = DEC;										break;
				case BIN:	out = BIN;										break;
				case HEX:	out = BIN;										break;
				case CHR:	out = CHR;										break;
				case DEG:	modus = DEG;									break;
				case GON:	modus = GON;									break;
				case RAD:	modus = RAD;									break;
				}
			} while ((op2 != STOP) && (op2 != ERR));
			
			if (!TestError()) return err;
			if (!op.IsEmpty()) OpPop();
			
			break;

		//====================================================================
		// Klammer
		//====================================================================
		case '(':	if (IsBinOp(OpTop())) OpPush(STOP);		break;

		//====================================================================
		// Unäre und Binäre Operatoren
		//====================================================================
		case '+':	OpPush(ADD);							break;
		case '-':	OpPush(oldValFlag ? SUB : NEG); 		break;
		case '*':	OpPush(MUL);							break;
		case '/':	OpPush(DIV);							break;
		case '%':	OpPush(MOD);							break;
		case '&':	OpPush(AND);							break;
		case '|':	OpPush(OR);								break;
		case '^':	OpPush(XOR);							break;
		case '!':	OpPush(NOT);							break;
		case '<':	OpPush(LT);								break;
		case '>':	OpPush(GT);								break;
		case '~':	OpPush(NOTB);							break;
		case ':':	OpPush(DP);								break;

		//====================================================================
		// Parametertrennung (Bsp.: pow(a,b))
		//====================================================================
		case ',':											break;

		//====================================================================
		// Alter Wert (@), Funktionsliste (?), Reset (#), Status (§),
		// Variablen- und Funktionsliste ($)
		//====================================================================
		case '@':	ValPush(oldValue);						break;
		case '?':	op.RemoveAll(); return Help();
		case '#':	op.RemoveAll(); return Reset();
		case '§':	op.RemoveAll(); return Status();
		case '$':	op.RemoveAll(); return VarList();

		//====================================================================
		// Zuweisungen und Vergleiche
		//====================================================================
		case '=':
			if (i == 0)	return Error("'='");
			switch(str[i-1])
			{
			case '+':	OpPop(); OpPush(ADDEQ);				break;
			case '-':	OpPop(); OpPush(SUBEQ);				break;
			case '*':	OpPop(); OpPush(MULEQ);				break;
			case '/':	OpPop(); OpPush(DIVEQ);				break;
			case '=':	OpPop(); OpPush(EQ);				break;
			case '!':	OpPop(); OpPush(NEQ);				break;
			case '<':	OpPop(); OpPush(LE);				break;
			case '>':	OpPop(); OpPush(GE);				break;
			case ':':	OpPop(); return SetFunction(TxtPop(), str.Mid(i + 1));
			default:	if (OpTop() != FIX) OpPush(SET);	break;
			}
			break;

		//====================================================================
		// Zeicheneingabe ("x oder 'x)
		//====================================================================
		case '\"':	i++; ValPush((int) str[i]);				break;
		case '\'':	i++; ValPush((int) str[i]);				break;

		//====================================================================
		// Dezimale, binäre und hexadezimale Zahlen beginnen immer mit einer
		// Ziffer (123, 0xab, 1100b)
		//====================================================================
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			for (i++, hilf = ""; ; i++)
			{
				hilf += c;
				c = str[i];									// Aktuelles Zeichen

				if (isxdigit(c))				continue;	// Hex, Bin oder Dec
				if (c == '.')					continue;	// Nachkommastellen

				switch (tolower(str[i - 1]))
				{
				case 'e':	if (c == '+')		continue;	// Positiver Exponent
							if (c == '-')		continue;	// Negativer Exponent
							break;
				case '0':	if (c == 'x')		continue;	// Hexadezimalzahl
							break;
				}

				break;		// Zahl abgeschlossen
			}

			ValPush(Dec(hilf));
			i--;
			if (OpTop() == NEG)	str.SetAt(i--, ')');
			break;

		//====================================================================
		// Funktionen, Zuweisungen, Variablen, Fehler
		//====================================================================
		default:
			for (name = ""; isalnum(c); c = str[++i]) name += c;
			i--;
			// 1. Interne Funktion
			if (fkt.Lookup(name.Lower(), j))		{ OpPush(STOP); OpPush(j); break; }
			// 2. Benutzerfunktion
			if (usrfn.Lookup(name, hilf))			{ TxtPush(name); OpPush(STOP); OpPush(USRFN); break; }
			// 3. Zuweisung
			if ((i+1 < len) && (str[i+1] == '='))	{ TxtPush(name); break; }
			// 4. Arithmetische Zuweisung (+=, ..)
			if ((i+2 < len) && (str[i+2] == '='))	{ TxtPush(name); break; }
			// 5. Externe Variable
			if (extVar && extVar->Lookup(name, a))	{ ValPush(a); break; }
			// 6. Interne Variable
			if (var.Lookup(name, a))				{ ValPush(a); break; }
			// 7. Fehler
			return Error("var " + name);
		}

		//====================================================================
		// Wenn eine Variable definiert wird, muß eine eventuell vorhandene
		// Benutzerfunktion gelöscht werden und umgekehrt,
		//====================================================================
		if (!op.IsEmpty())
			if (OpTop() == SETFN)		var.RemoveKey(TxtTop());
			else if (OpTop() == SET)	usrfn.RemoveKey(TxtTop());

		//====================================================================
		// Bei einer Folge von binären Operatoren, wird der Stack solange
		// aufgebaut, bis ein Operator niedriger Priorität auf einen Operator
		// höherer Priorität folgt. In diesem Fall muß der Stack abgebaut
		// werden (MUL und DIV haben höhere Priorität als alle anderen).
		//====================================================================
		oldValFlag = valFlag;
		if (!valFlag && !op.IsEmpty())
			if (IsBinOp(OpTop()))
			{
				// Letzter Operator hat hohe Priorität
				if ((OpTop() != MUL) && (OpTop() != DIV))
				{
					int oldOp = OpPop();
					// Vorheriger Operator hat gleiche Priorität ==> Auswerten
					if ((!op.IsEmpty()) && ((OpTop() == MUL) || (OpTop() == DIV)))
					{
						str.SetAt(i - 1, ')');
						i -= 2;
					}
					else
						OpPush(oldOp);
				}
			}
	}

	oldValue = (val.IsEmpty()) ? 0 : ValPop();

	switch (out)
	{
	case HEX:	name = Hex((int) oldValue);	break;
	case BIN:	name = Bin((int) oldValue);	break;
	case CHR:	name.Format("%c\t0x%2x\t%3d", (char) oldValue, (int) oldValue, (int) oldValue); break;
	case DEC:	if (komma < 0)	name.Format("%.16lg", oldValue);
				else			name.Format("%.*lf", komma, oldValue);
	}

	return name;
}
