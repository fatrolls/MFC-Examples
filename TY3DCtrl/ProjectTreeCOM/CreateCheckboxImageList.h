

#ifndef CREATECHECKBOXIMAGELIST_H
#define CREATECHECKBOXIMAGELIST_H
#include <atlstr.h>
#include "wtl/atlapp.h"
#include "wtl/atlgdi.h"
#include "wtl/atlctrls.h"
#include "wtl/atlcrack.h"
#include "wtl/atlmisc.h"
namespace HDCheckboxImageList
{
	const UINT HOT_INDEX		= 8;
	const UINT DISABLED_INDEX	= 4;

	BOOL CreateCheckboxImageList(WTL::CDCHandle pDC, 
								 WTL::CImageList& imagelist, 
								 int nSize, 
								 COLORREF crBackground);
}

#endif //CREATECHECKBOXIMAGELIST_H
