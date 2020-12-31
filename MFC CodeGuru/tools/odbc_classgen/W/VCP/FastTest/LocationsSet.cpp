/*
**LocationsSet.cpp
**LOCATIONS Object Implementation file
*/

#include <StdAfx.h>
#include "LocationsSet.h"

// Standard Constructors / Destructors
CLocationsSet::CLocationsSet(CDatabase* pDB) : m_nRowSetSize(1000), m_pDatabase(pDB)
{
    ASSERT(m_pDatabase->IsOpen());

    m_hstmt     = SQL_NULL_HSTMT;

    RETCODE ReturnCode = SQLAllocStmt(m_pDatabase->m_hdbc, &m_hstmt);

    if  (ReturnCode != SQL_SUCCESS)
        TRACE("Unable to allocate Statement Handle in CLocationsSet\n");

}


CLocationsSet::~CLocationsSet()
{
    if  (m_hstmt)
        SQLFreeStmt(m_hstmt,SQL_DROP);

    for (int i = 0; i < m_aData.GetSize(); i++)
        delete m_aData.GetAt(i);


    m_aData.RemoveAll();

}


int CLocationsSet::Load()
{
    CString                 strSQLString;
    RETCODE                 ReturnCode;
    UDWORD                  RowsFetched;
    UWORD*                  pRowStatus;
    pFF_DB_LOCATIONS_FIELDS        pHostData;


    ASSERT(m_nRowSetSize > 0);

    pRowStatus = new UWORD[m_nRowSetSize];
    ASSERT(pRowStatus);

    pHostData = new FF_DB_LOCATIONS_FIELDS[m_nRowSetSize];
    ASSERT(pHostData);

    SQLSetStmtOption(m_hstmt,SQL_BIND_TYPE,sizeof(FF_DB_LOCATIONS_FIELDS));
    SQLSetStmtOption(m_hstmt,SQL_CONCURRENCY,SQL_CONCUR_READ_ONLY);
    SQLSetStmtOption(m_hstmt,SQL_CURSOR_TYPE,SQL_CURSOR_KEYSET_DRIVEN);
    SQLSetStmtOption(m_hstmt,SQL_ROWSET_SIZE,m_nRowSetSize);

/*
**SELECT FROM THE TABLE
*/

    strSQLString.Format(
            "SELECT "
                "CODE,"
                "NAME"
            " FROM LOCATIONS " );

    ReturnCode = SQLExecDirect(m_hstmt,(UCHAR*)((LPCTSTR)strSQLString),SQL_NTS);
    if (ReturnCode)
    {
        CDBException* pDBEx = new CDBException();
        pDBEx->BuildErrorString(m_pDatabase,m_hstmt);
        throw ( pDBEx);
        return 0;
    }

    ReturnCode = SQLBindCol(m_hstmt,1,SQL_C_CHAR,pHostData[0].m_Code,LOCATIONS_CODE_SIZE,&pHostData[0].m_CodeInd);
    ReturnCode = SQLBindCol(m_hstmt,2,SQL_C_CHAR,pHostData[0].m_Name,LOCATIONS_NAME_SIZE,&pHostData[0].m_NameInd);


// Fetch and store...
    while  (true)
    {
        ReturnCode = SQLExtendedFetch(m_hstmt,SQL_FETCH_NEXT,1,&RowsFetched,pRowStatus);
        if (ReturnCode == SQL_ERROR)
        {
            CDBException* pDBEx = new CDBException();
            pDBEx->BuildErrorString(m_pDatabase,m_hstmt);
            throw ( pDBEx);
            return 0;
        }

        for	(UINT Count = 0; Count < RowsFetched; Count++)
        {
            if	(pRowStatus[Count] != SQL_ROW_DELETED && pRowStatus[Count] != SQL_ROW_ERROR )
            {
                pDB_LOCATIONS_FIELDS  pData = new DB_LOCATIONS_FIELDS();
                ASSERT(pData);

                pData->m_Code                    = pHostData[Count].m_Code;
                pData->m_Name                    = pHostData[Count].m_Name;

                m_aData.Add(pData);
            }

        }

        if	(RowsFetched < (UINT)m_nRowSetSize)
            break;
    }

    delete [] pRowStatus;
    delete [] pHostData;

    return m_aData.GetSize();


} /* end function */


