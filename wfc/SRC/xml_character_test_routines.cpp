#if ! defined( SUBSET_STLXML )
#include <wfc.h>
#else
#include <stlxml.h>
#endif
#pragma hdrstop

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
** $Workfile: xml_character_test_routines.cpp $
** $Revision: 3 $
** $Modtime: 1/28/00 5:33p $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

typedef struct _wfc_range
{
   DWORD low;
   DWORD high;
}
WFC_RANGE;

static inline BOOL __wfc_range_check( DWORD value_to_test, const WFC_RANGE * range, DWORD number_of_ranges )
{
   long bottom = 0;
   long top    = number_of_ranges - 1;
   long middle = 0;
   long half   = 0;

   while( bottom <= top )
   {
      half = number_of_ranges >> 1; // Same as dividing by two only faster

      if ( half != 0 )
      {
         middle = bottom + ( ( number_of_ranges & 1 ) ? half : ( half - 1 ) );

         if ( value_to_test >= range[ middle ].low &&
              value_to_test <= range[ middle ].high )
         {
            return( TRUE );
         }

         if ( value_to_test < range[ middle ].high )
         {
            top = middle - 1;
            number_of_ranges = ( number_of_ranges & 1 ) ? half : ( half - 1 );
         }
         else
         {
            bottom = middle + 1;
            number_of_ranges = half;
         }
      }
      else
      {
         if ( value_to_test >= range[ bottom ].low &&
              value_to_test <= range[ bottom ].high )
         {
            return( TRUE );
         }

         return( FALSE );
      }
   }

   return( FALSE );
}

