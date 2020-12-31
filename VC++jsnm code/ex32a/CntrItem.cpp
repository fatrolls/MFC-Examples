// CntrItem.cpp : implementation of the CEx32aCntrItem class
//

#include "stdafx.h"
#include "ex32a.h"

#include "ex32aDoc.h"
#include "ex32aView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx32aCntrItem implementation

IMPLEMENT_SERIAL(CEx32aCntrItem, CRichEditCntrItem, 0)

CEx32aCntrItem::CEx32aCntrItem(REOBJECT* preo, CEx32aDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
	
}

CEx32aCntrItem::~CEx32aCntrItem()
{
	// TODO: add cleanup code here
	
}

/////////////////////////////////////////////////////////////////////////////
// CEx32aCntrItem diagnostics

#ifdef _DEBUG
void CEx32aCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CEx32aCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
