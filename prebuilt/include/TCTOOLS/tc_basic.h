#pragma once
#ifndef __tc_basic_h_
#define __tc_basic_h_

/*
* this file just define common declare
*/

#define tcFALSE                0
#define tcTRUE                 1

#define tcINFINITE             ((tcUINT32)~0U)
#define tcIS_ERROR(status)  (status != tcSTATUS_OK)
#define tcONERROR(func) \
    do \
    { \
        status = func; \
        if (tcIS_ERROR(status)) \
        { \
            goto OnError; \
        } \
    } \
    while (tcFALSE)



#define tcMAXINT8              0x7f
#define tcMININT8              0x80
#define tcMAXINT16             0x7fff
#define tcMININT16             0x8000
#define tcMAXINT32             0x7fffffff
#define tcMININT32             0x80000000
#define tcMAXINT64             0x7fffffffffffffff
#define tcMININT64             0x8000000000000000
#define tcMAXUINT8             0xff
#define tcMINUINT8             0x0
#define tcMAXUINT16            0xffff
#define tcMINUINT16            0x0
#define tcMAXUINT32            0xffffffff
#define tcMINUINT32            0x0
#define tcMAXUINT64            0xffffffffffffffff
#define tcMINUINT64            0x0
#define tcMAXSIZE_T            ((tcSIZE_T)(-1))
#define tcMAXUINTPTR_T         (~(tcUINTPTR_T)0)


#define tcMATH_Log_HighPrecision(X)    (tcFLOAT)(log(((tcDOUBLE)X)))
#define tcMATH_Log2_HighPrecision(X)   (tcFLOAT)(log(((tcDOUBLE)X)) / log(2.0))
#define tcMATH_Ceiling(X)    (tcFLOAT)(ceilf((X)))
#define tcMATH_Power(X, Y)        (tcFLOAT)(powf((X),(Y)))
#define tcMATH_Power_HighPrecision(X, Y)        (tcFLOAT)((tcDOUBLE)powf((X),(Y)))
#define tcMATH_SquareRoot(X) (tcFLOAT)(sqrtf((X)))
#define tcMATH_SquareRoot_HighPrecision(X) (tcFLOAT)((tcDOUBLE)sqrtf((X)))
#define tcMATH_TangentH(X)   (tcFLOAT)(tanhf((X)))
#define tcMATH_TangentH_HighPrecision(X)   (tcFLOAT)(tanh((tcDOUBLE)(X)))
#define tcMATH_Exp(X)        (tcFLOAT)(expf((X)))
#define tcMATH_Exp_HighPrecision(X)        (tcFLOAT)(exp((tcDOUBLE)(X)))
#define tcMATH_Absolute(X)   (tcFLOAT)(fabsf((X)))
#define tcMATH_ReciprocalSquareRoot(X) (tcFLOAT)(1.0f / sqrtf((X)))
#define tcMATH_ReciprocalSquareRoot_HighPrecision(X) (tcFLOAT)((tcDOUBLE)(1.0 / sqrt((X))))
#define tcMATH_Sine(X)       (tcFLOAT)(sinf((X)))
#define tcMATH_Cosine(X)     (tcFLOAT)(cosf((X)))
#define tcMIN(x, y)            (((x) <= (y)) ? (x) : (y))
#define tcMAX(x, y)            (((x) >= (y)) ? (x) : (y))
#define tcALIGN(n, align)      (((n) + ((align) - 1)) & ~((align) - 1))
#define tcIS_SUCCESS(status)       ((status) == tcSTATUS_OK)
#define tcMIN(x, y)            (((x) <= (y)) ? (x) : (y))
#define tcMAX(x, y)            (((x) >= (y)) ? (x) : (y))
#define tcALIGN(n, align)      (((n) + ((align) - 1)) & ~((align) - 1))
#define tcALIGN_NP2(n, align) (((n) + (align) - 1) - (((n) + (align) - 1) % (align)))
#define tcALIGN_NP2_SAFE(n, align)                                         \
(                                                                           \
    (tcALIGN_NP2((n) & ~0ULL, (align) & ~0ULL) ^ tcALIGN_NP2(n, align)) ? \
        (n) : tcALIGN_NP2(n, align)                                        \
)
#define tcCEIL(x)                                                      \
(                                                                       \
    ((x) - (gctUINT32)(x)) == 0 ? (gctUINT32)(x) : (gctUINT32)(x) + 1   \
)
#define tcIS_SUCCESS(status)       ((status) == tcSTATUS_OK)

