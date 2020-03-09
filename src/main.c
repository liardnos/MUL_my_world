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

sfRenderWindow *window_g;

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
    return (1.0 - w)*a + w*b;
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
            //if (i == 0 || i == x-1 || ii == 0 || ii == y-1)
            //    mesh[i][ii] += 10000;

        }
        mesh[i][ii] = 0;
    }
    mesh[i] = 0;
    return (mesh);
}

float **mesh_to_points(float **mesh, int x, int y)
{
    float **points = malloc(sizeof(float *) * (x*y+1+2));
    points[x*y+2] = 0;
    for (int i = 0; i < x*y+2; i++)
        points[i] = malloc(sizeof(float) * 4);

    points[0][0] = 1;//cos(PI/4);
    points[0][1] = 0;//sin(PI/4);
    points[0][2] = 0;
    points[0][3] = 0;

    points[1][0] = 0;//-cos(PI/4);
    points[1][1] = 1;//sin(PI/4);
    points[1][2] = 0;
    points[1][3] = 0;
    points += 2;

    for (int i = 0; i < x; i++){
        for (int ii = 0; ii < y; ii++){
            points[i+ii*x][0] = -i;
            points[i+ii*x][1] = -ii;
            points[i+ii*x][2] = -mesh[i][ii];
            points[i+ii*x][3] = 1;
        }
    }
    points -= 2;
    return (points);
}

void drop_water(float **mesh, int x, int y, float f, float n)
{
    char ok = 0;
    if ((x <= 1 || x >= 254 || y <= 1 || y >= 254)){
        ok = 0;
    } else {
        float here = mesh[x][y];
        float drag = 0;
        for (int i = 0; i < 16; i++){
            int xx = rand()%3-1 + x;
            int yy = rand()%3-1 + y;
            if (here > mesh[xx][yy]){
                drag = pow(here - mesh[xx][yy], 0.5) * f-n;
                drop_water(mesh, xx, yy, f, n+drag);
                mesh[x][y] -= drag/2;
                mesh[x-1][y] -= drag/8;
                mesh[x+1][y] -= drag/8;
                mesh[x][y-1] -= drag/8;
                mesh[x][y+1] -= drag/8;
                ok = 1;
                break;
            }
        }
    }
    if (!ok){
        mesh[x+1][y] += n/8;
        mesh[x-1][y] += n/8;
        mesh[x][y+1] += n/8;
        mesh[x][y-1] += n/8;
        mesh[x][y] += n/2;
    }
}

float gauss(float x, float dec1, float dec2, float off)
{
    x -= off;
    return (1/(pow(E, x/dec2)+pow(E, -x/dec1)));
}

int min_i(int a, int b)
{
    return (a > b ? b : a);
}

