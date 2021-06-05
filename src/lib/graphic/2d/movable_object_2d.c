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

// ---------------------------------------------------------------------
// Private Constants
// ---------------------------------------------------------------------
/*!< description */

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
    \brief      Loops over the movable object.
    \param[in]  mo_2d_ptr
    \param[out] mo_2d_ptr
    \retval     none
*/
void loop_movable_object(movable_object_2d_ptr mo_2d_ptr)
{
    switch (mo_2d_ptr->mo_status)
    {
    case INIT:
        mo_2d_ptr->bresenham.dx = abs(mo_2d_ptr->bresenham.x1 - mo_2d_ptr->bresenham.x0);
        mo_2d_ptr->bresenham.sx = mo_2d_ptr->bresenham.x0 < mo_2d_ptr->bresenham.x1 ? 1 : -1;
        mo_2d_ptr->bresenham.dy = abs(mo_2d_ptr->bresenham.y1 - mo_2d_ptr->bresenham.y0);
        mo_2d_ptr->bresenham.sy = mo_2d_ptr->bresenham.y0 < mo_2d_ptr->bresenham.y1 ? 1 : -1;
        mo_2d_ptr->bresenham.err = (mo_2d_ptr->bresenham.dx > mo_2d_ptr->bresenham.dy ? mo_2d_ptr->bresenham.dx : -mo_2d_ptr->bresenham.dy) / 2;
        mo_2d_ptr->bresenham.e2 = 0;
        // Status
        mo_2d_ptr->mo_status = MOVE;
        break;

    case MOVE:
        if ((mo_2d_ptr->bresenham.x0 == mo_2d_ptr->bresenham.x1) && (mo_2d_ptr->bresenham.y0 == mo_2d_ptr->bresenham.y1))
        {
            mo_2d_ptr->mo_status = IMPACT;
        }
        else
        {
            mo_2d_ptr->bresenham.e2 = mo_2d_ptr->bresenham.err;
            if (mo_2d_ptr->bresenham.e2 > -mo_2d_ptr->bresenham.dx)
            {
                mo_2d_ptr->bresenham.err -= mo_2d_ptr->bresenham.dy;
                mo_2d_ptr->bresenham.x0 += mo_2d_ptr->bresenham.sx;
            }
            if (mo_2d_ptr->bresenham.e2 < mo_2d_ptr->bresenham.dy)
            {
                mo_2d_ptr->bresenham.err += mo_2d_ptr->bresenham.dx;
                mo_2d_ptr->bresenham.y0 += mo_2d_ptr->bresenham.sy;
            }
        }
        break;

    case IMPACT:
        // mo_2d_ptr->mo_status = INIT;
        break;

    case STOP:
        // break;
    default:
        break;
    }
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
