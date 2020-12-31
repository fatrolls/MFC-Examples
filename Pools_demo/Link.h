#ifndef LINK_H
#define LINK_H
/*
SLINK - single link
*/

typedef struct _SLINK{
   _SLINK* _next;
} SLINK,*PSLINK;

///////////////////////////////////////////////////////////////////////////////////
/////////////////////////SINGLE////LINK////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

//initialize the link 
//void SLINK_Initialize(PSLINK)
#define SLINK_Initialize(_head)           ((_head)->_next = NULL)

//check if list is empty
//bool SLINK_IsEmpty(PSLINK)
#define SLINK_IsEmpty(_head)              ((_head)->_next == NULL)

//pop the first item in list  
//PSLINK SLINK_Pop(PSLINK)                                              
#define SLINK_Pop(_head)                  (_head)->_next;\
                                          (_head)->_next =  (_head)->_next->_next;
//push an item to the head of list    
//VOID SLINK_Push(PSLINK,PSLINK)                                            
#define SLINK_Push(_head,_link)           (_link)->_next =  (_head)->_next;\
                                          (_head)->_next =  (_link)


///////////////////////////////////////////////////////////////////////////////////
/////////////////////////////DOUBLE///LINK/////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

/*
DLINK - double link
*/
typedef struct _DLINK{
   _DLINK* _prev;
   _DLINK* _next;
} DLINK,*PDLINK;

//initialize the link 
//void DLINK_Initialize(PDLINK)
#define DLINK_Initialize(_head)            ((_head)->_next = (_head)->_prev = (_head))

//check if list is empty
//bool DLINK_IsEmpty(PDLINK) 
#define DLINK_IsEmpty(_head)               ((_head)->_next == (_head))

//insert item after the _head item
//void DLINK_InsertNext(PDLINK,PDLINK)
#define DLINK_InsertNext(_head,_dlink)     (_dlink)->_next = (_head)->_next;\
                                           (_dlink)->_prev = (_head);\
                                           (_head)->_next->_prev = (_dlink);\
                                           (_head)->_next = (_dlink);
//insert item previous to the _head item         
//void DLINK_InsertPrev(PDLINK,PDLINK)                             
#define DLINK_InsertPrev(_head,_dlink)     (_dlink)->_prev = (_head)->_prev;\
                                           (_dlink)->_next = (_head);\
                                           (_head)->_prev->_next = (_dlink);\
                                           (_head)->_prev = (_dlink);
//remove the item from list
//void DLINK_Remove(PDLINK)
#define DLINK_Remove(_dlink)               (_dlink)->_prev->_next = (_dlink)->_next;\
                                           (_dlink)->_next->_prev = (_dlink)->_prev
//extract the item previous to _head
//PDLINK DLINK_ExtructPrev(PDLINK)
#define DLINK_ExtructPrev(_head)           (_head)->_prev;\
                                           DLINK_Remove((_head)->_prev)
//extract the item after the _head item
//PDLINK DLINK_ExtructNext(PDLINK)
#define DLINK_ExtructNext(_head)           (_head)->_next;\
                                           DLINK_Remove((_head)->_next)

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

//get the object of type "type" that contains the field "field" stating in address "address"
#ifndef CONTAINING_RECORD

#define CONTAINING_RECORD(address, type, field) ((type *)( \
                                                 (PCHAR)(address) - \
                                                 (ULONG_PTR)(&((type *)0)->field)))

#endif
#endif // ALINK_H
