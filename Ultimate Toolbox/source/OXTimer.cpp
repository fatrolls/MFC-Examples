// ==========================================================================
//				Class Implementation : COXTimer
// ==========================================================================

// Source file : OXTimer.cpp

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.                      
			  
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OXTimer.h"
#include <mmsystem.h>

#ifndef OX_TIMER_NO_MM_LIB
	#pragma comment(lib, "winmm.lib")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(COXTimer, CObject)

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// Definition of static members
// ... Initialize to unkown
LARGE_INTEGER COXTimer::m_nIntervalTimerFrequency = { 0, 0 };
CMap<COXTimer*, COXTimer*, BOOL, BOOL> COXTimer::m_allTimers;
CMap<DWORD, DWORD, COXTimer*, COXTimer*> COXTimer::m_synchronizedTimers;

// Data members -------------------------------------------------------------
// protected:
	// LARGE_INTEGER m_rgStartIntervalCounter;
	// --- Start time of interval timer
	//	   The unit are COUNTS of the performance counter

	// LARGE_INTEGER m_rgStopIntervalCounter;
	// --- Stop time of interval timer
	//	   The unit are COUNTS of the performance counter

	// static LARGE_INTEGER m_nIntervalTimerFrequency; 
	// --- Number of counts per second the performance counter uses
	//     Accurracy is 1/m_nIntervalTimerFrequency (in seconds)
	//	   -1 = Counter is not available
	//		0 = Not yet initialzed

	// DWORD m_nUserData;
	// --- The user data associated with this timer object

	// P_OX_TIMER_NOTIFICATION m_pfNotification;
	// --- Pointer to the notification function

	// UINTm_nNonSynchronizedTimerNotifierID;
	// --- Timer ID used by the non synchronized timer

	// UINT m_nSynchronizedTimerNotifierID;
	// --- Timer ID used by the synchronized timer

	// BOOL m_bPeriodic;
	// --- Whether the running timer is periodic or not

	// static CMap<COXTimer*, COXTimer*, BOOL, BOOL> m_allTimers;
	// --- Map of all the timers (only the key is used, not the value)

	// static CMap<DWORD, DWORD, COXTimer*, COXTimer*> m_synchronizedTimers;
	// --- Map of all running synchronized timers
	//	   Organizes a map between the (synchronized) timer ID and the COXTimer object
// private:
	
// Member functions ---------------------------------------------------------
// public:

COXTimer::COXTimer()
	:
	m_nUserData(0),
	m_pfNotification(NULL),
	m_nNonSynchronizedTimerNotifierID(0),
	m_nSynchronizedTimerNotifierID(0),
	m_bPeriodic(FALSE)
	{
	m_startIntervalCounter.QuadPart = 0;
	m_stopIntervalCounter.QuadPart = 0;

	// ... Register this new object in the global map
	m_allTimers.SetAt(this, TRUE);

	ASSERT_VALID(this);
	}

BOOL COXTimer::StartInterval()
	{
	if (::QueryPerformanceCounter(&m_startIntervalCounter))
		return TRUE;
	else
		{
		TRACE0("COXTimer::StartInterval : Failed to use performance counter\n");
		return FALSE;
		}
	}

void COXTimer::StopInterval()
	{
	if (!::QueryPerformanceCounter(&m_stopIntervalCounter))
		TRACE0("COXTimer::StopInterval : Failed to use performance counter\n");
	}

LONGLONG COXTimer::GetInterval() const
	{
	return (m_stopIntervalCounter.QuadPart - m_startIntervalCounter.QuadPart) * 
			GetIntervalAccuracy();
	}

LONGLONG COXTimer::GetIntervalAccuracy()
	{
	if (m_nIntervalTimerFrequency.QuadPart == 0)
		{
		// Variable has not yet been initialzed, do it now
		if (!::QueryPerformanceFrequency(&m_nIntervalTimerFrequency))
			// ... Mark as unavailable
			m_nIntervalTimerFrequency.QuadPart = -1;
		}

	if (m_nIntervalTimerFrequency.QuadPart < 0)
		return -1;
	else
		// ... return result in nanoseconds (1E-9 s)
		return 1000000000 / m_nIntervalTimerFrequency.QuadPart ;
	}

