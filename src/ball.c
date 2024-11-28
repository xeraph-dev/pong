// Copyright 2024 xeraph. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "ball.h"
#include <assert.h>

static const float BALL_RADIUS = 5;
static const Color BALL_COLOR  = WHITE;

struct ball make_ball(void) {
    struct ball ball = {0};
    ball_init(&ball);
    return ball;
}

void ball_init(struct ball *ball) {
    assert(ball);

    ball->center.x = (float)(GetScreenWidth()) / 2;
    ball->center.y = (float)(GetScreenHeight()) / 2;
    ball->radius   = BALL_RADIUS;
    ball->color    = BALL_COLOR;
}

void ball_update(struct ball *ball) { assert(ball); }

void ball_draw(struct ball *const ball) {
    assert(ball);

    DrawCircleV(ball->center, ball->radius, ball->color);
}
