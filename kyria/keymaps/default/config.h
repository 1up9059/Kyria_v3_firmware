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


#define OLED_DRIVER_ENABLE
#define SPLIT_WRAP_SPI_KV       // o el que uses para tu transporte (I2C/SPI)
#define SPLIT_MODS_ENABLE   

/* ------ Opciones extra de RGB Matrix ------ */
#define SPLIT_WPM_ENABLE
#define RGB_DISABLE_WHEN_USB_SUSPENDED     // se apaga al suspender el host
#define RGB_MATRIX_TIMEOUT 300000          // se apaga tras 5 min sin teclear
#define WPM_SAMPLE_SECONDS 6               // se calcula el promedio de palabras cada 6 s

/* -- Compila solo los efectos que uses (ahorra ~25 kB) -- */
#define ENABLE_RGB_MATRIX_SOLID_COLOR
#define RGBLIGHT_EFFECT_BREATHING
#define ENABLE_RGB_MATRIX_CYCLE_ALL
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define ENABLE_RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_RGB_TEST
#    define RGBLIGHT_EFFECT_ALTERNATING
#    define RGBLIGHT_EFFECT_TWINKLE
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8

#define TAPPING_TERM 175
#define TAPPING_TERM_PER_KEY



