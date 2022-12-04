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
"    -> try to play with mouse's wheel, maybe something cool can happend\n"
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
"    -> Epic BGM : Le Pudding à l'Arsenic (Astérix et Cléopâtre)\n"
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

static void display_end_message(unsigned score)
{
    const unsigned steps[4] = { 10, 25, 50, 100 };
    const char *ends[4] = {
        "Read the --help and learn to play please.",
        "Nothing to say. Not bad nor good. Not interesting.",
        "Serial duck killer, woups... I mean SELECTOR, of course... "
        "(see --help fot further informations).",
        "Are you a cheater ? Otherwise don't you have something else to do ?"
    };
    size_t i = 0;

    DISPLAY_END_MSG;
}

static void update_score(sfRenderWindow *window, int sound, unsigned score)
{
    char new_title[40] = {0};
    char *score_str = NULL;
    char *sound_str = NULL;

    my_strcpy(&new_title[0], "Doggo Duck Hunt | Score ");
    score_str = my_utoa(score);
    my_strcpy(&new_title[24], score_str);
    free(score_str);
    my_strcat(&new_title[0], " | Sound ");
    sound_str = my_utoa((unsigned)sound);
    my_strcat(&new_title[0], sound_str);
    free(sound_str);
    sfRenderWindow_setTitle(window, &new_title[0]);
}

static void main_loop(sfRenderWindow *window, objects_t *obj)
{
    sfClock *rendering_clock = sfClock_create();
    sfClock *duck_clock = sfClock_create();
    unsigned score = 0;

    while (sfRenderWindow_isOpen(window) && rendering_clock && duck_clock) {
        if (IS_CLOCK_READY(duck_clock, 3)) {
            spawn_duck_at(obj, -(rand() % 200), rand() % 690);
            sfClock_restart(duck_clock);
        }
        handle_event(window, obj, &score);
        if (IS_CLOCK_READY(rendering_clock, 60)) {
            update_score(window, obj->death, score);
            draw_window(window, obj);
            sfClock_restart(rendering_clock);
        }
    }
    sfClock_destroy(duck_clock);
    sfClock_destroy(rendering_clock);
    display_end_message(score);
}

int main(int argc, char *argv[])
{
    const sfVideoMode video = {1200, 800, 32};
    sfRenderWindow *window = NULL;
    objects_t *obj = init_objects(argc, argv);
    const char *const start_title = "Doggo Duck Hunt | Score : 0 | Sound : 5";

    srand(time(NULL));
    if (!obj || argc > 2) {
        return 84;
    }
    if (!help(argc, argv)) {
        window = sfRenderWindow_create(video, start_title, 7, 0);
        sfRenderWindow_setFramerateLimit(window, 60);
        main_loop(window, obj);
        my_puts("---------------------------------------------");
        my_puts(credits_msg);
    }
    destroy_objects(obj);
    sfRenderWindow_destroy(window);
    return 0;
}