BOOL is_xml_BaseChar( DWORD character_to_test )
{
   // Test according to Rule 85

   static const WFC_RANGE static_basechar_range[ 201 ] = 
   {
      { 0x41, 0x5A }, // 0
      { 0x61, 0x7A }, // 1
      { 0xC0, 0xD6 }, // 2
      { 0xD8, 0xF6 }, // 3
      { 0xF8, 0xFF }, // 4
      { 0x0100, 0x0131 }, // 5
      { 0x0134, 0x013E }, // 6
      { 0x0141, 0x0148 }, // 7
      { 0x014A, 0x017E }, // 8
      { 0x0180, 0x01C3 }, // 9
      { 0x01CD, 0x01F0 }, // 10
      { 0x01F4, 0x01F5 }, // 11
      { 0x01FA, 0x0217 }, // 12
      { 0x0250, 0x02A8 }, // 13
      { 0x02BB, 0x02C1 }, // 14
      { 0x0386, 0x0386 }, // 15
      { 0x0388, 0x038A }, // 16
      { 0x038C, 0x038C }, // 17
      { 0x038E, 0x03A1 }, // 18
      { 0x03A3, 0x03CE }, // 19
      { 0x03D0, 0x03D6 }, // 20
      { 0x03DA, 0x03DA }, // 21
      { 0x03DC, 0x03DC }, // 22
      { 0x03DE, 0x03DE }, // 23
      { 0x03E0, 0x03E0 }, // 24
      { 0x03E2, 0x03F3 }, // 25
      { 0x0401, 0x040C }, // 26
      { 0x040E, 0x044F }, // 27
      { 0x0451, 0x045C }, // 28
      { 0x045E, 0x0481 }, // 29
      { 0x0490, 0x04C4 }, // 30
      { 0x04C7, 0x04C8 }, // 31
      { 0x04CB, 0x04CC }, // 32
      { 0x04D0, 0x04EB }, // 33
      { 0x04EE, 0x04F5 }, // 34
      { 0x04F8, 0x04F9 }, // 35
      { 0x0531, 0x0556 }, // 36
      { 0x0559, 0x0559 }, // 37
      { 0x0561, 0x0586 }, // 38
      { 0x05D0, 0x05EA }, // 39
      { 0x05F0, 0x05F2 }, // 40
      { 0x0621, 0x063A }, // 41
      { 0x0641, 0x064A }, // 42
      { 0x0671, 0x06B7 }, // 43
      { 0x06BA, 0x06BE }, // 44
      { 0x06C0, 0x06CE }, // 45
      { 0x06D0, 0x06D3 }, // 46
      { 0x06D5, 0x06D5 }, // 47
      { 0x06E5, 0x06E6 }, // 48
      { 0x0905, 0x0939 }, // 49
      { 0x093D, 0x093D }, // 50
      { 0x0958, 0x0961 }, // 51
      { 0x0985, 0x098C }, // 52
      { 0x098F, 0x0990 }, // 53
      { 0x0993, 0x09A8 }, // 54
      { 0x09AA, 0x09B0 }, // 55
      { 0x09B2, 0x09B2 }, // 56
      { 0x09B6, 0x09B9 }, // 57
      { 0x09DC, 0x09DD }, // 58
      { 0x09DF, 0x09E1 }, // 59
      { 0x09F0, 0x09F1 }, // 60
      { 0x0A05, 0x0A0A }, // 61
      { 0x0A0F, 0x0A10 }, // 62
      { 0x0A13, 0x0A28 }, // 63
      { 0x0A2A, 0x0A30 }, // 64
      { 0x0A32, 0x0A33 }, // 65
      { 0x0A35, 0x0A36 }, // 66
      { 0x0A38, 0x0A39 }, // 67
      { 0x0A59, 0x0A5C }, // 68
      { 0x0A5E, 0x0A5E }, // 69
      { 0x0A72, 0x0A74 }, // 70
      { 0x0A85, 0x0A8B }, // 71
      { 0x0A8D, 0x0A8D }, // 72
      { 0x0A8F, 0x0A91 }, // 73
      { 0x0A93, 0x0AA8 }, // 74
      { 0x0AAA, 0x0AB0 }, // 75
      { 0x0AB2, 0x0AB3 }, // 76
      { 0x0AB5, 0x0AB9 }, // 77
      { 0x0ABD, 0x0ABD }, // 78
      { 0x0AE0, 0x0AE0 }, // 79
      { 0x0B05, 0x0B0C }, // 80
      { 0x0B0F, 0x0B10 }, // 81
      { 0x0B13, 0x0B28 }, // 82
      { 0x0B2A, 0x0B30 }, // 83
      { 0x0B32, 0x0B33 }, // 84
      { 0x0B36, 0x0B39 }, // 85
      { 0x0B3D, 0x0B3D }, // 86
      { 0x0B5C, 0x0B5D }, // 87
      { 0x0B5F, 0x0B61 }, // 88
      { 0x0B85, 0x0B8A }, // 89
      { 0x0B8E, 0x0B90 }, // 90
      { 0x0B92, 0x0B95 }, // 91
      { 0x0B99, 0x0B9A }, // 92
      { 0x0B9C, 0x0B9C }, // 93
      { 0x0B9E, 0x0B9F }, // 94
      { 0x0BA3, 0x0BA4 }, // 95
      { 0x0BA8, 0x0BAA }, // 96
      { 0x0BAE, 0x0BB5 }, // 97
      { 0x0BB7, 0x0BB9 }, // 98
      { 0x0C05, 0x0C0C }, // 99
      { 0x0C0E, 0x0C10 }, // 100
      { 0x0C12, 0x0C28 }, // 101
      { 0x0C2A, 0x0C33 }, // 102
      { 0x0C35, 0x0C39 }, // 103
      { 0x0C60, 0x0C61 }, // 104
      { 0x0C85, 0x0C8C }, // 105
      { 0x0C8E, 0x0C90 }, // 106
      { 0x0C92, 0x0CA8 }, // 107
      { 0x0CAA, 0x0CB3 }, // 108
      { 0x0CB5, 0x0CB9 }, // 109
      { 0x0CDE, 0x0CDE }, // 110
      { 0x0CE0, 0x0CE1 }, // 111
      { 0x0D05, 0x0D0C }, // 112
      { 0x0D0E, 0x0D10 }, // 113
      { 0x0D12, 0x0D28 }, // 114
      { 0x0D2A, 0x0D39 }, // 115
      { 0x0D60, 0x0D61 }, // 116
      { 0x0E01, 0x0E2E }, // 117
      { 0x0E30, 0x0E30 }, // 118
      { 0x0E32, 0x0E33 }, // 119
      { 0x0E40, 0x0E45 }, // 120
      { 0x0E81, 0x0E82 }, // 121
      { 0x0E84, 0x0E84 }, // 122
      { 0x0E87, 0x0E88 }, // 123
      { 0x0E8A, 0x0E8A }, // 124
      { 0x0E8D, 0x0E8D }, // 125
      { 0x0E94, 0x0E97 }, // 126
      { 0x0E99, 0x0E9F }, // 127
      { 0x0EA1, 0x0EA3 }, // 128
      { 0x0EA5, 0x0EA5 }, // 129
      { 0x0EA7, 0x0EA7 }, // 130
      { 0x0EAA, 0x0EAB }, // 131
      { 0x0EAD, 0x0EAE }, // 132
      { 0x0EB0, 0x0EB0 }, // 133
      { 0x0EB2, 0x0EB3 }, // 134
      { 0x0EBD, 0x0EBD }, // 135
      { 0x0EC0, 0x0EC4 }, // 136
      { 0x0F40, 0x0F47 }, // 137
      { 0x0F49, 0x0F69 }, // 138
      { 0x10A0, 0x10C5 }, // 139
      { 0x10D0, 0x10F6 }, // 140
      { 0x1100, 0x1100 }, // 141
      { 0x1102, 0x1103 }, // 142
      { 0x1105, 0x1107 }, // 143
      { 0x1109, 0x1109 }, // 144
      { 0x110B, 0x110C }, // 145
      { 0x110E, 0x1112 }, // 146
      { 0x113C, 0x113C }, // 147
      { 0x113E, 0x113E }, // 148
      { 0x1140, 0x1140 }, // 149
      { 0x114C, 0x114C }, // 150
      { 0x114E, 0x114E }, // 151
      { 0x1154, 0x1155 }, // 152
      { 0x1159, 0x1159 }, // 153
      { 0x115F, 0x1161 }, // 154
      { 0x1163, 0x1163 }, // 155
      { 0x1165, 0x1165 }, // 156
      { 0x1167, 0x1167 }, // 157
      { 0x1169, 0x1169 }, // 158
      { 0x116D, 0x116E }, // 159
      { 0x1172, 0x1173 }, // 160
      { 0x1175, 0x1175 }, // 161
      { 0x119E, 0x119E }, // 162
      { 0x11A8, 0x11A8 }, // 163
      { 0x11AB, 0x11AB }, // 164
      { 0x11AE, 0x11AF }, // 165
      { 0x11B7, 0x11B8 }, // 166
      { 0x11BA, 0x11BA }, // 167
      { 0x11BC, 0x11C2 }, // 168
      { 0x11EB, 0x11EB }, // 169
      { 0x11F0, 0x11F0 }, // 170
      { 0x11F9, 0x11F9 }, // 171
      { 0x1E00, 0x1E9B }, // 172
      { 0x1EA0, 0x1EF9 }, // 173
      { 0x1F00, 0x1F15 }, // 174
      { 0x1F18, 0x1F1D }, // 175
      { 0x1F20, 0x1F45 }, // 176
      { 0x1F48, 0x1F4D }, // 177
      { 0x1F50, 0x1F57 }, // 178
      { 0x1F59, 0x1F59 }, // 179
      { 0x1F5B, 0x1F5B }, // 180
      { 0x1F5D, 0x1F5D }, // 181
      { 0x1F5F, 0x1F7D }, // 182
      { 0x1F80, 0x1FB4 }, // 183
      { 0x1FB6, 0x1FBC }, // 184
      { 0x1FBE, 0x1FBE }, // 185
      { 0x1FC2, 0x1FC4 }, // 186
      { 0x1FC6, 0x1FCC }, // 187
      { 0x1FD0, 0x1FD3 }, // 188
      { 0x1FD6, 0x1FDB }, // 189
      { 0x1FE0, 0x1FEC }, // 190
      { 0x1FF2, 0x1FF4 }, // 191
      { 0x1FF6, 0x1FFC }, // 192
      { 0x2126, 0x2126 }, // 193
      { 0x212A, 0x212B }, // 194
      { 0x212E, 0x212E }, // 195
      { 0x2180, 0x2182 }, // 196
      { 0x3041, 0x3094 }, // 197
      { 0x30A1, 0x30FA }, // 198
      { 0x3105, 0x312C }, // 199
      { 0xAC00, 0xD7A3 }  // 200
   };

   return( __wfc_range_check( character_to_test, static_basechar_range, 201 ) );
}

