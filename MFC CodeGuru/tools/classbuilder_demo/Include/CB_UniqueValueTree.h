#ifndef CB_UNIQUEVALUETREE_H
#define CB_UNIQUEVALUETREE_H

#include <assert.h>

#include "CB_IteratorMulti.h"

// defines for include files
#define RELATION_UNIQUEVALUETREE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
private:\
    ClassTo* _first##NameTo;\
    int _count##NameTo;\
\
public:\
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

#define RELATION_NOFILTER_UNIQUEVALUETREE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
private:\
    ClassTo* _first##NameTo;\
    int _count##NameTo;\
\
public:\
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

#define RELATION_UNIQUEVALUETREE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
public:\
    ClassFrom* _ref##NameFrom;\
    ClassTo* _parent##NameFrom;\
    ClassTo* _left##NameFrom;\
    ClassTo* _right##NameFrom;\
\
public:\
	ClassFrom* Get##NameFrom() { return _ref##NameFrom; };

// defines implementation
#define INIT_UNIQUEVALUETREE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    _first##NameTo = (ClassTo*)0;\
    _count##NameTo = 0;

#define EXIT_UNIQUEVALUETREE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    { for (ClassTo* item = GetFirst##NameTo(); item; item = GetFirst##NameTo())\
          Remove##NameTo(item); }

