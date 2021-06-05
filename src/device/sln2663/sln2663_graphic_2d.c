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

#include "device\sln2663\sln2663_graphic_2d.h"
#include <stdlib.h>

// ---------------------------------------------------------------------
// Private Constants
// ---------------------------------------------------------------------
/*!< Without movable object 2D */
#define WITHOUT_MO2D NULL
/*!< Total number of impact walls */
/*
            +-----------+
            |7    0    1|
            |           |
            |6    ·    2|
            |           |
            |5    4    3|
            +-----------+
*/
#define SIDE_IMPACT_WALL_TOTAL 8
/* Side impact*/
typedef enum
{
    Y_TOP,         /*!< Y TOP */
    X_RIGHT_Y_TOP, /*!< X RIGHT & Y TOP */
    X_RIGHT,
    X_RIGHT_Y_BOTTOM,
    Y_BOTTOM,
    X_LEFT_Y_BOTTOM,
    X_LEFT,
    X_LEFT_Y_TOP
} side_impact_enum;

// ---------------------------------------------------------------------
// Private Prototypes
// ---------------------------------------------------------------------
/*!
    \brief      Generate the seed of the random numbers.
    \param[in]  none
    \param[out] none
    \retval     seed
*/
unsigned int sln2663_graphic_2d_generate_random_seed();

/*!
    \brief      Generate random side impact wall.
    \param[in]  none
    \param[out] none
    \retval     seed
*/
side_impact_enum sln2663_graphic_2d_generate_random_side_impact_wall(sln2663_graphic_2d_ptr graphic_2d_ptr);

