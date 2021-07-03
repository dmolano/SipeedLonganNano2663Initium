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
/*!< Colors */
// ------------>rrrrrggggggbbbbb
#define BLACK 0b0000000000000000
#define WHITE 0b1111111111111111

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
    \brief      Get a color of movable object 2D.
    \param[in]  mo_2d_ptr
    \param[out] none
    \retval     uint16_t
*/
uint16_t sln2663_graphic_2d_get_color_movable_object(movable_object_2d_ptr mo_2d_ptr);

/*!
    \brief      Get a status of movable object 2D.
    \param[in]  mo_2d_ptr
    \param[out] none
    \retval     movable_object_status_enum
*/
movable_object_status_enum sln2663_graphic_2d_get_status_movable_object(movable_object_2d_ptr mo_2d_ptr);

/*!
    \brief      Initialize a graphic 2D structure.
    \param[in]  graphic_2d_ptr
    \param[in]  tft_dma_ptr
    \param[out] graphic_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_init_graphic(sln2663_graphic_2d_ptr graphic_2d_ptr, sln2663_tft_dma_ptr tft_dma_ptr);

/*!
    \brief      Loop movable objects.
    \param[in]  graphic_2d_ptr
    \param[in]  background_color
    \param[out] graphic_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_loop_movable_objects(sln2663_graphic_2d_ptr graphic_2d_ptr, uint16_t background_color);

/*!
    \brief      Set a color of movable object 2D.
    \param[in]  mo_2d_ptr
    \param[in]  color
    \param[out] mo_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_set_color_movable_object(movable_object_2d_ptr mo_2d_ptr, uint16_t color);

/*!
    \brief      Set a random end position.
    \param[in]  graphic_2d_ptr
    \param[in]  mo_2d_ptr
    \param[out] mo_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_set_random_final_position_movable_object(sln2663_graphic_2d_ptr graphic_2d_ptr, movable_object_2d_ptr mo_2d_ptr);

/*!
    \brief      Set a random starting position.
    \param[in]  graphic_2d_ptr
    \param[in]  mo_2d_ptr
    \param[out] mo_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_set_random_initial_position_movable_object(sln2663_graphic_2d_ptr graphic_2d_ptr, movable_object_2d_ptr mo_2d_ptr);

/*!
    \brief      Set speed of movable object 2D.
    \param[in]  mo_2d_ptr
    \param[in]  speed
    \param[out] mo_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_set_speed_movable_object(movable_object_2d_ptr mo_2d_ptr, uint8_t speed);

/*!
    \brief      Set a status of movable object 2D.
    \param[in]  mo_2d_ptr
    \param[in]  status_enum
    \param[out] mo_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_set_status_movable_object(movable_object_2d_ptr mo_2d_ptr, movable_object_status_enum status_enum);

#endif // __SLN2663_GRAPHIC_2D_H