#define REPLACE_UNIQUEVALUETREE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    _first##NameTo = pOld->_first##NameTo;\
    _count##NameTo = pOld->_count##NameTo;\
    pOld->_first##NameTo = (ClassTo*)0;\
    { for (ClassTo* item = GetFirst##NameTo(); item; item = GetNext##NameTo(item))\
          item->_ref##NameFrom = this; }

#define INIT_UNIQUEVALUETREE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    _ref##NameFrom = (ClassFrom*)0;\
    _parent##NameFrom = (ClassTo*)0;\
    _left##NameFrom = (ClassTo*)0;\
    _right##NameFrom = (ClassTo*)0;

#define EXIT_UNIQUEVALUETREE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    if (_ref##NameFrom)\
        _ref##NameFrom->Remove##NameTo(this);

#define REPLACE_UNIQUEVALUETREE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    _ref##NameFrom = (ClassFrom*)0;\
    _parent##NameFrom = (ClassTo*)0;\
    _left##NameFrom = (ClassTo*)0;\
    _right##NameFrom = (ClassTo*)0;\
    if (pOld->_ref##NameFrom)\
        pOld->_ref##NameFrom->Replace##NameTo(pOld, this);

#define METHODS_UNIQUEVALUETREE_ACTIVE(member, ClassFrom, NameFrom, ClassTo, NameTo) \
void ClassFrom##::Add##NameTo(ClassTo* item)\
{\
    METHOD_UNIQUEVALUETREE_ADD(member, ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Remove##NameTo(ClassTo* item)\
{\
    METHOD_UNIQUEVALUETREE_REMOVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::RemoveAll##NameTo()\
{\
    METHOD_UNIQUEVALUETREE_REMOVEALL(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::DeleteAll##NameTo()\
{\
    METHOD_UNIQUEVALUETREE_DELETEALL(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Replace##NameTo(ClassTo* item, ClassTo* newItem)\
{\
    METHOD_UNIQUEVALUETREE_REPLACE(member, ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
ClassTo* ClassFrom##::GetFirst##NameTo()\
{\
    METHOD_UNIQUEVALUETREE_GETFIRST(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
ClassTo* ClassFrom##::GetLast##NameTo()\
{\
    METHOD_UNIQUEVALUETREE_GETLAST(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
ClassTo* ClassFrom##::GetNext##NameTo(ClassTo* pos)\
{\
    METHOD_UNIQUEVALUETREE_GETNEXT(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
ClassTo* ClassFrom##::GetPrev##NameTo(ClassTo* pos)\
{\
    METHOD_UNIQUEVALUETREE_GETPREV(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
int ClassFrom##::Get##NameTo##Count()\
{\
    METHOD_UNIQUEVALUETREE_GETCOUNT(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define METHOD_UNIQUEVALUETREE_ADD(member, ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
\
    assert(item);\
    assert(item->_ref##NameFrom == (ClassFrom*)0);\
\
    _count##NameTo++;\
\
    item->_ref##NameFrom = this;\
\
    if (_first##NameTo)\
    {\
        ClassTo* current = _first##NameTo;\
        unsigned long bit = 0x1;\
        while (1)\
        {\
            assert(current->member != item->member);\
\
            if ((current->member & bit) == (item->member & bit))\
            {\
                if (current->_left##NameFrom)\
                {\
                    current = current->_left##NameFrom;\
                }\
                else\
                {\
                    current->_left##NameFrom = item;\
                    item->_parent##NameFrom = current;\
                    break;\
                }\
            }\
            else\
            {\
                if (current->_right##NameFrom)\
                {\
                    current = current->_right##NameFrom;\
                }\
                else\
                {\
                    current->_right##NameFrom = item;\
                    item->_parent##NameFrom = current;\
                    break;\
                }\
            }\
\
            bit <<= 1;\
        }\
    }\
    else\
    {\
        _first##NameTo = item;\
    }

#define METHOD_UNIQUEVALUETREE_REMOVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
\
    assert(item);\
    assert(item->_ref##NameFrom == this);\
\
    ClassFrom##::##NameTo##Iterator::Check(item);\
\
    _count##NameTo--;\
\
    ClassTo* replacement = 0;\
    ClassTo* move = 0;\
    if (item->_left##NameFrom)\
    {\
        replacement = item->_left##NameFrom;\
        replacement->_parent##NameFrom = item->_parent##NameFrom;\
        move = item->_right##NameFrom;\
    }\
    else if (item->_right##NameFrom)\
    {\
        replacement = item->_right##NameFrom;\
        replacement->_parent##NameFrom = item->_parent##NameFrom;\
    }\
\
    ClassTo* parent = item->_parent##NameFrom;\
    if (parent)\
    {\
        if (parent->_left##NameFrom == item)\
        {\
            parent->_left##NameFrom = replacement;\
        }\
        else\
        {\
            parent->_right##NameFrom = replacement;\
        }\
    }\
    else\
    {\
        _first##NameTo = replacement;\
    }\
\
    if (replacement)\
    {\
        while (1)\
        {\
            ClassTo* tmp = replacement->_right##NameFrom;\
            replacement->_right##NameFrom = move;\
            if (move)\
            {\
                move->_parent##NameFrom = replacement;\
            }\
            \
            if (!replacement->_left##NameFrom)\
            {\
                if (tmp)\
                {\
                    replacement->_left##NameFrom = tmp;\
                    tmp = 0;\
                }\
                else\
                {\
                    break;\
                }\
            }\
            move = tmp;\
            replacement = replacement->_left##NameFrom;\
        }\
    }\
\
    item->_ref##NameFrom = (ClassFrom*)0;\
    item->_parent##NameFrom = (ClassTo*)0;\
    item->_left##NameFrom = (ClassTo*)0;\
    item->_right##NameFrom = (ClassTo*)0;

#define METHOD_UNIQUEVALUETREE_REMOVEALL(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
\
    for (ClassTo* item = GetFirst##NameTo(); item; item = GetFirst##NameTo())\
          Remove##NameTo(item);

#define METHOD_UNIQUEVALUETREE_DELETEALL(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
\
    for (ClassTo* item = GetFirst##NameTo(); item; item = GetFirst##NameTo())\
          delete item;

#define METHOD_UNIQUEVALUETREE_REPLACE(member, ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
\
    assert(item);\
    assert(item->_ref##NameFrom == this);\
\
    assert(newItem);\
    assert(newItem->_ref##NameFrom == (ClassFrom*)0);\
\
    if (item->member == newItem->member)\
    {\
        ClassFrom##::##NameTo##Iterator::Check(item, newItem);\
        if (_first##NameTo == item)\
        {\
            _first##NameTo = newItem;\
        }\
        if (item->_parent##NameFrom)\
        {\
            if (item->_parent##NameFrom->_left##NameFrom == item)\
            {\
                item->_parent##NameFrom->_left##NameFrom = newItem;\
            }\
            else if (item->_parent##NameFrom->_right##NameFrom == item)\
            {\
                item->_parent##NameFrom->_right##NameFrom = newItem;\
            }\
        }\
        newItem->_ref##NameFrom = this;\
        newItem->_parent##NameFrom = item->_parent##NameFrom;\
        newItem->_left##NameFrom = item->_left##NameFrom;\
        newItem->_right##NameFrom = item->_right##NameFrom;\
        item->_ref##NameFrom = (ClassFrom*)0;\
        item->_parent##NameFrom = (ClassTo*)0;\
        item->_left##NameFrom = (ClassTo*)0;\
        item->_right##NameFrom = (ClassTo*)0;\
    }\
    else\
    {\
        ClassFrom##::##NameTo##Iterator::Check(item);\
        Remove##NameTo(item);\
        Add##NameTo(newItem);\
    }

#define METHOD_UNIQUEVALUETREE_GETFIRST(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
    return _first##NameTo;

#define METHOD_UNIQUEVALUETREE_GETLAST(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
\
    ClassTo* result = _first##NameTo;\
    while (result)\
    {\
        while (result->_right##NameFrom)\
        {\
            result = result->_right##NameFrom;\
        }\
\
        if (result->_left##NameFrom)\
        {\
            result = result->_left##NameFrom;\
        }\
        else\
        {\
            break;\
        }\
    }\
\
    return result;

#define METHOD_UNIQUEVALUETREE_GETNEXT(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
\
    ClassTo* result = 0;\
    if (pos == (ClassTo*)0)\
        result = _first##NameTo;\
    else\
    {\
        assert(pos->_ref##NameFrom == this);\
\
        if (pos->_left##NameFrom)\
        {\
            result = pos->_left##NameFrom;\
        }\
        else\
        {\
            if (pos->_right##NameFrom)\
            {\
                result = pos->_right##NameFrom;\
            }\
            else\
            {\
                ClassTo* parent = pos->_parent##NameFrom;\
                while (parent && (parent->_right##NameFrom == 0 || parent->_right##NameFrom == pos))\
                {\
                    pos = parent;\
                    parent = parent->_parent##NameFrom;\
                }\
\
                if (parent)\
                {\
                    result = parent->_right##NameFrom;\
                }\
            }\
        }\
    }\
\
    return result;

#define METHOD_UNIQUEVALUETREE_GETPREV(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
\
    ClassTo* result = 0;\
    if (pos == (ClassTo*)0)\
        result = GetLast##NameTo();\
    else\
    {\
        assert(pos->_ref##NameFrom == this);\
\
        if (pos->_parent##NameFrom)\
        {\
            if (pos->_parent##NameFrom->_left##NameFrom == pos || pos->_parent##NameFrom->_left##NameFrom == 0)\
            {\
                result = pos->_parent##NameFrom;\
            }\
            else /* Right branche and valid left branche */\
            {\
                result = pos->_parent##NameFrom->_left##NameFrom;\
                while (1)\
                {\
                    while (result->_right##NameFrom)\
                    {\
                        result = result->_right##NameFrom;\
                    }\
\
                    if (result->_left##NameFrom)\
                    {\
                        result = result->_left##NameFrom;\
                    }\
                    else\
                    {\
                        break;\
                    }\
                }\
            }\
        }\
    }\
\
    return result;

#define METHOD_UNIQUEVALUETREE_GETCOUNT(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
    return _count##NameTo;

#define METHODS_UNIQUEVALUETREE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#ifndef _BODY_VALUETREE_FIND
#define _BODY_VALUETREE_FIND(member, value, ClassFrom, NameFrom, ClassTo, NameTo) \
    ClassTo* result = 0;\
    if (_first##NameTo)\
    {\
        ClassTo* item = _first##NameTo;\
        unsigned long bit = 0x1;\
        while (1)\
        {\
            if (item->member == value)\
            {\
                result = item;\
                break;\
            }\
\
            if ((item->member & bit) == (value & bit))\
            {\
                if (item->_left##NameFrom)\
                {\
                    item = item->_left##NameFrom;\
                }\
                else\
                {\
                    break;\
                }\
            }\
            else\
            {\
                if (item->_right##NameFrom)\
                {\
                    item = item->_right##NameFrom;\
                }\
                else\
                {\
                    break;\
                }\
            }\
\
            bit <<= 1;\
        }\
    }
#endif

#define BODY_UNIQUEVALUETREE_FIND(member, value, ClassFrom, NameFrom, ClassTo, NameTo) \
    _BODY_VALUETREE_FIND(member, value, ClassFrom, NameFrom, ClassTo, NameTo) \
    return result;

#define BODY_UNIQUEVALUETREE_FINDREVERSE(member, value, ClassFrom, NameFrom, ClassTo, NameTo) \
    _BODY_VALUETREE_FIND(member, value, ClassFrom, NameFrom, ClassTo, NameTo) \
    return result;

#define WRITE_UNIQUEVALUETREE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    rCArchive << Get##NameTo##Count();\
    { for (ClassTo* item = GetFirst##NameTo(); item; item = GetNext##NameTo(item))\
          rCArchive << item->_index; }

#define READ_UNIQUEVALUETREE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    {\
        int count;\
        int index;\
\
        rCArchive >> count;\
        for (int i = 0; i < count; i++)\
        {\
            rCArchive >> index;\
            Add##NameTo((ClassTo*)(pointerArray[index]));\
        }\
    }

#endif
