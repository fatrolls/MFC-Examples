/*
Module : DATETIME.H
Purpose: Defines the interface to a number of Date and Date/Time classes
Created: PJN / DATE/1 / 05-05-1995
History: None

Copyright (c) 1995 by PJ Naughter.  
All rights reserved.

*/

#ifndef __DATE_H__


////////////////////////////////// Macros /////////////////////////////////////

#define __DATE_H__

                      

////////////////////////////////// Includes ///////////////////////////////////

#include <afx.h>
#include <iostream.h>
#include "win32sup.h"



////////////////////////////// Date Enums & Structs ///////////////////////////

enum CalendarType { JULIAN, GREGORIAN };


struct DateS
{
  LONG lYear;
  WORD wMonth;
  WORD wDay;
  WORD wWday;
  WORD wYday;
  CalendarType ct;
};


enum TimeFrame {UTC=0,
                ET, 
                LOCAL};


struct DateLS
{
  LONG lYear;
  WORD wMonth;
  WORD wDay;
  WORD wWday;
  WORD wYday;
  WORD wHour;
  WORD wMinute;
  WORD wSecond;
  WORD wMilliSeconds;
  CalendarType ct;
  TimeFrame tf;
};


/////////////////////////////// Free sub-programs (aka functions) /////////////
                                            

     

/////////////////////////////// Classes ///////////////////////////////////////

// forward declarations
class CLDate;
class CLTimeOfDay;
   
   
   
   
// A Date class with a granularity of 1 Day

class AFX_EXT_CLASS CDate : public CObject
{
  DECLARE_SERIAL(CDate)

public:
  friend class CLDate;
 
  enum MONTH { JANUARY=1,
               FEBRUARY=2,
               MARCH=3,
               APRIL=4,
               MAY=5,
               JUNE=6,
               JULY=7,
               AUGUST=8,
               SEPTEMBER=9,
               OCTOBER=10,
               NOVEMBER=11,
               DECEMBER=12};

  enum DayOfWeek { SUNDAY=1,
                   MONDAY=2,
                   TUESDAY=3,
                   WEDNESDAY=4,
                   THURSDAY=5,
                   FRIDAY=6,
                   SATURDAY=7};

  enum DateEpoch { EPOCH_JD,
                   EPOCH_MJD,
                   EPOCH_1900,
                   EPOCH_1950,
                   EPOCH_CTIME,
                   EPOCH_2000,
                   EPOCH_GREG};

  

  //constructors
  EXPORT16 CDate();
  EXPORT16 CDate(LONG Year, WORD Month, WORD Day);
  EXPORT16 CDate(const SYSTEMTIME& st);
  EXPORT16 CDate(LONG Year, WORD Month, WORD WeekOfMonth, WORD DayOfWeek); 
  EXPORT16 CDate(LONG Days, DateEpoch e);
  EXPORT16 CDate(const CDate& d);
  EXPORT16 CDate(const CTime& ctime);
#ifdef _WIN32
  EXPORT16 CDate(const COleDateTime& oleTime);
#endif  


  //Set operators
  CDate& EXPORT16 Set();
  CDate& EXPORT16 Set(LONG Year, WORD Month, WORD Day);
  CDate& EXPORT16 Set(DateS ds);
  CDate& EXPORT16 Set(const SYSTEMTIME& st);
  CDate& EXPORT16 Set(LONG Year, WORD Month, WORD WeekOfMonth, WORD DayOfWeek); 
  CDate& EXPORT16 Set(LONG Days, DateEpoch e);
  CDate& EXPORT16 Set(const CTime& ctime);
#ifdef _WIN32
  CDate& EXPORT16 Set(const COleDateTime& oleTime);
#endif  


  //statics constructors
  static CDate EXPORT16 CurrentDate();
  static CDate EXPORT16 FirstCurrentMonth(); 
  static CDate EXPORT16 LastCurrentMonth();  
  static CDate EXPORT16 FirstCurrentYear();
  static CDate EXPORT16 LastCurrentYear();
  static CDate EXPORT16 JDEpoch(); 
  static CDate EXPORT16 MJDEpoch();
  static CDate EXPORT16 Epoch1900();
  static CDate EXPORT16 Epoch1950();
  static CDate EXPORT16 EpochCTime();
  static CDate EXPORT16 Epoch2000();
  static CDate EXPORT16 GregorianEpoch();
  static void ClearStatics(); //Deallocate memory used by statics
  

