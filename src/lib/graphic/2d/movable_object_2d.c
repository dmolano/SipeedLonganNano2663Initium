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
    \brief      Calculate errors over the movable object 2D.
    \param[in]  mo_2d_ptr
    \param[out] mo_2d_ptr
    \retval     none
*/
void calculate_errors_movable_object_2d(movable_object_2d_ptr mo_2d_ptr);

/*!
    \brief      Detect possible impact of movable object.
    \param[in]  mo_2d_ptr movable object.
    \param[in]  x_min
    \param[in]  y_min
    \param[in]  x_max
    \param[in]  y_max
    \param[out] mo_2d_ptr
    \retval     none
*/
void detect_impact_movable_object_2d(movable_object_2d_ptr mo2d_ptr, uint32_t x_min, uint32_t y_min, uint32_t x_max, uint32_t y_max);

/*!
    \brief      Shift over the movable object 2D.
    \param[in]  mo_2d_ptr
    \param[out] mo_2d_ptr
    \retval     none
*/
void shift_movable_object_2d(movable_object_2d_ptr mo_2d_ptr);

/*!
    \brief      Loops over the alive movable object 2D.
    \param[in]  mo_2d_ptr
    \param[in]  x_min
    \param[in]  y_min
    \param[in]  x_max
    \param[in]  y_max
    \param[out] mo_2d_ptr
    \retval     none
*/
void loop_alive_movable_object_2d(movable_object_2d_ptr mo_2d_ptr, uint32_t x_min, uint32_t y_min, uint32_t x_max, uint32_t y_max);

/*!
    \brief      Loop speed over the movable object 2D.
    \param[in]  mo_2d_ptr
    \param[in]  next_status_enum
    \param[out] mo_2d_ptr
    \retval     none
*/
void loop_speed_movable_object_2d(movable_object_2d_ptr mo_2d_ptr, movable_object_status_enum next_status_enum);

// ---------------------------------------------------------------------
// Public Bodies
// ---------------------------------------------------------------------
/*!
    \brief      Get color of movable object 2D.
    \param[in]  mo_2d_ptr
    \param[out] none
    \retval     uint16_t
*/
uint16_t get_color_movable_object_2d(movable_object_2d_ptr mo_2d_ptr)
{
    return mo_2d_ptr->color;
}

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
    \param[in]  x_min
    \param[in]  y_min
    \param[in]  x_max
    \param[in]  y_max
    \param[out] mo_2d_ptr
    \retval     none
*/
void loop_movable_object_2d(movable_object_2d_ptr mo_2d_ptr, uint32_t x_min, uint32_t y_min, uint32_t x_max, uint32_t y_max)
{
    if (get_status_movable_object_2d(mo_2d_ptr) != DEAD)
    {
        loop_alive_movable_object_2d(mo_2d_ptr, x_min, y_min, x_max, y_max);
    }
}

/*!
    \brief      Set color of movable object 2D.
    \param[in]  mo_2d_ptr
    \param[in]  color
    \param[out] mo_2d_ptr
    \retval     none
*/
void set_color_movable_object_2d(movable_object_2d_ptr mo_2d_ptr, uint16_t color)
{
    mo_2d_ptr->color = color;
}

/*!
    \brief      Set speed of movable object 2D.
    \param[in]  mo_2d_ptr
    \param[in]  speed
    \param[out] mo_2d_ptr
    \retval     none
*/
void set_speed_movable_object_2d(movable_object_2d_ptr mo_2d_ptr, uint8_t speed)
{
    mo_2d_ptr->bresenham.speed = mo_2d_ptr->bresenham.speed2 = MAX_SPEED - speed;
}

/*!
    \brief      Set status of movable object 2D.
    \param[in]  mo_2d_ptr
    \param[in]  status_enum
    \param[out] mo_2d_ptr
    \retval     none
*/
void set_status_movable_object_2d(movable_object_2d_ptr mo_2d_ptr, movable_object_status_enum status_enum)
{
    mo_2d_ptr->mo_status_enum = status_enum;
}

// ---------------------------------------------------------------------
// Private Bodies
// ---------------------------------------------------------------------
/*!
    \brief      Calculate errors over the movable object 2D.
    \param[in]  mo_2d_ptr
    \param[out] mo_2d_ptr
    \retval     none
*/
void calculate_errors_movable_object_2d(movable_object_2d_ptr mo_2d_ptr)
{
    mo_2d_ptr->bresenham.err = (mo_2d_ptr->bresenham.dx > mo_2d_ptr->bresenham.dy ? mo_2d_ptr->bresenham.dx : -mo_2d_ptr->bresenham.dy) / 2;
    mo_2d_ptr->bresenham.e2 = 0;
}

