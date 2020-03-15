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

int main_edit(world_t *world);
void init_edit(world_t *world);

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
            mesh[i][ii] -= 5;
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
    points[0][0] = 1, points[0][1] = 0, points[0][2] = 0, points[0][3] = 0;
    points[1][0] = 0, points[1][1] = 1, points[1][2] = 0, points[1][3] = 0;
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

void drop_water(float **mesh, int *xy, float f, float n)
{
    char ok = 0;
    int x = xy[0];
    int y = xy[1];
    if (!(x <= 1 || x >= xy[2] - 2 || y <= 1 || y >= xy[3] - 2)){
        float here = mesh[x][y];
        for (int i = 0; i < 16; i++){
            int xx = rand() % 3 - 1 + x;
            int yy = rand() % 3 - 1 + y;
            if (here > mesh[xx][yy]){
                float d = pow(here - mesh[xx][yy], 0.5) * f - n;
                int xxyy[] = {xx, yy, xy[2], xy[3]};
                drop_water(mesh, xxyy, f, n+d);
                mesh[x][y] -= d/2, mesh[x-1][y] -= d/8, mesh[x+1][y] -= d/8;
                mesh[x][y-1] -= d/8, mesh[x][y+1] -= d/8, ok = 1;
                break;
            }
        }
    }
    !ok ? mesh[x+1][y] += n/8, mesh[x-1][y] += n/8,
    mesh[x][y+1] += n/8, mesh[x][y-1] += n/8, mesh[x][y] += n/2 : 0;
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

char calc_flag(float **points)
{
    float mid = cos(PI/4);
    char flag =
    (points[-1][2] > -mid && points[-1][2] < 0 && points[-2][2] < -mid) ? 0x0 :
    (points[-1][2] < mid && points[-1][2] > 0 && points[-2][2] < -mid) ? 0x1 :
    (points[-1][2] > mid && points[-2][2] > -mid && points[-2][2] < 0) ? 0x6 :
    (points[-1][2] > mid && points[-2][2] < mid && points[-2][2] > 0) ? 0x7 :
    (points[-1][2] < mid && points[-1][2] > 0 && points[-2][2] > mid) ? 0x3 :
    (points[-1][2] < 0 && points[-1][2] > -mid && points[-2][2] > mid) ? 0x2 :
    (points[-1][2] < -mid && points[-2][2] > 0 && points[-2][2] < mid) ? 0x5 :
    points[-1][2] < -mid && points[-2][2] < 0 && points[-2][2] > -mid ? 0x4 : 0;
    return (flag);
}

char **calc_sun_grid(float **mesh, int x, int y, world_t *world)
{
    world->sun += PI/6000;
    float sun_angle = fabsf(tan(world->sun));
    world->sun > PI*1.5 ? world->sun = -PI/2 : 0;
    sin(world->sun) < 0 ? sun_angle *= -1 : 0;
    static char **sun_grid = 0;
    if (sun_grid == 0){
        sun_grid = malloc(sizeof(char *) * y);
        for (int i = 0; i < y; i++) sun_grid[i] = malloc(sizeof(char) * x);
        world->sun_grid = sun_grid;
    }
    for (int yy = 0; yy < y; yy++){
        float start = mesh[yy][world->sun < PI/2 ? 0 : x-1];
        for (int xx = world->sun < PI/2.0 ? 0 : x-1; xx < x && 0 <= xx; xx += world->sun < PI/2.0 ? 1 : -1){
            start -= sun_angle;
            sun_grid[yy][xx] = ((mesh[yy][xx]) >= start) ?
            start = (mesh[yy][xx]), 1 : 0;
        }
    }
    return (sun_grid);
}

char did_we_draw(sfVector2f **vecs, float **points, int i, int y)
{
    if (i % y == 0 || points[i][2] < 0  || points[i][0] > SCREEN_X ||
        points[i][0] < 0 || points[i][1] > SCREEN_Y || points[i][1] < 0)
        return (1);
    vecs[0]->x = points[i][0], vecs[0]->y = points[i][1];
    if (vecs[0]->x > SCREEN_X || vecs[0]->x < 0 || vecs[0]->y > SCREEN_Y
        || vecs[0]->y < 0 || points[i][2] > 10000) return (1);
    vecs[1]->x = points[i-y][0], vecs[1]->y = points[i-y][1];
    if (vecs[1]->x > SCREEN_X || vecs[1]->x < 0 || vecs[1]->y > SCREEN_Y
        || vecs[1]->y < 0) return (1);
    vecs[2]->x = points[i-y-1][0], vecs[2]->y = points[i-y-1][1];
    if (vecs[2]->x > SCREEN_X || vecs[2]->x < 0 || vecs[2]->y > SCREEN_Y
        || vecs[2]->y < 0) return (1);
    vecs[3]->x = points[i-1][0], vecs[3]->y = points[i-1][1];
    if (vecs[3]->x > SCREEN_X || vecs[3]->x < 0 || vecs[3]->y > SCREEN_Y
        || vecs[3]->y < 0) return (1);
    return (0);
}

sfColor calc_color(float **mesh, int i, int x, char **sun_grid)
{
    float height = (mesh[i%x][i/x] + mesh[i%x-1][i/x-1] +
    mesh[i%x][i/x-1] + mesh[i%x-1][i/x])/4;
    int water = gauss(height, 100, 1, -20) * 500;
    int grass = gauss(height, 7, 7, -10) * 500;
    int stone = gauss(height, 1, 10, 10) * 500;
    int snow = gauss(height, 10, 100, 17) * 500;

    sfColor color[] = {min_i(snow+stone, 255), min_i(grass+snow+stone, 255),
    min_i(water+snow+stone, 255), 255};
    if (sun_grid[i%x][i/x] == 0){
        float div = 0;
        div += -sun_grid[(i+1)%x][i/x]+1;
        div += -sun_grid[(i-1)%x][i/x]+1;
        div += -sun_grid[i%x][(i/x+1)%x]+1;
        div += -sun_grid[i%x][(i/x-1)%x]+1;
        div = 1.0 / (div/2+1);
        color->r *= div, color->g *= div, color->b *= div;
    }
    return (*color);
}

void draw_shape(sfConvexShape *shape, sfVector2f **vecs, sfColor color,
    world_t *world)
{
    if (!world->mv){
        sfConvexShape_setPoint(shape, 0, *vecs[0]);
        sfConvexShape_setPoint(shape, 1, *vecs[1]);
        sfConvexShape_setPoint(shape, 2, *vecs[2]);
        sfConvexShape_setPoint(shape, 3, *vecs[3]);
        sfConvexShape_setFillColor(shape, color);
        sfRenderWindow_drawConvexShape(world->cam, shape, 0);
    } else {
        my_draw_line(world->cam_buf, vecs[0], vecs[1], color);
        my_draw_line(world->cam_buf, vecs[0], vecs[3], color);
    }
}

void aply_flags(char flag, float **points, int *i_v, int xy)
{
    int tmp;
    flag & 0x1 ? tmp = i_v[3], i_v[3] = i_v[1], i_v[1] = tmp, i_v[5] = -1 : 0;
    flag & 0x2 ? tmp = i_v[2], i_v[2] = i_v[0], i_v[0] = tmp, i_v[4] = -1 : 0;
    for (int i = -2; i < xy; i++){
        points[i][2] = -points[i][2];
        points[i][0] = points[i][0] * 2 / points[i][2] * 32 * 8 + SCREEN_X/2;
        points[i][1] = points[i][1] * 2 / points[i][2] * 32 * 8 + SCREEN_Y/2;
    }
}

void draw_mesh(world_t *world, float **points)
{
    char **sun_grid = calc_sun_grid(world->mesh, world->x, world->y, world);
    my_clear_buffer(world->cam_buf);
    static sfConvexShape *shape = 0; !shape ? shape = sfConvexShape_create(),
    sfConvexShape_setPointCount(shape, 4) : 0;
    int i_v[] = {1, 1, world->x-1, world->y-1, 1, 1};
    char flag = calc_flag(points);
    aply_flags(flag, points, i_v, world->x*world->y);
    sfVector2f **vecs = malloc(sizeof(sfVector2u *) * 4);
    for (int i = 0; i < 4; i++) vecs[i] = malloc(sizeof(sfVector2f));
    for (int i_x = i_v[0]; i_x != i_v[2]; i_x += i_v[4]){
        for (int i_y = i_v[1]; i_y != i_v[3]; i_y += i_v[5]){
            int i = (flag & 0x4) ? i_y+i_x*world->x : i_y*world->y+i_x;
            if (did_we_draw(vecs, points, i, world->x)) continue;
            sfColor color = calc_color(world->mesh, i, world->x, sun_grid);
            draw_shape(shape, vecs, color, world);
        }
    }
    free(vecs[0]), free(vecs[1]), free(vecs[2]), free(vecs[3]), free(vecs);
}

void free_mesh(float **mesh, int x, int y)
{
    int i = 0;
    for (; i < x; i++)
        free(mesh[i]);
    free(mesh);
}

int take_movement_input(float *mat_start, world_t *world)
{
    int mv = 0;
    static sfVector2i mouse_o = {0, 0};
    sfVector2i mouse = sfMouse_getPositionRenderWindow(world->cam);
    if (mouse.x < 0 || mouse.y < 0 || mouse.x > SCREEN_X || mouse.y > SCREEN_Y)
        return (0);
    sfKeyboard_isKeyPressed(sfKeyZ) ? mat3_tz(mat_start, 1), mv = 1 : 0;
    sfKeyboard_isKeyPressed(sfKeyS) ? mat3_tz(mat_start, -1), mv = 1 : 0;
    sfKeyboard_isKeyPressed(sfKeyQ) ? mat3_tx(mat_start, 1), mv = 1 : 0;
    sfKeyboard_isKeyPressed(sfKeyD) ? mat3_tx(mat_start, -1), mv = 1 : 0;
    sfKeyboard_isKeyPressed(sfKeyE) ? mat3_ty(mat_start, 1), mv = 1 : 0;
    sfKeyboard_isKeyPressed(sfKeyA) ? mat3_ty(mat_start, -1), mv = 1 : 0;
    sfKeyboard_isKeyPressed(sfKeyW) ? mat3_rz(mat_start, PI/180), mv = 1 : 0;
    sfKeyboard_isKeyPressed(sfKeyX) ? mat3_rz(mat_start, -PI/180), mv = 1 : 0;
    if (sfMouse_isButtonPressed(sfMouseLeft)){
        float vx = mouse.x - mouse_o.x;
        float vy = mouse.y - mouse_o.y;
        mat3_rx(mat_start, vy/180);
        mat3_ry(mat_start, -vx/180);
        mv = 1;
    }
    mouse_o = mouse;
    return (mv);
}

void init_map(world_t *world)
{
    int size_x = world->x;
    int size_y = world->y;
    float **mesh = create_mesh(world->x, world->y, 7);
    for (int i = 0; i < size_x*size_y; i++){
        int xy[] = {rand()%(size_x-2)+1, rand()%(size_y-2)+1, size_x, size_y};
        drop_water(mesh, xy, 0.5, 0);
    }
    world->mesh = mesh;
    world->sun = 0;
}

void init_cam(world_t *world)
{
    float *mat_start = mat3_init();
    mat3_ttx(mat_start, world->x/2);
    mat3_tty(mat_start, world->y/2);
    mat3_ry(mat_start, -0.01);
    mat3_rx(mat_start, -PI/1.5);
    mat3_tz(mat_start, -100);
    world->mat_start = mat_start;
    sfVideoMode mode = {SCREEN_X, SCREEN_Y, 32};
    world->cam = sfRenderWindow_create(mode, "camera", sfClose, 0);
    world->cam_buf = framebuffer_create(SCREEN_X, SCREEN_Y);
    world->mv = 1;
}

void draw_window(sfRenderWindow *win, framebuffer_t *fb)
{
    static sfSprite *sprite = 0; !sprite ? sprite = sfSprite_create() : 0;
    static sfTexture *texture = 0;
    !texture ? texture = sfTexture_create(SCREEN_X, SCREEN_Y) : 0;

    static char first = 0;
    for (; !first; first = 1){
        sfRenderWindow_setFramerateLimit(win, 60);
        sfSprite_setTexture(sprite, texture, sfTrue);
    }
    sfTexture_updateFromPixels(texture, fb->pixels, SCREEN_X, SCREEN_Y, 0, 0);
    sfRenderWindow_drawSprite(win, sprite, 0);
    sfRenderWindow_display(win);
    sfRenderWindow_clear(win, sfBlack);
}

int main_cam(world_t *world)
{
    int size_x = world->x;
    int size_y = world->y;
    for (int i = 0; i < size_x*size_y/100; i++){
        int xy[] = {rand()%(size_x-2)+1, rand()%(size_y-2)+1, size_x, size_y};
        if (world->mesh[xy[0]][xy[1]] < -20)
            drop_water(world->mesh, xy, 0.5, 0);
    }
    world->mv |= take_movement_input(world->mat_start, world);
    float **points = mesh_to_points(world->mesh, size_x, size_y);
    float **points2 = rotate_points(points, world->mat_start);
    draw_mesh(world, points2+2);
    free_points(points2);
    free_points(points);
    draw_window(world->cam, world->cam_buf);
    world->mv &= 2;
    return (0);
}

world_t *create_world(int x, int y)
{
    world_t *world = malloc(sizeof(world_t));
    world->x = x;
    world->y = y;
    init_map(world);
    init_cam(world);
    init_edit(world);
    return (world);
}

int main(int ac, char **av)
{
    srand(time(0));
    world_t *world = create_world(128, 128);
    for (int frame_nb = 0; frame_nb < 200000000; frame_nb++){
        main_cam(world);
        main_edit(world);
        /*while (sfRenderWindow_pollEvent(window_g, &event))
            if (event.type == sfEvtClosed)
                return (0);*/
    }

    for (int frame_nb = 0; frame_nb < 50000000; frame_nb++){
        //float *mat_inv = mat3_inv(mat_start);
        //float *mat_pos = mat3_multiply(mat_inv, mat_start);
        //free(mat_inv);
    }
    //free_mesh(mesh, size_x, size_y);
    //free(mat_start);
    return (0);
}
