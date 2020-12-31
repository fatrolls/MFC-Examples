// Rectangle.cpp: implementation of the CRectangle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PanningWindow.h"
#include "Shape.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRectangle::CRectangle( int nNumber, const CPoint pt )
	: CShape( CRect( pt.x, pt.y, pt.x + 90, pt.y + 90 ) , RGB( 255, 0, 0 ) )
{
	m_strNumber.Format( _T("%d"), nNumber );
}

CRectangle::~CRectangle()
{

}


void CRectangle::Draw( CDC *pDC ) const
{
	CRect rc = *this;
	ASSERT_VALID( pDC );
	pDC->FillSolidRect( rc, m_cr );

	//
	//	Don't care about the colour or the font really - this is just a demo!
	pDC->DrawText( m_strNumber, rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
}