#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

void HandleSignal(int sig) {
  std::cout << "Ahhh! SIGINT! (" << sig << ")" << std::endl;
}

int main() {
  char s[200];
  struct sigaction sa;

  sa.sa_handler = HandleSignal;
  sa.sa_flags = 0;  // or SA_RESTART
  sigemptyset(&sa.sa_mask);

  // Sets the sa to be the handler of SIGINT.
  if (sigaction(SIGINT, &sa, NULL) == -1) {
    perror("sigaction");
    exit(1);
  }

  printf("Enter a string:\n");

  if (fgets(s, sizeof s, stdin) == NULL)
    perror("fgets");
  else 
    printf("You entered: %s\n", s);

  return 0;
}
