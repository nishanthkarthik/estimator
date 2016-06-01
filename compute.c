#include <stdio.h>
#include <stdlib.h>

#define INFILE "pre.txt"
#define OUTFILE "post.csv"
#define ARRAY_SIZE 376

void iterate(double data[][ARRAY_SIZE], int nx, int ny, int dx, int dy)
{
    //increment diffs
    ++dx;
    ++dy;

    //bulk
    for (int i = 1; i < nx - 1; ++i)
    {
        for (int j = 1; j < ny - 1; ++j)
        {
            if ((i % dx) || (j % dy))
                data[i][j] = (data[i - 1][j] + data[i + 1][j] + data[i][j - 1] + data[i][j + 1]) * 0.25;
        }
    }

    // j = 0,ny-1 and iterate i
    for (int i = 1; i < nx - 1; ++i)
    {
        if (i % dx)
        {
            data[i][0] = (data[i - 1][0] + data[i + 1][0] + data[i][1]) / 3.0;
            data[i][ny - 1] = (data[i - 1][ny - 1] + data[i + 1][ny - 1] + data[i][ny - 2]) / 3.0;
        }
    }

    // i = 0,nx-1 and iterate j
    for (int j = 1; j < ny - 1; ++j)
    {
        if (j % dy)
        {
            data[0][j] = (data[0][j - 1] + data[0][j + 1] + data[1][j]) / 3.0;
            data[nx - 1][j] = (data[nx - 1][j - 1] + data[nx - 1][j + 1] + data[nx - 2][j]) / 3.0;
        }
    }

}

int main()
{
    FILE* in = fopen(INFILE, "r");
    if (in == NULL)
    {
        printf("%s\n", "error opening file");
        exit(-1);
    }
    char dgt[50];
    static double arr[ARRAY_SIZE][ARRAY_SIZE];

    fgets(dgt, 50, in);
    int nx = atoi(dgt);

    fgets(dgt, 50, in);
    int ny = atoi(dgt);

    fgets(dgt, 50, in);
    int dx = atoi(dgt);

    fgets(dgt, 50, in);
    int dy = atoi(dgt);

    fgets(dgt, 50, in);
    long itr = atol(dgt);

    printf("%d rows, %d cols\n", nx, ny);

    for (int i = 0; i < nx; ++i)
    {
        for (int j = 0; j < ny; ++j)
        {
            fgets(dgt, 50, in);
            arr[i][j] = atof(dgt);
            // printf("%d,%d\n", i, j);
        }
    }

    fclose(in);
    printf("beginning %ld iterations\n", itr);
    for (long i = 0; i < itr; ++i)
    {
        iterate(arr, nx, ny, dx, dy);
    }

    FILE* out = fopen(OUTFILE, "w");
    if (out == NULL)
    {
        printf("%s\n", "error opening file to write");
        exit(-1);
    }
    printf("%s\n", "writing to file");

    for (int i = 0; i < nx; ++i)
    {
        for (int j = 0; j < ny; ++j)
        {
            fprintf(out, "%.17g", arr[i][j]);
            if (j != ny - 1) fprintf(out, ",");
            // printf("%d,%d\n", i, j);
        }
        fprintf(out, "\n");
    }

    return 0;
}
