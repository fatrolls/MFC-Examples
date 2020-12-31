/**
 *
 * 文 件 名：o.h
 *
 * 描    述：o.h 文件。
 *
 * 创 建 者：赵平智   <bruce.zhao.zpz@gmail.com>
 *
 * 创建日期：20050310
 *
 * 版    本：1.0.18
 *
 * 版权(C)2005-2011 赵平智。保留所有权利。　　　
 *
 * 备    注：
 *
 *
 * * 维护历史 *
 *
 *   <日期>             <修改者>
 *   <修改内容...>
 *
 **/

#ifndef __O_H__
#define __O_H__
      
/* #define  NDEBUG */
#include <assert.h>


/*
*
* 名称：INLINE_VOFUNCTION
* 描述：内联VO函数的开关。0 - 不内联，1 - 内联，其它 - 保留不用。
* 备注：定义为1时，能否真正内联VO函数还取决于下面的“_INLINE_”宏定义是否有效。
*/
#define     INLINE_VOFUNCTION          0

/*
*
* 名称：_INLINE_
* 描述：宏定义内联指示符，因为编译器的内联指示符不统一。
* 备注：一定要定义为有效的内联指示符，否则即使编译通过，内联也是无效的，编译
*       器会自动把用其修饰的函数转为非内联编译。
*/
#define     _INLINE_		      __inline
     

/*
*
* 描述：OS、HO、SO的mask。
* 备注：目前OID是用64个比特位表示的（见下面OBJID数据类型定义）。其
*       中，高16位是OS标识域，中32位是HO标识域，低16位是SO标识域。
*/
#define     MSKOS		          0xFFFF000000000000L
#define     MSKHO		          0x0000FFFFFFFF0000L
#define     MSKSO		          0x000000000000FFFFL


/*
*
* 各OS的OID。
*/
#define		OID_OICOS             0x0001000000000000L     /* Oicos的OID。*/
#define		OID_UNIX              0x0002000000000000L     /* Unix的OID。*/
#define		OID_LINUX             0x0003000000000000L     /* Linux的OID。*/
#define		OID_WINDOWS           0x0004000000000000L     /* Windows的OID。*/


/*
*
* 名称：OID_OS
* 描述：OS的OID。
*/
#define		OID_OS                OID_WINDOWS


/*
*
* 一级数据类型定义
*/
typedef     char                        SI8;  
typedef     unsigned char               UI8;  
typedef     short                       SI16;  
typedef     unsigned short              UI16; 
typedef     int                         SI32; 
typedef     unsigned int                UI32; 

#if OID_OS == OID_OICOS
#elif OID_OS == OID_UNIX
#elif OID_OS == OID_LINUX
typedef     long long                   SI64;
typedef     unsigned long long          UI64;
#elif OID_OS == OID_WINDOWS
typedef     __int64                     SI64;
typedef     unsigned __int64            UI64;
#else
#error the OID of OS is undefined.
#endif

typedef     float			            SR32;
/* typedef     unsigned float              UR32;  */
typedef     double                      SR64;
/* typedef     unsigned double             UR64; */
typedef     void                        VOID; 


/*
*
* 二级数据类型定义
*/
typedef     UI8         BYTE;              /* 位元组类型。*/
typedef     UI32        ACTION;            /* 行为类型。*/
typedef     SI32        RESULT;            /* 结果类型，必须是有符号类型。*/
typedef     UI32        BYTKTY;            /* by BYTe，c(K)apaciTY and q(K)uantiTY's type，以Byte为单位的容量和数量类型。*/
typedef     UI32        BITKTY;            /* by BIT，c(K)apaciTY and q(K)uantiTY's type，以Bit为单位的容量和数量类型。*/

typedef     UI16        MLDSN;             /* MSN类型。*/
typedef     UI64        OBJID;             /* OID类型。*/
typedef     UI32        REFCNT;            /* object's REFerence CouNT type，对象的引用计数类型。*/
typedef     UI32        MODES;             /* 模式集类型。*/

typedef     UI16        NUMCS;             /* the NUMber of CS type，CS的数量类型。*/
typedef     UI16        NUMND;             /* the NUMber of ND type，ND的数量类型。*/
typedef     UI16        NUMIB;             /* the NUMber of IB type，IB的数量类型。*/
typedef     UI16        NUMBN;             /* the NUMber of BN type，BN的数量类型。*/

typedef     SI8         BOOL;              /* 布尔类型，规定此类型数据只能有两个值：TRUE 或 FALSE （见下面 TRUE 和 FALSE 的定义）。*/


/*
*
* Byte大小（比特位数）
*/
#define     BYTESIZE        8


/*
*
* 描述：MSN
* 备注：要求MSN从1开始顺序编号，定义模板如下，
*       #define   MSN_XXX1    (MSN_ + 0)  /-* xxx1的MSN。HO *-/
*       #define   MSN_XXX2    (MSN_ + 1)  /-* xxx2的MSN。AO *-/
*       #define   MSN_XXX3    (MSN_ + 2)  /-* xxx3的MSN。.. *-/
*       #define   MSN_XXX4    (MSN_ + 3)  /-* xxx4的MSN。GO *-/
*       #define   MSN_XXX5    (MSN_ + 4)  /-* xxx5的MSN。.. *-/
*       ...     ...     ...     ...     ...     ...   
*       #define   MSN_XXXn    (MSN_ + n-1)  /-* xxxn的MSN。... *-/
*/
#define    MSN_OIOIC         1				   /* OIOIC的MSN。*/
#define    MSN_              (MSN_OIOIC + 1)   /* 其它MSN的起点。*/

/*
*
* 描述：通用模式定义。
* 备注：可定义 sizeof(MODES)*BYTESIZE 个通用模式。即如下，
*
*       #define   MOD_                     1
*       #define   MOD_XXX0             ( MOD_ << 0 )     /-* BIT0。1：xxx；0：xxx。*-/
*       #define   MOD_XXX1             ( MOD_ << 1 )     /-* BIT1。1：xxx；0：xxx。*-/
*       #define   MOD_XXX2             ( MOD_ << 2 )     /-* BIT2。1：xxx；0：xxx。*-/
*       ...     ...     ...     ...     ...     ...    
*       #define   MOD_XXXn            ( MOD_ << (sizeof(MODES)*BYTESIZE-1) )   /-* BITn。 1：xxx； 0：xxx。*-/
*/
#define   MOD_                  1
#define   MOD_SHARED            ( MOD_ << 0 )     /* BIT0。0：共享；1：非共享。*/
#define   MOD_BLOCKI            ( MOD_ << 1 )     /* BIT1。0：阻断输入；1：非阻断输入。只适用于Input和IOput接口。*/
#define   MOD_BLOCKO            ( MOD_ << 2 )     /* BIT2。0：阻断输出；1：非阻断输出。只适用于Output和IOput接口。*/


/*
*
* 描述：对象交互行为分类定义。
* 备注：1. 按是否须要输入Byte流和有没有输出Byte流,可将交互行为分为四种：
*          AC0 - 不需输入Byte流也没有输出Byte流；
*          AC1 - 不需要输入Byte流但有输出Byte流；
*          AC2 - 需要输入Byte流但没有输出Byte流；
*          AC3 - 即需要输入Byte流也有输出Byte流。
*
*       2. TSI和TSO
*          TSI - the Type of Stream Inputted，输入流类型。
*          TSO - the Type of Stream Outputted，输出流类型。
*/
#define     AC0        0  
#define     AC1        (1 << (sizeof(ACTION)*BYTESIZE - 2))   
#define     AC2        (2 << (sizeof(ACTION)*BYTESIZE - 2))   
#define     AC3        (3 << (sizeof(ACTION)*BYTESIZE - 2))  

