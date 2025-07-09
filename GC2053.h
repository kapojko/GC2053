#ifndef GC2053_H
#define GC2053_H

// Based on https://github.com/OpenIPC/openingenic/blob/master/kernel/sensors/t31/gc2053/gc2053.c

/*
 * Copyright (C) 2012 Ingenic Semiconductor Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <stdint.h>
#include <stdbool.h>

#define GC2053_CHIP_ID 0x2053

#define GC2053_ADDR_IDSEL_0 (0x6e) // 7-bit I2C address (shifted left by 1) when ID_SEL=0
#define GC2053_ADDR_IDSEL_1 (0x7e) // 7-bit I2C address (shifted left by 1) when ID_SEL=1

#define GC2053_MCLK 24000000

enum GC2053_Mode {
    GC2053_MODE_1920_1080_30FPS_DVP, /* 1920*1080 @ max 30fps dvp*/
    GC2053_MODE_1920_1080_15FPS_DVP, /* 1920*1080 @ max 15fps dvp*/
    GC2053_MODE_1920_1080_30FPS_MIPI, /* 1920*1080 @ max 30fps mipi*/
    GC2053_MODE_1920_1080_25FPS_MIPI, /* 1920*1080 @ max 25fps mipi*/
    GC2053_MODE_1920_1080_15FPS_MIPI, /* 1920*1080 @ max 15fps mipi*/
    GC2053_MODE_1920_1080_40FPS_MIPI, /* 1920*1080 @ max 40fps mipi*/
};

struct GC2053_Platform {
    int (*sccbReadReg)(uint8_t sccbId, uint8_t regAddr, uint8_t *data);
    int (*sccbWriteReg)(uint8_t sccbId, uint8_t regAddr, uint8_t data);

    void (*delayMs)(int ms);

    uint8_t id;
};

bool GC2053_ReadChipId(struct GC2053_Platform *p, uint16_t *chipId);

bool GC2053_SetExpo(struct GC2053_Platform *p, int value);
bool GC2053_SetIntegrationTime(struct GC2053_Platform *p, int value);
bool GC2053_SetAnalogGain(struct GC2053_Platform *p, int value);
bool GC2053_SetDigitalGain(struct GC2053_Platform *p, int value);
bool GC2053_SetAutoPregain(struct GC2053_Platform *p, int value_64x);
bool GC2053_GetBlackPedestal(struct GC2053_Platform *p, int *value);

bool GC2053_Init(struct GC2053_Platform *p, enum GC2053_Mode mode);
bool GC2053_SetStream(struct GC2053_Platform *p, enum GC2053_Mode mode, bool enable);
bool GC2053_SetFPS(struct GC2053_Platform *p, enum GC2053_Mode mode, int fps);
bool GC2053_SetVFlip(struct GC2053_Platform *p, int enable);


#endif // GC2053_H
