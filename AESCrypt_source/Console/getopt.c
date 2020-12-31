/*
 *  getopt.c
 *  
 *  Copyright (C) 1998, 2009, 2013
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved.
 *
 *  Description:
 *      This file implements the 'getopt()' function found on UNIX systems.
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

#include <stdio.h>
#include <string.h>

/*
 *  Define global used by "getopt"
 */
wchar_t optflag = '-';
wchar_t *optarg = 0;
int     optind  = 1;
int     opterr  = 1;
int     optopt  = 0;


/*  
 *  getopt
 *
 *  Description:
 *      This funtion will parse command line options passed in the argv
 *      array in a program's main() routine.
 *
 *  Parameters:
 *      argc
 *          The argument count passed to main()
 *      argv
 *          The argument array passed to main()
 *      option_string
 *          The string of options.  The string contains letters representing
 *          the single character options.  If an option requires an argument
 *          to follow, a ":" is placed after the option in the option string.
 *          (That implies that ":" is not a valid option character).  Options
 *          are preceded by "optflag" character (default is "-").  Two
 *          option characters together (i.e., "--" when using the default
 *          option flag) on the command line signals getopt to stop processing
 *          options and return EOF.
 *
 *  Returns:
 *      This function will return the character of the current option, "?"
 *      if the option on the command line is invalid, or EOF once the end
 *      of the options has been reached.  Any errors encountered during
 *      the processing of the command line will result in messages displayed
 *      to STDERR unless the variable opterr is set to 0.  If an invalid
 *      option is found, the offending option character is stored in the
 *      variable optopt since the return value is "?".  (Note that an
 *      invalid option is either one not found in the option string or
 *      an option that should be followed with an argument, but is not.)
 *
 *  Comments:
 *      Like the UNIX version of getopt, this function must be used with care.
 *      If EOF is returned, getopt should never be called again.  If it
 *      is, the behavior should be considered "undefined".  If an option
 *      that requires an argument is, instead, followed by another
 *      option, the second option will mistakenly be taken as the argument.
 *      This is unfortunate, but is consistent with the UNIX version.
 *
 */
int getopt( int             argc,
            wchar_t * const *argv,
            const wchar_t   *option_string)
{
    int         current_option;
    wchar_t     *option_index;
    static int  array_index = 0;
    static int  end_of_options = 0;

    /*
     *  If we have already detected the end of the options array, return EOF.
     */
    if (end_of_options)
    {
        return EOF;
    }

    /*
     *  Check to see if we are at the end of our options array.
     */
    if (optind >= argc)
    {
        end_of_options = 1;
        return EOF;
    }

    /*
     *  We will support multiple arguments following a single argument flag.
     *  We will do this by using the static variable array_index.
     *  If array_index is 0, make sure that argv[optind][array_index]
     *  is optflag.  If not, we can assume we are at the end of the options.
     */
    if (!array_index)
    {
        /*
         *  Verify that the first character is the options flag.  If not,
         *  return EOF.
         */
        if (argv[optind][0] != optflag)
        {
            end_of_options = 1;
            return EOF;
        }

        /*
         *  Command line program historically denote a "STDIN" parameter
         *  as a single "-".  To be consistent with the UNIX version of
         *  getopt, we will return EOF if we see a singe optflag character,
         *  but we will not increment the optind value.
         */
        if (argv[optind][1] == '\0')
        {
            end_of_options = 1;
            return EOF;
        }

        /*
         *  If we see two optflag characters together, we will assume
         *  we should stop processing options.  We will increment the
         *  optind value so that the calling routine can process any
         *  addition arguments passed into main().
         */
        if (argv[optind][1] == optflag && argv[optind][2] == '\0')
        {
            optind++;
            end_of_options = 1;
            return EOF;
        }

        /*
         *  Move the array_index past the option flag
         */
        array_index++;
    }

    /*
     *  Get the next option character.
     */
    optopt = current_option = argv[optind][array_index++];

    /*
     *  Verify that it is a valid option.
     */
    if (current_option != ':' &&
        (option_index = wcschr(option_string, current_option)) != NULL)
    {
        /*
         *  Check to see if this option should have an argument by looking
         *  at the next character in the option_string.
         */
        if (*(option_index+1) == ':')
        {
            /*
             *  Check to see if the argument is sitting beside the
             *  option in the argv array element.
             */
            if (argv[optind][array_index] != '\0')
            {
                /*
                 *  Take the remainder of the argv element to be the string.
                 */
                optarg = &argv[optind][array_index];
            }
            else
            {
                /*
                 *  The argument must be in the next argv element.  We
                 *  will increment optind and try to locate the argument
                 *  there.
                 */
                optind++;

                /*
                 *  If we do not have an argument, we should report an error.
                 */
                if (optind >= argc)
                {
                    /*
                     *  Since we could not find an argument for the option,
                     *  we will report an error if the opterr variable has
                     *  not been set to 0.
                     */
                    if (opterr)
                    {
                        fwprintf(   stderr,
                                    L"%s: option requires an argument -- %c\n",
                                    argv[0],
                                    current_option);
                    }

                    /*
                     *  Re-assign the current option value so that we
                     *  return a '?' on errors.
                     */
                    current_option = '?';
                }
                else
                {
                    /*
                     *  We've found the argument in the next argv element.
                     *  We will assign the address to optarg and then
                     *  move optind to point to the next element.
                     */
                    optarg = argv[optind];
                }
            }

            /*
             *  Since this option took an argument, we will want to
             *  advance the optind value and reset the array_index
             *  in preparation for the next call to getopt().
             */
            optind++;
            array_index = 0;
        }
    }
    else
    {
        /*
         *  Since we have an illegal argument, we will report it if
         *  the opterr variable has not been set to 0.
         */
        if (opterr)
        {
            fwprintf(   stderr,
                        L"%s: illegal option -- %c\n",
                        argv[0],
                        current_option);
        }

        /*
         *  Re-assign the current option value so that we
         *  return a '?' on errors.
         */
        current_option = '?';
    }

    /*
     *  If we are processing options in a single argv element and
     *  we have reached the end of the string, reset the array_index
     *  value and advance optind.
     */
    if (array_index && argv[optind][array_index] == '\0')
    {
        array_index = 0;
        optind++;
    }

    return current_option;
}
