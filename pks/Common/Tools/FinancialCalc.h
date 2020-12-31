// FinancialCalc.h: interface for the CFinancialCalc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FINANCIALCALC_H__FF8AC1FF_8E5A_48FF_90DF_763F2CF04EB8__INCLUDED_)
#define AFX_FINANCIALCALC_H__FF8AC1FF_8E5A_48FF_90DF_763F2CF04EB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum InstallmentType
{
	None = -1,
	Monthly=1,
	Quarterly=3,
	HalfYearly=6,
	Yearly=12
};

class CFinancialCalc  
{
private:

	static double Sum(double dRate, double dInitialAmount, double *pdInvestments, unsigned long *pulPeriods, int nCount);

public:

	static UINT GetEMI(double dAmount, double dInterestRate, int nYears, InstallmentType itypeBasis = Monthly);
	static double GetXIRR(double *pdInvestments, unsigned long *pulPeriods, int nCount);
	CFinancialCalc();
	virtual ~CFinancialCalc();
};

#endif // !defined(AFX_FINANCIALCALC_H__FF8AC1FF_8E5A_48FF_90DF_763F2CF04EB8__INCLUDED_)
