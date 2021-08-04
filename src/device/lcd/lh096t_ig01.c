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

#include "device/lcd/lh096t_ig01.h"

// ---------------------------------------------------------------------
// Private Constants
// ---------------------------------------------------------------------
#define MAX_COLS 160 /*!< Columns in pixel */
#define MAX_ROWS 80  /*!< Rows in pixel */

/*!< Initialization script. */
static const uint8_t INIT_SCRIPT[] =
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
// Private Structures
// ---------------------------------------------------------------------

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
    \brief      Returns the number of columns.
    \param[in]  none
    \param[out] none
    \retval     Number of columns.
*/
uint32_t lh096t_ig01_get_columns_lcd(void)
{
    return MAX_COLS;
}

/*!
    \brief      Returns the data of init script.
    \param[in]  index
    \param[out] none
    \retval     Data of init script.
*/
uint8_t lh096t_ig01_get_data_init_script(uint32_t index)
{
    uint8_t result = 0;

    if (index < lh096t_ig01_get_sizeof_init_script())
    {
        result = INIT_SCRIPT[index];
    }
    return result;
}

/*!
    \brief      Returns the number of rows.
    \param[in]  none
    \param[out] none
    \retval     Number of rows.
*/
uint32_t lh096t_ig01_get_rows_lcd(void)
{
    return MAX_ROWS;
}

/*!
    \brief      Returns the size of init script.
    \param[in]  none
    \param[out] none
    \retval     Size of init script.
*/
uint32_t lh096t_ig01_get_sizeof_init_script(void)
{
    return sizeof(INIT_SCRIPT);
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
