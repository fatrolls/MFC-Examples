;#if ! defined( MESSAGES_HEADER_FILE )
;
;#define MESSAGES_HEADER_FILE
;

MessageIdTypedef=DWORD

SeverityNames=(Success=0x0:STATUS_SEVERITY_SUCCESS
               Informational=0x1:STATUS_SEVERITY_INFORMATIONAL
               Warning=0x2:STATUS_SEVERITY_WARNING
               Error=0x3:STATUS_SEVERITY_ERROR
              )

FacilityNames=(System=0x0:FACILITY_SYSTEM
               Runtime=0x2:FACILITY_RUNTIME
               Stubs=0x3:FACILITY_STUBS
               Io=0x4:FACILITY_IO_ERROR_CODE
              )

MessageId=0x1
Severity=Informational
Facility=Application
SymbolicName=MSG_PINGER_SUCCESSFULLY_INSTALLED
Language=English
Pingersuccessfully installed by %1.
.

MessageId=0x2
Severity=Informational
Facility=Application
SymbolicName=MSG_PINGER_SUCCESSFULLY_REMOVED
Language=English
Pinger successfully removed by %1.
.

MessageId=0x3
Severity=Error
Facility=Application
SymbolicName=MSG_PINGER_ERROR_CODE
Language=English
Error %1, %2
.

MessageId=0x4
Severity=Informational
Facility=Application
SymbolicName=MSG_PINGER_SERVICE_STARTED
Language=English
Service started.
.

MessageId=0x5
Severity=Informational
Facility=Application
SymbolicName=MSG_PINGER_SERVICE_STOPPED
Language=English
Service stopped
.

MessageId=0x6
Severity=Error
Facility=Application
SymbolicName=MSG_PINGER_UNEXPECTED_ERROR
Language=English
Unexpected error at line %1 of %2, %3
.

MessageId=0x7
Severity=Informational
Facility=Application
SymbolicName=MSG_PINGER_RESTARTING_SERVICE
Language=English
Restarting service "%1"
.

MessageId=0x8
Severity=Error
Facility=Application
SymbolicName=MSG_CANT_CONNECT_TO_REGISTRY
Language=English
Can't connect to registry %1 because %2
.

MessageId=0x9
Severity=Error
Facility=Application
SymbolicName=MSG_CANT_CREATE_REGISTRY_KEY
Language=English
Can't create registry key %1 because %2
.

MessageId=0xA
Severity=Error
Facility=Application
SymbolicName=MSG_CANT_SET_REGISTRY_ENTRY
Language=English
Can't set registry entry %1 because %2
.

MessageId=0xB
Severity=Error
Facility=Application
SymbolicName=MSG_CANT_CREATE_SERVICE
Language=English
Call to CreateService() failed with %1 at line %2 of %3
.

MessageId=0xC
Severity=Error
Facility=Application
SymbolicName=MSG_CANT_CREATE_TIMER_THREAD
Language=English
Can't create the timer thread, CreateThread() failed with %1
.

MessageId=0xD
Severity=Error
Facility=Application
SymbolicName=MSG_CANT_CREATE_TIMER_EVENT
Language=English
Can't create the timer event, CreateEvent() failed with %1
.

;
; #endif // MESSAGES_HEADER_FILE