BOOL is_xml_Char( DWORD character_to_test )
{
   // Test according to Rule 2

   static const WFC_RANGE static_char_range[ 6 ] = 
   {
      { 0x0009, 0x0009 }, // 0
      { 0x000A, 0x000A }, // 1
      { 0x000D, 0x000D }, // 2
      { 0x0020, 0xD7FF }, // 3
      { 0xE000, 0xFFFD }, // 4
      { 0x10000, 0x10FFFF } // 5
   };

   return( __wfc_range_check( character_to_test, static_char_range, 6 ) );
}

BOOL is_xml_CombiningChar( DWORD character_to_test )
{
   // Test according to Rule 87

   static const WFC_RANGE static_combiningchar_range[ 96 ] = 
   {
      { 0x0300, 0x0345 }, // 0
      { 0x0360, 0x0361 }, // 1
      { 0x0483, 0x0486 }, // 2
      { 0x0591, 0x05A1 }, // 3
      { 0x05A3, 0x05B9 }, // 4
      { 0x05BB, 0x05BD }, // 5
      { 0x05BF, 0x05BF }, // 6
      { 0x05C1, 0x05C2 }, // 7
      { 0x05C4, 0x05C4 }, // 8
      { 0x064B, 0x0652 }, // 9
      { 0x0670, 0x0670 }, // 10
      { 0x06D6, 0x06DC }, // 11
      { 0x06DD, 0x06DF }, // 12
      { 0x06E0, 0x06E4 }, // 13
      { 0x06E7, 0x06E8 }, // 14
      { 0x06EA, 0x06ED }, // 15
      { 0x0901, 0x0903 }, // 16
      { 0x093C, 0x093C }, // 17
      { 0x093E, 0x094C }, // 18
      { 0x094D, 0x094D }, // 19
      { 0x0951, 0x0954 }, // 20
      { 0x0962, 0x0963 }, // 21
      { 0x0981, 0x0983 }, // 22
      { 0x09BC, 0x09BC }, // 23
      { 0x09BE, 0x09BE }, // 24
      { 0x09BF, 0x09BF }, // 25
      { 0x09C0, 0x09C4 }, // 26
      { 0x09C7, 0x09C8 }, // 27
      { 0x09CB, 0x09CD }, // 28
      { 0x09D7, 0x09D7 }, // 29
      { 0x09E2, 0x09E3 }, // 30
      { 0x0A02, 0x0A02 }, // 31
      { 0x0A3C, 0x0A3C }, // 32
      { 0x0A3E, 0x0A3E }, // 33
      { 0x0A3F, 0x0A3F }, // 34
      { 0x0A40, 0x0A42 }, // 35
      { 0x0A47, 0x0A48 }, // 36
      { 0x0A4B, 0x0A4D }, // 37
      { 0x0A70, 0x0A71 }, // 38
      { 0x0A81, 0x0A83 }, // 39
      { 0x0ABC, 0x0ABC }, // 40
      { 0x0ABE, 0x0AC5 }, // 41
      { 0x0AC7, 0x0AC9 }, // 42
      { 0x0ACB, 0x0ACD }, // 43
      { 0x0B01, 0x0B03 }, // 44
      { 0x0B3C, 0x0B3C }, // 45
      { 0x0B3E, 0x0B43 }, // 46
      { 0x0B47, 0x0B48 }, // 47
      { 0x0B4B, 0x0B4D }, // 48
      { 0x0B56, 0x0B57 }, // 49
      { 0x0B82, 0x0B83 }, // 50
      { 0x0BBE, 0x0BC2 }, // 51
      { 0x0BC6, 0x0BC8 }, // 53
      { 0x0BCA, 0x0BCD }, // 54
      { 0x0BD7, 0x0BD7 }, // 55
      { 0x0C01, 0x0C03 }, // 56
      { 0x0C3E, 0x0C44 }, // 57
      { 0x0C46, 0x0C48 }, // 58
      { 0x0C4A, 0x0C4D }, // 59
      { 0x0C55, 0x0C56 }, // 60
      { 0x0C82, 0x0C83 }, // 61
      { 0x0CBE, 0x0CC4 }, // 62
      { 0x0CC6, 0x0CC8 }, // 63
      { 0x0CCA, 0x0CCD }, // 64
      { 0x0CD5, 0x0CD6 }, // 65
      { 0x0D02, 0x0D03 }, // 66
      { 0x0D3E, 0x0D43 }, // 67
      { 0x0D46, 0x0D48 }, // 68
      { 0x0D4A, 0x0D4D }, // 69
      { 0x0D57, 0x0D57 }, // 70
      { 0x0E31, 0x0E31 }, // 71
      { 0x0E34, 0x0E3A }, // 72
      { 0x0E47, 0x0E4E }, // 73
      { 0x0EB1, 0x0EB1 }, // 74
      { 0x0EB4, 0x0EB9 }, // 75
      { 0x0EBB, 0x0EBC }, // 76
      { 0x0EC8, 0x0ECD }, // 77
      { 0x0F18, 0x0F19 }, // 78
      { 0x0F35, 0x0F35 }, // 79
      { 0x0F37, 0x0F37 }, // 80
      { 0x0F39, 0x0F39 }, // 81
      { 0x0F3E, 0x0F3E }, // 82
      { 0x0F3F, 0x0F3F }, // 83
      { 0x0F71, 0x0F84 }, // 84
      { 0x0F86, 0x0F8B }, // 85
      { 0x0F90, 0x0F95 }, // 86
      { 0x0F97, 0x0F97 }, // 87
      { 0x0F99, 0x0FAD }, // 88
      { 0x0FB1, 0x0FB7 }, // 89
      { 0x0FB9, 0x0FB9 }, // 90
      { 0x20D0, 0x20DC }, // 91
      { 0x20E1, 0x20E1 }, // 92
      { 0x302A, 0x302F }, // 93
      { 0x3099, 0x3099 }, // 94
      { 0x309A, 0x309A }  // 95
   };

   return( __wfc_range_check( character_to_test, static_combiningchar_range, 96 ) );
}

