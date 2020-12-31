// MIMEContentAgent.cpp: implementation of the CMIMEContentAgent class.
// Author: Wes Clyburn (clyburnw@enmu.edu)
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MIMEContentAgent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMIMEContentAgent::CMIMEContentAgent( int nMIMEType )
{
	m_nMIMETypeIHandle = nMIMEType;
}

CMIMEContentAgent::~CMIMEContentAgent()
{

}

BOOL CMIMEContentAgent::QueryType(int nContentType)
{
	return nContentType == m_nMIMETypeIHandle ? TRUE : FALSE;
}

