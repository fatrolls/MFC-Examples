// Shape.h: interface for the CShape class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAPE_H__675D466A_02AF_11D2_B5CF_000000000000__INCLUDED_)
#define AFX_SHAPE_H__675D466A_02AF_11D2_B5CF_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CShape: protected CRect
{
public:
	CShape( const CRect &rc, const COLORREF cr );
	virtual ~CShape();
	virtual void Draw( CDC *pDC ) const = 0;

protected:
	COLORREF m_cr;
};



class CRectangle : public CShape
{
public:
	CRectangle( int nNumber, const CPoint pt );
	virtual ~CRectangle();
	virtual void Draw( CDC *pDC ) const;

private:
	CString m_strNumber;
};

#endif // !defined(AFX_SHAPE_H__675D466A_02AF_11D2_B5CF_000000000000__INCLUDED_)
