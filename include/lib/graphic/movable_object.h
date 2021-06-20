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
    STOP,                    /*!< STOP */
    SHOOT,                   /*!< SHOOT */
    MOVE,                    /*!< MOVE */
    RICOCHET,                /*!< RICOCHET */
    IMPACT_Y_TOP,            /*!< IMPACT 0 */
    IMPACT_X_RIGHT_Y_TOP,    /*!< IMPACT 1 */
    IMPACT_X_RIGHT,          /*!< IMPACT 2 */
    IMPACT_X_RIGHT_Y_BOTTOM, /*!< IMPACT 3 */
    IMPACT_Y_BOTTOM,         /*!< IMPACT 4 */
    IMPACT_X_LEFT_Y_BOTTOM,  /*!< IMPACT 5 */
    IMPACT_X_LEFT,           /*!< IMPACT 6 */
    IMPACT_X_LEFT_Y_TOP      /*!< IMPACT 7 */
} movable_object_status_enum;

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