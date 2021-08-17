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
#include "device/sln2663/sln2663_gpio_swt.h"
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
    \brief      SWT SLN2663 init function
    \param[in]  swt_device_ptr 
    \param[in]  swt_gpio_ptr 
    \param[in]  rcu_periph 
    \param[in]  gpio_port 
    \param[in]  gpio_mode 
    \param[in]  gpio_pin 
    \param[in]  gpio_frequency 
    \param[out]  swt_gpio_ptr 
    \retval     none
*/
void sln2663_gpio_swt_init(swt_ptr swt_device_ptr,
                           sln2663_gpio_swt_ptr swt_gpio_ptr,
                           uint32_t gpio_port,
                           uint32_t gpio_mode,
                           uint32_t gpio_pin,
                           uint32_t gpio_frequency)
{
    rcu_periph_enum rcu_periph;

    rcu_periph = calculate_rcu_periph(gpio_port);
    // Taking note of the parameters.
    swt_gpio_ptr->swt_device_ptr = swt_device_ptr;
    swt_gpio_ptr->rcu_periph = rcu_periph;
    swt_gpio_ptr->gpio_port = gpio_port;
    swt_gpio_ptr->gpio_mode = gpio_mode;
    swt_gpio_ptr->gpio_pin = gpio_pin;
    swt_gpio_ptr->gpio_frequency = gpio_frequency;
    swt_gpio_ptr->lastBinaryState = swt_gpio_ptr->binary_states.off;
    // Initializing the peripheral RCU.
    sln2663_rcu_periph_clock_enable(rcu_periph);
    // Preparing the port-pin pair with the frequency and output mode.
    gpio_init(gpio_port, gpio_mode, gpio_frequency, gpio_pin);
}

/*!
    \brief   Check if a switch is off.   
    \param[in]  swt_gpio_ptr 
    \param[out]  none 
    \retval     none
*/
bool sln2663_gpio_swt_is_off(sln2663_gpio_swt_ptr swt_gpio_ptr)
{
    bool result = FALSE;

    if (swt_gpio_ptr != NULL)
    {
        FlagStatus flag_status;

        flag_status = gpio_input_bit_get(swt_gpio_ptr->gpio_port, swt_gpio_ptr->gpio_pin);
        if (flag_status == swt_gpio_ptr->binary_states.off)
        {
            result = TRUE;
        }
    }
    return result;
}

/*!
    \brief   Check if a switch is on.   
    \param[in]  swt_gpio_ptr 
    \param[out]  none 
    \retval     none
*/
bool sln2663_gpio_swt_is_on(sln2663_gpio_swt_ptr swt_gpio_ptr)
{
    bool result = FALSE;

    if (swt_gpio_ptr != NULL)
    {
        FlagStatus flag_status;

        flag_status = gpio_input_bit_get(swt_gpio_ptr->gpio_port, swt_gpio_ptr->gpio_pin);
        if (flag_status == swt_gpio_ptr->binary_states.on)
        {
            result = TRUE;
        }
    }
    return result;
}

/*!
    \brief   Check if a switch is clicked.   
    \param[in]  swt_gpio_ptr 
    \param[out]  none 
    \retval     none
*/
bool sln2663_gpio_swt_is_clicked(sln2663_gpio_swt_ptr swt_gpio_ptr)
{
    bool result = FALSE;

    if (swt_gpio_ptr != NULL)
    {
        FlagStatus flag_status;

        flag_status = gpio_input_bit_get(swt_gpio_ptr->gpio_port, swt_gpio_ptr->gpio_pin);
        if (swt_gpio_ptr->lastBinaryState == swt_gpio_ptr->binary_states.off)
        {
            if (flag_status == swt_gpio_ptr->binary_states.on)
            {
                result = TRUE;
            }
        }
        swt_gpio_ptr->lastBinaryState = flag_status;
    }
    return result;
}

// ---------------------------------------------------------------------
// Private Bodies
// ---------------------------------------------------------------------
