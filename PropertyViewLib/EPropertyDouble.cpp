
#include "stdafx.h"
#include "IPropertyHost.h"
#include "EPropListCtrl.h"
#include "EPropertyDouble.h"
#include "EPropWndEdit.h"
#include "math.h"

//bool EPropertyDouble::HasEdit()
//{
//	return true;
//}

EPropertyDouble::EPropertyDouble( IPropertyHost* pHost , const CString& sName , double* pProperty , const CString& sUnit , double dMinAllowed , double dMaxAllowed , bool bEnabled ) : ENumericProperty( pHost , sName , pProperty , sUnit , bEnabled , dMinAllowed , dMaxAllowed )
{
}

EPropertyDouble::~EPropertyDouble()
{
}

double EPropertyDouble::GetNumericValue()
{
	double d = *(double*)m_pProperty;
	return d;
}


bool EPropertyDouble::SetNumeric( double dVarValue )
{
	bool bPropertyChanged = false;

	double d = dVarValue;

	if( m_pHost->PropertyChanging(m_pProperty,&d) )
	{
		*(double*)m_pProperty = d;
		bPropertyChanged = true;
	}

	return bPropertyChanged;
}

int EPropertyDouble::GetNumSignificantDigits()
{
	return 12;
}
