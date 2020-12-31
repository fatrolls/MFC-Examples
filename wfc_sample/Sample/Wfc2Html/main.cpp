#include "wfc2html.h"
#pragma hdrstop

// This program will scan and crossreference CPP source code.

int _tmain( int argc, LPCTSTR argv[] )
{
   WFCTRACEINIT( TEXT( "_tmain()" ) );

   CCPPToHTMLTranslator translator;

   translate_file( TEXT( "\\wfc\\sample\\wfc2html\\CCPPToHTMLTranslator.cpp" ), translator );

   return( EXIT_SUCCESS );
}