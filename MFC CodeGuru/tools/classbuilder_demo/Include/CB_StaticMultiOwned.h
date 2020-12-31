#ifndef CB_MULTI_STATIC_OWNED_H
#define CB_MULTI_STATIC_OWNED_H

#include "CB_StaticMulti.h"

// defines for include files
#define RELATION_STATIC_MULTI_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
public:\
    static ClassTo* _first##NameTo;\
    static ClassTo* _last##NameTo;\
    static int _count##NameTo;\
\
protected:\
    static void Add##NameTo##First(ClassTo* item);\
    static void Add##NameTo##Last(ClassTo* item);\
    static void Add##NameTo##After(ClassTo* item, ClassTo* pos);\
    static void Add##NameTo##Before(ClassTo* item, ClassTo* pos);\
    static void Remove##NameTo(ClassTo* item);\
    static void Replace##NameTo(ClassTo* item, ClassTo* newItem);\
\
public:\
    static void DeleteAll##NameTo();\
    static ClassTo* GetFirst##NameTo();\
    static ClassTo* GetLast##NameTo();\
    static ClassTo* GetNext##NameTo(ClassTo* pos);\
    static ClassTo* GetPrev##NameTo(ClassTo* pos);\
    static int Get##NameTo##Count();\
    static void Move##NameTo##First(ClassTo* item);\
    static void Move##NameTo##Last(ClassTo* item);\
    static void Move##NameTo##After(ClassTo* item, ClassTo* pos);\
    static void Move##NameTo##Before(ClassTo* item, ClassTo* pos);\
    static void Sort##NameTo(int (*comp)(ClassTo*, ClassTo*));\
    ITERATOR_STATIC_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define RELATION_NOFILTER_STATIC_MULTI_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
public:\
    static ClassTo* _first##NameTo;\
    static ClassTo* _last##NameTo;\
    static int _count##NameTo;\
\
protected:\
    static void Add##NameTo##First(ClassTo* item);\
    static void Add##NameTo##Last(ClassTo* item);\
    static void Add##NameTo##After(ClassTo* item, ClassTo* pos);\
    static void Add##NameTo##Before(ClassTo* item, ClassTo* pos);\
    static void Remove##NameTo(ClassTo* item);\
    static void Replace##NameTo(ClassTo* item, ClassTo* newItem);\
\
public:\
    static void DeleteAll##NameTo();\
    static ClassTo* GetFirst##NameTo();\
    static ClassTo* GetLast##NameTo();\
    static ClassTo* GetNext##NameTo(ClassTo* pos);\
    static ClassTo* GetPrev##NameTo(ClassTo* pos);\
    static int Get##NameTo##Count();\
    static void Move##NameTo##First(ClassTo* item);\
    static void Move##NameTo##Last(ClassTo* item);\
    static void Move##NameTo##After(ClassTo* item, ClassTo* pos);\
    static void Move##NameTo##Before(ClassTo* item, ClassTo* pos);\
    static void Sort##NameTo(int (*comp)(ClassTo*, ClassTo*));\
    ITERATOR_NOFILTER_STATIC_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define RELATION_STATIC_MULTI_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
	RELATION_STATIC_MULTI_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo)

// defines implementation
#define INIT_STATIC_MULTI_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define EXIT_STATIC_MULTI_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define REPLACE_STATIC_MULTI_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define INIT_STATIC_MULTI_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
	ClassFrom::_count##NameTo++;\
\
    if (ClassFrom::_last##NameTo)\
    {\
        _next##NameFrom = (ClassTo*)0;\
        _prev##NameFrom = ClassFrom::_last##NameTo;\
        _prev##NameFrom->_next##NameFrom = this;\
        ClassFrom::_last##NameTo = this;\
    }\
    else\
    {\
        _prev##NameFrom = (ClassTo*)0;\
        _next##NameFrom = (ClassTo*)0;\
        ClassFrom::_first##NameTo = ClassFrom::_last##NameTo = this;\
    }

#define EXIT_STATIC_MULTI_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    EXIT_STATIC_MULTI_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define REPLACE_STATIC_MULTI_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
    assert(pOld);\
    ClassFrom::NameTo##Iterator::Check(pOld, this);\
\
    if (pOld->_next##NameFrom)\
        pOld->_next##NameFrom->_prev##NameFrom = this;\
    else\
        ClassFrom::_last##NameTo = this;\
\
    if (pOld->_prev##NameFrom)\
        pOld->_prev##NameFrom->_next##NameFrom = this;\
    else\
        ClassFrom::_first##NameTo = this;\
\
    _next##NameFrom = pOld->_next##NameFrom;\
    _prev##NameFrom = pOld->_prev##NameFrom;\
\
    pOld->_next##NameFrom = (ClassTo*)0;\
    pOld->_prev##NameFrom = (ClassTo*)0;

#define METHODS_STATIC_MULTI_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    ClassTo* ClassFrom##::_first##NameTo = (ClassTo*)0;\
    ClassTo* ClassFrom##::_last##NameTo = (ClassTo*)0;\
	int ClassFrom##::_count##NameTo = 0;\
void ClassFrom##::Add##NameTo##First(ClassTo* item)\
{\
    METHOD_STATIC_MULTI_ADDFIRST(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Add##NameTo##Last(ClassTo* item)\
{\
    METHOD_STATIC_MULTI_ADDLAST(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Add##NameTo##After(ClassTo* item, ClassTo* pos)\
{\
    METHOD_STATIC_MULTI_ADDAFTER(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Add##NameTo##Before(ClassTo* item, ClassTo* pos)\
{\
    METHOD_STATIC_MULTI_ADDBEFORE(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Remove##NameTo(ClassTo* item)\
{\
    METHOD_STATIC_MULTI_REMOVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::DeleteAll##NameTo()\
{\
    METHOD_STATIC_MULTI_DELETEALL(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Replace##NameTo(ClassTo* item, ClassTo* newItem)\
{\
    METHOD_STATIC_MULTI_REPLACE(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
ClassTo* ClassFrom##::GetFirst##NameTo()\
{\
    METHOD_STATIC_MULTI_GETFIRST(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
ClassTo* ClassFrom##::GetLast##NameTo()\
{\
    METHOD_STATIC_MULTI_GETLAST(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
ClassTo* ClassFrom##::GetNext##NameTo(ClassTo* pos)\
{\
    METHOD_STATIC_MULTI_GETNEXT(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
ClassTo* ClassFrom##::GetPrev##NameTo(ClassTo* pos)\
{\
    METHOD_STATIC_MULTI_GETPREV(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
int ClassFrom##::Get##NameTo##Count()\
{\
    METHOD_STATIC_MULTI_GETCOUNT(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Move##NameTo##First(ClassTo* item)\
{\
    METHOD_STATIC_MULTI_MOVEFIRST(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Move##NameTo##Last(ClassTo* item)\
{\
    METHOD_STATIC_MULTI_MOVELAST(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Move##NameTo##After(ClassTo* item, ClassTo* pos)\
{\
    METHOD_STATIC_MULTI_MOVEAFTER(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Move##NameTo##Before(ClassTo* item, ClassTo* pos)\
{\
    METHOD_STATIC_MULTI_MOVEBEFORE(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Sort##NameTo(int (*comp)(ClassTo*, ClassTo*))\
{\
    METHOD_STATIC_MULTI_SORT(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define METHODS_STATIC_MULTI_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#endif
