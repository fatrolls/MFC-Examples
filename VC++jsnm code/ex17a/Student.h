// student.h

#ifndef _INSIDE_VISUAL_CPP_STUDENT
#define _INSIDE_VISUAL_CPP_STUDENT

class CStudent : public CObject
{
	DECLARE_SERIAL(CStudent)
public:
	CString m_strName;
	int m_nGrade;

	CStudent()
	{
		m_nGrade = 0;
	}

	CStudent(const char* szName, int nGrade) : m_strName(szName)
	{
		m_nGrade = nGrade;
	}

	CStudent(const CStudent& s) : m_strName(s.m_strName)
	{
		// copy constructor
		m_nGrade = s.m_nGrade;
	}

	const CStudent& operator =(const CStudent& s)
	{
		m_strName = s.m_strName;
		m_nGrade = s.m_nGrade;
		return *this;
	}

	BOOL operator ==(const CStudent& s) const
	{
		if ((m_strName == s.m_strName) && (m_nGrade == s.m_nGrade)) {
			return TRUE;
		}
		else {
			return FALSE;
		}
	}

	BOOL operator !=(const CStudent& s) const
	{
		// Let’s make use of the operator we just defined!
		return !(*this == s);
	}

	virtual void Serialize(CArchive& ar);

#ifdef _DEBUG
	void Dump(CDumpContext& dc) const;
#endif // _DEBUG
};

typedef CTypedPtrList<CObList, CStudent*> CStudentList;

#endif // _INSIDE_VISUAL_CPP_STUDENT
