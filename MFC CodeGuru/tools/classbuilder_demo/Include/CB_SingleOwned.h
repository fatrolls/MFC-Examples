#ifndef CB_SINGLE_OWNED_H
#define CB_SINGLE_OWNED_H

#include "CB_Single.h"

// defines for include files
#define RELATION_SINGLE_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
public:\
	ClassTo* _ref##NameTo;\
\
protected:\
    void Add##NameTo(ClassTo* item);\
    void Remove##NameTo(ClassTo* item);\
    void Replace##NameTo(ClassTo* item, ClassTo* newItem);\
\
public:\
    void Move##NameTo(ClassTo* item);\
    ClassTo* Get##NameTo() {return _ref##NameTo;};

#define RELATION_SINGLE_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
	RELATION_SINGLE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo)

// defines implementation
#define INIT_SINGLE_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
   INIT_SINGLE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define EXIT_SINGLE_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    if (_ref##NameTo)\
        delete _ref##NameTo;

#define REPLACE_SINGLE_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    REPLACE_SINGLE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define INIT_SINGLE_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
    assert(p##NameFrom);\
    assert(p##NameFrom->_ref##NameTo == (ClassTo*)0);\
\
    _ref##NameFrom = p##NameFrom;\
    p##NameFrom->_ref##NameTo = this;

#define EXIT_SINGLE_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    EXIT_SINGLE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define REPLACE_SINGLE_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
    assert(pOld);\
	assert(pOld->_ref##NameFrom);\
    assert(pOld->_ref##NameFrom->_ref##NameTo == pOld);\
\
    _ref##NameFrom = pOld->_ref##NameFrom;\
    _ref##NameFrom->_ref##NameTo = this;\
    pOld->_ref##NameFrom = (ClassFrom*)0;

#define METHODS_SINGLE_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    METHODS_SINGLE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) 

#define METHODS_SINGLE_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#endif
