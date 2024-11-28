// Copyright 2024 xeraph. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "../screen.h"
#include <assert.h>

void screen_gameplay_init(struct game_state *state) {
    assert(state);

    state->player = make_paddle(PADDLE_LEFT);
    state->rival  = make_paddle(PADDLE_RIGHT);
    state->ball   = make_ball();
}

void screen_gameplay_deinit(struct game_state *state) {
    assert(state);

    state->player = (struct paddle){0};
    state->rival  = (struct paddle){0};
    state->ball   = (struct ball){0};
}

void screen_gameplay_input(struct game_state *state) {
    assert(state);

    if (IsKeyDown(KEY_W)) paddle_move_up(&state->player);
    if (IsKeyDown(KEY_S)) paddle_move_down(&state->player);
    if (IsKeyDown(KEY_UP)) paddle_move_up(&state->rival);
    if (IsKeyDown(KEY_DOWN)) paddle_move_down(&state->rival);
}

void screen_gameplay_update(struct game_state *state) {
    assert(state);

    paddle_update(&state->player);
    paddle_update(&state->rival);
    ball_update(&state->ball);
}

void screen_gameplay_draw(struct game_state *const state) {
    assert(state);

    paddle_draw(&state->player);
    paddle_draw(&state->rival);
    ball_draw(&state->ball);
}