  //static operations
  static BOOL EXPORT16     IsLeap(LONG Year);
  static WORD EXPORT16     DaysInYear(LONG Year);
  static WORD EXPORT16     DaysInMonth(WORD Month, BOOL IsLeap);
  static WORD EXPORT16     DaysSinceJan1(WORD Month, WORD Day, BOOL IsLeap);
  static WORD EXPORT16     DaysSinceJan0(WORD Month, WORD Day, BOOL IsLeap);
  static void EXPORT16     SetDefaultFormat(const CString& Format);
  static CString& EXPORT16 GetDefaultFormat();
  static WORD EXPORT16     CurrentMonth();
  static WORD EXPORT16     CurrentDay();
  static LONG EXPORT16     CurrentYear();
  static WORD EXPORT16     CurrentDayOfWeek();
  static void EXPORT16     SetBeginingDayOfWeek(WORD BeginOfWeek);
  static WORD EXPORT16     GetBeginingDayOfWeek();
  static void EXPORT16     SetEndJulianCalendar(LONG Year, WORD Month, WORD Day);
  static void EXPORT16     SetBeginGregCalendar(LONG Year, WORD Month, WORD Day);
  static DateS EXPORT16    GetEndJulianCalendar();
  static DateS EXPORT16    GetBeginGregCalendar();
  static BOOL EXPORT16     InGregorianCalendar(LONG Year, WORD Month, WORD Day);
#ifdef _DEBUG
  static BOOL EXPORT16     SetDoConstructorAsserts(BOOL bDoAsserts);
#endif
  static CString& EXPORT16 GetFullStringDayOfWeek(WORD DayOfWeek);
  static CString& EXPORT16 GetAbrStringDayOfWeek(WORD DayOfWeek);
  static CString& EXPORT16 GetFullStringMonth(WORD Month);
  static CString& EXPORT16 GetAbrStringMonth(WORD Month);

  
  //static Holiday constructors
  static CDate EXPORT16 NewYearsDay(LONG Year=CDate::CurrentYear());
  static CDate EXPORT16 ValentinesDay(LONG Year=CDate::CurrentYear());
  static CDate EXPORT16 AshWednesday(LONG Year=CDate::CurrentYear());
  static CDate EXPORT16 StPatricksDay(LONG Year=CDate::CurrentYear());
  static CDate EXPORT16 GoodFriday(LONG Year=CDate::CurrentYear());
  static CDate EXPORT16 EasterSunday(LONG Year=CDate::CurrentYear());
  static CDate EXPORT16 CanadaDay(LONG Year=CDate::CurrentYear());
  static CDate EXPORT16 IndependenceDay(LONG Year=CDate::CurrentYear());
  static CDate EXPORT16 BastilleDay(LONG Year=CDate::CurrentYear());
  static CDate EXPORT16 ChristmasDay(LONG Year=CDate::CurrentYear());

  
  //Operations
  WORD EXPORT16       DaysSinceJan1() const;
  WORD EXPORT16       DaysSinceJan0() const;
  DateS EXPORT16      GetDate() const;
  WORD EXPORT16       GetDay() const;
  WORD EXPORT16       GetMonth() const;
  LONG EXPORT16       GetYear() const;
  LONG EXPORT16       GetCEBCEYear(BOOL& IsCE) const;
  WORD EXPORT16       Get2DigitYear() const;
  LONG EXPORT16       Since1900Epoch() const;
  LONG EXPORT16       Since1950Epoch() const;
  LONG EXPORT16       SinceCTimeEpoch() const;
  LONG EXPORT16       Since2000Epoch() const;
  LONG EXPORT16       GDN() const;
  LONG EXPORT16       JD() const;
  BOOL EXPORT16       IsLeap() const;
  WORD EXPORT16       DaysInYear() const;
  WORD EXPORT16       DaysInMonth() const;
  void EXPORT16       AddYear(int Years=1);
  void EXPORT16       AddWeek(int Weeks=1);
  void EXPORT16       AddMonth(int Months=1);
  WORD EXPORT16       GetDayOfWeek() const; 
  CString& EXPORT16   GetStringCEBCEYear() const;    
  CString& EXPORT16   GetFullStringDayOfWeek() const;
  CString& EXPORT16   GetAbrStringDayOfWeek() const;
  CString& EXPORT16   GetFullStringMonth() const;
  CString& EXPORT16   GetAbrStringMonth() const;
  SYSTEMTIME EXPORT16 GetSYSTEMTIME() const;
  tm   EXPORT16       GetTM() const;
  WORD EXPORT16       GetWeekOfYear() const;    
  WORD EXPORT16       GetWeekOfMonth() const;
  BOOL EXPORT16       IsValid() const;          
  LONG EXPORT16       Collate() const;          
  BOOL EXPORT16       InGregorianCalendar() const;
                                          
                                        
  //Creation of other CDate's from this instance
  CDate EXPORT16 FirstThisMonth() const;
  CDate EXPORT16 LastThisMonth() const;
  CDate EXPORT16 FirstThisYear() const;
  CDate EXPORT16 LastThisYear() const;
  

