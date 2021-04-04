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

#include "device\lcd\lh096t_ig01.h"

// ---------------------------------------------------------------------
// Private Constants
// ---------------------------------------------------------------------
#define MAX_COLS 160 /*!< Columns in pixel */
#define MAX_ROWS 80  /*!< Rows in pixel */

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
    \brief      Initializes an LH096T-IG01 LCD module.
    \param[in]  lh096t_ig01_device_ptr
    \param[out] lh096t_ig01_device_ptr
    \retval     none
*/
void lh096t_ig01_values_init(lh096t_ig01_ptr lh096t_ig01_device_ptr)
{
    lh096t_ig01_device_ptr->resolution.columns = MAX_COLS;
    lh096t_ig01_device_ptr->resolution.rows = MAX_ROWS;
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
