#include "j_csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct df
{
    int column;
    int rows;
    long size;
    FILE *fp;
    char ***data;
    char *filename;
} dataframe;

int get_dframe_size(const dataframe *pd)
{
    return pd->size;
}

int get_dframe_column(const dataframe *pd)
{
    return pd->column;
}

int get_dframe_rows(const dataframe *pd)
{
    return pd->rows;
}

char *get_dframe_filename(const dataframe *pd)
{
    return pd->filename;
}

int get_value_int(const dataframe *pd, const int row, const int column)
{
    char *ptr = pd->data[row][column];
    int value;
    sscanf(ptr, "%d", &value);
    return value;
}

long get_value_long(const dataframe *pd, const int row, const int column)
{
    char *ptr = pd->data[row][column];
    long value;
    sscanf(ptr, "%ld", &value);
    return value;
}

float get_value_float(const dataframe *pd, const int row, const int column)
{
    char *ptr = pd->data[row][column];
    float value;
    sscanf(ptr, "%f", &value);
    return value;
}

double get_value_double(const dataframe *pd, const int row, const int column)
{
    char *ptr = pd->data[row][column];
    double value;
    sscanf(ptr, "%lf", &value);
    return value;
}

char *get_value(const dataframe *pd, const int row, const int column)
{
    char *ptr = pd->data[row][column];
    return ptr;
}

void dframe_shape(const dataframe *pd)
{
    printf("%d x %d\n", pd->rows, pd->column);
}

void dframe_features(const dataframe *pd)
{
    for (int i = 0; i < pd->column; i++)
    {
        printf("%s\t", pd->data[0][i]);
    }
    printf("\n");
}

void dframe_head(const dataframe *pd, int count)
{
    for (int i = 0; i <= count; i++)
    {
        for (int j = 0; j < pd->column; j++)
        {
            printf("%-20s", pd->data[i][j]);
        }
        printf("\n");
    }
}

void dframe_show(const dataframe *pd)
{
    for (int i = 0; i < pd->rows; i++)
    {
        for (int j = 0; j < pd->column; j++)
        {
            printf("%-20s", pd->data[i][j]);
        }
        printf("\n");
    }
}

dataframe *dframe_readcsv(const char *filename, const char sep, const int line_length)
{
    dataframe *dat = (dataframe *)malloc(sizeof(dataframe));
    dat->column = 0;
    dat->rows = 0;
    dat->filename = strdup(filename);
    dat->filename[strcspn(dat->filename, "\n")] = '\0';
    dat->fp = fopen(dat->filename, "r");
    fseek(dat->fp, 0, SEEK_END);
    dat->size = ftell(dat->fp);
    rewind(dat->fp);

    char *rawdata = (char *)malloc(sizeof(char) * dat->size);
    memset(rawdata, 0, dat->size);
    char line[line_length];
    while (fgets(line, line_length, dat->fp) != NULL)
    {
        line[strcspn(line, "\n")] = sep;
        strcat(rawdata, line);
        dat->rows++;
    }
    rewind(dat->fp);
    fgets(line, line_length, dat->fp);
    for (int i = 0; i < strlen(line); i++)
    {
        if (line[i] == sep)
            dat->column++;
    }
    dat->column++;

    dat->data = (char ***)malloc(sizeof(char **) * dat->rows);
    for (int i = 0; i < dat->rows; i++)
    {
        dat->data[i] = (char **)malloc(sizeof(char *) * dat->column);
    }

    char *token = strtok(rawdata, &sep);
    for (int i = 0; i < dat->rows; i++)
    {
        for (int j = 0; j < dat->column; j++)
        {
            dat->data[i][j] = strdup(token);
            token = strtok(0, &sep);
        }
    }
    free(rawdata);

    return dat;
}

void dframe_destroy(dataframe *pd)
{
    for (int i = 0; i < pd->rows; i++)
    {
        for (int j = 0; j < pd->column; j++)
        {
            free(pd->data[i][j]);
        }
        free(pd->data[i]);
    }
    free(pd->data);

    free(pd->filename);
    fclose(pd->fp);
    pd->column = 0;
    pd->rows = 0;
    pd->size = 0;
    free(pd);
}