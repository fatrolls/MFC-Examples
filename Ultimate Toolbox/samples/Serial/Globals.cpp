#include "stdafx.h"
#include "Globals.h"

CString GetAppDir()
{

	LPTSTR	clStr = GetCommandLine();
	LPTSTR	buf;
	CString string;
	int 	loop;

	//create the temp buffer
	buf = new TCHAR[ lstrlen(clStr) + 1 ];

	//copy the command line and check to see if the first character is a quote
	if(clStr[0] == '\"')
		lstrcpy(buf,&clStr[1]);
	else
		lstrcpy(buf,clStr);


	//check to see if the command line is empty
	loop = 0;
	if(lstrlen(buf) > 0){

		loop = lstrlen(buf);
		while(loop > 0){
			if(buf[loop]== _T('.')){
				  break;
			}
			loop --;
		}
		while(loop > 0){
			if(buf[loop]== _T('\\')){
				buf[loop] = 0;
				  break;
			}
			loop --;
		}
	}

	if(loop == 0){
		
		delete[] buf;

		//create the temp buffer
		buf = new TCHAR[MAX_PATH + 1];
		 
		_tgetcwd(buf,255);
	}

	string = buf;

	delete[] buf;

	return string;
}

void PumpMessages()
{
	static MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}