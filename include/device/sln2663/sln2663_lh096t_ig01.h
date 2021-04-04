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
#include "device\sln2663\sln2663_tft.h"
#include "device\tft\lh096t_ig01.h"

#ifndef __SLN2663_LH096T_IG01_H
#define __SLN2663_LH096T_IG01_H

// ---------------------------------------------------------------------
// Public Constants
// ---------------------------------------------------------------------
/*!< description */

// ---------------------------------------------------------------------
// Public Structures
// ---------------------------------------------------------------------
/*!
    \brief      LH096T-IG01 in http://dl.sipeed.com/shareURL/LONGAN/Nano/HDK/Longan%20Nano%202663/Longan nano 2663(Schematic).pdf
*/
typedef lh096t_ig01 sln2663_lh096t_ig01, *sln2663_lh096t_ig01_ptr;

// ---------------------------------------------------------------------
// Public Prototypes
// ---------------------------------------------------------------------
/*!
    \brief      Initializes an LCD module.
    \param[in]  lcd_module_device_ptr
    \param[in]  tft_dma_ptr
    \param[out] lcd_module_device_ptr
    \param[out] tft_dma_ptr
    \retval     none
*/
void sln2663_lh096t_ig01_init(sln2663_lcd_module_ptr lcd_module_device_ptr,
                              sln2663_tft_dma_ptr tft_dma_ptr);

#endif // __SLN2663_LH096T_IG01_H