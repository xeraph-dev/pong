// Copyright 2024 xeraph. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "game.h"
#include "screen.h"
#include <raylib.h>

static const int   SCREEN_WIDTH  = 854;
static const int   SCREEN_HEIGHT = 480;
static const char *WINDOW_TITLE  = "PONG";
static const int   TARGET_FPS    = 60;

static void game_init(struct game_state *state) {
    state->screen = SCREEN_EMPTY;
    change_screen(state, SCREEN_GAMEPLAY);
}

static void game_update(struct game_state *state) { screen_update(state); }

static void game_draw(struct game_state *const state) {
    screen_draw(state);

    DrawFPS(10, 10);
}

struct game_state make_game(void) {
    struct game_state state = {0};

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(TARGET_FPS);
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    game_init(&state);
    return state;
}

void game_run(struct game_state *state) {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        game_update(state);
        game_draw(state);

        EndDrawing();
    }
}
