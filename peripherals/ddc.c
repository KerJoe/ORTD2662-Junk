#include <stdint.h>
#include <string.h> // memcpy

#include "peripherals/ddc.h"
#include "scaler/scaler_access.h"

const uint8_t testEDID[] =
{
    0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x12, 0xE5, 0x00, 0x21, 0x50, 0x2D, 0x31, 0x01, // 0x0X
    0x1C, 0x13, 0x01, 0x03, 0x81, 0x2F, 0x1A, 0x78, 0x2E, 0x35, 0x85, 0xA6, 0x56, 0x48, 0x9A, 0x24, // 0x1X
    0x12, 0x50, 0x54, 0xAF, 0xEF, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, // 0x2X
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xA1, 0x13, 0x00, 0x40, 0x41, 0x58, 0x19, 0x20, 0x2C, 0x58, // 0x3X
    0x36, 0x00, 0xDC, 0x0C, 0x11, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x30, 0x0A, 0x0A, // 0x4X
    0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x00, 0x00, 0x00, 0xFD, 0x00, 0x38, // 0x5X
    0x4B, 0x1E, 0x53, 0x15, 0x00, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFC, // 0x6X
    0x00, 0x48, 0x44, 0x4D, 0x49, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x01, 0xF9, // 0x7X
};

// Assumes defualt 128 bytes for all three DDCs
// ddcNumber starts from 0
void UploadEDID(uint8_t ddcNumber, uint8_t* data)
{
    // Enable MCU access to EDID
    switch (ddcNumber)
    {
        case 0: XSFRWriteByte(DDC1_CONTROL0, InsertBits8(DDC1_CONTROL0, 0, 1, 0b0)); break;
        case 1: XSFRWriteByte(DDC2_CONTROL0, InsertBits8(DDC2_CONTROL0, 0, 1, 0b0)); break;
        case 2: XSFRWriteByte(DDC3_CONTROL0, InsertBits8(DDC3_CONTROL0, 0, 1, 0b0)); break;
    }
#   ifdef __SDCC
    __xdata uint16_t* p = (__xdata uint16_t*)(0xFD80 + 0x80 * ddcNumber);
    memcpy(p, data, 128);
#   else
    for (uint8_t i; i < 128; i++)
    {
        switch (ddcNumber)
        {
            case 0: XSFRWriteByte(DDC1_INDEX, i); XSFRWriteByte(DDC1_DATA, data[i]); break;
            case 1: XSFRWriteByte(DDC2_INDEX, i); XSFRWriteByte(DDC2_DATA, data[i]); break;
            case 2: XSFRWriteByte(DDC3_INDEX, i); XSFRWriteByte(DDC3_DATA, data[i]); break;
        }
    }
#   endif
    // Enable DDC access to EDID
    switch (ddcNumber)
    {
        case 0: XSFRWriteByte(DDC1_CONTROL0, InsertBits8(DDC1_CONTROL0, 0, 1, 0b1)); break;
        case 1: XSFRWriteByte(DDC2_CONTROL0, InsertBits8(DDC2_CONTROL0, 0, 1, 0b1)); break;
        case 2: XSFRWriteByte(DDC3_CONTROL0, InsertBits8(DDC3_CONTROL0, 0, 1, 0b1)); break;
    }
}