/* Generated by Together */

#include "stdafx.h"
#include "IPropertyHost.h"
#include "EPropertyCheck.h"

#include "SetRawPixels.h"
#include "CheckOn.h"
#include "CheckOnDisabled.h"
#include "CheckOff.h"
#include "CheckOffDisabled.h"

CString EPropertyCheck::GetTextValue()
{
//----
//	bool bCheck = *m_pProperty;
//	return bCheck ? "YES" : "NO";
//----
	return "";
}
int EPropertyCheck::GetIconWidth()
{
	return 13;
}

EPropertyCheck::EPropertyCheck( IPropertyHost* pHost , const CString& sName , bool* pProperty ) : EIconTextButtonProperty( pHost , sName , pProperty , true )
{
}

EPropertyCheck::~EPropertyCheck()
{
}

int EPropertyCheck::GetHeight( CDC* pDC )
{
	return 3 + 13 + 3;
}

void EPropertyCheck::DrawIcon( CDC* pDC , EPropWnd* pParent , const CRect& Rect )
{
	bool bCheck = *((bool*)m_pProperty);

	int* pImage = IsEnabled() ? ( bCheck ? pCheckOn : pCheckOff ) : ( bCheck ? pCheckOnDisabled : pCheckOffDisabled );

	CRect r;
	r.left   = Rect.left;
	r.top    = Rect.top;
	r.right  = Rect.left + pCheckOn[0];
	r.bottom = Rect.top + pCheckOn[1];
	SetRawPixels( pDC , pImage , &r );

//-----------

//	CRect r = Rect;
//
//	pDC->SelectStockObject( BLACK_PEN );
//	if (IsEnabled())
//	{
//		pDC->SelectStockObject( WHITE_BRUSH );
//	}
//	else
//	{
//		pDC->FillSolidRect( &r , pParent->GetColorPaneKey() );
//		pDC->SelectStockObject( NULL_BRUSH );
//	}
//	pDC->Rectangle(&r);
//
//	CPoint p = r.TopLeft();
//
//	if( bCheck )
//	{
//		r.DeflateRect(3,3);
//
//		int x0 = r.left;
//		int y0 = r.top;
//		int x1 = r.right;
//		int y1 = r.bottom;
//
//		pDC->MoveTo(x0,y0);
//		pDC->LineTo(x1,y1);
//
//		pDC->MoveTo(x0+1,y0);
//		pDC->LineTo(x1,y1-1);
//		pDC->MoveTo(x0,y0+1);
//		pDC->LineTo(x1-1,y1);
//
//		pDC->MoveTo(x1-1  ,y0  );
//		pDC->LineTo(x0-1  ,y1  );
//		pDC->MoveTo(x1-1-1,y0  );
//		pDC->LineTo(x0-1  ,y1-1);
//		pDC->MoveTo(x1-1  ,y0+1);
//		pDC->LineTo(x0-1+1,y1  );
//	}

//-----------

}


bool EPropertyCheck::OnLButtonDown( EPropWnd* pParent , CPoint p )
{
	bool bPropertyChanged = false;

	if( m_IconRect.PtInRect(p) )
	{
		bPropertyChanged = ToggleCheck();
	}

	return bPropertyChanged;
}

bool EPropertyCheck::OnSpaceKey()
{
	return ToggleCheck();
}

bool EPropertyCheck::ToggleCheck()
{
	bool bPropertyChanged = false;

	if( IsEnabled() )
	{
		bool bCheck = *(bool*)m_pProperty;
		bCheck = !bCheck;

		if( m_pHost->PropertyChanging(m_pProperty,&bCheck) )
		{
			*(bool*)m_pProperty = bCheck;
			bPropertyChanged = true;
		}
	}

	return bPropertyChanged;
}