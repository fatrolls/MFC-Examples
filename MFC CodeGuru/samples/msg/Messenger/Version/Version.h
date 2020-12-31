#ifndef VERSION_H
#define VERSION_H

enum EBuildVersion
{
	BUILD_YEAR = 0,	// not implemented
	BUILD_MONTH,    // not implemented
	BUILD_WEEK,		// not implemented
	BUILD_DAY,
	BUILD_HOUR,
	BUILD_MIN,
	BUILD_SEC
};
//Usage:
//COleDateTime		date(1996, 3, 1, 0, 0, 0);
//GetBuildVersion(date.Format(0, LANG_ENGLISH))
//			OR
//GetBuildVersion("1 Nov 1996 0:0:0")
int GetBuildVersion(LPCSTR BaseDataTime,EBuildVersion type = BUILD_DAY);

#endif