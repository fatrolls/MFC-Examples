// Base64.cpp
/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 1996-1997, Chris Sells
// All rights reserved.
//
// NO WARRANTIES ARE EXTENDED. USE AT YOUR OWN RISK.
//
// To contact the author with suggestions or comments, use
// csells@sellsbrothers.com

#include "stdafx.h"
#include "Base64.h"

#define BAD_POINTER_RETURN(p) if( !p ) return E_POINTER
#define BAD_POINTER_RETURN_OR_ZERO(p) if( !p ) return E_POINTER; else *p = 0
#define DIM(rg) (sizeof(rg)/sizeof(*rg))

// Map 6-bit byte to 8-bit character
static const char
g_szMap64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// Map 8-bit character to 6-bit byte
#define INVALID_BYTE64  255
#define OFFSET_BYTE64   '+'
static const byte
g_byteMap64[] =
{
    62, // +
    INVALID_BYTE64,
    INVALID_BYTE64,
    INVALID_BYTE64,
    63, // /
    52, // 0
    53, // 1
    54, // 2
    55, // 3
    56, // 4
    57, // 5
    58, // 6
    59, // 7
    60, // 8
    61, // 9
    INVALID_BYTE64,
    INVALID_BYTE64,
    INVALID_BYTE64,
    INVALID_BYTE64,
    INVALID_BYTE64,
    INVALID_BYTE64,
    INVALID_BYTE64,
    0,  // A
    1,  // B
    2,  // C
    3,  // D
    4,  // E
    5,  // F
    6,  // G
    7,  // H
    8,  // I
    9,  // J
    10, // K
    11, // L
    12, // M
    13, // N
    14, // O
    15, // P
    16, // Q
    17, // R
    18, // S
    19, // T
    20, // U
    21, // V
    22, // W
    23, // X
    24, // Y
    25, // Z
    INVALID_BYTE64,
    INVALID_BYTE64,
    INVALID_BYTE64,
    INVALID_BYTE64,
    INVALID_BYTE64,
    INVALID_BYTE64,
    26, // a
    27, // b
    28, // c
    29, // d
    30, // e
    31, // f
    32, // g
    33, // h
    34, // i
    35, // j
    36, // k
    37, // l
    38, // m
    39, // n
    40, // o
    41, // p
    42, // q
    43, // r
    44, // s
    45, // t
    46, // u
    47, // v
    48, // w
    49, // x
    50, // y
    51, // z
};

// Turn up to three bytes into four characters in the range [A-Za-z0-9+/],
// using = as the padding character.
HRESULT Encode64(
    char*       rgc,   // Encoded characters
    const BYTE* rgb,   // Array of bytes to encode
    size_t      cb)    // Number of bytes to encode (1, 2 or 3)
{
    BAD_POINTER_RETURN(rgc);
    BAD_POINTER_RETURN(rgb);

    HRESULT hr = S_OK;

    // Break out three 8-bit bytes into four characters using 6-bit bytes,
    // padding with the = character should less than 3 bytes be encoded.
    switch( cb )
    {
    case 3:
        rgc[0] = g_szMap64[((rgb[0] >> 2))];
        rgc[1] = g_szMap64[((rgb[0] & 0x03) << 4) | (rgb[1] >> 4)];
        rgc[2] = g_szMap64[((rgb[1] & 0x0f) << 2) | (rgb[2] >> 6)];
        rgc[3] = g_szMap64[((rgb[2] & 0x3f))];
    break;

    case 2:
        rgc[0] = g_szMap64[((rgb[0] >> 2))];
        rgc[1] = g_szMap64[((rgb[0] & 0x03) << 4) | (rgb[1] >> 4)];
        rgc[2] = g_szMap64[((rgb[1] & 0x0f) << 2)];
        rgc[3] = '=';
    break;

    case 1:
        rgc[0] = g_szMap64[((rgb[0] >> 2))];
        rgc[1] = g_szMap64[((rgb[0] & 0x03) << 4)];
        rgc[2] = '=';
        rgc[3] = '=';
    break;

    default:
        hr = E_INVALIDARG;
    break;
    }

    return hr;
}


