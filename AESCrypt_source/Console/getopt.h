/*
 *  getopt.h
 *  
 *  Copyright (C) 1998, 2009, 2013
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved.
 *
 *  Description:
 *      This file defines the 'getopt()' function found on UNIX systems.
 *      This version was written to facilitate porting UNIX-based software
 *      to other platforms which do not contain this function, including
 *      Windows NT.
 *
 *  Portability Issues:
 *      None.
 *
 *  Caveats:
 *      As with the UNIX version of this routine, this function is not
 *      thread-safe, nor should it ever be called once it returns EOF.
 */

/*
 *  Define the function prototype only.
 */
int getopt( int             argc,
            wchar_t * const *argv,
            const wchar_t   *option_string);
