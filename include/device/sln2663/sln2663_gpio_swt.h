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
#include "device/swt/swt.h"

#ifndef __SLN2663_GPIO_SWT_H
#define __SLN2663_GPIO_SWT_H

// ---------------------------------------------------------------------
// Public Constants
// ---------------------------------------------------------------------
/*!< description */

// ---------------------------------------------------------------------
// Public Structures
// ---------------------------------------------------------------------
/*!
    \brief      Switch. https://en.wikipedia.org/wiki/Switch
*/
typedef struct _SLN2663_GPIO_SWT
{
    swt_ptr swt_device_ptr; /*!< Switch device */
    rcu_periph_enum rcu_periph;
    uint32_t gpio_port;
    uint32_t gpio_mode;
    uint32_t gpio_pin;
    uint32_t gpio_frequency;
    struct
    {
        FlagStatus on;
        FlagStatus off;
    } binary_states; /*!< Binary states. */
} sln2663_gpio_swt, *sln2663_gpio_swt_ptr;

// ---------------------------------------------------------------------
// Public Prototypes
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
                           uint32_t gpio_frequency);

/*!
    \brief   Check if a switch is off.   
    \param[in]  swt_gpio_ptr 
    \param[out]  none 
    \retval     none
*/
bool sln2663_gpio_swt_is_off(sln2663_gpio_swt_ptr swt_gpio_ptr);

/*!
    \brief   Check if a switch is on.   
    \param[in]  swt_gpio_ptr 
    \param[out]  none 
    \retval     none
*/
bool sln2663_gpio_swt_is_on(sln2663_gpio_swt_ptr swt_gpio_ptr);

#endif // __SLN2663_GPIO_SWT_H