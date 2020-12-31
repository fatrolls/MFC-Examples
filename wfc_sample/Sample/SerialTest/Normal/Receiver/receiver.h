#if ! defined( RECEIVER_HEADER_FILE )

#define RECEIVER_HEADER_FILE

#include <wfc.h>

DWORD compute_checksum( const DWORD * buffer, DWORD number_of_entries );

#endif // RECEIVER_HEADER_FILE
