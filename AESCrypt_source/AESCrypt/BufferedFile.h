/*
 *  BufferedFile.cpp
 *
 *  Copyright (C) 2006, 2008, 2013
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved.
 *
 *  This module defines a buffered file I/O class for reading and
 *  writing sequential files.  Buffering is necessary for better
 *  performance when reading or writing to network storage devices.
 *
 */

#pragma once

#define BUFFER_FILE_SIZE    8192

class BufferedFile {

    private:
        HANDLE          file_handle;
        DWORD           io_return_code;
        bool            write_mode;
        bool            reached_eof;
        unsigned char   buffer[BUFFER_FILE_SIZE];
        unsigned char   *left, *right;

        inline bool isClosed();
        bool FlushBuffer();

    public:
        BufferedFile();
        ~BufferedFile();

        DWORD OpenFile( const TCHAR *filename,
                        bool        write,
                        DWORD       dwCreationDisposition);

        DWORD ReadFile( LPVOID  lpBuffer,
                        DWORD   nNumberOfBytesToRead,
                        LPDWORD lpNumberOfBytesRead);

        DWORD FileSize( PLARGE_INTEGER file_size);

        DWORD WriteFile(LPCVOID lpBuffer,
                        DWORD   nNumberOfBytesToWrite,
                        LPDWORD lpNumberOfBytesWritten);

        DWORD CloseFile();

};