/* 判断交互行为种类的mask */
#define     MSKAC      (3 << (sizeof(ACTION)*BYTESIZE - 2)) 


/*
*
* 描述：行为定义。   
* 备注：=== 定义模板 ===
*    
*       /-** AC0 行为：**-/
*       #define     XXX_YYYYY            (AC0_ + 0)  
*       #define     XXX_YYYYY            (AC0_ + 1)  
*       ...     ...     ...     ...     ...     ...   
*
*       /-** AC1 行为：**-/
*       #define     XXX_YYYYY            (AC1_ + 0)  
*       #define     XXX_YYYYY            (AC1_ + 1)  
*       ...     ...     ...     ...     ...     ...   
*
*       /-** AC2 行为：**-/
*       #define     XXX_YYYYY            (AC2_ + 0)  
*       #define     XXX_YYYYY            (AC2_ + 1)  
*       ...     ...     ...     ...     ...     ...   
*
*       /-** AC3 行为：**-/
*       #define     XXX_YYYYY            (AC3_ + 0)  
*       #define     XXX_YYYYY            (AC3_ + 1)  
*       ...     ...     ...     ...     ...     ...   
*                      
*/

/** AC0 行为：**/
#define     ASK_SHARED                  (AC0 + 0)                /* 问对象共享么。*/
#define     SET_SHARED                  (AC0 + 1)                /* 设置对象共享。*/
#define     SET_UNSHARED                (AC0 + 2)                /* 设置对象非共享。*/
#define     SET_BLOCKI                  (AC0 + 3)                /* 设置对象阻断输入。*/
#define     SET_UNBLOCKI                (AC0 + 4)                /* 设置对象非阻断输入。*/
#define     SET_BLOCKO                  (AC0 + 5)                /* 设置对象阻断输出。*/
#define     SET_UNBLOCKO                (AC0 + 6)                /* 设置对象非阻断输出。*/
#define     CMD_RESET                   (AC0 + 7)                /* 重置。*/
#define     CMD_PREPARE                 (AC0 + 8)                /* 准备。*/
#define     AC0_                        (AC0 + 9)                /* <其它AC0行为的起点> */ 

/** AC1 行为：**/
#define     GET_IQCTY                   (AC1 + 0)                /* 获取IQ容量。*/
#define     GET_OQCTY                   (AC1 + 1)                /* 获取OQ容量。*/
#define     AC1_                        (AC1 + 2)                /* <其它AC1行为的起点> */ 

/** AC2 行为：**/
#define     SET_IQCTY                   (AC2 + 0)                /* 设置IQ容量。*/
#define     SET_OQCTY                   (AC2 + 1)                /* 设置OQ容量。*/
#define     CMD_INITIALIZE              (AC2 + 2)                /* 初始化 */
#define     AC2_                        (AC2 + 3)                /* <其它AC2行为的起点> */ 

/** AC3 行为：**/
/* ...     ...     ...     ...     ...     ... */
#define     AC3_                        (AC3 + 0)                /* <其它AC3行为的起点> */



/*
*
* 描述：结果定义。 
* 备注：=== 定义模板 ===
*
*       ...     ...     ...     ...     ...     ...  
*       #define       RN_XXXXX            (RN_ - 1) 
*       #define       RN_XXXXX            (RN_ - 0) 
*       /-** N 结果（上）：**-/
* 
*       ...     ...     ...     ...     ...     ...  
*       #define       RO_XXXXX           (RON_ - 1) 
*       #define       RO_XXXXX           (RON_ - 0) 
*       /-**
*       ** 负 O 结果（上）：
*       **
*       ** 正 O 结果（下）：
*       **-/
*       #define       RO_XXXXX           (ROP_ + 0)  
*       #define       RO_XXXXX           (ROP_ + 1)  
*       ...     ...     ...     ...     ...     ...     
*
*       /-** P 结果（下）：**-/ 
*       #define       RP_XXXXX            (RP_ + 0)  
*       #define       RP_XXXXX            (RP_ + 1)  
*       ...     ...     ...     ...     ...     ...     
*
*/

#define        RN_                         (R_N - 7)                 /* <其它N结果的起点> */
#define        RN_LACKOID                  (R_N - 6)                 /* __CreateObject__，没有足够的OID供分配。*/
#define        RN_HASVR                    (R_N - 5)                 /* CallerCome，已经有这个VR了。*/
#define        RN_LOST                     (R_N - 4)                 /* Enqueue/Dequeue，已丢失了Byte。*/
#define        RN_UNSHARED                 (R_N - 3)                 /* Open，对象是非共享的。*/
#define        RN_FULL                     (R_N - 2)                 /* Open，对象引用已满，不能再打开。*/
#define        RN_INVALIDARG               (R_N - 1)                 /* 无效参数 */
#define        R_N                          __RON__		             /* N结果（否定性结果）的起点。*/

#define        __RON__                     (RON_ - 1000)             /* O结果域的N界。*/

#define        RON_		                   (R_O - 3)                 /* <其它负O结果的起点> */
#define        RO_NOPEN		               (R_O - 2)                 /* Close，对象还没有被打开。*/
#define        RO_VAINLY                   (R_O - 1)                 /* 空操作 */
#define        R_O			                0			             /* O结果（中立性结果）域的中点。*/
#define        RO_OBSOIX                   (R_O + 1)                 /* OBS顺序非接力访问模式专用执行结果。*/
#define        RO_SBOOIX                   (R_O + 2)                 /* SBO顺序非接力访问模式专用执行结果。*/
#define        RO__SBOOIX                  (R_O + 3)                 /* SBO顺序接力访问模式专用执行结果。*/
#define        ROP_		                   (R_O + 4)                 /* <其它正O结果的起点> */

#define        __ROP__                     (ROP_ + 1000)             /* O结果域的P界。*/

#define        R_P                          __ROP__		             /* P结果（肯定性结果）的起点。*/
#define        RP_RCZERO                   (R_P + 1)                 /* Close，对象引用计数变为0。*/
#define        RP_RCONE                    (R_P + 2)                 /* Open，对象引用计数为1。*/    
#define        RP_                         (R_P + 3)                 /* <其它P结果的起点> */

/*
*
* 描述：结果的否定性/中立性/肯定性检测定义。
* 备注：RN --- Negative Result；
*       RO --- O  Result；
*       RP --- Positive Result。
*/
#define     RN(Result)      ( (RESULT)(Result) <= __RON__ )  
#define     RO(Result)      ( ( (RESULT)(Result) > __RON__ ) && ( (RESULT)(Result) < __ROP__ ) )
#define     RP(Result)      ( (RESULT)(Result) >= __ROP__ )  



/*
*
* 定义布尔值和空指针值。
*/
#undef TRUE
#undef FALSE
#undef NULL

#define TRUE          1      /* 布尔类型数据值：真 */
#define FALSE         0      /* 布尔类型数据值：假 */
#define NULL          0      /* 指针类型数据值：空 */


/*======================+  OIOIC  +======================*/