#define tcTENSOR_MAX_DIMENSION     4
#define tcTC_ZDP_LOOP3_COUNT 3
#define tcTC_ZDP_LOOP6_COUNT 6
#define ARCH_PARM_COUNT                    3
#define tc_ARCH_NN_SUPPORT_MAX_INPUT_COUNT 4
#define TC_TRANSPOSE_MAX_INTERLEAVE_CH 16
#define HIGH_DP_LOOP1_COUNT 1
#define FEATURE_VALUE(Feature, name) (Feature[name])
#define FEATURE_AVAILABLE(Feature, name) ((Feature[name]) ? tcTRUE : tcFALSE)


#define OPTION_DDR_KERNEL_BURST_SIZE Feature[TC_OPTION_DDR_KERNEL_BURST_SIZE]
#define VIP_SRAM_WIDTH_IN_BYTES Feature[TC_OPTION_PHYSICAL_VIP_SRAM_WIDTH_IN_BYTE]
#define OPTION_AXI_BUS_WIDTH Feature[TC_OPTION_AXI_BUS_WIDTH]
#define TC_VIPSRAM_ALIGN_SIZE               (tcMAX(128, VIP_SRAM_WIDTH_IN_BYTES))

#define LANES_PERCORE                       64
#define NN_INPUT_XSIZE_MAX                  ((1 << 13) - 1)


#define NN_LUT_PARAM_SIZE 3
#define NN_LUT_BUFF_SIZE (1024 + NN_LUT_PARAM_SIZE)
#define FLOAT_BIAS_EXPONENT 127
#define FLOAT8_E5M2_BIAS_EXPONENT 15
#define FLOAT_MATISSA_SIZE  23
#define FLOAT8_E4M3_BIAS_EXPONENT 7
#define FLOAT8_E4M3_MANTISSA_SIZE 3
#define FLOAT8_E5M2_MANTISSA_SIZE 2
#define SINGLEFLOATFINITYMAX        0x7F7FFFFF
#define SINGLEFLOATFINITYMIN        0xFF7FFFFF
#define MAX_TABLE_LOOKUP_SIZE 1024
#define F16_EXPONENT_BITS 0x1F
#define F16_EXPONENT_BIAS 15
#define F21_EXPONENT_SHIFT 15
#define F21_MANTISSA_BITS ((1 << F21_EXPONENT_SHIFT) - 1)
#define F21_MANTISSA_SHIFT (23 - F21_EXPONENT_SHIFT)
#define F21_MAX_EXPONENT (F16_EXPONENT_BITS << F21_EXPONENT_SHIFT)
#define SE5M15_MAX_VALUE  (131070)
#define SE5M15_MIN_VALUE  (-131070)
#define SE8M12_EXPONENT_SHIFT 12
#define SE8M12_MANTISSA_BITS ((1 << SE8M12_EXPONENT_SHIFT) - 1)
#define SE8M12_MANTISSA_SHIFT (23 - SE8M12_EXPONENT_SHIFT)
#define SE8M12_MAX_EXPONENT (SE8M12_MANTISSA_BITS << SE8M12_EXPONENT_SHIFT)
/* Alignment with a non-power of two value. */
#define KERNEL_CACHE_START_END_ALIGNMENT_SIZE \
    ((Feature[TC_OPTION_USE_VIPSRAM_FOR_KERNEL_STREAMING]) ? tcMAX(VIP_SRAM_WIDTH_IN_BYTES, OPTION_DDR_KERNEL_BURST_SIZE) : 0)


typedef char* tcSTRING;
typedef const char* tcCONST_STRING;
typedef double                  tcDOUBLE;
typedef unsigned long long      tcUINTPTR_T;

