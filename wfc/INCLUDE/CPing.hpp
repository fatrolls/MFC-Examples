#if ! defined( PING_CLASS_HEADER )

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
** $Workfile: cping.hpp $
** $Revision: 9 $
** $Modtime: 1/04/00 4:52a $
*/

#define PING_CLASS_HEADER

#if ! defined( IP_EXPORT_INCLUDED )

#define IP_EXPORT_INCLUDED

/*NOINC*/

//
// IP types
//
typedef unsigned long   IPAddr;     // An IP address.
typedef unsigned long   IPMask;     // An IP subnet mask.
typedef unsigned long   IP_STATUS;  // Status code returned from IP APIs.

/*INC*/
#if 0
struct ip_option_information {
    unsigned char      Ttl;             // Time To Live
    unsigned char      Tos;             // Type Of Service
    unsigned char      Flags;           // IP header flags
    unsigned char      OptionsSize;     // Size in bytes of options data
    unsigned char FAR *OptionsData;     // Pointer to options data
}; /* ip_option_information */

struct icmp_echo_reply {
    IPAddr                         Address;         // Replying address
    unsigned long                  Status;          // Reply status
    unsigned long                  RoundTripTime;   // RTT in milliseconds
    unsigned short                 DataSize;        // Echo data size
    unsigned short                 Reserved;        // Reserved for system use
    void FAR                      *Data;            // Pointer to the echo data
    struct ip_option_information   Options;         // Reply options
}; /* icmp_echo_reply */

/*NOINC*/

//
// IP Options structure for use by the application-level ICMP interface.
//

typedef struct ip_option_information IP_OPTION_INFORMATION,
                                     FAR *PIP_OPTION_INFORMATION;

typedef struct icmp_echo_reply ICMP_ECHO_REPLY, FAR *PICMP_ECHO_REPLY;
#endif // 0
/*INC*/

//
// IP status codes returned to transports and user IOCTLs.
//

#define IP_STATUS_BASE              11000

#define IP_SUCCESS                  0
#define IP_BUF_TOO_SMALL            (IP_STATUS_BASE + 1)
#define IP_DEST_NET_UNREACHABLE     (IP_STATUS_BASE + 2)
#define IP_DEST_HOST_UNREACHABLE    (IP_STATUS_BASE + 3)
#define IP_DEST_PROT_UNREACHABLE    (IP_STATUS_BASE + 4)
#define IP_DEST_PORT_UNREACHABLE    (IP_STATUS_BASE + 5)
#define IP_NO_RESOURCES             (IP_STATUS_BASE + 6)
#define IP_BAD_OPTION               (IP_STATUS_BASE + 7)
#define IP_HW_ERROR                 (IP_STATUS_BASE + 8)
#define IP_PACKET_TOO_BIG           (IP_STATUS_BASE + 9)
#define IP_REQ_TIMED_OUT            (IP_STATUS_BASE + 10)
#define IP_BAD_REQ                  (IP_STATUS_BASE + 11)
#define IP_BAD_ROUTE                (IP_STATUS_BASE + 12)
#define IP_TTL_EXPIRED_TRANSIT      (IP_STATUS_BASE + 13)
#define IP_TTL_EXPIRED_REASSEM      (IP_STATUS_BASE + 14)
#define IP_PARAM_PROBLEM            (IP_STATUS_BASE + 15)
#define IP_SOURCE_QUENCH            (IP_STATUS_BASE + 16)
#define IP_OPTION_TOO_BIG           (IP_STATUS_BASE + 17)
#define IP_BAD_DESTINATION          (IP_STATUS_BASE + 18)

//
// The next group are status codes passed up on status indications.
//

#define IP_ADDR_DELETED             (IP_STATUS_BASE + 19)
#define IP_SPEC_MTU_CHANGE          (IP_STATUS_BASE + 20)
#define IP_MTU_CHANGE               (IP_STATUS_BASE + 21)

#define IP_GENERAL_FAILURE          (IP_STATUS_BASE + 50)

#define MAX_IP_STATUS               IP_GENERAL_FAILURE

#define IP_PENDING                  (IP_STATUS_BASE + 255)

//
// IP header flags
//
#define IP_FLAG_DF      0x2         // Don't fragment this packet.

//
// IP Option Types
//
#define IP_OPT_EOL      0                       // End of list option
#define IP_OPT_NOP      1                       // No operation
#define IP_OPT_SECURITY 0x82                    // Security option.
#define IP_OPT_LSRR     0x83                    // Loose source route.
#define IP_OPT_SSRR     0x89                    // Strict source route.
#define IP_OPT_RR       0x7                     // Record route.
#define IP_OPT_TS       0x44                    // Timestamp.
#define IP_OPT_SID      0x88                    // Stream ID (obsolete)
#define MAX_OPT_SIZE    40

#endif // IP_EXPORT_INCLUDED

// === Structures Required by the ICMP.DLL ====================================

typedef struct {
   unsigned char Ttl;                                           // Time To Live
   unsigned char Tos;                                        // Type Of Service
   unsigned char Flags;                                      // IP header flags
   unsigned char OptionsSize;                  // Size in bytes of options data
   unsigned char *OptionsData;                       // Pointer to options data
} IP_OPTION_INFORMATION, * PIP_OPTION_INFORMATION;

