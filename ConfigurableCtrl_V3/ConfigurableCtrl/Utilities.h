#pragma once

#include <set>

inline BOOL IsKeyDown(int nVirtKey)
{
	return ((HIWORD(GetKeyState(nVirtKey))) == 0xFFFF)? TRUE : FALSE; 
}

inline BOOL IsKeyToggled(int nVirtKey)
{
	return ((LOWORD(GetKeyState(nVirtKey))) == 0x0001)? TRUE : FALSE; 
}

BOOL IsRectInRect(LPRECT prc1, LPRECT prc2);

LONG atox(TCHAR *pchr); // Converts an hexadecimal string to a long

template <class T> const T &Min(const T& a, const T&b)
{
	return (a < b)? a : b;
}

namespace DateUtils
{
	inline bool IsLeapYear(int iYear)
	{
		return iYear%4? false : (iYear%100? true : (iYear%400? false : true));
	}
	inline int LastDay(int iMonth, int iYear)
	{
		int iLastDay = 31;

		if (iMonth == 2)
			iLastDay = IsLeapYear(iYear)? 29 : 28;
		else if (iMonth == 4 || iMonth == 6 || iMonth == 9 || iMonth == 11)
			iLastDay--;

		return iLastDay;
	}
	DWORD GetDWordFromDMY(int iDay, int iMonth, int iYear);
	void GetDMYFromDWord(DWORD dwDate, int &iDay, int &iMonth, int &iYear);
}

class CDWordSet
{
public:
	inline BOOL Insert(const DWORD& dw);
	inline void Remove(const DWORD& dw);
	inline void Clear();
	inline DWORD First() const;
	inline DWORD Last() const;
	DWORD Next(const DWORD& dw) const;
	DWORD Prev(const DWORD& dw) const;
	void IncrementHIWORD(WORD wFromPos, BOOL Incr = TRUE);
	void IncrementLOWORD(WORD wFromPos, BOOL Incr = TRUE);
private:
	std::set<DWORD> m_DwordSet;
};

 BOOL CDWordSet::Insert(const DWORD& dw)
 {
	return m_DwordSet.insert(dw).second;
 }

void CDWordSet::Remove(const DWORD& dw)
{
	m_DwordSet.erase(dw);	
}

void CDWordSet::Clear()
{
	m_DwordSet.clear();
}

DWORD CDWordSet::First() const
{
	return *m_DwordSet.begin();
}

DWORD CDWordSet::Last() const
{
	return *--m_DwordSet.end();
}

