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
#include "gd32vf103.h"

#ifndef __LCD_MODULE_H
#define __LCD_MODULE_H

// ---------------------------------------------------------------------
// Public Constants
// ---------------------------------------------------------------------
/*!< description */

// ---------------------------------------------------------------------
// Public Structures
// ---------------------------------------------------------------------
/*!
    \brief      LCD Module. https://en.wikipedia.org/wiki/Liquid-crystal_display
*/
typedef struct _LCD_MODULE
{
    struct
    {
        uint32_t columns; /*!< of pixels. */
        uint32_t rows;    /*!< of pixels. */
    } resolution;
} lcd_module, *lcd_module_ptr;


// ---------------------------------------------------------------------
// Public Prototypes
// ---------------------------------------------------------------------
/*!
    \brief      function
    \param[in]  none
    \param[out] none
    \retval     none
*/

#endif // __LCD_MODULE_H