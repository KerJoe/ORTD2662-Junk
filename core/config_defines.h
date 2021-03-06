#pragma once

#include <stdbool.h>

#define TRUE  1
#define FALSE 0

#define TTL  0
#define LVDS 1
#define RSDS 3

#define TMDS0 0
#define TMDS1 1

// TODO: Find if BG actually means single color fill
#define PANEL_HTOTAL    (PANEL_H_SYNC_WIDTH + PANEL_H_BACK_PORCH + PANEL_H_ACTIVE + PANEL_H_FRONT_PORCH - 4) // Real DH_Total (Target value) = DH_Total (Register value) + 4
#define PANEL_HS_END    (PANEL_H_SYNC_WIDTH)
#define PANEL_HBG_STA   (PANEL_H_SYNC_WIDTH + PANEL_H_BACK_PORCH - 10) // Real DH_BKGD_STA (Target value) = DH_BKGD_STA (Register value) + 10
#define PANEL_HACT_STA  (PANEL_H_SYNC_WIDTH + PANEL_H_BACK_PORCH - 10) // Real DH_ACT_STA (Target value) = DH_ACT_STA (Register value) + 10
#define PANEL_HACT_END  (PANEL_H_SYNC_WIDTH + PANEL_H_BACK_PORCH + PANEL_H_ACTIVE - 10) // Real DH_ACT_END (Target value) = DH_ACT_END (Register value) + 10
#define PANEL_HBG_END   (PANEL_H_SYNC_WIDTH + PANEL_H_BACK_PORCH + PANEL_H_ACTIVE - 10) // Real DH_BKGD_END (Target value) = DH_BKGD_END (Register value) + 10

#define PANEL_VTOTAL    (PANEL_V_SYNC_WIDTH + PANEL_V_BACK_PORCH + PANEL_V_ACTIVE + PANEL_V_FRONT_PORCH)
#define PANEL_VS_END    (PANEL_V_SYNC_WIDTH)
#define PANEL_VBG_STA   (PANEL_V_SYNC_WIDTH + PANEL_V_BACK_PORCH)
#define PANEL_VACT_STA  (PANEL_V_SYNC_WIDTH + PANEL_V_BACK_PORCH)
#define PANEL_VACT_END  (PANEL_V_SYNC_WIDTH + PANEL_V_BACK_PORCH + PANEL_V_ACTIVE)
#define PANEL_VBG_END   (PANEL_V_SYNC_WIDTH + PANEL_V_BACK_PORCH + PANEL_V_ACTIVE)

#define ACTIVE_LEVEL_HIGH 1
#define ACTIVE_LEVEL_LOW  0

#define DDC0 0
#define DDC1 1
#define DDC2 2

#define IR_NEC 0
#define IR_RC5 1