#include <stdio.h>
#include <stdlib.h>

#define INFILE "pre.txt"
#define OUTFILE "post.csv"
#define ARRAY_SIZE 1000

void iterate(double data[][ARRAY_SIZE], int nx, int ny, int dx, int dy)
{
    for (int i = 0; i < nx; ++i)
    {
        for (int j = 0; j < ny; ++j)
        {
            if (i % (dx + 1) == 0 && j % (dy + 1) == 0)
                continue;
            else if (i == 0 && 0 < j && j < ny)
                data[i][j] = (data[i][j - 1] + data[i][j + 1] + data[i + 1][j]) / 3;
            else if (j == 0 && 0 < i && i < nx)
                data[i][j] = (data[i - 1][j] + data[i + 1][j] + data[i][j + 1]) / 3;
            else if (i == nx - 1 && 0 < j && j < ny)
                data[i][j] = (data[i][j - 1] + data[i][j + 1] + data[i - 1][j]) / 3;
            else if (j == ny - 1 && 0 < i && i < nx)
                data[i][j] = (data[i - 1][j] + data[i + 1][j] + data[i][j - 1]) / 3;
            else
                data[i][j] = (data[i - 1][j] + data[i + 1][j] + data[i][j - 1] + data[i][j + 1]) / 4;
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
    double arr[ARRAY_SIZE][ARRAY_SIZE];

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