/*!
    \brief      Detect possible impact of movable object.
    \param[in]  mo_2d_ptr movable object.
    \param[in]  x_min
    \param[in]  y_min
    \param[in]  x_max
    \param[in]  y_max
    \param[out] mo_2d_ptr
    \retval     none
*/
void detect_impact_movable_object_2d(movable_object_2d_ptr mo2d_ptr, uint32_t x_min, uint32_t y_min, uint32_t x_max, uint32_t y_max)
{
    if (mo2d_ptr->bresenham.xn < x_min)
    {
        if (mo2d_ptr->bresenham.yn < (int)y_min)
        {
            mo2d_ptr->mo_status_enum = IMPACT_X_LEFT_Y_TOP;
        }
        else if (mo2d_ptr->bresenham.yn > y_max)
        {
            mo2d_ptr->mo_status_enum = IMPACT_X_LEFT_Y_BOTTOM;
        }
        else
        {
            mo2d_ptr->mo_status_enum = IMPACT_X_LEFT;
        }
    }
    else if (mo2d_ptr->bresenham.xn > x_max)
    {
        if (mo2d_ptr->bresenham.yn < (int)y_min)
        {
            mo2d_ptr->mo_status_enum = IMPACT_X_RIGHT_Y_TOP;
        }
        else if (mo2d_ptr->bresenham.yn > y_max)
        {
            mo2d_ptr->mo_status_enum = IMPACT_X_RIGHT_Y_BOTTOM;
        }
        else
        {
            mo2d_ptr->mo_status_enum = IMPACT_X_RIGHT;
        }
    }
    else if (mo2d_ptr->bresenham.yn < (int)y_min)
    {
        mo2d_ptr->mo_status_enum = IMPACT_Y_TOP;
    }
    else if (mo2d_ptr->bresenham.yn > y_max)
    {
        mo2d_ptr->mo_status_enum = IMPACT_Y_BOTTOM;
    }
}

