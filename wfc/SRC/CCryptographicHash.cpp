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
** $Workfile: CCryptographicHash.cpp $
** $Revision: 24 $
** $Modtime: 1/04/00 5:09a $
** $Reuse Tracing Code: 1 $
*/

#if _MSC_VER < 1020
#pragma message( "Need Visual C++ 4.2 or later to compile CCryptographicHash" )
#else // _MSC_VER

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// Construction

CCryptographicHash::CCryptographicHash()
{
   WFCLTRACEINIT( TEXT( "CCryptographicHash::CCryptographicHash()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   m_Hash = NULL;
   m_AutomaticallyDestroy = FALSE;
}

CCryptographicHash::CCryptographicHash( HCRYPTHASH source_handle, BOOL automatically_destroy )
{
   WFCLTRACEINIT( TEXT( "CCryptographicHash::CCryptographicHash( HCRYPTHASH )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   m_Hash = NULL;
   m_AutomaticallyDestroy = FALSE;

   FromHandle( source_handle, automatically_destroy );
}

CCryptographicHash::~CCryptographicHash()
{
   WFCLTRACEINIT( TEXT( "CCryptographicHash::CCryptographicHash()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   if ( m_AutomaticallyDestroy != FALSE )
   {
      Destroy();
   }
}

// Methods

BOOL CCryptographicHash::Destroy( void )
{
   WFCLTRACEINIT( TEXT( "CCryptographicHash::Destroy()" ) );

   BOOL return_value = FALSE;

   return_value = ::CryptDestroyHash( m_Hash );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
   }
   else
   {
      return_value = TRUE;
   }

   m_Hash                 = NULL;
   m_AutomaticallyDestroy = FALSE;

   return( return_value );
}

BOOL CCryptographicHash::FromHandle( HCRYPTHASH source_handle, BOOL automatically_destroy )
{
   WFCLTRACEINIT( TEXT( "CCryptographicHash::FromHandle()" ) );

   // See if we are already handling a key

   if ( m_Hash != NULL )
   {
      if ( m_AutomaticallyDestroy != FALSE )
      {
         Destroy();
      }
   }

   m_Hash = source_handle;
   m_AutomaticallyDestroy = automatically_destroy;

   return( TRUE );
}

BOOL CCryptographicHash::GetAlgorithmIdentifier( DWORD& identifier )
{
   WFCLTRACEINIT( TEXT( "CCryptographicHash::GetAlgorithmIdentifier()" ) );

   DWORD buffer_length = sizeof( identifier );

   return( GetParameter( parameterAlgorithmIdentifier, (BYTE *) &identifier, buffer_length ) );
}

HCRYPTHASH CCryptographicHash::GetHandle( void ) const
{
   return( m_Hash );
}

BOOL CCryptographicHash::GetLength( DWORD& length )
{
   WFCLTRACEINIT( TEXT( "CCryptographicHash::GetLength()" ) );

   DWORD buffer_length = sizeof( length );

   return( GetParameter( parameterLength, (BYTE *) &length, buffer_length ) );
}

BOOL CCryptographicHash::GetValue( CByteArray& value )
{
   WFCLTRACEINIT( TEXT( "CCryptographicHash::Value()" ) );

   value.SetSize( 1024 ); // A Massive value

   DWORD buffer_length = value.GetSize();

   BOOL return_value = FALSE;

   return_value = GetParameter( parameterValue, value.GetData(), buffer_length );

   if ( return_value != FALSE )
   {
      value.SetSize( buffer_length );
   }

   return( return_value );
}

BOOL CCryptographicHash::GetParameter( const DWORD parameter_to_get, BYTE *buffer, DWORD& buffer_length, const DWORD flags )
{
   WFCLTRACEINIT( TEXT( "CCryptographicHash::GetParameter()" ) );

   BOOL return_value = FALSE;

   return_value = ::CryptGetHashParam( m_Hash, parameter_to_get, buffer, &buffer_length, flags );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
   }
   else
   {
      return_value = TRUE;
   }

   // Frank O'Rourke <forourke@trintech.com> found a bug here. For some unknown
   // reason, I was returning m_ErrorCode. I guess I had a case of the stupids that day.

   return( return_value );
}

BOOL CCryptographicHash::Hash( CByteArray& data_to_compute_hash_on, DWORD flags )
{
   WFCLTRACEINIT( TEXT( "CCryptographicHash::Hash( CByteArray )" ) );

   BOOL return_value = FALSE;

   // They screwed up the declaration. The buffer parameter should be
   // const BYTE * but it isn't. That means we cannot make our
   // data_to_compute_hash_on const correct.

   return_value = ::CryptHashData( m_Hash, 
                                   data_to_compute_hash_on.GetData(), 
                                   data_to_compute_hash_on.GetSize(),
                                   flags );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
   }
   else
   {
      return_value = TRUE;
   }

   return( return_value );
}

BOOL CCryptographicHash::Hash( const CCryptographicKey& key_to_hash, DWORD flags )
{
   WFCLTRACEINIT( TEXT( "CCryptographicHash::Hash( CCryptographicKey )" ) );

   BOOL return_value = FALSE;

   return_value = ::CryptHashSessionKey( m_Hash, 
                                         key_to_hash.GetHandle(), 
                                         flags );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
   }
   else
   {
      return_value = TRUE;
   }

   return( return_value );
}

BOOL CCryptographicHash::SetParameter( const DWORD parameter_to_set, BYTE *buffer, const DWORD flags )
{
   WFCLTRACEINIT( TEXT( "CCryptographicHash::SetParameter()" ) );

   BOOL return_value = FALSE;

   // The buffer parameter to CryptSetHashParam is not const correct. It is
   // described in the documentation as an [in] parameter. This means the
   // CryptoAPI promises not to modify it. However, the parameter is not
   // typed as const. This means they screwed up the prototype.

   return_value = ::CryptSetHashParam( m_Hash, parameter_to_set, buffer, flags );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
   }
   else
   {
      return_value = TRUE;
   }

   return( return_value );
}

BOOL CCryptographicHash::SetValue( CByteArray& value )
{
   WFCLTRACEINIT( TEXT( "CCryptographicHash::SetValue()" ) );

   return( SetParameter( parameterValue, value.GetData() ) );
}

BOOL CCryptographicHash::Sign( DWORD which_key_to_sign_with, CString& password, CByteArray& signed_hash, DWORD flags )
{
   WFCLTRACEINIT( TEXT( "CCryptographicHash::Sign()" ) );

   signed_hash.RemoveAll();

   DWORD number_of_bytes_in_signature = 0;

   BOOL return_value = FALSE;

   // Find out how many bytes we need for the signed hash

   return_value = ::CryptSignHash( m_Hash,
                                   which_key_to_sign_with,
                                   password,
                                   flags,
                                   NULL,
                                  &number_of_bytes_in_signature );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACE( TEXT( "Can't get size of signed hash" ) );
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   signed_hash.SetSize( number_of_bytes_in_signature );

   return_value = ::CryptSignHash( m_Hash,
                                   which_key_to_sign_with,
                                   password,
                                   flags,
                                   signed_hash.GetData(),
                                  &number_of_bytes_in_signature );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACE( TEXT( "Can't get signed hash" ) );
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   return( TRUE );
}

BOOL CCryptographicHash::VerifySignature( CByteArray& signature_to_be_verified, CCryptographicKey& public_key_to_verify_with, CString& password, DWORD flags )
{
   WFCLTRACEINIT( TEXT( "CCryptographicHash::VerifySignature()" ) );

   // Once this function has been called, Destroy() must be called.

   BOOL return_value = FALSE;

   return_value = ::CryptVerifySignature( m_Hash,
                                          signature_to_be_verified.GetData(),
                                          signature_to_be_verified.GetSize(),
                                          public_key_to_verify_with.GetHandle(),
                                          password,
                                          flags );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   // Call succeeded, we must now destroy our hash

   Destroy();

   return( TRUE );
}

#endif // _MSC_VER

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CCryptographicHash</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that handles CryptoAPI hashing.">
</HEAD>

<BODY>

<H1>CCryptographicHash : <A HREF="CCryptography.htm">CCryptography</A></H1>
$Revision: 24 $<BR><HR>

<H2>Description</H2>

This class encapsulates cryptographic hashes. A &quot;cryptographic hash&quot; is
basically a checksum.

<H2>Constructors</H2>

<DL COMPACT>

<DT><PRE><B>CCryptographicHash</B>()
<B>CCryptographicHash</B>( HCRYPTHASH source_handle, BOOL automatically_destroy = TRUE )</PRE><DD>
Constructs the object.

</DL>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>BOOL <B>Destroy</B>( void )</PRE><DD>
Destroys the hash.

<DT><PRE>BOOL <B>FromHandle</B>( HCRYPTHASH source_handle, BOOL automatically_destroy = TRUE )</PRE><DD>
Tells the class to start playing with the HCRYPTHASH provided.

<DT><PRE>BOOL <B>GetAlgorithmIdentifier</B>( DWORD&amp; identifier )</PRE><DD>
Retrieves the identifier for the algorithm.

<DT><PRE>HCRYPTHASH <B>GetHandle</B>( void ) const</PRE><DD>
Returns the encapsulated HCRYPTHASH so you can play with the API directly.

<DT><PRE>BOOL <B>GetLength</B>( DWORD&amp; block_length )</PRE><DD>
Retrieves the block length.

<DT><PRE>BOOL <B>GetValue</B>( CByteArray&amp; hash_result )</PRE><DD>
Retrieves the hash itself.

<DT><PRE>BOOL <B>GetParameter</B>( const DWORD parameter_to_get, BYTE *buffer, DWORD&amp; buffer_length, const DWORD flags = 0 )</PRE><DD>
Retrieves one of the following bits of information:
<UL>
<LI>parameterAlgorithmIdentifier
<LI>parameterLength
<LI>parameterValue
</UL>
It is probably easier to call the helper functions, <B>GetAlgorithmIdentifier</B>(),
<B>GetLength</B>() or <B>GetValue</B>() than <B>GetParameter</B>().

<DT><PRE>BOOL <B>Hash</B>(  CByteArray&amp; data_to_compute_a_hash_on, DWORD flags = CRYPT_USERDATA  )
BOOL <B>Hash</B>( const CCryptographicKey&amp; key_to_hash, DWORD flags = 0 )</PRE><DD>
Computes the hash value from the data block (<CODE>data_to_compute_hash_on</CODE>)or
the CCryptographicKey (<CODE>key_to_hash</CODE>) given. You can retrieve the hash via <B>GetValue</B>.

<DT><PRE>BOOL <B>SetParameter</B>( const DWORD parameter_to_set, BYTE *buffer, const DWORD flags = 0 )</PRE><DD>
Sets a parameter of the key. You can set one of these parameters:
<UL>
<LI>parameterValue
</UL>

<DT><PRE>BOOL <B>SetValue</B>( CByteArray&amp; value )</PRE><DD>
Basically calls <B>SetParameter</B>() with parameterValue.

<DT><PRE>BOOL <B>Sign</B>( DWORD which_key_to_sign_with, CString&amp; password, CByteArray&amp; signature, DWORD flags = 0 )</PRE><DD>
After you've created the hash you must sign it. You
must supply a plain text password to be used in the signature.

<DT><PRE>BOOL <B>VerifySignature</B>( CByteArray&amp; signature, CCryptographicKey&amp; public_key_to_verify_with, CString&amp; password, DWORD flags = 0 )</PRE><DD>
To verify the signature, you must supply
the exact same plain text password as the person who signed (using <B>Sign</B>()) the hash.

</DL>

<H2>Example</H2><PRE><CODE>Sorry.</CODE></PRE>

<H2>API's Used</H2>
<UL>
<LI>CryptDestroyHash
<LI>CryptGetHashParam
<LI>CryptHashData
<LI>CryptHashSessionKey
<LI>CryptSetHashParam
<LI>CryptSignHash
<LI>CryptVerifySignature
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CCryptographicHash.cpp $<BR>
$Modtime: 1/04/00 5:09a $
</BODY>
</HTML>
The following line should go in AUTOEXP.DAT so the debugging tooltips will format properly
ToolTipFormatLine=CCryptographicHash=m_Hash=<m_Hash>
#endif
