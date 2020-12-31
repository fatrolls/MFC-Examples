// FILTJECT.CPP -- Inject or remove filter driver for a specified device
// Copyright (C) 1999 by Walter Oney
// All rights reserved


#include "stdafx.h"

LPTSTR* CommandLineToArgv(LPTSTR cmdline, int* pargc);

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
	{							// DllMain
    return TRUE;
	}							// DllMain

///////////////////////////////////////////////////////////////////////////////

extern "C" void WINAPI InjectFilter(HWND hwnd, HINSTANCE hInst, LPCTSTR rawline, int nshow)
	{							// InjectFilter
	HDEVINFO hinfoset = INVALID_HANDLE_VALUE;

	// Determine which platform we're running on. You'll see why a bit later...

	OSVERSIONINFO vi = {sizeof(OSVERSIONINFO)};
	GetVersionEx(&vi);
	BOOL win98 = vi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS;

	// Parse arguments. We expect to be called this way:
	// rundll32 filtject,InjectFilter devname filtname [-Add | -Remove] [-Upper | -Lower] [-First | -LAst | -Before name | -AFter name]
	// Default is to inject 1st upper filter

	int argc;
	LPTSTR cmdline = _tcsdup(rawline);
	LPTSTR* argv = CommandLineToArgv(cmdline, &argc);
	if (!argv)
		{
		free(cmdline);
		return;
		}

	LPTSTR devname = NULL;
	LPTSTR filtname = NULL;
	LPTSTR existing = NULL;
	BOOL upper = TRUE;
	BOOL add = TRUE;
	
	enum POSITION {FIRST, LAST, BEFORE, AFTER, REMOVE} pos = FIRST;

	for (int iarg = 0; iarg < argc; ++iarg)
		{						// inspect arguments
		LPTSTR arg = argv[iarg];
		if (arg[0] == _T('-') || arg[0] == _T('/'))
			{					// parse option
			++arg;
			_tcslwr(arg);
			int len = _tcslen(arg);
			if (memcmp(arg, _T("upper"), min(len, 5) * sizeof(TCHAR)) == 0)
				upper = TRUE;
			else if (memcmp(arg, _T("lower"), min(len, 5) * sizeof(TCHAR)) == 0)
				upper = FALSE;
			else if (memcmp(arg, _T("first"), min(len, 5) * sizeof(TCHAR)) == 0)
				pos = FIRST;
			else if (memcmp(arg, _T("last"), min(len, 4) * sizeof(TCHAR)) == 0)
				pos = LAST;
			else if (memcmp(arg, _T("add"), min(len, 3 * sizeof(TCHAR))) == 0)
				pos = FIRST;
			else if (memcmp(arg, _T("remove"), min(len, 6) * sizeof(TCHAR)) == 0)
				pos = REMOVE;
			else
				{				// before or after something
				if (iarg == argc - 1)
					goto badargs;
				existing = argv[++iarg];
				if (memcmp(arg, _T("before"), min(len, 6) * sizeof(TCHAR)) == 0)
					pos = BEFORE;
				else if (memcmp(arg, _T("after"), min(len, 5) * sizeof(TCHAR)) == 0)
					pos = AFTER;
				else
					goto badargs;
				}				// before or after something
			}					// parse option

		else if (!devname)
			devname = arg;
		else if (!filtname)
			filtname = arg;
		else
			goto badargs;
		}						// inspect arguments

	if (!devname || !filtname)
		goto badargs;			// didn't get both required parameters

	if (pos == REMOVE)
		existing = filtname;	// so we'll search for it later on

	// Use SetupDi functions to locate each instance of the specified device

	hinfoset = SetupDiGetClassDevs(NULL, NULL, hwnd, DIGCF_PRESENT | DIGCF_ALLCLASSES);
	if (hinfoset == INVALID_HANDLE_VALUE)
		goto error;

	{							// local scope
	DWORD propcode = upper ? SPDRP_UPPERFILTERS : SPDRP_LOWERFILTERS;
	LPTSTR valname = upper ? _T("UpperFilters") : _T("LowerFilters");
	SP_DEVINFO_DATA devinfo = {sizeof(SP_DEVINFO_DATA)};

	for (DWORD devindex = 0; SetupDiEnumDeviceInfo(hinfoset, devindex, &devinfo); ++devindex)
		{						// for each device
		DWORD junk;
		TCHAR value[512];
		BOOL found = FALSE;
		if (SetupDiGetDeviceRegistryProperty(hinfoset, &devinfo, SPDRP_FRIENDLYNAME, &junk, (PBYTE) value, sizeof(value), NULL)
			&& _tcsicmp((LPCTSTR) value, devname) == 0)
			found = TRUE;
		if (!found
			&& SetupDiGetDeviceRegistryProperty(hinfoset, &devinfo, SPDRP_DEVICEDESC, &junk, (PBYTE) value, sizeof(value), NULL)
			&& _tcsicmp((LPCTSTR) value, devname) == 0)
			found = TRUE;
		if (!found)
			continue;			// not this device

		DWORD len;				// length of existing value
		HKEY hkey;				// (Win98) registry key handle
		DWORD regtype;			// (Win98) registry data type

		// If running in Win98, open the hardware key and use regular registry functions to get and store
		// the Upper/Lower Filters value. This is necessary because SetupDiSetDeviceRegistryProperty doesn't
		// store a correctly terminated MULTI_SZ value.

		if (win98)
			{					// open registry key
			hkey = SetupDiOpenDevRegKey(hinfoset, &devinfo, DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_ALL_ACCESS);
			if (hkey == INVALID_HANDLE_VALUE)
				continue;		// can't open hardware key
			len = sizeof(value);
			if (RegQueryValueEx(hkey, valname, NULL, &regtype, (PBYTE) value, &len) != 0 || len == 0)
				{				// no existing list
				len = sizeof(TCHAR);
				value[0] = 0;
				regtype = REG_BINARY;
				}				// no existing list
			}					// open registry key

		// If running in Win2K, SetupDiSetDeviceRegistryProperty works correctly

		else
			{					// use setup function
			if (!SetupDiGetDeviceRegistryProperty(hinfoset, &devinfo, propcode, &junk, (PBYTE) value, sizeof(value), &len) || len == 0)
				len = sizeof(TCHAR), value[0] = 0;		// empty filter list
			}					// use setup function

		// Locate the spot in the existing list of filters where we should insert the new one (or remove the old one)

		LPTSTR insert = value;
		if (pos == LAST)
			{					// put this filter last
			while (*insert)
				insert += _tcslen(insert) + 1;
			}					// put this filter last
		else if (pos != FIRST)
			{					// before or after something
			while (*insert && _tcsicmp(existing, insert) != 0)
				insert += _tcslen(insert) + 1;
			if (*insert && pos == AFTER)
				insert += _tcslen(insert) + 1;
			if (!*insert && pos == BEFORE)
				insert = value;	// default if "before" filter not found
			}					// before or after something

		// Calculate the number of existing bytes preceding the insertion/deletion spot

		int ncopy = (insert - value) * sizeof(TCHAR);

		// If removing a filter, construct a smaller filter string

		if (pos == REMOVE)
			{					// remove filter
			if (*insert)
				{				// filter was actually in the list
				LPTSTR remove = insert + _tcslen(insert) + 1;
				len -= (_tcslen(existing) + 1) * sizeof(TCHAR);
				ncopy = len - ncopy;
				memcpy(insert, remove, ncopy);
				if (len == sizeof(TCHAR))
					len = 0;	// nothing left

				// Rewrite the filter list

				if (win98)
					{			// remove via registry call
					if (len)
						RegSetValueEx(hkey, valname, 0, regtype, (PBYTE) value, len);
					else
						RegDeleteValue(hkey, valname);
					}			// remove via registry call
				else
					SetupDiSetDeviceRegistryProperty(hinfoset, &devinfo, propcode, (PBYTE) value, len);
				}				// filter was actually in the list
			}					// remove filter

		// Construct a new list of filter drivers

		else
			{					// add filter
			DWORD newlen;
			newlen = len + (_tcslen(filtname) + 1) * sizeof(TCHAR);

			LPTSTR newvalue = (LPTSTR) malloc(newlen);
			if (!newvalue)
				{					// can't get memory
				if (win98)
					RegCloseKey(hkey);
				continue;			// can't get this tiny bit of memory??
				}					// can't get memory

			PBYTE pcopy = (PBYTE) newvalue;
			if (ncopy)
				memcpy(pcopy, value, ncopy);
			pcopy += ncopy;

			if (add)
				{					// insert new name
				_tcscpy((LPTSTR) pcopy, filtname);
				pcopy += (_tcslen(filtname) + 1) * sizeof(TCHAR);

				ncopy = len - ncopy;
				memcpy(pcopy, insert, ncopy);
				}					// insert new name
			else
				{					// remove name
				}					// remove name

			// Install the new filter list

			if (win98)
				RegSetValueEx(hkey, valname, 0, regtype, (PBYTE) newvalue, newlen);
			else
				SetupDiSetDeviceRegistryProperty(hinfoset, &devinfo, propcode, (PBYTE) newvalue, newlen);

			free(newvalue);
			}						// add filter

		if (win98)
			RegCloseKey(hkey);
		}						// for each device
	}							// local scope

cleanup:
	if (hinfoset != INVALID_HANDLE_VALUE)
		SetupDiDestroyDeviceInfoList(hinfoset);
	free(argv);
	free(cmdline);
	return;

badargs:
	OutputDebugString(_T("InjectFilter - invalid arguments\n"));
	goto cleanup;

error:
	OutputDebugString(_T("InjectFilter - error trying to inject filter\n"));
	goto cleanup;
	}							// InjectFilter

