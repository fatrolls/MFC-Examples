// FinancialCalc.cpp: implementation of the CFinancialCalc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FinancialCalc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#include <math.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFinancialCalc::CFinancialCalc()
{

}

CFinancialCalc::~CFinancialCalc()
{

}

UINT CFinancialCalc::GetEMI(double dAmount, double dInterestRate, int nYears, InstallmentType itypeBasis)
{
	double dEMI = 0.0;

	double dROI = dInterestRate / 100;
	double dMonthlyROI = dROI / 12;

	int nMonths = nYears * 12; 

	double dNumerator = dAmount * dROI * pow((1 + (dMonthlyROI * (double)itypeBasis)),(nMonths / (double)itypeBasis)); 
	double dDenominator = (pow((1 + (dMonthlyROI * (double)itypeBasis)),(nMonths / (double)itypeBasis)) - 1) * 12;
	
	dEMI = dNumerator / dDenominator; 
    
	if (fmod(dEMI,1.0) > 0.5)
	{
		return (UINT)ceil(dEMI);
	}
	else
	{
		return (UINT)floor(dEMI);
	}
}

double CFinancialCalc::GetXIRR(double *pdInvestments, unsigned long *pulPeriods, int nCount)
{
	double dMaxRate = 1.0;
	double dMinRate = -0.99;

	double dXIRR = 0.0;
	double dGuessedRate = 0.0;
	
	double dInitialAmount = *(pdInvestments + 0);
	double dTrialValue;

	double dStartUpMax = Sum(dMaxRate,dInitialAmount,pdInvestments,pulPeriods,nCount);
	double dStartUpMin = Sum(dMinRate,dInitialAmount,pdInvestments,pulPeriods,nCount);
	
	if ((dStartUpMax >= 0) || (dStartUpMin <= 0))
	{
		return 0.0;
	}
	else
	{
//		int niteration = 0;
		while(true)
		{
			dGuessedRate = (dMaxRate + dMinRate) / 2;

			dTrialValue = Sum(dGuessedRate,dInitialAmount,pdInvestments,pulPeriods,nCount);
//			niteration++;
			if(sqrt(pow((dTrialValue / dInitialAmount) ,2)) < 0.0000000001)
			{
				dXIRR = dGuessedRate;
//				printf("\nNo of Iteration = %d\n",niteration);
				return dXIRR; 
			}
			else if (dTrialValue < 0.0)
			{
				dMaxRate = dGuessedRate;
			}
			else
			{
				dMinRate = dGuessedRate;
			}
		}
	}

	return 0.0;
}

double CFinancialCalc::Sum(double dRate, double dInitialAmount, double *pdInvestments, unsigned long *pulPeriods, int nCount)
{
	double dTotal = 0.0;
	
	for(int i=1;i<nCount;i++)
	{
		unsigned long ulPeriod = *(pulPeriods + i);
		double dReturn=pow((1.0+dRate),((double)ulPeriod/365));
		dTotal = dTotal + (*(pdInvestments + i) / dReturn);
	}

	return dTotal + dInitialAmount;
}