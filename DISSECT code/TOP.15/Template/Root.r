//	$$r_file$$.r: Macintosh-specific resources

#include "types.r"
$$IF(!PROJTYPE_DLL)
#include "ftab.r"
$$ENDIF //!PROJTYPE_DLL
#include "CodeFrag.r"
$$IF(!PROJTYPE_DLL)

resource 'SIZE' (-1)
{
	reserved,
	acceptSuspendResumeEvents,
	reserved,
	canBackground,				
	doesActivateOnFGSwitch,
	backgroundAndForeground,	
	dontGetFrontClicks,			
	ignoreAppDiedEvents,		
	is32BitCompatible,			
	isHighLevelEventAware,
	localAndRemoteHLEvents,
	isStationeryAware,
	useTextEditServices,
	reserved,
	reserved,
	reserved,

// Set different sizes depending on whether we're compiling for
//  PowerMacintosh or 68K

#ifdef _MPPC_

$$IF(CONTAINER || MINI_SERVER || FULL_SERVER || CONTAINER_SERVER || AUTOMATION)
	3000 * 1024,
	3000 * 1024
$$ELSE //(NO OLE)
	2500 * 1024,
	2500 * 1024
$$ENDIF //OLE

#else //!_MPPC_

#ifdef _DEBUG
	3000 * 1024,
	3000 * 1024
#else
	2000 * 1024,
	2000 * 1024
#endif //DEBUG

#endif //_MPPC

};

resource 'BNDL' (128, purgeable)	// $$root$$ bundle resource ID
{
	'$$CREATOR$$',			// $$root$$ signature
	0,						// resource ID of signature resource:
							// should be 0
 	{
		'ICN#',				// mapping local IDs in 'FREF's to 'ICN#' IDs
		{
			0, 128,
			1, 129
		},
		'FREF',				// local resource IDs for 'FREF's
		{
			0, 128,
			1, 129
		}
	}
};

resource 'FREF' (128, purgeable)	// $$root$$ application
{
	'APPL', 0,
	""
};

resource 'FREF' (129, purgeable)	// $$root$$ document
{
	'$$FILE_TYPE$$', 1,
	""
};

type '$$CREATOR$$' as 'STR ';

resource '$$CREATOR$$' (0, purgeable)
{
	"$$root$$ Application"
};
$$ENDIF //PROJTYPE_DLL

#ifdef _MPPC_

resource 'cfrg' (0)
{
	{
		kPowerPC,
		kFullLib,
		kNoVersionNum,
		kNoVersionNum,
		kDefaultStackSize,
		kNoAppSubFolder,
$$IF(PROJTYPE_DLL)
		kIsLib,
$$ELSE //!DLL
		kIsApp,
$$ENDIF //PROJTYPE_DLL
		kOnDiskFlat,
		kZeroOffset,
		kWholeFork,
$$IF(PROJTYPE_DLL)
		"$$ROOT$$"
$$ELSE //!PROJTYPE_DLL
		"$$root$$"
$$ENDIF //PROJTYPE_DLL
	}
};

#endif //_MPPC_
