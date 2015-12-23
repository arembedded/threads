/* Example code for starting
 * 2 threads and controlling 
 * their run-time frequency.
 *
 * All code provided is as is 
 * and not completely tested
 *
 * Author: Aadil Rizvi
 * Date: 12/22/2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <util/util.h>
#include <sys/time.h>

pthread_t thread1;
pthread_t thread2;

void thread1_main(void);
void thread2_main(void);

void sig_handler(int signum) {
    if (signum != SIGINT) {
        printf("Received invalid signum = %d in sig_handler()\n", signum);
        ASSERT(signum == SIGINT);
    }

    printf("Received SIGINT. Exiting Application\n");

    pthread_cancel(thread1);
    pthread_cancel(thread2);

    exit(0);
}

int main(void) {
    pthread_attr_t attr;
    int status;
 
    signal(SIGINT, sig_handler);

    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, 1024*1024);
   
    printf("Creating thread1\n");
    status = pthread_create(&thread1, &attr, (void*)&thread1_main, NULL);
    if (status != 0) {
        printf("Failed to create thread1 with status = %d\n", status);
        ASSERT(status == 0);
    }    

    printf("Creating thread2\n");
    status = pthread_create(&thread2, &attr, (void*)&thread2_main, NULL);
    if (status != 0) {
        printf("Failed to create thread2 with status = %d\n", status);
        ASSERT(status == 0);
    }    

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    sig_handler(SIGINT);
    
    return 0;
}

void thread1_main(void) {
    unsigned int run_cnt;
    unsigned int exec_period_usecs;
    struct timeval ts;    

    exec_period_usecs = 1000000; /*in micro-seconds*/

    printf("Thread 1 started. Execution period = %d uSecs\n",\
                                           exec_period_usecs);
    run_cnt = 0;

    while(1) {
        usleep(exec_period_usecs);
        gettimeofday(&ts, NULL);
        printf("%06lu.%06lu: --- Thread1 run_cnt = %d ---\n",\
                                           (unsigned int)ts.tv_sec,\
                                           (unsigned int)ts.tv_usec,\
                                           run_cnt);
        run_cnt += 1;
    }
}


void thread2_main(void) {
    unsigned int run_cnt;
    unsigned int exec_period_usecs;
    struct timeval ts;    

    exec_period_usecs = 5000000; /*in micro-seconds*/

    printf("Thread 2 started. Execution period = %d uSecs\n",\
                                           exec_period_usecs);
    run_cnt = 0;

    while(1) {
        usleep(exec_period_usecs);
        gettimeofday(&ts, NULL);
        printf("%06lu.%06lu: --- XXXXXX --- Thread2 run_cnt = %d --- XXXXXX ---\n",\
                                           (unsigned int)ts.tv_sec,\
                                           (unsigned int)ts.tv_usec,\
                                           run_cnt);
        run_cnt += 1;
    }
}
