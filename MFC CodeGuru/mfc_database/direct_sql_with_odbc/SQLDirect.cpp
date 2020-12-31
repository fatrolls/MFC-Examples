#include "stdafx.h"
#include "sqldirect.h"

CSQLDirect::CSQLDirect()
{
	Init();
}

CSQLDirect::CSQLDirect( CString svConnect )
{
	Init();

	Connect( svConnect );
}

CSQLDirect::~CSQLDirect()
{
	if( m_psvErrorMsg )
		delete m_psvErrorMsg;

	if( m_psvSQL )
		delete m_psvSQL;

	if( m_hStmt!=NULL )
		SQLFreeStmt( m_hStmt, SQL_DROP );

	if( m_hDBC!=NULL ) {
		SQLDisconnect( m_hDBC );
		SQLFreeConnect( m_hDBC );
	}

	if( m_hEnv!=NULL )
		SQLFreeEnv( m_hEnv );

	KillCols();
}

void CSQLDirect::Init( void )
{
	m_psvErrorMsg=0;
	m_psvSQL=0;

	m_psvErrorMsg=new _TUCHAR[ SQL_MAX_MESSAGE_LENGTH-1 ];

	m_hDBC=NULL;
	m_hEnv=NULL;
	m_hStmt=NULL;

	m_bSupressErrors=false;
}

int CSQLDirect::ExecuteSQL( LPCSTR svSQL )
{
	if( m_psvSQL )
		delete m_psvSQL;

	if( m_hStmt!=NULL )
		Close();
	
	m_psvSQL=new _TUCHAR[ strlen( svSQL )+1 ];
	strcpy( (char*)m_psvSQL,svSQL );

	int nRet=SQLExecDirect( m_hStmt,m_psvSQL,SQL_NTS );

	if( ( nRet!=SQL_SUCCESS && nRet!=SQL_SUCCESS_WITH_INFO ) && !m_bSupressErrors ) 
		DisplayError();

	return nRet;
}

int CSQLDirect::Connect( LPCSTR svSource )
{
	int nConnect=SQLAllocEnv( &m_hEnv );

	if( nConnect==SQL_SUCCESS ) {
		nConnect=SQLAllocConnect( m_hEnv,&m_hDBC );

		if( nConnect==SQL_SUCCESS ) {
			SQLSetConnectOption( m_hDBC,SQL_LOGIN_TIMEOUT,5 );

			// Connect to the datasource.
			_TUCHAR *psvSource=new _TUCHAR[ strlen( svSource )+1 ];
			_TUCHAR *psvUser=new _TUCHAR;
			_TUCHAR *psvPassword=new _TUCHAR;

			strcpy( (char*)psvSource,svSource );

			nConnect=SQLConnect( m_hDBC,psvSource,SQL_NTS,psvUser,SQL_NTS,psvPassword,SQL_NTS );

			if( nConnect==SQL_SUCCESS || nConnect==SQL_SUCCESS_WITH_INFO ) {
				// Now that the datasource is open, get our SQL statement handle.
				nConnect=SQLAllocStmt( m_hDBC,&m_hStmt );
			}

			delete psvSource;
			delete psvUser;
			delete psvPassword;
		}
		else 
			DisplayError();
	}
	else 
		DisplayError();

	return nConnect;
}

void CSQLDirect::DisplayError( void )
{
	if( !m_bSupressErrors ) {
		CString svError;
		GetError( svError );

		// We'll get fancier later.
		if( !svError.IsEmpty() )
			AfxMessageBox( svError );
	}
}

void CSQLDirect::GetError( CString& svMsg )
{
	_TUCHAR* pSqlState=new _TUCHAR[SQL_MAX_MESSAGE_LENGTH-1];
	SDWORD NativeError;
	SWORD svErrorMsg;

	SQLError( m_hEnv,m_hDBC,m_hStmt,pSqlState,&NativeError,m_psvErrorMsg,
		SQL_MAX_MESSAGE_LENGTH-1,&svErrorMsg );

	delete pSqlState;

	svMsg=m_psvErrorMsg;
}

void CSQLDirect::KillCols( void ) 
{
	for( int nItem=0;nItem<m_ColArray.GetSize();nItem++ ) {
		CSQLColumn* pCol=(CSQLColumn*)m_ColArray[nItem];
		delete pCol;
	}

	if( m_ColArray.GetSize() )
		m_ColArray.RemoveAll();
}

CString CSQLDirect::GetCol( int nCol )
{
	CString svValue;

	// Due to the nature of the SQL API, repeated calls to the same column will result in a NULL value passed
	// back into svData. We need to keep track of the columns that have been used already and if so, pass back
	// the data stored in our array.
	int nIndex=FindColumn( nCol );

	if( nIndex==-1 ) {
		// Get the column from the SQL cursor.
		UCHAR svData[8192];
		SDWORD cbDataLen;

		SQLGetData( m_hStmt,nCol,GetColumnType( nCol ),&svData,8192,&cbDataLen );
	
		svValue=svData;
		svValue.TrimRight();

		AddColumn( nCol,svValue );
	}
	else {
		// Get the value from the column array.
		svValue=GetColumn( nCol )->m_svValue;
	}

	return svValue;
}

