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
// Private Structures
// ---------------------------------------------------------------------
/*!
    \brief      Configuration of the PIN electrode.
*/
typedef enum _MODE_INDEX
{
    REG, /*!< register */
    DATA /*!< data */
} mode_index;

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
void lh096t_ig01_init(lh096t_ig01_ptr lh096t_ig01_device_ptr)
{
    mode_index mode = REG;
    uint8_t index_data;
    uint8_t first_data;
    // Initialize the display.
    for (uint32_t index = 0; index < sizeof(INIT_SCRIPT); index++)
    {
        if (mode == REG)
        {
            lcd_reg(INIT_SCRIPT[index++]);
            index_data = INIT_SCRIPT[index];
            mode = DATA;
            first_data = 1;
        }
        else
        {
            if (index_data == NO_PARAMETER)
            {
                // The data for the current record has been finalized. We go to registration mode.
                mode = REG;
            }
            else
            {
                if (first_data == 1)
                {
                    spi_wait_idle();
                    lcd_mode_data();
                    first_data = 0;
                }
                lcd_u8c(INIT_SCRIPT[index]);
                index_data--;
            }
        }
    }
}

/*!
    \brief      Initializes values of LH096T-IG01 LCD module.
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
