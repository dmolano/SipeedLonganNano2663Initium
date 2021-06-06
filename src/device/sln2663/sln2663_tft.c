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
    \brief      .
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_dma_tft_send_const_u16(uint16_t data, uint32_t count);

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
    \param[in]  command
    \param[out] none
    \retval     none
*/
void sln2663_lcd_tft_set_addr(int x, int y, int w, int h);

/*!
    \brief      .
    \param[in]  data
    \param[out] none
    \retval     none
*/
void sln2663_lcd_tft_u16(uint16_t data);

/*!
    \brief      .
    \param[in]  data
    \param[out] none
    \retval     none
*/
void sln2663_lcd_tft_u16c(uint16_t data);

/*!
    \brief      .
    \param[in]  data
    \param[out] none
    \retval     none
*/
void sln2663_lcd_tft_u8(uint8_t data);

/*!
    \brief      .
    \param[in]  data
    \param[out] none
    \retval     none
*/
void sln2663_lcd_tft_u8c(uint8_t data);

/*!
    \brief      .
    \param[in]  data
    \param[out] none
    \retval     none
*/
void sln2663_lcd_tft_wait(sln2663_tft_dma_ptr tft_dma_ptr);

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
    \brief      set 16 bits
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_spi_tft_set_16bit();

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
    
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_AF);
    rcu_periph_clock_enable(RCU_DMA0);
    rcu_periph_clock_enable(RCU_SPI0);

    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5 | GPIO_PIN_7);
    gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2);
    gpio_bit_reset(GPIOB, GPIO_PIN_0 | GPIO_PIN_1); // DC=0, RST=0
    sln2663_tft_disable();

    DELAY_ONE_MILISECOND;
    gpio_bit_set(GPIOB, GPIO_PIN_1); // RST=1
    DELAY_FIVE_MILISECOND;

    // Deinit SPI and DMA.
    spi_i2s_deinit(SPI0);
    dma_deinit(DMA0, DMA_CH1);
    dma_deinit(DMA0, DMA_CH2);

    // Configure DMA, do not enable.
    DMA_CHCTL(DMA0, DMA_CH1) = (uint32_t)(DMA_PRIORITY_ULTRA_HIGH | DMA_CHXCTL_MNAGA); // Receive.
    DMA_CHCTL(DMA0, DMA_CH2) = (uint32_t)(DMA_PRIORITY_ULTRA_HIGH | DMA_CHXCTL_DIR);   // Transmit.
    DMA_CHPADDR(DMA0, DMA_CH1) = (uint32_t)&SPI_DATA(SPI0);
    DMA_CHPADDR(DMA0, DMA_CH2) = (uint32_t)&SPI_DATA(SPI0);

    // Configure and enable SPI.
    SPI_CTL0(SPI0) = (uint32_t)(SPI_MASTER | SPI_TRANSMODE_FULLDUPLEX | SPI_FRAMESIZE_8BIT | SPI_NSS_SOFT | SPI_ENDIAN_MSB | SPI_CK_PL_LOW_PH_1EDGE | SPI_PSC_8);
    SPI_CTL1(SPI0) = (uint32_t)(SPI_CTL1_DMATEN);
    spi_enable(SPI0);

    // Enable lcd controller.
    sln2663_tft_enable();

    // Init
    sln2663_lcd_tft_init_script();
    // Init AFBR
    tft_dma_ptr->afbr.status = DISABLED;
    tft_dma_ptr->afbr.wait_status = NONE;
    DELAY_ONE_SECOND;
}

// ---------------------------------------------------------------------
// Private Bodies
// ---------------------------------------------------------------------
// ---------- //
//     DMA    //
// ---------- //
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

uint32_t g_dma_const_value = 0;

