/******************************************************************************
 *                                                                            *
 * Copyright (c) 2024 by Vivante Corp.  All rights reserved.                  *
 *                                                                            *
 * The material in this file is confidential and contains trade secrets of    *
 * Vivante Corporation.  This is proprietary information owned by Vivante     *
 * Corporation.  No part of this work may be disclosed, reproduced, copied,   *
 * transmitted, or used in any way for any purpose, without the express       *
 * written permission of Vivante Corporation.                                 *
 *                                                                            *
 ******************************************************************************/
/**
 * @file tc_gpgpu_api.h
 * @brief tensor core api
 * @details There are four kinds of typical class(*_parameter, tc_buffer, tc_fragment, tc_operation) interface
 * @version 1.0.0
 * @date 2024-11
 */

#ifndef __tc_gpgpu_api_h_
#define __tc_gpgpu_api_h_

#include "tc_types.h"
#include <vector>
#include <memory>

/******************************************************************************
***************************** gpgpu customized APIs ***************************
******************************************************************************/
namespace vsi {
namespace tensorcore {
namespace tools {

/**
 * @cond
 *
 */
template<typename T>
class tc_vector_impl;
/**
 * @endcond
 *
 */

 /**
  * @brief conv2d_param
  *
  */
class conv2d_param {
public:
    /**
    * @brief Define the parameter of constructor
    * @
    * @param stride convolution stride, width and height must be the same value, only support 1 and 2
    * @param padding stands for the input padding pixels with [top, left, bottom, right], range is [-16, 15]
    * @param pad_mode only support TC_PAD_MODE_CONST
    * @param pad_const pad value
    * @param coef_encoder_mode coef encoded mode
    * @param coef_cache_mode where the coef body is stored
    * @param output_mode see details
    * @param iteration co-work with fragment's iter_inc to calculate address
    * @param block_x block size x of depth2space (conv2d fuse d2s is conflict with TRSP1 layout of output)
    * @param block_y block size y of depth2space (conv2d fuse d2s is conflict with TRSP1 layout of output)
    */
    TC_API_ENTRY conv2d_param(
        tcUINT32        stride,
        tc_int4         padding,
        TC_PAD_MODE     pad_mode,
        tcINT32         pad_const,
        TC_COEF_ENCODER_MODE coef_encoder_mode,
        TC_CACHE_MODE coef_cache_mode,
        TC_FP_CLASSIFY  output_mode,
        tcUINT32        iteration,
        tcUINT32        block_x,
        tcUINT32        block_y);

    /**
    * @brief Define the parameter of constructor
    * @
    * @param stride convolution stride, width and height must be the same value, only support 1 and 2
    * @param padding stands for the input padding pixels with [top, left, bottom, right], range is [-16, 15]
    * @param pad_mode only support TC_PAD_MODE_CONST
    * @param pad_const pad value
    * @param coef_encoder_mode coef encoded mode
    * @param coef_cache_mode where the coef body is stored
    * @param output_mode see details
    * @param iteration co-work with fragment's iter_inc to calculate address
    */
    TC_API_ENTRY conv2d_param(
        tcUINT32        stride,
        tc_int4         padding,
        TC_PAD_MODE     pad_mode,
        tcINT32         pad_const,
        TC_COEF_ENCODER_MODE coef_encoder_mode,
        TC_CACHE_MODE   coef_cache_mode,
        TC_FP_CLASSIFY  output_mode,
        tcUINT32        iteration);

    /**
    * @brief disable 2_4 sparity
    * @attention toolKits will encode coef with 2_4_sparity if possible, but programmer can disable 2_4_sparity
    */
    TC_API_ENTRY void disable_2_4_sparity() { _enable_2_4_sparity = false; };

    /**
     * @cond
     *
     */
    /**
     * @brief Get the nn stride of conv2d
     */
    tcUINT32 get_stride() const {return _stride;};

    /**
     * @brief Get the padding of conv2d
     */
    tc_int4 get_padding() const {return _padding;};

    /**
     * @brief Get the pad mode of conv2d, only support pad with const
     */
    TC_PAD_MODE get_pad_mode() const {return _pad_mode;};

    /**
     * @brief Get the pad const value
     */
    tcINT32 get_pad_const() const {return _pad_const;};

    /**
     * @brief Get the coef encoder mode of conv2d
     */
    TC_COEF_ENCODER_MODE get_coef_encoder_mode() const {return _coef_encoder_mode;};

    /**
     * @brief Get the coef cache mode of conv2d
     */

    TC_CACHE_MODE get_coef_cache_mode() const {return _coef_cache_mode;};

    /**
     * @brief Get the output mode of conv2d
     */
    TC_FP_CLASSIFY get_output_mode() const {return _output_mode;};

