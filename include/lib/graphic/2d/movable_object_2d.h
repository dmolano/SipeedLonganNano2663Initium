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
#include "lib\graphic\movable_object.h"

#ifndef __MOVABLE_OBJECT_2D_H
#define __MOVABLE_OBJECT_2D_H

// ---------------------------------------------------------------------
// Public Constants
// ---------------------------------------------------------------------
#define MAX_SPEED 255
#define MIN_SPEED 0

// ---------------------------------------------------------------------
// Public Structures
// ---------------------------------------------------------------------
/*!
    \brief      Movable Object 2D
    http://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C

void line(int x0, int y0, int x1, int y1)
{

    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;
    int xn = x0, yn = y0;

    for (;;)
    {
        setPixel(xn, yn);
        if (xn == x1 && yn == y1)
            break;
        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            xn += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            yn += sy;
        }
    }
}
*/
typedef struct _BRESENHAM_LOOP_INFO_STRUCT
{
    int dx, dy;
    int x0, y0;   // start point
    int xnb, ynb; // before (xn,yn)
    int xn, yn;
    int x1, y1; // MOVE: end point
    int sx, sy;
    int err, e2;
    uint8_t speed; // speed.
    uint8_t speed2;
} bresenham_loop_info, *bresenham_loop_info_ptr;

/*!
    \brief      Movable Object 2D
*/
typedef struct _MOVABLE_OBJECT_2D
{
    uint16_t color;
    movable_object_status_enum mo_status_enum;
    bresenham_loop_info bresenham;
    // Circular linked list: https://en.wikipedia.org/wiki/Linked_list#Circular_linked_list
    struct _MOVABLE_OBJECT_2D *next_movable_object_2d_ptr;
} movable_object_2d, *movable_object_2d_ptr;

// ---------------------------------------------------------------------
// Public Prototypes
// ---------------------------------------------------------------------
/*!
    \brief      Get color of movable object 2D.
    \param[in]  mo_2d_ptr
    \param[out] none
    \retval     uint16_t
*/
uint16_t get_color_movable_object_2d(movable_object_2d_ptr mo_2d_ptr);

/*!
    \brief      Get status of movable object 2D.
    \param[in]  mo_2d_ptr
    \param[out] none
    \retval     movable_object_status_enum
*/
movable_object_status_enum get_status_movable_object_2d(movable_object_2d_ptr mo_2d_ptr);

/*!
    \brief      Loops over the movable object 2D.
    \param[in]  mo_2d_ptr
    \param[in]  x_min
    \param[in]  y_min
    \param[in]  x_max
    \param[in]  y_max
    \param[out] mo_2d_ptr
    \retval     none
*/
void loop_movable_object_2d(movable_object_2d_ptr mo_2d_ptr, uint32_t x_min, uint32_t y_min, uint32_t x_max, uint32_t y_max);

/*!
    \brief      Set color of movable object 2D.
    \param[in]  mo_2d_ptr
    \param[in]  color
    \param[out] mo_2d_ptr
    \retval     none
*/
void set_color_movable_object_2d(movable_object_2d_ptr mo_2d_ptr, uint16_t color);

/*!
    \brief      Set speed of movable object 2D.
    \param[in]  mo_2d_ptr
    \param[in]  speed
    \param[out] mo_2d_ptr
    \retval     none
*/
void set_speed_movable_object_2d(movable_object_2d_ptr mo_2d_ptr, uint8_t speed);

/*!
    \brief      Loops over the movable object 2D.
    \param[in]  mo_2d_ptr
    \param[in]  status_enum
    \param[out] mo_2d_ptr
    \retval     none
*/
void set_status_movable_object_2d(movable_object_2d_ptr mo_2d_ptr, movable_object_status_enum status_enum);

#endif // __MOVABLE_OBJECT_2D_H