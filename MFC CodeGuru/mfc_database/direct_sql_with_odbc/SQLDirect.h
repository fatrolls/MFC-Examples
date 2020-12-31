#ifndef __SQLDIRECT
#define __SQLDIRECT

#include "sqlcolumn.h"

class CSQLDirect {
public:
	CSQLDirect();
	CSQLDirect( CString );
	~CSQLDirect();

	void Init( void );
	void GetError( CString& );
	void Close( void );
	int ExecuteSQL( LPCSTR );
	int Connect( LPCSTR );
	int Fetch( void );
	int GetColumnID( CString,CString );
	int GetColumnType( int );
	CString GetCol( int );
	CString GetCol( CString,CString = _T("") );
	CString GetColumnName( int );

	inline void CSQLDirect::SupressErrors( bool bSupress = true ) { m_bSupressErrors=bSupress; }

private:
	void KillCols( void );
	void AddColumn( int,CString );
	void DisplayError( void );
	int FindColumn( int );
	CSQLColumn* GetColumn( int );

private:
	_TUCHAR* m_psvSQL;
	_TUCHAR* m_psvErrorMsg;
	HENV		m_hEnv;
	HDBC		m_hDBC;
	HSTMT		m_hStmt;
	CPtrArray	m_ColArray;
	bool			m_bSupressErrors;
};

#endif // __SQL