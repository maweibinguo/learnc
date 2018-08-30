#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER_LENGTH 1024

int copy_content(char const * desc, char const * source);

char error_msg[255];
void main(int argc, char **argv)
{
    if(argc != 3) {
        printf("enter your desc file and source file");
        exit(EXIT_FAILURE);
    }
    copy_content(*++argv, *++argv);
}

int copy_content(char const * desc, char const * source)
{
    FILE * source_fp, * desc_fp;

    char buffer[MAX_BUFFER_LENGTH];
    if( (source_fp = fopen(source, "r")) == NULL ) {
        sprintf(error_msg, "open source file %s failed", source);
        perror(error_msg);
        exit(EXIT_FAILURE);
    }
    if( (desc_fp = fopen(desc, "w")) == NULL ) {
        perror("open desc file failed");
        exit(EXIT_FAILURE);
    }

    while(fgets(buffer, MAX_BUFFER_LENGTH, source_fp) != NULL) {
        if(fputs(buffer, desc_fp) == EOF) {
            perror("write data failed");
            exit(EXIT_FAILURE);
        }
    }
}
