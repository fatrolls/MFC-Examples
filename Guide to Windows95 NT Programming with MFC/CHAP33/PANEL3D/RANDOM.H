///////////////////////////////////////////////////////////////////
//  Module   : RANDOM.H
//
//  Purpose  : Provides global random number functions.
//
//  Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date     : 04-29-96
///////////////////////////////////////////////////////////////////

#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <stdlib.h>  // for srand(), rand()

///////////////////////////////////////////////////////////////////
// CRand class

class CRand : public CObject
{
public:
   CRand();

public:
   UINT MapRand(UINT nMax);

protected:
   // Macro for seeding random number generator
   inline void SeedRand() { srand((UINT)::GetTickCount()); }
};

///////////////////////////////////////////////////////////////////
// CRand::CRand() - constructor

CRand::CRand() 
{
   SeedRand();
}

///////////////////////////////////////////////////////////////////
// CRand::MapRand() - helper method maps random number to nMax

UINT CRand::MapRand(UINT nMax)
{
   // The random number generator is seeded with the
   // SeedRand() method in the CRand constructor!
   
   // Map a random number to nMax
   int   nRand   = rand();
   float fMap    = (float) nMax / RAND_MAX;
   float fRetVal = (float) nRand * fMap + 0.5F;

   return (UINT) fRetVal;
}

#endif  // __RANDOM_H__

///////////////////////////////////////////////////////////////////