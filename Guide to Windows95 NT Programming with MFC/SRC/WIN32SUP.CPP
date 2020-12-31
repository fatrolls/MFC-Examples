/*
Module : win32sup.cpp
Purpose: Defines a number of components to allow dtime code to be portable across
         Win32n(NT), Win32c(95), Win32s, Win16 & Dos
Created: PJN / DATE/2 / 29-04-1996
History: None

Copyright (c) 1996 by PJ Naughter.  
All rights reserved.

*/

/////////////////////////////////  Includes  //////////////////////////////////
#include "stdafx.h"
#include "resource.h"
#include <stdarg.h>
#include <ctype.h>
#include "win32sup.h"
#include "datetime.h"


/////////////////////////////// Local Functions ///////////////////////////////
#ifdef _DOS
void AfxFormatStrings(CString& rString, UINT nIDS, const char* rglpsz, int nString);
void AfxFormatStrings(CString& rString, const char* pszFormat, const char* rglpsz, int nString);
#endif



/////////////////////////////////  Macros  ////////////////////////////////////
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////// Implementation ////////////////////////////////

char* MyGetEnv(const char* pszVariableName)
{                  
  #if defined(_WINDOWS) && !defined(_WIN32) && defined(_AFXDLL) //call our own version of getenv
    return DLLGetEnv(pszVariableName);    //if in a Win16 dll
  #else
    return getenv(pszVariableName);
  #endif
}



#ifndef _WIN32


#ifdef _WINDOWS      
//The reason the DllGetEnv function is required instead is because of a limitation of getenv
//in Win16 DLL's. See the article Q78542 on the MSDN for a full explanation
char* DLLGetEnv(const char* pszVariableName)
{
  char* pEnvSearch; 
  const char* pszVarSearch;
                            
  //Check for a NULL pointer                          
  if (!*pszVariableName )  
    return NULL;
 
  //  Get a pointer to the MS-DOS environment block
  pEnvSearch = GetDOSEnvironment();
 
  while ( *pEnvSearch )  //While there are strings to parse
  {     
    /*
    Make a copy of the pointer to the name of the
    environment variable to search for.
    */
    pszVarSearch = pszVariableName;
 
    //  Check to see if the variable names match
    while (*pEnvSearch && *pszVarSearch &&
           *pEnvSearch == *pszVarSearch )
    {
      pEnvSearch++;
      pszVarSearch++;
    }

    /*
    If the names match, the lpEnvSearch pointer is on the "="
    character and lpszVarSearch is on a null terminator.
    Increment and return lpszEnvSearch, which will point to the
    environment variable's contents.
    
    If the names do not match, increment lpEnvSearch until it
    reaches the end of the current variable string.
    */
    if (*pEnvSearch == '=' && *pszVarSearch == '\0')
      return (pEnvSearch + 1);
    else
      while (*pEnvSearch)
        pEnvSearch++;
 
    /*
    At this point the end of the environment variable's string
    has been reached. Increment lpEnvSearch to move to the
    next variable in the environment block. If it is NULL,
    the end of the environment block has been reached.
    */
    pEnvSearch++;
  }

  /*
  If this section of code is reached, the variable
  was not found.
  */
  return NULL;
}
#endif //_WINDOWS
  

  

