# J CSV

A .csv reader in C by **Jyotismoy Kalita**

---

## Usage

### Downloading

```sh
git clone https://github.com/JyotismoyKalita/JCSV.git
cd JCSV
```

Copy the `j_csv.c` and `j_csv.h` into your project folder containing the main c file.

### Compiling

```sh
gcc example.c j_csv.c -o example
```

### Executing

```sh
./example
```

## Functions

The datatype used is a user-defined datatype `dataframe`, which contains

- **column**: stores no. of column after reading from a file
- **row**: stores no. of row after reading from a file
- **size**: stores the size of the file after reading from it
- **fp**: the file pointer to the file
- **data**: stores the data that has been read from the file
- **filename**: stores the filename of the file

These data members of the struct are not directly accessible from the main file.

### Reading the CSV File

```c
dframe_readcsv(const char* filename, const char sep, const int line_length)
```

Takes filename, seperator character and max estimated length of a line in the file as the arguments. Returns the pointer to the `dataframe` file.

the `line_length` determines the size of line buffer.  
If the lines aren't that big, `256` is recommended.

If say, `line_length` is given as **64** but in the file, a line is **128** characters long, then the line buffer wont be able to capture the entire line. Hence, always provide a suitable value for `line_length`.


### Freeing the Dataframe

```c
dframe_destroy(dataframe *)
```

Takes the address of the dataframe to be freed as an input.

### Accessing the stored values

The values are stored in a 3-dimensional array of **char**.  
`data` is **char***** type. It points to the array of rows.  
Each row is of **char**** type. They point to the array of columns.  
Each column is of **char*** type. They point to the actual string value.  

But the `data` variable is not accessible directly, hence, we need to use getter functions. These functions takes the address of the dataframe, index of row and index of column as input (**Indexes start at 0**).

#### Get the string value at index: Row, Column

```c
char *get_value(const dataframe *, const int row, const int column)
```

#### Get the int value at index: Row, Column

```c
int get_value_int(const dataframe *, const int row, const int column)
```

#### Get the long value at index: Row, Column

```c
long get_value_long(const dataframe *, const int row, const int column)
```

#### Get the float value at index: Row, Column

```c
float get_value_float(const dataframe *, const int row, const int column)
```

#### Get the double value at index: Row, Column

```c
double get_value_double(const dataframe *, const int row, const int column)
```

More datatype support will be added in future.

## Other Functions

### Getting No. of Columns

```c
int get_dframe_column(const dataframe *)
```

Returns **int** value of the no. of columns of the dataframe whose address is passed as argument

### Getting No. of Rows

```c
int get_dframe_rows(const dataframe *)
```

Returns **int** value of the no. of rows of the dataframe whose address is passed as argument

### Getting the Filename

```c
char* get_dframe_filename(const dataframe *)
```

Returns **char*** value of the name of file used in the dataframe whose address is passed as argument

### Getting the size of file

```c
int get_dframe_size(const dataframe *)
```

Returns **int*** value of the size of file used in the dataframe whose address is passed as argument

### Printing the shape

```c
void dframe_shape(const dataframe *);
```

Prints the Shape ( Row x Column) of the dataframe whose address is passed as argument

### Printing the feature

```c
void dframe_feature(const dataframe *);
```

Prints the features (name of columns / first row) of the dataframe whose address is passed as argument

### Printing the dataframe

```c
void dframe_show(const dataframe *);
```

Prints the entire dataframe whose address is passed as argument

### Printing the top N rows

```c
void dframe_head(const dataframe *, int count);
```

Prints the top `count` no of rows of the dataframe whose address is passed as argument
