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
void movable_object_2d_calculate_errors(movable_object_2d_ptr mo_2d_ptr);

/*!
    \brief      Detect possible impact of movable object.
    \param[in]  mo_2d_ptr movable object.
    \param[in]  x_min
    \param[in]  y_min
    \param[in]  x_max
    \param[in]  y_max
    \param[out] mo_2d_ptr
    \retval     side_impact_enum
*/
side_impact_enum movable_object_2d_detect_impact(movable_object_2d_ptr mo2d_ptr, uint32_t x_min, uint32_t y_min, uint32_t x_max, uint32_t y_max);

/*!
    \brief      Shift over the movable object 2D.
    \param[in]  mo_2d_ptr
    \param[in]  x_min
    \param[in]  y_min
    \param[in]  x_max
    \param[in]  y_max
    \param[out] mo_2d_ptr
    \retval     none
*/
void movable_object_2d_shift(movable_object_2d_ptr mo_2d_ptr, uint32_t x_min, uint32_t y_min, uint32_t x_max, uint32_t y_max);

/*!
    \brief      Move over the alive movable object 2D.
    \param[in]  mo_2d_ptr
    \param[in]  x_min
    \param[in]  y_min
    \param[in]  x_max
    \param[in]  y_max
    \param[out] mo_2d_ptr
    \retval     none
*/
void movable_object_2d_move_alive(movable_object_2d_ptr mo_2d_ptr, uint32_t x_min, uint32_t y_min, uint32_t x_max, uint32_t y_max);

/*!
    \brief      Loop speed over the movable object 2D.
    \param[in]  mo_2d_ptr
    \param[in]  next_status_enum
    \param[out] mo_2d_ptr
    \retval     none
*/
void movable_object_2d_move_speed(movable_object_2d_ptr mo_2d_ptr, movable_object_status_enum next_status_enum);

/*!
    \brief      Check if must wait for speed the movable object 2D.
    \param[in]  mo_2d_ptr
    \param[out] none
    \retval     TRUE if speed == MAX_SPEED
*/
uint8_t movable_object_2d_check_must_wait_for_speed(movable_object_2d_ptr mo_2d_ptr);

// ---------------------------------------------------------------------
// Public Bodies
// ---------------------------------------------------------------------
/*!
    \brief      Get color of movable object 2D.
    \param[in]  mo_2d_ptr
    \param[out] none
    \retval     uint16_t
*/
uint16_t movable_object_2d_get_color(movable_object_2d_ptr mo_2d_ptr)
{
    return mo_2d_ptr->color;
}

/*!
    \brief      Get status of movable object 2D.
    \param[in]  mo_2d_ptr
    \param[out] none
    \retval     movable_object_status_enum
*/
movable_object_status_enum movable_object_2d_get_status(movable_object_2d_ptr mo_2d_ptr)
{
    return mo_2d_ptr->mo_status_enum;
}

/*!
    \brief      Move over the movable object 2D.
    \param[in]  mo_2d_ptr
    \param[in]  x_min
    \param[in]  y_min
    \param[in]  x_max
    \param[in]  y_max
    \param[out] mo_2d_ptr
    \retval     none
*/
void movable_object_2d_move(movable_object_2d_ptr mo_2d_ptr, uint32_t x_min, uint32_t y_min, uint32_t x_max, uint32_t y_max)
{
    if (movable_object_2d_get_status(mo_2d_ptr) != DEAD)
    {
        movable_object_2d_move_alive(mo_2d_ptr, x_min, y_min, x_max, y_max);
    }
}

/*!
    \brief      Set color of movable object 2D.
    \param[in]  mo_2d_ptr
    \param[in]  color
    \param[out] mo_2d_ptr
    \retval     none
*/
void movable_object_2d_set_color(movable_object_2d_ptr mo_2d_ptr, uint16_t color)
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
void movable_object_2d_set_speed(movable_object_2d_ptr mo_2d_ptr, uint8_t speed)
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
void movable_object_2d_set_status(movable_object_2d_ptr mo_2d_ptr, movable_object_status_enum status_enum)
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
void movable_object_2d_calculate_errors(movable_object_2d_ptr mo_2d_ptr)
{
    mo_2d_ptr->bresenham.err = (mo_2d_ptr->bresenham.dx > mo_2d_ptr->bresenham.dy ? mo_2d_ptr->bresenham.dx : -mo_2d_ptr->bresenham.dy) / 2;
    mo_2d_ptr->bresenham.e2 = 0;
}

