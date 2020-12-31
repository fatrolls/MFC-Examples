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

#include "stdafx.h"
#include "FastString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Constructor
CFastString::CFastString(DWORD u32_InitialSize)
{
	mu32_Allocated = max(64, u32_InitialSize);
	ms_String.GetBuffer(mu32_Allocated);
	ms_String.ReleaseBuffer(0);
}

void CFastString::AppendString(CString& s_Data)
{
	AppendBuffer(s_Data, s_Data.GetLength());
}

// Append string data in t_Data to the end of the FastString
// s32_Characters=-1 -> determine the length
void CFastString::AppendBuffer(const TCHAR* t_Data, int s32_Characters)
{
	if (s32_Characters == 0)
		return;

	if (s32_Characters < 0)
		s32_Characters = _tcslen(t_Data);

	DWORD u32_OldLen = ms_String.GetLength();
	DWORD u32_NewLen = u32_OldLen + s32_Characters;

	// Duplicate the buffer if too small
	while (u32_NewLen > mu32_Allocated)
	{
		mu32_Allocated *= 2;
	}

	// GetBuffer() automatically adds one character for the terminating zero
	// and copies the old content into the new buffer
	TCHAR* t_Buf = ms_String.GetBuffer(mu32_Allocated);
	
	// If compiled as UNICODE --> sizeof(TCHAR) = 2 
	memcpy(t_Buf + u32_OldLen, t_Data, s32_Characters * sizeof(TCHAR));

	ms_String.ReleaseBuffer(u32_NewLen);
}

void CFastString::Empty()
{
	// ATTENTION: Do NOT call ms_String.Empty() here! This would release the allocated buffer.
	// ReleaseBuffer(0) only sets the string length to zero and writes the '\0' character.
	ms_String.ReleaseBuffer(0);
}

BSTR CFastString::AllocSysString()
{
	return ms_String.AllocSysString();
}

CString CFastString::GetString()
{
	return ms_String;
}
