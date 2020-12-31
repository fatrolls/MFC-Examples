#if ! defined( SPRINT_SPECTRUM_CLASS_HEADER )

/*
** Author: Samuel R. Blackburn
** Internet: wfc@pobox.com
**
** You can use it any way you like as long as you don't try to sell it.
**
** Any attempt to sell WFC in source code form must have the permission
** of the original author. You can produce commercial executables with
** WFC but you can't sell WFC.
**
** Copyright, 2000, Samuel R. Blackburn
**
** $Workfile: SprintSpectrum.hpp $
** $Revision: 6 $
** $Modtime: 1/04/00 5:01a $
*/

#define SPRINT_SPECTRUM_CLASS_HEADER

class CSprintSpectrum : public CPager
{
   protected:

      virtual BOOL m_Send( void );

   public:

      CSprintSpectrum();

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CSprintSpectrum();
};

#endif // SPRINT_SPECTRUM_CLASS_HEADER
