// Network2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "NetworkImpl.h"


void Wait()
{
	char c = 0;

	while( std::cin >> c )
	{
		if( c == 'q' )
			return;
	}
}

// Debug Memory Info
void DebugAllocSize(LONG allocCount, size_t size)
{
	std::cout << "Alloc" << allocCount << ": " << size << std::endl;
}

void DebugDeallocSize(LONG deallocCount, size_t size)
{
	std::cout << "Dealloc" << deallocCount << ": " << size << std::endl;
}



int _tmain(int argc, _TCHAR* argv[])
{
	// 测试内存申请释放
	Callback::RegisterCallback(std::tr1::bind(&DebugAllocSize, std::tr1::placeholders::_1, std::tr1::placeholders::_2),
		std::tr1::bind(&DebugDeallocSize, std::tr1::placeholders::_1, std::tr1::placeholders::_2));

	// IOCP服务
	IODispatcher ioService(GetFitThreadNum());

	try
	{	
		NetworkImpl server(ioService); 
		server.Start(5050);

		Wait();
	}
	catch(std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	system("pause");
	return 0;
}

