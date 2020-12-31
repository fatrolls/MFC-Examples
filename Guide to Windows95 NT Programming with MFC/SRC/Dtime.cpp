/*
Module : DTIME.cpp
Purpose: Defines the initialization routines for the DLL.
Created: PJN / DATE/1 / 22-02-1996
History: None

Copyright (c) 1995 by PJ Naughter.  
All rights reserved.

*/

/////////////////////////////////  Includes  //////////////////////////////////
#include "stdafx.h"  
#include <memory.h>
#include "win32sup.h"
#include "dtime.h"
#include "dtwinver.h"
#ifdef _WINDOWS
#include <afxdllx.h>
#endif



///////////////////////////////// Locals //////////////////////////////////////
#ifdef _WINDOWS
static AFX_EXTENSION_MODULE DtimeDLL = { NULL, NULL };
#endif


/////////////////////////////////  Macros  ////////////////////////////////////
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif         



/////////////////////////////// Implementation ////////////////////////////////
#ifdef _WINDOWS
#ifdef _WIN32
extern "C" int APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
  if (dwReason == DLL_PROCESS_ATTACH)
  {
    TRACE0("DTIME Extension DLL Initializing\n");

    // Extension DLL one-time initialization
    AfxInitExtensionModule(DtimeDLL, hInstance);

    // Insert this DLL into the resource chain
    new CDynLinkLibrary(DtimeDLL);
  }
  else if (dwReason == DLL_PROCESS_DETACH)
  {
    TRACE0("DTIME Extension DLL Terminating\n");

    // Extension DLL one-time deinitialization
    AfxTermExtensionModule(DtimeDLL);
  }

  return 1;   // ok
}
#else
extern "C" int CALLBACK LibMain(HINSTANCE hInstance, WORD, WORD, LPSTR)
{                                              
  TRACE0("DTIME Extension DLL Initializing\n");
  AfxInitExtensionModule(DtimeDLL, hInstance);
  return 1;
}       

extern "C" int FAR PASCAL _WEP(int)
{
  TRACE0("DTIME Extension DLL Terminating\n");
  return 1;
}

#endif //_WIN32
#endif //_WINDOWS

