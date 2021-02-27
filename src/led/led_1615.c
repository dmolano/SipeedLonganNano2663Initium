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

// ---------------------------------------------------------------------
// Private Constants
// ---------------------------------------------------------------------
/*!< description */

// ---------------------------------------------------------------------
// Private Prototypes
// ---------------------------------------------------------------------
/*!
    \brief      1615 LED physics value init function
    \param[in]  led_1615_ptr 
    \param[out] led_1615_ptr
    \retval     none
*/
void led_1615_physics_values_init(led_1615_ptr led_ptr);

// ---------------------------------------------------------------------
// Public Bodies
// ---------------------------------------------------------------------
/*!
    \brief      Returns red LED function
    \param[in]  led_1615_ptr 
    \param[out] none
    \retval     single_led_ptr
*/
single_led_ptr led_1615_get_red_led(led_1615_ptr led_ptr)
{
    return rgb_led_get_red((rgb_led_ptr)led_ptr);
}

/*!
    \brief      1615 LED physics value init function
    \param[in]  led_1615_ptr 
    \param[out] led_1615_ptr
    \retval     none
*/
void led_1615_physics_values_init(led_1615_ptr led_ptr)
{
    single_led_ptr single_led_red_ptr = rgb_led_get_red((rgb_led_ptr)led_ptr);

    single_led_red_ptr->min_led_voltage = 20; // 2,0 v
    single_led_red_ptr->max_led_voltage = 22; // 2,2 v
    single_led_red_ptr->min_led_voltage = 50; // 5 mA
    single_led_red_ptr->min_led_voltage = 200; // 20 mA
    single_led_red_ptr->breakdown_voltage = 50; // 5 v
}

/*!
    \brief      1615 LED physics value init function
    \param[in]  led_1615_ptr 
    \param[out] led_1615_ptr
    \retval     none
*/
void led_1615_values_init(led_1615_ptr led_ptr)
{
    rgb_led_values_init((rgb_led_ptr)led_ptr);
    led_1615_physics_values_init(led_ptr);
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
