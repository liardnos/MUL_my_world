/*
** EPITECH PROJECT, 2019
** my_compute_power_it
** File description:
** hello
*/

#include <SFML/Graphics.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../my.h"
#include "../screen.h"

int my_draw_line(framebuffer_t *buf, sfVector2f *vects0, sfVector2f *vects1,
    sfColor color)
{
    float size_x = (float)vects1->x - (float)vects0->x;
    float size_y = (float)vects1->y - (float)vects0->y;
    float y = 0;
    if (size_x == 0 && size_y == 0)
        return (0);
    else if (size_x*size_x > size_y*size_y){
        float coef = size_y / size_x;
        if (size_x > 0.0) for (float x = 0; x <= size_x; x++, y += coef)
                my_put_pixel(buf, vects0->x+x, vects0->y+y, color);
        else if (size_x < 0.0) for (float x = 0; x >= size_x; x--, y -= coef)
                my_put_pixel(buf, vects0->x+x, vects0->y+y, color);
    } else {
        float coef = size_x / size_y;
        if (size_y > 0.0) for (float x = 0; y <= size_y; y++, x += coef)
                my_put_pixel(buf, vects0->x+x, vects0->y+y, color);
        else if (size_y < 0.0)
            for (float x = 0; y >= size_y; y--, x -= coef)
                my_put_pixel(buf, vects0->x+x, vects0->y+y, color);
    }
}

void my_draw_lines(framebuffer_t *buf, sfVector2f **vects, int n, sfColor color)
{
    for (int i = 0; i < n-1; i++){
        my_draw_line(buf, vects[i], vects[i+1], color);
    }
}
