#include "niftycounter.hpp"
//Stream.cpp
static int nifty_counter = 0; 
// The counter is initialized at load-time i.e., before any of the static objects are initialized.
StreamInitializer::StreamInitializer ()
{
   if (0 == nifty_counter++)
   {
      // Initialize Stream object's static members.
   }
}
StreamInitializer::~StreamInitializer ()
{
   if (0 == --nifty_counter)
   {
      // Clean-up.
   }
}

