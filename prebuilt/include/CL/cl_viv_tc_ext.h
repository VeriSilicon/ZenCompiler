/****************************************************************************
*
*    Copyright 2016 - 2023 Vivante Corporation, Santa Clara, California.
*    All Rights Reserved.
*
*    Permission is hereby granted, free of charge, to any person obtaining
*    a copy of this software and associated documentation files (the
*    'Software'), to deal in the Software without restriction, including
*    without limitation the rights to use, copy, modify, merge, publish,
*    distribute, sub license, and/or sell copies of the Software, and to
*    permit persons to whom the Software is furnished to do so, subject
*    to the following conditions:
*
*    The above copyright notice and this permission notice (including the
*    next paragraph) shall be included in all copies or substantial
*    portions of the Software.
*
*    THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
*    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
*    IN NO EVENT SHALL VIVANTE AND/OR ITS SUPPLIERS BE LIABLE FOR ANY
*    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
*    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
*    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
*****************************************************************************/

#ifndef _GC_TC_H
#define _GC_TC_H 1

#ifdef _VIV_TC_EXTENSION

/*
 * TC_MAX_RANK defines the maximum rank supported by TensorCore. 
 */
#define TC_MAX_RANK 4

/*
 * A dummy definition used as a reminder that the decorated
 * function parameter is intended to represnt an immediate value.
 */
#define __imm

typedef event_t tc_event_t;
typedef uint tc_fragment_handle_t;
typedef uint tc_circular_buffer_t;

#if SUPPORT_64BIT_DIMENSION
typedef ulong4 tc_dim_t
#else
typedef uint4 tc_dim_t;
#endif
typedef uint16 tc_fusion_data_t;

#define TC_EMPTY_FRAGMENT       (tc_fragment_handle_t)0

typedef enum _tc_space_spec_t
{
    TC_SPACE_SPEC_GLOBAL        = 0,
    TC_SPACE_SPEC_LOCAL         = 1,
} tc_space_spec_t;

typedef enum _tc_dtype_t
{
    TC_DTYPE_UINT8              = 0,
    TC_DTYPE_UINT16             = 1,
    TC_DTYPE_INT4               = 2,
    TC_DTYPE_INT8               = 3,
    TC_DTYPE_INT16              = 4,
    TC_DTYPE_INT32              = 5,
    TC_DTYPE_INT64              = 6,
    TC_DTYPE_HALF               = 7,
    TC_DTYPE_FLOAT              = 8,
    TC_DTYPE_BFLOAT16           = 9,
    TC_DTYPE_FLOAT8_E4M3        = 10,
    TC_DTYPE_FLOAT8_E5M2        = 11,
} tc_dtype_t;

typedef enum _tc_pad_mode_t
{
    TC_PAD_MODE_CONST           = 0,
    TC_PAD_MODE_EDGE            = 1,
    TC_PAD_MODE_REFLECT         = 2,
    TC_PAD_MODE_MIRROR          = 3,
} tc_pad_mode_t;

typedef enum _tc_cache_mode_t
{
    TC_CACHE_MODE_NONE          = 0,
    TC_CACHE_MODE_DIRECT        = 1,
    TC_CACHE_MODE_CACHE         = 2,
} tc_cache_mode_t;

typedef enum _tc_coef_encoder_mode_t
{
    TC_COEF_ENCODER_MODE_NONE   = 0,
    TC_COEF_ENCODER_MODE_ENCODE = 1,
    TC_COEF_ENCODER_MODE_REORDER= 2,
} tc_coef_encoder_mode_t;

#endif /* _VIV_TC_EXTENSION */

#endif
