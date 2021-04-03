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

#include "device\sln2663\sln2663_lh096t_ig01.h"

// ---------------------------------------------------------------------
// Private Constants
// ---------------------------------------------------------------------
/*!< description */

// ---------------------------------------------------------------------
// Private Prototypes
// ---------------------------------------------------------------------
/*!
    \brief      function
    \param[in]  none
    \param[out] none
    \retval     system error
*/

// ---------------------------------------------------------------------
// Public Bodies
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
                              sln2663_tft_dma_ptr tft_dma_ptr)
{
    lh096t_ig01_values_init((lh096t_ig01_ptr)lcd_module_device_ptr);
}

// ---------------------------------------------------------------------
// Private Bodies
// ---------------------------------------------------------------------
/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
