/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** -> main
*/

#include <time.h>
#include <stdlib.h>
#include "my_hunter.h"
#include "my.h"

const char *const help_msg =
"                 ___________ \n"
"                / ~~~~~~~~~ \\\n"
"                | MY_HUNTER |\n"
"                \\___________/\n"
"---------------------------------------------\n"
"#############################################\n"
"############__---~~~~~|~~~~~--__#############\n"
"########.-~~          |          ~~-.########\n"
"#####.-~     .-~~~~-. |              ~-.#####\n"
"####/       {  o     }|                 \\####\n"
"###/        /       / |                  \\###\n"
"##|        `--r'   {  | ,___.-',          |##\n"
"##|          /      ~-|         ',        |##\n"
"##|---------{---------|----------'--------|##\n"
"##|          \\        |         /         |##\n"
"##|           \\       |        /          |##\n"
"###\\         ~ ~~~~~~~|~~~~~~~~~ ~       /###\n"
"####\\       ~ ~ ~ ~ ~ | ~ ~ ~ ~ ~ ~     /####\n"
"#####`-_     ~ ~ ~ ~ ~|~ ~ ~ ~ ~ ~    _-'####\n"
"########`-__    ~ ~ ~ | ~ ~ ~ ~   __-'#######\n"
"############~~---_____|_____---~~############\n"
"#############################################\n"
"\n"
"USAGE :\n"
"./my_hunter <flag>\n"
"    -> <flag> can be either -h (or --help) --> which displays this menu\n"
"    -> OR --epic which sets a more epic bgm :)\n"
"---------------------------------------------\n"
"CONTROLS :\n"
"    -> mouse left click to SELECT a duck\n"
"    -> use the mouse's wheel to change the SELECTION sound (there are 10)\n"
"---------------------------------------------\n"
"For the fervent animal rights defenders, "
"I swear that no duck was harmed in any way.\n"
"They are only selected and automatically moved into their home, "
"then gently freed when they are sound asleep.\n"
"---------------------------------------------\n"
"              Have Fun :)\n";

const char *const credits_msg =
"Credits :\n"
"    -> Default BGM : Humoresque of a Little Dog"
" (Super Smash Bros Ultimate, EarthBound serie)\n"
"    -> Epic BGM : The Obscurus - Rooftop Chase"
" (Fantastic Beasts and Where to Find Them)\n"
"    -> Death sounds : various sources (mainly depositphotos)\n";

static int help(int argc, char *argv[])
{
    if (argc != 2) {
        return 0;
    }
    if (my_strcmp(argv[1], "-h") == 0 || my_strcmp(argv[1], "--help") == 0) {
        my_puts(help_msg);
        return 1;
    }
    return my_strcmp(argv[1], "--epic") == 0 ? 0 : 1;
}

static int clock_ready(sfClock *clock, unsigned fps)
{
    return sfClock_getElapsedTime(clock).microseconds >= 1000000 / fps;
}

static void main_loop(sfRenderWindow *window, objects_t *obj, sfClock *clock)
{
    while (sfRenderWindow_isOpen(window)) {
        if (clock_ready(clock, 3)) {
            spawn_duck_at(obj, -(rand() % 200), rand() % 690);
            sfClock_restart(clock);
        }
        handle_event(window, obj);
        if (clock_ready(clock, 60)) {

        }
        draw_window(window, obj);
    }
}

int main(int argc, char *argv[])
{
    const sfVideoMode video = {1200, 800, 32};
    sfRenderWindow *window = NULL;
    objects_t *obj = init_objects(argc, argv);
    sfClock *clock = sfClock_create();

    srand(time(NULL));
    if (!obj || argc > 2) {
        return 84;
    }
    if (!help(argc, argv)) {
        window = sfRenderWindow_create(video, "Doggo Duck Hunt", 7, 0);
        main_loop(window, obj, clock);
        my_puts(credits_msg);
    }
    destroy_objects(obj);
    sfRenderWindow_destroy(window);
    sfClock_destroy(clock);
    return 0;
}