DWORD GetTimeZoneInformation(LPTIME_ZONE_INFORMATION lpTimeZoneInformation)
{             
  //Ini files could have been used on Win32s, Win16 but then another
  //method would be required for Dos as the Get/Write Profile.. are Windows
  //specific, hence the reason environment variables are used. This will
  //also allow DTime to ported to UNIX more easily in the furture.     
  DWORD rVal;
  
  //default to some reasonable values
  lpTimeZoneInformation->StandardDate.wYear = 0;  
  lpTimeZoneInformation->StandardDate.wMonth = 10;  
  lpTimeZoneInformation->StandardDate.wDayOfWeek = 0;        
  lpTimeZoneInformation->StandardDate.wDay = 5;  
  lpTimeZoneInformation->StandardDate.wHour = 2;  
  lpTimeZoneInformation->StandardDate.wMinute = 0;  
  lpTimeZoneInformation->StandardDate.wSecond = 0;
  lpTimeZoneInformation->StandardDate.wMilliseconds = 0;
    
  lpTimeZoneInformation->DaylightDate.wYear = 0;  
  lpTimeZoneInformation->DaylightDate.wMonth = 3;  
  lpTimeZoneInformation->DaylightDate.wDayOfWeek = 0;        
  lpTimeZoneInformation->DaylightDate.wDay = 5;  
  lpTimeZoneInformation->DaylightDate.wHour = 1;  
  lpTimeZoneInformation->DaylightDate.wMinute = 0;  
  lpTimeZoneInformation->DaylightDate.wSecond = 0;     
  lpTimeZoneInformation->DaylightDate.wMilliseconds = 0;

  
  //Any values which can be taken from the standard TZ environment value
  
  if (MyGetEnv("TZ"))
  {                                 
    _tzset();                                                   
    _fstrcpy(lpTimeZoneInformation->StandardName, _tzname[0]);
    _fstrcpy(lpTimeZoneInformation->DaylightName, _tzname[1]);
        
    if (_daylight)
    { 
      lpTimeZoneInformation->DaylightBias = -60;
      rVal = TIME_ZONE_ID_DAYLIGHT;      
    }  
    else
    {
      lpTimeZoneInformation->DaylightBias = 0;
      rVal = TIME_ZONE_ID_STANDARD;
    }  
    lpTimeZoneInformation->StandardBias = 0;
    lpTimeZoneInformation->Bias = _timezone/60;
  }
  else  //if no TZ environment is set then assume UCT timeframe and no daylight settings
        //This behaviour is different to the 16 bit c runtime library which defaults
        //to "PST8PDT"
  {
    _fstrcpy(lpTimeZoneInformation->StandardName, "");
    _fstrcpy(lpTimeZoneInformation->DaylightName, "");
    lpTimeZoneInformation->DaylightBias = -60;
    lpTimeZoneInformation->StandardBias = 0;
    lpTimeZoneInformation->Bias = 0;
    rVal = TIME_ZONE_ID_STANDARD;    
  }
  
  //the rest of the values required in TIME_ZONE_INFORMATION
  //are taken from environment variables newly defined for DTIME
  char* pszEnvVar = MyGetEnv("STD_DATE");
  if (pszEnvVar)
  {                
    //take a copy of the string so that any changes
    //we make will not be reflected back into the environment
    char* pszStandardDate = new char[strlen(pszEnvVar)];
    
    if (pszStandardDate)
    {
      strcpy(pszStandardDate, pszEnvVar);
    
      BOOL bParseOK = TRUE;
      char* sepChars = " ";
                
      char* pszTok = strtok(pszStandardDate, sepChars);
      bParseOK = (pszTok != NULL); 
      
      if (bParseOK)        
        lpTimeZoneInformation->StandardDate.wYear = (WORD) atoi(pszTok);
        
      pszTok = strtok(NULL, sepChars); 
      bParseOK = bParseOK && (pszTok != NULL);         
      if (bParseOK)
        lpTimeZoneInformation->StandardDate.wMonth = (WORD) atoi(pszTok);   
  
      pszTok = strtok(NULL, sepChars);             
      bParseOK = bParseOK && (pszTok != NULL);               
      if (bParseOK)
        lpTimeZoneInformation->StandardDate.wDayOfWeek = (WORD) atoi(pszTok);
  
      pszTok = strtok(NULL, sepChars);             
      bParseOK = bParseOK && (pszTok != NULL);               
      if (bParseOK)
        lpTimeZoneInformation->StandardDate.wDay = (WORD) atoi(pszTok);
  
      pszTok = strtok(NULL, sepChars); 
      bParseOK = bParseOK && (pszTok != NULL);         
      if (bParseOK)
        lpTimeZoneInformation->StandardDate.wHour = (WORD) atoi(pszTok);   
  
      pszTok = strtok(NULL, sepChars);             
      bParseOK = bParseOK && (pszTok != NULL);   
      if (bParseOK)            
        lpTimeZoneInformation->StandardDate.wMinute = (WORD) atoi(pszTok);
  
      pszTok = strtok(NULL, sepChars);             
      bParseOK = bParseOK && (pszTok != NULL);               
      if (bParseOK)
        lpTimeZoneInformation->StandardDate.wSecond = (WORD) atoi(pszTok); 
        
      delete []pszStandardDate;  
    }  
  }                                                              


  pszEnvVar = MyGetEnv("DYLT_DATE");
  if (pszEnvVar)
  { 
    //take a copy of the string so that any changes
    //we make will not be reflected back into the environment
    char* pszDaylightDate = new char[strlen(pszEnvVar)];
    
    if (pszDaylightDate)
    {
      strcpy(pszDaylightDate, pszEnvVar);
  
      BOOL bParseOK = TRUE; 
      char* sepChars = " ";
                
      char* pszTok = strtok(pszDaylightDate, sepChars);
      bParseOK = (pszTok != NULL);         
      if (bParseOK)    
        lpTimeZoneInformation->DaylightDate.wYear = (WORD) atoi(pszTok);
              
      pszTok = strtok(NULL, sepChars); 
      bParseOK = bParseOK && (pszTok != NULL);         
      if (bParseOK)    
        lpTimeZoneInformation->DaylightDate.wMonth = (WORD) atoi(pszTok);   
      
      pszTok = strtok(NULL, sepChars);             
      bParseOK = bParseOK && (pszTok != NULL);               
      if (bParseOK)    
        lpTimeZoneInformation->DaylightDate.wDayOfWeek = (WORD) atoi(pszTok);
          
      pszTok = strtok(NULL, sepChars);
      bParseOK = bParseOK && (pszTok != NULL);               
      if (bParseOK)    
        lpTimeZoneInformation->DaylightDate.wDay = (WORD) atoi(pszTok);
  
      pszTok = strtok(NULL, sepChars); 
      bParseOK = bParseOK && (pszTok != NULL);         
      if (bParseOK)    
        lpTimeZoneInformation->DaylightDate.wHour = (WORD) atoi(pszTok);   
  
      pszTok = strtok(NULL, sepChars);             
      bParseOK = bParseOK && (pszTok != NULL);               
      if (bParseOK)    
        lpTimeZoneInformation->DaylightDate.wMinute = (WORD) atoi(pszTok);
  
      pszTok = strtok(NULL, sepChars);             
      bParseOK = bParseOK && (pszTok != NULL);               
      if (bParseOK)    
        lpTimeZoneInformation->DaylightDate.wSecond = (WORD) atoi(pszTok);
  
      delete []pszDaylightDate;                                  
    }  
  }                                                              
  
  
  return rVal;
}

 
                
