#ifndef _CALENDAR_H
#define _CALENDAR_H
 
#include <windows.h>
 
struct myDATE{
 int  year;
 int  month;
 int  day;
 bool isRunYue;
};
 
class calendar{
public:
 calendar(){};
 ~calendar(){};
 
  LONG lDaysFrom1900(myDATE date);//date与1900年相差的天数
  UINT lYearDays(UINT y);//农历y年的总天数
  UINT leapDays(UINT y);//传回农历 y年闰月的天数
  UINT leapMonth(UINT y);// 传回农历 y年闰哪个月 1-12 , 没闰传回 0
  UINT monthDays(UINT y,UINT m);//传回农历 y年m月的总天数
  myDATE Lunar(myDATE date);//输入阳历日期，返回阴历日期
  char* dayOfWeek(myDATE date);//输入阳历日期，返回星期几
  char* getLunarString (myDATE date );// 输入阴历日期,得到表示农历的字串
  UINT solarDays(UINT y,UINT m);//传回国历 y年某m+1月的天数
 
 
private:
 char                    m_slunar[100];//用于存储农历信息
 
 static DWORD   lunarInfo[];//
 static UINT    solarMonth[];
 static char    sSolarTerm[];
 static DWORD   dTermInfo[];
 static char    sFtv[];
 
};
#endif