#include <signal.h>
#include <stdio.h>
#include <unistd.h>
 
pid_t SENDER_PID;
int INPUTED_NUM = 0;
int NUM_OF_BIT = 0;
 
void my_handler(int nsig) {
  int current_bit = 0;
 
  if (nsig == SIGUSR1) {
    current_bit = 0;
  } else if (nsig == SIGUSR2) {
    current_bit = 1;
  }
 
  if (current_bit == 1) {
    INPUTED_NUM |= (1 << NUM_OF_BIT);
  }
 
  NUM_OF_BIT++;
 
  if (NUM_OF_BIT >= 32) {
    return;
  }
 
  if (kill(SENDER_PID, SIGUSR1)) {
    printf("Error occured while sending request for new bit.");
  }
}
 
int main(void) {
 
  printf("Enter sender PID: ");
  scanf("%d", &SENDER_PID);

  (void)signal(SIGUSR1, my_handler);
  (void)signal(SIGUSR2, my_handler);
 
  while(NUM_OF_BIT < 32)
  ;
 
  printf("Inputed number: %d\n", INPUTED_NUM);
 
  return 0;
}
