/*
 * Copyright Bruce Liang (ldcsaa@gmail.com)
 *
 * Version	: 2.3.2
 * Author	: Bruce Liang
 * Website	: http://www.jessma.org
 * Porject	: https://code.google.com/p/ldcsaa
 * Bolg		: http://www.cnblogs.com/ldcsaa
 * WeiBo	: http://weibo.com/u/1402935851
 * QQ Group	: 75375912
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
/******************************************************************************

Module:  VarConv.h
Notices: Copyright (c) 2006 Bruce Liang
Purpose: 定义 Variant 到普通数据类型的转换函数.
Desc:
			1. 通常用于数据库访问或其他与 COM 有关的操作

Usage:

Rule:	

Example:	(见: TestDBAccessor 测试程序用中的数据库访问操作)
											
******************************************************************************/

/*########################################################################
			  ------------------------------------------------
							 Variant 数值类型转换
			  ------------------------------------------------
  ########################################################################*/

#pragma once

#include <comdef.h>
#include <comutil.h>

#define TYPE_CAST_ERROR		MAKE_HRESULT(1, 0xFF, 0xFF)

// 获取 _com_error 描述
CString GetComErrorDesc(_com_error e);

// Variant 数值类型转换
double			vartof		(const _variant_t& var);
BYTE			vartoi1		(const _variant_t& var);
short			vartoi2		(const _variant_t& var);
long			vartoi4		(const _variant_t& var);
COleCurrency	vartocy		(const _variant_t& var);
CString			vartostr	(const _variant_t& var);
bool			vartobool	(const _variant_t& var);
COleDateTime	vartodate	(const _variant_t& var);
