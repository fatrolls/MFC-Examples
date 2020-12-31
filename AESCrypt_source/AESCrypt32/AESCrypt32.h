/*
 *  AESCrypt32.h
 *
 *  Copyright (C) 2006, 2008
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved.
 *
 ******************************************************************************
 *  $Id: AESCrypt32.h,v 1.2 2008/09/01 10:41:04 paulej Exp $
 ******************************************************************************
 *
 *  This header file simply defines various values used by the AESCrypt32.cpp
 *  module.
 *
 */

#pragma once

#include "resource.h"

// Externals in the AESCrypt DLL
bool AESLibBusy();
void ProcessFiles(  StringList *file_list,
                    bool encrypt);