typedef struct {
   DWORD Address;                                           // Replying address
   unsigned long  Status;                                       // Reply status
   unsigned long  RoundTripTime;                         // RTT in milliseconds
   unsigned short DataSize;                                   // Echo data size
   unsigned short Reserved;                          // Reserved for system use
   void *Data;                                      // Pointer to the echo data
   IP_OPTION_INFORMATION Options;                              // Reply options
} IP_ECHO_REPLY, * PIP_ECHO_REPLY;

#if ! defined( _ICMP_INCLUDED_ )

#define _ICMP_INCLUDED_

//
// Exported Routines.
//

//++
//
// Routine Description:
//
//     Opens a handle on which ICMP Echo Requests can be issued.
//
// Arguments:
//
//     None.
//
// Return Value:
//
//     An open file handle or INVALID_HANDLE_VALUE. Extended error information
//     is available by calling GetLastError().
//
//--

HANDLE
WINAPI
IcmpCreateFile(
    VOID
    );


//++
//
// Routine Description:
//
//     Closes a handle opened by ICMPOpenFile.
//
// Arguments:
//
//     IcmpHandle  - The handle to close.
//
// Return Value:
//
//     TRUE if the handle was closed successfully, otherwise FALSE. Extended
//     error information is available by calling GetLastError().
//
//--

BOOL
WINAPI
IcmpCloseHandle(
    HANDLE  IcmpHandle
    );

//++
//
// Routine Description:
//
//     Sends an ICMP Echo request and returns one or more replies. The
//     call returns when the timeout has expired or the reply buffer
//     is filled.
//
// Arguments:
//
//     IcmpHandle           - An open handle returned by ICMPCreateFile.
//
//     DestinationAddress   - The destination of the echo request.
//
//     RequestData          - A buffer containing the data to send in the
//                            request.
//
//     RequestSize          - The number of bytes in the request data buffer.
//
//     RequestOptions       - Pointer to the IP header options for the request.
//                            May be NULL.
//
//     ReplyBuffer          - A buffer to hold any replies to the request.
//                            On return, the buffer will contain an array of
//                            ICMP_ECHO_REPLY structures followed by options
//                            and data. The buffer should be large enough to
//                            hold at least one ICMP_ECHO_REPLY structure
//                            and 8 bytes of data - this is the size of
//                            an ICMP error message.
//
//     ReplySize            - The size in bytes of the reply buffer.
//
//     Timeout              - The time in milliseconds to wait for replies.
//
// Return Value:
//
//     Returns the number of replies received and stored in ReplyBuffer. If
//     the return value is zero, extended error information is available
//     via GetLastError().
//
//--

DWORD
WINAPI
IcmpSendEcho(
    HANDLE                   IcmpHandle,
    IPAddr                   DestinationAddress,
    LPVOID                   RequestData,
    WORD                     RequestSize,
    PIP_OPTION_INFORMATION   RequestOptions,
    LPVOID                   ReplyBuffer,
    DWORD                    ReplySize,
    DWORD                    Timeout
    );


#endif // _ICMP_INCLUDED_

typedef HANDLE (WINAPI *ICMP_OPEN_FUNCTION)( VOID );
typedef VOID (WINAPI *ICMP_CLOSE_FUNCTION)( HANDLE );
typedef DWORD (WINAPI *ICMP_SEND_ECHO_FUNCTION)( HANDLE, IPAddr, LPVOID, WORD, PIP_OPTION_INFORMATION, LPVOID, DWORD, DWORD );

class CPingResults
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CPingResults )
#endif // WFC_NO_SERIALIZATION

   public:

      CPingResults();
      CPingResults( const CPingResults&   source );
      CPingResults( const CPingResults *  source );
      CPingResults( const IP_ECHO_REPLY&  source );
      CPingResults( const IP_ECHO_REPLY * source );
     ~CPingResults();

      CString Address;
      DWORD   RoundTripTimeInMilliseconds;
      BYTE    TimeToLive;

      virtual void Copy( const CPingResults&   source );
      virtual void Copy( const CPingResults *  source );
      virtual void Copy( const IP_ECHO_REPLY&  source );
      virtual void Copy( const IP_ECHO_REPLY * source );
      virtual void Empty( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

      virtual CPingResults& operator = ( const CPingResults& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )
      virtual void Dump( CDumpContext& dump_context ) const;
#endif // _DEBUG
};

class CPing : public CSimpleSocket
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CPing( const CPing& ) {};
      CPing& operator=( const CPing& ) { return( *this ); };

   protected:

      HMODULE m_ICMP_DLL_Instance;

      HANDLE (WINAPI *m_Open)    ( VOID );
      VOID   (WINAPI *m_Close)   ( HANDLE );
      DWORD  (WINAPI *m_SendEcho)( HANDLE, IPAddr, LPVOID, WORD, PIP_OPTION_INFORMATION, LPVOID, DWORD, DWORD );

   public:

      CPing();
      virtual ~CPing();

      virtual void ConvertErrorToString( DWORD error_code, CString& meaning ) const;
      virtual BOOL Open( void );

#if ! defined( WFC_STL )
      virtual BOOL Open( const char *channel_name, UINT port_number = 23, CFileException* pError = NULL );
#else // WFC_STL
      virtual BOOL Open( const char *channel_name, UINT port_number = 23 );
#endif // WFC_STL
      
      virtual DWORD Ping( const CString& name_or_address, CPingResults * results_p = NULL, short desired_time_to_live = 255 );
};

#endif // PING_CLASS_HEADER
