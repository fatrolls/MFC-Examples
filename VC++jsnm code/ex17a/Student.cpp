#include "stdafx.h"
#include "student.h"

IMPLEMENT_SERIAL(CStudent, CObject, 0)

void CStudent::Serialize(CArchive& ar)
{
	TRACE("Entering CStudent::Serialize\n");
	if (ar.IsStoring()) {
		ar << m_strName << m_nGrade;
	}
	else {
		ar >> m_strName >> m_nGrade;
	}
}

#ifdef _DEBUG
void CStudent::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
	dc << "m_strName = " << m_strName << "\nm_nGrade = " << m_nGrade;
}
#endif // _DEBUG
