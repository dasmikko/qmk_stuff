#include QMK_KEYBOARD_H
#include "keymap_danish.h"
#include "sendstring_danish.h"

#ifdef BONGOCAT_ENABLE
    #include <bongocat.h>
#endif

enum layers {
    _QWERTY = 0,
    _ALT,
    _NAV,
    _SYM,
    _FUNCTION,
    _SYM_ALT
};


// Aliases for readability
#define QWERTY   DF(_QWERTY)

#define SYM      MO(_SYM)
#define SYM_ALT  MO(_SYM_ALT)
#define NAV      MO(_NAV)
#define FKEYS    MO(_FUNCTION)
#define TFKEYS   TT(_FUNCTION)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)


// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

/* MT(MOD_RALT, KC_ESC) */


enum combo_events {
  COMBO_NUMPAD,
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM numpad_combo[] = {KC_LGUI, KC_LALT, COMBO_END};

combo_t key_combos[] = {
  [COMBO_NUMPAD] = COMBO(numpad_combo, MO(_ALT)),
};





// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-----------------------------------------------.                              ,-------------------------------------------.
 * |  Tab    |   Q  |   W  |   E  |   R  |   T     |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
 * |---------+------+------+------+------+---------|                              |------+------+------+------+------+--------|
 * |  Shift  |   A  |   S  |   D  |   F  |   G     |                              |   H  |   J  |   K  |   L  | ;  : |  Enter |
 * |---------+------+------+------+------+---------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |  Ctrl   |   Z  |   X  |   C  |   V  |   B     | Left | Right|  | AltGr|  Up  |   N  |   M  | , ;  | . :  | - _  |  RCTRL |
 * `-----------------------+------+------+---------+------+------|  |------+------+------+------+------+----------------------'
 *                         | LGUI | LAlt | Sym_Alt | Space| Nav  |  | Sym  | Down |  ESC | RGUI | Menu |
 *                         `-------------------------------------'  `----------------------------------'
 */
	[_QWERTY] = LAYOUT(
        KC_TAB  ,  KC_Q  ,  KC_W  ,  KC_E     ,  KC_R     ,  KC_T          ,                                                                                               KC_Y     ,  KC_U     ,  KC_I     ,  KC_O    ,  KC_P     ,  KC_BSPC, 
        KC_LSFT ,  KC_A  ,  KC_S  ,  KC_D     ,  KC_F     ,  KC_G          ,                                                                                               KC_H     ,  KC_J     ,  KC_K     ,  KC_L    ,  KC_NUHS   ,  KC_ENT, 
        KC_LCTL ,  KC_Z  ,  KC_X  ,  KC_C     ,  KC_V     ,  KC_B          ,  KC_LEFT   ,  KC_RGHT   ,                                 MT(MOD_RALT, KC_ESC)  ,  KC_UP   ,  KC_N     ,  KC_M     ,  KC_COMM  ,  KC_DOT  ,  KC_SLSH  ,  MT(MOD_RSFT, KC_RCTL), 
                                     KC_LGUI  ,  KC_LALT  ,  MO(_SYM_ALT)  ,  KC_SPC    ,  NAV       ,                                 SYM                   ,  KC_DOWN ,  KC_ESC   ,  TFKEYS   ,  KC_DOWN
    ),

/*
 * Base Layer: ALT Layer
 *
 * ,-------------------------------------------------.                                         ,----------------------------------------------------.
 * |  TAB  |  F9  |  F10  |  F11   |  F12   |  TRNS  |                                         |  NUM7  |  NUM8  |  NUM9  |  /    |   *    |  Bksp  |
 * |-------+------+-------+--------+--------+--------|                                         |--------+--------+--------+-------+--------+--------|
 * |  TRNS |  F5  |  F6   |  F7    |  F8    |  TRNS  |                                         |  NUM4  |  NUM5  |  NUM6  |   +   |  .     |  Enter |
 * |-------+------+-------+--------+--------+--------+---------------.     ,-------------------+--------+--------+--------+-------+--------+--------|
 * |  TRNS |  F1  |  F2   |  F3    |  F4    |  F     |  G      |  H  |     |  LSFT   |  TRNS   |  NUM1  |  NUM2  |  NUM3  | Enter |  TRNS  |  RCTL  |
 * `----------------------+--------+--------+--------+---------+-----|     |---------+---------+--------+--------+--------+-------------------------'
 *                        |  TRNS  |  TRNS  |  C     |  Space  |  V  |     |  LCTL   |  TRNS   |  NUM0  |  ,     |    .   |
 *                        `------------------------------------------'     `----------------------------------------------'
 */
    [_ALT] = LAYOUT(
        LALT(KC_TAB)  ,  KC_F9  ,  KC_F10  ,  KC_F11   ,  KC_F12   ,  KC_TRNS  ,                                                                            KC_P7  ,  KC_P8      ,  KC_P9    ,  KC_PSLS  ,  KC_PAST  ,  KC_BSPC  ,  
        KC_TRNS       ,  KC_F5  ,  KC_F6   ,  KC_F7    ,  KC_F8    ,  KC_TRNS  ,                                                                            KC_P4  ,  KC_P5      ,  KC_P6    ,  KC_PPLS  ,  KC_PCMM  ,  KC_ENT  ,  
        KC_TRNS       ,  KC_F1  ,  KC_F2   ,  KC_F3    ,  KC_F4    ,  KC_TRNS  ,  KC_TRNS  ,  KC_LALT  ,                            KC_LSFT  ,  KC_TRNS  ,  KC_P1  ,  KC_P2      ,  KC_P3    ,  KC_PENT  ,  KC_TRNS  ,  KC_RCTL  , 
                                              KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,                            KC_LCTL  ,  KC_TRNS  ,  KC_P0  ,  KC_KP_DOT  ,  KC_DOT
    ),

/*
 * Base Layer: Navigation Layer
 *
 * ,---------------------------------------------------------------.                                       ,----------------------------------------------------.
 * |  TRNS  |  TRNS  |  TRNS  |  TRNS  |  TRNS  |  LSFT + PGUP     |                                       |  INS   |  HOME  |  PGUP  |  PAUS  |  LBRC  |  TRNS  |
 * |--------+--------+--------+--------+--------+------------------|                                       |--------+--------+--------+--------+--------+--------|
 * |  TRNS  |  LGUI  |  LALT  |  TRNS  |  TRNS  |  LSFT + PGDN     |                                       |  DEL   |  END   |  PGDN  |  SCLN  |  QUOT  |  TRNS  |
 * |--------+--------+--------+--------+--------+------------------+---------------.     ,-----------------+--------+--------+--------+--------+--------+--------|
 * |  TRNS  |  TRNS  |  NUM   |  TRNS  |  TRNS  |  TRNS            |  G      |  H  |     |  HOME  |  PGUP  |  END   |  MPRV  |  MPLY  |  MNXT  |  TRNS  |  PSCR  |
 * `--------------------------+--------+--------+------------------+---------+-----|     |--------+--------+--------+--------+--------+--------------------------'
 *                            |  TRNS  |  TRNS  |  TRNS            |  Space  |  V  |     |  TRNS  |  PGDN  |  MUTE  |  VOLD  |  VOLU  |
 *                            `----------------------------------------------------'     `--------------------------------------------'
 */



