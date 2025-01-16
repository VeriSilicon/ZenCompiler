#pragma once
/**
 * @cond
 *
 */
#ifndef __tc_types_h_
#define __tc_types_h_

#ifdef __cplusplus
extern "C" {
#endif

#define TC_VERSION_MAJOR 1
#define TC_VERSION_MINOR 0
#define TC_VERSION_PATCH 0
#define TC_VERSION \
    (TC_VERSION_MAJOR * 10000 + TC_VERSION_MINOR * 100 + TC_VERSION_PATCH)
#include <stddef.h>
#if !defined(GC_KMD)
# if defined(__KERNEL__)
#  include "linux/version.h"
#  include "linux/types.h"
# elif defined(UNDER_CE)
#  include <crtdefs.h>
typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;
# elif defined(_MSC_VER) && (_MSC_VER <= 1500)
#  include <crtdefs.h>
#  include "vadefs.h"
# elif defined(__QNXNTO__)
#  define _QNX_SOURCE
#  include <stdint.h>
#  include <stdio.h>
# else
#  include <stdint.h>
#  include <stdlib.h>
#  include <stddef.h>
#  include <stdio.h>
# endif
#endif

    /*!
    * \internal
    * \def TC_API_ENTRY
    * \brief This is a tag used to identify exported, public API functions as
    * distinct from internal functions, helpers, and other non-public interfaces.
    * It can optionally be defined in the make system according the the compiler and intent.
    * \ingroup group_basic_features
    */
#ifndef TC_API_ENTRY
#if defined(_WIN32)
#define TC_API_ENTRY __declspec(dllexport)
#else
#define TC_API_ENTRY __attribute__((visibility("default")))
#endif
#endif
#ifndef TC_INTERNAL_ENTRY
#if defined(_WIN32)
#define TC_INTERNAL_ENTRY __declspec(dllexport)
#else
#define TC_INTERNAL_ENTRY __attribute__((visibility("default")))
#endif
#endif
#ifndef TC_API_CALL
#if defined(_WIN32)
#define TC_API_CALL __stdcall
#else
#define TC_API_CALL
#endif
#endif
#ifndef TC_INTERNAL_CALL
#if defined(_WIN32)
#define TC_INTERNAL_CALL __stdcall
#else
#define TC_INTERNAL_CALL
#endif
#endif
#ifndef TC_CALLBACK
#if defined(_WIN32)
#define TC_CALLBACK __stdcall
#else
#define TC_CALLBACK
#endif

#endif

typedef int                     tcBOOL;
typedef signed int              tcENUM;
typedef tcBOOL*                 tcBOOL_PTR;
typedef int                     tcINT;
typedef signed char             tcINT8;
typedef signed short            tcINT16;
typedef signed int              tcINT32;
typedef signed long long        tcINT64;
typedef tcINT*                  tcINT_PTR;
typedef tcINT8*                 tcINT8_PTR;
typedef tcINT16*                tcINT16_PTR;
typedef tcINT32*                tcINT32_PTR;
typedef tcINT64*                tcINT64_PTR;
typedef unsigned int            tcUINT;
typedef unsigned char           tcUINT8;
typedef unsigned short          tcUINT16;
typedef unsigned int            tcUINT32;
typedef unsigned long long      tcUINT64;
typedef tcUINT*                 tcUINT_PTR;
typedef tcUINT8*                tcUINT8_PTR;
typedef tcUINT16*               tcUINT16_PTR;
typedef tcUINT32*               tcUINT32_PTR;
typedef tcUINT64*               tcUINT64_PTR;
typedef size_t                  tcSIZE_T;
typedef float                   tcFLOAT;
typedef float*                  tcFLOAT_PTR;
typedef void*                   tcPOINTER;
typedef void*                   tcHANDLE;
typedef char                    tcCHAR;
typedef tcUINT64                tcADDRESS;
typedef unsigned long int       ulong;
typedef unsigned short int      ushort;
typedef unsigned int            uint;
/**
 * @endcond
 *
 */

/**
 * @file tc_types.h
 * Basic define
 */

/**
 * @brief two int
 *
 */
typedef struct
{
    tcINT32 x; /**< x-coordinate */
    tcINT32 y; /**< y-coordinate */
}tc_int2;

/**
 * @brief four int
 *
 */
typedef struct
{
    tcINT32 x;/**< x-coordinate */
    tcINT32 y;/**< y-coordinate */
    tcINT32 z;/**< z-coordinate */
    tcINT32 w;/**< w-coordinate */
}tc_int4;

/**
 * @brief four long
 *
 */
typedef struct
{
    tcINT64 x;/**< x-coordinate */
    tcINT64 y;/**< y-coordinate */
    tcINT64 z;/**< z-coordinate */
    tcINT64 w;/**< w-coordinate */
}tc_long4;

/**
 * @brief four unsigned long
 *
 */
typedef struct
{
    tcUINT64 x;/**< x-coordinate */
    tcUINT64 y;/**< y-coordinate */
    tcUINT64 z;/**< z-coordinate */
    tcUINT64 w;/**< w-coordinate */
}tc_ulong4;


/**
 * @enum tcSTATUS
 * @brief tcSTATUS
 */
typedef enum
{
    tcSTATUS_OK = 0,                 /**< Success */
    tcSTATUS_FALSE = 0,              /**< False */
    tcSTATUS_TRUE = 1,               /**< True */
    tcSTATUS_INVALID_ARGUMENT = -1,  /**< Invalid argument */
    tcSTATUS_INVALID_OBJECT = -2,    /**< Invalid object */
    tcSTATUS_OUT_OF_MEMORY = -3,     /**< Out of memory */
    tcSTATUS_INVALID_ADDRESS = -4,   /**< Invalid address */
    tcSTATUS_NOT_SUPPORTED = -5,     /**< Not support */
    tcSTATUS_OUT_OF_RESOURCES = -6,  /**< Out of resource */
    tcSTATUS_INVALID_DATA = -7,      /**< Invalid data */
    tcSTATUS_NOT_FOUND = -8,         /**< Can not find */
    tcSTATUS_NOT_ALIGNED = -9,       /**< Can not align */
    tcSTATUS_VERSION_MISMATCH = -10, /**< Version mismatch */
    tcSTATUS_INVALID_INDEX = -100,   /**< Invalid index */
    tcSTATUS_LINK_LIB_ERROR = -101,  /**< Link error */
    tcSTATUS_INVALID_TILE_KPC = -102,/**< Invalid tile size or kpc */
    tcSTATUS_NO_ENOUGH_SPACE = -103, /**< Space not enough */
}tcSTATUS;

/**
 * @enum TC_CACHE_MODE
 * @brief TC_CACHE_MODE
 */
typedef enum
{
    TC_CACHE_MODE_NONE = 0,                          /**< No cache */
    TC_CACHE_MODE_STREAM_CACHE = TC_CACHE_MODE_NONE, /**< No cache */
    TC_CACHE_MODE_DIRECT_CACHE,                      /**< Read data from local directly but still provide
                                                        global address which contains data */
    TC_CACHE_MODE_CACHE,                             /**< Read data from global and cache the read data
                                                        to local memory */
}TC_CACHE_MODE;

/**
 * @enum TC_SPACE_MEMORY
 * @brief TC_SPACE_MEMORY
 */
typedef enum
{
    TC_SPACE_SPEC_INVALID = 0, /**< Invalid */
    TC_SPACE_SPEC_GLOBAL = 1,  /**< Global */
    TC_SPACE_SPEC_LOCAL = 2,   /**< Local */

}TC_SPACE_MEMORY;

/**
 * @enum TC_FP_CLASSIFY
 * | Data Type | NORMAL | DENORMAL |
 * |:------------ |:------------ |:------------ |
 * | fp8 | Yes | Yes |
 * | half | Yes | Yes |
 * | float | Yes | No |
 * | bfloat16 | Yes | No |
 */
typedef enum
{
    TC_FP_NORMAL = 0x0,   /**< Normal */
    TC_FP_DENROMAL = 0x1, /**< Denormal */
    TC_FP_INFINITE = 0x2, /**< Infinity, Not support */
}TC_FP_CLASSIFY;


/**
 * @enum TC_DATA_TYPE
 * @brief TC_DATA_TYPE
 */
typedef enum
{
    TC_DTYPE_INVALID = -1,     /**< invalid */
    TC_DTYPE_UINT8 = 0,        /**< 8 bit unsigned integer */
    TC_DTYPE_UINT16 = 1,       /**< 16 bit unsigned integer */
    TC_DTYPE_INT4 = 2,         /**< 4 bit signed integer */
    TC_DTYPE_INT8 = 3,         /**< 8 bit signed integer */
    TC_DTYPE_INT16 = 4,        /**< 16 bit signed integer */
    TC_DTYPE_INT32 = 5,        /**< 32 bit signed integer */
    TC_DTYPE_INT64 = 6,        /**< 64 bit signed integer */
    TC_DTYPE_HALF = 7,         /**< 16 bit float, SE5M10 */
    TC_DTYPE_FLOAT = 8,        /**< 32 bit float */
    TC_DTYPE_BFLOAT16 = 9,     /**< 16 bit float, SE8M7 */
    TC_DTYPE_CHAR = 10,        /**< 1 bit char */
    TC_DTYPE_UINT32 = 11,      /**< 32 bit unsigned integer */
    TC_DTYPE_UINT64 = 12,      /**< 64 bit unsigned integer */
    TC_DTYPE_FLOAT64 = 13,     /**< 64 bit float */
    TC_DTYPE_BOOL = 14,        /**< 1 bit BOOL */
    TC_DTYPE_BOOL8 = 15,       /**< 8 bit BOOL */
    TC_DTYPE_UINT4 = 16,       /**< 4 bit unsigned integer */
    TC_DTYPE_FLOAT8_E4M3 = 18, /**< 8 bit float, E4M3 */
    TC_DTYPE_FLOAT8_E5M2 = 19, /**< 8 bit float, E5M2 */
}TC_DATA_TYPE;

/**
 * @enum TC_FRAGMENT_TYPE
 * @brief Fragment Type
 */
typedef enum
{
    TC_FRGAMENT_GENGERAL = 0, /**< General fragment */
    TC_FRAGMENT_WEIGHT = 1,   /**< Weight fragment */
    TC_FRAGMENT_BIAS = 2,     /**< Bias fragment */
    TC_FRAGMENT_PRELU = 3,    /**< Prelu fragment */
    TC_FRAGMENT_LUT_IN = 4,   /**< Lut in fragment */
    TC_FRAGMENT_LUT_OUT = 5,  /**< Lut out fragment */
}TC_FRAGMENT_TYPE;

/**
 * @enum TC_PAD_MODE
 * @brief TC_PAD_MODE
 */
typedef enum
{
    TC_PAD_MODE_CONST = 0,    /**< Pad with const valude */
    TC_PAD_MODE_EDGE = 1,     /**< Duplicates the values of boundary elements to fill the padded regions. Not support */
    TC_PAD_MODE_REFLECT = 2,  /**< Reflect padding involves mirroring the input data at the boundaries, \
                                   providing a seamless continuation of the data's pattern into the padded area. Not support */
    TC_PAD_MODE_MIRROR = 3,   /**< Like reflection, mirror padding mirrors the input data at the edges
                                    creating a symmetrical pattern across the padding boundaries. Not support */
}TC_PAD_MODE;

/**
 * @enum TC_COEF_ENCODER_MODE
 * @brief TC_COEF_ENCODER_MODE
 */
typedef enum
{
    NONE = 0,     /**< Reserved, unused */
    ENCODE = 1,   /**< Reorder + humman compression */
    REORDER = 2,  /**< Reorder only */
}TC_COEF_ENCODER_MODE;

/**
 * @cond
 *
 */
typedef tcUINT32 tc_fusion_data_t[16];

typedef tcUINT32 tc_operation_info_t[32];

typedef struct _TC_BUFFER* tc_buffer_t;

typedef struct _TC_FRAGMENT_HANDLE* tc_fragment_handle_t;
/**
 * @endcond
 *
 */
#ifdef __cplusplus
}
#endif

#endif /* __tc_types_h_ */