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
#include "stdlib.h"

// ---------------------------------------------------------------------
// Private Constants
// ---------------------------------------------------------------------
/*!< description */

// ---------------------------------------------------------------------
// Private Prototypes
// ---------------------------------------------------------------------
/*!
    \brief      Loops over the movable object.
    \param[in]  mo_2d_ptr
    \param[out] mo_2d_ptr
    \retval     none
*/
void calculate_impact(movable_object_2d_ptr mo_2d_ptr);

// ---------------------------------------------------------------------
// Public Bodies
// ---------------------------------------------------------------------
/*!
    \brief      Get status of movable object 2D.
    \param[in]  mo_2d_ptr
    \param[out] none
    \retval     movable_object_status_enum
*/
movable_object_status_enum get_status_movable_object_2d(movable_object_2d_ptr mo_2d_ptr)
{
    return mo_2d_ptr->mo_status_enum;
}

/*!
    \brief      Loops over the movable object 2D.
    \param[in]  mo_2d_ptr
    \param[out] mo_2d_ptr
    \retval     none
*/
void loop_movable_object_2d(movable_object_2d_ptr mo_2d_ptr)
{
    switch (get_status_movable_object_2d(mo_2d_ptr))
    {
    case INIT:
        // X
        // Taking note of the starting point.
        mo_2d_ptr->bresenham.xn = mo_2d_ptr->bresenham.x0;
        // Calculating the sign of the movements.
        mo_2d_ptr->bresenham.dx = abs(mo_2d_ptr->bresenham.x1 - mo_2d_ptr->bresenham.x0);
        mo_2d_ptr->bresenham.sx = mo_2d_ptr->bresenham.x0 < mo_2d_ptr->bresenham.x1 ? 1 : -1;
        // Y
        // Taking note of the starting point: Y
        mo_2d_ptr->bresenham.yn = mo_2d_ptr->bresenham.y0;
        mo_2d_ptr->bresenham.dy = abs(mo_2d_ptr->bresenham.y1 - mo_2d_ptr->bresenham.y0);
        // Calculating the sign of the movements.
        mo_2d_ptr->bresenham.sy = mo_2d_ptr->bresenham.y0 < mo_2d_ptr->bresenham.y1 ? 1 : -1;
        // Noting the biggest difference.
        mo_2d_ptr->bresenham.err = (mo_2d_ptr->bresenham.dx > mo_2d_ptr->bresenham.dy ? mo_2d_ptr->bresenham.dx : -mo_2d_ptr->bresenham.dy) / 2;
        mo_2d_ptr->bresenham.e2 = 0;
        // Next status.
        set_status_movable_object_2d(mo_2d_ptr, MOVE);
        break;

    case MOVE:
        mo_2d_ptr->bresenham.e2 = mo_2d_ptr->bresenham.err;
        if (mo_2d_ptr->bresenham.e2 > -mo_2d_ptr->bresenham.dx)
        {
            mo_2d_ptr->bresenham.err -= mo_2d_ptr->bresenham.dy;
            mo_2d_ptr->bresenham.xn += mo_2d_ptr->bresenham.sx;
        }
        if (mo_2d_ptr->bresenham.e2 < mo_2d_ptr->bresenham.dy)
        {
            mo_2d_ptr->bresenham.err += mo_2d_ptr->bresenham.dx;
            mo_2d_ptr->bresenham.yn += mo_2d_ptr->bresenham.sy;
        }
        break;

    case IMPACT:
        // Next status.
        set_status_movable_object_2d(mo_2d_ptr, RICOCHET);
        break;

    case STOP:
        // break;

    default:
        // STOP = DEFAULT
        break;
    }
}

/*!
    \brief      Set status of movable object 2D.
    \param[in]  mo_2d_ptr
    \param[in]  mo_status_enum
    \param[out] mo_2d_ptr
    \retval     none
*/
void set_status_movable_object_2d(movable_object_2d_ptr mo_2d_ptr, movable_object_status_enum mo_status_enum)
{
    mo_2d_ptr->mo_status_enum = mo_status_enum;
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