    [_NAV] = LAYOUT(
        KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  , KC_TRNS  ,  KC_TRNS  ,  LSFT(KC_PGUP)  ,                                                              KC_INS   ,  KC_HOME  ,  KC_PGUP  ,  KC_PAUS  ,  KC_LBRC  ,  KC_TRNS, 
        KC_TRNS  ,  KC_LGUI  ,  KC_LALT  , KC_TRNS  ,  KC_TRNS  ,  KC_TRNS        ,                                                              KC_DEL   ,  KC_END   ,  KC_PGDN  ,  KC_SCLN  ,  KC_QUOT  ,  KC_TRNS, 
        KC_TRNS  ,  KC_TRNS  ,  KC_NUM   , KC_TRNS  ,  KC_TRNS  ,  KC_TRNS        ,  KC_HOME  ,  KC_END   ,              KC_HOME  ,  KC_PGUP  ,  KC_END   ,  KC_MPRV  ,  KC_MPLY  ,  KC_MNXT  ,  KC_TRNS  ,  KC_PSCR,
                                           KC_TRNS  ,  KC_TRNS  ,  KC_TRNS        ,  KC_TRNS  ,  KC_TRNS  ,              KC_TRNS  ,  KC_PGDN  ,  KC_MUTE  ,  KC_VOLD  ,  KC_VOLU
    ),
    [_SYM] = LAYOUT(
        KC_GRV   ,  KC_1        ,  KC_2        ,  KC_3        ,  KC_4        ,  KC_5,                                                                                                   KC_6        ,  KC_7        ,  KC_8        ,  KC_9        ,  KC_0     ,  KC_MINS, 
        KC_LSFT  ,  LSFT(KC_1)  ,  LSFT(KC_2)  ,  LSFT(KC_3)  ,  LSFT(KC_4)  ,  LSFT(KC_7)  ,                                                                                           LSFT(KC_8)  ,  LSFT(KC_9)  ,  KC_EQL      ,  KC_RBRC     ,  KC_NUHS  ,  LSFT(KC_NO), 
        KC_LSFT  ,  KC_NUBS     ,  RALT(KC_2)  ,  RALT(KC_3)  ,  RALT(KC_4)  ,  LSFT(KC_6)  ,  KC_TRNS  ,  KC_TRNS  ,                                           KC_TRNS  ,  KC_RCBR  ,  RALT(KC_7)  ,  RALT(KC_0)  ,  RALT(KC_8)  ,  RALT(KC_9)  ,  KC_SLSH  ,  KC_TRNS,  
                                                  KC_TRNS     ,  KC_TRNS     ,  KC_TRNS     ,  KC_TRNS  ,  KC_TRNS  ,                                           KC_TRNS  ,  KC_TRNS  ,  KC_TRNS     ,  KC_RALT     ,  KC_TRNS
    ),

/*
 * Base Layer: Function Layer
 *
 * ,-------------------------------------------------.                                              ,--------------------------------------------------------------------------------.
 * |  TAB  |  F9  |  F10  |  F11   |  F12   |  TRNS  |                                              |  NUM7          |  NUM8        |  NUM9        |  /            |   *    |  Bksp  |
 * |-------+------+-------+--------+--------+--------|                                              |----------------+--------------+--------------+---------------+--------+--------|
 * |  TRNS |  F5  |  F6   |  F7    |  F8    |  TRNS  |                                              |  NUM4          |  Mouse SUp   |  Mouse up    |  Mouse SDown  |  .     |  Enter |
 * |-------+------+-------+--------+--------+--------+---------------.     ,------------------------+----------------+--------------+--------------+---------------+--------+--------|
 * |  TRNS |  F1  |  F2   |  F3    |  F4    |  F     |  G      |  H  |     |  LSFT  |  TRNS         |  NUM1          |  Mouse left  |  Mouse down  |  Mouse right  |  TRNS  |  RCTL  |
 * `----------------------+--------+--------+--------+---------+-----|     |--------+---------------+----------------+--------------+--------------+---------------------------------'
 *                        |  TRNS  |  TRNS  |  C     |  Space  |  V  |     |  LCTL  |  Mouse Bleft  |  Mouse Bright  |  ,           |  .           |
 *                        `------------------------------------------'     `-----------------------------------------------------------------------'
 */

