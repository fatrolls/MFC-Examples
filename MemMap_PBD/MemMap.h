#ifndef _MEMMAP_H_
#define _MEMMAP_H_
///////////////////////////////////////////////////////////////////////////////
// MemMap.h
// Rohit Joshi
// 12/14/2004
// Policy based design of Memory mapped file.
// Following policies are define.
// 1. CreationPolicy: Default value: Create
//    It allows user to create file for mapping memory.
//    Currently two implementations are available in which Create
//    creates new file where as Open opens existing file. If doesn't
//    exist, it throws error
// 2. DeletionPolicy: Default value:  Delete
//    It allows user to decide whether to delete memory mapped file
//    when object goes outof scope or keep the file for other processes to
//    use. The default value is Delete which will delete the file. Other
//    is NoDelete which won't delete the file.
// 3. MappingPolicy: Default Value: SharedMap
//    It allows user to decided whether to create memory mapped filed as
//    shared among processes or private to process
// 4. MemorySyncPolicy: Default value MemSync
//    In shared mode,data written in memory needs to be syncronized with
//    data in file. It allows user to sync data immidiatly or in asyncronous 
//    mode. Inconsistent data can be invalidate using MemInvalidate policy
////////////////////////////////////////////////////////////////////////////////
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <cerrno>
#include <cstdio>
#include <cstdarg>


