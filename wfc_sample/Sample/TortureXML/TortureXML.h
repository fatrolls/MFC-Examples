#if ! defined( XML_TORTURE_TEST_HEADER_FILE )

#define XML_TORTURE_TEST_HEADER_FILE

#include <wfc.h>

// For generating random characters of different classes

// BaseChar characters
#define MINIMUM_BaseChar (0x41)
#define MAXIMUM_BaseChar (0xD7A3)
#define GET_RANDOM_BaseChar( r, x ) { do { x = (WCHAR) ( ( r.GetInteger() % \
( MAXIMUM_BaseChar - MINIMUM_BaseChar ) ) + MINIMUM_BaseChar ); \
while( is_xml_BaseChar( x ) == FALSE ); }

// CombiningChar characters
#define MINIMUM_CombiningChar (0x0300)
#define MAXIMUM_CombiningChar (0x309A)
#define GET_RANDOM_CombiningChar( r, x ) { do { x = (WCHAR) ( ( r.GetInteger() % \
( MAXIMUM_CombiningChar - MINIMUM_CombiningChar ) ) + MINIMUM_CombiningChar ); \
while( is_xml_CombiningChar( x ) == FALSE ); }

// Digit characters
#define MINIMUM_Digit (0x0030)
#define MAXIMUM_Digit (0x0F29)
#define GET_RANDOM_Digit( r, x ) { do { x = (WCHAR) ( ( r.GetInteger() % \
( MAXIMUM_Digit - MINIMUM_Digit ) ) + MINIMUM_Digit ); \
while( is_xml_Digit( x ) == FALSE ); }

// Extender characters
#define MINIMUM_Extender (0x00B7)
#define MAXIMUM_Extender (0x30FE)
#define GET_RANDOM_Extender( r, x ) { do { x = (WCHAR) ( ( r.GetInteger() % \
( MAXIMUM_Extender - MINIMUM_Extender ) ) + MINIMUM_Extender ); \
while( is_xml_Extender( x ) == FALSE ); }

// Ideographic characters
#define MINIMUM_Ideographic (0x3007)
#define MAXIMUM_Ideographic (0x9FA5)
#define GET_RANDOM_Ideographic( r, x ) { do { x = (WCHAR) ( ( r.GetInteger() % \
( MAXIMUM_Ideographic - MINIMUM_Ideographic ) ) + MINIMUM_Ideographic ); \
while( is_xml_Ideographic( x ) == FALSE ); }

// Letter characters
#define MINIMUM_Letter (0x41)
#define MAXIMUM_Letter (0x9FA5)
#define GET_RANDOM_Letter( r, x ) { do { x = (WCHAR) ( ( r.GetInteger() % \
( MAXIMUM_Letter - MINIMUM_Letter ) ) + MINIMUM_Letter ); \
while( is_xml_Letter( x ) == FALSE ); }

// NameChar characters
#define MINIMUM_NameChar (0x41)
#define MAXIMUM_NameChar (0x9FA5)
#define GET_RANDOM_NameChar( r, x ) { do { x = (WCHAR) ( ( r.GetInteger() % \
( MAXIMUM_NameChar - MINIMUM_NameChar ) ) + MINIMUM_NameChar ); \
while( is_xml_NameChar( x ) == FALSE ); }

// Char characters
#define MINIMUM_Char (0x09)
#define MAXIMUM_Char (0x10FFFF)
#define GET_RANDOM_Char( r, x ) { do { x = (DWORD) ( ( r.GetInteger() % \
( MAXIMUM_Char - MINIMUM_Char ) ) + MINIMUM_Char ); \
while( is_xml_NameChar( x ) == FALSE ); }

void create_huge_character_reference(   LPCTSTR filename, DWORD size, CRandomNumberGenerator2& random );
void create_huge_element(               LPCTSTR filename, DWORD size, CRandomNumberGenerator2& random );
void create_huge_element_and_attribute( LPCTSTR filename, DWORD size, CRandomNumberGenerator2& random );
void create_huge_element_name(          LPCTSTR filename, DWORD size, CRandomNumberGenerator2& random );
void create_huge_encoding(              LPCTSTR filename, DWORD size, CRandomNumberGenerator2& random );
void create_huge_version(               LPCTSTR filename, DWORD size, CRandomNumberGenerator2& random );

#endif // XML_TORTURE_TEST_HEADER_FILE
