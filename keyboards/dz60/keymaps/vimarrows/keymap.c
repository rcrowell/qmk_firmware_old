#include "dz60.h"

#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

// custom keycodes
enum custom_keycodes {
  MY_LSHIFT_LBRACE = SAFE_RANGE,
  MY_RSHIFT_RBRACE
};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static bool lshift_lbrace_interrupted = false;
  static bool rshift_rbrace_interrupted = false;
  static uint16_t lshift_lbrace_timer = 0;
  static uint16_t rshift_rbrace_timer = 0;
  switch(keycode) {
    case MY_LSHIFT_LBRACE:
      if (record->event.pressed) {
        lshift_lbrace_interrupted = false;
        lshift_lbrace_timer = timer_read();
        register_mods(MOD_BIT(KC_LSHIFT));
      } else {
        if (!lshift_lbrace_interrupted && timer_elapsed(lshift_lbrace_timer) < 200) {
          register_code(KC_LBRACKET);
          unregister_code(KC_LBRACKET);
        }
        unregister_mods(MOD_BIT(KC_LSHIFT));
      }
      return false;
    case MY_RSHIFT_RBRACE:
      if (record->event.pressed) {
        rshift_rbrace_interrupted = false;
        rshift_rbrace_timer = timer_read();
        register_mods(MOD_BIT(KC_RSHIFT));
      } else {
        if (!rshift_rbrace_interrupted && timer_elapsed(rshift_rbrace_timer) < 200) {
          register_code(KC_RBRACKET);
          unregister_code(KC_RBRACKET);
        }
        unregister_mods(MOD_BIT(KC_RSHIFT));
      }
      return false;
  }
  // default:
  lshift_lbrace_interrupted = true;
  rshift_rbrace_interrupted = true;
  return true;
};

// tapdances
void dance_esc_forcequit_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_ESC);
  } else {
    register_code(KC_LALT);
    register_code(KC_LGUI);
    register_code(KC_ESC);
  }
};
void dance_esc_forcequit_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code(KC_ESC);
  } else {
    unregister_code(KC_LALT);
    unregister_code(KC_LGUI);
    unregister_code(KC_ESC);
  }
}
enum {
  TD_ESC_FORCEQUIT = 0
};
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ESC_FORCEQUIT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_esc_forcequit_finished, dance_esc_forcequit_reset)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // standard layer
  KEYMAP(
         KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLASH, TD(TD_ESC_FORCEQUIT),
         KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSPACE,
         KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
         KC_LSPO, KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC, KC_NO,
         MO(1), KC_LALT, KC_LGUI, KC_SPC, KC_SPC, KC_SPC, KC_RGUI, KC_UP, KC_LEFT, KC_DOWN, KC_RIGHT),
  // standard fn layer
  KEYMAP(
         RESET, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP,
         KC_TRNS, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DELETE,
         KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MEDIA_PLAY_PAUSE,
         MY_LSHIFT_LBRACE, KC_TRNS, KC_TRNS, KC_TRNS, BL_DEC, BL_TOGG, BL_INC, BL_STEP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MY_RSHIFT_RBRACE, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TG(2), KC_PGUP, KC_MEDIA_PREV_TRACK, KC_PGDOWN, KC_MEDIA_NEXT_TRACK),
  // wasd layer
  KEYMAP(
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};