#ifdef _WINDOWS

int Win16Printf(const char *format, ...)
{   
  CString sOut;
  va_list argList;
  va_start(argList, format);
  sOut.FormatV(format, argList);
  va_end(argList);
  OutputDebugString(sOut);
  return sOut.GetLength();
}

#endif //_WINDOWS               
               

//to avoid circular calls                           

#undef CString


CStringEx::CStringEx()
{          
}
                                    

CStringEx::CStringEx(const CString& stringSrc) : CString(stringSrc)
{
}


CStringEx::CStringEx(char ch, int nRepeat) : CString(ch, nRepeat)
{       
}


CStringEx::CStringEx(const char* psz) : CString(psz)
{ 
}


CStringEx::CStringEx(const char* pch, int nLength) : CString(pch, nLength)
{ 
} 



void CStringEx::FormatV(const char* pszFormat, va_list argList)
{   
  ASSERT(AfxIsValidString(pszFormat));

  GetBuffer(512);
  VERIFY(vsprintf(m_pchData, pszFormat, argList) <= GetAllocLength());
  ReleaseBuffer();
  va_end(argList);
}


void CStringEx::Format(const char* pszFormat, ...)
{
  ASSERT(AfxIsValidString(pszFormat));

  va_list argList;
  va_start(argList, pszFormat);
  FormatV(pszFormat, argList);
  va_end(argList);
} 


void CStringEx::Format(UINT nFormatID, ...)
{
  CStringEx strFormat;
  VERIFY(strFormat.LoadString(nFormatID) != 0);

  va_list argList;
  va_start(argList, nFormatID);
  FormatV(strFormat, argList);
  va_end(argList);
}


//back to override                                                    
#define CString CStringEx



#endif //_WIN32






#ifdef _DOS
void AfxFormatStrings(CStringEx& rString, UINT nIDS, const char* rglpsz, int nString)
{
  CStringEx sText;
  ASSERT(sText.LoadString(nIDS));
  AfxFormatStrings(rString, sText, rglpsz, nString);
}
   

