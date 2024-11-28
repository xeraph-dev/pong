// Copyright 2024 xeraph. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include <raylib.h>

struct ball {
    Vector2 center;
    float   radius;
    Color   color;
};

struct ball make_ball(void);
void        ball_init(struct ball *ball);
void        ball_update(struct ball *ball);
void        ball_draw(struct ball *const ball);
