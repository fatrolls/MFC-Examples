//=========================================================
//	TITLE:		Global 
//				for WinNT, MSVC 5.0, MFC 4.1
//				Copyright (C) Matrix Baltic Software
//				Vilnius, Lithuania
//	MODULE:		
//	PURPOSE:	
//
//	AUTHOR:		Audrius Vasiliauskas
// 
//	NOTES:		
//
//=========================================================



#include "stdafx.h"
#include "Version.h"

#ifndef __AFXDISP_H__
	#include <afxdisp.h>
#endif



static char THIS_TIMESTAMP[] = __TIMESTAMP__;
static char THIS_DATE[] = __DATE__;
static char THIS_TIME[] = __TIME__;



int GetBuildVersion(LPCSTR BaseDataTime,EBuildVersion type)
{
	int ret = 0;
	CString date;
	COleDateTime buildTime;
	COleDateTime baseTime;
	COleDateTime currentTime;
	COleDateTimeSpan spanElapsed;

	date = date + THIS_DATE + " " + THIS_TIME;
	if(buildTime.ParseDateTime(date, 0, LANG_ENGLISH) == FALSE)
		return -1;

	if(baseTime.ParseDateTime(BaseDataTime, 0, LANG_ENGLISH) == FALSE)
		return -1;

	ASSERT(baseTime < buildTime);

	currentTime = COleDateTime::GetCurrentTime();
	if(currentTime < buildTime || currentTime < baseTime)
		return -1;

	spanElapsed = buildTime - baseTime;

	switch(type)
	{
	case BUILD_DAY:
		ret = spanElapsed.GetDays();
		break;
	case BUILD_HOUR:
		ret = spanElapsed.GetHours();
		break;
	case BUILD_MIN:
		ret = spanElapsed.GetMinutes();
		break;
	case BUILD_SEC:
		ret = spanElapsed.GetSeconds();
		break;
	}

	return ret;
}
