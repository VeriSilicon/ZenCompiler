#pragma once
#ifndef __tc_operation_h_
#define __tc_operation_h_

#include "tc_operation_parameter.h"

class tx_operation
{
    //virtual ~tx_operation();

};

class tx_conv2d : public tx_operation
{
    tx_conv2d();
    ~tx_conv2d();
private:
    tcUINT8                     _iteration;
    std::vector<TC_OP_TYPE_S>   _op_pipe;
    tcUINT32                    _last_cmd;
    tcUINT32                    _pid;

    TC_PAD_MODE                 _pad_mode;
    tcINT8                      _padding[4];
    std::vector<tx_tensor>      _input;
    tx_encoded_coef             _coef;

    tcUINT8                     _stride[2];
    tcBOOL                      _relu_0;
    tx_pool_param* _pool_param;

    /*other opeartion push into _op_pipe*/
    tcBOOL                      _relu_1;
    tcUINT8                     _block_size[2];
    tcTC_ROUND_MODE             _rounding_mode;
    std::vector<tx_tensor>      _output;

    tcBOOL                      _per_channel;
    tcUINT32                    _group_size;


    tcINT32                     _tile_Width;
    tcINT32                     _tileHeight;
    tcINT32                     _kpc;

    tx_cache_param* _in_out_cache;
    tcINT32                     _coef_cache_mode;
    tcUINT32                    _coef_cache_addr;
    tcUINT32                    _coef_cache_size;
};

class tx_matmul : public tx_operation
{
    tx_matmul();

    ~tx_matmul();
private:
    tcUINT8                     _iteration;
    std::vector<TC_OP_TYPE_S>   _op_pipe;
    tcINT8                      _padding[4];
    tcBOOL                      _transpose_a;
    tx_tensor* _input_a;
    tcBOOL                      _transpose_b;
    tx_tensor* _input_b;
    tx_tensor* _input_c;
    tcBOOL                      _relu_0;
    /*other opeartion push into _op_pipe*/
    tcBOOL                      _relu1;
    tcUINT8                     _block_size[2];
    tcBOOL                      _transpose_output;
    tcTC_ROUND_MODE             _rounding_mode;
    std::vector<tx_tensor>      _output;

    tx_cache_param* _in_out_cache;
};

class tx_nt : public tx_operation
{
    tx_nt();
    ~tx_nt();
    tcUINT32 getTransposeSramStride(
        tcUINT32* Feature,
        tcUINT32 tileXSizeInBytes,
        tcUINT32 inImageXSizeInBytes
    );
private:
    tcUINT8                     _iteration;
    tcINT8                      _padding[4];
    tcUINT64                    _word_size;
    std::vector<tx_tensor>      _input;
    std::vector<tx_tensor>      _output;

    tx_cache_param* _in_out_cache;
};

class tx_dma : public tx_operation
{
    tx_dma();
    ~tx_dma();
private:
    tcUINT8                     _iteration;
    tcINT8                      _padding[4];
    tcUINT64                    _word_size;
    std::vector<tx_tensor>         _input;
    std::vector<tx_tensor>         _output;
};

#endif

