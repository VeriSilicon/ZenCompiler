/*******************************************************************************
 * Copyright (c) 2019-2020 The Khronos Group Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/


#ifndef OPENCL_CL_BHALF_VIV_H
#define OPENCL_CL_BHALF_VIV_H

#include <CL/cl_platform.h>

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Rounding mode used when converting to cl_bhalf.
 */
typedef enum
{
  CL_BHALF_RTE, // round to nearest even
  CL_BHALF_RTZ, // round towards zero
  CL_BHALF_RTP, // round towards positive infinity
  CL_BHALF_RTN, // round towards negative infinity
} cl_bhalf_rounding_mode;

/*
 *Convert a cl_float to a cl_bhalf
 */
static inline cl_half cl_bhalf_from_float(cl_float f, cl_bhalf_rounding_mode rounding_mode)
{
  // Type-punning to get direct access to underlying bits
  union
  {
    cl_float f;
    uint32_t i;
  } f32;
  f32.f = f;

  // Extract sign bit
  uint16_t sign = f32.i >> 31;

  // Extract FP32 exponent and mantissa
  uint32_t f_exp = (f32.i >> 23) & 0xFF;
  uint32_t f_mant = f32.i & ((1 << 23) - 1);

  // Remove FP32 exponent bias
  int32_t exp = f_exp - 127;

  // Add BFP16 exponent bias
  uint16_t bh_exp = (uint16_t)(exp + 15);

  // Add BFP16 mantissa
  uint32_t lsb_pos = CL_FLT_MANT_DIG - 8;
  uint16_t bh_mant = (uint16_t)(f_mant >> lsb_pos);

  // Check whether need to round
  uint32_t halfway = 1 << (lsb_pos - 1);
  uint32_t mask = (halfway << 1) - 1;

  switch (rounding_mode)
  {
    case CL_BHALF_RTE:
      if ((f_mant & mask) > halfway)
      {
        // More than halfway -> round up
        bh_mant += 1;
      }
      else if ((f_mant & mask) == halfway)
      {
        // Exactly halfway -> round to nearest even
        if (bh_mant & 0x1)
          bh_mant += 1;
      }
      break;
    case CL_BHALF_RTZ:
      // Mantissa has already been truncated -> do nothing
      break;
    case CL_BHALF_RTP:
      if ((f_mant & mask) && !sign)
      {
        // Round positive numbers up
        bh_mant += 1;
      }
      break;
    case CL_BHALF_RTN:
      if ((f_mant & mask) && sign)
      {
        // Round negative numbers down
        bh_mant += 1;
      }
      break;
  }
  // Check for mantissa overflow
  if (bh_mant & 0x80)
  {
    bh_exp += 1;
    bh_mant = 0;
  }

  uint16_t bh = (sign << 15) | (bh_exp << 7) | (bh_mant);

  return bh;

}

/*
 *Convert a cl_bhalf to a cl_float
 */
static inline cl_float cl_bhalf_to_float(cl_bhalf bh)
{
  // Type-punning to get direct access to underlying bits
  union
  {
    cl_float f;
    uint32_t i;
  } f32;

  // Extract sign bit
  uint16_t sign = bh >> 15;

  // Extract BFP16 exponent
  uint16_t bh_exp = (bh >> 7) & 0xFF;

  // Extract BFP16 mantissa
  uint16_t bh_mant = bh & 0x7F;

  // Add FP32 exponent and mantissa
  int32_t f_exp = bh_exp - 15 + 127;
  uint32_t f_mant = bh_mant << 16;

  f32.i =  (sign << 31) | (f_exp << 23) | f_mant;

  return f32.f;

}

/*
 *Convert a cl_bhalf to a cl_half
 */
static inline cl_half cl_bhalf_to_half(cl_bhalf bh)
{
  // Extract sign bit
  uint16_t sign = bh >> 15;

  // Extract BFP16 exponent
  uint16_t bh_exp = (bh >> 7) & 0x5F;

  // Extract BFP16 mantissa
  uint16_t bh_mant = bh & 0x7F;

  return sign << 15 | (bh_exp & 0x1F) << 10 | bh_mant << 3;

}

/*
 *Convert a cl_half to a cl_bhalf
 */
static inline cl_bhalf cl_half_to_bhalf(cl_half h, cl_bhalf_rounding_mode rounding_mode)
{
  // Extract sign bit
  uint16_t sign = h >> 15;

  // Extract FP16 exponent and mantissa
  uint16_t h_exp = (h >> 10) & 0x1F;
  uint16_t h_mant = h & 0x3FF;

  // Add BFP16 exponent and mantissa
  uint16_t bh_exp = h_exp;
  uint32_t lsb_pos = 11 - 8;
  uint16_t bh_mant = (uint16_t)(h_mant >> lsb_pos);
  // Check whether need to round
  uint32_t halfway = 1 << (lsb_pos - 1);
  uint32_t mask = (halfway << 1) - 1;

  switch (rounding_mode)
  {
    case CL_BHALF_RTE:
      if ((h_mant & mask) > halfway)
      {
        // More than halfway -> round up
        bh_mant += 1;
      }
      else if ((h_mant & mask) == halfway)
      {
        // Exactly halfway -> round to nearest even
        if (bh_mant & 0x1)
          bh_mant += 1;
      }
      break;
    case CL_BHALF_RTZ:
      // Mantissa has already been truncated -> do nothing
      break;
    case CL_BHALF_RTP:
      if ((h_mant & mask) && !sign)
      {
        // Round positive numbers up
        bh_mant += 1;
      }
      break;
    case CL_BHALF_RTN:
      if ((h_mant & mask) && sign)
      {
        // Round negative numbers down
        bh_mant += 1;
      }
      break;
  }
  // Check for mantissa overflow
  if (bh_mant & 0x80)
  {
    bh_exp += 1;
    bh_mant = 0;
  }

  return sign << 15 | bh_exp << 7 | bh_mant;
}

#ifdef __cplusplus
}
#endif

#endif  /* OPENCL_CL_BHALF_VIV_H */