BOOL COXTimer::StartNotifier(LONGLONG nDelay, P_OX_TIMER_NOTIFICATION pfTimerNotification, 
		BOOL bPeriodic /* = FALSE */, BOOL bSynchronized /* = FALSE */, LONGLONG nAccuracy /* = -1 */)
	{
	// Convert to milliseconds because this is the smallest resolution we can use
	int nMilliDelay = NANO_TO_MILLI(nDelay);
	int nMilliAccuracy = 0;

	if (0 <= nAccuracy)
		nMilliAccuracy = NANO_TO_MILLI(nAccuracy);
	else
		{
		// Use 1% of the total delay time and always less than a second
		nMilliAccuracy = NANO_TO_MILLI(nDelay / 100);
		if (1000 < nMilliAccuracy)
			nMilliAccuracy = 1000;
		}

	// Adjust invalid requests
	if (nMilliDelay <= 0)
		{
		TRACE0("COXTimer::StartNotifier : Requested delay time to short, using 1 millisecond\n");
		nMilliDelay = 1;
		}
	if (nMilliAccuracy <= 0)
		{
		TRACE0("COXTimer::StartNotifier : Requested accuracy to high, using 1 millisecond\n");
		nMilliAccuracy = 1;
		}

	// Kill previous timers
	StopNotifier();

	m_bPeriodic = bPeriodic;
	if (!bSynchronized)
		return StartNonSynchronizedNotifier(nMilliDelay, pfTimerNotification, bPeriodic, 
			nMilliAccuracy);
	else 
		return StartSynchronizedNotifier(nMilliDelay, pfTimerNotification, bPeriodic, 
			nMilliAccuracy);
	}

void COXTimer::StopNotifier()
	{
	// Stop both nonsynchronized and synchronized timer
	StopNonSynchronizedNotifier();
	StopSynchronizedNotifier();

	m_pfNotification = NULL;
	}

void COXTimer::SetUserData(DWORD nUserData /* = 0 */)
	{
	m_nUserData = nUserData;
	}

DWORD COXTimer::GetUserData() const
	{
	return m_nUserData;
	}

#ifdef _DEBUG
void COXTimer::AssertValid() const
	{
	CObject::AssertValid();
	}

void COXTimer::Dump(CDumpContext& dc) const
	{
	CObject::Dump(dc);
	}
#endif //_DEBUG

COXTimer::~COXTimer()
	{
	// Stop possible running timer
	StopNotifier();
	ASSERT(m_nNonSynchronizedTimerNotifierID == 0);
	ASSERT(m_pfNotification == NULL);

	// Unregister this object from the global map
	m_allTimers.RemoveKey(this);
	}

// protected:
BOOL COXTimer::StartNonSynchronizedNotifier(int nMilliDelay, P_OX_TIMER_NOTIFICATION pfTimerNotification, 
	BOOL bPeriodic, int nMilliAccuracy)
	// --- In  : nMilliDelay : The delay in milliseconds that must elaps before the
	//					  notificvation function is called
	//			 pfTimerNotification : The notification function to call
	//			 bPeriodic : Whether the function should be called periodically (TRUE)
	//						 or just one (FALSE)
	//			 nMilliAccuracy : The minimum accuracy in milliseconds.  
	// --- Out : 
	// --- Returns : Whether it succeeded or not.  
	// --- Effect : Starts the non synchronized timer notifier
	{
	// Store the setting of this timer
	// (Must be set before starting timer so that there is no period during which the
	//  data members do not have a valid value)
	m_nNonSynchronizedTimerNotifierID = 0;
	m_pfNotification = pfTimerNotification;

	// Start a new timer
	m_nNonSynchronizedTimerNotifierID = ::timeSetEvent(nMilliDelay, nMilliAccuracy, 
		NonSynchronizedNotificationCallback, (DWORD)this, 
		bPeriodic ? TIME_PERIODIC : TIME_ONESHOT);
	if (m_nNonSynchronizedTimerNotifierID == 0)
		{
		TRACE0("COXTimer::StartNonSynchronizedNotifier : Failed to start the timer\n");
		// ... Reset data memebers
		m_pfNotification = NULL;
		}

	return (m_nNonSynchronizedTimerNotifierID != 0);
	}

void CALLBACK COXTimer::NonSynchronizedNotificationCallback(UINT /* uTimerID */, UINT /* uMsg */, DWORD dwUser, DWORD /* dw1 */, DWORD /* dw2 */)
	// --- In  : uTimerID : The timer ID
	//			 uMsg : 
	//			 dwUser : The user data
	//			 dw1 : 
	//			 dw2 : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : The non synchronized callback function of all objects 
{
	COXTimer* pTimer = (COXTimer*)dwUser;

	BOOL bDummy;
	if (!m_allTimers.Lookup(pTimer, bDummy))
	{
		TRACE1("COXTimer::NonSynchronizedNotificationCallback : Timer object at address 0x%X does not exist anymore, ignoring\n",
			pTimer);
		return;
	}

	// ... Do some sanity checks (timer object must still exist!)
	ASSERT(pTimer != NULL);
	ASSERT(AfxIsValidAddress(pTimer, sizeof(COXTimer)));
	ASSERT_VALID(pTimer);

	// ... Delegate to object
	pTimer->OnNonSynchronizedNotification();
}