    /**
     * @brief Get the iteration of conv2d
     */
    tcUINT32 get_iteration() const {return _iteration;};

    tcUINT32 get_block_x() const {return _block_x;};

    tcUINT32 get_block_y() const {return _block_y;};
    /**
     * @endcond
     *
     */
private:
    tcUINT32    _stride;
    tc_int4     _padding;
    TC_PAD_MODE _pad_mode;
    tcINT32     _pad_const;
    tcUINT32    _iteration;
    tcUINT32    _block_x;
    tcUINT32    _block_y;
    TC_COEF_ENCODER_MODE _coef_encoder_mode;
    TC_CACHE_MODE _coef_cache_mode;
    tcBOOL      _enable_2_4_sparity;
    TC_FP_CLASSIFY _output_mode;
};

/**
 * @brief matmul_param
 *
 */
class matmul_param {
public:
    /**
     * @brief Construct a new matmul param object
     *
     * @param transpose_a transpose input a
     * @param transpose_b transpose input b, not support yet
     * @param iteration   co-work with fragment's iter_inc to calculate address
     * @param output_mode see details
     */
    TC_API_ENTRY matmul_param(tcBOOL transpose_a, tcBOOL transpose_b, tcUINT32 iteration, TC_FP_CLASSIFY output_mode);

    /**
     * @cond
     *
     */

    /**
     * @brief If input a of matmul transpose, return true
     */
    tcBOOL get_transpose_a()const { return _transpose_a; };
    /**
     * @brief If input b of matmul transpose, return true. Not support yet
     */
    tcBOOL  get_transpose_b()const { return _transpose_b; };
    tcUINT32 get_iteration()const { return _iteration; };
    TC_FP_CLASSIFY get_output_mode()const {return _output_mode;};
    /**
     * @endcond
     *
     */
private:
    tcBOOL      _transpose_a;
    tcBOOL      _transpose_b;
    tcUINT32    _iteration;
    TC_FP_CLASSIFY _output_mode;
};

/**
 * @brief memcpy_param
 *
 */
class memcpy_param
{
public:
    /**
     * @brief memcpy_param
     *
     * @param word_size word size of memcpy
     * @param padding   padding
     * @param pad_const  pad const value
     * @param iteration  iteration
     */
    TC_API_ENTRY memcpy_param(tcINT32 word_size, tc_int4 padding, tcINT32 pad_const, tcUINT32 iteration);
    /**
     * @cond
     *
     */
    tcUINT32 get_word_size() const;
    tc_int4  get_padding() const;
    tcINT32  get_pad_const() const;
    tcUINT32 get_iteration() const;
    /**
     * @endcond
     *
     */
private:
    tcINT32     _word_size;
    tc_int4     _padding;
    tcINT32     _pad_const;
    tcUINT32    _iteration;
};

/**
 * @brief tc_buffer
 *
 */
class tc_buffer {
public:
    /**
     * @brief Construct an empty tc buffer object
     * @attention programmer can apply this statement when cannot decide where cache buffer locate
     */
    TC_API_ENTRY tc_buffer();
    /**
     * @brief Construct a tc buffer object
     * @pre sdk allocate global memory always 64 bytes alignment
     * @param space_spec TC_SPACE_SPEC_GLOBAL or TC_SPACE_SPEC_LOCAL
     * @param dtype      data type
     * @param size       buffer size, must be aligned to 64 bytes(global memory) or 256 bytes(local memory)
     * @param offset     offset to the address, must be aligned to 64 bytes(global memory) or 256 bytes(local memory). In one word: buffer range: [(char*)address + offset, (char*)address + offset + size), and hardware access with circular
     * @param address    buffer logical address, corresponding physical address must be aligned to 64 bytes(global memory) or 256 bytes(local memory)
     */
    TC_API_ENTRY tc_buffer(TC_SPACE_MEMORY space_spec, TC_DATA_TYPE dtype, tcUINT64 size, tcUINT64 offset, void* address);
    /**
     * @brief Construct a tc buffer object
     * @pre sdk allocate global memory always 64 bytes alignment
     * @param space_spec TC_SPACE_SPEC_GLOBAL or TC_SPACE_SPEC_LOCAL
     * @param dtype      data type
     * @param size       buffer size, must be aligned to 64 bytes(global memory) or 256 bytes(local memory)
     * @param offset     offset to the address, must be aligned to 64 bytes(global memory) or 256 bytes(local memory). In one word: buffer range: [(char*)address + offset, (char*)address + offset + size), and hardware access with circular
     * @param address    buffer logical address, corresponding physical address must be aligned to 64 bytes(global memory) or 256 bytes(local memory), const value
     */
    TC_API_ENTRY tc_buffer(TC_SPACE_MEMORY space_spec, TC_DATA_TYPE dtype, tcUINT64 size, tcUINT64 offset, const void* address);

