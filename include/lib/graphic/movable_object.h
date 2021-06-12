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
    STOP,    /*!< STOP */
    SHOOT,   /*!< SHOOT */
    MOVE,    /*!< MOVE */
    IMPACT,  /*!< IMPACT */
    RICOCHET /*!< RICOCHET */
} movable_object_status_enum;

// ---------------------------------------------------------------------
// Public Structures
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// Public Prototypes
// ---------------------------------------------------------------------
#endif // __MOVABLE_OBJECT_H