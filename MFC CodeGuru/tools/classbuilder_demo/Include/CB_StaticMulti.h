#ifndef CB_STATIC_MULTI_H
#define CB_STATIC_MULTI_H

#include <assert.h>

#include "CB_IteratorStaticMulti.h"

// defines for include files
#define RELATION_STATIC_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
public:\
    static ClassTo* _first##NameTo;\
    static ClassTo* _last##NameTo;\
    static int _count##NameTo;\
\
public:\
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

#define RELATION_NOFILTER_STATIC_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
public:\
    static ClassTo* _first##NameTo;\
    static ClassTo* _last##NameTo;\
    static int _count##NameTo;\
\
public:\
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

#define RELATION_STATIC_MULTI_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
public:\
    ClassTo* _prev##NameFrom;\
    ClassTo* _next##NameFrom;

// defines implementation
#define INIT_STATIC_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) 

#define EXIT_STATIC_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define REPLACE_STATIC_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define INIT_STATIC_MULTI_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    _prev##NameFrom = (ClassTo*)0;\
    _next##NameFrom = (ClassTo*)0;

#define EXIT_STATIC_MULTI_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
	assert(this);\
    if (_prev##NameFrom || _next##NameFrom || ClassFrom##::GetFirst##NameTo() == this)\
    {\
        ClassFrom::NameTo##Iterator::Check(this);\
\
        ClassFrom::_count##NameTo--;\
\
        if (_next##NameFrom)\
            _next##NameFrom->_prev##NameFrom = _prev##NameFrom;\
        else\
            ClassFrom::_last##NameTo = _prev##NameFrom;\
\
        if (_prev##NameFrom)\
            _prev##NameFrom->_next##NameFrom = _next##NameFrom;\
        else\
            ClassFrom::_first##NameTo = _next##NameFrom;\
\
        _prev##NameFrom = (ClassTo*)0;\
        _next##NameFrom = (ClassTo*)0;\
    }

#define REPLACE_STATIC_MULTI_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
    assert(pOld);\
    if ((pOld->_prev##NameFrom != (ClassTo*)0) ||\
        (pOld->_next##NameFrom != (ClassTo*)0) ||\
        (ClassFrom::GetFirst##NameTo() == pOld))\
    {\
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
        pOld->_prev##NameFrom = (ClassTo*)0;\
    }\
    else\
    {\
        _prev##NameFrom = (ClassTo*)0;\
        _next##NameFrom = (ClassTo*)0;\
    }

#define METHODS_STATIC_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
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
void ClassFrom##::RemoveAll##NameTo()\
{\
    METHOD_STATIC_MULTI_REMOVEALL(ClassFrom, NameFrom, ClassTo, NameTo) \
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
int ClassFrom##::Includes##NameTo(ClassTo* item)\
{\
    METHOD_STATIC_MULTI_INCLUDES(ClassFrom, NameFrom, ClassTo, NameTo) \
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

#define METHOD_STATIC_MULTI_ADDFIRST(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(item);\
    assert(item->_prev##NameFrom == (ClassTo*)0 &&\
            item->_next##NameFrom == (ClassTo*)0 &&\
            (_first##NameTo != item));\
\
    _count##NameTo++;\
\
    if (_first##NameTo)\
    {\
        _first##NameTo->_prev##NameFrom = item;\
        item->_next##NameFrom = _first##NameTo;\
        _first##NameTo = item;\
    }\
    else\
        _first##NameTo = _last##NameTo = item;

#define METHOD_STATIC_MULTI_ADDLAST(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(item);\
    assert(item->_prev##NameFrom == (ClassTo*)0 &&\
            item->_next##NameFrom == (ClassTo*)0 &&\
            (_first##NameTo != item));\
\
    _count##NameTo++;\
\
    if (_last##NameTo)\
    {\
        _last##NameTo->_next##NameFrom = item;\
        item->_prev##NameFrom = _last##NameTo;\
        _last##NameTo = item;\
    }\
    else\
        _first##NameTo = _last##NameTo = item;

#define METHOD_STATIC_MULTI_ADDAFTER(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(pos);\
    assert((pos->_prev##NameFrom != (ClassTo*)0) ||\
            (pos->_next##NameFrom != (ClassTo*)0) ||\
            (_first##NameTo == pos));\
\
    assert(item);\
    assert(item->_prev##NameFrom == (ClassTo*)0 &&\
            item->_next##NameFrom == (ClassTo*)0 &&\
            (_first##NameTo != item));\
\
    _count##NameTo++;\
\
    item->_prev##NameFrom = pos;\
    item->_next##NameFrom = pos->_next##NameFrom;\
    pos->_next##NameFrom  = item;\
\
    if (item->_next##NameFrom)\
        item->_next##NameFrom->_prev##NameFrom = item;\
    else\
        _last##NameTo = item;

#define METHOD_STATIC_MULTI_ADDBEFORE(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(pos);\
    assert((pos->_prev##NameFrom != (ClassTo*)0) ||\
            (pos->_next##NameFrom != (ClassTo*)0) ||\
            (_first##NameTo == pos));\
\
    assert(item);\
\
    assert(item->_prev##NameFrom == (ClassTo*)0 &&\
            item->_next##NameFrom == (ClassTo*)0 &&\
            (_first##NameTo != item));\
\
    _count##NameTo++;\
\
    item->_next##NameFrom = pos;\
    item->_prev##NameFrom = pos->_prev##NameFrom;\
    pos->_prev##NameFrom  = item;\
\
    if (item->_prev##NameFrom)\
        item->_prev##NameFrom->_next##NameFrom = item;\
    else\
        _first##NameTo = item;

#define METHOD_STATIC_MULTI_REMOVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(item);\
    assert((item->_prev##NameFrom != (ClassTo*)0) ||\
            (item->_next##NameFrom != (ClassTo*)0) ||\
            (_first##NameTo == item));\
\
    ClassFrom##::##NameTo##Iterator::Check(item);\
\
    _count##NameTo--;\
\
    if (item->_next##NameFrom)\
        item->_next##NameFrom->_prev##NameFrom = item->_prev##NameFrom;\
    else\
        _last##NameTo = item->_prev##NameFrom;\
\
    if (item->_prev##NameFrom)\
        item->_prev##NameFrom->_next##NameFrom = item->_next##NameFrom;\
    else\
        _first##NameTo = item->_next##NameFrom;\
\
    item->_prev##NameFrom = (ClassTo*)0;\
    item->_next##NameFrom = (ClassTo*)0;

#define METHOD_STATIC_MULTI_REMOVEALL(ClassFrom, NameFrom, ClassTo, NameTo) \
    for (ClassTo* item = GetFirst##NameTo(); item; item = GetFirst##NameTo())\
          Remove##NameTo(item);

#define METHOD_STATIC_MULTI_DELETEALL(ClassFrom, NameFrom, ClassTo, NameTo) \
    for (ClassTo* item = GetFirst##NameTo(); item; item = GetFirst##NameTo())\
          delete item;

#define METHOD_STATIC_MULTI_REPLACE(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(item);\
    assert((item->_prev##NameFrom != (ClassTo*)0) ||\
            (item->_next##NameFrom != (ClassTo*)0) ||\
            (_first##NameTo == item));\
\
    assert(newItem);\
    assert(newItem->_prev##NameFrom == (ClassTo*)0 &&\
            newItem->_next##NameFrom == (ClassTo*)0 &&\
            (_first##NameTo != newItem));\
\
    ClassFrom##::##NameTo##Iterator::Check(item, newItem);\
\
    if (item->_next##NameFrom)\
        item->_next##NameFrom->_prev##NameFrom = newItem;\
    else\
        _last##NameTo = newItem;\
\
    if (item->_prev##NameFrom)\
        item->_prev##NameFrom->_next##NameFrom = newItem;\
    else\
        _first##NameTo = newItem;\
\
    newItem->_next##NameFrom = item->_next##NameFrom;\
    newItem->_prev##NameFrom = item->_prev##NameFrom;\
    item->_next##NameFrom = (ClassTo*)0;\
    item->_prev##NameFrom = (ClassTo*)0;

#define METHOD_STATIC_MULTI_GETFIRST(ClassFrom, NameFrom, ClassTo, NameTo) \
    return _first##NameTo;

#define METHOD_STATIC_MULTI_GETLAST(ClassFrom, NameFrom, ClassTo, NameTo) \
    return _last##NameTo;

#define METHOD_STATIC_MULTI_GETNEXT(ClassFrom, NameFrom, ClassTo, NameTo) \
    if (pos == (ClassTo*)0)\
        return _first##NameTo;\
\
    assert((pos->_prev##NameFrom != (ClassTo*)0) ||\
            (pos->_next##NameFrom != (ClassTo*)0) ||\
            (_first##NameTo == pos));\
\
    return pos->_next##NameFrom;

#define METHOD_STATIC_MULTI_GETPREV(ClassFrom, NameFrom, ClassTo, NameTo) \
    if (pos == (ClassTo*)0)\
        return _last##NameTo;\
\
    assert((pos->_prev##NameFrom != (ClassTo*)0) ||\
            (pos->_next##NameFrom != (ClassTo*)0) ||\
            (_first##NameTo == pos));\
\
    return pos->_prev##NameFrom;

#define METHOD_STATIC_MULTI_GETCOUNT(ClassFrom, NameFrom, ClassTo, NameTo) \
    return _count##NameTo;

#define METHOD_STATIC_MULTI_INCLUDES(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(item);\
    if (item->_prev##NameFrom || item->_next##NameFrom || (_first##NameTo == item))\
        return 1;\
\
    return 0;

#define METHOD_STATIC_MULTI_MOVEFIRST(ClassFrom, NameFrom, ClassTo, NameTo) \
    Remove##NameTo(item);\
    Add##NameTo##First(item);

#define METHOD_STATIC_MULTI_MOVELAST(ClassFrom, NameFrom, ClassTo, NameTo) \
    Remove##NameTo(item);\
    Add##NameTo##Last(item);

#define METHOD_STATIC_MULTI_MOVEAFTER(ClassFrom, NameFrom, ClassTo, NameTo) \
    Remove##NameTo(item);\
    Add##NameTo##After(item, pos);

#define METHOD_STATIC_MULTI_MOVEBEFORE(ClassFrom, NameFrom, ClassTo, NameTo) \
    Remove##NameTo(item);\
    Add##NameTo##Before(item, pos);

#define METHOD_STATIC_MULTI_SORT(ClassFrom, NameFrom, ClassTo, NameTo) \
	for (ClassTo* a = GetFirst##NameTo(); a; a = GetNext##NameTo(a))\
	{\
        ClassTo* b = GetNext##NameTo(a);\
\
        while (b && (comp(a, b) > 0))\
        {\
            Remove##NameTo(b);\
            ClassTo* c = GetPrev##NameTo(a);\
            while (c && (comp(c, b) > 0))\
                c = GetPrev##NameTo(c);\
\
            if (c)\
                Add##NameTo##After(b, c);\
            else\
                Add##NameTo##First(b);\
\
            b = GetNext##NameTo(a);\
        }\
    }

#define METHODS_STATIC_MULTI_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#endif
