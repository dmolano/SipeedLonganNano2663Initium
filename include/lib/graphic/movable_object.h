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

#ifndef __MOVABLE_OBJECT_H
#define __MOVABLE_OBJECT_H

// ---------------------------------------------------------------------
// Public Constants
// ---------------------------------------------------------------------
/* Movable object status enum */
typedef enum
{
    DEAD,         /*!< DEAD */
    STOP,         /*!< STOP */
    SHOOT,        /*!< SHOOT */
    MOVE,         /*!< MOVE */
    RICOCHET,     /*!< RICOCHET */
    WAIT_MOVE,    /*!< WAIT_MOVE*/
    WAIT_RICOCHET /*!< WAIT_RICOCHET*/
} movable_object_status_enum;

/*!< Total number of impact walls */
/*
            +-----------+
            |7    0    1|
            |           |
            |6    ·    2|
            |           |
            |5    4    3|
            +-----------+
*/
#define SIDE_IMPACT_WALL_TOTAL 8

/* Side impact*/
typedef enum
{
    Y_TOP,            /*!< 0 */
    X_RIGHT_Y_TOP,    /*!< 1 */
    X_RIGHT,          /*!< 2 */
    X_RIGHT_Y_BOTTOM, /*!< 3 */
    Y_BOTTOM,         /*!< 4 */
    X_LEFT_Y_BOTTOM,  /*!< 5 */
    X_LEFT,           /*!< 6 */
    X_LEFT_Y_TOP,     /*!< 7 */
    NONE_IMPACT       /*!< . */
} side_impact_enum;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif
// ---------------------------------------------------------------------
// Public Structures
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// Public Prototypes
// ---------------------------------------------------------------------
#endif // __MOVABLE_OBJECT_H