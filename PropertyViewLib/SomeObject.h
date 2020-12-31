// SomeObject0.h: interface for the SomeObject0 class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SOMEOBJECT_H
#define SOMEOBJECT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IPropertyHost.h"

//#include "PropertyViewLib/EPropertyTextBlock.h"
////#include "PropertyViewLib/ITreeHost.h"
//
///*
//class ENoteProperty : public EPropertyTextblock
//{
//public:
//	ENoteProperty( IPropertyHost* pHost , const CString& sName , CString* pProperty );
//
//	virtual int  GetPreferedWidth( CDC* pDC );
//	virtual int  GetHeight();
//	virtual void Draw( CDC* pDC ,  EPropListCtrl* pView , const CRect& r );
//
//};
//*/



class SomeObject1 : public IPropertyHost
{

private:

	double   m_d00;
	double   m_d01;
	double   m_d02;
	double   m_d03;

	double   m_d10;
	double   m_d11;
	double   m_d12;
	double   m_d13;

	double*  m_pDoubles;

public:

	SomeObject1();
	virtual ~SomeObject1();

	//
	// IPropertyHost
	//
    virtual void GetProperties( EPropList& PropList );

};

class SomeObject0 : public IPropertyHost
{

private:

	double        m_dDouble;
	float         m_fFloat;
	int           m_nInt;
	unsigned int  m_uInt;
	unsigned char m_uChar;

	int           m_nCentimeters;

	double   m_dAngle;
	COLORREF m_cColor;
	CString  m_sName;
	int      m_nCombo;
	bool     m_bBool;
	CString  m_sTextblock;
	CString  m_sReadOnlyString;
	double   m_dLargeNumber;

	bool   m_bSizeEnabled;
	double m_dWidth;
	double m_dHeight;


	COLORREF m_cNewColor;

	double   m_dMultiDouble1;
	double   m_dMultiDouble2;
	double   m_dMultiDouble3;
	double   m_dMultiDouble4;

public:

	SomeObject0();
	virtual ~SomeObject0();
//	void AddAnother();
//	void RemoveAnother();

	//
	// IPropertyHost
	//
    virtual void GetProperties( EPropList& PropList );
	virtual bool PropertyChanging( const void* pProperty , void* pNewValue );
	virtual bool IsPropertyEnabled( const void* pProperty );

	//
	// ITreeHost
	//
//	virtual CString GetTreeLabel();
//	virtual void    GetTreeChildren( IHostList* pList );
//	virtual void    GetTreeContextMenu( EContextMenu* pMenu );
//	virtual bool    OnTreeContextCommand( int nCommand );
//	virtual int     GetTreeIcon();

};

#endif // !defined(AFX_SomeObject0_H__4796102F_9249_40C5_B52E_B186E0E498D8__INCLUDED_)
