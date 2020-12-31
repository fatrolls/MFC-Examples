// ENumericProperty.cpp: implementation of the ENumericProperty class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EPropWndEdit.h"
#include "ENumericProperty.h"

#include <iostream>     
#include <sstream>     
#include <iomanip>
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ENumericProperty::ENumericProperty( IPropertyHost* pHost , const CString& sName , void* pProperty , const CString& sUnit , bool bEnabled , double dMinAllowed , double dMaxAllowed ) : EIconTextButtonProperty( pHost , sName , pProperty , bEnabled )
{
	m_sFixedUnit            = sUnit;
	m_dMax                  = dMaxAllowed;
	m_dMin                  = dMinAllowed;
	m_pUnitSymbol           = &m_sFixedUnit;
	m_dScale                = 1.0;
	m_pScaleMul             = NULL;
	m_pScaleDiv             = NULL;
	m_pUnitScaleHost        = NULL;
	m_nFormatFlags          = EIconTextButtonProperty::DEFAULT;
	m_nNumDecimals          = -1;
}

ENumericProperty::~ENumericProperty()
{
}

bool ENumericProperty::GetSortValueDouble( double& dValue )
{
	dValue = GetNumericValue();
	return true;
}

bool ENumericProperty::HasEdit()
{
	return m_pProperty != NULL;
}

ENumericProperty* ENumericProperty::AddSpecialCaseText( double dSpecialCaseValue , CString sText )
{
	SpecialCase sc(dSpecialCaseValue,sText);
	m_vSpecialCases.push_back(sc);
	return this;
}

CString ENumericProperty::GetSpecialCaseText( double dValue )
{
	CString s;

	int n = m_vSpecialCases.size();

	for( int c=0 ; c<n ; c++ )
	{
		if( dValue == m_vSpecialCases[c].m_dValue )
		{
			s = m_vSpecialCases[c].m_sText;
			break;
		}
	}

	return s;
}

ENumericProperty* ENumericProperty::SetScale( double dScale )
{
	m_dScale = dScale;
	return this;
}

ENumericProperty* ENumericProperty::SetScale( const double* pMultiply , const double* pDivide )
{
	m_pScaleMul = pMultiply;
	m_pScaleDiv = pDivide;
	return this;
}

ENumericProperty* ENumericProperty::SetUnit( const CString* pUnitSymbol )
{
	m_pUnitSymbol = pUnitSymbol;
	return this;
}

ENumericProperty* ENumericProperty::SetUnit( UnitScaleHost* pUnitScaleHost )
{
	m_pUnitScaleHost = pUnitScaleHost;
	return this;
}

double ENumericProperty::GetScale()
{
	double dScale = m_dScale;

	if( m_pUnitScaleHost )
	{
		CString s;
		dScale = m_pUnitScaleHost->GetUnitScale(s);
	}
	else
	{
		if( m_pScaleMul != NULL )
		{
			dScale *= (*m_pScaleMul);
		}

		if( m_pScaleDiv != NULL )
		{
			dScale /= (*m_pScaleDiv);
		}
	}

	return dScale;
}

ENumericProperty* ENumericProperty::SetStyle( UINT nFormatFlags , int nNumDecimals )
{
	m_nFormatFlags = nFormatFlags;
	m_nNumDecimals = nNumDecimals;
	return this;
}