    /**
     * @brief Performance interface: Construct a tc buffer object supporting TRSP layout or BANK-BRICK layout
     *        Programmer need to create normal tc_buffer and get trsp_size array or brick_size after tc_operation object created
     *        Then update fragment by re-creating tc_buffer with proper trsp_size or brick_size
     * @image latex channel-first.png "Channel-First(Default) Mode" width=300px
     * @image latex trsp.png "TRSP Mode" width=400px
     * @image latex bank_brick.png "Bank-Brick Mode" width=480px
     * @overload
     * @pre sdk allocate global memory always 64 bytes alignment
     * @param space_spec   TC_SPACE_SPEC_GLOBAL or TC_SPACE_SPEC_LOCAL
     * @param dtype        data type
     * @param size         buffer size, must be aligned to 64 bytes(global memory) or 256 bytes(local memory)
     * @param trsp_size    transpose size of TRSP layout
     * @param brick_size   brick size of BANK-BRICK layout
     * @param offset       offset to the address, must be aligned to 64 bytes(global memory) or 256 bytes(local memory). In one word: buffer range: [(char*)address + offset, (char*)address + offset + size), and hardware access with circular
     * @param address      buffer address, must be aligned to 64 bytes(global memory) or 256 bytes(local memory)
     */
    TC_API_ENTRY tc_buffer(TC_SPACE_MEMORY space_spec, TC_DATA_TYPE dtype, tcUINT64 size, tcUINT32 trsp_size, tcUINT32 brick_size, tcUINT64 offset, void* address);
    /**
     * @brief Performance interface: Construct a tc buffer object supporting TRSP layout or BANK-BRICK layout
     *        Programmer need to create normal tc_buffer and get trsp_size array or brick_size after tc_operation object created
     *        Then update fragment by re-creating tc_buffer with proper trsp_size or brick_size
     * @image latex channel-first.png "Channel-First(Default) Mode" width=300px
     * @image latex trsp.png "TRSP Mode" width=400px
     * @image latex bank_brick.png "Bank-Brick Mode" width=480px
     * @overload
     * @pre sdk allocate global memory always 64 bytes alignment
     * @param space_spec   TC_SPACE_SPEC_GLOBAL or TC_SPACE_SPEC_LOCAL
     * @param dtype        data type
     * @param size         buffer size, must be aligned to 64 bytes(global memory) or 256 bytes(local memory)
     * @param trsp_size    transpose size of TRSP layout
     * @param brick_size   brick size of BANK-BRICK layout
     * @param offset       offset to the address, must be aligned to 64 bytes(global memory) or 256 bytes(local memory). In one word: buffer range: [(char*)address + offset, (char*)address + offset + size), and hardware access with circular
     * @param address      buffer address, must be aligned to 64 bytes(global memory) or 256 bytes(local memory), const address value
     */
    TC_API_ENTRY tc_buffer(TC_SPACE_MEMORY space_spec, TC_DATA_TYPE dtype, tcUINT64 size, tcUINT32 trsp_size, tcUINT32 brick_size, tcUINT64 offset, const void* address);

    /**
     * @brief Performance interface: Construct a tc cache buffer object for input and output
     * @overload
     * @param space_spec  cache buffer must be TC_SPACE_SPEC_LOCAL
     * @param size        buffer size, must be aligned to 256 bytes(local memory)
     * @param offset      offset to the address, must be aligned to 256 bytes(local memory)
     */
    TC_API_ENTRY tc_buffer(TC_SPACE_MEMORY space_spec, tcUINT64 size, tcUINT64 offset); /* cache */
    /**
     * @brief Performance interface: Construct a tc cache buffer object for coef
     * @image latex coef_cache.png "Coef Cache" width=400px
     * @param space_spec              cache buffer must be TC_SPACE_SPEC_LOCAL
     * @param size                    buffer size, must be aligned to 256 bytes(local memory)
     * @param coef_encoded_body_size  data bit stream size of coef encoded body
     * @param offset                  offset to the address, must be aligned to 256 bytes(local memory)
     */
    TC_API_ENTRY tc_buffer(TC_SPACE_MEMORY space_spec, tcUINT64 size, tcUINT64 coef_encoded_body_size, tcUINT64 offset);

    /**
     * @cond
     */
    tc_buffer_t get_buffer() const;
    /**
     * @endcond
     */

