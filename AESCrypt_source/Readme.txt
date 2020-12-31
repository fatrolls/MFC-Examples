AESCrypt File Format Description

Items in quotes are a literal string.  Words outside of quotes
are a textual description of the contents.  Fixed-valued octets are
written in hexidecimal form (e.g., 0x01).

The AESCrypt version 2 file format is as follows.
      3 Octets - 'AES'
      1 Octet  - 0x02 (Version)
      1 Octet  - Reserved
     .... Start of repeating extension block section
      2 Octet  - Length in octets (in network byte order) of an extension
                 identifier and contents.  If 0x0000, then no further
                 extensions exist and the next octet is the start of the
                 Initialization Vector (IV).  Following an extension,
                 this length indicator would appear again to indicate
                 presence or absense of another extension and the size of
                 any such extension.
     nn Octets - Extension identifier.  This is either a URI or an
                 identifier defined by the AES developer community and
                 documented on the standard extensions page, either
                 of which is terminated by a single 0x00 octet.  All
                 extension identifiers are case sensitive.
                   Examples of URIs:
                      http://www.aescrypt.com/extensions/creator/
                      urn:oid:1.3.6.1.4.1.17090.55.14
                      urn:uuid:85519EA3-1DA6-45b9-9041-8CD368D8C086
                   Note:
                      A URI was used to allow anybody to define extension
                      types, though we should strive to define a standard
                      set of extensions.
                   Examples of standard extension identifiers:
                      CREATED-DATE
                      CREATED-BY
                 A special extension is defined that has no name, but is
                 merely a "container" for extensions to be added after the
                 AES file is initially created.  Such an extension avoids
                 the need to read and re-write the entire file in order to
                 add a small extension.  Software tools that create AES
                 files should insert a 128-octet "container" extension,
                 placing a 0x00 in the first octet of the extension
                 identifier field.  Developers may then insert extensions
                 into this "container" area and reduce the size of this
                 "container" as necessary.  If larger extensions are added
                 or the "container" area is filled entirely, then reading
                 and re-writing the entire file would be necessary to add
                 additional extensions.
     nn Octets - The contents of the extension
     .... End of repeating extension block section
     16 Octets - Initialization Vector (IV) used for encrypting the
                 IV and symmetric key that is actually used to encrypt
                 the bulk of the plaintext file.
     48 Octets - Encrypted IV and 256-bit AES key used to encrypt the
                 bulk of the file
                 16 octets - Initialization Vector
                 32 octets - encryption key
     32 Octets - HMAC
     nn Octets - Encrypted message (2^64 octets max)
      1 Octet  - File size modulo 16 in least significant bit positions
     32 Octets - HMAC

     Thus, the footprint of the file is at least 136 octets.

The AESCrypt version 1 file format is as follows.
      3 Octets - 'AES'
      1 Octet  - 0x01 (Version)
      1 Octet  - Reserved
     16 Octets - Initialization Vector (IV) used for encrypting the
                 IV and symmetric key that is actually used to encrypt
                 the bulk of the plaintext file.
     48 Octets - Encrypted IV and 256-bit AES key used to encrypt the
                 bulk of the file
                 16 octets - Initialization Vector
                 32 octets - encryption key
     32 Octets - HMAC
     nn Octets - Encrypted message (2^64 octets max)
      1 Octet  - File size modulo 16 in least significant bit positions
     32 Octets - HMAC

     Thus, the footprint of the file is at least 134 octets.

The AESCrypt version 0 file format is as follows.
      3 Octets - 'AES'
      1 Octet  - 0x00 (Version)
      1 Octet  - File size modulo 16 in least significant bit positions
     16 Octets - Initialization Vector (IV)
     nn Octets - Encrypted message (2^64 octets max)
     32 Octets - HMAC

     Thus, the footprint of the file is at least 53 octets.