void draw_mesh(framebuffer_t *buf, float **points, int x, int y, float **mesh, int mode)
{
    static float sun = 0;
    sun += PI/600;
    sun > PI*2 ? sun = 0 : 0;
    float sun_angle = fabsf(tan(sun));
    printf("sun %f %f\n", sun_angle, sun);
    static char **sun_grid = 0;
    if (sun_grid == 0){
        sun_grid = malloc(sizeof(char *) * y);
        for (int i = 0; i < y; i++)
            sun_grid[i] = malloc(sizeof(char) * x);
    }
    for (int yy = 0; yy < y; yy++){
        float start = mesh[yy][sun < PI/2 ? 0 : x-1];
        for (int xx = sun < PI/2 ? 0 : x-1; xx < x && 0 <= xx; xx += sun < PI/2 ? 1 : -1){
            start -= sun_angle;
            if (mesh[yy][xx] >= start && sun < PI){
                start = mesh[yy][xx];
                sun_grid[yy][xx] = 1;
            } else
                sun_grid[yy][xx] = 0;
        }
    }
    int size = 1;
    sfVector2f *vec1 = malloc(sizeof(sfVector2u));
    sfVector2f *vec2 = malloc(sizeof(sfVector2u));
    sfVector2f *vec3 = malloc(sizeof(sfVector2u));
    sfVector2f *vec4 = malloc(sizeof(sfVector2u));
    sfColor color_water = sfBlue;
    sfColor color_snow = sfWhite;
    sfColor color_grass = sfGreen;
    sfColor color;

    my_clear_buffer(buf);
    static sfConvexShape *shape = 0;
    if (!shape){
        shape = sfConvexShape_create();
        sfConvexShape_setPointCount(shape, 4);
    }

    int i_x_s = 1;
    int i_y_s = 1;
    int i_x_e = x - 1;
    int i_y_e = y - 1;
    int i_x_inc = 1;
    int i_y_inc = 1;
    char flag = 0;
    int tmp;
    int a = 0;
    points += 2;

    //draw prioryti
    static help = 0;
    help++;
    unsigned long int tab = 0x0;

    float mid = cos(PI/4);

    //points[-1][2] = pow(pow(points[-1][1], 2) + pow(points[-1][0], 2), 0.5);
    //points[-2][2] = pow(pow(points[-2][1], 2) + pow(points[-2][0], 2), 0.5);

    if (points[-1][2] > -mid && points[-1][2] < 0 && points[-2][2] < -mid)
        printf("1\n"), flag = 0x0;
    else if (points[-1][2] < mid && points[-1][2] > 0 && points[-2][2] < -mid)
        printf("2\n"), flag = 0x1;
    else if (points[-1][2] > mid && points[-2][2] > -mid && points[-2][2] < 0)
        printf("3\n"), flag = 0x6;
    else if (points[-1][2] > mid && points[-2][2] < mid && points[-2][2] > 0)
        printf("4\n"), flag = 0x7;
    else if (points[-1][2] < mid && points[-1][2] > 0 && points[-2][2] > mid)
        printf("5\n"), flag = 0x3;
    else if (points[-1][2] < 0 && points[-1][2] > -mid && points[-2][2] > mid)
        printf("6\n"), flag = 0x2;
    else if (points[-1][2] < -mid && points[-2][2] > 0 && points[-2][2] < mid)
        printf("7\n"), flag = 0x5;
    else if (points[-1][2] < -mid && points[-2][2] < 0 && points[-2][2] > -mid)
        printf("8\n"), flag = 0x4;
    printf("%i\n", flag);

    if (flag & 0x1){
        tmp = i_y_e;
        i_y_e = i_y_s;
        i_y_s = tmp;
        i_y_inc = -1;
    }

    if (flag & 0x2){
        tmp = i_x_e;
        i_x_e = i_x_s;
        i_x_s = tmp;
        i_x_inc = -1;
    }

    printf("%f %f\n", (points[-2][2]), (points[-1][2]));

    for (int i = -2; i < x*y; i++){
        points[i][2] = -points[i][2];
        points[i][0] = points[i][0]*size/points[i][2]*32*8 + SCREEN_X/2;
        points[i][1] = points[i][1]*size/points[i][2]*32*8 + SCREEN_Y/2;
    }

    {//db
        sfVector2u vecf[] = {points[-2][0], points[-2][1]};
        my_draw_circle(buf, *vecf, 10, &sfRed);
        vecf->x = points[-1][0];
        vecf->y = points[-1][1];
        my_draw_circle(buf, *vecf, 10, &sfBlue);

        vecf->x = points[0][0];
        vecf->y = points[0][1];
        my_draw_circle(buf, *vecf, 10, &sfGreen);
        vecf->x = points[x-1][0];
        vecf->y = points[x-1][1];
        my_draw_circle(buf, *vecf, 10, &sfGreen);
        vecf->x = points[y*x-1][0];
        vecf->y = points[y*x-1][1];
        my_draw_circle(buf, *vecf, 10, &sfGreen);
        vecf->x = points[y*x-y+1][0];
        vecf->y = points[y*x-y+1][1];
        my_draw_circle(buf, *vecf, 10, &sfGreen);
    }//db

    float max_height = 0;
    float min_height = 0;
    for (int i = 0; mesh[i]; i++){
        for (int ii = 0; mesh[i][ii]; ii++){
        mesh[i][ii] > max_height ? max_height = mesh[i][ii] : 0;
        mesh[i][ii] < min_height ? min_height = mesh[i][ii] : 0;
        }
    }

    int tmp2 = 0;
    for (int i_x = i_x_s; i_x != i_x_e; i_x += i_x_inc){
        for (int i_y = i_y_s; i_y != i_y_e; i_y += i_y_inc){
            int i;
            if (flag & 0x4)
                i = i_y+i_x*x;
            else
                i = i_y*y+i_x;
            tmp2++;
            //if (tmp2 > 128)
            //    return;
            if (i % y == 0 || points[i][2] < 0  || points[i][0] > SCREEN_X || points[i][0] < 0 || points[i][1] > SCREEN_Y || points[i][1] < 0)
                continue;
            vec1->x = points[i][0];
            vec1->y = points[i][1];
            if (vec1->x > SCREEN_X || vec1->x < 0 || vec1->y > SCREEN_Y || vec1->y < 0 || points[i][2] > 2000000)
            continue;


            vec2->x = points[i-y][0];
            vec2->y = points[i-y][1];
            if (vec2->x > SCREEN_X || vec2->x < 0 || vec2->y > SCREEN_Y || vec2->y < 0)
                continue;

            vec3->x = points[i-y-1][0];
            vec3->y = points[i-y-1][1];
            if (vec3->x > SCREEN_X || vec3->x < 0 || vec3->y > SCREEN_Y || vec3->y < 0)
            continue;

            vec4->x = points[i-1][0];
            vec4->y = points[i-1][1];
            if (vec4->x > SCREEN_X || vec4->x < 0 || vec4->y > SCREEN_Y || vec4->y < 0)
            continue;


            float height = (mesh[i%x][i/x] + mesh[i%x-1][i/x-1] +
            mesh[i%x][i/x-1] + mesh[i%x-1][i/x])/4;
            //float pente = fabsf(height - mesh[i%x][i/x]) + fabsf(height - mesh[i%x-1][i/x-1]) + fabsf(height - mesh[i%x][i/x-1]) + fabsf(height - mesh[i%x-1][i/x]);
            //pente /= 4.0;
            //printf("pente %f\n", pente);
            int grass = gauss(height, 15, 10, 0) * 500;
            int snow = gauss(height, 5, 100, 15) * 500;
            int water = gauss(height, 100, 5, -20) * 500;

            sfColor color[] = {min_i(snow, 255), min_i(grass+snow, 255), min_i(water+snow, 255), 255};
            if (sun_grid[i%x][i/x] == 0)
                color->r /= 2, color->g /= 2, color->b /= 2;
            if (mode == 1){
                sfConvexShape_setPoint(shape, 0, *vec1);
                sfConvexShape_setPoint(shape, 1, *vec2);
                sfConvexShape_setPoint(shape, 2, *vec3);
                sfConvexShape_setPoint(shape, 3, *vec4);
                sfConvexShape_setFillColor(shape, *color);
                sfRenderWindow_drawConvexShape(window_g, shape, 0);
            } else if (mode == 2){
                my_draw_line(buf, vec1, vec2, *color);
                my_draw_line(buf, vec1, vec4, *color);
            }
        }
    }
    free(vec1), free(vec2), free(vec3), free(vec4);
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
    int chunk_size; //in point
    int draw_d; //in chunk
} map_t;

