#ifndef CB_CRITICAL_STATIC_MULTI_H
#define CB_CRITICAL_STATIC_MULTI_H

#include <assert.h>

#include "CB_CriticalSection.h"
#include "CB_StaticMulti.h"

// defines for include files
#define RELATION_CRITICAL_STATIC_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
private:\
    static ClassTo* _first##NameTo;\
    static ClassTo* _last##NameTo;\
    static int _count##NameTo;\
\
public:\
    static CriticalSection _criticalSection##NameTo;\
\
    static void Add##NameTo##First(ClassTo* item);\
    static void Add##NameTo##Last(ClassTo* item);\
    static void Add##NameTo##After(ClassTo* item, ClassTo* pos);\
    static void Add##NameTo##Before(ClassTo* item, ClassTo* pos);\
    static void Remove##NameTo(ClassTo* item);\
    static void RemoveAll##NameTo();\
    static void DeleteAll##NameTo();\
    static void Replace##NameTo(ClassTo* item, ClassTo* newItem);\
    static ClassTo* GetFirst##NameTo();\
    static ClassTo* GetLast##NameTo();\
    static ClassTo* GetNext##NameTo(ClassTo* pos);\
    static ClassTo* GetPrev##NameTo(ClassTo* pos);\
    static int Get##NameTo##Count();\
    static int Includes##NameTo(ClassTo* item);\
    static void Move##NameTo##First(ClassTo* item);\
    static void Move##NameTo##Last(ClassTo* item);\
    static void Move##NameTo##After(ClassTo* item, ClassTo* pos);\
    static void Move##NameTo##Before(ClassTo* item, ClassTo* pos);\
    static void Sort##NameTo(int (*comp)(ClassTo*, ClassTo*));\
    ITERATOR_STATIC_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define RELATION_NOFILTER_CRITICAL_STATIC_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
private:\
    static ClassTo* _first##NameTo;\
    static ClassTo* _last##NameTo;\
    static int _count##NameTo;\
\
public:\
    static CriticalSection _criticalSection##NameTo;\
\
    static void Add##NameTo##First(ClassTo* item);\
    static void Add##NameTo##Last(ClassTo* item);\
    static void Add##NameTo##After(ClassTo* item, ClassTo* pos);\
    static void Add##NameTo##Before(ClassTo* item, ClassTo* pos);\
    static void Remove##NameTo(ClassTo* item);\
    static void RemoveAll##NameTo();\
    static void DeleteAll##NameTo();\
    static void Replace##NameTo(ClassTo* item, ClassTo* newItem);\
    static ClassTo* GetFirst##NameTo();\
    static ClassTo* GetLast##NameTo();\
    static ClassTo* GetNext##NameTo(ClassTo* pos);\
    static ClassTo* GetPrev##NameTo(ClassTo* pos);\
    static int Get##NameTo##Count();\
    static int Includes##NameTo(ClassTo* item);\
    static void Move##NameTo##First(ClassTo* item);\
    static void Move##NameTo##Last(ClassTo* item);\
    static void Move##NameTo##After(ClassTo* item, ClassTo* pos);\
    static void Move##NameTo##Before(ClassTo* item, ClassTo* pos);\
    static void Sort##NameTo(int (*comp)(ClassTo*, ClassTo*));\
    ITERATOR_NOFILTER_STATIC_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define RELATION_CRITICAL_STATIC_MULTI_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
public:\
    ClassTo* _prev##NameFrom;\
    ClassTo* _next##NameFrom;

#define INIT_CRITICAL_STATIC_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) 

#define EXIT_CRITICAL_STATIC_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define REPLACE_CRITICAL_STATIC_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define INIT_CRITICAL_STATIC_MULTI_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    INIT_STATIC_MULTI_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define EXIT_CRITICAL_STATIC_MULTI_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    EXIT_STATIC_MULTI_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define REPLACE_CRITICAL_STATIC_MULTI_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    REPLACE_STATIC_MULTI_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define METHODS_CRITICAL_STATIC_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    ClassTo* ClassFrom##::_first##NameTo = (ClassTo*)0;\
    ClassTo* ClassFrom##::_last##NameTo = (ClassTo*)0;\
	int ClassFrom##::_count##NameTo = 0;\
    CriticalSection ClassFrom##::_criticalSection##NameTo;\
void ClassFrom##::Add##NameTo##First(ClassTo* item)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_STATIC_MULTI_ADDFIRST(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Add##NameTo##Last(ClassTo* item)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_STATIC_MULTI_ADDLAST(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Add##NameTo##After(ClassTo* item, ClassTo* pos)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_STATIC_MULTI_ADDAFTER(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Add##NameTo##Before(ClassTo* item, ClassTo* pos)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_STATIC_MULTI_ADDBEFORE(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Remove##NameTo(ClassTo* item)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_STATIC_MULTI_REMOVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::RemoveAll##NameTo()\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_STATIC_MULTI_REMOVEALL(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::DeleteAll##NameTo()\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_STATIC_MULTI_DELETEALL(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Replace##NameTo(ClassTo* item, ClassTo* newItem)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
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
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_STATIC_MULTI_GETNEXT(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
ClassTo* ClassFrom##::GetPrev##NameTo(ClassTo* pos)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_STATIC_MULTI_GETPREV(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
int ClassFrom##::Get##NameTo##Count()\
{\
    METHOD_STATIC_MULTI_GETCOUNT(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
int ClassFrom##::Includes##NameTo(ClassTo* item)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_STATIC_MULTI_INCLUDES(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Move##NameTo##First(ClassTo* item)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_STATIC_MULTI_MOVEFIRST(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Move##NameTo##Last(ClassTo* item)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_STATIC_MULTI_MOVELAST(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Move##NameTo##After(ClassTo* item, ClassTo* pos)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_STATIC_MULTI_MOVEAFTER(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Move##NameTo##Before(ClassTo* item, ClassTo* pos)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_STATIC_MULTI_MOVEBEFORE(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Sort##NameTo(int (*comp)(ClassTo*, ClassTo*))\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_STATIC_MULTI_SORT(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define METHODS_CRITICAL_STATIC_MULTI_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#endif