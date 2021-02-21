/* 
 * This file is part of the Sipeed Longan Nano Initium.
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

#ifndef __SLN2663_TIME_H
#define __SLN2663_TIME_H

// ---------------------------------------------------------------------
// Public Constants
// ---------------------------------------------------------------------
#define ONE_SECOND_TIME 1000 /*!< in milliseconds */

// ---------------------------------------------------------------------
// Public Prototypes
// ---------------------------------------------------------------------

/*!
    \brief      delay a time in milliseconds
    \param[in]  count: count in milliseconds
    \param[out] none
    \retval     none
*/
void time_delay_ms(uint32_t count);

#endif // __SLN2663_TIME_H