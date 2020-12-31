/*
 * AES Crypt for Windows (Command-Line)
 * Copyright (C) 2007, 2008, 2009, 2013
 *
 * Contributors:
 *     Glenn Washburn <crass@berlios.de>
 *     Paul E. Jones <paulej@packetizer.com>
 *     Mauro Gilardi <galvao.m@gmail.com>
 *
 * This software is licensed as "freeware."  Permission to distribute
 * this software in source and binary forms is hereby granted without a
 * fee.  THIS SOFTWARE IS PROVIDED 'AS IS' AND WITHOUT ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * THE AUTHOR SHALL NOT BE HELD LIABLE FOR ANY DAMAGES RESULTING FROM
 * THE USE OF THIS SOFTWARE, EITHER DIRECTLY OR INDIRECTLY, INCLUDING,
 * BUT NOT LIMITED TO, LOSS OF DATA OR DATA BEING RENDERED INACCURATE.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h> // malloc
#include <errno.h> // errno
#include <wchar.h>

#include "getopt.h"
#include "password.h"

/*
 *  read_password_error
 *
 *  Returns the description of the error when reading the password.
 */
const wchar_t* read_password_error(int error)
{
    if (error == AESCRYPT_READPWD_GETWCHAR)
        return L"user aborted";
    if (error == AESCRYPT_READPWD_TOOLONG)
        return L"password too long";
    if (error == AESCRYPT_READPWD_NOMATCH)
        return L"passwords don't match";
    return L"No valid error code specified!!!";
}

/*
 *  read_password
 *
 *  This function reads at most 'MAX_PASSWD_LEN'-1 characters
 *  from the console with echo disabled, putting them in 'buffer'.
 *  'buffer' MUST BE ALREADY ALLOCATED!!!
 *  When mode is ENC the function requests password confirmation.
 *
 *  Return value:
 *    >= 0 the password length (0 if empty password is in input)
 *    < 0 error (return value indicating the specific error)
 */

int read_password(wchar_t* buffer, encryptmode_t mode)
{
    wchar_t pwd_confirm[MAX_PASSWD_LEN+1]; // Used for password confirmation
    wint_t c;                              // Character read from input
    int chars_read;                        // Chars read from input
    wchar_t* p;                            // Password buffer pointer
    int i;                                 // Loop counter
    int match;                             // Do the two passwords match?

    // Round 1 - Read the password into buffer
    // (If encoding) Round 2 - read password 2 for confirmation
    for (i = 0; (i == 0) || (i == 1 && mode == ENC); i++)
    {
        // Choose the buffer where to put the password
        if (!i)
        {
            p = buffer;
        }
        else
        {
            p = pwd_confirm;
        }

        // Prompt for password
        if (i)
        {
            wprintf(L"Re-");
        }
        wprintf(L"Enter password: ");
        fflush(stdout);

        // Read from input and fill buffer till MAX_PASSWD_LEN chars are read
        chars_read = 0;
        while (((c = _getwch()) != L'\r') && (c != 0x0003))
        {
            // fill buffer till MAX_PASSWD_LEN
            if (chars_read <= MAX_PASSWD_LEN)
                p[chars_read] = (wchar_t) c;
            chars_read++;
        }

        if (chars_read <= MAX_PASSWD_LEN)
            p[chars_read] = '\0';

        wprintf(L"\r\n");

        // check for CTRL-C key press
        if (c == 0x0003)
        {
            // For security reasons, erase the password
            wmemset(buffer, 0, MAX_PASSWD_LEN+1);
            wmemset(pwd_confirm, 0, MAX_PASSWD_LEN+1);
            return AESCRYPT_READPWD_GETWCHAR;
        }

        // Check chars_read.  The password must be maximum MAX_PASSWD_LEN
        // chars.  If too long an error is returned
        if (chars_read > MAX_PASSWD_LEN)
        {
            // For security reasons, erase the password
            wmemset(buffer, 0, MAX_PASSWD_LEN+1);
            wmemset(pwd_confirm, 0, MAX_PASSWD_LEN+1);
            return AESCRYPT_READPWD_TOOLONG;
        }
    }

    // Password must be compared only when encrypting
    if (mode == ENC)
    {
        // Check if passwords match
        match = wcscmp(buffer, pwd_confirm);
        wmemset(pwd_confirm, 0, MAX_PASSWD_LEN+1);

        if (match != 0)
        {
            // For security reasons, erase the password
            wmemset(buffer, 0, MAX_PASSWD_LEN+1);
            return AESCRYPT_READPWD_NOMATCH;
        }
    }

    return chars_read;
}
