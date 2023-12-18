/*
 * Copyright 2017 Rockchip Electronics Co. LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __HAL_H265E_BASE_H__
#define __HAL_H265E_BASE_H__

#include "mpp_env.h"
#include "mpp_log.h"
#include "mpp_common.h"
#include "mpp_device.h"
#include "mpp_hal.h"
#include "rga_api.h"

#include "hal_h265e_vepu22_def.h"

typedef struct hal_h265e_ctx {
    MppHalApi       hal_api;
    MppDev          dev;
    MppBufferGroup  buf_grp;

    /*
     * the ion buffer's fd of ROI map
     * ROI map holds importance levels for CTUs within a picture. The memory size is the number of CTUs of picture in bytes.
     * For example, if there are 64 CTUs within a picture, the size of ROI map is 64 bytes.
     * All CTUs have their ROI importance level (0 ~ 8 ; 1 byte)  in raster order.
     * A CTU with a high ROI important level is encoded with a lower QP for higher quality.
     * It should be given when hw_cfg.ctu.roi_enable is 1.
     */
    MppBuffer       roi;

    /*
     * Sthe ion buffer's fd of CTU qp map
     * The memory size is the number of CTUs of picture in bytes.
     * For example if there are 64 CTUs within a picture, the size of CTU map is 64 bytes.
     * It should be given when hw_cfg.ctu.ctu_qp_enable is 1.

     * The content of ctuQpMap directly is mapped to the Qp used to encode the CTU. I.e,
     * if (ctuQpMap[k]==5], it means that CTU(k) is encoded with Qp=5.
     */
    MppBuffer       ctu;

    /*
     * the ion buffer's fd of preprocess
     * The IP of H265 Encoder need stride of luma and chroma align 16
     * If the input fomrat is  YU12 or YV12, and their stride of input buffer is not align 32(only align 16),
     * this means the stride of chroma is align 8, so we need translate input format to nv12.
     */
    MppBuffer       pre_buf;

    void           *en_info;
    RK_U32          option;
    RK_U32          user_cfg;
    void            *hw_cfg;
    Vepu22H265eRet  result;
    MppCbCtx        *enc_cb;


    MppEncCfgSet    *cfg;
    MppEncCfgSet    *set;

    RK_U32          init;

    RgaCtx          rga_ctx;
    /*
     * write yuv data(only for debug)
     */
    FILE*           mInFile;

    /*
     * write bit stram data(only for debug)
     */
    FILE*           mOutFile;
} HalH265eCtx;

#endif
