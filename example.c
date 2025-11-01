#include <stdio.h>
#include "j_csv.h"

int main()
{
    char filename[256];
    printf("Enter filename: ");
    fgets(filename, 256, stdin);
    dataframe *table = dframe_readcsv(filename, ';', 256);
    dframe_shape(table);
    dframe_show(table);
    dframe_destroy(table);
    printf("Name: %s\n", get_value(table, 1, 0));
    printf("Roll NO: %ld\n", get_value_long(table, 1, 1));
    printf("Grade: %lf\n", get_value_double(table, 1, 2));
    return 0;
}