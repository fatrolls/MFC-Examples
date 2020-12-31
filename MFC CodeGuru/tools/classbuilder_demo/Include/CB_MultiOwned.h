#ifndef CB_MULTI_OWNED_H
#define CB_MULTI_OWNED_H

#include "CB_Multi.h"

// defines for include files
#define RELATION_MULTI_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
public:\
    ClassTo* _first##NameTo;\
    ClassTo* _last##NameTo;\
    int _count##NameTo;\
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

#define RELATION_NOFILTER_MULTI_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
public:\
    ClassTo* _first##NameTo;\
    ClassTo* _last##NameTo;\
    int _count##NameTo;\
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

#define RELATION_MULTI_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
	RELATION_MULTI_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo)

// defines implementation
#define INIT_MULTI_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
   INIT_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define EXIT_MULTI_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    { for (ClassTo* item = GetFirst##NameTo(); item; item = GetFirst##NameTo())\
          delete item; }

#define REPLACE_MULTI_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    REPLACE_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define INIT_MULTI_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
    assert(p##NameFrom);\
    p##NameFrom->_count##NameTo++;\
\
    _ref##NameFrom = p##NameFrom;\
\
    if (p##NameFrom->_last##NameTo)\
    {\
        _next##NameFrom = (ClassTo*)0;\
        _prev##NameFrom = p##NameFrom->_last##NameTo;\
        _prev##NameFrom->_next##NameFrom = this;\
        p##NameFrom->_last##NameTo = this;\
    }\
    else\
    {\
        _prev##NameFrom = (ClassTo*)0;\
        _next##NameFrom = (ClassTo*)0;\
        p##NameFrom->_first##NameTo = p##NameFrom->_last##NameTo = this;\
    }

#define EXIT_MULTI_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    EXIT_MULTI_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define REPLACE_MULTI_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    assert(this);\
    assert(pOld);\
    assert(pOld->_ref##NameFrom);\
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
    pOld->_prev##NameFrom = (ClassTo*)0;

#define METHODS_MULTI_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
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

#define METHODS_MULTI_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#endif
