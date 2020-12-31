#include <windows.h>
#include <stdio.h>

DWORD WINAPI mythread(LPVOID junk)
	{							// mythread
	puts("Hello from the thread!");
	return 0;
	}							// mythread

int main(int argc, char *argv[])
	{							// main
	DWORD tid;
	HANDLE hThread;

	hThread = CreateThread(NULL, 0, mythread, NULL,
	0, &tid);
	if (hThread)
		{						// thread has been started
		puts("Hello from the main program!");
		WaitForSingleObject(hThread, INFINITE);
		}						// thread has been started
	return 0;
	}							// main
