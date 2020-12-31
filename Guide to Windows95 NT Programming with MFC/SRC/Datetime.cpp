/*
Module : DATETIME.H
Purpose: Implementation for a number of Date / Time classes
Created: PJN / DATE/1 / 05-05-1995
History: None

Copyright (c) 1995 by PJ Naughter.  
All rights reserved.

*/

/////////////////////////////////  Includes  //////////////////////////////////
#include "stdafx.h"
#include "limits.h"
#include "time.h"
#include "stdlib.h"
#include "math.h"                                      
#include "float.h"
#include "win32sup.h"
#include "datetime.h"
#include "resource.h"



//////////////////////////////////  Macros  ///////////////////////////////////
IMPLEMENT_SERIAL(CDate, CObject, 1)
IMPLEMENT_SERIAL(CLTimeSpan, CObject, 1)
IMPLEMENT_SERIAL(CLTimeOfDay, CObject, 1)
IMPLEMENT_SERIAL(CLDate, CObject, 1)



#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif


////////////////////////////////// Locals /////////////////////////////////////
LONG lfloor(LONG a, LONG b);
void SetFebLength(BOOL bIsLeap);
void ResetFebLength();



////////////////////////////////// Statics ////////////////////////////////////

CString CDate::sm_sBuffer         = _T(""); 
CString CDate::sm_sDefaultFormat  = _T("%d/%m/%c");  
WORD    CDate::sm_wBeginOfWeek    = MONDAY;
LONG    CDate::sm_lEndJulianYear  = 1582;
WORD    CDate::sm_wEndJulianMonth = 10;
WORD    CDate::sm_wEndJulianDay   = 4;
LONG    CDate::sm_lBeginGregYear  = 1582;
WORD    CDate::sm_wBeginGregMonth = 10; 
WORD    CDate::sm_wBeginGregDay   = 15;
BOOL    CDate::sm_bDoAsserts = TRUE;

CString CLTimeSpan::sm_sBuffer = _T("");
CString CLTimeSpan::sm_sDefaultFormat = _T("%D %H:%M:%S.%F"); 
BOOL    CLTimeSpan::sm_bDoAsserts = TRUE;

CString CLTimeOfDay::sm_sBuffer = _T("");  
CString CLTimeOfDay::sm_sDefaultFormat = _T("%H:%M:%S.%F");
BOOL    CLTimeOfDay::sm_bDoAsserts = TRUE;    

CString CLDate::sm_sBuffer = _T("");
CString CLDate::sm_sDefaultFormat = _T("%H:%M:%S.%F %d/%m/%c %t"); 
BOOL    CLDate::sm_bDoAsserts     = TRUE;
BOOL    CLDate::sm_bIsDst         = TRUE;



static const int DeltaTTable[187] =
 {1240, 1150, 1060, 980, 910, 850, 790, 740, 700, 650,
  620, 580, 550, 530, 500, 480, 460, 440, 420, 400, 
  370, 350, 330, 310, 280, 260, 240, 220, 200, 180, 
  160, 140, 130, 120, 110, 100,  90,  90,  90,  90, 
   90,  90,  90,  90, 100, 100, 100, 100, 100, 110, 
  110, 110, 110, 110, 110, 110, 110, 120, 120, 120,
  120, 120, 130, 130, 130, 130, 140, 140, 140, 150,
  150, 150, 150, 160, 160, 160, 160, 160, 170, 170,
  170, 170, 170, 170, 170, 170, 160, 160, 150, 140,
  137, 131, 127, 125, 125, 125, 125, 125, 125, 123,
  120, 114, 106,  96,  86,  75,  66,  60,  57,  56, 
   57,  59,  62,  65,  68,  71,  73,  75,  77,  78,
   79,  75,  64,  54,  29,  16, -10, -27, -36, -47,
  -54, -52, -55, -56, -58, -59, -62, -64, -61, -47,
  -27,   0,  26,  54,  77, 105, 134, 160, 182, 202,
  212, 224, 235, 239, 243, 240, 239, 239, 237, 240,
  243, 253, 262, 273, 282, 291, 300, 307, 314, 322,
  331, 340, 350, 365, 383, 402, 422, 445, 465, 485,
  505, 522, 538, 549, 558, 569, 580};

static WORD MonthLength[14] =
  {
  0,  31, 28, 31, 30, 31, 30,
  31, 31, 30, 31, 30, 31, 0};




////////////////////////////////// Implementation /////////////////////////////
            


//Free Sub-Programs

void SetFebLength(BOOL bIsLeap)
{
  MonthLength[2] = (WORD) (28 + bIsLeap);
}

void ResetFebLength()
{
  MonthLength[2] = 28;
};

LONG lfloor(LONG a, LONG b)
{
  ASSERT(b > 0);
  return (a >= 0L ? a/b : (a%b == 0L) - 1 - labs(a)/b);
}


//CDate Implementation

CDate::CDate(LONG Year, WORD Month, WORD Day)
{ 
  Set(Year, Month, Day);
}

CDate::CDate(const SYSTEMTIME& st)
{
  Set(st);
}

CDate::CDate(LONG Year, WORD Month, WORD WeekOfMonth, WORD DayOfWeek)
{
  Set(Year, Month, WeekOfMonth, DayOfWeek);
}

CDate::CDate(LONG Days, DateEpoch e)
{
  Set(Days, e);
}

CDate::CDate()
{
  Set();
}

CDate::CDate(const CDate& d)
{
  m_lDays = d.m_lDays;
  m_bInGregCalendar = d.m_bInGregCalendar;
}

CDate::CDate(const CTime& ctime)
{
  Set(ctime.GetTime()/86400, EPOCH_CTIME);
}
                                     
#ifdef _WIN32
CDate::CDate(const COleDateTime& oleTime)
{
  Set(oleTime);
}                     
#endif

CDate& CDate::Set()
{
  m_lDays = LONG_MIN;
  m_bInGregCalendar = FALSE;
  return *this;
}

CDate& CDate::Set(LONG Year, WORD Month, WORD Day)
{
  //The following method has been taken from the magazine "Microsoft Systems Journal"
  //I cannot find the copy again, so if anyone recognises the algorithm please let
  //me know so I can credit the author.

  if (Month < JANUARY || Month > DECEMBER ||
      Day > DaysInMonth(Month, IsLeap(Year)))
  {
    if (sm_bDoAsserts)
      ASSERT(FALSE);
    Set();
    return *this;
  }
  
  if (((Year > sm_lEndJulianYear) && (Year < sm_lBeginGregYear)) ||
      ((Year == sm_lEndJulianYear) && ((Month > sm_wEndJulianMonth) && (Month < sm_wBeginGregMonth))) ||
      ((Year == sm_lEndJulianYear) && (Month == sm_wEndJulianMonth) && (Day > sm_wEndJulianDay) && (Day < sm_wBeginGregDay)))
  {
    if (sm_bDoAsserts)
      ASSERT(FALSE);
    Set();
    return *this;
  }

  SetFebLength(IsLeap(Year));
  m_lDays = (Year-1)*365 + lfloor(Year-1, 4L);
  m_bInGregCalendar = InGregorianCalendar(Year, Month, Day);
  if (m_bInGregCalendar)
    m_lDays += lfloor(Year-1, 400L) - lfloor(Year-1, 100L);
  while (--Month)
    m_lDays += MonthLength[Month];
  m_lDays += Day - 577736L - 2*(!m_bInGregCalendar);
  ResetFebLength();

  return *this;
}

CDate& CDate::Set(LONG Year, WORD Month, WORD WeekOfMonth, WORD DayOfWeek)
{
  if (WeekOfMonth < 1 || WeekOfMonth > 5 || DayOfWeek < 1 && DayOfWeek > 7)
  {
    if (sm_bDoAsserts)
      ASSERT(FALSE);
    Set();
    return *this;
  }

  if (WeekOfMonth < 5)
  {
    CDate FirstMonth(Year, Month, 1);
    if (!FirstMonth.IsValid())
    {
      if (sm_bDoAsserts)
        ASSERT(FALSE);
      Set();
      return *this;
    }
    WORD dow = FirstMonth.GetDayOfWeek();
    WORD Day = (WORD) (((DayOfWeek - dow + 7) % 7) + (7*(WeekOfMonth-1)) + 1);
    Set(Year, Month, Day);
  }
  else  //5 means the last week of the month
  {
    WORD NewMonth = (WORD) (Month + 1);
    LONG NewYear = Year;
    if (NewMonth > DECEMBER)
    {
      Month = 1;
      ++Year;
    }
       
    Set(NewYear, NewMonth, 1, DayOfWeek);
    AddWeek(-1);
  }

  return *this;
}

CDate& CDate::Set(LONG Days, DateEpoch e)
{
  switch (e)
  {
    case EPOCH_GREG:
    {
      m_lDays = Days;
      break;
    }
    case EPOCH_JD:    
    {
      m_lDays = Days - 2299161;  //-2299161 coresponds to the GDN of JD Epoch namely 1 January -4712 
      break;
    }
    case EPOCH_MJD:   
    {
      m_lDays = Days + 100839L;  //100839 coresponds to the GDN of MJD Epoch namely 17 November 1858 
      break;
    }
    case EPOCH_1900:
    {
      m_lDays = Days + 115860L;  //115860 corresponds to the GDN of 1 January 1900
      break;
    }
    case EPOCH_1950:
    {
      m_lDays = Days + 134122L;  //134122 corresponds to the GDN of 1 January 1950
      break;
    }
    case EPOCH_CTIME:
    {
      m_lDays = Days + 141427L;  //141427 corresponds to the GDN of 1 January 1970
      break;
    }
    case EPOCH_2000:  
    {
      m_lDays = Days + 152384L;  //152384 corresponds to the GDN of 1 January 2000
      break;
    }
    default: ASSERT(FALSE); //should not occur
  }
    
  if (m_lDays > 2146905911)  //Largest valid GDN
  {
    if (sm_bDoAsserts)
      ASSERT(FALSE);
    Set();
  }

  m_bInGregCalendar = *this > CDate(sm_lBeginGregYear, sm_wBeginGregMonth, sm_wBeginGregDay);

  return *this;
}

CDate& CDate::Set(const SYSTEMTIME& st)
{
  Set(st.wYear, st.wMonth, st.wDay);
  return *this;
}

CDate& CDate::Set(const CTime& ctime)
{
  return Set(ctime.GetTime()/86400, EPOCH_CTIME);
}
      
#ifdef _WIN32
CDate& CDate::Set(const COleDateTime& oleTime)
{
  return Set((LONG) oleTime.GetYear(), (WORD) oleTime.GetMonth(), (WORD) oleTime.GetDay());
}                     
#endif

CDate CDate::CurrentDate()
{   
  #ifdef _WIN32
    SYSTEMTIME st;
    ::GetLocalTime(&st);
    return CDate(st);
  #else      
    time_t csecs = time(NULL);
    tm* ct = localtime(&csecs);
    return CDate((LONG) (ct->tm_year + 1900), (WORD) (ct->tm_mon + 1), (WORD) (ct->tm_mday));
  #endif
}

WORD CDate::CurrentMonth()
{              
  return CurrentDate().GetMonth();
}

WORD CDate::CurrentDay()
{
  return CurrentDate().GetDay();
}

LONG CDate::CurrentYear()
{                               
  return CurrentDate().GetYear();
}

WORD CDate::CurrentDayOfWeek()
{            
  return CurrentDate().GetDayOfWeek();
}

void CDate::SetBeginingDayOfWeek(WORD BeginOfWeek)
{
  sm_wBeginOfWeek = BeginOfWeek;
}

WORD CDate::GetBeginingDayOfWeek()
{
  return sm_wBeginOfWeek;
}

void CDate::SetEndJulianCalendar(LONG Year, WORD Month, WORD Day)
{
  sm_lEndJulianYear = Year;
  sm_wEndJulianMonth = Month;
  sm_wEndJulianDay = Day;
}

void CDate::SetBeginGregCalendar(LONG Year, WORD Month, WORD Day)
{
  sm_lBeginGregYear = Year;
  sm_wBeginGregMonth = Month;
  sm_wBeginGregDay = Day;
}

DateS CDate::GetEndJulianCalendar()
{
  DateS rVal;
  rVal.lYear = sm_lEndJulianYear;
  rVal.wMonth = sm_wEndJulianMonth;
  rVal.wDay = sm_wEndJulianDay;
  rVal.wWday = CDate(sm_lEndJulianYear, sm_wEndJulianMonth, sm_wEndJulianDay).GetDayOfWeek();
  rVal.wYday = DaysSinceJan0(sm_wEndJulianMonth, sm_wEndJulianDay, IsLeap(sm_lEndJulianYear));
  rVal.ct = JULIAN;
  return rVal;
}

DateS CDate::GetBeginGregCalendar()
{
  DateS rVal;
  rVal.lYear = sm_lBeginGregYear;
  rVal.wMonth = sm_wBeginGregMonth;
  rVal.wDay = sm_wBeginGregDay;
  rVal.wWday = CDate(sm_lBeginGregYear, sm_wBeginGregMonth, sm_wBeginGregDay).GetDayOfWeek();
  rVal.wYday = DaysSinceJan0(sm_wBeginGregMonth, sm_wBeginGregDay, IsLeap(sm_lBeginGregYear));
  rVal.ct = GREGORIAN;
  return rVal;
}

