/* Copyright 2022 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_ANIMATIONS
#    define RGBLIGHT_HUE_STEP  8
#    define RGBLIGHT_SAT_STEP  8
#    define RGBLIGHT_VAL_STEP  8
#endif

#define DEBOUNCE 18

#define NO_MUSIC_MODE
#define LAYER_STATE_16BIT

#ifdef TAP_DANCE_ENABLE
    #define TAPPING_TERM 175
#endif

// Prevent normal rollover on alphas from accidentally triggering mods.
//#define IGNORE_MOD_TAP_INTERRUPT

#ifdef VIA_ENABLE
    //#define LAYER_STATE_8BIT
    #define DYNAMIC_KEYMAP_LAYER_COUNT 9
#endif

#define TAPPING_TOGGLE 2

// Inertia mouse keys
#define MOUSEKEY_INERTIA true
#define MOUSEKEY_INTERVAL 8
#define MOUSEKEY_DELAY 50 
#define MOUSEKEY_MAX_SPEED 18
#define MOUSEKEY_TIME_TO_MAX 32
#define MOUSEKEY_FRICTION 38
#define MOUSEKEY_MOVE_DELTA 1

// Kinetic
// #define MK_KINETIC_SPEED true
// #define MOUSEKEY_DELAY 5
// #define MOUSEKEY_INTERVAL 10
// #define MOUSEKEY_MOVE_DELTA 16
// #define MOUSEKEY_INITIAL_SPEED 100
// #define MOUSEKEY_BASE_SPEED 5000
// #define MOUSEKEY_DECELERATED_SPEED 400
// #define MOUSEKEY_ACCELERATED_SPEED 3000
// #define MOUSEKEY_WHEEL_INITIAL_MOVEMENTS 16
// #define MOUSEKEY_WHEEL_BASE_MOVEMENTS 32
// #define MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS 48
// #define MOUSEKEY_WHEEL_DECELERATED_MOVEMENTS 8 */

// Accelerated mouse keys
// #define MOUSEKEY_TIME_TO_MAX 50

// #define TAPPING_TERM 175 // Milliseconds
// #define TAPPING_TERM_PER_KEY




#define BONGOCAT_ENABLE

//#undef RGBLIGHT_ANIMATIONS
//#undef RGBLIGHT_EFFECT_BREATHING
//#undef RGBLIGHT_EFFECT_RAINBOW_MOOD
//#undef RGBLIGHT_EFFECT_RAINBOW_SWIRL
//#undef RGBLIGHT_EFFECT_KNIGHT
#undef RGBLIGHT_EFFECT_SNAKE
#undef RGBLIGHT_EFFECT_CHRISTMAS
#undef RGBLIGHT_EFFECT_STATIC_GRADIENT
#undef RGBLIGHT_EFFECT_RGB_TEST
#undef RGBLIGHT_EFFECT_ALTERNATING
#undef RGBLIGHT_EFFECT_TWINKLE


#define SPLIT_WPM_ENABLE
#define SPLIT_TRANSPORT_MIRROR
    

#define I2C1_CLOCK_SPEED  1000000
