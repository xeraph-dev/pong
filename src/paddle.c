// Copyright 2024 xeraph. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "paddle.h"
#include "assert.h"
#include <math.h>
#include <raylib.h>

static const Vector2 PADDLE_SIZE   = {10, 50};
static const Color   PADDLE_COLOR  = WHITE;
static const float   PADDLE_OFFSET = 10;
static const float   PADDLE_SPEED  = 300;

struct paddle make_paddle(enum paddle_position position) {
    struct paddle paddle = {0};
    paddle_init(&paddle, position);
    return paddle;
}

void paddle_init(struct paddle *paddle, enum paddle_position position) {
    assert(paddle);

    paddle->rec.width  = PADDLE_SIZE.x;
    paddle->rec.height = PADDLE_SIZE.y;
    paddle->rec.y      = (float)(GetScreenHeight()) / 2 - PADDLE_SIZE.y / 2;
    switch (position) {
    case PADDLE_LEFT:
        paddle->rec.x = PADDLE_OFFSET;
        break;
    case PADDLE_RIGHT:
        paddle->rec.x = (float)(GetScreenWidth())-PADDLE_SIZE.x - PADDLE_OFFSET;
        break;
    }

    paddle->color = PADDLE_COLOR;
    paddle->speed = PADDLE_SPEED;
}

void paddle_update(struct paddle *const paddle) { assert(paddle); }

void paddle_draw(struct paddle *const paddle) {
    assert(paddle);

    DrawRectangleRec(paddle->rec, paddle->color);
}

void paddle_move_up(struct paddle *paddle) {
    assert(paddle);

    paddle->rec.y = fmaxf(paddle->rec.y - paddle->speed * GetFrameTime(), 0);
}

void paddle_move_down(struct paddle *paddle) {
    assert(paddle);

    paddle->rec.y = fminf(paddle->rec.y + paddle->speed * GetFrameTime(),
                          (float)(GetScreenHeight())-paddle->rec.height);
}