CString ENumericProperty::GetTextValue()
{
	//
	// Get the numeric value from a type specific sub class (int, float..)
	//

	double dVarValue = (m_pProperty==NULL) ? 1.0 : GetNumericValue();

	//
	// Test if this value has some specific label
	//

	CString s = GetSpecialCaseText(dVarValue);

	//
	// If no specific label, format the numeric value
	//

	if( s.GetLength()==0 )
	{
		double dGuiValue = dVarValue * GetScale();		//scale to gui

		CString sUnit;
		CString sFormat;

		if( ( m_nFormatFlags&EIconTextButtonProperty::SCIENTIFIC) != 0 )
		{
			if( m_nNumDecimals!=-1 )
			{
				sFormat.Format( "%%1.%ie", m_nNumDecimals );
			}
			else
			{
				sFormat.Format( "%e" );
			}

			s.Format( sFormat , dGuiValue );
		}
		else
		{
			if( m_nNumDecimals!=-1 )
			{
				sFormat.Format( "%%.%ilf" , m_nNumDecimals );
				s.Format( sFormat , dGuiValue );
			}
			else
			{

//--------------------------------------
				s.Format("%lf",dGuiValue);		//default if something goes wrong in the "significant" calcultion..

				CString qq;
				qq.Format("%.15lf",dGuiValue);	//enough decimals..

				int n = qq.GetLength();
				int nCountSignificant = 0;
				int nNumSignificantDigits = GetNumSignificantDigits();	//get from type specific subclass

				for( int i=0 ; i<n ; i++ )
				{
					if( '0'<=qq[i] && qq[i]<='9' )
					{
						nCountSignificant++;
						if( nCountSignificant==nNumSignificantDigits )
						{
							s = qq.Left(i+1);
						}
					}
				}

//--------------------------------------

//				ostringstream os;
//				os.precision( m_nNumSignificantDigits );
//				os << dGuiValue;
//				string y = os.str();
//				s = y.c_str();
			}

			//
			// trim away trailing zeros and comma (is any..)
			//

			CString sComma;
			sComma.Format("%.1lf",1.2);
			char cComma = sComma[1];

			bool bHasComma = (s.Find(cComma)>0);
			
			if( bHasComma )
			{
				s.TrimRight('0');
				s.TrimRight(cComma);
			}
			
			if( (m_nFormatFlags&EIconTextButtonProperty::THOUSANDS) != 0 )
			{
				s = FormatThousands(s);
			}
		}
		
		if( m_pUnitScaleHost )
		{
			m_pUnitScaleHost->GetUnitScale(sUnit);
		}
		else
		{
			if( m_pUnitSymbol != NULL )
			{
				sUnit = *m_pUnitSymbol;
			}
		}

		if( sUnit.GetLength() > 0 )
		{
			s += " ";
			s += sUnit;
		}
	}

	return s;
}


bool ENumericProperty::OnPropApply()
{
	ASSERT( m_bSelected == true );
	ASSERT( m_pEdit     != NULL );
	ASSERT( IsEnabled() == true );

	bool bPropertyChanged = false;

	double d1;
	double d2;
	double dGuiValue;

	CString s;
	m_pEdit->GetWindowText(s);

	if( s != m_sInitialValueText )				//not the same
	{
//		if( (m_nFormatFlags & EIconTextButtonProperty::THOUSANDS) != 0 )
//		{
//		}







		double dOldGuiValue = GetNumericValue() * GetScale();

		bool bValid = true;

		s.Remove(' ');
		s.Remove( GetThousandSeparator() );

		int nHex = 0;
		if( sscanf(s,"0x%x",&nHex)==1 )
		{
			dGuiValue = nHex;
		}
		else if( sscanf(s,"%lf/%lf",&d1,&d2)==2 )
		{
			dGuiValue = d1/d2;
		}
		else if( sscanf(s,"%lf*%lf",&d1,&d2)==2 )
		{
			dGuiValue = d1*d2;
		}
		else if( sscanf(s,"%lf+%lf",&d1,&d2)==2 )
		{
			dGuiValue = d1+d2;
		}
		else if( sscanf(s,"%lf-%lf",&d1,&d2)==2 )
		{
			dGuiValue = d1-d2;
		}
		else if( sscanf(s,"%lf",&d1)==1 )			//normal situation, entering a new number
		{
			dGuiValue = d1;
		}
		else if( sscanf(s,"/%lf",&d1)==1 )
		{
			dGuiValue = dOldGuiValue/d1;
		}
		else if( sscanf(s,"*%lf",&d1)==1 )
		{
			dGuiValue = dOldGuiValue*d1;
		}
		else if( sscanf(s,"+%lf",&d1)==1 )
		{
			dGuiValue = dOldGuiValue+d1;
		}
		else if( sscanf(s,"-%lf",&d1)==1 )
		{
			dGuiValue = dOldGuiValue-d1;
		}
		else
		{
			bValid = false;
		}

		if( bValid )
		{
			double dVarValue = dGuiValue / GetScale();		//gui -> var

			if( (m_dMin==0 && m_dMax==0) || (m_dMin<=dVarValue && dVarValue<=m_dMax) )	//within range?
			{
				bPropertyChanged = SetNumeric(dVarValue);
			}
		}
	}

	return bPropertyChanged;
}
