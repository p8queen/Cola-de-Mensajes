#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct Msm {
    long mtype;
    int litros;
}Msm;

void enviarDatos(int msgid, long tipo){
    struct Msm msm;
    msm.mtype=tipo;
    int i;
    for (i = 0; i < 10; ++i) {
        msm.litros = 10000*i;
        msgsnd(msgid,&msm,sizeof(Msm)-sizeof(long),IPC_NOWAIT);
    }
}

int main(int argc, const char *argv[])
{
    //crear
    key_t clave = ftok("/temp",40);
    int msgid = msgget(clave,IPC_CREAT|0660);
    //envia datos
    enviarDatos(msgid, 1);
    enviarDatos(msgid, 2);
    
    //
    char buffer[12];
    scanf("%s",buffer);
    //liberar
    msgctl(msgid,IPC_RMID,NULL);
    return 0;
}
