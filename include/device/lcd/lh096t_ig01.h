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
/*!< description */

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