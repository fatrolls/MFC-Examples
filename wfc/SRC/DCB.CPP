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
** $Workfile: dcb.cpp $
** $Revision: 16 $
** $Modtime: 1/04/00 5:24a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CDeviceControlBlock::CDeviceControlBlock()
{
   ::ZeroMemory( (DCB *) this, sizeof( DCB ) );
   DCBlength = sizeof( DCB );
   fBinary = TRUE; // Always TRUE for NT
}

CDeviceControlBlock::CDeviceControlBlock( const DCB * source )
{
   DCBlength = sizeof( DCB );

   Copy( source );
}

CDeviceControlBlock::CDeviceControlBlock( const DCB& source )
{
   DCBlength = sizeof( DCB );

   Copy( source );
}

CDeviceControlBlock::CDeviceControlBlock( const CDeviceControlBlock& source )
{
   DCBlength = sizeof( DCB );

   Copy( source );
}

CDeviceControlBlock::~CDeviceControlBlock()
{
   DCBlength = 0;
}

void CDeviceControlBlock::Copy( const CDeviceControlBlock& source )
{
   Copy( (DCB *) &source );
}

void CDeviceControlBlock::Copy( const DCB& source )
{
   Copy( &source );
}

void CDeviceControlBlock::Copy( const DCB* source )
{
   ASSERT( source != NULL );
   ASSERT( source != this );

   if ( source == this )
   {
      return;
   }

   if ( source == NULL )
   {
      ::ZeroMemory( (DCB *) this, sizeof( DCB ) );
      DCBlength = sizeof( DCB );
      fBinary = TRUE; // Always TRUE for NT
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      BaudRate          = source->BaudRate;
      fBinary           = source->fBinary;
      fParity           = source->fParity;
      fOutxCtsFlow      = source->fOutxCtsFlow;
      fOutxDsrFlow      = source->fOutxDsrFlow;
      fDtrControl       = source->fDtrControl;
      fDsrSensitivity   = source->fDsrSensitivity;
      fTXContinueOnXoff = source->fTXContinueOnXoff;
      fOutX             = source->fOutX;
      fInX              = source->fInX;
      fErrorChar        = source->fErrorChar;
      fNull             = source->fNull;
      fRtsControl       = source->fRtsControl;
      fDummy2           = source->fDummy2;
      wReserved         = source->wReserved;
      XonLim            = source->XonLim;
      XoffLim           = source->XoffLim;
      ByteSize          = source->ByteSize;
      Parity            = source->Parity;
      StopBits          = source->StopBits;
      XonChar           = source->XonChar;
      XoffChar          = source->XoffChar;
      ErrorChar         = source->ErrorChar;
      EofChar           = source->EofChar;
      EvtChar           = source->EvtChar;
   }
   catch( ... )
   {
      ::ZeroMemory( (DCB *) this, sizeof( DCB ) );
      DCBlength = sizeof( DCB );
      fBinary = TRUE; // Always TRUE for NT
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CDeviceControlBlock::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CDeviceControlBlock at " ) << (void *) this << TEXT( "\n{\n" );
   dump_context << TEXT( "   DCBlength =         " ) << DCBlength         << TEXT( "\n" );
   dump_context << TEXT( "   BaudRate =          " ) << BaudRate          << TEXT( " (" );

   switch( BaudRate )
   {
      case CBR_110:

         dump_context << TEXT( "CBR_110" );
         break;

      case CBR_300:

         dump_context << TEXT( "CBR_300" );
         break;

      case CBR_600:

         dump_context << TEXT( "CBR_600" );
         break;

      case CBR_1200:

         dump_context << TEXT( "CBR_1200" );
         break;

      case CBR_2400:

         dump_context << TEXT( "CBR_2400" );
         break;

      case CBR_4800:

         dump_context << TEXT( "CBR_4800" );
         break;

      case CBR_9600:

         dump_context << TEXT( "CBR_9600" );
         break;

      case CBR_14400:

         dump_context << TEXT( "CBR_14400" );
         break;

      case CBR_19200:

         dump_context << TEXT( "CBR_19200" );
         break;

      case CBR_38400:

         dump_context << TEXT( "CBR_38400" );
         break;

      case CBR_56000:

         dump_context << TEXT( "CBR_56000" );
         break;

      case CBR_57600:

         dump_context << TEXT( "CBR_57600" );
         break;

      case CBR_115200:

         dump_context << TEXT( "CBR_115200" );
         break;

      case CBR_128000:

         dump_context << TEXT( "CBR_128000" );
         break;

      case CBR_256000:

         dump_context << TEXT( "CBR_256000" );
         break;
   }

   dump_context << TEXT( ")\n" );

   dump_context << TEXT( "   fBinary =           " ) << fBinary           << TEXT( "\n" );
   dump_context << TEXT( "   fParity =           " ) << fParity           << TEXT( "\n" );
   dump_context << TEXT( "   fOutxCtsFlow =      " ) << fOutxCtsFlow      << TEXT( "\n" );
   dump_context << TEXT( "   fOutxDsrFlow =      " ) << fOutxDsrFlow      << TEXT( "\n" );
   dump_context << TEXT( "   fDtrControl =       " ) << fDtrControl       << TEXT( " (" );

   switch( fDtrControl )
   {
      case DTR_CONTROL_DISABLE:

         dump_context << TEXT( "DTR_CONTROL_DISABLE" );
         break;

      case DTR_CONTROL_ENABLE:

         dump_context << TEXT( "DTR_CONTROL_ENABLE" );
         break;

      case DTR_CONTROL_HANDSHAKE:

         dump_context << TEXT( "DTR_CONTROL_HANDSHAKE" );
         break;
   }

   dump_context << TEXT( ")\n" );

   dump_context << TEXT( "   fDsrSensitivity =   " ) << fDsrSensitivity   << TEXT( "\n" );
   dump_context << TEXT( "   fTXContinueOnXoff = " ) << fTXContinueOnXoff << TEXT( "\n" );
   dump_context << TEXT( "   fOutX =             " ) << fOutX             << TEXT( "\n" );
   dump_context << TEXT( "   fInX =              " ) << fInX              << TEXT( "\n" );
   dump_context << TEXT( "   fErrorChar =        " ) << fErrorChar        << TEXT( "\n" );
   dump_context << TEXT( "   fNull =             " ) << fNull             << TEXT( "\n" );
   dump_context << TEXT( "   fRtsControl =       " ) << fRtsControl       << TEXT( " (" );

   switch( fRtsControl )
   {
      case RTS_CONTROL_DISABLE:

         dump_context << TEXT( "RTS_CONTROL_DISABLE" );
         break;

      case RTS_CONTROL_ENABLE:

         dump_context << TEXT( "RTS_CONTROL_ENABLE" );
         break;

      case RTS_CONTROL_HANDSHAKE:

         dump_context << TEXT( "RTS_CONTROL_HANDSHAKE" );
         break;

      case RTS_CONTROL_TOGGLE:

         dump_context << TEXT( "RTS_CONTROL_TOGGLE" );
         break;
   }

   dump_context << TEXT( ")\n" );

   dump_context << TEXT( "   fDummy2 =           " ) << fDummy2           << TEXT( "\n" );
   dump_context << TEXT( "   wReserved =         " ) << wReserved         << TEXT( "\n" );
   dump_context << TEXT( "   XonLim =            " ) << XonLim            << TEXT( "\n" );
   dump_context << TEXT( "   XoffLim =           " ) << XoffLim           << TEXT( "\n" );
   dump_context << TEXT( "   ByteSize =          " ) << ByteSize          << TEXT( "\n" );
   dump_context << TEXT( "   Parity =            " ) << Parity            << TEXT( " (" );

   switch( Parity )
   {
      case EVENPARITY:

         dump_context << TEXT( "EVENPARITY" );
         break;

      case MARKPARITY:

         dump_context << TEXT( "MARKPARITY" );
         break;

      case NOPARITY:

         dump_context << TEXT( "NOPARITY" );
         break;

      case ODDPARITY:

         dump_context << TEXT( "ODDPARITY" );
         break;

      case SPACEPARITY:

         dump_context << TEXT( "SPACEPARITY" );
         break;
   }

   dump_context << TEXT( ")\n" );

   dump_context << TEXT( "   StopBits =          " ) << StopBits          << TEXT( " (" );

   switch( StopBits )
   {
      case ONESTOPBIT:

         dump_context << TEXT( "ONESTOPBIT" );
         break;

      case ONE5STOPBITS:

         dump_context << TEXT( "ONE5STOPBITS" );
         break;

      case TWOSTOPBITS:

         dump_context << TEXT( "TWOSTOPBITS" );
         break;
   }

   dump_context << TEXT( ")\n" );

   dump_context << TEXT( "   XonChar =           " ) << XonChar           << TEXT( "\n" );
   dump_context << TEXT( "   XoffChar =          " ) << XoffChar          << TEXT( "\n" );
   dump_context << TEXT( "   ErrorChar =         " ) << ErrorChar         << TEXT( "\n" );
   dump_context << TEXT( "   EofChar =           " ) << EofChar           << TEXT( "\n" );
   dump_context << TEXT( "   EvtChar =           " ) << EvtChar           << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

CDeviceControlBlock& CDeviceControlBlock::operator=( const CDeviceControlBlock& source )
{
   Copy( source );
   return( *this );
}

CDeviceControlBlock& CDeviceControlBlock::operator=( const DCB& source )
{
   Copy( source );
   return( *this );
}

// End of source
