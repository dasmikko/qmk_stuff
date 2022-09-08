#include QMK_KEYBOARD_H

#ifdef BONGOCAT_ENABLE
    #include <bongocat.h>
#endif

enum {
    TD_ESC_CAPS,
    CT_CLN,
    TD_A_AA,
    TD_O_OE,
    TD_E_AE,
};

// Tap dance tap and hold implementation

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    qk_tap_dance_action_t *action;

    switch (keycode) {
        case TD(TD_A_AA):  // list all tap dance keycodes with tap-hold configurations
        case TD(TD_O_OE):
        case TD(TD_E_AE):
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
    }
    return true;
}

void tap_dance_tap_hold_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(qk_tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }






enum layers {
    _QWERTY = 0,
    _GAMING,
    _COLEMAK_DH,
    _NAV,
    _SYM,
    _FUNCTION,
    _ADJUST,
    _SYM_ALT
};


// Aliases for readability
#define QWERTY   DF(_QWERTY)
#define GAMING   DF(_GAMING)
#define DVORAK   DF(_DVORAK)

#define SYM      MO(_SYM)
#define SYM_ALT  MO(_SYM_ALT)
#define NAV      MO(_NAV)
#define FKEYS    MO(_FUNCTION)
#define ADJUST   MO(_ADJUST)
#define TGAMING  TT(_GAMING)
#define TFKEYS   TT(_FUNCTION)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)



// Tap Dance declarations

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [CT_CLN] = ACTION_TAP_DANCE_TAP_HOLD(KC_COLN, KC_SCLN),
    [TD_A_AA] = ACTION_TAP_DANCE_TAP_HOLD(KC_A, KC_LBRC),
    [TD_O_OE] = ACTION_TAP_DANCE_TAP_HOLD(KC_O, KC_QUOT),
};


// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

