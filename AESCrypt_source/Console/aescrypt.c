/*
 *  AES Crypt for Windows (console application)
 *  Copyright (C) 2007, 2008, 2009, 2010, 2013
 *
 *  Contributors:
 *      Glenn Washburn <crass@berlios.de>
 *      Paul E. Jones <paulej@packetizer.com>
 *      Mauro Gilardi <galvao.m@gmail.com>
 *
 * This software is licensed as "freeware."  Permission to distribute
 * this software in source and binary forms is hereby granted without a
 * fee.  THIS SOFTWARE IS PROVIDED 'AS IS' AND WITHOUT ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * THE AUTHOR SHALL NOT BE HELD LIABLE FOR ANY DAMAGES RESULTING FROM
 * THE USE OF THIS SOFTWARE, EITHER DIRECTLY OR INDIRECTLY, INCLUDING,
 * BUT NOT LIMITED TO, LOSS OF DATA OR DATA BEING RENDERED INACCURATE.
 *
 */

#define _CRT_SECURE_NO_WARNINGS 1

#include <windows.h>
#include <Wincrypt.h>
#include <io.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <wchar.h>

#include "getopt.h"
#include "aescrypt.h"
#include "password.h"
#include "version.h"

/*
 *  Define externals
 */
extern wchar_t *optarg;
extern int     optopt;
extern int     optind;
extern int     opterr;

/*
 *  encrypt_stream
 *
 *  This function is called to encrypt the open data steam "infp".
 */
