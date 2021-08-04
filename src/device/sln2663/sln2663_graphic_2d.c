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

#include "device/sln2663/sln2663_graphic_2d.h"
#include <stdlib.h>

// ---------------------------------------------------------------------
// Private Constants
// ---------------------------------------------------------------------
/*!< Without movable object 2D */
#define WITHOUT_MO2D NULL

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
    \param[in]  graphic_2d_ptr
    \param[out] none
    \retval     side_impact
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

/*!
    \brief      Move movable object.
    \param[in]  graphic_2d_ptr
    \param[in]  mo_2d_ptr movable object.
    \param[out] mo_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_move_movable_object(sln2663_graphic_2d_ptr graphic_2d_ptr, movable_object_2d_ptr now_mo2d_ptr);

/*!
    \brief      Treat collision on movable object.
    \param[in]  graphic_2d_ptr
    \param[in]  first_mo2d_ptr movable object.
    \param[in]  now_mo2d_ptr movable object.
    \param[in]  background_color background color.
    \param[in]  collision_color collision color.
    \param[out] mo_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_treat_collision_movable_object(sln2663_graphic_2d_ptr graphic_2d_ptr, movable_object_2d_ptr first_mo2d_ptr, movable_object_2d_ptr now_mo2d_ptr, uint16_t background_color, uint16_t collision_color);

/*!
    \brief      Treat collision movable objects.
    \param[in]  graphic_2d_ptr
    \param[in]  first_mo2d_ptr
    \param[in]  background_color background color.
    \param[in]  collision_color collision color.
    \param[out] graphic_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_treat_collisions_movable_object(sln2663_graphic_2d_ptr graphic_2d_ptr, movable_object_2d_ptr first_mo2d_ptr, uint16_t background_color, uint16_t collision_color);

/*!
    \brief      Treat collision movable objects.
    \param[in]  graphic_2d_ptr
    \param[in]  background_color background color.
    \param[in]  collision_color collision color.
    \param[out] graphic_2d_ptr
    \retval     TRUE if more loops are neccesary.
*/
int sln2663_graphic_2d_treat_collisions_movable_objects(sln2663_graphic_2d_ptr graphic_2d_ptr, uint16_t background_color, uint16_t collision_color);

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
    \brief      Get a color of movable object 2D.
    \param[in]  mo_2d_ptr
    \param[out] none
    \retval     uint16_t
*/
uint16_t sln2663_graphic_2d_get_color_movable_object(movable_object_2d_ptr mo_2d_ptr)
{
    return movable_object_2d_get_color(mo_2d_ptr);
}

/*!
    \brief      Get a status of movable object 2D.
    \param[in]  mo_2d_ptr
    \param[out] none
    \retval     movable_object_status_enum
*/
movable_object_status_enum sln2663_graphic_2d_get_status_movable_object(movable_object_2d_ptr mo_2d_ptr)
{
    return movable_object_2d_get_status(mo_2d_ptr);
}

/*!
    \brief      Initialize a graphic 2D structure.
    \param[in]  graphic_2d_ptr
    \param[in]  tft_dma_ptr
    \param[out] graphic_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_init_graphic(sln2663_graphic_2d_ptr graphic_2d_ptr, sln2663_tft_dma_ptr tft_dma_ptr)
{
    // Initialize the pseudo-random number generator.
    srand(sln2663_graphic_2d_generate_random_seed());
    // Hooking up with the TFT device.
    graphic_2d_ptr->tft_dma_ptr = tft_dma_ptr;
    // Initializes the circular list.
    graphic_2d_ptr->last_mo2d_ptr = WITHOUT_MO2D;
}

/*!
    \brief      Move movable objects.
    \param[in]  graphic_2d_ptr
    \param[in]  background_color
    \param[in]  collision_color
    \param[out] graphic_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_move_movable_objects(sln2663_graphic_2d_ptr graphic_2d_ptr)
{
    movable_object_2d_ptr now_mo2d_ptr;

    now_mo2d_ptr = graphic_2d_ptr->last_mo2d_ptr; // Last movable object.
    // Move
    do
    {
        now_mo2d_ptr = now_mo2d_ptr->next_movable_object_2d_ptr;              // Next movable object.
        sln2663_graphic_2d_move_movable_object(graphic_2d_ptr, now_mo2d_ptr); // Loop this movable object.
    } while (now_mo2d_ptr != graphic_2d_ptr->last_mo2d_ptr);
}

/*!
    \brief      Loop movable objects.
    \param[in]  graphic_2d_ptr
    \param[in]  background_color
    \param[in]  collision_color
    \param[out] graphic_2d_ptr
    \retval     TRUE if more loops are neccesary.
*/
int sln2663_graphic_2d_loop_movable_objects(sln2663_graphic_2d_ptr graphic_2d_ptr, uint16_t background_color, uint16_t collision_color)
{
    int result = FALSE;

    if (graphic_2d_ptr->last_mo2d_ptr != WITHOUT_MO2D)
    {
        sln2663_graphic_2d_move_movable_objects(graphic_2d_ptr);
        result = sln2663_graphic_2d_treat_collisions_movable_objects(graphic_2d_ptr, background_color, collision_color);
    }
    return result;
}

