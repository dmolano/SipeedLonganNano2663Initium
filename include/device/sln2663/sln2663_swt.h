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
#include "device/swt/swt.h"
#include "device/sln2663/sln2663_gpio_swt.h"

#ifndef __SLN2663_SWT_H
#define __SLN2663_SWT_H

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
typedef swt sln2663_swt, *sln2663_swt_ptr;

// ---------------------------------------------------------------------
// Public Prototypes
// ---------------------------------------------------------------------
/*!
    \brief      Switch Pull-Up init function
    \param[in]  swt_device_ptr 
    \param[in]  swt_ptr 
    \param[out]  swt_device_ptr 
    \param[out]  swt_ptr 
    \retval     none
*/
void sln2663_swt_init(sln2663_swt_ptr swt_device_ptr,
                       sln2663_gpio_swt_ptr swt_ptr);

#endif // __SLN2663_SWT_H