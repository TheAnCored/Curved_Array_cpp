#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "hclass.hpp"

int dance_with_array(const char *filename_input, const char *filename_output);

int reading_rowLen(FILE *pointer);

int *string_len(FILE *pointer, int *strings_array, int rowLen);

List **filling_array(FILE *pointer, List **strings_array, int rowLen);

int search(List **strings_array, int rowLen);

int check_column(List **strings_array, int rowLen, int column);

void writing_to_file(FILE *pointer_out, List **strings_array, int rowLen);

void moving(List **list, int rowLen, int index);