// LogMsg.cpp: implementation of the CLogMessage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LogMsg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogMessage::CLogMessage()
{
    if (m_LogFile.Open ("LOG.TXT", CFile::modeCreate | CFile::modeWrite | CFile::typeText))
    {   
        m_bSuccess = TRUE;
    }
    else
    {
        m_bSuccess = FALSE;
    }
}

CLogMessage::~CLogMessage()
{
    m_LogFile.Close ();
}

BOOL CLogMessage::WriteError(const CString & strMessage)
{
    TRY
    {
        if (m_bSuccess)
        {
            m_LogFile.WriteString (strMessage);
        }
        else
        {
            throw;
        }
    }
    CATCH (CFileException, e)
    {
        return FALSE;
    }
    END_CATCH

    return TRUE;
}