/*
*
* 描述：队列结构体
* 备注：q_，pq_。
*/
typedef struct TAG_QUEUE
{
   BYTE*    Dtrm;        /* Data Room，数据空间。*/
   BYTKTY   Cty;         /* Dtrm的容量。*/
   BYTE*    Front;       /* 当前第一个Byte数据的地址。*/
   BYTE*    Rear;        /* 当前最后一个Byte数据的地址。*/
   BYTKTY   Qty;         /* 当前Dtrm内存有的Byte数量。*/
   BYTKTY   Lost;        /* 因Dtrm已满而丢弃的Byte数量。*/
}QUEUE;


/*
*
* 描述：VR结构体。
* 备注：vr_，pvr_。
*/
typedef struct TAG_VR
{
	OBJID    cr;  /* CR的ID。*/
	OBJID    mr;  /* MR的ID。*/
}VR;   

/*
*
* 描述：定义 EM 数据类型。
* 备注：1. em_，pem_；
*       2. 对象的实际扩展成员必须放在如下格式的EM结构体里，
*			typedef struct TAG_EM_XXX
*			{
*				...
*			}EM_XXX;
*/
typedef    VOID     EM;  /* 定义EM数据类型。*/


/*
*
* 描述：OIOIC对象模型结构体。
* 备注：“OIOIC”是5个通用接口（Open，Input，Output，Interact，Close）的第一个字符的合写。
*/
typedef struct TAG_OBJECT
{   
   /* RefCnt，对象引用计数（Reference Count）。*/
   REFCNT     RefCnt;

   /* MSN，模的SN。*/  
   MLDSN      MSN;
   
   /* OID，对象的ID。*/  
   OBJID      OID; 
   
   /* 为了... 需要下面两个成员： 
   * po_AND：指向AND。
   * NND：the Number of ND of IC，IC的ND数量，也就是AND的元素数量。*/
   struct TAG_OBJECT*   po_AND; 
   NUMND      NND; 
   
   /* 为能高效率访问IBN，需要下面两个成员：
   * ppo_AIB：指向AIB数组。
   * NIB：the Number of IB，IB数量，即AIB的元素数量。*/
   struct TAG_OBJECT**  ppo_AIB;
   NUMIB      NIB; 
   
   /* 为了能访问BN的EM和高效率地清除来访记录，需要下面两个成员：
   * ppo_ABN：指向ABN数组。
   * NBN：the Number of BN，BN数量，即ABN的元素数量。*/
   struct TAG_OBJECT**  ppo_ABN;
   NUMBN	  NBN; 
   
   /* 不可重入（Not Reentrant）访问规则，即同一MR的同一CR对每个BN只能访问一次。
   * 为遵守不可重入访问规则，需要下面两个成员：
   * pvr_ACS：指向ACS。
   * NCS：the Number of CS，CS的数量，即ACS的元素数量。*/
   VR*        pvr_ACS;
   NUMCS      NCS;    
   
   /** 对象接口：Open，Input，Output，IOput，Interact0~3，Close。**/
   
   /* 名称：Open
   *  描述：打开。
   *  参数：pCaller --- [IN] 来访者。*/
   RESULT  (*Open) (struct TAG_OBJECT* This, const VR* pCaller);
   /* 名称：Input
   *  描述：输入。
   *  参数：IStrm --- [IN] 输入流；
   *        Qty --- [IN] 输入的Byte数量；
   *        pCaller --- [IN] 来访者。*/
   RESULT  (*Input) (struct TAG_OBJECT* This, BYTE* IStrm, BYTKTY Qty, const VR* pCaller);
   /* 名称：Output
   *  描述：输出。
   *  参数：OStrm --- [OUT] 输出流的流向；
   *        Cty --- [IN] OStrm所指存储空间的容量；
   *        pQty --- [OUT] 指向实际输出的Byte数量；
   *        pCaller --- [IN] 来访者。*/
   RESULT  (*Output) (struct TAG_OBJECT* This, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller);
   /* 名称：IOput
   *  描述：输入输出。
   *  参数：IStrm --- [IN] 输入流；
   *        Qty --- [IN] 输入的Byte数量；
   *        OStrm --- [OUT] 输出流的流向；
   *        Cty --- [IN] OStrm所指存储空间的容量；
   *        pQty --- [OUT] 指向实际输出的Byte数量；
   *        pCaller --- [IN] 来访者。*/
   RESULT  (*IOput) (struct TAG_OBJECT* This, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller);
   /* 名称：Interact0
   *  描述：交互，接收AC0类型的行为。
   *  参数：Act --- [IN] 交互行为；
   *        pCaller --- [IN] 来访者。*/
   RESULT  (*Interact0) (struct TAG_OBJECT* This, ACTION Act, const VR* pCaller);
   /* 名称：Interact1
   *  描述：交互，接收AC1类型的行为。
   *  参数：Act --- [IN] 交互行为；
   *        OStrm --- [OUT] 输出流的流向；
   *        Cty --- [IN] OStrm所指存储空间的容量；
   *        pQty --- [OUT] 指向实际输出的Byte数量；
   *        pCaller --- [IN] 来访者。*/
   RESULT  (*Interact1) (struct TAG_OBJECT* This, ACTION Act, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller);
   /* 名称：Interact2
   *  描述：交互，接收AC2类型的行为。
   *  参数：Act --- [IN] 交互行为；
   *        IStrm --- [IN] 输入流；
   *        Qty --- [IN] 输入的Byte数量；
   *        pCaller --- [IN] 来访者。*/
   RESULT  (*Interact2) (struct TAG_OBJECT* This, ACTION  Act, BYTE* IStrm, BYTKTY Qty, const VR* pCaller);
   /* 名称：Interact3
   *  描述：交互，接收AC3类型的行为。
   *  参数：Act --- [IN] 交互行为；
   *        IStrm --- [IN] 输入流；
   *        Qty --- [IN] 输入的Byte数量；
   *        OStrm --- [OUT] 输出流的流向；
   *        Cty --- [IN] OStrm所指存储空间的容量；
   *        pQty --- [OUT] 指向实际输出的Byte数量；
   *        pCaller --- [IN] 来访者。*/
   RESULT  (*Interact3) (struct TAG_OBJECT* This, ACTION Act, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller);
   /* 名称：Close
   *  描述：关闭。
   *  参数：pCaller --- [IN] 来访者。*/
   RESULT  (*Close) (struct TAG_OBJECT* This, const VR* pCaller);
   
   /* pEM，指向对象的EM（扩展成员）。*/
   EM*    pEM;   
}OBJECT;


/*=============+  宏封装单个Byte入列和出列  +============*/

/* 单个Byte入列有两种模式：
*  1. PLACE --- 放入模式，向有空闲空间的队列放入一个Byte；
*  2. PUSH --- 推入模式，向已满（没有空闲空间）的队列推入一个Byte，把第一个Byte挤出扔掉。*/

/*
*
* 名称：ENQ_PLACE_BYTE
* 描述：宏，向有空闲空间的队列放入一个Byte。
* 参数：pQ --- [IN] QUEUE类型指针，指向队列，这个队列必须是有空闲空间的； 
*       byte --- [IN] 入列的Byte。
* 备注：只有在队列有空闲空间时才能使用。如下，
*
*		 if(pQ->Qty < pQ->Cty)
*		 { 
*		  	ENQ_PLACE_BYTE(pQ, byte);
*		 }else
*		 {
*		 	pQ->Lost++; 
* 
*	 		/-* ... *-/
*		 }
*/
#define  ENQ_PLACE_BYTE(pQ, byte) \
	do{ \
		if((pQ)->Rear == (pQ)->Dtrm + (pQ)->Cty - 1) \
			(pQ)->Rear = (pQ)->Dtrm; \
		else \
			(pQ)->Rear++; \
		*((pQ)->Rear) = (byte); \
		(pQ)->Qty++; \
		if((pQ)->Dtrm-1 == (pQ)->Front) \
			(pQ)->Front = (pQ)->Dtrm; \
	}while(0)

