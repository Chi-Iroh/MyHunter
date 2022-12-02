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

#define TEST_OBJ_ALLOC(alloc_expr) { if (!(alloc_expr)) {  \
    destroy_objects(obj); return NULL;                     \
} }

#define LOAD_DEATHS() {                                 \
char name[11] = "death0.ogg";                            \
for (size_t i = 0; i < 10; i++) {                       \
    name[5] = '0' + i;                                  \
    obj->deaths[i] = sfMusic_createFromFile(&name[0]);  \
    TEST_OBJ_ALLOC(obj->deaths[i])                      \
}}

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
    sfMusic *deaths[10];
    int death;
} objects_t;

void draw_window(sfRenderWindow *window, objects_t *obj);

void spawn_duck_at(objects_t *obj, float x, float y);

void handle_event(sfRenderWindow *window, objects_t *obj);

void destroy_objects(objects_t *obj);

objects_t *init_objects(int argc, char *argv[]);

extern const char *const help_msg;

extern const char *const credits_msg;
