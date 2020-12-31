#include "ConData.h"

///////////////////////////////////////////////////////////
//
// Definitions to allow us to use the CONNECTDATA in a list.
//

bool operator==(const CONNECTDATA& lhs, const CONNECTDATA& rhs)
{
	return ((lhs.pUnk == rhs.pUnk) && (lhs.dwCookie == rhs.dwCookie)) ;
}


bool operator!=(const CONNECTDATA& lhs, const CONNECTDATA& rhs)
{
	return !operator==(lhs, rhs) ;
}


bool operator<(const CONNECTDATA& lhs, const CONNECTDATA& rhs)
{
	return (lhs.pUnk < rhs.pUnk) ;
}

bool operator>(const CONNECTDATA& lhs, const CONNECTDATA& rhs)
{
	return (lhs.pUnk > rhs.pUnk) ;
}

bool operator<=(const CONNECTDATA& lhs, const CONNECTDATA& rhs)
{
	return (lhs.pUnk <= rhs.pUnk) ;
}

bool operator>=(const CONNECTDATA& lhs, const CONNECTDATA& rhs)
{
	return (lhs.pUnk >= rhs.pUnk) ;
}

void swap(CONNECTDATA& lhs, CONNECTDATA& rhs)
{
	CONNECTDATA x ;
	x.dwCookie = lhs.dwCookie ;
	lhs.dwCookie = rhs.dwCookie ;
	rhs.dwCookie = x.dwCookie ;

	x.pUnk = lhs.pUnk ;
	lhs.pUnk = rhs.pUnk ;
	rhs.pUnk = x.pUnk ;
}