enum {
    TC_DEBUG_LEVEL_NONE = 0,
    TC_DEBUG_LEVEL_INFO = 1,
    /*VX_DEBUG_LEVEL_ERROR = 2,*/
};

typedef enum _tc_fusion_id {
    TC_FUSION_ID_TRANSPOSE_INPUT_LAYOUT = 0,

    TC_FUSION_ID_RELU_1 = 2,
    TC_FUSION_ID_POOLING = 3,
    TC_FUSION_ID_PRELU = 4,
    TC_FUSION_ID_LEAKY_RELU = 5,
    TC_FUSION_ID_ADD = 6,
    TC_FUSION_ID_RELU_2 = 7,
    TC_FUSION_ID_MUL = 8,
    TC_FUSION_ID_LUT = 9,
    TC_FUSION_ID_DEPTH2SPACE = 11,
    TC_FUSION_ID_RESCALE = 12,
    TC_FUSION_ID_RESCALE_PCQ = 13,
    TC_FUSION_ID_CLAMP = 14,
    //ext for toolkits
    TC_FUSION_ID_CONV = 15,
    TC_FUSION_ID_HASBIAS_FLAG = 16,
    TC_FUSION_ID_IS_PCQ_FLAG = 17,
} tc_fusion_id;

#define TC_FUSION_TYPE(NAME, VALUE) TC_FUSION_TYPE_##NAME = VALUE,
#define TC_FUSION_TYPE_ENUMS \
    TC_FUSION_TYPE(TRANSPOSE_INPUT_LAYOUT, 1 << 31) \
    TC_FUSION_TYPE(RELU, 1 << 29) \
    TC_FUSION_TYPE(MAXPOOLING, 1 << 28) \
    TC_FUSION_TYPE(PRELU, 1 << 27) \
    TC_FUSION_TYPE(LEAKYRELU, 1 << 26) \
    TC_FUSION_TYPE(ADD, 1 << 25) \
    TC_FUSION_TYPE(RELU2, 1 << 24) \
    TC_FUSION_TYPE(MUL, 1 << 23) \
    TC_FUSION_TYPE(LUT, 1 << 22) \
    TC_FUSION_TYPE(D2S, 1 << 20) \
    TC_FUSION_TYPE(RESCALE, 1 << 19) \
    TC_FUSION_TYPE(PCQRESCALE, 1 << 18) \
    TC_FUSION_TYPE(CLAMP, 1 << 17) \
    TC_FUSION_TYPE(CONV, 1 << 16) \
    TC_FUSION_TYPE(HASBIAS_FLAG, 1 << 15) \
    TC_FUSION_TYPE(STREAM_PROCESS0, 1 << 14) \
    TC_FUSION_TYPE(STREAM_PROCESS1, 1 << 13) \
    TC_FUSION_TYPE(STREAM_PROCESS2, 1 << 12) \


