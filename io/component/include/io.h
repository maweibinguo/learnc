#ifndef IO_H
#define IO_H

#define FILE_NAME "zero.data"

#include "./common.h"

extern void print_title(char * title);

extern void clear_buffer_stdin();

extern size_t write_component_data();

extern header init();

#endif
