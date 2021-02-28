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

#include "device\sln2663\sln2663_led_1615.h"

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
                           gd32vf103_gpio_led_ptr blue_led_ptr)
{
    led_1615_values_init((led_1615_ptr)led_device_ptr);
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
