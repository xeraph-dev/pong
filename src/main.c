// Copyright 2024 xeraph. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "game.h"

int main(void) {
    struct game_state game = make_game();
    game_run(&game);
}
