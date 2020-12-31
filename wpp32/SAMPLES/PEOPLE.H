//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: PEOPLE.H
//
#ifndef PEOPLE_H
#define PEOPLE_H

#include <wpp.h>

////////////////
// Base dialog ID: after IDOK, IDCANCEL, etc.
// 
#define ID_BASE	10	

#define IDLB_PEOPLE		(ID_BASE + 0)
#define IDM_EDIT			(ID_BASE + 1)
#define IDM_EDITNEW		(ID_BASE + 2)
#define IDM_OKNEXT		(ID_BASE + 3)
#define IDM_OKPREV		(ID_BASE + 4)

#define IDSI_ABOUTICON	(ID_BASE + 9)
#define IDED_NAME			(ID_BASE + 10)
#define IDED_ADDR			(ID_BASE + 11)
#define IDED_CITY			(ID_BASE + 12)
#define IDCB_STATE		(ID_BASE + 13)
#define IDED_ZIP			(ID_BASE + 14)
#define IDED_PHONE		(ID_BASE + 15)
#define IDB_SELECTED		(ID_BASE + 16)

// The following must be consecutive
#define IDRBG_STATUS		(ID_BASE + 20)
#define IDB_FRIEND		(ID_BASE + 21)
#define IDB_BUSINESS		(ID_BASE + 22)
#define IDB_OTHER			(ID_BASE + 23)


#endif