BOOL is_xml_Digit( DWORD character_to_test )
{
   // Test according to Rule 88

   static const WFC_RANGE static_digit_range[ 15 ] = 
   {
      { 0x0030, 0x0039 }, // 0
      { 0x0660, 0x0669 }, // 1
      { 0x06F0, 0x06F9 }, // 2
      { 0x0966, 0x096F }, // 3
      { 0x09E6, 0x09EF }, // 4
      { 0x0A66, 0x0A6F }, // 5
      { 0x0AE6, 0x0AEF }, // 6
      { 0x0B66, 0x0B6F }, // 7
      { 0x0BE7, 0x0BEF }, // 8
      { 0x0C66, 0x0C6F }, // 9
      { 0x0CE6, 0x0CEF }, // 10
      { 0x0D66, 0x0D6F }, // 11
      { 0x0E50, 0x0E59 }, // 12
      { 0x0ED0, 0x0ED9 }, // 13
      { 0x0F20, 0x0F29 }  // 14
   };

   return( __wfc_range_check( character_to_test, static_digit_range, 15 ) );
}

BOOL is_xml_Extender( DWORD character_to_test )
{
   // Test according to Rule 89

   static const WFC_RANGE static_extender_range[ 11 ] = 
   {
      { 0x00B7, 0x00B7 }, // 0
      { 0x02D0, 0x02D0 }, // 1
      { 0x02D1, 0x02D1 }, // 2
      { 0x0387, 0x0387 }, // 3
      { 0x0640, 0x0640 }, // 4
      { 0x0E46, 0x0E46 }, // 5
      { 0x0EC6, 0x0EC6 }, // 6
      { 0x3005, 0x3005 }, // 7
      { 0x3031, 0x3035 }, // 8
      { 0x309D, 0x309E }, // 9
      { 0x30FC, 0x30FE }  // 10
   };

   return( __wfc_range_check( character_to_test, static_extender_range, 11 ) );
}

