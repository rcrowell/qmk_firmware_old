#include "dz60.h"

#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

/* //Tap Dance Definitions */
/* enum { */
/*   TD_SHIFT_PARENS = 0 */
/* }; */

/* qk_tap_dance_action_t tap_dance_actions[] = { */
/*   [TD_SHIFT_PARENS]  = ACTION_TAP_DANCE_DOUBLE(KC_LEFT_PAREN, KC_RIGHT_PAREN) */
/* }; */

void lshift_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1 && !state->pressed) {
    register_code(KC_LSHIFT);
    register_code(KC_9);
  } else if (state->count == 2) {
    register_code(KC_LSHIFT);
    register_code(KC_0);
  } else {
    register_code(KC_LSHIFT);
  }
};

void lshift_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1 && !state->pressed) {
    unregister_code(KC_9);
    unregister_code(KC_LSHIFT);
  } else if (state->count == 2) {
    unregister_code(KC_0);
    unregister_code(KC_LSHIFT);
  } else {
    unregister_code(KC_LSHIFT);
  }
};

enum {
  TD_LSHIFT = 0
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_LSHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lshift_finished, lshift_reset)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	KEYMAP(
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLASH, KC_ESC,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSPACE,
		KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
		TD(TD_LSHIFT), KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_UP, KC_NO,
		MO(1), KC_LALT, KC_LGUI, KC_SPC, KC_SPC, KC_SPC, KC_RGUI, KC_RSHIFT, KC_LEFT, KC_DOWN, KC_RIGHT),
	KEYMAP(
		RESET, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP,
		KC_TRNS, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DELETE,
		KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, BL_DEC, BL_TOGG, BL_INC, BL_STEP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_PLAY_PAUSE, KC_TRNS, RESET, KC_MEDIA_PREV_TRACK, KC_PGDOWN, KC_MEDIA_NEXT_TRACK),

	KEYMAP(
		KC_TRNS, M(1), M(2), M(3), M(4), M(5), M(6), M(7), M(8), M(9), M(10), M(11), M(12), KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};

/* enum function_id { */
/*     SHIFT_ESC, */
/* }; */

/* const uint16_t PROGMEM fn_actions[] = { */
/*   [0]  = ACTION_FUNCTION(SHIFT_ESC), */
/* }; */

/* void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) { */
/*   static uint8_t shift_esc_shift_mask; */
/*   switch (id) { */
/*     case SHIFT_ESC: */
/*       shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK; */
/*       if (record->event.pressed) { */
/*         if (shift_esc_shift_mask) { */
/*           add_key(KC_GRV); */
/*           send_keyboard_report(); */
/*         } else { */
/*           add_key(KC_ESC); */
/*           send_keyboard_report(); */
/*         } */
/*       } else { */
/*         if (shift_esc_shift_mask) { */
/*           del_key(KC_GRV); */
/*           send_keyboard_report(); */
/*         } else { */
/*           del_key(KC_ESC); */
/*           send_keyboard_report(); */
/*         } */
/*       } */
/*       break; */
/*   } */
/* } */
