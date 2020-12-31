#include <wfc.h>
#pragma hdrstop

void _tmain()
{
   CPasswordChangeFilter filter;

   filter.AddFilter( TEXT( "e:\\wfc\\sample\\passwordfilter\\dll\\password.dll" ) );
}