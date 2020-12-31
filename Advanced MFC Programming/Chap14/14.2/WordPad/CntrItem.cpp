#include "stdafx.h"
#include "WordPad.h"
#include "WPDoc.h"
#include "WPView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(CWordPadCntrItem, CRichEditCntrItem, 0)

CWordPadCntrItem::CWordPadCntrItem(REOBJECT* preo, CWordPadDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
}

CWordPadCntrItem::~CWordPadCntrItem()
{
}

#ifdef _DEBUG
void CWordPadCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CWordPadCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif
