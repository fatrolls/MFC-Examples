#ifndef CB_VALUETREE_OWNED_H
#define CB_VALUETREE_OWNED_H

#include "CB_ValueTree.h"

// defines for include files
#define RELATION_VALUETREE_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
private:\
    ClassTo* _first##NameTo;\
    int _count##NameTo;\
\
protected:\
\
public:\
    void Add##NameTo(ClassTo* item);\
    void Remove##NameTo(ClassTo* item);\
    void DeleteAll##NameTo();\
    void Replace##NameTo(ClassTo* item, ClassTo* newItem);\
    ClassTo* GetFirst##NameTo();\
    ClassTo* GetLast##NameTo();\
    ClassTo* GetNext##NameTo(ClassTo* pos);\
    ClassTo* GetPrev##NameTo(ClassTo* pos);\
    int Get##NameTo##Count();\
    ITERATOR_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define RELATION_NOFILTER_VALUETREE_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
private:\
    ClassTo* _first##NameTo;\
    int _count##NameTo;\
\
protected:\
\
public:\
    void Add##NameTo(ClassTo* item);\
    void Remove##NameTo(ClassTo* item);\
    void DeleteAll##NameTo();\
    void Replace##NameTo(ClassTo* item, ClassTo* newItem);\
    ClassTo* GetFirst##NameTo();\
    ClassTo* GetLast##NameTo();\
    ClassTo* GetNext##NameTo(ClassTo* pos);\
    ClassTo* GetPrev##NameTo(ClassTo* pos);\
    int Get##NameTo##Count();\
    ITERATOR_NOFILTER_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define RELATION_VALUETREE_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
	RELATION_VALUETREE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo)

// defines implementation
#define INIT_VALUETREE_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
   INIT_VALUETREE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define EXIT_VALUETREE_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    { for (ClassTo* item = GetFirst##NameTo(); item; item = GetFirst##NameTo())\
          delete item; }

#define REPLACE_VALUETREE_OWNED_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    REPLACE_VALUETREE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define INIT_VALUETREE_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    _ref##NameFrom = (ClassFrom*)0;\
    _parent##NameFrom = (ClassTo*)0;\
    _left##NameFrom = (ClassTo*)0;\
    _right##NameFrom = (ClassTo*)0;\
    _sibling##NameFrom = (ClassTo*)0;\
    assert(p##NameFrom);\
    p##NameFrom->Add##NameTo(this);

#define EXIT_VALUETREE_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    EXIT_VALUETREE_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define REPLACE_VALUETREE_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    _ref##NameFrom = (ClassFrom*)0;\
    _parent##NameFrom = (ClassTo*)0;\
    _left##NameFrom = (ClassTo*)0;\
    _right##NameFrom = (ClassTo*)0;\
    _sibling##NameFrom = (ClassTo*)0;\
    pOld->_ref##NameFrom->Replace##NameTo(pOld, this);

#define METHODS_VALUETREE_OWNED_ACTIVE(member, ClassFrom, NameFrom, ClassTo, NameTo) \
void ClassFrom##::Add##NameTo(ClassTo* item)\
{\
    METHOD_VALUETREE_ADD(member, ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Remove##NameTo(ClassTo* item)\
{\
    METHOD_VALUETREE_REMOVE(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::DeleteAll##NameTo()\
{\
    METHOD_VALUETREE_DELETEALL(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
void ClassFrom##::Replace##NameTo(ClassTo* item, ClassTo* newItem)\
{\
    METHOD_VALUETREE_REPLACE(member, ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
ClassTo* ClassFrom##::GetFirst##NameTo()\
{\
    METHOD_VALUETREE_GETFIRST(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
ClassTo* ClassFrom##::GetLast##NameTo()\
{\
    METHOD_VALUETREE_GETLAST(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
ClassTo* ClassFrom##::GetNext##NameTo(ClassTo* pos)\
{\
    METHOD_VALUETREE_GETNEXT(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
ClassTo* ClassFrom##::GetPrev##NameTo(ClassTo* pos)\
{\
    METHOD_VALUETREE_GETPREV(ClassFrom, NameFrom, ClassTo, NameTo) \
}\
\
int ClassFrom##::Get##NameTo##Count()\
{\
    METHOD_VALUETREE_GETCOUNT(ClassFrom, NameFrom, ClassTo, NameTo) \
}

#define METHODS_VALUETREE_OWNED_PASSIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#endif
