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
    \brief      Add a movable object 2D into graphic 2D structure.
    \param[in]  graphic_2d_ptr
    \param[in]  mo_2d_ptr
    \param[out] graphic_2d_ptr
    \param[out] mo_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_generate_random_movable_object(sln2663_graphic_2d_ptr graphic_2d_ptr, movable_object_2d_ptr mo_2d_ptr)
{
    mo_2d_ptr->x0 = rand() % 160;
    mo_2d_ptr->y0 = rand() % 80;
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
    // Random
    srand(sln2663_graphic_2d_calculate_random_seed());
    // List
    graphic_2d_ptr->last_mo2d_ptr = WITHOUT_MO2D;
}

// ---------------------------------------------------------------------
// Private Bodies
// ---------------------------------------------------------------------
/*!
    \brief      Calculate the seed of the random numbers.
    \param[in]  none
    \param[out] none
    \retval     seed
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
