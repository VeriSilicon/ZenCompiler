#ifndef __CL_EXT_VIV_H
#define __CL_EXT_VIV_H

#include <CL/cl.h>
#include <CL/cl_platform.h>

#ifdef __cplusplus
extern "C" {
#endif

/* VIV: 0x4280 ~ 0x428F enum for Verisilicon */
/* VIV: -1143  ~ -1153  Error Code for Verisilicon */

/* address or size is not aligned */
#define CL_NOT_ALIGNED          -1143


/********************************************************************
* cl_vivante_device_attribute_query
********************************************************************/
#define CL_MEM_USE_UNCACHED_HOST_MEMORY_VIV         (1 << 28)

/* for CL_MEM_USE_HOST_PHYSICAL_ADDR_VIV, application must make
   sure the physical address passed in is a 40 bit address
*/
#define CL_MEM_USE_HOST_PHYSICAL_ADDR_VIV           (1 << 29)


/* external sram */
#define CL_MEM_ALLOC_FROM_EXTERNAL_SRAM_VIV         (((cl_mem_flags)1) << 63)
/* return type: size_t[] */
#define CL_DEVICE_EXTERNAL_SRAM_SIZE_VIV            0x4280
/* return type: cl_uint */
#define CL_DEVICE_VIDMEM_CHANNEL_COUNT_VIV          0x4281
/* return type: size_t[] */
#define CL_DEVICE_CLOCK_BANDWIDTH_VIV               0X428A
/* return type: char[] */
#define CL_DEVICE_TC_FEATURE_VIV                    0x428B
/* return tyep: cl_uint */
#define CL_DEVICE_CUSTOMER_ID_VIV                   0x428C

/* properties for clCreateBufferWithProperties and clCreateImageWithProperties */
/* property value type: cl_uint */
#define CL_DEVICE_ALLOC_FROM_EXTSRAM_INDEX_VIV      0x4282
/* property value type: cl_uint */
#define CL_DEVICE_ALLOC_FROM_VIDMEM_INDEX_VIV       0x4283
/* property value type: cl_uint*/
#define CL_DEVICE_ALLOC_ALIGNMENT_VIV       0x4284

/* dump IR for compiler */
/* function name: clSetCompilerDumpOptionVIV */
#define DUMP_OPTION_OFF                             0x0
#define DUMP_OPTION_ALL                             0xFFFFFFFF
typedef CL_API_ENTRY cl_int (CL_API_CALL *clSetCompilerDumpOptionVIV_fn)(cl_uint option);

/* device info */
/* type: uint */
#define CL_DEVICE_PHYSICAL_ADDRESS_BITS_VIV         0x4286
/* type: uint */
#define CL_DEVICE_VIRTUAL_ADDRESS_BITS_VIV          0x4287
#define CL_DEVICE_INTERNAL_SRAM_SIZE_VIV            0x4288
#define CL_DEVICE_MIN_PTCM_SIZE_VIV                 0x4289

#define CL_DEVICE_FP8_CONFIG_VIV                    0x428D
#define CL_DEVICE_BF16_CONFIG_VIV                   0x428E


/* command queue info */
#define CL_QUEUE_PROFILE_INFO                       0x428F


#ifdef __cplusplus
}
#endif

#endif
