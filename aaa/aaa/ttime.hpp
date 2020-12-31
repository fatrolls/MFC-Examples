#pragma  once
#include <windows.h>

#pragma comment(lib,"winmm.lib")

//timeGetTime 精度是1ms,默认是10ms

    //#include <winbase.h>
    //#pragma comment(lib,"kernel32.dll")
    //GetTickCount 精度是10ms
    //clock 精度是10ms
    
    class N_Script_Timer
{
        public:
                N_Script_Timer()
                {
                        running = false;
                        milliseconds = 0;
                        seconds = 0;
                        start_t = 0;
                        end_t = 0;
                }
                void Start()
                {
                        if(running)return;
                        running = true;
                        timeBeginPeriod(1);
                        start_t = timeGetTime();
                }
                void End()
                {
                        if(!running)return;
                        running = false;
                        end_t = timeGetTime();
                        timeEndPeriod(1);
                        milliseconds = end_t - start_t;
                        seconds = milliseconds / (float)1000;
                }
                float milliseconds;
                float seconds;

        private:
                unsigned long start_t;
                unsigned long end_t;
                bool running;
};

