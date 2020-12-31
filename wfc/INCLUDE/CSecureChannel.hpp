#if ! defined( SECURE_CHANNEL_CLASS_HEADER )

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
** Copyright, 1998, Samuel R. Blackburn
**
** $Workfile: CSecureChannel.hpp $
** $Revision: 4 $
** $Modtime: 3/08/98 12:01p $
*/

#define SECURE_CHANNEL_CLASS_HEADER

class CSecureChannel
{
   protected:

      DWORD m_ErrorCode;

      CFile * m_File_p;

      CCryptographicProvider  m_Provider;
      CCryptographicAlgorithm m_Algorithm;
      CCryptographicKey       m_SendingKey;   // Used for encrypting
      CCryptographicKey       m_ReceivingKey; // Used for decrypting

   public:

      CSecureChannel();
      virtual ~CSecureChannel();

      virtual BOOL Open( CUniformResourceLocator& url );
      virtual BOOL Close( void );
};

#endif // SECURE_CHANNEL_CLASS_HEADER
