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

#define E 2.71828182846
#define PI 3.14159265359
#define SCREEN_X 800
#define SCREEN_Y 800

#include "world.h"

char button(world_t *world, int b_nb)
{
    button_t *b = &world->edi_buttons[b_nb];
    int vect[] = {b->pos_x, b->pos_y, b->size_x, b->size_y};
    sfVector2i m = sfMouse_getPositionRenderWindow(world->edi);
    char flag = 0;
    (m.x > b->pos_x && m.y > b->pos_y &&
    m.x < b->pos_x + b->size_x && m.y < b->pos_y + b->size_y) ? flag |= 0x1 : 0;
    (flag & 0x1 && sfMouse_isButtonPressed(sfMouseLeft)) ? flag |= 0x2 : 0;
    flag == 0x0 ? my_draw_rect(world->edi_buf, vect, b->color1) : 0;
    flag == 0x1 ? my_draw_rect(world->edi_buf, vect, b->color2) : 0;
    flag == 0x3 ? my_draw_rect(world->edi_buf, vect, b->color3) : 0;
    sfText_setString(world->txt, b->txt);
    sfText_setCharacterSize(world->txt, 20);
    sfText_setFont(world->txt, world->font);
    sfText_setFillColor(world->txt, sfWhite);
    sfVector2f vect2[] = {b->pos_x+10, b->pos_y+10};
    sfText_setPosition(world->txt, *vect2);
    sfRenderWindow_drawText(world->edi, world->txt, 0);
    flag == 0x3 ? b->on == 1 ? flag = 0x2 : (b->on = 1) : (b->on = 0);
    return (flag);
}

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

void button5(world_t *world, int nb)
{
    button_t *buts = world->edi_buttons;
    buts[nb].pos_x = SCREEN_X - 150, buts[nb].pos_y = 100 + nb*60;
    buts[nb].size_x = 150, buts[nb].size_y = 50;
    sfColor c1[] = {255, 255, 255, 50};
    sfColor c2[] = {50, 50, 50, 0};
    sfColor c3[] = {200, 200, 200, 255};
    buts[nb].color1 = *c1, buts[nb].color2 = *c2, buts[nb].color3 = *c3;
    buts[nb].txt = "Switch Vue";
    buts[nb].on = 0;
}

void init_buttons(world_t *world)
{
    button0(world, 0);
    button1(world, 1);
    button2(world, 2);
    button3(world, 3);
    button4(world, 4);
    button5(world, 5);
}

void init_edit(world_t *world)
{
    sfVideoMode mode = {SCREEN_X, SCREEN_Y, 32};
    world->buton_nb = 6;
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

void draw_player(world_t *world)
{
    float *mat_inv = mat3_inv(world->mat_start);
    float *mat_pos = mat3_multiply(mat_inv, world->mat_start);
    free(mat_inv);
    int cs = SCREEN_X/(world->x)*1.5;
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
    int cs = SCREEN_X/(world->x)*1.5;
    for (int y = 1; y < world->y; y++){
        for (int x = 1; x < world->x; x++){
            sfColor color = calc_color(world->mesh, x+y*world->x, world->x, world->sun_grid);
            vect.x = ((world->x-x)-1)*cs + world->edi_x;
            vect.y = (y-1)*cs + world->edi_y;
            my_draw_square(world->edi_buf, vect, cs, color);
        }
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
    int cs = SCREEN_X/(world->x)*1.5;
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
    sfKeyboard_isKeyPressed(sfKeyZ) ? world->edi_y += 5, world->mv |= 1 : 0;
    sfKeyboard_isKeyPressed(sfKeyS) ? world->edi_y -= 5, world->mv |= 1 : 0;
    sfKeyboard_isKeyPressed(sfKeyQ) ? world->edi_x += 5, world->mv |= 1 : 0;
    sfKeyboard_isKeyPressed(sfKeyD) ? world->edi_x -= 5, world->mv |= 1 : 0;
    int cs = SCREEN_X/(world->x)*1.5;
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

int interact_butons(world_t *world)
{
    int tot = 0;
    button(world, 0) == 0x3 ? world->brush += 1 : 0;
    button(world, 1) == 0x3 ? world->brush > 0 ? world->brush -= 1 : 0 : 0;
    button(world, 2) == 0x3 ? world->brush_type = 1 : 0;
    button(world, 3) == 0x3 ? world->brush_type = 2 : 0;
    button(world, 4) == 0x3 ? world->brush_type = 3 : 0;
    button(world, 5) == 0x3 ? world->mv ^= 2 : 0;
    for (int i = 0; i < world->buton_nb; i++)
        tot += button(world, i);
    return (tot);
}

int main_edit(world_t *world)
{
    draw_map(world);
    draw_player(world);
    draw_brush(world);
    if (!interact_butons(world)){
        take_input_edit(world);
    }
    draw_window(world->edi, world->edi_buf);
    my_clear_buffer(world->edi_buf);
    return (0);
}
