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

#ifndef __SWT_H
#define __SWT_H

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
typedef struct _SWT
{
    uint8_t id; /*!< Switch identifier. */
    struct
    {
        FlagStatus on;
        FlagStatus off;
    } binary_states;      /*!< Binary states. */
} swt, *swt_ptr;

// ---------------------------------------------------------------------
// Public Prototypes
// ---------------------------------------------------------------------
/*!
    \brief      function
    \param[in]  none
    \param[out] none
    \retval     none
*/

#endif // __SWT_H