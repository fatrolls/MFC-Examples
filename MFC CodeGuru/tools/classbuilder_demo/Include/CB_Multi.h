#ifndef CB_MULTI_H
#define CB_MULTI_H

#include <assert.h>

#include "CB_IteratorMulti.h"

// defines for include files
#define RELATION_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
public:\
    ClassTo* _first##NameTo;\
    ClassTo* _last##NameTo;\
    int _count##NameTo;\
\
public:\
    void Add##NameTo##First(ClassTo* item);\
    void Add##NameTo##Last(ClassTo* item);\
    void Add##NameTo##After(ClassTo* item, ClassTo* pos);\
    void Add##NameTo##Before(ClassTo* item, ClassTo* pos);\
    void Remove##NameTo(ClassTo* item);\
    void RemoveAll##NameTo();\
    void DeleteAll##NameTo();\
    void Replace##NameTo(ClassTo* item, ClassTo* newItem);\
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

#define RELATION_NOFILTER_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
public:\
    ClassTo* _first##NameTo;\
    ClassTo* _last##NameTo;\
    int _count##NameTo;\
\
public:\
    void Add##NameTo##First(ClassTo* item);\
    void Add##NameTo##Last(ClassTo* item);\
    void Add##NameTo##After(ClassTo* item, ClassTo* pos);\
    void Add##NameTo##Before(ClassTo* item, ClassTo* pos);\
    void Remove##NameTo(ClassTo* item);\
    void RemoveAll##NameTo();\
    void DeleteAll##NameTo();\
    void Replace##NameTo(ClassTo* item, ClassTo* newItem);\
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

#define RELATION_MULTI_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
public:\
    ClassFrom* _ref##NameFrom;\
    ClassTo* _prev##NameFrom;\
    ClassTo* _next##NameFrom;\
\
public:\
	ClassFrom* Get##NameFrom() { return _ref##NameFrom; };

// defines implementation
#define INIT_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    _first##NameTo = (ClassTo*)0;\
    _last##NameTo = (ClassTo*)0;\
    _count##NameTo = 0;

#define EXIT_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    { for (ClassTo* item = GetFirst##NameTo(); item; item = GetFirst##NameTo())\
          Remove##NameTo(item); }

#define REPLACE_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    _first##NameTo = pOld->_first##NameTo;\
    _last##NameTo = pOld->_last##NameTo;\
    _count##NameTo = pOld->_count##NameTo;\
    pOld->_first##NameTo = (ClassTo*)0;\
    pOld->_last##NameTo = (ClassTo*)0;\
    { for (ClassTo* item = GetFirst##NameTo(); item; item = GetNext##NameTo(item))\
          item->_ref##NameFrom = this; }

#define INIT_MULTI_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    _ref##NameFrom = (ClassFrom*)0;\
    _prev##NameFrom = (ClassTo*)0;\
    _next##NameFrom = (ClassTo*)0;

#define EXIT_MULTI_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
    if (_ref##NameFrom)\
    {\
        ClassFrom##::##NameTo##Iterator::Check(this);\
\
        _ref##NameFrom->_count##NameTo--;\
\
        if (_next##NameFrom)\
            _next##NameFrom->_prev##NameFrom = _prev##NameFrom;\
        else\
            _ref##NameFrom->_last##NameTo = _prev##NameFrom;\
\
        if (_prev##NameFrom)\
            _prev##NameFrom->_next##NameFrom = _next##NameFrom;\
        else\
            _ref##NameFrom->_first##NameTo = _next##NameFrom;\
\
        _prev##NameFrom = (ClassTo*)0;\
        _next##NameFrom = (ClassTo*)0;\
        _ref##NameFrom = (ClassFrom*)0;\
    }

#define REPLACE_MULTI_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
    assert(pOld);\
    if (pOld->_ref##NameFrom)\
    {\
        ClassFrom##::##NameTo##Iterator::Check(pOld, this);\
\
        _ref##NameFrom = pOld->_ref##NameFrom;\
\
        if (pOld->_next##NameFrom)\
            pOld->_next##NameFrom->_prev##NameFrom = this;\
        else\
            _ref##NameFrom->_last##NameTo = this;\
\
        if (pOld->_prev##NameFrom)\
            pOld->_prev##NameFrom->_next##NameFrom = this;\
        else\
            _ref##NameFrom->_first##NameTo = this;\
\
        _next##NameFrom = pOld->_next##NameFrom;\
        _prev##NameFrom = pOld->_prev##NameFrom;\
\
        pOld->_ref##NameFrom = (ClassFrom*)0;\
        pOld->_next##NameFrom = (ClassTo*)0;\
        pOld->_prev##NameFrom = (ClassTo*)0;\
    }\
    else\
    {\
        _ref##NameFrom = (ClassFrom*)0;\
        _prev##NameFrom = (ClassTo*)0;\
        _next##NameFrom = (ClassTo*)0;\
    }

#define METHODS_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
void ClassFrom##::Add##NameTo##First(ClassTo* item)\
{\
    METHOD_MULTI_ADDFIRST(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Add##NameTo##Last(ClassTo* item)\
{\
    METHOD_MULTI_ADDLAST(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Add##NameTo##After(ClassTo* item, ClassTo* pos)\
{\
    METHOD_MULTI_ADDAFTER(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Add##NameTo##Before(ClassTo* item, ClassTo* pos)\
{\
    METHOD_MULTI_ADDBEFORE(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Remove##NameTo(ClassTo* item)\
{\
    METHOD_MULTI_REMOVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::RemoveAll##NameTo()\
{\
    METHOD_MULTI_REMOVEALL(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::DeleteAll##NameTo()\
{\
    METHOD_MULTI_DELETEALL(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Replace##NameTo(ClassTo* item, ClassTo* newItem)\
{\
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
    METHOD_MULTI_GETNEXT(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
ClassTo* ClassFrom##::GetPrev##NameTo(ClassTo* pos)\
{\
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
    METHOD_MULTI_MOVEFIRST(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Move##NameTo##Last(ClassTo* item)\
{\
    METHOD_MULTI_MOVELAST(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Move##NameTo##After(ClassTo* item, ClassTo* pos)\
{\
    METHOD_MULTI_MOVEAFTER(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Move##NameTo##Before(ClassTo* item, ClassTo* pos)\
{\
    METHOD_MULTI_MOVEBEFORE(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Sort##NameTo##(int (*comp)(ClassTo*, ClassTo*))\
{\
    METHOD_MULTI_SORT(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define METHOD_MULTI_ADDFIRST(ClassFrom, NameFrom, ClassTo, NameTo) \
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
        _first##NameTo->_prev##NameFrom = item;\
        item->_next##NameFrom = _first##NameTo;\
        _first##NameTo = item;\
    }\
    else\
        _first##NameTo = _last##NameTo = item;

#define METHOD_MULTI_ADDLAST(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
\
    assert(item);\
    assert(item->_ref##NameFrom == (ClassFrom*)0);\
\
    _count##NameTo++;\
\
    item->_ref##NameFrom = this;\
\
    if (_last##NameTo)\
    {\
        _last##NameTo->_next##NameFrom = item;\
        item->_prev##NameFrom = _last##NameTo;\
        _last##NameTo = item;\
    }\
    else\
        _first##NameTo = _last##NameTo = item;

#define METHOD_MULTI_ADDAFTER(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
\
    assert(item);\
    assert(item->_ref##NameFrom == (ClassFrom*)0);\
\
    assert(pos);\
    assert(pos->_ref##NameFrom == this);\
\
    _count##NameTo++;\
\
    item->_ref##NameFrom = this;\
    item->_prev##NameFrom = pos;\
    item->_next##NameFrom = pos->_next##NameFrom;\
    pos->_next##NameFrom  = item;\
\
    if (item->_next##NameFrom)\
        item->_next##NameFrom->_prev##NameFrom = item;\
    else\
        _last##NameTo = item;

#define METHOD_MULTI_ADDBEFORE(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
\
    assert(item);\
    assert(item->_ref##NameFrom == (ClassFrom*)0);\
\
    assert(pos);\
    assert(pos->_ref##NameFrom == this);\
\
    _count##NameTo++;\
\
    item->_ref##NameFrom = this;\
    item->_next##NameFrom = pos;\
    item->_prev##NameFrom = pos->_prev##NameFrom;\
    pos->_prev##NameFrom  = item;\
\
    if (item->_prev##NameFrom)\
        item->_prev##NameFrom->_next##NameFrom = item;\
    else\
        _first##NameTo = item;

#define METHOD_MULTI_REMOVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
\
    assert(item);\
    assert(item->_ref##NameFrom == this);\
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
    item->_next##NameFrom = (ClassTo*)0;\
    item->_ref##NameFrom = (ClassFrom*)0;

#define METHOD_MULTI_REMOVEALL(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
\
    for (ClassTo* item = GetFirst##NameTo(); item; item = GetFirst##NameTo())\
          Remove##NameTo(item);

#define METHOD_MULTI_DELETEALL(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
\
    for (ClassTo* item = GetFirst##NameTo(); item; item = GetFirst##NameTo())\
          delete item;

#define METHOD_MULTI_REPLACE(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
\
    assert(item);\
    assert(item->_ref##NameFrom == this);\
\
    assert(newItem);\
    assert(newItem->_ref##NameFrom == (ClassFrom*)0);\
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
    item->_prev##NameFrom = (ClassTo*)0;\
\
    item->_ref##NameFrom = (ClassFrom*)0;\
    newItem->_ref##NameFrom = this;

#define METHOD_MULTI_GETFIRST(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
    return _first##NameTo;

#define METHOD_MULTI_GETLAST(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
    return _last##NameTo;

#define METHOD_MULTI_GETNEXT(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
\
    if (pos == (ClassTo*)0)\
        return _first##NameTo;\
\
    assert(pos);\
    assert(pos->_ref##NameFrom == this);\
\
    return pos->_next##NameFrom;

#define METHOD_MULTI_GETPREV(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
\
    if (pos == (ClassTo*)0)\
        return _last##NameTo;\
\
    assert(pos);\
    assert(pos->_ref##NameFrom == this);\
\
    return pos->_prev##NameFrom;

#define METHOD_MULTI_GETCOUNT(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
    return _count##NameTo;

#define METHOD_MULTI_MOVEFIRST(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(item);\
    assert(item->_ref##NameFrom);\
    item->_ref##NameFrom->Remove##NameTo(item);\
    Add##NameTo##First(item);

#define METHOD_MULTI_MOVELAST(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(item);\
    assert(item->_ref##NameFrom);\
    item->_ref##NameFrom->Remove##NameTo(item);\
    Add##NameTo##Last(item);

#define METHOD_MULTI_MOVEAFTER(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(item);\
    assert(item->_ref##NameFrom);\
    item->_ref##NameFrom->Remove##NameTo(item);\
    Add##NameTo##After(item, pos);

#define METHOD_MULTI_MOVEBEFORE(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(item);\
    assert(item->_ref##NameFrom);\
    item->_ref##NameFrom->Remove##NameTo(item);\
    Add##NameTo##Before(item, pos);

#define METHOD_MULTI_SORT(ClassFrom, NameFrom, ClassTo, NameTo) \
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

#define METHODS_MULTI_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define SERIALIZE_ALL_OBJECTS(Document, DocumentName, DocumentBase, DocumentBaseName) \
    if (rCArchive.IsStoring())\
    {\
        /* Write the number of objects to store.*/\
        rCArchive << Get##DocumentBaseName##Count();\
\
        /* Reserve index = 0; for the NULL pointer*/\
        int index = 1;\
\
        /* Write the data of the objects*/\
        DocumentBase* object;\
        for (object = GetFirst##DocumentBaseName(); object; object = GetNext##DocumentBaseName(object))\
        {\
            object->_index = index++;\
            rCArchive << object;\
        }\
\
        /* Write relations of Document*/\
        SerializeRelations(rCArchive, NULL);\
\
        /* Write all other objects relations*/\
        for (object = GetFirst##DocumentBaseName(); object; object = GetNext##DocumentBaseName(object))\
        {\
            object->SerializeRelations(rCArchive, NULL);\
        }\
   }\
   else\
   {\
        /* Read the number of objects stored*/\
        int objectCount;\
        rCArchive >> objectCount;\
\
        /* Make an array for the pointer mapping*/\
        DocumentBase** pointerArray = new DocumentBase*[objectCount+1];\
        pointerArray[0] = NULL;\
\
        /* Read the data of the objects*/\
        for (int index = 1; index <= objectCount; index++)\
        {\
            CObject* pCObject;\
            rCArchive >> pCObject;\
            pointerArray[index] = (DocumentBase*)pCObject;\
        }\
\
        /* Read relations of Document*/\
        SerializeRelations(rCArchive, pointerArray);\
\
        /* Read all other objects relations*/\
        for (index = 1; index <= objectCount; index++)\
            pointerArray[index]->SerializeRelations(rCArchive, pointerArray);\
\
        delete pointerArray;\
    }

#define WRITE_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    rCArchive << Get##NameTo##Count();\
    { for (ClassTo* item = GetFirst##NameTo(); item; item = GetNext##NameTo(item))\
          rCArchive << item->_index; }

#define READ_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    {\
        int count;\
        int index;\
\
        rCArchive >> count;\
        for (int i = 0; i < count; i++)\
        {\
            rCArchive >> index;\
            Add##NameTo##Last((ClassTo*)(pointerArray[index]));\
        }\
    }

#endif
