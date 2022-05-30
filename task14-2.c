#include <signal.h>
#include <stdio.h>

void my_handler(int nsig) {
    if (nsig == 2) {
        printf("Receive signal %d, CTRL-C pressed\n", nsig);
    } else if (nsig == 3) {
        printf("Receive signal %d, CTRL-4 pressed\n", nsig);
    }
}

int main(void) {
  //
  // Set the process response to the SIGINT and SIGQUIT signals.
  //
  (void)signal(SIGINT, my_handler);
  (void)signal(SIGQUIT, my_handler);
  //
  // From this point, the process will print SIGINT and SIGQUIT messages.
  //
  while(1);
  return 0;
}
