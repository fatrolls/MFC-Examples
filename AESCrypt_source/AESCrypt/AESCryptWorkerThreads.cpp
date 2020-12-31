/*
 *  AESCryptWorkerThreads.cpp
 *
 *  Copyright (C) 2006, 2007, 2008, 2013
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved.
 *
 *  This module implements the AESCryptWorkerThreads class, which is
 *  responsible for all background encryption and decryption functions.
 *
 */

#include "stdafx.h"
#include "AESCryptWorkerThreads.h"
#include "PasswdDialog.h"
#include "ErrorHandling.h"
#include "BufferedFile.h"
#include "ProgressDialog.h"
#include "version.h"
#include <time.h>

extern "C" {
#include "aes.h"
#include "sha256.h"
}

#define FOOTPRINT_V0  53
#define FOOTPRINT_V1  134
#define FOOTPRINT_V2  136

/*
 * Function prototype used later
 */
DWORD WINAPI ThreadInit(LPVOID lpParameter);

/*
 * AESCryptWorkerThreads Constructor
 */
AESCryptWorkerThreads::AESCryptWorkerThreads()
{
    InitializeCriticalSection(&Critical_Section);
    Thread_Count = 0;
}

/*
 * AESCryptWorkerThreads Destructor
 */
AESCryptWorkerThreads::~AESCryptWorkerThreads()
{
    HANDLE handle;

    // Wait for any active threads to complete
    // In theory, this block of code should never run, since
    // the IsBusy() call should be made and the class should
    // not be destroyed.  But, just in case...
    while(1)
    {
        EnterCriticalSection(&Critical_Section);
        if (Thread_Count == 0)
        {
            LeaveCriticalSection(&Critical_Section);
            break;
        }
        LeaveCriticalSection(&Critical_Section);
        Sleep(200);
    }

    // Release any thread handles not already released
    while (!Terminated_Threads.empty())
    {
        handle = Terminated_Threads.front();
        WaitForSingleObject(&handle, INFINITE);
        CloseHandle(handle);
        Terminated_Threads.pop_front();
    }
    DeleteCriticalSection(&Critical_Section);
}

/*
 * IsBusy()
 *
 * Are there worker threads working?
 */
bool AESCryptWorkerThreads::IsBusy()
{
    bool busy = false;

    EnterCriticalSection(&Critical_Section);
    if (Thread_Count > 0)
    {
        busy = true;
    }
    LeaveCriticalSection(&Critical_Section);

    return busy;
}

/*
 * BeginWork
 *
 */
void AESCryptWorkerThreads::ProcessFiles(   StringList *file_list,
                                            bool encrypt)
{
    PasswdDialog dlg;

    // Prompt the user for a password
    if (dlg.DoModal(::GetActiveWindow(), (encrypt ? 1 : 0)) == IDOK)
    {
        if (StartThread(file_list,
                        dlg.passwd,
                        encrypt) == false)
        {
            // We were unable to start a thread, so we must clean up
            // the file list.
            delete file_list;
        }
    }
    else
    {
        // The user canceled the operation, so delete the file list
        delete file_list;
    }
}

/*
 * StartThread
 *
 * This function will start a new thread to encrypt or decrypt files
 * as requested by the user.
 */
bool AESCryptWorkerThreads::StartThread(StringList *file_list,
                                        TCHAR *passwd,
                                        bool encrypt)
{
    WorkerData *worker_data = NULL;
    DWORD thread_id;
    HANDLE thread_handle;

    try
    {
        worker_data = new WorkerData;
        worker_data->file_list = file_list;
        worker_data->encrypt = encrypt;
        _tcscpy_s(worker_data->passwd, MAX_PASSWD_LEN+1, passwd);
        worker_data->aes_crypt_worker_threads = this;
    }
    catch(...)
    {
        ::ReportError(  _T("Memory allocation failed"),
                        ERROR_SUCCESS);
    }

    if (worker_data != NULL)
    {
        // We do not want the new thread to come before we're ready.
        // We want the thread to know its handle before it starts
        // doing any real work.
        EnterCriticalSection(&Critical_Section);

        // Create the thread
        thread_handle = CreateThread(   NULL,
                                        0,
                                        ThreadInit,
                                        (LPVOID) worker_data,
                                        0,
                                        &thread_id);

        if (thread_handle != NULL)
        {
            // Let the thread know its handle
            worker_data->thread_handle = thread_handle;

            // Increase the internal thread counter
            Thread_Count++;

            // Let the thread in
            LeaveCriticalSection(&Critical_Section);

            // We successfully created the thread and handed
            // the list of files to that thread for processing.
            return true;
        }
        else
        {
            // Let go of the critical section
            LeaveCriticalSection(&Critical_Section);

            // Free the memory allocated for the worker_data structure
            delete worker_data;
            
            ::ReportError(  _T("Thread creation failed"),
                            ERROR_SUCCESS);
        }
    }

    // Returning false means something failed and caller must
    // delete the file list, since posession was not transferred
    // to a thread
    return false;
}

/*
 * ThreadEntry
 *
 * This is where the thread comes back into the class to get some work
 * done.
 */
