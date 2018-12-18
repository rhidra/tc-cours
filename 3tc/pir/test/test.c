#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define BILLION  1E9;

int main() {

    // Calculate time taken by a request
    struct timespec requestStart, requestEnd;
    clock_gettime(CLOCK_REALTIME, &requestStart);

    int a=0, i;
    for (i = 0; i < 10000000; i++) {
        if (a < 500)
            a+=1;
        else
            a+=2;
    }

    clock_gettime(CLOCK_REALTIME, &requestEnd);

    // Calculate time it took
    double accum = ( requestEnd.tv_sec - requestStart.tv_sec )
      + ( requestEnd.tv_nsec - requestStart.tv_nsec )
      / BILLION;

    printf( "%lf\n", accum );
    printf("début = %lf\n", requestStart.tv_nsec);
    printf("fin = %lf\n", requestEnd.tv_nsec);

    return 0;
}