BOOL CDate::InGregorianCalendar(LONG Year, WORD Month, WORD Day)
{
  if (Year == sm_lBeginGregYear)
  {
    if (Month == sm_wBeginGregMonth)
      return (Day >= sm_wBeginGregDay);
    else
      return (Month > sm_wBeginGregMonth);
  }
  else
    return (Year > sm_lBeginGregYear);
}

#ifdef _DEBUG
BOOL CDate::SetDoConstructorAsserts(BOOL bDoAsserts)
{
  BOOL bOldDoAsserts = sm_bDoAsserts;
  sm_bDoAsserts = bDoAsserts;
  return bOldDoAsserts;
}
#endif

CString& CDate::GetFullStringDayOfWeek(WORD DayOfWeek)
{
  sm_sBuffer.Empty();
  if (DayOfWeek > 0 && DayOfWeek <= 7)
  {
    if (!sm_sBuffer.LoadString(IDS_WEEKDAY1 - 1 + DayOfWeek))
      ASSERT(FALSE);
  }
  return sm_sBuffer;
}

CString& CDate::GetAbrStringDayOfWeek(WORD DayOfWeek)
{
  sm_sBuffer.Empty();
  if (DayOfWeek > 0 && DayOfWeek <= 7)
  {
    if (!sm_sBuffer.LoadString(IDS_ABR_WEEKDAY1 - 1 + DayOfWeek))
      ASSERT(FALSE);
  }
  return sm_sBuffer;
}

CString& CDate::GetFullStringMonth(WORD Month)
{
  sm_sBuffer.Empty();
  if (Month > 0 && Month <= 12)
  {
    if (!sm_sBuffer.LoadString(IDS_MONTH1 - 1 + Month))
      ASSERT(FALSE);
  }
  return sm_sBuffer;
}

CString& CDate::GetAbrStringMonth(WORD Month)
{
  sm_sBuffer.Empty();
  if (Month > 0 && Month <= 12)
  {
    if (!sm_sBuffer.LoadString(IDS_ABR_MONTH1 - 1 + Month))
      ASSERT(FALSE);
  }
  return sm_sBuffer;
}

CDate CDate::FirstCurrentMonth()
{
  CDate c = CDate::CurrentDate();
  return CDate(c.GetYear(), c.GetMonth(), 1); 
}

CDate CDate::LastCurrentMonth()
{
  CDate c = CDate::CurrentDate();
  return CDate(c.GetYear(), c.GetMonth(), c.DaysInMonth()); 
}

CDate CDate::FirstCurrentYear()
{
  CDate c = CDate::CurrentDate();
  return CDate(c.GetYear(), 1, 1); 
}              

CDate CDate::LastCurrentYear()
{
  CDate c = CDate::CurrentDate();
  return CDate(c.GetYear(), 12, CDate::DaysInMonth(12, c.IsLeap())); 
}

CDate CDate::JDEpoch()
{
  return CDate(0, EPOCH_JD);
}

CDate CDate::MJDEpoch()
{
  return CDate(0, EPOCH_MJD);
}

CDate CDate::Epoch1900()
{
  return CDate(0, EPOCH_1900);
}

CDate CDate::Epoch1950()
{
  return CDate(0, EPOCH_1950);
}

CDate CDate::EpochCTime()
{
  return CDate(0, EPOCH_CTIME);
}

CDate CDate::Epoch2000()
{
  return CDate(0, EPOCH_2000);
}

CDate CDate::GregorianEpoch()
{
  return CDate(0, EPOCH_GREG);
}                 

void CDate::ClearStatics()
{
  sm_sBuffer.Empty();
  sm_sDefaultFormat.Empty();
}

CDate CDate::NewYearsDay(LONG Year) 
{
  return CDate(Year, JANUARY, 1);
}

CDate CDate::ValentinesDay(LONG Year) 
{
  return CDate(Year, FEBRUARY, 14);
}

CDate CDate::AshWednesday(LONG Year)
{                                      
  return CDate::EasterSunday(Year) - 39L;    //Ash Wednesday occurs 39 days before Easter Sunday
}

CDate CDate::StPatricksDay(LONG Year) 
{
  return CDate(Year, MARCH, 17);
}

CDate CDate::GoodFriday(LONG Year)
{ 
  return CDate::EasterSunday(Year) - 2L;     //Good Friday occurs 2 days before Easter Sunday
}

CDate CDate::EasterSunday(LONG Year)
{
  //The following method has been taken from the book "Astronimical Algorithms" by Jean Meeus
  //which was taken in turn from a book "General Astronomy" by Spencer Jones. It has been 
  //published again in the "Journal of the British Astronomical Association, Vol 88" where
  //it is said that it was devised in 1876 and appeared in Butcher's "Ecclesiastical Calendar"

  if (InGregorianCalendar(Year, 4, 1))  //in the Gregorain Calendar, Will possibly give results if Calendar
  {                                     //switches from Julian to Gregorian in March or April because then
    int a = (int) (Year % 19);          //the year may be considered Gregorian or Julian
    int b = (int) (Year / 100);
    int c = (int) (Year % 100);
    int d = b / 4;
    int e = b % 4;
    int f = (b+8) / 25;
    int g = (b - f + 1) / 3;
    int h = (19*a + b - d - g + 15) % 30;
    int i = c / 4;
    int k = c % 4;
    int l = (32 + 2*e + 2*i - h -k) % 7;
    int m = (a + 11*h +22*l) / 451;
    int n = (h + l - 7*m + 114) / 31;
    int p = (h + l - 7*m + 114) % 31;
    return CDate(Year, WORD(n), WORD(p+1));
  }
  else              //in the Julian Calendar
  {                          
    int a = (int) (Year % 4);
    int b = (int) (Year % 7);
    int c = (int) (Year % 19);
    int d = (19*c + 15) % 30;
    int e = (2*a + 4*b - d + 34) % 7;
    int f = (d + e + 114) / 31;
    int g = (d + e + 114) % 31;
    return CDate(Year, (WORD) f, (WORD) (g + 1));
  }  
}

CDate CDate::CanadaDay(LONG Year)
{
  return CDate(Year, JULY, 1);
}

CDate CDate::IndependenceDay(LONG Year) 
{
  return CDate(Year, JULY, 4);
}

CDate CDate::BastilleDay(LONG Year) 
{
  return CDate(Year, JULY, 14);
}

CDate CDate::ChristmasDay(LONG Year)  
{
  return CDate(Year, DECEMBER, 25);
}

BOOL CDate::IsLeap(LONG Year)
{                
  if (InGregorianCalendar(Year, 1, 1))    //Will give incorrect results if Calendar switches
  {                                       //from Julian to Gregorian in the Year 1600 (if any Country did)
    if ((Year % 100) == 0)                
      return ((Year % 400) == 0) ? TRUE : FALSE;
    else
      return ((Year % 4) == 0) ? TRUE : FALSE;
  }
  else                                        
    return ((Year % 4) == 0) ? TRUE : FALSE;
      
}

WORD CDate::DaysInYear(LONG Year)
{
  return IsLeap(Year) ? ((WORD) 366) : ((WORD) 365);
}

WORD CDate::DaysInMonth(WORD Month, BOOL IsLeap)
{
  SetFebLength(IsLeap);
  ASSERT(Month >= 1 && Month <= 12);
  WORD r = MonthLength[Month];
  ResetFebLength();
  return r;
}

WORD CDate::DaysSinceJan1(WORD Month, WORD Day, BOOL IsLeap)
{
  return (WORD) (DaysSinceJan0(Month, Day, IsLeap) - 1);
}


WORD CDate::DaysSinceJan0(WORD Month, WORD Day, BOOL IsLeap)
{            
  ASSERT(Month >= JANUARY && Month <= DECEMBER);
  ASSERT(Day <= DaysInMonth(Month, IsLeap) && Day >= 1);
  int k = IsLeap ? 1 : 2;
  WORD rVal = (WORD) ((int(275*Month/9)) - (k*int((Month+9)/12)) + Day - 30);
  return rVal; 
}

void CDate::SetDefaultFormat(const CString& Format)
{
  sm_sDefaultFormat = Format;
}

CString& CDate::GetDefaultFormat()
{
  return sm_sDefaultFormat;
}

WORD CDate::DaysSinceJan1() const
{
  AssertValid();
  return (WORD) (*this - CDate(GetYear(), 1, 1));
}

WORD CDate::DaysSinceJan0() const
{
  AssertValid();
  return (WORD) (DaysSinceJan1() + 1);
}

DateS CDate::GetDate() const
{
  //See the comment in CDate::Set(LONG Year, WORD Month, WORD Day)
  //for references to where the algorithm is taken from

  AssertValid();
  BOOL bIsGreg = InGregorianCalendar();
  BOOL bIsJulian = !bIsGreg;
  DateS ds;
  LONG gdn = m_lDays + 577735L + 2*bIsJulian;
  LONG y4 = 1461L;
  LONG y400 = 146100L - 3*bIsGreg;
  LONG y100 = 36525L - bIsGreg;
  BOOL exception=FALSE;
  ds.lYear = 400*lfloor(gdn, y400);
  gdn -= y400*lfloor(gdn, y400);       //400 year periods
  if (gdn > 0L)
  {
    ds.lYear += 100*lfloor(gdn, y100);  //100 year periods
    gdn -= y100*lfloor(gdn, y100);
    exception = (gdn == 0L && bIsGreg);
    if (gdn > 0L)
    {
      ds.lYear += 4*lfloor(gdn, y4);     //4 year periods
      gdn -= y4*lfloor(gdn, y4);
      if (gdn > 0L)
      {
        int i=0;
        while (gdn > 365 && ++i < 4)
        {
          ds.lYear++;
          gdn -= 365L;
        }
      }
    }
  }
  if (exception)
    gdn = 366L; //occurs once every hundred years with Gregorian calendar
  else
  {
    ds.lYear++;
    gdn++;
  }
  SetFebLength(IsLeap(ds.lYear));
  ds.wMonth = 1;
  while (ds.wMonth < 13 && gdn > ((LONG) MonthLength[ds.wMonth]))
    gdn -= MonthLength[ds.wMonth++];
  if (ds.wMonth == 13)
  {
    ds.wMonth = 1;
    ds.lYear++;
  }
  ResetFebLength();
  ds.wDay = (WORD) gdn;
  ds.wWday = (WORD) ((m_lDays+12)%7 + 1); 
  ds.wYday = DaysSinceJan0(ds.wMonth, ds.wDay, IsLeap(ds.lYear));

  return ds;
}

WORD CDate::GetDay() const
{
  AssertValid();
  return GetDate().wDay;
}

WORD CDate::GetMonth() const
{
  AssertValid();
  return GetDate().wMonth;
}

LONG CDate::GetYear() const
{
  AssertValid();
  return GetDate().lYear;
}

LONG CDate::GetCEBCEYear(BOOL& IsCE) const
{
  AssertValid();
  LONG Year = GetDate().lYear;

  if (Year > 0)
  {
    IsCE = TRUE;
    return Year;
  }
  else
  {
    IsCE = FALSE;
    return labs(GetYear() - 1);
  }
}

WORD CDate::Get2DigitYear() const
{
  AssertValid();
  LONG Year = labs(GetYear());
  return (WORD) (Year - ((Year/100)*100));
}


WORD CDate::GetWeekOfYear() const
{               
  AssertValid(); 
  CDate FirstOfYear(GetYear(), JANUARY, 1, GetBeginingDayOfWeek());
  LONG diff = *this - FirstOfYear;
  if (diff < 0)
    return 0;
  else
    return (WORD) (diff/7 + 1);
}


WORD CDate::GetWeekOfMonth() const
{                  
  AssertValid();
  CDate FirstOfMonth(GetYear(), GetMonth(), 1, GetBeginingDayOfWeek());
  LONG diff = *this - FirstOfMonth;
  if (diff < 0)
    return 0;
  else
    return (WORD) (diff/7 + 1);
}

LONG CDate::Since1900Epoch() const
{
  AssertValid();
  return *this - CDate(1900, 1, 1);
}

LONG CDate::Since1950Epoch() const
{
  AssertValid();
  return *this - CDate(1950, 1, 1);
}

LONG CDate::SinceCTimeEpoch() const
{
  AssertValid();  
  return *this - CDate(1970, 1, 1);
}

LONG CDate::Since2000Epoch() const
{
  AssertValid();
  return *this - CDate(2000, 1, 1);
}

LONG CDate::JD() const
{
  AssertValid();
  return *this - JDEpoch();
}

LONG CDate::GDN() const
{
  AssertValid();
  return m_lDays;
}

BOOL CDate::IsLeap() const
{
  AssertValid();
  return IsLeap(GetYear());
}

WORD CDate::DaysInYear() const
{ 
  AssertValid();
  return DaysInYear(GetYear());
}

WORD CDate::DaysInMonth() const
{
  AssertValid();
  return DaysInMonth(GetMonth(), IsLeap());
}

void CDate::AddYear(int Years)
{
  AssertValid();
  LONG Months = Years*12;
  if (Months >= INT_MIN && Months <= INT_MAX)
    AddMonth((int) Months);
  else
  {
    ASSERT(FALSE);
    Set();
  }
}

void CDate::AddMonth(int Months)
{
  AssertValid();
  LONG NewMonth = (LONG) GetMonth();
  LONG NewYear = GetYear();
  NewMonth += Months;
  if ((NewMonth > DECEMBER) || (NewMonth < JANUARY))
  {
    NewYear += NewMonth / 12;
    NewMonth = NewMonth % 12;
  }
  if (NewMonth < JANUARY)
  {
    --NewYear;
    NewMonth += 12;
  }

  WORD Day = GetDay();

  WORD MaxDays = DaysInMonth((WORD) NewMonth, IsLeap(NewYear));
  if (Day > MaxDays)
    Day = MaxDays;
  Set(NewYear, (WORD) NewMonth, Day);
}

