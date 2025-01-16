#ifndef __tc_hardware_feature_h_
#define __tc_hardware_feature_h_

#include "tc_operation.h"

#ifdef __cplusplus
extern "C" {
#endif

tcSIZE_T
gcGetZDPLoopCount(tcSIZE_T WeightX,
    tcSIZE_T WeightY,
    tcSIZE_T SliceCount,
    TC_DATA_TYPE WeightFormat,
    tcBOOL ZdpLoop6Support,
    tcBOOL IsDepthWise
);

gcsFEATURE_DATABASE*
tcQueryFeatureDB(
    tcUINT32 customerID
);

tcSTATUS
tcFillInFeatureTable(
    gcsFEATURE_DATABASE* FeatureDB,
    tcUINT32* Feature
);

tcUINT32 tcQueryNNCoreCount(
    tcUINT32* Feature,
    tcENUM weight_format
);

tcUINT32 tcQueryNNCoreCountAvailable(
    tcUINT32* Feature,
    tcENUM weight_format,
    tcBOOL is_depth_wise
);

#ifdef __cplusplus
}
#endif
#endif
