/*
 *  BufferedFile.cpp
 *
 *  Copyright (C) 2006, 2008, 2013
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved.
 *
 *  This module implements a buffered file I/O class for reading and
 *  writing sequential files.  Buffering is necessary for better
 *  performance when reading or writing to network storage devices.
 *
 */

#include "stdafx.h"
#include "BufferedFile.h"

/*
 * Constructor
 */
BufferedFile::BufferedFile()
{
    file_handle = INVALID_HANDLE_VALUE;
    io_return_code = ERROR_SUCCESS;
}

/*
 * Destructor
 */
BufferedFile::~BufferedFile()
{
    CloseFile();
}

/*
 * OpenFile
 */
DWORD BufferedFile::OpenFile(   const TCHAR *filename,
                                bool write,
                                DWORD dwCreationDisposition)
{
    // If a file is already open, report that we have too many open files
    if (!isClosed())
    {
        return ERROR_OPEN_FAILED;
    }

    // Initialize member variables
    write_mode = write;
    left = right = buffer;
    reached_eof = false;
    io_return_code = ERROR_SUCCESS;

    file_handle = CreateFile(   filename,
                                (write_mode == true) ?
                                    GENERIC_WRITE : GENERIC_READ,
                                (write_mode == true) ?
                                    0 : FILE_SHARE_READ,
                                NULL,
                                dwCreationDisposition,
                                FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN,
                                NULL);

    if (file_handle == INVALID_HANDLE_VALUE)
    {
        io_return_code = GetLastError();
    }

    return io_return_code;
}

/*
 * isClosed
 */
inline bool BufferedFile::isClosed()
{
    return (file_handle == INVALID_HANDLE_VALUE);
}

/*
 * ReadFile
 */
DWORD BufferedFile::ReadFile(   LPVOID lpBuffer,
                                DWORD nNumberOfBytesToRead,
                                LPDWORD lpNumberOfBytesRead)
{
    DWORD return_code = ERROR_SUCCESS;
    unsigned char   *user_buffer = (unsigned char *)lpBuffer;
    DWORD           bytes_read;

    *lpNumberOfBytesRead = 0;
    
    // If the file is closed or open for writing, report error
    if (isClosed() || (write_mode == true))
    {
        return ERROR_INVALID_HANDLE;
    }

    while(*lpNumberOfBytesRead < nNumberOfBytesToRead)
    {
        // If there is data in the internal buffer, copy the bytes
        if (left < right)
        {
            *user_buffer = *left;
            left++;
            user_buffer++;
            (*lpNumberOfBytesRead)++;
        }
        else
        {
            bytes_read = 0;

            // If the previous file operation resulted in an error,
            // then return that error.  If the EOF was reached, then
            // the return code will be ERROR_HANDLE_EOF.
            if ((io_return_code != ERROR_SUCCESS) || (reached_eof == true))
            {
                // If the io_return_code shows success, then the only
                // reason we would reach this point is because we had
                // previously reached the end of the file.  Set the
                // io_return_code appropriately now.
                if (io_return_code == ERROR_SUCCESS)
                {
                    return_code = ERROR_HANDLE_EOF;
                }
                else
                {
                    return_code = io_return_code;
                }
                break;
            }
            else
            {
                // Try to fill the internal buffer with more
                // octets from the open file.
                if (!::ReadFile(file_handle,
                                buffer,
                                BUFFER_FILE_SIZE,
                                &bytes_read,
                                NULL))
                {
                    io_return_code = GetLastError();

                    // End of file is "normal", so let's not report
                    // this result until we try to read subsequent
                    // octets from the file.
                    if (io_return_code == ERROR_HANDLE_EOF)
                    {
                        reached_eof = true;
                        io_return_code = ERROR_SUCCESS;
                    }
                }
            }

            /* Adjust the internal buffer pointers */
            left = buffer;
            right = buffer + bytes_read;
        }
    }

    return return_code;
}

/*
 * FileSize
 */
DWORD BufferedFile::FileSize(PLARGE_INTEGER file_size)
{
    DWORD return_code = ERROR_SUCCESS;

    // If the file is closed or open for writing, report error
    if (isClosed() || (write_mode == true))
    {
        return ERROR_INVALID_HANDLE;
    }

    if (!::GetFileSizeEx(file_handle, file_size))
    {
        return_code = GetLastError();
    }

    return return_code;
}

/*
 * WriteFile
 */
DWORD BufferedFile::WriteFile(  LPCVOID lpBuffer,
                                DWORD nNumberOfBytesToWrite,
                                LPDWORD lpNumberOfBytesWritten)
{
    unsigned char *user_buffer = (unsigned char *)lpBuffer;

    *lpNumberOfBytesWritten = 0;

    // If the file is closed or open for reading, report error
    if (isClosed() || (write_mode == false))
    {
        return ERROR_INVALID_HANDLE;
    }

    while(*lpNumberOfBytesWritten < nNumberOfBytesToWrite)
    {
        *right = *user_buffer;
        user_buffer++;
        right++;
        (*lpNumberOfBytesWritten)++;

        if (right - left > BUFFER_FILE_SIZE)
        {
            if (!FlushBuffer())
            {
                io_return_code = GetLastError();
                break;
            }
        }
    }

    return io_return_code;
}

/*
 * CloseFile
 */
DWORD BufferedFile::CloseFile()
{
    DWORD return_code = ERROR_SUCCESS;

    if (isClosed())
    {
        return ERROR_SUCCESS;
    }

    if (write_mode == true)
    {
        if (!FlushBuffer())
        {
            return_code = GetLastError();
        }
    }

    if ((!CloseHandle(file_handle)) && (return_code == ERROR_SUCCESS))
    {
        return_code = GetLastError();
    }

    file_handle = INVALID_HANDLE_VALUE;

    return return_code;
}
 
/*
 * FlushBuffer
 */
bool BufferedFile::FlushBuffer()
{
    DWORD bytes_written;
    DWORD bytes_to_write;

    bytes_to_write = (DWORD) (right - left);

    if (bytes_to_write > 0)
    {
        if (!::WriteFile(   file_handle,
                            buffer,
                            bytes_to_write,
                            &bytes_written,
                            NULL))
        {
            right = buffer;
            return false;
        }
    }

    right = buffer;
    return true;
}

