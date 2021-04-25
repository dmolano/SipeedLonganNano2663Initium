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
#include "device\sln2663\sln2663_time.h"
#include "gd32vf103_spi.h"
#include "gd32vf103_dma.h"

// ---------------------------------------------------------------------
// Private Constants
// ---------------------------------------------------------------------
#define SCL_TFT_RCU_PERIPH RCU_GPIOA
#define SDA_TFT_RCU_PERIPH RCU_GPIOA
#define CS_TFT_RCU_PERIPH RCU_GPIOB
#define RS_TFT_RCU_PERIPH RCU_GPIOB
#define RST_TFT_RCU_PERIPH RCU_GPIOB // RST=RES

#define SCL_TFT_GPIO_PORT GPIOA
#define SDA_TFT_GPIO_PORT GPIOA
#define CS_TFT_GPIO_PORT GPIOB
#define RS_TFT_GPIO_PORT GPIOB
#define RST_TFT_GPIO_PORT GPIOB // RST=RES

#define SCL_TFT_GPIO_PIN GPIO_PIN_5
#define SDA_TFT_GPIO_PIN GPIO_PIN_7
#define CS_TFT_GPIO_PIN GPIO_PIN_2
#define RS_TFT_GPIO_PIN GPIO_PIN_0
#define RST_TFT_GPIO_PIN GPIO_PIN_1 // RST=RES

#define SCL_TFT_GPIO_MODE GPIO_MODE_AF_PP
#define SDA_TFT_GPIO_MODE GPIO_MODE_AF_PP
#define CS_TFT_GPIO_MODE GPIO_MODE_OUT_PP
#define RS_TFT_GPIO_MODE GPIO_MODE_OUT_PP
#define RST_TFT_GPIO_MODE GPIO_MODE_OUT_PP // RST=RES

#define TFT_FREQUENCY GPIO_OSPEED_50MHZ

#define TFT_DISABLE_WAIT_MS 1
#define TFT_RESET_WAIT_MS 5

// SPI
#define SPI0_CTL0_CONFIGURATION SPI_MASTER | SPI_TRANSMODE_FULLDUPLEX | SPI_FRAMESIZE_8BIT | SPI_NSS_SOFT | SPI_ENDIAN_MSB | SPI_CK_PL_LOW_PH_1EDGE | SPI_PSC_8

// TIME
#define DELAY_ONE_MILISECOND sln2663_time_delay_ms(ONE_MILISECOND_TIME)
#define DELAY_FIVE_MILISECOND sln2663_time_delay_ms(FIVE_MILISECOND_TIME)
// ---------------------------------------------------------------------
// Private Prototypes
// ---------------------------------------------------------------------
/*!
    \brief      Configure DMA, do not enable.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_dma_tft_configure();

/*!
    \brief      Initialize GPIO for TFT.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_gpio_tft_init();

/*!
    \brief      .
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_lcd_tft_clear(sln2663_tft_dma_ptr tft_dma_ptr, uint16_t color);

/*!
    \brief      .
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_lcd_tft_init_script();

/*!
    \brief      .
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_lcd_tft_mode_data();

/*!
    \brief      .
    \param[in]  command
    \param[out] none
    \retval     none
*/
void sln2663_lcd_tft_reg(st7735s_command command);

/*!
    \brief      .
    \param[in]  data
    \param[out] none
    \retval     none
*/
void sln2663_lcd_tft_u8c(uint8_t data);

