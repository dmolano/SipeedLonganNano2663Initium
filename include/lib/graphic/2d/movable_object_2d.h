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
#include "gd32vf103.h"

#ifndef __MOVABLE_OBJECT_2D_H
#define __MOVABLE_OBJECT_2D_H

// ---------------------------------------------------------------------
// Public Constants
// ---------------------------------------------------------------------
/* Movable object status enum */
typedef enum
{
    STOP,  /*!< STOP */
    INIT,  /*!< INIT */
    MOVE,  /*!< MOVE */
    IMPACT /*!< IMPACT */
} movable_object_status_enum;

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

    for (;;)
    {
        setPixel(x0, y0);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            y0 += sy;
        }
    }
}
*/
typedef struct _BRESENHAM_LOOP_INFO_STRUCT
{
    int dx, dy, x0, y0, xn, yn, x1, y1, sx, sy, err, e2;
} bresenham_loop_info, *bresenham_loop_info_ptr;

typedef struct _DDA_LOOP_INFO_STRUCT
{

} dda_loop_info, *dda_loop_info_ptr;

/*!
    \brief      Movable Object 2D
*/
typedef struct _MOVABLE_OBJECT_2D
{
    uint16_t color;
    movable_object_status_enum mo_status;
    bresenham_loop_info bresenham;
    struct _MOVABLE_OBJECT_2D *next_movable_object_2d_ptr;
} movable_object_2d, *movable_object_2d_ptr;

// ---------------------------------------------------------------------
// Public Prototypes
// ---------------------------------------------------------------------
/*!
    \brief      Loops over the movable object.
    \param[in]  mo_2d_ptr
    \param[out] mo_2d_ptr
    \retval     none
*/
void loop_movable_object(movable_object_2d_ptr mo_2d_ptr);

#endif // __MOVABLE_OBJECT_2D_H