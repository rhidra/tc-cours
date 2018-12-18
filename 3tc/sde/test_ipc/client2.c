#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct info {
  int pid;
  int data;
} INFO;



int main() {
  int msg_id;

  key_t key = ftok("ipc.c", 0);
  struct msgbuf {
    long mtype;
    INFO data;
  } msg_buf;

  struct msg_buf {
    long mtype;
    int data;
  } msg_buf2;

  if ((msg_id = msgget(key, S_IRUSR | S_IWUSR)) < 0) {
    printf("Erreur 1\n");
    exit(1);
  }

  do {
    msgrcv(msg_id, &msg_buf, sizeof(msg_buf.data), 2, 0);
    if (msg_buf.mtype == 1) {
      printf("Reçu 1 : %d\n", msg_buf.data.data);
    } else if (msg_buf.mtype == 2) {
      printf("Reçu 2 : %d\n", msg_buf.data);
    }
  } while (msg_buf.data.data >= 0);

  return 0;
}
