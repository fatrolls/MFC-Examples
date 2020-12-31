/*
Module : DTWINVER.H
Purpose: Interface of a function to perform
         version detection on OS
Created: PJN / DATE/2 / 11-05-1996
History: None

Copyright (c) 1996 by PJ Naughter.  
All rights reserved.

*/

#ifndef __DTWINVER_H__                                          

////////////////////////////////// Includes ///////////////////////////////////
#include "win32sup.h"



////////////////////////////////// defines ////////////////////////////////////

//values which get stored in [OS_VERSION_INFO].dwEmulatedPlatformId 
//and [OS_VERSION_INFO].dwUnderlyingPlatformId 
const DWORD PLATFORM_WIN32S =            0;
const DWORD PLATFORM_WINDOWS95 =         1;
const DWORD PLATFORM_NT_WORKSTATION =    2; 
const DWORD PLATFORM_WINDOWS =           3;  
const DWORD PLATFORM_WINDOWSFW =         4;
const DWORD PLATFORM_DOS =               5;
const DWORD PLATFORM_NT_SERVER =         6;
const DWORD PLATFORM_NT_ADVANCEDSERVER = 7;


typedef struct _OS_VERSION_INFO
{
  DWORD dwOSVersionInfoSize;
                  
  //What version of OS is being emulated
  DWORD dwEmulatedMajorVersion;
  DWORD dwEmulatedMinorVersion;
  DWORD dwEmulatedBuildNumber;
  DWORD dwEmulatedPlatformId;
  TCHAR szEmulatedCSDVersion[128];

  //What version of OS is really running                 
  DWORD dwUnderlyingMajorVersion;
  DWORD dwUnderlyingMinorVersion;
  DWORD dwUnderlyingBuildNumber;
  DWORD dwUnderlyingPlatformId;   
  TCHAR szUnderlyingCSDVersion[128];
} OS_VERSION_INFO, *POS_VERSION_INFO, FAR *LPOS_VERSION_INFO;
                                          
                                          
/////////////////////////////// Functions /////////////////////////////////////
BOOL EXPORT16 GetOSVersion(LPOS_VERSION_INFO lpVersionInformation);


#endif //__DTWINVER_H__