/*
** EPITECH PROJECT, 2019
** my_str_isprintable
** File description:
** hello
*/

#include <stdlib.h>
#include "my.h"
#include "screen.h"
#include <SFML/Graphics.h>
#include <SFML/Window/Export.h>
#include <SFML/Window/Keyboard.h>
#include <math.h>
#include <stdio.h>
#include "world.h"

int min_i(int a, int b)
{
    return (a > b ? b : a);
}

void draw_window(sfRenderWindow *win, framebuffer_t *fb)
{
    static sfSprite *sprite = 0; !sprite ? sprite = sfSprite_create() : 0;
    static sfTexture *texture = 0;
    !texture ? texture = sfTexture_create(SCREEN_X, SCREEN_Y) : 0;

    static char first = 0;
    for (; !first; first = 1){
        sfRenderWindow_setFramerateLimit(win, 60);
        sfSprite_setTexture(sprite, texture, sfTrue);
    }
    sfTexture_updateFromPixels(texture, fb->pixels, SCREEN_X, SCREEN_Y, 0, 0);
    sfRenderWindow_drawSprite(win, sprite, 0);
    sfRenderWindow_display(win);
    sfRenderWindow_clear(win, sfBlack);
}

world_t *create_world(int x, int y)
{
    world_t *world = malloc(sizeof(world_t));
    world->x = x;
    world->y = y;
    init_map(world);
    init_cam(world);
    init_edit(world);
    return (world);
}

int main(int ac, char **av)
{
    int size = 128;
    if (ac == 2 && !my_strcmp(av[1], "-h")){
        help();
        return (0);
    } else if (ac == 2 && my_getnbr(av[1]) > 0)
        size = my_getnbr(av[1]);
    srand(&size);
    world_t *world = create_world(size, size);
    sfEvent event;
    for (int frame_nb = 0; frame_nb < 200000000; frame_nb++){
        main_cam(world);
        main_edit(world);
        while (sfRenderWindow_pollEvent(world->edi, &event))
            if (event.type == sfEvtClosed)
                return (0);
        while (sfRenderWindow_pollEvent(world->cam, &event))
            if (event.type == sfEvtClosed)
                return (0);
    }
    return (0);
}
