#ifndef CB_CRITICAL_SINGLE_H
#define CB_CRITICAL_SINGLE_H

#include <assert.h>

#include "CB_CriticalSection.h"
#include "CB_Single.h"

// defines for include files
#define RELATION_CRITICAL_SINGLE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
public:\
	ClassTo* _ref##NameTo;\
\
public:\
    static CriticalSection _criticalSection##NameTo;\
\
    void Add##NameTo(ClassTo* item);\
    void Remove##NameTo(ClassTo* item);\
    void Move##NameTo(ClassTo* item);\
    void Replace##NameTo(ClassTo* item, ClassTo* newItem);\
    ClassTo* Get##NameTo() { return _ref##NameTo; };


#define RELATION_CRITICAL_SINGLE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
public:\
    ClassFrom* _ref##NameFrom;\
\
public:\
	ClassFrom* Get##NameFrom() { return _ref##NameFrom; };

// defines implementation

#define INIT_CRITICAL_SINGLE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    INIT_SINGLE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define EXIT_CRITICAL_SINGLE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    EXIT_SINGLE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define REPLACE_CRITICAL_SINGLE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    REPLACE_SINGLE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define INIT_CRITICAL_SINGLE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    INIT_SINGLE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) 

#define EXIT_CRITICAL_SINGLE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    EXIT_SINGLE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define REPLACE_CRITICAL_SINGLE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    REPLACE_SINGLE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define METHODS_CRITICAL_SINGLE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    CriticalSection ClassFrom##::_criticalSection##NameTo;\
void ClassFrom##::Add##NameTo(ClassTo* item)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_SINGLE_ADD(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Remove##NameTo(ClassTo* item)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_SINGLE_REMOVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Move##NameTo(ClassTo* item)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_SINGLE_MOVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Replace##NameTo(ClassTo* item, ClassTo* newItem)\
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    METHOD_SINGLE_REPLACE(ClassFrom, NameFrom, ClassTo, NameTo) \
}


#define METHODS_CRITICAL_SINGLE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#endif