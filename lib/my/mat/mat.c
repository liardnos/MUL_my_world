/*
** EPITECH PROJECT, 2019
** my_compute_power_it
** File description:
** hello
*/

float *mat3_init(void)
{
    float *mat = malloc(sizeof(float) * 16);
    memset(mat, 0, sizeof(float) * 16);
    mat[0] = 1;
    mat[5] = 1;
    mat[10] = 1;
    return (mat);
}

float *mat3_multiply(float *mat1, float *mat2)
{
    float *mat = malloc(sizeof(float) * 16);
    memset(mat, 0, sizeof(float) * 16);
    for (int y = 0; y < 4; y++){
        for (int x = 0; x < 4; x++){
            for (int i = 0; i < 4; i++){
                mat[x+y*4] += mat1[i+y*4] * mat2[x+i*4];
            }
        }
    }
    return (mat);
}

float *mat3_init_x(float a)
{
    float *mat = mat3_init();
    mat[5] = cos(a);
    mat[6] = -sin(a);
    mat[9] = sin(a);
    mat[10] = cos(a);
    return (mat);
}

float *mat3_init_y(float a)
{
    float *mat = mat3_init();
    mat[0] = cos(a);
    mat[2] = sin(a);
    mat[8] = -sin(a);
    mat[10] = cos(a);
    return (mat);
}

float *mat3_init_z(float a)
{
    float *mat = mat3_init();
    mat[0] = cos(a);
    mat[1] = -sin(a);
    mat[4] = sin(a);
    mat[5] = cos(a);
    return (mat);
}
