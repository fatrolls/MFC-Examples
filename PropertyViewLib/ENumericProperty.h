// ENumericProperty.h: interface for the ENumericProperty class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENUMERICPROPERTY_H__B74ECABC_E561_4A5B_A9C2_D59151A7BA9A__INCLUDED_)
#define AFX_ENUMERICPROPERTY_H__B74ECABC_E561_4A5B_A9C2_D59151A7BA9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EIconTextButtonProperty.h"
#include <vector>

class ENumericProperty : public EIconTextButtonProperty
{

protected:

	//
	// someone to ask about unitscale and symbol
	//

	class UnitScaleHost
	{
	public:
		virtual double GetUnitScale( CString& sSymbol )
		{
			return 1.0;
		}
	};

	//
	//
	//

	class SpecialCase
	{
	public:
		double m_dValue;
		CString m_sText;
		SpecialCase( double dValue , CString sText )
		{
			m_dValue = dValue;
			m_sText  = sText;
		}
	};

	std::vector<SpecialCase> m_vSpecialCases;

protected:

	double  m_dScale;		//scale the property by this value before showing on screen (eg for showing value in another unit)
	CString m_sFixedUnit;
	const CString* m_pUnitSymbol;
	const double*  m_pScaleMul;
	const double*  m_pScaleDiv;
	double m_dMin;
	double m_dMax;
	UnitScaleHost* m_pUnitScaleHost;
	UINT m_nFormatFlags;
	int m_nNumDecimals;
//	int m_nNumSignificantDigits;

public:

	ENumericProperty( IPropertyHost* pHost , const CString& sName , void* pProperty , const CString& sUnit , bool bEnabled , double dMinAllowed , double dMaxAllowed );
	virtual ~ENumericProperty();

protected:

	CString GetSpecialCaseText( double dValue );
	double GetScale();
	CString GetTextValue();

protected:

	//
	// EProperty
	//
	virtual bool GetSortValueDouble( double& dValue );
	virtual bool OnPropApply();

	//
	// EIconTextButtonProperty
	//
	virtual bool HasEdit();

	//
	// this
	//
	virtual double GetNumericValue() = 0;
	virtual bool SetNumeric( double dVarValue ) = 0;
	virtual int GetNumSignificantDigits() = 0;

public:

	//
	// this
	//

	ENumericProperty* AddSpecialCaseText( double dSpecialCaseValue , CString sText );
	ENumericProperty* SetScale( double dScale );
	ENumericProperty* SetScale( const double* pMultiply , const double* pDivide );
	ENumericProperty* SetUnit( const CString* pUnitSymbol );
	ENumericProperty* SetUnit( UnitScaleHost* pUnitScaleHost );
	ENumericProperty* SetStyle( UINT nFormatFlags=EIconTextButtonProperty::DEFAULT , int nNumDecimals=-1 );
};

#endif // !defined(AFX_ENUMERICPROPERTY_H__B74ECABC_E561_4A5B_A9C2_D59151A7BA9A__INCLUDED_)