/*!
    \brief      Set a color of movable object 2D.
    \param[in]  mo_2d_ptr
    \param[in]  color
    \param[out] mo_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_set_color_movable_object(movable_object_2d_ptr mo_2d_ptr, uint16_t color)
{
    movable_object_2d_set_color(mo_2d_ptr, color);
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
        mo_2d_ptr->bresenham.x1 = rand() % graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.columns;
        mo_2d_ptr->bresenham.y1 = -1;
        break;
    case X_RIGHT_Y_TOP:
        mo_2d_ptr->bresenham.x1 = graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.columns;
        mo_2d_ptr->bresenham.y1 = -1;
        break;
    case X_RIGHT:
        mo_2d_ptr->bresenham.x1 = graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.columns;
        mo_2d_ptr->bresenham.y1 = rand() % graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.rows;
        break;
    case X_RIGHT_Y_BOTTOM:
        mo_2d_ptr->bresenham.x1 = graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.columns;
        mo_2d_ptr->bresenham.y1 = graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.rows;
        break;
    case Y_BOTTOM:
        mo_2d_ptr->bresenham.x1 = rand() % graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.columns;
        mo_2d_ptr->bresenham.y1 = graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.rows;
        break;
    case X_LEFT_Y_BOTTOM:
        mo_2d_ptr->bresenham.x1 = -1;
        mo_2d_ptr->bresenham.y1 = graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.rows;
        break;
    case X_LEFT:
        mo_2d_ptr->bresenham.x1 = -1;
        mo_2d_ptr->bresenham.y1 = rand() % graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.rows;
        break;
    case X_LEFT_Y_TOP:
        mo_2d_ptr->bresenham.x1 = -1;
        mo_2d_ptr->bresenham.y1 = -1;
        break;
    default:
        mo_2d_ptr->bresenham.x1 = rand() % graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.columns;
        mo_2d_ptr->bresenham.y1 = rand() % graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.rows;
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
    mo_2d_ptr->bresenham.x0 = mo_2d_ptr->bresenham.xn = rand() % graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.columns;
    mo_2d_ptr->bresenham.y0 = mo_2d_ptr->bresenham.yn = rand() % graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.rows;
}

/*!
    \brief      Set speed of movable object 2D.
    \param[in]  mo_2d_ptr
    \param[in]  speed
    \param[out] mo_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_set_speed_movable_object(movable_object_2d_ptr mo_2d_ptr, uint8_t speed)
{
    movable_object_2d_set_speed(mo_2d_ptr, speed);
}

/*!
    \brief      Set a status of movable object 2D.
    \param[in]  mo_2d_ptr
    \param[in]  status_enum
    \param[out] mo_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_set_status_movable_object(movable_object_2d_ptr mo_2d_ptr, movable_object_status_enum status_enum)
{
    movable_object_2d_set_status(mo_2d_ptr, status_enum);
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

    /*
            +-----------+
            |7    0    1|
            |           |
            |6    ·    2|
            |           |
            |5    4    3|
            +-----------+
*/
    result = (side_impact_enum)(rand() % SIDE_IMPACT_WALL_TOTAL);
    // result = (side_impact_enum)((rand() % 6) | 0b0001); // odd
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

