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
float ***grid_grad(int x, int y)
{
    float ***grad = malloc(sizeof(float *) * (x+1));
    for (int i = 0; i < x; i++){
        grad[i] = malloc(sizeof(float*) * (y+1));
        int ii = 0;
        for (; ii < y; ii++){
            grad[i][ii] = malloc(sizeof(float) * 2);
            grad[i][ii][0] = ((rand()%5000)/2500.0-1);
            grad[i][ii][1] = ((rand()%5000)/2500.0-1);
        }
        grad[i][ii] = 0;
    }
    grad[y] = 0;
    return (grad);
}

float lerp(float a, float b, float w) {
    return (1.0f - w)*a + w*b;
}

float dotGridGradient(int ix, int iy, float x, float y)
{
    static float ***grad = 0;
    if (!grad)
        grad = grid_grad(128, 128);
    float dx = x - (float)ix;
    float dy = y - (float)iy;
    return (dx*grad[iy%128][ix%128][0] + dy*grad[iy%128][ix%128][1]);
}

float perlin(float x, float y)
{
    int x0 = (int)x;
    int x1 = x0 + 1;
    int y0 = (int)y;
    int y1 = y0 + 1;

    float sx = x - (float)x0;
    float sy = y - (float)y0;

    float n0, n1, ix0, ix1, value;

    n0 = dotGridGradient(x0, y0, x, y);
    n1 = dotGridGradient(x1, y0, x, y);
    ix0 = lerp(n0, n1, sx);

    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    ix1 = lerp(n0, n1, sx);
    value = lerp(ix0, ix1, sy);
    return value;
}

float **create_mesh(int x, int y, int d)
{
    float **mesh = malloc(sizeof(float *) * (x+1));
    int i = 0;
    for (; i < x; i++){
        mesh[i] = malloc(sizeof(float) * (y+1));
        int ii = 0;
        for (; ii < y; ii++){
            mesh[i][ii] = 0;
            for (int d_nb = 0; d_nb < d; d_nb++)
                mesh[i][ii] += perlin((float)i/(1.1*pow(2, d_nb)), (float)ii/(1.1*pow(2, d_nb)))*pow(2, d_nb);
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

void drop_water(float **mesh, int x, int y, float f, int n)
{
    mesh[x][y] -= f;
    float here = mesh[x][y];
    if (n >= 64){
        mesh[x][y] += f;
        return;
    }

    //framebuffer_t *buf = draw();
    //sfVector2f vec[] = {}
    //my_draw_circle(buf, vec, 5, sfRed);
    char ok = 0;
    if (here > mesh[x-1][y]){
        drop_water(mesh, x-1, y, f, n+1);
        ok = 1;
    }
    else if (here > mesh[x+1][y]){
        drop_water(mesh, x+1, y, f, n+1);
        ok = 1;
    }
    else if (here > mesh[x][y-1]){
        drop_water(mesh, x, y-1, f, n+1);
        ok = 1;
    }
    else if (here > mesh[x][y+1]){
        drop_water(mesh, x, y+1, f, n+1);
        ok = 1;
    }
    if (!ok)
        mesh[x][y] += (n+1)*f;
}

void draw_mesh(framebuffer_t *buf, float **points, int x, int y)
{
    int size = 1;
    sfVector2f *vec = malloc(sizeof(sfVector2u));
    sfVector2f *vec1 = malloc(sizeof(sfVector2u));
    sfVector2f *vec3 = malloc(sizeof(sfVector2u));

    for (int i = 0; i < x*y; i++){
        points[i][2] = -points[i][2];
        points[i][0] = points[i][0]*size/points[i][2]*32*8 + SCREEN_X/2;
        points[i][1] = points[i][1]*size/points[i][2]*32*8 + SCREEN_Y/2;
    }

    for (int i = y+1; i < x*y; i++){
        if (i % y == 0 || points[i][2] < 0  || points[i][0] > SCREEN_X || points[i][0] < 0 || points[i][1] > SCREEN_Y || points[i][1] < 0)
            continue;
        //printf("%f %f %f %f\n", points[i][0], points[i][1], points[i][2], points[i][3]);
        vec->x = points[i][0];
        vec->y = points[i][1];

        vec1->x = points[i-1][0];
        vec1->y = points[i-1][1];

        vec3->x = points[i-y][0];
        vec3->y = points[i-y][1];
        sfColor color = {255, 255, 255, 255};
        my_draw_line(buf, vec, vec1, color);
        my_draw_line(buf, vec, vec3, color);
        //my_put_pixel(buf, points[i][0]*size + 512, points[i][1]*size + 512, sfWhite);
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

typedef struct chunk
{
    float **mesh;
    int x;
    int y;
} chunk_t;

typedef struct map
{
    lld_t *chunk_x;
    lld_t *chunk_y;
    int chunk_size;
    int draw_d;
} map_t;

//main
int main(int ac, char **av)
{
    int size_x = 256;
    int size_y = 256;
    float **mesh = create_mesh(size_x, size_y, 9);
    float **points2;
    float **points;
    map_t *map = malloc(sizeof(map_t));
    map->draw_d = 100;

    float *mat_start = mat3_init();
    mat3_rz(mat_start, -45.0/180*3.14);
    mat3_rx(mat_start, 70.0/180*3.14);
    mat3_tz(mat_start, -100);

    //float *mat_play = mat3_init();

    //points2 = rotate_points(points, mat_start);
    sfVector2i mouse_o;
    sfVector2i mouse;

    for (int frame_nb = 0; frame_nb < 6000; frame_nb++){
        framebuffer_t *buf = draw();
        my_clear_buffer(buf);

        printf("frame %i\n", frame_nb);
        //if (!(frame_nb%1))
        //    drop_water(mesh, size_x/2, size_y/2, 0.01, 0);

        if (sfKeyboard_isKeyPressed(sfKeyZ)){
            mat3_tz(mat_start, 1);
        }
        if (sfKeyboard_isKeyPressed(sfKeyS)){
            mat3_tz(mat_start, -1);
        }
        if (sfKeyboard_isKeyPressed(sfKeyQ)){
            mat3_tx(mat_start, 1);
        }
        if (sfKeyboard_isKeyPressed(sfKeyD)){
            mat3_tx(mat_start, -1);
        }
        if (sfKeyboard_isKeyPressed(sfKeyE)){
            mat3_ty(mat_start, 1);
        }
        if (sfKeyboard_isKeyPressed(sfKeyA)){
            mat3_ty(mat_start, -1);
        }
        if (sfKeyboard_isKeyPressed(sfKeyW)){
            mat3_rz(mat_start, 1.0/180*3.14);
        }
        if (sfKeyboard_isKeyPressed(sfKeyX)){
            mat3_rz(mat_start, -1.0/180*3.14);
        }
        mouse = sfMouse_getPosition(0);
        if (sfMouse_isButtonPressed(sfMouseLeft)){
            float vx = mouse.x - mouse_o.x;
            float vy = mouse.y - mouse_o.y;
            mat3_rx(mat_start, vy/180);
            mat3_ry(mat_start, -vx/180);
        }
        mouse_o = mouse;
        points = mesh_to_points(mesh, size_x, size_y);
        points2 = rotate_points(points, mat_start);
        draw_mesh(buf, points2, size_x, size_y);
        free_points(points2);
        free_points(points);
    }
    free_mesh(mesh, size_x, size_y);
    free(mat_start);
   // free_points(points2);
    return (0);
}
