/*
** EPITECH PROJECT, 2019
** my_str_isprintable
** File description:
** hello
*/

typedef struct button
{
    int pos_x;
    int pos_y;
    int size_x;
    int size_y;
    sfColor color1;
    sfColor color2;
    sfColor color3;
    char *txt;
    char on;
} button_t;

typedef struct world
{
    int x;
    int y;
    sfRenderWindow *cam;
    float *mat_start;
    char **sun_grid;
    char mv;
    framebuffer_t *cam_buf;
    sfRenderWindow *edi;
    float **mesh;
    framebuffer_t *edi_buf;
    int edi_x;
    int edi_y;
    int brush;
    int brush_type;
    button_t *edi_buttons;
    sfText *txt;
    sfFont *font;
    int buton_nb;
    float sun;
} world_t;

sfColor calc_color(float **mesh, int i, int x, char **sun_grid);
void drop_water(float **mesh, int *xy, float f, float n);
void draw_window(sfRenderWindow *win, framebuffer_t *fb);
