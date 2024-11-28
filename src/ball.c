// Copyright 2024 xeraph. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "ball.h"
#include "paddle.h"
#include <assert.h>
#include <raymath.h>
#include <stdlib.h>

static const float   BALL_RADIUS = 5;
static const Color   BALL_COLOR  = WHITE;
static const Vector2 BALL_SPEED  = {400, 300};

static void ball_move(struct ball *ball) {
    assert(ball);

    float   dt    = GetFrameTime();
    Vector2 speed = Vector2Multiply(ball->speed, (Vector2){dt, dt});
    ball->center  = Vector2Add(ball->center, speed);
}

static void ball_handle_collisions(struct ball *ball, struct paddle *player,
                                   struct paddle *rival) {
    assert(ball);
    assert(player);
    assert(rival);

    bool is_colliding_top = ball->center.y <= ball->radius;
    bool is_colliding_bottom =
        ball->center.y + ball->radius >= (float)(GetScreenHeight());
    bool is_colliding_left = ball->center.x <= ball->radius;
    bool is_colliding_right =
        ball->center.x + ball->radius >= (float)(GetScreenWidth());

    if (is_colliding_top || is_colliding_bottom) ball->speed.y *= -1;
    if (is_colliding_left) paddle_score_up(rival);
    if (is_colliding_right) paddle_score_up(player);

    bool is_colliding_player =
        CheckCollisionCircleRec(ball->center, ball->radius, player->rec);
    bool is_colliding_rival =
        CheckCollisionCircleRec(ball->center, ball->radius, rival->rec);
    if (is_colliding_player || is_colliding_rival) {
        ball->speed.x *= -1;
    }

    if (is_colliding_left || is_colliding_right) ball_init(ball);
}

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
    ball->speed    = BALL_SPEED;
    if (rand() % 2) ball->speed.x *= -1;
    if (rand() % 2) ball->speed.y *= -1;
}

void ball_update(struct ball *ball, struct paddle *player,
                 struct paddle *rival) {
    assert(ball);
    assert(player);
    assert(rival);

    ball_move(ball);
    ball_handle_collisions(ball, player, rival);
}

void ball_draw(struct ball *const ball) {
    assert(ball);

    DrawCircleV(ball->center, ball->radius, ball->color);
}
