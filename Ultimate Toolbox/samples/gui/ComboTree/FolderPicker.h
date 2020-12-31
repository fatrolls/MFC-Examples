// FolderPicker.h: interface for the CFolderPicker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FOLDERPICKER_H__35306227_1C37_11D4_AD1F_0050BAAB46B1__INCLUDED_)
#define AFX_FOLDERPICKER_H__35306227_1C37_11D4_AD1F_0050BAAB46B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\..\INCLUDE\OXComboPickerCtrl.h"

class CFolderPicker : public COXComboPickerCtrl  
{
public:
	CFolderPicker();
	virtual ~CFolderPicker();
 	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
 
};

#endif // !defined(AFX_FOLDERPICKER_H__35306227_1C37_11D4_AD1F_0050BAAB46B1__INCLUDED_)