    /**
     * @brief Get the trsp size object
     * @return tcUINT32 trsp size
     */
    TC_API_ENTRY tcUINT32 get_trsp_size() const;
    /**
     * @brief Get the brick size object
     * @return tcUINT32 brick size
     */
    TC_API_ENTRY tcUINT32 get_brick_size() const;

private:
    class Impl;
    std::shared_ptr<Impl> _buffer_impl;
};

/**
 * @brief tc_fragment
 *
 */
class tc_fragment {
public:
    /**
     * @brief Construct a tc fragment object
     * @param size tensor shape, always follow [N, C, H, W]
     * @param stride tensor stride, always follow [N, C, H, W]
     * @param scale tensor quant parameter
     * @param zero_point tensor quant parameter
     * @param offset offset to the tc_buffer, it must be less than tc_buffer->size
     * @param iter_inc co-work with tc_operation to calcalate the real data access address. Hardware access start address is (char*)tc_buffer->address + tc_buffer->offset + offset + iter_inc * tc_operation->iteration
     * @param tc_buffer memory object
     */
    TC_API_ENTRY tc_fragment(const std::vector<tcUINT64> &size, const std::vector<tcUINT64> &stride,
        const std::vector<float> &scale, const std::vector<int> &zero_point,
        tcUINT64 offset, tcUINT32 iter_inc,
        tc_buffer &tc_buffer);
    /**
     * @brief Construct a tc fragment object
     * @param size tensor shape, always follow [N, C, H, W]
     * @param stride tensor stride, always follow [N, C, H, W]
     * @param scale tensor quant parameter
     * @param zero_point tensor quant parameter
     * @param offset offset to the tc_buffer, it must be less than tc_buffer->size
     * @param iter_inc co-work with tc_operation to calcalate the real data access address. Hardware access start address is (char*)tc_buffer->address + tc_buffer->offset + offset + iter_inc * tc_operation->iteration
     * @param tc_buffer memory object
     * @param type fragment type should be specified, if fragment is weight, bias, prelu alpha, lut in/out
     */
    TC_API_ENTRY tc_fragment(const std::vector<tcUINT64> &size, const std::vector<tcUINT64> &stride,
        const std::vector<float> &scale, const std::vector<int> &zero_point,
        tcUINT64 offset, tcUINT32 iter_inc,
        tc_buffer &tc_buffer, TC_FRAGMENT_TYPE type);

    /**
     * @brief Construct a new tc fragment object
     *
     * @param size tensor shape, always follow [N, C, H, W]
     * @param stride tensor stride
     * @param scale tensor quant parameter
     * @param zero_point tensor quant parameter
     * @param group_size group size of group quantlization
     * @param offset offset to the tc_buffer, it must be less than tc_buffer->size
     * @param iter_inc co-work with tc_operation to calcalate the real data access address. Hardware access start address is (char*)tc_buffer->address + tc_buffer->offset + offset + iter_inc * tc_operation->iteration
     * @param tc_buffer memory object
     * @param type fragment type should be specified, if fragment were weight, bias, prelu alpha, lut in/out
     */
    TC_API_ENTRY tc_fragment(const std::vector<tcUINT64> &size, const std::vector<tcUINT64> &stride,
        const std::vector<float> &scale, const std::vector<int> &zero_point,
        tcUINT32 group_size, tcUINT64 offset, tcUINT32 iter_inc,
        tc_buffer &tc_buffer, TC_FRAGMENT_TYPE type);

    /**
    * @brief if perchannel, return true
    * @return tcBOOL TRUE: Per-channel FALSE: Not Per-channel
    */
    TC_API_ENTRY tcBOOL get_is_perchannel() const;

    /**
     * @cond
     *
     */
    /**
     * @brief Get the fragment handle
     */
    tc_fragment_handle_t get_fragment() const;
    /**
     * @endif
     *
     */

    /**
     * @brief Get the fragment type
     */
    TC_FRAGMENT_TYPE get_fragment_type() const;

    tc_buffer_t get_buffer() const;

    void set_buffer(tc_buffer& tc_buf);
    /**
     * @endcond
     *
     */
private:

    class Impl;
    std::shared_ptr<Impl> _frag_impl;
};

/**
 * @brief base class of tensore core operation
 *
 */
class tc_operation {
    virtual tcUINT32  get_cmd_buffer_size() const = 0;
    virtual void get_cmd(void* retData, tcUINT32 size) const = 0;
public:
    ~tc_operation() {};
};


/**
 * @brief tc_conv2d
 *
 */
class tc_conv2d : public tc_operation {
    /**
     * # Conv2d in Verisilicon Tensor Core
     * @image latex conv_core.png "Conv2d Computation Pipeline" width=480px
     * Definition: https://pytorch.org/docs/2.3/generated/torch.nn.Conv2d.html (Not support dilation and groups) \n
     * Qi , Zi , Si  stand for quantized value, zero point and scale of input respectively \n
     * Qw , Zw , Sw  stand for quantized value, zero point and scale of weight respectively \n
     * Qo , Zo , So  stand for quantized value, zero point and scale of output respectively \n
     * QB stands for quantized value of bias and QB' stands for new bias \n
     * Verisilicon follows biasScale = inputScale*weightScale, and abs(biasScale - inputScale*weightScale) < 10-6 is permitted
     *
    # Support data type
    * | Mode | Input | Weight | Bias | Output |
    * |:------------ |:------------ |:------------ |:------------ |:------------ |
    * | s8xs8 with int32 accumulate | int8 | int8 | int32 | int8, int16, int32 |
    * | s16xs8 with int48 accumulate | int16 | int8 | int32 | int8, int16, int32 |
    * | u8xs8 with int32 accumulate | uint8 | int8 | int32 | uint8, int32 |
    * | fp16 with fp32 accumulate | half |  half, int8, uint8 | float | half, float(bfloat16) |
    * | bf16 with fp32 accumulate | bfloat16 | bfloat16, int8, uint8 | float | bfloat16, float(bfloat16) |
    * | fp8 with fp32 accumulate | fp8_e4m3 | fp8_e4m3 |  float | fp8_e4m3, half, bfloat16 |
    * | fp8 with fp32 accumulate | fp8_e4m3 | fp8_e5m2 |  float | fp8_e4m3, fp8_e5m2, half, bfloat16 |
    * | fp8 with fp32 accumulate | fp8_e5m2 | fp8_e4m3 |  float | fp8_e4m3, fp8_e5m2, half, bfloat16 |
    * | tf32 with fp32 accumulate | float | float, int8, uint8 | float | half, float(bfloat16) |
    *
    */
public:
    /**
     * @param input         input fragment object of conv2d
     * @param input_cache   input cache buffer object of conv2d
     * @param coef          coef fragment objects of conv2d, including weight/bias
     * @param coef_cache    coef cache buffer object of conv2d
     * @param output        output fragment object of conv2d
     * @param output_cache  output cache buffer object of conv2d
     * @param param         conv2d param object
     * @param pid           customer id, query from sdk vendor
     */
    TC_API_ENTRY tc_conv2d(tc_fragment       &input,
        tc_buffer               &input_cache,
        const std::vector<tc_fragment> &coef,
        tc_buffer               &coef_cache,
        tc_fragment             &output,
        tc_buffer               &output_cache,
        conv2d_param            &param,
        tcUINT32                pid);

    /**
     * @param input         input fragment object of conv2d
     * @param input_cache   input cache buffer object of conv2d
     * @param coef          coef fragment objects of conv2d, including weight/bias
     * @param coef_cache    coef cache buffer object of conv2d
     * @param output        output fragment object of conv2d
     * @param output_cache  output cache buffer object of conv2d
     * @param param         conv2d param object
     * @param pid           customer id, query from sdk vendor
     */
    TC_API_ENTRY tc_conv2d(tc_fragment& input,
        tc_buffer              &input_cache,
        const std::vector<tc_fragment>&& coef,
        tc_buffer               &coef_cache,
        tc_fragment             &output,
        tc_buffer               &output_cache,
        conv2d_param            &param,
        tcUINT32                pid);

    /**
     * @cond
     */
    TC_API_ENTRY ~tc_conv2d();
    /**
     * @endcond
     */

    /**
     * @return tile [tile_w tile_h]
     * @attention This functions must be called and transfer correspongding value into kenrel, or result is undefined
     */
    TC_API_ENTRY std::vector<tcUINT32> get_tile_size() const;

    /**
     * @return the kernels per core of conv2d
     * @attention This functions must be called and transfer correspongding value into kenrel, or result is undefined
     */
    TC_API_ENTRY tcUINT32 get_kpc() const;

    /**
     * @return the encoded bitstream size
     * @attention This functions must be called and transfer correspongding value into kenrel, or result is undefined
     */
    TC_API_ENTRY tcUINT64 get_coef_encoded_size() const;

    /**
    * @brief if perchannel, return true
    * @return tcBOOL TRUE: Per-channel FALSE: Not Per-channel
    */
    TC_API_ENTRY tcBOOL get_is_perchannel() const;

    /**
     * @return tcBOOL TRUE: enable, FALSE: disable
     * @attention This functions must be called and transfer correspongding value into kenrel, or result is undefined
     */
    TC_API_ENTRY tcBOOL get_is_2_4_sparsity_enable() const;

