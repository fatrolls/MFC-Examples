/* Generated by Together */

#ifndef EPROPERTYDOUBLE_H
#define EPROPERTYDOUBLE_H

#include "ENumericProperty.h"

class EPropertyDouble : public ENumericProperty
{

public:

//	virtual bool OnPropApply();

public:

    EPropertyDouble( IPropertyHost* pHost , const CString& sName , double* pProperty , const CString& sUnit , double dMinAllowed=0 , double dMaxAllowed=0 , bool bEnabled=true );
	virtual ~EPropertyDouble();

	//
	// ENumericProperty
	//

	virtual double GetNumericValue();
	virtual bool SetNumeric( double dVarValue );
	virtual int GetNumSignificantDigits();

};


#include <vector>
#include "IPropertyHost.h"
using namespace std;
class EPropertyMultiDouble : public EPropertyDouble , public IPropertyHost
{

	class Target
	{
	public:
		IPropertyHost* m_pHost;
		double* m_pSubject;
		Target( IPropertyHost* pHost , double* pSubject )
		{
			m_pHost    = pHost;
			m_pSubject = pSubject;
		}
		bool AskChange( double d )
		{
			return m_pHost->PropertyChanging( m_pSubject , &d );
		}
		void DoChange( double d )
		{
			*m_pSubject = d;
		}
	};

	double m_dSharedValue;			//valid if all subjects equal!
	vector<Target*> m_vTargets;

public:

	EPropertyMultiDouble( IPropertyHost* pHost , const CString& sName , const CString& sUnit="" , double dMinAllowed=0 , double dMaxAllowed=0 , bool bEnabled=true ) : EPropertyDouble( NULL , sName , &m_dSharedValue , sUnit , dMinAllowed , dMaxAllowed , bEnabled )
	{
		m_pHost = this;
		m_dSharedValue = 0;
	}

	~EPropertyMultiDouble()
	{
		while( m_vTargets.size()>0 )
		{
			delete m_vTargets.back();
			m_vTargets.pop_back();
		}
	}

	//
	// IPropertyHost
	//

    virtual bool PropertyChanging( const void* pProperty , void* pNewValue )
	{
		//
		// check if everyone allows change?
		//

		double dNewValue = *(double*)pNewValue;

		bool bChange = true;

		for( int i=0 ; i<m_vTargets.size() ; i++ )
		{
			if( m_vTargets[i]->AskChange(dNewValue)==false )
			{
				bChange = false;
				break;
			}
		}

		if( bChange )
		{
			for( int i=0 ; i<m_vTargets.size() ; i++ )
			{
				m_vTargets[i]->DoChange(dNewValue);
			}
		}

		return bChange;
	}

	//
	// this
	//
	void AppendSubject( IPropertyHost* pHost , double* pProperty )
	{
		m_vTargets.push_back( new Target(pHost,pProperty) );
	}

	CString Format(double d)
	{
		CString s;
		s.Format("%lf",d);

		bool bHasComma = (s.Find(',')>=0) || (s.Find('.')>=0);
		
		if( bHasComma )
		{
			s.TrimRight('0');
			s.TrimRight('.');
			s.TrimRight(',');
		}

		return s;
	}

	virtual CString GetTextValue()
	{
		CString s;

		bool bValid = true;

		if( m_vTargets.size()>=0 )
		{
			m_dSharedValue = *m_vTargets[0]->m_pSubject;

			double dMin = m_dSharedValue;
			double dMax = m_dSharedValue;

			for( int i=1 ; i<m_vTargets.size() ; i++ )
			{
				double d = *m_vTargets[i]->m_pSubject;

				if( d<dMin ) dMin=d;
				if( d>dMax ) dMax=d;
			}

			if( dMin!=dMax )
			{
//-----------------
				CString sMin = Format(dMin);
				CString sMax = Format(dMax);
				s.Format("[%s;%s]",sMin,sMax);
//-----------------
//				s = "**VARIES**";
//-----------------
				bValid = false;
			}
		}

		if( bValid )
		{
			s = EPropertyDouble::GetTextValue();
		}

		return s;
	}


};

#endif //EPROPERTYDOUBLE_H