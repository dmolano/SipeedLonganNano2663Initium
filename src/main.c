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

#include "main.h"

// ---------------------------------------------------------------------
// Private Constants
// ---------------------------------------------------------------------
#define FOREVER 1 /*!< for all time */
// LEDS 1615
#define TURN_ON_RED_LED1 sln2663_gpio_led_turn_on(&(sln_data_ptr->RED_LED1))
#define TURN_OFF_RED_LED1 sln2663_gpio_led_turn_off(&(sln_data_ptr->RED_LED1))
#define TURN_ON_GREEN_LED1 sln2663_gpio_led_turn_on(&(sln_data_ptr->GREEN_LED1))
#define TURN_OFF_GREEN_LED1 sln2663_gpio_led_turn_off(&(sln_data_ptr->GREEN_LED1))
#define TURN_ON_BLUE_LED1 sln2663_gpio_led_turn_on(&(sln_data_ptr->BLUE_LED1))
#define TURN_OFF_BLUE_LED1 sln2663_gpio_led_turn_off(&(sln_data_ptr->BLUE_LED1))
// Test
//#define TEST_FLASH
#define TEST_MO
// Total of Movable object 2D.
#define MO_2D_TOTAL 20
// Background color.
#define BACKGROUND_COLOR BLACK
// Collision color.
#define COLLISION_COLOR RED
// ---------------------------------------------------------------------
// Private Variables
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// Private Prototypes
// ---------------------------------------------------------------------
/*!
    \brief      main init function
    \param[in]  sln_data_ptr Sipeed Longan Nano data
    \param[out] none
    \retval     system error
*/
int sln2663_main_init(sln2663_ptr sln_data_ptr);

/*!
    \brief      main loop function
    \param[in]  sln_data_ptr Sipeed Longan Nano data
    \param[out] none
    \retval     system error
*/
int sln2663_main_loop(sln2663_ptr sln_data_ptr);

// ---------------------------------------------------------------------
// Bodies
// ---------------------------------------------------------------------
/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
    sln2663 sln_data;
    int result;

    result = sln2663_main_init(&sln_data);
    if (result == NO_ERROR_INIT_SLN2663)
    {
        result = sln2663_main_loop(&sln_data);
    }
    return result;
}

/*!
    \brief      main init function
    \param[in]  sln_data_ptr Sipeed Longan Nano data
    \param[out] none
    \retval     system error
*/
int sln2663_main_init(sln2663_ptr sln_data_ptr)
{
    int result = NO_ERROR_INIT_SLN2663;

    // LED1 --> LED1615
    sln2663_led1_init(&(sln_data_ptr->led1.device),
                      &(sln_data_ptr->led1.gpio_red),
                      &(sln_data_ptr->led1.gpio_green),
                      &(sln_data_ptr->led1.gpio_blue));
    // TFT (DMA) --> LH096T-IG01
    sln2663_tft_dma_init(&(sln_data_ptr->tft.device),
                         &(sln_data_ptr->tft.tft_dma));
    // Clear LCD
    sln2663_lcd_tft_clear(&(sln_data_ptr->tft.tft_dma), BACKGROUND_COLOR);
    return result;
}