void CDate::AddWeek(int Weeks)
{
  AssertValid();
  *this += 7L*((LONG)Weeks);
}

WORD CDate::GetDayOfWeek() const
{
  AssertValid();
  return GetDate().wWday;
}

CString& CDate::GetStringCEBCEYear() const
{
  AssertValid();
  BOOL bIsCEYear;
  LONG lCEYear = GetCEBCEYear(bIsCEYear);
  CString sYear;                    
  sYear.Format(_T("%ld"), lCEYear);
  if (bIsCEYear)
    AfxFormatString1(sm_sBuffer, IDS_CEYEAR, sYear);
  else
    AfxFormatString1(sm_sBuffer, IDS_BCEYEAR, sYear);
  return sm_sBuffer;
}

CString& CDate::GetFullStringDayOfWeek() const
{
  AssertValid();
  return GetFullStringDayOfWeek(GetDayOfWeek());
}

CString& CDate::GetAbrStringDayOfWeek() const
{
  AssertValid();
  return GetAbrStringDayOfWeek(GetDayOfWeek());
}

CString& CDate::GetFullStringMonth() const
{
  AssertValid();
  return GetFullStringMonth(GetMonth());
}

CString& CDate::GetAbrStringMonth() const
{
  AssertValid();
  return GetAbrStringMonth(GetMonth());
}

SYSTEMTIME CDate::GetSYSTEMTIME() const
{
  AssertValid();
  SYSTEMTIME s;
  s.wYear = 0;
  s.wMonth = 0;
  s.wDayOfWeek = 0;
  s.wDay = 0;
  s.wHour = 0;
  s.wMinute = 0;
  s.wSecond = 0;
  s.wMilliseconds = 0;

  DateS ds = GetDate();

  //handle range errors
  if ((ds.lYear < 0) || (ds.lYear > USHRT_MAX))
  {
    ASSERT(FALSE);
    s.wYear = 0;
    return s;
  }
  
  s.wYear = (WORD) ds.lYear;
  s.wMonth = ds.wMonth;
  s.wDayOfWeek = (WORD) (ds.wWday - 1);  //SYSTEMTIME uses 0 based indices
  s.wDay = ds.wDay;

  return s;
}                
                          
tm CDate::GetTM() const
{
  AssertValid();
  tm rVal;
  
  rVal.tm_sec   = 0;
  rVal.tm_min   = 0;
  rVal.tm_hour  = 0;
  rVal.tm_mday  = 0;
  rVal.tm_mon   = 0;
  rVal.tm_year  = 0;
  rVal.tm_wday  = 0;
  rVal.tm_yday  = 0;
  rVal.tm_isdst = 0;
 
  DateS ds = GetDate(); 
     
#ifdef _WIN32
  long MinYear = 1900L + LONG_MIN;
  long MaxYear = LONG_MAX;
#else   
  long MinYear = 1900L + SHRT_MIN;
  long MaxYear = 1900L + SHRT_MAX;
#endif

  //handle range errors
  if ((ds.lYear < MinYear) || (ds.lYear > MaxYear))
  {
    ASSERT(FALSE);
    return rVal;
  }
  
  rVal.tm_year = (int) (ds.lYear - 1900L);
  rVal.tm_mon = ds.wMonth - 1;  //tm struct uses 0 based indices
  rVal.tm_wday = ds.wWday - 1;  //tm struct uses 0 based indices
  rVal.tm_mday = ds.wDay; 
  rVal.tm_wday = ds.wYday - 1; //Returns days since Jan 1
              
  return rVal;
}

BOOL CDate::IsValid() const
{
  return (m_lDays == LONG_MIN) ? FALSE : TRUE;
}

LONG CDate::Collate() const
{
  AssertValid();
  DateS s;
  s = GetDate();
  return (s.lYear*10000) + (s.wMonth*100) + s.wDay;
}

BOOL CDate::InGregorianCalendar() const
{
  AssertValid();
  return m_bInGregCalendar;
}

CDate CDate::FirstThisMonth() const
{
  AssertValid();
  DateS s=GetDate();
  return CDate(s.lYear, s.wMonth, 1);  
}

CDate CDate::LastThisMonth() const
{
  AssertValid();
  DateS s = GetDate();
  return CDate(s.lYear, s.wMonth, DaysInMonth(s.wMonth, IsLeap(s.lYear)));  
}

CDate CDate::FirstThisYear() const
{
  AssertValid();
  DateS s = GetDate();
  CDate d(s.lYear, JANUARY, 1);
  return d;  
}

CDate CDate::LastThisYear() const
{
  AssertValid();
  DateS s = GetDate();
  CDate d(s.lYear, DECEMBER, 1);
  return d;  
}

CDate& CDate::operator=(const CDate& d)
{
  m_lDays = d.m_lDays;
  m_bInGregCalendar = d.m_bInGregCalendar;
  return *this;
}

CDate CDate::operator+(LONG Days) const
{
  AssertValid();
  return CDate(m_lDays + Days, EPOCH_GREG);
}

LONG CDate::operator-(const CDate& d) const
{
  AssertValid();
  return m_lDays - d.m_lDays;
}

CDate CDate::operator-(LONG Days) const
{
  AssertValid();
  return CDate(m_lDays - Days, EPOCH_GREG);
}

CDate& CDate::operator+=(LONG Days)
{
  AssertValid();
  m_lDays += Days;
  return *this;
}

CDate& CDate::operator-=(LONG Days)
{
  AssertValid();
  m_lDays -= Days;
  return *this;
}

CDate& CDate::operator++()
{
  AssertValid();
  m_lDays++;
  return *this;
}

CDate& CDate::operator--()
{
  AssertValid();
  m_lDays--;
  return *this;
}

BOOL CDate::operator==(const CDate& d) const
{
  AssertValid();
  return m_lDays == d.m_lDays;
}

BOOL CDate::operator>(const CDate& d) const
{
  AssertValid();
  return m_lDays > d.m_lDays;
}

BOOL CDate::operator>=(const CDate& d) const
{
  AssertValid();
  return m_lDays >= d.m_lDays;
}

BOOL CDate::operator<(const CDate& d) const
{
  AssertValid();
  return m_lDays < d.m_lDays;
}

BOOL CDate::operator<=(const CDate& d) const
{
  AssertValid();
  return m_lDays <= d.m_lDays;
}

BOOL CDate::operator!=(const CDate& d) const
{
  AssertValid();
  return m_lDays != d.m_lDays;
}

#ifdef _DEBUG
void CDate::AssertValid() const
{
  CObject::AssertValid();
  ASSERT(IsValid());
}
#endif

#ifdef _DEBUG
void CDate::Dump(CDumpContext& dc) const
{
  CObject::Dump(dc);
  dc << Format() << _T("\n");
}
#endif

/*    //The Following Format parameters are supported

%a    Abbreviated weekday name
%A    Full weekday name
%b    Abbreviated month name
%B    Full month name
%d    Day of month as decimal number (01 - 31)
%j    Day of year as decimal number (001 - 366)
%m    Month as decimal number (01 - 12)
%U    Week of year as decimal number
%w    Weekday as decimal number (1 - 7; Sunday is 1)
%x    Short date representation, appropriate to current locale
%y    Year without century, as decimal number (00 - 99)
%Y    Year with century, as decimal number
%c    Year displayed using C.E.(Current Epoch) / B.C.E (Before Current Epoch) convention e.g. -1023 = 1022 BCE
%#x   Long date representation, appropriate to current locale
%#d, %#j, %#m, %#U, %#y Remove leading zeros (if any)
*/
CString& CDate::Format(const CString& sFormat) const
{ 
  if (!IsValid())
    sm_sBuffer.Empty();
  else
  {
    CString sBuffer;
    sm_sBuffer.Empty();
    CString rVal;
    int sFmtLength = sFormat.GetLength();

    for (int i=0; i<sFmtLength; i++)
    {
      TCHAR c = sFormat.GetAt(i);
      if (c == TCHAR('%'))
      {
        ++i;
        if (i < sFmtLength)
        {
          c = sFormat.GetAt(i);
          switch (c)
          {
            case TCHAR('a'):
            {
              rVal += GetAbrStringDayOfWeek();
              break;
            }
            case TCHAR('A'):
            {
              rVal += GetFullStringDayOfWeek();
              break;
            }
            case TCHAR('b'):
            {
              rVal += GetAbrStringMonth();
              break;
            }
            case TCHAR('c'):
            {
              rVal += GetStringCEBCEYear();
              break;
            }
            case TCHAR('B'):
            {
              rVal += GetFullStringMonth();
              break;
            }
            case TCHAR('d'):
            {
              sBuffer.Format(_T("%.02d"), GetDay());
              rVal += sBuffer;
              break;
            }
            case TCHAR('j'):
            {
              sBuffer.Format(_T("%.03d"), DaysSinceJan0());
              rVal += sBuffer;
              break;
            }
            case TCHAR('m'):
            {
              sBuffer.Format(_T("%.02d"), GetMonth());
              rVal += sBuffer;
              break;
            }
            case TCHAR('U'):
            {
              sBuffer.Format(_T("%.02d"), GetWeekOfYear());
              rVal += sBuffer;
              break;
            }
            case TCHAR('w'):
            {
              sBuffer.Format(_T("%d"), GetDayOfWeek());
              rVal += sBuffer;
              break;
            }                                   
            
          #ifdef _WIN32
            case TCHAR('x'):
            {
              sBuffer.Empty();
              SYSTEMTIME st = GetSYSTEMTIME();
              int Res = ::GetDateFormat(LOCALE_USER_DEFAULT,
                                      DATE_SHORTDATE,
                                      &st,
                                      NULL,
                                      sBuffer.GetBufferSetLength(100),
                                      100); 
              if (Res == 0)
                TRACE1("GetDateFormat() Failed in CDate::Format(), GetLastError() returned %ul\n", ::GetLastError());
              sBuffer.ReleaseBuffer();
              rVal += sBuffer;
              break;
            }                 
          #else
            #ifndef _WINDLL  //only available when statically linked to CRT
              case TCHAR('x'):
              {
                sBuffer.Empty();                                            
                tm tmCDate = GetTM();
                strftime(sBuffer.GetBufferSetLength(200), 200, "%x", &tmCDate);
                sBuffer.ReleaseBuffer();
                rVal += sBuffer;
                break;
              }    
            #endif               
          #endif
            
            case TCHAR('y'):
            {
              LONG Year = GetYear();
              sBuffer.Format(_T("%.02d"), Get2DigitYear());
              rVal += sBuffer;
              break;
            }
            case TCHAR('Y'):
            {
              sBuffer.Format(_T("%ld"), GetYear());
              rVal += sBuffer;
              break;
            }
            case TCHAR('#'):
            {
              if (i < sFmtLength)
              {
                ++i;
                c = sFormat.GetAt(i);
                switch (c)
                {
                  case TCHAR('d'):
                  {
                    sBuffer.Format(_T("%d"), GetDay());
                    rVal += sBuffer;
                    break;
                  }
                  case TCHAR('j'):
                  {
                    sBuffer.Format(_T("%d"), DaysSinceJan0());
                    rVal += sBuffer;
                    break;
                  }
                  case TCHAR('m'):
                  {
                    sBuffer.Format(_T("%d"), GetMonth());
                    rVal += sBuffer;
                    break;
                  }
                  case TCHAR('U'):
                  {
                    sBuffer.Format(_T("%d"), GetWeekOfYear());
                    rVal += sBuffer;
                    break;
                  }                                    
                  
                #ifdef _WIN32
                  case TCHAR('x'):
                  {
                    sBuffer.Empty();
                    SYSTEMTIME st = GetSYSTEMTIME();
                    int Res = ::GetDateFormat(LOCALE_USER_DEFAULT,
                                            DATE_LONGDATE,
                                            &st,
                                            NULL,
                                            sBuffer.GetBufferSetLength(100),
                                            100); 
                    if (Res == 0)
                      TRACE1("GetDateFormat() Failed in CDate::Format(), GetLastError() returned %ul\n", ::GetLastError());

                    sBuffer.ReleaseBuffer();
                    rVal += sBuffer;
                    break;
                  }               
                #else   
                  #ifndef _WINDLL  //only available when statically linked to CRT
                    case TCHAR('x'):    //Long representation is the same as short representation when not on Win32
                    {
                      sBuffer.Empty();                                       
                      tm tmCDate = GetTM();
                      strftime(sBuffer.GetBufferSetLength(200), 200, "%x", &tmCDate);
                      sBuffer.ReleaseBuffer();
                      rVal += sBuffer;
                      break;
                    }                                                            
                  #endif  
                #endif
                  
                  case TCHAR('y'):
                  {
                    LONG Year = GetYear();
                    sBuffer.Format(_T("%d"), Get2DigitYear());
                    rVal += sBuffer;
                    break;
                  }
                  default:
                  {
                    rVal += c;
                    break;
                  }
                }
              }
              break;
            }
            default:
            {
              rVal += c;
              break;
            }
          }
        }
      }
      else
      {
        rVal += c;
      }
    }
    sm_sBuffer = rVal;
  }

  return sm_sBuffer;
}

void CDate::Serialize(CArchive& ar)
{
  CObject::Serialize(ar);
  if(ar.IsStoring())
  {
    ar << m_lDays;
    ar << (WORD) m_bInGregCalendar;
  }
  else
  {
    ar >> m_lDays;
    ar >> (WORD&) m_bInGregCalendar;
  }
}