int CSQLDirect::GetColumnType( int nCol )
{
	int nType=SQL_C_DEFAULT;

	// Due to the nature of the SQL API, repeated calls to the same column will result in a NULL value passed
	// back into svData. We need to keep track of the columns that have been used already and if so, pass back
	// the data stored in our array.
	int nIndex=FindColumn( nCol );

	if( nIndex==-1 ) {
		// Get the column from the SQL cursor.
		UCHAR svColName[256];
		SWORD swCol,swType,swScale,swNull;
		UDWORD pcbColDef;

		SQLDescribeCol( m_hStmt,nCol,svColName,256,&swCol,&swType,&pcbColDef,&swScale,&swNull );

		nType=(int)swType;
	}
	else {
		// Get the value from the column array.
		nType=GetColumn( nCol )->m_nType;
	}

	switch( nType ) {
	case SQL_LONGVARBINARY:
		nType=SQL_C_DEFAULT;
		break;
	default:
		nType=SQL_C_CHAR;
		break;
	};

	return nType;
}

void CSQLDirect::AddColumn( int nCol,CString svData )
{
	int nIndex=m_ColArray.Add( new CSQLColumn );
	CSQLColumn* pCol=(CSQLColumn*)m_ColArray[nIndex];

	pCol->m_nCol=nCol;
	pCol->m_svValue=svData;
}

int CSQLDirect::FindColumn( int nCol )
{
	bool bFound=false;

	for( int nIndex=0;nIndex<m_ColArray.GetSize();nIndex++ ) {
		CSQLColumn* pCol=(CSQLColumn*)m_ColArray[nIndex];

		if( pCol->m_nCol==nCol ) {
			bFound=true;
			break;
		}
	}

	return ( bFound ) ? nIndex : -1;
}

int CSQLDirect::Fetch( void )
{
	// Start with a fresh batch of columns.
	KillCols();

	// Fetch the next row.
	int nRet=SQLFetch( m_hStmt );

	if( ( nRet!=SQL_SUCCESS && nRet!=SQL_SUCCESS_WITH_INFO ) && !m_bSupressErrors )
		DisplayError();

	return nRet;
}

CString CSQLDirect::GetColumnName( int nCol )
{
	UCHAR svColName[256];
	SWORD swCol,swType,swScale,swNull;
	UDWORD pcbColDef;

	SQLDescribeCol( m_hStmt,nCol,svColName,256,&swCol,&swType,&pcbColDef,&swScale,&swNull );

	CString svName=svColName;
	svName.TrimRight();

	return svName;
}

int CSQLDirect::GetColumnID( CString svField,CString svTable )
{
	UCHAR svColName[256];
	UCHAR ucOwner[256];
	SWORD swCol,swType,swScale,swNull;
	UDWORD pcbColDef;
	SDWORD wColLen;

	int nCol=1;

	// Get the total # of columns in this query.
	SQLColAttributes( m_hStmt,0,SQL_COLUMN_COUNT,ucOwner,256,&swScale,&wColLen );
	int nMaxCols=(int)wColLen;

	while( nCol<=nMaxCols ) {
		int nRet=SQLDescribeCol( m_hStmt,nCol,svColName,256,&swCol,&swType,&pcbColDef,&swScale,&swNull );
		SQLColAttributes( m_hStmt,nCol,SQL_COLUMN_TABLE_NAME,ucOwner,256,&swScale,&wColLen );

		// If we hit this condition, then our field is not in the dataset.
		if( nRet!=SQL_SUCCESS ) {
			nCol=0;
			break;
		}

		CString svName=svColName;
		CString svOwner=ucOwner;

		svName.TrimRight();
		svOwner.TrimRight();

		if( ( svName==svField ) ) {
			if(  !svTable.IsEmpty() ) {
				if( svOwner==svTable )
					break;
				else
					nCol++;
			}
			else
				break;
		}
		else
			nCol++;
	}

	return nCol;
}

CString CSQLDirect::GetCol( CString svName, CString svTable )
{
	return GetCol( GetColumnID( svName,svTable ) );
}

CSQLColumn* CSQLDirect::GetColumn( int nCol )
{
	int nIndex=FindColumn( nCol );

	if( nIndex==-1 )
		return 0;
	
	return (CSQLColumn*)m_ColArray[nIndex];
}

void CSQLDirect::Close( void )
{
	if( m_hStmt!=NULL ) {
		// Free
		SQLFreeStmt( m_hStmt, SQL_DROP );

		KillCols();

		// Allocate again.
		SQLAllocStmt( m_hDBC,&m_hStmt );
	}
}
