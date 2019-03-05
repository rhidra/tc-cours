#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Communication entre deux processus père et fils
// grâce à une file de messages.

int main() {

  int pid, msg_id, note;
  // Génération d'une clé
  key_t key = ftok("ex3.c", 0);

  struct msgbuf{
    long mtype;
    int mnote;
  } msg_buf;

  if((pid = fork()) == 0) { //fils
    if ((msg_id = msgget(key, S_IRUSR | S_IWUSR)) == 0) {
      do{
        sleep(1);
        msgrcv(msg_id, &msg_buf, sizeof(int), 1, 0);
        printf("Reçu %d.\n", msg_buf.mnote);
      } while(msg_buf.mnote >= 0);
    }
  } else if(pid >0) {
    if((msg_id = msgget(key, S_IRUSR | S_IWUSR | IPC_CREAT)) == 0) { // Creation de la file de messages bien passée
      printf("Entrez une suite de notes.\n");
      do {
        scanf("%d", &note);
        msg_buf.mtype = 1;
        msg_buf.mnote = note;
        msgsnd(msg_id, &msg_buf, sizeof(msg_buf.mnote), 0);
      } while(note >=0);
      msgctl(key, IPC_RMID, NULL);
    }
  }


  return 0;
}
