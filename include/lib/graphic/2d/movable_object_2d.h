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
/*!< description */

/* Side impact*/
typedef enum
{
    STOP,    /*!< STOP */
    INITIAL, /*!< INITIAL */
    MOVING,
    IMPACT
} movable_object_status_enum;

// ---------------------------------------------------------------------
// Public Structures
// ---------------------------------------------------------------------
/*!
    \brief      Movable Object 2D
*/
typedef struct _BRESENHAM_LOOP_INFO_STRUCT
{
    int dx, dy, p, x, y, s1, s2, e, i, swap;
} bresenham_loop_info, *bresenham_loop_info_ptr;

typedef struct _DDA_LOOP_INFO_STRUCT
{

} dda_loop_info, *dda_loop_info_ptr;

/*!
    \brief      Movable Object 2D
*/
typedef struct _MOVABLE_OBJECT_2D
{
    int x0;
    int y0;
    int x1;
    int y1;
    uint16_t color;
    movable_object_status_enum mo_status;
    bresenham_loop_info bresenham;
    struct _MOVABLE_OBJECT_2D *next_movable_object_2d_ptr;
} movable_object_2d, *movable_object_2d_ptr;

// ---------------------------------------------------------------------
// Public Prototypes
// ---------------------------------------------------------------------
/*!
    \brief      function
    \param[in]  none
    \param[out] none
    \retval     none
*/

#endif // __MOVABLE_OBJECT_2D_H