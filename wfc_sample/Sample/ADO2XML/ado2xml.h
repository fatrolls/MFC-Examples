#if ! defined( ADO2XML_HEADER_FILE )

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
** $Workfile: ado2xml.h $
** $Revision: 1 $
** $Modtime: 3/19/00 7:44a $
** $Reuse Tracing Code: 1 $
*/

#define ADO2XML_HEADER_FILE

#define _WIN32_WINNT (0x0400)

#define WFC_STL
#include <wfc.h>

#define _INC_MALLOC
#import "c:\program files\Common Files\System\ADO\msado15.dll" no_namespace rename( "EOF", "EndOfFile" )

#include <icrsint.h>

#include "CDatabaseParameters.hpp"

void convert_DataTypeEnum_to_string( DWORD data_type_enum, CString& string_to_fill );
void convert_desired_tables( const CExtensibleMarkupLanguageElement * settings, const CDatabaseParameters& database_parameters );;
void get_blob( FieldPtr& field_p, CByteArray& blob );
void normalize_string( CString& string_to_normalize );
void output_field( FieldPtr& field );
void output_types( DWORD data_type_enum );
void print_COM_error( _com_error& exception );
void print_provider_error( _ConnectionPtr );
void replace( CString& string, const CString& what_to_replace, const CString& what_to_replace_it_with );

bool convert_table( _ConnectionPtr& connection_p, const CString& table_name, const CString& where_clause );
bool get_table_names( _ConnectionPtr& connection_p, CStringArray& table_names );
bool open_connection_to_database( const CDatabaseParameters& database_parameters, _ConnectionPtr& connection_p );
bool output_schema( _ConnectionPtr& connection_p, const CString& table_name, const CString& where_clause );

#endif // ADO2XML_HEADER_FILE
