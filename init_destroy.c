/*
** EPITECH PROJECT, 2022
** init_destroy.c
** File description:
** -> handles initialization and destruction od assets
*/

#include <string.h>
#include <stdlib.h>
#include "my_hunter.h"
#include "my.h"

void destroy_objects(objects_t *obj)
{
    ducks_t *tmp;

    DESTROY_IF_ALLOCATED(sfTexture_destroy, obj->back_tx);
    DESTROY_IF_ALLOCATED(sfTexture_destroy, obj->duck_tx);
    DESTROY_IF_ALLOCATED(sfSprite_destroy, obj->back);
    while (obj->ducks) {
        tmp = obj->ducks->next;
        DESTROY_IF_ALLOCATED(sfSprite_destroy, obj->ducks->duck);
        DESTROY_IF_ALLOCATED(free, obj->ducks);
        obj->ducks = tmp;
    }
    DESTROY_IF_ALLOCATED(sfMusic_destroy, obj->bgm);
    for (size_t i = 0; i < 10; i++) {
        DESTROY_IF_ALLOCATED(sfSound_destroy, obj->deaths[i]);
        DESTROY_IF_ALLOCATED(sfSoundBuffer_destroy, obj->deaths_buffers[i]);
    }
    free(obj);
}

static int init_textures_and_back(objects_t *obj)
{
    if (!obj) {
        return 0;
    }
    obj->back_tx = sfTexture_createFromFile("background.jpg", NULL);
    obj->duck_tx = sfTexture_createFromFile("duck.png", NULL);
    if (!obj->back_tx || !obj->duck_tx) {
        return 0;
    }
    obj->back = sfSprite_create();
    if (!obj->back) {
        return 0;
    }
    sfSprite_setTexture(obj->back, obj->back_tx, sfTrue);
    return 1;
}

objects_t *init_objects(int argc, char *argv[])
{
    objects_t *obj = malloc(sizeof(objects_t));

    if (obj) {
        memset(obj, 0, sizeof(objects_t));
        obj->has_fiesta = my_strcmp(argv[1], "--fiesta") == 0;
        TEST_OBJ_ALLOC(init_textures_and_back(obj));
        if (argc == 2 && obj->has_fiesta) {
            TEST_OBJ_ALLOC(obj->bgm = sfMusic_createFromFile("fiesta_bgm.ogg"));
        } else {
            TEST_OBJ_ALLOC(obj->bgm = sfMusic_createFromFile("bgm.ogg"));
        }
        sfMusic_setVolume(obj->bgm, 66.67f);
        LOAD_DEATHS();
        obj->death = 5;
        sfMusic_setLoop(obj->bgm, sfTrue);
        sfMusic_play(obj->bgm);
    }
    return obj;
}
