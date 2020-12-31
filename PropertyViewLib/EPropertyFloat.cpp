
#include "stdafx.h"
#include "IPropertyHost.h"
#include "EPropListCtrl.h"
#include "EPropertyFloat.h"
#include "EPropWndEdit.h"
#include "math.h"


EPropertyFloat::EPropertyFloat( IPropertyHost* pHost , const CString& sName , float* pProperty , const CString& sUnit , float fMinAllowed , float fMaxAllowed , bool bEnabled ) : ENumericProperty( pHost , sName , pProperty , sUnit , bEnabled , fMinAllowed , fMaxAllowed )
{
}

EPropertyFloat::~EPropertyFloat()
{
}

double EPropertyFloat::GetNumericValue()
{
	float f = *(float*)m_pProperty;
	return f;
}

bool EPropertyFloat::SetNumeric( double dVarValue )
{
	bool bPropertyChanged = false;

	float f = (float)dVarValue;

	if( m_pHost->PropertyChanging(m_pProperty,&f) )
	{
		*(float*)m_pProperty = f;
		bPropertyChanged = true;
	}

	return bPropertyChanged;
}

int EPropertyFloat::GetNumSignificantDigits()
{
	return 6;
}








