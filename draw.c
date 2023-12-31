/*
** EPITECH PROJECT, 2022
** obj.c
** File description:
** -> obj sprites
*/

#include "my_hunter.h"
#include <stdlib.h>

static void add_duck(ducks_t **ducks, sfSprite *duck)
{
    ducks_t *new_duck = *ducks;
    ducks_t **last_duck = ducks;

    while (*last_duck) {
        last_duck = &(*last_duck)->next;
        if (*last_duck) {
            new_duck = new_duck->next;
        }
    }
    *last_duck = malloc(sizeof(ducks_t));
    if (*last_duck) {
        (*last_duck)->duck = duck;
        (*last_duck)->next = NULL;
    } else {
        sfSprite_destroy(duck);
    }
}

void spawn_duck_at(objects_t *obj, float x, float y)
{
    sfSprite *new_duck = sfSprite_create();

    if (new_duck) {
        sfSprite_setPosition(new_duck, (sfVector2f){x, y});
        sfSprite_setTextureRect(new_duck, TEXTURE_RECT(0));
        sfSprite_setTexture(new_duck, obj->duck_tx, sfFalse);
        add_duck(&obj->ducks, new_duck);
    }
}

static void destroy_useless_ducks(ducks_t **ducks, float offset)
{
    ducks_t *previous = NULL;
    ducks_t *start = *ducks;
    ducks_t *tmp = NULL;
    while (start) {
        if (sfSprite_getPosition(start->duck).x < 1200 - 110 - offset) {
            previous = start;
            start = start->next;
            continue;
        }
        sfSprite_destroy(start->duck);
        tmp = start;
        if (previous) {
            previous->next = start->next;
        } else {
            *ducks = start->next;
        }
        start = previous ? start->next : *ducks;
        free(tmp);
    }
}

static void
move_and_draw_all_ducks(sfRenderWindow *window, ducks_t **ducks, float offset)
{
    static unsigned animation = 0;
    ducks_t *start = NULL;

    destroy_useless_ducks(ducks, offset);
    start = *ducks;
    while (start && start->duck) {
        sfSprite_setTextureRect(start->duck, TEXTURE_RECT(animation));
        sfSprite_move(start->duck, (sfVector2f) { offset, 0.f });
        sfRenderWindow_drawSprite(window, start->duck, NULL);
        start = start->next;
    }
    animation = (animation + 1) % 3;
}

void draw_window(sfRenderWindow *window, objects_t *obj)
{
    sfRenderWindow_clear(window, (sfColor) { 0xB5, 0xFC, 0xF6, 0xFF });
    sfRenderWindow_drawSprite(window, obj->back, NULL);
    move_and_draw_all_ducks(window, &obj->ducks, 5.f);
    sfRenderWindow_display(window);
}
