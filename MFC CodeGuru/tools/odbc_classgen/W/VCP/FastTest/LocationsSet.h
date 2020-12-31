/*
**LocationsSet.h
**LOCATIONS Definition file
*/

#if	!defined(__DB_LOCATIONS_FIELDS__)
#define __DB_LOCATIONS_FIELDS__



#ifndef __AFXTEMPL_H__
#pragma message("Include AfxTempl.h in StdAfx.h for faster Compilation")
#include <afxtempl.h>
#endif


#define LOCATIONS_CODE_SIZE                          9
#define LOCATIONS_NAME_SIZE                          31


//Internal Cache for the data

typedef struct
{
    char                          m_Code[LOCATIONS_CODE_SIZE];
    SDWORD                        m_CodeInd;
    char                          m_Name[LOCATIONS_NAME_SIZE];
    SDWORD                        m_NameInd;
}FF_DB_LOCATIONS_FIELDS, *pFF_DB_LOCATIONS_FIELDS;


//structure to hold the final data

typedef struct
{
    CString                       m_Code;
    CString                       m_Name;
}DB_LOCATIONS_FIELDS, *pDB_LOCATIONS_FIELDS;


//Class Definition
class CLocationsSet
{
public:
//Standard constructor
    CLocationsSet(CDatabase* pDB = NULL);

//Standard Destructor
    ~CLocationsSet();

//Operations
    bool GetSpecific(pDB_LOCATIONS_FIELDS);
    bool Insert(pDB_LOCATIONS_FIELDS);
    bool Update(pDB_LOCATIONS_FIELDS);
    bool Delete(pDB_LOCATIONS_FIELDS);
    int  Load();

//Attributes
    CTypedPtrArray <CPtrArray, pDB_LOCATIONS_FIELDS> m_aData;
private:
    CDatabase* m_pDatabase;
    HSTMT      m_hstmt;
    int        m_nRowSetSize;
};

#endif

/*
** end file
*/