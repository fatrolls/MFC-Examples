// BufferPool.h: interface for the CBufferPool class.
//
//////////////////////////////////////////////////////////////////////

#ifndef BUFFER_POOL_H
#define BUFFER_POOL_H

#include "link.h"

//struct _SEGMENT;
typedef struct _SEGMENT *PSEGMENT;


class CBufferPool  
{
public:
	CBufferPool(){}
	virtual ~CBufferPool(){}
	bool  Create(	IN const unsigned int   nBufferSize,
					IN const unsigned int	nNumberOfBuffersInSegment,
					IN const unsigned int	nNumberOfSegmentsStrat,
					IN const unsigned int	nNumberOfSegmentsLowMark,
					IN const unsigned int	nNumberOfSegmentsHighMark = -1,
					IN const double			lfRatioForSegmentDeletion = 0.333);
	
	void* Allocate();
	void  Free(const void* pBuffer);

	void Destroy();

private:
	bool AllocateSegment();
	void FreeSegment(IN PSEGMENT p_segment);

	//member variables
	DLINK			m_SegmentsListHead;


	
	unsigned int	m_nNumberOfBuffersInSegment;
	unsigned int	m_nNumberOfSegmentsStrat;
	unsigned int	m_nNumberOfSegmentsLowMark;
	unsigned int	m_nNumberOfSegmentsHighMark;
	unsigned int	m_nBufferSize;

	UINT			m_nNumberOfSegments;
	UINT			m_nFreeBuffers;
	

	PSEGMENT		m_pSegmentCandidateForDeletion;
	unsigned int	m_nCandidateDeletionLimit;

	CRITICAL_SECTION			m_CriticalSection;	
};

#endif //BUFFER_POOL_H