    [_FUNCTION] = LAYOUT(
        KC_TAB   ,  KC_F9  ,  KC_F10  ,  KC_F11   ,  KC_F12   ,  KC_TRNS  ,                                                                               KC_P7       ,  KC_P8        ,  KC_P9       ,  KC_PSLS        ,  KC_PAST  ,  KC_PMNS  ,  
        KC_TRNS  ,  KC_F5  ,  KC_F6   ,  KC_F7    ,  KC_F8    ,  KC_TRNS  ,                                                                               KC_P4       ,  KC_MS_WH_UP  ,  KC_MS_UP    ,  KC_MS_WH_DOWN  ,  KC_PCMM  ,  KC_PEQL  ,  
        KC_TRNS  ,  KC_F1  ,  KC_F2   ,  KC_F3    ,  KC_F4    ,  KC_TRNS  ,  KC_TRNS  ,  KC_LALT  ,                            KC_LSFT  ,  KC_TRNS     ,  KC_P1       ,  KC_MS_LEFT   ,  KC_MS_DOWN  ,  KC_MS_RIGHT    ,  KC_TRNS  ,  KC_RCTL  , 
                                         KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,                            KC_LCTL  ,  KC_MS_BTN1  ,  KC_MS_BTN2  ,  KC_TRNS      ,  KC_TRNS
    ),
    [_SYM_ALT] = LAYOUT(
        KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_SCLN  ,  KC_TRNS  ,  KC_TRNS  ,                                                                              KC_TRNS        ,  KC_TRNS        ,  KC_TRNS       ,  KC_QUOT        ,  KC_TRNS             ,  KC_DEL  ,  
        KC_TRNS  ,  KC_LBRC  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,                                                                              RALT(KC_NUBS)  ,  LSFT(KC_NUHS)  ,  RALT(KC_EQL)  ,  RALT(KC_RBRC)  ,  KC_TRNS             ,  KC_TRNS  ,  
        KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,                              KC_TRNS  ,  KC_TRNS  ,  KC_NUBS        ,  LSFT(KC_NUBS)  ,  LSFT(KC_7)    ,  LSFT(KC_0)     ,  KC_NONUS_BACKSLASH  ,  KC_TRNS  ,  
                                            KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,                              KC_TRNS  ,  KC_TRNS  ,  KC_TRNS        ,  KC_TRNS        ,  KC_TRNS
    )
};