void AfxFormatStrings(CStringEx& rString, const char* pszFormat, const char* rglpsz, int nString)
{
  // NOTE: will not work for strings > 255 characters
  
  int nTotalLen = lstrlen(pszFormat);
  for (int i = 0; i < nString; i++)
  {
    if (rglpsz[i] != NULL)
      nTotalLen += strlen(&rglpsz[i]);
  }

  const char* pchSrc = pszFormat;
  char* pchDest = rString.GetBuffer(nTotalLen+1);
  while (*pchSrc != '\0')
  {
    if (pchSrc[0] == '%' && (pchSrc[1] >= '1' && pchSrc[1] <= '9'))
    {
      i = pchSrc[1] - '1';
      pchSrc += 2;
      if (i >= nString)
      {
        TRACE1("Error: illegal string index requested %d\n", i);
        *pchDest++ = '?';
      }
      else if (rglpsz[i] != NULL)
      {
        strcpy(pchDest, &rglpsz[i]);
        pchDest += strlen(pchDest);
      }
    }
    else
    {
      if (_AfxIsDBCSLeadByte(*pchSrc))
        *pchDest++ = *pchSrc++; // copy first of 2 bytes
      *pchDest++ = *pchSrc++;
    }
  }
  rString.ReleaseBuffer((int)((const char*)pchDest - (const char*)rString));
  // Release will assert if we went too far
}


void AfxFormatString1(CStringEx& rString, UINT nIDS, const char* psz1)
{                                                               
  AfxFormatStrings(rString, nIDS, psz1, 1);
}
                                 
                                 
                                 
                                 
                                 
                                 
  
//////////////// Implementation of CString::LoadString for Dos ////////////////

typedef struct _STRING_RES
{ 
  unsigned int nID;
  char* sText;
} STRING_RES;


//actual string table used by DTime, this should be kept in sync with
//the rc file that DTime uses on Win16/Win32