  //Overloaded Arithmetic Operators
  CDate& EXPORT16 operator=(const CDate& d);
  CDate  EXPORT16 operator+(LONG Days) const;
  LONG   EXPORT16 operator-(const CDate& d) const;
  CDate  EXPORT16 operator-(LONG Days) const;
  CDate& EXPORT16 operator+=(LONG Days);
  CDate& EXPORT16 operator-=(LONG Days);
  CDate& EXPORT16 operator++();
  CDate& EXPORT16 operator--();


  //Overloaded Equality operators
  BOOL EXPORT16 operator==(const CDate& d) const;
  BOOL EXPORT16 operator>(const CDate& d) const;
  BOOL EXPORT16 operator>=(const CDate& d) const;
  BOOL EXPORT16 operator<(const CDate& d) const;
  BOOL EXPORT16 operator<=(const CDate& d) const;
  BOOL EXPORT16 operator!=(const CDate& d) const;


  //Diagnostics / Debug
  #ifdef _DEBUG
  virtual void EXPORT16 AssertValid() const;
  virtual void EXPORT16 Dump(CDumpContext& dc) const;
  #endif


  //Display
  CString& EXPORT16 Format(const CString& sFormat=CDate::GetDefaultFormat()) const;
  

  //Serialization
  virtual void EXPORT16 Serialize(CArchive& ar);


  //streaming
  friend ostream&  AFX_EXT_API EXPORT16 operator<<(ostream& os, const CDate& Date);
  friend CArchive& AFX_EXT_API EXPORT16 operator<<(CArchive& ar, CDate& Date);
  friend CArchive& AFX_EXT_API EXPORT16 operator>>(CArchive& ar, CDate& Date);
  

protected:
  LONG m_lDays;                      //Count of days since 15 October 1582 (Gregorian Calendrical System or n.s) 
  BOOL m_bInGregCalendar;            //Is this date in the Gregorian Calendar
    
  static CString sm_sBuffer;         //local Buffer for string return values
  static CString sm_sDefaultFormat;  //Default Format string
  static WORD    sm_wBeginOfWeek;    //Day of Week considered the begining of the week

  static LONG sm_lEndJulianYear;     //The Date when the Julian Calendar Finished
  static WORD sm_wEndJulianMonth;
  static WORD sm_wEndJulianDay;

  static LONG sm_lBeginGregYear;     //The Date when the Gregorian Calendar Started
  static WORD sm_wBeginGregMonth;
  static WORD sm_wBeginGregDay;
  static BOOL sm_bDoAsserts;         //Do constructor asserts
};




// A Time span class with a granularity of 1 millisecond which
// is used in conjunction with the time class CLDate

class AFX_EXT_CLASS CLTimeSpan : public CObject
{
public:
  friend class CLDate;
  friend class CLTimeOfDay;

  DECLARE_SERIAL(CLTimeSpan)
    
