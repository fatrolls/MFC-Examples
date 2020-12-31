#ifndef CB_CRITICAL_VALUETREE_H
#define CB_CRITICAL_VALUETREE_H

#include <assert.h>

#include "CB_CriticalSection.h"
#include "CB_ValueTree.h"

// defines for include files
#define RELATION_CRITICAL_VALUETREE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
private:\
    ClassTo* _first##NameTo;\
    int _count##NameTo;\
\
public:\
    static CriticalSection _criticalSection##NameTo;\
\
    void Add##NameTo(ClassTo* item);\
    void Remove##NameTo(ClassTo* item);\
    void RemoveAll##NameTo();\
    void DeleteAll##NameTo();\
    void Replace##NameTo(ClassTo* item, ClassTo* newItem);\
    ClassTo* GetFirst##NameTo();\
    ClassTo* GetLast##NameTo();\
    ClassTo* GetNext##NameTo(ClassTo* pos);\
    ClassTo* GetPrev##NameTo(ClassTo* pos);\
    int Get##NameTo##Count();\
    ITERATOR_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define RELATION_NOFILTER_CRITICAL_VALUETREE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
private:\
    ClassTo* _first##NameTo;\
    int _count##NameTo;\
\
public:\
    static CriticalSection _criticalSection##NameTo;\
\
    void Add##NameTo(ClassTo* item);\
    void Remove##NameTo(ClassTo* item);\
    void RemoveAll##NameTo();\
    void DeleteAll##NameTo();\
    void Replace##NameTo(ClassTo* item, ClassTo* newItem);\
    ClassTo* GetFirst##NameTo();\
    ClassTo* GetLast##NameTo();\
    ClassTo* GetNext##NameTo(ClassTo* pos);\
    ClassTo* GetPrev##NameTo(ClassTo* pos);\
    int Get##NameTo##Count();\
    ITERATOR_NOFILTER_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define RELATION_CRITICAL_VALUETREE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
public:\
    ClassFrom* _ref##NameFrom;\
    ClassTo* _parent##NameFrom;\
    ClassTo* _left##NameFrom;\
    ClassTo* _right##NameFrom;\
    ClassTo* _sibling##NameFrom;\
\
public:\
	ClassFrom* Get##NameFrom() { return _ref##NameFrom; };

// defines implementation
#define INIT_CRITICAL_VALUETREE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    INIT_VALUETREE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define EXIT_CRITICAL_VALUETREE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    EXIT_VALUETREE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define REPLACE_CRITICAL_VALUETREE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    REPLACE_VALUETREE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define INIT_CRITICAL_VALUETREE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    INIT_VALUETREE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define EXIT_CRITICAL_VALUETREE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    EXIT_VALUETREE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define REPLACE_CRITICAL_VALUETREE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    REPLACE_VALUETREE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define METHODS_CRITICAL_VALUETREE_ACTIVE(member, ClassFrom, NameFrom, ClassTo, NameTo) \
    CriticalSection ClassFrom##::_criticalSection##NameTo;\
void ClassFrom##::Add##NameTo(ClassTo* item)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_VALUETREE_ADD(member, ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Remove##NameTo(ClassTo* item)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_VALUETREE_REMOVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::RemoveAll##NameTo()\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_VALUETREE_REMOVEALL(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::DeleteAll##NameTo()\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_VALUETREE_DELETEALL(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Replace##NameTo(ClassTo* item, ClassTo* newItem)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_VALUETREE_REPLACE(member, ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
ClassTo* ClassFrom##::GetFirst##NameTo()\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_VALUETREE_GETFIRST(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
ClassTo* ClassFrom##::GetLast##NameTo()\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_VALUETREE_GETLAST(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
ClassTo* ClassFrom##::GetNext##NameTo(ClassTo* pos)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_VALUETREE_GETNEXT(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
ClassTo* ClassFrom##::GetPrev##NameTo(ClassTo* pos)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_VALUETREE_GETPREV(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
int ClassFrom##::Get##NameTo##Count()\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_VALUETREE_GETCOUNT(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define METHODS_CRITICAL_VALUETREE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define BODY_CRITICAL_VALUETREE_FIND(member, value, ClassFrom, NameFrom, ClassTo, NameTo) \
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    BODY_VALUETREE_FIND(member, value, ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define BODY_CRITICAL_VALUETREE_FINDREVERSE(member, value, ClassFrom, NameFrom, ClassTo, NameTo) \
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    BODY_VALUETREE_FINDREVERSE(member, value, ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define WRITE_CRITICAL_VALUETREE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    WRITE_VALUETREE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define READ_CRITICAL_VALUETREE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    READ_VALUETREE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#endif