void InitDTime()
{   
  //Display some TRACE statements about the version of the DTime dll
  #ifdef _WIN32
    WORD wDTimeVer = ::GetDTimeVersion();
    CString sVer;
    sVer.Format(CString("%d.%02d"), HIBYTE(wDTimeVer), LOBYTE(wDTimeVer));

    #ifdef _UNICODE
    TRACE1("(32 bit Unicode Debug Build) Version: %s (C) PJ Naughter 1996\n", sVer);
    #else
    TRACE1("(32 bit Ascii Debug Build) Version: %s (C) PJ Naughter 1996\n", sVer);
    #endif
  #else
    WORD wDTimeVer = GetDTimeVersion();
    CString sVer;
    sVer.Format("%d.%02d", HIBYTE(wDTimeVer), LOBYTE(wDTimeVer));
    TRACE1("(16 bit Debug Build) Version: %s (C) PJ Naughter 1996\n", sVer); 
                   
    //Also add into the resource chain for Win16 here
    #ifdef _WINDOWS
    new CDynLinkLibrary(DtimeDLL);
    #endif
  #endif           
                 
  //Display some info about which OS we are running on                                                
  #ifdef _DEBUG
    OS_VERSION_INFO osvi;          
    memset(&osvi, 0, sizeof(OS_VERSION_INFO));
    osvi.dwOSVersionInfoSize = sizeof(OS_VERSION_INFO);
    GetOSVersion(&osvi);

    //generate a string based on the OS version to display
    CString sOSVer;
    switch (osvi.dwEmulatedPlatformId)
    {
      case PLATFORM_WIN32S:            sOSVer = _T("Win32s");                     break; 
      case PLATFORM_WINDOWS95:         sOSVer = _T("Windows 95");                 break;
      case PLATFORM_NT_WORKSTATION:    sOSVer = _T("Windows NT Workstation");     break;
      case PLATFORM_WINDOWS:           sOSVer = _T("Windows");                    break;
      case PLATFORM_WINDOWSFW:         sOSVer = _T("Windows For Workgroups");     break; 
      case PLATFORM_DOS:               sOSVer = _T("Dos");                        break;
      case PLATFORM_NT_SERVER:         sOSVer = _T("Windows NT Server");          break;
      case PLATFORM_NT_ADVANCEDSERVER: sOSVer = _T("Windows NT Advanced Server"); break;
      default:                         sOSVer = _T("Unknown");                    break;
    }
    CString sBuf;
    sBuf.Format(_T(" v%d."), osvi.dwEmulatedMajorVersion);  
    sOSVer += sBuf;
    sBuf.Format(_T("%02d"), osvi.dwEmulatedMinorVersion); 
    sOSVer += sBuf;
    sBuf.Format(_T(" Build:%d, underlying OS: "), osvi.dwEmulatedBuildNumber); 
    sOSVer += sBuf;
    switch (osvi.dwUnderlyingPlatformId)
    {
      case PLATFORM_WIN32S:            sBuf = _T("Win32s");                     break;
      case PLATFORM_WINDOWS95:         sBuf = _T("Windows 95");                 break;
      case PLATFORM_NT_WORKSTATION:    sBuf = _T("Windows NT Workstation");     break;
      case PLATFORM_WINDOWS:           sBuf = _T("Windows");                    break;
      case PLATFORM_WINDOWSFW:         sBuf = _T("Windows For Workgroups");     break;
      case PLATFORM_DOS:               sBuf = _T("Dos");                        break;
      case PLATFORM_NT_SERVER:         sBuf = _T("Windows NT Server");          break;
      case PLATFORM_NT_ADVANCEDSERVER: sBuf = _T("Windows NT Advanced Server"); break;
      default:                         sBuf = _T("Unknown");                    break;
    } 
    sOSVer += sBuf;
    sBuf.Format(_T(" v%d."), osvi.dwUnderlyingMajorVersion);
    sOSVer += sBuf;
    sBuf.Format(_T("%02d"), osvi.dwUnderlyingMinorVersion);
    sOSVer += sBuf;
    sBuf.Format(_T(" Build:%d"), osvi.dwUnderlyingBuildNumber); 
    sOSVer += sBuf;
    TRACE1("Running on OS: %s\n", sOSVer);
  #endif
}


void TermDTime()
{             
  //Empty the static CStrings stored in the
  //4 main classes. This avoids false
  //memory leak statements displayed when DTime 
  //is used by a Win16 app.          
  
  CDate::ClearStatics();
  CLDate::ClearStatics();
  CLTimeSpan::ClearStatics();
  CLTimeOfDay::ClearStatics();  
}
                   
                   
WORD GetDTimeVersion()
{
  return 0x010b;       //v1.0   Original Release
                       //v1.1   Port to Win16 / Dos
                       //v1.11  Now includes German translation, minor bug fixes
}