  //constructors
  EXPORT16 CLTimeSpan();
  EXPORT16 CLTimeSpan(LONG Day, WORD Hour, WORD Minute, 
             WORD Second, WORD MilliSecond);
  EXPORT16 CLTimeSpan(const CLTimeSpan& lts);
  EXPORT16 CLTimeSpan(const CTimeSpan& ts);
  EXPORT16 CLTimeSpan(const CLTimeOfDay& tod);
#ifdef _WIN32
  EXPORT16 CLTimeSpan(const COleDateTimeSpan& oleTimeSpan);
#endif  
  EXPORT16 CLTimeSpan(const double& Seconds);

  //Set operators
  CLTimeSpan& EXPORT16 Set();
  CLTimeSpan& EXPORT16 Set(LONG Day, WORD Hour, WORD Minute, 
                  WORD Second, WORD MilliSecond);
  CLTimeSpan& EXPORT16 Set(const CTimeSpan& ts);
  CLTimeSpan& EXPORT16 Set(const CLTimeOfDay& tod);
#ifdef _WIN32
  CLTimeSpan& EXPORT16 Set(const COleDateTimeSpan& oleTimeSpan);
#endif  
  CLTimeSpan& EXPORT16 Set(const double& Seconds);
  
  //statics constructors
  static CLTimeSpan EXPORT16 OneCivilYear();
  static CLTimeSpan EXPORT16 OneDay();
  static CLTimeSpan EXPORT16 OneHour();
  static CLTimeSpan EXPORT16 OneMinute();
  static CLTimeSpan EXPORT16 OneSecond();
  static CLTimeSpan EXPORT16 OneMilliSecond();  

  
  //static operations
  static void     EXPORT16 SetDefaultFormat(const CString& Format);
  static CString& EXPORT16 GetDefaultFormat();
#ifdef _DEBUG
  static BOOL     EXPORT16 SetDoConstructorAsserts(BOOL bDoAsserts);
#endif                                                            
  static void ClearStatics(); //Deallocate memory used by statics
  
  
  //Operations
  LONG        EXPORT16 GetTotalDays() const; 
  WORD        EXPORT16 GetHours() const; 
  WORD        EXPORT16 GetMinutes() const; 
  WORD        EXPORT16 GetSeconds() const; 
  WORD        EXPORT16 GetMilliSeconds() const; 
  BOOL        EXPORT16 IsValid() const; 
  CLTimeSpan& EXPORT16 Negate();
  BOOL        EXPORT16 IsPositiveSpan() const;
  double      EXPORT16 SecondsAsDouble() const;
                                           
                                        
  //Overloaded Arithmetic Operators
  CLTimeSpan& EXPORT16       operator=(const CLTimeSpan& TimeSpan);
  CLTimeSpan  EXPORT16       operator+(const CLTimeSpan& TimeSpan) const;
  CLTimeSpan  EXPORT16       operator-(const CLTimeSpan& TimeSpan) const;
  CLTimeSpan& EXPORT16       operator+=(CLTimeSpan& TimeSpan);
  CLTimeSpan& EXPORT16       operator-=(CLTimeSpan& TimeSpan);
  friend CLTimeSpan AFX_EXT_API EXPORT16 operator-(const CLTimeSpan& TimeSpan);
  CLTimeSpan  EXPORT16       operator*(WORD Multiplier) const;
  friend CLTimeSpan AFX_EXT_API EXPORT16 operator*(WORD Multiplier, const CLTimeSpan& TimeSpan);
  CLTimeSpan  EXPORT16       operator/(WORD divisor) const;
  CLTimeSpan& EXPORT16       operator*=(WORD Multiplier);
  CLTimeSpan& EXPORT16       operator/=(WORD Divisor);
  


  //Overloaded Equality operators
  BOOL EXPORT16 operator==(const CLTimeSpan& TimeSpan) const;
  BOOL EXPORT16 operator>(const CLTimeSpan& TimeSpan) const;
  BOOL EXPORT16 operator>=(const CLTimeSpan& TimeSpan) const;
  BOOL EXPORT16 operator<(const CLTimeSpan& TimeSpan) const;
  BOOL EXPORT16 operator<=(const CLTimeSpan& TimeSpan) const;
  BOOL EXPORT16 operator!=(const CLTimeSpan& TimeSpan) const;


  //Diagnostics / Debug
  #ifdef _DEBUG
  virtual void EXPORT16 AssertValid() const;
  virtual void EXPORT16 Dump(CDumpContext& dc) const;
  #endif


