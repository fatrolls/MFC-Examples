/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1997 by Joerg Koenig and the ADG mbH, Mannheim, Germany
// All rights reserved
//
// Distribute freely, except: don't remove my name from the source or
// documentation (don't take credit for my work), mark your changes (don't
// get me blamed for your possible bugs), don't alter or remove this
// notice.
// No warrantee of any kind, express or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.
//
// Send bug reports, bug fixes, enhancements, requests, flames, etc., and
// I'll try to keep a version up to date.  I can be reached as follows:
//    J.Koenig@adg.de                 (company site)
//    Joerg.Koenig@rhein-neckar.de    (private site)
/////////////////////////////////////////////////////////////////////////////

// last revised $Date: 3.02.98 20:24 $


#ifndef ProcessMgr_h
#define ProcessMgr_h


#ifndef __AFXDISP_H__
	// add `#include <afxdisp.h>´ in your stdafx.h if the following error occurs
	#error "You have to include <afxdisp.h> before you can use this file"
#endif

class AFX_EXT_CLASS CProcessMgr {
	static BOOL		m_bToolHelpOK;		// normally TRUE on Win95 and FALSE on NT

	// members for lexical analysis:
	const CString	m_strSpace;
	const CString *	m_pstrCmd;
	int				m_nIdx;
	int				m_nLen;


	enum LEXER { TOK_CD, TOK_STRING, TOK_CMDSEP, TOK_EOF };


	public:
		CProcessMgr();
		~CProcessMgr();

	public:
			// Parse from a string and extract the directory where
			// the process should run, the command itself and its
			// arguments.
			// <CmdLine> has the following syntax (BNF-like):
			//		CmdLine :	command
			//				|	command arguments
			//				|	'cd' directory ';' command
			//				|	'cd' directory ';' command arguments
			//
			//		command	:	string
			//
			//		arguments:	string
			//				|	arguments string
			//
			//		directory:	string	/* shall consist of a full path ! */
			//
			//		string	:	'[^ \t]+'			/*	string without blanks/tabs */
			//				|	'"' '[^"]*' '"'		/*	quoted string can
			//											contain any character
			//											except " itself
			//										*/
			//
			// For those programmers who are not familiar with BNF-notation
			// here are some samples for valid <CmdLine>s:
			//		cmd
			//		cmd /c dir
			//		cd C:\windows ; cmd /c dir
			//		cd "C:\Program Files\Informix" ; cmd /c dir
			//		cd "C:\Program Files\Pictures" ; "\\picard\Software\Graphic Utilities\PSP\psp.exe" Title.jpg
			// Note that you have to double all occurencies of '\' in C/C++ source code!
			//
			// Note that <command> can refer to any file (not just executables!).
			// See "Execute()" below.
			//
			// ParseCommand() returns TRUE, if <CmdLine> is syntactical
			// correct and FALSE if not. It does not check wether
			// <directory> or <command> are valid!
		BOOL		ParseCommand(
						const CString & CmdLine,
						CString & Directory,
						CString & Cmd,
						CString & Args
					);

			// Start a command with parameters in a specified directory.
			// The second form of this method parses the command-line first,
			// before it tries to execute.
			// You can set the parameter <bWait> to TRUE, if you want to
			// wait for the end of the spawned process, before "Execute()"
			// returns.
			// If the <strCmd> does not refer to an executable file, then
			// "Execute()" searches for an associated command for this
			// type of file.
			// The result of this function is either a PID (bWait==FALSE)
			// or the exit-code of the process (bWait==TRUE).
		DWORD		Execute(
						const CString & strCmd,
						const CString & strArgs,
						const CString & strDir = "",
						BOOL bWait = FALSE
					);
		DWORD		Execute(const CString & strCmdLine, BOOL bWait = FALSE) {
						CString strCmd, strDir, strArgs;
						if( ParseCommand(strCmdLine, strDir, strCmd, strArgs) )
							return Execute(strCmd, strArgs, strDir, bWait);
						return 0;
					}

			// Wait for the end of the process with process-ID <PID>. The result
			// is the exit-code of that process.
		DWORD		Wait( DWORD PID ) const;


			// Determine wether a program is currently running or not.
			// If <FileName> refers to a shell-link, then the link will
			// be resolved and the filename the link points to will be used.
			// Returns the process id (PID) of the program or 0 (null) if the
			// program is currently not running.
			// The second form of "IsProgramRunning()" takes a PID. This
			// function is somewhat insecure on NT, because the process
			// with <PID> must have PROCESS_QUERY_INFORMATION access.
			// If this function cannot determine, wether the process with
			// <PID> is running or not, it returns DWORD(-1).
		DWORD		IsProgramRunning(const CString & FileName) const;
		DWORD		IsProgramRunning(DWORD PID) const;

			// Switch the process with the given PID into the foreground.
			// Returns TRUE on success and FALSE on failure (no such process
			// or process has hidden windows only (possibly a DDE/OLE server))
			// If the top-level window of this process is minimized, then it
			// will be restored.
		BOOL		SwitchProcessIntoForeground(DWORD dwPID) const;
		BOOL		SwitchProcessIntoForeground( const CString & FileName ) const {
						DWORD PID = IsProgramRunning(FileName);
						return (PID > 0)
							? SwitchProcessIntoForeground(PID)
							: FALSE;
					}

			// GetLinkInfo() retrieves the path of the file/object
			// <LinkName> refers to and stores the pathname in <Path>.
			// GetLinkInfo() returns TRUE on success and FALSE on failure
			// (<Path> stays undefined on failure !)
		BOOL		GetLinkInfo(const CString & LinkName, CString & Path) const;
		
			// Compare two filenames and return TRUE if they refer to the
			// same file or FALSE, if not
		BOOL		CompareFilenames(LPCSTR Path1, LPCSTR Path2) const;

	protected:	// overridables
			// The "OnExecError()" handler will be called if "Execute()" fails.
			// The default implementation pops up a messagebox containing a
			// human readable reason (english).
		virtual void	OnExecError( int nErrorCode, const CString & strCommand );

	private:
			// Helper-function for "ParseCommand()" (see above).
			// Extract the next token from a given command-String.
		LEXER		LexCommand(CString & strToken);
		
			// "GetErrorText()" tries to retrieve a messagetext for a
			// system error number. You can use
			//		GetErrorText(GetLastError(), str);
			// for instance.
			// The function returens TRUE on success and FALSE if it could
			// not find an apropriate piece of text.
		BOOL		GetErrorText(int nError, CString & strErrText);

	private:
			// Check out wether we're running on NT or Win95. Use
			// the toolhelp-library on Win95; the registry on NT.
		static BOOL		InitToolhelp32();
};

#endif	// ProcessMgr_h