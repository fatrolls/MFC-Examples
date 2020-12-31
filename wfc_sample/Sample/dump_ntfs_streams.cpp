#include <windows.h>
#include <stdio.h>

#pragma hdrstop



#define err doerr( __FILE__, __LINE__ )



void doerr( const char *file, int line )
{
	DWORD e;

	e = GetLastError();
	if ( e == 0 )
		return;

	printf( "%s(%d): gle = %lu\n", file, line, e );
	exit( 2 );
}



void enableprivs()
{
	HANDLE hToken;
	byte buf[sizeof TOKEN_PRIVILEGES * 2];
	TOKEN_PRIVILEGES & tkp = *( (TOKEN_PRIVILEGES *) buf );

	if ( ! OpenProcessToken( GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken ) )
		err;

	// enable SeBackupPrivilege, SeRestorePrivilege

	if ( !LookupPrivilegeValue( NULL, SE_BACKUP_NAME, &tkp.Privileges[0].Luid ) )
		err;

	if ( !LookupPrivilegeValue( NULL, SE_RESTORE_NAME, &tkp.Privileges[1].Luid ) )
		err;

	tkp.PrivilegeCount = 2;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	tkp.Privileges[1].Attributes = SE_PRIVILEGE_ENABLED;

	AdjustTokenPrivileges( hToken, FALSE, &tkp, sizeof tkp,
		NULL, NULL );
}



void dumphdr( WIN32_STREAM_ID & wsi )
{
	const char *p;

	printf( "\nstream [%lu] \"%S\":\n", wsi.dwStreamNameSize,
		wsi.dwStreamNameSize? wsi.cStreamName: L"" );
	switch ( wsi.dwStreamId )
	{
	case BACKUP_DATA:
		p = "data";
		break;
	case BACKUP_EA_DATA:
		p = "extended attributes";
		break;
	case BACKUP_SECURITY_DATA:
		p = "security";
		break;
	case BACKUP_ALTERNATE_DATA:
		p = "other streams";
		break;
	case BACKUP_LINK:
		p = "link";
		break;
	default:
		p = "unknown";
		break;
	}
	printf( "  type: %s\n", p );
	printf( "  size: %I64d\n", wsi.Size.QuadPart );
}



int main( int argc, char *argv[] )
{
	HANDLE fh;

	if ( argc != 2 )
	{
		printf( "usage: dump_ntfs_streams {file}\n" );
		return 1;
	}

	enableprivs();

	fh = CreateFile( argv[1], GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_POSIX_SEMANTICS, NULL );
	if ( fh == INVALID_HANDLE_VALUE || fh == NULL )
		err;

	byte buf[4096];
	DWORD numread, numtoskip;
	void *ctx = NULL;
	WIN32_STREAM_ID & wsi = *( (WIN32_STREAM_ID *) buf );

	numtoskip = 0;
	while ( 1 )
	{
		// we are at the start of a stream header. read it.
		if ( ! BackupRead( fh, buf, 20, &numread, FALSE, TRUE, &ctx ) )
			err;

		if ( numread == 0 )
			break;

		if ( wsi.dwStreamNameSize > 0 )
		{
			if ( ! BackupRead( fh, buf + 20, wsi.dwStreamNameSize, &numread, FALSE, TRUE, &ctx ) )
				err;

			if ( numread != wsi.dwStreamNameSize )
				break;
		}

		dumphdr( wsi );

		// skip stream data
		if ( wsi.Size.QuadPart > 0 )
		{
			DWORD lo, hi;
			BackupSeek( fh, 0xffffffffL, 0x7fffffffL, &lo, &hi, &ctx );
		}
	}

	// make NT release the context
	BackupRead( fh, buf, 0, &numread, TRUE, FALSE, &ctx );

	CloseHandle( fh );

	return 0;
}