void AESCryptWorkerThreads::ThreadEntry(WorkerData *worker_data)
{
    HANDLE          handle;

    // Try to enter the critical section
    EnterCriticalSection(&Critical_Section);

    // Release any thread handles not already released
    while (!Terminated_Threads.empty())
    {
        handle = Terminated_Threads.front();
        WaitForSingleObject(&handle, INFINITE);
        CloseHandle(handle);
        Terminated_Threads.pop_front();
    }

    // OK, we're in sync with our caller and cleaned up old threads
    LeaveCriticalSection(&Critical_Section);

    if (worker_data->encrypt)
    {
        EncryptFiles(   worker_data->file_list,
                        worker_data->passwd);
    }
    else
    {
        DecryptFiles(   worker_data->file_list,
                        worker_data->passwd);
    }

    // Delete the file list
    delete worker_data->file_list;

    // Once we are done with what we wanted to do, then decrement the
    // thread count, clean up memory, etc.
    EnterCriticalSection(&Critical_Section);
    Thread_Count--;
    Terminated_Threads.push_back(worker_data->thread_handle);
    LeaveCriticalSection(&Critical_Section);
    
    // Delete the worker data structure
    delete worker_data;
}

/*
 *  DoMessageLoop
 *
 *  This routine will service the windows message queues for the running
 *  thread so that messages are delivered and windows are properly updated.
 */
inline void AESCryptWorkerThreads::DoMessageLoop()
{
    MSG msg;

    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    { 
        TranslateMessage(&msg); 
        DispatchMessage(&msg); 
    }
}

/*
 * ThreadInit
 *
 * This is a C function where the thread starts life.
 */
DWORD WINAPI ThreadInit(LPVOID lpParameter)
{
    WorkerData *worker_data =
                        (WorkerData*) lpParameter;

    worker_data->aes_crypt_worker_threads->ThreadEntry(worker_data);

    return 0;
}

/*
 * EncryptFiles
 *
 * This function is called by the worker thread to encrypt a list of files.
 */
