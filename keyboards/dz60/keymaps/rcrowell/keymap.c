#include "dz60.h"

#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

/* void lshift_underscore_finished (qk_tap_dance_state_t *state, void *user_data) { */
/*   if (state->interrupted || !state->pressed) { */
/*     register_code(KC_LSHIFT); */
/*     register_code(KC_MINUS); */
/*   } else { */
/*     register_code(KC_LSHIFT); */
/*   } */
/* }; */

/* void lshift_underscore_reset (qk_tap_dance_state_t *state, void *user_data) { */
/*   if (state->interrupted || !state->pressed) { */
/*     unregister_code(KC_MINUS); */
/*     unregister_code(KC_LSHIFT); */
/*   } else { */
/*     unregister_code(KC_LSHIFT); */
/*   } */
/* }; */

/* enum { */
/*   TD_LSHIFT_UNDERSCORE = 0 */
/* }; */

/* qk_tap_dance_action_t tap_dance_actions[] = { */
/*   [TD_LSHIFT_UNDERSCORE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lshift_underscore_finished, lshift_underscore_reset) */
/* }; */

enum custom_keycodes {
  MY_LSHIFT = SAFE_RANGE,
  MY_LALT,
  MY_LGUI
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static bool user_lshift_interrupted = false;
  static bool user_lalt_interrupted = false;
  static bool user_lgui_interrupted = false;
  static uint16_t user_lshift_timer = 0;
  static uint16_t user_lalt_timer = 0;
  static uint16_t user_lgui_timer = 0;

  switch(keycode) {
    case MY_LSHIFT: {
      if (record->event.pressed) {
        user_lshift_interrupted = false;
        user_lshift_timer = timer_read();
        register_mods(MOD_BIT(KC_LSHIFT));
      } else {
        if (!user_lshift_interrupted && timer_elapsed(user_lshift_timer) < 200) {
          register_code(KC_MINUS);
          unregister_code(KC_MINUS);
        }
        unregister_mods(MOD_BIT(KC_LSHIFT));
      }
      return false;
    }

    case MY_LALT: {
      if (record->event.pressed) {
        user_lalt_interrupted = false;
        user_lalt_timer = timer_read();
        register_mods(MOD_BIT(KC_LALT));
      } else {
        unregister_mods(MOD_BIT(KC_LALT));
        if (!user_lalt_interrupted && timer_elapsed(user_lalt_timer) < 200) {
          register_code(KC_LSHIFT);
          register_code(KC_9);
          unregister_code(KC_9);
          unregister_code(KC_LSHIFT);
        }
      }
      return false;
    }

    case MY_LGUI: {
      if (record->event.pressed) {
        user_lgui_interrupted = false;
        user_lgui_timer = timer_read();
        register_mods(MOD_BIT(KC_LGUI));
      } else {
        unregister_mods(MOD_BIT(KC_LGUI));
        if (!user_lgui_interrupted && timer_elapsed(user_lgui_timer) < 200) {
          register_code(KC_LSHIFT);
          register_code(KC_0);
          unregister_code(KC_0);
          unregister_code(KC_LSHIFT);
        }
      }
      return false;
    }

    default: {
      user_lshift_interrupted = true;
      user_lalt_interrupted = true;
      user_lgui_interrupted = true;
      return true;
    }
  }
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	KEYMAP(
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLASH, KC_ESC,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSPACE,
		KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
		MY_LSHIFT, KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_UP, KC_NO,
		MO(1), MY_LALT, MY_LGUI, KC_SPC, KC_SPC, KC_SPC, KC_RGUI, KC_RSPC, KC_LEFT, KC_DOWN, KC_RIGHT),
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
