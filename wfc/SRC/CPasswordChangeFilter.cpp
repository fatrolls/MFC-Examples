#include <wfc.h>
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** Internet: wfc@pobox.com
**
** You can use it any way you like as long as you don't try to sell it.
**
** Any attempt to sell WFC in source code form must have the permission
** of the original author. You can produce commercial executables with
** WFC but you can't sell WFC.
**
** Copyright, 2000, Samuel R. Blackburn
**
** $Workfile: CPasswordChangeFilter.cpp $
** $Revision: 13 $
** $Modtime: 1/17/00 9:09a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CPasswordChangeFilter::CPasswordChangeFilter()
{
   WFCLTRACEINIT( TEXT( "CPasswordChangeFilter::CPasswordChangeFilter()" ) );
}

CPasswordChangeFilter::~CPasswordChangeFilter()
{
   WFCLTRACEINIT( TEXT( "CPasswordChangeFilter::~CPasswordChangeFilter()" ) );
}

BOOL CPasswordChangeFilter::AddFilter( const CString& dll_name )
{
   WFCLTRACEINIT( TEXT( "CPasswordChangeFilter::AddFilter()" ) );

   CRegistry registry;

   if ( registry.Connect( (HKEY) CRegistry::keyLocalMachine ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't connect to local machine" ) );
      return( FALSE );
   }

   if ( registry.Open( TEXT( "SYSTEM\\CurrentControlSet\\Control\\Lsa" ), (CRegistry::CreatePermissions)(CRegistry::permissionRead | CRegistry::permissionSetValue ) ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't open SYSTEM\\CurrentControlSet\\Control\\Lsa" ) );
      return( FALSE );
   }

   CStringArray current_filters;

   GetCurrentFilters( current_filters );

   int index = 0;
   int number_of_filters = current_filters.GetSize();

   CString filter_name;

   while( index < number_of_filters )
   {
      filter_name = current_filters.GetAt( index );

      if ( filter_name.CompareNoCase( dll_name ) == 0 )
      {
         // The filter is already added. That was silly.
         return( TRUE );
      }
      else
      {
         index++;
      }
   }

   current_filters.Add( dll_name );

   if ( registry.SetStringArrayValue( TEXT( "Notification Packages" ), current_filters ) == FALSE )
   {
      return( FALSE );
   }

   return( TRUE );
}

BOOL CPasswordChangeFilter::GetCurrentFilters( CStringArray& current_filters )
{
   WFCLTRACEINIT( TEXT( "CPasswordChangeFilter::GetCurrentFilters()" ) );

   CRegistry registry;

   if ( registry.Connect( (HKEY) CRegistry::keyLocalMachine ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't connect to local machine" ) );
      return( FALSE );
   }

   if ( registry.Open( TEXT( "SYSTEM\\CurrentControlSet\\Control\\Lsa" ), (CRegistry::CreatePermissions)(CRegistry::permissionRead) ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't open SYSTEM\\CurrentControlSet\\Control\\Lsa" ) );
      return( FALSE );
   }

   if ( registry.GetStringArrayValue( TEXT( "Notification Packages" ), current_filters ) == FALSE )
   {
      current_filters.RemoveAll();
      return( FALSE );
   }

   return( TRUE );
}

BOOL CPasswordChangeFilter::OnChanged( PASSWORD_FILTER_STRING * /* user_name */, ULONG /* relative_id */, PASSWORD_FILTER_STRING * /* new_password */ )
{
   WFCLTRACEINIT( TEXT( "CPasswordChangeFilter::OnChanged()" ) );
   return( TRUE );
}

BOOL CPasswordChangeFilter::OnFilter( PASSWORD_FILTER_STRING * /* user_name */, PASSWORD_FILTER_STRING * /* full_user_name */, PASSWORD_FILTER_STRING * /* new_password */, BOOL /* was_set */ )
{
   WFCLTRACEINIT( TEXT( "CPasswordChangeFilter::OnFilter()" ) );
   return( TRUE );
}

BOOL CPasswordChangeFilter::OnInitialize( void )
{
   WFCLTRACEINIT( TEXT( "CPasswordChangeFilter::OnInitialize()" ) );
   return( TRUE );
}

BOOL CPasswordChangeFilter::RemoveFilter( const CString& dll_name )
{
   WFCLTRACEINIT( TEXT( "CPasswordChangeFilter::RemoveFilter()" ) );

   CRegistry registry;

   if ( registry.Connect( (HKEY) CRegistry::keyLocalMachine ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't connect to local machine" ) );
      return( FALSE );
   }

   if ( registry.Open( TEXT( "SYSTEM\\CurrentControlSet\\Control\\Lsa" ), (CRegistry::CreatePermissions)(CRegistry::permissionRead | CRegistry::permissionSetValue ) ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't open SYSTEM\\CurrentControlSet\\Control\\Lsa" ) );
      return( FALSE );
   }

   CStringArray current_filters;

   GetCurrentFilters( current_filters );

   int index = 0;
   int number_of_filters = current_filters.GetSize();

   CString filter_name;

   while( index < number_of_filters )
   {
      filter_name = current_filters.GetAt( index );

      if ( filter_name.CompareNoCase( dll_name ) == 0 )
      {
         // We found one.
         current_filters.RemoveAt( index );
         number_of_filters--;
      }
      else
      {
         index++;
      }
   }

   current_filters.Add( dll_name );

   if ( registry.SetStringArrayValue( TEXT( "Notification Packages" ), current_filters ) == FALSE )
   {
      return( FALSE );
   }

   return( TRUE );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CPasswordChangeFilter</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that intercepts password changes on a domain.">
</HEAD>

<BODY>
<H1>CPasswordChangeFilter</H1>
$Revision: 13 $<BR><HR>

<H2>Description</H2>
This class makes it easy to filter password changes in NT.

<H2>Data Members</H2>None.

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>BOOL <B>AddFilter</B>( const CString&amp; dll_name )</PRE><DD>
This method adds the <CODE>dll_name</CODE> to the list of DLL's
that will be called when a password changes.

<DT><PRE>BOOL <B>GetCurrentFilters</B>( CStringArray&amp; current_filters )</PRE><DD>
Retrieves a list of filters currently in use. These are the names of the DLL's
that are called when a user's password changes.

<DT><PRE>BOOL <B>OnChanged</B>( PASSWORD_FILTER_STRING * user_name, ULONG relative_id, PASSWORD_FILTER_STRING * new_password )</PRE><DD>
This is called when the user changed their password. This is where you would
do smurphy things like change passwords on other applications (or operating
operating systems). This is the key to &quot;single user logon&quot; setups.
Whenever the user changes their password, <B>OnChanged</B>() will get called
allowing you to take the appropriate actions to change their password any
where else it needs changing.

<DT><PRE>BOOL <B>OnFilter</B>( PASSWORD_FILTER_STRING * user_name, PASSWORD_FILTER_STRING * full_user_name, PASSWORD_FILTER_STRING * new_password, BOOL was_set )</PRE><DD>
Called when a user is changing their password. This is where you would
put your code to &quot;score&quot; a user's typed in password. If it
does not meet your randomness criteria, return FALSE. If the password
is OK, then return TRUE. The default is to return TRUE.

<DT><PRE>BOOL <B>OnInitialize</B>( void )</PRE><DD>
Returns TRUE. Override it to do what you want.

<DT><PRE>BOOL <B>RemoveFilter</B>( const CString&amp; dll_name )</PRE><DD>
This method removes the <CODE>dll_name</CODE> from the list of DLL's
that will be called when a password changes.

</DL>

<H2>Notes</H2>

Notifications and filtering only takes place on the machine that holds
the passwords. This could be the Primary Domain Controller (PDC) if you are
using domains. If you are using domains, don't forget to install the
password filter on the Backup Domain Controllers (BDC) so the filters
will continue if an election was forced (i.e. role reversal).

<H2>Example</H2><PRE><CODE>void _tmain()
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;_tmain()&quot; ) );

   <B>CPasswordChangeFilter</B> filter;

   filter.AddFilter( TEXT( &quot;e:\\wfc\\sample\\passwordfilter\\dll\\password.dll&quot; ) );
}</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CPasswordChangeFilter.cpp $<BR>
$Modtime: 1/17/00 9:09a $
</BODY>

</HTML>
#endif
