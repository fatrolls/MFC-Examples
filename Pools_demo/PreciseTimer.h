
//PreciseTimer.h

#ifndef _PRECISETIMER_H_
#define _PRECISE_H_

//More precise Timer for measuring time intervals in microseconds.
//The performance of this Timer is dependent on the performance of the system.
class CPreciseTimer
{
public:
	//CONSTRUCTOR
	CPreciseTimer();

	bool SupportsHighResCounter();
	void StartTimer();
	void StopTimer();
	__int64 GetTime();

private:
	//Auxiliary Function
	void UpdateElapsed();

	//Member variables
	bool m_bRunning;	
	__int64 m_i64Start;
	__int64 m_i64Elapsed;

	//Some auxiliary variables
	__int64 m_i64Counts;
	LARGE_INTEGER m_liCount;

	//Static Variables
	static bool sm_bInit;
	static bool sm_bPerformanceCounter;
	static __int64 sm_i64Freq;
};

inline bool CPreciseTimer::SupportsHighResCounter()
{
	return sm_bPerformanceCounter;
}

//Auxiliary Function
inline void CPreciseTimer::UpdateElapsed()
{
	if(true == sm_bPerformanceCounter)
	{
		QueryPerformanceCounter(&m_liCount);
		m_i64Counts = ((__int64)m_liCount.HighPart << 32) + (__int64)m_liCount.LowPart;
		//Transform in microseconds
		(m_i64Counts *= 1000000) /= sm_i64Freq;
	}
	else
		//Transform milliseconds to microseconds
		m_i64Counts = (__int64)GetTickCount() * 1000;
	if(m_i64Counts > m_i64Start)
		m_i64Elapsed = m_i64Counts - m_i64Start;
	else
		//Eliminate possible number overflow (0x7fffffffffffffff is the maximal __int64 positive number)
		m_i64Elapsed = (0x7fffffffffffffff - m_i64Start) + m_i64Counts;
}

#endif // _PRECISETIMER_H_