/*!
    \brief      Loop movable object.
    \param[in]  graphic_2d_ptr
    \param[in]  mo_2d_ptr movable object.
    \param[out] mo_2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_move_movable_object(sln2663_graphic_2d_ptr graphic_2d_ptr, movable_object_2d_ptr now_mo2d_ptr)
{
    // Loop
    movable_object_2d_move(now_mo2d_ptr, 0, 0, graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.columns - 1, graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.rows - 1);
}

/*!
    \brief      Treat collision on movable object.
    \param[in]  graphic_2d_ptr
    \param[in]  first_mo2d_ptr movable object.
    \param[in]  background_color background color.
    \param[in]  collision_color collision color.
    \param[out] first_mo2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_treat_collision_movable_object(sln2663_graphic_2d_ptr graphic_2d_ptr, movable_object_2d_ptr first_mo2d_ptr, movable_object_2d_ptr now_mo2d_ptr,
                                                       uint16_t background_color, uint16_t collision_color)
{
    movable_object_status_enum first_status = movable_object_2d_get_status(first_mo2d_ptr);
    movable_object_status_enum now_status = movable_object_2d_get_status(now_mo2d_ptr);

    if ((first_mo2d_ptr != now_mo2d_ptr) && (now_status != DEAD))
    {
        if ((first_mo2d_ptr->bresenham.xn == now_mo2d_ptr->bresenham.xn) &&
            (first_mo2d_ptr->bresenham.yn == now_mo2d_ptr->bresenham.yn))
        {
            // Collision
            if (first_status != DEAD)
            {
                movable_object_2d_set_status(first_mo2d_ptr, DEAD);
                if ((first_mo2d_ptr->bresenham.xnb != first_mo2d_ptr->bresenham.xn) ||
                    (first_mo2d_ptr->bresenham.ynb != first_mo2d_ptr->bresenham.yn))
                {
                    sln2663_lcd_tft_setpixel(graphic_2d_ptr->tft_dma_ptr,
                                             first_mo2d_ptr->bresenham.xnb,
                                             first_mo2d_ptr->bresenham.ynb,
                                             background_color);
                }
                sln2663_lcd_tft_setpixel(graphic_2d_ptr->tft_dma_ptr,
                                         first_mo2d_ptr->bresenham.xn,
                                         first_mo2d_ptr->bresenham.yn,
                                         collision_color);
            }
            movable_object_2d_set_status(now_mo2d_ptr, DEAD);
            sln2663_lcd_tft_setpixel(graphic_2d_ptr->tft_dma_ptr,
                                     now_mo2d_ptr->bresenham.xnb,
                                     now_mo2d_ptr->bresenham.ynb,
                                     background_color);
        }
        else
        {
            // First != Now => ¿Swap?
            if ((first_mo2d_ptr->bresenham.xn == now_mo2d_ptr->bresenham.xnb) &&
                (first_mo2d_ptr->bresenham.yn == now_mo2d_ptr->bresenham.ynb) &&
                (first_mo2d_ptr->bresenham.xnb == now_mo2d_ptr->bresenham.xn) &&
                (first_mo2d_ptr->bresenham.ynb == now_mo2d_ptr->bresenham.yn))
            {
                // Swap => Collision
                if (first_status != DEAD)
                {
                    movable_object_2d_set_status(first_mo2d_ptr, DEAD);
                    sln2663_lcd_tft_setpixel(graphic_2d_ptr->tft_dma_ptr,
                                             first_mo2d_ptr->bresenham.xn,
                                             first_mo2d_ptr->bresenham.yn,
                                             collision_color);
                }
                movable_object_2d_set_status(now_mo2d_ptr, DEAD);
                sln2663_lcd_tft_setpixel(graphic_2d_ptr->tft_dma_ptr,
                                         now_mo2d_ptr->bresenham.xn,
                                         now_mo2d_ptr->bresenham.yn,
                                         collision_color);
            }
            else
            {
                // Next now.
            }
        }
    }
    else
    {
        // SAME OR DEAD => nothing to do.
    }
}

/*!
    \brief      Treat collisions on movable object.
    \param[in]  graphic_2d_ptr
    \param[in]  first_mo2d_ptr movable object.
    \param[in]  background_color background color.
    \param[in]  collision_color collision color.
   \param[out] first_mo2d_ptr
    \retval     none
*/
void sln2663_graphic_2d_treat_collisions_movable_object(sln2663_graphic_2d_ptr graphic_2d_ptr, movable_object_2d_ptr first_mo2d_ptr, uint16_t background_color, uint16_t collision_color)
{
    movable_object_2d_ptr now_mo2d_ptr;

    now_mo2d_ptr = first_mo2d_ptr;
    do
    {
        now_mo2d_ptr = now_mo2d_ptr->next_movable_object_2d_ptr;                                                                            // Next movable object.
        sln2663_graphic_2d_treat_collision_movable_object(graphic_2d_ptr, first_mo2d_ptr, now_mo2d_ptr, background_color, collision_color); // Treat collision on this movable object.
    } while (now_mo2d_ptr != graphic_2d_ptr->last_mo2d_ptr);
    // Did FIRST end up dead?
    if (movable_object_2d_get_status(first_mo2d_ptr) != DEAD)
    {
        // Has anything been advanced?
        if ((first_mo2d_ptr->bresenham.xnb != first_mo2d_ptr->bresenham.xn) ||
            (first_mo2d_ptr->bresenham.ynb != first_mo2d_ptr->bresenham.yn))
        {
            sln2663_lcd_tft_setpixel(graphic_2d_ptr->tft_dma_ptr,
                                     first_mo2d_ptr->bresenham.xnb,
                                     first_mo2d_ptr->bresenham.ynb,
                                     background_color);
        }
        // Do not delete!!
        // if (((first_mo2d_ptr->bresenham.xn < 0) ||
        //      (first_mo2d_ptr->bresenham.yn < 0) ||
        //      (first_mo2d_ptr->bresenham.xn >= (int)graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.columns) ||
        //      (first_mo2d_ptr->bresenham.yn >= (int)graphic_2d_ptr->tft_dma_ptr->lcd_device_ptr->resolution.rows)))
        // {
        //     // WRONG
        //     // ---------------------->rrrrrggggggbbbbb
        //     first_mo2d_ptr->color = 0b1111111111100000;
        // }
        // Do not delete!!
        sln2663_lcd_tft_setpixel(graphic_2d_ptr->tft_dma_ptr,
                                 first_mo2d_ptr->bresenham.xn,
                                 first_mo2d_ptr->bresenham.yn,
                                 movable_object_2d_get_color(first_mo2d_ptr));
    }
}

