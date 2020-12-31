// TLabelComboBox.cpp: implementation of the CTLabelComboBox class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TLabelComboBox.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTLabelComboBox::CTLabelComboBox()
{

}

CTLabelComboBox::~CTLabelComboBox()
{

}

CWnd* CTLabelComboBox::GetEditControl()
{
	CWnd* pWnd = GetWindowControl();
	switch (pWnd->GetStyle() & 0x3)
	{
		case CBS_SIMPLE:
		case CBS_DROPDOWN:
			return pWnd->GetDlgItem(1001);
			break;
		case CBS_DROPDOWNLIST:
			return pWnd;
			break;
	}
	return NULL;
}
