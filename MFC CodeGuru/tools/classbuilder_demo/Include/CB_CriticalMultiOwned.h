#ifndef CB_CRITICAL_MULTI_OWNED_H
#define CB_CRITICAL_MULTI_OWNED_H

#include "CB_CriticalMulti.h"
#include "CB_MultiOwned.h"

// defines for include files
#define RELATION_CRITICAL_MULTI_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
public:\
    ClassTo* _first##NameTo;\
    ClassTo* _last##NameTo;\
    int _count##NameTo;\
\
public:\
    static CriticalSection _criticalSection##NameTo;\
\
protected:\
    void Add##NameTo##First(ClassTo* item);\
    void Add##NameTo##Last(ClassTo* item);\
    void Add##NameTo##After(ClassTo* item, ClassTo* pos);\
    void Add##NameTo##Before(ClassTo* item, ClassTo* pos);\
    void Remove##NameTo(ClassTo* item);\
    void Replace##NameTo(ClassTo* item, ClassTo* newItem);\
\
public:\
    void DeleteAll##NameTo();\
    ClassTo* GetFirst##NameTo();\
    ClassTo* GetLast##NameTo();\
    ClassTo* GetNext##NameTo(ClassTo* pos);\
    ClassTo* GetPrev##NameTo(ClassTo* pos);\
    int Get##NameTo##Count();\
    void Move##NameTo##First(ClassTo* item);\
    void Move##NameTo##Last(ClassTo* item);\
    void Move##NameTo##After(ClassTo* item, ClassTo* pos);\
    void Move##NameTo##Before(ClassTo* item, ClassTo* pos);\
    void Sort##NameTo(int (*comp)(ClassTo*, ClassTo*));\
    ITERATOR_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define RELATION_NOFILTER_CRITICAL_MULTI_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
public:\
    ClassTo* _first##NameTo;\
    ClassTo* _last##NameTo;\
    int _count##NameTo;\
\
public:\
    static CriticalSection _criticalSection##NameTo;\
\
protected:\
    void Add##NameTo##First(ClassTo* item);\
    void Add##NameTo##Last(ClassTo* item);\
    void Add##NameTo##After(ClassTo* item, ClassTo* pos);\
    void Add##NameTo##Before(ClassTo* item, ClassTo* pos);\
    void Remove##NameTo(ClassTo* item);\
    void Replace##NameTo(ClassTo* item, ClassTo* newItem);\
\
public:\
    void DeleteAll##NameTo();\
    ClassTo* GetFirst##NameTo();\
    ClassTo* GetLast##NameTo();\
    ClassTo* GetNext##NameTo(ClassTo* pos);\
    ClassTo* GetPrev##NameTo(ClassTo* pos);\
    int Get##NameTo##Count();\
    void Move##NameTo##First(ClassTo* item);\
    void Move##NameTo##Last(ClassTo* item);\
    void Move##NameTo##After(ClassTo* item, ClassTo* pos);\
    void Move##NameTo##Before(ClassTo* item, ClassTo* pos);\
    void Sort##NameTo(int (*comp)(ClassTo*, ClassTo*));\
    ITERATOR_NOFILTER_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define RELATION_CRITICAL_MULTI_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
	RELATION_CRITICAL_MULTI_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define INIT_CRITICAL_MULTI_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    INIT_MULTI_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define EXIT_CRITICAL_MULTI_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    EXIT_MULTI_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define REPLACE_CRITICAL_MULTI_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    REPLACE_MULTI_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define INIT_CRITICAL_MULTI_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    INIT_MULTI_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define EXIT_CRITICAL_MULTI_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    EXIT_MULTI_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define REPLACE_CRITICAL_MULTI_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    REPLACE_MULTI_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define METHODS_CRITICAL_MULTI_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    CriticalSection ClassFrom##::_criticalSection##NameTo;\
void ClassFrom##::Add##NameTo##First(ClassTo* item)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_MULTI_ADDFIRST(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Add##NameTo##Last(ClassTo* item)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_MULTI_ADDLAST(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Add##NameTo##After(ClassTo* item, ClassTo* pos)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_MULTI_ADDAFTER(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Add##NameTo##Before(ClassTo* item, ClassTo* pos)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_MULTI_ADDBEFORE(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Remove##NameTo(ClassTo* item)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_MULTI_REMOVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::DeleteAll##NameTo()\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_MULTI_DELETEALL(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Replace##NameTo(ClassTo* item, ClassTo* newItem)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_MULTI_REPLACE(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
ClassTo* ClassFrom##::GetFirst##NameTo()\
{\
    METHOD_MULTI_GETFIRST(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
ClassTo* ClassFrom##::GetLast##NameTo()\
{\
    METHOD_MULTI_GETLAST(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
ClassTo* ClassFrom##::GetNext##NameTo(ClassTo* pos)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_MULTI_GETNEXT(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
ClassTo* ClassFrom##::GetPrev##NameTo(ClassTo* pos)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_MULTI_GETPREV(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
int ClassFrom##::Get##NameTo##Count()\
{\
    METHOD_MULTI_GETCOUNT(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Move##NameTo##First(ClassTo* item)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_MULTI_MOVEFIRST(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Move##NameTo##Last(ClassTo* item)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_MULTI_MOVELAST(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Move##NameTo##After(ClassTo* item, ClassTo* pos)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_MULTI_MOVEAFTER(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Move##NameTo##Before(ClassTo* item, ClassTo* pos)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_MULTI_MOVEBEFORE(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Sort##NameTo##(int (*comp)(ClassTo*, ClassTo*))\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_MULTI_SORT(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define METHODS_CRITICAL_MULTI_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#endif