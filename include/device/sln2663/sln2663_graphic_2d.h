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
#include "lib\graphic\2d\movable_object_2d.h"
#include "device\sln2663\sln2663_tft.h"

#ifndef __SLN2663_GRAPHIC_2D_H
#define __SLN2663_GRAPHIC_2D_H

// ---------------------------------------------------------------------
// Public Constants
// ---------------------------------------------------------------------
/*!< description */

// ---------------------------------------------------------------------
// Public Structures
// ---------------------------------------------------------------------
/*!
    \brief      Graphic 2D
*/
typedef struct _SLN2663_GRAPHIC_2D
{
    sln2663_tft_dma_ptr tft_dma_ptr;
    movable_object_2d_ptr last_mo2d_ptr;
} sln2663_graphic_2d, *sln2663_graphic_2d_ptr;

// ---------------------------------------------------------------------
// Public Prototypes
// ---------------------------------------------------------------------
/*!
    \brief      Add a movable object 2D into graphic 2D structure.
    \param[in]  graphic_2d_ptr
    \param[in]  mo_2d_ptr
    \param[out] graphic_2d_ptr
    \param[out] mo_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_add_movable_object(sln2663_graphic_2d_ptr graphic_2d_ptr, movable_object_2d_ptr mo_2d_ptr);

/*!
    \brief      Initialize a graphic 2D structure.
    \param[in]  graphic_2d_ptr
    \param[in]  tft_dma_ptr
    \param[out] graphic_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_init_graphic_2d(sln2663_graphic_2d_ptr graphic_2d_ptr, sln2663_tft_dma_ptr tft_dma_ptr);

/*!
    \brief      Add a movable object 2D into graphic 2D structure.
    \param[in]  graphic_2d_ptr
    \param[in]  mo_2d_ptr
    \param[out] graphic_2d_ptr
    \param[out] mo_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_set_random_position_movable_object(sln2663_graphic_2d_ptr graphic_2d_ptr, movable_object_2d_ptr mo_2d_ptr);

#endif // __SLN2663_GRAPHIC_2D_H