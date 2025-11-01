#ifndef CSVREADER
#define CSVREADER

typedef struct df dataframe;

int get_dframe_size(const dataframe *);

int get_dframe_column(const dataframe *);

int get_dframe_rows(const dataframe *);

char *get_dframe_filename(const dataframe *);

int get_value_int(const dataframe *, const int row, const int column);

long get_value_long(const dataframe *, const int row, const int column);

float get_value_float(const dataframe *, const int row, const int column);

double get_value_double(const dataframe *, const int row, const int column);

char *get_value(const dataframe *, const int row, const int column);

void dframe_shape(const dataframe *);

void dframe_features(const dataframe *);

void dframe_head(const dataframe *, int count);

void dframe_show(const dataframe *);

dataframe *dframe_readcsv(const char *filename, const char sep, const int line_length);

void dframe_destroy(dataframe *);
#endif