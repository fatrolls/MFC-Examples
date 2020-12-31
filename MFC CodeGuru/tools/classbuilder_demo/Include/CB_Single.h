#ifndef CB_SINGLE_H
#define CB_SINGLE_H

#include <assert.h>

// defines for include files
#define RELATION_SINGLE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
public:\
	ClassTo* _ref##NameTo;\
\
public:\
    void Add##NameTo(ClassTo* item);\
    void Remove##NameTo(ClassTo* item);\
    void Move##NameTo(ClassTo* item);\
    void Replace##NameTo(ClassTo* item, ClassTo* newItem);\
    ClassTo* Get##NameTo() { return _ref##NameTo; };

#define RELATION_SINGLE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
public:\
    ClassFrom* _ref##NameFrom;\
\
public:\
	ClassFrom* Get##NameFrom() { return _ref##NameFrom; };

// defines implementation
#define INIT_SINGLE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    _ref##NameTo = (ClassTo*)0;

#define EXIT_SINGLE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    if (_ref##NameTo)\
        Remove##NameTo(_ref##NameTo);

#define REPLACE_SINGLE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    _ref##NameTo = pOld->_ref##NameTo;\
    pOld->_ref##NameTo = (ClassTo*)0;\
    if (_ref##NameTo)\
        _ref##NameTo->_ref##NameFrom = this;

#define INIT_SINGLE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    _ref##NameFrom = (ClassFrom*)0;

#define EXIT_SINGLE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
    if (_ref##NameFrom)\
    {\
        assert(_ref##NameFrom->_ref##NameTo == this);\
\
        _ref##NameFrom->_ref##NameTo = (ClassTo*)0;\
        _ref##NameFrom = (ClassFrom*)0;\
    }

#define REPLACE_SINGLE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
    assert(pOld);\
	if (pOld->_ref##NameFrom)\
    {\
        assert(pOld->_ref##NameFrom->_ref##NameTo == pOld);\
\
        _ref##NameFrom = pOld->_ref##NameFrom;\
        _ref##NameFrom->_ref##NameTo = this;\
        pOld->_ref##NameFrom = (ClassFrom*)0;\
    }\
    else\
        _ref##NameFrom = (ClassFrom*)0;

#define METHODS_SINGLE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
void ClassFrom##::Add##NameTo(ClassTo* item)\
{\
    METHOD_SINGLE_ADD(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Remove##NameTo(ClassTo* item)\
{\
    METHOD_SINGLE_REMOVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Move##NameTo(ClassTo* item)\
{\
    METHOD_SINGLE_MOVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Replace##NameTo(ClassTo* item, ClassTo* newItem)\
{\
    METHOD_SINGLE_REPLACE(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define METHOD_SINGLE_ADD(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
    assert(_ref##NameTo == (ClassTo*)0);\
    assert(item);\
    assert(item->_ref##NameFrom == (ClassFrom*)0);\
\
    item->_ref##NameFrom = this;\
    _ref##NameTo = item;

#define METHOD_SINGLE_REMOVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
    assert(_ref##NameTo == item);\
    assert(item);\
    assert(item->_ref##NameFrom == this);\
\
    item->_ref##NameFrom = (ClassFrom*)0;\
    _ref##NameTo = (ClassTo*)0;

#define METHOD_SINGLE_MOVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(item);\
    assert(item->_ref##NameFrom);\
    item->_ref##NameFrom->Remove##NameTo(item);\
    Add##NameTo(item);

#define METHOD_SINGLE_REPLACE(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
    assert(_ref##NameTo == item);\
    assert(item);\
    assert(item->_ref##NameFrom == this);\
    assert(newItem);\
    assert(newItem->_ref##NameFrom == (ClassFrom*)0);\
\
    item->_ref##NameFrom = (ClassFrom*)0;\
    newItem->_ref##NameFrom = this;\
    _ref##NameTo = newItem;

#define METHODS_SINGLE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define WRITE_SINGLE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    if (Get##NameTo())\
        rCArchive << Get##NameTo()->_index;\
    else\
        rCArchive << int(0);

#define READ_SINGLE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    {\
        int index;\
\
        rCArchive >> index;\
        if (index && !Get##NameTo())\
            Add##NameTo((ClassTo*)(pointerArray[index]));\
    }

#endif
