#include "stdafx.h"         // MFC core and standard components
#include "dtime.h"          // DTime main include



//the test app        
#if defined(_WINDOWS) || defined(_WIN32)
class CApp : public CWinApp
{
  virtual BOOL InitInstance(); 
};

//create the app
CApp NEAR theApp;


//test code goes in InitInstance under Windows or main on Dos
BOOL CApp::InitInstance()
{              
#else
int main()
{
#endif //defined(_WINDOWS) || defined(_WIN32)

#if defined(_WINDOWS) || defined(_WIN32)
  DWORD StartTicks = GetTickCount();
#else
  time_t StartTime = time(NULL);  
#endif  
  
  //initialise the DTime package
  InitDTime();
  InitDTimeSettings();

                    
  //Set the title of the console Window
#ifdef _WIN32
  SetConsoleTitle(_T("Test program to exercise the DTime package"));

  //Uncomment the following line to try the german version of DTime
  //SetThreadLocale(MAKELCID(MAKELANGID(LANG_GERMAN, SUBLANG_GERMAN), SORT_DEFAULT));

#endif

  //Display some intro text
  _tprintf(_T("This program is best used under a debugger so\n"));
  _tprintf(_T("that code can be stepped into etc.\n"));
  _tprintf(_T("Some calls to Dtime contained in this code is designed to cause ASSERTIONS\n"));
  _tprintf(_T("<Hit Enter to continue>\n"));
  int chr = getchar();

  //first some helpful information will be displayed
  _tprintf(_T("\nTimezone Standard Name is currently \"%s\"\n"), CLDate::StandardName());
  _tprintf(_T("Timezone Bias is currently %s\n"), (CLDate::TimezoneBias()).Format());
  _tprintf(_T("Daylight Name is currently \"%s\"\n"), CLDate::DaylightName());
  _tprintf(_T("Daylight Bias is currently %s\n"), (CLDate::DaylightBias()).Format());

  
  //Test of the CDate class

  //first all the constructors
  CDate x(1582, CDate::OCTOBER, 15);    //m_lDays = 0
  x = CDate(1992, CDate::OCTOBER, 10);  //m_lDays = 149745
  x = CDate(-4712, CDate::JANUARY, 1);  //m_lDays = -2299161
  x = CDate(1582, CDate::OCTOBER, 4);   //m_lDays = -1;


  //should be invalid dates, causing ASSERTs
  /*
  x = CDate(1582, CDate::OCTOBER, 8);
  ASSERT(!x.IsValid());
  x = CDate(1995, CDate::FEBRUARY, 29);
  ASSERT(!x.IsValid());
  x = CDate(1900, CDate::FEBRUARY, 29);
  ASSERT(!x.IsValid());
  x = CDate(1582, CDate::JANUARY, 32);
  ASSERT(!x.IsValid());
  x = CDate(1900, 13, 8);
  ASSERT(!x.IsValid());
  x = CDate(5879612L, 1, 1);
  ASSERT(!x.IsValid());
  x = CDate(5879611L, 8, 1);
  ASSERT(!x.IsValid());
  x = CDate(5879612L, 7, 12);
  ASSERT(!x.IsValid());
  */


  //should be invalid dates and should ASSERT
  /*
  CDate::SetDoAsserts(TRUE);
  x = CDate(1582, CDate::OCTOBER, 8);
  x = CDate(1995, CDate::FEBRUARY, 29);
  x = CDate(1900, CDate::FEBRUARY, 29);
  x = CDate(1582, CDate::JANUARY, 32);
  x = CDate(1900, 13, 8);
  x = CDate(5879612L, 1, 1);
  x = CDate(5879611L, 8, 1);
  x = CDate(5879612L, 7, 12);
  */


  //construction using DateS structure
  DateS ds;
  ds.lYear = 1582;
  ds.wMonth = CDate::OCTOBER;
  ds.wDay = 15;
  x = CDate(ds.lYear, ds.wMonth, ds.wDay);  //m_lDays = 0


  //Construction using the Win32 SYSTEMTIME structure
  SYSTEMTIME st;
  st.wYear = 1582;
  st.wMonth = 10;
  st.wDay = 15;
  x = CDate(st);


  //Construction using the direct count of days
  x = CDate(0, CDate::EPOCH_JD);    //m_lDays = -2299161
  x = CDate(0, CDate::EPOCH_GREG);  //m_lDays = 0
  x = CDate(0, CDate::EPOCH_MJD);   //m_lDays = 100839
  x = CDate(0, CDate::EPOCH_1900);  //m_lDays = 115860
  x = CDate(0, CDate::EPOCH_1950);  //m_lDays = 134122
  x = CDate(0, CDate::EPOCH_CTIME); //m_lDays = 141427
  x = CDate(0, CDate::EPOCH_2000);  //m_lDays = 152384
  


  //CTime Construction
  CTime z(1970, 1, 2, 0, 0, 0);
  x = CDate(z);  //m_lDays = 141428
  CString& s = x.Format();
      
  //COleDateTime Construction
#if defined(_WIN32)
  COleDateTime dt(1992, CDate::OCTOBER, 10, 0, 0, 0);
  x = CDate(dt);  //m_lDays = 149745
  s = x.Format();
  dt = COleDateTime(1970, 1, 2, 0, 0, 0);
  x = CDate(dt);  //m_lDays = 141428
  s = x.Format();
#endif  


  //Static Constructors
  x = CDate::CurrentDate();
  s = x.Format();
  //_tprintf should be replaced by w_tprintf under _UNICODE
  _tprintf(_T("The current date is %s\n"), s);
  x = CDate::FirstCurrentMonth();
  s = x.Format();
  _tprintf(_T("The first of the current month is %s\n"), s);
  x = CDate::FirstCurrentYear();
  s = x.Format();
  _tprintf(_T("The First of the current year is %s\n"), s);
  x = CDate::LastCurrentYear();
  s = x.Format();
  _tprintf(_T("The last of the current year is %s\n"), s);
  x = CDate::JDEpoch();
  s = x.Format();
  _tprintf(_T("The Julian Day Epoch is %s\n"), s);
  x = CDate::MJDEpoch();
  s = x.Format();
  _tprintf(_T("The Modified Julian Day Epoch is %s\n"), s);
  x = CDate::Epoch1900();
  s = x.Format();
  _tprintf(_T("The 1900 Epoch is %s\n"), s);
  x = CDate::Epoch1950();
  s = x.Format();
  _tprintf(_T("The 1950 Epoch is %s\n"), s);
  x = CDate::EpochCTime();
  s = x.Format();
  _tprintf(_T("The CTime Epoch is %s\n"), s);
  x = CDate::Epoch2000();
  s = x.Format();
  _tprintf(_T("The 2000 Epoch is %s\n"), s);
  x = CDate::GregorianEpoch();
  s = x.Format();
  _tprintf(_T("The Gregorian Epoch is %s\n"), s);


  //Try the static operations

  ASSERT(CDate::IsLeap(2000));
  ASSERT(!CDate::IsLeap(1900));
  ASSERT(!CDate::IsLeap(1902));
  ASSERT(CDate::IsLeap(1400));
  ASSERT(CDate::IsLeap(1300));
  ASSERT(!CDate::IsLeap(1302));
  ASSERT(CDate::DaysInYear(2000) == 366);
  ASSERT(CDate::DaysInYear(1998) == 365);
  ASSERT(CDate::DaysInMonth(CDate::JANUARY, TRUE) == 31);
  ASSERT(CDate::DaysInMonth(CDate::FEBRUARY, TRUE) == 29);
  ASSERT(CDate::DaysInMonth(CDate::FEBRUARY, FALSE) == 28);
  ASSERT(CDate::DaysInMonth(CDate::JUNE, TRUE) == 30);
  ASSERT(CDate::DaysSinceJan0(CDate::JANUARY, 1, TRUE) == 1);
  ASSERT(CDate::DaysSinceJan0(CDate::JANUARY, 1, FALSE) == 1);
  ASSERT(CDate::DaysSinceJan0(CDate::DECEMBER, 31, TRUE) == 366);
  ASSERT(CDate::DaysSinceJan0(CDate::DECEMBER, 31, FALSE) == 365);
  ASSERT(CDate::DaysSinceJan0(CDate::JULY, 13, TRUE) == 195);
  ASSERT(CDate::DaysSinceJan0(CDate::JULY, 13, FALSE) == 194);
  ASSERT(CDate::DaysSinceJan1(CDate::DECEMBER, 31, TRUE) == 365);
  ASSERT(CDate::DaysSinceJan1(CDate::DECEMBER, 31, FALSE) == 364);
  ASSERT(CDate::DaysSinceJan1(CDate::JULY, 13, TRUE) == 194);
  ASSERT(CDate::DaysSinceJan1(CDate::JULY, 13, FALSE) == 193);
  ASSERT(CDate::DaysSinceJan1(CDate::JANUARY, 1, TRUE) == 0);
  ASSERT(CDate::DaysSinceJan1(CDate::JANUARY, 1, FALSE) == 0);
  
  WORD m = CDate::CurrentMonth();
  _tprintf(_T("The current month is %d\n"), m);

  WORD d = CDate::CurrentDay();
  _tprintf(_T("The current day is %d\n"), d);

  long y = CDate::CurrentYear();
  _tprintf(_T("The current year is %ld\n"), y);

  WORD dow = CDate::CurrentDayOfWeek();
  _tprintf(_T("The current day of week is %d\n"), dow);


  //is it possible to have only 3 of a weekday in a month
  //Construction using the WeekOfMonth parameter
  x = CDate(1995, 9, 3, CDate::FRIDAY);
  ASSERT(x == CDate(1995, 9, 15));
  x = CDate(1995, 9, 1, CDate::SATURDAY);
  ASSERT(x == CDate(1995, 9, 2));
  x = CDate(1995, 9, 1, CDate::TUESDAY);
  ASSERT(x == CDate(1995, 9, 5));
  x = CDate(1995, 9, 5, CDate::SUNDAY);
  ASSERT(x == CDate(1995, 9, 24));
  x = CDate(1995, 9, 5, CDate::FRIDAY);
  ASSERT(x == CDate(1995, 9, 29));




  //Testing static holiday constructors

  //some of these will need at least 2 day tests

  x = CDate::NewYearsDay();
  s = x.Format();
  _tprintf(_T("New Years Day occurs on %s this year\n"), s);

  x = CDate::ValentinesDay();
  s = x.Format();
  _tprintf(_T("Valentines Day occurs on %s this year\n"), s);

  x = CDate::StPatricksDay();
  s = x.Format();
  _tprintf(_T("St Patricks Day occurs on %s this year\n"), s);

  x = CDate::AshWednesday();
  s = x.Format();
  _tprintf(_T("Ash Wednesday occurs on %s this year\n"), s);

  x = CDate::GoodFriday();
  s = x.Format();
  _tprintf(_T("Good Friday occurs on %s this year\n"), s);

  x = CDate::EasterSunday();
  s = x.Format();
  _tprintf(_T("Easter Sunday occurs on %s this year\n"), s);

  x = CDate::CanadaDay();
  s = x.Format();
  _tprintf(_T("Canada Day occurs on %s this year\n"), s);

  x = CDate::IndependenceDay();
  s = x.Format();
  _tprintf(_T("American Independence Day occurs on %s this year\n"), s);

  x = CDate::BastilleDay();
  s = x.Format();
  _tprintf(_T("Bastille Day occurs on %s this year\n"), s);

  x = CDate::ChristmasDay();
  s = x.Format();
  _tprintf(_T("Christmas Day occurs on %s this year\n"), s);

  
  //test the range of the class

  /*
  CDate::SetEndJulianCalendar(1752, 8, 10);
  CDate::SetBeginGregCalendar(1752, 8, 20);
  */
  

  
  long StartYear = 1700;
  long EndYear = 5000;

  /*  //Uncomment if you want to perform a full range check on CDate's construction routines
  _tprintf(_T("\n\nNow going to construct a CDate for all dates\n"));
  _tprintf(_T("between the years %ld and %ld\n"), StartYear, EndYear);
  _tprintf(_T("This may take a while\n"));
  _tprintf(_T("<Hit Enter to continue>\n"));
  chr = getchar();
  DWORD StartTime = GetTickCount();

  for (long Year = StartYear; Year < EndYear; Year++)
  {
    if (Year % 10 == 0)
       _tprintf(_T("Testing Year %ld\n"), Year);
    for (WORD Month = CDate::JANUARY; Month <= CDate::DECEMBER; Month++)
    {
      for (WORD Day = 1; Day <= CDate::DaysInMonth(Month, CDate::IsLeap(Year)); Day++)
      {
        x = CDate(Year, Month, Day);
        if (x.IsValid())
        {
          DateS ds = x.GetDate();
          if ((ds.lYear != Year) || (ds.wMonth != Month) || (ds.wDay != Day))
          {
            s = x.Format();
            _tprintf(_T("Error occured testing %s\n"), s);
          }
        }
      }
    }
  }

  DWORD EndTime = GetTickCount();
  DWORD SecondsTaken = (EndTime - StartTime)/1000;
  _tprintf(_T("The time taken for the validity test was %ld seconds\n"), SecondsTaken);
  _tprintf(_T("Or about %ld seconds for 1000 years\n"), (SecondsTaken*1000)/(EndYear - StartYear));
  _tprintf(_T("<Hit Enter to continue>\n"));
  chr = getchar();
  */



  //change the time when the gregorian Calendar comes into action

  //for the moment , the values will be changed to match some known values
  /*
  x = CDate(50000, 1, 30);
  s = x.Format();
  _tprintf(_T("%s (NS) Gregorian Day Number is ", s);
  _tprintf(_T("%ld\n"), x.JD());
  CDate::SetEndJulianCalendar(x.GetYear()+1, 8, 10);
  CDate::SetBeginGregCalendar(x.GetYear()+1, 8, 20);
  x = CDate(50000, 1, 30);
  s = x.Format();
  _tprintf(_T("%s (OS) Gregorian Day Number is ", s);
  _tprintf(_T("%ld\n"), x.JD());
  */


  //try out the accessors for the end of Julian and
  //begin of Gregorian dates
  ds = CDate::GetEndJulianCalendar();
  CDate EndJulian(ds.lYear, ds.wMonth, ds.wDay);
  s = EndJulian.Format();
  _tprintf(_T("The End of the Julian calendar occurs on %s\n"), s);
  ds = CDate::GetBeginGregCalendar();
  CDate BeginGreg(ds.lYear, ds.wMonth, ds.wDay);
  s = BeginGreg.Format();
  _tprintf(_T("The begining of the Gregorian calendar occurs on %s\n"), s);
  
    
  // Try out the other operators
  long l = 0;
  x = CDate::CurrentDate();
  l = x.Since1900Epoch();
  _tprintf(_T("Today is %ld days since the 1900 epoch\n"), l);
  l = x.Since1950Epoch();
  _tprintf(_T("Today is %ld days since the 1950 epoch\n"), l);
  l = x.SinceCTimeEpoch();
  _tprintf(_T("Today is %ld days since the CTime epoch\n"), l);
  l = x.Since2000Epoch();
  _tprintf(_T("Today is %ld days since the 2000 epoch\n"), l);
  l = x.GDN();
  _tprintf(_T("Today is %ld days since the Gregorian epoch\n"), l);
  l = x.JD();
  _tprintf(_T("Today is %ld days since the Julian Day epoch\n"), l);
  if (x.IsLeap())
    _tprintf(_T("This year is a leap year\n"));
  else
    _tprintf(_T("This year is not a leap year\n"));
  WORD diy = x.DaysInYear();
  _tprintf(_T("This year contains %d days \n"), diy);
  WORD dim = x.DaysInMonth();
  _tprintf(_T("This month contains %d days \n"), dim);
  x.AddYear(100);
  s = x.Format();
  _tprintf(_T("100 years from today is %s\n"), s);
  x.AddYear(-100);
  s = x.Format();
  _tprintf(_T("100 years from today - 100 years is %s\n"), s);
  x.AddMonth(100);
  s = x.Format();
  _tprintf(_T("100 months from today is %s\n"), s);
  x.AddMonth(-100);
  s = x.Format();
  _tprintf(_T("100 months from today - 100 months is %s\n"), s);
  x.AddWeek(100);
  s = x.Format();
  _tprintf(_T("100 weeks from today is %s\n"), s);
  x.AddWeek(-100);
  s = x.Format();
  _tprintf(_T("100 weeks from today - 100 weeks is %s\n"), s);
  dow = x.GetDayOfWeek();
  _tprintf(_T("Todays day of week is %d\n"), dow);
  s = x.GetFullStringDayOfWeek();
  _tprintf(_T("Todays full string day of week is %s\n"), s);
  s = x.GetAbrStringDayOfWeek();
  _tprintf(_T("Todays Abreviated string day of week is %s\n"), s);
  s = x.GetFullStringMonth();
  _tprintf(_T("Todays full string Month is %s\n"), s);
  s = x.GetAbrStringMonth();
  _tprintf(_T("Todays Abreviated string Month is %s\n"), s);
  _tprintf(_T("Today is %d days since the 1st of this year\n"), x.DaysSinceJan1());
  _tprintf(_T("Today is %d days since the 0th of this year\n"), x.DaysSinceJan0());
  
  if (x.InGregorianCalendar())
    _tprintf(_T("Today is in the Gregorian Calendar\n"));
  else
    _tprintf(_T("Today is in the Julian Calendar\n"));


  //Creation of other CDate's from this instance
  x = CDate(1995, 2, 3);
  s = x.Format();
  _tprintf(_T("The CDate used to test CDate creation from this instance is %s\n"), s);
  CDate c = x.FirstThisMonth();
  s = c.Format();
  _tprintf(_T("FirstThisMonth returns %s\n"), s);
  c = x.LastThisMonth();
  s = c.Format();
  _tprintf(_T("LastThisMonth returns %s\n"), s);
  c = x.FirstThisYear();
  s = c.Format();
  _tprintf(_T("FirstThisYear returns %s\n"), s);
  c = x.LastThisYear();
  s = c.Format();
  _tprintf(_T("FirstThisMonth returns %s\n"), s);


  //assigment operator has been tested before
  x = CDate::CurrentDate();
  c = x + 100;
  s = c.Format();
  _tprintf(_T("100 days from today is %s\n"), s);
  c = c - 100;
  s = c.Format();
  _tprintf(_T("100 days from today  - 100 days is %s\n"), s);
  long diff = CDate(2000, 1, 1) - CDate::CurrentDate();
  _tprintf(_T("the timespan between Epoch 2000 and today is %ld\n"), diff);
  c += 1000;
  s = c.Format();
  _tprintf(_T("today incremented by 1000 days is %s\n"), s);
  c -= 1000;
  s = c.Format();
  _tprintf(_T("today incremented by 1000 days decremented by 1000 is %s\n"), s);
  ++c;
  s = c.Format();
  _tprintf(_T("Tomorrow is %s\n"), s);
  --c;
  --c;
  s = c.Format();
  _tprintf(_T("Yesterday was %s\n"), s);


  //try out the Dump operator
#ifdef _DEBUG
  afxDump << c;
#endif

  c = CDate::CurrentDate();
  
  //Full test of the Format function
  _tprintf(_T("A full test of Format for Today gives\n"));
  s = c.Format("%a");
  _tprintf(_T("Abbreviated weekday name : %s\n"), s);
  s = c.Format("%A");
  _tprintf(_T("Full weekday name : %s\n"), s);
  s = c.Format("%b");
  _tprintf(_T("Abbreviated month name : %s\n"), s);
  s = c.Format("%c");
  _tprintf(_T("Year displayed using CE / BCE convention : %s\n"), s);
  s = c.Format("%B");
  _tprintf(_T("Full month name : %s\n"), s);
  s = c.Format("%d");
  _tprintf(_T("Day of month as decimal number (01 - 31) : %s\n"), s);
  s = c.Format("%j");
  _tprintf(_T("Day of year as decimal number (001 - 366) : %s\n"), s);
  s = c.Format("%m");
  _tprintf(_T("Month as decimal number (01 - 12) : %s\n"), s);
  s = c.Format("%U");
  _tprintf(_T("Week of year as decimal number : %s\n"), s);
  s = c.Format("%w");
  _tprintf(_T("Weekday as decimal number (1 - 7), Sunday is 1 : %s\n"), s);
  s = c.Format("%x");
  _tprintf(_T("Date representation for current locale : %s\n"), s);
  s = c.Format("%y");
  _tprintf(_T("Year without century, as decimal number (00 - 99) : %s\n"), s);
  s = c.Format("%Y");
  _tprintf(_T("Year with century, as decimal number : %s\n"), s);
  s = c.Format("%#x");
  _tprintf(_T("Long date representation, appropriate to current locale : %s\n"), s);
  s = c.Format("%#d");
  _tprintf(_T("Day of month without leading zeros : %s\n"), s);
  s = c.Format("%#j");
  _tprintf(_T("Day of year without leading zeros : %s\n"), s);
  s = c.Format("%#m");
  _tprintf(_T("Month without leading zeroes : %s\n"), s);
  s = c.Format("%#U");
  _tprintf(_T("Week of year without leading zeroes : %s\n"), s);
  s = c.Format("%#y");
  _tprintf(_T("Year without century without leading zeroes : %s\n"), s);
  


  /*
  virtual void Serialize(CArchive& ar);
  friend ostream& operator<<(ostream& os, const CDate& Date);
  friend CArchive& operator<<(CArchive& ar, CDate& Date);
  friend CArchive& operator>>(CArchive& ar, CDate& Date);
  */



  // Try out the week of year function
  x = CDate(1997, 1, 1);
  s = x.Format();
  _tprintf(_T("The first of January for testing the Week Of Year function is %s\n"), s);
  _tprintf(_T("Setting the begining of the week to THURSDAY\n"));
  CDate v = CDate(1997, CDate::JANUARY, 1, CDate::THURSDAY);
  s = v.Format();
  _tprintf(_T("The 1st Thursday of 1997 is %s\n"), s);
  CDate::SetBeginingDayOfWeek(CDate::THURSDAY);
  for (WORD i=1; i<32; i++)
  {
    CDate p(1997, 1, i);
    WORD woy = p.GetWeekOfYear();
    s = p.Format();
    _tprintf(_T("The week of the year for %s is"), s);
    _tprintf(_T(" %d\n"), woy);
  }


  // Try out the week of year function
  x = CDate(1997, 1, 1);
  s = x.Format();
  _tprintf(_T("The first of january for testing the Week Of year function is %s\n"), s);
  v = CDate(1997, CDate::JANUARY, 1, CDate::MONDAY);
  s = v.Format();
  _tprintf(_T("The 1st Monday of 1997 is %s\n"), s);
  _tprintf(_T("Setting the begining of the week to MONDAY\n"));
  CDate::SetBeginingDayOfWeek(CDate::MONDAY);
  for (i=1; i<32; i++)
  {
    CDate p(x.GetYear(), x.GetMonth(), i);
    WORD woy = p.GetWeekOfYear();
    s = p.Format();
    _tprintf(_T("The week of the year for %s is"), s);
    _tprintf(_T(" %d\n"), woy);
  }


  // Try out the week of month function
  x = CDate::CurrentDate();
  x = x.FirstThisMonth();
  s = x.Format();
  _tprintf(_T("The first of this month for testing the Week Of month function is %s\n"), s);
  v = CDate(x.GetYear(), x.GetMonth(), 1, CDate::THURSDAY);
  s = v.Format();
  _tprintf(_T("The 1st Thursday of the month is %s\n"), s);
  _tprintf(_T("Setting the begining of the week to THURSDAY\n"));
  CDate::SetBeginingDayOfWeek(CDate::THURSDAY);
  for (i=1; i<=x.DaysInMonth(); i++)
  {
    CDate p(x.GetYear(), x.GetMonth(), i);
    WORD wom = p.GetWeekOfMonth();
    s = p.Format();
    _tprintf(_T("The week of the month for %s is"), s);
    _tprintf(_T(" %d\n"), wom);
  }



  // Try out the week of Month function with a different begining of week
  x = CDate::CurrentDate();
  x = x.FirstThisMonth();
  s = x.Format();
  _tprintf(_T("The first of this month for testing the Week Of month function is %s\n"), s);
  v = CDate(x.GetYear(), x.GetMonth(), 1, CDate::MONDAY);
  s = v.Format();
  _tprintf(_T("The 1st Monday of the month is %s\n"), s);
  _tprintf(_T("Setting the begining of the week to MONDAY\n"));
  CDate::SetBeginingDayOfWeek(CDate::MONDAY);
  for (i=1; i<=x.DaysInMonth(); i++)
  {
    CDate p(x.GetYear(), x.GetMonth(), i);
    WORD wom = p.GetWeekOfMonth();
    s = p.Format();
    _tprintf(_T("The week of the month for %s is"), s);
    _tprintf(_T(" %d\n"), wom);
  }



  //try out the collate function
  x = CDate::CurrentDate();
  long coll = x.Collate();
  _tprintf(_T("The collate function for today returns %ld\n"), coll);




  //Test of the CLTimeSpan class

  
  //first the constructors
  CLTimeSpan ts;
  ASSERT(!ts.IsValid());

  ts = CLTimeSpan(3, 4, 5, 6, 233);
  long dd = ts.GetTotalDays();
  WORD hh = ts.GetHours();
  WORD mm = ts.GetMinutes();
  WORD ss = ts.GetSeconds();
  WORD ms = ts.GetMilliSeconds();
  s = ts.Format();

  ts = CLTimeSpan(3, 27, 59, 69, 1233);
  s = ts.Format();

  CLTimeSpan ts2(ts);
  s = ts2.Format();

  CTimeSpan OneDay(1, 0, 0, 0);
  ts = CLTimeSpan(OneDay);
  s = ts.Format();

  ts = CLTimeSpan(86400.5);
  s = ts.Format();

  ts = CLTimeSpan(-23.5);
  dd = ts.GetTotalDays();
  hh = ts.GetHours();
  mm = ts.GetMinutes();
  ss = ts.GetSeconds();
  ms = ts.GetMilliSeconds();
  s = ts.Format();
  double secs = ts.SecondsAsDouble();

  ts = CLTimeSpan(-86401.5987);
  dd = ts.GetTotalDays();
  hh = ts.GetHours();
  mm = ts.GetMinutes();
  ss = ts.GetSeconds();
  ms = ts.GetMilliSeconds();
  s = ts.Format();
  secs = ts.SecondsAsDouble();

  ts = CLTimeSpan(-86401.5981);
  dd = ts.GetTotalDays();
  hh = ts.GetHours();
  mm = ts.GetMinutes();
  ss = ts.GetSeconds();
  ms = ts.GetMilliSeconds();
  s = ts.Format();
  secs = ts.SecondsAsDouble();
  
  ts = CLTimeSpan(86399.999);
  ms = ts.GetMilliSeconds();
  s = ts.Format();
  secs = ts.SecondsAsDouble();

  ts = CLTimeSpan(86399.99999);    //should round up to nearest second
  ms = ts.GetMilliSeconds();
  s = ts.Format();
  secs = ts.SecondsAsDouble();

  ts = CLTimeSpan(263967.987654);  //should round up to nearest millisecond
  s = ts.Format();
  secs = ts.SecondsAsDouble();

  ts = CLTimeSpan(263967.987354);  //should round down to nearest millisecond
  s = ts.Format();
  secs = ts.SecondsAsDouble();

  //COleDateTimeSpan Construction
#if defined(_WIN32)
  COleDateTimeSpan olets(19, 12, 10, 3);
  ts = CLTimeSpan(olets);  
  s = ts.Format();
#endif  



  //Set operators have been tested via the constructors

  //static Constructors

  ts = CLTimeSpan::OneCivilYear();
  s = ts.Format();
  _tprintf(_T("One Civil year as a time span is %s\n"), s);
  ts = CLTimeSpan::OneDay();
  s = ts.Format();
  _tprintf(_T("One Day as a time span is %s\n"), s);
  ts = CLTimeSpan::OneHour();
  s = ts.Format();
  _tprintf(_T("One Hour as a time span is %s\n"), s);
  ts = CLTimeSpan::OneMinute();
  s = ts.Format();
  _tprintf(_T("One Minute as a time span is %s\n"), s);
  ts = CLTimeSpan::OneSecond();
  s = ts.Format();
  _tprintf(_T("One Second as a time span is %s\n"), s);
  ts = CLTimeSpan::OneMilliSecond();
  s = ts.Format();
  _tprintf(_T("One MilliSecond as a time span is %s\n"), s);

  //days, Hours, Minutes Seconds & MilliSecond accessors
  //already tested via Format
  

  //Overloaded Arithmetic Operators
  CLTimeSpan ts1 = CLTimeSpan::OneCivilYear();
  ts2 = CLTimeSpan::OneDay();
  //operator= already tested           //not fully tested yet
  CLTimeSpan ts3 = ts1 + ts2;
  _tprintf(_T("One year + One day is %s\n"), ts3.Format());
  ts3 = ts1 - ts2;
  _tprintf(_T("One year - One day is %s\n"), ts3.Format());
  ts3 = ts2 - ts1;

  _tprintf(_T("One day - One year is %s\n"), ts3.Format());
  ts1 = CLTimeSpan::OneCivilYear();
  ts2 = CLTimeSpan::OneDay();
  ts1 += ts2;
  _tprintf(_T("One year incremented by one day is %s\n"), ts1.Format());
  ts1 -= ts2;
  _tprintf(_T("One year+one day decremented by one day is %s\n"), ts1.Format());
  ts1 = CLTimeSpan::OneCivilYear();
  ts2 -= ts1;
  _tprintf(_T("One day decremented by one year is %s\n"), ts2.Format());
  ts1 = CLTimeSpan::OneCivilYear();
  ts1.Negate();
  ts2 = CLTimeSpan::OneDay();
  ts3 = ts1 - ts2;
  _tprintf(_T("-One year - one day is %s\n"), ts3.Format());
  ts3 = ts1 + ts2;
  _tprintf(_T("-One year + one day is %s\n"), ts3.Format());
  ts1 = CLTimeSpan::OneCivilYear();
  ts2 = CLTimeSpan::OneDay();
  ts2.Negate();
  ts3 = ts1 - ts2;
  _tprintf(_T("One year - (-one day) is %s\n"), ts3.Format());
  ts3 = ts1 + ts2;
  _tprintf(_T("One year + (-one day) is %s\n"), ts3.Format());
  ts1 = CLTimeSpan::OneCivilYear();
  ts1.Negate();
  ts2 = CLTimeSpan::OneDay();
  ts1 += ts2;
  _tprintf(_T("-One year incremented by one day is %s\n"), ts1.Format());
  ts1 -= ts2;
  _tprintf(_T("-One year + 1 day decremented by one day is %s\n"), ts1.Format());
  ts2 = CLTimeSpan::OneCivilYear();
  ts2.Negate();
  ts1 -= ts2;
  _tprintf(_T("-One year decremented by -one year is %s\n"), ts1.Format());
  ts1 += ts2;
  _tprintf(_T("-One year - -one year incremented by -one year is %s\n"), ts1.Format());
  ts1 = CLTimeSpan::OneCivilYear();
  ts2 = CLTimeSpan::OneDay();
  ts2.Negate();
  ts3 = ts1 - ts2;
  _tprintf(_T("One year - -one day is %s\n"), ts3.Format());
  ts3 = ts1 + ts2;
  _tprintf(_T("One year + -one day is %s\n"), ts3.Format());
  ts3 = ts2 - ts1;
  _tprintf(_T("-One day - one year is %s\n"), ts3.Format());
  ts3 = ts2 + ts1;
  _tprintf(_T("-One day + one year is %s\n"), ts3.Format());
  ts1 = CLTimeSpan::OneCivilYear();
  ts2 = CLTimeSpan::OneDay();
  ts3 = ts1 * 100;
  
  dd = ts3.GetTotalDays();
  hh = ts3.GetHours();
  mm = ts3.GetMinutes();
  ss = ts3.GetSeconds();
  ms = ts3.GetMilliSeconds();
  s = ts3.Format();
  
  _tprintf(_T("One year * 100 is %s\n"), ts3.Format());
  ts3 = 100 * ts1;
  _tprintf(_T("100 * One year is %s\n"), ts3.Format());
  ts3 = ts1 / 3;
  _tprintf(_T("One year / 3 is %s\n"), ts3.Format());
  ts1 *= 100;
  _tprintf(_T("One year *= 100 is %s\n"), ts1.Format());
  ts1 = CLTimeSpan::OneCivilYear();
  ts1 /= 100;
  _tprintf(_T("One year /= 100 is %s\n"), ts1.Format());
  ts1 = CLTimeSpan(365, 6, 10, 34, 33);
  ts3 = ts1 * 100;
  _tprintf(_T("%s * 100 is"), ts1.Format());
  _tprintf(_T(" %s\n"), ts3.Format());
  ts3 = ts1 / 100;
  _tprintf(_T("%s / 100 is"), ts1.Format());
  _tprintf(_T(" %s\n"), ts3.Format());



  //overloaded equality operators
  ts1 = CLTimeSpan::OneCivilYear();
  ts2 = CLTimeSpan::OneDay();
  ASSERT(ts1 >= ts2);
  ASSERT(ts1 > ts2);
  ASSERT(ts2 < ts1);
  ASSERT(ts2 <= ts1);
  ASSERT(ts2 != ts1);
  ASSERT(!(ts2 == ts1));
  
  //AssertValid() has already been tested
#ifdef _DEBUG
  afxDump << ts2;
#endif
  
  //Format has already been tested




  //Try out of the CLTimeOfDay class

  //first the constructors
  CLTimeOfDay tod;
  ASSERT(!tod.IsValid());

  //tod = CLTimeOfDay(23, 59, 61, 0); //should assert
  //tod = CLTimeOfDay(24, 59, 61, 0); //should assert
  //tod = CLTimeOfDay(23, 59, 59, 1000); //should assert
                     
  SYSTEMTIME stnow;                   
#ifdef _WIN32      
  GetLocalTime(&stnow);
  tod = CLTimeOfDay(stnow);
  s = tod.Format();
#endif  

  CLTimeOfDay tod2(tod);
  s = tod.Format();

  //tod2 = CLTimeOfDay(-23.5); //should assert
  s = tod2.Format();

  //tod2 = CLTimeOfDay(-86401.5); //should assert
  s = tod2.Format();

  tod2 = CLTimeOfDay(86399.999);
  s = tod2.Format();

  tod2 = CLTimeOfDay(86199.9766);
  s = tod2.Format();

  
  //Set functions tested via the constructors

 
  //The static constructors

  tod = CLTimeOfDay::CurrentTimeOfDay(LOCAL);
  s = tod.Format();
  _tprintf(_T("The local time of day is %s\n"), s);

  tod = CLTimeOfDay::CurrentTimeOfDay(UTC);
  s = tod.Format();
  _tprintf(_T("The UTC time of day is %s\n"), s);

  //tod = CLTimeOfDay::CurrentTimeOfDay(ET); //should assert
  
  tod = CLTimeOfDay::Midnight();
  s = tod.Format();
  _tprintf(_T("Midnight as a time of day is %s\n"), s);

  tod = CLTimeOfDay::Midday();
  s = tod.Format();
  _tprintf(_T("Midday as a time of day is %s\n"), s);

  

  //try out the operations
  tod = CLTimeOfDay::CurrentTimeOfDay(UTC);
  WORD wVal = tod.GetHour();
  wVal = tod.GetMinute();
  long lVal = tod.GetTotalSeconds();
  wVal = tod.GetSecond();
  wVal = tod.GetMilliSecond();
  ASSERT(tod.IsValid());
  ULARGE_INTEGER col = tod.Collate();
  _tprintf(_T("The collate function for the Current UTC time of day is\n"));
  _tprintf(_T("HightPart:%ld LowPart:%ld\n"), col.HighPart, col.LowPart);
  stnow = tod.GetSYSTEMTIME();

  //Arithmetic operators
  
  CLTimeOfDay tod3(12, 1, 2, 3);
  CLTimeSpan  ts4(1, 25, 59, 45, 28);
  //operator= already tested
  CLTimeOfDay tod4 = tod3 + ts4;
  s = tod4.Format();
  CString& s2 = tod3.Format();
  CString& s3 = ts4.Format();
  _tprintf(_T("%s"), s2);
  _tprintf(_T(" + %s = "), s3);
  _tprintf(_T("%s\n"), s);

  tod2 = tod3 - ts4;
  s2 = tod3.Format();
  _tprintf(_T("%s"), s2);
  s3 = ts4.Format();
  _tprintf(_T(" - %s = "), s3);
  s = tod2.Format();
  _tprintf(_T("%s\n"), s);
 
  s2 = tod3.Format();
  _tprintf(_T("%s"), s2);
  tod3 += ts4;
  s3 = ts4.Format();
  _tprintf(_T(" += %s = "), s3);
  s = tod3.Format();
  _tprintf(_T("%s\n"), s);
  
  s2 = tod3.Format();
  _tprintf(_T("%s"), s2);
  tod3 -= ts4;
  s3 = ts4.Format();
  _tprintf(_T(" -= %s = "), s3);
  s = tod3.Format();
  _tprintf(_T("%s\n"), s);

  //try out negative timespans
  ts4.Negate();
  tod4 = tod3 + ts4;
  s2 = tod3.Format();
  _tprintf(_T("%s"), s2);
  s3 = ts4.Format();
  _tprintf(_T(" + %s = "), s3);
  s = tod4.Format();
  _tprintf(_T("%s\n"), s);

  tod2 = tod3 - ts4;
  s2 = tod3.Format();
  _tprintf(_T("%s"), s2);
  s3 = ts4.Format();
  _tprintf(_T(" - %s = "), s3);
  s = tod2.Format();
  _tprintf(_T("%s\n"), s);

  s2 = tod3.Format();
  _tprintf(_T("%s"), s2);
  tod3 += ts4;
  s3 = ts4.Format();
  _tprintf(_T(" += %s = "), s3);
  s = tod3.Format();
  _tprintf(_T("%s\n"), s);
  
  s2 = tod3.Format();
  _tprintf(_T("%s"), s2);
  tod3 -= ts4;
  s3 = ts4.Format();
  _tprintf(_T(" -= %s = "), s3);
  s = tod3.Format();
  _tprintf(_T("%s\n"), s);
  


  //equality operators

  CLTimeOfDay tod1(12, 1, 2, 3);
  tod2 = CLTimeOfDay(13, 0, 2, 2);

  ASSERT(tod1 <= tod2);
  ASSERT(tod1 < tod2);
  ASSERT(tod2 > tod1);
  ASSERT(tod2 >= tod1);
  ASSERT(tod2 != tod1);
  ASSERT(!(tod2 == tod1));






  //Try out the CLDate class

  //first the constructors
  CLDate ldate;
  ASSERT(!ldate.IsValid());
  ldate = CLDate(1995, 10, 3, 12, 11, 10, 330, LOCAL);
  s = ldate.Format();
  //SYSTEMTIME st; 
#ifdef _WIN32  
  ::GetLocalTime(&st);
  ldate = CLDate(st, LOCAL);
  s = ldate.Format();
#endif  
  ldate = CLDate(1995, 3, 5, CDate::SUNDAY, 0, 0, 0, 0, UTC); 
  s = ldate.Format();
  ldate = CLDate(1000, CDate::EPOCH_JD, 0, 0, 0, 0, UTC);
  s = ldate.Format();
  //Copy constructor already tested
  CTime ct = CTime::GetCurrentTime();
  ldate = CLDate(ct);
  s = ldate.Format();
  ldate = CLDate(CDate::CurrentDate(), CLTimeOfDay::CurrentTimeOfDay(LOCAL), LOCAL);
  s = ldate.Format();
      
#if defined(_WIN32)
  COleDateTime ldt(1992, CDate::OCTOBER, 10, 3, 4, 5);
  ldate = CLDate(ldt, UTC);
  s = ldate.Format();
  ldt = COleDateTime(1970, 2, 1, 5, 6, 7);
  ldate = CLDate(ldt, LOCAL);
  s = ldate.Format();
#endif  
  
  //Set operators tested via the constructors above

  //Static Constructors
  ldate = CLDate::CurrentTime(UTC);
  s = ldate.Format();   

  //need to test SetDefaultFormat()

  //check out the deltaT function
  CLTimeSpan DT = CLDate::DeltaT(ldate);
  s = DT.Format();
  
  DT = CLDate::DeltaT(CLDate(1650, 1, 1, 0, 0, 0, 0, UTC));
  s = DT.Format();
  _tprintf(_T("The DeltaT timespan for the Year 1650 is %s\n"), s);  //should be +48 Seconds

  DT = CLDate::DeltaT(CLDate(1750, 1, 1, 0, 0, 0, 0, UTC));
  s = DT.Format();
  _tprintf(_T("The DeltaT timespan for the Year 1750 is %s\n"), s);  //should be +13 Seconds

  DT = CLDate::DeltaT(CLDate(1850, 1, 1, 0, 0, 0, 0, UTC));
  s = DT.Format();
  _tprintf(_T("The DeltaT timespan for the Year 1850 is %s\n"), s);  //should be +7.1 Seconds

  DT = CLDate::DeltaT(CLDate(1910, 1, 1, 0, 0, 0, 0, UTC));
  s = DT.Format();
  _tprintf(_T("The DeltaT timespan for the Year 1910 is %s\n"), s);  //should be +10.5 Seconds
  
  DT = CLDate::DeltaT(CLDate(1950, 1, 1, 0, 0, 0, 0, UTC));
  s = DT.Format();
  _tprintf(_T("The DeltaT timespan for the Year 1950 is %s\n"), s);  //should be +29.1 Seconds

  DT = ldate.DeltaT();
  s = DT.Format();
  _tprintf(_T("The current DeltaT timespan is %s\n"), s);            //??? depends on current date
  
  DT = CLDate::DeltaT(CLDate(2000, 1, 1, 0, 0, 0, 0, UTC));
  s = DT.Format();
  _tprintf(_T("The DeltaT timespan for the Year 2000 is %s\n"), s);  //should be around +1 minute



  //check page 72 of the Book "Astronomical Algorithms" for 
  //other sample values of DeltaT

  //Need to try out the following functions
  //GetCDate & GetCLTimeOfDay tested through the Format function
  st = ldate.GetSYSTEMTIME();
  
  ldate.AddYear(10);
  s = ldate.Format();
  _tprintf(_T("10 years from now UTC is %s\n"), s);

  ldate = CLDate::CurrentTime(UTC);
  ldate.AddWeek(-10);
  s = ldate.Format();
  _tprintf(_T("10 weeks before today UTC is %s\n"), s);

  ldate = CLDate::CurrentTime(UTC);
  ldate.AddMonth(-14);
  s = ldate.Format();
  _tprintf(_T("14 months before today UTC is %s\n"), s);

  
  ASSERT(ldate.IsValid());     
  ldate = CLDate();
  ASSERT(!ldate.IsValid());


  //Test a daylight savings date

  ldate = CLDate(1995, 7, 9, 8, 7, 6, 0, UTC);
  CString& s1 = ldate.Format();
  _tprintf(_T("%s is "), s1);
  ldate.SetTimeFrame(UTC);
  s = ldate.Format();
  _tprintf(_T("%s\n"), s);

  ldate = CLDate(1995, 7, 9, 8, 7, 6, 0, UTC);
  s1 = ldate.Format();
  _tprintf(_T("%s is "), s1);
  ldate.SetTimeFrame(ET);
  s = ldate.Format();
  _tprintf(_T("%s\n"), s);

  ldate = CLDate(1995, 7, 9, 8, 7, 6, 0, UTC);
  s1 = ldate.Format();
  _tprintf(_T("%s is "), s1);
  ldate.SetTimeFrame(LOCAL);
  s = ldate.Format();
  _tprintf(_T("%s\n"), s);

  ldate = CLDate(1995, 7, 9, 8, 7, 6, 0, ET);
  s1 = ldate.Format();
  _tprintf(_T("%s is "), s1);
  ldate.SetTimeFrame(UTC);
  s = ldate.Format();
  _tprintf(_T("%s\n"), s);

  ldate = CLDate(1995, 7, 9, 8, 7, 6, 0, ET);
  s1 = ldate.Format();
  _tprintf(_T("%s is "), s1);
  ldate.SetTimeFrame(ET);
  s = ldate.Format();
  _tprintf(_T("%s\n"), s);
  
  ldate = CLDate(1995, 7, 9, 8, 7, 6, 0, ET);
  s1 = ldate.Format();
  _tprintf(_T("%s is "), s1);
  ldate.SetTimeFrame(LOCAL);
  s = ldate.Format();
  _tprintf(_T("%s\n"), s);

  ldate = CLDate(1995, 7, 9, 8, 7, 6, 0, LOCAL);
  s1 = ldate.Format();
  _tprintf(_T("%s is "), s1);
  ldate.SetTimeFrame(UTC);
  s = ldate.Format();
  _tprintf(_T("%s\n"), s);
  
  ldate = CLDate(1995, 7, 9, 8, 7, 6, 0, LOCAL);
  s1 = ldate.Format();
  _tprintf(_T("%s is "), s1);
  ldate.SetTimeFrame(ET);
  s = ldate.Format();
  _tprintf(_T("%s\n"), s);
  
  ldate = CLDate(1995, 7, 9, 8, 7, 6, 0, LOCAL);
  s1 = ldate.Format();
  _tprintf(_T("%s is "), s1);
  ldate.SetTimeFrame(LOCAL);
  s = ldate.Format();
  _tprintf(_T("%s\n"), s);


  //test a Standard time

  ldate = CLDate(1995, 12, 9, 8, 7, 6, 0, UTC);
  s1 = ldate.Format();
  _tprintf(_T("%s is "), s1);
  ldate.SetTimeFrame(UTC);
  s = ldate.Format();
  _tprintf(_T("%s\n"), s);

  ldate = CLDate(1995, 12, 9, 8, 7, 6, 0, UTC);
  s1 = ldate.Format();
  _tprintf(_T("%s is "), s1);
  ldate.SetTimeFrame(ET);
  s = ldate.Format();
  _tprintf(_T("%s\n"), s);

  ldate = CLDate(1995, 12, 9, 8, 7, 6, 0, UTC);
  s1 = ldate.Format();
  _tprintf(_T("%s is "), s1);
  ldate.SetTimeFrame(LOCAL);
  s = ldate.Format();
  _tprintf(_T("%s\n"), s);

  ldate = CLDate(1995, 12, 9, 8, 7, 6, 0, ET);
  s1 = ldate.Format();
  _tprintf(_T("%s is "), s1);
  ldate.SetTimeFrame(UTC);
  s = ldate.Format();
  _tprintf(_T("%s\n"), s);

  ldate = CLDate(1995, 12, 9, 8, 7, 6, 0, ET);
  s1 = ldate.Format();
  _tprintf(_T("%s is "), s1);
  ldate.SetTimeFrame(ET);
  s = ldate.Format();
  _tprintf(_T("%s\n"), s);
  
  ldate = CLDate(1995, 12, 9, 8, 7, 6, 0, ET);
  s1 = ldate.Format();
  _tprintf(_T("%s is "), s1);
  ldate.SetTimeFrame(LOCAL);
  s = ldate.Format();
  _tprintf(_T("%s\n"), s);

  ldate = CLDate(1995, 12, 9, 8, 7, 6, 0, LOCAL);
  s1 = ldate.Format();
  _tprintf(_T("%s is "), s1);
  ldate.SetTimeFrame(UTC);
  s = ldate.Format();
  _tprintf(_T("%s\n"), s);
  
  ldate = CLDate(1995, 12, 9, 8, 7, 6, 0, LOCAL);
  s1 = ldate.Format();
  _tprintf(_T("%s is "), s1);
  ldate.SetTimeFrame(ET);
  s = ldate.Format();
  _tprintf(_T("%s\n"), s);
  
  ldate = CLDate(1995, 12, 9, 8, 7, 6, 0, LOCAL);
  s1 = ldate.Format();
  _tprintf(_T("%s is "), s1);
  ldate.SetTimeFrame(LOCAL);
  s = ldate.Format();
  _tprintf(_T("%s\n"), s);



  //Need to test the two conditions where a LOCAL time occurs twice 
  //or not at all


  ldate = CLDate::CurrentTime(UTC);
  s = ldate.Format();
  _tprintf(_T("The current UTC date is %s\n"), s);
  ldate = CLDate::CurrentTime(ET);
  s = ldate.Format();
  _tprintf(_T("The current ET date is %s\n"), s);
  ldate = CLDate::CurrentTime(LOCAL);
  s = ldate.Format();
  _tprintf(_T("The current LOCAL date is %s\n"), s);

  BOOL bInDst = ldate.IsDST();
  if (bInDst)
    _tprintf(_T("Current date is a Daylight Time\n"));
  else
    _tprintf(_T("Current date is a Standard Time\n"));

  //operator= already tried out

  ldate = CLDate::CurrentTime(UTC);
  ts = CTimeSpan(10, 10, 10, 10);
  ldate += ts;
  s1 = ts.Format();
  _tprintf(_T("%s from today UTC is "), s1);
  s = ldate.Format();
  _tprintf(_T("%s\n"), s);


  //Arithmetic operators
  ldate = CLDate::CurrentTime(LOCAL);
  CLDate ldate3 = ldate;
  ldate3.SetTimeFrame(UTC);
  ldate3 += CLTimeSpan(0, 0, 0, 1, 0);
  ts = ldate3 - ldate;



  //try out the equality operators
  ldate = CLDate::CurrentTime(UTC);
  CLDate ldate2(ldate);
  ldate2.SetTimeFrame(LOCAL);
  ASSERT(ldate == ldate2);
  ASSERT(!(ldate != ldate2));
  ldate2 += CLTimeSpan(0, 0, 0, 0, 1);
  ASSERT(ldate2 != ldate);
  ASSERT(ldate2 >= ldate);
  ASSERT(ldate <= ldate2);
  ASSERT(ldate < ldate2);

  //AssertValid() already tested internally

#ifdef _DEBUG
  afxDump << ldate;
#endif
  
  
  //Full test of the Format function
  ldate = CLDate::CurrentTime(LOCAL);
  _tprintf(_T("A full test of CLDate::Format for Now (LOCAL) gives\n"));
  s = ldate.Format("%a");
  _tprintf(_T("Abbreviated weekday name : %s\n"), s);
  s = ldate.Format("%A");
  _tprintf(_T("Full weekday name : %s\n"), s);
  s = ldate.Format("%b");
  _tprintf(_T("Abbreviated month name : %s\n"), s);
  s = ldate.Format("%B");
  _tprintf(_T("Full month name : %s\n"), s);
  s = ldate.Format("%c");
  _tprintf(_T("Year displayed using CE / BCE convention : %s\n"), s);
  s = ldate.Format("%d");
  _tprintf(_T("Day of month as decimal number (01 - 31) : %s\n"), s);
  s = ldate.Format("%j");
  _tprintf(_T("Day of year as decimal number (001 - 366) : %s\n"), s);
  s = ldate.Format("%m");
  _tprintf(_T("Month as decimal number (01 - 12) : %s\n"), s);
  s = ldate.Format("%U");
  _tprintf(_T("Week of year as decimal number : %s\n"), s);
  s = ldate.Format("%w");
  _tprintf(_T("Weekday as decimal number (1 - 7), Sunday is 1 : %s\n"), s);
  s = ldate.Format("%x");
  _tprintf(_T("Date representation for current locale : %s\n"), s);
  s = ldate.Format("%y");
  _tprintf(_T("Year without century, as decimal number (00 - 99) : %s\n"), s);
  s = ldate.Format("%Y");
  _tprintf(_T("Year with century, as decimal number : %s\n"), s);
  s = ldate.Format("%#x");
  _tprintf(_T("Long date representation, appropriate to current locale : %s\n"), s);
  s = ldate.Format("%#d");
  _tprintf(_T("Day of month without leading zeros : %s\n"), s);
  s = ldate.Format("%#j");
  _tprintf(_T("Day of year without leading zeros : %s\n"), s);
  s = ldate.Format("%#m");
  _tprintf(_T("Month without leading zeroes : %s\n"), s);
  s = ldate.Format("%#U");
  _tprintf(_T("Week of year without leading zeroes, with Sunday as first day of week : %s\n"), s);
  s = ldate.Format("%#y");
  _tprintf(_T("Year without century without leading zeroes : %s\n"), s);
  s = ldate.Format("%H");
  _tprintf(_T("Hours in the current day : %s\n"), s);
  s = ldate.Format("%h");
  _tprintf(_T("AM / PM Hours in the current day : %s\n"), s);
  s = ldate.Format("%P");
  _tprintf(_T("AM / PM Indicator for the current day : %s\n"), s);
  s = ldate.Format("%M");
  _tprintf(_T("Minutes in the current day : %s\n"), s);
  s = ldate.Format("%S");
  _tprintf(_T("Seconds in the current day : %s\n"), s);
  s = ldate.Format("%F");
  _tprintf(_T("Milliseconds in the current day : %s\n"), s);
  s = ldate.Format("%#H");
  _tprintf(_T("Hours in the current day without leading zeros: %s\n"), s);
  s = ldate.Format("%#h");
  _tprintf(_T("AM / PM Hours in the current day without leading zeros: %s\n"), s);
  s = ldate.Format("%#M");
  _tprintf(_T("Minutes in the current day without leading zeros : %s\n"), s);
  s = ldate.Format("%#S");
  _tprintf(_T("Seconds in the current day without leading zeros : %s\n"), s);
  ldate = CLDate::CurrentTime(UTC);
  s = ldate.Format();
  _tprintf(_T("The Current UTC long date is %s\n"), s);


  //cross the DST marker
  _tprintf(_T("\n\n"));

  _tprintf(_T("Some of the following code is designed to cause ASSERTIONS\n"));
  _tprintf(_T("You can safely press IGNORE. To see why these assertions occur\n"));
  _tprintf(_T("you should trace into the DTime code\n"));
  _tprintf(_T("<Hit Enter to continue>\n"));
  chr = getchar();


  //you will need to modify these values depending on when your
  //computer is set to cross the DST marker

  ldate = CLDate(1996, 3, 31, 0, 10, 0, 0, LOCAL);
  for (int p=0; p<24; p++)
  {
    CLDate OldDate(ldate);
    s = ldate.Format();
    _tprintf(_T("%s is "), s);
    ldate.SetTimeFrame(UTC);
    s1 = ldate.Format();
    _tprintf(_T("%s\n"), s1);
    ldate = OldDate;
    ldate += CLTimeSpan(0, 0, 10, 0, 0);
  }

  ldate = CLDate(1996, 3, 31, 1, 59, 0, 0, LOCAL);  //does occur
  BOOL bIsDst = ldate.IsDST();

  ldate = CLDate(1996, 3, 31, 2, 00, 0, 0, LOCAL);  //does occur
  bIsDst = ldate.IsDST();

  ldate = CLDate(1996, 3, 31, 2, 01, 0, 0, LOCAL);  //does not occur
  //bIsDst = ldate.IsDST();    //should assert

  ldate = CLDate(1996, 3, 31, 2, 30, 0, 0, LOCAL);  //does not occur
  //bIsDst = ldate.IsDST();    //should assert

  ldate = CLDate(1996, 3, 31, 3, 00, 0, 0, LOCAL);  //does occur
  bIsDst = ldate.IsDST();

  ldate = CLDate(1996, 10, 27, 1, 59, 0, 0, LOCAL);  //does occur
  bIsDst = ldate.IsDST();

  ldate = CLDate(1996, 10, 27, 3, 00, 0, 0, LOCAL);  //occurs twice
  //bIsDst = ldate.IsDST();    //should assert

  ldate = CLDate(1996, 10, 27, 2, 30, 0, 0, LOCAL);  //occurs twice
  //bIsDst = ldate.IsDST();    //should assert

  ldate = CLDate(1996, 10, 27, 2, 59, 0, 0, LOCAL);  //occurs twice
  //bIsDst = ldate.IsDST();    //should assert

  ldate = CLDate(1996, 10, 27, 2, 00, 0, 0, LOCAL);  //occurs twice
  //bIsDst = ldate.IsDST();  //should assert

  ldate = CLDate(1996, 10, 27, 3, 01, 0, 0, LOCAL);  //does occur
  bIsDst = ldate.IsDST();

  ldate = CLDate(1996, 3, 31, 1, 59, 0, 0, UTC);
  bIsDst = ldate.IsDST();
  ldate.SetTimeFrame(LOCAL);
  s = ldate.Format();

  ldate = CLDate(1996, 3, 31, 2, 00, 0, 0, UTC);
  bIsDst = ldate.IsDST();
  ldate.SetTimeFrame(LOCAL);
  s = ldate.Format();

  ldate = CLDate(1996, 3, 31, 2, 01, 0, 0, UTC);
  bIsDst = ldate.IsDST();
  ldate.SetTimeFrame(LOCAL);
  s = ldate.Format();

  ldate = CLDate(1996, 3, 31, 2, 30, 0, 0, UTC);
  bIsDst = ldate.IsDST();
  ldate.SetTimeFrame(LOCAL);
  s = ldate.Format();

  ldate = CLDate(1996, 3, 31, 2, 59, 0, 0, UTC);
  bIsDst = ldate.IsDST();
  ldate.SetTimeFrame(LOCAL);
  s = ldate.Format();
  
  ldate = CLDate(1996, 3, 31, 3, 00, 0, 0, UTC);
  bIsDst = ldate.IsDST();
  ldate.SetTimeFrame(LOCAL);
  s = ldate.Format();

  ldate = CLDate(1996, 10, 27, 1, 59, 0, 0, UTC);
  s = ldate.Format();
  bIsDst = ldate.IsDST();
  ldate.SetTimeFrame(LOCAL);
  s = ldate.Format();

  ldate = CLDate(1996, 10, 27, 2, 00, 0, 0, UTC);
  bIsDst = ldate.IsDST();
  ldate.SetTimeFrame(LOCAL);
  s = ldate.Format();

  ldate = CLDate(1996, 10, 27, 2, 30, 0, 0, UTC);
  bIsDst = ldate.IsDST();
  ldate.SetTimeFrame(LOCAL);
  s = ldate.Format();

  ldate = CLDate(1996, 10, 27, 2, 59, 0, 0, UTC);
  bIsDst = ldate.IsDST();
  ldate.SetTimeFrame(LOCAL);
  s = ldate.Format();

  ldate = CLDate(1996, 10, 27, 3, 00, 0, 0, UTC);
  bIsDst = ldate.IsDST();
  ldate.SetTimeFrame(LOCAL);
  s = ldate.Format();

  ldate = CLDate(1996, 10, 27, 3, 01, 0, 0, UTC);
  bIsDst = ldate.IsDST();
  ldate.SetTimeFrame(LOCAL);
  s = ldate.Format();

#if defined(_WINDOWS) || defined(_WIN32)
  DWORD TimeInterval = GetTickCount() - StartTicks;
  _tprintf(_T("Time taken to execute program in milliseconds is : %ld\n"), TimeInterval);
#else                                            
  time_t TimeInterval = time(NULL) - StartTime;
  _tprintf(_T("Time taken to execute program in seconds is : %ld\n"), TimeInterval);
#endif

  TermDTime();
  
  return FALSE;
}
