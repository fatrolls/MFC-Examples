// ==========================================================================
// 					Class Specification : COXTimer
// ==========================================================================

// Header file : OXTimer.h

// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CObject

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	This class can be used to measure the elapsed time between two moments
//	 (interval timer) or the trigger a notification when a specified amount 
//	 of time has elapsed (notification timer)

// Remark:
//	All time is expressed in nanoseconds.  But it is possible that such an 
//	 accuracy is not met (either by the hardware or by Win32).
//	An interval timer can be queried for its resolution

// Prerequisites (necessary conditions):

/////////////////////////////////////////////////////////////////////////////

#ifndef __OXTIMER_H__
#define __OXTIMER_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

#include <AfxTempl.h>


class COXTimer;

// ... Type definition of the callback function
typedef void (CALLBACK OX_TIMER_NOTIFICATION) (COXTimer* pTimer);
typedef OX_TIMER_NOTIFICATION* P_OX_TIMER_NOTIFICATION;

// Some handy macros to convert between unit, milli, micro and nano
// Nano seconds use a LONGLONG, unit, milli and micro use an int
#define NANO_TO_MICRO(nano) (int)((LONGLONG)(nano) / 1000)
#define NANO_TO_MILLI(nano) (int)((LONGLONG)(nano) / 1000000)
#define NANO_TO_UNIT(nano)	(int)((LONGLONG)(nano) / 1000000000)
#define MICRO_TO_NANO(micro) ((LONGLONG)(micro) * 1000)
#define MILLI_TO_NANO(milli) ((LONGLONG)(milli) * 1000000)
#define UNIT_TO_NANO(unit)	 ((LONGLONG)(unit)  * 1000000000)
 
class OX_CLASS_DECL COXTimer : public CObject
{
DECLARE_DYNAMIC(COXTimer);

// Data members -------------------------------------------------------------
public:
protected:
	LARGE_INTEGER	m_startIntervalCounter;
	LARGE_INTEGER	m_stopIntervalCounter;
	static LARGE_INTEGER m_nIntervalTimerFrequency;  // -1 = not available, 0 = unknown, other OK

	DWORD	m_nUserData;
	P_OX_TIMER_NOTIFICATION m_pfNotification;
	UINT	m_nNonSynchronizedTimerNotifierID;
	UINT	m_nSynchronizedTimerNotifierID;
	BOOL	m_bPeriodic;
	static CMap<COXTimer*, COXTimer*, BOOL, BOOL> m_allTimers;
	static CMap<DWORD, DWORD, COXTimer*, COXTimer*> m_synchronizedTimers;

private:
	
// Member functions ---------------------------------------------------------
public:
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Constructs the object
	COXTimer();

	// *** Interval Timer functions

	// --- In  : 
	// --- Out : 
	// --- Returns : Whether it succeeded or not.  This function may fail if the platform
	//				 does not support a high accuracy interval timer
	// --- Effect : Starts the interval timer
	BOOL StartInterval();

	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : Stops the interval timer
	void StopInterval();


	// --- In  : 
	// --- Out : 
	// --- Returns : The elapsed time of the counter in nanoseconds
	//				 There are 1,000,000,000 nanoseconds in 1 second
	//				 If the value is not strictly positive an error has occurred
	// --- Effect : This function returns the elapsed time between the last start and stop
	//				of the counter
	LONGLONG GetInterval() const;

	// --- In  : 
	// --- Out : 
	// --- Returns : The maximum accuracy of an interval timer specified in nanoseconds
	//				 There are 1,000,000,000 nanoseconds in 1 second
	//				 (return -1 in case the platform does not support a 
	//				  high accuracy interval timer)
	// --- Effect : 
	static LONGLONG GetIntervalAccuracy();


	// *** Notification Timer functions

	// --- In  : nDelay : The delay in nanoseconds that must elaps before the
	//					  notificvation function is called
	//			 pfTimerNotification : The notification function to call
	//			 bPeriodic : Whether the function should be called periodically (TRUE)
	//						 or just one (FALSE)
	//			 bSynchronized : Whether the callback should be called from this thread (TRUE)
	//							 or from a seperate dedicated thread (TRUE)
	//							 Using a seperate thread will produce more superieur results
	//			 nAccuracy : The minimum accuracy in nanoseconds.  Bu default this is 1%
	//						   of the specified delay with a maximum of 1 second
	// --- Out : 
	// --- Returns : Whether it succeeded or not.  
	// --- Effect : Starts the timer notifier
	//				Using this function with a very small delay time (< 10 ms) might
	//				use so much CPU time that your computers seems to hang
	BOOL StartNotifier(LONGLONG nDelay, P_OX_TIMER_NOTIFICATION pfTimerNotification, 
		BOOL bPeriodic = FALSE, BOOL bSynchronized = FALSE, LONGLONG nAccuracy = -1);

	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : Stops the timer notifier
	void StopNotifier();


	// --- In  : nUserData : The user data to associate with this timer
	// --- Out : 
	// --- Returns : 
	// --- Effect : 
	void SetUserData(DWORD nUserData = 0);


	// --- In  : 
	// --- Out : 
	// --- Returns : The user data associated with this timer
	// --- Effect : 
	DWORD GetUserData() const;


#ifdef _DEBUG
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : AssertValid performs a validity check on this object 
	//				by checking its internal state. 
	//				In the Debug version of the library, AssertValid may assert and 
	//				thus terminate the program.
	virtual void AssertValid() const;
	
	// --- In  : dc : The diagnostic dump context for dumping, usually afxDump.
	// --- Out : 
	// --- Returns :
	// --- Effect : Dumps the contents of the object to a CDumpContext object. 
	//				It provides diagnostic services for yourself and 
	//				 other users of your class. 
	//				Note  The Dump function does not print a newline character
	//				 at the end of its output. 
	virtual void Dump(CDumpContext& dc) const;
#endif

	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of the object
	virtual ~COXTimer();

protected:
	BOOL StartNonSynchronizedNotifier(int nMilliDelay, P_OX_TIMER_NOTIFICATION pfTimerNotification, 
		BOOL bPeriodic, int nMilliAccuracy);
	static void CALLBACK NonSynchronizedNotificationCallback(UINT uTimerID, UINT uMsg, 
		DWORD dwUser, DWORD dw1, DWORD dw2);
	void OnNonSynchronizedNotification();
	void StopNonSynchronizedNotifier();

	BOOL StartSynchronizedNotifier(int nMilliDelay, P_OX_TIMER_NOTIFICATION pfTimerNotification, 
		BOOL bPeriodic, int nMilliAccuracy);
	static void CALLBACK SynchronizedNotificationCallback(HWND hWnd, UINT uMsg, 
		UINT nTimerID, DWORD nTime);
	void OnSynchronizedNotification();
	void StopSynchronizedNotifier();

private:
                   
};

#endif // __OXTIMER_H__
// ==========================================================================
