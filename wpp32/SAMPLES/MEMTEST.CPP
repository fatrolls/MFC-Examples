//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: MEMTEST.CPP
//
// "Memory Hog" program demonstrates Windows++ memory management.

#include "prefix.h"

MyApp myApp; // instantiate one and only app

// A typical small C++ object.
class memBlock {
	char str[32];
public:
	memBlock* next;
	memBlock()	{ strcpy(str, "hello, world"); }
};

const BIGOBJSIZE = 1<<16;					// a large chunk of storage

static memBlock * firstBlock = NULL;	// first small block in list
static long objSize = 0;					// size of current obj to alloc
static long numObj = 0;						// number of objects allocated

////////////////
// Show how many objects we allocated and memory stats too.
// 
void ShowTestResults()
{
	sprintf(theApp->scratch, 
		"Allocated %ld %ld-byte objects.", numObj, objSize);
	MsgBox(theApp->scratch,"MEMTEST");
}

//////////////////
// Program entry point
// 
void MyApp::main()
{
	if (MsgBox("Start small object test?\n", "MEMTEST", MB_YESNO)!=IDYES)
		return;

	HCURSOR save = Cursor = IDC_WAIT;		// set cursor to wait icon

	// Allocate as many little objects as we can.
	// Stop at 100,000 (otherwise it will take all day!).
	// The point is to prove that we can allocate many more than
	// 8K objects (the LDT limit).
	// 
	memBlock *mb;
	objSize = sizeof(memBlock);
	for (numObj=0; numObj < 100000; numObj++) {
		mb = new memBlock;				// alloc new block
		if (mb==NULL)
			break;
		mb->next = firstBlock;			// chain it..
		firstBlock = mb;					// ..to the list
	}
	ShowTestResults();

	// Free all small blocks
/*	while ((mb = firstBlock) != NULL) {
		firstBlock = mb->next;
		delete mb;
	}*/

	// Tell user we're about to start big obj test, but give him/her
	// a chance to cancel if we're in 386 enhanced mode.
	// 
	strcpy(theApp->scratch, "Starting big object test.");
	strcat(theApp->scratch, "\nWARNING: this may take several minutes!");
	if (MsgBox(theApp->scratch,"MEMTEST", MB_OKCANCEL)==IDCANCEL)
		return;
		
	// OK, start the big object test.
	// 
	objSize = BIGOBJSIZE;
	for (numObj = 0; numObj < 1000; numObj++) {
		char FAR* p = new char [BIGOBJSIZE];
		if (p==NULL)
			break;

		// actually write into all of memory
		for (int i=0; i<BIGOBJSIZE; i++)
			*p++ = 'X';
	}
	ShowTestResults();

	Cursor = save;		// restore cursor
}
