/***********************************************
Email Server Information
************************************************/

Registry Entries 

REG_SZ		RootPath		root path for the que and user mail    

REG_DWORD	NumberDomainNames
REG_SZ		DomainNameXXX	local domain name(s), where XXX is a number 
							starting from 0    

REG_DWORD	NumberDNSNames	
REG_SZ		DNSNameXXX		Name server name(s), whre XXX starts from 0

REG_DWORD	MaxOut			max. mail out at once
REG_DWORD	MaxIn			max. mail to receive at once

REG_DWORD	MaxRetries		max. times to try and resend the mail
REG_DWORD	RetryInterval	seconds between retries

REG_DWORD	NumberUsers		number of users in the system
REG_SZ		XXXUser			username where XXX starts from 0
REG_SZ		XXXPassword		password where XXX starts from 0
REG_DWORD	XXXNumberEmail	Addresses	number of email addresses 
							where XXX starts from 0
REG_SZ		XXXEmailAddressYYY		email address(s) where XXX starts from 0  
									YYY starts from 0




Que header format:

time_t	last time written
DWORD	retryCount
DWORD	toLength - includes termination
LPSTR	to
DWORD	fromLength  - includes termination
LPSTR	from
DWORD	returnMail - 0 not returning 1- invalid domain 2-invalid user 3 - max retires
-The message follows immediatly after the header


Directory structure

ROOTPATH  - email server directory

ROOTPATH\QUE	- outbound que directory

ROOTPATH\XXX	- user directory, where XXX is the user number which
				  matches the user entry in the registry

the names of the files in the directories are use numbers only