namespace Joshi
{
///////////////////////////////////////////////////////////////////////////////
// CREATION POLICY:
//  1. CreateReadWrite
//  2. CreateReadWriteTruncate
//  3. OpenReadWrite

///////////////////////////////////////////////////////////////////////////////
// CreateReadWrite:Create a file new file if not exist. Open in read/write mode
///////////////////////////////////////////////////////////////////////////////
    class CreateReadWrite 
    {
    public:
        // create a file and open in read/write mode
        static int OpenFile(const std::string &sFileName)
        {
             return open(sFileName.c_str(), O_CREAT | O_RDWR, 0666);
        }
        // current opearion
        static bool TruncateFile(int nFd, unsigned nFileSize, void **pMemFile)
        {
            return true;
        }
    };
///////////////////////////////////////////////////////////////////////////////
// CreateReadWriteTruncate:Create a file new file if not exist. Open in 
// read/write and trucate mode
///////////////////////////////////////////////////////////////////////////////
    class CreateReadWriteTruncate 
    {
    public:
        // Open in read/write and truncate mode
        static int OpenFile(const std::string &sFileName)
        {
             return open(sFileName.c_str(), O_CREAT | O_TRUNC| O_RDWR, 0666);
        }
        //truncate the file and set it to zero
        static bool TruncateFile(int nFd, unsigned nFileSize, void **pMemFile)
        {
            char cZero = 0;
            if ((lseek(nFd, nFileSize - 1, SEEK_SET) == -1) ||
                (write(nFd, &cZero, 1) == -1))
               return false;
            memset(*pMemFile, 0, nFileSize);
            return true;
        }
    };
///////////////////////////////////////////////////////////////////////////////
// OpenReadWrite:Open file in read/write mode if exist
///////////////////////////////////////////////////////////////////////////////
    class OpenReadWrite 
    {
    public:
        // Open in read/write mode
        static int OpenFile(const std::string &sFileName)
        {
             return open(sFileName.c_str(), O_RDWR, 0666);
        }
        // current opearion
        static bool TruncateFile(int nFd, unsigned nFileSize, void **pMemFile)
        {
            return true;
        }
    };
///////////////////////////////////////////////////////////////////////////////
// OpenReadOnly:Open file in read only mode if exist
///////////////////////////////////////////////////////////////////////////////
    class OpenReadOnly 
    {
    public:
        // create a file and open in read/write mode
        static int OpenFile(const std::string &sFileName)
        {
             return open(sFileName.c_str(), O_RDWR, 0666);
        }
        // current opearion
        static bool TruncateFile(int nFd, unsigned nFileSize, void **pMemFile)
        {
            return true;
        }
    };
///////////////////////////////////////////////////////////////////////////////
// MAPPING POLICY:
//  1. SharedMapReadWrite
//  2. PrivateMapReadWrite

/////////////////////////////////////////////////////////////////////////////
// SharedMap: Maps the memory for shared access among the proceces
// //////////////////////////////////////////////////////////////////////////
    class SharedMapReadWrite
    {
    public:
        // map the file
        static void* Map(unsigned nFileSize, int nMapFd)
        {
            return mmap(0, nFileSize, PROT_READ|PROT_WRITE,
                    MAP_SHARED, nMapFd, 0);
        }
    };
/////////////////////////////////////////////////////////////////////////////
// PrivateMap: Maps the memory for private access to process
// //////////////////////////////////////////////////////////////////////////
    class PrivateMapReadWrite
    {
    public:
        // map the file
        static void* Map(unsigned nFileSize, int nMapFd)
        {
            return mmap(0, nFileSize, PROT_READ|PROT_WRITE,
                    MAP_PRIVATE, nMapFd, 0);
        }

    };
///////////////////////////////////////////////////////////////////////////////
// DELETION POLICY:
// 1. Delete
// 2. DoNotDelete

///////////////////////////////////////////////////////////////////////////////
// Delete: It deletes (unlink) the file
//////////////////////////////////////////////////////////////////////////////
    class  Delete
    {
    public:
        static void DeleteFile(const std::string &sFileName) 
        {
            if (sFileName.length() > 0) {
                unlink(sFileName.c_str());
            }
        }
    };
///////////////////////////////////////////////////////////////////////////////
// DoNotDelete: It doesn't delete the file
//////////////////////////////////////////////////////////////////////////////
    class DoNotDelete
    {
    public:
        static void DeleteFile(const std::string &sFileName) {}
    };
 
///////////////////////////////////////////////////////////////////////////////
// MEMSYNC POLICY:
// 1. MemAsync
// 2. MemSync
// 3. MemInvalidate
///////////////////////////////////////////////////////////////////////////////
// MemAsync: It syncs the data asyncronously
//////////////////////////////////////////////////////////////////////////////
    class  MemAsync
    {
    public:
        // syncronize data
        static bool Sync(void **pMemFile, unsigned nFileSize) 
        {
            if(msync(*pMemFile, nFileSize, MS_ASYNC) == -1)
               return false;
            return true;
        }
    };
///////////////////////////////////////////////////////////////////////////////
// MemSync: It syncs the data syncronously
//////////////////////////////////////////////////////////////////////////////
    class MemSync
    {
    public:
        // syncronize data
        static bool Sync(void **pMemFile, unsigned nFileSize) 
        {
            if(msync(*pMemFile, nFileSize, MS_SYNC) == -1)
               return false;
            return true;
        }
    };
///////////////////////////////////////////////////////////////////////////////
// MemInvalidate: Invalidate memory region
//////////////////////////////////////////////////////////////////////////////
    class MemInvalidate
    {
    public:
        // syncronize data
        static bool Sync(void **pMemFile, unsigned nFileSize) 
        {
            if(msync(*pMemFile, nFileSize, MS_INVALIDATE) == -1)
               return false;
            return true;
        }
    };
/////////////////////////////////////////////////////////////////////////////
// MemMapFileException: Memory map exception class
// It concatinates the user error message with system error message.
////////////////////////////////////////////////////////////////////////////
    class MemMapFileException : public std::exception
    {
    private:
        std::string message;
    public:
        explicit MemMapFileException(const char* format, ...): message("Error: ")
        {
            va_list args;
            char buffer[256];
            memset(buffer, '\0', sizeof(buffer));
            va_start(args, format);
            vsnprintf(buffer, sizeof(buffer), format, args);
            va_end(args);
            message += buffer;
            message += ':';
            message += strerror(errno);

        }
        ~MemMapFileException() throw() {}
        const char* what() const throw()
        {
            return message.c_str();
        }
    };

//////////////////////////////////////////////////////////////////////////////
// MemMapFilePtr: It is a memory map wrapper class which provides the memory
// mapping functionality based on below defined policies.
// 1. CreationPolicy
// 2. DeletionPolicy
// 3. MappingPolicy
// 4. MemSyncPolicy
//////////////////////////////////////////////////////////////////////////////

    template<typename CreationPolicy,
             typename DeletionPolicy, 
             typename MappingPolicy,
             typename MemSyncPolicy
             >
    class MemMapFile
    {
        int m_nMapFd;  // file descriptor
        unsigned m_nFileSize;
        std::string m_sFileName;
        void *m_pMemFile;

        // private functions not implemented
        MemMapFile();
        MemMapFile(const MemMapFile &);
        MemMapFile& operator=(const MemMapFile&);

    public:

        // constructor
        MemMapFile(const unsigned nSize, const std::string &sFileName) throw(MemMapFileException):
                               m_nMapFd(-1),m_nFileSize(nSize),m_sFileName(sFileName),
                               m_pMemFile(MAP_FAILED) 
        {

        }
        // destructor
        virtual ~MemMapFile() throw()
        {
            DeleteFile();
        }    
        // Create memory mapped file
        void OpenFile() throw (MemMapFileException)
        {
            // create the memory-mapped file
            int fd = CreationPolicy::OpenFile(m_sFileName);
            if (fd < 0) {
                std::string sFileName(m_sFileName);
                m_sFileName = "";
                throw MemMapFileException("Cannot open file [%s]",
                        sFileName.c_str());
            }
            m_nMapFd = fd;
        }

        // Map the file
        void* MapFile() throw (MemMapFileException)
        {
            // map the file to memory
            m_pMemFile = MappingPolicy::Map(m_nFileSize, m_nMapFd);
            if (m_pMemFile == MAP_FAILED) {
                close(m_nMapFd);
                DeletionPolicy::DeleteFile(m_sFileName);
                throw MemMapFileException("Failed memory-mapping file: ",
                     m_sFileName.c_str());
            }
            return m_pMemFile;
        }
        // Sync the data
        void Sync() throw (MemMapFileException)
        {
            if(!MemSyncPolicy::Sync(&m_pMemFile, m_nFileSize))
            {
                close(m_nMapFd);
                DeletionPolicy::DeleteFile(m_sFileName);
                throw MemMapFileException("Failed to syncronize data to file : [%s], size[%d]",
                                           m_sFileName.c_str(),m_nFileSize);
            }
                
        }
        // trucate the file
        void TruncateFile(const unsigned nSize) throw (MemMapFileException)
        {
            // set the file's size
            if (!CreationPolicy::TruncateFile(m_nMapFd, m_nFileSize, &m_pMemFile)) {
                close(m_nMapFd);
                DeletionPolicy::DeleteFile(m_sFileName);
                throw MemMapFileException("Failed to truncate the file : [%s], size[%d]",
                                     m_sFileName.c_str(),m_nFileSize);
            }
            m_nFileSize = nSize;
        }

        // Delete the file based on policy
        void DeleteFile() throw()
            //throw (std::exception)
        {
            Unmap();
            DeletionPolicy::DeleteFile(m_sFileName);
            m_sFileName = "";
        }

        // unmap the file
        void Unmap() throw()
        {
            if (m_pMemFile != MAP_FAILED) {
                close(m_nMapFd);
                munmap((char *)m_pMemFile, m_nFileSize);
                m_pMemFile = MAP_FAILED;
            }

        }


    };       

//////////////////////////////////////////////////////////////////////////////
// MemMapFilePtr: It is a memory map wrapper class which provides the memory
// mapping functionality based on below defined policies.
// 1. CreationPolicy: Default value: CreateReadWrite
// 2. DeletionPolicy: Default value: DeleteFile
// 3. MappingPolicy:  Default Value: SharedMap
// 4. MemSyncPolicy:  Defauly value: MemSync
//////////////////////////////////////////////////////////////////////////////
    template<typename T, typename CreationPolicy=CreateReadWrite,
             typename DeletionPolicy=DoNotDelete, 
             typename MappingPolicy=SharedMapReadWrite,
             typename MemSyncPolicy=MemSync
             >
    class MemMapFilePtr
    {
        typedef MemMapFile<CreationPolicy,DeletionPolicy,MappingPolicy,MemSync> MemMapFileDef;
        MemMapFileDef * m_pFile;
        T* m_pObj;

        // private functions not implemented
        MemMapFilePtr();
        MemMapFilePtr(const MemMapFilePtr &);
        MemMapFilePtr& operator=(const MemMapFilePtr&);

    public:

        // constructor
        explicit MemMapFilePtr(const std::string &sFileName, unsigned nSize=sizeof(T)):m_pFile(0)
        {
            m_pFile = new MemMapFileDef(nSize, sFileName);
            m_pFile->OpenFile();
            m_pFile->TruncateFile(sizeof(T));
            m_pObj = reinterpret_cast<T*>(m_pFile->MapFile());

        }
        // syncronize the data
        void Sync()
        {
            m_pFile->Sync();
        }
        // destructor
        virtual ~MemMapFilePtr()
        {
            m_pFile->DeleteFile();
            delete m_pFile;
        }
        // operator*
        T& operator*()
        {
            return *m_pObj;
        }
        // operator*
        T& operator*() const
        {
            return *m_pObj;
        }
        // operator->
        T* operator->()
        {
            return m_pObj;
        }
        // operator ->
        T* operator->() const
        {
            return m_pObj;
        }
    };

} // namespace
#endif // _MEMMAP_H_
