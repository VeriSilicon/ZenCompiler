#ifndef __tc_operation_parameter_h_
#define __tc_operation_parameter_h_

#include "tc_common.h"

/**
 * @brief class memory to describe a memory
 */
class tx_memory
{
    /**
     * @brief Construct a memory object
     * @param type memory type
     * @param layout memory layout
     * @param logical_addr logical address accesed by software
     * @param physical_addr physical address accesed by hardware
     * @param size memory size in bytes.
     */
    tx_memory(TC_MEMORY_TYPE      type,
        tcTC_LAYOUT         layout,
        tcPOINTER* logical_addr, /*start address*/
        tcUINT64            physical_addr, /*start address*/
        tcUINT64            size /*InBytes*/
    );

private:
    TC_MEMORY_TYPE      _type;
    tcTC_LAYOUT         _layout;
    tcPOINTER* _logical_addr; /*start address*/
    tcUINT64            _physical_addr; /*start address*/
    tcUINT64            _size; /*InBytes*/
};

/**
 * @brief class tensor to describe a tensor
 */
class tx_tensor
{
    /**
 * @brief Construct a tensor object
 * @param buffer physical memory
 * @param size  shape informationm, followsing [W, H, C, N]
 * @param offset offset to buffer start address
 * @param stride_in_bits tensor strides in bits, followsing [W, H, C, N]
 * @param dataFormat data format
 */
    tx_tensor(tx_memory* buffer,
        std::vector<tcUINT64>       size,
        tcUINT64                    offset,
        std::vector<tcUINT64>       stride_in_bits,
        TC_DATA_TYPE                data_format,
        std::vector<tcFLOAT>& scale,
        std::vector<tcINT32>& zp,
        std::string                  name
    );

private:
    std::string                 _name;
    tx_memory* _buffer;
    tcUINT64                    _offset;
    std::vector<tcUINT64>        _size;
    std::vector<tcUINT64>        _stride_in_bits;
    TC_DATA_TYPE                _dataFormat;
    std::vector<tcFLOAT>        _scale;
    std::vector<tcINT32>        _zp;

    tcUINT64                    _increase;
};

/**
 * @brief class coef to minimal parameter
 */
class tx_coef
{
    /**
 * @brief Construct a tensor object
 * @param buffer physical memory
 * @param size  shape informationm, followsing [W, H, C, N]
 * @param stride_in_bits tensor strides in bits, followsing [W, H, C, N]
 * @param dataFormat data format
 */
    tx_coef();
private:
    std::vector<tx_tensor>          _original_coef; /*how to sperate weight/bias/prelu/...*/
    tcINT32                         _input_zp;
};


/**
 * @brief class encoded_coef to describe coef and encoded coef
 */
class tx_encoded_coef
{
    /**
 * @brief Construct a tensor object
 * @param buffer physical memory
 * @param size  shape informationm, followsing [W, H, C, N]
 * @param stride_in_bits tensor strides in bits, followsing [W, H, C, N]
 * @param dataFormat data format
 */
    tx_encoded_coef(tx_memory* buffer,
        std::vector<tcUINT64>        size,
        std::vector<tcUINT64>        stride_in_bits,
        TC_DATA_TYPE                data_format
    );
private:
    std::vector<tx_tensor>      _original_coef;/*how to sperate weight/bias/prelu/...*/
    TC_ARCH_PARAM_S             _tile_size_kpc;
    tx_memory* _encoded_buffer;
    tcUINT64                    _stream_size;
    tcFLOAT                     _encoded_ratio;
    tcUINT64                    _body_size;
    TC_COEF_ENCODER_MODE        _encode_mode;
    tcBOOL                      _is_2_4Sparsity;
    tcBOOL                      _lut_load;
};

class tx_pool_param
{
    tx_pool_param();
private:
    tcTC_POOLING_TYPE           _type;
    tcINT8                      _pool_pad[4];
    tcUINT8                     _pool_stride[2];
    tcUINT8                     _pool_size[2];
};

class tx_prelu_param
{
    tx_prelu_param();
private:
    tcTYPE_ACTIVATION_E         _type;
    std::vector<tcFLOAT>        _alpha;
    tcINT8                      _pool_pad[4];
    tcUINT8                     _pool_stride[2];
    tcUINT8                     _pool_size[2];
};

class tx_sp_param
{
    virtual ~tx_sp_param();
};

class tx_cache_param
{

private:
    tcUINT32                    _input_cache_addr;
    tcUINT32                    _input_cache_size;
    tcUINT32                    _output_cache_addr;
    tcUINT32                    _output_cache_size;
};


#endif
