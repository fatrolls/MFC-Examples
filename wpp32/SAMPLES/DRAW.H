//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: DRAW.H
//
// Command IDs for DRAW
// 
#define ID_EDITDUP		11
#define ID_NEWLINE		12
#define ID_NEWRECT		13
#define ID_NEWELLIPSE	14
#define ID_FRONT			15
#define ID_BACK			16
#define ID_TOGGLEBUF		17

// Base IDs for edge and fill commands
#define ID_EDGE			20
#define ID_FILL			30

// Below are added to ID_EDGE or ID_FILL
#define ID_COLORBLACK	0
#define ID_COLORWHITE	1
#define ID_COLORRED		2
#define ID_COLORGREEN	3	
#define ID_COLORBLUE		4
#define ID_COLORNONE		5
#define ID_COLORRANDOM	6
#define ID_COLORLAST		7

#define NEDITCOMMANDS	9		// Number of items in Edit menu
#define POS_NEW			0		// relative pos in Edit menu of New command