  //Display
  CString& EXPORT16 Format(const CString& sFormat=CLTimeSpan::GetDefaultFormat()) const;
  

  //Serialization
  virtual void EXPORT16 Serialize(CArchive& ar);


  //streaming
  friend ostream&  AFX_EXT_API EXPORT16 operator<<(ostream& os, const CLTimeSpan& TimeSpan);
  friend CArchive& AFX_EXT_API EXPORT16 operator<<(CArchive& ar, CLTimeSpan& TimeSpan);
  friend CArchive& AFX_EXT_API EXPORT16 operator>>(CArchive& ar, CLTimeSpan& TimeSpan);
  
         
protected:
  double m_dSeconds;

  static CString sm_sBuffer;         //local Buffer for string return values
  static CString sm_sDefaultFormat;  //Default Format string
  static BOOL    sm_bDoAsserts;      //Asserts in constructors / castings, otherwise sets date to invalid date
};




// A Time of Day class with a granularity of 1 millisecond which
// is used in conjunction with the time class CDate in the CLDate class

class AFX_EXT_CLASS CLTimeOfDay : public CObject
{
public:
  friend class CLDate;
  
  DECLARE_SERIAL(CLTimeOfDay)


  //constructors
  EXPORT16 CLTimeOfDay();
  EXPORT16 CLTimeOfDay(WORD Hour, WORD Minute, 
             WORD Second, WORD MilliSecond);
  EXPORT16 CLTimeOfDay(const SYSTEMTIME& st);             
  EXPORT16 CLTimeOfDay(const CLTimeOfDay& ltod);
  EXPORT16 CLTimeOfDay(DWORD TotalSeconds, WORD MilliSecond);
  EXPORT16 CLTimeOfDay(const double& Seconds);

  //Set operators
  CLTimeOfDay& EXPORT16 Set();
  CLTimeOfDay& EXPORT16 Set(WORD Hour, WORD Minute, 
                  WORD Second, WORD MilliSecond);
  CLTimeOfDay& EXPORT16 Set(const SYSTEMTIME& st);          
  CLTimeOfDay& EXPORT16 Set(DWORD TotalSeconds, WORD MilliSecond);   
  CLTimeOfDay& EXPORT16 Set(const double& Seconds);


  //statics constructors              
  static CLTimeOfDay EXPORT16 CurrentTimeOfDay(TimeFrame tf);
  static CLTimeOfDay EXPORT16 Midnight();
  static CLTimeOfDay EXPORT16 Midday();

  
  //static operations
  static void     EXPORT16 SetDefaultFormat(const CString& Format);
  static CString& EXPORT16 GetDefaultFormat();
#ifdef _DEBUG
  static BOOL     EXPORT16 SetDoConstructorAsserts(BOOL bDoAsserts);
#endif
  static void ClearStatics(); //Deallocate memory used by statics  
  
  //Operations
  WORD           EXPORT16 GetHour() const; 
  WORD           EXPORT16 GetMinute() const; 
  WORD           EXPORT16 GetSecond() const; 
  DWORD          EXPORT16 GetTotalSeconds() const;
  WORD           EXPORT16 GetMilliSecond() const; 
  WORD           EXPORT16 GetAMPMHour() const; 
  CString&       EXPORT16 GetAMPMString() const;
  BOOL           EXPORT16 IsValid() const;          
  ULARGE_INTEGER EXPORT16 Collate() const;
  SYSTEMTIME     EXPORT16 GetSYSTEMTIME() const;
  tm             EXPORT16 GetTM() const;
  double         EXPORT16 SecondsAsDouble() const;
  
                                       
                                        
  //Overloaded Arithmetic Operators
  CLTimeOfDay& EXPORT16 operator=(const CLTimeOfDay& Tod);
  CLTimeOfDay  EXPORT16 operator+(const CLTimeSpan& TimeSpan) const;
  CLTimeOfDay  EXPORT16 operator-(const CLTimeSpan& TimeSpan) const;
  CLTimeOfDay& EXPORT16 operator+=(CLTimeSpan& TimeSpan);
  CLTimeOfDay& EXPORT16 operator-=(CLTimeSpan& TimeSpan);


