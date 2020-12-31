// dumpexports.cpp

#include <windows.h>
#include <imagehlp.h>
#pragma comment(lib, "imagehlp")
#include <stdio.h>
#include <stddef.h>
#pragma hdrstop

PCSTR FormatMessageLastErrorA(DWORD dw = GetLastError())
{
	PSTR msg = NULL;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		dw,
		0,
		reinterpret_cast<PSTR>(&msg),
		256,
		NULL);
	return msg;
}

int main(int argc, char** argv)
{
	int result = EXIT_FAILURE;
	if (argc < 2)
	{
		fprintf(
			stderr,
			"Usage: %s exeOrDll\n"
			" Dumps named exports of exeOrDll.\n",
			argv[0] != NULL ? argv[0] : "dumpexports");
	}
	else
	{
		PIMAGE_DEBUG_INFORMATION pDebugInfo =
			MapDebugInformation(
				NULL,
				argv[1],
				NULL,
				0);
		if (pDebugInfo == NULL)
		{
			DWORD lastError = GetLastError();
			PCSTR msg =  FormatMessageLastErrorA(lastError);
			if (msg != NULL && msg[0] != 0)
			{
				fprintf(stderr, "%s", msg);
			}
			result = lastError; // questionable mixing main return with Win32 errors..
		}
		else
		{
			__try
			{
				PCSTR exportedNamesBegin = pDebugInfo->ExportedNames;
				PCSTR exportedNamesEnd   = exportedNamesBegin + pDebugInfo->ExportedNamesSize;
				if (exportedNamesBegin == NULL || exportedNamesEnd == exportedNamesBegin)
				{
					fprintf(stderr, "%s\n", "No exports?");
				}
				else
				{
					while (*exportedNamesBegin && exportedNamesBegin < exportedNamesEnd)
					{
						printf("%s\n", exportedNamesBegin);
						exportedNamesBegin += strlen(exportedNamesBegin) + 1;
					}
					result = EXIT_SUCCESS;
				}
			}
			__finally
			{
				UnmapDebugInformation(pDebugInfo);
			}
		}
	}
	return result;
}
