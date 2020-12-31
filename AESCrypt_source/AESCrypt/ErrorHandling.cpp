/*
 *  ErrorHandling.cpp
 *
 *  Copyright (C) 2007, 2008, 2013
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved.
 *
 *  This file defines various global error handling and reporting functions.
 *
 */

#include "stdafx.h"

/*
 * ReportError
 *
 * Report an error to the user
 */
void ReportError(   std::basic_string<TCHAR> message,
                    DWORD reason)
{
    LPTSTR error_string;

    if (reason != ERROR_SUCCESS)
    {
        if (::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                    FORMAT_MESSAGE_FROM_SYSTEM,
                    NULL,
                    reason,
                    0,
                    (LPTSTR)&error_string,
                    0,
                    NULL) != 0)
        {
            LPTSTR p = _tcschr(error_string, _T('\r'));
            if(p != NULL)
            {
                *p = _T('\0');
            }

            message += _T(":\n");
            message += error_string;

            ::LocalFree(error_string);
        }
    }

    ::MessageBox(NULL,message.c_str(),_T("AES Crypt Error"), MB_OK);
}