/*!
    \brief      Initialize a movable object 2D into graphic 2D structure.
    \param[in]  mo_2d_ptr
    \param[in]  graphic_2d_ptr
    \param[out] mo_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_init_movable_object(movable_object_2d_ptr mo_2d_ptr, sln2663_graphic_2d_ptr graphic_2d_ptr);
// ---------------------------------------------------------------------
// Public Bodies
// ---------------------------------------------------------------------
/*!
    \brief      Add a movable object 2D into graphic 2D structure.
    \param[in]  graphic_2d_ptr
    \param[in]  mo_2d_ptr
    \param[out] graphic_2d_ptr
    \param[out] mo_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_add_movable_object(sln2663_graphic_2d_ptr graphic_2d_ptr, movable_object_2d_ptr mo_2d_ptr)
{
    if (graphic_2d_ptr->last_mo2d_ptr == WITHOUT_MO2D)
    {
        graphic_2d_ptr->last_mo2d_ptr = mo_2d_ptr;
        mo_2d_ptr->next_movable_object_2d_ptr = mo_2d_ptr;
    }
    else
    {
        // The new last points to the first.
        mo_2d_ptr->next_movable_object_2d_ptr = graphic_2d_ptr->last_mo2d_ptr->next_movable_object_2d_ptr;
        // The old last points to the new last.
        graphic_2d_ptr->last_mo2d_ptr->next_movable_object_2d_ptr = mo_2d_ptr;
        // The new last one is noted.
        graphic_2d_ptr->last_mo2d_ptr = mo_2d_ptr;
    }
    sln2663_graphic_2d_init_movable_object(mo_2d_ptr, graphic_2d_ptr);
}

/*!
    \brief      Initialize a graphic 2D structure.
    \param[in]  graphic_2d_ptr
    \param[in]  tft_dma_ptr
    \param[out] graphic_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_init_graphic_2d(sln2663_graphic_2d_ptr graphic_2d_ptr, sln2663_tft_dma_ptr tft_dma_ptr)
{
    // Initialize the pseudo-random number generator.
    srand(sln2663_graphic_2d_generate_random_seed());
    // Hooking up with the TFT device.
    graphic_2d_ptr->tft_dma_ptr = tft_dma_ptr;
    // Initializes the circular list.
    graphic_2d_ptr->last_mo2d_ptr = WITHOUT_MO2D;
}

/*!
    \brief      Set a random end position.
    \param[in]  graphic_2d_ptr
    \param[in]  mo_2d_ptr
    \param[out] mo_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_set_random_final_position_movable_object(sln2663_graphic_2d_ptr graphic_2d_ptr, movable_object_2d_ptr mo_2d_ptr)
{
    switch (sln2663_graphic_2d_generate_random_side_impact_wall(graphic_2d_ptr))
    {
    case Y_TOP:
        mo_2d_ptr->x1 = rand() % graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.columns;
        mo_2d_ptr->y1 = 0;
        break;
    case X_RIGHT_Y_TOP:
        mo_2d_ptr->x1 = graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.columns - 1;
        mo_2d_ptr->y1 = 0;
        break;
    case X_RIGHT:
        mo_2d_ptr->x1 = graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.columns - 1;
        mo_2d_ptr->y1 = rand() % graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.rows;
        break;
    case X_RIGHT_Y_BOTTOM:
        mo_2d_ptr->x1 = graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.columns - 1;
        mo_2d_ptr->y1 = graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.rows - 1;
        break;
    case Y_BOTTOM:
        mo_2d_ptr->x1 = rand() % graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.columns;
        mo_2d_ptr->y1 = graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.rows - 1;
        break;
    case X_LEFT_Y_BOTTOM:
        mo_2d_ptr->x1 = 0;
        mo_2d_ptr->y1 = graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.rows - 1;
        break;
    case X_LEFT:
        mo_2d_ptr->x1 = 0;
        mo_2d_ptr->y1 = rand() % graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.rows;
        break;
    case X_LEFT_Y_TOP:
        mo_2d_ptr->x1 = 0;
        mo_2d_ptr->y1 = 0;
        break;
    default:
        mo_2d_ptr->x1 = rand() % graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.columns;
        mo_2d_ptr->y1 = rand() % graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.rows;
        break;
    }
}

/*!
    \brief      Set a random starting position.
    \param[in]  graphic_2d_ptr
    \param[in]  mo_2d_ptr
    \param[out] mo_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_set_random_initial_position_movable_object(sln2663_graphic_2d_ptr graphic_2d_ptr, movable_object_2d_ptr mo_2d_ptr)
{
    mo_2d_ptr->x0 = rand() % graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.columns;
    mo_2d_ptr->y0 = rand() % graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.rows;
}

/*!
    \brief      Loop movable objects.
    \param[in]  graphic_2d_ptr
    \param[out] graphic_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_loop_movable_objects(sln2663_graphic_2d_ptr graphic_2d_ptr)
{
    if (graphic_2d_ptr->last_mo2d_ptr != WITHOUT_MO2D)
    {
        movable_object_2d_ptr next_mo2d_ptr;

        next_mo2d_ptr = graphic_2d_ptr->last_mo2d_ptr; // Last movable object.
        do
        {
            next_mo2d_ptr = next_mo2d_ptr->next_movable_object_2d_ptr; // Next movable object.
            sln2663_lcd_tft_setpixel(graphic_2d_ptr->tft_dma_ptr,
                                     next_mo2d_ptr->x0,
                                     next_mo2d_ptr->y0,
                                     next_mo2d_ptr->color);
        } while (next_mo2d_ptr != graphic_2d_ptr->last_mo2d_ptr);
    }
}
// ---------------------------------------------------------------------
// Private Bodies
// ---------------------------------------------------------------------
/*!
    \brief      Calculate the seed of the pseudo-random numbers.
    \param[in]  none
    \param[out] none
    \retval     Seed for the generation of pseudo-random numbers.
*/
unsigned int sln2663_graphic_2d_generate_random_seed()
{
    return get_timer_value();
}

/*!
    \brief      Calculate random side impact wall.
    \param[in]  none
    \param[out] none
    \retval     seed
*/
side_impact_enum sln2663_graphic_2d_generate_random_side_impact_wall(sln2663_graphic_2d_ptr graphic_2d_ptr)
{
    side_impact_enum result;

    result = rand() % SIDE_IMPACT_WALL_TOTAL;
    return result;
}

/*!
    \brief      Initialize a movable object 2D into graphic 2D structure.
    \param[in]  mo_2d_ptr
    \param[in]  graphic_2d_ptr
    \param[out] mo_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_init_movable_object(movable_object_2d_ptr mo_2d_ptr, sln2663_graphic_2d_ptr graphic_2d_ptr)
{
}
