// FrequenceCtrl.cpp: Implementierung der Klasse CFrequenceCtrl.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "FrequenceCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CFrequenceCtrl::CFrequenceCtrl()
{
}

CFrequenceCtrl::~CFrequenceCtrl()
{
}

CString CFrequenceCtrl::OnFormatText(const CString& strText)
{
	CString strFormattedText;
	strFormattedText.Format("%.1fMHz", 87.5+GetPos()/360.0*20.6);
	return strFormattedText;
}
