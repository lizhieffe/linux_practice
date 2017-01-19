#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>

constexpr char kPtypeParent[] = "PARENT";
constexpr char kPtypeChild[] = "CHILD";

int main() {
  int fd[2];
  pid_t child_pid;

  const char str[] = "Hello, world!\n";
  char read_buffer[80];
  int nbytes;

  std::string ptype;

  pipe(fd);

  if ((child_pid = fork()) == -1) {
    perror("fork");
    return 1;
  }

  if (child_pid == 0) {
    ptype = kPtypeChild;

    // Child closes the pipe read.
    std::cout << ptype << " closes the pipe read." << std::endl;
    close(fd[0]);

    write(fd[1], str, (strlen(str) + 1));
  } else {
    ptype = kPtypeParent;

    // Parent clodes the pipe write.
    std::cout << ptype << " closes the pipe write." << std::endl;
    close(fd[1]);

    nbytes = read(fd[0], read_buffer, sizeof(read_buffer));
    std::cout << ptype << " read from pipe: " << read_buffer << std::endl;

    // Execute ls command.
    execlp("ls", "ls", (char *)NULL);
  }
  return 0;
}
