#if ! defined( SERVICE_APPLICATION_CLASS_HEADER )

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
** Copyright, 1998, Samuel R. Blackburn
**
** $Workfile: CServiceApplication.hpp $
** $Revision: 1 $
** $Modtime: 7/20/98 6:41p $
*/

#define SERVICE_APPLICATION_CLASS_HEADER

typedef void (*SHOW_USAGE_ROUTINE)( LPCTSTR );
typedef void (*SET_DEFAULTS_ROUTINE)( void );

class CServiceApplication
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CServiceApplication( const CServiceApplication& ) {};
      CServiceApplication& operator=( const CServiceApplication& ) { return( *this ); };

   protected:

      virtual int m_Main( int number_of_command_line_arguments,
                          LPCTSTR command_line_arguments[],
                          LPCTSTR service_name,
                          LPCTSTR friendly_service_name,
                          LPCTSTR executable_path,
                          DWORD   installation_configuration,
                          LPTHREAD_START_ROUTINE worker_thread,
                          SHOW_USAGE_ROUTINE show_usage,
                          SET_DEFAULTS_ROUTINE set_defaults );

   public:

      CServiceApplication( int number_of_command_line_arguments,
                           LPCTSTR command_line_arguments[],
                           LPCTSTR service_name,
                           LPCTSTR friendly_service_name,
                           LPCTSTR executable_path,
                           LPTHREAD_START_ROUTINE worker_thread,
                           SHOW_USAGE_ROUTINE show_usage = NULL,
                           SET_DEFAULTS_ROUTINE set_defaults = NULL,
                           DWORD   installation_configuration = SERVICE_DEMAND_START );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CServiceApplication( void );
};

#endif // SERVICE_APPLICATION_CLASS_HEADER