///////////////////////////////////////////////////////////////////////////////
// Note -- CommandLineToArgvW exists already, but not the ANSI equivalent @&*%!

LPTSTR* CommandLineToArgv(LPTSTR cmdline, int* pargc)
	{							// CommandLineToArgv
	int argc = 0;
	while (*cmdline == _T(' ') || *cmdline == _T('\t'))
		++cmdline;				// skip leading blanks

	LPTSTR arg = cmdline;
	while (*arg)
		{						// count arguments
		TCHAR ch;
		while ((ch = *arg) == _T(' ') || ch == _T('\t'))
			*arg++ = _T(' ');	// skip leading blanks, replace tabs with blanks
		if (!ch)
			break;				// end of command line
		
		++argc;
		
		if (ch == _T('\"'))
			{					// quoted arg
			*arg++ = _T(' ');	// replace leading quote with space
			while ((ch = *arg) && ch != _T('\"'))
				++arg;			// find trailing quote
			}					// quoted arg
		else
			{					// unquoted arg
			while ((ch = *arg) && ch != _T(' ') && ch != _T('\t'))
				++arg;			// find space after arg
			}					// unquoted arg

		if (ch)
			*arg++ = 0;			// change ending delimiter to nul
		}						// count arguments

	if (!argc)
		return NULL;			// no arguments

	LPTSTR* argv = (LPTSTR*) malloc(argc * sizeof(LPTSTR));
	if (!argv)
		return NULL;			// can't allocate memory

	arg = cmdline;
	for (int iarg = 0; iarg < argc; ++iarg)
		{						// fill in argv array
		TCHAR ch;
		while ((ch = *arg) == _T(' '))
			++arg;				// skip to start of arg
		argv[iarg] = arg;
		arg += _tcslen(arg) + 1;	// skip to end of arg
		}						// fill in argv array

	*pargc = argc;
	return argv;
	}							// CommandLineToArgv