    /**
     * @brief get the encoded bitstream
     * @param retData encoding coef into the pointer
     * @param size memory size of retData pointer
     * @return tcSTATUS
     * @attention This functions must be called and transfer correspongding value into kenrel, or result is undefined \
     * Programmer should allocate larger size than get_coef_encoded_size
     */
    TC_API_ENTRY tcSTATUS get_coef_encoded_data(void* retData, tcUINT64 size) const;

    /**
     * @return the input cache size, programmer need allocate local memory in kernel
     * @attention This functions must be called and transfer correspongding value into kenrel, or result is undefined
     */
    TC_API_ENTRY tcUINT32 get_input_cache_size() const;

    /**
     * @return the output cache size, programmer need allocate local memory in kernel
     * @attention This functions must be called and transfer correspongding value into kenrel, or result is undefined
     */
    TC_API_ENTRY tcUINT32 get_output_cache_size() const;

    /**
     * @return the coef full cache size which is encoded body size, programmer need allocate proper local memory in kernel, due to partial cache support
     * @attention This functions must be called and transfer correspongding value into kenrel, or result is undefined
     */
    TC_API_ENTRY tcUINT32 get_coef_encoded_body_size() const;

    /**
     * @brief set tile size of conv2d
     * @param tile [tile_w tile_h]
     * @attention Performance interface, update operation parameters
     */
    TC_API_ENTRY void set_tile_size(const std::vector<tcUINT32> &tile);

    /**
     * @brief set kernels per core of conv2d
     * @param kpc Performance interface to update operation parameters
     */
    TC_API_ENTRY void set_kpc(const tcUINT32 kpc);
    /**
     * @brief Set the input of conv2d
     * @param frag update input fragment
     */
    TC_API_ENTRY void set_input(tc_fragment &frag);
    /**
     * @brief Set the coef object
     * @param frag update coef(weight/bias...) fragments
     */
    TC_API_ENTRY void set_coef(std::vector<tc_fragment> &frag);
    /**
     * @brief Set the output object
     * @param frag update output fragment
     */
    TC_API_ENTRY void set_output(tc_fragment &frag);
    /**
     * @brief Set the param object
     * @param param update conv2d param object
     */
    TC_API_ENTRY void set_param(conv2d_param &param);

    /**
     * @return The proper brick size to do performance optimization
     * @attention Programmers need to update corresponding buffer if feature enable
    */
    TC_API_ENTRY tcUINT32 get_proper_input_brick_size() const;

    /**
     * @return The proper brick size to do performance optimization
     * @attention Programmers need to update corresponding buffer if feature enable
    */
    TC_API_ENTRY tcUINT32 get_proper_output_brick_size() const;

    /**
     * @return The input proper trsp channle to do performance optimization
     * @attention Programmers need to update corresponding buffer if feature enable
    */
    TC_API_ENTRY std::vector<tcUINT32> get_proper_input_trsp_size() const;

    /**
     * @return The output proper trsp channle to do performance optimization
     * @attention Programmers need to update corresponding buffer if feature enable
    */
    TC_API_ENTRY std::vector<tcUINT32> get_proper_output_trsp_size() const;

    /**
     * @param cache_buffer update input cache buffer. If programmer program cache size larger than the one from tcToolKits, hardware performs better performance in general
     * @attention This API not support in OpenCL platform
     */
    TC_API_ENTRY void set_input_cache(tc_buffer &cache_buffer);

    /**
     * @param cache_buffer      update coef cache buffer
     * @attention This API not support in OpenCL platform
     */
    TC_API_ENTRY void set_coef_cache(tc_buffer &cache_buffer);

    /**
     * @param cache_buffer      update output cache buffer
     * @attention This API not support in OpenCL platform
     */
    TC_API_ENTRY void set_output_cache(tc_buffer &cache_buffer);

    /**
     * @param flag  TRUE: last cmd, FALSE: defalut
     * @attention This API not support in OpenCL platform
     */
    TC_API_ENTRY void set_last_cmd(const tcBOOL flag);

    /**
     * @return the tensor core command buffer size
     * @attention This API not support in OpenCL platform
     */
    TC_API_ENTRY tcUINT32 get_cmd_buffer_size() const override;

    /**
     * @param retData The pointer to store command
     * @param size The pointer buffer size
     * @attention This API not support in OpenCL platform
     */
    TC_API_ENTRY void get_cmd(void* retData, tcUINT32 size) const override;

private:

    class Impl;
    std::shared_ptr<Impl> _conv_impl;

