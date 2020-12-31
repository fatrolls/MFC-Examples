
#include "calendar.h"
#include <cstdio>//.h

DWORD calendar::lunarInfo[]={
 0x04bd8,0x04ae0,0x0a570,0x054d5,0x0d260,0x0d950,0x16554,0x056a0,0x09ad0,0x055d2,
 0x04ae0,0x0a5b6,0x0a4d0,0x0d250,0x1d255,0x0b540,0x0d6a0,0x0ada2,0x095b0,0x14977,
 0x04970,0x0a4b0,0x0b4b5,0x06a50,0x06d40,0x1ab54,0x02b60,0x09570,0x052f2,0x04970,
 0x06566,0x0d4a0,0x0ea50,0x06e95,0x05ad0,0x02b60,0x186e3,0x092e0,0x1c8d7,0x0c950,
 0x0d4a0,0x1d8a6,0x0b550,0x056a0,0x1a5b4,0x025d0,0x092d0,0x0d2b2,0x0a950,0x0b557,
 0x06ca0,0x0b550,0x15355,0x04da0,0x0a5d0,0x14573,0x052d0,0x0a9a8,0x0e950,0x06aa0,
 0x0aea6,0x0ab50,0x04b60,0x0aae4,0x0a570,0x05260,0x0f263,0x0d950,0x05b57,0x056a0,
 0x096d0,0x04dd5,0x04ad0,0x0a4d0,0x0d4d4,0x0d250,0x0d558,0x0b540,0x0b5a0,0x195a6,
 0x095b0,0x049b0,0x0a974,0x0a4b0,0x0b27a,0x06a50,0x06d40,0x0af46,0x0ab60,0x09570,
 0x04af5,0x04970,0x064b0,0x074a3,0x0ea50,0x06b58,0x055c0,0x0ab60,0x096d5,0x092e0,
 0x0c960,0x0d954,0x0d4a0,0x0da50,0x07552,0x056a0,0x0abb7,0x025d0,0x092d0,0x0cab5,
 0x0a950,0x0b4a0,0x0baa4,0x0ad50,0x055d9,0x04ba0,0x0a5b0,0x15176,0x052b0,0x0a930,
 0x07954,0x06aa0,0x0ad50,0x05b52,0x04b60,0x0a6e6,0x0a4e0,0x0d260,0x0ea65,0x0d530,
 0x05aa0,0x076a3,0x096d0,0x04bd7,0x04ad0,0x0a4d0,0x1d0b6,0x0d250,0x0d520,0x0dd45,
 0x0b5a0,0x056d0,0x055b2,0x049b0,0x0a577,0x0a4b0,0x0aa50,0x1b255,0x06d20,0x0ada0
};
UINT calendar::solarMonth[]={31,28,31,30,31,30,31,31,30,31,30,31};
UINT calendar::lYearDays(UINT y)
{
   UINT i, sum = 348;
   for(i=0x8000; i>0x8; i>>=1)
   {
    sum += (lunarInfo[y-1900] & i)? 1: 0;
   }
   return(sum+leapDays(y));
}
 
UINT calendar::leapDays(UINT y)
{
   if(leapMonth(y))
   {
    return (lunarInfo[y-1900] & 0x10000)? 30: 29;
   }
   else
   {
    return 0;
   }
}
 
UINT calendar::leapMonth(UINT y)
{
   return lunarInfo[y-1900] & 0xf;
}
 
UINT calendar::monthDays(UINT y,UINT m)
{
   return (lunarInfo[y-1900] & (0x10000>>m))? 30: 29;
}
LONG calendar::lDaysFrom1900(myDATE date)
{
 LONG days;
 
 days=365*date.year+(date.year-1)/4-(date.year-1)/100+(date.year-1)/400-
  (365*1900+(1900-1)/4-(1900-1)/100+(1900-1)/400);
 
 for(int i=0;i<date.month-1;i++)
 {
  days+=solarMonth[i];
 }
 days+=date.day;
 if((date.year%4==0&&date.year%100!=0)||date.year%400==0)
 {
  if(date.month>2)
  {
   days++;
  }
 }
 return days;
}
 
