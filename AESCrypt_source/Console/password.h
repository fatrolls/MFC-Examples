/*
 * password.h
 *
 * Copyright (C) 2007, 2008, 2009, 2013
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

#ifndef __AESCRYPT_PASSWORD_H__
#define __AESCRYPT_PASSWORD_H__

#define MAX_PASSWD_LEN  1024

typedef enum {UNINIT, DEC, ENC} encryptmode_t;

/*
 * Error codes for read_password function.
 */
#define AESCRYPT_READPWD_GETWCHAR    -5 
#define AESCRYPT_READPWD_TOOLONG     -6
#define AESCRYPT_READPWD_NOMATCH     -7

/*
 * Function Prototypes
 */
const wchar_t* read_password_error(int error);
int read_password(wchar_t* buffer,
                  encryptmode_t mode);

#endif // __AESCRYPT_PASSWORD_H__
