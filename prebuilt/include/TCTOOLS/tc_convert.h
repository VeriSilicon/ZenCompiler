#pragma once
#ifndef __tc_convert_h_
#define __tc_convert_h_

#include "tc_types.h"
#include "tc_basic.h"

#ifdef __cplusplus
extern "C" {
#endif

tcFLOAT
gcFp8e4m3toFp32(
    const tcUINT8 in
);

tcFLOAT
gcFp8e5m2toFp32(
    const tcUINT8 in
);

tcFLOAT
gcFp16toFp32(
    const tcUINT16 in
);

tcFLOAT
gcBF16toFp32(
    const tcUINT16 in
);

tcUINT16
gcFP32toFp16(
    tcFLOAT val
);

tcUINT16
gcFp32ToSE4M9(
    tcFLOAT data
);

tcUINT16
gcFp32ToSE5M9(
    tcFLOAT data
);

tcUINT32
gcFp32ToSE6M15(
    tcFLOAT data
);

#ifdef __cplusplus
}
#endif

#endif