/*!
    \brief      Detect possible impact of movable object.
    \param[in]  mo_2d_ptr movable object.
    \param[in]  side_impact
    \param[in]  x_in
    \param[in]  y_in
    \param[out] mo_2d_ptr
    \retval     none
*/
void movable_object_2d_treat_impact(movable_object_2d_ptr mo_2d_ptr, side_impact_enum side_impact, int x_in, int y_in)
{
    switch (side_impact)
    {
    case Y_TOP:
    case Y_BOTTOM:
        mo_2d_ptr->bresenham.x0 = mo_2d_ptr->bresenham.xn = x_in;
        mo_2d_ptr->bresenham.y0 = mo_2d_ptr->bresenham.yn = y_in;
        mo_2d_ptr->bresenham.sy *= -1;
        // Noting the biggest difference.
        mo_2d_ptr->bresenham.e2 = 0;
        break;

    case X_LEFT:
    case X_RIGHT:
        mo_2d_ptr->bresenham.x0 = mo_2d_ptr->bresenham.xn = x_in;
        mo_2d_ptr->bresenham.sx *= -1;
        mo_2d_ptr->bresenham.y0 = mo_2d_ptr->bresenham.yn = y_in;
        // Noting the biggest difference.
        mo_2d_ptr->bresenham.e2 = 0;
        break;

    case X_RIGHT_Y_TOP:
    case X_RIGHT_Y_BOTTOM:
    case X_LEFT_Y_BOTTOM:
    case X_LEFT_Y_TOP:
        mo_2d_ptr->bresenham.x0 = mo_2d_ptr->bresenham.xn = x_in;
        mo_2d_ptr->bresenham.sx *= -1;
        mo_2d_ptr->bresenham.y0 = mo_2d_ptr->bresenham.yn = y_in;
        mo_2d_ptr->bresenham.sy *= -1;
        // Noting the biggest difference.
        mo_2d_ptr->bresenham.e2 = 0;
        break;
    default:
        break;
    }
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
side_impact_enum movable_object_2d_detect_impact(movable_object_2d_ptr mo2d_ptr, uint32_t x_min, uint32_t y_min, uint32_t x_max, uint32_t y_max)
{
    side_impact_enum result = NONE_IMPACT;

    if (mo2d_ptr->bresenham.xn < (int)x_min)
    {
        if (mo2d_ptr->bresenham.yn < (int)y_min)
        {
            result = X_LEFT_Y_TOP;
        }
        else if (mo2d_ptr->bresenham.yn > (int)y_max)
        {
            result = X_LEFT_Y_BOTTOM;
        }
        else
        {
            result = X_LEFT;
        }
    }
    else if (mo2d_ptr->bresenham.xn > (int)x_max)
    {
        if (mo2d_ptr->bresenham.yn < (int)y_min)
        {
            result = X_RIGHT_Y_TOP;
        }
        else if (mo2d_ptr->bresenham.yn > (int)y_max)
        {
            result = X_RIGHT_Y_BOTTOM;
        }
        else
        {
            result = X_RIGHT;
        }
    }
    else if (mo2d_ptr->bresenham.yn < (int)y_min)
    {
        result = Y_TOP;
    }
    else if (mo2d_ptr->bresenham.yn > (int)y_max)
    {
        result = Y_BOTTOM;
    }
    return result;
}

/*!
    \brief      Move over the alive movable object 2D.
    \param[in]  mo_2d_ptr
    \param[in]  x_min
    \param[in]  y_min
    \param[in]  x_max
    \param[in]  y_max
    \param[out] mo_2d_ptr
    \retval     none
*/
void movable_object_2d_move_alive(movable_object_2d_ptr mo_2d_ptr, uint32_t x_min, uint32_t y_min, uint32_t x_max, uint32_t y_max)
{
    side_impact_enum side_impact;
    int x_in = 0, y_in = 0;

    switch (movable_object_2d_get_status(mo_2d_ptr))
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
        movable_object_2d_calculate_errors(mo_2d_ptr);
        // Speed
        mo_2d_ptr->bresenham.speed2 = READY_TO_SHIFT;
        // Next status: ¿has it speed?
        if (movable_object_2d_check_must_wait_for_speed(mo_2d_ptr) == TRUE)
        {
            movable_object_2d_set_status(mo_2d_ptr, WAIT_MOVE); // WAIT_MOVE
        }
        else
        {
            movable_object_2d_set_status(mo_2d_ptr, MOVE); // MOVE
        }
        break;
    case WAIT_MOVE:
        movable_object_2d_move_speed(mo_2d_ptr, MOVE);
        break;
    case WAIT_RICOCHET:
        movable_object_2d_move_speed(mo_2d_ptr, RICOCHET);
        break;
    case MOVE:
        x_in = mo_2d_ptr->bresenham.xn;
        y_in = mo_2d_ptr->bresenham.yn;
        movable_object_2d_shift(mo_2d_ptr, x_min, y_min, x_max, y_max);                       // Shift
        side_impact = movable_object_2d_detect_impact(mo_2d_ptr, x_min, y_min, x_max, y_max); // Impact
        if (side_impact != NONE_IMPACT)
        {
            movable_object_2d_treat_impact(mo_2d_ptr, side_impact, x_in, y_in);
            if ((side_impact != X_RIGHT_Y_TOP) &&
                (side_impact != X_RIGHT_Y_BOTTOM) &&
                (side_impact != X_LEFT_Y_BOTTOM) &&
                (side_impact != X_LEFT_Y_TOP))
            {
                movable_object_2d_shift(mo_2d_ptr, x_min, y_min, x_max, y_max);
            }
            // Next status: ¿has it speed?
            if (movable_object_2d_check_must_wait_for_speed(mo_2d_ptr) == TRUE)
            {
                movable_object_2d_set_status(mo_2d_ptr, WAIT_RICOCHET); // WAIT_MOVE
            }
            else
            {
                movable_object_2d_set_status(mo_2d_ptr, RICOCHET); // MOVE
            }
        }
        else
        {
            // Next status: ¿has it speed?
            if (movable_object_2d_check_must_wait_for_speed(mo_2d_ptr) == TRUE)
            {
                movable_object_2d_set_status(mo_2d_ptr, WAIT_MOVE); // WAIT_MOVE
            }
            else
            {
                movable_object_2d_set_status(mo_2d_ptr, MOVE); // MOVE
            }
        }
        break;
    case RICOCHET:
        x_in = mo_2d_ptr->bresenham.xn;
        y_in = mo_2d_ptr->bresenham.yn;
        movable_object_2d_shift(mo_2d_ptr, x_min, y_min, x_max, y_max); // Shift
        // Next status: ¿has it speed?
        side_impact = movable_object_2d_detect_impact(mo_2d_ptr, x_min, y_min, x_max, y_max); // Impact
        if (side_impact != NONE_IMPACT)
        {
            movable_object_2d_treat_impact(mo_2d_ptr, side_impact, x_in, y_in);
            if ((side_impact != X_RIGHT_Y_TOP) &&
                (side_impact != X_RIGHT_Y_BOTTOM) &&
                (side_impact != X_LEFT_Y_BOTTOM) &&
                (side_impact != X_LEFT_Y_TOP))
            {
                movable_object_2d_shift(mo_2d_ptr, x_min, y_min, x_max, y_max);
            }
        }
        if (movable_object_2d_check_must_wait_for_speed(mo_2d_ptr) == TRUE)
        {
            movable_object_2d_set_status(mo_2d_ptr, WAIT_RICOCHET); // WAIT_RICOCHET
        }
        else
        {
            movable_object_2d_set_status(mo_2d_ptr, RICOCHET); // MOVE
        }
        break;
    default:
        break;
    }
}