/*
*
* 名称：ENQ_PUSH_BYTE
* 描述：宏，向已满（没有空闲空间）的队列推入一个Byte，把第一个Byte挤出扔掉。
* 参数：pQ --- [IN] QUEUE类型指针，指向队列；
*       byte --- [IN] 入列的Byte。
* 备注：只有在队列已满时才能使用。如下，
*
*	  	 if(pQ->Qty < pQ->Cty)
*		 {
*			ENQ_PLACE_BYTE(pQ, byte);
*		 }else
*		 {
*		 	ENQ_PUSH_BYTE(pQ, byte);
*		 	pQ->Lost++; 
* 
*			/-* ... *-/
*		 }
*/
#define  ENQ_PUSH_BYTE(pQ, byte) \
	do{ \
		(pQ)->Rear = (pQ)->Front; \
		*((pQ)->Rear) = (byte); \
		if( (pQ)->Front == ((pQ)->Dtrm + (pQ)->Cty -1) ) \
			(pQ)->Front = (pQ)->Dtrm; \
		else \
			(pQ)->Front++; \
	}while(0)

/*
*
* 名称：DEQ_BYTE
* 描述：宏，从非空的队列出列一个Byte。
* 参数：pQ --- [IN] QUEUE类型指针，指向队列；
*       pByte --- [OUT] Byte地址，输出出列的Byte。
* 备注：只有在队列非空时才能使用。如下，
*
*	  	 if(pQ->Qty > 0)
*		 {
*			DEQ_BYTE(pQ, pByte);
*		 }
*/
#define  DEQ_BYTE(pQ, pByte) \
	do{ \
		*(pByte) = *((pQ)->Front); \
		(pQ)->Qty--; \
		if(0 == (pQ)->Qty) \
			(pQ)->Front = (pQ)->Rear = (pQ)->Dtrm -1; \
		else if( (pQ)->Front == ((pQ)->Dtrm + (pQ)->Cty -1) ) \
			(pQ)->Front = (pQ)->Dtrm; \
		else \
			(pQ)->Front++; \
	}while(0)


/*===================+  内联VO函数  +====================*/

/* 注意：内联VO函数和非内联VO函数的功能是完全相同的。*/


#if INLINE_VOFUNCTION == 1

/**
*
* 名称：VO_Open
* 描述：接口Open的VO函数。
* 参数：pObject --- [IN] 指向对象；
*       pCaller --- [IN] 来访者。
*/    	             
static  _INLINE_  RESULT  VO_Open(OBJECT* pObject, const VR* pCaller)
{
	extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller);
	extern  RESULT  CallerLeave(OBJECT* pND, const VR* pCaller);

	RESULT  ir = R_O;

	assert( pObject != NULL );
	assert( pCaller->cr != 0 );
	assert( pCaller->mr != 0 );
	
	if( R_P == CallerCome(pObject, pCaller) )
	{
		ir = pObject->Open(pObject, pCaller);
		CallerLeave(pObject, pCaller);
	}else { ir = R_N; }
	
	return ir;
}
       
/**
*
* 名称：VO_Input
* 描述：接口Input的VO函数。
* 参数：pObject --- [IN] 指向对象； 
*       IStrm --- [IN] 输入流；
*       Qty --- [IN] 输入的Byte数量；
*       pCaller --- [IN] 来访者。
*/          
static  _INLINE_  RESULT  VO_Input(OBJECT* pObject, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{
	extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller);
	extern  RESULT  CallerLeave(OBJECT* pND, const VR* pCaller);

	RESULT  ir = R_O;

	assert( pObject != NULL );
	assert( IStrm != NULL );
	assert( Qty > 0 );
	assert( pCaller->cr != 0 );
	assert( pCaller->mr != 0 );

	if( R_P == CallerCome(pObject, pCaller) ) 
	{ 
		ir = pObject->Input(pObject, IStrm, Qty, pCaller); 
		CallerLeave(pObject, pCaller); 
	}else { ir = R_N; }
	
	return ir;
}

/**
*
* 名称：VO_Output
* 描述：接口Output的VO函数。
* 参数：pObject --- [IN] 指向对象； 
*       OStrm --- [OUT] 输出流的流向；
*       Cty --- [IN] OStrm所指存储空间的容量；
*       pQty --- [OUT] 指向实际输出的Byte数量；
*       pCaller --- [IN] 来访者。
*/      
static  _INLINE_  RESULT  VO_Output(OBJECT* pObject, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller) 
{
	extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller);
	extern  RESULT  CallerLeave(OBJECT* pND, const VR* pCaller);

	RESULT  ir = R_O;

	assert( pObject != NULL );
	assert( OStrm != NULL );
	assert( Cty > 0 );
	assert( pQty != NULL );
	assert( pCaller->cr != 0 );
	assert( pCaller->mr != 0 );

	*pQty = 0;

	if( R_P == CallerCome(pObject, pCaller) ) 
	{ 
		ir = pObject->Output(pObject, OStrm, Cty, pQty, pCaller); 
		CallerLeave(pObject, pCaller); 
	}else { ir = R_N; }
	
	return ir;
}

/**
*
* 名称：VO_IOput
* 描述：接口IOput的VO函数。
* 参数：pObject --- [IN] 指向对象； 
*       IStrm --- [IN] 输入流；
*       Qty --- [IN] 输入的Byte数量；
*       OStrm --- [OUT] 输出流的流向；
*       Cty --- [IN] OStrm所指存储空间的容量；
*       pQty --- [OUT] 指向实际输出的Byte数量；
*       pCaller --- [IN] 来访者。
*/  
static  _INLINE_  RESULT  VO_IOput(OBJECT* pObject, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{
	extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller);
	extern  RESULT  CallerLeave(OBJECT* pND, const VR* pCaller);
	
	RESULT  ir = R_O;

	assert( pObject != NULL );
	assert( IStrm != NULL );
	assert( Qty > 0 );
	assert( OStrm != NULL );
	assert( Cty > 0 );
	assert( pQty != NULL );
	assert( pCaller->cr != 0 );
	assert( pCaller->mr != 0 );
	
	*pQty = 0;

	if( R_P == CallerCome(pObject, pCaller) ) 
	{ 
		ir = pObject->IOput(pObject, IStrm, Qty, OStrm, Cty, pQty, pCaller); 
		CallerLeave(pObject, pCaller); 
	}else { ir = R_N; }
	
	return ir;
}

/**
*
* 名称：VO_Interact0
* 描述：接口Interact0的VO函数。
* 参数：pObject --- [IN] 指向对象；
*       Act --- [IN] 交互行为；
*       pCaller --- [IN] 来访者。
*/	       
static  _INLINE_  RESULT  VO_Interact0(OBJECT* pObject, ACTION Act, const VR* pCaller) 
{
	extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller);
	extern  RESULT  CallerLeave(OBJECT* pND, const VR* pCaller);

	RESULT  ir = R_O;

	assert( pObject != NULL );
	assert( (MSKAC & Act) == AC0 );
	assert( pCaller->cr != 0 );
	assert( pCaller->mr != 0 );
	
	if( R_P == CallerCome(pObject, pCaller) )
	{
		ir = pObject->Interact0(pObject, Act, pCaller);
		CallerLeave(pObject, pCaller);
	}else { ir = R_N; }
	
	return ir;
}

