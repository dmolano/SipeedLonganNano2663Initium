/* 
 * This file is part of the Sipeed Longan Nano Initium.
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

#include "device\sln2663\sln2663.h"
#include "device\sln2663\sln2663_led_1615.h"
#include "device\sln2663\sln2663_time.h"

// ---------------------------------------------------------------------
// Public Constants
// ---------------------------------------------------------------------
#define RED_LED_1615_OB gpio_red_led_1615_on_board     /*!< red LED_1615 on board (OB) */
#define GREEN_LED_1615_OB gpio_green_led_1615_on_board /*!< green LED_1615 on board (OB) */
#define BLUE_LED_1615_OB gpio_blue_led_1615_on_board   /*!< blue LED_1615 on board (OB) */

// ---------------------------------------------------------------------
// Public Structures
// ---------------------------------------------------------------------
/*!
    \brief      Sipeed Longan Nano 2663 data (http://dl.sipeed.com/shareURL/LONGAN/Nano)
*/
typedef struct _SLN2663_DATA
{
    sln2663_led_1615 led_1615_on_board;            /*!< Longan nano 2663(Schematic).pdf */
    sln2663_gpio_led gpio_red_led_1615_on_board;   /*!< http://dl.sipeed.com/shareURL/LONGAN/Nano/DOC/GD32VF103_User_Manual_EN_V1.2.pdf#7.-General-purpose and alternate-function I/Os (GPIO and AFIO) */
    sln2663_gpio_led gpio_green_led_1615_on_board; /*!< http://dl.sipeed.com/shareURL/LONGAN/Nano/DOC/GD32VF103_User_Manual_EN_V1.2.pdf#7.-General-purpose and alternate-function I/Os (GPIO and AFIO) */
    sln2663_gpio_led gpio_blue_led_1615_on_board;  /*!< http://dl.sipeed.com/shareURL/LONGAN/Nano/DOC/GD32VF103_User_Manual_EN_V1.2.pdf#7.-General-purpose and alternate-function I/Os (GPIO and AFIO) */
} sln2663, *sln2663_ptr;
