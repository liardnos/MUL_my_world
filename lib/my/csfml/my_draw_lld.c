/*
** EPITECH PROJECT, 2019
** my_compute_power_it
** File description:
** unfinish
*/

#include <SFML/Graphics.h>
#include "../screen.h"
#include "../my.h"

int my_draw_lld(framebuffer_t *buf, lld_t *lld)
{
    static int start = 1;
    static sfVector2u pos[] = {10, 10};
    static sfColor color[] = {255, 255, 255, 255};
    static unsigned int size = 10;
    if (start == 1){
        start = 0;
    }
    lld_t *mov = lld->next;
    for (int i = 0; mov; i++, mov = mov->next){
        my_draw_circle(buf, *pos, 10, color);
        pos->x += size*2 + 10;
    }
}