#ifdef OLED_ENABLE
// Used to draw on to the oled screen
bool oled_task_user(void) { 
    if (is_keyboard_master()) {
        #ifdef BONGOCAT_ENABLE
            render_bongocat();  // renders bongocat
            oled_set_cursor(0, 0);
        #else
            static const char PROGMEM raw_logo[] = {
                0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,192,  0,  0,  0,  0,  0,  0,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 12, 12,252,252, 12, 12,  0,252,252, 56, 56,252,252,  0,  0,  0,  0,  0,  0,  0,
                0,  0,  0,  0,240,240,224,224,112,112, 48, 48, 48,  0,192,224,240,240,176,176,176,240,240,  0,  0,  0,255,255,255,192,224,224,224, 96, 96,  0,  0,  0,248,255, 31, 15, 63,120,240,192,128,  0,255,255,  0,128,192,192,224, 96, 96, 96, 96,224,128,128,  0,  0,  0,  0,  0,  0,  0,  0,255,255,127,112, 48,112,240,224,192,  0,  0,192,192,224,240,112,240,240,192,128,  0,  0,  0,128,128,192, 64, 96, 96,224,128,  0,  0,  0,192,192,128,128,192,192,192,  0,  0,128,128,128,192,192,254,254,248,  0,  0,  0,  0,  0,  0,  0, 
                0,  0,  0,  0, 63, 63,  3,  0,  0,  0,  0,  0,  0,  0,  7, 15, 31, 59, 57, 49, 49, 49, 49, 48, 56, 56,  1, 31, 31,  3,  7,  7, 14, 14, 12, 28, 28,  0,  7, 63, 60,  0,  0,  0,  0,  3, 15, 31, 31,  1,  0, 15, 15, 13, 12, 12, 12, 12, 12, 15, 15, 15, 30, 28, 24, 24, 24, 24,  0,  0, 31, 31, 24, 24, 24, 28, 30, 15,  7,  0, 31, 63, 57, 48, 48, 48, 56, 56, 31, 31,  0, 14, 31, 31, 27, 24, 24, 24, 12, 15, 31, 28,  0,  0, 31, 31,  3,  3,  1,  1,  0, 28, 63, 63, 51, 49, 49, 56, 60, 31, 31, 60, 56, 48, 48,  0,  0,  0,
            };
            oled_write_raw_P(raw_logo, sizeof(raw_logo));
            oled_set_cursor(0, 4);
        #endif
        
                                    // sets cursor to (row, column) using charactar spacing (5 rows on 128x32 screen, anything more will overflow back to the top)
        //sprintf(wpm_str, "WPM:%03d", get_current_wpm());  // edit the string to change wwhat shows up, edit %03d to change how many digits show up
        //oled_write(wpm_str, false);                       // writes wpm on top left corner of string
        oled_write_P(PSTR("WPM: "), false);
        oled_write(get_u8_str(get_current_wpm(), '0'), false);

        #ifdef BONGOCAT_ENABLE
            oled_set_cursor(0, 5);
        #else
            oled_set_cursor(0, 5);
        #endif
        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _QWERTY:
                oled_write_P(PSTR("QWERTY\n"), false);
                break;
            case _NAV:
                oled_write_P(PSTR("Nav\n"), false);
                break;
            case _SYM:
                oled_write_P(PSTR("Sym\n"), false);
                break;
            case _FUNCTION:
                oled_write_P(PSTR("Function\n"), false);
                break;
            case _SYM_ALT:
                oled_write_P(PSTR("Sym Alt\n"), false);
                break;
            case _ALT:
                oled_write_P(PSTR("Numpad\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }

        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPLCK ") : PSTR("       "), false);	
    } else {
        #ifdef BONGOCAT_ENABLE
            oled_write_P(PSTR("rekNa board\n"), false);
        #else
            
            // clang-format off
            static const char PROGMEM kyria_logo[] = {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x30, 0x0c, 0x06, 
0x02, 0x03, 0x01, 0x01, 0x01, 0x03, 0x06, 0x0c, 0x18, 0x30, 0xe0, 0x80, 0xc0, 0x60, 0x30, 0xf0, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x19, 0x61, 0xc2, 0x0c, 0x08, 0x9f, 0x9f, 0x60, 0x60, 0x20, 
0x20, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x3f, 0x30, 0x78, 0x87, 0x01, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x30, 0x0d, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 
0x80, 0x00, 0x00, 0x10, 0x00, 0x00, 0x04, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x40, 0x60, 
0x20, 0x20, 0x30, 0x30, 0x30, 0x30, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x01, 0x02, 0x84, 0xc4, 0xe4, 0xc2, 0xc2, 0x01, 0x00, 0x00, 0x80, 0xc0, 0x20, 0x18, 0x16, 0x11, 
0x10, 0x30, 0x20, 0x60, 0xc0, 0x80, 0x80, 0x80, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x30, 0x68, 0xc8, 0x88, 0x08, 0x18, 0x0c, 0x83, 0x81, 0xc0, 0x80, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x04, 0x04, 0x08, 0x08, 0x08, 
0x08, 0x08, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x06, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 
0x20, 0x20, 0x20, 0x40, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x30, 0x78, 0xc7, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0f, 0x08, 0x0c, 0x06, 0x08, 0x08, 0x0f, 0x06, 0xff, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 
0xe0, 0x00, 0x00, 0x03, 0x07, 0x04, 0x06, 0x01, 0x01, 0x02, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0f, 
0x78, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 
0x03, 0x1e, 0x70, 0x40, 0x40, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x68, 0x4c, 0x4c, 
0x44, 0x47, 0x40, 0x40, 0xc0, 0xf0, 0xff, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x02, 0x02, 0x02, 
0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x03, 0x1c, 0x30, 
0x10, 0x10, 0x08, 0x0c, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
            };
            oled_set_cursor(0, 0);
            // clang-format on
            oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
            //oled_set_cursor(10, 7);
            //oled_write_P(PSTR("rekNa board\n"), false);
        #endif
        
    }  
    
    return false;
}
#endif
