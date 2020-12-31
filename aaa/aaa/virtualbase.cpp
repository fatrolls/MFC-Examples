#include "virtualbase.hpp"

#define MAX_TEST_COUNT 1000 * 1000 * 16
#define TIME_ELAPSE() ( std::clock() - start * 1.0 ) / CLOCKS_PER_SEC

int testvirtualbase(   )
{
    /*
     * 类体系中的尺寸.
     */

    std::cout << "================================ sizeof ================================" << std::endl;
    
    std::cout << "    ----------------------------------------------------------------" << std::endl;
    std::cout << "sizeof( CBaseClass1 )       = " << sizeof( CBaseClass1 ) << std::endl;
    std::cout << std::endl;
    std::cout << "sizeof( CSubClassV1 )       = " << sizeof( CSubClassV1 ) << std::endl;
    std::cout << "sizeof( CSubClassV2 )       = " << sizeof( CSubClassV2 ) << std::endl;
    std::cout << "sizeof( CDiamondClass1 )    = " << sizeof( CDiamondClass1 ) << std::endl;
    std::cout << "sizeof( CDiamondSubClass1 ) = " << sizeof( CDiamondSubClass1 ) << std::endl;
    std::cout << std::endl;
    std::cout << "sizeof( CSubClassN1 )       = " << sizeof( CSubClassN1 ) << std::endl;
    std::cout << "sizeof( CSubClassN2 )       = " << sizeof( CSubClassN2 ) << std::endl;
    std::cout << "sizeof( CMultiClass1 )      = " << sizeof( CMultiClass1 ) << std::endl;
    std::cout << "sizeof( CMultiSubClass1 )   = " << sizeof( CMultiSubClass1 ) << std::endl;
//sizeof( CBaseClass1 )       = 4
//
//sizeof( CSubClassV1 )       = 8
//sizeof( CSubClassV2 )       = 8
//sizeof( CDiamondClass1 )    = 12
//sizeof( CDiamondSubClass1 ) = 12
//
//sizeof( CSubClassN1 )       = 4
//sizeof( CSubClassN2 )       = 4
//sizeof( CMultiClass1 )      = 8
//sizeof( CMultiSubClass1 )   = 8
    std::cout << "    ----------------------------------------------------------------" << std::endl;
    std::cout << "sizeof( CBaseClass2 )       = " << sizeof( CBaseClass2 ) << std::endl;
    std::cout << std::endl;
    std::cout << "sizeof( CSubClassV3 )       = " << sizeof( CSubClassV3 ) << std::endl;
    std::cout << "sizeof( CSubClassV4 )       = " << sizeof( CSubClassV4 ) << std::endl;
    std::cout << "sizeof( CDiamondClass2 )    = " << sizeof( CDiamondClass2 ) << std::endl;
    std::cout << "sizeof( CDiamondSubClass2 ) = " << sizeof( CDiamondSubClass2 ) << std::endl;
    std::cout << std::endl;
    std::cout << "sizeof( CSubClassN3 )       = " << sizeof( CSubClassN3 ) << std::endl;
    std::cout << "sizeof( CSubClassN4 )       = " << sizeof( CSubClassN4 ) << std::endl;
    std::cout << "sizeof( CMultiClass2 )      = " << sizeof( CMultiClass2 ) << std::endl;
    std::cout << "sizeof( CMultiSubClass2 )   = " << sizeof( CMultiSubClass2 ) << std::endl;
//sizeof( CBaseClass2 )       = 4
//
//sizeof( CSubClassV3 )       = 8
//sizeof( CSubClassV4 )       = 8
//sizeof( CDiamondClass2 )    = 12
//sizeof( CDiamondSubClass2 ) = 12
//
//sizeof( CSubClassN3 )       = 4
//sizeof( CSubClassN4 )       = 4
//sizeof( CMultiClass2 )      = 8
//sizeof( CMultiSubClass2 )   = 8
    /*
     * 对象内存布局
     */

    std::cout << "================================ layout ================================" << std::endl;
    
    std::cout << "    --------------------------------MI------------------------------" << std::endl;
    CLayoutSubClass1 *lsc = new CLayoutSubClass1;
    std::cout << "sizeof( CLayoutSubClass1 )   = " << sizeof( CLayoutSubClass1 ) << std::endl;
    std::cout << "CLayoutBase1 offset of CLayoutSubClass1 is " << (char*)(CLayoutBase1 *)lsc - (char*)lsc << std::endl;
    std::cout << "CBaseClass1  offset of CLayoutSubClass1 is " << (char*)(CBaseClass1  *)lsc - (char*)lsc << std::endl;
    std::cout << "CLayoutBase2 offset of CLayoutSubClass1 is " << (char*)(CLayoutBase2 *)lsc - (char*)lsc << std::endl;
    int *ptr = (int*)lsc;
    std::cout << "vbc in CLayoutSubClass1 is " << *(int*)ptr[3] << std::endl;
    delete lsc;

//sizeof( CLayoutSubClass1 )   = 20
//CLayoutBase1 offset of CLayoutSubClass1 is 0
//CBaseClass1  offset of CLayoutSubClass1 is 16
//CLayoutBase2 offset of CLayoutSubClass1 is 8
//vbc in CLayoutSubClass1 is -12   

    std::cout << "    --------------------------------SI------------------------------" << std::endl;
    CSubClassV1 *scv1 = new CSubClassV1( 1 );
    std::cout << "sizeof( CSubClassV1 )   = " << sizeof( CSubClassV1 ) << std::endl;
    std::cout << "CBaseClass1 offset of CSubClassV1 is " << (char*)(CBaseClass1 *)scv1 - (char*)scv1 << std::endl;
    ptr = (int*)scv1;
    std::cout << "vbc in CSubClassV1 is " << *(int*)ptr[0] << std::endl;
    delete scv1;

//sizeof( CSubClassV1 )   = 8
//CBaseClass1 offset of CSubClassV1 is 4
//vbc in CSubClassV1 is 0

    /*
     * 性能测试
     */

    std::cout << "================================ Performance ================================" << std::endl;
    double times[4];
    size_t idx = 0;
    CSubClassV1 *ptr1 = new CDiamondClass1( 1 );
    std::clock_t start = std::clock();
    {
        for ( size_t i = 0; i < MAX_TEST_COUNT; ++i )
            ptr1->m_val = i;
    }
    times[idx++] = TIME_ELAPSE();
    delete static_cast<CDiamondClass1*>( ptr1 );
    CSubClassN1 *ptr2 = new CMultiClass1( 0 );
    start = std::clock();
    {
        for ( size_t i = 0; i < MAX_TEST_COUNT; ++i )
            ptr2->m_val = i;
    }
    times[idx++] = TIME_ELAPSE();
    delete static_cast<CMultiClass1*>( ptr2 );
    std::cout << "CSubClassV1::ptr1->m_val " << times[0] << " s" << std::endl;
    std::cout << "CSubClassN1::ptr2->m_val " << times[1] << " s" << std::endl;
    return 0;

   //CSubClassV1::ptr1->m_val 0.047 s
   //CSubClassN1::ptr2->m_val 0.015 s

}

 

