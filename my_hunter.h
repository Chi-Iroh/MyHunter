/*
** EPITECH PROJECT, 2022
** my_hunter.h
** File description:
** -> protos and struct for drawing
*/

#pragma once

#include <SFML/Graphics.h>
#include <SFML/Audio.h>

#define DESTROY_IF_ALLOCATED(destroyer, var) { if (var) {   \
    (destroyer)(var);                                       \
} }

#define TEXTURE_RECT(animation) (sfIntRect) {   \
    110 * (animation), 0, 110, 110              \
}

#define TEST_DRAWABLE_ALLOC(alloc_expr) { if (!(alloc_expr)) {  \
    destroy_drawable(draw); return NULL;                        \
} }

typedef struct ducks_struct {
    sfSprite *duck;
    struct ducks_struct *next;
} ducks_t;

typedef struct {
    sfTexture *back_tx;
    sfTexture *duck_tx;
    sfSprite *back;
    ducks_t *ducks;
    sfMusic *bgm;
} drawable_t;

void draw_window(sfRenderWindow *window, drawable_t *draw);

void spawn_duck_at(drawable_t *draw, float x, float y);
