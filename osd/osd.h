#pragma once
#include "stdint.h"

#define OSD_CHAR_OFFSET    0x13
#define OSD_FONT_OFFSET    0x300
#define OSD_CHAR_ADDRESS   0x1000 + OSD_CHAR_OFFSET
#define OSD_FONT_ADDRESS   0x1000 + OSD_FONT_OFFSET

// TODO: Change magic numbers to osd_0 etc
#define OSDWriteByte0(__address, __data) OSDWriteByte((__address) | (0b00 << 14), __data)
#define OSDWriteByte1(__address, __data) OSDWriteByte((__address) | (0b01 << 14), __data)
#define OSDWriteByte2(__address, __data) OSDWriteByte((__address) | (0b10 << 14), __data)
#define OSDWriteByte012(__address, __data) OSDWriteByte((__address) | (0b11 << 14), __data)

#define OSDReadByte0(__address) OSDReadByte((__address) | (0b00 << 14))
#define OSDReadByte1(__address) OSDReadByte((__address) | (0b01 << 14))
#define OSDReadByte2(__address) OSDReadByte((__address) | (0b10 << 14))
#define OSDReadByte012(__address) OSDReadByte((__address) | (0b11 << 14))

typedef struct
{
    uint8_t effectHeight : 3;   // Border/Shadow height
    uint8_t effectWidth : 3;    // Border/Shadow width
    uint8_t : 2;

    uint8_t borderColor : 4;
    uint8_t shadowColor : 4;

    uint8_t gradientBlueEnable : 1;
    uint8_t gradientGreenEnable : 1;
    uint8_t gradientRedEnable : 1;
    uint8_t gradientSteps : 2;
    uint8_t gradientBluePolarity : 1;
    uint8_t gradientGreenPolarity : 1;
    uint8_t gradientRedPolarity : 1;


    uint16_t horStart : 11;
    uint16_t verStart : 11;
    uint16_t : 2;


    uint16_t horEnd : 11;
    uint16_t verEnd : 11;
    uint16_t : 2;


    uint8_t color : 4;
    uint8_t gradientLevel : 3;
    uint8_t : 1;

    uint8_t enable : 1;
    uint8_t effectType : 3; // 000: Shadow Type 1; 001: Shadow Type 2; 010: Shadow Type3; 011: Shadow Type 4; 100: 3D Button Type 1; 101: 3D Button Type 2; 111: Border
    uint8_t effectEnable : 1;
    uint8_t gradientDirection : 1;
    uint8_t gradientEnable : 1;
    uint8_t : 1;
} OSDWindow;

typedef struct
{
    uint8_t charHeight2X : 1;
    uint8_t charWidth2X : 1;
    uint8_t charEffect : 3; // Effect type border/shadow
    uint8_t : 1;
    uint8_t vbiFunction : 1;
    uint8_t notStop : 1; // If 0 then end of row commands

    uint8_t width : 3;  // Width of character
    uint8_t height : 5;

    uint8_t length : 8; // Number of characters
} OSDRow;

typedef struct
{
    uint8_t : 6;
    uint8_t blinking : 1;
    uint8_t isVisible : 1; // Is character non blank

    uint8_t length : 8; // If isVisible is 1; then this byte sets the size of empty space (not Character.width)

    uint8_t : 4;
    uint8_t color : 4; // 0 is special for transparent
} OSDCharacterBlank;

typedef struct // One bit color
{
    uint8_t width : 4;
    uint8_t fontSize : 2; // 0 - 1 bit,  1 - 4 bit,  3 - 2 bit
    uint8_t blinking : 1;
    uint8_t isVisible : 1; // Is character non blank

    uint8_t character : 8; // If isVisible is 1; then this byte sets the size of empty space (not Character.width)

    uint8_t bgColor : 4; // 0 is special for transparent
    uint8_t fgColor : 4;
} OSDCharacter1;

// TODO: Other bit character bit counts

void OSDWriteByte(uint16_t address, uint8_t data);
void OSDWriteTriplet(uint16_t address, uint8_t byte0, uint8_t byte1, uint8_t byte2);
void OSDWriteTriplets(uint16_t address, uint8_t* data, uint16_t count);
uint8_t OSDReadByte(uint16_t address);
void OSDInit();
void UploadColorPallete(uint8_t pallete[][3]);
void UploadFont_1Bit_8x16(uint8_t font[][16]);
void UploadVLC(uint16_t address, uint8_t* data_array);
void SetOSDOffset(uint16_t hor, uint16_t ver);
void OSDEnable(uint8_t state);
void SetOSDCharAlignment(uint8_t state);
void OSDSetWindow(OSDWindow* window, uint8_t windowNumber);
void OSDSetRow(OSDRow* row, uint8_t rowNumber);
void OSDSetChar1(OSDCharacter1* ch1, uint8_t ch1Number);
void OSDEndRow(uint8_t rowNumber);
void OSDSetBlank(OSDCharacterBlank* chb, uint8_t chbNumber);