/*!
    \brief      Treat collision movable objects.
    \param[in]  graphic_2d_ptr
    \param[in]  background_color background color.
    \param[in]  collision_color collision color.
    \param[out] graphic_2d_ptr
    \retval     TRUE if more loops are neccesary.
*/
int sln2663_graphic_2d_treat_collisions_movable_objects(sln2663_graphic_2d_ptr graphic_2d_ptr, uint16_t background_color, uint16_t collision_color)
{
    int result = FALSE;
    movable_object_2d_ptr now_mo2d_ptr;

    now_mo2d_ptr = graphic_2d_ptr->last_mo2d_ptr; // Last movable object.
    // Move
    do
    {
        now_mo2d_ptr = now_mo2d_ptr->next_movable_object_2d_ptr; // Next movable object.
        if ((movable_object_2d_get_status(now_mo2d_ptr) != DEAD) &&
            ((movable_object_2d_get_status(now_mo2d_ptr) == MOVE) || (movable_object_2d_get_status(now_mo2d_ptr) == RICOCHET)))
        {
            sln2663_graphic_2d_treat_collisions_movable_object(graphic_2d_ptr, now_mo2d_ptr, background_color, collision_color); // Treat collisions over this movable object.
        }
        if (movable_object_2d_get_status(now_mo2d_ptr) != DEAD)
        {
            result = TRUE;
        }
    } while (now_mo2d_ptr != graphic_2d_ptr->last_mo2d_ptr);
    return result;
}