/*!
    \brief      main loop function
    \param[in]  sln_data_ptr Sipeed Longan Nano data
    \param[out] none
    \retval     system error
*/
int sln2663_main_loop(sln2663_ptr sln_data_ptr)
{
    int result = NO_ERROR_INIT_SLN2663;
    int condition = FOREVER;

    sln2663_graphic_2d graphic_2d;
    movable_object_2d mo_2d_list[MO_2D_TOTAL];

    sln2663_graphic_2d_init_graphic(&graphic_2d, &(sln_data_ptr->tft.tft_dma));
    for (int index = 0; index < MO_2D_TOTAL; index++)
    {
        // (X0, Y0)
        sln2663_graphic_2d_set_random_initial_position_movable_object(&graphic_2d, &mo_2d_list[index]);
        // (X1, Y1)
        sln2663_graphic_2d_set_random_final_position_movable_object(&graphic_2d, &mo_2d_list[index]);
        // Color
        sln2663_graphic_2d_set_color_movable_object(&mo_2d_list[index], WHITE);
        // Initial status = SHOOT
        sln2663_graphic_2d_set_status_movable_object(&mo_2d_list[index], SHOOT);
        // Speed
        // sln2663_graphic_2d_set_speed_movable_object(&mo_2d_list[index], MAX_SPEED - (index * 5));
        sln2663_graphic_2d_set_speed_movable_object(&mo_2d_list[index], MAX_SPEED);
        // Add
        sln2663_graphic_2d_add_movable_object(&graphic_2d, &mo_2d_list[index]);
    }
    while (condition == FOREVER)
    {
#ifdef TEST_FLASH
        // ------------------------------------------>rrrrrggggggbbbbb
        sln2663_spi_tft_wait_idle();
        sln2663_lcd_tft_clear(&(sln_data_ptr->tft.tft_dma), 0b1111100000000000);
        TURN_ON_RED_LED1;
        DELAY_ONE_SECOND;
        TURN_OFF_RED_LED1;
        // ------------------------------------------>rrrrrggggggbbbbb
        sln2663_spi_tft_wait_idle();
        sln2663_lcd_tft_clear(&(sln_data_ptr->tft.tft_dma), 0b0000000000000000);
        // ------------------------------------------>rrrrrggggggbbbbb
        sln2663_spi_tft_wait_idle();
        sln2663_lcd_tft_clear(&(sln_data_ptr->tft.tft_dma), 0b1111100000000000);
        TURN_ON_RED_LED1;
        DELAY_HUNDRED_MILISECOND;
        TURN_OFF_RED_LED1;
        // ------------------------------------------>rrrrrggggggbbbbb
        sln2663_spi_tft_wait_idle();
        sln2663_lcd_tft_clear(&(sln_data_ptr->tft.tft_dma), 0b0000000000000000);

        DELAY_HALF_SECOND;

        // ------------------------------------------>rrrrrggggggbbbbb
        sln2663_spi_tft_wait_idle();
        sln2663_lcd_tft_clear(&(sln_data_ptr->tft.tft_dma), 0b0000011111100000);
        TURN_ON_GREEN_LED1;
        DELAY_ONE_SECOND;
        TURN_OFF_GREEN_LED1;
        // ------------------------------------------>rrrrrggggggbbbbb
        sln2663_spi_tft_wait_idle();
        sln2663_lcd_tft_clear(&(sln_data_ptr->tft.tft_dma), 0b0000000000000000);
        // ------------------------------------------>rrrrrggggggbbbbb
        sln2663_spi_tft_wait_idle();
        sln2663_lcd_tft_clear(&(sln_data_ptr->tft.tft_dma), 0b0000011111100000);
        TURN_ON_GREEN_LED1;
        DELAY_HUNDRED_MILISECOND;
        TURN_OFF_GREEN_LED1;
        // ------------------------------------------>rrrrrggggggbbbbb
        sln2663_spi_tft_wait_idle();
        sln2663_lcd_tft_clear(&(sln_data_ptr->tft.tft_dma), 0b0000000000000000);

        DELAY_HALF_SECOND;

        // ------------------------------------------>rrrrrggggggbbbbb
        sln2663_spi_tft_wait_idle();
        sln2663_lcd_tft_clear(&(sln_data_ptr->tft.tft_dma), 0b0000000000011111);
        TURN_ON_BLUE_LED1;
        DELAY_ONE_SECOND;
        TURN_OFF_BLUE_LED1;
        // ------------------------------------------>rrrrrggggggbbbbb
        sln2663_spi_tft_wait_idle();
        sln2663_lcd_tft_clear(&(sln_data_ptr->tft.tft_dma), 0b0000000000000000);
        // ------------------------------------------>rrrrrggggggbbbbb
        sln2663_spi_tft_wait_idle();
        sln2663_lcd_tft_clear(&(sln_data_ptr->tft.tft_dma), 0b0000000000011111);
        TURN_ON_BLUE_LED1;
        DELAY_HUNDRED_MILISECOND;
        TURN_OFF_BLUE_LED1;
        // ------------------------------------------>rrrrrggggggbbbbb
        sln2663_spi_tft_wait_idle();
        sln2663_lcd_tft_clear(&(sln_data_ptr->tft.tft_dma), 0b0000000000000000);

        DELAY_ONE_SECOND;
#endif
#ifdef TEST_MO
        sln2663_graphic_2d_loop_movable_objects(&graphic_2d, BACKGROUND_COLOR, COLLISION_COLOR);
        DELAY_TEN_MILISECOND;
#endif
    }
    return result;
}