BOOL is_xml_Ideographic( DWORD character_to_test )
{
   // Test according to Rule 86

   static const WFC_RANGE static_ideographic_range[ 3 ] = 
   {
      { 0x3007, 0x3007 }, // 0
      { 0x3021, 0x3029 }, // 1
      { 0x4E00, 0x9FA5 }  // 2
   };

   return( __wfc_range_check( character_to_test, static_ideographic_range, 3 ) );
}

BOOL is_xml_Letter( DWORD character_to_test )
{
   // Test according to Rule 84

   if ( is_xml_BaseChar( character_to_test ) == TRUE )
   {
      return( TRUE );
   }

   if ( is_xml_Ideographic( character_to_test ) == TRUE )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL is_xml_NameChar( DWORD character_to_test )
{
   // Test according to Rule 4

   if ( is_xml_Letter( character_to_test ) == TRUE )
   {
      return( TRUE );
   }

   if ( is_xml_Digit( character_to_test ) == TRUE )
   {
      return( TRUE );
   }

   if ( character_to_test == '.' ||
        character_to_test == '-' ||
        character_to_test == '_' ||
        character_to_test == ':' )
   {
      return( TRUE );
   }

   if ( is_xml_CombiningChar( character_to_test ) == TRUE )
   {
      return( TRUE );
   }

   if ( is_xml_Extender( character_to_test ) == TRUE )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL is_xml_PubidChar( DWORD character_to_test )
{
   // Test according to Rule 13

   if ( character_to_test >= 'a' && character_to_test <= 'z' )
   {
      return( TRUE );
   }

   if ( character_to_test >= 'A' && character_to_test <= 'Z' )
   {
      return( TRUE );
   }

   if ( character_to_test >= '0' && character_to_test <= '9' )
   {
      return( TRUE );
   }

   if ( character_to_test == 0x0020 ||
        character_to_test == 0x000D ||
        character_to_test == 0x000A )
   {
      return( TRUE );
   }

   if ( character_to_test == '-'  ||
        character_to_test == '\'' ||
        character_to_test == '('  ||
        character_to_test == ')'  ||
        character_to_test == '+'  ||
        character_to_test == ','  ||
        character_to_test == '.'  ||
        character_to_test == '/'  ||
        character_to_test == ':'  ||
        character_to_test == '='  ||
        character_to_test == '?'  ||
        character_to_test == ';'  ||
        character_to_test == '!'  ||
        character_to_test == '*'  ||
        character_to_test == '#'  ||
        character_to_test == '@'  ||
        character_to_test == '$'  ||
        character_to_test == '_'  ||
        character_to_test == '%'  )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL is_xml_white_space( DWORD character_to_test )
{
   // Test according to Rule 3

   if ( character_to_test == 0x0020 ||
        character_to_test == 0x000D ||
        character_to_test == 0x000A ||
        character_to_test == 0x0009 )
   {
      return( TRUE );
   }

   return( FALSE );
}
