#if ! defined( SIMPLE_CLASS_HEADER )

/*
** Author: Samuel R. Blackburn
** Internet: sblackbu@erols.com
**
** You can use it any way you like as long as you don't try to sell it.
**
** Any attempt to sell WFC in source code form must have the permission
** of the original author. You can produce commercial executables with
** WFC but you can't sell WFC.
**
** Copyright, 1997, Samuel R. Blackburn
**
** $Workfile: CDataFile.hpp $
** $Revision: 1 $
** $Modtime: 6/10/97 7:42p $
*/

#define SIMPLE_CLASS_HEADER

class CSimpleClass
{
   public:

      char         CharacterValue;
      BYTE         ByteValue;
      WORD         WordValue;
      LONG         LongValue;
      DWORD        DwordValue;
      float        FloatValue;
      double       DoubleValue;
      CString      StringValue;
      CByteArray   ByteArray;
      CStringArray StringArray;
      CDWordArray  DwordArray;
      CWordArray   WordArray;

      CSimpleClass()
      {
         CharacterValue = 0;
         ByteValue      = 0;
         WordValue      = 0;
         LongValue      = 0;
         DwordValue     = 0;
         FloatValue     = 0.0;
         DoubleValue    = 0.0;
      };

     ~CSimpleClass()
      {
         CharacterValue = 0;
         ByteValue      = 0;
         WordValue      = 0;
         LongValue      = 0;
         DwordValue     = 0;
         FloatValue     = 0.0;
         DoubleValue    = 0.0;
      };

      // Here's where we tell the class how to read/write itself
      // to/from a CDataChunk

      void Serialize( CDataArchive& archive )
      {
         if ( archive.IsStoring() == TRUE )
         {
            archive.Write( CharacterValue );
            archive.Write( ByteValue      );
            archive.Write( WordValue      );
            archive.Write( LongValue      );
            archive.Write( DwordValue     );
            archive.Write( FloatValue     );
            archive.Write( DoubleValue    );
            archive.Write( StringValue    );
            archive.Write( ByteArray      );
            archive.Write( StringArray    );
            archive.Write( DwordArray     );
            archive.Write( WordArray      );
         }
         else
         {
            archive.Read( CharacterValue );
            archive.Read( ByteValue      );
            archive.Read( WordValue      );
            archive.Read( LongValue      );
            archive.Read( DwordValue     );
            archive.Read( FloatValue     );
            archive.Read( DoubleValue    );
            archive.Read( StringValue    );
            archive.Read( ByteArray      );
            archive.Read( StringArray    );
            archive.Read( DwordArray     );
            archive.Read( WordArray      );
         }
      }

      void Dump( void ) const
      {
         _tprintf( TEXT( "This CSimpleClass contains:\n" ) );
         _tprintf( TEXT( "CharacterValue '%c'\n" ), CharacterValue  );
         _tprintf( TEXT( "ByteValue      %02X\n" ), (int) ByteValue );
         _tprintf( TEXT( "WordValue      %04X\n" ), (int) WordValue );
         _tprintf( TEXT( "DwordValue     %08X\n" ), DwordValue );
         _tprintf( TEXT( "FloatValue     %.14f\n" ), FloatValue );
         _tprintf( TEXT( "DoubleValue    %.14lf\n" ), DoubleValue );
         _tprintf( TEXT( "StringValue    %s\n" ), (LPCTSTR) StringValue );

         DWORD index = 0;

         index = ByteArray.GetSize();

         _tprintf( TEXT( "ByteArray contains %lu elements\n" ), index );

         if ( index != 0 )
         {
            index = 0;

            while( index < ByteArray.GetSize() )
            {
               _tprintf( TEXT( "   [%02d] = %02X\n" ), (int) index, ByteArray.GetAt( index ) );
               index++;
            }
         }

         index = WordArray.GetSize();

         _tprintf( TEXT( "WordArray contains %lu elements\n" ), index );

         if ( index != 0 )
         {
            index = 0;

            while( index < WordArray.GetSize() )
            {
               _tprintf( TEXT( "   [%02d] = %04X\n" ), (int) index, WordArray.GetAt( index ) );
               index++;
            }
         }

         index = DwordArray.GetSize();

         _tprintf( TEXT( "DwordArray contains %lu elements\n" ), index );

         if ( index != 0 )
         {
            index = 0;

            while( index < DwordArray.GetSize() )
            {
               _tprintf( TEXT( "   [%02d] = %08X\n" ), (int) index, DwordArray.GetAt( index ) );
               index++;
            }
         }

         index = StringArray.GetSize();

         _tprintf( TEXT( "StringArray contains %lu elements\n" ), index );

         if ( index != 0 )
         {
            index = 0;

            while( index < StringArray.GetSize() )
            {
               _tprintf( TEXT( "   [%02d] = %s\n" ), (int) index, (const char *) StringArray.GetAt( index ) );
               index++;
            }
         }
      }
};

#endif // SIMPLE_CLASS_HEADER
