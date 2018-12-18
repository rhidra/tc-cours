#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {

  int note, pipe; 
  int res;

  res = access("fifo", F_OK);

  if (res == -1) {
    res = mkfifo("fifo", S_IRUSR | S_IWUSR);
  }

  if(res == 0) { //creation du pipe bien passée
    pipe = open("fifo", O_WRONLY);
    printf("Entrez une suite de notes.\n");
    do {
      scanf("%d", &note);
      write(pipe, &note, sizeof(int)); //ecriture dans le tube
    } while(note >=0);
    close(pipe);
  }


  return 0;
}
