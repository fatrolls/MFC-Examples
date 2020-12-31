
// ---------------------------------------------------------------------------------------------------------
//
// CFastString class
// 
// Purpose: Speed-Optimized String class
//          The Microsoft CString class is optimized for low memory consumption but not for speed.
//          If a CString has 1000 Bytes and you append 30 Bytes it will reallocate 1030 Bytes.
//          CFastString duplicates the memory each time more memory is required and so avoids unnecessary reallocations
//          Allocating memory on the heap is slow and should be avoided where ever possible
//
// Tipp:    To understand what's going on in CString study the source code in STRCORE.CPP
//
// Author:  ElmüSoft (www.netcult.ch)
//
// ---------------------------------------------------------------------------------------------------------

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif


class CFastString
{
public:
	CFastString(DWORD u32_InitialSize);
	void AppendBuffer(const TCHAR* t_Data, int s32_Characters=-1);
	void AppendString(CString& s_Data);
	void Empty();
	BSTR AllocSysString();
	CString GetString();

private:
	CString ms_String;
	DWORD   mu32_Allocated;
};