void AESCryptWorkerThreads::EncryptFiles(
                                StringList  *file_list,
                                TCHAR       *passwd)
{
    aes_context                 aes_ctx;
    sha256_context              sha_ctx;
    std::basic_string<TCHAR>    in_file, out_file;
    BufferedFile                in_buffered_file,
                                out_buffered_file;
    DWORD                       result_code;
    unsigned char               IV[16];
    unsigned char               buffer[32];
    unsigned char               iv_key[48];
    unsigned char               digest[32];
    LARGE_INTEGER               file_size; // 64-bit integer structure
    ULONGLONG                   bytes_left;
    int                         i, j, n;
    DWORD                       bytes_written, bytes_read;
    unsigned char               ipad[64];
    unsigned char               opad[64];
    bool                        error_abort = false;
    ProgressDialog              dlg;
    time_t                      current_time;
    clock_t                     last_clock_time;
    ULONGLONG                   last_percent, current_percent;
    HCRYPTPROV                  hProv;
    unsigned char               tag_buffer[256];


    // Passing a non-zero instructs the dialog to display
    // "Encrypting..."
    dlg.Create(NULL,1);

    // Prepare for random number generation
    if (!CryptAcquireContext(   &hProv,
                                NULL,
                                NULL,
                                PROV_RSA_FULL,
                                CRYPT_VERIFYCONTEXT))
    {
        result_code = GetLastError();
        if (GetLastError() == NTE_BAD_KEYSET)
        {
            if (!CryptAcquireContext(   &hProv,
                                        NULL,
                                        NULL,
                                        PROV_RSA_FULL,
                                        CRYPT_NEWKEYSET|CRYPT_VERIFYCONTEXT))
            {
                result_code = GetLastError();
            }
            else
            {
                result_code = ERROR_SUCCESS;
            }
        }

        if (result_code != ERROR_SUCCESS)
        {
            ::ReportError(
                _T("Could not acquire handle to crypto context"),
                0);
            error_abort = true;
        }
    }

    // Walk through the list of files encrypting each
    while(!file_list->empty() && !error_abort)
    {
        // Get the filename
        in_file = file_list->front();
        out_file = in_file + _T(".aes");

        // Reset the progress bar (default range is 0..100)
        dlg.SendDlgItemMessage( IDC_PROGRESSBAR,
                                PBM_SETPOS,
                                0,
                                0);

        // Display the file name
        dlg.SetDlgItemText( IDC_FILENAME,
                            in_file.c_str());

        // Make sure the window is visible
        dlg.ShowWindow(SW_SHOWNORMAL);
        dlg.UpdateWindow();
        DoMessageLoop();

        result_code = in_buffered_file.OpenFile(in_file.c_str(),
                                                false,
                                                OPEN_EXISTING);
        if (result_code != ERROR_SUCCESS)
        {
            ::ReportError(  _T("Unable to open input file ") + in_file,
                            result_code);
            error_abort = true;
        }
        else
        {
            result_code = out_buffered_file.OpenFile(
                                    out_file.c_str(),
                                    true,
                                    CREATE_NEW);

            if (result_code != ERROR_SUCCESS)
            {
                // Close the input file
                in_buffered_file.CloseFile();

                ::ReportError(  _T("Unable to open output file ") + out_file,
                                result_code);
                error_abort = true;
            }
            else
            {
                try
                {
                    // Create the 16-bit IV and 32-bit encryption key
                    // used for encrypting the plaintext file.  We do
                    // not trust the system's randomization functions, so
                    // we improve on that by also hashing the random digits
                    // and using only a portion of the hash.  This IV and key
                    // generation could be replaced with any good random
                    // source of data.
                    memset(iv_key, 0, 48);
                    for (i=0; i<48; i+=16)
                    {
                        memset(buffer, 0, 32);
                        sha256_starts(&sha_ctx);
                        for(j=0; j<256; j++)
                        {
                            if (!CryptGenRandom(hProv,
                                                32,
                                                (BYTE *) buffer))
                            {
                                throw SystemErrorException(
                                    _T("Windows is unable to generate random digits"),
                                    0);
                            }
                            sha256_update(&sha_ctx, buffer, 32);
                        }
                        sha256_finish(&sha_ctx, digest);
                        memcpy(iv_key+i, digest, 16);
                    }

                    // Determine the file size
                    result_code = in_buffered_file.FileSize(&file_size);
                    if (result_code != ERROR_SUCCESS)
                    {
                        throw SystemErrorException(
                                    _T("Unable to determine file size of ") +
                                    in_file,
                                    result_code);
                    }

                    // Write an AES signature at the head of the file, along.
                    // with the AES file format version number.
                    buffer[0] = 'A';
                    buffer[1] = 'E';
                    buffer[2] = 'S';
                    buffer[3] = (unsigned char) 0x02;   // Version 2
                    buffer[4] = '\0';               // Reserved for version 0
                    result_code = out_buffered_file.WriteFile(  buffer,
                                                                5,
                                                                &bytes_written);
                    if (result_code != ERROR_SUCCESS)
                    {
                        throw SystemErrorException(
                                    _T("Unable to write to ") +
                                    out_file,
                                    result_code);
                    }

                    // Write the CREATED-BY tag
                    j = 11 +                          // "CREATED-BY\0"
                        (int) strlen(PROG_NAME) +     // Program name
                        1 +                           // Space
                        (int) strlen(PROG_VERSION);   // Program version string

                    // Our extension buffer is only 256 octets long, so
                    // let's not write an extension if it is too big
                    if (j < 256)
                    {
                        buffer[0] = '\0';
                        buffer[1] = (unsigned char) (j & 0xff);
                        result_code = out_buffered_file.WriteFile(  buffer,
                                                                    2,
                                                                    &bytes_written);
                        if (result_code != ERROR_SUCCESS)
                        {
                            throw SystemErrorException(
                                        _T("Unable to write to ") +
                                        out_file,
                                        result_code);
                        }

                        strcpy_s((char *)tag_buffer, 256, "CREATED_BY");
                        // Add 1 to the length write \0
                        j = (int) strlen((char *) tag_buffer) + 1;
                        result_code = out_buffered_file.WriteFile(  tag_buffer,
                                                                    j,
                                                                    &bytes_written);
                        if (result_code != ERROR_SUCCESS)
                        {
                            throw SystemErrorException(
                                        _T("Unable to write to ") +
                                        out_file,
                                        result_code);
                        }

                        sprintf_s(  (char *)tag_buffer,
                                    256, "%s %s",
                                    PROG_NAME,
                                    PROG_VERSION);
                        j = (int) strlen((char *)tag_buffer);
                        result_code = out_buffered_file.WriteFile(  tag_buffer,
                                                                    j,
                                                                    &bytes_written);
                        if (result_code != ERROR_SUCCESS)
                        {
                            throw SystemErrorException(
                                        _T("Unable to write to ") +
                                        out_file,
                                        result_code);
                        }
                    }

                    // Write out the "container" extension
                    buffer[0] = '\0';
                    buffer[1] = (unsigned char) 128;
                    result_code = out_buffered_file.WriteFile(  buffer,
                                                                2,
                                                                &bytes_written);
                    if (result_code != ERROR_SUCCESS)
                    {
                        throw SystemErrorException(
                                    _T("Unable to write to ") +
                                    out_file,
                                    result_code);
                    }

                    memset(tag_buffer, 0, 128);
                    result_code = out_buffered_file.WriteFile(  tag_buffer,
                                                                128,
                                                                &bytes_written);
                    if (result_code != ERROR_SUCCESS)
                    {
                        throw SystemErrorException(
                                    _T("Unable to write to ") +
                                    out_file,
                                    result_code);
                    }

                    // Write out 0x0000 to indicate that no more extensions exist
                    buffer[0] = '\0';
                    buffer[1] = '\0';
                    result_code = out_buffered_file.WriteFile(  buffer,
                                                                2,
                                                                &bytes_written);
                    if (result_code != ERROR_SUCCESS)
                    {
                        throw SystemErrorException(
                                    _T("Unable to write to ") +
                                    out_file,
                                    result_code);
                    }

                    // We will use an initialization vector comprised of
                    // the current time, file size, file name, and 32 octets
                    // of psuedo-random digits, all hashed together with
                    // SHA-256.
                    current_time = time(NULL);
                    for(i = 0; i < 8; i++)
                    {
                        buffer[i] = (unsigned char)
                                        (current_time >> (i * 8));
                    }
                    for(i = 0; i< 8; i++)
                    {
                        buffer[i+8] = (unsigned char)
                                        (file_size.QuadPart >> (i*8));
                    }

                    sha256_starts(  &sha_ctx);
                    sha256_update(  &sha_ctx, buffer, 16);
                    sha256_update(  &sha_ctx,
                                    (unsigned char *)in_file.c_str(),
                                    // Unicode means the bytes are twice
                                    // the string length.
                                    (unsigned long)
                                    _tcsnlen(   in_file.c_str(),
                                                (MAX_PATH+1)) *
                                                sizeof(TCHAR));
                    for(i=0; i<256; i++)
                    {
                        if (!CryptGenRandom(hProv,
                                            32,
                                            (BYTE *) buffer))
                        {
                            throw SystemErrorException(
                                _T("Windows is unable to generate random digits"),
                                0);
                        }
                        sha256_update(&sha_ctx, buffer, 32);
                    }

                    sha256_finish(&sha_ctx, digest);

                    memcpy(IV, digest, 16);

                    // Write the initialization vector to the file
                    result_code = out_buffered_file.WriteFile(  IV,
                                                                16,
                                                                &bytes_written);
                    if (result_code != ERROR_SUCCESS)
                    {
                        throw SystemErrorException(
                                    _T("Unable to write to ") +
                                    out_file,
                                    result_code);
                    }

                    // Hash the IV and password 8192 times
                    memset(digest, 0, 32);
                    memcpy(digest, IV, 16);
                    for(i=0; i<8192; i++)
                    {
                        sha256_starts(  &sha_ctx);
                        sha256_update(  &sha_ctx, digest, 32);
                        sha256_update(  &sha_ctx,
                                        (unsigned char*)passwd,
                                        // Unicode means the bytes are twice
                                        // the string length.
                                        (unsigned long)
                                        _tcsnlen(passwd, MAX_PASSWD_LEN+1)*
                                        sizeof(TCHAR));
                        sha256_finish(  &sha_ctx,
                                        digest);
                    }

                    // Because the aes_set_key routine is not thread safe,
                    // protect it with a critical section.
                    EnterCriticalSection(&Critical_Section);
                    aes_set_key(&aes_ctx, digest, 256);
                    LeaveCriticalSection(&Critical_Section);

                    // Set the ipad and opad arrays with values as
                    // per RFC 2104 (HMAC).  HMAC is defined as
                    //   H(K XOR opad, H(K XOR ipad, text))
                    memset(ipad, 0x36, 64);
                    memset(opad, 0x5C, 64);

                    for(i=0; i<32; i++)
                    {
                        ipad[i] ^= digest[i];
                        opad[i] ^= digest[i];
                    }

                    sha256_starts(&sha_ctx);
                    sha256_update(&sha_ctx, ipad, 64);

                    // Encrypt the IV and key used to encrypt the plaintext file,
                    // writing that encrypted text to the output file.
                    for(i=0; i<48; i+=16)
                    {
                        // Place the next 16 octets of IV and key buffer into
                        // the input buffer.
                        memcpy(buffer, iv_key+i, 16);

                        // XOR plain text block with previous encrypted
                        // output (i.e., use CBC)
                        for(j=0; j<16; j++)
                        {
                            buffer[j] ^= IV[j];
                        }

                        // Encrypt the contents of the buffer
                        aes_encrypt(&aes_ctx, buffer, buffer);
                        
                        // Concatenate the "text" as we compute the HMAC
                        sha256_update(&sha_ctx, buffer, 16);

                        // Write the encrypted block
                        result_code = out_buffered_file.WriteFile(
                                                            buffer,
                                                            16,
                                                            &bytes_written);
                        if (result_code != ERROR_SUCCESS)
                        {
                            throw SystemErrorException(
                                        _T("Unable to write to ") +
                                        out_file,
                                        result_code);
                        }
                        
                        // Update the IV (CBC mode)
                        memcpy(IV, buffer, 16);
                    }

                    // Write the HMAC
                    sha256_finish(&sha_ctx, digest);
                    sha256_starts(&sha_ctx);
                    sha256_update(&sha_ctx, opad, 64);
                    sha256_update(&sha_ctx, digest, 32);
                    sha256_finish(&sha_ctx, digest);
                    result_code = out_buffered_file.WriteFile(
                                                    digest,
                                                    32,
                                                    &bytes_written);
                    if (result_code != ERROR_SUCCESS)
                    {
                        throw SystemErrorException(
                                    _T("Unable to write to ") +
                                    out_file,
                                    result_code);
                    }

                    // Re-load the IV and encryption key with the IV and
                    // key to now encrypt the datafile.  Also, reset the HMAC
                    // computation.
                    memcpy(IV, iv_key, 16);

                    // Because the aes_set_key routine is not thread safe,
                    // protect it with a critical section.
                    EnterCriticalSection(&Critical_Section);
                    aes_set_key(&aes_ctx, iv_key+16, 256);
                    LeaveCriticalSection(&Critical_Section);

                    // Set the ipad and opad arrays with values as
                    // per RFC 2104 (HMAC).  HMAC is defined as
                    //   H(K XOR opad, H(K XOR ipad, text))
                    memset(ipad, 0x36, 64);
                    memset(opad, 0x5C, 64);

                    for(i=0; i<32; i++)
                    {
                        ipad[i] ^= iv_key[i+16];
                        opad[i] ^= iv_key[i+16];
                    }

                    // Wipe the IV and encryption mey from memory
                    memset(iv_key, 0, 48);

                    sha256_starts(&sha_ctx);
                    sha256_update(&sha_ctx, ipad, 64);

                    last_clock_time = clock();
                    current_percent = 0;
                    bytes_left = file_size.QuadPart;
                    while(bytes_left > 0)
                    {
                        n = (bytes_left > 16) ? 16 : (int) bytes_left;
                        bytes_left -= n;
                        result_code = in_buffered_file.ReadFile(buffer,
                                                                n,
                                                                &bytes_read);
                        if (result_code != ERROR_SUCCESS)
                        {
                            throw SystemErrorException(
                                        _T("Unable to read ") +
                                        in_file,
                                        result_code);
                        }

                        // XOR plain text block with previous encrypted
                        // output (i.e., use CBC)
                        for(i=0; i<16; i++)
                        {
                            buffer[i] ^= IV[i];
                        }

                        // Encrypt the contents of the buffer
                        aes_encrypt(&aes_ctx, buffer, buffer);
                        
                        // Concatenate the "text" as we compute the HMAC
                        sha256_update(&sha_ctx, buffer, 16);

                        // Write the encrypted block
                        result_code = out_buffered_file.WriteFile(
                                                            buffer,
                                                            16,
                                                            &bytes_written);
                        if (result_code != ERROR_SUCCESS)
                        {
                            throw SystemErrorException(
                                        _T("Unable to write to ") +
                                        out_file,
                                        result_code);
                        }
                        
                        // Update the IV (CBC mode)
                        memcpy(IV, buffer, 16);

                        // Update the UI when more than 250ms has passed
                        // or when there is no more data to read or
                        // when the next 1 percent of the file has been
                        // processed
                        current_percent =
                            (file_size.QuadPart - bytes_left) *
                                        100 / file_size.QuadPart;
                        if ((clock() - last_clock_time >
                            (CLOCKS_PER_SEC / 4)) ||
                            (bytes_left == 0) ||
                            (current_percent > last_percent))
                        {
                            // Update the progress bar
                            dlg.SendDlgItemMessage(
                                IDC_PROGRESSBAR,
                                PBM_SETPOS,
                                (WPARAM) current_percent,
                                0);
                            dlg.UpdateWindow();
                            DoMessageLoop();
                            if (dlg.abort_processing == true)
                            {
                                error_abort = true;
                                break;
                            }

                            last_clock_time = clock();
                            last_percent = current_percent;
                        }
                    }

                    if (error_abort == false)
                    {
                        // Write the HMAC
                        sha256_finish(&sha_ctx, digest);
                        sha256_starts(&sha_ctx);
                        sha256_update(&sha_ctx, opad, 64);
                        sha256_update(&sha_ctx, digest, 32);
                        sha256_finish(&sha_ctx, digest);
                        buffer[0] = (char) (file_size.LowPart & 0x0F);
                        result_code = out_buffered_file.WriteFile(
                                                            buffer,
                                                            1,
                                                            &bytes_written);
                        if (result_code == ERROR_SUCCESS)
                        {
                            result_code = out_buffered_file.WriteFile(
                                                            digest,
                                                            32,
                                                            &bytes_written);
                        }
                        if (result_code != ERROR_SUCCESS)
                        {
                            throw SystemErrorException(
                                        _T("Unable to write to ") +
                                        out_file,
                                        result_code);
                        }
                    }
                }
                catch(SystemErrorException e)
                {
                    ::ReportError(e.Message,e.Reason);
                    error_abort = true;
                }

                in_buffered_file.CloseFile();
                out_buffered_file.CloseFile();

                // We will attempt to cleanup, but we don't care if this
                // really works or not...
                if (error_abort == true)
                {
                    DeleteFile(out_file.c_str());
                    error_abort = true;
                }
            }
        }

        // Remove the filename from the list
        file_list->pop_front();
    }

    // For security reasons, erase the password
    memset(passwd, 0, sizeof(TCHAR) * MAX_PASSWD_LEN);
    
    // We processed the files, so we must have properly allocated hProv.
    // Now, release it.
    if (file_list->empty())
    {
        CryptReleaseContext(hProv, 0);
    }

    // Destroy the progress window
    dlg.DestroyWindow();

}