/*!
    \brief      .
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_dma_tft_send_const_u16(uint16_t data, uint32_t count)
{
    sln2663_spi_tft_wait_idle();
    g_dma_const_value = data;
    sln2663_lcd_tft_mode_data();
    sln2663_spi_tft_set_16bit();
    dma_channel_disable(DMA0, DMA_CH2);
    dma_memory_width_config(DMA0, DMA_CH2, DMA_MEMORY_WIDTH_16BIT);
    dma_periph_width_config(DMA0, DMA_CH2, DMA_PERIPHERAL_WIDTH_16BIT);
    dma_memory_address_config(DMA0, DMA_CH2, (uint32_t)(&g_dma_const_value));
    dma_memory_increase_disable(DMA0, DMA_CH2);
    dma_transfer_number_config(DMA0, DMA_CH2, count);
    dma_channel_enable(DMA0, DMA_CH2);
}

// ---------- //
//    GPIO    //
// ---------- //

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

// ---------- //
//     LCD    //
// ---------- //

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
        sln2663_lcd_tft_set_addr(0, 0, tft_dma_ptr->lcd_device_ptr->resolution.columns, tft_dma_ptr->lcd_device_ptr->resolution.rows);
        sln2663_dma_tft_send_const_u16(color, tft_dma_ptr->lcd_device_ptr->resolution.columns * tft_dma_ptr->lcd_device_ptr->resolution.rows);
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
        uint8_t element = lh096t_ig01_get_data_init_script(index);

        switch (mode)
        {
        case COMMAND:
            sln2663_lcd_tft_reg(element);
            mode = LENGTH;
            break;

        case LENGTH:
            length_data = element;
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
            //break;

        case REST_DATA:
            sln2663_lcd_tft_u8c(element);
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
void sln2663_lcd_tft_set_addr(int x, int y, int w, int h)
{
    sln2663_lcd_tft_reg(CASET);
    sln2663_lcd_tft_u16(x + 1);
    sln2663_lcd_tft_u16c(x + w);
    sln2663_lcd_tft_reg(RASET);
    sln2663_lcd_tft_u16(y + 26);
    sln2663_lcd_tft_u16c(y + h + 25);
    sln2663_lcd_tft_reg(RAMWR);
}

/*!
    \brief      set pixel
    \param[in]  tft_dma_ptr:
    \param[in]  x: x position
    \param[in]  y: y position
    \param[out] none
    \retval     none
*/
void sln2663_lcd_tft_setpixel(sln2663_tft_dma_ptr tft_dma_ptr, int x, int y, uint16_t color)
{
    if ((tft_dma_ptr != NULL) && (tft_dma_ptr->afbr.status == ENABLED))
    {
        return;
    }

    sln2663_lcd_tft_wait(tft_dma_ptr);
    sln2663_lcd_tft_set_addr(x, y, 1, 1);
    sln2663_lcd_tft_u8(color >> 8);
    sln2663_lcd_tft_u8c(color);
}

/*!
    \brief      .
    \param[in]  data
    \param[out] none
    \retval     none
*/
void sln2663_lcd_tft_u16(uint16_t data)
{
    sln2663_spi_tft_wait_idle();
    sln2663_spi_tft_set_16bit();
    sln2663_lcd_tft_mode_data();
    spi_i2s_data_transmit(SPI0, data);
}

/*!
    \brief      .
    \param[in]  data
    \param[out] none
    \retval     none
*/
void sln2663_lcd_tft_u16c(uint16_t data)
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
void sln2663_lcd_tft_u8(uint8_t data)
{
    sln2663_spi_tft_wait_idle();
    sln2663_spi_tft_set_8bit();
    sln2663_lcd_tft_mode_data();
    spi_i2s_data_transmit(SPI0, data);
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

// ---------- //
//     RCU    //
// ---------- //

/*!
    \brief      Initialize RCU for TFT.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_rcu_tft_init()
{
    // Initializing the peripheral RCU.
    sln2663_rcu_periph_clock_enable(RCU_GPIOA);
    sln2663_rcu_periph_clock_enable(RCU_GPIOB);
    sln2663_rcu_periph_clock_enable(RCU_AF);
    sln2663_rcu_periph_clock_enable(RCU_DMA0);
    sln2663_rcu_periph_clock_enable(RCU_SPI0);
}

// ---------- //
//     SPI    //
// ---------- //

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
    \brief      set 16 bits
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sln2663_spi_tft_set_16bit()
{
    if (!(SPI_CTL0(SPI0) & (uint32_t)(SPI_CTL0_FF16)))
    {
        SPI_CTL0(SPI0) &= ~(uint32_t)(SPI_CTL0_SPIEN);
        SPI_CTL0(SPI0) |= (uint32_t)(SPI_CTL0_FF16);
        SPI_CTL0(SPI0) |= (uint32_t)(SPI_CTL0_SPIEN);
    }
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

// ---------- //
//     TFT    //
// ---------- //

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