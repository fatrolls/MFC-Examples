#include <windows.h>
#include <stdio.h>

/* Kill.c: Kill a process given its Process ID on the command line
 */

int main(int argc, char **argv) {

	HANDLE process;
	DWORD PID;

	if ( 2 != argc ) {
		fprintf(stderr, "\nUsage: kill <PID>");
		return 1;
	}
	
	PID = strtoul(argv[1], NULL, 0);	// base 0 allows 0x prefix for hex input...

	process = OpenProcess(PROCESS_TERMINATE, 0, PID);
	TerminateProcess(process, (unsigned)-1);
	return 0;
}

	

