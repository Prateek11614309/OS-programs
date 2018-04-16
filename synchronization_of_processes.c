/*
Brief Description:
Synchronize 1  teacher and 3 students processes
*/
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#define prateek 3
volatile int count_variable=0;
void teacher(int s, siginfo_t *info, void *ptr){
   if (s == SIGUSR2){
      printf("\ncontroller(%d): teacher received signal from student %d process\n",
            (int)getpid(), (int)info->si_pid);
    }
    --count_variable;
 }

 void student(int sig){
    if (sig == SIGUSR1){
      printf("\ncompute(%d): student received  signal from teacher process %d\n",
            (int)getpid(), (int)getppid());
    }
 }

int main(){
    int count;
    pid_t pid[prateek];
    count_variable = prateek;

    struct sigaction p;

    p.sa_flags = SA_SIGINFO | SA_RESTART; 
    p.sa_sigaction = teacher;
    sigaction(SIGUSR2, &p, NULL);

    /* spawned students */
    for (count = 0; count < prateek; count++)
    {
        switch(pid[count] = fork()){
            case -1:
                perror("Fork error");
                exit(1);
            case 0:
                {
                    struct sigaction c;
                    c.sa_flags = 0;
                    c.sa_handler = student;
                    sigaction(SIGUSR1, &c, NULL);
                    pause();
                    sleep(1);
                    printf("Sending student  to teacher (%d)\n", getppid());
                    sleep(count+1);
                    kill(getppid(), SIGUSR2);
                    exit(0);
                    break;
                }
            default:
                break;
        }
 }

    sleep (1); 
    for (count = 0; count < prateek; count++){
        printf ("Sending student to teacher %d\n", (int)pid[count]);
        kill(pid[count], SIGUSR1);
    }

    
    while (count_variable)
    {
         usleep(10000); 
    }

    for (count = 0; count < prateek; count++)
    {
        int status;
        waitpid (pid[count], &status, 0);
        printf ("student process %d executed status=%d\n", pid[count], status);
        kill(pid[count], SIGUSR1);
    }

    return 0;
}