/*!
    \brief      Shift over the movable object 2D.
    \param[in]  mo_2d_ptr
    \param[in]  x_min
    \param[in]  y_min
    \param[in]  x_max
    \param[in]  y_max
    \param[out] mo_2d_ptr
    \retval     none
*/
void movable_object_2d_shift(movable_object_2d_ptr mo_2d_ptr, uint32_t x_min, uint32_t y_min, uint32_t x_max, uint32_t y_max)
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
    \brief      Check if must wait for speed the movable object 2D.
    \param[in]  mo_2d_ptr
    \param[out] none
    \retval     TRUE if speed == MAX_SPEED
*/
uint8_t movable_object_2d_check_must_wait_for_speed(movable_object_2d_ptr mo_2d_ptr)
{
    uint8_t result = FALSE;

    if ((mo_2d_ptr->bresenham.speed != MAX_SPEED) && (mo_2d_ptr->bresenham.speed2 != READY_TO_SHIFT))
    {
        result = TRUE;
    }
    return result;
}

/*!
    \brief      Move speed over the movable object 2D.
    \param[in]  mo_2d_ptr
    \param[in]  next_status_enum
    \param[out] mo_2d_ptr
    \retval     none
*/
void movable_object_2d_move_speed(movable_object_2d_ptr mo_2d_ptr, movable_object_status_enum next_status_enum)
{
    if (mo_2d_ptr->bresenham.speed2 == READY_TO_SHIFT)
    {
        mo_2d_ptr->bresenham.speed2 = mo_2d_ptr->bresenham.speed;
        movable_object_2d_set_status(mo_2d_ptr, next_status_enum);
    }
    else
    {
        mo_2d_ptr->bresenham.speed2--;
    }
}