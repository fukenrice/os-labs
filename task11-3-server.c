#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main() {
    int msqid;
    key_t key;
    char pathname[] = "task11-3-server.c";
    int len, maxlen;

    struct msgbuf {
        long mtype;
        struct {
            pid_t pid;
            float finfo;
        } info;
    } clienbuf;

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

    maxlen = sizeof(clienbuf.info);
    while (true) {

        if ((len = msgrcv(msqid, (struct msgbuf *)&clienbuf, maxlen, -2, 0)) < 0) {
            printf("Can't receive message from queue\n");
            exit(-1);
        }

        if (clienbuf.mtype == 1) {
            printf("Server killed");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(0);
        }

        serverbuf.mtype = clienbuf.info.pid;

        serverbuf.finfo = clienbuf.info.finfo * clienbuf.info.finfo;

        len = sizeof(serverbuf.finfo);

        if (msgsnd(msqid, (struct servmsggbuf *)&serverbuf, len, 0) < 0) {
            printf("Can't send message to queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
            exit(-1);
        }
    }

    return 0;
}
