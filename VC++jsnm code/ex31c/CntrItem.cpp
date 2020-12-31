// CntrItem.cpp : implementation of the CEx31cCntrItem class
//

#include "stdafx.h"
#include "ex31c.h"

#include "ex31cDoc.h"
#include "ex31cView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx31cCntrItem implementation

IMPLEMENT_SERIAL(CEx31cCntrItem, CRichEditCntrItem, 0)

CEx31cCntrItem::CEx31cCntrItem(REOBJECT* preo, CEx31cDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
	
}

CEx31cCntrItem::~CEx31cCntrItem()
{
	// TODO: add cleanup code here
	
}

/////////////////////////////////////////////////////////////////////////////
// CEx31cCntrItem diagnostics

#ifdef _DEBUG
void CEx31cCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CEx31cCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
