// EPropertyFont.h: interface for the EPropertyFont class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EPROPERTYFONT_H__3EDDB0E0_3725_4A6C_93BE_EC084AFA49B5__INCLUDED_)
#define AFX_EPROPERTYFONT_H__3EDDB0E0_3725_4A6C_93BE_EC084AFA49B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EIconTextButtonProperty.h"

class EPropertyFont : public EIconTextButtonProperty
{

public:

	EPropertyFont( IPropertyHost* pHost , const CString& sName , CFont* pFont );
	virtual ~EPropertyFont();

	//
	// overrides of icontextbutton
	//
	virtual bool HasButton();
	virtual bool OnCommand( EPropWnd* pParent , WPARAM wParam , LPARAM lParam );
	virtual CString GetTextValue();

};

#endif // !defined(AFX_EPROPERTYFONT_H__3EDDB0E0_3725_4A6C_93BE_EC084AFA49B5__INCLUDED_)
