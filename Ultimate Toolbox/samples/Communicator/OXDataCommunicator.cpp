// ==========================================================================
//				Class Implementation : COXDataCommunicator
// ==========================================================================

// Source file : OXDataCommunicator.cpp

//----------------- Dundas Software ----------------------------------------                          
//========================================================================
			  
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OXDataCommunicator.h"
#include "CommunicatorDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(COXDataCommunicator, COXCommunicator)

/////////////////////////////////////////////////////////////////////////////
// Definition of static members

// Data members -------------------------------------------------------------
// protected:

// private:
	
// Member functions ---------------------------------------------------------
// public:
COXDataCommunicator::COXDataCommunicator(CCommunicatorDoc* pCommunicatorDoc, UINT nStreamBufferSize /* = 4096 */)
	:
	COXCommunicator(nStreamBufferSize),
	m_pCommunicatorDoc(pCommunicatorDoc)
	{
	ASSERT_VALID(this);
	ASSERT(pCommunicatorDoc != NULL);
	}

void COXDataCommunicator::OnClientCreate(HCLIENT_COMMUNICATOR hClient, COXCommunicator* pClientCommunicator)
	{
	m_pCommunicatorDoc->OnClientCreate(hClient, pClientCommunicator);
	}

void COXDataCommunicator::OnClientReceive(HCLIENT_COMMUNICATOR hClient, COXCommunicator* pClientCommunicator, DWORD nSize, int nErrorCode)
	{
	m_pCommunicatorDoc->OnClientReceive(hClient, pClientCommunicator, nSize, nErrorCode);
	}

void COXDataCommunicator::OnClientClose(HCLIENT_COMMUNICATOR hClient, COXCommunicator* pClientCommunicator, int nErrorCode)
	{
	m_pCommunicatorDoc->OnClientClose(hClient, pClientCommunicator, nErrorCode);
	}

void COXDataCommunicator::OnServerReceive(DWORD nSize, int nErrorCode)
	{
	m_pCommunicatorDoc->OnServerReceive(nSize, nErrorCode);
	}

void COXDataCommunicator::OnServerClose(int nErrorCode)
	{
	m_pCommunicatorDoc->OnServerClose(nErrorCode);
	}

#ifdef _DEBUG
void COXDataCommunicator::AssertValid() const
	{
	COXCommunicator::AssertValid();
	}

void COXDataCommunicator::Dump(CDumpContext& dc) const
	{
	COXCommunicator::Dump(dc);
	}
#endif //_DEBUG

COXDataCommunicator::~COXDataCommunicator()
	{
	}

// protected:

// private:

// ==========================================================================
