#ifndef OBJECTPOOL_H
#define OBJECTPOOL_H
#include "BufferPool.h"

/*------------------------------------------------------------------------
operator new()
  
	new "placement" using the buffer pool instade of the real allocation
  
 
   size_t size                  size of the object a must parameter
   CBufferPool * BufferPool     buffer pool that allocates buffers of the object size
	
------------------------------------------------------------------------*/
inline void * operator new(size_t size , CBufferPool * BufferPool)
{
   //allocate the buffer
   return BufferPool->Allocate();
}
/*------------------------------------------------------------------------
operator delete()

  delete placement using the buffer pool instade of the real allocation
  
 DoomedObject - pointer to the buffer holding the object
 CBufferPool * BufferPool - buffer pool that free buffers of the object size
				
------------------------------------------------------------------------*/
inline void   operator delete(void * DoomedObject , CBufferPool * BufferPool)
{   
   //free the buffer
   BufferPool->Free(DoomedObject);
}



template <class T>
class  CObjectPool
{
public:
   bool Create(IN const unsigned int nNumberOfObjectsInSegment,
               IN const unsigned int nNumberOfSegmentsStrat,
               IN const unsigned int nNumberOfSegmentsLowMark,
               IN const unsigned int nNumberOfSegmentsHighMark = -1);
   
   inline T*   Allocate();
   
   inline void Free(IN T * obj);
   
   void        Destroy();

private:
   CBufferPool BufferPool;
};


/*------------------------------------------------------------------------
Create()
	
	  Call the create of the buffer pool with the object size

   IN UINT nNumberOfObjectsInSegment - Number of Objects in a segment
   IN UINT nNumberOfSegmentsStart    - Start Number of Segments
   IN UINT nNumberOfSegmentsLowMark  - Minimum Number of Segments
   IN UINT nNumberOfSegmentsHighMark - Maximum Number of Segments
				
------------------------------------------------------------------------*/

template <class T>
bool CObjectPool<T>::Create(IN const unsigned int nNumberOfObjectsInSegment,
                            IN const unsigned int nNumberOfSegmentsStart,
                            IN const unsigned int nNumberOfSegmentsLowMark,
                            IN const unsigned int nNumberOfSegmentsHighMark /*=-1*/)
{
   //create the buffer pool with a buffer size sizeof(T)
   return BufferPool.Create(sizeof(T),
                     nNumberOfObjectsInSegment,
                     nNumberOfSegmentsStart,
                     nNumberOfSegmentsLowMark,
                     nNumberOfSegmentsHighMark);
}

/*------------------------------------------------------------------------
Allocate()

  returnes a pointer to the object allocated using the buffer pool
		
------------------------------------------------------------------------*/

template <class T>
inline T * CObjectPool<T>::Allocate()
{ 
   //call the placement new operator
   return new (&BufferPool) T();
}

/*------------------------------------------------------------------------
Free()
	
  returns the object to the pool allocated using the buffer pool

	T * obj - the pointer to the object allocated using the object pool
				
------------------------------------------------------------------------*/


template <class T>
inline void CObjectPool<T>::Free(IN T * obj)
{
   //call the placement delete operator
   operator delete(obj,&BufferPool);
}


/*------------------------------------------------------------------------
Destroy()

  Destroys the pool
			
------------------------------------------------------------------------*/

template <class T>
void CObjectPool<T>::Destroy()
{
   //Destroy buffer pool
   BufferPool.Destroy();
}



#endif // OBJECTPOOL_H





















