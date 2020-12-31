// EPropertySeparator.cpp: implementation of the EPropertySeparator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EPropListCtrl.h"
#include "EPropertySeparator.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EPropertySeparator::EPropertySeparator( IPropertyHost* pHost , const CString& sName ) : EProperty( pHost , sName , NULL )
{
}

EPropertySeparator::~EPropertySeparator()
{
}

int EPropertySeparator::GetHeight( CDC* pDC )
{
	int h = 5;

	if( m_sName.GetLength() > 0 )						//this is a thin seperator without key or value
	{
		h = 19;
	}

	return h;
}

COLORREF EPropertySeparator::GetColorKey( EPropWnd* pCtrl )
{
	COLORREF c = EProperty::GetColorKey(pCtrl);			//default

//	if( m_sName.GetLength() > 0 )						//this is a thin seperator without key or value
	{
		c = pCtrl->GetColorPaneKeyActive();				//RGB(100,100,100);
	}

	return c;
}

void EPropertySeparator::Draw( CDC* pDC ,  EPropWnd* pCtrl )
{
	pDC->FillSolidRect( &m_Rect , GetColorKey(pCtrl) );
}

bool EPropertySeparator::IsBoldKey()
{
	return true;
}

bool EPropertySeparator::IsSelectable()
{
	return false;
}
