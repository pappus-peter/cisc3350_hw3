#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ‘int’ constant that will carry the maximum length of a line from 400 to 1000
const int LINE_SIZE = 400;


// 1. The function should return an ‘int’, 
// and the two parameters it accepts are the input file’s descriptor (‘int’) and the buffer where the line will be stored (‘char *’). We call them here fd and buf.
// We call them here fd and buf
int reader_line (int fd, char *buf )
{
    char *buf1 = buf;
    ssize_t ret; 
    short max = LINE_SIZE-1; 
    ret = read (fd, buf1);
    
    while (buf1 != '\n')
    {
        if(ret == -1)
        {
            perror("read");
            return 0; 
        }
        if(max == 0)
        {
            // write(stderr, "the read line is longer than allowed size"); 
            // write(STDERR_FILENO, error_msg, strlen(error_msg));
            char *error_msg = "the read line is longer than allowed size";
            if(write(2, error_msg, strlen(error_msg)) == -1)
            {
                perror("write");
            }
            return 0; 
        }
        max --; 
        buf1 ++;


    }
    
    FILE * file; 
    file = fopen (argv[i], "r"); // file is opened in read mode

    return ret;
}