    /**
     * @brief Set the tc progam option of conv2d, only used in saicheng1
     *
     * @param option 0: disable 1:enable
     */
    void set_tc_progam_option(const tcUINT32 option);
};

/**
 * @brief tc_matmul
 *
 */
class tc_matmul : public tc_operation{
    /**
     * # Matmul in Verisilicon Tensor Core
     * @image latex matmul.png "Convert Matmul to Conv2d Pipeline" width=480px
     * Definition: https://pytorch.org/docs/2.3/generated/torch.matmul.html \n
     # Support data type
     * | Mode | input a | input b | Output |
    * |:------------ |:------------ |:------------ |:------------ |
    * | s8xs8 with int32 accumulate | int8 | int8 | int8, int16, int32 |
    * | s16xs8 with int48 accumulate | int16 | int8 | int8, int16, int32 |
    * | u8xu8 with int32 accumulate | uint8 | uint8 | uint8, int32 |
    * | fp16 with fp32 accumulate | half |  half | half, float(bfloat16) |
    * | bf16 with fp32 accumulate | bfloat16 | bfloat16 | bfloat16, float(bfloat16) |
    * | fp8 with fp32 accumulate | fp8_e4m3 | fp8_e4m3 | fp8_e4m3, half, bfloat16 |
    * | fp8 with fp32 accumulate | fp8_e4m3 | fp8_e5m2 | fp8_e4m3, fp8_e5m2, half, bfloat16 |
    * | fp8 with fp32 accumulate | fp8_e5m2 | fp8_e4m3 | fp8_e4m3, fp8_e5m2, half, bfloat16 |
    * | tf32 with fp32 accumulate | float | float | half, float(bfloat16) |
     */
public:
    /**
     * @param a            input a fragment of matmul object
     * @param a_cache      input a cahche buffer of matmul object
     * @param b            input b fragment of matmul object
     * @param b_cache      input b cahche buffer of matmul object
     * @param output       output fragment of matmul object
     * @param output_cache output cache buffer of matmul object
     * @param param        matmul param object
     * @param pid          customer id, can query from device info
     */
    TC_API_ENTRY tc_matmul(tc_fragment   &a,
    tc_buffer               &a_cache,
    tc_fragment             &b,
    tc_buffer               &b_cache,
    tc_fragment             &output,
    tc_buffer               &output_cache,
    matmul_param            &param,
    tcUINT32                pid);

    TC_API_ENTRY ~tc_matmul();

    /**
    * @return tile [tile_w tile_h]
    * @attention This functions must be called and transfer correspongding value into kenrel, or result is undefined
    */
    TC_API_ENTRY std::vector<tcUINT32> get_tile_size() const;
    /**
     * @return the kernels per core of matmul
     * @attention This functions must be called and transfer correspongding value into kenrel, or result is undefined
     */
    TC_API_ENTRY tcUINT32 get_kpc() const;
    /**
     * @return the input b cache size of matmul, programmer need allocate local memory in kernel
     * @attention This functions must be called and transfer correspongding value into kenrel, or result is undefined
     */
    TC_API_ENTRY tcUINT32 get_b_cache_size();
    /**
     * @return the output cache size of matmul, programmer need allocate local memory in kernel
     * @attention This functions must be called and transfer correspongding value into kenrel, or result is undefined
     */
    TC_API_ENTRY tcUINT32 get_output_cache_size();

    /**
     * @return The proper brick size to do performance optimization
     * @attention Programmers need to update corresponding buffer if feature enable
    */
    TC_API_ENTRY tcUINT32 get_proper_a_brick_size() const;

    /**
     * @return The proper brick size to do performance optimization
     * @attention Programmers need to update corresponding buffer if feature enable
    */
    TC_API_ENTRY tcUINT32 get_proper_b_brick_size() const;

    /**
     * @return The proper brick size to do performance optimization
     * @attention Programmers need to update corresponding buffer if feature enable
    */
    TC_API_ENTRY tcUINT32 get_proper_output_brick_size() const;

    /**
     * @brief set tile size of matmul
     * @param tile [tile_w tile_h]
     * @attention Performance interface, update operation parameters
     */
    TC_API_ENTRY void set_tile_size(const std::vector<tcUINT32> &tile);
    /**
     * @brief set kernels per core of matmul
     * @param kpc Performance interface to update operation parameters
     */
    TC_API_ENTRY void set_kpc(const tcUINT32 kpc);
    /**
     * @brief set input a fragment of matmul
     * @param frag update a fragment
     */
    TC_API_ENTRY void set_a(tc_fragment &frag);
    /**
     * @brief set input b fragment of matmul
     * @param frag update b fragment
     */
    TC_API_ENTRY void set_b(tc_fragment &frag);
    /**
     * @brief set cache buffer of input b of matmul
     * @param cache_buffer update b cache buffer
     * @attention This API not support in OpenCL platform
     */
    TC_API_ENTRY void set_b_cache(tc_buffer &cache_buffer);
    /**
     * @brief set output fragment of matmul
     * @param frag update output fragment
     */
    TC_API_ENTRY void set_output(tc_fragment &frag);
    /**
     * @param cache_buffer      update output cache buffer
     * @attention This API not support in OpenCL platform
     */
    TC_API_ENTRY void set_output_cache(tc_buffer &cache_buffer);
    /**
     * @brief set parammeters of matmul
     * @param param update matmul param object
     */
    TC_API_ENTRY void set_param(matmul_param &param);

