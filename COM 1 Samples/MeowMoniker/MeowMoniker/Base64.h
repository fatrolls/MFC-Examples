// Base64.h

#ifndef __BASE64_H__
#define __BASE64_H__

// Turn up to three bytes into four characters in the range [A-Za-z0-9+/],
// using = as the padding character.
HRESULT Encode64(char*       rgc,   // Array of 4 encoded characters
                 const BYTE* rgb,   // Array of bytes to encode
                 size_t      cb);   // Number of bytes to encode (1, 2 or 3)

// Turn four characters in the range [A-Za-z0-9+/] into n bytes,
// stopping when the = padding character is reached.
HRESULT Decode64(BYTE*          rgb,    // Decoded bytes
                 size_t*        pcb,    // Number of decoded bytes (1, 2 or 3)
                 const char*    rgc);   // Array of 4 characters to decode

// Base64 encode a buffer of bytes where cch >= (cb/3) * 4.
HRESULT BufferEncode64(char*        rgc,    // Array of encoded characters
                       size_t       cch,    // Number of encoded characters
                       const BYTE*  rgb,    // Array of bytes to encode
                       size_t       cb);    // Number of bytes to encode

// Base64 decode a buffer of characters where *pcb >= (cch/4) * 3.
// NOTE: On input, *pcb is assumed to be the maximum size of rgb.
HRESULT BufferDecode64(BYTE*        rgb,    // Array of decoded bytes
                       size_t*      pcb,    // Number of decoded bytes
                       const char*  rgc,    // Array of characters to decode
                       size_t       cch);   // Number of characters to decode

#endif  // __BASE64_H__
