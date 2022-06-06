#include <signal.h>
#include <stdio.h>
#include <unistd.h>
 
pid_t RECEIVER_PID;
int INPUTED_NUM = 0;
int NUM_OF_BIT = 0;
 
void send_bit() {
  int current_bit = INPUTED_NUM & (1 << NUM_OF_BIT);
 
  if (kill(RECEIVER_PID, (current_bit ? SIGUSR2 : SIGUSR1))) {
    printf("Error occured while sending bit %d to reciever", NUM_OF_BIT);
  }
 
  NUM_OF_BIT++;
}
 
void my_handler(int nsig) {
  if (nsig == SIGUSR1) {
    send_bit();
  }
}
 
int main(void) {
 
  printf("Enter receiver PID: ");
  scanf("%d", &RECEIVER_PID);
 
  printf("Enter number to send: ");
  scanf("%d", &INPUTED_NUM);
 
  (void)signal(SIGUSR1, my_handler);
 
  send_bit();
 
  while(NUM_OF_BIT < 32)
  ;
 
  return 0;
}