STRING_RES StringTable[] =
{                             
  {  IDS_WEEKDAY1,            "Sunday"},
  {  IDS_WEEKDAY2,            "Monday"},
  {  IDS_WEEKDAY3,            "Tuesday"},
  {  IDS_WEEKDAY4,            "Wednesday"},
  {  IDS_WEEKDAY5,            "Thursday"},
  {  IDS_WEEKDAY6,            "Friday"},
  {  IDS_WEEKDAY7,            "Saturday"},
  {  IDS_ABR_WEEKDAY1,        "Sun"},
  {  IDS_ABR_WEEKDAY2,        "Mon"},
  {  IDS_ABR_WEEKDAY3,        "Tue"},
  {  IDS_ABR_WEEKDAY4,        "Wed"},
  {  IDS_ABR_WEEKDAY5,        "Thur"},
  {  IDS_ABR_WEEKDAY6,        "Fri"},
  {  IDS_ABR_WEEKDAY7,        "Sat"},
  {  IDS_MONTH1,              "January"},
  {  IDS_MONTH2,              "February"},
  {  IDS_MONTH3,              "March"},
  {  IDS_MONTH4,              "April"},
  {  IDS_MONTH5,              "May"},
  {  IDS_MONTH6,              "June"},
  {  IDS_MONTH7,              "July"},
  {  IDS_MONTH8,              "August"},
  {  IDS_MONTH9,              "September"},
  {  IDS_MONTH10,             "October"},
  {  IDS_MONTH11,             "November"},
  {  IDS_MONTH12,             "December"},
  {  IDS_ABR_MONTH1,          "Jan"},
  {  IDS_ABR_MONTH2,          "Feb"},
  {  IDS_ABR_MONTH3,          "Mar"},
  {  IDS_ABR_MONTH4,          "Apr"},
  {  IDS_ABR_MONTH5,          "May"},
  {  IDS_ABR_MONTH6,          "Jun"},
  {  IDS_ABR_MONTH7,          "Jul"},
  {  IDS_ABR_MONTH8,          "Aug"},
  {  IDS_ABR_MONTH9,          "Sep"},
  {  IDS_ABR_MONTH10,         "Oct"},
  {  IDS_ABR_MONTH11,         "Nov"},
  {  IDS_ABR_MONTH12,         "Dec"},
  {  IDS_INVALID_DATE_RANGE,  "The date entered is outside of the allowable range"},
  {  IDS_INVALID_TIMESPAN_RANGE, 
                            "The time span entered is outside of the allowable range"},
  {  IDS_INVALID_TIMEOFDAY_RANGE, 
                            "The time of day entered is outside of the allowable range"},
  {  IDS_INVALID_DATE_MIN,    "The date entered is earlier that the allowable value"},
  {  IDS_INVALID_TIMESPAN_MIN, 
                            "The time span entered is earlier that the allowable value"},
  {  IDS_INVALID_TIMEOFDAY_MIN, 
                            "The time of day entered is earlier that the allowable value"},
  {  IDS_INVALID_DATE_MAX,    "The date entered is later that the allowable value"},
  {  IDS_INVALID_TIMESPAN_MAX, 
                            "The time span entered is later that the allowable value"},
  {  IDS_INVALID_TIMEOFDAY_MAX, 
                            "The time of day entered is later that the allowable value"},
  {  IDS_CEYEAR,              "%1 CE"},
  {  IDS_BCEYEAR,             "%1 BCE"},
  {  IDS_LOCAL,               "Local"},
  {  IDS_UTC,                 "UTC"},
  {  IDS_ET,                  "ET"},
  {  IDS_AM,                  "AM"},
  {  IDS_PM,                  "PM"},
  {  IDS_INVALID_DATE,        "A valid date must be entered."},
  {  IDS_INVALID_TIMESPAN,    "A valid time span must be entered."},
  {  IDS_INVALID_TIMEOFDAY,   "A valid time of day must be entered."},
  {  IDS_INVALID_LDATE,       "A valid long date must be entered."},
  {  IDS_INVALID_LDATE_MIN,   "The long date entered is earlier that the allowable value"},
  {  IDS_INVALID_LDATE_MAX,   "The long date entered is later that the allowable value"},
  {  IDS_YEAR,                "Year"},
  {  IDS_MONTH,               "Month"},
  {  IDS_DAY,                 "Day"},
  {  IDS_HOUR,                "Hour"},
  {  IDS_MINUTE,              "Minute"},
  {  IDS_SECOND,              "Second"},
  {  IDS_MILLISECOND,         "Millisecond"},
  {  IDS_ABR_HOUR,            "H"},
  {  IDS_ABR_MINUTE,          "M"},
  {  IDS_ABR_SECOND,          "S"},
  {  IDS_ABR_MILLISECOND,     "MS"},
  {  IDS_TIMEFRAME,           "Timeframe"},
  {  IDS_ENTERED_INVALID_DATE, 
                            "Please enter a valid date. A Possible reason that the date is invalid is that it occured during the skip when the Gregorian calendar was introduced."},
  {  IDS_ENTERED_INVALID_LDATE, 
                            "Please enter a valid long date. Possible reasons that the date is invalid is that it occured during the skip when the Gregorian calendar was introduced or when Daylight Savings was introduced or removed."},
  {  IDS_EDIT_TEXT,           "..."},
  {  IDS_UNICODE_DEBUG,       "(Unicode Debug Build)"},
  {  IDS_UNICODE_RELEASE,     "(Unicode Release Build)"},
  {  IDS_ASCII_DEBUG,         "(Ascii Debug Build)"},
  {  IDS_ASCII_RELEASE,       "(Ascii Release Build)"},
  {  IDS_SHAREWARE_CAPTION,   "DTime v%1 %2"},
  {  IDS_TT_PUSHPIN,          "Keep Visible"},
  {  IDS_TT_MODIFY,           "Modify"}
};  

 
//The function to the the actual load  
                                   

BOOL CStringEx::LoadString(UINT nID)
{                                
  //this is not intended as a generic solution but just enough
  //to make DTime work on Dos without too many changes.
  //A generic solution would store the actual string table on
  //file, would buffer access to it, and would use a binary search
  //instead of our simple linear search
  
  int nNumEntries = sizeof(StringTable) / sizeof(STRING_RES);

  //simple linear search through the table, nothing fancy                                 
  for (int i = 0; i<nNumEntries; i++)
  {
    if (StringTable[i].nID == nID)
    {
      *this = StringTable[i].sText;
      return TRUE;
    }
  }
  
  return FALSE;
} 



#endif // _DOS