ostream& operator<<(ostream& os, const CDate& date)
{
  return os << date.Format();
}

CArchive& operator<<(CArchive& ar, CDate& date)
{
  ASSERT(ar.IsStoring());
  date.Serialize(ar);
  return ar;
}

CArchive& operator>>(CArchive& ar, CDate& date)
{
  ASSERT(!ar.IsStoring());
  date.Serialize(ar);
  return ar;
}







//CLTimeSpan Implementation


CLTimeSpan::CLTimeSpan()
{
  Set();
}

CLTimeSpan::CLTimeSpan(LONG Day, WORD Hour, WORD Minute, 
                       WORD Second, WORD MilliSecond)
{
  Set(Day, Hour, Minute, Second, MilliSecond);
}

CLTimeSpan::CLTimeSpan(const CLTimeSpan& lts)
{
  m_dSeconds = lts.m_dSeconds;
}

CLTimeSpan::CLTimeSpan(const CTimeSpan& ts)
{
  Set(ts);
}

CLTimeSpan::CLTimeSpan(const CLTimeOfDay& tod)
{
  Set(tod);
}
      
#ifdef _WIN32
CLTimeSpan::CLTimeSpan(const COleDateTimeSpan& oleTimeSpan)
{
  Set(oleTimeSpan);
}                     
#endif

CLTimeSpan::CLTimeSpan(const double& Seconds)
{                                             
  Set(Seconds);
}

CLTimeSpan& CLTimeSpan::Set()
{                          
  m_dSeconds = DBL_MAX;
  return *this;
}

CLTimeSpan& CLTimeSpan::Set(LONG Day, WORD Hour, WORD Minute, 
                            WORD Second, WORD MilliSecond)
{ 
  m_dSeconds = Day*86400.0 +
               Hour*3600.0 +
               Minute*60.0 +
               Second      +
               MilliSecond/1000.0;
  return *this;
}                            

CLTimeSpan& CLTimeSpan::Set(const CTimeSpan& ts)
{
  m_dSeconds = ts.GetTotalSeconds();
  return *this;
}

CLTimeSpan& CLTimeSpan::Set(const CLTimeOfDay& tod)
{
  Set(0, tod.GetHour(), tod.GetMinute(), tod.GetSecond(), tod.GetMilliSecond());
  return *this;
}
      
#ifdef _WIN32
CLTimeSpan& CLTimeSpan::Set(const COleDateTimeSpan& oleTimeSpan)
{
  return Set(oleTimeSpan.GetTotalSeconds());
}                     
#endif

CLTimeSpan& CLTimeSpan::Set(const double& Seconds)
{ 
  if (((Seconds > 0) && (Seconds > ((double)LONG_MAX)*86400)) || 
      ((Seconds < 0) && (Seconds < ((double)LONG_MIN)*86400)))
  {
    if (sm_bDoAsserts)
      ASSERT(FALSE);
    Set();
  }
  else
  {
    double IntPart, fraction;
    fraction = modf(Seconds, &IntPart);
    fraction = (floor(fraction*1000 + 0.5))/1000;
    m_dSeconds = IntPart + fraction;
  }
  
  return *this;
}

CLTimeSpan CLTimeSpan::OneCivilYear()
{
  return CLTimeSpan(365, 6, 0, 0, 0);
}

CLTimeSpan CLTimeSpan::OneDay()
{
  return CLTimeSpan(1, 0, 0, 0, 0);
}

CLTimeSpan CLTimeSpan::OneHour()
{
  return CLTimeSpan(0, 1, 0, 0, 0);
}

CLTimeSpan CLTimeSpan::OneMinute()
{
  return CLTimeSpan(0, 0, 1, 0, 0);
}

CLTimeSpan CLTimeSpan::OneSecond()
{
  return CLTimeSpan(0, 0, 0, 1, 0);
}

CLTimeSpan CLTimeSpan::OneMilliSecond()
{
  return CLTimeSpan(0, 0, 0, 0, 1);
}

void CLTimeSpan::SetDefaultFormat(const CString& Format)
{
  sm_sDefaultFormat = Format;
}

CString& CLTimeSpan::GetDefaultFormat()
{
  return sm_sDefaultFormat;
}

#ifdef _DEBUG
BOOL CLTimeSpan::SetDoConstructorAsserts(BOOL bDoAsserts)
{
  BOOL bOldDoAsserts = sm_bDoAsserts;
  sm_bDoAsserts = bDoAsserts;
  return bOldDoAsserts;
}
#endif                     

void CLTimeSpan::ClearStatics()
{
  sm_sBuffer.Empty();
  sm_sDefaultFormat.Empty();
}
                                 
LONG CLTimeSpan::GetTotalDays() const
{
  AssertValid();
  return (LONG) (m_dSeconds/86400);
}

WORD CLTimeSpan::GetHours() const
{
  AssertValid();
  return (WORD) ((fabs(m_dSeconds) - 86400L*fabs(GetTotalDays()))/3600);
}

WORD CLTimeSpan::GetMinutes() const
{
  AssertValid();
  return (WORD) ((fabs(m_dSeconds) - 86400L*fabs(GetTotalDays()) - 3600L*GetHours())/60);
}

WORD CLTimeSpan::GetSeconds() const
{
  AssertValid();
  return (WORD) (fabs(m_dSeconds) - 86400L*fabs(GetTotalDays()) - 3600L*GetHours() - 60*GetMinutes());
}                             

WORD CLTimeSpan::GetMilliSeconds() const
{
  AssertValid();
  double IntPart, fraction;
  fraction = modf(m_dSeconds, &IntPart);
  return (WORD) labs(((LONG) (floor(fraction*1000 + 0.5))));
}

BOOL CLTimeSpan::IsValid() const
{
  return (m_dSeconds != DBL_MAX);
}

CLTimeSpan& CLTimeSpan::Negate()
{
  AssertValid();
  m_dSeconds = (-m_dSeconds);
  return *this;
}

BOOL CLTimeSpan::IsPositiveSpan() const
{
  AssertValid();
  return (m_dSeconds >= 0);
}

double CLTimeSpan::SecondsAsDouble() const
{
  AssertValid();
  return m_dSeconds;
}

BOOL CLTimeSpan::operator==(const CLTimeSpan& TimeSpan) const
{
  AssertValid();
  return (m_dSeconds == TimeSpan.m_dSeconds);
}

BOOL CLTimeSpan::operator>(const CLTimeSpan& TimeSpan) const
{
  AssertValid();
  return (m_dSeconds > TimeSpan.m_dSeconds);
}

BOOL CLTimeSpan::operator>=(const CLTimeSpan& TimeSpan) const
{
  AssertValid();
  return (m_dSeconds >= TimeSpan.m_dSeconds);
}

BOOL CLTimeSpan::operator<(const CLTimeSpan& TimeSpan) const
{
  AssertValid();
  return (m_dSeconds < TimeSpan.m_dSeconds);
}

BOOL CLTimeSpan::operator<=(const CLTimeSpan& TimeSpan) const
{
  AssertValid();
  return (m_dSeconds <= TimeSpan.m_dSeconds);
}

BOOL CLTimeSpan::operator!=(const CLTimeSpan& TimeSpan) const
{
  AssertValid();
  return (m_dSeconds != TimeSpan.m_dSeconds);
}
                                 
CLTimeSpan& CLTimeSpan::operator=(const CLTimeSpan& TimeSpan)
{ 
  m_dSeconds = TimeSpan.m_dSeconds;
  return *this;
}

CLTimeSpan CLTimeSpan::operator+(const CLTimeSpan& TimeSpan) const
{
  AssertValid();
  TimeSpan.AssertValid();
  double rVal = m_dSeconds + TimeSpan.m_dSeconds;
  return CLTimeSpan(rVal);
}

CLTimeSpan CLTimeSpan::operator-(const CLTimeSpan& TimeSpan) const
{
  AssertValid();
  TimeSpan.AssertValid();
  double rVal = m_dSeconds - TimeSpan.m_dSeconds;
  return rVal;
}

CLTimeSpan& CLTimeSpan::operator+=(CLTimeSpan& TimeSpan)
{
  *this = *this + TimeSpan;
  return *this;
}

CLTimeSpan& CLTimeSpan::operator-=(CLTimeSpan& TimeSpan)
{
  *this = *this - TimeSpan;
  return *this;
}

CLTimeSpan operator-(const CLTimeSpan& TimeSpan)
{
  CLTimeSpan rVal(TimeSpan);
  return rVal.Negate();
}

CLTimeSpan CLTimeSpan::operator*(WORD Multiplier) const
{
  return ::operator*(Multiplier, *this);
}

CLTimeSpan operator*(WORD Multiplier, const CLTimeSpan& TimeSpan)
{
  TimeSpan.AssertValid();
  double rVal = TimeSpan.m_dSeconds * Multiplier;
  return CLTimeSpan(rVal);
}

CLTimeSpan CLTimeSpan::operator/(WORD divisor) const
{
  AssertValid();
  double rVal = m_dSeconds / ((double) divisor);
  return CLTimeSpan(rVal);
}

CLTimeSpan& CLTimeSpan::operator*=(WORD Multiplier)
{
  *this = operator*(Multiplier);
  return *this;
}

CLTimeSpan& CLTimeSpan::operator/=(WORD Divisor)
{
  *this = operator/(Divisor);
  return *this;
}

#ifdef _DEBUG
void CLTimeSpan::AssertValid() const
{
  CObject::AssertValid();
  ASSERT(IsValid());
}
#endif

#ifdef _DEBUG
void CLTimeSpan::Dump(CDumpContext& dc) const
{
  CObject::Dump(dc);
  dc << Format() << _T("\n");
}
#endif

/*    //The Following Format parameters are supported        
%D    Total days in this CLTimeSpan
%H    Hours in this CLTimeSpan (00 - 23)
%M    Minutes in the current hour in this CLTimeSpan (00 - 59)
%S    Seconds in the current minute in this CLTimeSpan (00 - 59)
%F    MilliSeconds in the current second in this CLTimeSpan (000 - 999)
%%    Percent sign
%#H, %#M, %#S  Remove leading zeros (if any).
*/
CString& CLTimeSpan::Format(const CString& sFormat) const
{ 
  if (!IsValid())
    sm_sBuffer.Empty();
  else
  {
    CString sBuffer;
    CString rVal;
    sm_sBuffer.Empty();
    int sFmtLength = sFormat.GetLength();

    for (int i=0; i<sFmtLength; i++)
    {
      TCHAR c = sFormat.GetAt(i);
      if (c == TCHAR('%'))
      {
        ++i;
        if (i < sFmtLength)
        {
          c = sFormat.GetAt(i);
          switch (c)
          {
            case TCHAR('D'):
            {
              LONG Days = GetTotalDays();
              sBuffer.Format(_T("%ld"), Days);
              if (IsPositiveSpan())
                rVal += _T("+");
              else if (Days == 0) //handle neagtive 0
                rVal += _T("-");
              rVal += sBuffer;
              break;
            }
            case TCHAR('H'):
            {
              sBuffer.Format(_T("%.02d"), GetHours());
              rVal += sBuffer;
              break;
            }
            case TCHAR('M'):
            {
              sBuffer.Format(_T("%.02d"), GetMinutes());
              rVal += sBuffer;
              break;
            }
            case TCHAR('S'):
            {
              sBuffer.Format(_T("%.02d"), GetSeconds());
              rVal += sBuffer;
              break;
            }
            case TCHAR('F'):
            {
              sBuffer.Format(_T("%.03d"), GetMilliSeconds());
              rVal += sBuffer;
              break;
            }
            case TCHAR('#'):
            {
              if (i < sFmtLength)
              {
                ++i;
                c = sFormat.GetAt(i);
                switch (c)
                {
                  case TCHAR('H'):
                  {
                    sBuffer.Format(_T("%d"), GetHours());
                    rVal += sBuffer;
                    break;
                  }
                  case TCHAR('M'):
                  {
                    sBuffer.Format(_T("%d"), GetMinutes());
                    rVal += sBuffer;
                    break;
                  }
                  case TCHAR('S'):
                  {
                    sBuffer.Format(_T("%d"), GetSeconds());
                    rVal += sBuffer;
                    break;
                  }
                  default:
                  {
                    rVal += c;
                    break;
                  }
                }
              break;
              }
            }
            default:
            {
              rVal += c;
              break;
            }
          }
        }
      }
      else
      {
        rVal += c;
      }
    }
    sm_sBuffer = rVal;
  }
  
  return sm_sBuffer;
}

void CLTimeSpan::Serialize(CArchive& ar)
{
  CObject::Serialize(ar);
  if(ar.IsStoring())
  {
    ar << m_dSeconds;
  }
  else
  {
    ar >> m_dSeconds;
  }
}

ostream& operator<<(ostream &os, const CLTimeSpan& TimeSpan)
{
  return os << TimeSpan.Format();
}                  

CArchive& operator<<(CArchive& ar, CLTimeSpan& TimeSpan)
{
  ASSERT(ar.IsStoring());
  TimeSpan.Serialize(ar);
  return ar;
}
               
CArchive& operator>>(CArchive& ar, CLTimeSpan& TimeSpan)
{
  ASSERT(!ar.IsStoring());
  TimeSpan.Serialize(ar);
  return ar;
}






//CLTimeOfDay Implementation

CLTimeOfDay::CLTimeOfDay()
{
  Set();
}

