// Copyright 2024 xeraph. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "screen.h"

void change_screen(struct game_state *state, enum game_screen screen) {
    screen_deinit(state);
    state->screen = screen;
    screen_init(state);
}

void screen_init(struct game_state *state) {
    switch (state->screen) {
    case SCREEN_EMPTY:
        break;
    case SCREEN_TITLE:
        screen_title_init(state);
        break;
    case SCREEN_GAMEPLAY:
        screen_gameplay_init(state);
        break;
    case SCREEN_ENDING:
        screen_ending_init(state);
        break;
    }
}
void screen_deinit(struct game_state *state) {
    switch (state->screen) {
    case SCREEN_EMPTY:
        break;
    case SCREEN_TITLE:
        screen_title_deinit(state);
        break;
    case SCREEN_GAMEPLAY:
        screen_gameplay_deinit(state);
        break;
    case SCREEN_ENDING:
        screen_ending_deinit(state);
        break;
    }
}
void screen_update(struct game_state *state) {
    switch (state->screen) {
    case SCREEN_EMPTY:
        break;
    case SCREEN_TITLE:
        screen_title_update(state);
        break;
    case SCREEN_GAMEPLAY:
        screen_gameplay_update(state);
        break;
    case SCREEN_ENDING:
        screen_ending_update(state);
        break;
    }
}
void screen_draw(struct game_state *const state) {
    switch (state->screen) {
    case SCREEN_EMPTY:
        break;
    case SCREEN_TITLE:
        screen_title_draw(state);
        break;
    case SCREEN_GAMEPLAY:
        screen_gameplay_draw(state);
        break;
    case SCREEN_ENDING:
        screen_ending_draw(state);
        break;
    }
}
