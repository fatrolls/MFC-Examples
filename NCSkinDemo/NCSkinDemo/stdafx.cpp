
// stdafx.cpp : source file that includes just the standard includes
// NCSkinDemo.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"


CString GetModulePath()
{
	TCHAR s_buf[MAX_PATH];
	s_buf[0] = 0x0;
	DWORD n_result = ::GetModuleFileName(NULL, s_buf, sizeof(TCHAR) * MAX_PATH);
	TCHAR	s_drive[MAX_PATH];
	s_drive[0] = 0x0;
	TCHAR s_dir[MAX_PATH];
	s_dir[0] = 0x0;
	/*errno_t n_err_no =*/ 
	_tsplitpath(s_buf, s_drive, s_dir, NULL, NULL);
	//assert(n_err_no == 0);
	_tcscpy_s(s_buf, s_drive);
	_tcscat_s(s_buf, s_dir);
	return CString(s_buf);
}