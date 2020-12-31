#ifndef INCLUDE_CTIMER_HPP_
#define INCLUDE_CTIMER_HPP_

#if defined(_MSC_VER)
#  define NOMINMAX // workaround a bug in windows.h
#  include <windows.h>
#else
#  include <sys/time.h>
#endif

namespace Utils
{
   class CTimer
   {
   private:
#     if defined(_MSC_VER)
         LARGE_INTEGER m_depart;
#     else
         timeval m_depart;
#     endif

   public:
      inline void start()
      {
#        if defined(_MSC_VER)
            QueryPerformanceCounter(&m_depart);
#        else
            gettimeofday(&m_depart, 0);
#        endif
      };

      inline float GetSecondes() const
      {
#        if defined(_MSC_VER)
            LARGE_INTEGER now;
            LARGE_INTEGER freq;

            QueryPerformanceCounter(&now);
            QueryPerformanceFrequency(&freq);

            return (now.QuadPart - m_depart.QuadPart) / static_cast<float>(freq.QuadPart);
#        else
            timeval now;
            gettimeofday(&now, 0);

            return now.tv_sec - m_depart.tv_sec + (now.tv_usec - m_depart.tv_usec) / 1000000.0f;
#        endif
      };
   };
}
#endif // INCLUDE_CTIMER_HPP_
