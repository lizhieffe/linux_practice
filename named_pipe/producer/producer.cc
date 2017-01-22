#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "../../american_maid"

int main() {
  char s[1024];
  int num, fd;

  mknod(FIFO_NAME, S_IFIFO | 0666, 0);

  std::cout << "Waiting for the reader..." << std::endl;
  fd = open(FIFO_NAME, O_WRONLY);
  std::cout << "Got a reader, please type in some words." << std::endl;

  while (gets(s), !feof(stdin)) {
    if ((num = write(fd, s, strlen(s))) == -1) {
      perror("write");
    } else {
      printf("speak: wrote %d bytes\n", num);
    }
  }
}
