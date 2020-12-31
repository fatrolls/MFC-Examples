// ==========================================================================
// 						Class Implementation : COXSerializer
// ==========================================================================

// Source file : oxsrlzr.cpp

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.    
                  
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OXSRLZR.H"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

static TCHAR BASED_CODE MsgOutOfMemory[]= _T("Out of Memory!");
static TCHAR BASED_CODE no_resource_string_available[] = _T("RC error: No RESSERLZR.RC file found");

COXSerializer::COXSerializer() :
	m_bInitialized(FALSE),
    m_pObject(NULL)
{
}

COXSerializer::~COXSerializer()
{
}

BOOL COXSerializer::Initialize(CString sFileName, CObject* pObject)
{
    if (pObject == NULL)
	{
        TRACE0("COXSerializer::Initialize: pObject argument can't be NULL");
		ASSERT(FALSE);
        return FALSE;
    }        
    ASSERT_VALID(pObject);
    if (pObject->IsSerializable() == FALSE)
        return FALSE;

    m_fileException.m_cause = CFileException::none;    
    m_fileException.m_lOsError = 0L;    
    m_archiveException.m_cause = CArchiveException::none;
    m_bMemoryException = FALSE;

    m_bInitialized = TRUE;
    m_sFileName = sFileName;
    m_pObject = pObject;
    return TRUE;
}

BOOL COXSerializer::Load(BOOL bDisplayException)
{
	CFile		file;
	CArchive*	pArchive=NULL;

    if (m_bInitialized==FALSE)
        return FALSE;

    m_fileException.m_cause = CFileException::none;    
    m_fileException.m_lOsError = 0L;    
    m_archiveException.m_cause = CArchiveException::none;
    m_bMemoryException = FALSE;

    if (!file.Open(m_sFileName, CFile::modeRead | CFile::typeBinary |   
                               CFile::shareExclusive, &m_fileException))
	{
        if (bDisplayException)
            m_fileException.ReportError();
        return FALSE;
    }
    TRY
	{
        pArchive = new CArchive(&file, CArchive::load);
        m_pObject->Serialize(*pArchive);
        delete pArchive;
        file.Close();
    }
	CATCH (CMemoryException, e)
	{
        m_bMemoryException = TRUE;
		delete pArchive;
        if (bDisplayException) 
            AfxMessageBox(MsgOutOfMemory);
        return FALSE;
	}
    AND_CATCH (CArchiveException, e)
	{
        m_archiveException.m_cause = e->m_cause;
        if (bDisplayException) 
           e->ReportError();
        delete pArchive;
        return FALSE;
    }
    AND_CATCH (CFileException, e)
	{
        m_fileException.m_cause = e->m_cause;
        m_fileException.m_lOsError = e->m_lOsError;
        if (bDisplayException) 
           e->ReportError();
        delete pArchive;
        return FALSE;
    }
	END_CATCH

    return TRUE;
}

BOOL COXSerializer::Save(BOOL bDisplayException)
{
	CFile		file;
	CArchive*	pArchive=NULL;

    if (m_bInitialized==FALSE)
        return FALSE;
    m_fileException.m_cause = CFileException::none;    
    m_fileException.m_lOsError = 0L;    
    m_archiveException.m_cause = CArchiveException::none;
    m_bMemoryException = FALSE;

    if (!file.Open(m_sFileName, CFile::modeCreate | CFile::modeWrite |
                               CFile::typeBinary | CFile::shareExclusive, 
                               &m_fileException))
	{
        if (bDisplayException)
            m_fileException.ReportError();
        return FALSE;
    }
    TRY
	{
        pArchive = new CArchive(&file, CArchive::store);
        m_pObject->Serialize(*pArchive);
        delete pArchive;
        file.Close();
    }
	CATCH (CMemoryException, e)
	{
        m_bMemoryException = TRUE;
		delete pArchive;
        if (bDisplayException) 
            AfxMessageBox(MsgOutOfMemory);
        return FALSE;
	}
    AND_CATCH (CArchiveException, e)
	{
        m_archiveException.m_cause = e->m_cause;
        if (bDisplayException) 
           e->ReportError();
        delete pArchive;
        return FALSE;
    }
    AND_CATCH (CFileException, e)
	{
        m_fileException.m_cause = e->m_cause;
        m_fileException.m_lOsError = e->m_lOsError;
        if (bDisplayException) 
            e->ReportError();
        delete pArchive;
        return FALSE;
    }
	END_CATCH

    return(TRUE);
}

