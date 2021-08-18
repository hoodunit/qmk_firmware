#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _QWERTY_SHIFT 1
#define _COLEMAK 2
#define _COLEMAK_SHIFT 3
#define _SYMB 4
#define _NAV 5

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  QWERTY_SHIFT,
  COLEMAK,
  COLEMAK_SHIFT,
  SYMB,
  NAV,
  ESC_ALL,
  BS_DEL
};

#define SYM_L   MO(_SYMB)
#define KC_ALAS LALT_T(KC_PAST)
#define KC_CTPL LCTL_T(KC_PSLS)
#define KC_NAGR LT(_NAV, KC_GRV)
#define KC_NAMI LT(_NAV, KC_MINS)

// Shifted keys
#define S_ENT S(KC_ENT)
#define S_SPC S(KC_SPC)
#define S_TAB S(KC_TAB)

// Finnish characters
//#define AE      UC(0x00e4) // ä
//#define AE_U    UC(0x00c4) // Ä
//#define OO      UC(0x00f6) // ö
//#define OO_U    UC(0x00d6) // Ö
//#define RUO_O   UC(0x00e5) // å
//#define RUO_O_U UC(0x00c5) // Å

// Change default layer to Colemak
#define TO_COLE DF(_COLEMAK)
// Change default layer to QWERTY
#define TO_QWER DF(_QWERTY)

#define CLR_QWER TO(_QWERTY)
#define CLR_COLE TO(_COLEMAK)

// One-shot layers
//#define SHIFT OSL(_QWERTY_SHIFT)
#define SHIFT OSM(MOD_LSFT)
#define SHFT_COL OSL(_COLEMAK_SHIFT)
#define TAP_LALT OSM(MOD_LALT)
#define TAP_LCTL OSM(MOD_LCTL)
#define TAP_RALT OSM(MOD_RALT)
#define TAP_RCTL OSM(MOD_RCTL)
#define TAP_WIN OSM(MOD_LGUI)
#define TAP_SYM OSL(_SYMB)
#define TAP_NAV TT(_NAV)
#define SPC_NAV LT(_NAV, KC_SPC)
#define S_SPC_NV LT(_NAV, S(KC_SPC))

#define CTRL_ESC MT(MOD_LCTL, KC_ESC)
#define CTL_TAB LCTL(KC_TAB)
#define CTLS_TAB LCTL(LSFT(KC_TAB))
// Trigger Xmonad to map Super_L key to Hyper_L
#define RST_HYP LCTL(LSFT(LALT(KC_K)))

// Set Unicode input mode to Linux
void eeconfig_init_user(void) {
  set_unicode_input_mode(UC_LNX);
}

static bool bsdel_mods = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ESC_ALL:
      if (record->event.pressed) {
        clear_keyboard();
        clear_oneshot_mods();
        layer_off(_QWERTY_SHIFT);
        layer_off(_COLEMAK_SHIFT);
        layer_off(_SYMB);
        layer_off(_NAV);
      } else {
        // release
      }
      break;
    case BS_DEL:
       if (record->event.pressed) {
         uint8_t shift_is_held = (keyboard_report->mods & (MOD_BIT(KC_LSFT)) );
         uint8_t kc = shift_is_held ? KC_DEL : KC_BSPC;
         if (shift_is_held) {
           unregister_code(KC_LSFT);
         }
         register_code(kc);
         if (shift_is_held) {
           register_code(KC_LSFT);
         }
         bsdel_mods = shift_is_held;
       } else {
         uint8_t kc = bsdel_mods ? KC_DEL : KC_BSPC;
         unregister_code(kc);
       }
      break;
  }
  return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_DEL  ,KC_INS  ,KC_PSCR ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                            KC_5    ,KC_4    ,KC_3    ,KC_2    ,KC_1    ,ESC_ALL  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_BSLS ,KC_P    ,KC_O    ,KC_I    ,KC_U    ,KC_Y    ,KC_MNXT ,                          KC_VOLU ,KC_T    ,KC_R    ,KC_E    ,KC_W    ,KC_Q    ,KC_TAB  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_QUOT ,TAP_SYM ,KC_L    ,KC_K    ,KC_J    ,KC_H    ,KC_MPRV ,                          KC_VOLD ,KC_G    ,KC_F    ,KC_D    ,KC_S    ,KC_A    ,CTRL_ESC,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     SHIFT   ,KC_SLSH ,KC_DOT  ,KC_COMM ,KC_M    ,KC_N    ,KC_MPLY ,RST_HYP ,        XXXXXXX ,KC_MUTE ,KC_B    ,KC_V    ,KC_C    ,KC_X    ,KC_Z    ,SHIFT   ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_BRIU ,KC_BRID ,KC_ALGR ,KC_SCLN ,     TAP_RCTL,    KC_SPC  ,KC_ENT  ,        TAP_NAV ,BS_DEL  ,    TAP_WIN ,     TAP_WIN ,TAP_LALT ,XXXXXXX ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_SYMB] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F11  ,KC_F10  ,KC_F9   ,KC_F8   ,KC_F7   ,KC_F6   ,                                            KC_F5   ,KC_F4   ,KC_F3   ,KC_F2   ,KC_F1   ,ESC_ALL ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_F12  ,KC_AMPR ,KC_PLUS ,KC_RCBR ,KC_LCBR ,KC_TILD ,XXXXXXX ,                          XXXXXXX ,KC_PERC ,KC_9    ,KC_8    ,KC_7    ,KC_GRV  ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,KC_UNDS ,KC_MINS ,KC_RPRN ,KC_LPRN ,KC_ASTR ,XXXXXXX ,                          XXXXXXX ,KC_DLR  ,KC_6    ,KC_5    ,KC_4    ,KC_0    ,ESC_ALL ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_RSFT ,KC_AT   ,KC_EQUAL,KC_RBRC ,KC_LBRC ,KC_CIRC ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,KC_HASH ,KC_3    ,KC_2    ,KC_1    ,KC_DOT  ,KC_LSFT ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,_______ ,_______ ,KC_EXLM ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX ,XXXXXXX ,RGB_VAI ,RGB_SAI ,RGB_HUI ,RGB_MOD ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,RGB_VAD ,RGB_SAD ,RGB_HUD ,RGB_RMOD,RGB_TOG ,                          XXXXXXX ,XXXXXXX ,CTL_TAB ,CTLS_TAB,XXXXXXX ,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,KC_RIGHT,KC_UP   ,KC_DOWN ,KC_LEFT ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,KC_RGHT ,KC_UP   ,KC_DOWN ,KC_LEFT ,ESC_ALL ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_RSFT ,XXXXXXX ,KC_MS_R ,KC_MS_U ,KC_MS_D ,KC_MS_L ,KC_BTN1 ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_END  ,KC_PGUP ,KC_PGDN ,KC_HOME ,KC_LSFT ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_COLEMAK] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     ESC_ALL ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,TO_QWER  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,KC_Q    ,KC_W    ,KC_F    ,KC_P    ,KC_B    ,KC_VOLU ,                          KC_MNXT ,KC_J    ,KC_L    ,KC_U    ,KC_Y    ,KC_SCLN ,KC_BSLS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     CTRL_ESC,KC_A    ,KC_R    ,KC_S    ,KC_T    ,KC_G    ,KC_VOLD ,                          KC_MPRV ,KC_K    ,KC_N    ,KC_E    ,KC_I    ,KC_O    ,KC_QUOT ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     SHIFT   ,KC_Z    ,KC_X    ,KC_C    ,KC_D    ,KC_V    ,KC_MUTE ,XXXXXXX ,        XXXXXXX ,KC_MPLY ,KC_M    ,KC_H    ,KC_COMM ,KC_DOT  ,KC_SLSH ,SHIFT   ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,TAP_LALT,     TAP_WIN ,    KC_BSPC ,TAP_NAV ,        KC_ENT  ,KC_SPC  ,    TAP_RCTL,     TAP_SYM ,XXXXXXX ,KC_BRID ,KC_BRIU
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  )

