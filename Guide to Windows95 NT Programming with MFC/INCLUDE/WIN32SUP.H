/*
Module : WIN32SUP.H
Purpose: Defines a number of components to allow dtime code to be portable across
         Win32n(NT), Win32c(95), Win32s, Win16 & Dos
Created: PJN / DATE/2 / 29-04-1996
History: None

Copyright (c) 1996 by PJ Naughter.  
All rights reserved.

*/

#ifndef __WIN32SUP_H__

        
////////////////////////////////// Macros /////////////////////////////////////

#define __WIN32SUP_H__

#ifndef __cplusplus
  #error Requires C++ compilation (use a .cpp suffix)
#endif                 


#ifdef _WIN32

  // Anything which is required from Win16 or Dos when compiling on Win32
  #define EXPORT16

#else

  // Anything which is required when compiling on Win16 or Dos
  
  /////////////// defines /////////////////////////////////////////////////////
  #define AFX_EXT_API
  #define AFX_EXT_CLASS
  
  #define TIME_ZONE_ID_UNKNOWN  0
  #define TIME_ZONE_ID_STANDARD 1
  #define TIME_ZONE_ID_DAYLIGHT 2
  
  #ifdef _WINDOWS
  #define _tprintf Win16Printf
  #define EXPORT16 __export   
  #define TCHAR char
  #define LPCTSTR LPCSTR
  #elif _DOS
  #define _tprintf printf
  #define TCHAR char
  #define EXPORT16
  #endif
  #define _T(x) x

                                                    
  /////////////// Structures //////////////////////////////////////////////////
  typedef struct _SYSTEMTIME 
  {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
  } SYSTEMTIME, *PSYSTEMTIME, FAR *LPSYSTEMTIME;
                       
  typedef struct _ULARGE_INTEGER 
  {
    DWORD LowPart; 
    DWORD HighPart; 
  } ULARGE_INTEGER, *PULARGE_INTEGER, FAR *LPULARGE_INTEGER; 
                                  
  typedef struct _TIME_ZONE_INFORMATION 
  {
    LONG Bias;
    char StandardName[32];
    SYSTEMTIME StandardDate;
    LONG StandardBias;
    char DaylightName[32];
    SYSTEMTIME DaylightDate;
    LONG DaylightBias;
  } TIME_ZONE_INFORMATION, *PTIME_ZONE_INFORMATION, FAR *LPTIME_ZONE_INFORMATION;
                                                
  
  ////////////// Emulation of required Win32 functions ////////////////////////
  DWORD EXPORT16 GetTimeZoneInformation(LPTIME_ZONE_INFORMATION lpTimeZoneInformation);
  
  
  ////////////// Functions which should have been in Win16 to begin with //////
  #ifdef _WINDOWS
  char* EXPORT16 DLLGetEnv(const char* pszVariableName);  //emulation of getenv for a Win16 DLL                    
  #endif


  //////////// A CString Class with Format support ////////////////////////////
  class CStringEx : public CString
  {
  public:       
    //Constructors / Destructors
    EXPORT16 CStringEx();
    EXPORT16 CStringEx(const CString& stringSrc);
    EXPORT16 CStringEx(char ch, int nRepeat = 1);
    EXPORT16 CStringEx(const char* psz);
    EXPORT16 CStringEx(const char* pch, int nLength);
                          
    //Operations
    void EXPORT16 Format(const char* pszFormat, ...);
    void EXPORT16 Format(UINT nFormatID, ...);
    
    //As there is no console APIS on Win16 we will output the info via OutputDebugString                         
    #ifdef _WINDOWS
    friend int EXPORT16 Win16Printf(const char *format, ...);
    #endif
    
    #ifndef _WINDOWS  //emulation of the LoadString function on Dos
    BOOL LoadString(UINT nID);            
    #endif
  
  protected:
    void FormatV(const char* pszFormat, va_list argList);
  };
  
  #define LOBYTE(w)     ((BYTE)(w))
  #define HIBYTE(w)     ((BYTE)(((UINT)(w) >> 8) & 0xFF))

  #define CString CStringEx

#endif // _WIN32        


//////////// function to wrap call to DllGetEnv when in a Win16 DLL ///////////
char* EXPORT16 MyGetEnv(const char* pszVariableName); 


#ifdef _DOS  //emulation of usual MFC function if on Dos
void AfxFormatString1(CStringEx& rString, UINT nIDS, const char* psz1);
#endif
        
#endif //__WIN32SUP_H__