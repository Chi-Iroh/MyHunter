/*
** EPITECH PROJECT, 2022
** my_hunter.h
** File description:
** -> protos and struct for drawing
*/

#pragma once

#include <SFML/Graphics.h>
#include <SFML/Audio.h>

#define DESTROY_IF_ALLOCATED(destroyer, var) {  \
    if (var) {                                  \
        (destroyer)(var);                       \
    }                                           \
}

#define TEXTURE_RECT(animation) (sfIntRect) {   \
    110 * (animation), 0, 110, 110              \
}

#define TEST_OBJ_ALLOC(alloc_expr) {        \
    if (!(alloc_expr)) {                    \
        destroy_objects(obj); return NULL;  \
    }                                       \
}

#define LOAD_SOUND(sound, file, buf) {                              \
    (sound) = sfSound_create();                                     \
    TEST_OBJ_ALLOC((sound));                                        \
    (buf) = sfSoundBuffer_createFromFile((file));                   \
    TEST_OBJ_ALLOC((buf));                                          \
    sfSound_setBuffer((sound), (buf));                              \
    sfSound_setVolume((sound), 50.f + 50.f * !(obj->has_fiesta));   \
}

#define LOAD_DEATHS() {                                                 \
    char name[11] = "death0.ogg";                                       \
    for (size_t i = 0; i < 10; i++) {                                   \
        name[5] = '0' + i;                                              \
        LOAD_SOUND(obj->deaths[i], &name[0], obj->deaths_buffers[i]);   \
    }                                                                   \
}

#define IS_CLOCK_READY(clock, fps)  \
sfClock_getElapsedTime((clock)).microseconds >= 1000000 / (fps)


#ifdef DISP_END_50
    #define DISPLAY_END_MSG my_puts(ends[2]);
#elif defined(DISP_END_100)
    #define DISPLAY_END_MSG my_puts(ends[3]);
#elif defined(DISP_END_MAX)
    #define DISPLAY_END_MSG my_puts(ends[4]);
#else
#define DISPLAY_END_MSG                 \
    while (i < 4 && steps[i] < score) { \
        i++;                            \
    }                                   \
    my_puts(ends[i]);
#endif

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
    sfSound *deaths[10];
    sfSoundBuffer *deaths_buffers[10];
    int death;
    int has_fiesta;
} objects_t;

void draw_window(sfRenderWindow *window, objects_t *obj);

void spawn_duck_at(objects_t *obj, float x, float y);

void handle_event(sfRenderWindow *window, objects_t *obj, unsigned *score);

void destroy_objects(objects_t *obj);

objects_t *init_objects(int argc, char *argv[]);

extern const char *const help_msg;

extern const char *const credits_msg;
