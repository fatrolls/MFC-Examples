// FrequencyCtrl.h: Schnittstelle für die Klasse CFrequencyCtrl.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_FREQUENCYCTRL_H_)
#define _FREQUENCYCTRL_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RoundSliderCtrl.h"

class CFrequencyCtrl : public CRoundSliderCtrl  
{
public:
	CFrequencyCtrl();
	virtual ~CFrequencyCtrl();

protected:
	virtual CString OnFormatText() const;
};

#endif // !defined(_FREQUENCYCTRL_H_)
