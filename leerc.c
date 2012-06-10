#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>

struct Msm {
    long mtype;
    int litros;
}Msm;

void leerDatos(int msgid,long tipo){
    struct Msm msm;
    int i;    
    for (i = 0; i < 10; ++i) {
        msgrcv(msgid,&msm,sizeof(msm)-sizeof(long),tipo,0);
        printf("tipo mensaje: [%ld] litros: [%d]\n",msm.mtype,msm.litros);
    }

}

int main(int argc, const char *argv[])
{
    //crear
    key_t clave = ftok("/temp",40);
    int msgid = msgget(clave,0660);
    if(msgid<0){
        perror("error en cola\n");exit(1);}
    //envia datos
    leerDatos(msgid, 2);
    leerDatos(msgid, 1);
    
    return 0;
}
