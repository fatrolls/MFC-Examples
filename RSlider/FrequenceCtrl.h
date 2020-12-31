// FrequencyCtrl.h: Schnittstelle für die Klasse CFrequencyCtrl.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FREQUENCYCTRL_H__CDEEB233_D871_11D2_B834_CB47E296C204__INCLUDED_)
#define AFX_FREQUENCYCTRL_H__CDEEB233_D871_11D2_B834_CB47E296C204__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RoundSliderCtrl.h"

class CFrequencyCtrl : public CRoundSliderCtrl  
{
public:
	CFrequencyCtrl();
	virtual ~CFrequencyCtrl();

	virtual CString OnFormatText(const CString& strText);
};

#endif // !defined(AFX_FREQUENCYCTRL_H__CDEEB233_D871_11D2_B834_CB47E296C204__INCLUDED_)
