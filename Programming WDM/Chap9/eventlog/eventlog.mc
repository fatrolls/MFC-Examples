;// Message definition file for EventLog driver
;// Copyright (C) 1999 by Walter Oney
;// All rights reserved

MessageIdTypedef = NTSTATUS

SeverityNames = (
	Success			= 0x0:STATUS_SEVERITY_SUCCESS
	Informational	= 0x1:STATUS_SEVERITY_INFORMATIONAL
	Warning			= 0x2:STATUS_SEVERITY_WARNING
	Error			= 0x3:STATUS_SEVERITY_ERROR
	)

FacilityNames = (
	System			= 0x0
	Eventlog		= 0x2A:FACILITY_EVENTLOG_ERROR_CODE
	)

LanguageNames = (
	English			= 0x0409:msg00001
	German			= 0x0407:msg00002
	French			= 0x040C:msg00003
	)

MessageId = 0x0001
Facility = Eventlog
Severity = Informational
SymbolicName = EVENTLOG_MSG_TEST
Language = English
%2 said, "Hello, world!"
.
Language = German
%2 hat gesagt, «Wir sind nicht mehr im Kansas!»
.
Language = French
%2 a dit, «Mon chien a mangé mon devoir!»
.