/*!
    \brief      Initialize RCU for TFT.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_rcu_tft_init();

/*!
    \brief      Configure SPI, and do enable.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_spi_tft_configure();

/*!
    \brief      set 8 bits
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_spi_tft_set_8bit();

/*!
    \brief      .
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_spi_tft_wait_idle();

/*!
    \brief      .
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_spi_tft_wait_tbe();

/*!
    \brief      Disable TFT.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_tft_disable();

/*!
    \brief      Enable TFT.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_tft_enable();

/*!
    \brief      Reset TFT.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_tft_reset();

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
    lcd_device_ptr->resolution.columns = lh096t_ig01_get_columns_lcd();
    lcd_device_ptr->resolution.rows = lh096t_ig01_get_rows_lcd();
    tft_dma_ptr->lcd_device_ptr = lcd_device_ptr;
    // Init
    sln2663_rcu_tft_init();
    sln2663_gpio_tft_init();
    sln2663_tft_disable();
    DELAY_ONE_MILISECOND;
    sln2663_tft_reset();
    DELAY_FIVE_MILISECOND;
    // Deinit SPI.
    spi_i2s_deinit(SPI0);
    // Deinit DMA.
    dma_deinit(DMA0, DMA_CH1); // Receive.
    dma_deinit(DMA0, DMA_CH2); // Transmit.
    sln2663_dma_tft_configure();
    sln2663_spi_tft_configure();
    sln2663_tft_enable();
    sln2663_lcd_tft_init_script();
    // Init AFBR
    tft_dma_ptr->afbr.status = DISABLED;
    tft_dma_ptr->afbr.wait_status = NONE;
    // Clear LCD
    sln2663_lcd_tft_clear(tft_dma_ptr);
}

// ---------------------------------------------------------------------
// Private Bodies
// ---------------------------------------------------------------------
/*!
    \brief      Configure DMA, do not enable.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_dma_tft_configure()
{
    DMA_CHCTL(DMA0, DMA_CH1) = (uint32_t)(DMA_PRIORITY_ULTRA_HIGH | DMA_CHXCTL_MNAGA); // Receive.
    DMA_CHCTL(DMA0, DMA_CH2) = (uint32_t)(DMA_PRIORITY_ULTRA_HIGH | DMA_CHXCTL_DIR);   // Transmit.
    DMA_CHPADDR(DMA0, DMA_CH1) = (uint32_t)&SPI_DATA(SPI0);
    DMA_CHPADDR(DMA0, DMA_CH2) = (uint32_t)&SPI_DATA(SPI0);
}

/*!
    \brief      Initialize GPIO for TFT.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_gpio_tft_init()
{
    // Preparing the port-pin pair with the frequency and output mode.
    gpio_init(SCL_TFT_GPIO_PORT, SCL_TFT_GPIO_MODE, TFT_FREQUENCY, SCL_TFT_GPIO_PIN);
    gpio_init(SDA_TFT_GPIO_PORT, SDA_TFT_GPIO_MODE, TFT_FREQUENCY, SDA_TFT_GPIO_PIN);
    gpio_init(RS_TFT_GPIO_PORT, RS_TFT_GPIO_MODE, TFT_FREQUENCY, RS_TFT_GPIO_PIN);
    gpio_init(RST_TFT_GPIO_PORT, RST_TFT_GPIO_MODE, TFT_FREQUENCY, RST_TFT_GPIO_PIN);
    gpio_init(CS_TFT_GPIO_PORT, CS_TFT_GPIO_MODE, TFT_FREQUENCY, CS_TFT_GPIO_PIN);
}

/*!
    \brief      .
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_lcd_tft_clear(sln2663_tft_dma_ptr tft_dma_ptr, uint16_t color)
{
    if (tft_dma_ptr->afbr.status == DISABLED)
    {
        sln2663_lcd_tft_wait(tft_dma_ptr);
        sln2663_lcd_set_addr(0, 0, tft_dma_ptr->lcd_device_ptr->resolution.columns, tft_dma_ptr->lcd_device_ptr->resolution.rows);
        dma_send_const_u16(color, tft_dma_ptr->lcd_device_ptr->resolution.columns * tft_dma_ptr->lcd_device_ptr->resolution.rows);
    }
}

/*!
    \brief      .
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_lcd_tft_init_script()
{
    mode_index mode = COMMAND;
    uint8_t length_data = NO_PARAMETER;

    // Initialize the display.
    for (uint32_t index = 0; index < lh096t_ig01_get_sizeof_init_script(); index++)
    {
        switch (mode)
        {
        case COMMAND:
            sln2663_lcd_tft_reg(lh096t_ig01_get_data_init_script(index));
            mode = LENGTH;
            break;

        case LENGTH:
            length_data = lh096t_ig01_get_data_init_script(index);
            if (length_data == NO_PARAMETER)
            {
                mode = COMMAND;
            }
            else
            {
                mode = FIRST_DATA;
            }
            break;

        case FIRST_DATA:
            sln2663_spi_tft_wait_idle();
            sln2663_lcd_tft_mode_data();
            mode = REST_DATA;
            break;

        case REST_DATA:
            sln2663_lcd_tft_u8c(lh096t_ig01_get_data_init_script(index));
            if (--length_data == NO_PARAMETER)
            {
                mode = COMMAND;
            }
            break;

        default:
            break;
        }
    }
}

/*!
    \brief      .
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_lcd_tft_mode_cmd()
{
    gpio_bit_reset(RS_TFT_GPIO_PORT, RS_TFT_GPIO_PIN);
}

/*!
    \brief      .
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_lcd_tft_mode_data()
{
    gpio_bit_set(RS_TFT_GPIO_PORT, RS_TFT_GPIO_PIN);
}

/*!
    \brief      .
    \param[in]  command
    \param[out] none
    \retval     none
*/
void sln2663_lcd_tft_reg(st7735s_command command)
{
    sln2663_spi_tft_wait_idle();
    sln2663_spi_tft_set_8bit();
    sln2663_lcd_tft_mode_cmd();
    spi_i2s_data_transmit(SPI0, command);
}

