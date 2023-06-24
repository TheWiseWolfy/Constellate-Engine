/*
File:KeyCodes.h

This file is simply boiler plate key codes taken and renamed from GLFW, 
Providing my own set of KeyCode macros makes the users of the engine not depend 
directly on GLFW macros. 

Relevant documentation:
Keyboard keys: https://www.glfw.org/docs/3.3/group__keys.html

*/
 
#define 	CSL_KEY_UNKNOWN   -1
#define 	CSL_KEY_SPACE   32
#define 	CSL_KEY_APOSTROPHE   39 /* ' */
#define 	CSL_KEY_COMMA   44 /* , */
#define 	CSL_KEY_MINUS   45 /* - */
#define 	CSL_KEY_PERIOD   46 /* . */
#define 	CSL_KEY_SLASH   47 /* / */

#define 	CSL_KEY_0   48
#define 	CSL_KEY_1   49
#define 	CSL_KEY_2   50
#define 	CSL_KEY_3   51
#define 	CSL_KEY_4   52
#define 	CSL_KEY_5   53
#define 	CSL_KEY_6   54
#define 	CSL_KEY_7   55
#define 	CSL_KEY_8   56
#define 	CSL_KEY_9   57

#define 	CSL_KEY_SEMICOLON   59 /* ; */
#define 	CSL_KEY_EQUAL   61 /* = */
#define 	CSL_KEY_A   65
#define 	CSL_KEY_B   66
#define 	CSL_KEY_C   67
#define 	CSL_KEY_D   68
#define 	CSL_KEY_E   69
#define 	CSL_KEY_F   70
#define 	CSL_KEY_G   71
#define 	CSL_KEY_H   72
#define 	CSL_KEY_I   73
#define 	CSL_KEY_J   74
#define 	CSL_KEY_K   75
#define 	CSL_KEY_L   76
#define 	CSL_KEY_M   77
#define 	CSL_KEY_N   78
#define 	CSL_KEY_O   79
#define 	CSL_KEY_P   80
#define 	CSL_KEY_Q   81
#define 	CSL_KEY_R   82
#define 	CSL_KEY_S   83
#define 	CSL_KEY_T   84
#define 	CSL_KEY_U   85
#define 	CSL_KEY_V   86
#define 	CSL_KEY_W   87
#define 	CSL_KEY_X   88
#define 	CSL_KEY_Y   89
#define 	CSL_KEY_Z   90

#define 	CSL_KEY_LEFT_BRACKET   91 /* [ */
#define 	CSL_KEY_BACKSLASH   92 /* \ */
#define 	CSL_KEY_RIGHT_BRACKET   93 /* ] */
#define 	CSL_KEY_GRAVE_ACCENT   96 /* ` */
#define 	CSL_KEY_WORLD_1   161 /* non-US #1 */
#define 	CSL_KEY_WORLD_2   162 /* non-US #2 */
#define 	CSL_KEY_ESCAPE   256
#define 	CSL_KEY_ENTER   257
#define 	CSL_KEY_TAB   258
#define 	CSL_KEY_BACKSPACE   259
#define 	CSL_KEY_INSERT   260
#define 	CSL_KEY_DELETE   261
#define 	CSL_KEY_RIGHT   262
#define 	CSL_KEY_LEFT   263
#define 	CSL_KEY_DOWN   264
#define 	CSL_KEY_UP   265
#define 	CSL_KEY_PAGE_UP   266
#define 	CSL_KEY_PAGE_DOWN   267
#define 	CSL_KEY_HOME   268
#define 	CSL_KEY_END   269
#define 	CSL_KEY_CAPS_LOCK   280
#define 	CSL_KEY_SCROLL_LOCK   281
#define 	CSL_KEY_NUM_LOCK   282
#define 	CSL_KEY_PRINT_SCREEN   283
#define 	CSL_KEY_PAUSE   284

#define 	CSL_KEY_F1   290
#define 	CSL_KEY_F2   291
#define 	CSL_KEY_F3   292
#define 	CSL_KEY_F4   293
#define 	CSL_KEY_F5   294
#define 	CSL_KEY_F6   295
#define 	CSL_KEY_F7   296
#define 	CSL_KEY_F8   297
#define 	CSL_KEY_F9   298
#define 	CSL_KEY_F10   299
#define 	CSL_KEY_F11   300
#define 	CSL_KEY_F12   301

#define 	CSL_KEY_KP_0   320
#define 	CSL_KEY_KP_1   321
#define 	CSL_KEY_KP_2   322
#define 	CSL_KEY_KP_3   323
#define 	CSL_KEY_KP_4   324
#define 	CSL_KEY_KP_5   325
#define 	CSL_KEY_KP_6   326
#define 	CSL_KEY_KP_7   327
#define 	CSL_KEY_KP_8   328
#define 	CSL_KEY_KP_9   329

#define 	CSL_KEY_KP_DECIMAL   330
#define 	CSL_KEY_KP_DIVIDE   331
#define 	CSL_KEY_KP_MULTIPLY   332
#define 	CSL_KEY_KP_SUBTRACT   333
#define 	CSL_KEY_KP_ADD   334
#define 	CSL_KEY_KP_ENTER   335
#define 	CSL_KEY_KP_EQUAL   336

#define 	CSL_KEY_LEFT_SHIFT   340
#define 	CSL_KEY_LEFT_CONTROL   341
#define 	CSL_KEY_LEFT_ALT   342
#define 	CSL_KEY_LEFT_SUPER   343
#define 	CSL_KEY_RIGHT_SHIFT   344
#define 	CSL_KEY_RIGHT_CONTROL   345
#define 	CSL_KEY_RIGHT_ALT   346
#define 	CSL_KEY_RIGHT_SUPER   347
#define 	CSL_KEY_MENU   348

#define CSL_RELEASE   0
#define CSL_PRESS   1
#define CSL_REPEAT   2