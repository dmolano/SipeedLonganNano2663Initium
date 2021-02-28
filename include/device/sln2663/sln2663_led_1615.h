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
#include "device\led\led_1615.h"
#include "device\gd32vf103\gpio\gpio_led.h"

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
    \brief      1615 LED SLN2663 init function
    \param[in]  led_device_ptr 
    \param[in]  red_led_ptr 
    \param[in]  green_led_ptr 
    \param[in]  blue_led_ptr 
    \param[out]  led_device_ptr 
    \param[out]  red_led_ptr 
    \param[out]  green_led_ptr 
    \param[out]  blue_led_ptr 
    \retval     none
*/
void sln2663_led_1615_init(sln2663_led_1615_ptr led_device_ptr,
                           gd32vf103_gpio_led_ptr red_led_ptr,
                           gd32vf103_gpio_led_ptr green_led_ptr,
                           gd32vf103_gpio_led_ptr blue_led_ptr);

#endif // __SLN2663_LED_1615_H