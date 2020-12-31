/*
 *  ErrorHandling.h
 *
 *  Copyright (C) 2007, 2008, 2013
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved.
 *
 *  This file defines various error handling and reporting functions.
 *
 */

/* Global Error Reporting Function */
void ReportError(   std::basic_string<TCHAR> message,
					DWORD reason);

/*
 * This class exists to allow us to easily bail out when
 * we have system I/O issues.
 */
class SystemErrorException
{
    public:
        DWORD                       Reason;
        std::basic_string<TCHAR>    Message;

        SystemErrorException(   std::basic_string<TCHAR> message,
                                DWORD reason = 0)
        {
            Reason = reason;
            Message = message;
        }

        SystemErrorException()
        {
            Reason = GetLastError();
        }
};
