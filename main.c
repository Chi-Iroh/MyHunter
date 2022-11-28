/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** -> displays a flying duck and handles mouse events
*/

#include <SFML/Graphics.h>

static int init_textures(sfTexture **background, sfTexture **duck)
{
    *background = sfTexture_createFromFile("background.jpg", NULL);
    if (!*background) {
        return 0;
    }
    *duck = sfTexture_createFromFile("duck.png", NULL);
    if (!*duck) {
        sfTexture_destroy(*background);
        return 0;
    }
    return 1;
}

static void handle_event(sfRenderWindow *window, sfEvent *event)
{
    if (event->type == sfEvtClosed) {
        sfRenderWindow_close(window);
    }
}

static void
draw_window(sfRenderWindow *window, sfTexture *background, sfTexture *duck)
{
    static unsigned n = 0;
    static float offset = 0.f;
    sfSprite *duck_s = sfSprite_create();
    sfSprite *background_s = sfSprite_create();

    sfSprite_setTextureRect(duck_s, (sfIntRect){ 110 * n, 0, 110, 110 });
    sfSprite_setTexture(duck_s, duck, sfFalse);
    sfSprite_move(duck_s, (sfVector2f){ .x = offset, .y = 0 });
    sfSprite_setTexture(background_s, background, sfTrue);
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawSprite(window, background_s, NULL);
    sfRenderWindow_drawSprite(window, duck_s, NULL);
    sfRenderWindow_display(window);
    sfSprite_destroy(background_s);
    sfSprite_destroy(duck_s);
    sfSleep((sfTime){ 1000000 / 60 });
    n = (n + 100) % 3;
    offset = (int)(offset + 10) % 1200;
}

int main(void)
{
    my_printf("%a", 0x1.2567p5);
    const sfVideoMode video = {1200, 800, 32};
    sfRenderWindow *window = sfRenderWindow_create(video, "Coin-Coin", 7, 0);
    sfTexture *background = NULL;
    sfTexture *duck = NULL;
    sfEvent event;

    if (!init_textures(&background, &duck)) {
        return 84;
    }
    while (sfRenderWindow_isOpen(window))  {
        while (sfRenderWindow_pollEvent(window, &event)) {
            handle_event(window, &event);
        }
        draw_window(window, background, duck);
    }
    sfTexture_destroy(duck);
    sfTexture_destroy(background);
    return 0;
}
