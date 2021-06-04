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

#include "device\sln2663\sln2663_graphic_2d.h"
#include <stdlib.h>

// ---------------------------------------------------------------------
// Private Constants
// ---------------------------------------------------------------------
/*!< Without movable object 2D */
#define WITHOUT_MO2D NULL

// ---------------------------------------------------------------------
// Private Prototypes
// ---------------------------------------------------------------------
/*!
    \brief      Calculate the seed of the random numbers.
    \param[in]  none
    \param[out] none
    \retval     seed
*/
unsigned int sln2663_graphic_2d_calculate_random_seed();

/*!
    \brief      Initialize a movable object 2D into graphic 2D structure.
    \param[in]  mo_2d_ptr
    \param[in]  graphic_2d_ptr
    \param[out] mo_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_init_movable_object(movable_object_2d_ptr mo_2d_ptr, sln2663_graphic_2d_ptr graphic_2d_ptr);

// ---------------------------------------------------------------------
// Public Bodies
// ---------------------------------------------------------------------
/*!
    \brief      Add a movable object 2D into graphic 2D structure.
    \param[in]  graphic_2d_ptr
    \param[in]  mo_2d_ptr
    \param[out] graphic_2d_ptr
    \param[out] mo_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_add_movable_object(sln2663_graphic_2d_ptr graphic_2d_ptr, movable_object_2d_ptr mo_2d_ptr)
{
    if (graphic_2d_ptr->last_mo2d_ptr == WITHOUT_MO2D)
    {
        graphic_2d_ptr->last_mo2d_ptr = mo_2d_ptr;
    }
    else
    {
        mo_2d_ptr->next_movable_object_2d_ptr = graphic_2d_ptr->last_mo2d_ptr;
        graphic_2d_ptr->last_mo2d_ptr->next_movable_object_2d_ptr = mo_2d_ptr;
        graphic_2d_ptr->last_mo2d_ptr = mo_2d_ptr;
    }
    sln2663_graphic_2d_init_movable_object(mo_2d_ptr, graphic_2d_ptr);
}

/*!
    \brief      Initialize a graphic 2D structure.
    \param[in]  graphic_2d_ptr
    \param[in]  tft_dma_ptr
    \param[out] graphic_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_init_graphic_2d(sln2663_graphic_2d_ptr graphic_2d_ptr, sln2663_tft_dma_ptr tft_dma_ptr)
{
    // Initialize the pseudo-random number generator.
    srand(sln2663_graphic_2d_calculate_random_seed());
    // Hooking up with the TFT device.
    graphic_2d_ptr->tft_dma_ptr = tft_dma_ptr;
    // Initializes the circular list.
    graphic_2d_ptr->last_mo2d_ptr = WITHOUT_MO2D;
}

/*!
    \brief      Add a movable object 2D into graphic 2D structure.
    \param[in]  graphic_2d_ptr
    \param[in]  mo_2d_ptr
    \param[out] graphic_2d_ptr
    \param[out] mo_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_set_random_position_movable_object(sln2663_graphic_2d_ptr graphic_2d_ptr, movable_object_2d_ptr mo_2d_ptr)
{
    mo_2d_ptr->x0 = rand() % graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.columns;
    mo_2d_ptr->y0 = rand() % graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.rows;
}

// ---------------------------------------------------------------------
// Private Bodies
// ---------------------------------------------------------------------
/*!
    \brief      Calculate the seed of the pseudo-random numbers.
    \param[in]  none
    \param[out] none
    \retval     Seed for the generation of pseudo-random numbers.
*/
unsigned int sln2663_graphic_2d_calculate_random_seed() {
    return get_timer_value();
}

/*!
    \brief      Initialize a movable object 2D into graphic 2D structure.
    \param[in]  mo_2d_ptr
    \param[in]  graphic_2d_ptr
    \param[out] mo_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_init_movable_object(movable_object_2d_ptr mo_2d_ptr, sln2663_graphic_2d_ptr graphic_2d_ptr)
{
}
