// Copyright 2024 xeraph. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "paddle.h"
#include <raylib.h>

static const Vector2 PADDLE_OFFSET = {10, 5};
static const Vector2 PADDLE_SIZE   = {10, 50};
static const Color   PADDLE_COLOR  = WHITE;

struct paddle make_paddle(enum paddle_position position) {
    struct paddle paddle = {0};
    paddle_init(&paddle, position);
    return paddle;
}

void paddle_init(struct paddle *paddle, enum paddle_position position) {
    paddle->rec.width  = PADDLE_SIZE.x;
    paddle->rec.height = PADDLE_SIZE.y;
    paddle->rec.y      = (float)(GetScreenHeight()) / 2 - PADDLE_SIZE.y / 2;
    switch (position) {
    case PADDLE_LEFT:
        paddle->rec.x = PADDLE_OFFSET.x;
        break;
    case PADDLE_RIGHT:
        paddle->rec.x =
            (float)(GetScreenWidth())-PADDLE_SIZE.x - PADDLE_OFFSET.x;
        break;
    }

    paddle->color = PADDLE_COLOR;
}

void paddle_update(struct paddle *const _) {}

void paddle_draw(struct paddle *const paddle) {
    DrawRectangleRec(paddle->rec, paddle->color);
}
