#ifndef __tc_coef_encoder_h_
#define __tc_coef_encoder_h_

#include "tc_common.h"
#include "tc_hardware_feature.h"

#ifdef __cplusplus
extern "C" {
#endif

#define COMPRESS_DEBUG 1
#define MAX_HISTO_COUNT 256
#define MAX_SIZE_HISTO_COUNT 9
#define BF16_BIAS_SIZE 3
#define ZERO_SKIP_COUNT 9
#define SET_1_LOG (1) /*Default is 1, can be 0, 1, 2, 0 is the best (small win), but can only put in 3 bit Huffman code*/
#define SET_1_SIZE (1<<SET_1_LOG)
#define THROUGHPUT (Feature[TC_OPTION_NN_COEF_DECOMPRESS_PERF_X] == 8 ? 8 : (Feature[TC_OPTION_NN_COEF_DECOMPRESS_PERF_X] == 3 ? 3 : 2))
#define CODESYMBOLLEN (Feature[TC_OPTION_NN_COEF_DECOMPRESS_PERF_X] == 8 ? 24 : 8)
#define MAX_RUN_LENGTH (Feature[TC_OPTION_NN_LOOP1_DP_NUMBER] == 16 ? 4 : 256)
#define LOG_RUN_SIZE1 4    /*The 2nd set of run-length can have 1<<LOG_RUN_SIZE1 of run-length*/
#define HUFFMAN_CODING_TYPE_NON_RUN_LEN 0
#define HUFFMAN_CODING_TYPE_RUN_LEN 1
#define MAX_RUNLEN_SIZE (2+(1<<LOG_RUN_SIZE1)) /*allow 18 run-length in maximum.*/
#define NN_INTEGER_BIAS_BITS                27
#define NN_INTEGER_BIAS_BITS_VIP_V7         32
#define NN_INTEGER_BIAS_BITS_VIP_V7_INT16xINT8         40
#define NN_INTEGER_BIAS_BITS_VIP_V7_INT16   48
#define NN_Z_POSITION_OFFSET_BITS           24
#define NN_Z_POSITION_OFFSET_BITS_VIP_V7    32
#define NN_INTEGER_BIAS_BITS_VIP_INT16xINT8 48
#define PRINT_PER_CORE_SIZE 0
#define NUM_OF_VZ_PERCORE_LENGTH (Feature[TC_OPTION_DECOMP_VZ_GROUP_BITS])
#define DP_AMOUNT_FOR_1X1_KERNEL (Feature[TC_OPTION_NN_LOOP1_DP_NUMBER])
#define PRE_PROCESS_FASTDP3_INLINE 5
#define PRE_PROCESS_FASTDP3_LOOP_COUNT 3

typedef enum _tcCOEF_ENCODER_TYPE
{
    tcTYPE_COEF_ENCODER_INVALID = 0,
    tcTYPE_COEF_ENCODER_WEIGHTBIAS = 1,
    tcTYPE_COEF_ENCODER_POSTMULTIPLY = 1 << 1,
    tcTYPE_COEF_ENCODER_LUT = 1 << 2,
    tcTYPE_COEF_ENCODER_WEIGHTBIAS_POSTMULTI = tcTYPE_COEF_ENCODER_WEIGHTBIAS | tcTYPE_COEF_ENCODER_POSTMULTIPLY,
    tcTYPE_COEF_ENCODER_WEIGHTBIAS_LUT = tcTYPE_COEF_ENCODER_WEIGHTBIAS | tcTYPE_COEF_ENCODER_LUT,
    tcTYPE_COEF_ENCODER_WEIGHTBIAS_POSTMULTI_LUT = tcTYPE_COEF_ENCODER_WEIGHTBIAS | tcTYPE_COEF_ENCODER_POSTMULTIPLY | tcTYPE_COEF_ENCODER_LUT, /* invalid option*/
}tcCOEF_ENCODER_TYPE;

typedef struct CmpStages2Sym
{
    tcINT32 stageCode[3];
    tcINT32 bitLength[3];
    tcINT32 hideBit;
    tcINT32 size;
}CodeSymbol;

typedef struct _tc_weight_bias_huffman_cfg_s
{
    tcUINT8                                 pre_encode;         /*true means using prevEncode, prediction from previous pixel*/
    tcUINT8                                 coding_type;        /*false means no zero run length mode*/
    tcUINT8                                 bit16_flag;
    tcUINT8                                 fp16_flag;

    tcUINT8                                 version;            /*Version Number: Version.SubVersion, Now it is 1.0*/
    tcUINT8                                 run_len_table_size;
    tcUINT8                                 run_len_table[MAX_RUNLEN_SIZE];
    tcUINT8                                 map_to_huffman[LOG_RUN_SIZE1];  /*8 mapping to Huffman Symbols, each bytes take 2 mapping*/
    tcINT16                                 avg_bias;           /*The bias for*/
    tcUINT8                                 reserved;
    tcUINT8                                 shift_back;
    tcUINT32                                cmp_bit_length;     /*number of Symbols in the stream*/
}
tc_weight_bias_huffman_cfg_s, * tc_weight_bias_huffman_cfg;

typedef struct _tc_weight_bias_entropy_param_s
{
    tcINT32                                 outBest2Run[MAX_RUNLEN_SIZE];
    tcINT32                                 bestRunsSorted[MAX_RUNLEN_SIZE];
    tcINT32                                 best2Runs[SET_1_SIZE];
    tcINT32                                 freq[SET_1_SIZE + MAX_RUNLEN_SIZE];
    tcINT32                                 numBestRuns;
    tcINT32                                 freqSum;
}
tc_weight_bias_entropy_param_s, * tc_weight_bias_entropy_param;

typedef enum _tcCOEF_ENCODER_ELEMENT_TYPE
{
    tcTYPE_ELEMENT_WEIGHTBIAS = 0,
    tcTYPE_ELEMENT_LOOKUPTABLE = 1,
    tcTYPE_ELEMENT_POSTMULTIPLY = 2,
}tcCOEF_ENCODER_ELEMENT_TYPE;

typedef enum _tcCOEF_ENCODER_COMPRESS_MODE
{
    tcCOMPRESS_MODE_NONE = 0,
    tcCOMPRESS_MODE_ENCODE = 1,
    tcCOMPRESS_MODE_REORDER = 2,
}tcCOEF_ENCODER_COMPRESS_MODE;

typedef enum _tcCOEF_ENCODER_INFO_TYPE
{
    tcENCODED_DATA = 1,
    tcENCODED_SIZE = 2,
    tcCACHE_SIZE = 3,
    tcTILESIZE_KPC = 4,
    tcKERNEL_ALIGN_STREAM_SIZE = 5,
    tcKERNEL_STREAM_FULL_CACHE_SIZE = 6,
    tcKERNEL_MAX_STREAM_SIZE_PER_COER = 7,
    tcPER_CORE_SIZE = 8,
    tcIS2_4SPARSITY = 9,
}tcCOEF_ENCODER_INFO_TYPE;


typedef struct _tcCOEF_ENCODER* tcCOEF_ENCODER_PTR;
typedef struct _tcCOMPRESS_FEATURE_DATABASE tcCOMPRESS_FEATURE_DATABASE;

typedef struct _tcCREATE_COEF_ENCODER_INFO
{
    tcCOEF_ENCODER_ELEMENT_TYPE element_type; /* indicate wb/postMulti/lut to add*/
    struct
    {
        /** weight dimCount only support 3 and 4 **/
        /** 3: depthwise conv **/
        /** 4: conv **/
        tcTC_MEMORY_INFO weight;
        const tcFLOAT* weightScales;
        const tcINT32* weightZeroPoints;
        tcTC_MEMORY_INFO bias;
        const tcFLOAT* biasScales;
        const tcINT32* biasZeroPoints;
        tcBOOL isPerChannel;
    }
    tcCreateWBInfo;

    struct
    {
        const tcFLOAT* alpha;  //Prelu alpha
        tcSIZE_T filterCount;  //Prelu channel count
    }
    tcPreluAlPhaInfo;

    struct
    {
        const tcFLOAT* lutIn;
        const tcFLOAT* lutOut;
        const tcFLOAT* alpha;
        const tcFLOAT* beta;
        tcTYPE_ACTIVATION_E activationType;
        tcSIZE_T length;       // length of lutIn and lutOut
    }
    tcCreateLUTInfo;
}tcCREATE_COEF_ENCODER_INFO, * tcCREATE_COEF_ENCODER_INFO_PTR;

typedef struct _tcCOEF_ENCODER_COMPRESSION_INFO
{
    struct
    {
        TC_DATA_TYPE inputDataFormat;     // convolution's input format
        TC_DATA_TYPE outputDataFormat;    // convolution's input format
        tcFLOAT inputScale;               // convolution's input scale
        tcINT32 inputZP;                  // convolution's input zeropoint
        tcINT32 nnStride;                 // Convolution's stride
        tcINT32 encoderMode;              // Same as TC_COEF_ENCODER_MODE defined above.
        tcUINT64 convOutXSize;            // convolution's output x size
        tcUINT64 convOutYSize;            // convolution's output y size
        tcINT32 kernelsPerCore;           // kernels per core
        tcINT32 groupSize;                // group size
    }
    tcWeightBiasCompressionInfo;

    struct
    {
        TC_DATA_TYPE inputDataFormat;   // lut's input format
        tcFLOAT inputScale;               // lut's input scale
        tcINT32 inputZP;                  // lut's input zeropoint
        TC_DATA_TYPE outputDataFormat;  // lut's output format
        tcFLOAT outputScale;              // lut's output scale
        tcINT32 outputZP;                 // lut's output zeropoint
#ifdef USE_OPENVX
        tcBOOL isSPLut;               // reserved
#endif
    }
    tcFillInLUTInfo;

    struct
    {
        TC_DATA_TYPE pReluInputDataFormat;   // prelu input format
        tcFLOAT pReluInputScale;               // prelu input scale
        tcINT32 pReluInputZP;                 // prelu input zeropoint
        TC_DATA_TYPE outputDataFormat;       // final output format
        tcFLOAT outputScale;                   // final output scale
        tcINT32 outputZP;                     // final output zeropoint
    }
    tcGeneratePostMultiPlyInfo;

    struct
    {
        tcINT32 poolingSize;                    // valid if pool enabled
        tcINT32 poolingStride;                  // valid if pool enabled
    }
    tcPoolingInfo;

    struct
    {
        tcUINT64 tcProgramOptionFlag;           //refer to chapter `TC Program Option` for more details
    }
    tcProgramOption;

}tcCOEF_ENCODER_COMPRESSION_INFO, * tcCOEF_ENCODER_COMPRESSION_INFO_PTR;

// API to create struct _tcCOEF_ENCODER internal
tcSTATUS tco_CoefEncoderCreate(
    tcCOEF_ENCODER_PTR* encoder
);

// API to append neccessary info to struct _tcCOEF_ENCODER
// Extract info from tcCREATE_COEF_ENCODER_INFO, and append it to _tcCOEF_ENCODER
// Need append multiple times if you fused some layers
tcSTATUS tco_CoefEncoderAppend(
    tcCOEF_ENCODER_PTR encoder,
    const tcCREATE_COEF_ENCODER_INFO_PTR info
);

// API to destory the resource
tcSTATUS tco_CoefEncoderDestroy(
    tcCOEF_ENCODER_PTR encoder
);

// API to fetch coef_encoeder info
// Refer to tcCOEF_ENCODER_INFO_TYPE for more details
// Need enough space started from handle `data` specified by `paramterSize`
tcSTATUS tco_CoefEncoderGetInfo(
    tcCOEF_ENCODER_PTR encoder,
    const tcCOEF_ENCODER_COMPRESSION_INFO_PTR compressionInfo,
    tcUINT32    pid,                               // Identity of HW
    tcCOEF_ENCODER_INFO_TYPE info_type,            // Refer to chapter Valid output of coefEncoder
    size_t      paramterSize,
    tcPOINTER   data,                              // Output handle, type specified by info_type
    size_t*     paramterSizeRet                    // Return accurate size of data, no bigger than paramterSize
);

struct _tcCOEF_ENCODER
{
    tcCOEF_ENCODER_TYPE encoderType;

    struct
    {
        tcTC_MEMORY_INFO weight;
        const tcFLOAT* weightScales;
        const tcINT32* weightZeroPoints;
        tcTC_MEMORY_INFO bias;
        tcFLOAT* biasScales;
        tcINT32* biasZeroPoints;
        tcBOOL isDepthWise;
        tcBOOL isPerChannel;
    }
    tcWeightBias;

    struct
    {
        const tcFLOAT* alpha;
        tcSIZE_T filterCount;
    }
    tcPrelu;

    struct
    {
        const tcFLOAT* lutIn;
        const tcFLOAT* lutOut;
        const tcFLOAT* alpha;
        const tcFLOAT* beta;
        tcTYPE_ACTIVATION_E activationType;
        tcSIZE_T length;
    }
    tcLUT;

    tcUINT32_PTR lutRef;
    tcUINT32_PTR postMultiply;
    tcUINT32_PTR negativePostMultiply;
    tcPOINTER encodedData;
    tcINT32   encodedSize;
    tcINT32   cacheSize;
    TC_ARCH_PARAM tileSizeKpc;
    tcBOOL   is2_4Sparsity;
};

tcSTATUS tc_encoder(
     tcOPERATION_INFO_PTR     operation_info,
     tcUINT32                 encoder_type,
    TC_QUERY_INFO_PTR       encoded_ptr
    );

#ifdef __cplusplus
}
#endif

#endif /* __tc_coef_encoder_h_ */