  //Overloaded Equality operators
  BOOL EXPORT16 operator==(const CLTimeOfDay& Tod) const;
  BOOL EXPORT16 operator>(const CLTimeOfDay& Tod) const;
  BOOL EXPORT16 operator>=(const CLTimeOfDay& Tod) const;
  BOOL EXPORT16 operator<(const CLTimeOfDay& Tod) const;
  BOOL EXPORT16 operator<=(const CLTimeOfDay& Tod) const;
  BOOL EXPORT16 operator!=(const CLTimeOfDay& Tod) const;


  //Diagnostics / Debug
  #ifdef _DEBUG
  virtual void EXPORT16 AssertValid() const;
  virtual void EXPORT16 Dump(CDumpContext& dc) const;
  #endif


  //Display
  CString& EXPORT16 Format(const CString& sFormat=CLTimeOfDay::GetDefaultFormat()) const;
  

  //Serialization
  virtual void EXPORT16 Serialize(CArchive& ar);


  //streaming
  friend ostream&  AFX_EXT_API EXPORT16 operator<<(ostream& os, const CLTimeOfDay& Tod);
  friend CArchive& AFX_EXT_API EXPORT16 operator<<(CArchive& ar, CLTimeOfDay& Tod);
  friend CArchive& AFX_EXT_API EXPORT16 operator>>(CArchive& ar, CLTimeOfDay& Tod);
  
         
protected:
  DWORD m_dwTotalSeconds;            //Actual instance data 
  WORD m_wMilliSeconds;

  static CString sm_sBuffer;         //local Buffer for string return values
  static CString sm_sDefaultFormat;  //Default Format string
  static BOOL    sm_bDoAsserts;      //Asserts in constructors / castings, otherwise sets date to invalid date
};




// A Date class with a granularity of 1 millisecond

class AFX_EXT_CLASS CLDate : public CObject
{
public:
  DECLARE_SERIAL(CLDate)
   
  //constructors
  EXPORT16 CLDate();
  EXPORT16 CLDate(LONG Year, WORD Month, WORD Day, 
         WORD Hour, WORD Minute, WORD Second,
         WORD MilliSecond, TimeFrame tf);
  EXPORT16 CLDate(const SYSTEMTIME& st, TimeFrame tf, BOOL bUseDayOfWeek=FALSE);
  EXPORT16 CLDate(LONG Year, WORD Month, WORD WeekOfMonth,
         WORD DayOfWeek, WORD Hour, WORD Minute, WORD Second,
         WORD MilliSecond, TimeFrame tf); 
  EXPORT16 CLDate(LONG Days, CDate::DateEpoch e, WORD Hour, WORD Minute,
         WORD Second, WORD MilliSecond, TimeFrame tf);
  EXPORT16 CLDate(const CLDate& ld);
  EXPORT16 CLDate(const CTime& ct);
  EXPORT16 CLDate(const CDate& Date, const CLTimeOfDay& Tod, TimeFrame tf);
#ifdef _WIN32
  EXPORT16 CLDate(const COleDateTime& oleTime, TimeFrame tf);
#endif  


  //Set operators
  CLDate& EXPORT16 Set();
  CLDate& EXPORT16 Set(LONG Year, WORD Month, WORD Day,
              WORD Hour, WORD Minute, WORD Second,
              WORD MilliSecond, TimeFrame tf);
  CLDate& EXPORT16 Set(const SYSTEMTIME& st, TimeFrame tf, BOOL bUseDayOfWeek=FALSE);           
  CLDate& EXPORT16 Set(LONG Year, WORD Month, WORD WeekOfMonth, 
              WORD DayOfWeek, WORD Hour, WORD Minute, WORD Second,
              WORD MilliSecond, TimeFrame tf); 
  CLDate& EXPORT16 Set(LONG Days, CDate::DateEpoch e, WORD Hour, WORD Minute,
              WORD Second, WORD MilliSecond, TimeFrame tf);
  CLDate& EXPORT16 Set(const CTime& ct);         
  CLDate& EXPORT16 Set(const CDate& Date, const CLTimeOfDay& Tod, TimeFrame tf);
#ifdef _WIN32
  CLDate& EXPORT16 Set(const COleDateTime& oleTime, TimeFrame tf);
#endif  