int encrypt_stream(FILE *infp, FILE *outfp, wchar_t* passwd, int passlen)
{
    aes_context                 aes_ctx;
    sha256_context              sha_ctx;
    aescrypt_hdr                aeshdr;
    sha256_t                    digest;
    unsigned char               IV[16];
    unsigned char               iv_key[48];
    int                         i, j, n;
    unsigned char               buffer[32];
    unsigned char               ipad[64], opad[64];
    unsigned char               tag_buffer[256];
    HCRYPTPROV                  hProv;
    DWORD                       result_code;

    // Prepare for random number generation
    if (!CryptAcquireContext(   &hProv,
                                NULL,
                                NULL,
                                PROV_RSA_FULL,
                                CRYPT_VERIFYCONTEXT))
    {
        result_code = GetLastError();
        if (GetLastError() == NTE_BAD_KEYSET)
        {
            if (!CryptAcquireContext(   &hProv,
                                        NULL,
                                        NULL,
                                        PROV_RSA_FULL,
                                        CRYPT_NEWKEYSET|CRYPT_VERIFYCONTEXT))
            {
                result_code = GetLastError();
            }
            else
            {
                result_code = ERROR_SUCCESS;
            }
        }

        if (result_code != ERROR_SUCCESS)
        {
            fprintf(stderr, "Could not acquire handle to crypto context");
            return -1;
        }
    }

    // Create the 16-bit IV and 32-bit encryption key
    // used for encrypting the plaintext file.  We do
    // not trust the system's randomization functions, so
    // we improve on that by also hashing the random digits
    // and using only a portion of the hash.  This IV and key
    // generation could be replaced with any good random
    // source of data.
    memset(iv_key, 0, 48);
    for (i=0; i<48; i+=16)
    {
        memset(buffer, 0, 32);
        sha256_starts(&sha_ctx);
        for(j=0; j<256; j++)
        {
            if (!CryptGenRandom(hProv,
                                32,
                                (BYTE *) buffer))
            {
                fprintf(stderr, "Windows is unable to generate random digits");
                return -1;
            }
            sha256_update(&sha_ctx, buffer, 32);
        }
        sha256_finish(&sha_ctx, digest);
        memcpy(iv_key+i, digest, 16);
    }

    // Write an AES signature at the head of the file, along
    // with the AES file format version number.
    buffer[0] = 'A';
    buffer[1] = 'E';
    buffer[2] = 'S';
    buffer[3] = (unsigned char) 0x02;   // Version 2
    buffer[4] = '\0';                   // Reserved for version 0
    if (fwrite(buffer, 1, 5, outfp) != 5)
    {
        fprintf(stderr, "Error: Could not write out header data\n");
        CryptReleaseContext(hProv, 0);
        return  -1;
    }

    // Write out the CREATED-BY tag
    j = 11 +                        // "CREATED-BY\0"
        (int)strlen(PROG_NAME) +    // Program name
        1 +                         // Space
        (int)strlen(PROG_VERSION);  // Program version ID

    // Our extension buffer is only 256 octets long, so
    // let's not write an extension if it is too big
    if (j < 256)
    {
        buffer[0] = '\0';
        buffer[1] = (unsigned char) (j & 0xff);
        if (fwrite(buffer, 1, 2, outfp) != 2)
        {
            fprintf(stderr, "Error: Could not write tag to AES file (1)\n");
            CryptReleaseContext(hProv, 0);
            return  -1;
        }

        strncpy((char *)tag_buffer, "CREATED_BY", 255);
        tag_buffer[255] = '\0';
        if (fwrite(tag_buffer, 1, 11, outfp) != 11)
        {
            fprintf(stderr, "Error: Could not write tag to AES file (2)\n");
            CryptReleaseContext(hProv, 0);
            return  -1;
        }

        sprintf((char *)tag_buffer, "%s %s", PROG_NAME, PROG_VERSION);
        j = (int) strlen((char *)tag_buffer);
        if (fwrite(tag_buffer, 1, j, outfp) != j)
        {
            fprintf(stderr, "Error: Could not write tag to AES file (3)\n");
            CryptReleaseContext(hProv, 0);
            return  -1;
        }
    }

    // Write out the "container" extension
    buffer[0] = '\0';
    buffer[1] = (unsigned char) 128;
    if (fwrite(buffer, 1, 2, outfp) != 2)
    {
        fprintf(stderr, "Error: Could not write tag to AES file (4)\n");
        CryptReleaseContext(hProv, 0);
        return  -1;
    }
    memset(tag_buffer, 0, 128);
    if (fwrite(tag_buffer, 1, 128, outfp) != 128)
    {
        fprintf(stderr, "Error: Could not write tag to AES file (5)\n");
        CryptReleaseContext(hProv, 0);
        return  -1;
    }

    // Write out 0x0000 to indicate that no more extensions exist
    buffer[0] = '\0';
    buffer[1] = '\0';
    if (fwrite(buffer, 1, 2, outfp) != 2)
    {
        fprintf(stderr, "Error: Could not write tag to AES file (6)\n");
        CryptReleaseContext(hProv, 0);
        return  -1;
    }

    // Create a random IV
    sha256_starts(  &sha_ctx);

    for (i=0; i<256; i++)
    {
        if (!CryptGenRandom(hProv,
                            32,
                            (BYTE *) buffer))
        {
            fprintf(stderr, "Windows is unable to generate random digits");
            CryptReleaseContext(hProv, 0);
            return  -1;
        }
        sha256_update(  &sha_ctx,
                        buffer,
                        32);
    }

    sha256_finish(  &sha_ctx, digest);

    memcpy(IV, digest, 16);

    // We're finished collecting random data
    CryptReleaseContext(hProv, 0);

    // Write the initialization vector to the file
    if (fwrite(IV, 1, 16, outfp) != 16)
    {
        fprintf(stderr, "Error: Could not write out initialization vector\n");
        return  -1;
    }
    
    // Hash the IV and password 8192 times
    memset(digest, 0, 32);
    memcpy(digest, IV, 16);
    for(i=0; i<8192; i++)
    {
        sha256_starts(  &sha_ctx);
        sha256_update(  &sha_ctx, digest, 32);
        sha256_update(  &sha_ctx,
                        (unsigned char*)passwd,
                        (unsigned long)(passlen * sizeof(wchar_t)));
        sha256_finish(  &sha_ctx,
                        digest);
    }

    // Set the AES encryption key
    aes_set_key(&aes_ctx, digest, 256);

    // Set the ipad and opad arrays with values as
    // per RFC 2104 (HMAC).  HMAC is defined as
    //   H(K XOR opad, H(K XOR ipad, text))
    memset(ipad, 0x36, 64);
    memset(opad, 0x5C, 64);

    for(i=0; i<32; i++)
    {
        ipad[i] ^= digest[i];
        opad[i] ^= digest[i];
    }

    sha256_starts(&sha_ctx);
    sha256_update(&sha_ctx, ipad, 64);

    // Encrypt the IV and key used to encrypt the plaintext file,
    // writing that encrypted text to the output file.
    for(i=0; i<48; i+=16)
    {
        // Place the next 16 octets of IV and key buffer into
        // the input buffer.
        memcpy(buffer, iv_key+i, 16);

        // XOR plain text block with previous encrypted
        // output (i.e., use CBC)
        for(j=0; j<16; j++)
        {
            buffer[j] ^= IV[j];
        }

        // Encrypt the contents of the buffer
        aes_encrypt(&aes_ctx, buffer, buffer);
        
        // Concatenate the "text" as we compute the HMAC
        sha256_update(&sha_ctx, buffer, 16);

        // Write the encrypted block
        if (fwrite(buffer, 1, 16, outfp) != 16)
        {
            fprintf(stderr, "Error: Could not write iv_key data\n");
            return  -1;
        }
        
        // Update the IV (CBC mode)
        memcpy(IV, buffer, 16);
    }

    // Write the HMAC
    sha256_finish(&sha_ctx, digest);
    sha256_starts(&sha_ctx);
    sha256_update(&sha_ctx, opad, 64);
    sha256_update(&sha_ctx, digest, 32);
    sha256_finish(&sha_ctx, digest);
    // Write the encrypted block
    if (fwrite(digest, 1, 32, outfp) != 32)
    {
        fprintf(stderr, "Error: Could not write iv_key HMAC\n");
        return  -1;
    }

    // Re-load the IV and encryption key with the IV and
    // key to now encrypt the datafile.  Also, reset the HMAC
    // computation.
    memcpy(IV, iv_key, 16);

    // Set the AES encryption key
    aes_set_key(&aes_ctx, iv_key+16, 256);

    // Set the ipad and opad arrays with values as
    // per RFC 2104 (HMAC).  HMAC is defined as
    //   H(K XOR opad, H(K XOR ipad, text))
    memset(ipad, 0x36, 64);
    memset(opad, 0x5C, 64);

    for(i=0; i<32; i++)
    {
        ipad[i] ^= iv_key[i+16];
        opad[i] ^= iv_key[i+16];
    }

    // Wipe the IV and encryption mey from memory
    memset(iv_key, 0, 48);

    sha256_starts(&sha_ctx);
    sha256_update(&sha_ctx, ipad, 64);

    // Initialize the last_block_size value to 0
    aeshdr.last_block_size = 0;

    while ((n = (int)fread(buffer, 1, 16, infp)) > 0)
    {
        // XOR plain text block with previous encrypted
        // output (i.e., use CBC)
        for(i=0; i<16; i++)
        {
            buffer[i] ^= IV[i];
        }

        // Encrypt the contents of the buffer
        aes_encrypt(&aes_ctx, buffer, buffer);
        
        // Concatenate the "text" as we compute the HMAC
        sha256_update(&sha_ctx, buffer, 16);

        // Write the encrypted block
        if (fwrite(buffer, 1, 16, outfp) != 16)
        {
            fprintf(stderr, "Error: Could not write to output file\n");
            return  -1;
        }
        
        // Update the IV (CBC mode)
        memcpy(IV, buffer, 16);

        // Assume this number of octets is the file modulo
        aeshdr.last_block_size = n;
    }

    // Check to see if we had a read error
    if (n < 0)
    {
        fprintf(stderr, "Error: Couldn't read input file\n");
        return  -1;
    }

    // Write the file size modulo
    buffer[0] = (char) (aeshdr.last_block_size & 0x0F);
    if (fwrite(buffer, 1, 1, outfp) != 1)
    {
        fprintf(stderr, "Error: Could not write the file size modulo\n");
        return  -1;
    }

    // Write the HMAC
    sha256_finish(&sha_ctx, digest);
    sha256_starts(&sha_ctx);
    sha256_update(&sha_ctx, opad, 64);
    sha256_update(&sha_ctx, digest, 32);
    sha256_finish(&sha_ctx, digest);
    if (fwrite(digest, 1, 32, outfp) != 32)
    {
        fprintf(stderr, "Error: Could not write the file HMAC\n");
        return  -1;
    }

    return 0;
}

