#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>


int mainPPID(pid_t Cpid){
    int inputChar = NULL;

    printf("PID pere : %d | PID fils : %d \n", getpid(), Cpid);
    while(inputChar != 'p'){
        scanf("%c", &inputChar);
    }
    kill(Cpid, SIGINT);
    
    wait();

    while (1)
    {
        /* code */
    }
    
    return 0;
}

int mainCPID(){
    printf("\tPPID : %d | PID : %d \n", getppid(), getpid());
    
    sigwait("", SIGINT);

    return 0;
}

int main(int argc, char **argv)
{
    pid_t Ppid = getpid();
    pid_t Cpid = fork();
    

    if(Cpid == 0){
        //Instance du process fils (Cpid pas initialisé)
        return mainCPID();
    }
    else{
        //Instance pere (Cpid initialisé car process crée)
        return mainPPID(Cpid);
    }
}