//  [_QWERTY_SHIFT] = LAYOUT(
//  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
//     ESC_ALL ,S(KC_1) ,S(KC_2) ,S(KC_3) ,S(KC_4) ,S(KC_5) ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
//  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
//     S_TAB   ,S(KC_Q) ,S(KC_W) ,S(KC_E) ,S(KC_R) ,S(KC_T) ,XXXXXXX ,                          XXXXXXX ,S(KC_Y) ,S(KC_U) ,S(KC_I) ,S(KC_O) ,S(KC_P) ,KC_PIPE ,
//  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
//     ESC_ALL ,S(KC_A) ,S(KC_S) ,S(KC_D) ,S(KC_F) ,S(KC_G) ,XXXXXXX ,                          XXXXXXX ,S(KC_H) ,S(KC_J) ,S(KC_K) ,S(KC_L) ,_______ ,KC_DQUO,
//  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
//     _______ ,S(KC_Z) ,S(KC_X) ,S(KC_C) ,S(KC_V) ,S(KC_B) ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,S(KC_N) ,S(KC_M) ,KC_LT   ,KC_GT   ,KC_QUES, _______ ,
//  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
//     XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,     _______ ,    KC_DEL  ,_______ ,        S_ENT   ,S_SPC   ,    _______ ,     KC_COLN ,_______ ,_______ ,_______
//  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
//  ),

//  [_COLEMAK_SHIFT] = LAYOUT(
//  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
//     ESC_ALL ,S(KC_1) ,S(KC_2) ,S(KC_3) ,S(KC_4) ,S(KC_5) ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
//  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
//     _______ ,S(KC_Q) ,S(KC_W) ,S(KC_F) ,S(KC_P) ,S(KC_B) ,XXXXXXX ,                          XXXXXXX ,S(KC_Y) ,S(KC_U) ,S(KC_I) ,S(KC_O) ,KC_COLN ,KC_PIPE ,
//  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
//     ESC_ALL ,S(KC_A) ,S(KC_R) ,S(KC_S) ,S(KC_T) ,S(KC_G) ,XXXXXXX ,                          XXXXXXX ,S(KC_K) ,S(KC_N) ,S(KC_E) ,S(KC_I) ,S(KC_O) ,KC_DQUO,
//  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
//     _______ ,S(KC_Z) ,S(KC_X) ,S(KC_C) ,S(KC_D) ,S(KC_V) ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,S(KC_M) ,S(KC_H) ,KC_LT   ,KC_GT   ,KC_QUES ,_______ ,


//     _______ ,_______ ,_______ ,_______ ,     _______ ,    KC_DEL  ,_______ ,        S_ENT   ,S_SPC   ,    _______ ,     _______ ,_______ ,_______ ,_______
//  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
//  ),

//  [_NAV] = LAYOUT(
//  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
//     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
//  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
//     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
//  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
//     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
//  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
//     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
//  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
//     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
//  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
//  )

};
