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
#define TEST_BALL
#define MO_2D_TOTAL 100
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
/*!
    \brief      Find the mathematical sign of the reported number.
    \param[in]  num reported number.
    \param[out] none
    \retval     sign: 
*/
int calculate_sign_math(int num);

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

    sln2663_graphic_2d_init_graphic_2d(&graphic_2d, &(sln_data_ptr->tft.tft_dma));
    for (int index = 0; index < MO_2D_TOTAL; index++)
    {
        sln2663_graphic_2d_set_random_initial_position_movable_object(&graphic_2d, &mo_2d_list[index]);
        sln2663_graphic_2d_set_random_final_position_movable_object(&graphic_2d, &mo_2d_list[index]);
        // ------------------------>rrrrrggggggbbbbb
        mo_2d_list[index].color = 0b1111111111111111;
        mo_2d_list[index].mo_status = INITIAL;
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
#ifdef TEST_BALL
        // for (int index = 0; index < MO_2D_TOTAL; index++)
        // {
        //     sln2663_lcd_tft_setpixel(&(sln_data_ptr->tft.tft_dma), mo_2d_list[index].x0, mo_2d_list[index].y0, 0b1111111111111111);
        //     sln2663_lcd_tft_setpixel(&(sln_data_ptr->tft.tft_dma), mo_2d_list[index].x1, mo_2d_list[index].y1, 0b1111111111111111);
        // }
        sln2663_graphic_2d_loop_movable_objects(&graphic_2d);
        DELAY_ONE_SECOND;
#endif
    }
    return result;
}
