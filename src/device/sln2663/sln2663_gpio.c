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

#include "device/sln2663/sln2663_gpio.h"
#include "device/sln2663/sln2663_rcu.h"

// ---------------------------------------------------------------------
// Private Constants
// ---------------------------------------------------------------------
/*!< description */

// ---------------------------------------------------------------------
// Private Prototypes
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// Public Bodies
// ---------------------------------------------------------------------
/*!
    \brief      Function that calculates the peripheral based on the GPIO port.
    \param[in]  gpio_port 
    \retval     rcu_periph_enum
*/
rcu_periph_enum calculate_rcu_periph(uint32_t gpio_port)
{
    rcu_periph_enum result = 0;

    switch (gpio_port)
    {
    case GPIOA:
        result = RCU_GPIOA;
        break;
    case GPIOB:
        result = RCU_GPIOB;
        break;
    case GPIOC:
        result = RCU_GPIOC;
        break;
    case GPIOD:
        result = RCU_GPIOD;
        break;
    case GPIOE:
        result = RCU_GPIOE;
        break;
    default:
        break;
    }
    return result;
}

// ---------------------------------------------------------------------
// Private Bodies
// ---------------------------------------------------------------------