/**
*
* 名称：VO_Interact1
* 描述：接口Interact1的VO函数。
* 参数：pObject --- [IN] 指向对象；
*       Act --- [IN] 交互行为；
*       OStrm --- [OUT] 输出流的流向；
*       Cty --- [IN] OStrm所指存储空间的容量；
*       pQty --- [OUT] 指向实际输出的Byte数量；
*       pCaller --- [IN] 来访者。
*/       
static  _INLINE_  RESULT  VO_Interact1(OBJECT* pObject, ACTION Act, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller) 
{
	extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller);
	extern  RESULT  CallerLeave(OBJECT* pND, const VR* pCaller);

	RESULT  ir = R_O;

	assert( pObject != NULL );
	assert( (MSKAC & Act) == AC1 );
	assert( OStrm != NULL );
	assert( Cty > 0 );
	assert( pQty != NULL );
	assert( pCaller->cr != 0 );
	assert( pCaller->mr != 0 );

	*pQty = 0;

	if( R_P == CallerCome(pObject, pCaller) ) 
	{ 
		ir = pObject->Interact1(pObject, Act, OStrm, Cty, pQty, pCaller); 
		CallerLeave(pObject, pCaller); 
	}else { ir = R_N; }
	
	return ir;
}

/**
*
* 名称：VO_Interact2
* 描述：接口Interact2的VO函数。
* 参数：pObject --- [IN] 指向对象；
*       Act --- [IN] 交互行为；
*       IStrm --- [IN] 输入流；
*       Qty --- [IN] 输入的Byte数量；
*       pCaller --- [IN] 来访者。
*/       
static  _INLINE_  RESULT  VO_Interact2(OBJECT* pObject, ACTION Act, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)  
{
	extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller);
	extern  RESULT  CallerLeave(OBJECT* pND, const VR* pCaller);

	RESULT  ir = R_O;
	
	assert( pObject != NULL );
	assert( (MSKAC & Act) == AC2 );
	assert( IStrm != NULL );
	assert( Qty > 0 );
	assert( pCaller->cr != 0 );
	assert( pCaller->mr != 0 );

	if( R_P == CallerCome(pObject, pCaller) ) 
	{ 
		ir = pObject->Interact2(pObject, Act, IStrm, Qty, pCaller); 
		CallerLeave(pObject, pCaller); 
	}else { ir = R_N; }
	
	return ir;
}

/**
*
* 名称：VO_Interact3
* 描述：接口Interact3的VO函数。
* 参数：pObject --- [IN] 指向对象；
*       Act --- [IN] 交互行为；
*       IStrm --- [IN] 输入流；
*       Qty --- [IN] 输入的Byte数量；
*       OStrm --- [OUT] 输出流的流向；
*       Cty --- [IN] OStrm所指存储空间的容量；
*       pQty --- [OUT] 指向实际输出的Byte数量；
*       pCaller --- [IN] 来访者。
*/       
static  _INLINE_  RESULT  VO_Interact3(OBJECT* pObject, ACTION Act, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)  
{
	extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller);
	extern  RESULT  CallerLeave(OBJECT* pND, const VR* pCaller);

	RESULT  ir = R_O;

	assert( pObject != NULL );
	assert( (MSKAC & Act) == AC3 );
	assert( IStrm != NULL );
	assert( Qty > 0 );
	assert( OStrm != NULL );
	assert( Cty > 0 );
	assert( pQty != NULL );
	assert( pCaller->cr != 0 );
	assert( pCaller->mr != 0 );

	*pQty = 0;

	if( R_P == CallerCome(pObject, pCaller) ) 
	{ 
		ir = pObject->Interact3(pObject, Act, IStrm, Qty, OStrm, Cty, pQty, pCaller); 
		CallerLeave(pObject, pCaller); 
	}else { ir = R_N; }
	
	return ir;
}

/**
*
* 名称：VO_Close
* 描述：接口Close的VO函数。
* 参数：pObject --- [IN] 指向对象； 
*       pCaller --- [IN] 来访者。
*/       
static  _INLINE_  RESULT  VO_Close(OBJECT* pObject, const VR* pCaller) 
{
	extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller);
	extern  RESULT  CallerLeave(OBJECT* pND, const VR* pCaller);

	RESULT  ir = R_O;
	
	assert( pObject != NULL );
	assert( pCaller->cr != 0 );
	assert( pCaller->mr != 0 );

	if( R_P == CallerCome(pObject, pCaller) ) 
	{ 
		ir = pObject->Close(pObject, pCaller); 
		CallerLeave(pObject, pCaller); 
	}else { ir = R_N; }
	
	return ir;
}

#endif  /* #if INLINE_VOFUNCTION == 1 */

/*===============+ 继承链的四种访问模式 +================*/

/*  
* 1. 继承链的两种访问顺序：OBS和SBO。
* （1）OBS，others before self，先访问节点的IBN后访问节点自身；
* （2）SBO，self before others，先访问节点自身后访问节点的IBN。
*
* 2. 继承链的两种访问方式：接力和非接力访问。
* （1）接力访问，Relay Visiting，访问上一个节点后，不管是什么执行结果接
*      着访问下一节点。OBS返回LND的执行结果；SBO的返回结果分两种情况，
*      单重继承链返回FND的执行结果，多重继承链返回RO__SBOOIX。
* （2）相反就是非接力访问，Non-Relay Visiting，访问上一个节点后，如果不
*      是RO_OBSOIX（对于OBS）或RO_SBOOIX（对于SBO）就返回执行结果，否则
*      就访问下一个节点。
*
* 3. 继承链的两种访问顺序和两种访问方式组合为继承链的四种访问模式。
* （1）OBS_O_IX，OBS_OBJECT_<INTERFACE> 型的宏，按OBS顺序非接力访问；
* （2）OBS_O_IX_，OBS_OBJECT_<INTERFACE>_ 型的宏，按OBS顺序接力访问；
* （3）SBO_O_IX，SBO_OBJECT_<INTERFACE> 型的宏，按SBO顺序非接力访问；
* （4）_SBO_O_IX，_SBO_OBJECT_<INTERFACE> 型的宏，按SBO顺序接力访问。
*
* 注：1. Open和Close接口只能按OBS顺序接力访问，所以Open和Close接口没
*        有OBS_O_IX、SBO_O_IX和_SBO_O_IX。
*     2. 同一接口，四种访问模式只能选择其一，因此同一接口内不能同时存
*        两种不同的访问模式。
*     3. 接力访问一般适用于单重继承，对于多重继承意义不大。
*/