/*
 * DecryptFiles
 *
 * This function is called by the worker thread to decrypt a list of files.
 */
void AESCryptWorkerThreads::DecryptFiles(
                                StringList  *file_list,
                                TCHAR       *passwd)
{
    aes_context                 aes_ctx;
    sha256_context              sha_ctx;
    std::basic_string<TCHAR>    in_file;
    TCHAR                       out_file[MAX_PATH+1];
    TCHAR                       *p;
    BufferedFile                in_buffered_file,
                                out_buffered_file;
    DWORD                       result_code;
    unsigned char               IV[16];
    unsigned char               buffer[32], buffer2[32];
    unsigned char               iv_key[48];
    unsigned char               digest[32];
    LARGE_INTEGER               file_size; // 64-bit integer structure
    ULONGLONG                   bytes_left;
    int                         last_block_size;
    bool                        last_block_size_read;
    int                         i, j, n;
    DWORD                       bytes_written, bytes_read;
    unsigned char               ipad[64];
    unsigned char               opad[64];
    bool                        error_abort = false;
    ProgressDialog              dlg;
    unsigned                    version;
    unsigned                    footprint;
    clock_t                     last_clock_time;
    ULONGLONG                   last_percent, current_percent;

    // Passing a zero instructs the dialog to display
    // "Decrypting..."
    dlg.Create(NULL,0);

    // Walk through the list of files decrypting each
    while(!file_list->empty() && !error_abort)
    {
        // Get the filename
        in_file = file_list->front();
        _tcscpy_s(out_file, MAX_PATH, in_file.c_str());
        i = (int) _tcslen(out_file);
        if (i < 5)
        {
            ::ReportError(  _T("Invalid input file name: ") + in_file,
                            0);
            error_abort = true;
        }

        // Reset the progress bar (default range is 0..100)
        dlg.SendDlgItemMessage( IDC_PROGRESSBAR,
                                PBM_SETPOS,
                                0,
                                0);

        // Display the file name
        dlg.SetDlgItemText( IDC_FILENAME,
                            in_file.c_str());

        // Make sure the window is visible
        dlg.ShowWindow(SW_SHOWNORMAL);
        dlg.UpdateWindow();
        DoMessageLoop();
        
        // Remove the .aes extension (we hope ... gulp)
        p = out_file + i - 4;
        *p = _T('\0');

        if (error_abort == false)
        {
            result_code = in_buffered_file.OpenFile(in_file.c_str(),
                                                    false,
                                                    OPEN_EXISTING);
            if (result_code != ERROR_SUCCESS)
            {
                ::ReportError(  _T("Unable to open input file ") + in_file,
                                result_code);
                error_abort = true;
            }
        }

        if (error_abort == false)
        {
            result_code = out_buffered_file.OpenFile(   out_file,
                                                        true,
                                                        CREATE_NEW);
            if (result_code != ERROR_SUCCESS)
            {
                std::basic_string<TCHAR> message;

                // Close the input file
                in_buffered_file.CloseFile();

                message = _T("Unable to open output file ");
                message += out_file;
                ::ReportError(message, result_code);
                error_abort = true;
            }
            else
            {
                try
                {
                    // Determine the file size
                    result_code = in_buffered_file.FileSize(&file_size);
                    if (result_code != ERROR_SUCCESS)
                    {
                        throw SystemErrorException(
                                    _T("Unable to determine file size of ") +
                                    in_file,
                                    result_code);
                    }

                    if (file_size.QuadPart < FOOTPRINT_V0)
                    {
                        throw SystemErrorException(
                                    _T("Invalid input file ") +
                                    in_file + _T("\n File too short"),
                                    0);
                    }

                    // Read the file header
                    result_code = in_buffered_file.ReadFile(buffer,
                                                            5,
                                                            &bytes_read);
                    if (result_code != ERROR_SUCCESS)
                    {
                        throw SystemErrorException(
                                    _T("Unable to read ") +
                                    in_file,
                                    result_code);
                    }

                    if (buffer[0] != 'A' || buffer[1] != 'E' ||
                        buffer[2] != 'S')
                    {
                        throw SystemErrorException(
                                    _T("Invalid input file ") +
                                    in_file + _T("\n Invalid signature"),
                                    0);
                    }

                    version = (unsigned) buffer[3];
                    if (version > 2)
                    {
                        throw SystemErrorException(
                                    _T("Invalid input file ") +
                                    in_file + _T("\n Unsupported version"),
                                    0);
                    }

                    // How many bytes are left in the message
                    // (excludes header and HMAC)
                    if (version == 0)
                    {
                        bytes_left = file_size.QuadPart - FOOTPRINT_V0;

                        // Determine the number of octets in the last data block
                        last_block_size = (int) buffer[4] & 0x0F;
                        footprint = FOOTPRINT_V0;
                    }
                    else if (version == 1)
                    {
                        if (file_size.QuadPart < FOOTPRINT_V1)
                        {
                            throw SystemErrorException(
                                        _T("Invalid input file ") +
                                        in_file + _T("\n File too short"),
                                        0);
                        }

                        bytes_left = file_size.QuadPart - FOOTPRINT_V1;
                        footprint = FOOTPRINT_V1;
                    }
                    else  // Must be a V2 file
                    {
                        if (file_size.QuadPart < FOOTPRINT_V2)
                        {
                            throw SystemErrorException(
                                        _T("Invalid input file ") +
                                        in_file + _T("\n File too short"),
                                        0);
                        }

                        bytes_left = file_size.QuadPart - FOOTPRINT_V2;
                        footprint = FOOTPRINT_V2;
                    }

                    // Skip over extensions present in v2 or later files
                    if (version >= 2)
                    {
                        do
                        {
                            // Read the extension size
                            result_code =
                                in_buffered_file.ReadFile(  buffer,
                                                            2,
                                                            &bytes_read);
                            if (result_code != ERROR_SUCCESS)
                            {
                                throw SystemErrorException(
                                            _T("Unable to read ") +
                                            in_file,
                                            result_code);
                            }

                            // Determine the extension length, zero means no
                            // more extensions.
                            i = j = (((int)buffer[0]) << 8) | (int)buffer[1];

                            // The bytes_left variable has already accounted
                            // for the 0x0000 extension in the file footprint.
                            // If this is a "real" extension, then reduce the
                            // bytes_left variable further.
                            if (j)
                            {
                                bytes_left -= (2 + j);
                            }

                            while (i--)
                            {
                                // Read the extension size
                                result_code =
                                    in_buffered_file.ReadFile(  buffer,
                                                                1,
                                                                &bytes_read);
                                if (result_code != ERROR_SUCCESS)
                                {
                                    throw SystemErrorException(
                                                _T("Unable to read ") +
                                                in_file,
                                                result_code);
                                }
                            }
                        } while(j);
                    }

                    // The message must be a multiple of 16 octets
                    if (bytes_left & 0x0F)
                    {
                        throw SystemErrorException(
                                    _T("Invalid input file ") +
                                    in_file + _T("\n Message length invalid"),
                                    0);
                    }

                    // Read the IV
                    result_code = in_buffered_file.ReadFile(IV,
                                                            16,
                                                            &bytes_read);
                    if (result_code != ERROR_SUCCESS)
                    {
                        throw SystemErrorException(
                                    _T("Unable to read ") +
                                    in_file,
                                    result_code);
                    }

                    // Hash the IV and password 8192 times
                    memset(digest, 0, 32);
                    memcpy(digest, IV, 16);
                    for(i=0; i<8192; i++)
                    {
                        sha256_starts(  &sha_ctx);
                        sha256_update(  &sha_ctx, digest, 32);
                        sha256_update(  &sha_ctx,
                                        (unsigned char*)passwd,
                                        // Unicode means the bytes are twice
                                        // the string length.
                                        (unsigned long)
                                        _tcsnlen(passwd, MAX_PASSWD_LEN+1)*
                                        sizeof(TCHAR));
                        sha256_finish(  &sha_ctx,
                                        digest);
                    }

                    // Because the aes_set_key routine is not thread safe,
                    // protect it with a critical section.
                    EnterCriticalSection(&Critical_Section);
                    aes_set_key(&aes_ctx, digest, 256);
                    LeaveCriticalSection(&Critical_Section);

                    // Set the ipad and opad arrays with values as
                    // per RFC 2104 (HMAC).  HMAC is defined as
                    //   H(K XOR opad, H(K XOR ipad, text))
                    memset(ipad, 0x36, 64);
                    memset(opad, 0x5C, 64);

                    for(i=0; i<32; i++)
                    {
                        ipad[i] ^= digest[i];
                        opad[i] ^= digest[i];
                    }

                    sha256_starts(&sha_ctx);
                    sha256_update(&sha_ctx, ipad, 64);

                    // If this is a version 1 file, then read the IV and key
                    // for decrypting the bulk of the file.
                    if (version >= 1)
                    {
                        for(i=0; i<48; i+=16)
                        {
                            result_code = in_buffered_file.ReadFile(buffer,
                                                                    16,
                                                                    &bytes_read);
                            if (result_code != ERROR_SUCCESS)
                            {
                                throw SystemErrorException(
                                            _T("Unable to read ") +
                                            in_file,
                                            result_code);
                            }

                            memcpy(buffer2, buffer, 16);

                            sha256_update(&sha_ctx, buffer, 16);
                            aes_decrypt(&aes_ctx, buffer, buffer);

                            // XOR plain text block with previous encrypted
                            // output (i.e., use CBC)
                            for(j=0; j<16; j++)
                            {
                                iv_key[i+j] = (buffer[j] ^ IV[j]);
                            }

                            // Update the IV (CBC mode)
                            memcpy(IV, buffer2, 16);
                        }

                        // Verify that the HMAC is correct
                        sha256_finish(&sha_ctx, digest);
                        sha256_starts(&sha_ctx);
                        sha256_update(&sha_ctx, opad, 64);
                        sha256_update(&sha_ctx, digest, 32);
                        sha256_finish(&sha_ctx, digest);

                        result_code = in_buffered_file.ReadFile(buffer,
                                                                32,
                                                                &bytes_read);
                        if (result_code != ERROR_SUCCESS)
                        {
                            throw SystemErrorException(
                                        _T("Unable to read ") +
                                        in_file,
                                        result_code);
                        }

                        if (memcmp(digest, buffer, 32))
                        {
                            throw SystemErrorException(
                                        _T("Error in file ") +
                                        in_file +
                                        _T("\nMessage has been altered or password is incorrect"),
                                        0);
                        }

                        // Re-load the IV and encryption key with the IV and
                        // key to now encrypt the datafile.  Also, reset the HMAC
                        // computation.
                        memcpy(IV, iv_key, 16);

                        // Because the aes_set_key routine is not thread safe,
                        // protect it with a critical section.
                        EnterCriticalSection(&Critical_Section);
                        aes_set_key(&aes_ctx, iv_key+16, 256);
                        LeaveCriticalSection(&Critical_Section);

                        // Set the ipad and opad arrays with values as
                        // per RFC 2104 (HMAC).  HMAC is defined as
                        //   H(K XOR opad, H(K XOR ipad, text))
                        memset(ipad, 0x36, 64);
                        memset(opad, 0x5C, 64);

                        for(i=0; i<32; i++)
                        {
                            ipad[i] ^= iv_key[i+16];
                            opad[i] ^= iv_key[i+16];
                        }

                        // Wipe the IV and encryption mey from memory
                        memset(iv_key, 0, 48);

                        sha256_starts(&sha_ctx);
                        sha256_update(&sha_ctx, ipad, 64);
                    }
                    
                    last_clock_time = clock();
                    current_percent = 0;
                    last_block_size_read = false;
                    while(bytes_left > 0)
                    {
                        bytes_left -= 16;
                        result_code = in_buffered_file.ReadFile(buffer,
                                                                16,
                                                                &bytes_read);
                        // If we're processing a version 1 or greaterfile and
                        // we reach the end of the file, then let's read the
                        // file size modulo octet.
                        if (bytes_left == 0 && version >= 1 &&
                            result_code == ERROR_SUCCESS)
                        {
                            result_code = in_buffered_file.ReadFile(buffer2,
                                                                    1,
                                                                    &bytes_read);
                            
                            // Determine the number of octets in the last
                            // data block
                            last_block_size = (int) buffer2[0] & 0x0F;
                            last_block_size_read = true;
                        }
                        if (result_code != ERROR_SUCCESS)
                        {
                            throw SystemErrorException(
                                        _T("Unable to read ") +
                                        in_file,
                                        result_code);
                        }

                        memcpy(buffer2, buffer, 16);

                        sha256_update(&sha_ctx, buffer, 16);
                        aes_decrypt(&aes_ctx, buffer, buffer);

                        // XOR plain text block with previous encrypted
                        // output (i.e., use CBC)
                        for(i=0; i<16; i++)
                        {
                            buffer[i] ^= IV[i];
                        }

                        // Update the IV (CBC mode)
                        memcpy(IV, buffer2, 16);

                        // If this is the final block, then we may
                        // write less than 16 octets
                        n = ((bytes_left > 0) ||
                             (last_block_size == 0)) ? 16 : last_block_size;

                        // Write the decrypted block
                        result_code = out_buffered_file.WriteFile(
                                                            buffer,
                                                            n,
                                                            &bytes_written);
                        if (result_code != ERROR_SUCCESS)
                        {
                            std::basic_string<TCHAR> message;
                            message = _T("Unable to write to ");
                            message += out_file;
                            throw SystemErrorException(message, result_code);
                        }

                        // Update the UI when more than 250ms has passed
                        // or when there is no more data to read or
                        // when the next 1 percent of the file has been
                        // processed
                        current_percent =
                            (file_size.QuadPart - bytes_left - footprint) *
                                        100 / (file_size.QuadPart - footprint);
                        if ((clock() - last_clock_time >
                            (CLOCKS_PER_SEC / 4)) ||
                            (bytes_left == 0) ||
                            (current_percent > last_percent))
                        {
                            // Update the progress bar
                            dlg.SendDlgItemMessage(
                                IDC_PROGRESSBAR,
                                PBM_SETPOS,
                                (WPARAM) current_percent,
                                0);
                            dlg.UpdateWindow();
                            DoMessageLoop();
                            if (dlg.abort_processing == true)
                            {
                                error_abort = true;
                                break;
                            }

                            last_clock_time = clock();
                            last_percent = current_percent;
                        }
                    }

                    if (error_abort == false)
                    {
                        if (last_block_size_read == false && version >= 1)
                        {
                            result_code = in_buffered_file.ReadFile(buffer2,
                                                                    1,
                                                                    &bytes_read);
                            
                            if (result_code != ERROR_SUCCESS)
                            {
                                throw SystemErrorException(
                                            _T("Unable to read ") +
                                            in_file,
                                            result_code);
                            }

                            // Determine the number of octets in the last
                            // data block
                            last_block_size = (int) buffer2[0] & 0x0F;

                            // If the last_block_size value was not previously
                            // read, that means the file had no encrypted octets
                            // and therefore the last_block_size value should
                            // be zero.
                            if (last_block_size != 0)
                            {
                                throw SystemErrorException(
                                            _T("Error in file ") +
                                            in_file +
                                            _T("\nMessage has been altered and should not be trusted."),
                                            0);
                            }

                        }

                        // Verify that the HMAC is correct
                        sha256_finish(&sha_ctx, digest);
                        sha256_starts(&sha_ctx);
                        sha256_update(&sha_ctx, opad, 64);
                        sha256_update(&sha_ctx, digest, 32);
                        sha256_finish(&sha_ctx, digest);

                        result_code = in_buffered_file.ReadFile(buffer,
                                                                32,
                                                                &bytes_read);
                        if (result_code != ERROR_SUCCESS)
                        {
                            throw SystemErrorException(
                                        _T("Unable to read ") +
                                        in_file,
                                        result_code);
                        }

                        if (memcmp(digest, buffer, 32))
                        {
                            if (version == 0)
                            {
                                throw SystemErrorException(
                                            _T("Error in file ") +
                                            in_file +
                                            _T("\nMessage has been altered or password is incorrect"),
                                            0);
                            }
                            else
                            {
                                throw SystemErrorException(
                                            _T("Error in file ") +
                                            in_file +
                                            _T("\nMessage has been altered and should not be trusted."),
                                            0);
                            }
                        }
                    }
                }
                catch(SystemErrorException e)
                {
                    ::ReportError(e.Message,e.Reason);
                    error_abort = true;
                }

                in_buffered_file.CloseFile();
                out_buffered_file.CloseFile();

                // We will attempt to cleanup, but we don't care if this
                // really works or not...
                if (error_abort == true)
                {
                    DeleteFile(out_file);
                }
            }
        }

        // Remove the filename from the list
        file_list->pop_front();
    }

    // For security reasons, erase the password
    memset(passwd, 0, sizeof(TCHAR) * MAX_PASSWD_LEN);
                    
    // Destroy the progress window
    dlg.DestroyWindow();
}