void COXTimer::OnNonSynchronizedNotification()
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : The non synchronized callback function of this object 
	{
	if (m_pfNotification != NULL)
		m_pfNotification(this);
	}

void COXTimer::StopNonSynchronizedNotifier()
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : Stops the non synchronized timer notifier
	{
	if (m_nNonSynchronizedTimerNotifierID != 0)
		{
		// ... Only need to timeKillEvent if the timer was periodic
		if (m_bPeriodic)
			VERIFY(::timeKillEvent(m_nNonSynchronizedTimerNotifierID) == TIMERR_NOERROR);
		m_nNonSynchronizedTimerNotifierID = 0;
		}
	}

BOOL COXTimer::StartSynchronizedNotifier(int nMilliDelay, P_OX_TIMER_NOTIFICATION pfTimerNotification, 
	BOOL /* bPeriodic */, int /* nMilliAccuracy */)
	// --- In  : nMilliDelay : The delay in milliseconds that must elaps before the
	//					  notificvation function is called
	//			 pfTimerNotification : The notification function to call
	//			 bPeriodic : Whether the function should be called periodically (TRUE)
	//						 or just one (FALSE)
	//			 nMilliAccuracy : The minimum accuracy in milliseconds.  
	// --- Out : 
	// --- Returns : Whether it succeeded or not.  
	// --- Effect : Starts the synchronized timer notifier
	{
	// Store the setting of this timer
	// (Must be set before starting timer so that there is no period during which the
	//  data members do not have a valid value)
	m_nNonSynchronizedTimerNotifierID = 0;
	m_pfNotification = pfTimerNotification;

	// Start a new timer

	// Appearantly we have to specify a valid window handle, even when we are using a
	// callback function.  If we would use a callback function with a NULL HWND,
	// MFC's main message loop will not dispatch the thread message.
	// We will use the main window by default
#ifdef _DEBUG
	if (AfxGetMainWnd()->GetSafeHwnd() == NULL)
		TRACE0("COXTimer::StartSynchronizedNotifier : Function needs the HWND of the main window, may not be NULL, failing\n");
#endif

	m_nSynchronizedTimerNotifierID = ::SetTimer(AfxGetMainWnd()->GetSafeHwnd(), (DWORD)this, nMilliDelay, SynchronizedNotificationCallback);
	if (m_nSynchronizedTimerNotifierID != 0)
		{
		// Register as synchronized timer (ID - COXTimer*)
		m_synchronizedTimers.SetAt(m_nSynchronizedTimerNotifierID, this);
		}
	else
		{
		TRACE0("COXTimer::StartSynchronizedNotifier : Failed to start the timer\n");
		// ... Reset data memebers
		m_pfNotification = NULL;
		}

	return (m_nSynchronizedTimerNotifierID != 0);
	}

void CALLBACK COXTimer::SynchronizedNotificationCallback(HWND /*hWnd*/, 
														 UINT /*uMsg*/, 
														 UINT nTimerID, 
														 DWORD /*nTime*/)
	// --- In  : hWnd : 
	//			 uMsg :
	//			 uTimerID : The timer ID
	//			 nTime : The current time
	// --- Out : 
	// --- Returns : 
	// --- Effect : The synchronized callback function of all objects 
{
	COXTimer* pTimer = (COXTimer*)nTimerID;

	BOOL bDummy;
	if (!m_allTimers.Lookup(pTimer, bDummy))
		{
		TRACE1("COXTimer::SynchronizedNotificationCallback : Timer object at address 0x%X does not exist anymore, ignoring\n",
			pTimer);
		return;
		}

	// ... Do some sanity checks (timer object must still exist!)
	ASSERT(pTimer != NULL);
	ASSERT(AfxIsValidAddress(pTimer, sizeof(COXTimer)));
	ASSERT_VALID(pTimer);

	// ... Delegate to object
	pTimer->OnSynchronizedNotification();
}

void COXTimer::OnSynchronizedNotification()
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : The synchronized callback function of this object 
	{
	if (m_pfNotification != NULL)
		m_pfNotification(this);

	// If this is not a periodic timer, kill the timer now
	if (!m_bPeriodic)
		StopNotifier();
	}

void COXTimer::StopSynchronizedNotifier()
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : Stops the synchronized timer notifier
	{
	if (m_nSynchronizedTimerNotifierID != 0)
		{
		// ... KillTimer may return FALSE if the main window has already been destroyed
		::KillTimer(AfxGetMainWnd()->GetSafeHwnd(), m_nSynchronizedTimerNotifierID);
		// ... Remove from global map
		VERIFY(m_synchronizedTimers.RemoveKey(m_nSynchronizedTimerNotifierID));
		m_nSynchronizedTimerNotifierID = 0;
		}
	}

// private:

// ==========================================================================
