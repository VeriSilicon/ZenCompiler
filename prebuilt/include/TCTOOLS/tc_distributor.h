#pragma once
#ifndef __tc_distributor_h_
#define __tc_distributor_h_

#include "tc_common.h"

/******************************************************************************
****************************** FRAGMENT WRAP *******************************
******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

// Decouple the enum according to op later
typedef enum _TC_QUERY_TYPE_INFO
{
    TC_COEF_ENCODED_DATA    = 1,
    TC_COEF_ENCODED_SIZE    = 2,
    TC_IN_CACHE_SIZE        = 3,
    TC_OUT_CACHE_SIZE       = 4,
    TC_COEF_CACHE_SIZE      = 5,
    TC_TILE_SIZE_W          = 6,
    TC_TILE_SIZE_H          = 7,
    TC_KPC                  = 8,
    TC_IS2_4SPARSITY        = 9,

    TC_IN0_TRSP_CHANNEL     = 11,
    TC_IN1_TRSP_CHANNEL     = 12,
    TC_OUT_TRSP_CHANNEL     = 13,
    TC_COMMAND_BUFFER       = 14,
    TC_COMMAND_BUFFER_SIZE  = 15,
    /* info query */
    TC_COMMAND_ITERATION    = 16,
    TC_OUTPUT_MODE          = 17,
    /* generic query for conv*/
    /* generic query for matmul*/
    TC_MATMUL_IS_A_TRANSPOSE = 18,
    TC_MATMUL_IS_B_TRANSPOSE = 19,
    TC_MATMUL_IS_OUT_TRANSPOSE = 20,
    /* generic query for memcpy*/
    TC_IN0_BRICK_SIZE        = 21,
    TC_IN1_BRICK_SIZE        = 22,
    TC_OUT_BRICK_SIZE        = 23,
    TC_IS_PER_CHANNEL        = 24,

}TC_QUERY_TYPE_INFO;

typedef struct _TC_BUFFER
{
    TC_SPACE_MEMORY spaceMemory;
    TC_DATA_TYPE dataType;
    unsigned int size;
    unsigned long offset;
    unsigned int trsp_channel;
    unsigned int brick_size;
    unsigned int stream_size;
    tcBOOL is_cache_buffer;
    void* addr;
}TC_BUFFER;

typedef struct _TC_FRAGMENT_HANDLE
{
    TC_BUFFER buffer;
    tc_ulong4 size;
    tc_long4 stride;
    TC_DATA_TYPE dataType;
    const float* scale;
    const int* zeroPoint;
    TC_SPACE_MEMORY spaceMemory;
    size_t transposeChannel;
    size_t brick_size;
    void* addr;
    unsigned long offset;
    unsigned long startAddr; // offset
    TC_FRAGMENT_TYPE frag_type;
    uint group_size;
    uint iter_inc;
    bool isPerchannel;
}TC_FRAGMENT_HANDLE;

typedef struct
{
    uint stream_size;
    TC_SPACE_MEMORY spaceMemory;
    void* addr;
}TC_FRAGMENT_CACHE, * tc_fragment_cache_t;

typedef struct
{
    TC_DATA_TYPE dataType;
    TC_SPACE_MEMORY spaceMemory;
    unsigned int size;
    unsigned long offset;
    void* baseAddr;
}TC_CIRCULAR_BUFFER, * tc_circular_buffer_t;

typedef struct
{
    TC_SPACE_MEMORY spaceMemory;
    uint streamSize;
    uint size;
    void* addr;
}TC_CACHE_BUFFER, * tc_cache_buffer_t;


tc_buffer_t
tc_wrap_buffer(TC_SPACE_MEMORY space_spec, TC_DATA_TYPE dtype, uint size, ulong offset, uint trsp_channel, uint brick_size, uint stream_size, tcBOOL is_cache, void* address);

tc_cache_buffer_t
tc_wrap_cache_buffer(TC_SPACE_MEMORY space_spec, uint streamSize, uint size, void* address);

tc_fragment_handle_t
tc_buffer_get_fragment(tc_ulong4 size, tc_long4 stride, float* scale, int* zero_point, int group_size,
    tc_cache_buffer_t tc_cache_buffer, size_t offset,
    uint iter_inc, tc_buffer_t tc_buffer);

/* For vx */
tc_circular_buffer_t
tc_warp_circular(TC_SPACE_MEMORY spaceMemory, uint size, ulong offset, void* addr);

