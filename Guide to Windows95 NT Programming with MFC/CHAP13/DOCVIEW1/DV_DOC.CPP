///////////////////////////////////////////////////////////////////
// Module  : DV_DOC.CPP
//
// Purpose : Implementation of the CDocView1Doc class.
//
// Author  : Rob McGregor - rob_mcgregor@compuserve.com
//
// Date    : 05-12-96
///////////////////////////////////////////////////////////////////

#include "stdafx.h"     // Standard include   
#include "DocView1.h"   // View           
#include "DV_Doc.h"     // Document           
                                   
IMPLEMENT_DYNCREATE(CDocView1Doc, CDocument)

///////////////////////////////////////////////////////////////////
// CDocView1Doc construction/destruction

CDocView1Doc::CDocView1Doc()
{
}

CDocView1Doc::~CDocView1Doc()
{
}

///////////////////////////////////////////////////////////////////
// CDocView1Doc::OnNewDocument()

BOOL CDocView1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// SDI documents will reuse this document, initialize here...

	return TRUE;
}

///////////////////////////////////////////////////////////////////


