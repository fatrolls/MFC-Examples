// FolderPicker.cpp: implementation of the CFolderPicker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FolderPicker.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFolderPicker::CFolderPicker()
{

}

CFolderPicker::~CFolderPicker()
{

}

void CFolderPicker::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if(m_pDropDown!=NULL)
	{
		lpMeasureItemStruct->itemHeight=m_pDropDown->GetItemHeight();
	}
	else
	{
		lpMeasureItemStruct->itemHeight=38;
	}
}

