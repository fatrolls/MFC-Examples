#ifndef __FILESYSTEM_FILE_HPP
#define __FILESYSTEM_FILE_HPP

#include "../IOCP/Dispatcher.hpp"
#include "../IOCP/Buffer.hpp"







namespace async
{
	
	namespace filesystem
	{

		using namespace async::IOCP;

		// forward declare
		class File;
		typedef pointer<File> FilePtr;


		// class FileBuffer
		typedef BufferT<char, MemoryMgr::DEFAULT_FILE_SIZE, async::memory::MemAllocator<char, MemoryMgr::FileMemoryPool> > FileBuffer;
		//typedef BufferT<char, MemoryMgr::DEFAULT_FILE_SIZE, std::allocator<char> > FileBuffer;
		typedef pointer<FileBuffer> FileBufferPtr;



		//--------------------------------------------------------------------------------
		// class File

		class File
			: public Object
		{
		private:
			HANDLE file_;
			IODispatcher &io_;

		public:
			File(IODispatcher &, LPCTSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE hTemplate = NULL);
			virtual ~File();

			// non-copyable
		private:
			File(const File &);
			File &operator=(const File &);


		public:
			HANDLE operator()()
			{
				return file_;
			}
			const HANDLE operator()() const
			{
				return file_;
			}

			HANDLE GetHandle()
			{
				return file_;
			}
			HANDLE GetHandle() const
			{
				return file_;
			}

		public:
			// Read
			AsyncResultPtr BeginRead(const FileBufferPtr &buf, size_t nOffset, size_t nBufSize, PLARGE_INTEGER fileOffset
				, AsyncCallbackFunc callback = 0, const ObjectPtr &asyncState = nothing, const ObjectPtr &internalState = nothing);
			size_t EndRead(const AsyncResultPtr &asynResult);

			// Write
			AsyncResultPtr BeginWrite(const FileBufferPtr &buf, size_t nOffset, size_t nBufSize, PLARGE_INTEGER fileOffset
				, AsyncCallbackFunc callback = 0, const ObjectPtr &asyncState = nothing, const ObjectPtr &internalState = nothing);
			size_t EndWrite(const AsyncResultPtr &asynResult);


			void Close();

		private:
			size_t _EndAsyncOperation(const AsyncResultPtr &asyncResult);
		};
	}





}




#endif