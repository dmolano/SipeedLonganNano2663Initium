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
#define RED_LED1_GPIO_PORT GPIOC   /*!< description */
#define GREEN_LED1_GPIO_PORT GPIOA /*!< description */
#define BLUE_LED1_GPIO_PORT GPIOA  /*!< description */

#define RED_LED1_GPIO_PIN GPIO_PIN_13  /*!< description */
#define GREEN_LED1_GPIO_PIN GPIO_PIN_1 /*!< description */
#define BLUE_LED1_GPIO_PIN GPIO_PIN_2  /*!< description */

#define LED1_FREQUENCY GPIO_OSPEED_50MHZ /*!< description */

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
    \param[out]  swt_device_ptr 
    \param[out]  swt_ptr 
    \retval     none
*/
void sln2663_swt_init(sln2663_swt_ptr swt_device_ptr,
                      sln2663_gpio_swt_ptr swt_ptr)
{
    // // DEVICE
    // led_1615_values_init((led_1615_ptr)led_device_ptr);
    // // RED
    // sln2663_gpio_led_init(rgb_led_get_red((rgb_led_ptr)led_device_ptr),
    //                       red_led_ptr,
    //                       RED_LED1_GPIO_PORT,
    //                       RED_LED1_GPIO_PIN,
    //                       LED1_FREQUENCY);
    // // GREEN
    // sln2663_gpio_led_init(rgb_led_get_green((rgb_led_ptr)led_device_ptr),
    //                       green_led_ptr,
    //                       GREEN_LED1_GPIO_PORT,
    //                       GREEN_LED1_GPIO_PIN,
    //                       LED1_FREQUENCY);
    // // BLUE
    // sln2663_gpio_led_init(rgb_led_get_blue((rgb_led_ptr)led_device_ptr),
    //                       blue_led_ptr,
    //                       BLUE_LED1_GPIO_PORT,
    //                       BLUE_LED1_GPIO_PIN,
    //                       LED1_FREQUENCY);
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