/* MT(MOD_RALT, KC_ESC) */

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = LAYOUT(
        KC_TAB  ,  KC_Q          , KC_W    ,  KC_E     ,  KC_R          ,  KC_T     ,                                                                                   KC_Y     ,  KC_U     ,  KC_I     ,  TD(TD_O_OE)  ,  KC_P     ,  KC_BSPC, 
        KC_LSFT ,  TD(TD_A_AA)   , KC_S    ,  KC_D     ,  KC_F          ,  KC_G     ,                                                                                   KC_H     ,  KC_J     ,  KC_K     ,  KC_L         ,  KC_SCLN  ,  KC_ENT, 
        KC_LCTL ,  KC_Z  , KC_X  , KC_C    ,  KC_V     ,  KC_B          ,  KC_LEFT  ,  KC_RGHT   ,                         KC_UP  ,  KC_DOWN               ,  KC_N   ,  KC_M     ,  KC_COMM  ,  KC_DOT   ,  KC_SLSH      ,  KC_RCTL, 
                                   KC_LGUI ,  KC_LALT  ,  MO(_SYM_ALT)  ,  KC_SPC   ,  NAV       ,                         SYM    ,  MT(MOD_RALT, KC_ESC)  ,  FKEYS  ,  TGAMING  ,  TFKEYS
    ),
    [_GAMING] = LAYOUT(
        KC_GRV  ,  KC_1     , KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,                                                           KC_6  ,  KC_7     ,  KC_8     ,  KC_9     ,  KC_0   ,  KC_BSPC, 
        KC_TAB  ,  KC_LSFT  , KC_Q  ,  KC_W  ,  KC_E  ,  KC_R  ,                                                           KC_T  ,  KC_Y     ,  KC_UP    ,  KC_I     ,  KC_P   ,  KC_ENT, 
        KC_NO   ,  KC_LCTL  , KC_A  ,  KC_S  ,  KC_D  ,  KC_F  ,  KC_G  ,  KC_H    ,                      KC_J  ,  KC_K  , KC_L  ,  KC_LEFT  ,  KC_DOWN  ,  KC_RGHT  ,  KC_NO  ,  KC_ESC, 
                                       KC_Z  ,  KC_X  ,  KC_C  ,  KC_V  ,  KC_SPC  ,                      KC_B  ,  KC_N  , KC_M  ,  KC_TRNS  ,  KC_NO
    ),
    [_COLEMAK_DH] = LAYOUT(KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_BSPC, MT(MOD_LCTL, KC_ESC), KC_A, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, KC_O, MT(MOD_RCTL, KC_QUOTE), KC_LSFT, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_LBRC, KC_CAPS, MO(5), KC_RBRC, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_LGUI, MO(6), KC_LALT, KC_SPC, MO(3), MO(4), KC_SPC, KC_TRNS, KC_RGUI, KC_APP),
    [_NAV] = LAYOUT(
        KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  , KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,                                                              KC_INS   ,  KC_HOME  ,  KC_PGUP  ,  KC_PAUS  ,  KC_TRNS  ,  KC_LBRC, 
        KC_TRNS  ,  KC_LGUI  ,  KC_LALT  , KC_LCTL  ,  KC_LSFT  ,  KC_TRNS  ,                                                              KC_DEL   ,  KC_END   ,  KC_PGDN  ,  KC_SCRL  ,  KC_SCLN  ,  KC_QUOT, 
        KC_TRNS  ,  KC_TRNS  ,  KC_NUM   , KC_CAPS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_SCRL  ,              KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_MPRV  ,  KC_MPLY  ,  KC_MNXT  ,  KC_TRNS  ,  KC_PSCR,
                                           KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,              KC_TRNS  ,  KC_TRNS  ,  KC_MUTE  ,  KC_VOLD  ,  KC_VOLU
    ),
    [_SYM] = LAYOUT(
        KC_GRV   ,  KC_1        ,  KC_2        ,  KC_3        ,  KC_4        ,  KC_5,                                                                                                   KC_6        ,  KC_7        ,  KC_8        ,  KC_9        ,  KC_0     ,  KC_MINS, 
        KC_LSFT  ,  LSFT(KC_1)  ,  LSFT(KC_2)  ,  LSFT(KC_3)  ,  LSFT(KC_4)  ,  LSFT(KC_7)  ,                                                                                           LSFT(KC_8)  ,  LSFT(KC_9)  ,  KC_EQL      ,  KC_RBRC     ,  KC_NUHS  ,  LSFT(KC_NO), 
        KC_LSFT  ,  KC_NUBS     ,  RALT(KC_2)  ,  RALT(KC_3)  ,  RALT(KC_4)  ,  LSFT(KC_6)  ,  KC_TRNS  ,  KC_TRNS  ,                                           KC_TRNS  ,  KC_RCBR  ,  RALT(KC_7)  ,  RALT(KC_0)  ,  RALT(KC_8)  ,  RALT(KC_9)  ,  KC_SLSH  ,  KC_TRNS,  
                                                  KC_TRNS     ,  KC_TRNS     ,  KC_TRNS     ,  KC_TRNS  ,  KC_TRNS  ,                                           KC_TRNS  ,  KC_TRNS  ,  KC_TRNS     ,  KC_RALT     ,  KC_TRNS
    ),
    [_FUNCTION] = LAYOUT(
        KC_TRNS  ,  KC_F9  ,  KC_F10  ,  KC_F11   ,  KC_F12   ,  KC_TRNS  ,                                                                            KC_P7  ,  KC_P8    ,  KC_P9    ,  KC_PSLS  ,  KC_PAST  ,  KC_PMNS  ,  
        KC_TRNS  ,  KC_F5  ,  KC_F6   ,  KC_F7    ,  KC_F8    ,  KC_TRNS  ,                                                                            KC_P4  ,  KC_P5    ,  KC_P6    ,  KC_PPLS  ,  KC_PCMM  ,  KC_PEQL  ,  
        KC_TRNS  ,  KC_F1  ,  KC_F2   ,  KC_F3    ,  KC_F4    ,  KC_TRNS  ,  KC_TRNS  ,  KC_LALT  ,                            KC_LSFT  ,  KC_TRNS  ,  KC_P1  ,  KC_P2    ,  KC_P3    ,  KC_PENT  ,  KC_TRNS  ,  KC_RCTL  , 
                                         KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,                            KC_LCTL  ,  KC_TRNS  ,  KC_P0  ,  KC_TRNS  ,  KC_TRNS
    ),
    [_ADJUST] = LAYOUT(
        KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  DF(0)    ,  KC_TRNS  ,  KC_TRNS  ,                                                                            KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS   ,  KC_TRNS  ,  
        KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  DF(1)    ,  KC_TRNS  ,  KC_TRNS  ,                                                                            RGB_TOG  ,  RGB_SAI  ,  RGB_HUI  ,  RGB_VAI  ,  RGB_MOD   ,  KC_TRNS  , 
        KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  DF(2)    ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,                             KC_TRNS  , KC_TRNS  ,  KC_TRNS  ,  RGB_SAD  ,  RGB_HUD  ,  RGB_VAD  ,  RGB_RMOD  ,  KC_TRNS  , 
                                            KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,                             KC_TRNS  , KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS
    ),  
    [_SYM_ALT] = LAYOUT(
        KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_SCLN  ,  KC_TRNS  ,  KC_TRNS  ,                                                                              KC_TRNS        ,  KC_TRNS        ,  KC_TRNS       ,  KC_QUOT        ,  KC_TRNS             ,  KC_DEL  ,  
        KC_TRNS  ,  KC_LBRC  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,                                                                              RALT(KC_NUBS)  ,  LSFT(KC_NUHS)  ,  RALT(KC_EQL)  ,  RALT(KC_RBRC)  ,  KC_TRNS             ,  KC_TRNS  ,  
        KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,                              KC_TRNS  ,  KC_TRNS  ,  KC_NUBS        ,  LSFT(KC_NUBS)  ,  LSFT(KC_7)    ,  LSFT(KC_0)     ,  KC_NONUS_BACKSLASH  ,  KC_TRNS  ,  
                                            KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,  KC_TRNS  ,                              KC_TRNS  ,  KC_TRNS  ,  KC_TRNS        ,  KC_TRNS        ,  KC_TRNS
    )
};










void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  //debug_enable=true;
  //debug_matrix=false;
  //debug_keyboard=true;
  //debug_mouse=true;
}



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
            case _ADJUST:
                oled_write_P(PSTR("Adjust\n"), false);
                break;
            case _SYM_ALT:
                oled_write_P(PSTR("Sym Alt\n"), false);
                break;
            case _GAMING:
                oled_write_P(PSTR("Gamer TM\n"), false);
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

