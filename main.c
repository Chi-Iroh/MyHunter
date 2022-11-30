/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** -> displays a flying duck and handles mouse events
*/

#include "my_hunter.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void destroy_drawable(drawable_t *draw)
{
    DESTROY_IF_ALLOCATED(sfTexture_destroy, draw->back_tx);
    DESTROY_IF_ALLOCATED(sfTexture_destroy, draw->duck_tx);
    DESTROY_IF_ALLOCATED(sfSprite_destroy, draw->back);
    while (draw->ducks && draw->ducks->duck) {
        DESTROY_IF_ALLOCATED(sfSprite_destroy, draw->ducks->duck);
        draw->ducks = draw->ducks->next;
    }
    DESTROY_IF_ALLOCATED(sfMusic_destroy, draw->bgm);
    free(draw);
    draw = NULL;
}

static int init_textures_and_back(drawable_t *draw)
{
    if (!draw) {
        return 0;
    }
    draw->back_tx = sfTexture_createFromFile("background.jpg", NULL);
    draw->duck_tx = sfTexture_createFromFile("duck.png", NULL);
    if (!draw->back_tx || !draw->duck_tx) {
        return 0;
    }
    draw->back = sfSprite_create();
    if (!draw->back) {
        return 0;
    }
    sfSprite_setTexture(draw->back, draw->back_tx, sfTrue);
    return 1;
}

static drawable_t *init_drawable(void)
{
    drawable_t *draw = malloc(sizeof(drawable_t));

    if (draw) {
        memset(draw, 0, sizeof(drawable_t));
        TEST_DRAWABLE_ALLOC(init_textures_and_back(draw));
        TEST_DRAWABLE_ALLOC(draw->bgm = sfMusic_createFromFile("bgm.ogg"));
        sfMusic_setLoop(draw->bgm, sfTrue);
        sfMusic_play(draw->bgm);
    }
    return draw;
}

static void handle_event(sfRenderWindow *window)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {

        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(window);
        }
    }
}

int main(void)
{
    const sfVideoMode video = {1200, 800, 32};
    sfRenderWindow *window = sfRenderWindow_create(video, "Coin-Coin", 7, 0);
    drawable_t *draw = init_drawable();
    srand(time(NULL));

    if (!draw) {
        return 84;
    }
    spawn_duck_at(draw, 0, 0);
    while (sfRenderWindow_isOpen(window))  {
        handle_event(window);
        draw_window(window, draw);
    }
    destroy_drawable(draw);
    return 0;
}