/*!
    \brief      Loops over the alive movable object 2D.
    \param[in]  mo_2d_ptr
    \param[in]  x_min
    \param[in]  y_min
    \param[in]  x_max
    \param[in]  y_max
    \param[out] mo_2d_ptr
    \retval     none
*/
void loop_alive_movable_object_2d(movable_object_2d_ptr mo_2d_ptr, uint32_t x_min, uint32_t y_min, uint32_t x_max, uint32_t y_max)
{
    movable_object_status_enum before_status_enum;

    // int x_in = 0, y_in = 0;

    before_status_enum = get_status_movable_object_2d(mo_2d_ptr);
    switch (before_status_enum)
    {
    case SHOOT:
        //
        // X
        //
        // Taking note of the starting point.
        mo_2d_ptr->bresenham.xnb = mo_2d_ptr->bresenham.xn = mo_2d_ptr->bresenham.x0;
        // Calculating the sign of the movements.
        mo_2d_ptr->bresenham.dx = abs(mo_2d_ptr->bresenham.x1 - mo_2d_ptr->bresenham.x0);
        mo_2d_ptr->bresenham.sx = mo_2d_ptr->bresenham.x0 < mo_2d_ptr->bresenham.x1 ? 1 : -1;
        //
        // Y
        //
        // Taking note of the starting point: Y
        mo_2d_ptr->bresenham.ynb = mo_2d_ptr->bresenham.yn = mo_2d_ptr->bresenham.y0;
        mo_2d_ptr->bresenham.dy = abs(mo_2d_ptr->bresenham.y1 - mo_2d_ptr->bresenham.y0);
        //
        // ERROR
        //
        // Calculating the sign of the movements.
        mo_2d_ptr->bresenham.sy = mo_2d_ptr->bresenham.y0 < mo_2d_ptr->bresenham.y1 ? 1 : -1;
        // Noting the biggest difference.
        calculate_errors_movable_object_2d(mo_2d_ptr);
        // Next status.
        set_status_movable_object_2d(mo_2d_ptr, WAIT_MOVE);
        break;
    case WAIT_MOVE:
        loop_speed_movable_object_2d(mo_2d_ptr, MOVE);
        break;
    case WAIT_RICOCHET:
        loop_speed_movable_object_2d(mo_2d_ptr, RICOCHET);
        break;
    case MOVE:
    case RICOCHET:
        // x_in = mo_2d_ptr->bresenham.xn;
        // y_in = mo_2d_ptr->bresenham.yn;
        shift_movable_object_2d(mo_2d_ptr);
        detect_impact_movable_object_2d(mo_2d_ptr, x_min, y_min, x_max, y_max);
        break;
    default:
        break;
    }
    switch (get_status_movable_object_2d(mo_2d_ptr))
    {
    case IMPACT_Y_TOP:
    case IMPACT_Y_BOTTOM:
        mo_2d_ptr->bresenham.x0 = mo_2d_ptr->bresenham.xn = x_in;
        mo_2d_ptr->bresenham.y0 = mo_2d_ptr->bresenham.yn = y_in;
        mo_2d_ptr->bresenham.sy *= -1;
        // Noting the biggest difference.
        mo_2d_ptr->bresenham.e2 = 0;
        // Next status.
        set_status_movable_object_2d(mo_2d_ptr, RICOCHET);
        shift_movable_object_2d(mo_2d_ptr);
        break;

    case IMPACT_X_LEFT:
    case IMPACT_X_RIGHT:
        mo_2d_ptr->bresenham.x0 = mo_2d_ptr->bresenham.xn = x_in;
        mo_2d_ptr->bresenham.sx *= -1;
        mo_2d_ptr->bresenham.y0 = mo_2d_ptr->bresenham.yn = y_in;
        // Noting the biggest difference.
        mo_2d_ptr->bresenham.e2 = 0;
        // Next status.
        set_status_movable_object_2d(mo_2d_ptr, RICOCHET);
        shift_movable_object_2d(mo_2d_ptr);
        break;

    case IMPACT_X_RIGHT_Y_TOP:
    case IMPACT_X_RIGHT_Y_BOTTOM:
    case IMPACT_X_LEFT_Y_BOTTOM:
    case IMPACT_X_LEFT_Y_TOP:
        mo_2d_ptr->bresenham.x0 = mo_2d_ptr->bresenham.xn = x_in;
        mo_2d_ptr->bresenham.sx *= -1;
        mo_2d_ptr->bresenham.y0 = mo_2d_ptr->bresenham.yn = y_in;
        mo_2d_ptr->bresenham.sy *= -1;
        // Noting the biggest difference.
        mo_2d_ptr->bresenham.e2 = 0;
        // Next status.
        set_status_movable_object_2d(mo_2d_ptr, RICOCHET);
        shift_movable_object_2d(mo_2d_ptr);
        break;

    default:
        switch (before_status_enum)
        {
        case MOVE:
            set_status_movable_object_2d(mo_2d_ptr, WAIT_MOVE);
            break;
        case RICOCHET:
            set_status_movable_object_2d(mo_2d_ptr, WAIT_RICOCHET);
            break;
        default:
            break;
        }
        break;
    }
}

/*!
    \brief      Shift over the movable object 2D.
    \param[in]  mo_2d_ptr
    \param[out] mo_2d_ptr
    \retval     none
*/
void shift_movable_object_2d(movable_object_2d_ptr mo_2d_ptr)
{
    int carry_xyn_2_xy1 = FALSE;

    mo_2d_ptr->bresenham.xnb = mo_2d_ptr->bresenham.xn;
    mo_2d_ptr->bresenham.ynb = mo_2d_ptr->bresenham.yn;
    // If we are asked to move forward, and xn is equal to x1, ...
    if ((mo_2d_ptr->bresenham.xn == mo_2d_ptr->bresenham.x1) && (mo_2d_ptr->bresenham.yn == mo_2d_ptr->bresenham.y1))
    {
        // ... then we are dragging x1 along with xn.
        carry_xyn_2_xy1 = TRUE;
    }
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
    if (carry_xyn_2_xy1 == TRUE)
    {
        mo_2d_ptr->bresenham.x1 = mo_2d_ptr->bresenham.xn;
        mo_2d_ptr->bresenham.y1 = mo_2d_ptr->bresenham.yn;
    }
}

/*!
    \brief      Loop speed over the movable object 2D.
    \param[in]  mo_2d_ptr
    \param[in]  next_status_enum
    \param[out] mo_2d_ptr
    \retval     none
*/
void loop_speed_movable_object_2d(movable_object_2d_ptr mo_2d_ptr, movable_object_status_enum next_status_enum)
{
    if (mo_2d_ptr->bresenham.speed2 == 0)
    {
        mo_2d_ptr->bresenham.speed2 = mo_2d_ptr->bresenham.speed;
        set_status_movable_object_2d(mo_2d_ptr, next_status_enum);
    }
    else
    {
        mo_2d_ptr->bresenham.speed2--;
    }
}