/////////////////////////////////////////////////////////////////////
// file SerializeVersion.h
/////////////////////////////////////////////////////////////////////


#ifndef __SerializeVersion_H
#define __SerializeVersion_H

inline int SerializeVersion(CArchive& ar, const int VERSION, BOOL bThrowEx = TRUE)
{
	WORD version = VERSION;
	if (ar.IsStoring())
		{
		ar << version;
		return VERSION;
		}
	else
		{
		ar >> version;
		if (bThrowEx && VERSION != version)
			{
			ASSERT(0);
			AfxThrowArchiveException(CArchiveException::badSchema,ar.m_strFileName);
			}
		return version;
		}
}

#endif // __SerializeVersion_H
