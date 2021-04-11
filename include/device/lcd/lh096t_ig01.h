/* 
 * This file is part of the Sipeed Longan Nano 2663 Initium.
 * Copyright (c) 2021 Dionisio Molano Robledo.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "lcd_module.h"

#ifndef __LH096T_IG01_H
#define __LH096T_IG01_H

// ---------------------------------------------------------------------
// Public Constants
// ---------------------------------------------------------------------
#define NO_PARAMETER 0x00 /*!< No parameter */

/*!< ST7735S instructions */
typedef enum ST7735S_INSTRUCTION
{
    NOP = 0x00,
    SWRESET = 0x01,   /* Software Reset */
    RDDID = 0x04,     /* Read Display ID */
    RDDST = 0x09,     /* Read Display Status */
    RDDPM = 0x0a,     /* Read Display Power Mode */
    RDDMADCTL = 0x0b, /* Read Display MADCTL */
    RDDCOLMOD = 0x0c, /* Read Display Pixel Format */
    RDDIM = 0x0d,     /* Read Display Image Mode */
    RDDSM = 0x0e,     /* Read Display Signal Mode */
    RDDSDR = 0x0f,    /* Read Display Self-Diagnostic Result */
    SLPIN = 0x10,     /* Sleep In */
    SLPOUT = 0x11,    /* Sleep Out */
    PTLON = 0x12,     /* Partial Display Mode On */
    NORON = 0x13,     /* Normal Display Mode On */
    INVOFF = 0x20,    /* Display Inversion Off */
    INVON = 0x21,     /* Display Inversion On */
    GAMSET = 0x26,    /* Gamma Set */
    DISPOFF = 0x28,   /* Display Off */
    DISPON = 0x29,    /* Display On */
    CASET = 0x2a,     /* Column Address Set */
    RASET = 0x2b,     /* Row Address Set */
    RAMWR = 0x2c,     /* Memory Write */
    RGBSET = 0x2d,    /* Color Setting 4k, 65k, 262k */
    RAMRD = 0x2e,     /* Memory Read */
    PTLAR = 0x30,     /* Partial Area */
    SCRLAR = 0x33,    /* Scroll Area Set */
    TEOFF = 0x34,     /* Tearing Effect Line OFF */
    TEON = 0x35,      /* Tearing Effect Line ON */
    MADCTL = 0x36,    /* Memory Data Access Control */
    VSCSAD = 0x37,    /* Vertical Scroll Start Address of RAM */
    IDMOFF = 0x38,    /* Idle Mode Off */
    IDMON = 0x39,     /* Idle Mode On */
    COLMOD = 0x3a,    /* Interface Pixel Format */
    RDID1 = 0xda,     /* Read ID1 Value */
    RDID2 = 0xdb,     /* Read ID2 Value */
    RDID3 = 0xdc,     /* Read ID3 Value */
    FRMCTR1 = 0xb1,   /* Frame Rate Control in normal mode, full colors */
    FRMCTR2 = 0xb2,   /* Frame Rate Control in idle mode, 8 colors */
    FRMCTR3 = 0xb3,   /* Frame Rate Control in partial mode, full colors */
    INVCTR = 0xb4,    /* Display Inversion Control */
    PWCTR1 = 0xc0,    /* Power Control 1 */
    PWCTR2 = 0xc1,    /* Power Control 2 */
    PWCTR3 = 0xc2,    /* Power Control 3 in normal mode, full colors */
    PWCTR4 = 0xc3,    /* Power Control 4 in idle mode 8colors */
    PWCTR5 = 0xc4,    /* Power Control 5 in partial mode, full colors */
    VMCTR1 = 0xc5,    /* VCOM Control 1 */
    VMOFCTR = 0xc7,   /* VCOM Offset Control */
    WRID2 = 0xd1,     /* Write ID2 Value */
    WRID3 = 0xd2,     /* Write ID3 Value */
    NVFCTR1 = 0xd9,   /* NVM Control Status */
    NVFCTR2 = 0xde,   /* NVM Read Command */
    NVFCTR3 = 0xdf,   /* NVM Write Command */
    GMCTRP1 = 0xe0,   /* Gamma '+'Polarity Correction Characteristics Setting */
    GMCTRN1 = 0xe1,   /* Gamma '-'Polarity Correction Characteristics Setting */
    GCV = 0xfc,       /* Gate Pump Clock Frequency Variable */
} st7735s_instruction;

/*!< ST7735S instructions */
static const uint8_t INIT_SEQUENCE[] =
    {
        INVON, NO_PARAMETER,
        FRMCTR1, 3, 0x05, 0x3a, 0x3a,
        FRMCTR2, 3, 0x05, 0x3a, 0x3a,
        FRMCTR3, 6, 0x05, 0x3a, 0x3a, 0x05, 0x3a, 0x3a,
        INVCTR, 1, 0x03,
        PWCTR1, 3, 0x62, 0x02, 0x04,
        PWCTR2, 1, 0xc0,
        PWCTR3, 2, 0x0d, 0x00,
        PWCTR4, 2, 0x8d, 0x6a,
        PWCTR5, 2, 0x8d, 0xee,
        VMCTR1, 1, 0x0e,
        GMCTRP1, 16, 0x10, 0x0e, 0x02, 0x03, 0x0e, 0x07, 0x02, 0x07, 0x0a, 0x12, 0x27, 0x37, 0x00, 0x0d, 0x0e, 0x10,
        GMCTRN1, 16, 0x10, 0x0e, 0x03, 0x03, 0x0f, 0x06, 0x02, 0x08, 0x0a, 0x13, 0x26, 0x36, 0x00, 0x0d, 0x0e, 0x10,
        COLMOD, 1, 0x55,
        MADCTL, 1, 0x78,
        DISPON, NO_PARAMETER,
        SLPOUT, NO_PARAMETER};
        
// ---------------------------------------------------------------------
// Public Structures
// ---------------------------------------------------------------------
/*!
    \brief      LH096T-IG01. https://dl.sipeed.com/shareURL/LONGAN/Nano/HDK/0.96 inch 80x160 IPS LCD.pdf
*/
typedef lcd_module lh096t_ig01, *lh096t_ig01_ptr;

// ---------------------------------------------------------------------
// Public Prototypes
// ---------------------------------------------------------------------
/*!
    \brief      Initializes an LH096T-IG01 LCD module.
    \param[in]  lh096t_ig01_device_ptr
    \param[out] lh096t_ig01_device_ptr
    \retval     none
*/
void lh096t_ig01_values_init(lh096t_ig01_ptr lh096t_ig01_device_ptr);

#endif // __LH096T_IG01_H