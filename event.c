/*
** EPITECH PROJECT, 2022
** event.c
** File description:
** -> event handling
*/

#include "my_hunter.h"
#include "my.h"

static int are_coords_in_rect(sfVector2i coords, sfFloatRect rect)
{
    return coords.x >= rect.left && coords.x <= rect.left + rect.width &&
    coords.y >= rect.top && coords.y <= rect.top + rect.height;
}

static void kill_pressed_ducks(sfVector2i mouse_pos, objects_t *obj)
{
    ducks_t *ducks = obj->ducks;
    sfFloatRect sprite_rect;

    while (ducks) {
        sprite_rect = sfSprite_getGlobalBounds(ducks->duck);
        if (are_coords_in_rect(mouse_pos, sprite_rect)) {
            sfSprite_move(ducks->duck, (sfVector2f) { .x = 2000, .y = 0 });
            sfMusic_play(obj->deaths[obj->death]);
        }
        ducks = ducks->next;
    }
}

void handle_event(sfRenderWindow *window, objects_t *obj)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {

        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(window);
        }
        if (event.type == sfEvtMouseButtonPressed) {
            kill_pressed_ducks(sfMouse_getPosition((sfWindow*)window), obj);
        }
        if (event.type == sfEvtMouseWheelScrolled) {
            obj->death += event.mouseWheelScroll.delta;
            obj->death += 10 * (obj->death < 0);
            obj->death %= 10;
            my_printf("Song n°%d\n", obj->death);
        }
    }
}
