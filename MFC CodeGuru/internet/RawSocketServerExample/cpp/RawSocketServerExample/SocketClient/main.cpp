////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\..\SocketServer\names.h"
#include "RawSocket.h"

int Error(LPCTSTR Message)
{
	int nErr = GetLastError();
	//cerr << _T("\nError:#") << nErr << _T(" : ") << Message << _T("\n");
	_ftprintf(stderr, _T("\nError:#%d : %s\n"),nErr,Message);
	return 1;
}
int main (int argc, char* argv[])
{
	if (!AfxSocketInit())
		return Error(_T("\nCannot initialize socket\n"));

	if (argc < 3)
		return Error(_T("\nPleace specify Server x.x.x.x:y\n"));

	int nPort = atoi(argv[2]);
#ifndef _UNICODE
	CString strIP = argv[1];
#else
	wchar_t tempstr[200];
	MultiByteToWideChar (CP_ACP, 0, argv[1], -1, tempstr, 200);
	CString strIP = tempstr;
#endif
	while(1)
		{
		try
		{
		CWizReadWriteSocket socket;

		if(!socket.Connect(strIP, nPort))
			return Error(_T("Cannot connect to server"));

#if 0
		char buff[500];
		const char *Res = NULL;
		int  Len;
		for (int i = 0; i < nNames; i++)
			{
			CString str = Names[i][0];
#ifdef _UNICODE
			WideCharToMultiByte(CP_ACP, 0, str, -1, buff, 500, NULL, NULL);
			Res = buff;
#else
			Res = str;
#endif
			Len = strlen(Res);
			u_long nt_Len = htonl(Len);
			socket.Write (&nt_Len, sizeof(nt_Len));
			socket.Write (Res, Len);
			_ftprintf(stderr, _T("\n%s"),Names[i][0]);
			int r = -1;
			if ((r = socket.Read(&nt_Len, sizeof(nt_Len))) < sizeof(Len))
				goto finish;
			Len = ntohl (nt_Len);
			if ((r = socket.Read(buff, Len)) < Len)
				goto finish;
			buff[Len] = 0;			
			str = buff;

			_ftprintf(stderr, _T(" %s"),LPCTSTR(str));
			if (str != Names[i][1])
				{
				//cerr << _T(" Error! must be ") << Names[i][1];
				_ftprintf(stderr, _T(" Error! must be %s"),Names[i][1]);
				}
			} // for i
#else
		for (int i = 0; i < nNames; i++)
			{
			if (!socket.WriteString (Names[i][0]))
				goto finish;
			_ftprintf(stderr, _T("\n%s"),Names[i][0]);
			TCHAR buff[500];
			int nLen = socket.ReadString (buff,500);
			if (nLen == 0)
				goto finish;
			_ftprintf(stderr, _T(" %s"),buff);

			for (int j = 0; j < nLen; j++)
				if (buff [j] != Names[i][1][j])
					break;
			if (j != nLen || Names[i][1][nLen] != 0)
				_ftprintf(stderr, _T(" Error! must be %s"),Names[i][1]);
			} // for i
#endif
		}
		catch(CFileException*)
			{
			goto finish;
			}
		} // while 1
	return 0;
finish:
	_ftprintf(stderr, _T("Connection Terminated"));
	return 0;
}

