/*
 *  AESCryptWorkerThreads.h
 *
 *  Copyright (C) 2006, 2008, 2013
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved.
 *
 *  This file defines the AESCryptWorkerThreads class, which is
 *  responsible for all background encryption and decryption functions.
 *
 */

#pragma once

struct WorkerData;

class AESCryptWorkerThreads
{
    private:
        CRITICAL_SECTION    Critical_Section;
        int                 Thread_Count;
        std::list<HANDLE>   Terminated_Threads;

        bool StartThread(   StringList *file_list,
                            TCHAR *passwd,
                            bool encrypt);

        inline void DoMessageLoop();

        void EncryptFiles(  StringList *file_list,
							TCHAR *passwd);

        void DecryptFiles(  StringList *file_list,
                            TCHAR *passwd);

    public:
        AESCryptWorkerThreads();
        ~AESCryptWorkerThreads();

        // Indicates whether threads are working
        bool IsBusy();

        // Process files for encryption (true) or decryption (false)
        void ProcessFiles(  StringList *file_list,
                            bool encrypt);

        // This should only be called by threads
        // spawned by this class.
        void ThreadEntry(   WorkerData *worker_data);
};

struct WorkerData
{
    StringList              *file_list;
    TCHAR                   passwd[MAX_PASSWD_LEN+1];
    bool                    encrypt;
    HANDLE                  thread_handle;
    AESCryptWorkerThreads   *aes_crypt_worker_threads;
};
