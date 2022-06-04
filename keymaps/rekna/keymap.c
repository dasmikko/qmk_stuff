#include "print.h"
#include QMK_KEYBOARD_H
#include "raw_hid.h"

#ifdef BONGOCAT_ENABLE
    #include <bongocat.h>
#endif

enum layers {
    _QWERTY = 0,
    _DVORAK,
    _COLEMAK_DH,
    _NAV,
    _SYM,
    _FUNCTION,
    _ADJUST,
    _GAMING,
};


// Aliases for readability
#define QWERTY   DF(_QWERTY)
#define COLEMAK  DF(_COLEMAK_DH)
#define DVORAK   DF(_DVORAK)

#define SYM      MO(_SYM)
#define NAV      MO(_NAV)
#define FKEYS    MO(_FUNCTION)
#define ADJUST   MO(_ADJUST)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)

// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_ENT, KC_ESC, MO(5), TG(5), KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, LT(4,KC_DEL), KC_LGUI, MO(6), KC_LALT, KC_SPC, MO(3), MO(4), KC_BSPC, KC_RALT, TG(7), KC_RGUI),
	[1] = LAYOUT(KC_TAB, KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_BSPC, MT(MOD_LCTL, KC_ESC), KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, MT(MOD_RCTL, KC_MINUS), KC_LSFT, KC_SCLN, KC_Q, KC_J, KC_K, KC_X, KC_LBRC, KC_CAPS, MO(5), KC_RBRC, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_RSFT, MO(6), KC_LGUI, MT(MOD_LALT, KC_ENT), KC_SPC, MO(3), MO(4), KC_SPC, KC_RALT, KC_RGUI, KC_APP),
	[2] = LAYOUT(KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_BSPC, MT(MOD_LCTL, KC_ESC), KC_A, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, KC_O, MT(MOD_RCTL, KC_QUOTE), KC_LSFT, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_LBRC, KC_CAPS, MO(5), KC_RBRC, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_LGUI, MO(6), KC_LALT, KC_SPC, MO(3), MO(4), KC_SPC, KC_RALT, KC_RGUI, KC_APP),
	[3] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_HOME, KC_UP, KC_END, KC_VOLU, KC_DEL, KC_TRNS, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_TRNS, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, KC_INS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SCRL, KC_TRNS, KC_TRNS, KC_PAUS, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_PSCR, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[4] = LAYOUT(KC_BSLS, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_LSFT, LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), KC_EQL, KC_RBRC, KC_NUHS, LSFT(KC_NO), KC_LSFT, KC_NUBS, RALT(KC_2), RALT(KC_3), RALT(KC_4), LSFT(KC_6), KC_TRNS, KC_TRNS, KC_TRNS, KC_RCBR, RALT(KC_7), RALT(KC_0), RALT(KC_8), RALT(KC_9), KC_SLSH, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_RALT, KC_TRNS),
	[5] = LAYOUT(KC_TRNS, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_P7, KC_P8, KC_P9, KC_PSLS, KC_PAST, KC_PMNS, KC_TRNS, KC_F5, KC_F6, KC_F7, KC_F8, KC_TRNS, KC_P4, KC_P5, KC_P6, KC_PPLS, KC_PCMM, KC_PEQL, KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_TRNS, KC_TRNS, KC_LALT, KC_LSFT, KC_TRNS, KC_P1, KC_P2, KC_P3, KC_PENT, KC_TRNS, KC_RCTL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LCTL, KC_TRNS, KC_P0, KC_PDOT, KC_NUM),
	[6] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, DF(0), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DF(1), KC_TRNS, KC_TRNS, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DF(2), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[7] = LAYOUT(KC_TAB, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_LSFT, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};



void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=false;
  //debug_keyboard=true;
  //debug_mouse=true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif 
  return true;
}


// HID Stuff
void raw_hid_receive(uint8_t *data, uint8_t length) {
    uprintf("Hello");
    raw_hid_send(data, length);
}


#ifdef OLED_ENABLE
// Used to draw on to the oled screen
bool oled_task_user(void) { 
    if (is_keyboard_master()) {
        #ifdef BONGOCAT_ENABLE
            render_bongocat();  // renders bongocat
        #endif
        
        oled_set_cursor(0, 0);                            // sets cursor to (row, column) using charactar spacing (5 rows on 128x32 screen, anything more will overflow back to the top)
        //sprintf(wpm_str, "WPM:%03d", get_current_wpm());  // edit the string to change wwhat shows up, edit %03d to change how many digits show up
        //oled_write(wpm_str, false);                       // writes wpm on top left corner of string
        oled_write_P(PSTR("WPM: "), false);
        oled_write(get_u8_str(get_current_wpm(), '0'), false);
        
        oled_set_cursor(0, 5);
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
            case _ADJUST:
                oled_write_P(PSTR("Adjust\n"), false);
                break;
            case _GAMING:
                oled_write_P(PSTR("Gaming\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }

        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPLCK ") : PSTR("       "), false);	
    } else {
	oled_write_P(PSTR("rekNa board\n"), false);
    }  
    
    return false;
}
#endif

