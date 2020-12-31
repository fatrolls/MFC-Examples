// EPropertyDir.h: interface for the EPropertyDir class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EPROPERTYDIR_H__331DAC0F_6733_49F6_BEF8_85E45AA3AA94__INCLUDED_)
#define AFX_EPROPERTYDIR_H__331DAC0F_6733_49F6_BEF8_85E45AA3AA94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EPropertyString.h"

class EPropertyDir : public EPropertyString  
{
public:
	EPropertyDir(IPropertyHost* pHost , const CString& sName , CString* Property );
	virtual ~EPropertyDir();

	virtual bool HasButton();
	virtual bool OnCommand(EPropWnd* pParent , WPARAM wParam , LPARAM lParam ); 
};

#endif // !defined(AFX_EPROPERTYDIR_H__331DAC0F_6733_49F6_BEF8_85E45AA3AA94__INCLUDED_)
