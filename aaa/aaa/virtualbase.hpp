#pragma  once
#include <ctime>
#include <iostream>

/*
 * 带有数据成员的基类
 */

struct CBaseClass1

{
    CBaseClass1( size_t i ) : m_val( i ) {}
    size_t m_val;
};

/*
 * 虚拟继承体系
 */

struct CSubClassV1 : public virtual CBaseClass1
{
    CSubClassV1( size_t i ) : CBaseClass1( i ) {}
};

struct CSubClassV2 : public virtual CBaseClass1
{
    CSubClassV2( size_t i ) : CBaseClass1( i ) {}
};

struct CDiamondClass1 : public CSubClassV1, public CSubClassV2
{
    CDiamondClass1( size_t i ) : CBaseClass1( i ), CSubClassV1( i ), CSubClassV2( i ) {}
};

struct CDiamondSubClass1 : public CDiamondClass1
{
    CDiamondSubClass1( size_t i ) : CBaseClass1( i ), CDiamondClass1( i ) {}
};

/*
 * 正常继承体系
 */

struct CSubClassN1 : public CBaseClass1
{
    CSubClassN1( size_t i ) : CBaseClass1( i ) {}
};

struct CSubClassN2 : public CBaseClass1
{
    CSubClassN2( size_t i ) : CBaseClass1( i ) {}
};

struct CMultiClass1 : public CSubClassN1, public CSubClassN2
{
    CMultiClass1( size_t i ) : CSubClassN1( i ), CSubClassN2( i ) {}
};

struct CMultiSubClass1 : public CMultiClass1
{
    CMultiSubClass1( size_t i ) : CMultiClass1( i ) {}
};

/*
 * 不带有数据成员的接口基类
 */

struct CBaseClass2
{
    virtual void func() {};
    virtual ~CBaseClass2() {}
};

/*
 * 虚拟继承体系
 */

// struct CBaseClassX { CBaseClassX() {i1 = i2 = 0xFFFFFFFF;} size_t i1, i2;};

struct CSubClassV3 : public virtual CBaseClass2
{
};

struct CSubClassV4 : public virtual CBaseClass2
{
};

struct CDiamondClass2 : public CSubClassV3, public CSubClassV4
{
};

struct CDiamondSubClass2 : public CDiamondClass2
{
};

/*
 * 正常继承体系
 */

struct CSubClassN3 : public CBaseClass2
{
};

struct CSubClassN4 : public CBaseClass2
{
};

struct CMultiClass2 : public CSubClassN3, public CSubClassN4
{
};

struct CMultiSubClass2 : public CMultiClass2
{
};

/*
 * 内存布局用类声明.
 */

struct CLayoutBase1
{
    CLayoutBase1() : m_val1( 0 ), m_val2( 1 ) {}
    size_t m_val1, m_val2;
};

struct CLayoutBase2
{
    CLayoutBase2() : m_val1( 3 ) {}
    size_t m_val1;
};

struct CLayoutSubClass1 : public virtual CBaseClass1, public CLayoutBase1, public CLayoutBase2
{
    CLayoutSubClass1() : CBaseClass1( 2 ) {}
};
int testvirtualbase( );