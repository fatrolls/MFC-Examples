// FrequencyCtrl.cpp: Implementierung der Klasse CFrequencyCtrl.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FrequencyCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CFrequencyCtrl::CFrequencyCtrl()
{
}

CFrequencyCtrl::~CFrequencyCtrl()
{
}

CString CFrequencyCtrl::OnFormatText() const
{
	CString strFormattedText;

	const int nFreq = GetPos();

	switch(nFreq)
	{
	case 927:
	case 1004:
		strFormattedText = "SWR3";
		break;

	case 1002:
		strFormattedText = "Classic 1";
		break;

	case 948:
	case 1020:
		strFormattedText = "Spice Radio";
		break;

	case 931:
		strFormattedText = "Easy, Gotti!";
		break;

	case 953:
		strFormattedText = "Radio Gaga";
		break;

	case 1047:
	case 1064:
		strFormattedText = "Radio ISS";
		break;

/*
	case 984: // What a stupid test...
		strFormattedText = "Radio Nice-Music-But-Damn-Long-Name";
		break;
*/

	default:
		strFormattedText.Format("%.1fMHz", (double)nFreq / 10.0);
	}

	return strFormattedText;
}
