/*
Module : DTIME.H
Purpose: Defines the interface to all DateTime components
Created: PJN / DATE/1 / 23-02-1996
History: None

Copyright (c) 1996 by PJ Naughter.  
All rights reserved.

*/

#ifndef __DTIME_H__


////////////////////////////////// Macros /////////////////////////////////////

#define __DTIME_H__

#ifndef __cplusplus
  #error Requires C++ compilation (use a .cpp suffix)
#endif                 



////////////////////////////////// Includes ///////////////////////////////////
#include "win32sup.h"      //Aids to compile on Win16 and Win32 and Dos
#include "datetime.h"      //Underlying date & time classes

#ifdef _WINDOWS    //UI classes/functions only available when compiling on Windows
#include "pushpin.h"       //Push pin button
#include "dentry.h"        //data entry routines
#endif


//////////////////////////////// Global functions /////////////////////////////

void AFX_EXT_API EXPORT16 InitDTime();         //Should be called prior to using DTime 
                                               //You would usually call this at the start of
                                               //InitInstance(), main() or wmain()
                                               
void AFX_EXT_API EXPORT16 TermDTime();         //Should be called after using DTime
                                               //You would usually call this in ExitInstance
                                               //or at the end of main() or wmain()

WORD AFX_EXT_API EXPORT16 GetDTimeVersion();   //returns the current version of the classes 
                                               //currently 0x0110, major version = HIBYTE = 1
                                               //major version = LOBYTE = 10

BOOL AFX_EXT_API EXPORT16 InitDTimeSettings(); //Initialise static members from registry (Win32)
                                               //or environment variables (Win16 or Dos)



#endif //__DTIME_H__