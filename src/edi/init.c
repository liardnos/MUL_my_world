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
#include "../world.h"

void init_buttons(world_t *world)
{
    button0(world, 0);
    button1(world, 1);
    button2(world, 2);
    button3(world, 3);
    button4(world, 4);
    button5(world, 5);
    button6(world, 6);
    button7(world, 7);
    button8(world, 8);
    button9(world, 9);
}

void init_edit(world_t *world)
{
    sfVideoMode mode = {SCREEN_X, SCREEN_Y, 32};
    world->buton_nb = 10;
    world->edi = sfRenderWindow_create(mode, "editor", sfClose, 0);
    world->edi_buf = framebuffer_create(SCREEN_X, SCREEN_Y);
    world->edi_x = 0;
    world->edi_y = 0;
    world->brush_type = 0;
    world->brush = 1;
    world->edi_buttons = malloc(sizeof(button_t) * world->buton_nb);
    init_buttons(world);
    world->txt = sfText_create();
    world->font = sfFont_createFromFile("data/font.TTF");
}
