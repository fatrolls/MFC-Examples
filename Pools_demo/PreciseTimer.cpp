
//PreciseTimer.cpp

#include "stdafx.h"
#include "PreciseTimer.h"

bool CPreciseTimer::sm_bInit = false;
bool CPreciseTimer::sm_bPerformanceCounter;
__int64 CPreciseTimer::sm_i64Freq;

//CONSTRUCTOR
CPreciseTimer::CPreciseTimer() : m_i64Start(0), m_i64Elapsed(0), m_bRunning(false)
{
	//Only if not already initialized
	if(false == sm_bInit)
	{
		//Initializing some static variables dependent on the system just once
		LARGE_INTEGER liFreq;
		if(TRUE == QueryPerformanceFrequency(&liFreq))
		{
			//Only if the system is supporting High Performance
			sm_i64Freq = ((__int64)liFreq.HighPart << 32) + (__int64)liFreq.LowPart;
			sm_bPerformanceCounter = true;
		}
		else
			sm_bPerformanceCounter = false;
		sm_bInit = true;
	}
}

void CPreciseTimer::StartTimer()
{
	if(true == sm_bPerformanceCounter)
	{
		QueryPerformanceCounter(&m_liCount);
		m_i64Start = ((__int64)m_liCount.HighPart << 32) + (__int64)m_liCount.LowPart;
		//Transform in microseconds
		(m_i64Start *= 1000000) /= sm_i64Freq;
	}
	else
		//Transform milliseconds to microseconds
		m_i64Start = (__int64)GetTickCount() * 1000;
	m_bRunning = true;
}

void CPreciseTimer::StopTimer()
{
	UpdateElapsed();
	m_bRunning = false;
}

__int64 CPreciseTimer::GetTime()
{
	if(true == m_bRunning)
		UpdateElapsed();
	return m_i64Elapsed;
}