// Turn four characters in the range [A-Za-z0-9+/] into n bytes,
// stopping when the = padding character is reached.
HRESULT Decode64(
    BYTE*          rgb,    // Decoded bytes
    size_t*        pcb,    // Number of decoded bytes (1, 2 or 3)
    const char*    rgc)    // Array of 4 characters to decode
{
    BAD_POINTER_RETURN_OR_ZERO(pcb);
    BAD_POINTER_RETURN(rgb);
    BAD_POINTER_RETURN(rgc);

    // Translate four characters into four 6-bit bytes
    BYTE    rgbTmp[4];
    size_t  cch = 0;    // Count of characters to decode (stop at padding)
    HRESULT hr = S_OK;

    for( int i = 0; SUCCEEDED(hr) && rgc[i] != '=' && i < 4; i++ )
    {
        size_t  n = rgc[i] - OFFSET_BYTE64;
        if( n >= DIM(g_byteMap64) ||
            ((rgbTmp[i] = g_byteMap64[n]) == INVALID_BYTE64) )
        {
            hr = E_UNEXPECTED;
        }

        cch++;
    }

    if( SUCCEEDED(hr) )
    {
        // Translate 6-bit bytes into 8-bit bytes
        switch( cch )
        {
        case 4:
            rgb[0] = (rgbTmp[0] << 2) | (rgbTmp[1] >> 4);
            rgb[1] = (rgbTmp[1] << 4) | (rgbTmp[2] >> 2);
            rgb[2] = (rgbTmp[2] << 6) | (rgbTmp[3] >> 0);
            *pcb = 3;
        break;

        case 3:
            rgb[0] = (rgbTmp[0] << 2) | (rgbTmp[1] >> 4);
            rgb[1] = (rgbTmp[1] << 4) | (rgbTmp[2] >> 2);
            *pcb = 2;
        break;

        case 2:
            rgb[0] = (rgbTmp[0] << 2) | (rgbTmp[1] >> 4);
            *pcb = 1;
        break;

        default:
            hr = E_UNEXPECTED;
        break;
        }
    }

    return hr;
}


// Base64 encode a buffer of bytes where cch >= (cb/3) * 4.
HRESULT BufferEncode64(
    char*        rgc,    // Encoded array of characters
    size_t       cch,    // Size of encoding array
    const BYTE*  rgb,    // Array of bytes to encode
    size_t       cb)     // Number of bytes to encode
{
    BAD_POINTER_RETURN(rgc);
    BAD_POINTER_RETURN(rgb);

#ifdef _DEBUG
    if( cch%4 != 0 ) return E_UNEXPECTED;
    if( cch < (cb/3 * 4) ) return E_UNEXPECTED;
#endif

    HRESULT hr = S_OK;
    size_t  nRaw;
    size_t  nEncoded;

    for( nRaw = 0, nEncoded = 0;
         SUCCEEDED(hr) && (nRaw + 2) < cb;
         nRaw += 3, nEncoded += 4)
    {
        hr = Encode64(rgc + nEncoded, rgb + nRaw, 3);
    }

    // Catch the last 1 or 2 bytes
    if( SUCCEEDED(hr) )
    {
        if( cb - nRaw )
        {
            hr = Encode64(rgc + nEncoded, rgb + nRaw, cb - nRaw);
        }
    }

    return hr;
}


// Base64 decode a buffer of characters where *pcb >= (cch/4) * 3.
// NOTE: On input, *pcb is assumed to be the maximum size of rgb.
HRESULT BufferDecode64(
    BYTE*        rgb,    // Decoded array of bytes
    size_t*      pcb,    // Number of decoded bytes
    const char*  rgc,    // Array of characters to decode
    size_t       cch)    // Number of characters to decode
{
    BAD_POINTER_RETURN(pcb);
    BAD_POINTER_RETURN(rgb);
    BAD_POINTER_RETURN(rgc);

#ifdef _DEBUG
    if( *pcb < (cch/4 * 3) - 2 ) return E_UNEXPECTED;
#endif

    HRESULT hr = S_OK;
    size_t  nRaw;
    size_t  nEncoded;

    *pcb = 0;
    for( nRaw = 0, nEncoded = 0;
         SUCCEEDED(hr) && nEncoded < cch;
         nRaw += 3, nEncoded += 4)
    {
        size_t  cb;
        hr = Decode64(rgb + nRaw, &cb, rgc + nEncoded);
        *pcb += cb;
        if( cb < 3 )
        {
            break;
        }
    }

    return hr;
}
