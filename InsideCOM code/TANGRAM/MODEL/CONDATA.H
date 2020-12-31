#ifndef __ConData_h__
#define __ConData_h__

///////////////////////////////////////////////////////////
//
//
// Condata.h - Declares CONNECTDATA operators for use with STL list.
//
//

//. STL
#include <new.h>
#include <algorithm>
#include <xmemory>
#include <list>

// OLE Control header for CONNECTDATA.
#include <ocidl.h> 

///////////////////////////////////////////////////////////
//
// Global operators needed by the STL list container. 
//
bool operator==(const CONNECTDATA& lhs, const CONNECTDATA& rhs);
bool operator!=(const CONNECTDATA& lhs, const CONNECTDATA& rhs);
bool operator<(const CONNECTDATA& lhs, const CONNECTDATA& rhs);
bool operator>(const CONNECTDATA& lhs, const CONNECTDATA& rhs);
bool operator<=(const CONNECTDATA& lhs, const CONNECTDATA& rhs) ;
bool operator>=(const CONNECTDATA& lhs, const CONNECTDATA& rhs) ;
void swap(const CONNECTDATA& lhs, const CONNECTDATA& rhs);

///////////////////////////////////////////////////////////
//
// Definitions of STL list containing CONNECTDATA structures.
//
typedef std::list<CONNECTDATA> CConnectDataList;


#endif __ConData_h__