  //static constructors
  static CLDate EXPORT16 CurrentTime(TimeFrame tf);

  
  //static operations
  static void       EXPORT16 SetDefaultFormat(const CString& Format);
  static CString&   EXPORT16 GetDefaultFormat();
  static CLTimeSpan EXPORT16 DeltaT(CLDate& ld);
  static BOOL       EXPORT16 CurrentlyInDST();
  static CLTimeSpan EXPORT16 DaylightBias();
  static CLTimeSpan EXPORT16 TimezoneBias();
  static CString&   EXPORT16 DaylightName();
  static CString&   EXPORT16 StandardName();
#ifdef _DEBUG
  static BOOL EXPORT16 SetDoConstructorAsserts(BOOL bDoAsserts);
#endif
  static void ClearStatics(); //Deallocate memory used by statics
  

  //Operations
  CDate              EXPORT16 GetCDate() const;
  CLTimeOfDay        EXPORT16 GetCLTimeOfDay() const;
  DateLS             EXPORT16 GetDate() const;
  SYSTEMTIME         EXPORT16 GetSYSTEMTIME() const;
  tm                 EXPORT16 GetTM();  
  void               EXPORT16 AddYear(int Years=1);
  void               EXPORT16 AddWeek(int Weeks=1);
  void               EXPORT16 AddMonth(int Months=1);
  BOOL               EXPORT16 IsValid() const;
  CLTimeSpan         EXPORT16 DeltaT();
  TimeFrame          EXPORT16 SetTimeFrame(TimeFrame tf);
  TimeFrame          EXPORT16 GetTimeFrame() const;
  BOOL               EXPORT16 IsDST();
  CString&           EXPORT16 GetStringTimeFrame() const;
  double             EXPORT16 GSNAsDouble() const;
  double             EXPORT16 GDNAsDouble() const;
                                     
                                        
  //Overloaded Arithmetic Operators
  CLDate&    EXPORT16 operator=(const CLDate& ld);
  CLDate     EXPORT16 operator+(const CLTimeSpan& TimeSpan);
  CLTimeSpan EXPORT16 operator-(CLDate& ld);
  CLDate     EXPORT16 operator-(const CLTimeSpan& TimeSpan);
  CLDate&    EXPORT16 operator+=(const CLTimeSpan& TimeSpan);
  CLDate&    EXPORT16 operator-=(const CLTimeSpan& TimeSpan);
  CLDate&    EXPORT16 operator++();
  CLDate&    EXPORT16 operator--();


  //Overloaded Equality operators
  BOOL EXPORT16 operator==(CLDate& ld);
  BOOL EXPORT16 operator>(CLDate& ld);
  BOOL EXPORT16 operator>=(CLDate& ld);
  BOOL EXPORT16 operator<(CLDate& ld);
  BOOL EXPORT16 operator<=(CLDate& ld);
  BOOL EXPORT16 operator!=(CLDate& ld);


  //Diagnostics / Debug
  #ifdef _DEBUG
  virtual void EXPORT16 AssertValid() const;
  virtual void EXPORT16 Dump(CDumpContext& dc) const;
  #endif


  //Display
  CString& EXPORT16 Format(const CString& sFormat=CLDate::GetDefaultFormat()) const;
  

  //Serialization
  virtual void EXPORT16 Serialize(CArchive& ar);


  //streaming
  friend ostream&  AFX_EXT_API EXPORT16 operator<<(ostream& os, const CLDate& LDate);
  friend CArchive& AFX_EXT_API EXPORT16 operator<<(CArchive& ar, CLDate& LDate);
  friend CArchive& AFX_EXT_API EXPORT16 operator>>(CArchive& ar, CLDate& LDate);
  
         
protected:
  void CheckForValidLocalDate();
  BOOL DST();


  double m_dSeconds;                 //Actual instance data
  TimeFrame m_TimeFrame;             //What Time frame does this long date represent

  static CString sm_sBuffer;         //local Buffer for string return values
  static CString sm_sDefaultFormat;  //Default Format string
  static BOOL    sm_bDoAsserts;      //Asserts in constructors / castings, otherwise sets date to invalid date
  static BOOL    sm_bIsDst;          //Used when determinf if the date is in DSTAsserts in constructors / castings, otherwise sets date to invalid date
};

#endif //__DATE_H__




                                        
