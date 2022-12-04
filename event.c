/*
** EPITECH PROJECT, 2022
** event.c
** File description:
** -> event handling
*/

#include <limits.h>
#include <stdlib.h>
#include "my_hunter.h"
#include "my.h"

static int are_coords_in_rect(sfVector2i coords, sfFloatRect rect)
{
    return coords.x >= rect.left && coords.x <= rect.left + rect.width &&
    coords.y >= rect.top && coords.y <= rect.top + rect.height;
}

static void display_overflow_msg(unsigned score)
{
    char *score_str = NULL;

    if (score == 0) {
        my_puts("Wow, you broke the game. Overflow you know ?");
        my_putstr("I don't believe you could beat my personal score of ");
        score_str = my_utoa(UINT_MAX);
        my_putstr(score_str);
        my_puts(".\nReally sus...");
        my_puts("(Unless you did know the sudo key to "
        "break my beatiful game...)\n:insert angry face:");
        my_puts("---------------------------------------------");
        free(score_str);
    }
}

static void
kill_pressed_ducks(sfVector2i mouse_pos, objects_t *obj, unsigned *score)
{
    ducks_t *ducks = obj->ducks;
    sfFloatRect sprite_rect;

    while (ducks) {
        sprite_rect = sfSprite_getGlobalBounds(ducks->duck);
        if (are_coords_in_rect(mouse_pos, sprite_rect)) {
            sfSprite_move(ducks->duck, (sfVector2f) { .x = 2000, .y = 0 });
            sfSound_play(obj->deaths[obj->death]);
            (*score)++;
            display_overflow_msg(*score);
        }
        ducks = ducks->next;
    }
}

static void trigger_score_overflow_with_ctrl(unsigned *score)
{
    int is_ctrl_pressed = sfKeyboard_isKeyPressed(sfKeyLControl);

    is_ctrl_pressed |= sfKeyboard_isKeyPressed(sfKeyRControl);
    if (is_ctrl_pressed) {
        *score = UINT_MAX;
    }
}

void handle_event(sfRenderWindow *window, objects_t *obj, unsigned *score)
{
    sfEvent event;
    sfWindow *const cast_window = (sfWindow *)window;

    while (sfRenderWindow_pollEvent(window, &event)) {

        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(window);
        }
        if (event.type == sfEvtMouseButtonPressed) {
            kill_pressed_ducks(sfMouse_getPosition(cast_window), obj, score);
        }
        if (event.type == sfEvtMouseWheelScrolled) {
            obj->death += event.mouseWheelScroll.delta;
            obj->death += 10 * (obj->death < 0);
            obj->death %= 10;
        }
        trigger_score_overflow_with_ctrl(score);
    }
}
