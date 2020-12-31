// CntrItem.cpp : implementation of the CScrollTipDemoCntrItem class
//

#include "stdafx.h"
#include "ScrollTipDemo.h"

#include "ScrollTipDoc.h"
#include "ScrollTipEditView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScrollTipDemoCntrItem implementation

IMPLEMENT_SERIAL(CScrollTipDemoCntrItem, CRichEditCntrItem, 0)

CScrollTipDemoCntrItem::CScrollTipDemoCntrItem(REOBJECT* preo, CScrollTipDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
	
}

CScrollTipDemoCntrItem::~CScrollTipDemoCntrItem()
{
	// TODO: add cleanup code here
	
}

/////////////////////////////////////////////////////////////////////////////
// CScrollTipDemoCntrItem diagnostics

#ifdef _DEBUG
void CScrollTipDemoCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CScrollTipDemoCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
