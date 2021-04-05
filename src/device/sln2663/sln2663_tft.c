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

#include "device\sln2663\sln2663_rcu.h"
#include "device\sln2663\sln2663_tft.h"

// ---------------------------------------------------------------------
// Private Constants
// ---------------------------------------------------------------------
#define SCL_TFT_RCU_PERIPH RCU_GPIOA
#define SDA_TFT_RCU_PERIPH RCU_GPIOA
#define CS_TFT_RCU_PERIPH RCU_GPIOB
#define RS_TFT_RCU_PERIPH RCU_GPIOB
#define RST_TFT_RCU_PERIPH RCU_GPIOB

#define SCL_TFT_GPIO_PORT GPIOA
#define SDA_TFT_GPIO_PORT GPIOA
#define CS_TFT_GPIO_PORT GPIOB
#define RS_TFT_GPIO_PORT GPIOB
#define RST_TFT_GPIO_PORT GPIOB

#define SCL_TFT_GPIO_PIN GPIO_PIN_5
#define SDA_TFT_GPIO_PIN GPIO_PIN_7
#define CS_TFT_GPIO_PIN GPIO_PIN_2
#define RS_TFT_GPIO_PIN GPIO_PIN_0
#define RST_TFT_GPIO_PIN GPIO_PIN_1 // RST=RES

#define SCL_TFT_GPIO_MODE GPIO_MODE_AF_PP
#define SDA_TFT_GPIO_MODE GPIO_MODE_AF_PP
#define CS_TFT_GPIO_MODE GPIO_MODE_OUT_PP
#define RS_TFT_GPIO_MODE GPIO_MODE_OUT_PP
#define RST_TFT_GPIO_MODE GPIO_MODE_OUT_PP

#define TFT_FREQUENCY GPIO_OSPEED_50MHZ

#define TFT_DISABLE_WAIT_MS 1
#define TFT_RESET_WAIT_MS 5


// ---------------------------------------------------------------------
// Private Prototypes
// ---------------------------------------------------------------------
/*!
    \brief      function
    \param[in]  none
    \param[out] none
    \retval     system error
*/
void sln2663_gpio_tft_init();

/*!
    \brief      function
    \param[in]  none
    \param[out] none
    \retval     system error
*/
void sln2663_rcu_tft_init();

/*!
    \brief      function
    \param[in]  none
    \param[out] none
    \retval     system error
*/
void sln2663_spi_tft_init();

// ---------------------------------------------------------------------
// Public Bodies
// ---------------------------------------------------------------------
/*!
    \brief      Initializes an TFT DMA LCD module.
    \param[in]  lcd_device_ptr
    \param[in]  tft_dma_ptr
    \param[out] lcd_device_ptr
    \param[out] tft_dma_ptr
    \retval     none
*/
void sln2663_tft_dma_init(sln2663_lcd_ptr lcd_device_ptr,
                              sln2663_tft_dma_ptr tft_dma_ptr)
{
    lh096t_ig01_values_init((lh096t_ig01_ptr)lcd_device_ptr);
    sln2663_rcu_tft_init();
    sln2663_gpio_tft_init();
    sln2663_spi_tft_init();
}

// ---------------------------------------------------------------------
// Private Bodies
// ---------------------------------------------------------------------
/*!
    \brief      function
    \param[in]  none
    \param[out] none
    \retval     system error
*/
void sln2663_gpio_tft_init() {
    // Preparing the port-pin pair with the frequency and output mode.
    gpio_init(SCL_TFT_GPIO_PORT, SCL_TFT_GPIO_MODE, TFT_FREQUENCY, SCL_TFT_GPIO_PIN);
    gpio_init(SDA_TFT_GPIO_PORT, SDA_TFT_GPIO_MODE, TFT_FREQUENCY, SDA_TFT_GPIO_PIN);
    gpio_init(RS_TFT_GPIO_PORT, RS_TFT_GPIO_MODE, TFT_FREQUENCY, RS_TFT_GPIO_PIN);
    gpio_init(RST_TFT_GPIO_PORT, RST_TFT_GPIO_MODE, TFT_FREQUENCY, RST_TFT_GPIO_PIN);
    gpio_init(CS_TFT_GPIO_PORT, CS_TFT_GPIO_MODE, TFT_FREQUENCY, CS_TFT_GPIO_PIN);
}

/*!
    \brief      function
    \param[in]  none
    \param[out] none
    \retval     system error
*/
void sln2663_rcu_tft_init() {
    // Initializing the peripheral RCU.
    sln2663_rcu_periph_clock_enable(RCU_AF);
    sln2663_rcu_periph_clock_enable(RCU_SPI0);
    sln2663_rcu_periph_clock_enable(RCU_GPIOA);
    sln2663_rcu_periph_clock_enable(RCU_GPIOB);
}

/*!
    \brief      function
    \param[in]  none
    \param[out] none
    \retval     system error
*/
void sln2663_spi_tft_init() {
}