//main
int main(int ac, char **av)
{
    int a;
    srand(time(0));
    int size_x = 256;
    int size_y = 256;
    float **mesh = create_mesh(size_x, size_y, 7);
    float **points2;
    float **points;
    map_t *map = malloc(sizeof(map_t));
    map->draw_d = 100;
    map->chunk_x = lld_init();
    map->chunk_y = lld_init();
    float *mat_start = mat3_init();
    //mat3_rz(mat_start, -45.0/180*PI);
    //mat3_rx(mat_start, 70.0/180*PI);
    //mat3_tz(mat_start, -100);
    mat3_ttx(mat_start, size_x/2);
    mat3_tty(mat_start, size_y/2);
    mat3_rx(mat_start, -PI/2);

    sfVector2i mouse_o;
    sfVector2i mouse;
    mouse.x = 0;
    mouse.y = 0;

    sfEvent event;
    int mv = 0;
    for (int frame_nb = 0; frame_nb < 1000000; frame_nb++){
        framebuffer_t *buf = draw();
        while (sfRenderWindow_pollEvent(window_g, &event))
            if (event.type == sfEvtClosed)
                exit (0);

        //my_clear_buffer(buf);
        points = mesh_to_points(mesh, size_x, size_y);
        points2 = rotate_points(points, mat_start);
        draw_mesh(buf, points2, size_x, size_y, mesh, mv+1);
        mv = 0;
        free_points(points2);
        free_points(points);
        //printf("frame %i\n", frame_nb);
        for (int i = 0; i < 50; i++)
            drop_water(mesh, rand()%254+1, rand()%254+1, 0.5, 0);


        if (sfKeyboard_isKeyPressed(sfKeyZ)){
            mat3_tz(mat_start, 1);
            mv = 1;
        }
        if (sfKeyboard_isKeyPressed(sfKeyS)){
            mat3_tz(mat_start, -1);
            mv = 1;
        }
        if (sfKeyboard_isKeyPressed(sfKeyQ)){
            mat3_tx(mat_start, 1);
            mv = 1;
        }
        if (sfKeyboard_isKeyPressed(sfKeyD)){
            mat3_tx(mat_start, -1);
            mv = 1;
        }
        if (sfKeyboard_isKeyPressed(sfKeyE)){
            mat3_ty(mat_start, 1);
            mv = 1;
        }
        if (sfKeyboard_isKeyPressed(sfKeyA)){
            mat3_ty(mat_start, -1);
            mv = 1;
        }
        if (sfKeyboard_isKeyPressed(sfKeyW)){
            mat3_rz(mat_start, 1.0/180*PI);
            mv = 1;
        }
        if (sfKeyboard_isKeyPressed(sfKeyX)){
            mat3_rz(mat_start, -1.0/180*PI);
            mv = 1;
        }
        mouse = sfMouse_getPosition(0);
        if (sfMouse_isButtonPressed(sfMouseLeft)){
            float vx = mouse.x - mouse_o.x;
            float vy = mouse.y - mouse_o.y;
            mat3_rx(mat_start, vy/180);
            mat3_ry(mat_start, -vx/180);
            mv = 1;
        }
        mouse_o = mouse;

        float *mat_inv = mat3_inv(mat_start);
        float *mat_pos = mat3_multiply(mat_inv, mat_start);
        free(mat_inv);
        //float *mat_r = mat3_copy(mat_start);
        //print_mat(mat_pos);

        /*if ((int)mat_pos[3] >= size_x-1)
            mat3_ttx(mat_start, -254);
        if ((int)mat_pos[3] <= 1)
            mat3_ttx(mat_start, 254);
        if ((int)mat_pos[7] >= size_y-1)
            mat3_tty(mat_start, -254);
        if ((int)mat_pos[7] <= 1)
            mat3_tty(mat_start, 254);

        float mesh_z = mesh[(int)mat_pos[3]][(int)mat_pos[7]] - mat_pos[11]+10;
        mat3_ttz(mat_start, mesh_z);*/
    }
    free_mesh(mesh, size_x, size_y);
    free(mat_start);
   // free_points(points2);
    return (0);
}
