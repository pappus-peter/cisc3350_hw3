#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX_LINE_LENGTH 400

int read_line(int fd, char *buf) {
    char *buf1 = buf;
    ssize_t ret;
    short max = MAX_LINE_LENGTH - 1;

    ret = read(fd, buf1, 1);
    while (ret != 0 && buf1[0] != '\n') {
        if (ret == -1) {
            perror("read");
            return 0;
        }
        if (max == 0) {
            char *error_msg = "Line too long\n";
            if(write(2, error_msg, strlen(error_msg)) == -1){
                perror("write");
            }
            return 0;
        }
        max--;
        buf1++; 
        ret = read(fd, buf1, 1);
    }

    if(buf1[0] == '\n')
      buf1++;
    buf1[0] = '\0';
    
    return 1;
}

int main(int argc, char **argv) {
    int infile, outfile;

    switch (argc) {
        case 1:
            infile = 0;
            outfile = 1;
            break;
        case 2:
            if (strcmp(argv[1], "-") == 0) {
                infile = 0;
            } else {
                infile = open(argv[1], O_RDONLY);
                if (infile == -1) {
                    perror("open");
                    return EXIT_FAILURE;
                }
            }
            outfile = 1;
            break;
        case 3:
            if (strcmp(argv[1], "-") == 0) {
                infile = 0;
            } else {
                infile = open(argv[1], O_RDONLY);
                if (infile == -1) {
                    perror("open");
                    return EXIT_FAILURE;
                }
            }

            if (strcmp(argv[2], "-") == 0) {
                outfile = 1;
            } else {
                outfile = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
                if (outfile == -1) {
                    perror("open");
                    return EXIT_FAILURE;
                }
            }
            break;

        default:
            char *error_msg = "Cannot accept more than 4 arguments. \n";
            if(write(2, error_msg, strlen(error_msg)) == -1){
                perror("write");
            }
            return EXIT_FAILURE;
    }

    char *buffer1 = (char*) malloc(MAX_LINE_LENGTH * sizeof(char));
    
    if(buffer1 == NULL){
        perror("malloc for buffer1");
        return EXIT_FAILURE;
    }
    char *buffer2 = (char*) malloc(MAX_LINE_LENGTH * sizeof(char));
    
    if(buffer2 == NULL){
        perror("malloc for buffer2");
        return EXIT_FAILURE;
    }

    // read 1st line
    if(read_line(infile, buffer1) == 0){
        perror("read_line1");
        exit(EXIT_FAILURE);
    }
    //printf("Outfile is equal to %d", outfile);
    //printf("Buffer1 is eqqual to %s", buffer1);
    
    
    
    int res = write(outfile, buffer1, strlen(buffer1));
    
    if(res == -1){
        perror("write buffer1");
        exit(EXIT_FAILURE);
    }
    // read 2nd line
    if(read_line(infile, buffer2) == 0){
        perror("read_line2");
        exit(EXIT_FAILURE);
    } 

    // compare 2 lines
    while(buffer2[0] != '\0'){
        if(strcmp(buffer1, buffer2) != 0){
            write(outfile, buffer2, strlen(buffer2)); 

            char *swap = buffer1; 
            buffer1 = buffer2; 
            buffer2 = swap; 
        }
        if(read_line(infile, buffer2) == 0){
        perror("read_line3");
        exit(EXIT_FAILURE);
        } 
    }

    close(infile);
    close(outfile);
    free(buffer1);
    free(buffer2);  
    return EXIT_SUCCESS;    
}

    
