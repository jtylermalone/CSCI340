#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {


    if (argc != 2) {
        printf("Usage: ./HW10 <path_to_file>\n");
        exit(1);
    }

    // opening file for reading
    int file = open(argv[1], O_RDONLY);

    // getting file signature... we don't really
    // do anything with this, we just need a place
    // to dispose of the file signature
    char *file_signature = malloc(4);

    // reading 4 bytes of the file signature
    read(file, file_signature, 4);

    // freeing it here... if for some reason you needed
    // the file signature elsewhere, you coulld move this
    // line to the end of the program
    free(file_signature);

    // the next 4 bytes of the file contains the length
    // of the offset array.
    int *offset_array_length = malloc(4);
    read(file, offset_array_length, 4);

    // allocating space for offset array
    int *offset_array = malloc(sizeof(int) * *offset_array_length);

    // this loop loads values into the offset array
    for (int i = 0; i < *offset_array_length; i++) {

        // allocating space for offset array element,
        // reading it in and putting it in the array
        char *line_location = malloc(4);
        read(file, line_location, 4);
        offset_array[i] = *line_location;
    }
    
    // this loop goes through the file and prints 
    // each line.
    for (int i = 0; i < *offset_array_length; i++) {

        // lseek moves the file pointer to the specified
        // offset of bytes. setting the last paramter to
        // SEEK_SET means that lseek will offset from the 
        // start of the file
        lseek(file, offset_array[i], SEEK_SET);
        int *line_length = malloc(4);
        read(file, line_length, 4);

        // this loop actually prints each line. it runs
        // for line_length - 4 because the first 4 bytes
        // of each line define the length of the line. we 
        // don't want to print those characters
        for (int i = 0; i < (*line_length -  4); i++) {
            char *letter = malloc(1);
            read(file, letter, 1);
            printf("%s", letter);
            free(letter); 
        }

        free(line_length);
    }

    free(offset_array_length);
    free(offset_array);
    close(file);
    

}