bool CLocationsSet::GetSpecific(pDB_LOCATIONS_FIELDS pData)
{
    CString                 strSQLString;
    RETCODE                 ReturnCode;
    SDWORD                  PCBValue;
    FF_DB_LOCATIONS_FIELDS         HostData;


/*
**SELECT FROM THE TABLE
*/

    strSQLString.Format(
            "SELECT "
                "CODE,"
                "NAME"
            " FROM LOCATIONS" 
      " WHERE "
        "CODE                 = '%s' ",

        pData->m_Code
    ); /* end Format */

    ReturnCode = SQLExecDirect(m_hstmt,(UCHAR*)((LPCTSTR)strSQLString),SQL_NTS);
    if (ReturnCode)
    {
        CDBException* pDBEx = new CDBException();
        pDBEx->BuildErrorString(m_pDatabase,m_hstmt);
        throw ( pDBEx);
        return false;
    }

    ReturnCode = SQLBindCol(m_hstmt,1,SQL_C_CHAR,&HostData.m_Code,LOCATIONS_CODE_SIZE,&PCBValue);
    ReturnCode = SQLBindCol(m_hstmt,2,SQL_C_CHAR,&HostData.m_Name,LOCATIONS_NAME_SIZE,&PCBValue);


// Fetch
    ReturnCode = SQLFetch(m_hstmt);
    switch (ReturnCode)
    {
    case 0:
        break;
    case 100:
        return false;
    default:
        CDBException* pDBEx = new CDBException();
        pDBEx->BuildErrorString(m_pDatabase,m_hstmt);
        throw ( pDBEx);
        return false;
    }

    pData->m_Code                    = HostData.m_Code;
    pData->m_Name                    = HostData.m_Name;


    return true;


} /* end function */


bool CLocationsSet::Insert(pDB_LOCATIONS_FIELDS pData)
{
    CString        strSQLString;

    strSQLString.Format 
    ( "INSERT INTO LOCATIONS ("
        "CODE,"
        "NAME )"
   "VALUES     ("
        "'%s'   ,"   /* CODE */
        "'%s'   )",  /* NAME */
        pData->m_Code,
        pData->m_Name
    ); /* end format */

    
    try
    {
        m_pDatabase->ExecuteSQL(strSQLString);
    }
    catch (CDBException* pE)
    {
        pE->ReportError();
        pE->Delete();
        return false;
    }

    return true;


} /* end function */


bool CLocationsSet::Update(pDB_LOCATIONS_FIELDS pData)
{
    CString        strSQLString;

    strSQLString.Format 
    ( "UPDATE LOCATIONS SET "
        "CODE                 = '%s', "
        "NAME                 = '%s'  "
    "WHERE "
        "CODE                 = '%s' ",

        pData->m_Code,
        pData->m_Name,
        pData->m_Code
    ); /* end Format */

    
    try
    {
        m_pDatabase->ExecuteSQL(strSQLString);
    }
    catch (CDBException* pE)
    {
        pE->ReportError();
        pE->Delete();
        return false;
    }

    return true;


} /* end function */


bool CLocationsSet::Delete(pDB_LOCATIONS_FIELDS pData)
{
    CString        strSQLString;

    strSQLString.Format 
    ( "DELETE LOCATIONS "

    "WHERE "
        "CODE                 = '%s' ",

        pData->m_Code
    ); // end Format 

    
    try
    {
        m_pDatabase->ExecuteSQL(strSQLString);
    }
    catch (CDBException* pE)
    {
        pE->ReportError();
        pE->Delete();
        return false;
    }

    return true;


} /* end function */
