// guids.h -- WMI Guids for pnpevent driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#ifndef GUIDS_H
#define GUIDS_H

// {6A061783-E697-11D2-81B5-00C04FA330A6}
DEFINE_GUID(GUID_INTERFACE_PNPEVENT, 0x6a061783L, 0xe697, 0x11d2, 0x81, 0xb5, 0x00, 0xc0, 0x4f, 0xa3, 0x30, 0xa6);

// The following GUID is used for the custom event reported by IOCTL_GENERATE_EVENT:

// {28CE01A1-9436-11d2-81B5-00C04FA330A6}
DEFINE_GUID(GUID_PNPEVENT_EVENT, 0x28ce01a1, 0x9436, 0x11d2, 0x81, 0xb5, 0x0, 0xc0, 0x4f, 0xa3, 0x30, 0xa6);

#endif
