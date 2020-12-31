#include "stdafx.h"
#include "student.h"

IMPLEMENT_DYNAMIC(CStudent, CObject)

#ifdef _DEBUG
void CStudent::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
	dc << "m_strName = " << m_strName << "\nm_nGrade = " << m_nGrade;
}
#endif // _DEBUG