CLTimeOfDay::CLTimeOfDay(WORD Hour, WORD Minute, 
           WORD Second, WORD MilliSecond)
{
  Set(Hour, Minute, Second, MilliSecond);
}    

CLTimeOfDay::CLTimeOfDay(const double& Seconds)
{
  Set(Seconds);
}    

CLTimeOfDay::CLTimeOfDay(const SYSTEMTIME& st)
{        
  Set(st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
}
           
CLTimeOfDay::CLTimeOfDay(const CLTimeOfDay& ltod)
{
  m_dwTotalSeconds = ltod.m_dwTotalSeconds;
  m_wMilliSeconds = ltod.m_wMilliSeconds;
}                                

CLTimeOfDay::CLTimeOfDay(DWORD TotalSeconds, WORD MilliSecond)
{
  Set(TotalSeconds, MilliSecond);
}                                


CLTimeOfDay& CLTimeOfDay::Set()
{
  m_dwTotalSeconds = 86400; //an illegal value
  m_wMilliSeconds = 0;
  return *this;
}

CLTimeOfDay& CLTimeOfDay::Set(const double& Seconds)
{
  if (Seconds < 0)
  {
    if (sm_bDoAsserts)
      ASSERT(FALSE);
    Set();
    return *this;
  }
  
  double FracPart, IntPart;
  FracPart = modf(Seconds, &IntPart);
  DWORD dwSeconds = (DWORD) IntPart;
  WORD wMilliSeconds = (WORD) (FracPart*1000 + 0.5);
  Set(dwSeconds, wMilliSeconds);
  return *this;
}

CLTimeOfDay& CLTimeOfDay::Set(WORD Hour, WORD Minute,
                WORD Second, WORD MilliSecond)
{
  WORD AdditionalSeconds = (WORD) ((MilliSecond/1000)*1000);
  LONG lSeconds = Minute + 60L*Hour;
  lSeconds *= 60;
  lSeconds += Second + AdditionalSeconds;
  m_dwTotalSeconds = lSeconds;
  if (m_dwTotalSeconds >= 86400L)
  {
    if (sm_bDoAsserts)
      ASSERT(FALSE);
    Set();
    return *this;
  }
  m_wMilliSeconds = (WORD) (MilliSecond - (AdditionalSeconds*1000));
  return *this;  
}                
                                 
CLTimeOfDay& CLTimeOfDay::Set(DWORD TotalSeconds, WORD MilliSecond)
{
  WORD AdditionalSeconds = (WORD) ((MilliSecond/1000)*1000);
  m_dwTotalSeconds = TotalSeconds + AdditionalSeconds;
  if (m_dwTotalSeconds >= 86400)
  {
    if (sm_bDoAsserts)
      ASSERT(FALSE);
    Set();
    return *this;
  }
  m_wMilliSeconds = (WORD) (MilliSecond - (AdditionalSeconds*1000));
  return *this;  
}
                                 
CLTimeOfDay CLTimeOfDay::CurrentTimeOfDay(TimeFrame tf)
{ 
  #ifdef _WIN32
    SYSTEMTIME st;                                
    switch (tf)
    {    
      case UTC:
        ::GetSystemTime(&st); 
        break;
      case LOCAL:
        ::GetLocalTime(&st); 
        break;   
      case ET:
        ASSERT(FALSE);
        break;
      default: ASSERT(FALSE);
    }    
        
    return CLTimeOfDay(st);
  #else                                        
    time_t csecs = time(NULL);
    tm* ct = localtime(&csecs);
    CLTimeOfDay ctime((WORD) (ct->tm_hour), (WORD) (ct->tm_min), (WORD) (ct->tm_sec), 0);
    switch (tf)
    {
      case UTC:
        TIME_ZONE_INFORMATION tzi;
        GetTimeZoneInformation(&tzi);
        ctime -= CLTimeSpan((double) tzi.Bias);
        break;
      case LOCAL:                         
        {
        // nothing required;        
        break;
        }
      case ET:
        ASSERT(FALSE);
        break;
      default: ASSERT(FALSE);      
    }
  
    return ctime;
  #endif
}
                                 
CLTimeOfDay CLTimeOfDay::Midnight()
{
  return CLTimeOfDay(0, 0, 0, 0);
}

CLTimeOfDay CLTimeOfDay::Midday()
{
  return CLTimeOfDay(12, 0, 0, 0);
}

void CLTimeOfDay::SetDefaultFormat(const CString& Format)
{
  sm_sDefaultFormat = Format;
}

CString& CLTimeOfDay::GetDefaultFormat()
{
  return sm_sDefaultFormat;
}

#ifdef _DEBUG
BOOL CLTimeOfDay::SetDoConstructorAsserts(BOOL bDoAsserts)
{
  BOOL bOldDoAsserts = sm_bDoAsserts;
  sm_bDoAsserts = bDoAsserts;
  return bOldDoAsserts;
}
#endif                 

void CLTimeOfDay::ClearStatics()
{
  sm_sBuffer.Empty();
  sm_sDefaultFormat.Empty();
}
                                 
WORD CLTimeOfDay::GetHour() const
{
  AssertValid();
  return (WORD) (m_dwTotalSeconds/3600L);
}

WORD CLTimeOfDay::GetMinute() const
{
  AssertValid();
  return (WORD) ((m_dwTotalSeconds - (GetHour()*3600L))/60);
}

DWORD CLTimeOfDay::GetTotalSeconds() const
{
  AssertValid();
  return m_dwTotalSeconds;
}

WORD CLTimeOfDay::GetSecond() const
{
  AssertValid();
  return (WORD) (m_dwTotalSeconds - (60L * (GetMinute() + (60L*GetHour()))));
}                                                                

WORD CLTimeOfDay::GetMilliSecond() const
{
  AssertValid();
  return m_wMilliSeconds;
}

WORD CLTimeOfDay::GetAMPMHour() const
{
  AssertValid();
  WORD wHour = GetHour();
  if (wHour > 12)
    wHour -= 12;
  return wHour;
}                             

CString& CLTimeOfDay::GetAMPMString() const
{
  AssertValid();
  int nStringID;
  if (GetHour() > 12)
    nStringID = IDS_PM;
  else
    nStringID = IDS_AM;

  if (!sm_sBuffer.LoadString(nStringID))
    ASSERT(FALSE);
  return sm_sBuffer;
}

BOOL CLTimeOfDay::IsValid() const
{                  
  if (m_dwTotalSeconds >= 86400) 
    return FALSE;
  else
    return TRUE;  
}

ULARGE_INTEGER CLTimeOfDay::Collate() const
{
  AssertValid();
  ULARGE_INTEGER rVal;
  rVal.LowPart = m_wMilliSeconds;
  rVal.HighPart = (GetHour()*10000L) + (GetMinute()*100L) + GetSecond();
  return rVal;
}

SYSTEMTIME CLTimeOfDay::GetSYSTEMTIME() const
{
  AssertValid();
  SYSTEMTIME st;

  st.wYear=0;
  st.wMonth=0;
  st.wDayOfWeek=0;
  st.wDay=0;
  st.wHour = GetHour();
  st.wMinute = GetMinute();
  st.wSecond = GetSecond();
  st.wMilliseconds = GetMilliSecond();
  return st;
}

tm CLTimeOfDay::GetTM() const
{
  AssertValid();
  tm rVal;
  
  rVal.tm_hour  = GetHour();
  rVal.tm_min   = GetMinute();
  rVal.tm_sec   = GetSecond();
  rVal.tm_mday  = 0;
  rVal.tm_mon   = 0;
  rVal.tm_year  = 0;
  rVal.tm_wday  = 0;
  rVal.tm_yday  = 0;
  rVal.tm_isdst = 0;
              
  return rVal;
}

double CLTimeOfDay::SecondsAsDouble() const
{
  AssertValid();
  return m_dwTotalSeconds + m_wMilliSeconds/1000.0;
}


CLTimeOfDay& CLTimeOfDay::operator=(const CLTimeOfDay& Tod)
{               
  m_dwTotalSeconds = Tod.m_dwTotalSeconds;
  m_wMilliSeconds = Tod.m_wMilliSeconds;
  return *this;
}

CLTimeOfDay CLTimeOfDay::operator+(const CLTimeSpan& TimeSpan) const
{
  AssertValid();
  CLTimeSpan t = CLTimeSpan(*this) + CLTimeSpan(0, TimeSpan.GetHours(), TimeSpan.GetMinutes(),
                            TimeSpan.GetSeconds(),  TimeSpan.GetMilliSeconds());
  return CLTimeOfDay(t.GetHours(), t.GetMinutes(), t.GetSeconds(), t.GetMilliSeconds());
}

CLTimeOfDay CLTimeOfDay::operator-(const CLTimeSpan& TimeSpan) const
{
  AssertValid();
  CLTimeSpan t = CLTimeSpan::OneDay() + CLTimeSpan(*this) - 
                 CLTimeSpan(0, TimeSpan.GetHours(), TimeSpan.GetMinutes(),
                            TimeSpan.GetSeconds(),  TimeSpan.GetMilliSeconds());
  //1 Day is used to ensure result "t" does not go negative
  return CLTimeOfDay(t.GetHours(), t.GetMinutes(), t.GetSeconds(), t.GetMilliSeconds());
}

CLTimeOfDay& CLTimeOfDay::operator+=(CLTimeSpan& TimeSpan)
{
  *this = *this + TimeSpan;
  return *this;
}

CLTimeOfDay& CLTimeOfDay::operator-=(CLTimeSpan& TimeSpan)
{
  *this = *this - TimeSpan;
  return *this;
}

BOOL CLTimeOfDay::operator==(const CLTimeOfDay& Tod) const
{
  AssertValid();
  if ((m_wMilliSeconds == Tod.m_wMilliSeconds) &&
      (m_dwTotalSeconds == Tod.m_dwTotalSeconds))
    return TRUE;
  else
    return FALSE;    
}

BOOL CLTimeOfDay::operator>(const CLTimeOfDay& Tod) const
{               
  AssertValid();
  if (m_dwTotalSeconds == Tod.m_dwTotalSeconds)
    return (m_wMilliSeconds > Tod.m_wMilliSeconds);
  else
    return (m_dwTotalSeconds > Tod.m_dwTotalSeconds);
}

BOOL CLTimeOfDay::operator>=(const CLTimeOfDay& Tod) const
{               
  AssertValid();
  if (m_dwTotalSeconds == Tod.m_dwTotalSeconds)
    return (m_wMilliSeconds >= Tod.m_wMilliSeconds);
  else
    return (m_dwTotalSeconds >= Tod.m_dwTotalSeconds);
}

BOOL CLTimeOfDay::operator<(const CLTimeOfDay& Tod) const
{             
  AssertValid();
  if (m_dwTotalSeconds == Tod.m_dwTotalSeconds)
    return (m_wMilliSeconds < Tod.m_wMilliSeconds);
  else
    return (m_dwTotalSeconds < Tod.m_dwTotalSeconds);
}

BOOL CLTimeOfDay::operator<=(const CLTimeOfDay& Tod) const
{
  AssertValid();
  if (m_dwTotalSeconds == Tod.m_dwTotalSeconds)
    return (m_wMilliSeconds <= Tod.m_wMilliSeconds);
  else
    return (m_dwTotalSeconds <= Tod.m_dwTotalSeconds);
}

BOOL CLTimeOfDay::operator!=(const CLTimeOfDay& Tod) const
{               
  AssertValid();                  
  return !operator==(Tod);
}

#ifdef _DEBUG
void CLTimeOfDay::AssertValid() const
{
  CObject::AssertValid();
  ASSERT(IsValid());
}
#endif

#ifdef _DEBUG
void CLTimeOfDay::Dump(CDumpContext& dc) const
{
  CObject::Dump(dc);
  dc << Format() << _T("\n");
}
#endif                       

/*    //The Following Format parameters are supported        

%H    Hours in the current day
%M    Minutes in the current hour
%h    12 Hour format Hours in this CLTimeSpan (00 - 12)
%P    AM / PM indicator
%S    Seconds in the current minute
%F    MilliSeconds in the current second
%%    Percent sign       
%x    Time Of Day representation for current locale        
%#H, %#h, %#M, %#S  Remove leading zeros (if any).
*/
CString& CLTimeOfDay::Format(const CString& sFormat) const
{ 
  if (!IsValid())
    sm_sBuffer.Empty();
  else
  {
    CString sBuffer;
    sm_sBuffer.Empty();
    CString rVal;
    int sFmtLength = sFormat.GetLength();

    for (int i=0; i<sFmtLength; i++)
    {
      TCHAR c = sFormat.GetAt(i);
      if (c == TCHAR('%'))
      {
        ++i;
        if (i < sFmtLength)
        {
          c = sFormat.GetAt(i);
          switch (c)
          {
            case TCHAR('H'):
            {
              sBuffer.Format(_T("%.02d"), GetHour());
              rVal += sBuffer;
              break;
            }
            case TCHAR('M'):
            {
              sBuffer.Format(_T("%.02d"), GetMinute());
              rVal += sBuffer;
              break;
            }
            case TCHAR('h'):
            {
              sBuffer.Format(_T("%.02d"), GetAMPMHour());
              rVal += sBuffer;
              break;
            }
            case TCHAR('P'):
            {
              rVal += GetAMPMString();
              break;
            }
            case TCHAR('S'):
            {
              sBuffer.Format(_T("%.02d"), GetSecond());
              rVal += sBuffer;
              break;
            }
            case TCHAR('F'):
            {
              sBuffer.Format(_T("%.03d"), GetMilliSecond());
              rVal += sBuffer;
              break;                                              
            }                                                     
            
          #ifdef _WIN32
            case TCHAR('x'):                                      
            {
              sBuffer.Empty();
              SYSTEMTIME st = GetSYSTEMTIME();
              int Res = ::GetTimeFormat(LOCALE_USER_DEFAULT,
                                      LOCALE_NOUSEROVERRIDE,
                                      &st,
                                      NULL,
                                      sBuffer.GetBufferSetLength(100),
                                      100); 
              if (Res == 0)
                TRACE1("GetDateFormat() Failed in CLTimeSpan::Format(), GetLastError() returned %ul\n", ::GetLastError());
              sBuffer.ReleaseBuffer();
              rVal += sBuffer;
              break;
            }
          #endif
            
            case TCHAR('#'):
            {
              if (i < sFmtLength)
              {
                ++i;
                c = sFormat.GetAt(i);
                switch (c)
                {
                  case TCHAR('H'):
                  {
                    sBuffer.Format(_T("%d"), GetHour());
                    rVal += sBuffer;
                    break;
                  }
                  case TCHAR('h'):
                  {
                    sBuffer.Format(_T("%d"), GetAMPMHour());
                    rVal += sBuffer;
                    break;
                  }
                  case TCHAR('M'):
                  {
                    sBuffer.Format(_T("%d"), GetMinute());
                    rVal += sBuffer;
                    break;
                  }
                  case TCHAR('S'):
                  {
                    sBuffer.Format(_T("%d"), GetSecond());
                    rVal += sBuffer;
                    break;
                  }
                  default:
                  {
                    rVal += c;
                    break;
                  }
                }
              }
              break;
            }
            default:
            {
              rVal += c;
              break;
            }
          }
        }
      }
      else
      {
        rVal += c;
      }
    }
    sm_sBuffer = rVal;
  }
  return sm_sBuffer;
}


void CLTimeOfDay::Serialize(CArchive& ar)
{
  CObject::Serialize(ar);
  if(ar.IsStoring())
  {
    ar << m_dwTotalSeconds;
    ar << m_wMilliSeconds;
  }
  else
  {
    ar >> m_dwTotalSeconds;
    ar >> m_wMilliSeconds;
  }
}

ostream& operator<<(ostream &os, const CLTimeOfDay &TimeOfDay)
{
  return os << TimeOfDay.Format();
}                       

CArchive& operator<<(CArchive& ar, CLTimeOfDay &TimeOfDay)
{
  ASSERT(ar.IsStoring());
  TimeOfDay.Serialize(ar);
  return ar;
}

CArchive& operator>>(CArchive& ar, CLTimeOfDay &TimeOfDay)
{
  ASSERT(!ar.IsStoring());
  TimeOfDay.Serialize(ar);
  return ar;
}






//CLDate implementation


CLDate::CLDate()
{
  Set();
}
  
CLDate::CLDate(LONG Year, WORD Month, WORD Day, 
               WORD Hour, WORD Minute, WORD Second,
               WORD MilliSecond, TimeFrame tf)
{
  Set(Year, Month, Day, Hour, Minute, Second, MilliSecond, tf);
}                                            


CLDate::CLDate(const SYSTEMTIME& st, TimeFrame tf, BOOL bUseDayOfWeek)
{ 
  Set(st, tf, bUseDayOfWeek);
} 


CLDate::CLDate(LONG Year, WORD Month, WORD WeekOfMonth,
               WORD DayOfWeek, WORD Hour, WORD Minute, WORD Second,
               WORD MilliSecond, TimeFrame tf)
{
  Set(Year, Month, WeekOfMonth, DayOfWeek, Hour, Minute, Second, MilliSecond, tf);
}
               
CLDate::CLDate(LONG Days, CDate::DateEpoch e, WORD Hour, WORD Minute,
               WORD Second, WORD MilliSecond, TimeFrame tf)
{
  Set(Days, e, Hour, Minute, Second, MilliSecond, tf);
} 


CLDate::CLDate(const CDate& Date, const CLTimeOfDay& Tod, TimeFrame tf)
{ 
  Set(Date, Tod, tf);
}

CLDate::CLDate(const CLDate& ld)
{                                 
  m_dSeconds = ld.m_dSeconds;
  m_TimeFrame = ld.m_TimeFrame;
}

CLDate::CLDate(const CTime& ct)
{
  Set(ct);
}
      
#ifdef _WIN32
CLDate::CLDate(const COleDateTime& oleTime, TimeFrame tf)
{
  Set(oleTime, tf);
}                     
#endif

CLDate& CLDate::Set()
{
  m_dSeconds = DBL_MAX;
  return *this;
}

CLDate& CLDate::Set(LONG Year, WORD Month, WORD Day,
                    WORD Hour, WORD Minute, WORD Second,
                    WORD MilliSecond, TimeFrame tf)
{              
  m_TimeFrame = tf;

  CDate Date(Year, Month, Day);
  CLTimeOfDay Tod(Hour, Minute, Second, MilliSecond);

  m_dSeconds = Date.GDN()*86400.0 +
         Tod.GetTotalSeconds() +
         Tod.GetMilliSecond()/1000.0;

  if (tf == LOCAL)
    CheckForValidLocalDate();
  return *this;
}
                    
CLDate& CLDate::Set(const SYSTEMTIME& st, TimeFrame tf, BOOL bUseDayOfWeek)
{
  if (bUseDayOfWeek)  //Using Day-in-month format
  {
    if (st.wYear)     //an absolute year, wDayOfWeek is 0 based
      Set(st.wYear, st.wMonth, st.wDay, (WORD)(st.wDayOfWeek+1), st.wHour, 
          st.wMinute, st.wSecond, st.wMilliseconds, tf);
    else              //use the current year
      Set(CurrentTime(tf).GetCDate().GetYear(), st.wMonth, st.wDay, 
          (WORD)(st.wDayOfWeek+1), st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, tf);
  }
  else
  {
    if (st.wYear)     //an absolute year
      Set(st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, tf);
    else              //use the current year
      Set(CurrentTime(tf).GetCDate().GetYear(), st.wMonth, st.wDay, 
          st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, tf);
  }

  return *this;
}


CLDate& CLDate::Set(LONG Year, WORD Month, WORD WeekOfMonth, 
                    WORD DayOfWeek, WORD Hour, WORD Minute, WORD Second,
                    WORD MilliSecond, TimeFrame tf)
{
  m_TimeFrame = tf;

  CDate Date(Year, Month, WeekOfMonth, DayOfWeek);
  CLTimeOfDay Tod(Hour, Minute, Second, MilliSecond);

  m_dSeconds = Date.GDN()*86400.0 +
         Tod.GetTotalSeconds() +
         Tod.GetMilliSecond()/1000.0;

  if (tf == LOCAL)
    CheckForValidLocalDate();
  return *this;
}
                    
CLDate& CLDate::Set(LONG Days, CDate::DateEpoch e, WORD Hour, WORD Minute,
                    WORD Second, WORD MilliSecond, TimeFrame tf)
{
  m_TimeFrame = tf;

  CDate Date(Days, e);
  CLTimeOfDay Tod(Hour, Minute, Second, MilliSecond);

  m_dSeconds = Date.GDN()*86400.0 +
         Tod.GetTotalSeconds() +
         Tod.GetMilliSecond()/1000.0;

  if (tf == LOCAL)
    CheckForValidLocalDate();
  return *this;
}

CLDate& CLDate::Set(const CTime& ct)
{
  m_TimeFrame = UTC;
  tm* pTM = ct.GetGmtTm();
  Set(pTM->tm_year + 1900, (WORD) (pTM->tm_mon+1), (WORD) pTM->tm_mday, 
         (WORD) pTM->tm_hour, (WORD) pTM->tm_min, (WORD) pTM->tm_sec, 0, UTC);
  return *this;  
}

CLDate& CLDate::Set(const CDate& Date, const CLTimeOfDay& Tod, TimeFrame tf)
{
  m_TimeFrame = tf;

  m_dSeconds = Date.GDN()*86400.0 +
         Tod.GetTotalSeconds() +
         Tod.GetMilliSecond()/1000.0;


  if (tf == LOCAL)
    CheckForValidLocalDate();
  return *this;  
}
      
#ifdef _WIN32
CLDate& CLDate::Set(const COleDateTime& oleTime, TimeFrame tf)
{
  return Set((LONG) oleTime.GetYear(), (WORD) oleTime.GetMonth(), (WORD) oleTime.GetDay(),
             (WORD) oleTime.GetHour(), (WORD) oleTime.GetMinute(), (WORD) oleTime.GetSecond(), 0, tf);
}                     
#endif

void CLDate::CheckForValidLocalDate()
{
  //Should only be called when tested a LOCAL CLDate
  ASSERT(m_TimeFrame == LOCAL);

  TIME_ZONE_INFORMATION tzi;
  ASSERT(::GetTimeZoneInformation(&tzi) != TIME_ZONE_ID_UNKNOWN);
  
  //Set the TimeFrame to UTC so that we do not need to perform DST conversions in
  //the following arithmetic
  m_TimeFrame = UTC;

  CLDate BeginDaylightTime;
  LONG ThisYear = GetCDate().GetYear();
  if (tzi.DaylightDate.wYear == 0)  //Using Day-in-month format
    BeginDaylightTime.Set(ThisYear, tzi.DaylightDate.wMonth, tzi.DaylightDate.wDay, (WORD)(tzi.DaylightDate.wDayOfWeek+1),
                          tzi.DaylightDate.wHour, tzi.DaylightDate.wMinute, tzi.DaylightDate.wSecond, tzi.DaylightDate.wMilliseconds, UTC);
  else
    BeginDaylightTime.Set(tzi.DaylightDate.wYear, tzi.DaylightDate.wMonth, tzi.DaylightDate.wDay, tzi.DaylightDate.wHour,
                          tzi.DaylightDate.wMinute, tzi.DaylightDate.wSecond, tzi.DaylightDate.wMilliseconds, UTC);

  CLDate BeginStandardTime;
  if (tzi.StandardDate.wYear == 0)  //Using Day-in-month format
    BeginStandardTime.Set(ThisYear, tzi.StandardDate.wMonth, tzi.StandardDate.wDay, (WORD)(tzi.StandardDate.wDayOfWeek+1),
                          tzi.StandardDate.wHour, tzi.StandardDate.wMinute, tzi.StandardDate.wSecond, tzi.StandardDate.wMilliseconds, UTC);
  else
    BeginStandardTime.Set(tzi.StandardDate.wYear, tzi.StandardDate.wMonth, tzi.StandardDate.wDay, tzi.StandardDate.wHour, 
                          tzi.StandardDate.wMinute, tzi.StandardDate.wSecond, tzi.StandardDate.wMilliseconds, UTC);


#ifdef _DEBUG
  CString& s = BeginDaylightTime.Format();
  s = BeginStandardTime.Format();
#endif

  if (tzi.DaylightBias > 0)
  {
    //A CLDate which specifies a date which occurs twice
    CLDate StartNonUnique(BeginDaylightTime - CLTimeSpan(0, 0, (WORD) tzi.DaylightBias, 0, 0));
    if ((*this >= StartNonUnique) && (*this < BeginDaylightTime))
    {
      TRACE0("A CLDate using a LOCAL timeframe tried to be constructed which represents a non unique absolute time\n"); 
      if (sm_bDoAsserts)
        ASSERT(FALSE);
      Set();
      return;
    }

    //A CLDate which specifies a date which does not occur
    CLDate EndSkip(BeginStandardTime + CLTimeSpan(0, 0, (WORD) tzi.DaylightBias, 0, 0));
    if ((*this > BeginStandardTime) && (*this < EndSkip))
    {
      TRACE0("A CLDate using a LOCAL timeframe tried to be constructed which does not occur\n");
      if (sm_bDoAsserts)
        ASSERT(FALSE);
      Set();
      return;
    }

  }
  else if (tzi.DaylightBias < 0)
  {
    //A CLDate which specifies a date which does not occur
    CLDate EndSkip(BeginDaylightTime + CLTimeSpan(0, 0, (WORD) -tzi.DaylightBias, 0, 0));
    if ((*this > BeginDaylightTime) && (*this < EndSkip))
    {
      TRACE0("A CLDate using a LOCAL timeframe tried to be constructed which does not occur\n"); 
      if (sm_bDoAsserts)
        ASSERT(FALSE);
      Set();
      return;
    }

    //A CLDate which specifies a date which occurs twice
    CLDate StartNonUnique(BeginStandardTime - CLTimeSpan(0, 0, (WORD) -tzi.DaylightBias, 0, 0));
    if ((*this >= StartNonUnique) && 
        (*this <= BeginStandardTime) )
    {
      TRACE0("A CLDate using a LOCAL timeframe tried to be constructed which represents a non unique absolute time\n"); 
      if (sm_bDoAsserts)
        ASSERT(FALSE);
      Set();
      return;
    }
  }

  //return the timeframe back to local
  m_TimeFrame = LOCAL;
}
                    
CLDate CLDate::CurrentTime(TimeFrame tf)
{                                      
  #ifdef _WIN32
    SYSTEMTIME st;
    ::GetSystemTime(&st);
    CLDate rVal(st, UTC);
    rVal.SetTimeFrame(tf);
    return rVal; 
  #else         
    time_t csecs = time(NULL);
    tm* ct = localtime(&csecs);
    //Constructed using UTC timeframe to avoid check for valid timeframe
    CLDate rVal((LONG) (ct->tm_year+1900), (WORD) (ct->tm_mon+1), (WORD) (ct->tm_mday),
                (WORD) (ct->tm_hour), (WORD) (ct->tm_min), (WORD) (ct->tm_sec), 0, UTC);
    rVal.m_TimeFrame = LOCAL;            
    rVal.SetTimeFrame(tf);
    return rVal;
  #endif
}

void CLDate::SetDefaultFormat(const CString& Format)
{
  sm_sDefaultFormat = Format;
}

CString& CLDate::GetDefaultFormat()
{
  return sm_sDefaultFormat;
}

CLTimeSpan CLDate::DeltaT(CLDate& d)
{
  CLTimeSpan Tspan(d - CLDate(CDate::Epoch2000(), CLTimeOfDay(0, 0, 0, 0), d.GetTimeFrame()));
  double T = Tspan.GetTotalDays()/36525.0;
  double S;

  double y = 2000 + T * 100;
  if (y > 2000)
    S = 102.3 + T * (123.5 + T * 32.5);
  else if (y < 1620)
  {
    if (y < 948)
      S = 2715.6 + T * (573.36 + T * 46.5);
    else 
      S = 50.6 + T * (67.5 + T * 22.5);
  }
  else /* Interpolate from the static data table */
  {
    int Index = (int)((y - 1620) / 2);
    if (Index > 185)
      Index = 185;
    y = y / 2 - Index - 810;
    S = (DeltaTTable[Index] + (DeltaTTable[Index + 1] - DeltaTTable[Index]) * y) / 10;
  }

  return CLTimeSpan(S);
}

BOOL CLDate::CurrentlyInDST()
{
  TIME_ZONE_INFORMATION tzi;
  return ::GetTimeZoneInformation(&tzi) == TIME_ZONE_ID_DAYLIGHT;
}

CLTimeSpan CLDate::DaylightBias()
{
  TIME_ZONE_INFORMATION tzi;
  ASSERT(::GetTimeZoneInformation(&tzi) != TIME_ZONE_ID_UNKNOWN);

  CLTimeSpan rVal;
  if (tzi.DaylightBias > 0)
    rVal = CLTimeSpan(0, 0, (WORD) tzi.DaylightBias, 0, 0);
  else
  {
    rVal = CLTimeSpan(0, 0, (WORD) -tzi.DaylightBias, 0, 0);
    rVal.Negate();
  }
  return rVal;
}

CLTimeSpan CLDate::TimezoneBias()
{
  TIME_ZONE_INFORMATION tzi;
  ASSERT(::GetTimeZoneInformation(&tzi) != TIME_ZONE_ID_UNKNOWN);

  CLTimeSpan rVal;
  LONG tzBias = tzi.StandardBias + tzi.Bias;
  if (tzBias > 0)
    rVal = CLTimeSpan(0, 0, (WORD) tzBias, 0, 0);
  else
  {
    rVal = CLTimeSpan(0, 0, (WORD) -tzBias, 0, 0);
    rVal.Negate();
  }
  return rVal;
}

CString& CLDate::DaylightName()
{
  TIME_ZONE_INFORMATION tzi;
  ASSERT(::GetTimeZoneInformation(&tzi) != TIME_ZONE_ID_UNKNOWN);
  CString sName(tzi.DaylightName);
  sm_sBuffer = sName;
  return sm_sBuffer;
}

CString& CLDate::StandardName()
{
  TIME_ZONE_INFORMATION tzi;
  ASSERT(::GetTimeZoneInformation(&tzi) != TIME_ZONE_ID_UNKNOWN);
  CString sName(tzi.StandardName);
  sm_sBuffer = sName;
  return sm_sBuffer;
}

#ifdef _DEBUG
BOOL CLDate::SetDoConstructorAsserts(BOOL bDoAsserts)
{
  BOOL bOldDoAsserts = sm_bDoAsserts;
  sm_bDoAsserts = bDoAsserts;
  return bOldDoAsserts;
}
#endif            

void CLDate::ClearStatics()
{
  sm_sBuffer.Empty();
  sm_sDefaultFormat.Empty();
}

CDate CLDate::GetCDate() const
{
  AssertValid();
  return CDate((LONG) (m_dSeconds/86400.0), CDate::EPOCH_GREG);
}

CLTimeOfDay CLDate::GetCLTimeOfDay() const
{
  AssertValid();
  return CLTimeOfDay(m_dSeconds - GetCDate().GDN()*86400.0);
}

DateLS CLDate::GetDate() const
{
  DateLS rVal;
  DateS ds = GetCDate().GetDate();

  rVal.lYear = ds.lYear; 
  rVal.wMonth = ds.wMonth;
  rVal.wDay = ds.wDay;
  rVal.wWday = ds.wWday;
  rVal.wYday = ds.wYday;
  rVal.ct = ds.ct;
  rVal.tf = m_TimeFrame;
  CLTimeOfDay tod(GetCLTimeOfDay());
  rVal.wHour = tod.GetHour();
  rVal.wMinute = tod.GetMinute();
  rVal.wSecond = tod.GetSecond();
  rVal.wMilliSeconds = tod.GetMilliSecond();
  
  return rVal;
};

SYSTEMTIME CLDate::GetSYSTEMTIME() const
{
  SYSTEMTIME s = GetCDate().GetSYSTEMTIME();
  CLTimeOfDay tod(GetCLTimeOfDay());

  s.wHour = tod.GetHour();
  s.wMinute = tod.GetMinute();
  s.wSecond = tod.GetSecond();
  s.wMilliseconds = tod.GetMilliSecond();

  return s;
}                         

tm CLDate::GetTM()
{
  AssertValid();

  tm rVal;                
  rVal.tm_sec   = 0;
  rVal.tm_min   = 0;
  rVal.tm_hour  = 0;
  rVal.tm_mday  = 0;
  rVal.tm_mon   = 0;
  rVal.tm_year  = 0;
  rVal.tm_wday  = 0;
  rVal.tm_yday  = 0;
  rVal.tm_isdst = 0;

  DateLS ds = GetDate();

#ifdef _WIN32
  long MinYear = 1900L + LONG_MIN;
  long MaxYear = LONG_MAX;
#else
  long MinYear = 1900L + SHRT_MIN;
  long MaxYear = 1900L + SHRT_MAX;
#endif
 
  //handle range errors
  if ((ds.lYear < MinYear) || (ds.lYear > MaxYear))
  {
    ASSERT(FALSE);
    return rVal;
  }
  
  rVal.tm_hour = ds.wHour;
  rVal.tm_min = ds.wMinute;
  rVal.tm_sec = ds.wSecond;
  rVal.tm_year = (int) (ds.lYear - 1900L);
  rVal.tm_mon = ds.wMonth - 1;  //tm struct uses 0 based indices
  rVal.tm_wday = ds.wWday - 1;  //tm struct uses 0 based indices
  rVal.tm_mday = ds.wDay;
  rVal.tm_wday = ds.wYday - 1; //Returns days since Jan 1
  rVal.tm_isdst = IsDST();
              
  return rVal;
}

TimeFrame CLDate::GetTimeFrame() const
{
  AssertValid();
  return m_TimeFrame;
}

TimeFrame CLDate::SetTimeFrame(TimeFrame tf)
{
  if (tf == m_TimeFrame)  //quick return
    return tf;
    
  TimeFrame OldTF = m_TimeFrame;   

  switch (m_TimeFrame)
  {
    case LOCAL:
    {
      switch (tf)
      {
        case UTC:
        {
          //pretend that timeframe is UTC to avoid recursion in the arithmetic
          m_TimeFrame = UTC;

          *this += TimezoneBias();
          if (DST())
            *this += DaylightBias();
          break;
        }
        case ET:
        {
          SetTimeFrame(UTC);
          SetTimeFrame(ET);
          break;
        }
        default: ASSERT(FALSE);
      }
      break;
    }
    case ET:
    {
      switch (tf)
      {
        case UTC:
        {
          *this -= DeltaT();
          break;
        }
        case LOCAL:
        {
          SetTimeFrame(UTC);
          SetTimeFrame(LOCAL);
          break;
        }
        default: ASSERT(FALSE);
      }
      break;
    }
    case UTC:
    {
      switch (tf)
      {
        case LOCAL:
        {
          *this -= TimezoneBias();
          if (DST())
          {
            *this -= DaylightBias();
            sm_bIsDst = TRUE;
          }
          else
            sm_bIsDst = FALSE;
          break;
        }
        case ET:
        {
          *this += DeltaT();
          break;
        }
        default: ASSERT(FALSE);
      }
      break;
    }

    default: ASSERT(FALSE);
  }

  m_TimeFrame = tf;
  return OldTF;
};

BOOL CLDate::IsDST()
{
  AssertValid();
  BOOL rVal;  
  TimeFrame OldTF = GetTimeFrame();
  if (OldTF != LOCAL)
  {
    SetTimeFrame(LOCAL);
    rVal = sm_bIsDst;
  }
  else
    rVal = DST();
  return rVal;
}

BOOL CLDate::DST()
{
  AssertValid();
  BOOL rVal = TRUE;
  TIME_ZONE_INFORMATION tzi;
  ASSERT(::GetTimeZoneInformation(&tzi) != TIME_ZONE_ID_UNKNOWN);

  long lYear = GetCDate().GetYear();

  //SYSTEMTIME can only accomadate a WORD sized year
  //so we always return FALSE if outside of this range
  if ((lYear > SHRT_MAX) || (lYear < 0))
    rVal = FALSE;

  if (rVal)
  {
    TimeFrame OldTF = m_TimeFrame;
    m_TimeFrame = UTC;

    BOOL bUseDayOfWeek = FALSE;
    if (tzi.DaylightDate.wYear == 0)
    {
      bUseDayOfWeek = TRUE;
      tzi.DaylightDate.wYear = (WORD) lYear;
    }

    CLDate BeginDST(tzi.DaylightDate, UTC, bUseDayOfWeek);

#ifdef _DEBUG
    CString& s = BeginDST.Format();
#endif

    bUseDayOfWeek = FALSE;
    if (tzi.StandardDate.wYear == 0)
    {
      bUseDayOfWeek = TRUE;
      tzi.StandardDate.wYear = (WORD) lYear;
    }

    CLDate EndDST(tzi.StandardDate, UTC, bUseDayOfWeek);
#ifdef _DEBUG
    s = EndDST.Format();
#endif
  
    rVal = rVal && (*this >= BeginDST && *this < EndDST);

    m_TimeFrame = OldTF;
  }
  
  return rVal;
}

CString& CLDate::GetStringTimeFrame() const
{
  switch (m_TimeFrame)
  {
    case UTC:   
      if (!sm_sBuffer.LoadString(IDS_UTC))
        ASSERT(FALSE);
      break;
    case ET:  
      if (!sm_sBuffer.LoadString(IDS_ET))
        ASSERT(FALSE);
      break;
    case LOCAL: 
      if (!sm_sBuffer.LoadString(IDS_LOCAL))
        ASSERT(FALSE);
      break;
    default:  
      ASSERT(FALSE);
      break;
  }
  return sm_sBuffer;
}

double CLDate::GDNAsDouble() const
{
  AssertValid();
  return m_dSeconds/86400;
}

double CLDate::GSNAsDouble() const
{
  AssertValid();
  return m_dSeconds;
}


void CLDate::AddYear(int Years)
{
  AssertValid();
  CDate Date(GetCDate());
  CLTimeOfDay Tod(GetCLTimeOfDay());
  Date.AddYear(Years);
  Set(Date, Tod, m_TimeFrame);
}

void CLDate::AddMonth(int Months)
{
  AssertValid();
  CDate Date(GetCDate());
  CLTimeOfDay Tod(GetCLTimeOfDay());
  Date.AddMonth(Months);
  Set(Date, Tod, m_TimeFrame);
}

void CLDate::AddWeek(int Weeks)
{
  AssertValid();

  CDate Date(GetCDate());
  CLTimeOfDay Tod(GetCLTimeOfDay());
  Date.AddWeek(Weeks);
  Set(Date, Tod, m_TimeFrame);
}

BOOL CLDate::IsValid() const
{
  return (m_dSeconds != DBL_MAX);
}

CLTimeSpan CLDate::DeltaT()
{
  AssertValid();
  return DeltaT(*this);
}

CLDate& CLDate::operator=(const CLDate& d) 
{
  m_TimeFrame = d.m_TimeFrame;
  m_dSeconds = d.m_dSeconds;

  return *this;
}              

CLDate CLDate::operator+(const CLTimeSpan& TimeSpan)
{
  AssertValid();
  TimeSpan.AssertValid();

  //Because LOCAL Time is not a continous timeframe convert if necessary
  TimeFrame OldTF = GetTimeFrame();
  if (GetTimeFrame() == LOCAL)
    SetTimeFrame(UTC);


  double s = m_dSeconds + TimeSpan.m_dSeconds;
  CLDate rVal;
  rVal.m_dSeconds = s;
  rVal.m_TimeFrame = m_TimeFrame;

  SetTimeFrame(OldTF);
  rVal.SetTimeFrame(OldTF);

  return rVal;
}

CLTimeSpan CLDate::operator-(CLDate& ld)
{
  AssertValid();
  ld.AssertValid();

  //Because LOCAL Time is not a continous timeframe convert if necessary
  TimeFrame OldTF1 = GetTimeFrame();
  TimeFrame OldTF2 = ld.GetTimeFrame();
  if (!((OldTF1 == ET) && (OldTF2 == ET)))
  {
    TimeFrame OldTF1 = SetTimeFrame(UTC);
    TimeFrame OldTF2 = ld.SetTimeFrame(UTC);
  }


  double s = m_dSeconds - ld.m_dSeconds;
  CLTimeSpan rVal(s);

  SetTimeFrame(OldTF1);
  ld.SetTimeFrame(OldTF2);

  return rVal;
}

CLDate CLDate::operator-(const CLTimeSpan& TimeSpan)
{
  AssertValid();
  TimeSpan.AssertValid();

  //Because LOCAL Time is not a continous timeframe convert if necessary
  TimeFrame OldTF = GetTimeFrame();
  if (GetTimeFrame() == LOCAL)
    SetTimeFrame(UTC);


  double s = m_dSeconds - TimeSpan.m_dSeconds;
  CLDate rVal;
  rVal.m_dSeconds = s;
  rVal.m_TimeFrame = m_TimeFrame;


  return rVal;
}

CLDate& CLDate::operator+=(const CLTimeSpan& TimeSpan)
{
  *this = *this + TimeSpan;
  return *this;
}

CLDate& CLDate::operator-=(const CLTimeSpan& TimeSpan)
{
  *this = *this - TimeSpan;
  return *this;
}

CLDate& CLDate::operator++()
{
  AssertValid();
  m_dSeconds += 86400;
  return *this;
}

CLDate& CLDate::operator--()
{
  AssertValid();
  m_dSeconds -= 86400;
  return *this;
}
  
BOOL CLDate::operator==(CLDate& ld)
{
  AssertValid();
  
  //Because LOCAL Time is not a continous timeframe convert if necessary
  TimeFrame OldTF1 = GetTimeFrame();
  TimeFrame OldTF2 = ld.GetTimeFrame();
  if (!((OldTF1 == ET) && (OldTF2 == ET)))
  {
    TimeFrame OldTF1 = SetTimeFrame(UTC);
    TimeFrame OldTF2 = ld.SetTimeFrame(UTC);
  }

  BOOL rVal = (m_dSeconds == ld.m_dSeconds);

  SetTimeFrame(OldTF1);
  ld.SetTimeFrame(OldTF2);

  return rVal;
}

BOOL CLDate::operator>(CLDate& ld)
{
  AssertValid();

  //Because LOCAL Time is not a continous timeframe convert if necessary
  TimeFrame OldTF1 = GetTimeFrame();
  TimeFrame OldTF2 = ld.GetTimeFrame();
  if (!((OldTF1 == ET) && (OldTF2 == ET)))
  {
    TimeFrame OldTF1 = SetTimeFrame(UTC);
    TimeFrame OldTF2 = ld.SetTimeFrame(UTC);
  }

  BOOL rVal = (m_dSeconds > ld.m_dSeconds);

  SetTimeFrame(OldTF1);
  ld.SetTimeFrame(OldTF2);

  return rVal;
}

BOOL CLDate::operator>=(CLDate& ld)
{
  AssertValid();

  //Because LOCAL Time is not a continous timeframe convert if necessary
  TimeFrame OldTF1 = GetTimeFrame();
  TimeFrame OldTF2 = ld.GetTimeFrame();
  if (!((OldTF1 == ET) && (OldTF2 == ET)))
  {
    TimeFrame OldTF1 = SetTimeFrame(UTC);
    TimeFrame OldTF2 = ld.SetTimeFrame(UTC);
  }

  BOOL rVal = (m_dSeconds >= ld.m_dSeconds);

  SetTimeFrame(OldTF1);
  ld.SetTimeFrame(OldTF2);

  return rVal;
}

BOOL CLDate::operator<(CLDate& ld)
{
  AssertValid();

  //Because LOCAL Time is not a continous timeframe convert if necessary
  TimeFrame OldTF1 = GetTimeFrame();
  TimeFrame OldTF2 = ld.GetTimeFrame();
  if (!((OldTF1 == ET) && (OldTF2 == ET)))
  {
    TimeFrame OldTF1 = SetTimeFrame(UTC);
    TimeFrame OldTF2 = ld.SetTimeFrame(UTC);
  }

  BOOL rVal = (m_dSeconds < ld.m_dSeconds);

  SetTimeFrame(OldTF1);
  ld.SetTimeFrame(OldTF2);

  return rVal;
}

BOOL CLDate::operator<=(CLDate& ld)
{
  AssertValid();

  //Because LOCAL Time is not a continous timeframe convert if necessary
  TimeFrame OldTF1 = GetTimeFrame();
  TimeFrame OldTF2 = ld.GetTimeFrame();
  if (!((OldTF1 == ET) && (OldTF2 == ET)))
  {
    TimeFrame OldTF1 = SetTimeFrame(UTC);
    TimeFrame OldTF2 = ld.SetTimeFrame(UTC);
  }

  BOOL rVal = (m_dSeconds <= ld.m_dSeconds);

  SetTimeFrame(OldTF1);
  ld.SetTimeFrame(OldTF2);

  return rVal;
}

BOOL CLDate::operator!=(CLDate& ld)
{
  AssertValid();
  return !operator==(ld);
}

#ifdef _DEBUG
void CLDate::AssertValid() const       
{
  CObject::AssertValid();
  ASSERT(IsValid());
}
#endif

#ifdef _DEBUG
void CLDate::Dump(CDumpContext& dc) const
{
  CObject::Dump(dc);
  dc << Format() << _T("\n");
}
#endif           

/*
CString CLDate::Format(const CString& sFormat=CDate::m_sDefaultFormat) const
%a    Abbreviated weekday name
%A    Full weekday name
%b    Abbreviated month name
%B    Full month name
%d    Day of month as decimal number (01 - 31)
%j    Day of year as decimal number (001 - 366)
%m    Month as decimal number (01 - 12)
%P    AM / PM indicator
%U    Week of year as decimal number
%w    Weekday as decimal number (1 - 7; Sunday is 1)
%x    Date representation for current locale,  namely 
        Date representation + " " + Time Representation for current locale
%y    Year without century, as decimal number (00 - 99)
%Y    Year with century, as decimal number
%c    Year displayed using C.E.(Current Epoch) / B.C.E (Before Current Epoch) convention e.g. -1023 = 1022 BCE
%t    String containing a representation of the TimeFrame ("UTC", "LOCAL" or "ET")

%H    Hours in the day
%h    12 Hour format Hours in (00 - 12)
%M    Minutes in the hour
%S    Seconds in the minute
%F    MilliSeconds in the second
%%    Percent sign        


//may also need to include full windows escape character

%%    Percent sign

As in the printf function, the # flag may prefix any formatting code. 
In that case, the meaning of the format code is changed as follows.

Format Code Meaning
%#x Long date representation, appropriate to current locale, namely
      Long Date representation + " " + Time Representation for current locale


%#d, %#j, %#m, %#U, %#w, %#y, %#H, %#h, %#M, %#S  Remove leading zeros (if any).
*/
CString& CLDate::Format(const CString& sFormat) const
{ 
  if (!IsValid())
    sm_sBuffer.Empty();
  else
  {
    CString sBuffer;
    sm_sBuffer.Empty();
    CString rVal;
    int sFmtLength = sFormat.GetLength();

    for (int i=0; i<sFmtLength; i++)
    {
      TCHAR c = sFormat.GetAt(i);
      if (c == '%')
      {
        ++i;
        if (i < sFmtLength)
        {
          c = sFormat.GetAt(i);
          switch (c)
          {
            case TCHAR('H'):
            {
              sBuffer.Format(_T("%.02d"), GetCLTimeOfDay().GetHour());
              rVal += sBuffer;
              break;
            }
            case TCHAR('h'):
            {
              sBuffer.Format(_T("%.02d"), GetCLTimeOfDay().GetAMPMHour());
              rVal += sBuffer;
              break;
            }
            case TCHAR('M'):
            {
              sBuffer.Format(_T("%.02d"), GetCLTimeOfDay().GetMinute());
              rVal += sBuffer;
              break;
            }
            case TCHAR('P'):
            {
              rVal += GetCLTimeOfDay().GetAMPMString();
              break;
            }
            case TCHAR('S'):
            {
              sBuffer.Format(_T("%.02d"), GetCLTimeOfDay().GetSecond());
              rVal += sBuffer;
              break;
            }
            case TCHAR('F'):
            {
              sBuffer.Format(_T("%.03d"), GetCLTimeOfDay().GetMilliSecond());
              rVal += sBuffer;
              break;
            }
            case TCHAR('a'):
            {
              rVal += GetCDate().GetAbrStringDayOfWeek();
              break;
            }
            case TCHAR('A'):
            {
              rVal += GetCDate().GetFullStringDayOfWeek();
              break;
            }
            case TCHAR('b'):
            {
              rVal += GetCDate().GetAbrStringMonth();
              break;
            }
            case TCHAR('B'):
            {
              rVal += GetCDate().GetFullStringMonth();
              break;
            }
            case TCHAR('c'):
            {
              rVal += GetCDate().GetStringCEBCEYear();
              break;
            }
            case TCHAR('d'):
            {
              sBuffer.Format(_T("%.02d"), GetCDate().GetDay());
              rVal += sBuffer;
              break;
            }
            case TCHAR('j'):
            {
              sBuffer.Format(_T("%.03d"), GetCDate().DaysSinceJan0());
              rVal += sBuffer;
              break;
            }
            case TCHAR('m'):
            {
              sBuffer.Format(_T("%.02d"), GetCDate().GetMonth());
              rVal += sBuffer;
              break;
            }
            case TCHAR('t'):
            {
              rVal += GetStringTimeFrame();
              break;
            }
            case TCHAR('U'):
            {
              sBuffer.Format(_T("%.02d"), GetCDate().GetWeekOfYear());
              rVal += sBuffer;
              break;
            }
            case TCHAR('w'):
            {
              sBuffer.Format(_T("%d"), GetCDate().GetDayOfWeek());
              rVal += sBuffer;
              break;
            }
            case TCHAR('x'):
            {
              rVal += GetCDate().Format(_T("%x")) + _T(" ") + GetCLTimeOfDay().Format(_T("%x"));
              break;
            }
            case TCHAR('y'):
            {
              LONG Year = GetCDate().GetYear();
              sBuffer.Format(_T("%.02d"), GetCDate().Get2DigitYear());
              rVal += sBuffer;
              break;
            }
            case TCHAR('Y'):
            {
              sBuffer.Format(_T("%ld"), GetCDate().GetYear());
              rVal += sBuffer;
              break;
            }
            case TCHAR('#'):
            {
              if (i < sFmtLength)
              {
                ++i;
                c = sFormat.GetAt(i);
                switch (c)
                {
                  case TCHAR('d'):
                  {
                    sBuffer.Format(_T("%d"), GetCDate().GetDay());
                    rVal += sBuffer;
                    break;
                  }
                  case TCHAR('j'):
                  {
                    sBuffer.Format(_T("%d"), GetCDate().DaysSinceJan0());
                    rVal += sBuffer;
                    break;
                  }
                  case TCHAR('m'):
                  {
                    sBuffer.Format(_T("%d"), GetCDate().GetMonth());
                    rVal += sBuffer;
                    break;
                  }
                  case TCHAR('U'):
                  {
                    sBuffer.Format(_T("%d"), GetCDate().GetWeekOfYear());
                    rVal += sBuffer;
                    break;
                  }
                  case TCHAR('x'):
                  {
                    rVal += GetCDate().Format(_T("%#x")) + _T(" ") + GetCLTimeOfDay().Format(_T("%x"));
                    break;
                  }
                  case TCHAR('y'):
                  {
                    LONG Year = GetCDate().GetYear();
                    sBuffer.Format(_T("%d"), GetCDate().Get2DigitYear());
                    rVal += sBuffer;
                    break;
                  }
                  case TCHAR('H'):
                  {
                    sBuffer.Format(_T("%d"), GetCLTimeOfDay().GetHour());
                    rVal += sBuffer;
                    break;
                  }
                  case TCHAR('h'):
                  {
                    sBuffer.Format(_T("%d"), GetCLTimeOfDay().GetAMPMHour());
                    rVal += sBuffer;
                    break;
                  }
                  case TCHAR('M'):
                  {
                    sBuffer.Format(_T("%d"), GetCLTimeOfDay().GetMinute());
                    rVal += sBuffer;
                    break;
                  }
                  case TCHAR('S'):
                  {
                    sBuffer.Format(_T("%d"), GetCLTimeOfDay().GetSecond());
                    rVal += sBuffer;
                    break;
                  }
                  default:
                  {
                    rVal += c;
                    break;
                  }
                }
              }
              break;
            }
            default:
            {
              rVal += c;
              break;
            }
          }
        }
      }
      else
      {
        rVal += c;
      }
    }
    sm_sBuffer = rVal;
  }

  return sm_sBuffer;
}

void CLDate::Serialize(CArchive& ar)
{
  CObject::Serialize(ar);
  if(ar.IsStoring())
  {
    ar << m_dSeconds;
    ar << (WORD) m_TimeFrame;
  }
  else
  {
    ar >> m_dSeconds;
    ar >> (WORD&) m_TimeFrame;
  }
}

ostream& operator<<(ostream& os, const CLDate& ld)
{
  return os << ld.Format();
}

CArchive& operator<<(CArchive& ar, CLDate& ld)
{
  ASSERT(ar.IsStoring());
  ld.Serialize(ar);
  return ar;
}

CArchive& operator>>(CArchive& ar, CLDate& ld)
{
  ASSERT(!ar.IsStoring());
  ld.Serialize(ar);
  return ar;
}



