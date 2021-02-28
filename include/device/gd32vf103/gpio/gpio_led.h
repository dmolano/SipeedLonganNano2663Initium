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
#include "device\led\single_led.h"

#ifndef __GD32VF103_GPIO_LED_H
#define __GD32VF103_GPIO_LED_H

// ---------------------------------------------------------------------
// Public Constants
// ---------------------------------------------------------------------
/*!< description */

// ---------------------------------------------------------------------
// Public Structures
// ---------------------------------------------------------------------
/*!
    \brief      Single LED data. https://en.wikipedia.org/wiki/Light-emitting_diode#Physics_of_light_production_and_emission
*/
typedef struct _GD32VF103_GPIO_LED
{
    single_led_ptr led_ptr;                /*!< Led device */
} gd32vf103_gpio_led, *gd32vf103_gpio_led_ptr;


// ---------------------------------------------------------------------
// Public Prototypes
// ---------------------------------------------------------------------
/*!
    \brief      function
    \param[in]  none
    \param[out] none
    \retval     none
*/

#endif // __GD32VF103_GPIO_LED_H