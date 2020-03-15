/*
** EPITECH PROJECT, 2019
** my_str_isprintable
** File description:
** hello
*/

#include "../world.h"
#include "my.h"
#include <SFML/Graphics.h>
#include <SFML/Window/Export.h>

void button0(world_t *world, int nb)
{
    button_t *buts = world->edi_buttons;
    buts[nb].pos_x = SCREEN_X - 150, buts[nb].pos_y = 100 + nb*60;
    buts[nb].size_x = 150, buts[nb].size_y = 50;
    sfColor c1[] = {255, 255, 255, 50};
    sfColor c2[] = {50, 50, 50, 0};
    sfColor c3[] = {200, 200, 200, 255};
    buts[nb].color1 = *c1, buts[nb].color2 = *c2, buts[nb].color3 = *c3;
    buts[nb].txt = "Brush size +";
}

void button1(world_t *world, int nb)
{
    button_t *buts = world->edi_buttons;
    buts[nb].pos_x = SCREEN_X - 150, buts[nb].pos_y = 100 + nb*60;
    buts[nb].size_x = 150, buts[nb].size_y = 50;
    sfColor c1[] = {255, 255, 255, 50};
    sfColor c2[] = {50, 50, 50, 0};
    sfColor c3[] = {200, 200, 200, 255};
    buts[nb].color1 = *c1, buts[nb].color2 = *c2, buts[nb].color3 = *c3;
    buts[nb].txt = "Brush size -";
    buts[nb].on = 0;
}

void button2(world_t *world, int nb)
{
    button_t *buts = world->edi_buttons;
    buts[nb].pos_x = SCREEN_X - 150, buts[nb].pos_y = 100 + nb*60;
    buts[nb].size_x = 150, buts[nb].size_y = 50;
    sfColor c1[] = {255, 255, 255, 50};
    sfColor c2[] = {50, 50, 50, 0};
    sfColor c3[] = {200, 200, 200, 255};
    buts[nb].color1 = *c1, buts[nb].color2 = *c2, buts[nb].color3 = *c3;
    buts[nb].txt = "Water Drop";
    buts[nb].on = 0;
}

void button3(world_t *world, int nb)
{
    button_t *buts = world->edi_buttons;
    buts[nb].pos_x = SCREEN_X - 150, buts[nb].pos_y = 100 + nb*60;
    buts[nb].size_x = 150, buts[nb].size_y = 50;
    sfColor c1[] = {255, 255, 255, 50};
    sfColor c2[] = {50, 50, 50, 0};
    sfColor c3[] = {200, 200, 200, 255};
    buts[nb].color1 = *c1, buts[nb].color2 = *c2, buts[nb].color3 = *c3;
    buts[nb].txt = "Height +";
    buts[nb].on = 0;
}

void button4(world_t *world, int nb)
{
    button_t *buts = world->edi_buttons;
    buts[nb].pos_x = SCREEN_X - 150, buts[nb].pos_y = 100 + nb*60;
    buts[nb].size_x = 150, buts[nb].size_y = 50;
    sfColor c1[] = {255, 255, 255, 50};
    sfColor c2[] = {50, 50, 50, 0};
    sfColor c3[] = {200, 200, 200, 255};
    buts[nb].color1 = *c1, buts[nb].color2 = *c2, buts[nb].color3 = *c3;
    buts[nb].txt = "Height -";
    buts[nb].on = 0;
}
