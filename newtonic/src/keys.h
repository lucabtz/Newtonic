/*
 *   Newtonic
 *   Copyright (C) 2019 Luca "ekardnam" Bertozzi <luca.bertozzi11@studio.unibo.it>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#define 	NW_KEY_UNKNOWN   -1
#define 	NW_KEY_SPACE   32
#define 	NW_KEY_APOSTROPHE   39 /* ' */
#define 	NW_KEY_COMMA   44 /* , */
#define 	NW_KEY_MINUS   45 /* - */
#define 	NW_KEY_PERIOD   46 /* . */
#define 	NW_KEY_SLASH   47 /* / */
#define 	NW_KEY_0   48
#define 	NW_KEY_1   49
#define 	NW_KEY_2   50
#define 	NW_KEY_3   51
#define 	NW_KEY_4   52
#define 	NW_KEY_5   53
#define 	NW_KEY_6   54
#define 	NW_KEY_7   55
#define 	NW_KEY_8   56
#define 	NW_KEY_9   57
#define 	NW_KEY_SEMICOLON   59 /* ; */
#define 	NW_KEY_EQUAL   61 /* = */
#define 	NW_KEY_A   65
#define 	NW_KEY_B   66
#define 	NW_KEY_C   67
#define 	NW_KEY_D   68
#define 	NW_KEY_E   69
#define 	NW_KEY_F   70
#define 	NW_KEY_G   71
#define 	NW_KEY_H   72
#define 	NW_KEY_I   73
#define 	NW_KEY_J   74
#define 	NW_KEY_K   75
#define 	NW_KEY_L   76
#define 	NW_KEY_M   77
#define 	NW_KEY_N   78
#define 	NW_KEY_O   79
#define 	NW_KEY_P   80
#define 	NW_KEY_Q   81
#define 	NW_KEY_R   82
#define 	NW_KEY_S   83
#define 	NW_KEY_T   84
#define 	NW_KEY_U   85
#define 	NW_KEY_V   86
#define 	NW_KEY_W   87
#define 	NW_KEY_X   88
#define 	NW_KEY_Y   89
#define 	NW_KEY_Z   90
#define 	NW_KEY_LEFT_BRACKET   91 /* [ */
#define 	NW_KEY_BACKSLASH   92 /* \ */
#define 	NW_KEY_RIGHT_BRACKET   93 /* ] */
#define 	NW_KEY_GRAVE_ACCENT   96 /* ` */
#define 	NW_KEY_WORLD_1   161 /* non-US #1 */
#define 	NW_KEY_WORLD_2   162 /* non-US #2 */
#define 	NW_KEY_ESCAPE   256
#define 	NW_KEY_ENTER   257
#define 	NW_KEY_TAB   258
#define 	NW_KEY_BACKSPACE   259
#define 	NW_KEY_INSERT   260
#define 	NW_KEY_DELETE   261
#define 	NW_KEY_RIGHT   262
#define 	NW_KEY_LEFT   263
#define 	NW_KEY_DOWN   264
#define 	NW_KEY_UP   265
#define 	NW_KEY_PAGE_UP   266
#define 	NW_KEY_PAGE_DOWN   267
#define 	NW_KEY_HOME   268
#define 	NW_KEY_END   269
#define 	NW_KEY_CAPS_LOCK   280
#define 	NW_KEY_SCROLL_LOCK   281
#define 	NW_KEY_NUM_LOCK   282
#define 	NW_KEY_PRINT_SCREEN   283
#define 	NW_KEY_PAUSE   284
#define 	NW_KEY_F1   290
#define 	NW_KEY_F2   291
#define 	NW_KEY_F3   292
#define 	NW_KEY_F4   293
#define 	NW_KEY_F5   294
#define 	NW_KEY_F6   295
#define 	NW_KEY_F7   296
#define 	NW_KEY_F8   297
#define 	NW_KEY_F9   298
#define 	NW_KEY_F10   299
#define 	NW_KEY_F11   300
#define 	NW_KEY_F12   301
#define 	NW_KEY_F13   302
#define 	NW_KEY_F14   303
#define 	NW_KEY_F15   304
#define 	NW_KEY_F16   305
#define 	NW_KEY_F17   306
#define 	NW_KEY_F18   307
#define 	NW_KEY_F19   308
#define 	NW_KEY_F20   309
#define 	NW_KEY_F21   310
#define 	NW_KEY_F22   311
#define 	NW_KEY_F23   312
#define 	NW_KEY_F24   313
#define 	NW_KEY_F25   314
#define 	NW_KEY_KP_0   320
#define 	NW_KEY_KP_1   321
#define 	NW_KEY_KP_2   322
#define 	NW_KEY_KP_3   323
#define 	NW_KEY_KP_4   324
#define 	NW_KEY_KP_5   325
#define 	NW_KEY_KP_6   326
#define 	NW_KEY_KP_7   327
#define 	NW_KEY_KP_8   328
#define 	NW_KEY_KP_9   329
#define 	NW_KEY_KP_DECIMAL   330
#define 	NW_KEY_KP_DIVIDE   331
#define 	NW_KEY_KP_MULTIPLY   332
#define 	NW_KEY_KP_SUBTRACT   333
#define 	NW_KEY_KP_ADD   334
#define 	NW_KEY_KP_ENTER   335
#define 	NW_KEY_KP_EQUAL   336
#define 	NW_KEY_LEFT_SHIFT   340
#define 	NW_KEY_LEFT_CONTROL   341
#define 	NW_KEY_LEFT_ALT   342
#define 	NW_KEY_LEFT_SUPER   343
#define 	NW_KEY_RIGHT_SHIFT   344
#define 	NW_KEY_RIGHT_CONTROL   345
#define 	NW_KEY_RIGHT_ALT   346
#define 	NW_KEY_RIGHT_SUPER   347
#define 	NW_KEY_MENU   348
#define 	NW_KEY_LAST   NW_KEY_MENU

#define NW_BUTTON_LEFT 0
#define NW_BUTTON_RIGHT 1
#define NW_BUTTON_CENTER 2
