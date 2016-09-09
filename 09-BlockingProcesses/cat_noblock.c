/* cat_noblock.c - open a file and display its contents, but exit rather than
 * wait for input */
 
/* Copyright (C) 1998 by Ori Pomerantz */

#include  <stdio.h>    /* standard I/O */
#include  <fcntl.h>    /* for open */
#include  <unistd.h>   /* for read */
#include  <stdlib.h>   /* for exit */
#include  <errno.h>    /* for errno */

#define MAX_BYTES 1024*4

void main(int  argc, char *argv[])
{
  int     fd; /* The file descriptor for the file to read */
  ssize_t  bytes; /* The number of bytes read */
  char    buffer[MAX_BYTES]; /* The buffer for the bytes */
  /* Usage */
  if (argc != 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    puts("Reads the content of a file, but doesn't wait for input");
    exit(-1);
  }
  /* Open the file for reading in non blocking mode */
  fd = open(argv[1], O_RDONLY | O_NONBLOCK);
  /* If open failed */
  if (fd == -1) {
    if (errno == EAGAIN)
       puts("Open would block");
    else
       puts("Open failed");
    exit(-1);
  }
    /* Read the file and output its contents */
  do {
    int i;
    /* Read characters from the file */
    bytes = read(fd, buffer, MAX_BYTES);
    /* If there's an error, report it and die */
    if (bytes == -1) {
       if (errno == EAGAIN)
         puts("Normally I'd block, but you told me not to");
       else
         puts("Another read error");
       exit(-1);
    }
    /* Print the characters */
    if (bytes > 0) {
       for(i=0; i<bytes; i++)
         putchar(buffer[i]);
    }
    /* While there are no errors and the file isn't over */
  } while (bytes > 0);
}