tc_fragment_handle_t
tc_circular_get_fragment(tc_ulong4 size, tc_long4 stride, TC_DATA_TYPE dataType,
    float* scale, int* zero_point,
    size_t transpose_channel, size_t brick_mode, TC_CACHE_MODE cache_mode,
    void* cache_address, size_t cache_size, size_t cache_stream_size,
    size_t offset, uint iter_inc, ushort iteration, tc_circular_buffer_t circular_buffer
);

tcHANDLE tt_conv2d(tc_fragment_handle_t input, tc_buffer_t input_cache,
    tc_fragment_handle_t* coef, tc_buffer_t coef_cache,
    size_t stride, tc_int4 padding, TC_PAD_MODE pad_mode, int pad_const,
    TC_COEF_ENCODER_MODE coef_encoder_mode, TC_CACHE_MODE coef_cache_mode,
    int tile_w, int tile_h, int kpc,
    tc_fusion_data_t fusion_data,
    tc_fragment_handle_t fusion_second_input,
    tc_fragment_handle_t output, tc_buffer_t output_cache,
    tcUINT32 chipId,
    tcUINT32 option);

tcHANDLE tt_matmul(tc_fragment_handle_t a, tc_buffer_t a_cache,
    tc_fragment_handle_t b, tc_buffer_t b_cache,
    tcBOOL tranpose_a, tcBOOL transpose_b,
    int tile_w, int tile_h, int kpc,
    ushort iteration,
    tc_fragment_handle_t out, tc_buffer_t out_cache,
    tcUINT32 pid,
    tcUINT32 option);

tcHANDLE tt_memcpy(tc_fragment_handle_t in, tc_buffer_t in_cache,
    size_t word_size,
    tc_int4 padding, int pad_const, ushort iteration,
    tc_fragment_handle_t out, tc_buffer_t out_cache,
    tcUINT32 pid);

/*FIXME: not implemented yet*/
tcHANDLE tc_async_copy(tc_fragment_handle_t in,
    tc_fragment_handle_t out,
    tcUINT32 pid);

tcSTATUS tcCompressCombDestroy(TC_QUERY_INFO_PTR encoder);

tcSTATUS tc_update_block_size(tcHANDLE tc_handle, int block_x, int block_y);

tcSTATUS tc_update_tile_and_kpc(tcHANDLE tc_handle, int tile_w, int tile_h, int kpc);

tcSTATUS tc_update_last_cmd(tcHANDLE tc_handle, int last_cmd);

tcSTATUS tc_update_program_option(tcHANDLE tc_handle, int option);

tcSTATUS tc_update_input(tcHANDLE tc_handle, tc_fragment_handle_t input, TC_OPERATOR_TYPE opkind, tcBOOL isFirstInput);

tcSTATUS tc_update_output(tcHANDLE tc_handle, tc_fragment_handle_t output, TC_OPERATOR_TYPE opkind);

tcSTATUS tc_update_coef(tcHANDLE tc_handle, tc_fragment_handle_t* coef, int size);

tcSTATUS tc_update_conv2d_param(tcHANDLE tc_handle,
    size_t stride, tc_int4 padding, TC_PAD_MODE pad_mode, int pad_const,
    TC_COEF_ENCODER_MODE coef_encoder_mode, TC_CACHE_MODE coef_cache_mode);

tcSTATUS tc_update_matmul_param(tcHANDLE tc_handle, tcBOOL is_transpose_a);

tcSTATUS tc_reset_with_update(tcHANDLE tc_handle);

tcSTATUS tc_update_handle_internal(tcHANDLE tc_handle,
    TC_UPDATE_HANDLE_E update_type,
    void*              in,
    tcSIZE_T           size);

tcSTATUS tc_update_common_caches(tcHANDLE tc_handle,
    tc_buffer_t in_cache,
    tc_buffer_t coef_cache,
    tc_buffer_t out_cache);

tcSTATUS tc_destroy_buffer(tc_buffer_t buf);

tcSTATUS tc_destroy_fragment(tc_fragment_handle_t frag);

tcSTATUS tc_destroy_handle(tcHANDLE tc_handle);

tcBOOL isValidFragmentHandle(
    tc_fragment_handle_t fragment_handle_p
);

tcSTATUS tc_get_info(
    tcHANDLE            tc_handle,
    TC_QUERY_TYPE_INFO  info_type,
    tcPOINTER           data,
    tcSIZE_T            size);

tcHANDLE
tcGetQueryTypeHandle(
    TC_QUERY_INFO_PTR   query_info,
    TC_QUERY_TYPE_INFO  query_type
);
#ifdef __cplusplus
}
#endif
#endif