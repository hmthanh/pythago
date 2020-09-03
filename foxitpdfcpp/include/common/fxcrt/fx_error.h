/**
 * Copyright (C) 2003-2020, Foxit Software Inc..
 * All Rights Reserved.
 *
 * http://www.foxitsoftware.com
 *
 * The following code is copyrighted and is the proprietary of Foxit Software Inc.. It is not allowed to
 * distribute any parts of Foxit PDF SDK to third party or public without permission unless an agreement
 * is signed between Foxit Software Inc. and customers to explicitly grant customers permissions.
 *
 * @file fx_error.h
 * @brief Header file for error.
 */

/**
 * @addtogroup FXCRT
 * @{
 */

#ifndef _FX_ERROR_H_
#define _FX_ERROR_H_

// Basic error code specification.
// Define three segment code.(error code, module id, error type)
// error code occupy 16 bits.
// module id occupy 8 bits.
// error type occupy 8 bits.

// We define a basic module id order.
// NOTE: If you want register the module id, please update this file.
// fxcrt  ------  1
// fxge    ------  2
// fxcodec  ------  3
// fdrm    ------  4
// fpdfapi  ------  5
// fxtext  ------  6
// fpdfdoc  ------  7
#define FX_CRT_ID    1
#define FX_GE_ID    2
#define FX_CODEC_ID    3
#define FX_DRM_ID    4
#define FX_PDFAPI_ID  5
#define FX_TEXT_ID    6
#define FX_DOC_ID    7

// Error type
#define FX_ERR_TYPE_SUCCESS      0
#define FX_ERR_TYPE_MEMORY      1

// Error code
#define FX_ERR_CODE_OVERFLOW    0
#define FX_ERR_CODE_ALLOC_FAILE    1

#define FX_MAKEERROR(moduleid, errtype, errcode) ((((errcode) << 16) & 0xFFFF0000) | \
     (((moduleid) << 8) & 0x0000FF00) | ((errtype) & 0x000000FF))

#endif //_FX_ERROR_H_

/** @} */
