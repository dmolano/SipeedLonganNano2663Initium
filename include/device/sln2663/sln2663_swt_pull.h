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
#include "device/led/led_1615.h"
#include "device/sln2663/sln2663_gpio_led.h"

#ifndef __SLN2663_SWT_PULL_UP_H
#define __SLN2663_SWT_PULL_UP_H

// ---------------------------------------------------------------------
// Public Constants
// ---------------------------------------------------------------------
/*!< description */

// ---------------------------------------------------------------------
// Public Structures
// ---------------------------------------------------------------------
/*!
    \brief      Switch over pull-up resistor https://en.wikipedia.org/wiki/Pull-up_resistor
*/
typedef swt_pull sln2663_swt_pull_up, *sln2663_swt_pull_up_ptr;

/*!
    \brief      Switch over pull-down resistor https://en.wikipedia.org/wiki/Pull-up_resistor
*/
typedef swt_pull sln2663_swt_pull_down, *sln2663_swt_pull_down_ptr;
// ---------------------------------------------------------------------
// Public Prototypes
// ---------------------------------------------------------------------
/*!
    \brief      Switch Pull-Up init function
    \param[in]  swt_pull_up_device_ptr 
    \param[in]  swt_pull_up_ptr 
    \param[out]  swt_pull_up_device_ptr 
    \param[out]  swt_pull_up_ptr 
    \retval     none
*/
void sln2663_swt_pull_up_init(sln2663_swt_pull_up_ptr swt_pull_up_device_ptr,
                       sln2663_gpio_swt_pull_ptr swt_pull_ptr);

/*!
    \brief      Switch Pull-Down init function
    \param[in]  swt_pull_down_device_ptr 
    \param[in]  swt_pull_down_ptr 
    \param[out]  swt_pull_down_device_ptr 
    \param[out]  swt_pull_down_ptr 
    \retval     none
*/
void sln2663_swt_pull_up_init(sln2663_swt_pull_down_ptr swt_pull_down_device_ptr,
                       sln2663_gpio_swt_pull_ptr swt_pull_ptr);
#endif // __SLN2663_SWT_PULL_UP_H