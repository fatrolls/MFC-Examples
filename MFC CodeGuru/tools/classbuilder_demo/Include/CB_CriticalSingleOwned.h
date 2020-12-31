#ifndef CB_CRITICAL_SINGLE_OWNED_H
#define CB_CRITICAL_SINGLE_OWNED_H

#include "CB_CriticalSingle.h"
#include "CB_SingleOwned.h"

// defines for include files
#define RELATION_CRITICAL_SINGLE_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
public:\
	ClassTo* _ref##NameTo;\
\
public:\
    static CriticalSection _criticalSection##NameTo;\
\
protected:\
    void Add##NameTo(ClassTo* item);\
    void Remove##NameTo(ClassTo* item);\
    void Move##NameTo(ClassTo* item);\
    void Replace##NameTo(ClassTo* item, ClassTo* newItem);\
\
public:\
    ClassTo* Get##NameTo() {return _ref##NameTo;};

#define RELATION_CRITICAL_SINGLE_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
	RELATION_CRITICAL_SINGLE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo)

// defines implementation
#define INIT_CRITICAL_SINGLE_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
   INIT_SINGLE_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define EXIT_CRITICAL_SINGLE_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    EXIT_SINGLE_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define REPLACE_CRITICAL_SINGLE_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    REPLACE_SINGLE_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define INIT_CRITICAL_SINGLE_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    INIT_SINGLE_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define EXIT_CRITICAL_SINGLE_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    EXIT_SINGLE_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define REPLACE_CRITICAL_SINGLE_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
{\
    CriticalSectionLock lock(ClassFrom::_criticalSection##NameTo);\
    REPLACE_SINGLE_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define METHODS_CRITICAL_SINGLE_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    METHODS_CRITICAL_SINGLE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) 

#define METHODS_CRITICAL_SINGLE_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#endif