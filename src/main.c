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
/*
typedef struct mesh
{
    int size_x;
    int size_y;
    float **val;
} mesh_t;

typedef struct point
{
    float x;
    float y;
    float z;
    float t;
} point_t;

typedef struct points
{
    point_t *p_s;
    int p_nb;
} points_t;
*/
//rotation fonction
float **copy_points(float **points)
{
    int nb_p = 0;
    for (; points[nb_p]; nb_p++);
    float **new_points = malloc(sizeof(float *) * (nb_p+1));
    new_points[nb_p] = 0;
    for (int i = 0; i < nb_p; i++){
        new_points[i] = malloc(sizeof(float) * 4);
        new_points[i][0] = points[i][0];
        new_points[i][1] = points[i][1];
        new_points[i][2] = points[i][2];
        new_points[i][3] = points[i][3];
    }
    return (new_points);
}

void print_mat(float *mat)
{
    for (int i = 0; i < 16; i++){
        if ((i)%4 == 0 && i)
            printf("\n");
        printf("%f ", mat[i]);
    }
    printf("\n");
}

float **rotate_points(float **points, float *mat)
{
    int i = 0;
    for (i = 0; points[i]; i++);
    float **new_points = malloc(sizeof(float *) * (i+1));
    new_points[i] = 0;
    for (i = 0; points[i]; i++){
        new_points[i] = mat3_point(mat, points[i]);
    }
    return (new_points);
}

//points fonction
void free_points(float **points)
{
    for (int i = 0; points[i]; i++)
        free(points[i]);
    free(points);
}

//mesh fonction
/*float lerp(float a, float b, float w)
{
    return ((1.0 - w)*a + w*b);
}*/

float **create_mesh(int x, int y)
{
    float **mesh = malloc(sizeof(float *) * (x+1));
    int i = 0;
    for (; i < x; i++){
        mesh[i] = malloc(sizeof(float) * (y+1));
        int ii = 0;
        for (; ii < y; ii++){
            mesh[i][ii] = (rand()%5000)/5000.0;
        }
        mesh[i][ii] = 0;
    }
    mesh[i] = 0;
    return (mesh);
}

float **mesh_to_points(float **mesh, int x, int y)
{
    float **points = malloc(sizeof(float *) * (x*y+1));
    points[x*y] = 0;
    for (int i = 0; i < x*y; i++)
        points[i] = malloc(sizeof(float) * 4);

    int i = 0;
    for (; i < x; i++){
        for (int ii = 0; ii < y; ii++){
            points[i+ii*x][0] = i-x/2;
            points[i+ii*x][1] = ii-y/2;
            points[i+ii*x][2] = mesh[i][ii];
            points[i+ii*x][3] = 1;
        }
    }
    return (points);
}

void draw_mesh(framebuffer_t *buf, float **points, int x, int y)
{
    int size = 16;
    sfVector2f *vec = malloc(sizeof(sfVector2u));
    sfVector2f *vec1 = malloc(sizeof(sfVector2u));
    sfVector2f *vec3 = malloc(sizeof(sfVector2u));
    for (int i = 1+y; i < x*y; i++){
        if (i % y == 0)
            continue;
        //printf("%f %f %f %f\n", points[i][0], points[i][1], points[i][2], points[i][3]);
        vec->x = points[i][0]*size + 512;
        vec->y = points[i][1]*size + 512;

        vec1->x = points[i-1][0]*size + 512;
        vec1->y = points[i-1][1]*size + 512;

        vec3->x = points[i-y][0]*size + 512;
        vec3->y = points[i-y][1]*size + 512;
        //draw();
        //printf("%i %i %i %i\n", vec->x, vec->y, vec1->x, vec1->y);
        my_draw_line(buf, vec, vec1, sfWhite);
        //printf("%i %i %i %i\n", vec->x, vec->y, vec3->x, vec3->y);
        //my_draw_line(buf, vec, vec2, sfWhite);
        my_draw_line(buf, vec, vec3, sfWhite);
        //my_draw_line(buf, vec, vec4, sfWhite);
        //my_draw_circle(buf, *vec, 2, &sfRed);
    }
    free(vec), free(vec1), free(vec3);
}

void free_mesh(float **mesh, int x, int y)
{
    int i = 0;
    for (; i < x; i++)
        free(mesh[i]);
    free(mesh);
}

//main
int main(int ac, char **av)
{
    int size_x = 64;
    int size_y = 64;
    float **mesh = create_mesh(size_x, size_y);
    float **points = mesh_to_points(mesh, size_x, size_y);
    float **points2;

    float *mat_start = mat3_init();
    mat3_rx(mat_start, 70.0/180*3.14);
    mat3_rz(mat_start, -45.0/180*3.14);

    float *mat_play = mat3_init();
    mat3_ry(mat_play, 0/180*3.14);

    points2 = rotate_points(points, mat_start);
    free_points(points);
    points = points2;
    for (int frame_nb = 0; frame_nb < 6000; frame_nb++){
        framebuffer_t *buf = draw();
        my_fill_buffer(buf, sfBlack);
        printf("frame %i\n", frame_nb);
        if (sfKeyboard_isKeyPressed(sfKeyZ)){
            mat3_rx(mat_start, 1.0/180*3.14);
        }
        if (sfKeyboard_isKeyPressed(sfKeyS)){
            mat3_rx(mat_start, -1.0/180*3.14);
        }
        if (sfKeyboard_isKeyPressed(sfKeyQ)){
            mat3_ry(mat_start, 1.0/180*3.14);
        }
        if (sfKeyboard_isKeyPressed(sfKeyD)){
            mat3_ry(mat_start, -1.0/180*3.14);
        }
        points2 = rotate_points(points, mat_start);
        points2;
        draw_mesh(buf, points2, size_x, size_y);
        free_points(points2);
    }
    free_mesh(mesh, size_x, size_y);
    free_points(points);
    free(mat_start);
    free(mat_play);
    return (0);
}
