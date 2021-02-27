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
#include "led\led_1615.h"

#ifndef __SLN2663_LED_1615_H
#define __SLN2663_LED_1615_H

// ---------------------------------------------------------------------
// Public Constants
// ---------------------------------------------------------------------
/*!< description */

// ---------------------------------------------------------------------
// Public Structures
// ---------------------------------------------------------------------
/*!
    \brief      LED_1615 in http://dl.sipeed.com/shareURL/LONGAN/Nano/HDK/Longan%20Nano%202663/Longan nano 2663(Schematic).pdf
*/
typedef led_1615 sln2663_led_1615, *sln2663_led_1615_ptr;

// ---------------------------------------------------------------------
// Public Prototypes
// ---------------------------------------------------------------------
/*!
    \brief      led 1615 on board init function
    \param[in]  sln2663_led_1615_ptr led data
    \param[out] sln2663_led_1615_ptr
    \retval     none
*/
void sln2663_led_1615_init(sln2663_led_1615_ptr led);

#endif // __SLN2663_LED_1615_H