/*!
    \brief      .
    \param[in]  command
    \param[out] none
    \retval     none
*/
void sln2663_lcd_tft_set_addr(int x, int y, int w, int h) {

}

/*!
    \brief      .
    \param[in]  data
    \param[out] none
    \retval     none
*/
void sln2663_lcd_tft_u8c(uint8_t data)
{
    sln2663_spi_tft_wait_tbe();
    spi_i2s_data_transmit(SPI0, data);
}

/*!
    \brief      .
    \param[in]  data
    \param[out] none
    \retval     none
*/
void sln2663_lcd_tft_wait(sln2663_tft_dma_ptr tft_dma_ptr)
{
    if (tft_dma_ptr->afbr.status == ENABLED)
    {
        switch (tft_dma_ptr->afbr.wait_status)
        {
        case READ_U24:
            /* code */
            break;

        case WRITE_U24:
            /* code */
            break;

        default:
            break;
        }
    }
}

/*!
    \brief      Initialize RCU for TFT.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_rcu_tft_init()
{
    // Initializing the peripheral RCU.
    sln2663_rcu_periph_clock_enable(RCU_AF);
    sln2663_rcu_periph_clock_enable(RCU_SPI0);
    sln2663_rcu_periph_clock_enable(RCU_GPIOA);
    sln2663_rcu_periph_clock_enable(RCU_GPIOB);
}

/*!
    \brief      Configure SPI, and do enable.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_spi_tft_configure()
{
    SPI_CTL0(SPI0) = (uint32_t)(SPI0_CTL0_CONFIGURATION);
    SPI_CTL1(SPI0) = (uint32_t)(SPI_CTL1_DMATEN);
    spi_enable(SPI0);
}

/*!
    \brief      set 8 bits
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_spi_tft_set_8bit()
{
    if (SPI_CTL0(SPI0) & (uint32_t)(SPI_CTL0_FF16))
    {
        SPI_CTL0(SPI0) &= ~(uint32_t)(SPI_CTL0_SPIEN);
        // ---------------v
        SPI_CTL0(SPI0) &= ~(uint32_t)(SPI_CTL0_FF16);
        SPI_CTL0(SPI0) |= (uint32_t)(SPI_CTL0_SPIEN);
    }
}

/*!
    \brief      .
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_spi_tft_wait_idle()
{
    while (SPI_STAT(SPI0) & SPI_STAT_TRANS)
        ;
}

/*!
    \brief      .
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_spi_tft_wait_tbe()
{
    while (!(SPI_STAT(SPI0) & SPI_STAT_TBE))
        ;
}

/*!
    \brief      Disable TFT.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_tft_disable()
{
    gpio_bit_set(CS_TFT_GPIO_PORT, CS_TFT_GPIO_PIN);
}

/*!
    \brief      Enable TFT.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_tft_enable()
{
    gpio_bit_reset(CS_TFT_GPIO_PORT, CS_TFT_GPIO_PIN);
}

/*!
    \brief      Reset TFT.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_tft_reset()
{
    gpio_bit_set(RST_TFT_GPIO_PORT, RST_TFT_GPIO_PIN);
}