/*
*
* 名称：OBS_OBJECT_OPEN_
* 描述：宏，Open接口的OBS_O_IX_。
*/
#define  OBS_OBJECT_OPEN_ \
	do{ \
		RESULT   ir; \
		RESULT   fr; \
		NUMIB	 i; \
		VR	Caller; \
		EM_OIOIC*  pem = (EM_OIOIC*)GetEMofBN(This, MSN_OIOIC); \
		Caller.cr = pCaller->cr; \
		Caller.mr = This->OID; \
  		if(0 == ++This->RefCnt) \
		{ \
			This->RefCnt--; \
			return  RN_FULL; \
		} \
		if(!(MOD_SHARED & pem->mds) || 1 == This->RefCnt) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			for(i=0; i<This->NIB; i++) \
			{ \
				fr = CallerCome(*(This->ppo_AIB+i), pCaller); \
				if(R_P == fr) ir = (*(This->ppo_AIB+i))->Open(*(This->ppo_AIB+i), pCaller); \
				else if(RN_HASVR == fr) continue; \
				else ir = R_N; \
				if( RN(ir) ) \
				{ \
					NUMIB  j; \
					for( j=0; j<i; j++) \
					{ \
						if((*(This->ppo_AIB+j))->RefCnt == This->RefCnt) \
							VO_Close(*(This->ppo_AIB+j), &Caller); \
					} \
					This->RefCnt--; \
					return ir; \
				} \
			} \
		}else \
		{ \
			This->RefCnt--; \
			return RN_UNSHARED; \
		} \
	}while(0)
	
/*
*
* 名称：OBS_OBJECT_INPUT
* 描述：宏，Input接口的OBS_O_IX。
*/
#define  OBS_OBJECT_INPUT \
	do{ \
		RESULT   ir = RO_OBSOIX; \
		RESULT   fr; \
		NUMIB    i; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			fr = CallerCome(*(This->ppo_AIB+i), pCaller); \
			if(R_P == fr) ir = (*(This->ppo_AIB+i))->Input(*(This->ppo_AIB+i), IStrm, Qty, pCaller); \
			else if(RN_HASVR == fr) continue; \
			else ir = R_N; \
			if(ir != RO_OBSOIX) return ir; \
		} \
	}while(0)

/*
*
* 名称：OBS_OBJECT_INPUT_
* 描述：宏，Input接口的OBS_O_IX_。
*/
#define  OBS_OBJECT_INPUT_ \
	do{ \
		NUMIB    i; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			if(R_P == CallerCome(*(This->ppo_AIB+i), pCaller)) \
				(*(This->ppo_AIB+i))->Input(*(This->ppo_AIB+i), IStrm, Qty, pCaller); \
		} \
	}while(0)

/*
*
* 名称：SBO_OBJECT_INPUT
* 描述：宏，Input接口的SBO_O_IX。
*/
#define  SBO_OBJECT_INPUT \
	do{ \
		RESULT   ir = RO_SBOOIX; \
		RESULT   fr; \
		NUMIB    i; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			fr = CallerCome(*(This->ppo_AIB+i), pCaller); \
			if(R_P == fr) ir = (*(This->ppo_AIB+i))->Input(*(This->ppo_AIB+i), IStrm, Qty, pCaller); \
			else if(RN_HASVR == fr) continue; \
			else ir = R_N; \
			if(ir != RO_SBOOIX) return ir; \
		} \
		return ir; \
	}while(0)

/*
*
* 名称：_SBO_OBJECT_INPUT
* 描述：宏，Input接口的_SBO_O_IX。
*/
#define  _SBO_OBJECT_INPUT \
	do{ \
		RESULT   ir = RO__SBOOIX; \
		NUMIB    i; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			if(R_P == CallerCome(*(This->ppo_AIB+i), pCaller)) \
				ir = (*(This->ppo_AIB+i))->Input(*(This->ppo_AIB+i), IStrm, Qty, pCaller); \
		} \
		return ir; \
	}while(0)
	
/*
*
* 名称：OBS_OBJECT_OUTPUT
* 描述：宏，Output接口的OBS_O_IX。
*/
#define  OBS_OBJECT_OUTPUT \
	do{ \
		RESULT   ir = RO_OBSOIX;  \
		RESULT   fr; \
		NUMIB    i; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			fr = CallerCome(*(This->ppo_AIB+i), pCaller); \
			if(R_P == fr) ir = (*(This->ppo_AIB+i))->Output(*(This->ppo_AIB+i), OStrm, Cty, pQty, pCaller); \
			else if(RN_HASVR == fr) continue; \
			else ir = R_N; \
			if(ir != RO_OBSOIX) return ir; \
		} \
	}while(0)

/*
*
* 名称：OBS_OBJECT_OUTPUT_
* 描述：宏，Output接口的OBS_O_IX_。
*/
#define  OBS_OBJECT_OUTPUT_ \
	do{ \
		NUMIB    i; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			if(R_P == CallerCome(*(This->ppo_AIB+i), pCaller)) \
				(*(This->ppo_AIB+i))->Output(*(This->ppo_AIB+i), OStrm, Cty, pQty, pCaller); \
		} \
	}while(0)

/*
*
* 名称：SBO_OBJECT_OUTPUT
* 描述：宏，Output接口的SBO_O_IX。
*/
#define  SBO_OBJECT_OUTPUT \
	do{ \
		RESULT   ir = RO_SBOOIX; \
		RESULT   fr; \
		NUMIB    i; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			fr = CallerCome(*(This->ppo_AIB+i), pCaller); \
			if(R_P == fr) ir = (*(This->ppo_AIB+i))->Output(*(This->ppo_AIB+i), OStrm, Cty, pQty, pCaller); \
			else if(RN_HASVR == fr) continue; \
			else ir = R_N; \
			if(ir != RO_SBOOIX) return ir; \
		} \
		return ir; \
	}while(0)

/*
*
* 名称：_SBO_OBJECT_OUTPUT
* 描述：宏，Output接口的_SBO_O_IX。
*/
#define  _SBO_OBJECT_OUTPUT \
	do{ \
		RESULT   ir = RO__SBOOIX; \
		NUMIB    i; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			if(R_P == CallerCome(*(This->ppo_AIB+i), pCaller)) \
				ir = (*(This->ppo_AIB+i))->Output(*(This->ppo_AIB+i), OStrm, Cty, pQty, pCaller); \
		} \
		return ir; \
	}while(0)

/*
*
* 名称：OBS_OBJECT_IOPUT
* 描述：宏，IOput接口的OBS_O_IX。
*/
#define  OBS_OBJECT_IOPUT \
	do{ \
		RESULT   ir = RO_OBSOIX; \
		RESULT   fr; \
		NUMIB    i; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			fr = CallerCome(*(This->ppo_AIB+i), pCaller); \
			if(R_P == fr) ir = (*(This->ppo_AIB+i))->IOput(*(This->ppo_AIB+i), IStrm, Qty, OStrm, Cty, pQty, pCaller); \
			else if(RN_HASVR == fr) continue; \
			else ir = R_N; \
			if(ir != RO_OBSOIX) return ir; \
		} \
	}while(0)

/*
*
* 名称：OBS_OBJECT_IOPUT_
* 描述：宏，IOput接口的OBS_O_IX_。
*/
#define  OBS_OBJECT_IOPUT_ \
	do{ \
		NUMIB    i; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			if(R_P == CallerCome(*(This->ppo_AIB+i), pCaller)) \
				(*(This->ppo_AIB+i))->IOput(*(This->ppo_AIB+i), IStrm, Qty, OStrm, Cty, pQty, pCaller); \
		} \
	}while(0)

/*
*
* 名称：SBO_OBJECT_IOPUT
* 描述：宏，IOput接口的SBO_O_IX。
*/
#define  SBO_OBJECT_IOPUT \
	do{ \
		RESULT   ir = RO_SBOOIX; \
		RESULT   fr; \
		NUMIB    i; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			fr = CallerCome(*(This->ppo_AIB+i), pCaller); \
			if(R_P == fr) ir = (*(This->ppo_AIB+i))->IOput(*(This->ppo_AIB+i), IStrm, Qty, OStrm, Cty, pQty, pCaller); \
			else if(RN_HASVR == fr) continue; \
			else ir = R_N; \
			if(ir != RO_SBOOIX) return ir; \
		} \
		return ir; \
	}while(0)

