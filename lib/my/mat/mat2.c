/*
** EPITECH PROJECT, 2019
** my_compute_power_it
** File description:
** hello
*/

float *mat3_init_scale(float s)
{
    float *mat = malloc(sizeof(float) * 16);
    mat[0] = s;
    mat[5] = s;
    mat[11] = s;
    return (mat);
}

float *init_p(void)
{
    float *p = malloc(sizeof(float) * 4);
    memset(p, 0, sizeof(float) * 4);
    p[3] = 1;
    return (p);
}

float *mat3_point(float *mat, float *p)
{
    float *p2 = malloc(sizeof(float)*4);
    p2[0] = 0;
    p2[1] = 0;
    p2[2] = 0;
    p2[3] = 1;

    for (int n = 0; n < 4; n++){
        p2[n] = 0;
        for (int x = 0; x < 4; x++){
            p2[n] += mat[x + n*4] * p[x];
        }
    }
    return (p2);
}