/*
 *  decrypt_stream
 *
 *  This function is called to decrypt the open data steam "infp".
 */
int decrypt_stream(FILE *infp, FILE *outfp, wchar_t* passwd, int passlen)
{
    aes_context                 aes_ctx;
    sha256_context              sha_ctx;
    aescrypt_hdr                aeshdr;
    sha256_t                    digest;
    unsigned char               IV[16];
    unsigned char               iv_key[48];
    int                         i, j, n, bytes_read;
    unsigned char               buffer[64], buffer2[32];
    unsigned char               *head, *tail;
    unsigned char               ipad[64], opad[64];
    int                         reached_eof = 0;
    
    // Read the file header
    if ((bytes_read = (int) fread(&aeshdr, 1, sizeof(aeshdr), infp)) !=
         sizeof(aescrypt_hdr))
    {
        if (feof(infp))
        {
            fprintf(stderr, "Error: Input file is too short.\n");
        }
        else
        {
            perror("Error reading the file header:");
        }
        return  -1;
    }

    if (!(aeshdr.aes[0] == 'A' && aeshdr.aes[1] == 'E' &&
          aeshdr.aes[2] == 'S'))
    {
        fprintf(stderr, "Error: Bad file header (not aescrypt file or is corrupted? [%x, %x, %x])\n", aeshdr.aes[0], aeshdr.aes[1], aeshdr.aes[2]);
        return  -1;
    }

    // Validate the version number and take any version-specific actions
    if (aeshdr.version == 0)
    {
        // Let's just consider the least significant nibble to determine
        // the size of the last block
        aeshdr.last_block_size = (aeshdr.last_block_size & 0x0F);
    }
    else if (aeshdr.version > 0x02)
    {
        fprintf(stderr, "Error: Unsupported AES file version: %d\n",
                aeshdr.version);
        return  -1;
    }

    // Skip over extensions present v2 and later files
    if (aeshdr.version >= 0x02)
    {
        do
        {
            if ((bytes_read = (int) fread(buffer, 1, 2, infp)) != 2)
            {
                if (feof(infp))
                {
                    fprintf(stderr, "Error: Input file is too short.\n");
                }
                else
                {
                    perror("Error reading the file extensions:");
                }
                return  -1;
            }
            // Determine the extension length, zero means no more extensions
            i = j = (((int)buffer[0]) << 8) | (int)buffer[1];
            while (i--)
            {
                if ((bytes_read = (int) fread(buffer, 1, 1, infp)) != 1)
                {
                    if (feof(infp))
                    {
                        fprintf(stderr, "Error: Input file is too short.\n");
                    }
                    else
                    {
                        perror("Error reading the file extensions:");
                    }
                    return  -1;
                }
            }
        } while(j);
    }

    // Read the initialization vector from the file
    if ((bytes_read = (int) fread(IV, 1, 16, infp)) != 16)
    {
        if (feof(infp))
        {
            fprintf(stderr, "Error: Input file is too short.\n");
        }
        else
        {
            perror("Error reading the initialization vector:");
        }
        return  -1;
    }

    // Hash the IV and password 8192 times
    memset(digest, 0, 32);
    memcpy(digest, IV, 16);
    for(i=0; i<8192; i++)
    {
        sha256_starts(  &sha_ctx);
        sha256_update(  &sha_ctx, digest, 32);
        sha256_update(  &sha_ctx,
                        (unsigned char*)passwd,
                        (unsigned long)(passlen * sizeof(wchar_t)));
        sha256_finish(  &sha_ctx,
                        digest);
    }

    // Set the AES encryption key
    aes_set_key(&aes_ctx, digest, 256);

    // Set the ipad and opad arrays with values as
    // per RFC 2104 (HMAC).  HMAC is defined as
    //   H(K XOR opad, H(K XOR ipad, text))
    memset(ipad, 0x36, 64);
    memset(opad, 0x5C, 64);

    for(i=0; i<32; i++)
    {
        ipad[i] ^= digest[i];
        opad[i] ^= digest[i];
    }

    sha256_starts(&sha_ctx);
    sha256_update(&sha_ctx, ipad, 64);

    // If this is a version 1 or later file, then read the IV and key
    // for decrypting the bulk of the file.
    if (aeshdr.version >= 0x01)
    {
        for(i=0; i<48; i+=16)
        {
            if ((bytes_read = (int) fread(buffer, 1, 16, infp)) != 16)
            {
                if (feof(infp))
                {
                    fprintf(stderr, "Error: Input file is too short.\n");
                }
                else
                {
                    perror("Error reading input file IV and key:");
                }
                return  -1;
            }

            memcpy(buffer2, buffer, 16);

            sha256_update(&sha_ctx, buffer, 16);
            aes_decrypt(&aes_ctx, buffer, buffer);

            // XOR plain text block with previous encrypted
            // output (i.e., use CBC)
            for(j=0; j<16; j++)
            {
                iv_key[i+j] = (buffer[j] ^ IV[j]);
            }

            // Update the IV (CBC mode)
            memcpy(IV, buffer2, 16);
        }

        // Verify that the HMAC is correct
        sha256_finish(&sha_ctx, digest);
        sha256_starts(&sha_ctx);
        sha256_update(&sha_ctx, opad, 64);
        sha256_update(&sha_ctx, digest, 32);
        sha256_finish(&sha_ctx, digest);

        if ((bytes_read = (int) fread(buffer, 1, 32, infp)) != 32)
        {
            if (feof(infp))
            {
                fprintf(stderr, "Error: Input file is too short.\n");
            }
            else
            {
                perror("Error reading input file digest:");
            }
            return  -1;
        }

        if (memcmp(digest, buffer, 32))
        {
            fprintf(stderr, "Error: Message has been altered or password is incorrect\n");
            return  -1;
        }

        // Re-load the IV and encryption key with the IV and
        // key to now encrypt the datafile.  Also, reset the HMAC
        // computation.
        memcpy(IV, iv_key, 16);

        // Set the AES encryption key
        aes_set_key(&aes_ctx, iv_key+16, 256);

        // Set the ipad and opad arrays with values as
        // per RFC 2104 (HMAC).  HMAC is defined as
        //   H(K XOR opad, H(K XOR ipad, text))
        memset(ipad, 0x36, 64);
        memset(opad, 0x5C, 64);

        for(i=0; i<32; i++)
        {
            ipad[i] ^= iv_key[i+16];
            opad[i] ^= iv_key[i+16];
        }

        // Wipe the IV and encryption mey from memory
        memset(iv_key, 0, 48);

        sha256_starts(&sha_ctx);
        sha256_update(&sha_ctx, ipad, 64);
    }
    
    // Decrypt the balance of the file

    // Attempt to initialize the ring buffer with contents from the file.
    // Attempt to read 48 octets of the file into the ring buffer.
    if ((bytes_read = (int) fread(buffer, 1, 48, infp)) < 48)
    {
        if (!feof(infp))
        {
            perror("Error reading input file ring:");
            return  -1;
        }
        else
        {
            // If there are less than 48 octets, the only valid count
            // is 32 for version 0 (HMAC) and 33 for version 1 or
            // greater files ( file size modulo + HMAC)
            if ((aeshdr.version == 0x00 && bytes_read != 32) ||
                (aeshdr.version >= 0x01 && bytes_read != 33))
            {
                fprintf(stderr, "Error: Input file is corrupt (1:%d).\n",
                        bytes_read);
                return -1;
            }
            else
            {
                // Version 0 files would have the last block size
                // read as part of the header, so let's grab that
                // value now for version 1 files.
                if (aeshdr.version >= 0x01)
                {
                    // The first octet must be the indicator of the
                    // last block size.
                    aeshdr.last_block_size = (buffer[0] & 0x0F);
                }
                // If this initial read indicates there is no encrypted
                // data, then there should be 0 in the last_block_size field
                if (aeshdr.last_block_size != 0)
                {
                    fprintf(stderr, "Error: Input file is corrupt (2).\n");
                    return -1;
                }
            }
            reached_eof = 1;
        }
    }
    head = buffer + 48;
    tail = buffer;

    while(!reached_eof)
    {
        // Check to see if the head of the buffer is past the ring buffer
        if (head == (buffer + 64))
        {
            head = buffer;
        }

        if ((bytes_read = (int) fread(head, 1, 16, infp)) < 16)
        {
            if (!feof(infp))
            {
                perror("Error reading input file:");
                return  -1;
            }
            else
            {
                // The last block for v0 must be 16 and for v1 it must be 1
                if ((aeshdr.version == 0x00 && bytes_read > 0) ||
                    (aeshdr.version >= 0x01 && bytes_read != 1))
                {
                    fprintf(stderr, "Error: Input file is corrupt (3:%d).\n",
                            bytes_read);
                    return -1;
                }

                // If this is a v1 file, then the file modulo is located
                // in the ring buffer at tail + 16 (with consideration
                // given to wrapping around the ring, in which case
                // it would be at buffer[0])
                if (aeshdr.version >= 0x01)
                {
                    if ((tail + 16) < (buffer + 64))
                    {
                        aeshdr.last_block_size = (tail[16] & 0x0F);
                    }
                    else
                    {
                        aeshdr.last_block_size = (buffer[0] & 0x0F);
                    }
                }

                // Indicate that we've reached the end of the file
                reached_eof = 1;
            }
        }

        // Process data that has been read.  Note that if the last
        // read operation returned no additional data, there is still
        // one one ciphertext block for us to process if this is a v0 file.
        if ((bytes_read > 0) || (aeshdr.version == 0x00))
        {
            // Advance the head of the buffer forward
            if (bytes_read > 0)
            {
                head += 16;
            }

            memcpy(buffer2, tail, 16);

            sha256_update(&sha_ctx, tail, 16);
            aes_decrypt(&aes_ctx, tail, tail);

            // XOR plain text block with previous encrypted
            // output (i.e., use CBC)
            for(i=0; i<16; i++)
            {
                tail[i] ^= IV[i];
            }

            // Update the IV (CBC mode)
            memcpy(IV, buffer2, 16);

            // If this is the final block, then we may
            // write less than 16 octets
            n = ((!reached_eof) ||
                 (aeshdr.last_block_size == 0)) ? 16 : aeshdr.last_block_size;

            // Write the decrypted block
            if ((i = (int) fwrite(tail, 1, n, outfp)) != n)
            {
                perror("Error writing decrypted block:");
                return  -1;
            }
            
            // Move the tail of the ring buffer forward
            tail += 16;
            if (tail == (buffer+64))
            {
                tail = buffer;
            }
        }
    }

    // Verify that the HMAC is correct
    sha256_finish(&sha_ctx, digest);
    sha256_starts(&sha_ctx);
    sha256_update(&sha_ctx, opad, 64);
    sha256_update(&sha_ctx, digest, 32);
    sha256_finish(&sha_ctx, digest);

    // Copy the HMAC read from the file into buffer2
    if (aeshdr.version == 0x00)
    {
        memcpy(buffer2, tail, 16);
        tail += 16;
        if (tail == (buffer + 64))
        {
            tail = buffer;
        }
        memcpy(buffer2+16, tail, 16);
    }
    else
    {
        memcpy(buffer2, tail+1, 15);
        tail += 16;
        if (tail == (buffer + 64))
        {
            tail = buffer;
        }
        memcpy(buffer2+15, tail, 16);
        tail += 16;
        if (tail == (buffer + 64))
        {
            tail = buffer;
        }
        memcpy(buffer2+31, tail, 1);
    }

    if (memcmp(digest, buffer2, 32))
    {
        if (aeshdr.version == 0x00)
        {
            fprintf(stderr, "Error: Message has been altered or password is incorrect\n");
        }
        else
        {
            fprintf(stderr, "Error: Message has been altered and should not be trusted\n");
        }

        return -1;
    }

    return 0;
}

