// ==========================================================================
// 					Check specification
//----------------- Dundas Software ----------------------------------------                          
//========================================================================

// Header file : OXCheck.h
// //////////////////////////////////////////////////////////////////////////

#define INIT_CHECK()	\
	int _v = 0;			\
	int _cv = 0;		\
	CString _s,_cs;		\
	CString _sMsg;		\
	int errors = 0;		\
	int total = 0;		\
	int number = 1;

#define CHECK(value, correctValue)										\
	_v = (int)(value); _cv = (int)(correctValue); total++;					\
	_sMsg.Format(_T(" %2.2i (line %4.4i). %14.14s %i == %i"), number++,	__LINE__,	\
		((_v == _cv) ? _T("Correct") : _T("* INCORRECT *")), _v, _cv);	\
	TRACE1("%s\n", _sMsg);												\
	if (_v != _cv) { errors++; AfxMessageBox(_sMsg, MB_ICONEXCLAMATION); }

#define CHECKS(value, correctValue)										\
	_s = (value); _cs = (correctValue); total++;							\
	_sMsg.Format(_T(" %2.2i (line %4.4i). %14.14s %s == %s"), number++,	__LINE__,	\
	((_s == _cs) ? _T("Correct") : _T("* INCORRECT *")), _s, _cs);		\
	TRACE1("%s\n", _sMsg);												\
	if (_s != _cs) { errors++; AfxMessageBox(_sMsg, MB_ICONEXCLAMATION); }

#define RESET_NUMBER(Tx)	\
	number = 1;				\
	TRACE1("\n%s\n", _T(Tx));

#define SHOW_RESULT()		\
	TRACE2("\n*** Errors --- %i / %i\n", errors, total);

// //////////////////////////////////////////////////////////////////////////
