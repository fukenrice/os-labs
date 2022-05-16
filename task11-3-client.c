#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int msqid;
    pid_t getpid(void);
    key_t key;
    char pathname[] = "task11-3-server.c";
    int len, maxlen;

    struct msgbuf {
        long mtype;
        struct {
            pid_t pid;
            float finfo;
        } info;
    } clientbuf;

    struct servmsgbuf {
        long mtype;
        float finfo;
    } serverbuf;

    if ((key = ftok(pathname, 0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("Can\'t get msqid\n");
        exit(-1);
    }

    clientbuf.mtype = 2;
    clientbuf.info.pid = getpid();

    printf("Enter float number: ");
    scanf("%f", &(clientbuf.info.finfo));

    len = sizeof(clientbuf.info);

    if (msgsnd(msqid, (struct msgbuf *) &clientbuf, len, 0) < 0) {
        printf("Can\'t send message to queue\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
        exit(-1);
    }

    maxlen = sizeof(serverbuf.finfo);

    if ((len = msgrcv(msqid, &serverbuf, maxlen, getpid(), 0)) < 0) {
        printf("Can't receive message from queue\n");
        exit(-1);
    }

    printf("Server response = \t%f\n", serverbuf.finfo);

    return 0;
}