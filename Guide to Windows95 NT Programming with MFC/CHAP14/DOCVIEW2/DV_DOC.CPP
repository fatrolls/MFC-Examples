///////////////////////////////////////////////////////////////////
// Header  : DV_DOC.CPP
//
// Purpose : Implementation of the CDocView2Doc class.
//
// Author  : Rob McGregor - rob_mcgregor@compuserve.com
//
// Date    : 05-12-96
///////////////////////////////////////////////////////////////////

#include "stdafx.h"     // Standard include   
#include "DocView2.h"   // View           
#include "DV_Doc.h"     // Document           
                                   
IMPLEMENT_DYNCREATE(CDocView2Doc, CDocument)

///////////////////////////////////////////////////////////////////
// CDocView2Doc construction/destruction

CDocView2Doc::CDocView2Doc()
{
}

CDocView2Doc::~CDocView2Doc()
{
}

///////////////////////////////////////////////////////////////////
// CDocView2Doc::OnNewDocument()

BOOL CDocView2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// SDI documents will reuse this document, initialize here...

	return TRUE;
}

///////////////////////////////////////////////////////////////////