/*
 *  usage
 *
 *  Displays the program usage to the user.
 */
void usage(const wchar_t *progname)
{
    const wchar_t* progname_real; //contains the real name of the program (without path)

    progname_real = progname;
    while(*progname_real)
    {
        progname_real++;
    }
    while(progname_real > progname)
    {
        if ((*progname_real == L'\\') || (*progname_real == L'/'))
        {
            progname_real++;
            break;
        }
        progname_real--;
    }
    if (*progname_real == L'\0')
    {
        progname_real = LPROG_NAME;
    }
progname_real = progname;

    fwprintf(stderr, L"\nusage: %s {-e|-d} [-p <password>] { [-o <output filename>] <file> | <file> [<file> ...] }\n\n",
             progname_real);
}

/*
 *  version
 *
 *  Displays the program version to the user.
 */
void version(const wchar_t *progname)
{
    const wchar_t* progname_real; //contains the real name of the program (without path)

    progname_real = progname;
    while(*progname_real)
    {
        progname_real++;
    }
    while(progname_real > progname)
    {
        if ((*progname_real == L'\\') || (*progname_real == L'/'))
        {
            progname_real++;
            break;
        }
        progname_real--;
    }
    if (*progname_real == L'\0')
    {
        progname_real = LPROG_NAME;
    }

    fwprintf(   stderr, L"\n%s version %s (%s)\n\n",
                progname_real, LPROG_VERSION, LPROG_DATE);
}