    /**
    * @return A set of recommended trsp size of matmul's input a
    * @attention This functions is performance interface, and programmers need to update correspong buffer if feature enable
    */
    TC_API_ENTRY std::vector<tcUINT32> get_proper_a_trsp_size() const;
    /**
    * @return A set of recommended trsp size of matmul's input b
    * @attention This functions is performance interface, and programmers need to update correspong buffer if feature enable
    */
    TC_API_ENTRY std::vector<tcUINT32> get_proper_b_trsp_size() const;
    /**
    * @return A set of recommended trsp size of matmul's output
    * @attention This functions is performance interface, and programmers need to update correspong buffer if feature enable
    */
    TC_API_ENTRY std::vector<tcUINT32> get_proper_output_trsp_size() const;

    /**
     * @param flag  TRUE: last cmd, FALSE: defalut
     * @attention This API not support in OpenCL platform
     */
    TC_API_ENTRY void set_last_cmd(const tcBOOL flag);
    /**
     * @return the tensor core command buffer size
     * @attention This API not support in OpenCL platform
     */
    TC_API_ENTRY tcUINT32 get_cmd_buffer_size() const override;
    /**
     * @param retData The pointer to store command
     * @param size The pointer buffer size
     * @attention This API not support in OpenCL platform
     */
    TC_API_ENTRY void get_cmd(void* retData, tcUINT32 size) const override;

private:
    tcBOOL   is_get_cache_preparation_ok() const;
    tcSTATUS get_cache_preparation();

    class Impl;
    std::shared_ptr<Impl> _matmul_impl;
};

/**
 * @brief tc_memcpy
 *
 */
class tc_memcpy : public tc_operation{
    /**
     * # Memcpy in Verisilicon Tensor Core
     * @image latex tc_memcpy.png "Example" width=480px  \n
     * Definition: The tc_memcpy asynchronously triggers tensor core transpose operation(Not support data type convert)
     */
public:
    /**
     * @param input         input fragment object of memcpy
     * @param input_cache   input cache buffer object of memcpy
     * @param output        output fragment objects of memcpy
     * @param output_cache  output cache buffer object of memcpy
     * @param param         memcpy param object
     * @param pid           customer id, query from sdk vendor
     */
    TC_API_ENTRY tc_memcpy(tc_fragment   &input,
    tc_buffer           &input_cache,
    tc_fragment         &output,
    tc_buffer           &output_cache,
    memcpy_param        &param,
    tcUINT32            pid);

    TC_API_ENTRY ~tc_memcpy();

    /**
    * @return Cache size of memcpy's input
    * @attention These function must be called and set correspongding value into kenrel, or result is unpredicated
    */
    TC_API_ENTRY tcUINT32 get_input_cache_size() const;
    /**
    * @return Cache size of memcpy's output
    * @attention These function must be called and set correspongding value into kenrel, or result is unpredicated
    */
    TC_API_ENTRY tcUINT32 get_output_cache_size() const;


    /**
     * @param cache_buffer      update input cache buffer
     * @attention This API not support in OpenCL platform
     */

    TC_API_ENTRY void set_input_cache(tc_buffer& cache_buffer);
    /**
     * @param cache_buffer      update output cache buffer
     * @attention This API not support in OpenCL platform
     */
    TC_API_ENTRY void set_output_cache(tc_buffer& cache_buffer);

    /**
     * @return the tensor core command buffer size
     * @attention This API not support in OpenCL platform
     */
    TC_API_ENTRY tcUINT32 get_cmd_buffer_size() const override;
    /**
     * @param retData The pointer to store command
     * @param size The pointer buffer size
     * @attention This API not support in OpenCL platform
     */
    TC_API_ENTRY void get_cmd(void* retData, tcUINT32 size) const override;
    /**
     * @cond
     */
    TC_API_ENTRY tcBOOL is_cmd_gen_preparation() const;
    /**
     * @endcond
     *
     */

private:
    class Impl;
    std::shared_ptr<Impl> _memcpy_impl;
};

} /* namespace tools */
} /* namespace tensorcore */
} /* namespace vsi */
#endif /* __tc_gpgpu_api_h_ */
