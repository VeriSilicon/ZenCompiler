#ifndef _CL_VIV_TC_LIB_H
#define _CL_VIV_TC_LIB_H    1

#ifndef __static_assert
#define __static_assert(cond, msg) __assert_impl(cond, __LINE__, msg)
#define __assert_paste(msg, line) msg##line
#define __assert_impl(cond, line, msg)  \
    typedef char __assert_paste(assert_failed_##msg##_, line)[2*!!(cond)-1];
#endif

typedef enum _tc_fusion_id {
    TC_FUSION_ID_TRANSPOSE_INPUT_LAYOUT = 0,

    TC_FUSION_ID_RELU_1 = 2,
    TC_FUSION_ID_MAX_POOLING_2D = 3,
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
} tc_fusion_id;

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
#define TC_FUSION_MAX_POOLING_2D(data, ksize, stride, pad_top, pad_bottom, pad_left, pad_right)  \
    __static_assert(ksize == 2 || ksize == 3, invalid_ksize_for_max_pooling_2d); \
    { \
        const int p = (ksize == 3); \
        const int q = (stride == 2); \
        data[0] |= (0x00000001 << (31 - TC_FUSION_ID_MAX_POOLING_2D - 8)); \
        data[1] |= p; \
        data[1] |= q << 1; \
        data[14] = (pad_top & 0xff) << 24; \
        data[14] |= (pad_left & 0xff) << 16; \
        data[14] |= (pad_right & 0xff) << 8; \
        data[14] |= pad_bottom & 0xff; \
    }

#define TC_FUSION_PRELU(data, min, max)   \
    { \
        data[0] |= (0x00000001 << (31 - TC_FUSION_ID_PRELU - 8)); \
        data[3] = as_uint(min); \
        data[4] = as_uint(max); \
    }

// y = clamp(x * ((x > 0) ? pos_multiplier : neg_multiplier), min, max)
#define TC_FUSION_LEAKY_RELU(data, pos_multiplier, neg_multiplier, min, max)   \
    { \
        data[0] |= (0x00000001 << (31 - TC_FUSION_ID_LEAKY_RELU - 8)); \
        data[2] = as_uint(pos_multiplier); \
        data[3] = as_uint(neg_multiplier); \
        data[4] = as_uint(min); \
        data[5] = as_uint(max); \
    }

// y = clamp(x1 * a, min, max) + x2 * b + c
#define TC_FUSION_ADD(data, a, b, c, min, max)   \
    { \
        data[0] |= (0x00000001 << (31 - TC_FUSION_ID_ADD - 8)); \
        data[6] = as_uint(a); \
        data[7] = as_uint(b); \
        data[8] = as_uint(c); \
        data[9] = as_uint(min); \
        data[10] = as_uint(max); \
    }

#define TC_FUSION_RELU_2(data)   \
    { \
        data[0] |= (0x00000001 << (31 - TC_FUSION_ID_RELU_2 - 8)); \
    }

// y = clamp(x1 * x1_multiplier, min, max) * (x2 - x2_shift)
#define TC_FUSION_MUL(data, x1_multiplier, x2_shift, min, max)   \
    { \
        data[0] |= (0x00000001 << (31 - TC_FUSION_ID_MUL - 8)); \
        data[2] = as_uint(x1_multiplier); \
        data[3] = as_uint(x2_shift); \
        data[4] = as_uint(min); \
        data[5] = as_uint(max); \
    }

#define TC_FUSION_LUT(data)   \
    { \
        data[0] |= (0x00000001 << (31 - TC_FUSION_ID_LUT - 8)); \
    }

#define TC_FUSION_TRANSPOSE_OUTPUT_LAYOUT(data)   \
    { \
        data[0] |= (0x00000001 << (31 - TC_FUSION_ID_TRANSPOSE_OUTPUT_LAYOUT - 8)); \
    }

#define TC_FUSION_RESCALE(data, multiplier, out_shift) \
    { \
        data[0] |= (0x00000001 << (31 - TC_FUSION_ID_RESCALE - 8)); \
        data[11] = as_uint(multiplier); \
        data[12] = as_uint(out_shift); \
    }

#define TC_FUSION_RESCALE_PCQ(data, out_shift) \
    { \
        data[0] |= (0x00000001 << (31 - TC_FUSION_ID_RESCALE_PCQ - 8)); \
        data[11] = as_uint(out_shift); \
    }

#define TC_FUSION_DEPTH2SPACE(data, block_size_h, block_size_w)   \
    { \
        data[0] |= (0x00000001 << (31 - TC_FUSION_ID_DEPTH2SPACE - 8)); \
        data[13] = block_size_h & 0xff; \
        data[13] |= (block_size_w & 0xff) << 8; \
    }

#define TC_FUSION_CLAMP(data, min, max)   \
    { \
        data[0] |= (0x00000001 << (31 - TC_FUSION_ID_CLAMP - 8)); \
        data[4] = as_uint(min); \
        data[5] = as_uint(max); \
    }

#endif
