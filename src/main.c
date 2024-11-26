// Copyright 2024 xeraph. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <raylib.h>
#include <raymath.h>

#include <stdio.h>
#include <stdlib.h>

// MARK: defines

static const int   SCREEN_WIDTH  = 854;
static const int   SCREEN_HEIGHT = 480;
static const char *WINDOW_TITLE  = "PONG";
static const int   TARGET_FPS    = 60;

static const int SCORES_TO_WIN = 10;

static const float   PADDLE_OFFSET = 10;
static const float   PADDLE_WIDTH  = 10;
static const float   PADDLE_HEIGHT = 50;
static const float   BALL_RADIUS   = 5;
static const Vector2 BALL_SPEED    = {5, 3};

// MARK: structs

typedef struct {
    Vector2 center;
    Vector2 speed;
    float   radius;
} Ball;

typedef struct {
    Rectangle rec;
    float     speed;
    int       score;
    bool      win;
} Player;

// MARK: objects

static Ball   ball;
static Player player;
static Player rival;
static bool   paused;

// MARK: init

static void init_ball(void) {
    ball.center = (Vector2){(float)(GetScreenWidth()) / 2,
                            (float)(GetScreenHeight()) / 2};
    ball.speed  = BALL_SPEED;
    if (rand() % 2) ball.speed.x *= -1;
    if (rand() % 2) ball.speed.y *= -1;
    ball.radius = BALL_RADIUS;
}

static void init_player(void) {
    player.rec   = (Rectangle){PADDLE_OFFSET,
                               (float)(GetScreenHeight()) / 2 - PADDLE_HEIGHT / 2,
                               PADDLE_WIDTH, PADDLE_HEIGHT};
    player.speed = 5;
    player.score = 0;
    player.win   = false;
}

static void init_rival(void) {
    rival.rec =
        (Rectangle){(float)(GetScreenWidth())-PADDLE_WIDTH - PADDLE_OFFSET,
                    (float)(GetScreenHeight()) / 2 - PADDLE_HEIGHT / 2,
                    PADDLE_WIDTH, PADDLE_HEIGHT};
    rival.speed = 5;
    rival.score = 0;
    rival.win   = false;
}

static void init_game(void) {
    init_ball();
    init_player();
    init_rival();
    paused = true;
}

// MARK: ball update

static void move_ball(void) {
    ball.center = Vector2Add(ball.center, ball.speed);
}

static bool is_ball_colliding_top_screen(void) {
    return ball.center.y <= ball.radius;
}

static bool is_ball_colliding_bottom_screen(void) {
    return ball.center.y >= (float)(GetScreenHeight())-ball.radius;
}

static bool is_ball_colliding_left_screen(void) {
    return ball.center.x <= ball.radius;
}

static bool is_ball_colliding_right_screen(void) {
    return ball.center.x >= (float)(GetScreenWidth())-ball.radius;
}

static bool is_player_colliding_top_screen(Player p) {
    return p.rec.y <= PADDLE_OFFSET;
}

static bool is_player_colliding_bottom_screen(Player p) {
    return p.rec.y >= (float)(GetScreenHeight())-p.rec.height - PADDLE_OFFSET;
}

static void handle_ball_collision_with_screen(void) {
    if (is_ball_colliding_top_screen() || is_ball_colliding_bottom_screen()) {
        ball.speed.y *= -1;
    }
}

static void handle_ball_collision_with_player(void) {
    if (CheckCollisionCircleRec(ball.center, ball.radius, player.rec) ||
        CheckCollisionCircleRec(ball.center, ball.radius, rival.rec)) {
        ball.speed.x *= -1;
    }
}

static void update_ball(void) {
    move_ball();
    handle_ball_collision_with_screen();
    handle_ball_collision_with_player();
}

// MARK: player update

static void handle_player_input(void) {
    if (IsKeyDown(KEY_W)) player.rec.y -= player.speed;
    if (IsKeyDown(KEY_S)) player.rec.y += player.speed;
}

static void handle_rival_input(void) {
    if (IsKeyDown(KEY_UP)) rival.rec.y -= rival.speed;
    if (IsKeyDown(KEY_DOWN)) rival.rec.y += rival.speed;
}

static void handle_player_collision_with_screen(void) {
    if (is_player_colliding_top_screen(player)) player.rec.y = PADDLE_OFFSET;
    if (is_player_colliding_bottom_screen(player)) {
        player.rec.y =
            (float)(GetScreenHeight())-player.rec.height - PADDLE_OFFSET;
    }
}

static void handle_rival_collision_with_screen(void) {
    if (is_player_colliding_top_screen(rival)) rival.rec.y = PADDLE_OFFSET;
    if (is_player_colliding_bottom_screen(rival)) {
        rival.rec.y =
            (float)(GetScreenHeight())-rival.rec.height - PADDLE_OFFSET;
    }
}

static void update_player(void) {
    handle_player_input();
    handle_player_collision_with_screen();
}

static void update_rival(void) {
    handle_rival_input();
    handle_rival_collision_with_screen();
}

static void handle_player_score(void) {
    if (is_ball_colliding_left_screen()) rival.score++;
    if (player.score >= SCORES_TO_WIN) player.win = true;
}

static void handle_rival_score(void) {
    if (is_ball_colliding_right_screen()) player.score++;
    if (rival.score >= SCORES_TO_WIN) rival.win = true;
}

static void handle_reset_ball(void) {
    if (is_ball_colliding_left_screen() || is_ball_colliding_right_screen()) {
        init_ball();
    }
}

static void handle_user_input(void) {
    if (IsKeyPressed(KEY_SPACE)) paused = !paused;
    if (IsKeyPressed(KEY_R)) init_game();
}

static void update_game(void) {
    handle_user_input();
    if (paused) return;

    update_player();
    update_rival();

    update_ball();

    handle_player_score();
    handle_rival_score();

    handle_reset_ball();
}

// MARK: draw

static void draw_line(void) {
    const int x = GetScreenWidth() / 2;
    const int y = GetScreenHeight();
    DrawLine(x, 0, x, y, WHITE);
}

static void draw_score(int score, bool is_player) {
    const int font_size = 48;
    char      str[2];
    sprintf(str, "%d", score);
    int text_size = MeasureText(str, font_size);
    int x         = GetScreenWidth() / 4 - text_size / 2;
    if (!is_player) x += GetScreenWidth() / 2 + text_size;
    DrawText(str, x, 50, font_size, WHITE);
}

static void draw_player_score(void) { draw_score(player.score, true); }

static void draw_rival_score(void) { draw_score(rival.score, false); }

static void draw_ball(void) { DrawCircleV(ball.center, ball.radius, WHITE); }

static void draw_player(void) { DrawRectangleRec(player.rec, WHITE); }

static void draw_rival(void) { DrawRectangleRec(rival.rec, WHITE); }

static void draw_game(void) {
    draw_line();
    draw_player_score();
    draw_rival_score();

    draw_player();
    draw_rival();
    draw_ball();

    DrawFPS(10, 10);
}

// MARK: main

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(TARGET_FPS);
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    init_game();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        update_game();
        draw_game();

        EndDrawing();
    }

    CloseWindow();
    return EXIT_SUCCESS;
}
