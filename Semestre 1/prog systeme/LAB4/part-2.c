#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>


int mainPPID(pid_t Cpid){
    char fatherPayload[1024];
    sprintf(&fatherPayload, "je suis le pere et mon PID est %d", getpid());
    
    wait();

    FILE *fileP = fopen("fichier.txt","a");
    fputs(fatherPayload, fileP);
    fclose(fileP);

    return 0;
}

int mainCPID(){
    char childPayload[1024];
    sprintf(&childPayload, "je suis le fils et mon PID est %d\n", getpid());
    
    FILE *fileC = fopen("fichier.txt","a");
    fputs(childPayload, fileC);
    fclose(fileC);

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