/*
*
* 名称：_SBO_OBJECT_IOPUT
* 描述：宏，IOput接口的_SBO_O_IX。
*/
#define  _SBO_OBJECT_IOPUT \
	do{ \
		RESULT   ir = RO__SBOOIX; \
		NUMIB    i; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			if(R_P == CallerCome(*(This->ppo_AIB+i), pCaller)) \
				ir = (*(This->ppo_AIB+i))->IOput(*(This->ppo_AIB+i), IStrm, Qty, OStrm, Cty, pQty, pCaller); \
		} \
		return ir; \
	}while(0)
	
/*
*
* 名称：OBS_OBJECT_INTERACT0
* 描述：宏，Interact0接口的OBS_O_IX。
*/
#define  OBS_OBJECT_INTERACT0 \
	do{ \
		RESULT   ir = RO_OBSOIX; \
		RESULT   fr; \
		NUMIB    i; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			fr = CallerCome(*(This->ppo_AIB+i), pCaller); \
			if(R_P == fr) ir = (*(This->ppo_AIB+i))->Interact0(*(This->ppo_AIB+i), Act, pCaller); \
			else if(RN_HASVR == fr) continue; \
			else ir = R_N; \
			if(ir != RO_OBSOIX) return ir; \
		} \
	}while(0)

/*
*
* 名称：OBS_OBJECT_INTERACT0_
* 描述：宏，Interact0接口的OBS_O_IX_。
*/
#define  OBS_OBJECT_INTERACT0_ \
	do{ \
		NUMIB    i; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			if(R_P == CallerCome(*(This->ppo_AIB+i), pCaller)) \
				(*(This->ppo_AIB+i))->Interact0(*(This->ppo_AIB+i), Act, pCaller); \
		} \
	}while(0)

/*
*
* 名称：SBO_OBJECT_INTERACT0
* 描述：宏，Interact0接口的SBO_O_IX。
*/
#define  SBO_OBJECT_INTERACT0 \
	do{ \
		RESULT   ir = RO_SBOOIX; \
		RESULT   fr; \
		NUMIB    i; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			fr = CallerCome(*(This->ppo_AIB+i), pCaller); \
			if(R_P == fr) ir = (*(This->ppo_AIB+i))->Interact0(*(This->ppo_AIB+i), Act, pCaller); \
			else if(RN_HASVR == fr) continue; \
			else ir = R_N; \
			if(ir != RO_SBOOIX) return ir; \
		} \
		return ir; \
	}while(0)
	
/*
*
* 名称：_SBO_OBJECT_INTERACT0
* 描述：宏，Interact0接口的_SBO_O_IX。
*/
#define  _SBO_OBJECT_INTERACT0 \
	do{ \
		RESULT   ir = RO__SBOOIX; \
		NUMIB    i; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			if(R_P == CallerCome(*(This->ppo_AIB+i), pCaller)) \
				(*(This->ppo_AIB+i))->Interact0(*(This->ppo_AIB+i), Act, pCaller); \
		} \
		return ir; \
	}while(0)

/*
*
* 名称：OBS_OBJECT_INTERACT1
* 描述：宏，Interact1接口的OBS_O_IX。
*/
#define  OBS_OBJECT_INTERACT1 \
	do{ \
		RESULT   ir = RO_OBSOIX; \
		RESULT   fr; \
		NUMIB    i; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			fr = CallerCome(*(This->ppo_AIB+i), pCaller); \
			if(R_P == fr) ir = (*(This->ppo_AIB+i))->Interact1(*(This->ppo_AIB+i), Act, OStrm, Cty, pQty, pCaller); \
			else if(RN_HASVR == fr) continue; \
			else ir = R_N; \
			if(ir != RO_OBSOIX) return ir; \
		} \
	}while(0)

/*
*
* 名称：OBS_OBJECT_INTERACT1_
* 描述：宏，Interact1接口的OBS_O_IX_。
*/
#define  OBS_OBJECT_INTERACT1_ \
	do{ \
		NUMIB    i; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			if(R_P == CallerCome(*(This->ppo_AIB+i), pCaller)) \
				(*(This->ppo_AIB+i))->Interact1(*(This->ppo_AIB+i), Act, OStrm, Cty, pQty, pCaller); \
		} \
	}while(0)

/*
*
* 名称：SBO_OBJECT_INTERACT1
* 描述：宏，Interact1接口的SBO_O_IX。
*/
#define  SBO_OBJECT_INTERACT1 \
	do{ \
		RESULT   ir = RO_SBOOIX; \
		RESULT   fr; \
		NUMIB    i; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			fr = CallerCome(*(This->ppo_AIB+i), pCaller); \
			if(R_P == fr) ir = (*(This->ppo_AIB+i))->Interact1(*(This->ppo_AIB+i), Act, OStrm, Cty, pQty, pCaller); \
			else if(RN_HASVR == fr) continue; \
			else ir = R_N; \
			if(ir != RO_SBOOIX) return ir; \
		} \
		return ir; \
	}while(0)

/*
*
* 名称：_SBO_OBJECT_INTERACT1
* 描述：宏，Interact1接口的_SBO_O_IX。
*/
#define  _SBO_OBJECT_INTERACT1 \
	do{ \
		RESULT   ir = RO__SBOOIX; \
		NUMIB    i; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			if(R_P == CallerCome(*(This->ppo_AIB+i), pCaller)) \
				ir = (*(This->ppo_AIB+i))->Interact1(*(This->ppo_AIB+i), Act, OStrm, Cty, pQty, pCaller); \
		} \
		return ir; \
	}while(0)
	
/*
*
* 名称：OBS_OBJECT_INTERACT2
* 描述：宏，Interact2接口的OBS_O_IX。
*/
#define  OBS_OBJECT_INTERACT2 \
	do{ \
		RESULT   ir = RO_OBSOIX; \
		RESULT   fr; \
		NUMIB    i; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			fr = CallerCome(*(This->ppo_AIB+i), pCaller); \
			if(R_P == fr) ir = (*(This->ppo_AIB+i))->Interact2(*(This->ppo_AIB+i), Act, IStrm, Qty, pCaller); \
			else if(RN_HASVR == fr) continue; \
			else ir = R_N; \
			if(ir != RO_OBSOIX) return ir; \
		} \
	}while(0)

/*
*
* 名称：OBS_OBJECT_INTERACT2_
* 描述：宏，Interact2接口的OBS_O_IX_。
*/
#define  OBS_OBJECT_INTERACT2_ \
	do{ \
		NUMIB    i; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			if(R_P == CallerCome(*(This->ppo_AIB+i), pCaller)) \
				(*(This->ppo_AIB+i))->Interact2(*(This->ppo_AIB+i), Act, IStrm, Qty, pCaller); \
		} \
	}while(0)

/*
*
* 名称：SBO_OBJECT_INTERACT2
* 描述：宏，Interact2接口的SBO_O_IX。
*/
#define  SBO_OBJECT_INTERACT2 \
	do{ \
		RESULT   ir = RO_SBOOIX; \
		RESULT   fr; \
		NUMIB    i; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			fr = CallerCome(*(This->ppo_AIB+i), pCaller); \
			if(R_P == fr) ir = (*(This->ppo_AIB+i))->Interact2(*(This->ppo_AIB+i), Act, IStrm, Qty, pCaller); \
			else if(RN_HASVR == fr) continue; \
			else ir = R_N; \
			if(ir != RO_SBOOIX) return ir; \
		} \
		return ir; \
	}while(0)

