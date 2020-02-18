float *mat3_init(void)
{
    float *mat = malloc(sizeof(float) * 16);
    memset(mat, 0, sizeof(float) * 16);
    mat[0] = 1;
    mat[5] = 1;
    mat[10] = 1;
    return (mat);
}

void mat3_print(float *mat1)
{
    for (int y = 0; y < 4; y++){
        for (int x = 0; x < 4; x++){
            my_printf("%f | ", mat1[x + y*4]);
        }
        my_printf("\n");
    }
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

//transform the input point
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

float **mat3_points(float *mat, float **ps, int ps_nb)
{
    float **ps2 = malloc(sizeof(float) * (ps_nb+1));
    ps2[ps_nb] = 0;
    for (int i = 0; ps[i]; i++){

    }
}
