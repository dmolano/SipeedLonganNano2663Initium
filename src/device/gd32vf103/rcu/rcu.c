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

#include "device\gd32vf103\rcu\rcu.h"

// ---------------------------------------------------------------------
// Private Constants
// ---------------------------------------------------------------------
#define RCU_PERIPH_CLOCK_DISABLE 0 /*!< description */

// ---------------------------------------------------------------------
// Private Prototypes
// ---------------------------------------------------------------------
/*!
    \brief      function
    \param[in]  none
    \param[out] none
    \retval     system error
*/

// ---------------------------------------------------------------------
// Public Bodies
// ---------------------------------------------------------------------
/*!
    \brief      RCU initialization function.
    \param[in]  rcu_periph a rcu_periph_enum.
    \param[out] none
    \retval     none
*/
// TODO Put a prefix to 'rcu_init'
void rcu_init(rcu_periph_enum rcu_periph)
{
    static uint32_t rcus_periph_clock_enable = RCU_PERIPH_CLOCK_DISABLE;
    uint32_t rcu_periph_mask = BIT(RCU_BIT_POS(rcu_periph));

    if ((rcus_periph_clock_enable & rcu_periph_mask) == RCU_PERIPH_CLOCK_DISABLE)
    {
        rcu_periph_clock_enable(rcu_periph);
        rcus_periph_clock_enable |= rcu_periph_mask;
    }
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
