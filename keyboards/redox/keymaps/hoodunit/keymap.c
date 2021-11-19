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
#define _GAMING_FPS 6
#define _GAMING_SC2_CORE 7
#define _GAMING_SC2_CORE_V6 8
#define _GAMING_DOTA 9
#define _GAMING_NAV 10

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
#define TO_GAME DF(_GAMING_FPS)
#define TO_SC2 DF(_GAMING_SC2_CORE_V6)
#define TO_DOTA DF(_GAMING_DOTA)

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
#define TAP_GNV TT(_GAMING_NAV)
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
     ESC_ALL ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            XXXXXXX ,TO_SC2  ,TO_GAME ,KC_PSCR ,KC_INS  ,KC_DEL  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_VOLU ,                          KC_MNXT ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_BSLS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     CTRL_ESC,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,KC_VOLD ,                          KC_MPRV ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,TAP_SYM ,KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     SHIFT   ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_MUTE ,TAP_NAV ,        RST_HYP ,KC_MPLY ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,SHIFT   ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     TAP_RALT,XXXXXXX ,KC_ALGR ,TAP_LALT,     TAP_WIN ,    BS_DEL  ,TAP_WIN ,        KC_ENT  ,KC_SPC  ,    TAP_RCTL,     KC_SCLN ,KC_ALGR ,KC_BRID ,KC_BRIU //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_SYMB] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     ESC_ALL ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11 ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_GRV  ,KC_7    ,KC_8    ,KC_9    ,KC_PERC ,XXXXXXX ,                          XXXXXXX ,KC_TILD ,KC_LCBR ,KC_RCBR ,KC_PLUS ,KC_AMPR ,KC_F12 ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     ESC_ALL ,KC_0    ,KC_4    ,KC_5    ,KC_6    ,KC_DLR  ,XXXXXXX ,                          XXXXXXX ,KC_ASTR ,KC_LPRN ,KC_RPRN ,KC_MINS ,KC_UNDS ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT ,KC_DOT  ,KC_1    ,KC_2    ,KC_3    ,KC_HASH ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,KC_CIRC ,KC_LBRC ,KC_RBRC ,KC_EQUAL,KC_AT   ,KC_RSFT ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     KC_EXLM ,_______ ,_______ ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     ESC_ALL ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,CTLS_TAB,CTL_TAB ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     ESC_ALL ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT ,XXXXXXX , XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT ,KC_HOME ,KC_PGDN ,KC_PGUP ,KC_END  ,XXXXXXX ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,KC_BTN1 ,KC_MS_L ,KC_MS_D ,KC_MS_U ,KC_MS_R ,XXXXXXX ,KC_RSFT ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,KC_SPC  ,    _______ ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_GAMING_DOTA] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     ESC_ALL ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            XXXXXXX ,TO_SC2  ,TO_GAME ,KC_PSCR ,KC_INS  ,KC_DEL  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_VOLU ,                          KC_MNXT ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_BSLS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,KC_VOLD ,                          KC_MPRV ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,TAP_SYM ,KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     SHIFT   ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_MUTE ,TAP_GNV ,        RST_HYP ,KC_MPLY ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,SHIFT   ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     TAP_RALT,XXXXXXX ,KC_ALGR ,TAP_LALT,     TAP_WIN ,    BS_DEL  ,TAP_WIN ,        KC_ENT  ,KC_SPC  ,    TAP_RCTL,     KC_SCLN ,KC_ALGR ,KC_BRID ,KC_BRIU //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_GAMING_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     ESC_ALL ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,CTLS_TAB,CTL_TAB ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     ESC_ALL ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT ,XXXXXXX , XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT ,KC_HOME ,KC_PGDN ,KC_PGUP ,KC_END  ,XXXXXXX ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,KC_BTN1 ,KC_MS_L ,KC_MS_D ,KC_MS_U ,KC_MS_R ,XXXXXXX ,KC_RSFT ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,KC_SPC  ,    _______ ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),
//
//  [_GAMING_FPS] = LAYOUT(
//  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
//     KC_NAGR ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            TO_QWER ,XXXXXXX ,XXXXXXX ,KC_9    ,KC_0    ,KC_NAMI ,
//  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
//     KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,SYM_L   ,                          SYM_L   ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_EQL  ,
//  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
//     KC_ESC  ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,KC_LBRC ,                          KC_RBRC ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
//  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
//     KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,XXXXXXX ,KC_PGDN ,        RST_HYP ,XXXXXXX ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSFT ,
//  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
//     KC_LGUI ,KC_PPLS ,KC_PMNS ,KC_ALAS ,     KC_CTPL ,    KC_SPC  ,KC_DEL  ,        KC_ENT  ,KC_SPC  ,    KC_RALT ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
//  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
//  ),
//
//  [_GAMING_SC2_CORE] = LAYOUT(
//  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
//     ESC_ALL ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,XXXXXXX ,                                            TO_QWER ,XXXXXXX ,XXXXXXX ,KC_9    ,KC_0    ,KC_NAMI ,
//  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
//     KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_MINS ,KC_EQUAL,XXXXXXX ,                          SYM_L   ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_EQL  ,
//  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
//     KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_P    ,KC_LBRC ,KC_RBRC ,                          KC_RBRC ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
//  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
//     KC_B    ,KC_N    ,KC_M    ,KC_DOT  ,KC_SCLN ,KC_QUOTE,XXXXXXX , XXXXXXX ,        RST_HYP ,XXXXXXX ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSFT ,
//  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
//     TO_QWER ,XXXXXXX ,XXXXXXX ,KC_SLSH ,     KC_RALT ,    KC_LSFT  ,KC_RCTL  ,        KC_ENT  ,KC_SPC  ,    KC_RALT ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
//  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
//  ), // Missing: G
//
//  [_GAMING_SC2_CORE_V6] = LAYOUT(
//  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
//     KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_MINS ,                                            TO_QWER ,XXXXXXX ,XXXXXXX ,KC_9    ,KC_0    ,KC_NAMI ,
//  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
//     KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_LBRC ,KC_EQUAL,                          SYM_L   ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_EQL  ,
//  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
//     KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOTE,KC_RBRC ,                          KC_RBRC ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
//  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
//     KC_N    ,KC_M    ,KC_COMMA,KC_DOT  ,KC_BSLS ,KC_BSPC ,XXXXXXX , TO_QWER ,        RST_HYP ,XXXXXXX ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSFT ,
//  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
//     KC_G    ,KC_B    ,XXXXXXX ,KC_SLSH ,     KC_LALT ,    KC_RCTL  ,KC_RSFT  ,        KC_ENT  ,KC_SPC  ,    KC_RALT ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
//  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
//  ),

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

};