myDATE calendar::Lunar(myDATE date)
{
 LONG offset;
 int i, leap=0, temp=0;
 myDATE retdate;
 
 offset=lDaysFrom1900(date)-30;
 
 for(i=1900; i<2050 && offset>0; i++)
 {
  temp = lYearDays(i);
  offset -= temp;
 }
 
 if(offset<0)
 {
  offset += temp;
  i--;
 }
 
 retdate.year = i;
 
 leap = leapMonth(i);
 bool isLeap = false;
 
 for(i=1; i<13 && offset>0; i++)
 {
  if(leap>0 && i==(leap+1) && isLeap==false)
  {
   --i;
   isLeap = true;
   temp = leapDays(retdate.year);
  }
  else
  {
   temp = monthDays(retdate.year, i);
  }
  if(isLeap==true && i==(leap+1))
  {
   isLeap = false;
  }
  offset -= temp;
 }
 if(offset==0 && leap>0 && i==leap+1)
 {
  if(isLeap)
  {
   isLeap = false;
  }
  else
  {
   isLeap = true;
   --i;
  }
 }
 if(offset<=0)
 {
  offset += temp;
  --i;
 }
 retdate.month = i;
 retdate.day = offset ;
 retdate.isRunYue=isLeap;
 return retdate;
}
 
char* calendar::getLunarString (myDATE date)
{
 TCHAR szNongli[30], szNongliDay[10],szShuXiang[10];
 const char *cTianGan[]  = {"甲","乙","丙","丁","戊","己","庚","辛","壬","癸"}; /*天干名称*/
 const char *cDiZhi[]    = {"子","丑","寅","卯","辰","巳","午", "未","申","酉","戌","亥"}; /*地支名称*/
 const char *cShuXiang[] = {"鼠","牛","虎","兔","龙","蛇","马","羊","猴","鸡","狗","猪"}; /*属相名称*/
 const char *cDayName[]  = { "*","初一","初二","初三","初四","初五", /*农历日期名*/
        "初六","初七","初八","初九","初十",
        "十一","十二","十三","十四","十五",
        "十六","十七","十八","十九","二十",
        "廿一","廿二","廿三","廿四","廿五",      
        "廿六","廿七","廿八","廿九","三十"};
 const char *cMonName[]  = {"*","正","二","三","四","五","六", "七","八","九","十","十一","腊"};
 
 /*--生成农历天干、地支、属相 ==> wNongli--*/
 int nShuXiang = ((date.year - 4) % 60) % 12;
 if ( nShuXiang < 0 || nShuXiang >= sizeof(cShuXiang)/sizeof(cShuXiang[0]) )
 {
  return NULL ;
 }
 wsprintf(szShuXiang,"%s",cShuXiang[nShuXiang]);
 int nTianGan = ((date.year - 4) % 60) % 10;
 if ( nTianGan < 0 || nTianGan >= sizeof(cTianGan)/sizeof(cTianGan[0]) )
 {
  return NULL;
 }
 int nDiZhi = ((date.year - 4) % 60) % 12;
 if ( nDiZhi < 0 || nDiZhi >= sizeof(cDiZhi)/sizeof(cDiZhi[0]) )
 {
  return NULL;
 }
 
 wsprintf(szNongli,"%s(%s%s)年",szShuXiang,cTianGan[nTianGan],cDiZhi[nDiZhi]);
 
 /*--生成农历月、日 ==> wNongliDay--*/
 if ( date.month < 0 || date.month >= sizeof(cMonName)/sizeof(cMonName[0]) )
 {
  return NULL;
 }
 
 if (date.isRunYue)
 {
  wsprintf(szNongliDay,"闰%s",cMonName[date.month]);
 }
 else
 {
  strcpy(szNongliDay,cMonName[date.month]);
 }
 
 strcat(szNongliDay,"月");
 if ( date.day < 0 || date.day >= sizeof(cDayName)/sizeof(cDayName[0]) )
 {
  return NULL;
 }
 
 strcat(szNongliDay,cDayName[date.day]);
 strcat(szNongli,szNongliDay);
 sprintf(m_slunar,szNongli);
 return m_slunar;
}
char* calendar::dayOfWeek(myDATE date)
{
 char *cWeekName[]  = {"星期日","星期一","星期二","星期三","星期四","星期五","星期六"};
 
 if(date.month==1||date.month==2)
 {
  date.month+=12;
  date.year--;
 }
 return cWeekName[(date.day+1+2*date.month+3*(date.month+1)/5+date.year+date.year/4-date.year/100+date.year/400)%7];
}
 
UINT calendar::solarDays(UINT y,UINT m)
{
 if(m==1)//2月
 {
  return(((y%4 == 0) && (y%100 != 0) || (y%400 == 0))? 29: 28);
 }
 else
 {
  return(solarMonth[m]);
 }
}