/*
*
* 名称：_SBO_OBJECT_INTERACT2
* 描述：宏，Interact2接口的_SBO_O_IX。
*/
#define  _SBO_OBJECT_INTERACT2 \
	do{ \
		RESULT   ir = RO__SBOOIX; \
		NUMIB    i; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			if(R_P == CallerCome(*(This->ppo_AIB+i), pCaller)) \
				ir = (*(This->ppo_AIB+i))->Interact2(*(This->ppo_AIB+i), Act, IStrm, Qty, pCaller); \
		} \
		return ir; \
	}while(0)
	
/*
*
* 名称：OBS_OBJECT_INTERACT3
* 描述：宏，Interact3接口的OBS_O_IX。
*/
#define  OBS_OBJECT_INTERACT3 \
	do{ \
		RESULT   ir = RO_OBSOIX; \
		RESULT   fr; \
		NUMIB    i; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			fr = CallerCome(*(This->ppo_AIB+i), pCaller); \
			if(R_P == fr) ir = (*(This->ppo_AIB+i))->Interact3(*(This->ppo_AIB+i), Act, IStrm, Qty, OStrm, Cty, pQty, pCaller); \
			else if(RN_HASVR == fr) continue; \
			else ir = R_N; \
			if(ir != RO_OBSOIX) return ir; \
		} \
	}while(0)

/*
*
* 名称：OBS_OBJECT_INTERACT3_
* 描述：宏，Interact3接口的OBS_O_IX_。
*/
#define  OBS_OBJECT_INTERACT3_ \
	do{ \
		NUMIB    i; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			if(R_P == CallerCome(*(This->ppo_AIB+i), pCaller)) \
				(*(This->ppo_AIB+i))->Interact3(*(This->ppo_AIB+i), Act, IStrm, Qty, OStrm, Cty, pQty, pCaller); \
		} \
	}while(0)
 
/*
*
* 名称：SBO_OBJECT_INTERACT3
* 描述：宏，Interact3接口的SBO_O_IX。
*/
#define  SBO_OBJECT_INTERACT3 \
	do{ \
		RESULT   ir = RO_SBOOIX; \
		RESULT   fr; \
		NUMIB    i; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			fr = CallerCome(*(This->ppo_AIB+i), pCaller); \
			if(R_P == fr) ir = (*(This->ppo_AIB+i))->Interact3(*(This->ppo_AIB+i), Act, IStrm, Qty, OStrm, Cty, pQty, pCaller); \
			else if(RN_HASVR == fr) continue; \
			else ir = R_N; \
			if(ir != RO_SBOOIX) return ir; \
		} \
		return ir; \
	}while(0)

/*
*
* 名称：_SBO_OBJECT_INTERACT3
* 描述：宏，Interact3接口的_SBO_O_IX。
*/
#define  _SBO_OBJECT_INTERACT3 \
	do{ \
		RESULT   ir = RO__SBOOIX; \
		NUMIB    i; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			if(R_P == CallerCome(*(This->ppo_AIB+i), pCaller)) \
				ir = (*(This->ppo_AIB+i))->Interact3(*(This->ppo_AIB+i), Act, IStrm, Qty, OStrm, Cty, pQty, pCaller); \
		} \
		return ir; \
	}while(0)

/*
*
* 名称：OBS_OBJECT_CLOSE_
* 描述：宏，Close接口的OBS_O_IX_。
*/
#define  OBS_OBJECT_CLOSE_ \
	do{ \
		RESULT   ir; \
		RESULT   fr; \
		NUMIB    i; \
		if( 0 == This->RefCnt ) \
			return RO_NOPEN; \
		This->RefCnt--; \
		for(i=0; i<This->NIB; i++) \
		{ \
			extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller); \
			if((*(This->ppo_AIB+i))->RefCnt -1 == This->RefCnt) \
			{ \
				fr = CallerCome(*(This->ppo_AIB+i), pCaller); \
				if(R_P == fr) ir = (*(This->ppo_AIB+i))->Close(*(This->ppo_AIB+i), pCaller); \
				else if(RN_HASVR == fr) continue; \
				else ir = R_N; \
				if( RN(ir) ) \
				{ \
					This->RefCnt++; \
					return ir; \
				} \
			} \
		} \
	}while(0)

/*==========+  CreateObject & DestroyObject  +===========*/

/*
*
* 名称：CreateObject
* 描述：宏，动态创建对象。
* 参数：Msn --- [IN] 模序号，指定创建哪个模的对象。
*       IQCty --- [IN] 输入队列的容量。
*       OQCty --- [IN] 输出队列的容量。
*       NumCR --- [IN] 来访者数量。
*       ppObj --- [OUT] 输出创建的对象。
*/
extern  RESULT  __CreateObject__(MLDSN Msn, BYTKTY IQCty, BYTKTY OQCty, SI32 NumCR, OBJECT** ppObj, BYTE* pExotic);
#define  CreateObject(Msn, IQCty, OQCty, NumCR, ppObj) \
	    __CreateObject__(Msn, IQCty, OQCty, NumCR, ppObj, NULL)

/*
*
* 名称：DestroyObject
* 描述：宏，销毁动态创建的对象，即销毁由CreateObject宏创建的对象。
* 参数：pObj --- [IN] 指向对象。
*/
extern  BOOL  __DestroyObject__(OBJECT*  pObj); 
#define  DestroyObject( pObj ) \
	do{ \
		if(TRUE == __DestroyObject__(pObj)) \
		{ \
			free(pObj); \
			(pObj) = NULL; \
		} \
	}while(0) 

/*===========+  向外声明外面直接调用的函数  +============*/

extern  RESULT   Enqueue(QUEUE* pq, BYTE* IData, BYTKTY Qty);
extern  RESULT   Dequeue(QUEUE* pq, BYTE* OData, BYTKTY Cty, BYTKTY* pQty);
extern  OBJECT*  GetBN(OBJECT* pND, MLDSN msn);
extern  EM*      GetEMofBN(OBJECT* pND, MLDSN msn);
extern  QUEUE*   GetIQ(OBJECT* pND);
extern  QUEUE*   GetOQ(OBJECT* pND);

#if INLINE_VOFUNCTION == 0

extern  RESULT   VO_Open(OBJECT* pObject, const VR* pCaller);
extern  RESULT   VO_Input(OBJECT* pObject, BYTE* IStrm, BYTKTY Qty, const VR* pCaller);
extern  RESULT   VO_Output(OBJECT* pObject, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller); 
extern  RESULT   VO_IOput(OBJECT* pObject, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller);
extern  RESULT   VO_Interact0(OBJECT* pObject, ACTION Act, const VR* pCaller); 
extern  RESULT   VO_Interact1(OBJECT* pObject, ACTION Act, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller);
extern  RESULT   VO_Interact2(OBJECT* pObject, ACTION Act, BYTE* IStrm, BYTKTY Qty, const VR* pCaller);
extern  RESULT   VO_Interact3(OBJECT* pObject, ACTION Act, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller);
extern  RESULT   VO_Close(OBJECT* pObject, const VR* pCaller);

#endif


#endif  /* #ifndef __O_H__ */
