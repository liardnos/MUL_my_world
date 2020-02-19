/*
** EPITECH PROJECT, 2019
** my_compute_power_it
** File description:
** hello
*/

#include "../my.h"
#include "../screen.h"

void my_clear_buffer(framebuffer_t *buf)
{
    int size = buf->width * buf->height*4/sizeof(long int);
    long unsigned int *bufy = (long int *)buf->pixels;
    long unsigned int lcolor = 0;
    for (int i = 0; i < size; i++)
        bufy[i] = lcolor;
}
