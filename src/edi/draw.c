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

void draw_player(world_t *world)
{
    float *mat_inv = mat3_inv(world->mat_start);
    float *mat_pos = mat3_multiply(mat_inv, world->mat_start);
    free(mat_inv);
    int cs = world->cs;
    sfVector2u vect[] = {
        (world->x-mat_pos[3]) * cs + world->edi_x,
        mat_pos[7] * cs + world->edi_y
    };
    my_draw_circle(world->edi_buf, *vect, 10, &sfRed);
    free(mat_pos);
}

void draw_map(world_t *world)
{
    sfVector2u vect;
    sfVector2f vect1;
    sfVector2f vect2;
    int cs = world->cs;
    for (int y = 1; y < world->y; y++)
        for (int x = 1; x < world->x; x++){
            sfColor color = calc_color(world->mesh, x+y*world->x,
            world->x, world->sun_grid);
            vect.x = ((world->x-x)-1)*cs + world->edi_x;
            vect.y = (y-1)*cs + world->edi_y;
            my_draw_square(world->edi_buf, vect, cs, color);
        }
    vect1.x = world->edi_x%cs, vect1.y = world->edi_y%cs;
    vect2.x = world->edi_x%cs, vect2.y = SCREEN_Y;
    for (; vect1.x < SCREEN_X; vect1.x += cs, vect2.x += cs)
        my_draw_line(world->edi_buf, &vect1, &vect2, sfBlack);
    vect1.x = world->edi_x%cs, vect1.y = world->edi_y%cs;
    vect2.x = SCREEN_X, vect2.y = world->edi_y%cs;
    for (; vect1.y < SCREEN_X; vect1.y += cs, vect2.y += cs)
        my_draw_line(world->edi_buf, &vect1, &vect2, sfBlack);
}

void draw_brush(world_t *world)
{
    sfVector2i mouse = sfMouse_getPositionRenderWindow(world->edi);
    if (mouse.x < 0 || mouse.y < 0 || mouse.x > SCREEN_X || mouse.y > SCREEN_Y)
        return;
    int cs = world->cs;
    int x = (mouse.x)/cs;
    int y = (mouse.y)/cs;
    int brush = world->brush;
    int x_p = world->edi_x%cs;
    int y_p = world->edi_y%cs;
    sfVector2f vect1[] = {(x-brush+1)*cs+x_p, (y-brush+1)*cs+y_p};
    sfVector2f vect2[] = {(x+brush)*cs+x_p, (y-brush+1)*cs+y_p};
    sfVector2f vect3[] = {(x-brush+1)*cs+x_p, (y+brush)*cs+y_p};
    sfVector2f vect4[] = {(x+brush)*cs+x_p, (y+brush)*cs+y_p};
    my_draw_line(world->edi_buf, vect1, vect2, sfRed);
    my_draw_line(world->edi_buf, vect2, vect4, sfRed);
    my_draw_line(world->edi_buf, vect4, vect3, sfRed);
    my_draw_line(world->edi_buf, vect3, vect1, sfRed);
}
