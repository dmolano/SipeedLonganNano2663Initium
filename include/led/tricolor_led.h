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
#include "single_led.h"

#ifndef __SLN2663_TRICOLOR_LED_H
#define __SLN2663_TRICOLOR_LED_H

// ---------------------------------------------------------------------
// Public Constants
// ---------------------------------------------------------------------
#define TRI_LEDS 3 /*!< Number of LEDs */

// ---------------------------------------------------------------------
// Public Structures
// ---------------------------------------------------------------------
/*!
    \brief      Configuration of the PIN electrode.
*/
typedef enum _TRICOLOR_ARRAY
{
    FIRST,  /*!< first LED */
    SECOND, /*!< second LED */
    THIRD   /*!< third LED */
} tricolor_array;

/*!
    \brief      Tricolor LED data. https://en.wikipedia.org/wiki/Light-emitting_diode#RGB_tri-color
*/
typedef struct _TRICOLOR_LED
{
    single_led led[TRI_LEDS];
} tricolor_led, *tricolor_led_ptr;

// ---------------------------------------------------------------------
// Public Prototypes
// ---------------------------------------------------------------------
/*!
    \brief      function
    \param[in]  none
    \param[out] none
    \retval     none
*/

#endif // __SLN2663_TRICOLOR_LED_H