#define TC_IS_FUSE(NAME, data)   \
    ((0 == (data[0] & (0x00000001 << (31 - TC_FUSION_ID_##NAME - 8)))) ? tcFALSE : tcTRUE)

#define TC_FUSION_VERSION(data, ver)   \
    { \
        data[0] = ((0x000000ff & ver) << 24); \
    }

// uint data[0-1], feature bytes are [1~4], skip byte 0
#define TC_FUSION_TRANSPOSE_INPUT_LAYOUT(data)   \
    { \
        data[0] |= (0x00000001 << (31 - TC_FUSION_ID_TRANSPOSE_INPUT_LAYOUT - 8)); \
    }

#define TC_FUSION_RELU_1(data)   \
    { \
        data[0] |= (0x00000001 << (31 - TC_FUSION_ID_RELU_1 - 8)); \
    }

// Only support ksize 2x2 or 3x3, stride 2x2
#define TC_FUSION_POOLING(data, ksize, stride, pad_top, pad_bottom, pad_left, pad_right, pool_type)  \
    __static_assert(ksize == 2 || ksize == 3, invalid_ksize_for_max_pooling_2d); \
    { \
        const int p = (ksize == 3); \
        const int q = (stride == 2); \
        data[0] |= (0x00000001 << (31 - TC_FUSION_ID_POOLING - 8)); \
        data[1] |= p; \
        data[1] |= q << 1; \
        data[1] |= type << 2; \
        data[14] = (pad_top & 0xff) << 24; \
        data[14] |= (pad_left & 0xff) << 16; \
        data[14] |= (pad_right & 0xff) << 8; \
        data[14] |= pad_bottom & 0xff; \
    }

#define TC_FUSION_PRELU(data)   \
    { \
        data[0] |= (0x00000001 << (31 - TC_FUSION_ID_PRELU - 8)); \
    }

#define TC_FUSION_LEAKY_RELU(data)   \
    { \
        data[0] |= (0x00000001 << (31 - TC_FUSION_ID_LEAKY_RELU - 8)); \
    }

#define TC_FUSION_ADD(data)   \
    { \
        data[0] |= (0x00000001 << (31 - TC_FUSION_ID_ADD - 8)); \
    }

#define TC_FUSION_RELU_2(data)   \
    { \
        data[0] |= (0x00000001 << (31 - TC_FUSION_ID_RELU_2 - 8)); \
    }

#define TC_FUSION_MUL(data)   \
    { \
        data[0] |= (0x00000001 << (31 - TC_FUSION_ID_MUL - 8)); \
    }

#define TC_FUSION_LUT(data)   \
    { \
        data[0] |= (0x00000001 << (31 - TC_FUSION_ID_LUT - 8)); \
    }

#define TC_FUSION_TRANSPOSE_OUTPUT_LAYOUT(data)   \
    { \
        data[0] |= (0x00000001 << (31 - TC_FUSION_ID_TRANSPOSE_OUTPUT_LAYOUT - 8)); \
    }

#define TC_FUSION_RESCALE(data) \
    { \
        data[0] |= (0x00000001 << (31 - TC_FUSION_ID_RESCALE - 8)); \
    }

#define TC_FUSION_RESCALE_PCQ(data) \
    { \
        data[0] |= (0x00000001 << (31 - TC_FUSION_ID_RESCALE_PCQ - 8)); \
    }

#define TC_FUSION_DEPTH2SPACE(data, block_size_h, block_size_w)   \
    { \
        data[0] |= (0x00000001 << (31 - TC_FUSION_ID_DEPTH2SPACE - 8)); \
        data[13] = block_size_h & 0xff; \
        data[13] |= (block_size_w & 0xff) << 8; \
    }

#define TC_FUSION_CLAMP(data)   \
    { \
        data[0] |= (0x00000001 << (31 - TC_FUSION_ID_CLAMP - 8)); \
    }

#define TC_FUSION_CONV(data)   \
   { \
       data[0] |= (0x00000001 << (31 - TC_FUSION_ID_CONV - 8)); \
   }

#define TC_FUSION_HASBIAS_FLAG(data)   \
   { \
       data[0] |= (0x00000001 << (31 - TC_FUSION_ID_HASBIAS_FLAG - 8)); \
   }

#define TC_FUSION_IS_PCQ_FLAG(data)   \
   { \
       data[0] |= (0x00000001 << (31 - TC_FUSION_ID_IS_PCQ_FLAG - 8)); \
   }

#define TC_STREAM_PROCESS0(data)   \
    { \
        data[15] = TC_ID_STREAM_PROCESS0; \
    }

#define TC_STREAM_PROCESS1(data)   \
    { \
        data[15] = TC_ID_STREAM_PROCESS1; \
    }

#define TC_STREAM_PROCESS2(data)   \
    { \
        data[15] = TC_ID_STREAM_PROCESS2; \
    }

#define TC_STREAM_PROCESS_ATTRIBUTES_ARRAY(data, addr)    \
    { \
        data[11] = addr; \
    }

#define TC_STREAM_PROCESS_ATTRIBUTES_ENABLE(data, addr)    \
    { \
        data[12] = addr; \
    }

typedef enum _TC_FUSION_TYPE
{
    TC_FUSION_TYPE_ENUMS
}TC_FUSION_TYPE;

typedef enum _tc_sw_option_feature
{
    TC_OPTION_NN_INTERLEVE8,
    TC_OPTION_NN_ZDP3,
    TC_OPTION_NN_ZDP6,
    TC_OPTION_NN_XYDP9,
    TC_OPTION_NN_XYDP6,
    TC_OPTION_NN_XYDP0,
    TC_OPTION_NN_TF_QUANTIZATION,
    TC_OPTION_NN_FIRST_PIXEL_POOLING,
    TC_OPTION_NN_COEF_COMPRESSION_ENHANCEMENT,
    TC_OPTION_NN_DEPTHWISE_SUPPORT,
    TC_OPTION_SUPPORT_STREAMPROCESSOR,
    TC_OPTION_NN_SH_IN_PARALLEL,
    TC_OPTION_NN_TRANSPOSE,
    TC_OPTION_NN_NATIVE_STRIDE_TWO,
    TC_OPTION_NN_SUPPORT_CONV1x1_AND_NATIVE_CONV_STRIDE2,
    TC_OPTION_ASYMMETRIC_INT8,
    TC_OPTION_VIP_FINAL_RELEASE,
    TC_OPTION_NN_COEF_DECOMPRESS_BYPASS,
    TC_OPTION_NN_TENSOR_ADD,
    TC_OPTION_NN_SUPPORT_ALU_TENSOR_MULTI,
    TC_OPTION_TRANSPOSE_PHASE2,
    TC_OPTION_SMALLBATCH_PHASE1,
    TC_OPTION_SMALL_BATCH_PHASE2,
    TC_OPTION_ENHANCED_MAX_POOLING,
    TC_OPTION_NN_RINGBUFFER,
    TC_OPTION_TILE_ACCESS_CAPABILITY,
    TC_OPTION_NN_COMMAND_LOOP,
    TC_OPTION_NN_CONV_CORE_BYPASS,
    TC_OPTION_VIP_SUPPORT_TENSOR_TRANSFER,
    TC_OPTION_NN_TILE_BRICK_MODE,
    TC_OPTION_BIT_NN_TF32_MAC,
    TC_OPTION_NN_STRIDE2_FAST_XDP3,
    TC_OPTION_NN_SMALL_BATCH_PHASE2,
    TC_OPTION_NN_FLOAT32_IO,
    TC_OPTION_HW_V83,
    TC_OPTION_FASTXDP3_ONLY_IN_DEPTHWISE_FIX,
    TC_OPTION_FIX_11PK_NO_POOLING_NEWIMGRD_ADDR_FIX,
    TC_OPTION_NN_2ND_IMG_SMALL_3D_TILE_FIX,
    TC_OPTION_NN_CONV_1D_16BIT_FORMAT_INTILE_SIZE_LIMITATION_FIX,
    TC_OPTION_NN_TILE_YSIZE_127_LIMITATION_FIX,
    TC_OPTION_NN_VIPSRAM_DOUBLE_BUFFER_FIX,
    TC_OPTION_V83_INTILESIZE_1X1_10BITS_FIX,
    TC_OPTION_NN_SUPPORT_CONFIGURABLE_FASTXDP3,
    TC_OPTION_NN_PICOCORE_DEPTHWISE,
    TC_OPTION_TILESIZE_LIMITATION_CORE_BYPASS_FIX,
    TC_OPTION_LATENCY_HIDING_AT_FULL_AXI_BW,
    TC_OPTION_NN_FP8_PHASE1,
    TC_OPTION_NN_HIGH_PERF_DECODER,
    TC_OPTION_NN_ENHANCED_MAX_POOLING,
    TC_OPTION_NN_SP_EXEC_COUNT,
    TC_OPTION_SP_VECTOR_DEPTH,
    TC_OPTION_NN_LANES_PER_OUT_CYCLE,
    TC_OPTION_PHYSICAL_VIP_SRAM_WIDTH_IN_BYTE,
    TC_OPTION_AXI_BUS_WIDTH,
    TC_OPTION_DDR_KERNEL_BURST_SIZE,
    TC_OPTION_NN_MAD_PER_CORE,
    TC_OPTION_NN_SUPPORT_ZDP_LOOP6,
    TC_OPTION_NN_LOOP1_DP_NUMBER,
    TC_OPTION_NN_ACCUM_BUFFER_DEPTH,
    TC_OPTION_MAX_TILE_X_SIZE,
    TC_OPTION_NN_PREPROCESSOR_MAX_SEGMENT_PER_CYCLE,
    TC_OPTION_NN_IN_LINES_PER_CYCLE,
    TC_OPTION_FAST_DP3_PREPROCESSOR,
    TC_OPTION_NN_CORE_COUNT,
    TC_OPTION_NN_CORE_COUNT_INT8,
    TC_OPTION_NN_CORE_COUNT_INT16,
    TC_OPTION_NN_CORE_COUNT_UINT16,
    TC_OPTION_NN_CORE_COUNT_FLOAT16,
    TC_OPTION_NN_CORE_COUNT_BFLOAT16,
    TC_OPTION_NN_2ND_IMAGE_TILE_LIMIT_1024B_FIX,
    TC_OPTION_NN_TF32_MAC,
    TC_OPTION_NN_KERNEL_FIFO_IN_WIDTH,
    TC_OPTION_FIX_PRE_CORE_LOTS_ZEROSKIP_KERNEL_FURTHER_FIX,
    TC_OPTION_USE_VIPSRAM_FOR_KERNEL_STREAMING,
    TC_OPTION_DECOMP_VZ_GROUP_BITS,
    TC_OPTION_NN_COEF_DECOMPRESS_PERF_X,
    TC_OPTION_NN_CONV_INT16X8BIT_VIP_V7,
    TC_OPTION_NN_2V4_STRUCTURED_SPARSITY,
    TC_OPTION_BFLOAT_COEF_COMPRESSION_ZERO_COEFBIT14_INVERSE,
    TC_OPTION_BFP_COEF_AUTO_PAD_INCOMPLETE_ZERO_IN_KZ_PLANE,
    TC_OPTION_SPECIAL_8BIT_SIGN_ABS_CONV,
    TC_OPTION_NN_SINGLE_POSTMULT_FIELDS_IN_BITSTREAM,
    TC_OPTION_NN_SUPPORT_FUSA,
    TC_OPTION_NN_SUPPORT_KERNEL_1BYTE_ALIGN,
    TC_OPTION_NN_FLOAT_POST_MULT,
    TC_OPTION_FIX_PRE_CORE_LOTS_ZEROSKIP_KERNEL_FIX,
    TC_OPTION_NN_GROUP_QUANT_PHASE1,
    TC_OPTION_NN_BF16_I4_I8_QUANTIZATION,
    TC_OPTION_VIP_VERSION,
    TC_OPTION_NN_COMMAND_BUFFER_SIZE,
    TC_OPTION_NN_VIRTUAL_ADDRESS_BITS,
    TC_OPTION_NN_PHYSICAL_ADDRESS_BITS,
    TC_OPTION_NN_DEPTHWISE_16BIT_FORMAT,
    TC_OPTION_NN_INT16_TENSOR_ADD,
    TC_OPTION_NN_4BIT_PHASE1,
    TC_OPTION_NN_POST_OUT_SUPPORT_FP16,
    TC_OPTION_NN_POST_OUT_SUPPORT_BF16,
    TC_OPTION_NN_POST_OUT_SUPPORT_FP32,
    TC_OPTION_NN_POST_OUT_SUPPORT_INT32,
    TC_OPTION_NN_OUTPUT_CONVERT_UINT8_INT8_TO_UINT16_INT16_FIX,
    TC_OPTION_NN_SUPPORT_STREAM_PROCESSOR,
    TC_OPTION_NN_2ND_IMAGE_DATA_TYPE,
    TC_OPTION_NN_SUPPORT_16_8_QUANTIZATION,
    TC_OPTION_NN_POST_MULT_SUPPORT_FP_CONV,
    TC_OPTION_NN_SUPPORT_CONV_1D,
    TC_OPTION_MULTI_AXI_ID_IMG_KERNEL_SAME_FIX,
    TC_OPTION_FIRST_SECOND_IMG_SAME_ID_FIX,
    TC_OPTION_NN_NO_Z_LOCATION_OFFSET,
    TC_OPTION_NN_PRELU,
    TC_OPTION_NN_FIX_PRE_CORE_LOTS_ZEROSKIP_KERNEL_FIX,
    TC_OPTION_NN_SUPPORT_FP8_DOUBLE_MAC,
    TC_OPTION_TRSP2_NOT_SUPPORT_VIPSRAM_IN_XSTRIDE_IT_FETCH_XSIZE_FIX,
    TC_OPTION_COUNT,
}
tc_sw_option_feature_e;

typedef enum _tcTYPE_ACTIVATION_E
{
    TC_ACTIVATION_LOGISTIC = 0x0,
    TC_ACTIVATION_HYPERBOLIC_TAN = 0x1,
    TC_ACTIVATION_RELU = 0x2,
    TC_ACTIVATION_BRELU = 0x3,
    TC_ACTIVATION_SOFTRELU = 0x4,
    TC_ACTIVATION_ABS = 0x5,
    TC_ACTIVATION_SQUARE = 0x6,
    TC_ACTIVATION_SQRT = 0x7,
    TC_ACTIVATION_LINEAR = 0x8,
    TC_ACTIVATION_LEAKYRELU = 0x9,
    TC_ACTIVATION_RELU6 = 0xA,
    TC_ACTIVATION_RELU1 = 0xB,
    TC_ACTIVATION_RSQRT = 0xC,
    TC_ACTIVATION_LEAKYRELU_MAX_POOLING = 0xD,
    TC_ACTIVATION_SWISH = 0xE,
    TC_ACTIVATION_HSWISH = 0xF,
    TC_ACTIVATION_CUSTOM = 0x10,
    TC_ACTIVATION_SIGN_VSI = 0x12,
    TC_ACTIVATION_HSIGMOID_VSI = 0x13,
    TC_ACTIVATION_NEG_VSI = 0x14,
    TC_ACTIVATION_CLIP_VSI = 0x15,
    TC_ACTIVATION_EXP_VSI = 0x16,
    TC_ACTIVATION_SIN_VSI = 0x17,
    TC_ACTIVATION_COS_VSI = 0x18,
    TC_ACTIVATION_LOG_VSI = 0x19,
    TC_ACTIVATION_MISH_VSI = 0x1A,
    TC_ACTIVATION_GELU_VSI = 0x1B,
    TC_ACTIVATION_HGELU_VSI = 0x1C,
    TC_ACTIVATION_ELU_VSI = 0x1D,
    TC_ACTIVATION_SELU_VSI = 0x1E,
    TC_ACTIVATION_CELU_VSI = 0x1F,
    TC_ACTIVATION_RECIPROCAL_VSI = 0x20,
    TC_ACTIVATION_SOFTSIGN_VSI = 0x21,
    TC_ACTIVATION_ATAN_VSI = 0x22,
    TC_ACTIVATION_ATANH_VSI = 0x23,
    TC_ACTIVATION_ACOSH_VSI = 0x24,
    TC_ACTIVATION_INVERSE_SIGMOID_VSI = 0x25,
    TC_ACTIVATION_ROUND_VSI = 0x26,
    TC_ACTIVATION_ERF_VSI = 0x27,
    TC_ACTIVATION_USER_LUT = 0x28,
    TC_ACTIVATION_NONE = 0x29,
}tcTYPE_ACTIVATION_E; /* For future use */


typedef enum _TC_OPERATOR_TYPE
{
    TC_OPERATOR_CONV2D = 0,
    TC_OPERATOR_RELU = 1,
    TC_OPERATOR_MAX_POOLING = 2,
    TC_OPERATOR_ADD = 3,
    TC_OPERATOR_MUL = 4,
    TC_OPERATOR_USER_LUT = 5,
    TC_OPERATOR_LEAKYRELU = 6,
    TC_OPERATOR_PRELU = 7,
    TC_OPERATOR_DEPTH2SPACE = 8,
    TC_OPERATOR_MATMUL = 9,
    TC_OPERATOR_TRANSPOSE = 10,
    TC_OPERATOR_RESCALE = 11,
    TC_OPERATOR_ASYNC_COPY = 12,
}TC_OPERATOR_TYPE;

#endif
