#if ! defined( MESSAGES_HEADER_FILE )

#define MESSAGES_HEADER_FILE

//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//
#define FACILITY_SYSTEM                  0x0
#define FACILITY_STUBS                   0x3
#define FACILITY_RUNTIME                 0x2
#define FACILITY_IO_ERROR_CODE           0x4


//
// Define the severity codes
//
#define STATUS_SEVERITY_WARNING          0x2
#define STATUS_SEVERITY_SUCCESS          0x0
#define STATUS_SEVERITY_INFORMATIONAL    0x1
#define STATUS_SEVERITY_ERROR            0x3


//
// MessageId: MSG_WATCHDOG_SUCCESSFULLY_INSTALLED
//
// MessageText:
//
//  WatchDog successfully installed by %1.
//
#define MSG_WATCHDOG_SUCCESSFULLY_INSTALLED ((DWORD)0x40000001L)

//
// MessageId: MSG_WATCHDOG_SUCCESSFULLY_REMOVED
//
// MessageText:
//
//  WatchDog successfully removed by %1.
//
#define MSG_WATCHDOG_SUCCESSFULLY_REMOVED ((DWORD)0x40000002L)

//
// MessageId: MSG_WATCHDOG_ERROR_CODE
//
// MessageText:
//
//  Error %1, %2
//
#define MSG_WATCHDOG_ERROR_CODE          ((DWORD)0xC0000003L)

//
// MessageId: MSG_WATCHDOG_SERVICE_STARTED
//
// MessageText:
//
//  Service started.
//
#define MSG_WATCHDOG_SERVICE_STARTED     ((DWORD)0x40000004L)

//
// MessageId: MSG_WATCHDOG_SERVICE_STOPPED
//
// MessageText:
//
//  Service stopped
//
#define MSG_WATCHDOG_SERVICE_STOPPED     ((DWORD)0x40000005L)

//
// MessageId: MSG_WATCHDOG_UNEXPECTED_ERROR
//
// MessageText:
//
//  Unexpected error at line %1 of %2, %3
//
#define MSG_WATCHDOG_UNEXPECTED_ERROR    ((DWORD)0xC0000006L)

//
// MessageId: MSG_WATCHDOG_RESTARTING_SERVICE
//
// MessageText:
//
//  Restarting service "%1"
//
#define MSG_WATCHDOG_RESTARTING_SERVICE  ((DWORD)0x40000007L)

//
// MessageId: MSG_CANT_CONNECT_TO_REGISTRY
//
// MessageText:
//
//  Can't connect to registry %1 because %2
//
#define MSG_CANT_CONNECT_TO_REGISTRY     ((DWORD)0xC0000008L)

//
// MessageId: MSG_CANT_CREATE_REGISTRY_KEY
//
// MessageText:
//
//  Can't create registry key %1 because %2
//
#define MSG_CANT_CREATE_REGISTRY_KEY     ((DWORD)0xC0000009L)

//
// MessageId: MSG_CANT_SET_REGISTRY_ENTRY
//
// MessageText:
//
//  Can't set registry entry %1 because %2
//
#define MSG_CANT_SET_REGISTRY_ENTRY      ((DWORD)0xC000000AL)

//
// MessageId: MSG_CANT_CREATE_SERVICE
//
// MessageText:
//
//  Call to CreateService() failed with %1 at line %2 of %3
//
#define MSG_CANT_CREATE_SERVICE          ((DWORD)0xC000000BL)


 #endif // MESSAGES_HEADER_FILE
