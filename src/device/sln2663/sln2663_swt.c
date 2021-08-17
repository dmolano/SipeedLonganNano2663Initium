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

#include "device/sln2663/sln2663_swt.h"

// ---------------------------------------------------------------------
// Private Constants
// ---------------------------------------------------------------------
#define SWT_FREQUENCY GPIO_OSPEED_50MHZ /*!< Switch Frequency */

// ---------------------------------------------------------------------
// Private Prototypes
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// Public Bodies
// ---------------------------------------------------------------------
/*!
    \brief      Switch Pull-Up init function
    \param[in]  swt_device_ptr 
    \param[in]  swt_ptr 
    \param[in]  gpio_port 
    \param[in]  gpio_pin 
    \param[out]  swt_device_ptr 
    \param[out]  swt_ptr 
    \retval     none
*/
void sln2663_swt_pull_up_init(sln2663_swt_ptr swt_device_ptr,
                              sln2663_gpio_swt_ptr swt_ptr,
                              uint32_t gpio_port,
                              uint32_t gpio_pin)
{
    sln2663_gpio_swt_init(swt_device_ptr,
                          swt_ptr,
                          gpio_port,
                          GPIO_MODE_IPU,
                          gpio_pin,
                          SWT_FREQUENCY);
    swt_ptr->binary_states.on = RESET;
    swt_ptr->binary_states.off = SET;
}

/*!
    \brief      Switch Pull-Down init function
    \param[in]  swt_device_ptr 
    \param[in]  swt_ptr 
    \param[in]  gpio_port 
    \param[in]  gpio_pin 
    \param[out]  swt_device_ptr 
    \param[out]  swt_ptr 
    \retval     none
*/
void sln2663_swt_pull_down_init(sln2663_swt_ptr swt_device_ptr,
                                sln2663_gpio_swt_ptr swt_ptr,
                                uint32_t gpio_port,
                                uint32_t gpio_pin)
{
    sln2663_gpio_swt_init(swt_device_ptr,
                          swt_ptr,
                          gpio_port,
                          GPIO_MODE_IPD,
                          gpio_pin,
                          SWT_FREQUENCY);
    swt_ptr->binary_states.on = SET;
    swt_ptr->binary_states.off = RESET;
}
// ---------------------------------------------------------------------
// Private Bodies
// ---------------------------------------------------------------------
