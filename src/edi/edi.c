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

lld_t *get_brush_cell(world_t *world, int x, int y)
{
    static lld_t *lld = 0;
    lld ? lld_free(lld) : 0;
    lld = lld_init();
    int brush = world->brush;
    for (int xx = x - brush+1; xx < x + brush; xx++)
        for (int yy = y - brush+1; yy < y + brush; yy++)
            if (xx > 1 && xx < world->x-2 && yy > 1 && yy < world->y-2)
                lld_insert(lld, 0, xx + ((long unsigned int)yy << 32));
    return (lld);
}

void interact(world_t *world, int x, int y)
{
    int xy[] = {x, y, world->x, world->y};
    world->brush_type == 1 ? drop_water(world->mesh, xy, 0.5, 0) : 0;
    world->brush_type == 2 ? world->mesh[x][y] += 1 : 0;
    world->brush_type == 3 ? world->mesh[x][y] -= 1 : 0;
}

void take_input_edit(world_t *world)
{
    sfVector2i mouse = sfMouse_getPositionRenderWindow(world->edi);
    if (mouse.x < 0 || mouse.y < 0 || mouse.x > SCREEN_X || mouse.y > SCREEN_Y)
        return;
    int cs = world->cs;
    if (sfMouse_isButtonPressed(sfMouseLeft)){
        int xy[] = {world->x - (mouse.x - world->edi_x)/cs,
        (mouse.y - world->edi_y)/cs};
        lld_t *cells = get_brush_cell(world, xy[0], xy[1]);
        while (cells->data){
            int x = (long int)lld_read(cells, 0);
            int y = (long int)lld_pop(cells, 0) >> 32;
            interact(world, x, y);
        }
    }
}

int main_edit(world_t *world)
{
    draw_map(world);
    draw_player(world);
    draw_brush(world);
    sfVector2i m = sfMouse_getPositionRenderWindow(world->edi);
    if (!(m.x < 0 || m.y < 0 || m.x > SCREEN_X || m.y > SCREEN_Y))
        if (!interact_butons(world))
            take_input_edit(world);
    draw_window(world->edi, world->edi_buf);
    my_clear_buffer(world->edi_buf);
    return (0);
}
