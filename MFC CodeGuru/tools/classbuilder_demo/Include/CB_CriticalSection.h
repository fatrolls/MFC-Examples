#ifndef CB_CRITICAL_SECTION
#define CB_CRITICAL_SECTION

// This is Windows specific, need to change this for other platforms.
#include <windows.h>
#include <process.h>

class CriticalSection
{
private:
    CRITICAL_SECTION _criticalSection;

public:
    CriticalSection()
    {
        InitializeCriticalSection(&_criticalSection);
    }
    ~CriticalSection()
    {
        DeleteCriticalSection(&_criticalSection);
    }

    void Enter()
    { 
        EnterCriticalSection(&_criticalSection); 
    }
    void Leave()
    { 
        LeaveCriticalSection(&_criticalSection); 
    }
};

class CriticalSectionLock
{
private:
    CriticalSection& _criticalSection;

public:
    CriticalSectionLock(CriticalSection& criticalSection)
        : _criticalSection(criticalSection) 
    { 
        _criticalSection.Enter();
    }
    ~CriticalSectionLock()
    {
        _criticalSection.Leave();
    }
};

#endif