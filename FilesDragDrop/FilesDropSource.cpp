// FilesDropSource.cpp : implementation file
//

#include "stdafx.h"
#include "FilesList.h"
#include "FilesDropSource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilesDropSource


CFilesDropSource::CFilesDropSource()
		: COleDropSource()
{
}

CFilesDropSource::~CFilesDropSource()
{
}

BEGIN_MESSAGE_MAP(CFilesDropSource, COleDropSource)
	//{{AFX_MSG_MAP(CFilesDropSource)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