/*
 *  cleanup
 *
 *  Removes output files that are not fully and properly created.
 */
void cleanup(const wchar_t *outfile)
{
    if (wcscmp(outfile,L"-") && outfile[0] != '\0')
    {
        _wunlink(outfile);
    }
}

int wmain(int argc, wchar_t* argv[])
{
    int rc=0, passlen=0;
    FILE *infp = NULL;
    FILE *outfp = NULL;
    encryptmode_t mode=UNINIT;
    wchar_t *infile = NULL,
            pass[MAX_PASSWD_LEN+1];
    int file_count = 0;
    wchar_t outfile[1024];

    // Initialize the output filename
    outfile[0] = '\0';
    
    while ((rc = getopt(argc, argv, L"vhdep:o:")) != -1)
    {
        switch (rc)
        {
            case 'h':
                usage(argv[0]);
                return 0;
            case 'v':
                version(argv[0]);
                return 0;
            case 'd':
                if (mode != UNINIT)
                {
                    fprintf(stderr, "Error: only specify one of -d or -e\n");
                    cleanup(outfile);
                    return -1;
                }
                mode = DEC;
                break;
            case 'e':
                if (mode != UNINIT)
                {
                    fprintf(stderr, "Error: only specify one of -d or -e\n");
                    cleanup(outfile);
                    return -1;
                }
                mode = ENC;
                break;
            case 'p':
                if (optarg != 0)
                {
                    wcscpy(pass, optarg);
                    passlen = (int) wcslen(pass);
                    if (passlen < 0)
                    {
                        cleanup(outfile);
                        return -1;
                    }
                }
                break;
            case 'o':
                // outfile argument
                if (!wcsncmp(L"-", optarg, 2))
                {
                    // if '-' is outfile name then out to stdout
                    outfp = stdout;
                    _setmode(_fileno(stdout), _O_BINARY);
                }
                else if ((outfp = _wfopen(optarg, L"wb")) == NULL)
                {
                    fwprintf(stderr, L"Error opening output file %s:", optarg);
                    perror("");
                    cleanup(outfile);
                    return  -1;
                }
                wcsncpy(outfile, optarg, 1024);
                outfile[1023] = '\0';
                break;
            default:
                fwprintf(stderr, L"Error: Unknown option '%c'\n", rc);
        }
    }
    
    if (optind >= argc)
    {
        fprintf(stderr, "Error: No file argument specified\n");
        usage(argv[0]);
        cleanup(outfile);
        return -1;
    }

    if (mode == UNINIT)
    {
        fprintf(stderr, "Error: -e or -d not specified\n");
        usage(argv[0]);
        cleanup(outfile);
        return -1;
    }

    // Prompt for password if not provided on the command line
    if (passlen == 0)
    {
        passlen = read_password(pass, mode);

        switch (passlen)
        {
            case 0: //no password in input
                fprintf(stderr, "Error: No password supplied.\n");
                cleanup(outfile);
                return -1;
            case AESCRYPT_READPWD_GETWCHAR:
            case AESCRYPT_READPWD_TOOLONG:
                fwprintf(stderr, L"Error in read_password: %s.\n",
                        read_password_error(passlen));
                cleanup(outfile);
                return -1;
            case AESCRYPT_READPWD_NOMATCH:
                fprintf(stderr, "Error: Passwords don't match.\n");
                cleanup(outfile);
                return -1;
        }

        if (passlen < 0)
        {
            cleanup(outfile);
            // For security reasons, erase the password
            wmemset(pass, 0, passlen);
            return -1;
        }
    }

    file_count = argc - optind;
    if ((file_count > 1) && (outfp != NULL))
    {
        if (outfp != stdout)
        {
            fclose(outfp);
        }
        fprintf(stderr, "Error: A single output file may not be specified with multiple input files.\n");
        usage(argv[0]);
        cleanup(outfile);
        // For security reasons, erase the password
        wmemset(pass, 0, passlen);
        return -1;
    }

    while (optind < argc)
    {
        infile = argv[optind++];

        if(!wcsncmp(L"-", infile, 2))
        {
            if (file_count > 1)
            {
                if ((outfp != stdout) && (outfp != NULL))
                {
                    fclose(outfp);
                }
                fprintf(stderr, "Error: STDIN may not be specified with multiple input files.\n");
                usage(argv[0]);
                cleanup(outfile);
                // For security reasons, erase the password
                wmemset(pass, 0, passlen);
                return -1;
            }
            infp = stdin;
            _setmode(_fileno(stdin), _O_BINARY);
            if (outfp == NULL)
            {
                outfp = stdout;
                _setmode(_fileno(stdout), _O_BINARY);
            }
        }
        else if ((infp = _wfopen(infile, L"rb")) == NULL)
        {
            if ((outfp != stdout) && (outfp != NULL))
            {
                fclose(outfp);
            }
            fwprintf(stderr, L"Error opening input file %s : ", infile);
            perror("");
            cleanup(outfile);
            // For security reasons, erase the password
            wmemset(pass, 0, passlen);
            return  -1;
        }
        
        if (mode == ENC)
        {
            if (outfp == NULL)
            {
                _snwprintf(outfile, 1024, L"%s.aes", infile);
                if ((outfp = _wfopen(outfile, L"wb")) == NULL)
                {
                    if ((infp != stdin) && (infp != NULL))
                    {
                        fclose(infp);
                    }
                    fwprintf(stderr, L"Error opening output file %s : ", outfile);
                    perror("");
                    cleanup(outfile);
                    // For security reasons, erase the password
                    wmemset(pass, 0, passlen);
                    return  -1;
                }
            }
            
            rc = encrypt_stream(infp, outfp, pass, passlen);
        }
        else if (mode == DEC)
        {
            if (outfp == NULL)
            {
                // assume .aes extension
                wcsncpy(outfile, infile, wcslen(infile)-4);
                outfile[wcslen(infile)-4] = '\0';
                if ((outfp = _wfopen(outfile, L"wb")) == NULL)
                {
                    if ((infp != stdin) && (infp != NULL))
                    {
                        fclose(infp);
                    }
                    fwprintf(stderr, L"Error opening output file %s : ", outfile);
                    perror("");
                    cleanup(outfile);
                    // For security reasons, erase the password
                    wmemset(pass, 0, passlen);
                    return  -1;
                }
            }
            
            // should probably test against ascii, utf-16le, and utf-16be encodings
            rc = decrypt_stream(infp, outfp, pass, passlen);
        }
        
        if ((infp != stdin) && (infp != NULL))
        {
            fclose(infp);
        }
        if ((outfp != stdout) && (outfp != NULL))
        {
            fclose(outfp);
        }

        // If there was an error, remove the output file
        if (rc)
        {
            cleanup(outfile);
            // For security reasons, erase the password
            wmemset(pass, 0, passlen);
            return -1;
        }

        // Reset input/output file names and desriptors
        outfile[0] = '\0';
        infp = NULL;
        outfp = NULL;
    }

    // For security reasons, erase the password
    wmemset(pass, 0, passlen);
    
    return rc;
}

