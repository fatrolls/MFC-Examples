#include "stdafx.h"
#include "utilities.h"

BOOL IsRectInRect(LPRECT prc1, LPRECT prc2)
{
	POINT pt1 = {prc1->left, prc1->top}, pt2 = {prc1->right, prc1->bottom};
	return PtInRect(prc2, pt1) && PtInRect(prc2, pt2);
}

LONG atox(TCHAR *pchr)
// Assume already prefixed with 0x - not even checking here - can add this later
// finishes with \0
{
	LONG l = 0, i;
	bool IsColorRef = false; // Is it a color in format #91A3B0 for instance? 
	const TCHAR chr[] = _T("0123456789ABCDEF");

	if (pchr[0] == '0' && (pchr[1] == 'x' || pchr[1] == 'X'))
		pchr += 2; // Standard hexadecimal number.
	else if (pchr[0] == '#')
	{
		pchr ++;
		IsColorRef = true; 
	}
	
	for (;;)
	{
		i = 0;

		while (chr[i] != *pchr && i < sizeof(chr)/sizeof(char)) i++;

		if (i == sizeof(chr)/sizeof(char))
			ASSERT("Alien character in hexadecimal string.");
	
		l |= i;

		if (!++pchr || !*pchr)
			break;

		l <<= 4;
	}
	if (IsColorRef)
	{
		LONG Flag1 = l >> 16;
		LONG Flag2 = (l << 16) & 0x00FF0000;
		l &= 0x0000FF00;
		l |= Flag1 | Flag2;
	}
	return l;
}

DWORD DateUtils::GetDWordFromDMY(int iDay, int iMonth, int iYear)
{
	DWORD dwDate = 0;	
	dwDate |= iYear;
	dwDate <<= 4;
	dwDate |= iMonth;
	dwDate <<= 8;
	dwDate |= iDay;

	return 	dwDate;
}

void DateUtils::GetDMYFromDWord(DWORD dwDate, int &iDay, int &iMonth, int &iYear)
{
	iDay = dwDate & 0x000000ff;
	iMonth = (dwDate & 0x00000f00) >> 8;
	iYear = (dwDate & 0xfffff000) >> 12;
}

DWORD CDWordSet::Next(const DWORD& dw) const
{
	std::set<DWORD>::const_iterator it = m_DwordSet.find(dw);

	if (it != (--m_DwordSet.end()) && it != (m_DwordSet.end()))
		return *++it;
	return -1;
}

DWORD CDWordSet::Prev(const DWORD& dw) const
{
	std::set<DWORD>::const_iterator it = m_DwordSet.find(dw);

	if (it != m_DwordSet.begin())
		return *--it;
	return -1;
}

void CDWordSet::IncrementHIWORD(WORD wFromPos, BOOL Incr /*= TRUE*/)
{
	std::set<DWORD> DwordSet;
	std::set<DWORD>::iterator It;

	if (Incr)
		for (It = m_DwordSet.begin(); It != m_DwordSet.end(); It++)
			DwordSet.insert(HIWORD(*It) >= wFromPos? MAKELONG(LOWORD(*It), HIWORD(*It) + 1) : *It);
	else
		for (It = m_DwordSet.begin(); It != m_DwordSet.end(); It++)
		{
			if (HIWORD(*It) < wFromPos)
				DwordSet.insert(*It);
			else if (HIWORD(*It) > wFromPos)
				DwordSet.insert(MAKELONG(LOWORD(*It), HIWORD(*It) - 1));
		}
	m_DwordSet = DwordSet; 
}

void CDWordSet::IncrementLOWORD(WORD wFromPos, BOOL Incr /*= TRUE*/)
{
	std::set<DWORD> DwordSet;
	std::set<DWORD>::iterator It;

	if (Incr)
		for (It = m_DwordSet.begin(); It != m_DwordSet.end(); It++)
			DwordSet.insert(LOWORD(*It) >= wFromPos? MAKELONG(LOWORD(*It) + 1, HIWORD(*It)) : *It);
	else
		for (It = m_DwordSet.begin(); It != m_DwordSet.end(); It++)
		{
			if (LOWORD(*It) < wFromPos)
				DwordSet.insert(*It);
			else if (LOWORD(*It) > wFromPos)
				DwordSet.insert(MAKELONG(LOWORD(*It) - 1, HIWORD(*It)));
		}
	m_DwordSet = DwordSet; 
}

