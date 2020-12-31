#if ! defined( WFC_TRACE_CLASS_HEADER )

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
** $Workfile: WFCTrace.hpp $
** $Revision: 15 $
** $Modtime: 3/18/00 7:33a $
*/

#define WFC_TRACE_CLASS_HEADER

#if defined( _DEBUG )

#define WFCTRACEINIT( string )           CWfcTrace ___trace( string, BIT_0 );
#define WFCLTRACEINIT( string )          CWfcTrace ___trace( string, BIT_31 );
#define WFCTRACEINITLEVEL( string, x )   CWfcTrace ___trace( string, x );
#define WFCTRACE( string )               { ___trace.Output( string );               }
#define WFCTRACEVAL( string, value )     { ___trace.Output( string, value );        }
#define WFCTRACEVARIANT( string, value ) { ___trace.OutputVariant( string, value ); }
#define WFCTRACEBINVAL( string, value )  { ___trace.OutputBinary( string, value );  }
#define WFCTRACEDUMP( variable )         { ___trace.Output( #variable, variable );  }
#define WFCTRACEERROR( error_code )      { ___trace.ReportError( error_code );      }
#define WFCTRACEON()                     { CWfcTrace::TraceOn();                    }
#define WFCTRACEOFF()                    { CWfcTrace::TraceOff();                   }
#define WFCTRACEALLON()                  { CWfcTrace::TraceAllOn();                 }
#define WFCTRACEALLOFF()                 { CWfcTrace::TraceAllOff();                }
#define WFCTRACELEVELON( x )             { CWfcTrace::TraceLevelOn( x );            }
#define WFCTRACELEVELOFF( x )            { CWfcTrace::TraceLevelOff( x );           }

#else

#define WFCTRACEINIT( string )           {;}
#define WFCLTRACEINIT( string )          {;}
#define WFCTRACEINITLEVEL( string, x )   {;}
#define WFCTRACE( string )               {;}
#define WFCTRACEVAL( string, value )     {;}
#define WFCTRACEVARIANT( string, value ) {;}
#define WFCTRACEBINVAL( string, value )  {;}
#define WFCTRACEDUMP( variable )         {;}
#define WFCTRACEERROR( error_code )      {;}
#define WFCTRACEON()                     {;}
#define WFCTRACEOFF()                    {;}
#define WFCTRACEALLON()                  {;}
#define WFCTRACEALLOFF()                 {;}
#define WFCTRACELEVELON( x )             {;}
#define WFCTRACELEVELOFF( x )            {;}

#endif // _DEBUG

class CWfcTrace
#if ! defined( WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
   private:

      /*
      ** Don't allow canonical behavior
      */

      CWfcTrace(){};
      CWfcTrace( const CWfcTrace& ){};
      CWfcTrace& operator=( CWfcTrace& ){ return( *this ); };

   protected:

      CString m_FunctionName;
      DWORD   m_TracingLevel;

      void m_Indent( void ) const;

   public:

      static int   Indent;
      static DWORD Levels;
      static BOOL  Tracing;

      CWfcTrace( const CString& function_name, DWORD tracing_level );

      virtual ~CWfcTrace();

      static  void TraceAllOn( void );
      static  void TraceAllOff( void );
      static  void TraceLevelOn( DWORD level );
      static  void TraceLevelOff( DWORD level );
      static  void TraceOn( void );
      static  void TraceOff( void );
      virtual void Output( const CString& message ) const;
      virtual void Output( const CString& message, const int integer      ) const;
      virtual void Output( const CString& message, const UINT integer     ) const;
      virtual void Output( const CString& message, const long a_long      ) const;
      virtual void Output( const CString& message, const ULONG a_long     ) const;
      virtual void Output( const CString& message, const LONGLONG a_long  ) const;
      virtual void Output( const CString& message, const ULONGLONG a_long ) const;
      virtual void Output( const CString& message, const double a_double  ) const;
      virtual void Output( const CString& message, const CString& string  ) const;
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Output( const CString& message, const CObject * object ) const;
#endif // WFC_NO_SERIALIZATION
      virtual void Output( const CString& message, const VOID * pointer   ) const;
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Output( const CString& message, const CObject& object  ) const;
#endif // WFC_NO_SERIALIZATION
      virtual void Output( const CString& message, const LARGE_INTEGER& value ) const;
      virtual void Output( const CString& message, const ULARGE_INTEGER& value ) const;
      virtual void Output( const CString& message, const RECT& value ) const;
      virtual void Output( const CString& message, const POINT& value ) const;
      virtual void Output( const CString& message, const SIZE& value ) const;
      virtual void OutputBinary( const CString& message, const ULONG a_long ) const;
      virtual void OutputVariant( const CString& message, const VARIANT& value ) const;
      virtual void OutputVariant( const CString& message, const VARIANT* value ) const;
      virtual void ReportError( DWORD error_code );
};

#endif // WFC_TRACE_CLASS_HEADER
