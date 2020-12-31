#if ! defined( DCB_CLASS_HEADER )

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
** $Workfile: dcb.hpp $
** $Revision: 11 $
** $Modtime: 1/04/00 5:00a $
*/

/*
** Thanks go to Jim Schollenberger (J_A_S@compuserve.com)
** for finding a typo here...
*/

#define DCB_CLASS_HEADER

class CDeviceControlBlock : public _DCB
{
   public:

      CDeviceControlBlock();
      CDeviceControlBlock( const DCB * source );
      CDeviceControlBlock( const DCB& source );
      CDeviceControlBlock( const CDeviceControlBlock& source );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CDeviceControlBlock();

      /*
      ** Methods
      */

      virtual void Copy( const CDeviceControlBlock& source );
      virtual void Copy( const DCB *source );
      virtual void Copy( const DCB& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG

      virtual CDeviceControlBlock& operator=( const CDeviceControlBlock& source );
      virtual CDeviceControlBlock& operator=( const DCB& source );
};

#endif // DCB_CLASS_HEADER
