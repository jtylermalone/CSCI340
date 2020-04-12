#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <math.h>


int convert(char* hex) {

    int decimal = 0;

    int length = strlen(hex);

    for (int i = 0; i < length; i++) {

        char digit = hex[length - 1 - i];

        if (digit >= '0' && digit <= '9')
            decimal += (digit - '0') * pow(16, i);
        else
            decimal += (digit - 'A' + 10) * pow(16, i);

    }

    return decimal;

}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: ./HW10 <path_to_file>\n");
        exit(1);
    }
    int l;
    int n;
    int file = open(argv[1], O_RDONLY);
    char *offset_array_size = malloc(4);
    n = read(file, offset_array_size, 4);
    printf("**** 1st 4 bytes: %d\n", *offset_array_size);
    // dividing by 4 here because we're dealing with bytes
    *offset_array_size = *offset_array_size / 4;
    printf("offset array size: %d\n", *offset_array_size);
    int *offset_array = malloc(*offset_array_size);
    for (int i = 0; i < *offset_array_size; i++) {
        int *offset = malloc(4);
        read(file, offset, 4);
        offset_array[i] = *offset;
    }

    for (int i = 0; i < *offset_array_size; i++)
        printf("%d\n", offset_array[i]);
    printf("\n\n\n");
    
    for (int i = 0; i < *offset_array_size; i++) {
        lseek(file, offset_array[i], SEEK_SET);
        int *line_length;
        read(file, line_length, 4);
        printf("%d\n", *line_length);

    }
    

}