BOOL InitDTimeSettings()
{
  BOOL bSuccess = FALSE;

  BOOL bUseRegistry;
#ifdef _WIN32
  bUseRegistry = TRUE;
  
  OSVERSIONINFO osvi;
  GetVersionEx(&osvi);
  if (osvi.dwPlatformId == VER_PLATFORM_WIN32s)
    bUseRegistry = FALSE;
#else                 
  bUseRegistry = FALSE;
#endif  

#ifdef _WIN32
  if (bUseRegistry)
  {
    //use the registry if we are on Win32c or Win32n
      
    // Read the settings from the registry
    // Try opening the registry key:
    // HKEY_CURRENT_USER\Control Panel\DTime
    HKEY hcpl;
    if (RegOpenKeyEx(HKEY_CURRENT_USER,
                     _T("Control Panel"),
                     0,
                     KEY_QUERY_VALUE,
                     &hcpl) == ERROR_SUCCESS) 
    {
      HKEY happ;
      if (RegOpenKeyEx(hcpl,
                       _T("DTime"),
                       0,
                       KEY_QUERY_VALUE,
                       &happ) == ERROR_SUCCESS) 
      {
        bSuccess = TRUE;
        // Yes we are installed
    
        //First the begining day of week
        DWORD wBeginDayOfWeek;
        DWORD dwType = 0;
        DWORD dwSize = sizeof(wBeginDayOfWeek);
        LONG lSuccess = RegQueryValueEx(happ,
                        _T("BeginDayOfWeek"),
                        NULL,
                        &dwType,
                        (BYTE*)&wBeginDayOfWeek,
                        &dwSize);
        CDate::SetBeginingDayOfWeek((WORD) wBeginDayOfWeek);
    
    
    
        //the day part of the julian end date
        dwType = 0;
        DWORD Day;
        dwSize = sizeof(DWORD);
        lSuccess = RegQueryValueEx(happ,
                        _T("JulianEndDay"),
                        NULL,
                        &dwType,
                        (BYTE*)&Day,
                        &dwSize);
    
        //the month part of the julian end date
        dwType = 0;
        DWORD Month;
        dwSize = sizeof(DWORD);
        lSuccess = RegQueryValueEx(happ,
                        _T("JulianEndMonth"),
                        NULL,
                        &dwType,
                        (BYTE*)&Month,
                        &dwSize);
    
        //the year part of the julian end date
        dwType = 0;
        LONG Year;
        dwSize = sizeof(LONG);
        lSuccess = RegQueryValueEx(happ,
                        _T("JulianEndYear"),
                        NULL,
                        &dwType,
                        (BYTE*)&Year,
                        &dwSize);
    
        CDate::SetEndJulianCalendar(Year, (WORD) Month, (WORD) Day);
    
    
    
        //the day part of the gregorian begin date
        dwType = 0;
        dwSize = sizeof(DWORD);
        lSuccess = RegQueryValueEx(happ,
                        _T("GregorianBeginDay"),
                        NULL,
                        &dwType,
                        (BYTE*)&Day,
                        &dwSize);
    
        //the month part of the gregorian begin date
        dwType = 0;
        dwSize = sizeof(DWORD);
        lSuccess = RegQueryValueEx(happ,
                        _T("GregorianBeginMonth"),
                        NULL,
                        &dwType,
                        (BYTE*)&Month,
                        &dwSize);
    
        //the year part of the gregorian begin date
        dwType = 0;
        dwSize = sizeof(LONG);
        lSuccess = RegQueryValueEx(happ,
                        _T("GregorianBeginYear"),
                        NULL,
                        &dwType,
                        (BYTE*)&Year,
                        &dwSize);
    
        CDate::SetBeginGregCalendar(Year, (WORD) Month, (WORD) Day);
    
    
    
    
        //the default CDate format string
        CString sDefaultFormat;
        dwSize = 1024;
        LPTSTR pBuf = sDefaultFormat.GetBufferSetLength(dwSize);
        lSuccess = RegQueryValueEx(happ,
                        _T("CDateDefaultFormat"),
                        NULL,
                        &dwType,
                        (BYTE*)pBuf,
                        &dwSize);
        sDefaultFormat.ReleaseBuffer();
        CDate::SetDefaultFormat(sDefaultFormat);
    
        //the default CLDate format string
        dwSize = 1024;
        pBuf = sDefaultFormat.GetBufferSetLength(dwSize);
        lSuccess = RegQueryValueEx(happ,
                        _T("CLDateDefaultFormat"),
                        NULL,
                        &dwType,
                        (BYTE*)pBuf,
                        &dwSize);
        sDefaultFormat.ReleaseBuffer();
        CLDate::SetDefaultFormat(sDefaultFormat);
    
        //the default CLTimeSpan format string
        dwSize = 1024;
        pBuf = sDefaultFormat.GetBufferSetLength(dwSize);
        lSuccess = RegQueryValueEx(happ,
                        _T("CLTimeSpanDefaultFormat"),
                        NULL,
                        &dwType,
                        (BYTE*)pBuf,
                        &dwSize);
        sDefaultFormat.ReleaseBuffer();
        CLTimeSpan::SetDefaultFormat(sDefaultFormat);
    
        //the default CLTimeOfDay format string
        dwSize = 1024;
        pBuf = sDefaultFormat.GetBufferSetLength(dwSize);
        lSuccess = RegQueryValueEx(happ,
                        _T("CLTimeOfDayDefaultFormat"),
                        NULL,
                        &dwType,
                        (BYTE*)pBuf,
                        &dwSize);
        sDefaultFormat.ReleaseBuffer();
        CLTimeOfDay::SetDefaultFormat(sDefaultFormat);
    
        RegCloseKey(happ);
      }
      RegCloseKey(hcpl);
    }  
  }
#endif                  
  bSuccess = TRUE;


  if (!bUseRegistry)
  { 
    //Use environment variables to configure DTIME if on Win32s, Win16 or Dos. 
    //Ini files could have been used on Win32s, Win16 but then another
    //method would be required for Dos as the Get/Write Profile.. are Windows
    //specific
    
    char* pszCDateFormat = MyGetEnv("DATE_FMT");
    if (pszCDateFormat)
      CDate::SetDefaultFormat(pszCDateFormat);
      
    char* pszCLDateFormat = MyGetEnv("LDATE_FMT");
    if (pszCLDateFormat)
      CLDate::SetDefaultFormat(pszCLDateFormat);
      
    char* pszCLTimeSpanFormat = MyGetEnv("TS_FMT");
    if (pszCLTimeSpanFormat)
      CLTimeSpan::SetDefaultFormat(pszCLTimeSpanFormat);
      
    char* pszCLTimeOfDayFormat = MyGetEnv("TOD_FMT");
    if (pszCLTimeOfDayFormat)
      CLTimeOfDay::SetDefaultFormat(pszCLTimeOfDayFormat);
                                       
    char* pszBeginDayOfWeek = MyGetEnv("BDOW");
    if (pszBeginDayOfWeek)
      CDate::SetBeginingDayOfWeek((WORD) atoi(pszBeginDayOfWeek));

    char* pszEnvVar = MyGetEnv("JUL_END");
    if (pszEnvVar)
    {              
      //take a copy of the string so that any changes
      //we make will not be reflected back into the environment
      char* pszJulianEnd = new char[strlen(pszEnvVar)];
      
      if (pszJulianEnd)
      {
        strcpy(pszJulianEnd, pszEnvVar);
  
        BOOL bParseOK = TRUE;
        long Year;
        WORD Month;
        WORD Day;               
        char* sepChars = " ";
                
        char* pszTok = strtok(pszJulianEnd, sepChars);
        bParseOK = (pszTok != NULL);         
        if (bParseOK)
          Year = atol(pszTok);
        
        pszTok = strtok(NULL, sepChars); 
        bParseOK = bParseOK && (pszTok != NULL);         
        if (bParseOK)
          Month = (WORD) atoi(pszTok);   
  
        pszTok = strtok(NULL, sepChars);             
        bParseOK = bParseOK && (pszTok != NULL);               
        if (bParseOK)
          Day = (WORD) atoi(pszTok);
        
        if (bParseOK)
          //CDate::SetEndJulianCalendar(Year, Month, Day);
          
        delete []pszJulianEnd;
      }  
    }                                                              
    
    pszEnvVar = MyGetEnv("GREG_BEGIN");
    if (pszEnvVar)
    {                                       
      //take a copy of the string so that any changes
      //we make will not be reflected back into the environment
      char* pszGregBegin = new char[strlen(pszEnvVar)];
      
      if (pszGregBegin)
      {
        strcpy(pszGregBegin, pszEnvVar);
      
        BOOL bParseOK = TRUE;
        long Year;
        WORD Month;
        WORD Day;            
        char* sepChars = " ";
                
        char* pszTok = strtok(pszGregBegin, sepChars);
        bParseOK = (pszTok != NULL);         
        if (bParseOK)
          Year = atol(pszTok);
        
        pszTok = strtok(NULL, sepChars); 
        bParseOK = bParseOK && (pszTok != NULL);         
        if (bParseOK)
          Month = (WORD) atoi(pszTok);   
  
        pszTok = strtok(NULL, sepChars);             
        bParseOK = bParseOK && (pszTok != NULL);               
        if (bParseOK)
          Day = (WORD) atoi(pszTok);
        
        if (bParseOK)
          //CDate::SetBeginGregCalendar(Year, Month, Day);
          
        delete []pszGregBegin;
      }  
    }                                                              
  }

  return bSuccess;
}

                   

