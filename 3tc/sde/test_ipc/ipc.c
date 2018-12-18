#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <errno.h>

typedef struct info {
  int pid;
  int data;
} INFO;



int main() {
  int msg_id, msg_id2, i;
  key_t key = ftok("ipc.c", 0);

  struct msgbuf {
    long mtype;
    INFO data;
  } msg_buf;

  struct msg_buf {
    long mtype;
    int data;
  } msg_buf2;

  if ((msg_id = msgget(key, S_IRUSR | S_IWUSR | IPC_CREAT)) < 0) {
    int ersv = errno;
    printf("Erreur 1 : id=%d; errno = %d ; key = %d\n",msg_id, ersv, key);
    exit(1);
  }
  printf("Waiting to start ...\n");
  sleep(5);

  for (i = 0; i < 10; i++) {
    //sleep(1);
    printf("Sending 1 ...\n");
    msg_buf.mtype = 1;
    msg_buf.data.data = 10;
    msgsnd(msg_id, &msg_buf, sizeof(msg_buf.data), 0);

    if (i%2 == 0) {
      printf("Sending 2 ...\n");
      msg_buf.mtype = 2;
      msg_buf.data.data = 5;
      msgsnd(msg_id, &msg_buf, sizeof(msg_buf.data), 0);
    }
  }
  msg_buf.mtype = 1;
  msg_buf.data.data = -1;
  msgsnd(msg_id, &msg_buf, sizeof(msg_buf.data), 0);
  msg_buf.mtype = 2;
  msg_buf.data.data = -1;
  msgsnd(msg_id, &msg_buf, sizeof(msg_buf.data), 0);

  //msgctl(key, IPC_RMID, NULL);

  return 0;
}
