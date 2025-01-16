#pragma once
#ifndef __tc_common_h_
#define __tc_common_h_

#include <cmath>
#include <string.h>
#include <string>
#include <algorithm>

#ifdef _WIN32
# pragma warning(disable : 4127) /* Conditional expression is constant (do { } while(0)). */
# pragma warning(disable : 4100) /* Unreferenced formal parameter. */
# pragma warning(disable : 4204) /* Non-constant aggregate initializer (C99). */
# pragma warning(disable : 4131) /* Uses old-style declarator. */
# pragma warning(disable : 4206) /* Translation unit is empty. */
# pragma warning(disable : 4214) /* Nonstandard extension used :
                                  * bit field types other than int.
                                  */
#endif
#include "tc_convert.h"
#include <stdarg.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __static_assert
#define __static_assert(cond, msg) __assert_impl(cond, __LINE__, msg)
#define __assert_paste(msg, line) msg##line
#define __assert_impl(cond, line, msg)  \
    typedef char __assert_paste(assert_failed_##msg##_, line)[2*!!(cond)-1];
#endif

#ifndef gctUINT32
#define gctUINT32 unsigned int
#endif

#ifndef gctINT
#define gctINT    int
#endif

#ifndef gcvNULL
#define gcvNULL   NULL
#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4505)
#elif defined(__GNUC__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "gc_feature_database.h"
#ifdef _MSC_VER
#pragma warning(pop)
#elif defined(__GNUC__)
    #pragma GCC diagnostic pop
#endif

#ifdef __cplusplus
# define tcNULL                0
#else
# define tcNULL                ((void *)0)
#endif

#define TC_ENABLE_SWITCH_CLASS 0

#define TC_PRINT_BUFFER_COUNT      2048
void tcPRINT(tcUINT32 level, const char* msg, ...);

#define tcInfo(...)     tcPRINT(TC_DEBUG_LEVEL_INFO, __VA_ARGS__)
#define tcWarning(...)  tcPRINT(TC_DEBUG_LEVEL_INFO, __VA_ARGS__)
#define tcError(...)    tcPRINT(TC_DEBUG_LEVEL_INFO, __VA_ARGS__)

tcSTATUS
tc_GetEnv(
    tcCONST_STRING VarName,
    tcSTRING* Value
);

typedef enum _TC_UPDATE_HANDLE_E
{
    TC_UPDATE_HANDLE_INVALID                = 0,
    TC_UPDATE_HANDLE_INPUT_CACHE            = 1,
    TC_UPDATE_HANDLE_CONV2D_COEF_CAHCE      = 2,
    TC_UPDATE_HANDLE_OUTPUT_CACHE           = 3,
    TC_UPDATE_HANDLE_COUNT                  = 4,
}TC_UPDATE_HANDLE_E;

typedef enum _TC_OP_TYPE_S
{
    TC_CONV2D = 1,
    TC_MATMUL = 1<<1,
    TC_NN = TC_MATMUL|TC_CONV2D,/*hardware go into the same path, need support seperately*/
    TC_MEMCPY = 1 << 2,
    TC_POOLING = 1 << 3,
    TC_ADD = 1 << 4,
    TC_MUL = 1 << 5,
    TC_LUT_ACTIVATION = 1 << 6,
    TC_LEAKYRELU_PRELU = 1 << 7,
    TC_SP_IN_PROGRAM0 = 1 << 8,
    TC_SP_IN_PROGRAM1 = 1 << 9,
    TC_SP_IN_PROGRAM2 = 1 << 10,
    TC_ASYC_COPY = 1 << 11,

    TC_OP_COUNT
}TC_OP_TYPE_S, * TC_OP_TYPE;


typedef struct _TC_ARCH_PARAM_S
{
    tcUINT32                       outImageTileX;
    tcUINT32                       outImageTileY;
    tcUINT32                       kpc;
    tcUINT32                       interleaveMode;
}TC_ARCH_PARAM_S, * TC_ARCH_PARAM;

typedef enum _TC_MEMORY_TYPE
{
    TC_OPTION_MEM_TYPE_INVAILD = 0,
    TC_OPTION_MEM_TYPE_DDR = 1,
    TC_OPTION_MEM_TYPE_VIP_SRAM = 2,
    TC_OPTION_MEM_TYPE_AXI_SRAM,
    TC_OPTION_MEM_TYPE_SP_REGS
}TC_MEMORY_TYPE;

/*should be removed*/
typedef enum _TC_ACTIVATION_TYPE {
    TC_ID_ACTIVATION_NONE = 0,
    TC_ID_ACTIVATION_LOGISTIC = 1,
    TC_ID_ACTIVATION_HYPERBOLIC_TAN = 2,
    TC_ID_ACTIVATION_RELU = 3,
    TC_ID_ACTIVATION_BRELU = 4,
    TC_ID_ACTIVATION_SOFTRELU = 5,
    TC_ID_ACTIVATION_ABS = 6,
    TC_ID_ACTIVATION_SQUARE = 7,
    TC_ID_ACTIVATION_SQRT = 8,
    TC_ID_ACTIVATION_LINEAR = 9,
    TC_ID_ACTIVATION_RELU6 = 10,
    TC_ID_ACTIVATION_RELU1 = 11,
    TC_ID_ACTIVATION_RSQRT = 12,
    TC_ID_ACTIVATION_LEAKYRELU_MAX_POOLING = 13,
    TC_ID_ACTIVATION_SWISH = 14,
    TC_ID_ACTIVATION_HSWISH = 15,
    TC_ID_ACTIVATION_CUSTOM = 16,
    TC_ID_ACTIVATION_GELU_VSI = 17,
    TC_ID_ACTIVATION_HGELU_VSI = 18,
} TC_ACTIVATION_TYPE;

typedef enum _tcTC_LAYOUT_MODE
{
    TC_LAYOUT_CHANNEL_FIRST = 0,
    TC_LAYOUT_TRSP = 1,
    TC_LAYOUT_BANKBRICK = 2,
}tcTC_LAYOUT_MODE;

typedef struct _tcTC_LAYOUT
{
    tcTC_LAYOUT_MODE     layoutMode;
    tcUINT32             layoutValue[4];
}tcTC_LAYOUT;


/*TODO: should be replaced by tx_memory class*/
typedef struct _tcTC_MEMORY_INFO
{
    size_t        dims[tcTENSOR_MAX_DIMENSION]; /*NCHW*/
    tcUINT64      stridesInBytes[tcTENSOR_MAX_DIMENSION];
    TC_DATA_TYPE  dataFormat;
    tcBOOL        isLocalMemory;
    tcPOINTER     address;
    /*Circular for Assembler*/
    tcUINT64      bufferStartAddr;
    tcUINT64      bufferSizeInBytes;
    tcTC_LAYOUT   layout;
}tcTC_MEMORY_INFO, * tcTC_MEMORY_INFO_PTR;

/*TODO:should be replaced by tx_operation*/
typedef struct _tcOPERATION_INFO
{
    TC_OPERATOR_TYPE        opKind;
    tcUINT32                tcProgramOptionFlag;
    tcUINT32                tcLastCmd;
    tcUINT32                pid;
    tcUINT32                ptcmSize;

    tcPOINTER               bias_data_ptr;
    tcPOINTER               prelu_data_ptr;
    tcPOINTER               lut_data_in_ptr;
    tcPOINTER               lut_data_out_ptr;
    tcUINT32                lut_length;

    tcINT32                 tileWidth;
    tcINT32                 tileHeight;
    tcINT32                 kpc;
    tcUINT32                inputCacheStartAddr;
    tcUINT32                inputCacheSizeInBytes;
    tcUINT32                outputCacheStartAddr;
    tcUINT32                outputCacheSizeInBytes;
    TC_FP_CLASSIFY          outputMode;

    tcUINT32                fusionData[16];

    struct
    {
        tcBOOL              isPerChannel;
        tcBOOL              isDepthWise;
        tcINT32             coefEncodeMode;
        tcINT32             padMode;
        tcINT32             padConstValue;
        tcINT32             padding[tcTENSOR_MAX_DIMENSION][2];
        tcUINT32            convStride[tcTENSOR_MAX_DIMENSION];
        tcTC_MEMORY_INFO    input0;
        tcFLOAT             input0Scale;
        tcINT32             input0ZeroPoint;
        tcINT64             input0Offset;
        tcINT64             input0Inc;
        tcTC_MEMORY_INFO    weight;/*coef buffer ptr transfered by weight ptr*/
        tcFLOAT*            weightScale;
        tcINT32*            weightZeroPoint;
        tcTC_MEMORY_INFO    bias;
        tcFLOAT*            biasScale;
        tcINT32*            biasZeroPoint;
        tcTC_MEMORY_INFO    output;
        tcFLOAT             outputScale;
        tcINT32             outputZeroPoint;
        tcINT64             outputOffset;
        tcINT64             outputInc;
        tcFLOAT             convoutScale;
        tcINT32             convoutZeroPoint;
        tcINT32             coefCacheMode;
        tcUINT32            coefCacheStartAddr;
        tcUINT32            coefCacheSizeInBytes;
        tcUINT64            coefSizeInBytes;
        tcUINT32            convoutX;
        tcUINT32            convoutY;
        tcUINT32            groupSize;
    }conv2d;

    struct
    {
        tcBOOL           transposeA;
        tcTC_MEMORY_INFO inputA;
        tcFLOAT          inputAScale;
        tcINT32          inputAZeroPoint;
        tcINT64          inputAOffset;
        tcINT64          inputAInc;
        tcTC_MEMORY_INFO   inputB;
        tcFLOAT          inputBScale;
        tcINT32          inputBZeroPoint;
        tcINT64          inputBOffset;
        tcINT64          inputBInc;
        tcTC_MEMORY_INFO   output;
        tcFLOAT          outputScale;
        tcINT32          outputZeroPoint;
        tcINT64          outputOffset;
        tcINT64          outputInc;
    }
    matmul;

    struct
    {
        tcTC_MEMORY_INFO   input0;
        tcFLOAT          input0Scale;
        tcINT32          input0ZeroPoint;
        tcINT64          input0Offset;
        tcINT64          input0Inc;
        tcTC_MEMORY_INFO   output;
        tcFLOAT          outputScale;
        tcINT32          outputZeroPoint;
        tcINT64          outputOffset;
        tcINT64          outputInc;
    }
    relu;

    struct
    {
        tcTC_MEMORY_INFO   input0;
        tcFLOAT          input0Scale;
        tcINT32          input0ZeroPoint;
        tcINT64          input0Offset;
        tcINT64          input0Inc;
        tcTC_MEMORY_INFO   output;
        tcFLOAT          outputScale;
        tcINT32          outputZeroPoint;
        tcINT64          outputOffset;
        tcINT64          outputInc;
        /* padTop[0][0], padBottom[0][1], padLeft[1][0], padRight[1][1]*/
        tcINT32          poolingPad[tcTENSOR_MAX_DIMENSION][2];
        tcINT32          poolingStride[tcTENSOR_MAX_DIMENSION];
        tcINT32          poolingSize[tcTENSOR_MAX_DIMENSION];
    }
    pooling;

    struct
    {
        tcTC_MEMORY_INFO   input0;
        tcFLOAT          input0Scale;
        tcINT32          input0ZeroPoint;
        tcINT64          input0Offset;
        tcINT64          input0Inc;
        tcTC_MEMORY_INFO   input1;
        tcFLOAT          input1Scale;
        tcINT32          input1ZeroPoint;
        tcINT64          input1Offset;
        tcINT64          input1Inc;
        tcTC_MEMORY_INFO   output;
        tcFLOAT          outputScale;
        tcINT32          outputZeroPoint;
        tcINT64          outputOffset;
        tcINT64          outputInc;
    }
    add;

    struct
    {
        tcTC_MEMORY_INFO   input0;
        tcFLOAT          input0Scale;
        tcINT32          input0ZeroPoint;
        tcINT64          input0Offset;
        tcINT64          input0Inc;
        tcTC_MEMORY_INFO   input1;
        tcFLOAT          input1Scale;
        tcINT32          input1ZeroPoint;
        tcINT64          input1Offset;
        tcINT64          input1Inc;
        tcTC_MEMORY_INFO   output;
        tcFLOAT          outputScale;
        tcINT32          outputZeroPoint;
        tcINT64          outputOffset;
        tcINT64          outputInc;
    }
    mul;

    struct
    {
        tcTC_MEMORY_INFO   input0;
        tcFLOAT          input0Scale;
        tcINT32          input0ZeroPoint;
        tcINT64          input0Offset;
        tcINT64          input0Inc;
        tcTC_MEMORY_INFO   lutBitStream;
        tcTC_MEMORY_INFO   output;
        tcFLOAT          outputScale;
        tcINT32          outputZeroPoint;
        tcINT64          outputOffset;
        tcINT64          outputInc;
        tcTYPE_ACTIVATION_E  activationType;
        tcFLOAT*         alpha;
        tcFLOAT*         beta;
    }
    userLut;

    struct
    {
        tcTC_MEMORY_INFO   input0;
        tcFLOAT          input0Scale;
        tcINT32          input0ZeroPoint;
        tcINT64          input0Offset;
        tcINT64          input0Inc;
        tcTC_MEMORY_INFO   postBitStream;
        tcTC_MEMORY_INFO   output;
        tcFLOAT          outputScale;
        tcINT32          outputZeroPoint;
        tcINT64          outputOffset;
        tcINT64          outputInc;
        tcINT32          postStreamCacheMode;
        tcUINT64         postStreamCacheStartAddr;
        tcUINT64         postStreamCacheSizeInBytes;
        tcUINT64         filterCount;
    }
    prelu;

    struct
    {
        tcTC_MEMORY_INFO   input0;
        tcFLOAT          input0Scale;
        tcINT32          input0ZeroPoint;
        tcINT64          input0Offset;
        tcINT64          input0Inc;
        tcFLOAT          alpha;
        tcTC_MEMORY_INFO   output;
        tcFLOAT          outputScale;
        tcINT32          outputZeroPoint;
        tcINT64          outputOffset;
        tcINT64          outputInc;
    }
    leakyRelu;

    struct
    {
        tcTC_MEMORY_INFO   input0;
        tcINT64          input0Offset;
        tcINT64          input0Inc;
        tcINT32          blockStride[tcTENSOR_MAX_DIMENSION];
        tcTC_MEMORY_INFO   output;
        tcINT64          outputOffset;
        tcINT64          outputInc;
    }
    depth2space;

    struct
    {
        tcUINT32         wordSizeInBytes;
        tcTC_MEMORY_INFO   input0;
        tcINT64          input0Offset;
        tcINT64          input0Inc;
        tcTC_MEMORY_INFO   output;
        tcINT64          outputOffset;
        tcINT64          outputInc;
        tcINT32          padding[tcTENSOR_MAX_DIMENSION][2];
        tcINT32          padConstValue;
        tcUINT32         inSramStride;
        tcUINT32         outSramStride;
        /*tcUINT32         inImageTransposeBufStartAddr;
        tcUINT32         inImageTransposeBufSizeInBytes;
        tcUINT32         outImageTransposeBufStartAddr;
        tcUINT32         outImageTransposeBufSizeInBytes;*/
    }
    transpose;

    struct
    {
        tcTC_MEMORY_INFO   input0;
        tcFLOAT          input0Scale;
        tcINT32          input0ZeroPoint;
        tcINT64          input0Offset;
        tcINT64          input0Inc;
        tcFLOAT          multipiler;
        tcTC_MEMORY_INFO   output;
        tcFLOAT          outputScale;
        tcINT32          outputZeroPoint;
        tcINT64          outputOffset;
        tcINT64          outputInc;
    }
    rescale;

    struct
    {
        tcTC_MEMORY_INFO   input0;
        tcFLOAT          input0Scale;
        tcINT32          input0ZeroPoint;
        tcINT64          input0Offset;
        tcINT64          input0Inc;
        tcTC_MEMORY_INFO   tempBuffer;
        tcINT64          tempBufferOffset;
        tcINT64          tempBufferInc;
        tcINT32          axis;
        tcTC_MEMORY_INFO   output;
        tcFLOAT          outputScale;
        tcINT32          outputZeroPoint;
        tcINT64          outputOffset;
        tcINT64          outputInc;
    }
    softmax;

    struct
    {
        tcTC_MEMORY_INFO   input0;
        tcFLOAT          input0Scale;
        tcINT32          input0ZeroPoint;
        tcINT64          input0Offset;
        tcINT64          input0Inc;
        tcTC_MEMORY_INFO   tempBuffer;
        tcINT64          tempBufferOffset;
        tcINT64          tempBufferInc;
        tcTC_MEMORY_INFO   alpha;
        tcTC_MEMORY_INFO   beta;
        tcFLOAT          eps;
        tcINT32          axis;
        tcTC_MEMORY_INFO   output;
        tcFLOAT          outputScale;
        tcINT32          outputZeroPoint;
        tcINT64          outputOffset;
        tcINT64          outputInc;
    }
    layerNorm;

}tcOPERATION_INFO, * tcOPERATION_INFO_PTR;

/*why recored here?*/
typedef struct _TC_QUERY_INFO
{
    size_t encoder_size;
    void* encoder_data;
    TC_ARCH_PARAM_S tile_size_kpc;
    size_t in_cache_size;
    size_t out_cache_size;
    size_t coef_cache_size;
    size_t kernelStreamFullCacheSize;
    tcBOOL is2_4Sparsity;
    size_t in0_brick_size;
    size_t in1_brick_size;
    size_t out_brick_size;
    tcUINT32* in0_trsp_channel;
    tcUINT32* in1_trsp_channel;
    tcUINT32* out_trsp_channel;
    size_t command_buffer_size;
    void* command_buffer_data;
}TC_QUERY_INFO, * TC_QUERY_INFO_PTR;

#define TMP_RESOURCE_MAX_VAL 64
typedef struct _tcTMP_RESOURCE_POOL
{
    void*       tmpResources[TMP_RESOURCE_MAX_VAL];
    tcSIZE_T    tmpCount;
}tcTMP_RESROUCE_POOL, * tcTMP_RESROUCE_POOL_PTR;

typedef struct _tcTC_GENERIC_HANDLE_S
{
    tcOPERATION_INFO operation_info_s;
    TC_QUERY_INFO    query_info_s;
    tcTMP_RESROUCE_POOL resource_pool_s;
    tcUINT32         tcProgamOption;
}tcTC_GENERIC_HANDLE_S, *tcTC_GENERIC_HANDLE;

#define TENSOR_INFO_DIM_NUM(tensorInfo) \
    (tensorInfo)->dimCount

#define TENSOR_INFO_SIZES(tensorInfo) \
    (tensorInfo)->dims

#define TENSOR_INFO_SIZE_INDEX(tensorInfo, index) \
    TENSOR_INFO_SIZES(tensorInfo)[index]

#define TENSOR_INFO_STRIDES(tensorInfo) \
    (tensorInfo)->stridesInBytes

#define TENSOR_INFO_STRIDE_INDEX(tensorInfo, index) \
    (tensorInfo)->stridesInBytes[index]

#define TENSOR_INFO_SCALE(tensorInfo) \
    (tensorInfo)->scale

#define TENSOR_INFO_ZP(tensorInfo) \
    (tensorInfo)->zeroPoint

#define TENSOR_INFO_DATA_TYPE(tensorInfo) \
    (tensorInfo)->dataFormat

#define TENSOR_INFO_ADDRESS_TYPE(tensorInfo) \
    (tensorInfo)->addressType

#define TENSOR_INFO_LAYOUT_MODE(tensorInfo) \
    (tensorInfo)->layout.layoutMode

#define MEMORY_INFO_SIZES(memoryInfo) \
    (memoryInfo)->dims

#define MEMORY_INFO_SIZE_INDEX(memoryInfo, index) \
    MEMORY_INFO_SIZES(memoryInfo)[index]

#define MEMORY_INFO_DATA_TYPE(memoryInfo) \
    (memoryInfo)->dataFormat


/*should be removed*/
typedef enum _tcTC_GEMM_TYPE
{
    /* gemm command bits(only valid when nn_transpose_en = 0)
            0: regular convolution
            1: TransA x B
            2: A x B
    */
    tcTC_REGULAR_CONVOLUTION = 0,
    TC_GEMM_TRANS_MAT_A = 1,
    TC_GEMM_NONE_TRANS = 2,

} TC_GEMM_TYPE;

enum _TC_IMAGE_BLOCK_CTRL
{
    TC_NO_BLOCKING = 0,
    TC_UNUSED = 1,
    TC_BLOCK_ONE_3D_TILE = 2,
    TC_BLOCK_WHOLE_IMAGE = 3,
};

typedef enum _tcTC_ROUND_MODE
{
    tcTC_ROUNDING_MODE_SIMPLE_ROUNDING = 0,
    tcTC_ROUNDING_MODE_RTNE = 1,
    tcTC_ROUNDING_MODE_RTZ = 2,
    tcTC_ROUNDING_MODE_RTNI = 3,
}tcTC_ROUND_MODE;

typedef enum _tcTC_KERNEL_ENCODE_MODE
{
    tcTC_KERNEL_ENCODE_MODE_NONE = 0,
    tcTC_KERNEL_ENCODE_MODE_ENCODE = 1,
    tcTC_KERNEL_ENCODE_MODE_REORDER = 2,
}tcTC_KERNEL_ENCODE_MODE;

typedef enum _tcTC_POOLING_TYPE
{
    tcTC_POOLING_TYPE_NONE = 0,
    tcTC_POOLING_TYPE_MAX_POOLING = 1,
    tcTC_POOLING_TYPE_FIRST_PIXEL_POOLING = 2,
}tcTC_POOLING_TYPE;

enum
{
    TC_OPTION_TILE_BRICK_MODE_OFF = 0,
    TC_OPTION_TILE_BRICK_MODE_CONV = 1,
    TC_OPTION_TILE_BRICK_MODE_CONV_W0_16 = (0x1 << 1) | TC_OPTION_TILE_BRICK_MODE_CONV,
    TC_OPTION_TILE_BRICK_MODE_CONV_W0_32 = (0x1 << 2) | TC_OPTION_TILE_BRICK_MODE_CONV,
    TC_OPTION_TILE_BRICK_MODE_CONV_W0_64 = (0x1 << 3) | TC_OPTION_TILE_BRICK_MODE_CONV,
    TC_OPTION_TILE_BRICK_MODE_GEMM = (0x1 << 7),
    TC_OPTION_TILE_BRICK_MODE_MTB_W0_16 = (0x1 << 1) | TC_OPTION_TILE_BRICK_MODE_GEMM,
    TC_OPTION_TILE_BRICK_MODE_MTB_W0_32 = (0x1 << 2) | TC_OPTION_TILE_BRICK_MODE_GEMM,
    TC_OPTION_TILE_BRICK_MODE_MTB_W0_64 = (0x1 << 3) | TC_OPTION_TILE_BRICK_MODE_GEMM,
    TC_OPTION_TILE_BRICK_MODE_MTA_W0_16 = (0x1 << 4) | TC_OPTION_TILE_BRICK_MODE_MTB_W0_16,
    TC_OPTION_TILE_BRICK_MODE_MTA_W0_32 = (0x1 << 5) | TC_OPTION_TILE_BRICK_MODE_MTB_W0_32,
    TC_OPTION_TILE_BRICK_MODE_MTA_W0_64 = (0x1 << 6) | TC_OPTION_TILE_BRICK_MODE_MTB_W0_64,
};

typedef enum
{
    TC_SP_ATTRIBUTE_OUTPUT_COLLAPSE_DISABLED,
    TC_SP_ATTRIBUTE_OUTPUT_COLLAPSE_ENABLED,
}TC_SP_ATTR_OUTPUT_COLLAPSE_E;

typedef enum
{
    TC_SP_ATTRIBUTE_SUM_ENGINE_RESET_NONE,
    TC_SP_ATTRIBUTE_SUM_ENGINE_RESET_RESET,
}TC_SP_ATTR_SUM_EIGINE_E;

typedef enum
{
    TC_OPTION_SP_ATTRIBUTE_INPUT_TILE_MAPPING_XYMERGE,
    TC_OPTION_SP_ATTRIBUTE_INPUT_TILE_MAPPING_YZMERGE,
}TC_SP_ATTR_INPUT_TILE_MAPPING_E;

/*should be placed by tx_tensor*/
typedef struct _tcTC_TENSOR_INFO
{
    tcSIZE_T          dims[tcTENSOR_MAX_DIMENSION];
    tcINT64           stridesInBytes[tcTENSOR_MAX_DIMENSION];
    TC_DATA_TYPE      dataFormat;
    tcFLOAT           scale;
    tcINT32           zeroPoint;
    tcUINT64          startAddr;
    tcPOINTER         address;
    TC_MEMORY_TYPE    addressType;
    tcUINT64          bufferSizeInBytes;
    tcTC_LAYOUT       layout;
    tcUINT32          transposeChMinusOne;
}tcTC_TENSOR_INFO, * tcTC_TENSOR_INFO_PTR;

typedef enum
{
    TC_SP_ATTRIBUTE_TILE_ALIGN_SP_CORE_NONE = 0,
    TC_SP_ATTRIBUTE_TILE_ALIGN_SP_CORE_WITH_AXIS_X,
    TC_SP_ATTRIBUTE_TILE_ALIGN_SP_CORE_WITH_AXIS_Y,
    TC_SP_ATTRIBUTE_TILE_ALIGN_SP_CORE_WITH_AXIS_XY,
}
TC_SP_ATTR_TILE_ALIGN_E;

typedef enum _TC_SP_ATTR_E
{
    TC_OPTION_SP_ATTRIBUTE_NONE = 0,

    TC_OPTION_SP_ATTRIBUTE_INPUT_TILE_MAPPING,
    TC_OPTION_SP_ATTRIBUTE_OUTPUT_COLLAPSE_X,
    TC_OPTION_SP_ATTRIBUTE_OUTPUT_COLLAPSE_Y,
    TC_OPTION_SP_ATTRIBUTE_OUTPUT_COLLAPSE_Z,

    TC_OPTION_SP_ATTRIBUTE_PROG_INIT_INSTR_NUM,
    TC_OPTION_SP_ATTRIBUTE_PROG_LOOP_INSTR_NUM,
    TC_OPTION_SP_ATTRIBUTE_PROG_COMPLETE_INSTR_NUM,
    TC_OPTION_SP_ATTRIBUTE_PROG_ROUNDING_MODE,
    TC_OPTION_SP_ATTRIBUTE_INPUT_SETUP,

    TC_OPTION_SP_ATTRIBUTE_IGNORED_LEADING_OUTPUTS,
    TC_OPTION_SP_ATTRIBUTE_FLUSH_CYCLE_NUM,
    TC_OPTION_SP_ATTRIBUTE_IGNORED_LEADING_V11_WR,
    TC_OPTION_SP_ATTRIBUTE_IGNORED_LEADING_V12_WR,
    TC_OPTION_SP_ATTRIBUTE_IGNORED_LEADING_V11_RD,
    TC_OPTION_SP_ATTRIBUTE_IGNORED_LEADING_V12_RD,

    TC_OPTION_SP_ATTRIBUTE_CH0_POST_REDISTRIBUTE,
    TC_OPTION_SP_ATTRIBUTE_CH1_POST_REDISTRIBUTE,
    TC_OPTION_SP_ATTRIBUTE_V11_RESET_AT_START,
    TC_OPTION_SP_ATTRIBUTE_V12_RESET_AT_START,
    TC_OPTION_SP_ATTRIBUTE_V11_POP_CONFIG,
    TC_OPTION_SP_ATTRIBUTE_V12_POP_CONFIG,
    TC_OPTION_SP_ATTRIBUTE_ACCELERATOR_INPUT_SELECT,
    TC_OPTION_SP_ATTRIBUTE_IGNORED_LEADING_ACC_OUT,
    TC_OPTION_SP_ATTRIBUTE_SUM_ENGINE_RESET,
    TC_OPTION_SP_ATTRIBUTE_SUM_ENGINE_CONTROL,
    TC_OPTION_SP_ATTRIBUTE_SUM_ENGINE_NUM_CH_MINUS_ONE,
    TC_OPTION_SP_ATTRIBUTE_SUM_ENGINE_2D_ACCUM_STORAGE,
    TC_OPTION_SP_ATTRIBUTE_SUM_ENGINE_OP_SELECT,

    TC_OPTION_SP_ATTRIBUTE_NUM_OF_ELEMENTS_PER_LOOP_PER_INPUT,

    TC_OPTION_SP_ATTRIBUTE_NUM_OF_V11_RD_IN_FLUSH_CYCLE,
    TC_OPTION_SP_ATTRIBUTE_NUM_OF_V12_RD_IN_FLUSH_CYCLE,
    TC_OPTION_SP_ATTRIBUTE_NUM_OF_V11_WR_IN_FLUSH_CYCLE,
    TC_OPTION_SP_ATTRIBUTE_NUM_OF_V12_WR_IN_FLUSH_CYCLE,

    TC_OPTION_SP_ATTRIBUTE_GENERAL_COUNT,

    TC_OPTION_SP_ATTRIBUTE_CONST0,     /* NN post multiplier    */
    TC_OPTION_SP_ATTRIBUTE_CONST1,     /* NN neg pos multiplier */
    TC_OPTION_SP_ATTRIBUTE_CONST2,     /* NN tensor add const   */
    TC_OPTION_SP_ATTRIBUTE_CONST3,     /* NN clamp max          */
    TC_OPTION_SP_ATTRIBUTE_CONST4,     /* NN clmap min          */

    TC_OPTION_SP_ATTRIBUTE_CONST_COUNT,

    TC_OPTION_SP_ATTRIBUTE_SPLIT_AXIS,
    TC_OPTION_SP_ATTRIBUTE_SPLIT_MAX_SIZE,
    TC_OPTION_SP_ATTRIBUTE_SPLIT_TILEX_EQUAL_INIMAGEX,

    TC_OPTION_SP_ATTRIBUTE_MULTIVIP_SPLIT_AXIS,
    TC_OPTION_SP_ATTRIBUTE_FORCE_DUPLICATE_AXIS,

    TC_OPTION_SP_ATTRIBUTE_NOT_MERGE_CONVSP,
    TC_OPTION_SP_ATTRIBUTE_UPDATE_CONST0_TO_PCQ_COEF_TENSOR,
    TC_OPTION_SP_ATTRIBUTE_RESHAPE_ARRAY, /* bit layout | output:24-29 | input3:18-23 | input2:12-17 | input1:6-11 | input0:0-5 | */
    TC_OPTION_SP_ATTRIBUTE_ALIGN_SP_CORE_AXIS,
    TC_OPTION_SP_ATTRIBUTE_KEEP_TILE_SIZE,
    TC_OPTION_SP_ATTRIBUTE_BROADCAST_AXIS,

    TC_OPTION_SP_ATTRIBUTE_TOTAL_COUNT,
}
TC_SP_ATTR_E;

typedef struct _TC_SP_INFO_S
{
    tcUINT32                       attributesArray[TC_OPTION_SP_ATTRIBUTE_TOTAL_COUNT];
    tcUINT32                       attributesEnable[TC_OPTION_SP_ATTRIBUTE_TOTAL_COUNT];
}TC_SP_INFO_S, * TC_SP_INFO;

/*tx_nn*/
typedef struct _TC_NN_INST_INFO_S
{
     /*this struct means SW parameter*/
    tcUINT32                       operationType;
    tcUINT32                       gemmType;
    tcBOOL                         isHwDepthwise;

    TC_DATA_TYPE                   inImageDataType[tc_ARCH_NN_SUPPORT_MAX_INPUT_COUNT];
    tcUINT64                       inImageSize[tc_ARCH_NN_SUPPORT_MAX_INPUT_COUNT][tcTENSOR_MAX_DIMENSION]; /* WHCN */
    tcUINT64                       inImageStrideInBits[tc_ARCH_NN_SUPPORT_MAX_INPUT_COUNT][tcTENSOR_MAX_DIMENSION];

    TC_DATA_TYPE                   outImageDataType;
    tcUINT64                       outImageSize[tcTENSOR_MAX_DIMENSION]; /*outImageSize is final output, not convCore out */
    tcUINT64                       outImageStrideInBits[tcTENSOR_MAX_DIMENSION];

    TC_DATA_TYPE                   kernelDataType;
    tcUINT32                       kernelSize[tcTENSOR_MAX_DIMENSION];

    tcUINT32                       pad[tcTENSOR_MAX_DIMENSION][2];
    tcUINT32                       nnStride[tcTENSOR_MAX_DIMENSION];
    tcENUM                         poolingType;
    tcUINT32                       poolingPad[tcTENSOR_MAX_DIMENSION][2];
    tcUINT32                       poolingStride[tcTENSOR_MAX_DIMENSION];
    tcUINT32                       poolingSize[tcTENSOR_MAX_DIMENSION];
    tcUINT32                       d2sBlockStride[tcTENSOR_MAX_DIMENSION];
    tcINT32                        nnCoefDecompressBypass;
    tcBOOL                         kernelDirectStreamFromVipSram;

    /*memory related*/
    tcENUM                         inImageBufferType[tc_ARCH_NN_SUPPORT_MAX_INPUT_COUNT];
    tcENUM                         outImageBufferType;
    tcENUM                         inImageCacheMode[tc_ARCH_NN_SUPPORT_MAX_INPUT_COUNT];
    tcINT32                        kernelCacheMode;
    tcUINT64                       inImageCacheSize[tc_ARCH_NN_SUPPORT_MAX_INPUT_COUNT];//fill in streamSize when cacheMode is streamCache
    tcUINT64                       kernelCacheSize;
    /******************************/


    tcBOOL                         lut_load;

    /*streamProcessor*/
        TC_SP_INFO_S        spBasicInfo;
    /******************************/

    /*split_x_among_cluster*/
    tcUINT8                        hwTileWalkMode;
    tcUINT32                       sendOverlap2LeftCore;
    tcUINT32                       sendOverlap2RightCore;
    tcUINT32                       receiveOverlapFromLeftCore;
    tcUINT32                       receiveOverlapFromRightCore;
        /*****************************/

     /*transposePhase1*/
    tcUINT32                       transposeInchannel;
    tcUINT32                       transpose2ndInchannel;
    tcUINT32                       transposeOutchannel;
        /*****************************/

    /*bankBrick*/
    tcINT32                        in_img_brick_mode;
    tcINT32                        sec_img_brick_mode;
    tcINT32                        out_img_brick_mode;
        /*****************************/

            /*tileSize Kpc configuration*/
    tcUINT32                         tileSizeKpcConfig[ARCH_PARM_COUNT]; /*currently, only requests for tileSize are supported, kpc does not support*/
    tcUINT32                         TileXYMAX;
        /*****************************/

}TC_NN_INST_INFO_S, * TC_NN_INST_INFO;


/*tx_nt*/
typedef struct _TC_NT_INST_INFO_S
{
    tcUINT64                       word_size;
    tcENUM                         inImageDataType;
    tcUINT64                       inImageSize[tcTENSOR_MAX_DIMENSION]; /* WHCN */
    tcUINT64                       inImageStrideInBits[tcTENSOR_MAX_DIMENSION];
    tcENUM                         outImageDataType;
    tcUINT64                       outImageSize[tcTENSOR_MAX_DIMENSION]; /*outImageSize is final output, not convCore out */
    tcUINT64                       outImageStrideInBits[tcTENSOR_MAX_DIMENSION];
    tcUINT32                       pad[tcTENSOR_MAX_DIMENSION][2];
    /*memory related*/
    tcENUM                         inImageBufferType;
    tcENUM                         outImageBufferType;
    tcUINT64                       inImageCacheSize;//fill in streamSize when cacheMode is streamCache
    tcUINT64                       outImageCacheSize;
    /******************************/

}TC_NT_INST_INFO_S, * TC_NT_INST_INFO;


/*tx_dma*/
typedef struct _TC_DMA_INST_INFO_S
{
    tcENUM                         inImageDataType;
    tcUINT64                       inImageSize[tcTENSOR_MAX_DIMENSION]; /* WHCN */
    tcUINT64                       inImageStrideInBits[tcTENSOR_MAX_DIMENSION];

    tcENUM                         outImageDataType;
    tcUINT64                       outImageSize[tcTENSOR_MAX_DIMENSION]; /*outImageSize is final output, not convCore out */
    tcUINT64                       outImageStrideInBits[tcTENSOR_MAX_DIMENSION];

    /*memory related*/
    tcENUM                         inImageBufferType;
    tcENUM                         outImageBufferType;
    tcUINT64                       inImageCacheSize;//fill in streamSize when cacheMode is streamCache
    tcUINT64                       outImageCacheSize;
    /******************************/


}TC_DMA_INST_INFO_S, * TC_DMA_INST_INFO;

typedef struct _TC_COEF_INFO_S
{
    /*this struct contain coef key parameter*/
    tcFLOAT          encoded_retio;
    tcUINT32         encoded_stream_size;
    tcUINT32         encoded_body_size;
    tcBOOL           lut_load;
}TC_COEF_INFO_S, * TC_COEF_INFO;


typedef struct _TC_NN_EXEC_INFO_S
{
    /*this struct contain parameters when hardware executing to avoid dupilcate calculation*/
    tcUINT32    conv_core_count;
    tcUINT32    prep_dp_num;
    tcUINT32    dp_num;
    tcUINT32    zdp_loop_count;
    tcUINT32    inimg_buf_num;
    tcUINT32    tile_num;
    tcUINT32    kernel_dp_group_num; /*kernel*/
    tcUINT32    vz_group_num;
    tcUINT32    lanes_per_core;
    tcUINT32    hw_mac_count; /*different format may hsa different mac count*/
    tcUINT64    op_mac_count; /*kx * ky * kz * outx * outy * outz*/

    tcUINT64    conv_out[tcTENSOR_MAX_DIMENSION];
    tcUINT32    tile_num_w;     /* = tcCEIL(nn_info.outImageSize[0] / tile_kpc.outImageTileX);*/
    tcUINT32    tile_num_h;     /* = tcCEIL(nn_info.outImageSize[1] / tile_kpc.outImageTileY);*/
    tcUINT32    last_kpc;/*kpc of last vz group*/
    tcUINT32    tx_right;             /*= (nn_info.outImageSize[0] - 1) % tile_kpc.outImageTileX + 1;*/
    tcUINT32    ty_bottom;            /*= (nn_info.outImageSize[1] - 1) % tile_kpc.outImageTileY + 1;*/

}TC_NN_EXEC_INFO_S, * TC_NN_EXEC_INFO;


typedef struct _TC_NT_EXEC_INFO_S
{
    /*this struct contain parameters when hardware executing to avoid dupilcate calculation*/

    tcUINT32    tile_num;
    tcUINT32    tile_num_w;     /* = tcCEIL(nn_info.outImageSize[0] / tile_kpc.outImageTileX);*/
    tcUINT32    tile_num_h;     /* = tcCEIL(nn_info.outImageSize[1] / tile_kpc.outImageTileY);*/
    tcUINT32    tx_right;             /*= (nn_info.outImageSize[0] - 1) % tile_kpc.outImageTileX + 1;*/
    tcUINT32    ty_bottom;            /*= (nn_info.outImageSize[1] - 1) % tile_kpc.outImageTileY + 1;*/

}TC_NT_EXEC_INFO_S, * TC_NT_EXEC_INFO;

/*tx_operation*/
typedef struct _TC_OP_INFO_S
{
    TC_OP_TYPE_S type;
    union
    {
        struct
        {
            TC_NN_INST_INFO_S    nn_info;
            TC_COEF_INFO_S       coef_info;
            TC_ARCH_PARAM_S      tile_kpc;
            TC_NN_EXEC_INFO_S    nn_exec_param;
        };
        struct
        {
            TC_NT_INST_INFO_S    nt_info;
            TC_NT_EXEC_INFO_S    nt_exec_param;
        };
        struct
        {
            TC_DMA_INST_INFO_S   dma_info;
        };
    };
}TC_OP_INFO_S, *TC_OP_INFO;

/******************************************************************************
  ************************ common interfaces **********************************
  ******************************************************************************/


/******************************************************************************
  ************************ utility functions **********************************
  ******************************************************************************/


tcINT32
gcGetDataTypeBitSize(
    TC_DATA_TYPE DataType
);

tcUINT32
get_bpp(tcUINT32* Feature, TC_DATA_TYPE data_type);

tcSTATUS
gcGetMaxMinWithDataType(
    TC_DATA_TYPE format,
    tcFLOAT* max,
    tcFLOAT* min
);

tcENUM tcGetActivationType(
    TC_ACTIVATION_TYPE cmd_type
);

tcPOINTER
tcAllocateAndZeroMemory(
    tcSIZE_T size
);

tcBOOL isD2SModuleActive(
    tcOPERATION_INFO_PTR operation_info_p
);

tcSTATUS tcDestroyQueryResources(
    TC_QUERY_INFO_PTR query_info
);

tcSTATUS  tcDestroyTmpResourcePool(
    tcTMP_RESROUCE_POOL_PTR tmp_resorce_pool_p
);

tcSTATUS tcCheckCoefEncoderParameter(
    tcOPERATION_INFO operation_info
);

tcSTATUS tcCheckArchParameter(
    tcOPERATION_INFO operation_info
);

tcSTATUS tcCheckCacheParameter(
    tcOPERATION_INFO operation_info
);

tcBOOL tcOperation_IsTwoInputsOp(
    tcOPERATION_INFO_PTR operation_info_p
);

tcSIZE_T ComputeInputSize(
    tcSIZE_T    outputSize,
    tcUINT32  kernelSize,
    tcINT32   padTop,
    tcINT32   padBottom,
    tcUINT32  poolingSize,
    tcUINT32  poolingStride,
    tcBOOL    maxPoolingEnhanced,
    tcUINT32  poolingPadTop,
    tcUINT32  poolingPadBottom,
    tcUINT32  nnStride,
    tcUINT32  blockSize,
    tcSIZE_T* convOut,
    tcUINT32  type
);

tcSTATUS convert_nchw_to_whcn(
    tcTC_MEMORY_INFO memory_info,
    tcTC_MEMORY_INFO* new_memory_info
);

tcSTATUS getGemmBestIntxy(tcTC_MEMORY_INFO* input_info, tcTC_MEMORY_INFO* output_info);

tcSTATUS generateOpBasicInfo(tcOPERATION_INFO_PTR operation_info, TC_NN_INST_INFO_S* basic_info);

// reused by cacheSize calculation and assembler
tcSTATUS getTransposeTileSizeInBytes(
    tcUINT32 wordSizeInBytes,
    tcUINT32* inTileXSizeInBytes,
    tcUINT32* outTileXSizeInBytes
);

tcUINT32 getTransposeSramStride(
    tcUINT32* Feature,
    tcUINT32 tileXSizeInBytes,
    tcUINT32 inImageXSizeInBytes
);

tcBOOL is_valid_tilesize_kpc(
    tcHANDLE tc_handle);

tcBOOL is_op_valid_tilesize_kpc(
    tcOPERATION_INFO_PTR operation_info_p);

tcBOOL is_depthwise_conv(
    tc_ulong4 coef_size,
    tc_ulong4 output_size);
#ifdef __cplusplus
}
#endif

#include <vector>
namespace vsi {
    namespace tensorcore {
        namespace tools {
            namespace tc_common_utils {
                template <typename T, std::size_t N>
                std::vector<T> vector_insert_pad(const std::vector<T> vec_in)
                {
                    static_assert(N > 0, "N must greater than 0\n");
                    assert(vec_in.size() <= N && " [tcToolkits] Rank not support\n");
                    std::vector<T> vec_rt = vec_in;

                    std::reverse(vec_rt.begin(), vec_rt.end());
                    vec_rt.resize(N);
                    std::reverse(vec_rt.begin(), vec_rt.end());
                    return std::move(vec_rt);
                }
            }

            namespace tc_memcpy_utils {
                tcBOOL isValidMemcpyHandle(tcHANDLE tc_handle);
            }
        } // tools
    } // tensorcore
} //vsi

#endif /* __tc_common_h_ */