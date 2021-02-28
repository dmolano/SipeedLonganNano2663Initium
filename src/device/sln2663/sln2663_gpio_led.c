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

#include "device\sln2663\sln2663_gpio_led.h"
#include "device\sln2663\sln2663_rcu.h"

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
    \param[in]  led_ptr 
    \param[in]  rcu_periph 
    \param[in]  gpio_port 
    \param[in]  gpio_pin 
    \param[in]  gpio_frequency 
    \param[out]  led_ptr 
    \retval     none
*/
void sln2663_gpio_led_init(single_led_ptr led_device_ptr,
                           sln2663_gpio_led_ptr led_ptr,
                           rcu_periph_enum rcu_periph,
                           uint32_t gpio_port,
                           uint32_t gpio_pin,
                           uint32_t gpio_frequency)
{
    sln2663_rcu_periph_clock_enable(rcu_periph);
    gpio_init(gpio_port, GPIO_MODE_OUT_PP, gpio_frequency, gpio_pin);
    if (led_device_ptr->pin_to_host == ANODE)
    {
        GPIO_BOP(gpio_port) = gpio_pin;
    }
    else
    {
        GPIO_BC(gpio_port) = gpio_pin;
    }
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